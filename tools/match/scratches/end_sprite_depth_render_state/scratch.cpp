// end_sprite_depth_render_state @ 0x413650 (cdecl)

#include "render_pipeline_state.h"
#include "render_state_device.h"

int end_sprite_depth_render_state()
{
    RenderStateDevice* device = g_d3d_device;
    return device->vtbl->SetTransform(device, 2, &g_saved_d3d_view_transform);
}
