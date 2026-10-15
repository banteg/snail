// Opt-in mobile content layer (extras.h). Wraps the narrow seams listed in
// port/wrapped.txt; every wrapper delegates to its *_recovered body when
// g_port_extras is false.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archive_index.h"
#include "extras.h"
#include "game_root.h"
#include "landscape_manager.h"
#include "loading_bar.h"
#include "object_render_types.h"
#include "rmath_random.h"
#include "rstring.h"
#include "segment_cache.h"
#include "sub_tracks.h"
#include "subgame_runtime.h"
#include "texture_registry.h"
#include "track.h"

extern char g_level_file_text_buffer[];

char archive_or_file_exists_recovered(char* path, char force_filesystem)
    __asm__("_Z32archive_or_file_exists_recoveredPcc");
char* load_file_bytes_from_archive_or_fs_recovered(char* file_name, char* buffer, int* out_size)
    __asm__("_Z44load_file_bytes_from_archive_or_fs_recoveredPcS_Pi");
char* load_file_bytes_fixed_size_from_archive_or_fs_recovered(char* file_name, char* buffer, int byte_count)
    __asm__("_Z55load_file_bytes_fixed_size_from_archive_or_fs_recoveredPcS_i");
void track_change_recovered(cRTrack* self, int texture_set)
    __asm__("_ZN7cRTrack16Change_recoveredEi");
void subtracks_init_recovered(cRSubTracks* self, char* filename)
    __asm__("_ZN11cRSubTracks14Init_recoveredEPc");
void subgame_start_level_recovered(cRSubGame* self, int level_index)
    __asm__("_ZN9cRSubGame20StartLevel_recoveredEi");

void* allocate_tracked_memory(int size, char* name);
void xor_archive_bytes_in_place(int start_offset, char* bytes, int count);

bool g_port_extras = false;

