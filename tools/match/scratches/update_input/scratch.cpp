// update_input @ 0x40aa80 (thiscall)

#include "input_state.h"

int InputState::update_input()
{
    int result = current_buttons;
    int changed = previous_buttons ^ result;
    int pressed = changed & result;
    int inverse = result;
    inverse = ~inverse;
    int released = inverse & changed;

    previous_buttons = result;
    pressed_buttons = pressed;
    inverse_current_buttons = inverse;
    current_buttons = 0;
    released_buttons = released;
    return result;
}
