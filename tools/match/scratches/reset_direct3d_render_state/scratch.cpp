// Direct3DRenderer::reset_direct3d_render_state @ 0x4118b0

#include "direct3d_renderer.h"

void Direct3DRenderer::reset_direct3d_render_state()
{
    device->vtbl->SetRenderState(device, 0x8b, 0x00ffffff);
    device->vtbl->SetRenderState(device, 0x89, 0);
    device->vtbl->SetRenderState(device, 0x16, 1);
    device->vtbl->SetRenderState(device, 7, 1);

    Direct3DDevice8* local_device = device;
    local_device->vtbl->SetRenderState(local_device, 0x10, 1);

    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x0f, 1);
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x18, 0);
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x19, 5);
}
