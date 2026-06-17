// update_mouse_authored_scale @ 0x44bbd0 (cdecl, ret)

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern float g_mouse_screen_to_authored_y_scale; // data_777d68
extern float g_mouse_screen_to_authored_x_scale; // data_777d6c
extern Rect g_mouse_clip_rect; // data_777d88

int update_mouse_authored_scale(float authored_width, float authored_height)
{
    g_mouse_screen_to_authored_x_scale =
        authored_width / (float)(g_mouse_clip_rect.right - g_mouse_clip_rect.left);
    g_mouse_screen_to_authored_y_scale =
        authored_height / (float)(g_mouse_clip_rect.bottom - g_mouse_clip_rect.top);
    return g_mouse_clip_rect.top;
}
