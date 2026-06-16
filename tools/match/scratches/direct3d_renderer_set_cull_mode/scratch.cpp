// direct3d_renderer_set_cull_mode @ 0x411700 (thiscall, ret 0x4)

#include "direct3d_device8_view.h"

struct Direct3DDevice8Vtbl {
    char unknown_000[0xc8];
    int (__stdcall* SetRenderState)(Direct3DDevice8* self, int state, int value);
};

class Direct3DRenderer {
public:
    int direct3d_renderer_set_cull_mode(char cull_front);

    char unknown_0000[0xbb94];
    Direct3DDevice8* device; // +0xbb94
};

int Direct3DRenderer::direct3d_renderer_set_cull_mode(char cull_front)
{
    if (cull_front != 0) {
        return this->device->vtbl->SetRenderState(this->device, 0x16, 3);
    }
    return this->device->vtbl->SetRenderState(this->device, 0x16, 1);
}
