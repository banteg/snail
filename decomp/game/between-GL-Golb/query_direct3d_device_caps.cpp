// Direct3DRenderer::query_direct3d_device_caps @ 0x414600

#include "direct3d_renderer.h"

extern int debug_report_stub(char* format, int value); // @ 0x449c00

void Direct3DRenderer::query_direct3d_device_caps()
{
    d3d->vtbl->GetDeviceCaps(d3d, 0, 1, &device_caps);
    debug_report_stub("Max Texture Width %i\n", device_caps.max_texture_width);
    debug_report_stub("Max Texture Height %i\n", device_caps.max_texture_height);
}
