// consume_mouse_wheel_delta @ 0x4077f0 (cdecl, ret)

#include "mouse_input_state.h"

int consume_mouse_wheel_delta(int slot)
{
    int result = g_mouse_wheel_delta[slot];
    g_mouse_wheel_delta[slot] = 0;
    return result;
}
