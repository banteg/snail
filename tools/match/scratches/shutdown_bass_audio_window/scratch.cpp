// shutdown_bass_audio_window @ 0x407b00 (cdecl)

#include "audio_system.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) BOOL __stdcall DestroyWindow(HWND hwnd);
extern "C" __declspec(dllimport) BOOL __stdcall UnregisterClassA(
    char* class_name, HINSTANCE instance);

int abort_startup_with_3d_error(); // @ 0x4088a0

int shutdown_bass_audio_window()
{
    g_audio_backend.uninitialize_bass_audio_backend();
    if (g_bass_window != 0) {
        if (DestroyWindow(g_bass_window) == 0) {
            abort_startup_with_3d_error();
            g_bass_window = 0;
        }
    }

    int result = UnregisterClassA("BASS", g_application_instance);
    if (result == 0)
        return abort_startup_with_3d_error();
    return result;
}
