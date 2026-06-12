// read_right_mouse_button_state @ 0x407830 (cdecl, ret)

extern unsigned char g_right_mouse_button_latch[2]; // data_4b7230
extern unsigned char g_right_mouse_button_state[2]; // data_4b7640

unsigned char read_right_mouse_button_state(int slot)
{
    g_right_mouse_button_latch[slot] = 0;
    return g_right_mouse_button_state[slot];
}
