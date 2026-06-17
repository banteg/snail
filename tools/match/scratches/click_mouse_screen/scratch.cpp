// click_mouse_screen @ 0x44c060 (cdecl)

#include "mouse_cursor_state.h"

extern "C" __declspec(dllimport) int __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) int __stdcall SetCursorPos(int x, int y);

extern char* g_game_base; // data_4df904
extern int g_main_window; // data_4dfaf0
extern unsigned char g_fullscreen_active; // data_4dfaf4
extern unsigned char g_window_deactivated; // data_4b7654
extern int g_mouse_screen_x[]; // data_777d7c
extern int g_mouse_screen_y[]; // data_777d74
extern float g_mouse_live_x[]; // data_777d58
extern float g_mouse_live_y[]; // data_777d60

struct MouseOwner {
    char pad_00[0x60];
    float mouse_x;
    float mouse_y;
};

void* click_mouse_screen(int slot, int x, int y)
{
    if (!g_fullscreen_active
        && ((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured() == 1
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
    MouseOwner* owner = *(MouseOwner**)(g_game_base + 0x28c);
    owner->mouse_x = (float)x;
    char* result = g_game_base;
    (*(MouseOwner**)(result + 0x28c))->mouse_y = y_float;
    return result;
}
