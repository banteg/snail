// set_cull_mode @ 0x4129f0 (cdecl)

#include "direct3d_renderer.h"

int set_cull_mode(int cull_front)
{
    return g_direct3d_renderer.direct3d_renderer_set_cull_mode((char)cull_front);
}
