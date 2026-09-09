// Isolated loader comparison. IO/resource resolvers are explicit harness seams.
// Original-code executions and this harness receive no reconstruction credit.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "game_root.h"
#include "landscape_manager.h"

struct InputFile { char name[128]; unsigned int size; char bytes[4096]; };
static InputFile inputs[256];
static int input_count;
static char paths[63][128];
static int path_count;
static FILE* events;
static FILE* output;
static int diagnostic_count;
static char model_names[128][128];
static int model_count;
cRGame* g_game;
char* g_current_level_definition_name;
char g_level_file_text_buffer[0x2800];

static void require(int condition, const char* message)
{
    if (!condition) { printf("HARNESS FAILURE: %s\n", message); exit(2); }
}
static int equal(const char* a, const char* b) { return _stricmp(a, b) == 0; }
static void event(const char* kind, const char* value)
{
    fprintf(events, "%s:%s\n", kind, value);
}
static void* load(char* path, void* destination, int* size)
{
    event("file", path);
    for (int i = 0; i < input_count; ++i) {
        if (equal(path, inputs[i].name)) {
            require(destination != 0, "caller must supply a buffer");
            // Deterministic zero tail is fixture setup, not archive-loader behavior.
            memset(destination, 0, 4096);
            memcpy(destination, inputs[i].bytes, inputs[i].size);
            if (size) *size = inputs[i].size;
            return destination;
        }
    }
    return 0;
}
int load_file_bytes_from_archive_or_fs(char* path, char* destination, void* size)
{ return (int)load(path, destination, (int*)size); }
void* load_file_bytes_from_archive_or_fs(char* path, void* destination, int* size)
{ return load(path, destination, size); }
void enumerate_matching_archive_or_fs_entries(char* directory, char* pattern,
                                               int* count, char* names)
{
    require(equal(directory, "Segments") && equal(pattern, "*.txt"), "enumeration request");
    *count = 0;
    for (int i = 0; i < input_count; ++i) {
        if (_strnicmp(inputs[i].name, "SEGMENTS/", 9) == 0) {
            require(*count < 150, "catalog capacity");
            strcpy(names + 128 * (*count)++, inputs[i].name + 9);
        }
    }
}
extern "C" void loader_error(char* format, va_list args)
{
    char text[2048]; vsprintf(text, format, args);
    ++diagnostic_count; event("error", text);
}
extern "C" int report_errorf(char* format, ...)
{
    va_list args; va_start(args, format); loader_error(format, args); va_end(args);
    return 0;
}
int report_warningf(char* format, ...)
{
    char text[2048]; va_list args; va_start(args, format);
    vsprintf(text, format, args); va_end(args);
    ++diagnostic_count; event("warning", text); return 0;
}
int cRDirectX::ModelAdd(char* name)
{
    event("model", name);
    for (int i = 0; i < model_count; ++i) if (equal(model_names[i], name)) return i;
    require(model_count < 128 && strlen(name) < 128, "model table capacity");
    strcpy(model_names[model_count], name); return model_count++;
}
int cRPathManager::NameCode(char* name)
{
    event("path", name);
    for (int i = 0; i < path_count; ++i) if (equal(paths[i], name)) return i;
    require(0, "unknown path would reach native null table tail"); return -1;
}
static int resource_id(char* name)
{
    unsigned int id = 0;
    for (; *name; ++name) {
        unsigned char c = *name;
        if (c >= 'a' && c <= 'z') c -= 32;
        id = id * 31 + c;
    }
    return (int)(id & 0x7fffffff);
}
int cRLandscapeManager::Import(char* name)
{ event("landscape", name); return resource_id(name); }
int find_registered_sound_sample_id_by_name(char* name)
{ event("sound", name); return resource_id(name); }

