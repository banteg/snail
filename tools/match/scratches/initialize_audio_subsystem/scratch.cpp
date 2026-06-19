// initialize_audio_subsystem @ 0x407a10 (cdecl)

typedef void* HWND;
typedef void* HINSTANCE;
typedef void* HICON;
typedef void* HCURSOR;
typedef void* HBRUSH;
typedef void* HMENU;
typedef void* HMODULE;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef long LRESULT;
typedef int BOOL;
typedef unsigned short ATOM;

#include "audio_system.h"

struct WNDCLASSA {
    UINT style;
    LRESULT (__stdcall* lpfnWndProc)(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    char* lpszMenuName;
    char* lpszClassName;
};

extern "C" __declspec(dllimport) ATOM __stdcall RegisterClassA(WNDCLASSA* window_class);
extern "C" __declspec(dllimport) HWND __stdcall CreateWindowExA(unsigned int ex_style, char* class_name,
    char* window_name, unsigned int style, int x, int y, int width, int height,
    HWND parent, HMENU menu, HINSTANCE instance, void* param);
extern "C" __declspec(dllimport) BOOL __stdcall EndDialog(HWND hwnd, int result);

extern LRESULT __stdcall sub_4079e0(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void abort_startup_with_3d_error(); // @ 0x4088a0
void sub_407b00(); // cleanup after CreateWindowEx failure

extern HINSTANCE g_application_instance; // data_4dfad8
extern HWND g_bass_window;               // data_4dfaf8
extern char g_blank_text[];              // data_4dfb08
extern float g_config_sample_volume;     // data_4df918
extern float g_config_stream_volume;     // data_4df91c

char initialize_audio_subsystem()
{
    WNDCLASSA window_class;
    int zero = 0;

    window_class.style = zero;
    window_class.lpfnWndProc = sub_4079e0;
    window_class.cbClsExtra = zero;
    window_class.cbWndExtra = zero;
    window_class.hInstance = g_application_instance;
    window_class.hIcon = 0;
    window_class.hCursor = 0;
    window_class.hbrBackground = 0;
    window_class.lpszMenuName = 0;
    window_class.lpszClassName = "BASS";

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

    if (g_audio_backend.initialize_bass_audio_backend(g_bass_window) == 0) {
        abort_startup_with_3d_error();
        EndDialog(g_bass_window, 0);
        return 0;
    }

    g_audio_backend.set_global_sample_volume_config(g_config_sample_volume);
    g_audio_backend.set_global_stream_volume_config(g_config_stream_volume);
    return 1;
}
