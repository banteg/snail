// is_key_down @ 0x44bb40 (cdecl)

#include "direct_input_view.h"

unsigned char is_key_down(int key_code)
{
    if (g_keyboard_current_state[key_code & 0xff] == 0x80)
        return 1;
    return 0;
}
