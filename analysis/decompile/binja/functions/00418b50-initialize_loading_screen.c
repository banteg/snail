/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_loading_screen @ 0x418b50 */

00418b53        g_runtime_config.last_loading_budget = 0x4fc
00418b69        int32_t out_size
00418b69        int32_t eax_2
00418b69        if (is_archive_index_loaded() == 0)
00418bd9        eax_2 = sub_453404(g_direct3d_renderer.device, "Sprites/Loading.tga", 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_bar_on_texture)
00418b6b        void* buffer = get_archive_data_base()
00418b7d        load_file_bytes_from_archive_or_fs("Sprites/Loading.tga", buffer, &out_size)
00418bac        eax_2 = sub_4533c4(g_direct3d_renderer.device, buffer, out_size, 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_bar_on_texture)
00418be0        if (eax_2 s< 0)
00418be7        report_errorf("Failed to Create DirectX Texture Sprites/Loading.tga")
00418c00        sub_453467(g_direct3d_renderer.device, "Sprites/Debug.tga", &g_loading_bar_on_texture)
00418c05        struct Direct3DDevice8* device = g_direct3d_renderer.device
00418c15        device->vtbl->SetTexture(device, 0, g_loading_bar_on_texture)
00418c1b        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00418c28        device_1->vtbl->SetTextureStageState(device_1, 0, 0x10, 3)
00418c2e        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00418c3b        device_2->vtbl->SetTextureStageState(device_2, 0, 0x11, 3)
00418c41        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00418c4e        device_3->vtbl->SetTextureStageState(device_3, 0, 0xd, 3)
00418c54        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00418c61        device_4->vtbl->SetTextureStageState(device_4, 0, 0xe, 3)
00418c6e        int32_t eax_6
00418c6e        if (is_archive_index_loaded() == 0)
00418cda        eax_6 = sub_453404(g_direct3d_renderer.device, "Sprites/LoadingBarOn.tga", 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_background_texture)
00418c70        void* buffer_1 = get_archive_data_base()
00418c82        load_file_bytes_from_archive_or_fs("Sprites/LoadingBarOn.tga", buffer_1, &out_size)
00418caf        eax_6 = sub_4533c4(g_direct3d_renderer.device, buffer_1, out_size, 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_background_texture)
00418ce1        if (eax_6 s< 0)
00418ce8        report_errorf("Failed to Create DirectX Texture Sprites/LoadingBarOn.tga")
00418d01        sub_453467(g_direct3d_renderer.device, "Sprites/Debug.tga", &g_loading_background_texture)
00418d06        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00418d16        device_5->vtbl->SetTexture(device_5, 0, g_loading_background_texture)
00418d1c        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
00418d29        device_6->vtbl->SetTextureStageState(device_6, 0, 0x10, 3)
00418d2f        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
00418d3c        device_7->vtbl->SetTextureStageState(device_7, 0, 0x11, 3)
00418d5f        data_503284 = create_vertex_buffer(&g_direct3d_renderer, 4, 0x102)
00418d69        data_5032a4 = create_vertex_buffer(&g_direct3d_renderer, 4, 0x102)
00418d78        int32_t* eax_11 = *(data_503284 + 8)
00418d82        int32_t* var_8
00418d82        (*(*eax_11 + 0x2c))(eax_11, 0, 0x50, &var_8, 0)
00418d89        *var_8 = 0
00418d8f        var_8[1] = 0
00418d96        var_8[2] = 0
00418d9d        var_8[3] = 0
00418da4        var_8[4] = 0
00418db0        var_8[5] = 0x44200000
00418db7        var_8[6] = 0
00418dc3        var_8[7] = 0
00418dca        var_8[8] = 0x3f800000
00418dd1        var_8[9] = 0
00418dd8        var_8[0xa] = 0x44200000
00418de4        var_8[0xb] = 0x43f00000
00418deb        var_8[0xc] = 0
00418df2        var_8[0xd] = 0x3f800000
00418df9        var_8[0xe] = 0x3f800000
00418e00        var_8[0xf] = 0
00418e07        var_8[0x10] = 0x43f00000
00418e0e        var_8[0x11] = 0
00418e15        var_8[0x12] = 0
00418e1c        var_8[0x13] = 0x3f800000
00418e25        int32_t* eax_15 = *(data_5032a4 + 8)
00418e2b        (*(*eax_15 + 0x30))(eax_15)
00418e2e        int32_t result = begin_overlay_render_state()
00418e33        arg1[2] = 0
00418e36        arg1[1] = 0
00418e3a        *arg1 = 1
00418e45        return result
