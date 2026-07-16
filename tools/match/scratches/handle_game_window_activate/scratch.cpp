// handle_game_window_activate @ 0x4072f0 (cdecl)

#include "audio_system.h"
#include "main_loop_state.h"
#include "mouse_input_state.h"
#include "runtime_config.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow(HWND window, int command);
extern "C" __declspec(dllimport) BOOL __stdcall SetForegroundWindow(HWND window);
extern "C" __declspec(dllimport) HWND __stdcall SetFocus(HWND window);

int debug_report_stub(char* format); // @ 0x449c00, stripped in release
void set_fullscreen_mode(int enabled);

int handle_game_window_activate()
{
    debug_report_stub("G0Maximize %i\n");
    debug_report_stub("G0Maximize Do something\n");
    g_audio_backend.resume_audio_backend_if_paused();

    int zero = 0;
    char fullscreen_enabled = g_runtime_config.fullscreen_enabled;
    g_window_deactivated = (unsigned char)zero;
    if (fullscreen_enabled != 0) {
        set_fullscreen_mode(1);
    }

    unsigned int ticks = timeGetTime();
    g_previous_frame_timestamp_seconds = (float)ticks * 0.001f;
    ShowWindow(g_main_window, 1);
    SetForegroundWindow(g_main_window);
    int result = SetFocus(g_main_window);

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
