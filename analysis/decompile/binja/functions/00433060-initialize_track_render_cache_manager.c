/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_render_cache_manager @ 0x433060 */

00433070        __builtin_memcpy(&manager->max_vertex_counts, "\x30\x02\x00\x00\x30\x02\x00\x00\xa0\x00\x00\x00\x50\x00\x00\x00\x20\x03\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\xf0\x00\x00\x00\xa0\x00\x00\x00\x00\x05\x00\x00", 0x28)
004330b4        manager->owner_subgame = &g_game_base->subgame
004330b7        int32_t var_8 = 0
004330bb        struct Object** var_4 = &manager->slots[0][4].bod.object
004331cc        bool cond:1_1
004330bf        int32_t i = 0
004331a8        while (i s< 5)
004330d3        void* esi_1 = manager + (var_8 + i) * 0x3c
004330df        set_bod_object(esi_1 + 0x58, add_object_to_list(&g_object_list))
004330ec        *(*(esi_1 + 0x7c) + 0x10) = 0x80000
004330f6        *(*(esi_1 + 0x7c) + 0x2c) = 0
004330fc        *(*(esi_1 + 0x7c) + 0x38) = 0
00433102        *(*(esi_1 + 0x7c) + 0x54) = 0
00433108        *(*(esi_1 + 0x7c) + 0x5c) = 0
0043310e        *(*(esi_1 + 0x7c) + 0x64) = 1
0043312c        *(*(esi_1 + 0x7c) + 0xc0) = create_vertex_buffer(&g_direct3d_renderer, manager->max_vertex_counts[i], 0x142)
00433146        *(*(esi_1 + 0x7c) + 0xc8) = create_index_buffer(&g_direct3d_renderer.index_buffer_factory, manager->max_index_counts[i])
0043315b        *(*(esi_1 + 0x7c) + 0xcc) = allocate_tracked_memory(4, "DX TextureGroups")
00433164        char* ecx_6 = *(*(esi_1 + 0x7c) + 0xcc)
0043316a        *ecx_6 = 0
0043316a        ecx_6[1] = 0
0043316a        ecx_6[2] = 0
0043316a        ecx_6[3] = 0
0043317b        *(*(esi_1 + 0x7c) + 0xd0) = allocate_tracked_memory(4, "DX TextureGroupsTexture Ref")
0043318f        *(*(esi_1 + 0x7c) + 0xd4) = allocate_tracked_memory(4, "DX TextureGroupsTexture Primcount")
00433195        if (i == 4)
0043319d        (var_4 - 0x16c)->slots[0][4].bod.object->blend_mode = 5
004331a4        i += 1
004331bf        cond:1_1 = var_8 + 5 s< 0x2cb
004331c4        var_8 += 5
004331c8        var_4 = &var_4[0x4b]
004331cc        do while (cond:1_1)
004331d2        struct ObjectRenderVertex* (* esi_2)[0x5] = &manager->shared_vertex_buffers
004331d5        int32_t i_2 = 5
0043320a        void* result
0043320a        int32_t i_1
004331ee        (esi_2 - 0x2c)->shared_vertex_buffers[0] = allocate_tracked_memory((esi_2 - 0x2c)->max_vertex_counts[0] * 0x18, "GDX Cache Vertex Buffer")
004331fb        result = allocate_tracked_memory((esi_2 - 0x2c)->max_index_counts[0] << 1, "GDX Cache Index Buffer")
00433200        (esi_2 - 0x2c)->shared_index_buffers[0] = result
00433206        esi_2 = &(*esi_2)[1]
00433209        i_1 = i_2
00433209        i_2 -= 1
0043320a        do while (i_1 != 1)
00433213        return result
