// read_left_mouse_button_state @ 0x407810 (cdecl, ret)

#include "mouse_input_state.h"

unsigned char read_left_mouse_button_state(int slot)
{
    g_left_mouse_button_latch[slot] = 0;
    return g_left_mouse_button_state[slot];
}
