// Process-owned two-slot mouse state shared by the Win32 message path and the
// authored-coordinate DirectInput path.
#ifndef MOUSE_INPUT_STATE_H
#define MOUSE_INPUT_STATE_H

#include "rect.h"

enum {
    MOUSE_INPUT_SLOT_COUNT = 2,
};

extern unsigned char
    g_left_mouse_button_latch[MOUSE_INPUT_SLOT_COUNT]; // data_4b7764
extern unsigned char
    g_left_mouse_button_state[MOUSE_INPUT_SLOT_COUNT]; // data_4b7234
extern unsigned char
    g_right_mouse_button_latch[MOUSE_INPUT_SLOT_COUNT]; // data_4b7230
extern unsigned char
    g_right_mouse_button_state[MOUSE_INPUT_SLOT_COUNT]; // data_4b7640
extern int g_mouse_wheel_delta[MOUSE_INPUT_SLOT_COUNT]; // data_4dfad0

extern float g_mouse_live_x[MOUSE_INPUT_SLOT_COUNT]; // data_777d58
extern float g_mouse_live_y[MOUSE_INPUT_SLOT_COUNT]; // data_777d60
extern float g_mouse_screen_to_authored_y_scale; // data_777d68
extern float g_mouse_screen_to_authored_x_scale; // data_777d6c
extern char g_hide_system_cursor_flag; // data_777d70
extern int g_mouse_screen_y[MOUSE_INPUT_SLOT_COUNT]; // data_777d74
extern int g_mouse_screen_x[MOUSE_INPUT_SLOT_COUNT]; // data_777d7c
extern Rect g_mouse_clip_rect; // data_777d88

#endif
