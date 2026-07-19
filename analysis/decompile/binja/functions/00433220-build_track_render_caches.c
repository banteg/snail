/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_render_caches @ 0x433220 */

00433239        pack_color_rgba_u8(manager, &skirt_color)
00433240        uint32_t color_1 = 0xffffffff
00433250        int32_t row_index_2 = 0
00433252        int32_t row_index = 0
0043325b        if (manager->owner_subgame->runtime_row_count s> 0)
00433261        int32_t cell_byte_offset = 0
00433270        while (true)
00433271        int32_t temp1_1 = mods.dp.d(sx.q(row_index_2), 0x18)
00433279        int32_t vertex_count_1
00433279        int32_t vertex_count_2
00433279        int32_t vertex_count_3
00433279        int32_t vertex_count_4
00433279        int32_t vertex_count_5
00433279        int32_t index_count
00433279        int32_t index_count_1
00433279        int32_t index_count_2
00433279        int32_t index_count_3
00433279        int32_t index_count_4
00433279        int32_t cache_row_index
00433279        int32_t cache_row_index_saved
00433279        if (temp1_1 != 0)
004332f3        cache_row_index = cache_row_index_saved
0043328c        cache_row_index = row_index_2 s/ 0x18
00433290        cache_row_index_saved = cache_row_index
00433294        index_count = 0
0043329b        index_count_1 = 0
004332a6        index_count_2 = 0
004332aa        index_count_3 = 0
004332b1        index_count_4 = 0
004332bb        int32_t* eax_9 = &(&manager->slots[0][0].cache_row_base)[cache_row_index * 0x4b]
004332c4        vertex_count_1 = 0
004332c8        vertex_count_2 = 0
004332cc        manager->build_cache_row_base = fconvert.s(float.t(cache_row_index_saved) * fconvert.t(24f))
004332d2        vertex_count_3 = 0
004332d6        vertex_count_4 = 0
004332da        vertex_count_5 = 0
004332de        int32_t i_1 = 5
004332ef        int32_t i
004332e9        *eax_9 = manager->build_cache_row_base
004332eb        eax_9 = &eax_9[0xf]
004332ee        i = i_1
004332ee        i_1 -= 1
004332ef        do while (i != 1)
004332f7        int32_t var_3c_1 = 8
004335f4        bool cond:4_1
004332ff        int32_t fringe_byte_offset = cell_byte_offset + 0x3bfb0c
00433305        int32_t var_44_1 = 4
0043338b        bool cond:2_1
0043330d        struct SubgameRuntime* owner_subgame = manager->owner_subgame
00433310        struct Fringe* fringe_object = *(owner_subgame + fringe_byte_offset)
00433315        if (fringe_object != 0)
00433317        struct tColourSmall color_2
00433317        color_2.b = manager->skirt_color_bgra.b
00433317        color_2.g = manager->skirt_color_bgra.g
00433317        color_2.r = manager->skirt_color_bgra.r
00433317        color_2.a = manager->skirt_color_bgra.a
00433349        append_track_cache_object(manager, row_index, fringe_object->bod.object, &owner_subgame->runtime_cells[0][0].anchor_position + cell_byte_offset, manager->shared_vertex_buffers[4], &vertex_count_5, manager->shared_index_buffers[4], &index_count_4, manager->max_vertex_counts[4], manager->max_index_counts[4], color_2, 0)
00433373        *(&manager->slots[0][4].bod.object)[cache_row_index * 0x4b]->group_texture_refs = *(*(*(*(manager->owner_subgame + fringe_byte_offset) + 0x24) + 0x5c) + 0xc)
00433378        *(manager->owner_subgame + fringe_byte_offset) = 0
00433383        fringe_byte_offset += 4
00433386        cond:2_1 = var_44_1 != 1
00433387        var_44_1 -= 1
0043338b        do while (cond:2_1)
0043338d        struct SubgameRuntime* owner_subgame_2 = manager->owner_subgame
00433390        uint32_t cell_flags = *(&owner_subgame_2->runtime_cells[0][0].lane_and_flags + cell_byte_offset)
00433397        uint8_t* warning_cell_base = cell_byte_offset + owner_subgame_2
004333ab        struct Object* cache_object
004333ab        struct ObjectFaceQuad* source_facequads
004333ab        if ((cell_flags.b & 0x20) == 0 || (cell_flags & 0x4000) != 0x4000)
00433410        char eax_22 = is_sub_loc_floor(&warning_cell_base[0x3bfac8])
00433417        uint8_t* floor_or_slide_cell_base
00433417        uint32_t floor_cell_flags
00433417        if (eax_22 != 0)
0043341d        struct SubgameRuntime* owner_subgame_3 = manager->owner_subgame
00433420        floor_cell_flags = *(&owner_subgame_3->runtime_cells[0][0].lane_and_flags + cell_byte_offset)
00433427        floor_or_slide_cell_base = cell_byte_offset + owner_subgame_3
00433438        uint32_t color
00433438        if (eax_22 != 0 && (floor_cell_flags & 0x4000) == 0x4000)
00433443        int32_t var_60_1 = 1
00433448        color = color_1
00433449        if ((floor_cell_flags.b & 0x40) != 0x40)
0043351b        label_43351b:
0043351b        append_track_cache_object(manager, row_index, *(floor_or_slide_cell_base + 0x3bfaec), &floor_or_slide_cell_base[0x3bfad8], manager->shared_vertex_buffers[0], &vertex_count_1, manager->shared_index_buffers[0], &index_count, manager->max_vertex_counts[0], manager->max_index_counts[0], color, 1)
0043352a        source_facequads = *(*(&manager->owner_subgame->runtime_cells[0][0].object + cell_byte_offset) + 0x5c)
00433536        cache_object = (&manager->slots[0][0].bod.object)[cache_row_index * 0x4b]
0043353a        goto label_4335d0
0043347e        label_43347e:
0043347e        append_track_cache_object(manager, row_index, *(floor_or_slide_cell_base + 0x3bfaec), &floor_or_slide_cell_base[0x3bfad8], manager->shared_vertex_buffers[1], &vertex_count_2, manager->shared_index_buffers[1], &index_count_1, manager->max_vertex_counts[1], manager->max_index_counts[1], color, 1)
0043348d        source_facequads = *(*(&manager->owner_subgame->runtime_cells[0][0].object + cell_byte_offset) + 0x5c)
00433499        cache_object = (&manager->slots[0][1].bod.object)[cache_row_index * 0x4b]
004334a0        goto label_4335d0
004334af        char eax_27 = is_sub_loc_slide(&manager->owner_subgame->runtime_cells + cell_byte_offset)
004334b6        uint32_t slide_cell_flags
004334b6        if (eax_27 != 0)
004334bf        floor_or_slide_cell_base = manager->owner_subgame + cell_byte_offset
004334c1        slide_cell_flags = *(floor_or_slide_cell_base + 0x3bfb08)
004334d5        if (eax_27 != 0 && (slide_cell_flags & 0x4000) == 0x4000)
004334e0        int32_t var_60_2 = 1
004334e5        color = color_1
004334e6        if ((slide_cell_flags.b & 0x40) != 0x40)
004334e6        goto label_43347e
004334e6        goto label_43351b
00433550        if (is_sub_loc_ramp(&manager->owner_subgame->runtime_cells + cell_byte_offset) != 0)
00433559        uint8_t* ramp_cell_base = manager->owner_subgame + cell_byte_offset
0043356d        if ((*(ramp_cell_base + 0x3bfb08) & 0x4000) == 0x4000)
004335a5        append_track_cache_object(manager, row_index, *(ramp_cell_base + 0x3bfaec), &ramp_cell_base[0x3bfad8], manager->shared_vertex_buffers[3], &vertex_count_4, manager->shared_index_buffers[3], &index_count_3, manager->max_vertex_counts[3], manager->max_index_counts[3], color_1, 0)
004335ba        source_facequads = *(*(&manager->owner_subgame->runtime_cells[0][0].object + cell_byte_offset) + 0x5c)
004335c0        cache_object = (&manager->slots[0][3].bod.object)[cache_row_index * 0x4b]
004335c0        goto label_4335d0
004333e3        append_track_cache_object(manager, row_index, *(warning_cell_base + 0x3bfaec), &warning_cell_base[0x3bfad8], manager->shared_vertex_buffers[2], &vertex_count_3, manager->shared_index_buffers[2], &index_count_2, manager->max_vertex_counts[2], manager->max_index_counts[2], color_1, 1)
004333f2        source_facequads = *(*(&manager->owner_subgame->runtime_cells[0][0].object + cell_byte_offset) + 0x5c)
004333fe        cache_object = (&manager->slots[0][2].bod.object)[cache_row_index * 0x4b]
004335d0        label_4335d0:
004335d0        *cache_object->group_texture_refs = source_facequads->texture_ref
004335d2        struct SubgameRuntime* owner_subgame_1 = manager->owner_subgame
004335dc        uint32_t updated_cell_flags = *(&owner_subgame_1->runtime_cells[0][0].lane_and_flags + cell_byte_offset)
004335e3        updated_cell_flags:1.b &= 0xbf
004335e6        *(&owner_subgame_1->runtime_cells[0][0].lane_and_flags + cell_byte_offset) = updated_cell_flags
004335ec        cell_byte_offset += 0x54
004335ef        cond:4_1 = var_3c_1 != 1
004335f0        var_3c_1 -= 1
004335f4        do while (cond:4_1)
00433614        if (temp1_1 == 0x17 || row_index == manager->owner_subgame->runtime_row_count - 1)
0043361d        int32_t* max_vertex_count_cursor = &manager->max_vertex_counts
00433620        int32_t* family_staging_cursor = max_vertex_count_cursor
00433624        int32_t family_count_byte_offset = 0
00433632        struct Object** cache_object_ref = &(&manager->slots[0][0].bod.object)[cache_row_index * 0x4b]
00433646        while (true)
0043364e        struct ObjectVertexBuffer* vertex_buffer = (*cache_object_ref)->render_buffers->vertex_buffer
0043365d        void* locked_vertices
0043365d        vertex_buffer->vtbl->Lock(vertex_buffer, 0, *max_vertex_count_cursor * 0x18, &locked_vertices, 0)
00433673        struct ObjectIndexBufferResource* index_buffer = (*cache_object_ref)->index_buffer->buffer
0043367d        void* locked_indices
0043367d        index_buffer->vtbl->Lock(index_buffer, 0, max_vertex_count_cursor[5] << 1, &locked_indices, 0)
0043368c        int32_t ecx_52 = *max_vertex_count_cursor * 0x18
00433694        int32_t esi_3
00433694        int32_t edi_2
00433694        edi_2, esi_3 = __builtin_memcpy(locked_vertices, max_vertex_count_cursor[0xa], ecx_52 & 0xfffffffc)
0043369f        __builtin_memcpy(edi_2, esi_3, ecx_52 & 3)
004336ab        int32_t ecx_57 = family_staging_cursor[5] << 1
004336b2        int32_t esi_5
004336b2        int32_t edi_4
004336b2        edi_4, esi_5 = __builtin_memcpy(locked_indices, family_staging_cursor[0xf], ecx_57 & 0xfffffffc)
004336b9        __builtin_memcpy(edi_4, esi_5, ecx_57 & 3)
004336c4        struct ObjectVertexBuffer* vertex_buffer_1 = (*cache_object_ref)->render_buffers->vertex_buffer
004336ca        vertex_buffer_1->vtbl->Unlock(vertex_buffer_1)
004336d0        struct ObjectIndexBuffer* index_buffer_1 = (*cache_object_ref)->index_buffer
004336d6        struct ObjectIndexBufferResource* index_buffer_unlock
004336d6        index_buffer_unlock.b = index_buffer_1->buffer.b
004336d6        index_buffer_unlock:1.b = index_buffer_1->buffer:1.b
004336d6        index_buffer_unlock:2.b = index_buffer_1->buffer:2.b
004336d6        index_buffer_unlock:3.b = index_buffer_1->buffer:3.b
004336db        index_buffer_unlock->vtbl->Unlock(index_buffer_unlock)
004336e2        struct Object* flushed_object = *cache_object_ref
004336e9        cache_object_ref = &cache_object_ref[0xf]
004336f0        flushed_object->grouped_vertex_count = *(&vertex_count_1 + family_count_byte_offset)
004336ff        int32_t eax_53
004336ff        int32_t edx_48
004336ff        edx_48:eax_53 = muls.dp.d(0x55555556, *(&index_count + family_count_byte_offset))
00433714        family_staging_cursor = &family_staging_cursor[1]
00433718        *cache_object_ref[-0xf]->group_primitive_counts = edx_48 + (edx_48 u>> 0x1f)
00433721        cache_object_ref[-0xf]->vertex_count = *(&vertex_count_1 + family_count_byte_offset)
00433727        bool cond:6_1 = family_count_byte_offset + 4 s< 0x14
0043372a        family_count_byte_offset += 4
0043372e        if (not(cond:6_1))
0043372e        break
00433638        max_vertex_count_cursor = family_staging_cursor
0043373f        int32_t row_index_1 = row_index + 1
00433743        row_index = row_index_1
00433749        if (row_index_1 s>= manager->owner_subgame->runtime_row_count)
00433749        break
00433265        row_index_2 = row_index
0043374f        int32_t family_index = 0
00433751        manager->next_cache_row_z = 0f
00433757        manager->next_cache_row_index = 0
0043375d        int32_t family_index_saved = 0
00433769        int32_t max_vertices_seen = 0
0043376b        int32_t max_indices_seen = 0
00433770        int32_t eax_60
00433770        int32_t edx_53
00433770        edx_53:eax_60 = muls.dp.d(0x2aaaaaab, manager->owner_subgame->runtime_row_count)
00433772        int32_t edx_54 = edx_53 s>> 2
0043377a        int32_t cache_rows_remaining = edx_54 + (edx_54 u>> 0x1f)
0043377e        if (cache_rows_remaining s> 0)
00433786        struct Object** max_scan_object_ref = &(&manager->slots[0][0].bod.object)[family_index * 0xf]
004337ad        int32_t j
0043378a        struct Object* max_scan_object = *max_scan_object_ref
0043378c        int32_t vertex_count = max_scan_object->vertex_count
00433791        if (vertex_count s> max_vertices_seen)
00433793        max_vertices_seen = vertex_count
0043379d        int32_t max_indices_seen_1 = *max_scan_object->group_primitive_counts << 2
004337a2        if (max_indices_seen_1 s> max_indices_seen)
004337a4        max_indices_seen = max_indices_seen_1
004337a6        max_scan_object_ref = &max_scan_object_ref[0x4b]
004337ac        j = cache_rows_remaining
004337ac        cache_rows_remaining -= 1
004337ad        do while (j != 1)
004337af        family_index = family_index_saved
004337b8        switch (family_index)
004337bf        case 0
004337bf        row_index = "Floor"
004337c9        case 1
004337c9        row_index = "Slide"
004337d3        case 2
004337d3        row_index = "Warn"
004337dd        case 3
004337dd        row_index = "Ramp"
004337e7        case 4
004337e7        row_index = "Fringe"
00433803        family_index += 1
00433807        family_index_saved = family_index
0043380b        do while (family_index s< 5)
00433818        return
