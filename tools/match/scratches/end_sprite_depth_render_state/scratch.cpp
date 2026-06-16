// end_sprite_depth_render_state @ 0x413650 (cdecl)

#include "transform_matrix.h"

struct RenderStateDevice;

struct RenderStateDeviceVtbl {
    char unknown_000[0x94];
    int (__stdcall* SetTransform)(RenderStateDevice* self, int state, TransformMatrix* matrix);
};

struct RenderStateDevice {
    RenderStateDeviceVtbl* vtbl;
};

extern RenderStateDevice* g_d3d_device; // data_502fec
extern TransformMatrix g_saved_d3d_view_transform; // data_503178

int end_sprite_depth_render_state()
{
    RenderStateDevice* device = g_d3d_device;
    return device->vtbl->SetTransform(device, 2, &g_saved_d3d_view_transform);
}
