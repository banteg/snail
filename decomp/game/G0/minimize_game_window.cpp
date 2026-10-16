// minimize_game_window @ 0x407490

#include "rdebug.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) BOOL __stdcall PostMessageA(
    HWND window, UINT message, WPARAM wparam, LPARAM lparam);

void minimize_game_window()
{
    debug_report_stub("Software Minimize Window\n");
    PostMessageA(g_main_window, 5, 1, 0);
}
