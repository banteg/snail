// present_backbuffer @ 0x413520 (cdecl)

#include "direct3d_device8_view.h"

extern Direct3DDevice8* g_d3d_device; // data_502fec

int present_backbuffer()
{
    Direct3DDevice8* device = g_d3d_device;
    return device->vtbl->Present(device, 0, 0, 0, 0);
}
