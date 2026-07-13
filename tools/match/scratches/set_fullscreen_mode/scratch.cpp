// set_fullscreen_mode @ 0x414260 (cdecl)

#include "direct3d_renderer.h"

void set_fullscreen_mode(int enabled)
{
    g_direct3d_renderer.direct3d_renderer_set_fullscreen_mode(enabled);
}
