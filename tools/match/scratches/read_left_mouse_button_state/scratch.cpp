// read_left_mouse_button_state @ 0x407810 (cdecl, ret)

extern unsigned char g_left_mouse_button_state[2]; // data_4b7234
extern unsigned char g_left_mouse_button_latch[2]; // data_4b7764

unsigned char read_left_mouse_button_state(int slot)
{
    g_left_mouse_button_latch[slot] = 0;
    return g_left_mouse_button_state[slot];
}
