// Direct3DRenderer::restore_texture_ref_stage_states @ 0x4143c0

#include "direct3d_renderer.h"
#include "texture_registry.h"

void Direct3DRenderer::restore_texture_ref_stage_states()
{
    int index = 0;
    if (g_texture_refs.count <= 0) {
        return;
    }

    TextureRef* texture = &g_texture_refs.entries[0];
    do {

        device->vtbl->SetTexture(device, 0, g_d3d_texture_slots[index]);
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x10, 3);
        g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x11, 3);

        if ((texture->flags & TEXTURE_REF_HAS_ALPHA) != 0) {
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 1, 4);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 2, 2);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 3, 0);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 4, 4);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 5, 2);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 6, 0);
        }

        if ((texture->flags & TEXTURE_REF_WRAP_ADDRESSING) != 0) {
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x0d, 1);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x0e, 1);
        } else {
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x0d, 3);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x0e, 3);
        }

        ++index;
        ++texture;
    } while (index < g_texture_refs.count);
}
