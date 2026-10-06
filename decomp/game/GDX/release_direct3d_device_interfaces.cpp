// Direct3DRenderer::release_direct3d_device_interfaces @ 0x411960

#include "direct3d_renderer.h"

void Direct3DRenderer::release_direct3d_device_interfaces()
{
    if (device != 0) {
        device->vtbl->Release(device);
        device = 0;
    }

    if (d3d != 0) {
        d3d->vtbl->Release(d3d);
        d3d = 0;
    }
}
