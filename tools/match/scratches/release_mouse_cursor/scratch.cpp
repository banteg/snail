// release_mouse_cursor @ 0x44c400 (thiscall, ret)

class MouseCursorState {
public:
    void release_mouse_cursor();

    char captured; // +0x00
    char pad_01[3];
    int live_x;    // +0x04
    int live_y;    // +0x08
    int saved_x;   // +0x0c
    int saved_y;   // +0x10
};

void MouseCursorState::release_mouse_cursor()
{
    if (captured == 1) {
        live_x = saved_x;
        live_y = saved_y;
    }
    captured = 0;
}
