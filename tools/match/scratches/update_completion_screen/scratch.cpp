// update_completion_screen @ 0x4067e0 (thiscall, ret)

#include "completion_screen.h"

int CompletionPrompt::update_completion_screen()
{
    FrontendWidget* button;
    unsigned int flags;

    switch (state) {
    case 9:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((CompletionGameView*)g_game_base)->frontend_quit_mode = 3;
        }
        break;

    case 10:
        ((CompletionGameView*)g_game_base)->main_menu.update_main_menu();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((CompletionGameView*)g_game_base)->main_menu.destroy_main_menu();
            if (((CompletionGameView*)g_game_base)->frontend_quit_mode == 0)
                ((CompletionGameView*)g_game_base)->frontend_quit_mode = 1;
        }
        break;

    case 11:
        ((CompletionGameView*)g_game_base)->galaxy.update_galaxy();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            ((CompletionGameView*)g_game_base)->galaxy.destroy_galaxy();
            ((CompletionGameView*)g_game_base)->subgame.complete_subgame(1);
            if (((CompletionGameView*)g_game_base)->frontend_state_dirty == 1) {
                previous_frontend_state =
                    ((CompletionGameView*)g_game_base)->frontend_next_state;
                destroy_completion_screen();
                ((CompletionGameView*)g_game_base)->subgame.destroy_subgame();
            } else {
                destroy_completion_screen();
                ((CompletionGameView*)g_game_base)->subgame.destroy_subgame();
                ((CompletionGameView*)g_game_base)->frontend_next_state = 2;
            }
        }
        break;

    case 2:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            ((CompletionGameView*)g_game_base)->subgame.complete_subgame(1);
            if (((CompletionGameView*)g_game_base)->frontend_state_dirty == 1) {
                previous_frontend_state =
                    ((CompletionGameView*)g_game_base)->frontend_next_state;
                destroy_completion_screen();
                ((CompletionGameView*)g_game_base)->pause_menu.uninit_pause_menu();
                ((CompletionGameView*)g_game_base)->pause_menu_active = 0;
                g_sprite_manager.set_sprite_manager_paused(0);
                ((CompletionGameView*)g_game_base)->subgame.destroy_subgame();
            } else {
                destroy_completion_screen();
                ((CompletionGameView*)g_game_base)->pause_menu.uninit_pause_menu();
                ((CompletionGameView*)g_game_base)->pause_menu_active = 0;
                g_sprite_manager.set_sprite_manager_paused(0);
                ((CompletionGameView*)g_game_base)->subgame.destroy_subgame();
                int mode = ((CompletionGameView*)g_game_base)->selected_subgame_mode;
                if (mode == 4 || mode == 1)
                    ((CompletionGameView*)g_game_base)->subgame.initialize_subgame();
                else
                    ((CompletionGameView*)g_game_base)->frontend_next_state = 2;
            }
        }
        break;

    case 7:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((CompletionGameView*)g_game_base)->pause_menu.uninit_pause_menu();
            ((CompletionGameView*)g_game_base)->pause_menu_active = 0;
            g_sprite_manager.set_sprite_manager_paused(0);
            ((CompletionGameView*)g_game_base)->subgame.destroy_subgame();
            ((CompletionGameView*)g_game_base)->frontend_next_state = 2;
        }
        break;

    case 3:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((CompletionGameView*)g_game_base)->pause_menu.uninit_pause_menu();
            ((CompletionGameView*)g_game_base)->pause_menu_active = 0;
            g_sprite_manager.set_sprite_manager_paused(0);
            ((CompletionGameView*)g_game_base)->subgame.destroy_subgame();
            ((CompletionGameView*)g_game_base)->frontend_next_state =
                ((CompletionGameView*)g_game_base)->replay_launch_return_state;
        }
        break;

    case 4:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((CompletionGameView*)g_game_base)->subgame.destroy_subgame();
            ((CompletionGameView*)g_game_base)->frontend_next_state = 2;
        }
        break;

    case 8:
        ((CompletionGameView*)g_game_base)->new_game_menu.update_new_game_menu();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            launch_alpha72_url("Alpha72.url");
            ((CompletionGameView*)g_game_base)->frontend_next_state = 0;
            ((CompletionGameView*)g_game_base)->frontend_link_latch = 0;
            destroy_completion_screen();
        }
        break;
    }

    button = no_button;
    flags = button->widget_flags;
    if ((flags & 0x20) != 0) {
        button->widget_flags = flags & ~0x20;
        ((CompletionGameView*)g_game_base)->frontend_next_state = previous_frontend_state;
        ((CompletionGameView*)g_game_base)->frontend_link_latch = 0;
        return destroy_completion_screen();
    }
    return flags;
}
