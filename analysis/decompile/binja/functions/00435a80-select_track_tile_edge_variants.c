/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: select_track_tile_edge_variants @ 0x435a80 */

00435a87        int32_t i = 0
00435a8f        int32_t i_1 = 0
00435a93        if (game->runtime_row_count s<= 0)
00435a93        return
00435a9c        struct TrackRowCellTileByteView* tile_cursor = &game->runtime_cells[0][0].tile_id
00435aa7        int32_t j = 0
00435cfc        while (j s< 8)
00435aa9        tile_cursor->open_edge_mask = 0
00435aad        uint32_t lane_and_flags = tile_cursor->lane_and_flags
00435ab0        lane_and_flags:1.b &= 0x7f
00435ab3        tile_cursor->lane_and_flags = lane_and_flags
00435ab6        enum SubLocTileId tile_id = tile_cursor->tile_id
00435ae2        if (tile_id != SUBLOC_TILE_EMPTY && tile_id != SUBLOC_TILE_RING_MARKER && tile_id != SUBLOC_TILE_UNIVERSE_HOLE && tile_id != SUBLOC_TILE_PATH_ENTRY_LOWERCASE && tile_id != SUBLOC_TILE_PATH_ENTRY_UPPERCASE && tile_id != SUBLOC_TILE_WALL2)
00435aea        char eax_1
00435aea        if (j != 0)
00435af2        eax_1 = is_sub_loc_empty(tile_cursor - 0x90)
00435af9        if (j == 0 || eax_1 != 0)
00435afb        tile_cursor->open_edge_mask |= 8
00435b02        char eax_2
00435b02        if (j != 7)
00435b07        eax_2 = is_sub_loc_empty(&tile_cursor->stride_tail[0x10])
00435b0e        if (j == 7 || eax_2 != 0)
00435b10        tile_cursor->open_edge_mask |= 4
00435b16        char eax_3
00435b16        if (i != 0)
00435b1e        eax_3 = is_sub_loc_empty(tile_cursor - 0x2dc)
00435b25        if (i == 0 || eax_3 != 0)
00435b27        tile_cursor->open_edge_mask |= 1
00435b35        char eax_5
00435b35        if (i s< game->runtime_row_count - 1)
00435b3d        eax_5 = is_sub_loc_empty(tile_cursor + 0x264)
00435b44        if (i s>= game->runtime_row_count - 1 || eax_5 != 0)
00435b46        tile_cursor->open_edge_mask |= 2
00435b4a        int32_t eax_6 = 0
00435b4c        eax_6.b = tile_cursor->open_edge_mask
00435b55        struct Object* object
00435b55        if (eax_6 - 5 u<= 5)
00435b55        switch (eax_6)
00435bd0        case 5
00435bd0        tile_cursor->lane_and_flags |= 0x8000
00435bd3        enum SubLocTileId tile_id_2 = tile_cursor->tile_id
00435beb        if (tile_id_2 == SUBLOC_TILE_FLOOR_DOT || tile_id_2 == SUBLOC_TILE_FLOOR_VARIANT_14 || tile_id_2 == SUBLOC_TILE_FLOOR_DASH || tile_id_2 == SUBLOC_TILE_FLOOR_VARIANT_1B || tile_id_2 == SUBLOC_TILE_GARBAGE_HAZARD || tile_id_2 == SUBLOC_TILE_SALT_HAZARD)
00435cec        set_bod_object(tile_cursor - 0x3c, g_game_base->root_bod_catalog.floor_corners.storage[1].object)
00435bf7        if (tile_id_2 != SUBLOC_TILE_TRAMPOLINE && tile_id_2 != SUBLOC_TILE_WALL2 && is_sub_loc_ramp(tile_cursor - 0x3c) == 0)
00435cec        set_bod_object(tile_cursor - 0x3c, g_game_base->root_bod_catalog.slide_corners.storage[1].object)
00435c98        case 6
00435c98        tile_cursor->lane_and_flags |= 0x8000
00435c9b        enum SubLocTileId tile_id_4 = tile_cursor->tile_id
00435cb3        if (tile_id_4 == SUBLOC_TILE_FLOOR_DOT || tile_id_4 == SUBLOC_TILE_FLOOR_VARIANT_14 || tile_id_4 == SUBLOC_TILE_FLOOR_DASH || tile_id_4 == SUBLOC_TILE_FLOOR_VARIANT_1B || tile_id_4 == SUBLOC_TILE_GARBAGE_HAZARD || tile_id_4 == SUBLOC_TILE_SALT_HAZARD)
00435ce2        object = g_game_base->root_bod_catalog.floor_corners.storage[3].object
00435ce2        goto label_435ce8
00435cbb        if (tile_id_4 != SUBLOC_TILE_TRAMPOLINE && tile_id_4 != SUBLOC_TILE_WALL2 && is_sub_loc_ramp(tile_cursor - 0x3c) == 0)
00435cec        set_bod_object(tile_cursor - 0x3c, g_game_base->root_bod_catalog.slide_corners.storage[3].object)
00435b67        case 9
00435b67        tile_cursor->lane_and_flags |= 0x8000
00435b6a        enum SubLocTileId tile_id_1 = tile_cursor->tile_id
00435b82        if (tile_id_1 == SUBLOC_TILE_FLOOR_DOT || tile_id_1 == SUBLOC_TILE_FLOOR_VARIANT_14 || tile_id_1 == SUBLOC_TILE_FLOOR_DASH || tile_id_1 == SUBLOC_TILE_FLOOR_VARIANT_1B || tile_id_1 == SUBLOC_TILE_GARBAGE_HAZARD || tile_id_1 == SUBLOC_TILE_SALT_HAZARD)
00435bc0        object = g_game_base->root_bod_catalog.floor_corners.storage[0].object
00435ce8        label_435ce8:
00435cec        set_bod_object(tile_cursor - 0x3c, object)
00435b8e        if (tile_id_1 != SUBLOC_TILE_TRAMPOLINE && tile_id_1 != SUBLOC_TILE_WALL2 && is_sub_loc_ramp(tile_cursor - 0x3c) == 0)
00435cec        set_bod_object(tile_cursor - 0x3c, g_game_base->root_bod_catalog.slide_corners.storage[0].object)
00435c39        case 0xa
00435c39        tile_cursor->lane_and_flags |= 0x8000
00435c3c        enum SubLocTileId tile_id_3 = tile_cursor->tile_id
00435c54        if (tile_id_3 == SUBLOC_TILE_FLOOR_DOT || tile_id_3 == SUBLOC_TILE_FLOOR_VARIANT_14 || tile_id_3 == SUBLOC_TILE_FLOOR_DASH || tile_id_3 == SUBLOC_TILE_FLOOR_VARIANT_1B || tile_id_3 == SUBLOC_TILE_GARBAGE_HAZARD || tile_id_3 == SUBLOC_TILE_SALT_HAZARD)
00435cec        set_bod_object(tile_cursor - 0x3c, g_game_base->root_bod_catalog.floor_corners.storage[2].object)
00435c60        if (tile_id_3 != SUBLOC_TILE_TRAMPOLINE && tile_id_3 != SUBLOC_TILE_WALL2 && is_sub_loc_ramp(tile_cursor - 0x3c) == 0)
00435c74        struct GameRoot* game_base_1 = g_game_base
00435c7a        struct Object* object_1
00435c7a        object_1.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object.b
00435c7a        object_1:1.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object:1.b
00435c7a        object_1:2.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object:2.b
00435c7a        object_1:3.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object:3.b
00435cec        set_bod_object(tile_cursor - 0x3c, object_1)
00435cf1        i = i_1
00435cf5        j += 1
00435cf6        tile_cursor = &tile_cursor[1]
00435d06        i += 1
00435d07        i_1 = i
00435d0e        do while (i s< *(game + 0x54))
00435d1b        return
