// is_mouse_captured @ 0x44c3b0 (thiscall, ret)

#include "mouse_cursor_state.h"

unsigned char MouseCursorState::is_mouse_captured()
{
    return captured;
}
