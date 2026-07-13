// Windows prefix of the player-owned cRMouse object, cross-checked against the
// iPhone Mouse.o methods and the native capture/release helpers.
#ifndef MOUSE_CURSOR_STATE_H
#define MOUSE_CURSOR_STATE_H

class MouseCursorState {
public:
    unsigned char is_mouse_captured(); // @ 0x44c3b0, cRMouse::IsActive()
    void capture_mouse_cursor(); // @ 0x44c3c0, cRMouse::SetActive()
    void release_mouse_cursor(); // @ 0x44c400, cRMouse::SetInActive()

    unsigned char captured; // +0x00
    char pad_01[3];
    float live_x; // +0x04
    float live_y; // +0x08
    float saved_x; // +0x0c
    float saved_y; // +0x10
    unsigned char suppress_next_draw; // +0x14
};

// Windows cursor-position bridge used by update_mouse when the OS cursor owns
// the live authored coordinates. The helper is side-effect-only; incidental
// values left in eax are not a return contract.
void convert_mouse_screen_xy(int sensitivity_slot, float* x, float* y); // @ 0x44c100

#endif
