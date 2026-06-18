// update_main_menu @ 0x419e00 (thiscall, ret)

#include "completion_screen.h"

extern char* g_game_base; // data_4df904

void MainMenu::update_main_menu()
{
    unsigned int flags = new_game_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        new_game_widget->widget_flags = flags & ~0x20u;
        destroy_main_menu();
        ((CompletionGameView*)g_game_base)->frontend_next_state = 2;
        ((CompletionGameView*)g_game_base)->frontend_state_dirty = 1;
        return;
    }

    FrontendWidget* credits = credits_widget;
    flags = credits->widget_flags;
    if ((flags & 0x20) != 0) {
        credits->widget_flags = flags & ~0x20u;
        destroy_main_menu();
        ((CompletionGameView*)g_game_base)->frontend_next_state = 14;
        ((CompletionGameView*)g_game_base)->frontend_state_dirty = 1;
        return;
    }

    FrontendWidget* exit = exit_widget;
    flags = exit->widget_flags;
    if ((flags & 0x20) != 0) {
        exit->widget_flags = flags & ~0x20u;
        CompletionGameView* game = (CompletionGameView*)g_game_base;
        game->exit_prompt.previous_frontend_state = game->frontend_next_state;
        ((CompletionGameView*)g_game_base)->exit_prompt.prompt_y = exit_widget->layout_y;
        ((CompletionGameView*)g_game_base)->exit_prompt.state = 10;
        ((CompletionGameView*)g_game_base)->frontend_next_state = 8;
        return;
    }

    FrontendWidget* options = options_widget;
    flags = options->widget_flags;
    if ((flags & 0x20) != 0) {
        options->widget_flags = flags & ~0x20u;
        ((CompletionGameView*)g_game_base)->options_menu.active = 1;
        CompletionGameView* game = (CompletionGameView*)g_game_base;
        game->options_menu.previous_frontend_state = game->frontend_next_state;
        ((CompletionGameView*)g_game_base)->frontend_next_state = 6;
        return;
    }

    FrontendWidget* high_scores = high_scores_widget;
    int result = high_scores->widget_flags;
    if ((result & 0x20) != 0) {
        high_scores->widget_flags = result & ~0x20u;
        destroy_main_menu();
        ((CompletionGameView*)g_game_base)->frontend_next_state = 18;
        ((CompletionGameView*)g_game_base)->high_score_screen.mode = 0;
    }
}
