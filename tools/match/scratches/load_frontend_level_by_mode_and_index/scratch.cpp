// load_frontend_level_by_mode_and_index @ 0x443650 (thiscall, ret 0x8)

#include "sub_tracks.h"

int sprintf(char* buffer, char* format, ...);

extern char g_arcade_level_format[]; // 0x4a5014
extern char g_arcade_extra_level_path[]; // 0x4a5000
extern char g_challenge_level_path[]; // 0x4a4fd4
extern char g_tutorial_level_path[]; // 0x4a4fc4
extern char g_arcade000_level_path[]; // 0x4a4fb4
extern char g_time_trial_extra_level_format[]; // 0x4a4fe8

void SubTracks::load_frontend_level_by_mode_and_index(
    int mode,
    int level_index)
{
    char path[128];

    switch (mode) {
    case 0:
        if (level_index <= 50) {
            sprintf(path, g_arcade_level_format, level_index);
        } else {
            if (level_index == 51)
                sprintf(path, g_arcade_extra_level_path);
        }
        break;

    case 4:
        if (level_index <= 50)
            sprintf(path, g_arcade_level_format, level_index);
        else
            sprintf(path, g_time_trial_extra_level_format, level_index - 50);
        break;

    case 1:
        sprintf(path, g_challenge_level_path);
        break;

    case 7:
        sprintf(path, g_tutorial_level_path);
        break;

    case 2:
    case 3:
        sprintf(path, g_arcade000_level_path);
        break;

    default:
        break;
    }

    load_level_definition_file(path);
}
