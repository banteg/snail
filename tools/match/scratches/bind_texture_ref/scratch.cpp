// bind_texture_ref @ 0x414500 (cdecl)

#include "direct3d_device8_view.h"
#include "sprite.h"
#include "texture_registry.h"

extern int g_texture_bind_call_count;         // data_5031c0

int report_errorf(char* format, ...);

void bind_texture_ref(TextureRef* texture)
{
    if (texture == g_current_texture_ref) {
        return;
    }

    Direct3DDevice8* device = g_d3d_device;
    g_current_texture_ref = texture;
    int result = device->vtbl->SetTexture(device, 0, g_d3d_texture_slots[texture->slot_index]);
    ++g_texture_bind_call_count;

    if (result != 0) {
        report_errorf("SetTexture Failed %s", texture->name);
        return;
    }

    if ((texture->flags & TEXTURE_REF_WRAP_ADDRESSING) != 0) {
        device = g_d3d_device;
        device->vtbl->SetTextureStageState(device, 0, 0x0d, 1);
        device = g_d3d_device;
        device->vtbl->SetTextureStageState(device, 0, 0x0e, 1);
        return;
    }

    device = g_d3d_device;
    device->vtbl->SetTextureStageState(device, 0, 0x0d, 3);
    device = g_d3d_device;
    device->vtbl->SetTextureStageState(device, 0, 0x0e, 3);
}
