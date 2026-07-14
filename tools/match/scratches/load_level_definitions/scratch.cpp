// load_level_definitions @ 0x448900 (thiscall, receiver unused)

#include "sub_tracks.h"
#include "segment_catalog_types.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int* out_count,
    char* out_names); // @ 0x431740

void SMTracks::load_level_definitions()
{
    int count;
    char names[0x4000];

    enumerate_matching_archive_or_fs_entries("Levels", "*.txt", &count, names);

    int index = 0;
    if (count > 0) {
        char* name = names;
        do {
            g_game->subgame.level_definition_scratch.load_level_definition_file(name);
            ++index;
            name += 0x80;
        } while (index < count);
    }
}
