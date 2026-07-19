/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_objects @ 0x434be0 */

00434bea        struct SubgameRuntime* runtime = game
00434bf2        struct SubgameRuntime* runtime_saved = runtime
00434bf6        initialize_fringe_manager(&g_game_base->subgame.fringe_manager)
00434bfe        int32_t edge_variant_a = 0
00434c02        int32_t row_index = 0
00434c06        if (runtime->runtime_row_count s> 0)
00434c0c        struct SubRow* row = &runtime->runtime_rows
00434c14        struct TrackRowCell* cell = &runtime->runtime_cells
00434c1a        struct SubRow* row_cursor = row
0043514c        bool cond:2_1
00434c1e        int32_t cells_remaining = 8
0043512e        bool cond:1_1
00434c26        uint8_t open_edge_mask = cell->open_edge_mask
00434c29        int32_t fringe_family = 0
00434c2e        if (open_edge_mask == 9)
00434c30        fringe_family = 1
00434c3a        if (open_edge_mask == 5)
00434c3c        fringe_family = 3
00434c46        if (open_edge_mask == 0xa)
00434c48        fringe_family = 2
00434c52        if (open_edge_mask == 6)
00434c54        fringe_family = 4
00434c59        enum SubLocTileId tile_id = cell->tile_id
00434c66        if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET)
00434c68        fringe_family = 5
00434c83        if (tile_id == SUBLOC_TILE_RAMP_GREATER || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH || tile_id == SUBLOC_TILE_RAMP_LESS)
00434c85        fringe_family = 6
00434c94        if (tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET)
00434c96        fringe_family = 7
00434cbb        if ((row->flags.b & 4) != 0 || open_edge_mask == 0 || tile_id == SUBLOC_TILE_FLOOR_HASH_MARKER || (g_runtime_config.render_flags.b & 0x20) == 0)
004350e0        cell->fringe_front = nullptr
004350e3        cell->fringe_right = nullptr
004350e6        cell->fringe_left = nullptr
004350e9        cell->fringe_back = nullptr
00434ccd        if (is_neighbor_cell_solid(runtime, cell, 0, 0) == 1)
00434ce0        if (is_neighbor_cell_solid(runtime, cell, 0, 1) != 0)
00434dd4        cell->fringe_front = nullptr
00434cf4        if (is_neighbor_cell_solid(runtime, cell, 1, 1) != 1)
00434cfc        int32_t eax_5 = is_neighbor_cell_solid(runtime, cell, 1, 0)
00434d01        eax_5.b -= 1
00434d03        char temp1_1 = eax_5.b
00434d03        eax_5.b = neg.b(eax_5.b)
00434d0a        edge_variant_a = neg.d(sbb.d(eax_5, eax_5, temp1_1 != 0)) + 1
00434d1a        int32_t front_edge_variant_b
00434d1a        if (is_neighbor_cell_solid(runtime, cell, 0xffffffff, 1) != 1)
00434d27        int32_t eax_10 = is_neighbor_cell_solid(runtime, cell, 0xffffffff, 0)
00434d2c        eax_10.b -= 1
00434d2e        char temp2_1 = eax_10.b
00434d2e        eax_10.b = neg.b(eax_10.b)
00434d35        front_edge_variant_b = neg.d(sbb.d(eax_10, eax_10, temp2_1 != 0)) + 1
00434d1c        front_edge_variant_b = 0
00434d43        struct Fringe* front_fringe = allocate_fringe_object(&g_game_base->subgame.fringe_manager)
00434d4b        cell->fringe_front = front_fringe
00434d70        set_bod_object(front_fringe, g_game_base->root_bod_catalog.fringe_catalog.entries[0][0][0][(edge_variant_a + fringe_family * 0xc) * 3 + front_edge_variant_b].object)
00434d75        struct Fringe* fringe_front = cell->fringe_front
00434d81        fringe_front->bod.bod.list_flags |= 0x20
00434d89        struct Vec3* eax_15 = &cell->fringe_front->bod.position
00434d8c        eax_15->x = cell->anchor_position.x
00434d91        eax_15->y = cell->anchor_position.y
00434d97        eax_15->z = cell->anchor_position.z
00434dab        struct tColour front_color
00434dab        struct tColour* eax_16 = get_track_skirt_color(&g_game_base->subgame, &front_color)
00434db5        struct tColour* edx_8 = &cell->fringe_front->bod.color
00434db8        runtime = runtime_saved
00434dbc        edge_variant_a = 0
00434dbe        edx_8->r = eax_16->r
00434dc3        edx_8->g = eax_16->g
00434dc9        edx_8->b = eax_16->b
00434dcf        edx_8->a = eax_16->a
00434de4        if (is_neighbor_cell_solid(runtime, cell, 1, 0) != 0)
00434ed8        cell->fringe_right = nullptr
00434df8        if (is_neighbor_cell_solid(runtime, cell, 1, 0xffffffff) != 1)
00434e00        int32_t eax_20 = is_neighbor_cell_solid(runtime, cell, 0, 0xffffffff)
00434e05        eax_20.b -= 1
00434e07        char temp3_1 = eax_20.b
00434e07        eax_20.b = neg.b(eax_20.b)
00434e0e        edge_variant_a = neg.d(sbb.d(eax_20, eax_20, temp3_1 != 0)) + 1
00434e1e        int32_t right_edge_variant_b
00434e1e        if (is_neighbor_cell_solid(runtime, cell, 1, 1) != 1)
00434e2b        int32_t eax_25 = is_neighbor_cell_solid(runtime, cell, 0, 1)
00434e30        eax_25.b -= 1
00434e32        char temp4_1 = eax_25.b
00434e32        eax_25.b = neg.b(eax_25.b)
00434e39        right_edge_variant_b = neg.d(sbb.d(eax_25, eax_25, temp4_1 != 0)) + 1
00434e20        right_edge_variant_b = 0
00434e47        struct Fringe* right_fringe = allocate_fringe_object(&g_game_base->subgame.fringe_manager)
00434e4f        cell->fringe_right = right_fringe
00434e74        set_bod_object(right_fringe, g_game_base->root_bod_catalog.fringe_catalog.entries[0][1][0][(edge_variant_a + fringe_family * 0xc) * 3 + right_edge_variant_b].object)
00434e79        struct Fringe* fringe_right = cell->fringe_right
00434e85        fringe_right->bod.bod.list_flags |= 0x20
00434e8d        struct Vec3* eax_30 = &cell->fringe_right->bod.position
00434e90        eax_30->x = cell->anchor_position.x
00434e95        eax_30->y = cell->anchor_position.y
00434e9b        eax_30->z = cell->anchor_position.z
00434eaf        struct tColour right_color
00434eaf        struct tColour* eax_31 = get_track_skirt_color(&g_game_base->subgame, &right_color)
00434eb9        struct tColour* edx_16 = &cell->fringe_right->bod.color
00434ebc        runtime = runtime_saved
00434ec0        edge_variant_a = 0
00434ec2        edx_16->r = eax_31->r
00434ec7        edx_16->g = eax_31->g
00434ecd        edx_16->b = eax_31->b
00434ed3        edx_16->a = eax_31->a
00434ee8        if (is_neighbor_cell_solid(runtime, cell, 0xffffffff, 0) != 0)
00434fdc        cell->fringe_left = nullptr
00434efc        if (is_neighbor_cell_solid(runtime, cell, 0xffffffff, 1) != 1)
00434f04        int32_t eax_35 = is_neighbor_cell_solid(runtime, cell, 0, 1)
00434f09        eax_35.b -= 1
00434f0b        char temp5_1 = eax_35.b
00434f0b        eax_35.b = neg.b(eax_35.b)
00434f12        edge_variant_a = neg.d(sbb.d(eax_35, eax_35, temp5_1 != 0)) + 1
00434f22        int32_t left_edge_variant_b
00434f22        if (is_neighbor_cell_solid(runtime, cell, 0xffffffff, 0xffffffff) != 1)
00434f2f        int32_t eax_40 = is_neighbor_cell_solid(runtime, cell, 0, 0xffffffff)
00434f34        eax_40.b -= 1
00434f36        char temp6_1 = eax_40.b
00434f36        eax_40.b = neg.b(eax_40.b)
00434f3d        left_edge_variant_b = neg.d(sbb.d(eax_40, eax_40, temp6_1 != 0)) + 1
00434f24        left_edge_variant_b = 0
00434f4b        struct Fringe* left_fringe = allocate_fringe_object(&g_game_base->subgame.fringe_manager)
00434f53        cell->fringe_left = left_fringe
00434f78        set_bod_object(left_fringe, g_game_base->root_bod_catalog.fringe_catalog.entries[0][2][0][(edge_variant_a + fringe_family * 0xc) * 3 + left_edge_variant_b].object)
00434f7d        struct Fringe* fringe_left = cell->fringe_left
00434f89        fringe_left->bod.bod.list_flags |= 0x20
00434f91        struct Vec3* eax_45 = &cell->fringe_left->bod.position
00434f94        eax_45->x = cell->anchor_position.x
00434f99        eax_45->y = cell->anchor_position.y
00434f9f        eax_45->z = cell->anchor_position.z
00434fb3        struct tColour left_color
00434fb3        struct tColour* eax_46 = get_track_skirt_color(&g_game_base->subgame, &left_color)
00434fbd        struct tColour* edx_24 = &cell->fringe_left->bod.color
00434fc0        runtime = runtime_saved
00434fc4        edge_variant_a = 0
00434fc6        edx_24->r = eax_46->r
00434fcb        edx_24->g = eax_46->g
00434fd1        edx_24->b = eax_46->b
00434fd7        edx_24->a = eax_46->a
00434fec        if (is_neighbor_cell_solid(runtime, cell, 0, 0xffffffff) != 0)
004350e9        cell->fringe_back = nullptr
00435000        if (is_neighbor_cell_solid(runtime, cell, 0xffffffff, 0xffffffff) != 1)
00435008        int32_t eax_50 = is_neighbor_cell_solid(runtime, cell, 0xffffffff, 0)
0043500d        eax_50.b -= 1
0043500f        char temp7_1 = eax_50.b
0043500f        eax_50.b = neg.b(eax_50.b)
00435016        edge_variant_a = neg.d(sbb.d(eax_50, eax_50, temp7_1 != 0)) + 1
00435026        int32_t back_edge_variant_b
00435026        if (is_neighbor_cell_solid(runtime, cell, 1, 0xffffffff) != 1)
00435033        int32_t eax_55 = is_neighbor_cell_solid(runtime, cell, 1, 0)
00435038        eax_55.b -= 1
0043503a        char temp8_1 = eax_55.b
0043503a        eax_55.b = neg.b(eax_55.b)
00435041        back_edge_variant_b = neg.d(sbb.d(eax_55, eax_55, temp8_1 != 0)) + 1
00435028        back_edge_variant_b = 0
0043504f        struct Fringe* back_fringe = allocate_fringe_object(&g_game_base->subgame.fringe_manager)
00435057        cell->fringe_back = back_fringe
0043507c        set_bod_object(back_fringe, g_game_base->root_bod_catalog.fringe_catalog.entries[0][3][0][(edge_variant_a + fringe_family * 0xc) * 3 + back_edge_variant_b].object)
00435081        struct Fringe* fringe_back = cell->fringe_back
0043508d        fringe_back->bod.bod.list_flags |= 0x20
00435095        struct Vec3* eax_60 = &cell->fringe_back->bod.position
00435098        eax_60->x = cell->anchor_position.x
0043509d        eax_60->y = cell->anchor_position.y
004350a3        eax_60->z = cell->anchor_position.z
004350b7        struct tColour back_color
004350b7        struct tColour* eax_61 = get_track_skirt_color(&g_game_base->subgame, &back_color)
004350c1        struct tColour* edx_32 = &cell->fringe_back->bod.color
004350c4        runtime = runtime_saved
004350c8        edge_variant_a = 0
004350ca        edx_32->r = eax_61->r
004350cf        edx_32->g = eax_61->g
004350d5        edx_32->b = eax_61->b
004350db        edx_32->a = eax_61->a
004350ec        row = row_cursor
004350f3        if ((row->flags.b & 4) != 0)
004350f5        struct Fringe* fringe_front_1 = cell->fringe_front
004350ff        if (fringe_front_1 != 0)
00435101        fringe_front_1->bod.bod.list_flags &= 0xffffffdf
00435104        struct Fringe* fringe_back_1 = cell->fringe_back
00435109        if (fringe_back_1 != 0)
0043510b        fringe_back_1->bod.bod.list_flags &= 0xffffffdf
0043510e        struct Fringe* fringe_right_1 = cell->fringe_right
00435113        if (fringe_right_1 != 0)
00435115        fringe_right_1->bod.bod.list_flags &= 0xffffffdf
00435118        struct Fringe* fringe_left_1 = cell->fringe_left
0043511d        if (fringe_left_1 != 0)
0043511f        fringe_left_1->bod.bod.list_flags &= 0xffffffdf
00435126        cell = &cell[1]
00435129        cond:1_1 = cells_remaining != 1
0043512a        cells_remaining -= 1
0043512e        do while (cond:1_1)
0043513c        row = &row[1]
00435142        cond:2_1 = row_index + 1 s< runtime->runtime_row_count
00435144        row_index += 1
00435148        row_cursor = row
0043514c        do while (cond:2_1)
00435173        return 0
