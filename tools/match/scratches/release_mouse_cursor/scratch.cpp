// release_mouse_cursor @ 0x44c400 (thiscall, ret)

#include "mouse_cursor_state.h"

void MouseCursorState::release_mouse_cursor()
{
    if (captured == 1) {
        live_x = saved_x;
        live_y = saved_y;
    }
    captured = 0;
}
