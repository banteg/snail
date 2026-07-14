// set_immediate_blend_mode @ 0x412e50 (cdecl)

#include "direct3d_device8_view.h"

extern Direct3DDevice8* g_d3d_device; // data_502fec

void set_immediate_blend_mode(int blend_mode)
{
    switch (blend_mode) {
    case 0:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 0);
        return;

    case 1:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;

    case 2:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;

    case 4:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;

    case 14:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 10);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;

    case 6:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 2);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
        return;

    case 9:
    case 12:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
        return;

    case 5:
    case 8:
    case 11:
    case 13:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
        return;

    case 3:
    case 7:
    case 15:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
        return;
    }
}
