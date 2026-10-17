// Mobile content layer for the Ultimate profile (extras.h, profile.h). Wraps
// the narrow seams listed in port/wrapped.txt; every wrapper delegates to its
// *_recovered body in the Original profile.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archive_index.h"
#include "extras.h"
#include "font_system.h"
#include "game_root.h"
#include "landscape_manager.h"
#include "loading_bar.h"
#include "runtime_config.h"
#include "object_render_types.h"
#include "ring_special_effect_types.h"
#include "rmath_random.h"
#include "rstring.h"
#include "segment_cache.h"
#include "sub_tracks.h"
#include "subgame_runtime.h"
#include "texture_registry.h"
#include "track.h"

extern char g_level_file_text_buffer[];
void backdrop_render_recovered(cRBackdrop* self) __asm__("_ZN10cRBackdrop25render_backdrop_recoveredEv");
void sm_tracks_import_recovered(cRSMTracks* self) __asm__("_ZN10cRSMTracks16Import_recoveredEv");
void* load_config_file_recovered(char* name, void* bytes) __asm__("_Z26load_config_file_recoveredPcPv");
int write_file_bytes_recovered(char* name, void* bytes, int count) __asm__("_Z26write_file_bytes_recoveredPcPvi");

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
void subgame_add_ring_recovered(cRSubGame* self, cRSubLoc* cell, int requested_kind, cRSubGoldy* player, float ring_speed)
    __asm__("_ZN9cRSubGame17AddRing_recoveredEP8cRSubLociP10cRSubGoldyf");
void sub_ring_init_recovered(cRSubRing* self, int lives_snapshot)
    __asm__("_ZN9cRSubRing14Init_recoveredEi");

void* allocate_tracked_memory(int size, char* name);
void xor_archive_bytes_in_place(int start_offset, char* bytes, int count);

namespace {

const int kMobileTrackSetCount = 7;
const int kRandomTrackSetCode = 8;

ArchiveIndex* g_extras_archive_index = 0;
FILE* g_extras_archive_file = 0;
unsigned char* g_fringe_colours_tga = 0;

cRTexture* g_extra_track_textures[kMobileTrackSetCount];
cRTexture* g_extra_slide_textures[kMobileTrackSetCount];
bool g_random_fringe_pending = false;
float g_add_ring_speed = 0.0f;

// Android cRSubTracks::Init (000850d4) imports Padding, a four-row empty
// segment, beside every level's segments; BuildLevel lays it between each pair
// of segments a Random: level picks (port/patches/04-challenge-padding.patch).
// Its slot here is the first unused one, after the level's own.
SubSegment* g_padding_segment = 0;
bool g_padding_turn = false;
int g_padding_picks = 0;

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

}  // namespace

void extras_import_padding(cRSubTracks* level_definition)
{
    g_padding_segment = 0;
    int slot = level_definition->segment_count;
    if (!g_port_ultimate || level_definition->random_enabled != 1
        || slot >= (int)(sizeof(level_definition->segment_slots) / sizeof(SubSegment)))
        return;
    g_padding_segment = &level_definition->segment_slots[slot];
    level_definition->ImportSegment((char*)"padding.txt", g_padding_segment);
}

SubSegment* extras_next_padding()
{
    if (!g_padding_segment)
        return 0;
    g_padding_turn = !g_padding_turn;
    if (g_padding_turn)
        return 0;
    ++g_padding_picks;
    return g_padding_segment;
}

void extras_begin_level_build()
{
    g_padding_turn = false;
    g_padding_picks = 0;
}

int extras_padding_pick_count()
{
    return g_padding_picks;
}

// Enumerate the combined segment names before any level is parsed. Mobile
// definitions take precedence for shared names; the mobile set has every PC
// name, so no PC layout is left in the catalog.
void cRSMTracks::Import()
{
    if (!g_port_ultimate || this != &g_game->subgame.sm_tracks) {
        sm_tracks_import_recovered(this);
        return;
    }
    ArchiveIndex* saved = g_archive_index_records;
    ArchiveIndex* merged = (ArchiveIndex*)malloc(sizeof(int) + SMTRACK_SEGMENT_CAPACITY * sizeof(ArchiveEntry));
    if (!merged) abort();
    merged->count = 0;
    ArchiveIndex* indexes[2] = {saved, extras_get_archive_index()};
    for (int bank = 0; bank < 2; ++bank) {
        for (int i = 0; i < indexes[bank]->count; ++i) {
            ArchiveEntry entry = indexes[bank]->entries[i];
            if (strncasecmp(entry.path, "Segments/", 9) != 0)
                continue;
            int slot = 0;
            while (slot < merged->count && !path_equals_ignore_case(merged->entries[slot].path, entry.path))
                ++slot;
            if (slot == merged->count) {
                if (merged->count >= SMTRACK_SEGMENT_CAPACITY - 1) {
                    fprintf(stderr, "snail: mobile segment catalog exceeds capacity\n");
                    abort();
                }
                ++merged->count;
            }
            merged->entries[slot] = entry;
        }
    }
    g_archive_index_records = merged;
    sm_tracks_import_recovered(this);
    g_archive_index_records = saved;
    free(merged);
}

