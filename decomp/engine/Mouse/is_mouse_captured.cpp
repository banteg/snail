// cRMouse::IsActive @ 0x44c3b0 (thiscall, ret)

#include "mouse_cursor_state.h"

unsigned char cRMouse::IsActive()
{
    return captured;
}
