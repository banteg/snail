// begin_sprite_depth_render_state @ 0x413540 (cdecl)

#include "transform_matrix.h"

struct RenderStateDevice;

struct RenderStateDeviceVtbl {
    char unknown_000[0x94];
    int (__stdcall* SetTransform)(RenderStateDevice* self, int state, TransformMatrix* matrix);
    int (__stdcall* GetTransform)(RenderStateDevice* self, int state, TransformMatrix* matrix);
    char unknown_09c[0xfc - 0x9c];
    int (__stdcall* SetTextureStageState)(RenderStateDevice* self, int stage, int type, int value);
};

struct RenderStateDevice {
    RenderStateDeviceVtbl* vtbl;
};

extern RenderStateDevice* g_d3d_device; // data_502fec
extern TransformMatrix g_saved_d3d_view_transform; // data_503178

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
