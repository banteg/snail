// update_game_input @ 0x40aab0 (thiscall)

#include "game_root.h"
#include "input_controller_state.h"
#include "input_state.h"

void cRGameInput::AI()
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
        input.Update();
    }
}
