// render_game_frame_scene @ 0x4134c0 (cdecl)

#include "direct3d_device8_view.h"
#include "display_mode_state.h"
#include "game_root.h"
#include "render_pipeline_state.h"

extern GameRoot* g_game; // data_4df904

void render_game_frame_scene()
{
    Direct3DDevice8* device = g_d3d_device;
    device->vtbl->Clear(device, 0, 0, 2, 0xff000000, 1.0f, 0);

    device = g_d3d_device;
    device->vtbl->BeginScene(device);

    g_render_successful_primitive_count = 0;
    g_display_mode_state.update_display_mode_view_state();
    g_game->render_game_frame();

    device = g_d3d_device;
    device->vtbl->EndScene(device);
}
