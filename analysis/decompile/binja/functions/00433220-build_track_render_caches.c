/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_render_caches @ 0x433220 */

00433239        pack_color_rgba_u8(manager, &skirt_color)
00433240        uint32_t color_1 = 0xffffffff
00433250        int32_t row_index_2 = 0
00433252        int32_t row_index = 0
0043325b        if (manager->owner_subgame->runtime_row_count s> 0)
00433261        void* edi_1 = nullptr
00433270        while (true)
00433271        int32_t temp1_1 = mods.dp.d(sx.q(row_index_2), 0x18)
00433279        int32_t vertex_count
00433279        int32_t vertex_count_1
00433279        int32_t vertex_count_2
00433279        int32_t vertex_count_3
00433279        int32_t vertex_count_4
00433279        int32_t index_count
00433279        int32_t index_count_1
00433279        int32_t index_count_2
00433279        int32_t index_count_3
00433279        int32_t index_count_4
00433279        int32_t esi_1
00433279        int32_t var_40
00433279        if (temp1_1 != 0)
004332f3        esi_1 = var_40
0043328c        esi_1 = row_index_2 s/ 0x18
00433290        var_40 = esi_1
00433294        index_count = 0
0043329b        index_count_1 = 0
004332a6        index_count_2 = 0
004332aa        index_count_3 = 0
004332b1        index_count_4 = 0
004332bb        int32_t* eax_9 = &(&manager->slots[0][0].cache_row_base)[esi_1 * 0x4b]
004332c4        vertex_count = 0
004332c8        vertex_count_1 = 0
004332cc        manager->build_cache_row_base = fconvert.s(float.t(var_40) * fconvert.t(24f))
004332d2        vertex_count_2 = 0
004332d6        vertex_count_3 = 0
004332da        vertex_count_4 = 0
004332de        int32_t i_3 = 5
004332ef        int32_t i
004332e9        *eax_9 = manager->build_cache_row_base
004332eb        eax_9 = &eax_9[0xf]
004332ee        i = i_3
004332ee        i_3 -= 1
004332ef        do while (i != 1)
004332f7        int32_t var_3c_1 = 8
004335f4        bool cond:4_1
004332ff        void* ebp_1 = edi_1 + 0x3bfb0c
00433305        int32_t var_44_1 = 4
0043338b        bool cond:2_1
0043330d        struct SubgameRuntime* owner_subgame = manager->owner_subgame
00433310        void* edx_7 = *(owner_subgame + ebp_1)
00433315        if (edx_7 != 0)
00433317        struct tColourSmall color_2
00433317        color_2.b = manager->skirt_color_bgra.b
00433317        color_2.g = manager->skirt_color_bgra.g
00433317        color_2.r = manager->skirt_color_bgra.r
00433317        color_2.a = manager->skirt_color_bgra.a
00433349        append_track_cache_object(manager, row_index, *(edx_7 + 0x24), &owner_subgame->runtime_cells[0][0].anchor_position + edi_1, manager->shared_vertex_buffers[4], &vertex_count_4, manager->shared_index_buffers[4], &index_count_4, manager->max_vertex_counts[4], manager->max_index_counts[4], color_2, 0)
00433373        *(&manager->slots[0][4].bod.object)[esi_1 * 0x4b]->group_texture_refs = *(*(*(*(manager->owner_subgame + ebp_1) + 0x24) + 0x5c) + 0xc)
00433378        *(manager->owner_subgame + ebp_1) = 0
00433383        ebp_1 += 4
00433386        cond:2_1 = var_44_1 != 1
00433387        var_44_1 -= 1
0043338b        do while (cond:2_1)
0043338d        struct SubgameRuntime* owner_subgame_2 = manager->owner_subgame
00433390        int32_t ecx_13 = *(&owner_subgame_2->runtime_cells[0][0].lane_and_flags + edi_1)
00433397        void* eax_18 = edi_1 + owner_subgame_2
004333ab        void* eax_23
004333ab        void* ecx_21
004333ab        if ((ecx_13.b & 0x20) == 0 || (ecx_13 & 0x4000) != 0x4000)
00433410        char eax_24 = is_sub_loc_floor(eax_18 + 0x3bfac8)
00433417        void* eax_25
00433417        int32_t ebp_2
00433417        if (eax_24 != 0)
0043341d        struct SubgameRuntime* owner_subgame_3 = manager->owner_subgame
00433420        ebp_2 = *(&owner_subgame_3->runtime_cells[0][0].lane_and_flags + edi_1)
00433427        eax_25 = edi_1 + owner_subgame_3
00433438        uint32_t color
00433438        if (eax_24 != 0 && (ebp_2 & 0x4000) == 0x4000)
00433443        int32_t var_60_1 = 1
00433448        color = color_1
00433449        if ((ebp_2.b & 0x40) != 0x40)
0043351b        label_43351b:
0043351b        append_track_cache_object(manager, row_index, *(eax_25 + 0x3bfaec), eax_25 + 0x3bfad8, manager->shared_vertex_buffers[0], &vertex_count, manager->shared_index_buffers[0], &index_count, manager->max_vertex_counts[0], manager->max_index_counts[0], color, 1)
0043352a        ecx_21 = *(*(&manager->owner_subgame->runtime_cells[0][0].object + edi_1) + 0x5c)
00433536        eax_23 = (&manager->slots[0][0].bod.object)[esi_1 * 0x4b]
0043353a        goto label_4335d0
0043347e        label_43347e:
0043347e        append_track_cache_object(manager, row_index, *(eax_25 + 0x3bfaec), eax_25 + 0x3bfad8, manager->shared_vertex_buffers[1], &vertex_count_1, manager->shared_index_buffers[1], &index_count_1, manager->max_vertex_counts[1], manager->max_index_counts[1], color, 1)
0043348d        ecx_21 = *(*(&manager->owner_subgame->runtime_cells[0][0].object + edi_1) + 0x5c)
00433499        eax_23 = (&manager->slots[0][1].bod.object)[esi_1 * 0x4b]
004334a0        goto label_4335d0
004334af        char eax_30 = is_sub_loc_slide(&manager->owner_subgame->runtime_cells + edi_1)
004334b6        int32_t ebp_3
004334b6        if (eax_30 != 0)
004334bf        eax_25 = manager->owner_subgame + edi_1
004334c1        ebp_3 = *(eax_25 + 0x3bfb08)
004334d5        if (eax_30 != 0 && (ebp_3 & 0x4000) == 0x4000)
004334e0        int32_t var_60_2 = 1
004334e5        color = color_1
004334e6        if ((ebp_3.b & 0x40) != 0x40)
004334e6        goto label_43347e
004334e6        goto label_43351b
00433550        if (is_sub_loc_ramp(&manager->owner_subgame->runtime_cells + edi_1) != 0)
00433559        void* eax_38 = manager->owner_subgame + edi_1
0043356d        if ((*(eax_38 + 0x3bfb08) & 0x4000) == 0x4000)
004335a5        append_track_cache_object(manager, row_index, *(eax_38 + 0x3bfaec), eax_38 + 0x3bfad8, manager->shared_vertex_buffers[3], &vertex_count_3, manager->shared_index_buffers[3], &index_count_3, manager->max_vertex_counts[3], manager->max_index_counts[3], color_1, 0)
004335ba        ecx_21 = *(*(&manager->owner_subgame->runtime_cells[0][0].object + edi_1) + 0x5c)
004335c0        eax_23 = (&manager->slots[0][3].bod.object)[esi_1 * 0x4b]
004335c0        goto label_4335d0
004333e3        append_track_cache_object(manager, row_index, *(eax_18 + 0x3bfaec), eax_18 + 0x3bfad8, manager->shared_vertex_buffers[2], &vertex_count_2, manager->shared_index_buffers[2], &index_count_2, manager->max_vertex_counts[2], manager->max_index_counts[2], color_1, 1)
004333f2        ecx_21 = *(*(&manager->owner_subgame->runtime_cells[0][0].object + edi_1) + 0x5c)
004333fe        eax_23 = (&manager->slots[0][2].bod.object)[esi_1 * 0x4b]
004335d0        label_4335d0:
004335d0        **(eax_23 + 0xd0) = *(ecx_21 + 0xc)
004335d2        struct SubgameRuntime* owner_subgame_1 = manager->owner_subgame
004335dc        int32_t ecx_47 = *(&owner_subgame_1->runtime_cells[0][0].lane_and_flags + edi_1)
004335e3        ecx_47:1.b &= 0xbf
004335e6        *(&owner_subgame_1->runtime_cells[0][0].lane_and_flags + edi_1) = ecx_47
004335ec        edi_1 += 0x54
004335ef        cond:4_1 = var_3c_1 != 1
004335f0        var_3c_1 -= 1
004335f4        do while (cond:4_1)
00433614        if (temp1_1 == 0x17 || row_index == manager->owner_subgame->runtime_row_count - 1)
0043361d        int32_t (* edi_2)[0x5] = &manager->max_vertex_counts
00433620        int32_t (* var_44_2)[0x5] = edi_2
00433624        int32_t var_3c_2 = 0
00433632        int32_t* ebp_4 = &(&manager->slots[0][0].bod.object)[esi_1 * 0x4b]
00433646        while (true)
0043364e        int32_t* eax_51 = *(*(*ebp_4 + 0xc0) + 8)
0043365d        int32_t var_34
0043365d        (*(*eax_51 + 0x2c))(eax_51, 0, (edi_2 - 4)->max_vertex_counts[0] * 0x18, &var_34, 0)
00433673        int32_t* eax_53 = **(*ebp_4 + 0xc8)
0043367d        int32_t var_30
0043367d        (*(*eax_53 + 0x2c))(eax_53, 0, (edi_2 - 4)->max_index_counts[0] << 1, &var_30, 0)
0043368c        int32_t ecx_55 = (edi_2 - 4)->max_vertex_counts[0] * 0x18
00433694        int32_t esi_4
00433694        int32_t edi_4
00433694        edi_4, esi_4 = __builtin_memcpy(var_34, (edi_2 - 4)->shared_vertex_buffers[0], ecx_55 & 0xfffffffc)
0043369f        __builtin_memcpy(edi_4, esi_4, ecx_55 & 3)
004336ab        int32_t ecx_60 = (var_44_2 - 4)->max_index_counts[0] << 1
004336b2        int32_t esi_6
004336b2        int32_t edi_6
004336b2        edi_6, esi_6 = __builtin_memcpy(var_30, (var_44_2 - 4)->shared_index_buffers[0], ecx_60 & 0xfffffffc)
004336b9        __builtin_memcpy(edi_6, esi_6, ecx_60 & 3)
004336c4        int32_t* eax_58 = *(*(*ebp_4 + 0xc0) + 8)
004336ca        (*(*eax_58 + 0x30))(eax_58)
004336d0        char* ecx_65 = *(*ebp_4 + 0xc8)
004336d6        int32_t* eax_60
004336d6        eax_60.b = *ecx_65
004336d6        eax_60:1.b = ecx_65[1]
004336d6        eax_60:2.b = ecx_65[2]
004336d6        eax_60:3.b = ecx_65[3]
004336db        (*(*eax_60 + 0x30))(eax_60)
004336e2        void* eax_61 = *ebp_4
004336e9        ebp_4 = &ebp_4[0xf]
004336f0        *(eax_61 + 0xc4) = *(&vertex_count + var_3c_2)
004336ff        int32_t eax_62
004336ff        int32_t edx_49
004336ff        edx_49:eax_62 = muls.dp.d(0x55555556, *(&index_count + var_3c_2))
00433714        var_44_2 = &(*var_44_2)[1]
00433718        **(ebp_4[-0xf] + 0xd4) = edx_49 + (edx_49 u>> 0x1f)
00433721        *(ebp_4[-0xf] + 0x2c) = *(&vertex_count + var_3c_2)
00433727        bool cond:6_1 = var_3c_2 + 4 s< 0x14
0043372a        var_3c_2 += 4
0043372e        if (not(cond:6_1))
0043372e        break
00433638        edi_2 = var_44_2
0043373f        int32_t row_index_1 = row_index + 1
00433743        row_index = row_index_1
00433749        if (row_index_1 s>= manager->owner_subgame->runtime_row_count)
00433749        break
00433265        row_index_2 = row_index
0043374f        int32_t i_1 = 0
00433751        manager->next_cache_row_z = 0f
00433757        manager->next_cache_row_index = 0
0043375d        int32_t i_2 = 0
00433769        int32_t edi_7 = 0
0043376b        int32_t ebp_5 = 0
00433770        int32_t eax_69
00433770        int32_t edx_54
00433770        edx_54:eax_69 = muls.dp.d(0x2aaaaaab, manager->owner_subgame->runtime_row_count)
00433772        int32_t edx_55 = edx_54 s>> 2
0043377a        int32_t j_1 = edx_55 + (edx_55 u>> 0x1f)
0043377e        if (j_1 s> 0)
00433786        int32_t* esi_9 = &(&manager->slots[0][0].bod.object)[i_1 * 0xf]
004337ad        int32_t j
0043378a        void* eax_73 = *esi_9
0043378c        int32_t ecx_71 = *(eax_73 + 0x2c)
00433791        if (ecx_71 s> edi_7)
00433793        edi_7 = ecx_71
0043379d        int32_t eax_76 = **(eax_73 + 0xd4) << 2
004337a2        if (eax_76 s> ebp_5)
004337a4        ebp_5 = eax_76
004337a6        esi_9 = &esi_9[0x4b]
004337ac        j = j_1
004337ac        j_1 -= 1
004337ad        do while (j != 1)
004337af        i_1 = i_2
004337b8        switch (i_1)
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
00433803        i_1 += 1
00433807        i_2 = i_1
0043380b        do while (i_1 s< 5)
00433818        return
