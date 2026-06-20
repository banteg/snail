// set_fullscreen_mode @ 0x414260 (cdecl)

#include "direct3d_renderer.h"

extern Direct3DRenderer g_direct3d_renderer; // data_4f7458

int set_fullscreen_mode(int enabled)
{
    return g_direct3d_renderer.direct3d_renderer_set_fullscreen_mode(enabled);
}
