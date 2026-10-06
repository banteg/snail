// end_overlay_render_state @ 0x411de0 (cdecl)

#include "render_pipeline_state.h"
#include "render_state_device.h"

int end_overlay_render_state()
{
    RenderStateDevice* device = g_d3d_device;
    device->vtbl->SetTransform(device, 3, &g_saved_d3d_projection_transform);

    device = g_d3d_device;
    return device->vtbl->SetTransform(device, 2, &g_saved_d3d_view_transform);
}
