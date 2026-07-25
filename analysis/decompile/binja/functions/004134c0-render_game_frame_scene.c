/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_game_frame_scene @ 0x4134c0 */

004134c0        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
004134da        device_2->vtbl->Clear(device_2, 0, nullptr, 2, 0xff000000, 1f, 0)
004134e0        struct Direct3DDevice8* device = g_direct3d_renderer.device
004134e8        device->vtbl->BeginScene(device)
004134f3        g_render_successful_primitive_count = 0
004134fd        update_display_mode_view_state(&g_display_mode_state)
00413508        render_game_frame(g_game_base)
0041350d        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00413515        device_1->vtbl->EndScene(device_1)
0041351b        return
