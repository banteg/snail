// allocate_border @ 0x4032a0 (thiscall, ret)

#include "border_manager.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

BorderRecord* BorderManager::allocate_border()
{
    for (int i = 0; i < 150; ++i) {
        if (borders[i].flags == 0) {
            borders[i].created_time = *(int*)(g_game_base + 0x51c);
            return &borders[i];
        }
    }

    report_errorf("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    return 0;
}
