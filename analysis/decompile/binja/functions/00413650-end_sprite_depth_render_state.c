/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: end_sprite_depth_render_state @ 0x413650 */

00413650        struct Direct3DDevice8* device = g_direct3d_renderer.device
00413665        return device->vtbl->SetTransform(device, 2, &data_503178)
