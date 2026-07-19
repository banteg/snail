/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_track_render_cache_manager @ 0x433060 */

00433070        __builtin_memcpy(&manager->max_vertex_counts, "\x30\x02\x00\x00\x30\x02\x00\x00\xa0\x00\x00\x00\x50\x00\x00\x00\x20\x03\x00\x00\x00\x05\x00\x00\x00\x05\x00\x00\xf0\x00\x00\x00\xa0\x00\x00\x00\x00\x05\x00\x00", 0x28)
004330b4        manager->owner_subgame = &g_game_base->subgame
004330b7        int32_t slot_base = 0
004330bb        struct Object** skirt_object_ref = &manager->slots[0][4].bod.object
004331cc        bool cond:1_1
004330bf        int32_t family_index = 0
004331a8        while (family_index s< 5)
004330d3        struct TrackRenderCacheSlotCursor* slot_cursor = manager + (slot_base + family_index) * 0x3c
004330df        set_bod_object(&slot_cursor->slot.bod, add_object_to_list(&g_object_list))
004330ec        slot_cursor->slot.bod.object->flags = OBJECT_FLAG_RENDER_BUFFERS_READY
004330f6        slot_cursor->slot.bod.object->vertex_count = 0
004330fc        slot_cursor->slot.bod.object->vertices = nullptr
00433102        slot_cursor->slot.bod.object->facequad_count = 0
00433108        slot_cursor->slot.bod.object->facequads = nullptr
0043310e        slot_cursor->slot.bod.object->texture_group_count = 1
0043312c        slot_cursor->slot.bod.object->render_buffers = create_vertex_buffer(&g_direct3d_renderer, manager->max_vertex_counts[family_index], 0x142)
00433146        slot_cursor->slot.bod.object->index_buffer = create_index_buffer(&g_direct3d_renderer.index_buffer_factory, manager->max_index_counts[family_index])
0043315b        slot_cursor->slot.bod.object->group_index_starts = allocate_tracked_memory(4, "DX TextureGroups")
00433164        uint8_t* group_index_zero_bytes = slot_cursor->slot.bod.object->group_index_starts
0043316a        *group_index_zero_bytes = 0
0043316a        group_index_zero_bytes[1] = 0
0043316a        group_index_zero_bytes[2] = 0
0043316a        group_index_zero_bytes[3] = 0
0043317b        slot_cursor->slot.bod.object->group_texture_refs = allocate_tracked_memory(4, "DX TextureGroupsTexture Ref")
0043318f        slot_cursor->slot.bod.object->group_primitive_counts = allocate_tracked_memory(4, "DX TextureGroupsTexture Primcount")
00433195        if (family_index == 4)
0043319d        (*skirt_object_ref)->blend_mode = 5
004331a4        family_index += 1
004331bf        cond:1_1 = slot_base + 5 s< 0x2cb
004331c4        slot_base += 5
004331c8        skirt_object_ref = &skirt_object_ref[0x4b]
004331cc        do while (cond:1_1)
004331d2        struct ObjectRenderVertex* (* esi_1)[0x5] = &manager->shared_vertex_buffers
004331d5        int32_t shared_buffers_remaining = 5
0043320a        int32_t i
004331ee        (esi_1 - 0x2c)->shared_vertex_buffers[0] = allocate_tracked_memory((esi_1 - 0x2c)->max_vertex_counts[0] * 0x18, "GDX Cache Vertex Buffer")
00433200        (esi_1 - 0x2c)->shared_index_buffers[0] = allocate_tracked_memory((esi_1 - 0x2c)->max_index_counts[0] << 1, "GDX Cache Index Buffer")
00433206        esi_1 = &(*esi_1)[1]
00433209        i = shared_buffers_remaining
00433209        shared_buffers_remaining -= 1
0043320a        do while (i != 1)
00433213        return
