// allocate_border @ 0x4032a0 (thiscall, ret)

#include "border_manager.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

int report_errorf(char* format, ...);

FrontendWidget* BorderManager::allocate_border()
{
    for (int i = 0; i < 150; ++i) {
        if (borders[i].flags == 0) {
            borders[i].created_time = g_game->frame_counter;
            return (FrontendWidget*)&borders[i];
        }
    }

    report_errorf("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    return 0;
}
