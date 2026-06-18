// exit_high_score_screen @ 0x417b50 (thiscall, ret)

#include "high_score_screen.h"

int HighScoreScreen::exit_high_score_screen()
{
    HighScoreGameView* game = (HighScoreGameView*)g_game_base;
    if (game->selected_subgame_mode == 0) {
        game->frontend_next_state = 2;
        ((HighScoreGameView*)g_game_base)->ordinary_rebuild_selector = 2;
        ((HighScoreGameView*)g_game_base)->frontend_state_dirty = 1;
        game = (HighScoreGameView*)g_game_base;
    }

    if (game->selected_subgame_mode == 1) {
        game->frontend_next_state = 10;
        game = (HighScoreGameView*)g_game_base;
        ((HighScoreGameView*)g_game_base)->ordinary_rebuild_selector = 2;
        ((HighScoreGameView*)g_game_base)->frontend_state_dirty = 1;
    }

    return (int)game;
}
