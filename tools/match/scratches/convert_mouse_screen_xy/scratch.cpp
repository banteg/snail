// convert_mouse_screen_xy @ 0x44c100 (cdecl)

#include "game_root.h"
#include "mouse_input_state.h"
#include "runtime_config.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) BOOL __stdcall GetCursorPos(Point* point);
extern "C" __declspec(dllimport) HWND __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) BOOL __stdcall SetCursorPos(int x, int y);

float resolve_uncaptured_cursor_sensitivity_scale(float scale);

extern GameRoot* g_game; // data_4df904
extern float g_authored_view_width; // data_4df85c
extern float g_authored_view_height; // data_4b7760

void convert_mouse_screen_xy(int sensitivity_slot, float* x, float* y)
{
    Point point;
    int result;

    if (!g_fullscreen_active
        && g_game->players[0].mouse_cursor.is_mouse_captured()) {
        result = GetCursorPos(&point);
        if (result) {
            *x = (float)point.x;
            *y = (float)point.y;
            return;
        }
        *y = *x = 0.0f;
        return;
    }

    if (!g_game->players[0].mouse_cursor.is_mouse_captured()) {
        if (GetCursorPos(&point)) {
            *x += ((float)point.x - g_authored_view_width * 0.5f)
                * resolve_uncaptured_cursor_sensitivity_scale(
                    g_runtime_config.steering_sensitivity[sensitivity_slot])
                * g_mouse_screen_to_authored_x_scale;

            *y += ((float)point.y - g_authored_view_height * 0.5f)
                * resolve_uncaptured_cursor_sensitivity_scale(
                    g_runtime_config.steering_sensitivity[sensitivity_slot])
                * g_mouse_screen_to_authored_y_scale;
        } else {
            *y = *x = 0.0f;
        }

        result = GetActiveWindow();
        if (result == g_main_window) {
            SetCursorPos(
                (int)(g_authored_view_width * 0.5f),
                (int)(g_authored_view_height * 0.5f));
        }
        return;
    } else {
        if (GetCursorPos(&point)) {
            *x += ((float)point.x - g_authored_view_width * 0.5f)
                * g_mouse_screen_to_authored_x_scale;
            *y += ((float)point.y - g_authored_view_height * 0.5f)
                * g_mouse_screen_to_authored_y_scale;
        } else {
            *y = *x = 0.0f;
        }

        result = GetActiveWindow();
        if (result == g_main_window) {
            SetCursorPos(
                (int)(g_authored_view_width * 0.5f),
                (int)(g_authored_view_height * 0.5f));
        }
        return;
    }
}
