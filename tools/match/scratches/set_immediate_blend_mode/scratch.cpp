// set_immediate_blend_mode @ 0x412e50 (cdecl)

#include "direct3d_device8_view.h"

extern Direct3DDevice8* g_d3d_device; // data_502fec

int set_immediate_blend_mode(int blend_mode)
{
    switch (blend_mode) {
    case 0:
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 0);

    case 1:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);

    case 2:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 1);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);

    case 4:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);

    case 14:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 10);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);

    case 6:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 2);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);

    case 9:
    case 12:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);

    case 5:
    case 8:
    case 11:
    case 13:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);

    case 3:
    case 7:
    case 15:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
    }

    return blend_mode;
}
