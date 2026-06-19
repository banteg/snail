// convert_mouse_screen_xy @ 0x44c100 (cdecl)

#include "mouse_cursor_state.h"

struct Point {
    int x;
    int y;
};

extern "C" __declspec(dllimport) int __stdcall GetCursorPos(Point* point);
extern "C" __declspec(dllimport) int __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) int __stdcall SetCursorPos(int x, int y);

float resolve_uncaptured_cursor_sensitivity_scale(float scale);

extern char* g_game_base; // data_4df904
extern int g_main_window; // data_4dfaf0
extern unsigned char g_fullscreen_active; // data_4dfaf4
extern float g_authored_view_width; // data_4df85c
extern float g_authored_view_height; // data_4b7760
extern float g_steering_sensitivity[]; // flt_4df950
extern float g_mouse_screen_to_authored_y_scale; // data_777d68
extern float g_mouse_screen_to_authored_x_scale; // data_777d6c

int convert_mouse_screen_xy(int sensitivity_slot, float* x, float* y)
{
    Point point;
    int result;

    if (!g_fullscreen_active
        && ((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured()) {
        result = GetCursorPos(&point);
        if (result) {
            *x = (float)point.x;
            *y = (float)point.y;
            return (int)y;
        }
        *x = 0.0f;
        *y = 0.0f;
        return result;
    }

    if (!((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured()) {
        if (GetCursorPos(&point)) {
            *x += ((float)point.x - g_authored_view_width * 0.5f)
                * resolve_uncaptured_cursor_sensitivity_scale(
                    g_steering_sensitivity[sensitivity_slot])
                * g_mouse_screen_to_authored_x_scale;

            *y += ((float)point.y - g_authored_view_height * 0.5f)
                * resolve_uncaptured_cursor_sensitivity_scale(
                    g_steering_sensitivity[sensitivity_slot])
                * g_mouse_screen_to_authored_y_scale;
        } else {
            *x = 0.0f;
            *y = 0.0f;
        }

        result = GetActiveWindow();
        if (result == g_main_window) {
            return SetCursorPos(
                (int)(g_authored_view_width * 0.5f),
                (int)(g_authored_view_height * 0.5f));
        }
        return result;
    } else {
        if (GetCursorPos(&point)) {
            *x += ((float)point.x - g_authored_view_width * 0.5f)
                * g_mouse_screen_to_authored_x_scale;
            *y += ((float)point.y - g_authored_view_height * 0.5f)
                * g_mouse_screen_to_authored_y_scale;
        } else {
            *x = 0.0f;
            *y = 0.0f;
        }

        result = GetActiveWindow();
        if (result == g_main_window) {
            return SetCursorPos(
                (int)(g_authored_view_width * 0.5f),
                (int)(g_authored_view_height * 0.5f));
        }
        return result;
    }
}
