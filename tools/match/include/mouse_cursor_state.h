// Shared mouse cursor runtime view, cross-checked by capture/release helpers,
// uncaptured sensitivity, pause-menu teardown, and the frame update cursor draw.
#ifndef MOUSE_CURSOR_STATE_H
#define MOUSE_CURSOR_STATE_H

class MouseCursorState {
public:
    unsigned char is_mouse_captured(); // @ 0x44c3b0
    void capture_mouse_cursor();
    void release_mouse_cursor(); // @ 0x44c400

    unsigned char captured; // +0x00
    char pad_01[3];
    int live_x; // +0x04
    int live_y; // +0x08
    int saved_x; // +0x0c
    int saved_y; // +0x10
};

#endif
