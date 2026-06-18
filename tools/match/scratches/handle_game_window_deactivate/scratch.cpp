// handle_game_window_deactivate @ 0x407440 (cdecl)

#include "audio_system.h"

extern "C" __declspec(dllimport) void __stdcall ShowWindow(int window, int command);

extern unsigned char g_window_deactivated; // data_4b7654
extern char g_config_fullscreen_enabled;   // data_4df920
extern int g_pending_window_deactivate;    // data_4df860
extern int g_main_window;                  // data_4dfaf0

char handle_game_window_deactivate()
{
    char result = g_window_deactivated;
    if (result == 0) {
        if (g_config_fullscreen_enabled != 0) {
            g_audio_backend.pause_audio_backend_if_running();
            int main_window = g_main_window;
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
