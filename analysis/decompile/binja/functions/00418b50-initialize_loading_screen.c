/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_loading_screen @ 0x418b50 */

00418b53        g_last_loading_budget = 0x4fc
00418b69        int32_t var_4
00418b69        int32_t eax_3
00418b69        if (is_archive_index_loaded() == 0)
00418bd9        eax_3 = sub_453404(data_502fec, "Sprites/Loading.tga", 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_bar_on_texture)
00418b6b        char* eax_1 = get_archive_data_base()
00418b7d        load_file_bytes_from_archive_or_fs("Sprites/Loading.tga", eax_1, &var_4)
00418bac        eax_3 = sub_4533c4(data_502fec, eax_1, var_4, 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_bar_on_texture)
00418be0        if (eax_3 s< 0)
00418be7        report_errorf("Failed to Create DirectX Texture Sprites/Loading.tga")
00418c00        sub_453467(data_502fec, "Sprites/Debug.tga", &g_loading_bar_on_texture)
00418c05        int32_t* eax_5 = data_502fec
00418c15        (*(*eax_5 + 0xf4))(eax_5, 0, g_loading_bar_on_texture)
00418c1b        int32_t* eax_6 = data_502fec
00418c28        (*(*eax_6 + 0xfc))(eax_6, 0, 0x10, 3)
00418c2e        int32_t* eax_7 = data_502fec
00418c3b        (*(*eax_7 + 0xfc))(eax_7, 0, 0x11, 3)
00418c41        int32_t* eax_8 = data_502fec
00418c4e        (*(*eax_8 + 0xfc))(eax_8, 0, 0xd, 3)
00418c54        int32_t* eax_9 = data_502fec
00418c61        (*(*eax_9 + 0xfc))(eax_9, 0, 0xe, 3)
00418c6e        int32_t eax_13
00418c6e        if (is_archive_index_loaded() == 0)
00418cda        eax_13 = sub_453404(data_502fec, "Sprites/LoadingBarOn.tga", 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_background_texture)
00418c70        char* eax_11 = get_archive_data_base()
00418c82        load_file_bytes_from_archive_or_fs("Sprites/LoadingBarOn.tga", eax_11, &var_4)
00418caf        eax_13 = sub_4533c4(data_502fec, eax_11, var_4, 0, 0, 1, 0, 0x15, 1, 3, 3, 0xff00ff00, 0, 0, &g_loading_background_texture)
00418ce1        if (eax_13 s< 0)
00418ce8        report_errorf("Failed to Create DirectX Texture Sprites/LoadingBarOn.tga")
00418d01        sub_453467(data_502fec, "Sprites/Debug.tga", &g_loading_background_texture)
00418d06        int32_t* eax_15 = data_502fec
00418d16        (*(*eax_15 + 0xf4))(eax_15, 0, g_loading_background_texture)
00418d1c        int32_t* eax_16 = data_502fec
00418d29        (*(*eax_16 + 0xfc))(eax_16, 0, 0x10, 3)
00418d2f        int32_t* eax_17 = data_502fec
00418d3c        (*(*eax_17 + 0xfc))(eax_17, 0, 0x11, 3)
00418d5f        data_503284 = create_object_vertex_buffer_resource(&g_direct3d_renderer, 4, 0x102)
00418d69        data_5032a4 = create_object_vertex_buffer_resource(&g_direct3d_renderer, 4, 0x102)
00418d78        int32_t* eax_21 = *(data_503284 + 8)
00418d82        int32_t* var_8
00418d82        (*(*eax_21 + 0x2c))(eax_21, 0, 0x50, &var_8, 0)
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
00418e25        int32_t* eax_25 = *(data_5032a4 + 8)
00418e2b        (*(*eax_25 + 0x30))(eax_25)
00418e2e        int32_t result = begin_overlay_render_state()
00418e33        arg1[2] = 0
00418e36        arg1[1] = 0
00418e3a        *arg1 = 1
00418e45        return result
