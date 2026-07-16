/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: merge_track_tile_runs @ 0x435180 */

00435185        struct SubgameRuntime* game_1 = game
00435187        int32_t i = 0
00435189        struct SubgameRuntime* game_2 = game_1
00435192        if (game_1->runtime_row_count s> 0)
00435194        uint32_t* seed_lane_flags = &game_1->runtime_cells[0][0].lane_and_flags
0043519a        int32_t j_1 = 8
004351ae        int32_t j
0043519f        uint32_t ebp_1 = *seed_lane_flags
004351a1        seed_lane_flags = &seed_lane_flags[0x15]
004351aa        j = j_1
004351aa        j_1 -= 1
004351ab        seed_lane_flags[-0x15] = ebp_1 | 0x6000
004351ae        do while (j != 1)
004351b3        i += 1
004351b6        do while (i s< game_1->runtime_row_count)
004351b8        int32_t runtime_row_count = game_1->runtime_row_count
004351bb        int32_t var_10 = 0
004351c5        if (runtime_row_count s> 0)
004351d3        uint32_t* row_attachment_flags = &game_1->runtime_rows[0].attachment_body.bod.list_flags
004351d7        uint32_t* cell_lane_flags = &game_1->runtime_cells[0][0].lane_and_flags
004353d4        bool cond:3_1
004351dd        int32_t i_2 = 0
004351df        int32_t i_6 = 0
004351ee        while (true)
004351ee        char eax_2 = is_sub_loc_floor(&cell_lane_flags[-0x10])
004351f5        uint16_t eax_3
004351f5        if (eax_2 != 0)
004351fb        eax_3 = (*cell_lane_flags).w
00435208        if (eax_2 == 0 || (eax_3:1.b & 0x80) != 0 || (eax_3.b & 0x40) != 0)
004352c9        if (is_sub_loc_slide(&cell_lane_flags[-0x10]).b == 0)
004353e2        label_4353e2:
004353e2        uint8_t eax_18 = cell_lane_flags[-0x10]:0x3c.b
004353e5        uint8_t* wall_tile_cursor = &cell_lane_flags[-1]
004353ea        if (eax_18 == 0xe)
004353f0        uint32_t eax_19 = *cell_lane_flags
004353f2        int32_t esi_4 = 0
004353f4        eax_19:1.b &= 0xf1
004353f7        eax_19:1.b |= 1
004353fd        *cell_lane_flags = eax_19
004353ff        if (i_2 s< 8)
00435401        int32_t i_7 = i_2
00435406        while (*wall_tile_cursor == 0xe)
00435416        if ((eax_19 & 0x4000) != 0x4000)
00435416        break
00435418        eax_19:1.b &= 0xf1
0043541b        wall_tile_cursor = &wall_tile_cursor[0x54]
0043541e        eax_19:1.b |= 1
00435421        esi_4 += 1
00435422        i_7 += 1
00435423        *cell_lane_flags = eax_19
00435428        if (i_7 s>= 8)
00435428        break
0043542d        if (esi_4 s> 1)
0043544d        set_bod_object(&cell_lane_flags[-0x10], g_game_base->root_bod_catalog.unknown_18_21[3 + esi_4].object)
00435452        uint32_t edx_6 = *cell_lane_flags
00435459        edx_6:1.b &= 0xf0
00435461        int32_t i_10 = esi_4 - 1
00435464        *cell_lane_flags = (esi_4 & 0xf) << 8 | edx_6
00435466        if (i_10 s> 0)
00435485        uint32_t* wall_cleanup_lane_flags = &(&game_2->runtime_cells[0][0].lane_and_flags)[(i_10 + (var_10 << 3) + i_2) * 0x15]
004354a5        int32_t i_1
0043548c        int32_t ecx_32 = wall_cleanup_lane_flags[-0xf]
0043548f        wall_cleanup_lane_flags -= 0x54
00435495        wall_cleanup_lane_flags[6] = ecx_32 & 0xffffffdf
004354a1        i_1 = i_10
004354a1        i_10 -= 1
004354a2        wall_cleanup_lane_flags[0x15] &= 0xffff9fff
004354a5        do while (i_1 != 1)
004354b2        if (eax_18 == 0 || eax_18 == 0x23)
004354b8        uint32_t eax_24 = *cell_lane_flags
004354ba        eax_24:1.b &= 0xdf
004354bd        *cell_lane_flags = eax_24
004354c5        if (game_1->level_mode != 2)
004354df        eax_24:1.b &= 0xbf
004354e2        *cell_lane_flags = eax_24
004354d5        set_bod_object(&cell_lane_flags[-0x10], g_game_base->root_bod_catalog.universe_hole.object)
004352cf        uint16_t eax_9 = (*cell_lane_flags).w
004352dc        if ((eax_9:1.b & 0x80) != 0 || (eax_9.b & 0x40) != 0)
004352d4        goto label_4353e2
004352e2        int32_t esi_1 = 0
004352e7        if (i_2 s< 8)
004352ed        uint32_t* slide_lane_flags_cursor = cell_lane_flags
004352f9        if (is_sub_loc_slide(&slide_lane_flags_cursor[-0x10]) == 0)
004352f9        break
004352fb        uint16_t eax_11 = (*slide_lane_flags_cursor).w
00435300        if ((eax_11:1.b & 0x80) != 0)
00435300        break
00435305        if ((eax_11:1.b & 0x40) == 0)
00435305        break
00435309        if ((eax_11.b & 0x60) != 0)
00435309        break
0043530b        esi_1 += 1
0043530c        slide_lane_flags_cursor = &slide_lane_flags_cursor[0x15]
0043530f        i_2 += 1
00435313        do while (i_2 s< 8)
00435318        if (esi_1 s> 1)
00435334        set_bod_object(&cell_lane_flags[-0x10], g_game_base->root_bod_catalog.warning_slices.storage[7 + esi_1].object)
00435339        int32_t i_9 = esi_1 - 1
0043533c        if (i_9 s> 0)
0043535b        uint32_t* slide_cleanup_lane_flags = &(&game_2->runtime_cells[0][0].lane_and_flags)[(i_9 + (var_10 << 3) + i_6) * 0x15]
0043537b        int32_t i_3
00435362        int32_t ebp_3 = slide_cleanup_lane_flags[-0xf]
00435365        slide_cleanup_lane_flags -= 0x54
0043536b        slide_cleanup_lane_flags[6] = ebp_3 & 0xffffffdf
00435377        i_3 = i_9
00435377        i_9 -= 1
00435378        slide_cleanup_lane_flags[0x15] &= 0xffff9fff
0043537b        do while (i_3 != 1)
0043537d        i_2 = i_6
0043520e        int32_t esi = 0
00435213        if (i_2 s< 8)
00435219        int32_t i_4 = i_2
0043521b        uint8_t* floor_tile_cursor = &cell_lane_flags[-1]
0043521e        uint8_t eax_4 = *floor_tile_cursor
00435232        if (eax_4 != 1 && eax_4 != 0x15 && eax_4 != 0x1b && eax_4 != 0x21 && eax_4 != 0x22)
00435232        break
00435234        eax_3 = (*(floor_tile_cursor + 4)).w
0043523a        if ((eax_3:1.b & 0x80) != 0)
0043523a        break
0043523f        if ((eax_3:1.b & 0x40) == 0)
0043523f        break
00435243        if ((eax_3.b & 0x60) != 0)
00435243        break
00435245        esi += 1
00435246        floor_tile_cursor = &floor_tile_cursor[0x54]
00435249        i_4 += 1
0043524d        do while (i_4 s< 8)
00435252        if (esi s> 1)
00435272        set_bod_object(&cell_lane_flags[-0x10], g_game_base->root_bod_catalog.pillars[7 + esi].object)
00435277        int32_t i_8 = esi - 1
0043527a        if (i_8 s> 0)
00435299        uint32_t* floor_cleanup_lane_flags = &(&game_2->runtime_cells[0][0].lane_and_flags)[(i_8 + (var_10 << 3) + i_2) * 0x15]
004352b9        int32_t i_5
004352a0        int32_t ecx_8 = floor_cleanup_lane_flags[-0xf]
004352a3        floor_cleanup_lane_flags -= 0x54
004352a9        floor_cleanup_lane_flags[6] = ecx_8 & 0xffffffdf
004352b5        i_5 = i_8
004352b5        i_8 -= 1
004352b6        floor_cleanup_lane_flags[0x15] &= 0xffff9fff
004352b9        do while (i_5 != 1)
0043538c        if ((row_attachment_flags[-0x2d].b & 4) != 0)
00435397        cell_lane_flags[-0xf] &= 0xfffffddd
0043539a        uint32_t edx_4 = *cell_lane_flags
0043539c        edx_4:1.b &= 0xbf
0043539f        *cell_lane_flags = edx_4
004353a6        *row_attachment_flags &= 0xffffffdf
004353a8        i_2 += 1
004353a9        cell_lane_flags = &cell_lane_flags[0x15]
004353af        i_6 = i_2
004353b3        if (i_2 s>= 8)
004353b3        break
004351e5        game_1 = game_2
004353b9        game_1 = game_2
004353c7        row_attachment_flags = &row_attachment_flags[0x3d]
004353cb        runtime_row_count = game_1->runtime_row_count
004353ce        cond:3_1 = var_10 + 1 s< runtime_row_count
004353d0        var_10 += 1
004353d4        do while (cond:3_1)
004353e1        return runtime_row_count
