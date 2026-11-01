/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_registered_texture_ref @ 0x412a70 */

00412a83        uint32_t flags = g_texture_refs.entries[arg1].flags
00412a8c        if ((flags:1.b & 0x80) != 0)
00412cf6        return flags
00412a92        char* path = &(*g_texture_refs.entries)[arg1].name
00412aa5        if (archive_or_file_exists(path, 0) == 0)
00412aad        report_warningf("Texture File Missing using Debug.tga (%s)", path)
00412ad5        return D3DXCreateTextureFromFileA(g_direct3d_renderer.device, "Sprites/Debug.tga", &g_d3d_texture_slots[arg1])
00412add        if ((g_texture_refs.entries[arg1].flags.b & 0x20) == 0)
00412af2        (*g_texture_refs.entries)[arg1].texture_ref = 0
00412aea        (*g_texture_refs.entries)[arg1].texture_ref = load_file_bytes(path, nullptr)
00412b05        void buffer
00412b05        load_file_bytes_fixed_size_from_archive_or_fs(path, &buffer, 0x14)
00412b11        int32_t ebx_1 = 0
00412b16        char var_4
00412b16        ebx_1.b = var_4 != 0x20
00412b1a        int32_t ebx_3 = (ebx_1 - 1) & 0xffffff
00412b2b        int32_t eax_7
00412b2b        int32_t edi_1
00412b2b        if (is_archive_index_loaded() == 0)
00412b8c        edi_1 = arg1 << 2
00412baf        eax_7 = D3DXCreateTextureFromFileExA(g_direct3d_renderer.device, path, 0, 0, (*g_texture_refs.entries)[arg1].mip_levels, 0, 0x15, 1, 3, 3, ebx_3, 0, 0, edi_1 + g_d3d_texture_slots)
00412b2d        void* buffer_1 = get_archive_data_base()
00412b3b        int32_t out_size
00412b3b        load_file_bytes_from_archive_or_fs(path, buffer_1, &out_size)
00412b49        edi_1 = arg1 << 2
00412b7a        eax_7 = D3DXCreateTextureFromFileInMemoryEx(g_direct3d_renderer.device, buffer_1, out_size, 0, 0, (*g_texture_refs.entries)[arg1].mip_levels, 0, 0x15, 1, 3, 3, ebx_3, 0, 0, edi_1 + g_d3d_texture_slots)
00412bb7        if (eax_7 s< 0)
00412bbf        report_errorf("Failed to Create DirectX Texture %s", path)
00412be6        return D3DXCreateTextureFromFileA(g_direct3d_renderer.device, "Sprites/Debug.tga", edi_1 + g_d3d_texture_slots)
00412bed        struct Direct3DDevice8* device = g_direct3d_renderer.device
00412bfb        device->vtbl->SetTexture(device, 0, *(edi_1 + g_d3d_texture_slots))
00412c01        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
00412c0f        device_1->vtbl->SetTextureStageState(device_1, 0, 0x10, 3)
00412c15        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00412c23        device_2->vtbl->SetTextureStageState(device_2, 0, 0x11, 3)
00412c2e        if (var_4 == 0x20)
00412c43        g_texture_refs.entries[arg1].flags |= 0x10000
00412c49        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00412c53        device_3->vtbl->SetTextureStageState(device_3, 0, 1, 4)
00412c59        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00412c67        device_4->vtbl->SetTextureStageState(device_4, 0, 2, 2)
00412c6d        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00412c7b        device_5->vtbl->SetTextureStageState(device_5, 0, 3, 0)
00412c81        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
00412c8f        device_6->vtbl->SetTextureStageState(device_6, 0, 4, 4)
00412c95        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
00412ca3        device_7->vtbl->SetTextureStageState(device_7, 0, 5, 2)
00412ca9        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
00412cb7        device_8->vtbl->SetTextureStageState(device_8, 0, 6, 0)
00412cc5        int32_t var_8
00412cc5        uint32_t ecx_15 = zx.d(var_8.w)
00412ccb        flags = zx.d(var_8:2.w)
00412cd2        int32_t estimated_texture_vram_bytes_1 = g_estimated_texture_vram_bytes
00412cdb        (*g_texture_refs.entries)[arg1].loaded_width = ecx_15
00412ce1        (*g_texture_refs.entries)[arg1].loaded_height = flags
00412cea        g_estimated_texture_vram_bytes = estimated_texture_vram_bytes_1 + ((ecx_15 * flags) << 2)
00412cf6        return flags
