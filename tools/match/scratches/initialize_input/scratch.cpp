// initialize_input @ 0x40aa50 (thiscall, ret)

#include "input_state.h"

void InputState::initialize_input()
{
    inverse_current_buttons = -1;
    current_buttons = 0;
    pressed_buttons = 0;
    released_buttons = 0;
    previous_buttons = 0;
    axis_x = 0.0f;
    axis_y = 0.0f;
    authored_x = 320.0f;
    authored_y = 240.0f;
    pointer_value = 0.0f;
}
