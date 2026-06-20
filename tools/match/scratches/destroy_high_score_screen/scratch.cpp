// destroy_high_score_screen @ 0x417220 (thiscall, ret)

#include "border_manager.h"
#include "high_score_screen.h"

int HighScoreScreen::destroy_high_score_screen()
{
    g_high_score_selected_bank = selected_bank;
    ((BorderManager*)(g_game_base + 0xb4c))->kill_all_borders();
    *(char*)(g_game_base + 0x30d) = 0;
    *(int*)(g_game_base + 0x310) = 0;
    return 0;
}