namespace {

const int kMobileTrackSetCount = 7;
const int kRandomTrackSetCode = 8;

ArchiveIndex* g_extras_archive_index = 0;
FILE* g_extras_archive_file = 0;
unsigned char* g_fringe_colours_tga = 0;

cRTexture* g_extra_track_textures[kMobileTrackSetCount];
cRTexture* g_extra_slide_textures[kMobileTrackSetCount];
bool g_random_fringe_pending = false;

bool path_equals_ignore_case(const char* a, const char* b)
{
    while (*a && *b) {
        char ca = (*a >= 'a' && *a <= 'z') ? (char)(*a - ('a' - 'A')) : *a;
        char cb = (*b >= 'a' && *b <= 'z') ? (char)(*b - ('a' - 'A')) : *b;
        if (ca == '\\')
            ca = '/';
        if (cb == '\\')
            cb = '/';
        if (ca != cb)
            return false;
        ++a;
        ++b;
    }
    return *a == 0 && *b == 0;
}

const ArchiveEntry* find_extras_archive_entry(const char* path)
{
    if (!g_extras_archive_index || !g_extras_archive_file)
        return 0;
    for (int i = 0; i < g_extras_archive_index->count; ++i) {
        if (path_equals_ignore_case(g_extras_archive_index->entries[i].path, path))
            return &g_extras_archive_index->entries[i];
    }
    return 0;
}

// Android cRSubGame::GetSkirtColourRandom (0006c624): samples RGB from
// Sprites/FringeColours.tga at (int)(width * t) * 4 + 0x12.
void sample_skirt_colour_random(tColour* out, float t)
{
    if (!g_fringe_colours_tga)
        return;
    if (t < 0.0f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;
    unsigned int width = (unsigned int)g_fringe_colours_tga[12] | ((unsigned int)g_fringe_colours_tga[13] << 8);
    unsigned int index = (unsigned int)((float)width * t);
    if (index >= width)
        index = width - 1;
    unsigned int offset = 0x12 + index * 4;
    out->r = (float)g_fringe_colours_tga[offset + 0] / 255.0f;
    out->g = (float)g_fringe_colours_tga[offset + 1] / 255.0f;
    out->b = (float)g_fringe_colours_tga[offset + 2] / 255.0f;
    out->a = 0.4f;
}

void refresh_built_level_skirt_colours(cRSubGame* subgame)
{
    tColour skirt_color;
    tColour* resolved = subgame->GetSkirtColour(&skirt_color);
    for (int row = 0; row < subgame->runtime_row_count; ++row) {
        subgame->runtime_rows[row].attachment_body.color = *resolved;
        for (int lane = 0; lane < SUBGAME_TRACK_LANE_COUNT; ++lane) {
            cRSubLoc& cell = subgame->runtime_cells[row][lane];
            if (cell.fringe_front)
                cell.fringe_front->color = *resolved;
            if (cell.fringe_right)
                cell.fringe_right->color = *resolved;
            if (cell.fringe_left)
                cell.fringe_left->color = *resolved;
            if (cell.fringe_back)
                cell.fringe_back->color = *resolved;
        }
    }
    for (int row = 0; row < TRACK_RENDER_CACHE_ROW_COUNT; ++row)
        subgame->segment_cache.slots[row][TRACK_RENDER_CACHE_FRINGE].color = *resolved;
}

int parse_arcade_number(const char* filename)
{
    if (strncasecmp(filename, "Arcade", 6) != 0)
        return -1;
    if (strncasecmp(filename, "ArcadePro", 9) == 0 || strncasecmp(filename, "ArcadeExtra", 11) == 0)
        return -1;
    const char* p = filename + 6;
    if (!isdigit((unsigned char)p[0]) || !isdigit((unsigned char)p[1]) || !isdigit((unsigned char)p[2]))
        return -1;
    return (p[0] - '0') * 100 + (p[1] - '0') * 10 + (p[2] - '0');
}

}  // namespace

bool extras_init_archive()
{
    if (!g_port_extras)
        return true;
    FILE* f = fopen("SnailMailExtras.dat", "rb");
    if (!f) {
        fprintf(stderr, "snail: --extras requires SnailMailExtras.dat (run `uv run snail port extras`)\n");
        return false;
    }
    char probe[0x10];
    if (fread(probe, 1, sizeof(probe), f) == sizeof(probe)) {
        xor_archive_bytes_in_place(0, probe, sizeof(probe));
        int header_bytes = ((SerializedArchiveIndex*)probe)->entries[0].data_offset;
        if (header_bytes >= (int)sizeof(probe) && header_bytes < 4 * 1024 * 1024) {
            SerializedArchiveIndex* raw = (SerializedArchiveIndex*)malloc(header_bytes);
            if (raw) {
                fseek(f, 0, SEEK_SET);
                fread(raw, 1, header_bytes, f);
                xor_archive_bytes_in_place(0, (char*)raw, header_bytes);
                ArchiveIndex* idx = (ArchiveIndex*)raw;
                for (int i = 0; i < idx->count; ++i)
                    idx->entries[i].path += (int)idx;
                g_extras_archive_index = idx;
                g_extras_archive_file = f;
            }
        }
    }
    if (!g_extras_archive_file) {
        fclose(f);
        fprintf(stderr, "snail: invalid SnailMailExtras.dat\n");
        return false;
    }
    const ArchiveEntry* entry = find_extras_archive_entry("Sprites/FringeColours.tga");
    if (!entry || entry->byte_count < 0x12 + 32 * 4) {
        fprintf(stderr, "snail: SnailMailExtras.dat is missing Sprites/FringeColours.tga\n");
        return false;
    }
    g_fringe_colours_tga = (unsigned char*)malloc(entry->byte_count);
    if (!g_fringe_colours_tga)
        return false;
    fseek(g_extras_archive_file, entry->data_offset, SEEK_SET);
    fread(g_fringe_colours_tga, 1, entry->byte_count, g_extras_archive_file);
    xor_archive_bytes_in_place(entry->data_offset, (char*)g_fringe_colours_tga, entry->byte_count);
    return true;
}

ArchiveIndex* extras_get_archive_index()
{
    return g_extras_archive_index;
}

void extras_init_assets()
{
    if (!g_port_extras)
        return;
    for (int i = 0; i < 4; ++i) {
        g_extra_track_textures[i] = g_game->track.track_textures[i];
        g_extra_slide_textures[i] = g_game->track.slide_textures[i];
    }
    g_extra_track_textures[4] = g_texture_refs.Add((char*)"Objects/World00/Track4.tga", 0, 0);
    g_extra_slide_textures[4] = g_texture_refs.Add((char*)"Objects/World00/Slide4.tga", 0, 0);
    g_extra_track_textures[5] = g_texture_refs.Add((char*)"Objects/World00/Track5.tga", 0, 0);
    g_extra_slide_textures[5] = g_texture_refs.Add((char*)"Objects/World00/Slide5.tga", 0, 0);
    g_extra_track_textures[6] = g_texture_refs.Add((char*)"Objects/World00/Track6.tga", 0, 0);
    g_extra_slide_textures[6] = g_texture_refs.Add((char*)"Objects/World00/Slide6.tga", 0, 0);
    // The recovered road meshes tile with negative and repeated UVs. Match
    // the PC track textures instead of using Add's default clamped sampler.
    for (int i = 4; i < kMobileTrackSetCount; ++i) {
        g_extra_track_textures[i]->flags |= TEXTURE_REF_WRAP_ADDRESSING;
        g_extra_slide_textures[i]->flags |= TEXTURE_REF_WRAP_ADDRESSING;
        g_extra_track_textures[i]->mip_levels = 2;
        g_extra_slide_textures[i]->mip_levels = 2;
    }
    extras_init_paths();
    extras_init_pro();
}

const char* extras_track_texture_name(int slot)
{
    if (slot >= 0 && slot < 4 && g_game && g_game->track.track_textures[slot])
        return g_game->track.track_textures[slot]->name;
    if (g_port_extras && slot >= 0 && slot < kMobileTrackSetCount && g_extra_track_textures[slot])
        return g_extra_track_textures[slot]->name;
    return "?";
}

char __cdecl archive_or_file_exists(char* path, char force_filesystem)
{
    if (g_port_extras && force_filesystem == 0 && find_extras_archive_entry(path))
        return 1;
    return archive_or_file_exists_recovered(path, force_filesystem);
}

char __cdecl archive_or_file_exists(char* path, int force_filesystem)
{
    return archive_or_file_exists(path, (char)force_filesystem);
}

char* __cdecl load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, int* out_size)
{
    if (g_port_extras) {
        if (const ArchiveEntry* entry = find_extras_archive_entry(file_name)) {
            g_loading_bar.AI();
            if (out_size)
                *out_size = entry->byte_count;
            if (buffer == (char*)-1)
                return (char*)entry->data_offset;
            char* dst = buffer ? buffer : (char*)allocate_tracked_memory(entry->byte_count, file_name);
            fseek(g_extras_archive_file, entry->data_offset, SEEK_SET);
            fread(dst, 1, entry->byte_count, g_extras_archive_file);
            xor_archive_bytes_in_place(entry->data_offset, dst, entry->byte_count);
            return dst;
        }
    }
    return load_file_bytes_from_archive_or_fs_recovered(file_name, buffer, out_size);
}

