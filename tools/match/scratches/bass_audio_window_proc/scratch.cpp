// bass_audio_window_proc @ 0x4079e0 (stdcall, ret 0x10)

#include "win32_window_state.h"

extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int exit_code);
extern "C" __declspec(dllimport) LRESULT __stdcall DefWindowProcA(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

LRESULT __stdcall bass_audio_window_proc(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message != 0x10)
        return DefWindowProcA(hwnd, message, wparam, lparam);
    PostQuitMessage(0);
    return 0;
}
