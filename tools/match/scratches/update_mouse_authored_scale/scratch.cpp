// update_mouse_authored_scale @ 0x44bbd0 (cdecl)

#include "mouse_input_state.h"

void update_mouse_authored_scale(float authored_width, float authored_height)
{
    g_mouse_screen_to_authored_x_scale =
        authored_width / (float)(g_mouse_clip_rect.right - g_mouse_clip_rect.left);
    g_mouse_screen_to_authored_y_scale =
        authored_height / (float)(g_mouse_clip_rect.bottom - g_mouse_clip_rect.top);
}
