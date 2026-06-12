// consume_mouse_wheel_delta @ 0x4077f0 (cdecl, ret)

extern int g_mouse_wheel_delta[2]; // data_4dfad0

int consume_mouse_wheel_delta(int slot)
{
    int result = g_mouse_wheel_delta[slot];
    g_mouse_wheel_delta[slot] = 0;
    return result;
}
