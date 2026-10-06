// show_and_focus_game_window @ 0x4073b0 (cdecl)

#include "main_loop_state.h"
#include "mouse_input_state.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow(HWND window, int command);
extern "C" __declspec(dllimport) BOOL __stdcall SetForegroundWindow(HWND window);
extern "C" __declspec(dllimport) HWND __stdcall SetFocus(HWND window);
extern "C" __declspec(dllimport) HWND __stdcall SetActiveWindow(HWND window);

int show_and_focus_game_window()
{
    unsigned int ticks = timeGetTime();
    int zero = 0;

    g_previous_frame_timestamp_seconds = (float)ticks * 0.001f;
    ShowWindow(g_main_window, 1);
    SetForegroundWindow(g_main_window);
    SetFocus(g_main_window);
    int result = SetActiveWindow(g_main_window);

    g_left_mouse_button_latch[0] = (unsigned char)zero;
    g_left_mouse_button_state[0] = (unsigned char)zero;
    g_right_mouse_button_latch[0] = (unsigned char)zero;
    g_right_mouse_button_state[0] = (unsigned char)zero;
    g_left_mouse_button_latch[1] = (unsigned char)zero;
    g_left_mouse_button_state[1] = (unsigned char)zero;
    g_right_mouse_button_latch[1] = (unsigned char)zero;
    g_right_mouse_button_state[1] = (unsigned char)zero;

    return result;
}
