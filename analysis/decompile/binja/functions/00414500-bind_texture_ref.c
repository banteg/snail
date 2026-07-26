/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: bind_texture_ref @ 0x414500 */

0041450c        if (texture == g_current_texture_ref)
0041450c        return
00414512        struct Direct3DDevice8* device = g_direct3d_renderer.device
00414518        struct Direct3DTexture8** d3d_texture_slots_1 = g_d3d_texture_slots
0041451e        g_current_texture_ref = texture
00414533        int32_t eax = device->vtbl->SetTexture(device, 0, d3d_texture_slots_1[texture->slot_index])
00414543        g_texture_bind_call_count += 1
00414549        if (eax != 0)
00414554        report_errorf("SetTexture Failed %s", &texture->name)
0041455d        return
00414563        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00414568        struct Direct3DDevice8Vtbl* vtbl = device_1->vtbl
0041456a        if (((texture->flags).w:1.b & 0x10) != 0)
00414573        vtbl->SetTextureStageState(device_1, 0, 0xd, 1)
00414579        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00414587        device_2->vtbl->SetTextureStageState(device_2, 0, 0xe, 1)
0041458e        return
00414596        vtbl->SetTextureStageState(device_1, 0, 0xd, 3)
0041459c        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
004145aa        device_3->vtbl->SetTextureStageState(device_3, 0, 0xe, 3)
004145b1        return
