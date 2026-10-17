// cRMouse::SetActive @ 0x44c3c0 (thiscall, ret)

#include "input_polling.h"
#include "mouse_cursor_state.h"

void cRMouse::SetActive()
{
    if (captured == 0) {
        float x = live_x;
        saved_x = x;
        float y = live_y;
        saved_y = y;
        click_mouse_screen(0, (int)x, (int)y);
        suppress_next_draw = 1;
    }
    captured = 1;
}
