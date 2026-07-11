// update_completion_screen @ 0x4067e0 (thiscall, ret)

#include "exit.h"
#include "game_root.h"

int Exit::update_completion_screen()
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
            ((GameRoot*)g_game_base)->frontend_quit_mode = 3;
        }
        break;

    case 10:
        ((GameRoot*)g_game_base)->main_menu.update_main_menu();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((GameRoot*)g_game_base)->main_menu.destroy_main_menu();
            if (((GameRoot*)g_game_base)->frontend_quit_mode == 0)
                ((GameRoot*)g_game_base)->frontend_quit_mode = 1;
        }
        break;

    case 11:
        ((GameRoot*)g_game_base)->subgame.galaxy.update_galaxy();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            ((GameRoot*)g_game_base)->subgame.galaxy.destroy_galaxy();
            ((GameRoot*)g_game_base)->subgame.complete_subgame(1);
            if (((GameRoot*)g_game_base)->players[0].high_score_entry_pending == 1) {
                previous_frontend_state =
                    ((GameRoot*)g_game_base)->players[0].frontend_state;
                destroy_completion_screen();
                ((GameRoot*)g_game_base)->subgame.destroy_subgame();
            } else {
                destroy_completion_screen();
                ((GameRoot*)g_game_base)->subgame.destroy_subgame();
                ((GameRoot*)g_game_base)->players[0].frontend_state = 2;
            }
        }
        break;

    case 2:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            ((GameRoot*)g_game_base)->subgame.complete_subgame(1);
            if (((GameRoot*)g_game_base)->players[0].high_score_entry_pending == 1) {
                previous_frontend_state =
                    ((GameRoot*)g_game_base)->players[0].frontend_state;
                destroy_completion_screen();
                ((GameRoot*)g_game_base)->subgame.pause_menu.uninit_pause_menu();
                ((GameRoot*)g_game_base)->subgame.subgame_pause_gate = 0;
                g_sprite_manager.set_sprite_manager_paused(0);
                ((GameRoot*)g_game_base)->subgame.destroy_subgame();
            } else {
                destroy_completion_screen();
                ((GameRoot*)g_game_base)->subgame.pause_menu.uninit_pause_menu();
                ((GameRoot*)g_game_base)->subgame.subgame_pause_gate = 0;
                g_sprite_manager.set_sprite_manager_paused(0);
                ((GameRoot*)g_game_base)->subgame.destroy_subgame();
                int mode = ((GameRoot*)g_game_base)->subgame.level_mode;
                if (mode == 4 || mode == 1)
                    ((GameRoot*)g_game_base)->subgame.initialize_subgame();
                else
                    ((GameRoot*)g_game_base)->players[0].frontend_state = 2;
            }
        }
        break;

    case 7:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((GameRoot*)g_game_base)->subgame.pause_menu.uninit_pause_menu();
            ((GameRoot*)g_game_base)->subgame.subgame_pause_gate = 0;
            g_sprite_manager.set_sprite_manager_paused(0);
            ((GameRoot*)g_game_base)->subgame.destroy_subgame();
            ((GameRoot*)g_game_base)->players[0].frontend_state = 2;
        }
        break;

    case 3:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((GameRoot*)g_game_base)->subgame.pause_menu.uninit_pause_menu();
            ((GameRoot*)g_game_base)->subgame.subgame_pause_gate = 0;
            g_sprite_manager.set_sprite_manager_paused(0);
            ((GameRoot*)g_game_base)->subgame.destroy_subgame();
            ((GameRoot*)g_game_base)->players[0].frontend_state =
                ((GameRoot*)g_game_base)->subgame.replay_launch_return_state;
        }
        break;

    case 4:
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            destroy_completion_screen();
            ((GameRoot*)g_game_base)->subgame.destroy_subgame();
            ((GameRoot*)g_game_base)->players[0].frontend_state = 2;
        }
        break;

    case 8:
        ((GameRoot*)g_game_base)->new_game_menu.update_new_game_menu();
        button = yes_button;
        flags = button->widget_flags;
        if ((flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            launch_alpha72_url("Alpha72.url");
            ((GameRoot*)g_game_base)->players[0].frontend_state = 0;
            ((GameRoot*)g_game_base)->frontend_link_latch = 0;
            destroy_completion_screen();
        }
        break;
    }

    button = no_button;
    flags = button->widget_flags;
    if ((flags & 0x20) != 0) {
        button->widget_flags = flags & ~0x20;
        ((GameRoot*)g_game_base)->players[0].frontend_state = previous_frontend_state;
        ((GameRoot*)g_game_base)->frontend_link_latch = 0;
        return destroy_completion_screen();
    }
    return flags;
}
