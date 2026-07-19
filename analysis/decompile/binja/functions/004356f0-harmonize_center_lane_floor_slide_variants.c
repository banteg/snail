/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: harmonize_center_lane_floor_slide_variants @ 0x4356f0 */

004356f4        struct SubgameRuntime* game_1 = game
004356f6        int32_t i = 0
004356f8        struct SubgameRuntime* game_2 = game_1
004356ff        int32_t i_1 = 0
00435706        if (game_1->runtime_row_count - 1 s<= 0)
00435706        return
00435716        int32_t ecx_2 = 0
00435718        int32_t edx_2 = i & 7
0043571b        int32_t var_c_1 = 0
0043571f        int32_t var_4_1 = edx_2
00435734        while (true)
00435734        if (edx_2 == 3)
00435746        int32_t edx_3 = (ecx_2 + (i << 3)) * 0x15
00435752        struct RuntimeCellStrideAnchor* forward_cell_anchor = game_1 + (edx_3 << 2)
00435755        if (((&game_1->runtime_cells[0][0].lane_and_flags)[edx_3].b & 0x20) == 0)
00435762        if ((forward_cell_anchor->next_row_same_lane.lane_and_flags.b & 0x20) == 0 && is_sub_loc_floor(&forward_cell_anchor->cell) == 1 && (is_sub_loc_slide(&forward_cell_anchor->next_row_same_lane) == 1 || forward_cell_anchor->next_row_same_lane.tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE))
00435795        struct GameRoot* game_base_1 = g_game_base
004357a6        if (forward_cell_anchor->cell.object == game_base_1->root_bod_catalog.floor_slices.storage[0].object)
004357b1        set_bod_object(&forward_cell_anchor->cell, game_base_1->root_bod_catalog.slide_slices.storage[0].object)
004357be        forward_cell_anchor->cell.lane_and_flags |= 0x40
004357c4        game_base_1 = g_game_base
004357c9        int32_t j = 0
00435807        while (j s< 0xe0)
004357da        if (forward_cell_anchor->cell.object == *(&game_base_1->root_bod_catalog.floor_corners.storage[0].object + j))
004357e6        set_bod_object(&forward_cell_anchor->cell, *(&game_base_1->root_bod_catalog.slide_corners.storage[0].object + j))
004357f3        forward_cell_anchor->cell.lane_and_flags |= 0x40
004357f9        game_base_1 = g_game_base
004357fe        j += 0x38
0043581d        if ((forward_cell_anchor->cell.lane_and_flags.b & 0x20) == 0 && (forward_cell_anchor->next_row_same_lane.lane_and_flags.b & 0x20) == 0 && is_sub_loc_slide(&forward_cell_anchor->cell) == 1 && is_sub_loc_floor(&forward_cell_anchor->next_row_same_lane) == 1)
0043584b        struct GameRoot* game_base_2 = g_game_base
0043585c        if (forward_cell_anchor->cell.object == game_base_2->root_bod_catalog.slide_slices.storage[0].object)
00435867        set_bod_object(&forward_cell_anchor->cell, game_base_2->root_bod_catalog.floor_slices.storage[0].object)
00435874        forward_cell_anchor->cell.lane_and_flags |= 0x40
0043587a        game_base_2 = g_game_base
0043587f        int32_t j_1 = 0
004358bd        while (j_1 s< 0xe0)
00435890        if (forward_cell_anchor->cell.object == *(&game_base_2->root_bod_catalog.slide_corners.storage[0].object + j_1))
0043589c        set_bod_object(&forward_cell_anchor->cell, *(&game_base_2->root_bod_catalog.floor_corners.storage[0].object + j_1))
004358a9        forward_cell_anchor->cell.lane_and_flags |= 0x40
004358af        game_base_2 = g_game_base
004358b4        j_1 += 0x38
004358c7        if (edx_2 == 5)
004358dc        struct RuntimeCellStrideAnchor* backward_cell_anchor = game_1 + (ecx_2 + (i << 3)) * 0x54
004358e6        if ((backward_cell_anchor->cell.lane_and_flags.b & 0x20) == 0)
004358f3        if ((backward_cell_anchor->previous_row_same_lane.lane_and_flags.b & 0x20) == 0 && is_sub_loc_floor(&backward_cell_anchor->cell) == 1 && (is_sub_loc_slide(&backward_cell_anchor->previous_row_same_lane) == 1 || backward_cell_anchor->previous_row_same_lane.tile_id == SUBLOC_TILE_FLOOR_HASH_MARKER))
00435926        struct GameRoot* game_base_3 = g_game_base
00435937        if (backward_cell_anchor->cell.object == game_base_3->root_bod_catalog.floor_slices.storage[0].object)
00435942        set_bod_object(&backward_cell_anchor->cell, game_base_3->root_bod_catalog.slide_slices.storage[0].object)
0043594f        backward_cell_anchor->cell.lane_and_flags |= 0x40
00435955        game_base_3 = g_game_base
0043595a        int32_t j_2 = 0
00435998        while (j_2 s< 0xe0)
0043596b        if (backward_cell_anchor->cell.object == *(&game_base_3->root_bod_catalog.floor_corners.storage[0].object + j_2))
00435977        set_bod_object(&backward_cell_anchor->cell, *(&game_base_3->root_bod_catalog.slide_corners.storage[0].object + j_2))
00435984        backward_cell_anchor->cell.lane_and_flags |= 0x40
0043598a        game_base_3 = g_game_base
0043598f        j_2 += 0x38
004359ae        if ((backward_cell_anchor->cell.lane_and_flags.b & 0x20) == 0 && (backward_cell_anchor->previous_row_same_lane.lane_and_flags.b & 0x20) == 0 && is_sub_loc_slide(&backward_cell_anchor->cell) == 1 && is_sub_loc_floor(&backward_cell_anchor->previous_row_same_lane) == 1)
004359d8        struct GameRoot* game_base_4 = g_game_base
004359e9        if (backward_cell_anchor->cell.object == game_base_4->root_bod_catalog.slide_slices.storage[0].object)
004359f4        set_bod_object(&backward_cell_anchor->cell, game_base_4->root_bod_catalog.floor_slices.storage[0].object)
00435a01        backward_cell_anchor->cell.lane_and_flags |= 0x40
00435a07        game_base_4 = g_game_base
00435a0c        int32_t j_3 = 0
00435a4a        while (j_3 s< 0xe0)
00435a1d        if (backward_cell_anchor->cell.object == *(&game_base_4->root_bod_catalog.slide_corners.storage[0].object + j_3))
00435a29        set_bod_object(&backward_cell_anchor->cell, *(&game_base_4->root_bod_catalog.floor_corners.storage[0].object + j_3))
00435a36        backward_cell_anchor->cell.lane_and_flags |= 0x40
00435a3c        game_base_4 = g_game_base
00435a41        j_3 += 0x38
00435a50        ecx_2 = var_c_1 + 1
00435a54        var_c_1 = ecx_2
00435a58        if (ecx_2 s>= 8)
00435a58        break
00435725        edx_2 = var_4_1
00435729        game_1 = game_2
0043572d        i = i_1
00435a5e        game_1 = game_2
00435a66        i = i_1 + 1
00435a6a        i_1 = i
00435a71        do while (i s< game_1->runtime_row_count - 1)
00435a7e        return
