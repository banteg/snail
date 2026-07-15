/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_immediate_blend_mode @ 0x412e50 */

00412e57        int32_t value
00412e57        int32_t value_1
00412e57        struct Direct3DDevice8* device_5
00412e57        struct Direct3DDevice8* device_11
00412e57        struct Direct3DDevice8Vtbl* vtbl
00412e57        struct Direct3DDevice8Vtbl* vtbl_1
00412e57        switch (blend_mode)
00412e64        case 0
00412e64        struct Direct3DDevice8* device = g_direct3d_renderer.device
00412e70        device->vtbl->SetRenderState(device, 0x1b, 0)
00412e77        case 1
00412e77        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00412e83        device_1->vtbl->SetRenderState(device_1, 0x1b, 1)
00412e89        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00412e95        device_2->vtbl->SetRenderState(device_2, 0x13, 5)
00412e9b        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00412ea7        device_3->vtbl->SetRenderState(device_3, 0x14, 6)
00412eae        case 2
00412eae        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00412eba        device_4->vtbl->SetRenderState(device_4, 0x1b, 1)
00412ec0        device_5 = g_direct3d_renderer.device
00412ec5        value = 1
00412ec7        vtbl_1 = device_5->vtbl
00412fce        label_412fce:
00412fce        vtbl_1->SetRenderState(device_5, 0x13, value)
00412fd4        struct Direct3DDevice8* device_18 = g_direct3d_renderer.device
00412fe0        device_18->vtbl->SetRenderState(device_18, 0x14, 6)
00412fb0        case 3, 7, 0xf
00412fb0        struct Direct3DDevice8* device_17 = g_direct3d_renderer.device
00412fbc        device_17->vtbl->SetRenderState(device_17, 0x1b, 1)
00412fc2        device_5 = g_direct3d_renderer.device
00412fc7        value = 5
00412fc9        vtbl_1 = device_5->vtbl
00412fc9        goto label_412fce
00412ece        case 4
00412ece        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
00412eda        device_6->vtbl->SetRenderState(device_6, 0x1b, 1)
00412ee0        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
00412eec        device_7->vtbl->SetRenderState(device_7, 0x13, 5)
00412ef2        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
00412efe        device_8->vtbl->SetRenderState(device_8, 0x14, 6)
00412f79        case 5, 8, 0xb, 0xd
00412f79        struct Direct3DDevice8* device_15 = g_direct3d_renderer.device
00412f85        device_15->vtbl->SetRenderState(device_15, 0x1b, 1)
00412f8b        device_11 = g_direct3d_renderer.device
00412f90        value_1 = 5
00412f92        vtbl = device_11->vtbl
00412f92        goto label_412f97
00412f25        case 6
00412f25        struct Direct3DDevice8* device_10 = g_direct3d_renderer.device
00412f31        device_10->vtbl->SetRenderState(device_10, 0x1b, 1)
00412f37        device_11 = g_direct3d_renderer.device
00412f3c        value_1 = 2
00412f3e        vtbl = device_11->vtbl
00412f97        label_412f97:
00412f97        vtbl->SetRenderState(device_11, 0x13, value_1)
00412f9d        struct Direct3DDevice8* device_16 = g_direct3d_renderer.device
00412fa9        device_16->vtbl->SetRenderState(device_16, 0x14, 2)
00412f42        case 9, 0xc
00412f42        struct Direct3DDevice8* device_12 = g_direct3d_renderer.device
00412f4e        device_12->vtbl->SetRenderState(device_12, 0x1b, 1)
00412f54        struct Direct3DDevice8* device_13 = g_direct3d_renderer.device
00412f60        device_13->vtbl->SetRenderState(device_13, 0x13, 5)
00412f66        struct Direct3DDevice8* device_14 = g_direct3d_renderer.device
00412f72        device_14->vtbl->SetRenderState(device_14, 0x14, 2)
00412f05        case 0xe
00412f05        struct Direct3DDevice8* device_9 = g_direct3d_renderer.device
00412f11        device_9->vtbl->SetRenderState(device_9, 0x1b, 1)
00412f17        device_5 = g_direct3d_renderer.device
00412f1c        value = 0xa
00412f1e        vtbl_1 = device_5->vtbl
00412f20        goto label_412fce
00412fe6        return
