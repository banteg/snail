/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_blend_mode @ 0x412d00 */

00412d07        if (blend_mode u> 0x14)
00412d07        return
00412d0d        int32_t ecx_1 = 0
00412d0f        ecx_1.b = lookup_table_412e30[blend_mode]
00412d15        int32_t value
00412d15        struct Direct3DDevice8* device_4
00412d15        struct Direct3DDevice8Vtbl* vtbl
00412d15        switch (ecx_1)
00412d1c        case 0
00412d1c        struct Direct3DDevice8* device = g_direct3d_renderer.device
00412d28        device->vtbl->SetRenderState(device, 0x1b, 1)
00412d2e        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00412d3a        device_1->vtbl->SetRenderState(device_1, 0x13, 5)
00412d40        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00412d4c        device_2->vtbl->SetRenderState(device_2, 0x14, 6)
00412d53        case 1
00412d53        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00412d5f        device_3->vtbl->SetRenderState(device_3, 0x1b, 1)
00412d65        device_4 = g_direct3d_renderer.device
00412d6a        value = 5
00412d6c        vtbl = device_4->vtbl
00412dff        label_412dff:
00412dff        vtbl->SetRenderState(device_4, 0x13, value)
00412e05        struct Direct3DDevice8* device_12 = g_direct3d_renderer.device
00412e11        device_12->vtbl->SetRenderState(device_12, 0x14, 6)
00412d73        case 2
00412d73        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00412d7f        device_5->vtbl->SetRenderState(device_5, 0x1b, 1)
00412d85        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
00412d91        device_6->vtbl->SetRenderState(device_6, 0x13, 5)
00412d97        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
00412da3        device_7->vtbl->SetRenderState(device_7, 0x14, 2)
00412daa        case 3
00412daa        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
00412db6        device_8->vtbl->SetRenderState(device_8, 0x1b, 1)
00412dbc        struct Direct3DDevice8* device_9 = g_direct3d_renderer.device
00412dc8        device_9->vtbl->SetRenderState(device_9, 0x13, 2)
00412dce        struct Direct3DDevice8* device_10 = g_direct3d_renderer.device
00412dda        device_10->vtbl->SetRenderState(device_10, 0x14, 2)
00412de1        case 4
00412de1        struct Direct3DDevice8* device_11 = g_direct3d_renderer.device
00412ded        device_11->vtbl->SetRenderState(device_11, 0x1b, 1)
00412df3        device_4 = g_direct3d_renderer.device
00412df8        value = 2
00412dfa        vtbl = device_4->vtbl
00412dfa        goto label_412dff
00412e17        return
