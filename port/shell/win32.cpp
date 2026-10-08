// The few Win32 calls left in recovered code the port compiles, for a
// 640x480 client area at the screen origin with no window frame.

#include <stdio.h>
#include <stdlib.h>

#include "rect.h"
#include "render_backend.h"
#include "win32_window_state.h"

// initialize_direct3d_renderer_defaults sizes the windowed clip rectangle.
extern "C" BOOL __stdcall AdjustWindowRectEx(Rect*, UINT, BOOL, UINT)
{
    return 1;
}

// set_fullscreen_mode (port/replaced.txt) toggled the window and display mode;
// the host owns the window, so it decides how to go fullscreen.
void set_fullscreen_mode(char enabled)
{
    backend_set_fullscreen(enabled);
}

// The original showed a message box; the shell has no window to own one.
int abort_startup_with_3d_error()
{
    fprintf(stderr, "snail: Direct3D initialisation failed\n");
    exit(1);
}
