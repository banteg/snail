// update_pause_menu @ 0x4407a0 (thiscall, ret)

#include "completion_screen.h"

extern char* g_game_base; // data_4df904

void* PauseMenu::update_pause_menu()
{
    unsigned int flags = options_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        options_widget->widget_flags = flags & ~0x20u;
        ((CompletionGameView*)g_game_base)->options_menu.active = 0;
        CompletionGameView* game = (CompletionGameView*)g_game_base;
        game->options_menu.previous_frontend_state = game->frontend_next_state;
        ((CompletionGameView*)g_game_base)->frontend_next_state = 6;
        return game;
    }

    FrontendWidget* resume = resume_widget;
    flags = resume->widget_flags;
    if ((flags & 0x20) != 0) {
        resume->widget_flags = flags & ~0x20u;
        uninit_pause_menu();
        CompletionGameView* game = (CompletionGameView*)g_game_base;
        game->subgame_resume_state = 2;
        ((CompletionGameView*)g_game_base)->subgame_resume_requested = 1;
        return game;
    }

    FrontendWidget* end_game = end_game_widget;
    void* result = (void*)end_game->widget_flags;
    if (((unsigned int)result & 0x20) != 0) {
        end_game->widget_flags = (unsigned int)result & ~0x20u;
        CompletionGameView* game = (CompletionGameView*)g_game_base;
        game->exit_prompt.previous_frontend_state = game->frontend_next_state;
        game = (CompletionGameView*)g_game_base;
        if (game->selected_subgame_mode == 7) {
            game->exit_prompt.state = 7;
        } else if (game->replay_launch_from_frontend == 1) {
            game->exit_prompt.state = 3;
        } else {
            game->exit_prompt.state = 2;
        }
        CompletionGameView* result_game = (CompletionGameView*)g_game_base;
        result_game->ordinary_rebuild_selector = 2;
        ((CompletionGameView*)g_game_base)->frontend_next_state = 8;
        result = result_game;
    }
    return result;
}
