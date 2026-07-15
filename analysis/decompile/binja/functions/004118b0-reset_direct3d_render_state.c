/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_direct3d_render_state @ 0x4118b0 */

004118bd        struct Direct3DDevice8* device = renderer->device
004118c6        device->vtbl->SetRenderState(device, 0x8b, 0xffffff)
004118cc        struct Direct3DDevice8* device_1 = renderer->device
004118dc        device_1->vtbl->SetRenderState(device_1, 0x89, 0)
004118e2        struct Direct3DDevice8* device_2 = renderer->device
004118ef        device_2->vtbl->SetRenderState(device_2, 0x16, 1)
004118f5        struct Direct3DDevice8* device_3 = renderer->device
00411902        device_3->vtbl->SetRenderState(device_3, 7, 1)
00411908        struct Direct3DDevice8* device_7 = renderer->device
00411915        device_7->vtbl->SetRenderState(device_7, 0x10, 1)
0041191b        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00411927        device_4->vtbl->SetRenderState(device_4, 0xf, 1)
0041192d        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00411939        device_5->vtbl->SetRenderState(device_5, 0x18, 0)
0041193f        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
0041194b        device_6->vtbl->SetRenderState(device_6, 0x19, 5)
00411952        return
