// load_level_definitions @ 0x448900 (thiscall, receiver unused)

#include "rshell.h"
#include "sub_tracks.h"
#include "segment_catalog_types.h"
#include "game_root.h"

void cRSMTracks::OpenLevels()
{
    int count;
    char names[0x80][0x80];

    enumerate_matching_archive_or_fs_entries("Levels", "*.txt", &count, names);

    int index = 0;
    if (count > 0) {
        char* name = names[0];
        do {
            g_game->subgame.level_definition_scratch.Init(name);
            ++index;
            name += 0x80;
        } while (index < count);
    }
}
