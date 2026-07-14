// update_pause_menu @ 0x4407a0 (thiscall, ret)

#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void SubPause::update_pause_menu()
{
    unsigned int flags = options_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        options_widget->widget_flags = flags & ~0x20u;
        g_game->options.active = 0;
        GameRoot* game = g_game;
        game->options.previous_frontend_state =
            game->players[0].frontend_state;
        g_game->players[0].frontend_state = 6;
        return;
    }

    FrontendWidget* resume = resume_widget;
    flags = resume->widget_flags;
    if ((flags & 0x20) != 0) {
        resume->widget_flags = flags & ~0x20u;
        uninit_pause_menu();
        GameRoot* game = g_game;
        game->subgame.subgame_state = 2;
        g_game->subgame.resume_requested = 1;
        return;
    }

    FrontendWidget* end_game = end_game_widget;
    flags = end_game->widget_flags;
    if ((flags & 0x20) != 0) {
        end_game->widget_flags = flags & ~0x20u;
        GameRoot* game = g_game;
        game->exit_controller.previous_frontend_state =
            game->players[0].frontend_state;
        game = g_game;
        if (game->subgame.level_mode == 7) {
            game->exit_controller.state = 7;
        } else if (game->subgame.replay_launch_from_frontend == 1) {
            game->exit_controller.state = 3;
        } else {
            game->exit_controller.state = 2;
        }
        GameRoot* result_game = g_game;
        result_game->subgame.subgame_rebuild_selector = 2;
        g_game->players[0].frontend_state = 8;
    }
}
