// update_main_menu @ 0x419e00 (thiscall, ret)

#include "game_root.h"


void MainMenu::update_main_menu()
{
    unsigned int flags = new_game_widget->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        new_game_widget->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_main_menu();
        g_game->players[0].frontend_state = 2;
        g_game->players[0].redispatch_requested = 1;
        return;
    }

    FrontendWidget* credits = credits_widget;
    flags = credits->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        credits->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_main_menu();
        g_game->players[0].frontend_state = 14;
        g_game->players[0].redispatch_requested = 1;
        return;
    }

    FrontendWidget* exit = exit_widget;
    flags = exit->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        exit->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        GameRoot* game = g_game;
        game->exit_controller.previous_frontend_state =
            game->players[0].frontend_state;
        g_game->exit_controller.prompt_y = exit_widget->layout_y;
        g_game->exit_controller.state = 10;
        g_game->players[0].frontend_state = 8;
        return;
    }

    FrontendWidget* options = options_widget;
    flags = options->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        options->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        g_game->options.active = 1;
        GameRoot* game = g_game;
        game->options.previous_frontend_state =
            game->players[0].frontend_state;
        g_game->players[0].frontend_state = 6;
        return;
    }

    FrontendWidget* high_scores = high_scores_widget;
    int result = high_scores->widget_flags;
    if ((result & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        high_scores->widget_flags =
            result & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        destroy_main_menu();
        g_game->players[0].frontend_state = 18;
        g_game->high_score.mode = 0;
    }
}
