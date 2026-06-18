// configure_sprite_render_state @ 0x413670 (cdecl, ret)

struct Sprite {
    char unknown_00[0x28];
    int draw_mode; // +0x28
};

struct Direct3DDevice8;

struct Direct3DDevice8Vtbl {
    char unknown_00[0xc8];
    int (__stdcall* SetRenderState)(Direct3DDevice8* self, int state, int value);
};

struct Direct3DDevice8 {
    Direct3DDevice8Vtbl* vtbl;
};

extern Direct3DDevice8* g_d3d_device; // data_502fec

int configure_sprite_render_state(Sprite* sprite)
{
    switch (sprite->draw_mode) {
    case 2:
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 0);
    case 0:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
    case 1:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 1);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 6);
    case 10:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
    case 11:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 2);
    case 13:
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 1);
        g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x13, 5);
        return g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x14, 3);
    }

    return sprite->draw_mode;
}