const char* extras_save_path(const char* name)
{
    if (g_port_ultimate) {
        if (path_equals_ignore_case(name, "SnailMail.cfg")) return "SnailMailMobile.cfg";
        if (path_equals_ignore_case(name, "ScoreA.dat")) return "ScoreMobileA.dat";
        if (path_equals_ignore_case(name, "ScoreB.dat")) return "ScoreMobileB.dat";
        if (path_equals_ignore_case(name, "ScoreC.dat")) return "ScoreMobileC.dat";
    }
    return name;
}

void* load_config_file(char* file_name, void* buffer)
{
    const char* mapped = extras_save_path(file_name);
    if (g_port_ultimate && path_equals_ignore_case(file_name, "SnailMail.cfg")
        && !archive_or_file_exists_recovered((char*)mapped, 1)) {
        // Carry display/audio preferences across once, but start the mobile
        // campaign, tutorial included, separately. Do not rewrite the classic
        // save.
        void* result = load_config_file_recovered(file_name, buffer);
        if (buffer == &g_runtime_config) {
            g_runtime_config.highest_galaxy_route_index = 1;
            g_runtime_config.landscape_backdrop_variant_selector = 1;
            g_runtime_config.new_game_tutorial_started = 0;
        }
        return result;
    }
    return load_config_file_recovered((char*)mapped, buffer);
}

int write_file_bytes(char* path, void* bytes, int byte_count)
{
    return write_file_bytes_recovered((char*)extras_save_path(path), bytes, byte_count);
}

