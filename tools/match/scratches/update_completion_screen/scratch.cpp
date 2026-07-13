// update_completion_screen @ 0x4067e0 (thiscall, ret)

#include "exit.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void Exit::update_completion_screen()
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
            g_game->frontend_quit_mode = 3;
        }
        break;

    case 10:
        g_game->main_menu.update_main_menu();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            g_game->main_menu.destroy_main_menu();
            if (g_game->frontend_quit_mode == 0)
                g_game->frontend_quit_mode = 1;
        }
        break;

    case 11:
        g_game->subgame.galaxy.update_galaxy();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            g_game->subgame.galaxy.destroy_galaxy();
            g_game->subgame.complete_subgame(1);
            if (g_game->players[0].high_score_entry_pending == 1) {
                previous_frontend_state = g_game->players[0].frontend_state;
                destroy_completion_screen();
                g_game->subgame.destroy_subgame();
            } else {
                destroy_completion_screen();
                g_game->subgame.destroy_subgame();
                g_game->players[0].frontend_state = 2;
            }
        }
        break;

    case 2:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            g_game->subgame.complete_subgame(1);
            if (g_game->players[0].high_score_entry_pending == 1) {
                previous_frontend_state = g_game->players[0].frontend_state;
                destroy_completion_screen();
                g_game->subgame.pause_menu.uninit_pause_menu();
                g_game->subgame.subgame_pause_gate = 0;
                g_sprite_manager.set_sprite_manager_paused(0);
                g_game->subgame.destroy_subgame();
            } else {
                destroy_completion_screen();
                g_game->subgame.pause_menu.uninit_pause_menu();
                g_game->subgame.subgame_pause_gate = 0;
                g_sprite_manager.set_sprite_manager_paused(0);
                g_game->subgame.destroy_subgame();
                int mode = g_game->subgame.level_mode;
                if (mode == 4 || mode == 1)
                    g_game->subgame.initialize_subgame();
                else
                    g_game->players[0].frontend_state = 2;
            }
        }
        break;

    case 7:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            g_game->subgame.pause_menu.uninit_pause_menu();
            g_game->subgame.subgame_pause_gate = 0;
            g_sprite_manager.set_sprite_manager_paused(0);
            g_game->subgame.destroy_subgame();
            g_game->players[0].frontend_state = 2;
        }
        break;

    case 3:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            g_game->subgame.pause_menu.uninit_pause_menu();
            g_game->subgame.subgame_pause_gate = 0;
            g_sprite_manager.set_sprite_manager_paused(0);
            g_game->subgame.destroy_subgame();
            g_game->players[0].frontend_state =
                g_game->subgame.replay_launch_return_state;
        }
        break;

    case 4:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            g_game->subgame.destroy_subgame();
            g_game->players[0].frontend_state = 2;
        }
        break;

    case 8:
        g_game->intro.update_new_game_menu();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            launch_alpha72_url("Alpha72.url");
            g_game->players[0].frontend_state = 0;
            g_game->frontend_link_latch = 0;
            destroy_completion_screen();
        }
        break;
    }

    button = no_button;
    flags = button->widget_flags;
    if ((flags & 0x20) != 0) {
        button->widget_flags = flags & ~0x20;
        g_game->players[0].frontend_state = previous_frontend_state;
        g_game->frontend_link_latch = 0;
        destroy_completion_screen();
        return;
    }
}
