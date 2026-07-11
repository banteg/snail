// handle_game_window_deactivate @ 0x407440 (cdecl)

#include "audio_system.h"
#include "runtime_config.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) void __stdcall ShowWindow(HWND window, int command);

extern unsigned char g_window_deactivated; // data_4b7654
extern int g_pending_window_deactivate;    // data_4df860

char handle_game_window_deactivate()
{
    char result = g_window_deactivated;
    if (result == 0) {
        if (g_runtime_config.fullscreen_enabled != 0) {
            g_audio_backend.pause_audio_backend_if_running();
            HWND main_window = g_main_window;
            g_window_deactivated = 1;
            ShowWindow(main_window, 6);
        }

        result = (char)g_pending_window_deactivate;
        if (g_pending_window_deactivate != 0) {
            g_pending_window_deactivate = 0;
        }
    }

    return result;
}
