/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: promote_track_tiles_to_fringe_variants @ 0x4355f0 */

004355fb        int32_t i_1 = 0
00435605        if (game->runtime_row_count - 1 s<= 0)
00435605        return
0043560f        struct Object** esi_1 = &game->runtime_cells[0][0].object
004356dd        int32_t i
0043561a        int32_t j_1 = 8
004356c4        int32_t j
0043562b        (esi_1 - 0x3bfaec)->runtime_cells[0][0].lane_and_flags &= 0xffffffdf
00435635        if (is_sub_loc_empty(&esi_1[0x9f]) != 0)
0043563b        struct GameRoot* game_base_1 = g_game_base
00435640        int32_t k = 0
0043567e        while (k s< 0x1c0)
00435642        struct Object* object = (esi_1 - 0x3bfaec)->runtime_cells[0][0].object
00435656        if (object == *(&game_base_1->root_bod_catalog.floor_slices.storage[0].object + k) || object == *(&game_base_1->root_bod_catalog.slide_slices.storage[0].object + k))
00435663        set_bod_object(&esi_1[-9], *(&game_base_1->root_bod_catalog.warning_slices.storage[0].object + k))
0043566d        (esi_1 - 0x3bfaec)->runtime_cells[0][0].lane_and_flags |= 0x20
00435670        game_base_1 = g_game_base
00435675        k += 0x38
00435680        int32_t k_1 = 0
004356be        while (k_1 s< 0xe0)
00435682        struct Object* object_1 = (esi_1 - 0x3bfaec)->runtime_cells[0][0].object
00435696        if (object_1 == *(&game_base_1->root_bod_catalog.floor_corners.storage[0].object + k_1) || object_1 == *(&game_base_1->root_bod_catalog.slide_corners.storage[0].object + k_1))
004356a3        set_bod_object(&esi_1[-9], *(&game_base_1->root_bod_catalog.warning_corners.storage[0].object + k_1))
004356ad        (esi_1 - 0x3bfaec)->runtime_cells[0][0].lane_and_flags |= 0x20
004356b0        game_base_1 = g_game_base
004356b5        k_1 += 0x38
004356c0        esi_1 = &esi_1[0x15]
004356c3        j = j_1
004356c3        j_1 -= 1
004356c4        do while (j != 1)
004356d2        i = i_1 + 1
004356d6        i_1 = i
004356dd        do while (i s< game->runtime_row_count - 1)
004356ea        return
