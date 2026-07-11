// exit_high_score_screen @ 0x417b50 (thiscall, ret)

#include "game_root.h"
#include "high_score.h"

int HighScore::exit_high_score_screen()
{
    GameRoot* game = (GameRoot*)g_game_base;
    if (game->subgame.level_mode == 0) {
        game->players[0].frontend_state = 2;
        ((GameRoot*)g_game_base)->subgame.subgame_rebuild_selector = 2;
        ((GameRoot*)g_game_base)->players[0].redispatch_requested = 1;
        game = (GameRoot*)g_game_base;
    }

    if (game->subgame.level_mode == 1) {
        game->players[0].frontend_state = 10;
        game = (GameRoot*)g_game_base;
        ((GameRoot*)g_game_base)->subgame.subgame_rebuild_selector = 2;
        ((GameRoot*)g_game_base)->players[0].redispatch_requested = 1;
    }

    return (int)game;
}
