// update_mouse @ 0x44bc50 (cdecl)

#include "direct_input_view.h"
#include "game_root.h"
#include "mouse_window_state.h"
#include "win32_window_state.h"

#include <string.h>

extern "C" __declspec(dllimport) int __stdcall GetWindowRect(HWND hwnd, Rect* rect);
extern "C" __declspec(dllimport) int __stdcall GetClientRect(HWND hwnd, Rect* rect);
extern "C" __declspec(dllimport) int __stdcall ClipCursor(Rect* rect);
extern "C" __declspec(dllimport) int __stdcall SetCursor(int cursor);

extern GameRoot* g_game; // data_4df904
extern float g_mouse_live_x[]; // data_777d58
extern float g_mouse_live_y[]; // data_777d60
extern char g_hide_system_cursor_flag; // data_777d70
extern DirectInputDevice* g_mouse_device; // data_777d9c

int consume_mouse_wheel_delta(int slot); // @ 0x4077f0
unsigned char read_left_mouse_button_state(int slot); // @ 0x407810
unsigned char read_right_mouse_button_state(int slot); // @ 0x407830
void update_input_controller_pointer_region(
    int slot,
    int left,
    int top,
    int right,
    int bottom,
    int screen_x,
    int screen_y,
    int pointer_value,
    char button_a,
    char button_b,
    char button_c,
    char capture_when_outside,
    char force_clamp); // @ 0x4321c0

int update_mouse(HWND hwnd)
{
    DirectInputMouseState state;
    Rect window_rect;
    Rect client_rect;
    Rect clip_rect;

    if (g_mouse_device != 0) {
        memset(&state, 0, sizeof(state));

        if (g_mouse_device->GetDeviceState(20, &state) < 0) {
            while (g_mouse_device->Acquire() == 0x8007001e) {
            }
        }
    }

    if (!GetWindowRect(hwnd, &window_rect)) {
        window_rect.bottom = 0;
        window_rect.left = 0;
        window_rect.right = 0;
        window_rect.top = 0;
    } else if (!GetClientRect(hwnd, &client_rect)) {
        window_rect.bottom = 0;
        window_rect.left = 0;
        window_rect.right = 0;
        window_rect.top = 0;
    }

    if (g_fullscreen_active
        || !g_game->players[0].mouse_cursor.is_mouse_captured()) {
        g_mouse_live_x[0] = (float)state.x + g_mouse_live_x[0];
        g_mouse_live_y[0] = (float)state.y + g_mouse_live_y[0];

        if (g_mouse_live_x[0] < 0.0f) {
            g_mouse_live_x[0] = 0.0f;
        } else if (g_mouse_live_x[0] > 639.0f) {
            g_mouse_live_x[0] = 639.0f;
        }

        if (g_mouse_live_y[0] < 0.0f) {
            g_mouse_live_y[0] = 0.0f;
        } else if (g_mouse_live_y[0] > 479.0f) {
            g_mouse_live_y[0] = 479.0f;
        }
    } else {
        convert_mouse_screen_xy(0, &g_mouse_live_x[0], &g_mouse_live_y[0]);
    }

    if (g_fullscreen_active
        || !g_game->players[0].mouse_cursor.is_mouse_captured()) {
        ClipCursor(0);
        if (!g_game->players[0].mouse_cursor.is_mouse_captured()) {
            clip_rect.left =
                window_rect.left + client_rect.left - g_mouse_uncaptured_clip_rect.left;
            clip_rect.right =
                window_rect.right + client_rect.right - g_mouse_uncaptured_clip_rect.right;
            clip_rect.top =
                window_rect.top + client_rect.top - g_mouse_uncaptured_clip_rect.top;
            clip_rect.bottom =
                window_rect.bottom + client_rect.bottom - g_mouse_uncaptured_clip_rect.bottom;
            ClipCursor(&clip_rect);

            update_input_controller_pointer_region(
                0,
                0,
                0,
                640,
                480,
                (int)g_mouse_live_x[0],
                (int)g_mouse_live_y[0],
                consume_mouse_wheel_delta(0),
                read_left_mouse_button_state(0),
                read_right_mouse_button_state(0),
                0,
                g_game->players[0].mouse_cursor.is_mouse_captured(),
                g_fullscreen_active);
            goto maybe_hide_cursor;
        }

        update_input_controller_pointer_region(
            0,
            window_rect.left + client_rect.left - g_mouse_captured_client_rect.left,
            window_rect.top + client_rect.top - g_mouse_captured_client_rect.top,
            window_rect.left + client_rect.right - g_mouse_captured_client_rect.left,
            window_rect.top + client_rect.bottom - g_mouse_captured_client_rect.top,
            (int)g_mouse_live_x[0],
            (int)g_mouse_live_y[0],
            consume_mouse_wheel_delta(0),
            read_left_mouse_button_state(0),
            read_right_mouse_button_state(0),
            0,
            g_game->players[0].mouse_cursor.is_mouse_captured(),
            g_fullscreen_active);
    } else {
        if (!g_game->players[0].mouse_cursor.is_mouse_captured()) {
            clip_rect.left =
                window_rect.left + client_rect.left - g_mouse_uncaptured_clip_rect.left;
            clip_rect.right =
                window_rect.right + client_rect.right - g_mouse_uncaptured_clip_rect.right;
            clip_rect.top =
                window_rect.top + client_rect.top - g_mouse_uncaptured_clip_rect.top;
            clip_rect.bottom =
                window_rect.bottom + client_rect.bottom - g_mouse_uncaptured_clip_rect.bottom;
            ClipCursor(&clip_rect);
        } else {
            ClipCursor(0);
        }

        update_input_controller_pointer_region(
            0,
            window_rect.left + client_rect.left - g_mouse_uncaptured_clip_rect.left,
            window_rect.top + client_rect.top - g_mouse_uncaptured_clip_rect.top,
            window_rect.left + client_rect.right - g_mouse_uncaptured_clip_rect.left,
            window_rect.top + client_rect.bottom - g_mouse_uncaptured_clip_rect.top,
            (int)g_mouse_live_x[0],
            (int)g_mouse_live_y[0],
            consume_mouse_wheel_delta(0),
            read_left_mouse_button_state(0),
            read_right_mouse_button_state(0),
            0,
            g_game->players[0].mouse_cursor.is_mouse_captured(),
            g_fullscreen_active);
    }

maybe_hide_cursor:
    if (g_hide_system_cursor_flag)
        SetCursor(0);

    return 0;
}
