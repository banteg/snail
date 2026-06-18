// update_input @ 0x40aa80 (thiscall)

#include "input_state.h"

int InputState::update_input()
{
    int result = current_buttons;
    int previous = previous_buttons;
    int changed = previous ^ result;
    int pressed = changed & result;
    previous_buttons = result;
    pressed_buttons = pressed;
    int inverse = result;
    inverse = ~inverse;
    int released = inverse;
    inverse_current_buttons = inverse;
    released &= changed;
    current_buttons = 0;
    released_buttons = released;
    return result;
}
