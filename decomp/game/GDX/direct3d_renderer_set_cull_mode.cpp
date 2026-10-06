// direct3d_renderer_set_cull_mode @ 0x411700 (thiscall, ret 0x4)

#include "direct3d_renderer.h"

int Direct3DRenderer::direct3d_renderer_set_cull_mode(char cull_front)
{
    if (cull_front != 0) {
        return this->device->vtbl->SetRenderState(this->device, 0x16, 3);
    }
    return this->device->vtbl->SetRenderState(this->device, 0x16, 1);
}
