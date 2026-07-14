// destroy_high_score_screen @ 0x417220 (thiscall, ret)

#include "border_manager.h"
#include "game_root.h"
#include "high_score.h"

extern GameRoot* g_game; // data_4df904

void HighScore::destroy_high_score_screen()
{
    g_runtime_config.high_score_selected_bank = selected_bank;
    g_game->border_manager.kill_all_borders();
    g_game->players[0].high_score_entry_pending = 0;
    g_game->players[0].high_score_entry_rank = 0;
}
