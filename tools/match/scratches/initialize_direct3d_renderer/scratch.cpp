// initialize_direct3d_renderer @ 0x4129c0 (cdecl)

#include "direct3d_renderer.h"

char initialize_direct3d_renderer()
{
    g_direct3d_renderer.initialize_direct3d_renderer_defaults();
    g_direct3d_renderer.initialize_d3d8_device(0);
    g_direct3d_renderer.renderer_state = (RendererState*)
        g_direct3d_renderer.create_vertex_buffer(8, 0x142);
    return 1;
}
