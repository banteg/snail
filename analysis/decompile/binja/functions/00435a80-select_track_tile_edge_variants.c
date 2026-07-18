/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: select_track_tile_edge_variants @ 0x435a80 */

00435a83        int32_t runtime_row_count = game->runtime_row_count
00435a87        int32_t i = 0
00435a8f        int32_t i_1 = 0
00435a93        if (runtime_row_count s> 0)
00435a9c        uint8_t* esi_1 = &game->runtime_cells[0][0].tile_id
00435aa7        int32_t j = 0
00435cfc        while (j s< 8)
00435aa9        (esi_1 - 0x3bfb04)->:0x3bfb05.b = 0
00435aad        uint32_t lane_and_flags = (esi_1 - 0x3bfb04)->runtime_cells[0][0].lane_and_flags
00435ab0        lane_and_flags:1.b &= 0x7f
00435ab3        (esi_1 - 0x3bfb04)->runtime_cells[0][0].lane_and_flags = lane_and_flags
00435ab6        uint8_t eax = (esi_1 - 0x3bfb04)->:0x3bfb04.b
00435ae2        if (eax != 0 && eax != 0x23 && eax != 0x1c && eax != 0x1d && eax != 0x1e && eax != 0xe)
00435aea        char eax_1
00435aea        if (j != 0)
00435af2        eax_1 = is_sub_loc_empty(&esi_1[0xffffff70])
00435af9        if (j == 0 || eax_1 != 0)
00435afb        (esi_1 - 0x3bfb04)->:0x3bfb05.b |= 8
00435b02        char eax_2
00435b02        if (j != 7)
00435b07        eax_2 = is_sub_loc_empty(&esi_1[0x18])
00435b0e        if (j == 7 || eax_2 != 0)
00435b10        (esi_1 - 0x3bfb04)->:0x3bfb05.b |= 4
00435b16        char eax_3
00435b16        if (i != 0)
00435b1e        eax_3 = is_sub_loc_empty(&esi_1[0xfffffd24])
00435b25        if (i == 0 || eax_3 != 0)
00435b27        (esi_1 - 0x3bfb04)->:0x3bfb05.b |= 1
00435b35        char eax_5
00435b35        if (i s< game->runtime_row_count - 1)
00435b3d        eax_5 = is_sub_loc_empty(&esi_1[0x264])
00435b44        if (i s>= game->runtime_row_count - 1 || eax_5 != 0)
00435b46        (esi_1 - 0x3bfb04)->:0x3bfb05.b |= 2
00435b4a        int32_t eax_6 = 0
00435b4c        eax_6.b = (esi_1 - 0x3bfb04)->:0x3bfb05.b
00435b55        struct Object* object
00435b55        if (eax_6 - 5 u<= 5)
00435b55        switch (eax_6)
00435bd0        case 5
00435bd0        (esi_1 - 0x3bfb04)->runtime_cells[0][0].lane_and_flags |= 0x8000
00435bd3        uint8_t eax_11 = (esi_1 - 0x3bfb04)->:0x3bfb04.b
00435beb        if (eax_11 == 1 || eax_11 == 0x14 || eax_11 == 0x15 || eax_11 == 0x1b || eax_11 == 0x21 || eax_11 == 0x22)
00435cec        set_bod_object(&esi_1[0xffffffc4], g_game_base->root_bod_catalog.floor_corners.storage[1].object)
00435bf7        if (eax_11 != 0x16 && eax_11 != 0xe && is_sub_loc_ramp(&esi_1[0xffffffc4]) == 0)
00435cec        set_bod_object(&esi_1[0xffffffc4], g_game_base->root_bod_catalog.slide_corners.storage[1].object)
00435c98        case 6
00435c98        (esi_1 - 0x3bfb04)->runtime_cells[0][0].lane_and_flags |= 0x8000
00435c9b        uint8_t eax_18 = (esi_1 - 0x3bfb04)->:0x3bfb04.b
00435cb3        if (eax_18 == 1 || eax_18 == 0x14 || eax_18 == 0x15 || eax_18 == 0x1b || eax_18 == 0x21 || eax_18 == 0x22)
00435ce2        object = g_game_base->root_bod_catalog.floor_corners.storage[3].object
00435ce2        goto label_435ce8
00435cbb        if (eax_18 != 0x16 && eax_18 != 0xe && is_sub_loc_ramp(&esi_1[0xffffffc4]) == 0)
00435cec        set_bod_object(&esi_1[0xffffffc4], g_game_base->root_bod_catalog.slide_corners.storage[3].object)
00435b67        case 9
00435b67        (esi_1 - 0x3bfb04)->runtime_cells[0][0].lane_and_flags |= 0x8000
00435b6a        uint8_t eax_8 = (esi_1 - 0x3bfb04)->:0x3bfb04.b
00435b82        if (eax_8 == 1 || eax_8 == 0x14 || eax_8 == 0x15 || eax_8 == 0x1b || eax_8 == 0x21 || eax_8 == 0x22)
00435bc0        object = g_game_base->root_bod_catalog.floor_corners.storage[0].object
00435ce8        label_435ce8:
00435cec        set_bod_object(&esi_1[0xffffffc4], object)
00435b8e        if (eax_8 != 0x16 && eax_8 != 0xe && is_sub_loc_ramp(&esi_1[0xffffffc4]) == 0)
00435cec        set_bod_object(&esi_1[0xffffffc4], g_game_base->root_bod_catalog.slide_corners.storage[0].object)
00435c39        case 0xa
00435c39        (esi_1 - 0x3bfb04)->runtime_cells[0][0].lane_and_flags |= 0x8000
00435c3c        uint8_t eax_15 = (esi_1 - 0x3bfb04)->:0x3bfb04.b
00435c54        if (eax_15 == 1 || eax_15 == 0x14 || eax_15 == 0x15 || eax_15 == 0x1b || eax_15 == 0x21 || eax_15 == 0x22)
00435cec        set_bod_object(&esi_1[0xffffffc4], g_game_base->root_bod_catalog.floor_corners.storage[2].object)
00435c60        if (eax_15 != 0x16 && eax_15 != 0xe && is_sub_loc_ramp(&esi_1[0xffffffc4]) == 0)
00435c74        struct GameRoot* game_base_1 = g_game_base
00435c7a        struct Object* object_1
00435c7a        object_1.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object.b
00435c7a        object_1:1.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object:1.b
00435c7a        object_1:2.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object:2.b
00435c7a        object_1:3.b = game_base_1->root_bod_catalog.slide_corners.storage[2].object:3.b
00435cec        set_bod_object(&esi_1[0xffffffc4], object_1)
00435cf1        i = i_1
00435cf5        j += 1
00435cf6        esi_1 = &esi_1[0x54]
00435d02        runtime_row_count = game
00435d06        i += 1
00435d07        i_1 = i
00435d0e        do while (i s< *(runtime_row_count + 0x54))
00435d1b        return runtime_row_count