char* __cdecl load_file_bytes_from_archive_or_fs(char* file_name, void* buffer, int* out_size)
{
    return load_file_bytes_from_archive_or_fs(file_name, (char*)buffer, out_size);
}

char* __cdecl load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, void* out_size)
{
    return load_file_bytes_from_archive_or_fs(file_name, buffer, (int*)out_size);
}

char* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(char* file_name, char* buffer, int byte_count)
{
    if (g_port_extras) {
        if (const ArchiveEntry* entry = find_extras_archive_entry(file_name)) {
            g_loading_bar.AI();
            if (buffer == (char*)-1)
                return (char*)entry->data_offset;
            char* dst = buffer ? buffer : (char*)allocate_tracked_memory(byte_count, file_name);
            fseek(g_extras_archive_file, entry->data_offset, SEEK_SET);
            fread(dst, 1, byte_count, g_extras_archive_file);
            xor_archive_bytes_in_place(entry->data_offset, dst, byte_count);
            return dst;
        }
    }
    return load_file_bytes_fixed_size_from_archive_or_fs_recovered(file_name, buffer, byte_count);
}

char* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(char* file_name, char* buffer, unsigned int byte_count)
{
    return load_file_bytes_fixed_size_from_archive_or_fs(file_name, buffer, (int)byte_count);
}

