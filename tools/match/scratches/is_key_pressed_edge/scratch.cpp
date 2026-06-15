// is_key_pressed_edge @ 0x44bb10 (cdecl)

extern unsigned char g_keyboard_previous_state[0x100]; // data_777b4c
extern unsigned char g_keyboard_current_state[0x100];  // data_777c4c

unsigned char is_key_pressed_edge(int key_code)
{
    int index = key_code & 0xff;
    if (g_keyboard_current_state[index] == 0x80
            && g_keyboard_previous_state[index] == 0)
        return 1;
    return 0;
}
