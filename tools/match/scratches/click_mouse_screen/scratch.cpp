// click_mouse_screen @ 0x44c060 (cdecl)

#include "game_root.h"
#include "main_loop_state.h"
#include "mouse_input_state.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) HWND __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) int __stdcall SetCursorPos(int x, int y);


void* click_mouse_screen(int slot, int x, int y)
{
    if (!g_fullscreen_active
        && g_game->players[0].mouse_cursor.is_mouse_captured() == 1
        && slot == 0
        && !g_window_deactivated
        && GetActiveWindow() == g_main_window) {
        SetCursorPos(x, y);
    }

    g_mouse_screen_x[slot] = x;
    g_mouse_screen_y[slot] = y;
    g_mouse_live_x[slot] = (float)x;
    float y_float = (float)y;
    g_mouse_live_y[slot] = y_float;
    GameInput* owner = g_game->players[0].game_input;
    owner->input.authored_x = (float)x;
    GameRoot* result = g_game;
    result->players[0].game_input->input.authored_y = y_float;
    return result;
}