bool extras_init_archive()
{
    if (!g_port_ultimate)
        return true;
    FILE* f = fopen("SnailMailExtras.dat", "rb");
    if (!f) {
        fprintf(stderr, "snail: the ultimate profile needs SnailMailExtras.dat (run `uv run snail port extras`)\n");
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
    if (!g_port_ultimate)
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
    if (g_port_ultimate && slot >= 0 && slot < kMobileTrackSetCount && g_extra_track_textures[slot])
        return g_extra_track_textures[slot]->name;
    return "?";
}

char __cdecl archive_or_file_exists(char* path, char force_filesystem)
{
    path = (char*)extras_save_path(path);
    if (g_port_ultimate && force_filesystem == 0 && find_extras_archive_entry(path))
        return 1;
    return archive_or_file_exists_recovered(path, force_filesystem);
}

char* __cdecl load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, int* out_size)
{
    file_name = (char*)extras_save_path(file_name);
    if (g_port_ultimate) {
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

char* __cdecl load_file_bytes_fixed_size_from_archive_or_fs(char* file_name, char* buffer, int byte_count)
{
    file_name = (char*)extras_save_path(file_name);
    if (g_port_ultimate) {
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

// Android cRTrack::Change (0003f330): supports Track: 0-6 and 8 (random 0-6).
void cRTrack::Change(int texture_set)
{
    if (!g_port_ultimate) {
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
    if (!g_port_ultimate)
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

    bool random_fringe = false;
    cursor = Rstrfind((char*)"Fringe:", g_level_file_text_buffer);
    if (cursor != 0) {
        cursor = Rstrfind((char*)":", cursor) + 1;
        while (*cursor == ' ' || *cursor == '\t')
            ++cursor;
        if (*cursor == 'r' || *cursor == 'R')
            random_fringe = true;
    }
    if (this == &g_game->subgame.level_definition) {
        g_random_fringe_pending = random_fringe;
        extras_import_padding(this);
    }
    extras_map_level_paths(this);
}

// Android cRSubGame::StartLevel (000817ac): when Track: r (8) or Fringe: random
// is active, pick the random background, backdrop flip, and random fringe colour.
void cRSubGame::StartLevel(int level_index)
{
    extras_clear_tramp_rings();
    extras_begin_level_build();
    bool new_game = subgame_rebuild_selector == 3;
    subgame_start_level_recovered(this, level_index);
    if (!g_port_ultimate)
        return;

    // Android BuildLevel (0007e88c) starts a new game with 8 lives in the Pro
    // galaxy and 3, as Windows does, in the postal one.
    if (new_game && extras_is_pro_mode())
        player.visible_life_stock = 8;

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

// The Windows cRSubGame::AddRing gives every ring a phase and a phase step,
// and cRSubRing::AI swings an active ring across the track as Sin(phase) * 3
// when oscillate_x is set, but nothing on Windows sets it. Android's AddRing
// (00073290) sets it for every ring before cRSubRing::Init, with three step
// changes: kinds 5, 6 and 8 hold still when the segment row gave no RingSpeed=
// (Windows would divide by zero), kind 7 always holds still, and kind 2 is
// centred and still in the tutorial (level mode 7).
void cRSubGame::AddRing(cRSubLoc* cell, int requested_kind, cRSubGoldy* player, float ring_speed)
{
    g_add_ring_speed = ring_speed;
    subgame_add_ring_recovered(this, cell, requested_kind, player, ring_speed);
}

void cRSubRing::Init(int lives_snapshot)
{
    if (g_port_ultimate) {
        oscillate_x = 1;
        switch (kind) {
        case SUB_RING_KIND_EXPLODE_RAMP:
            if (g_game->subgame.level_mode == 7) {
                active_phase = 0.0f;
                active_phase_step = 0.0f;
            }
            break;
        case SUB_RING_KIND_NORMAL_AUTHORED:
        case SUB_RING_KIND_EXPLODE_AUTHORED:
        case SUB_RING_KIND_POWER_UP_AUTHORED:
            if (g_add_ring_speed == 0.0f)
                active_phase_step = 0.0f;
            break;
        case SUB_RING_KIND_SLOW_AUTHORED:
            active_phase_step = 0.0f;
            break;
        default:
            break;
        }
    }
    sub_ring_init_recovered(this, lives_snapshot);
}

__attribute__((export_name("snail_swaying_ring_count")))
int extras_swaying_ring_count()
{
    int swaying = 0;
    for (int i = 0; i < SUB_RING_POOL_CAPACITY; ++i) {
        const cRSubRing& ring = g_game->subgame.ring_effects.slots[i];
        if (ring.state == SUB_RING_STATE_ACTIVE && ring.oscillate_x)
            ++swaying;
    }
    return swaying;
}

// Lateral x of the first swinging ring, or 0 when none is active.
__attribute__((export_name("snail_swaying_ring_x")))
float extras_swaying_ring_x()
{
    for (int i = 0; i < SUB_RING_POOL_CAPACITY; ++i) {
        const cRSubRing& ring = g_game->subgame.ring_effects.slots[i];
        if (ring.state == SUB_RING_STATE_ACTIVE && ring.oscillate_x)
            return ring.transform.position.x;
    }
    return 0.0f;
}

// PC single-texture backdrops contain a 320x240 image inside a 512x256
// allocation. Converted Pro skies fill their texture, as on Android, so they
// need normalized UVs for the complete image, including horizontal flips.
void cRBackdrop::render_backdrop()
{
    cRTexture* texture = active_primary_texture_id >= 0 && active_primary_texture_id < SPRITE_TEXTURE_CAPACITY
        ? g_sprite_texture_table[active_primary_texture_id] : 0;
    if (!g_port_ultimate || !texture
        || (!path_equals_ignore_case(texture->name, "Backgrounds/SpacePro.tga")
            && !path_equals_ignore_case(texture->name, "Backgrounds/SpacePro2.tga"))) {
        backdrop_render_recovered(this);
        return;
    }
    tColour color;
    color.Set(1.0f, 1.0f, 1.0f, 1.0f);
    for (int y = 0; y < 7; ++y) {
        for (int x = 0; x < 7; ++x) {
            const BackdropDistortCell& tl = distort_grid[y][x];
            const BackdropDistortCell& tr = distort_grid[y][x + 1];
            const BackdropDistortCell& br = distort_grid[y + 1][x + 1];
            const BackdropDistortCell& bl = distort_grid[y + 1][x];
            float x0 = (float)x * 91.4285736f;
            float x1 = (float)(x + 1) * 91.4285736f;
            float y0 = (float)y * 68.5714264f;
            float y1 = (float)(y + 1) * 68.5714264f;
            float u0 = (float)x / 7.0f;
            float u1 = (float)(x + 1) / 7.0f;
            if (active_flip) {
                u0 = 1.0f - u0;
                u1 = 1.0f - u1;
            }
            OSDPrintUV(
                active_primary_texture_id,
                x0 + tl.current_x_offset, y0 + tl.current_y_offset,
                x1 + tr.current_x_offset, y0 + tr.current_y_offset,
                x1 + br.current_x_offset, y1 + br.current_y_offset,
                x0 + bl.current_x_offset, y1 + bl.current_y_offset,
                0, 0, 0x8000000, &color,
                u0, (float)y / 7.0f, u1, (float)(y + 1) / 7.0f, 0, 0);
        }
    }
}
