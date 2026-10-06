// begin_overlay_render_state @ 0x411e10 (cdecl)

#include "render_pipeline_state.h"
#include "render_state_device.h"

TransformMatrix* __stdcall build_orthographic_projection_matrix(
    TransformMatrix* matrix, float width, float height, float near_z, float far_z); // @ 0x4503a8
extern "C" TransformMatrix* __stdcall D3DXMatrixTranslation(
    TransformMatrix* matrix, float x, float y, float z); // @ 0x44fd8a

int begin_overlay_render_state()
{
    RenderStateDevice* device = g_d3d_device;
    device->vtbl->GetTransform(device, 3, &g_saved_d3d_projection_transform);

    device = g_d3d_device;
    device->vtbl->GetTransform(device, 2, &g_saved_d3d_view_transform);

    device = g_d3d_device;
    device->vtbl->SetTextureStageState(device, 0, 0xd, 3);
    device = g_d3d_device;
    device->vtbl->SetTextureStageState(device, 0, 0xe, 3);

    TransformMatrix projection;
    build_orthographic_projection_matrix(&projection, 640.0f, -480.0f, 0.0f, 1.0f);

    device = g_d3d_device;
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

    device->vtbl->SetTransform(device, 3, &projection);
    device = g_d3d_device;
    device->vtbl->SetTransform(device, 0x100, &identity);

    D3DXMatrixTranslation(&identity, -320.6f, -240.6f, 0.0f);

    device = g_d3d_device;
    device->vtbl->SetTransform(device, 2, &identity);
    device = g_d3d_device;
    device->vtbl->SetRenderState(device, 7, 0);
    device = g_d3d_device;
    device->vtbl->SetRenderState(device, 0xe, 0);
    device = g_d3d_device;
    return device->vtbl->SetRenderState(device, 0x89, 0);
}
