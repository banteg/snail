// read_right_mouse_button_state @ 0x407830 (cdecl, ret)

#include "mouse_input_state.h"

unsigned char read_right_mouse_button_state(int slot)
{
    g_right_mouse_button_latch[slot] = 0;
    return g_right_mouse_button_state[slot];
}
