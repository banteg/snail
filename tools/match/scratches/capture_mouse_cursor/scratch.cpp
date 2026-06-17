// capture_mouse_cursor @ 0x44c3c0 (thiscall, ret)

#include "mouse_cursor_state.h"

void* click_mouse_screen(int slot, int x, int y);

void MouseCursorState::capture_mouse_cursor()
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
