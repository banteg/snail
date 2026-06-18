// bind_texture_ref @ 0x414500 (cdecl)

#include "sprite.h"

struct TextureBindDevice;

struct TextureBindDeviceVtbl {
    char unknown_000[0xf4];
    int (__stdcall* SetTexture)(TextureBindDevice* self, int stage, void* texture);
    void* unknown_0f8;
    int (__stdcall* SetTextureStageState)(TextureBindDevice* self, int stage, int type, int value);
};

struct TextureBindDevice {
    TextureBindDeviceVtbl* vtbl;
};

extern TextureBindDevice* g_d3d_device;       // data_502fec
extern TextureRef* g_current_texture_ref;     // data_503174
extern int g_texture_bind_call_count;         // data_5031c0
extern void** g_d3d_texture_slots;            // data_5031c8

int report_errorf(char* format, ...);

void bind_texture_ref(TextureRef* texture)
{
    if (texture == g_current_texture_ref) {
        return;
    }

    TextureBindDevice* device = g_d3d_device;
    g_current_texture_ref = texture;
    int result = device->vtbl->SetTexture(device, 0, g_d3d_texture_slots[texture->slot_index]);
    ++g_texture_bind_call_count;

    if (result != 0) {
        report_errorf("SetTexture Failed %s", texture->name);
        return;
    }

    if ((texture->flags & 0x1000) != 0) {
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
