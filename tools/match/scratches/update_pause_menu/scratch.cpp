// update_pause_menu @ 0x4407a0 (thiscall, ret)

#include "game_root.h"

extern char* g_game_base; // data_4df904

void SubPause::update_pause_menu()
{
    unsigned int flags = options_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        options_widget->widget_flags = flags & ~0x20u;
        ((GameRoot*)g_game_base)->options.active = 0;
        GameRoot* game = (GameRoot*)g_game_base;
        game->options.previous_frontend_state =
            game->players[0].frontend_state;
        ((GameRoot*)g_game_base)->players[0].frontend_state = 6;
        return;
    }

    FrontendWidget* resume = resume_widget;
    flags = resume->widget_flags;
    if ((flags & 0x20) != 0) {
        resume->widget_flags = flags & ~0x20u;
        uninit_pause_menu();
        GameRoot* game = (GameRoot*)g_game_base;
        game->subgame.subgame_state = 2;
        ((GameRoot*)g_game_base)->subgame.resume_requested = 1;
        return;
    }

    FrontendWidget* end_game = end_game_widget;
    flags = end_game->widget_flags;
    if ((flags & 0x20) != 0) {
        end_game->widget_flags = flags & ~0x20u;
        GameRoot* game = (GameRoot*)g_game_base;
        game->exit_controller.previous_frontend_state =
            game->players[0].frontend_state;
        game = (GameRoot*)g_game_base;
        if (game->subgame.level_mode == 7) {
            game->exit_controller.state = 7;
        } else if (game->subgame.replay_launch_from_frontend == 1) {
            game->exit_controller.state = 3;
        } else {
            game->exit_controller.state = 2;
        }
        GameRoot* result_game = (GameRoot*)g_game_base;
        result_game->subgame.subgame_rebuild_selector = 2;
        ((GameRoot*)g_game_base)->players[0].frontend_state = 8;
    }
}