// Android cRTrack::Change (0003f330): supports Track: 0-6 and 8 (random 0-6).
void cRTrack::Change(int texture_set)
{
    if (!g_port_extras) {
        track_change_recovered(this, texture_set);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        g_extra_track_textures[i] = track_textures[i];
        g_extra_slide_textures[i] = slide_textures[i];
    }
    int selected = current_texture_set;
    switch (texture_set) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        selected = texture_set;
        break;
    case kRandomTrackSetCode:
        selected = (int)RAND((float)kMobileTrackSetCount, 0);
        break;
    default:
        break;
    }
    int previous = current_texture_set;
    if (selected != previous && selected >= 0 && selected < kMobileTrackSetCount
        && previous >= 0 && previous < kMobileTrackSetCount
        && g_extra_track_textures[selected] && g_extra_slide_textures[selected]) {
        g_object_list.ReTextureObjects(g_extra_track_textures[selected], g_extra_track_textures[previous]);
        g_object_list.ReTextureObjects(g_extra_slide_textures[selected], g_extra_slide_textures[previous]);
        current_texture_set = selected;
    }
}

// Android cRSubTracks::Init(char*) (000850d4): Track: 0-6, Track: r -> 8,
// Fringe: random, and the mobile postal level colour assignments.
void cRSubTracks::Init(char* filename)
{
    subtracks_init_recovered(this, filename);
    if (!g_port_extras)
        return;

    char* cursor = Rstrfind((char*)"Track:", g_level_file_text_buffer);
    if (cursor != 0) {
        cursor = Rstrfind((char*)":", cursor) + 1;
        while (*cursor == ' ' || *cursor == '\t')
            ++cursor;
        char ch = *cursor;
        if (ch >= '0' && ch <= '6')
            track_texture_set = ch - '0';
        else if (ch == 'r' || ch == 'R')
            track_texture_set = kRandomTrackSetCode;
    }

    char level_path[256];
    snprintf(level_path, sizeof(level_path), "Levels/%s", filename);
    bool from_base_archive = !find_extras_archive_entry(level_path);
    if (from_base_archive) {
        int arcade = parse_arcade_number(filename);
        if ((arcade >= 21 && arcade <= 25) || (arcade >= 41 && arcade <= 45)) {
            track_texture_set = 3;
        } else if (arcade >= 46 && arcade <= 50) {
            track_texture_set = 4;
            if (arcade == 50)
                fringe_color.store_color4f(255.0f / 255.0f, 250.0f / 255.0f, 50.0f / 255.0f, 1.0f);
        }
    }

    bool random_fringe = false;
    cursor = Rstrfind((char*)"Fringe:", g_level_file_text_buffer);
    if (cursor != 0) {
        cursor = Rstrfind((char*)":", cursor) + 1;
        while (*cursor == ' ' || *cursor == '\t')
            ++cursor;
        if (*cursor == 'r' || *cursor == 'R')
            random_fringe = true;
    }
    if (from_base_archive && path_equals_ignore_case(filename, "Challenge000.txt"))
        random_fringe = true;

    if (this == &g_game->subgame.level_definition)
        g_random_fringe_pending = random_fringe;
    extras_map_level_paths(this);
}

// Android cRSubGame::StartLevel (000817ac): when Track: r (8) or Fringe: random
// is active, pick the random background, backdrop flip, and random fringe colour.
void cRSubGame::StartLevel(int level_index)
{
    extras_clear_tramp_rings();
    subgame_start_level_recovered(this, level_index);
    if (!g_port_extras)
        return;

    if (level_definition.track_texture_set == kRandomTrackSetCode) {
        int landscape_index = 0;
        switch ((unsigned int)RAND(4.0f, 0)) {
        case 0:
            landscape_index = g_game->subgame.landscape_manager.Import((char*)"SpaceBluesWhorl.txt");
            break;
        case 1:
            landscape_index = g_game->subgame.landscape_manager.Import((char*)"SpaceGreenWarp.txt");
            break;
        case 2:
            landscape_index = g_game->subgame.landscape_manager.Import((char*)"SpacePurple.txt");
            break;
        case 3:
            landscape_index = g_game->subgame.landscape_manager.Import((char*)"SpaceRed.txt");
            break;
        }
        landscape_manager.Init(landscape_index);
        g_game->backdrop.pending_flip = (RAND(1.0f, 0) > 0.5f) ? 1 : 0;
        sample_skirt_colour_random(&level_definition.fringe_color, RAND(1.0f, 0));
        refresh_built_level_skirt_colours(this);
    } else if (g_random_fringe_pending) {
        sample_skirt_colour_random(&level_definition.fringe_color, RAND(1.0f, 0));
        refresh_built_level_skirt_colours(this);
    }
    g_random_fringe_pending = false;
}
