// is_key_pressed_edge @ 0x44bb10 (cdecl)

#include "direct_input_view.h"

unsigned char is_key_pressed_edge(unsigned char key_code)
{
    if (g_keyboard_current_state[key_code] == 0x80
            && g_keyboard_previous_state[key_code] == 0)
        return 1;
    return 0;
}
