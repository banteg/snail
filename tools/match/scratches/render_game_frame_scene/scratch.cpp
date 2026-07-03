// render_game_frame_scene @ 0x4134c0 (cdecl)

#include "direct3d_device8_view.h"
#include "display_mode_state.h"
#include "game_root.h"

extern Direct3DDevice8* g_d3d_device; // data_502fec
extern DisplayModeState g_display_mode_state; // data_4df9e0
extern int g_render_successful_primitive_count; // data_4f7454
extern char* g_game_base; // data_4df904

void render_game_frame_scene()
{
    Direct3DDevice8* device = g_d3d_device;
    device->vtbl->Clear(device, 0, 0, 2, 0xff000000, 1.0f, 0);

    device = g_d3d_device;
    device->vtbl->BeginScene(device);

    g_render_successful_primitive_count = 0;
    g_display_mode_state.update_display_mode_view_state();
    ((GameRoot*)g_game_base)->render_game_frame();

    device = g_d3d_device;
    device->vtbl->EndScene(device);
}
