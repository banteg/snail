// exit_high_score_screen @ 0x417b50 (thiscall, ret)

#include "game_root.h"
#include "high_score.h"

extern GameRoot* g_game; // data_4df904

void HighScore::exit_high_score_screen()
{
    GameRoot* game = g_game;
    if (game->subgame.level_mode == 0) {
        game->players[0].frontend_state = 2;
        g_game->subgame.subgame_rebuild_selector = 2;
        g_game->players[0].redispatch_requested = 1;
        game = g_game;
    }

    if (game->subgame.level_mode == 1) {
        game->players[0].frontend_state = 10;
        game = g_game;
        g_game->subgame.subgame_rebuild_selector = 2;
        g_game->players[0].redispatch_requested = 1;
    }

}
