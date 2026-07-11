// update_main_menu @ 0x419e00 (thiscall, ret)

#include "game_root.h"

extern char* g_game_base; // data_4df904

void MainMenu::update_main_menu()
{
    unsigned int flags = new_game_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        new_game_widget->widget_flags = flags & ~0x20u;
        destroy_main_menu();
        ((GameRoot*)g_game_base)->players[0].frontend_state = 2;
        ((GameRoot*)g_game_base)->players[0].redispatch_requested = 1;
        return;
    }

    FrontendWidget* credits = credits_widget;
    flags = credits->widget_flags;
    if ((flags & 0x20) != 0) {
        credits->widget_flags = flags & ~0x20u;
        destroy_main_menu();
        ((GameRoot*)g_game_base)->players[0].frontend_state = 14;
        ((GameRoot*)g_game_base)->players[0].redispatch_requested = 1;
        return;
    }

    FrontendWidget* exit = exit_widget;
    flags = exit->widget_flags;
    if ((flags & 0x20) != 0) {
        exit->widget_flags = flags & ~0x20u;
        GameRoot* game = (GameRoot*)g_game_base;
        game->exit_prompt.previous_frontend_state =
            game->players[0].frontend_state;
        ((GameRoot*)g_game_base)->exit_prompt.prompt_y = exit_widget->layout_y;
        ((GameRoot*)g_game_base)->exit_prompt.state = 10;
        ((GameRoot*)g_game_base)->players[0].frontend_state = 8;
        return;
    }

    FrontendWidget* options = options_widget;
    flags = options->widget_flags;
    if ((flags & 0x20) != 0) {
        options->widget_flags = flags & ~0x20u;
        ((GameRoot*)g_game_base)->options_menu.active = 1;
        GameRoot* game = (GameRoot*)g_game_base;
        game->options_menu.previous_frontend_state =
            game->players[0].frontend_state;
        ((GameRoot*)g_game_base)->players[0].frontend_state = 6;
        return;
    }

    FrontendWidget* high_scores = high_scores_widget;
    int result = high_scores->widget_flags;
    if ((result & 0x20) != 0) {
        high_scores->widget_flags = result & ~0x20u;
        destroy_main_menu();
        ((GameRoot*)g_game_base)->players[0].frontend_state = 18;
        ((GameRoot*)g_game_base)->high_score_screen.mode = 0;
    }
}
