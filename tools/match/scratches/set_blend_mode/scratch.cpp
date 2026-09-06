// set_blend_mode @ 0x412d00 (cdecl)

#include "direct3d_device8_view.h"

void set_blend_mode(int blend_mode)
{
    switch (blend_mode) {
    case 0:
    case 6:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;
    case 1:
    case 8:
    case 20:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;
    case 5:
    case 13:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
        return;
    case 7:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 2);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
        return;
    case 9:
    case 12:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;
    case 19:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 2);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;
    }
}
