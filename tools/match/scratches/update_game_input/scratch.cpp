// update_game_input @ 0x40aab0 (thiscall)

#include "game_root.h"
#include "input_state.h"

extern GameRoot* g_game; // data_4df904

float* copy_active_input_controller_state(
    int controller_slot,
    int* buttons,
    float* axis_x,
    float* axis_y,
    float* authored_x,
    float* authored_y,
    float* pointer_value,
    float* pointer_x,
    float* pointer_y);

void GameInputOwner::update_game_input()
{
    if (g_game->input_sampling_gate != 0) {
        copy_active_input_controller_state(
            input.controller_slot,
            &input.current_buttons,
            &input.axis_x,
            &input.axis_y,
            &input.authored_x,
            &input.authored_y,
            &input.pointer_value,
            &input.pointer_x,
            &input.pointer_y);
        input.update_input();
    }
}
