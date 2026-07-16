// set_hide_system_cursor_flag @ 0x44c050 (cdecl, ret)

#include "mouse_input_state.h"

char set_hide_system_cursor_flag(char hidden)
{
    g_hide_system_cursor_flag = hidden;
    return hidden;
}
