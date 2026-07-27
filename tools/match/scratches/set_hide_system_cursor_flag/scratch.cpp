// set_hide_system_cursor_flag @ 0x44c050 (cdecl)

#include "mouse_input_state.h"

void set_hide_system_cursor_flag(bool hidden)
{
    g_hide_system_cursor_flag = hidden;
}
