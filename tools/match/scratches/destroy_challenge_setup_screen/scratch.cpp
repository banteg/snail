// destroy_challenge_setup_screen @ 0x4161f0 (thiscall)

#include "border_manager.h"
#include "gui.h"
#include "subgame_runtime.h"

extern char* g_game_base; // data_4df904

void GUI::destroy_challenge_setup_screen()
{
    int mode = game->level_mode;
    switch (mode) {
    case 4:
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(next_level_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(previous_level_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(level_name_widget);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(play_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(back_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(replay_button);
        break;

    case 1:
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(play_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(back_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(speed_slider);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(difficulty_slider);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(replay_button);
        break;

    case 0:
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(next_level_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(previous_level_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(level_name_widget);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(play_button);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(back_button);
        break;
    }
}
