// initialize_audio_subsystem @ 0x407a10 (cdecl)

#include "audio_system.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) ATOM __stdcall RegisterClassA(WndClassA* window_class);
extern "C" __declspec(dllimport) HWND __stdcall CreateWindowExA(unsigned int ex_style, char* class_name,
    char* window_name, unsigned int style, int x, int y, int width, int height,
    HWND parent, HMENU menu, HINSTANCE instance, void* param);
extern "C" __declspec(dllimport) BOOL __stdcall EndDialog(HWND hwnd, int result);

extern LRESULT __stdcall sub_4079e0(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void abort_startup_with_3d_error(); // @ 0x4088a0
void sub_407b00(); // cleanup after CreateWindowEx failure

extern char g_blank_text[];              // data_4dfb08
extern float g_config_sample_volume;     // data_4df918
extern float g_config_stream_volume;     // data_4df91c

char initialize_audio_subsystem()
{
    WndClassA window_class;
    int zero = 0;

    window_class.style = zero;
    window_class.wnd_proc = sub_4079e0;
    window_class.cls_extra = zero;
    window_class.wnd_extra = zero;
    window_class.instance = g_application_instance;
    window_class.icon = 0;
    window_class.cursor = 0;
    window_class.background = 0;
    window_class.menu_name = 0;
    window_class.class_name = "BASS";

    if (RegisterClassA(&window_class) == 0) {
        abort_startup_with_3d_error();
        return 0;
    }

    g_bass_window = CreateWindowExA(0, "BASS", g_blank_text, 0x86000000, 0, 0, 0, 0,
        0, 0, g_application_instance, 0);
    if (g_bass_window == 0) {
        sub_407b00();
        abort_startup_with_3d_error();
        return 0;
    }

    if (g_audio_backend.initialize_bass_audio_backend((void*)g_bass_window) == 0) {
        abort_startup_with_3d_error();
        EndDialog(g_bass_window, 0);
        return 0;
    }

    g_audio_backend.set_global_sample_volume_config(g_config_sample_volume);
    g_audio_backend.set_global_stream_volume_config(g_config_stream_volume);
    return 1;
}
