// update_input @ 0x40aa80 (thiscall)

#include "input_state.h"

void cRInput::Update()
{
    int current = current_buttons;
    int changed = previous_buttons ^ current;
    int press = changed & current;
    pressed_buttons = press;
    int release = changed & ~current;
    released_buttons = release;
    previous_buttons = current;
    int inverse = ~current;
    inverse_current_buttons = inverse;
    current_buttons = 0;
}
