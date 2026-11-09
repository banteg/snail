// set_immediate_blend_mode @ 0x412e50 (cdecl)

#include "direct3d_renderer.h"

void set_immediate_blend_mode(int blend_mode)
{
    Direct3DDevice8* const& device = g_direct3d_renderer.device;
    switch (blend_mode) {
    case 0:
        device->vtbl->SetRenderState(device, 0x1b, 0);
        return;

    case 1:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 5);
        device->vtbl->SetRenderState(device, 0x14, 6);
        return;

    case 2:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 1);
        device->vtbl->SetRenderState(device, 0x14, 6);
        return;

    case 14:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 10);
        device->vtbl->SetRenderState(device, 0x14, 6);
        return;

    case 4:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 5);
        device->vtbl->SetRenderState(device, 0x14, 6);
        return;

    case 6:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 2);
        device->vtbl->SetRenderState(device, 0x14, 2);
        return;

    case 9:
    case 12:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 5);
        device->vtbl->SetRenderState(device, 0x14, 2);
        return;

    case 5:
    case 8:
    case 11:
    case 13:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 5);
        device->vtbl->SetRenderState(device, 0x14, 2);
        return;

    case 3:
    case 7:
    case 15:
        device->vtbl->SetRenderState(device, 0x1b, 1);
        device->vtbl->SetRenderState(device, 0x13, 5);
        device->vtbl->SetRenderState(device, 0x14, 6);
        return;
    }
}
