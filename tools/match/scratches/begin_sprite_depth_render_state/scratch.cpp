// begin_sprite_depth_render_state @ 0x413540 (cdecl)

#include "render_pipeline_state.h"
#include "render_state_device.h"

int begin_sprite_depth_render_state()
{
    RenderStateDevice* device = g_d3d_device;

    TransformMatrix identity;
    identity.position.z = 0.0f;
    identity.position.y = 0.0f;
    identity.position.x = 0.0f;
    identity.basis_forward_w = 0.0f;
    identity.basis_forward.y = 0.0f;
    identity.basis_forward.x = 0.0f;
    identity.basis_up_w = 0.0f;
    identity.basis_up.z = 0.0f;
    identity.basis_up.x = 0.0f;
    identity.basis_right_w = 0.0f;
    identity.basis_right.z = 0.0f;
    identity.basis_right.y = 0.0f;
    identity.position_w = 1.0f;
    identity.basis_forward.z = 1.0f;
    identity.basis_up.y = 1.0f;
    identity.basis_right.x = 1.0f;

    device->vtbl->GetTransform(device, 2, &g_saved_d3d_view_transform);
    device = g_d3d_device;
    device->vtbl->SetTransform(device, 2, &identity);
    device = g_d3d_device;
    device->vtbl->SetTransform(device, 0x100, &identity);
    device = g_d3d_device;
    device->vtbl->SetTextureStageState(device, 0, 0xd, 3);
    device = g_d3d_device;
    device->vtbl->SetTextureStageState(device, 0, 0xe, 3);
    device = g_d3d_device;
    return device->vtbl->SetTextureStageState(device, 0, 0x18, 0);
}
