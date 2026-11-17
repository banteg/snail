/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: end_overlay_render_state @ 0x411de0 */

00411de0        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00411def        device_1->vtbl->SetTransform(device_1, 3, &data_503220)
00411df5        struct Direct3DDevice8* device = g_direct3d_renderer.device
00411e0a        return device->vtbl->SetTransform(device, 2, &data_503178)