static void word(unsigned int value)
{ require(fwrite(&value, 4, 1, output) == 1, "write word"); }
// Lossless sparse encoding relative to the fixture fill byte. Every byte of
// the supplied region is covered; omitted spans reconstruct as that byte.
static void region(const char* tag, const void* memory, unsigned int size, unsigned char fill)
{
    char name[128]; memset(name, 0, sizeof(name)); strcpy(name, tag);
    require(fwrite(name, sizeof(name), 1, output) == 1, "write region name");
    word(size); word(fill);
    const unsigned char* bytes = (const unsigned char*)memory;
    unsigned int i = 0;
    while (i < size) {
        if (bytes[i] == fill) { ++i; continue; }
        unsigned int start = i++;
        while (i < size && bytes[i] != fill) ++i;
        word(start); word(i - start);
        require(fwrite(bytes + start, i - start, 1, output) == 1, "write region span");
    }
    word(0xffffffff);
}
static void normalize_segment(SubSegment& segment)
{
    unsigned int p = (unsigned int)segment.source_name;
    unsigned int base = (unsigned int)&g_game->subgame.sm_tracks;
    if (p >= base && p < base + sizeof(cRSMTracks))
        segment.source_name = (char*)(p - base);
}
int main(int argc, char** argv)
{
    require(argc == 4 || argc == 5, "usage: fixture output events [corrupt]");
    FILE* bundle = fopen(argv[1], "rb"); require(bundle != 0, "open input bundle");
    require(fread(&path_count, 4, 1, bundle) == 1 && path_count <= 63 && path_count > 0, "path count");
    require(fread(paths, 128, path_count, bundle) == (unsigned)path_count, "path names");
    require(fread(&input_count, 4, 1, bundle) == 1 && input_count <= 256 && input_count > 0, "file count");
    for (int i = 0; i < input_count; ++i) {
        require(fread(inputs[i].name, 128, 1, bundle) == 1, "file name");
        require(fread(&inputs[i].size, 4, 1, bundle) == 1 && inputs[i].size < 4096, "file size");
        require(fread(inputs[i].bytes, inputs[i].size, 1, bundle) == 1, "file bytes");
    }
    require(fgetc(bundle) == EOF, "trailing bundle data"); fclose(bundle);
    output = fopen(argv[2], "wb"); events = fopen(argv[3], "wb");
    require(output && events, "open outputs");
    g_game = (cRGame*)calloc(1, sizeof(cRGame));
    cRSubTracks* level = (cRSubTracks*)malloc(sizeof(cRSubTracks));
    require(g_game && level, "fixture allocation");
    int cases = 0;
    for (int seed = 0; seed < 2; ++seed) {
        unsigned char fill = seed ? 0xa5 : 0;
        model_count = 0;
        memset(&g_game->subgame.sm_tracks, fill, sizeof(cRSMTracks));
        g_game->subgame.sm_tracks.Import();
        if (argc == 5 && seed == 0) g_game->subgame.sm_tracks.entries[0].id ^= 1;
        region("catalog", &g_game->subgame.sm_tracks, sizeof(cRSMTracks), fill);
        if (argc == 5 && seed == 0) g_game->subgame.sm_tracks.entries[0].id ^= 1;
        for (int active = 0; active < 2; ++active) {
            for (i = 0; i < input_count; ++i) {
                if (_strnicmp(inputs[i].name, "LEVELS/", 7) != 0) continue;
                memset(level, fill, sizeof(cRSubTracks));
                memset(&g_game->subgame.galaxy, 0, sizeof(g_game->subgame.galaxy));
                g_game->subgame.galaxy.active = (char)active;
                memset(g_level_file_text_buffer, 0, sizeof(g_level_file_text_buffer));
                event("case", inputs[i].name);
                level->Init(inputs[i].name + 7);
                event("current-level", g_current_level_definition_name);
                require(level->segment_count >= 0 && level->segment_count <= 100, "segment count");
                for (int slot = 0; slot < 100; ++slot) normalize_segment(level->segment_slots[slot]);
                normalize_segment(level->first_segment); normalize_segment(level->last_segment);
                region(inputs[i].name, level, sizeof(cRSubTracks), fill);
                region("galaxy", &g_game->subgame.galaxy, sizeof(g_game->subgame.galaxy), 0);
                ++cases;
            }
        }
    }
    free(level); free(g_game);
    require(fclose(output) == 0 && fclose(events) == 0, "close outputs");
    printf("loaders cases=%d diagnostics=%d\n", cases, diagnostic_count);
    fflush(0);
    return 0;
}
