// destroy_challenge_setup_screen @ 0x4161f0 (thiscall)

#include "border_manager.h"
#include "game_root.h"
#include "gui.h"
#include "subgame_runtime.h"


void GUI::destroy_challenge_setup_screen()
{
    int mode = game->level_mode;
    switch (mode) {
    case 4:
        g_game->border_manager.kill_border(next_level_button);
        g_game->border_manager.kill_border(previous_level_button);
        g_game->border_manager.kill_border(level_name_widget);
        g_game->border_manager.kill_border(play_button);
        g_game->border_manager.kill_border(back_button);
        g_game->border_manager.kill_border(replay_button);
        break;

    case 1:
        g_game->border_manager.kill_border(play_button);
        g_game->border_manager.kill_border(back_button);
        g_game->border_manager.kill_border(speed_slider);
        g_game->border_manager.kill_border(difficulty_slider);
        g_game->border_manager.kill_border(replay_button);
        break;

    case 0:
        g_game->border_manager.kill_border(next_level_button);
        g_game->border_manager.kill_border(previous_level_button);
        g_game->border_manager.kill_border(level_name_widget);
        g_game->border_manager.kill_border(play_button);
        g_game->border_manager.kill_border(back_button);
        break;
    }
}
