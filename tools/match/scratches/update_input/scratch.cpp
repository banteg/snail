// update_input @ 0x40aa80 (thiscall)

#include "input_state.h"

void InputState::update_input()
{
    int result = current_buttons;
    int changed = previous_buttons ^ result;
    previous_buttons = result;
    pressed_buttons = changed & result;
    result = ~result;
    inverse_current_buttons = result;
    current_buttons = 0;
    released_buttons = changed & result;
}
