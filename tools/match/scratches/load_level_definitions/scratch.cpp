// load_level_definitions @ 0x448900 (cdecl)

#include "level_definition_loader.h"

extern char* g_game_base; // data_4df904

void enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int* out_count,
    char* out_names); // @ 0x431740

int load_level_definitions()
{
    int count;
    char names[0x4000];

    enumerate_matching_archive_or_fs_entries("Levels", "*.txt", &count, names);

    int result = count;
    int index = 0;
    if (count > 0) {
        char* name = names;
        do {
            ((LevelDefinitionLoader*)(g_game_base + 0x224804))->load_level_definition_file(name);
            result = count;
            ++index;
            name += 0x80;
        } while (index < count);
    }
    return result;
}
