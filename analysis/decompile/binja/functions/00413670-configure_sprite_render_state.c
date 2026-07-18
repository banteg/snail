/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: configure_sprite_render_state @ 0x413670 */

00413674        int32_t draw_mode = sprite->draw_mode
0041367a        if (draw_mode u<= 0xd)
00413680        int32_t ecx_1 = 0
00413682        ecx_1.b = configure_sprite_render_state_lookup_table[draw_mode]
00413688        switch (ecx_1)
004136a2        case 0
004136a2        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
004136ae        device_1->vtbl->SetRenderState(device_1, 0x1b, 1)
004136b4        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
004136c0        device_2->vtbl->SetRenderState(device_2, 0x13, 5)
004136c6        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
004136d8        return device_3->vtbl->SetRenderState(device_3, 0x14, 6)
004136d9        case 1
004136d9        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
004136e5        device_4->vtbl->SetRenderState(device_4, 0x1b, 1)
004136eb        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
004136f7        device_5->vtbl->SetRenderState(device_5, 0x13, 1)
004136fd        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
0041370f        return device_6->vtbl->SetRenderState(device_6, 0x14, 6)
0041368f        case 2
0041368f        struct Direct3DDevice8* device = g_direct3d_renderer.device
004136a1        return device->vtbl->SetRenderState(device, 0x1b, 0)
00413710        case 3
00413710        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
0041371c        device_7->vtbl->SetRenderState(device_7, 0x1b, 1)
00413722        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
0041372e        device_8->vtbl->SetRenderState(device_8, 0x13, 5)
00413734        struct Direct3DDevice8* device_9 = g_direct3d_renderer.device
00413746        return device_9->vtbl->SetRenderState(device_9, 0x14, 2)
00413747        case 4
00413747        struct Direct3DDevice8* device_10 = g_direct3d_renderer.device
00413753        device_10->vtbl->SetRenderState(device_10, 0x1b, 1)
00413759        struct Direct3DDevice8* device_11 = g_direct3d_renderer.device
00413765        device_11->vtbl->SetRenderState(device_11, 0x13, 5)
0041376b        struct Direct3DDevice8* device_12 = g_direct3d_renderer.device
0041377d        return device_12->vtbl->SetRenderState(device_12, 0x14, 2)
0041377e        case 5
0041377e        struct Direct3DDevice8* device_13 = g_direct3d_renderer.device
0041378a        device_13->vtbl->SetRenderState(device_13, 0x1b, 1)
00413790        struct Direct3DDevice8* device_14 = g_direct3d_renderer.device
0041379c        device_14->vtbl->SetRenderState(device_14, 0x13, 5)
004137a2        struct Direct3DDevice8* device_15 = g_direct3d_renderer.device
004137ae        return device_15->vtbl->SetRenderState(device_15, 0x14, 3)
004137b4        return draw_mode
