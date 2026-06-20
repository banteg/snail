// set_blend_mode @ 0x412d00 (cdecl)

#include "direct3d_device8_view.h"

extern Direct3DDevice8* g_d3d_device; // data_502fec

int set_blend_mode(int blend_mode)
{
    switch (blend_mode) {
    case 0:
    case 6:
    case 9:
    case 12:
    {
        Direct3DDevice8* device = g_d3d_device;
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device = g_d3d_device;
        device->vtbl->SetRenderState(device, 0x13, 5);
        device = g_d3d_device;
        return device->vtbl->SetRenderState(device, 0x14, 6);
    }
    case 1:
    case 8:
    case 20:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
    case 5:
    case 13:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
    case 7:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 2);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
    case 19:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 2);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
    }

    return blend_mode;
}
