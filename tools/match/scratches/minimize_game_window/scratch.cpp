// minimize_game_window @ 0x407490

#include "win32_window_state.h"

extern "C" __declspec(dllimport) BOOL __stdcall PostMessageA(
    HWND window, UINT message, WPARAM wparam, LPARAM lparam);

extern int debug_report_stub(char* message); // @ 0x449c00

void minimize_game_window()
{
    debug_report_stub("Software Minimize Window\n");
    PostMessageA(g_main_window, 5, 1, 0);
}
