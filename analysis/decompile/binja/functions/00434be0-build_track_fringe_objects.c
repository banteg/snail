/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_objects @ 0x434be0 */

00434bea        struct SubgameRuntime* game_1 = game
00434bf2        struct SubgameRuntime* game_2 = game_1
00434bf6        initialize_fringe_manager(&g_game_base->subgame.__offset(0x35bbbc).d)
00434bfe        int32_t ebx = 0
00434c02        int32_t var_48 = 0
00434c06        if (game_1->runtime_row_count s> 0)
00434c0c        struct SubRow (* edx_1)[0xc80] = &game_1->runtime_rows
00434c14        struct TrackRowCell (* esi_1)[0xc80][0x8] = &game_1->runtime_cells
00434c1a        struct SubRow (* var_44_1)[0xc80] = edx_1
0043514c        bool cond:2_1
00434c1e        int32_t var_4c_1 = 8
0043512e        bool cond:1_1
00434c26        uint8_t ecx_1 = (esi_1 - 0x3bfac8)->:0x3bfb05.b
00434c29        int32_t edi_1 = 0
00434c2e        if (ecx_1 == 9)
00434c30        edi_1 = 1
00434c3a        if (ecx_1 == 5)
00434c3c        edi_1 = 3
00434c46        if (ecx_1 == 0xa)
00434c48        edi_1 = 2
00434c52        if (ecx_1 == 6)
00434c54        edi_1 = 4
00434c59        uint8_t eax_2 = (esi_1 - 0x3bfac8)->:0x3bfb04.b
00434c66        if (eax_2 == 2 || eax_2 == 8 || eax_2 == 5)
00434c68        edi_1 = 5
00434c83        if (eax_2 == 3 || eax_2 == 9 || eax_2 == 0xb || eax_2 == 0xc || eax_2 == 0xd || eax_2 == 6)
00434c85        edi_1 = 6
00434c94        if (eax_2 == 4 || eax_2 == 0xa || eax_2 == 7)
00434c96        edi_1 = 7
00434cbb        if (((edx_1 - 0x5ccac8)->:0x5ccac8.b & 4) != 0 || ecx_1 == 0 || eax_2 == 0x20 || (g_runtime_config.render_flags.b & 0x20) == 0)
004350e0        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_front = nullptr
004350e3        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_right = nullptr
004350e6        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_left = nullptr
004350e9        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_back = nullptr
00434ccd        if (is_neighbor_cell_solid(game_1, esi_1, 0, 0) == 1)
00434ce0        if (is_neighbor_cell_solid(game_1, esi_1, 0, 1) != 0)
00434dd4        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_front = nullptr
00434cf4        if (is_neighbor_cell_solid(game_1, esi_1, 1, 1) != 1)
00434cfc        int32_t eax_6 = is_neighbor_cell_solid(game_1, esi_1, 1, 0)
00434d01        eax_6.b -= 1
00434d03        char temp1_1 = eax_6.b
00434d03        eax_6.b = neg.b(eax_6.b)
00434d0a        ebx = neg.d(sbb.d(eax_6, eax_6, temp1_1 != 0)) + 1
00434d1a        int32_t ebp
00434d1a        if (is_neighbor_cell_solid(game_1, esi_1, 0xffffffff, 1) != 1)
00434d27        int32_t eax_11 = is_neighbor_cell_solid(game_1, esi_1, 0xffffffff, 0)
00434d2c        eax_11.b -= 1
00434d2e        char temp2_1 = eax_11.b
00434d2e        eax_11.b = neg.b(eax_11.b)
00434d35        ebp = neg.d(sbb.d(eax_11, eax_11, temp2_1 != 0)) + 1
00434d1c        ebp = 0
00434d43        struct FringeObject* eax_15 = allocate_fringe_object(&g_game_base->subgame.__offset(0x35bbbc).d)
00434d4b        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_front = eax_15
00434d70        set_bod_object(eax_15, *(g_game_base + ((ebx + edi_1 * 0xc) * 3 + ebp) * 0x38 + 0x44dd4))
00434d75        struct FringeObject* fringe_front = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_front
00434d81        fringe_front->bod.list_flags |= 0x20
00434d89        struct Vec3* eax_17 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_front->position
00434d8c        eax_17->x = (esi_1 + 0x10)->x
00434d91        eax_17->y = (esi_1 + 0x10)->y
00434d97        eax_17->z = (esi_1 + 0x10)->z
00434dab        struct tColour out
00434dab        struct tColour* eax_18 = get_track_skirt_color(&g_game_base->subgame, &out)
00434db5        struct Color4f* edx_9 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_front->color
00434db8        game_1 = game_2
00434dbc        ebx = 0
00434dbe        edx_9->r = eax_18->r
00434dc3        edx_9->g = eax_18->g
00434dc9        edx_9->b = eax_18->b
00434dcf        edx_9->a = eax_18->a
00434de4        if (is_neighbor_cell_solid(game_1, esi_1, 1, 0) != 0)
00434ed8        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_right = nullptr
00434df8        if (is_neighbor_cell_solid(game_1, esi_1, 1, 0xffffffff) != 1)
00434e00        int32_t eax_22 = is_neighbor_cell_solid(game_1, esi_1, 0, 0xffffffff)
00434e05        eax_22.b -= 1
00434e07        char temp3_1 = eax_22.b
00434e07        eax_22.b = neg.b(eax_22.b)
00434e0e        ebx = neg.d(sbb.d(eax_22, eax_22, temp3_1 != 0)) + 1
00434e1e        int32_t ebp_3
00434e1e        if (is_neighbor_cell_solid(game_1, esi_1, 1, 1) != 1)
00434e2b        int32_t eax_27 = is_neighbor_cell_solid(game_1, esi_1, 0, 1)
00434e30        eax_27.b -= 1
00434e32        char temp4_1 = eax_27.b
00434e32        eax_27.b = neg.b(eax_27.b)
00434e39        ebp_3 = neg.d(sbb.d(eax_27, eax_27, temp4_1 != 0)) + 1
00434e20        ebp_3 = 0
00434e47        struct FringeObject* eax_31 = allocate_fringe_object(&g_game_base->subgame.__offset(0x35bbbc).d)
00434e4f        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_right = eax_31
00434e74        set_bod_object(eax_31, *(g_game_base + ((ebx + edi_1 * 0xc) * 3 + ebp_3) * 0x38 + 0x44fcc))
00434e79        struct FringeObject* fringe_right = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_right
00434e85        fringe_right->bod.list_flags |= 0x20
00434e8d        struct Vec3* eax_33 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_right->position
00434e90        eax_33->x = (esi_1 + 0x10)->x
00434e95        eax_33->y = (esi_1 + 0x10)->y
00434e9b        eax_33->z = (esi_1 + 0x10)->z
00434eaf        struct tColour out_1
00434eaf        struct tColour* eax_34 = get_track_skirt_color(&g_game_base->subgame, &out_1)
00434eb9        struct Color4f* edx_17 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_right->color
00434ebc        game_1 = game_2
00434ec0        ebx = 0
00434ec2        edx_17->r = eax_34->r
00434ec7        edx_17->g = eax_34->g
00434ecd        edx_17->b = eax_34->b
00434ed3        edx_17->a = eax_34->a
00434ee8        if (is_neighbor_cell_solid(game_1, esi_1, 0xffffffff, 0) != 0)
00434fdc        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_left = nullptr
00434efc        if (is_neighbor_cell_solid(game_1, esi_1, 0xffffffff, 1) != 1)
00434f04        int32_t eax_38 = is_neighbor_cell_solid(game_1, esi_1, 0, 1)
00434f09        eax_38.b -= 1
00434f0b        char temp5_1 = eax_38.b
00434f0b        eax_38.b = neg.b(eax_38.b)
00434f12        ebx = neg.d(sbb.d(eax_38, eax_38, temp5_1 != 0)) + 1
00434f22        int32_t ebp_6
00434f22        if (is_neighbor_cell_solid(game_1, esi_1, 0xffffffff, 0xffffffff) != 1)
00434f2f        int32_t eax_43 = is_neighbor_cell_solid(game_1, esi_1, 0, 0xffffffff)
00434f34        eax_43.b -= 1
00434f36        char temp6_1 = eax_43.b
00434f36        eax_43.b = neg.b(eax_43.b)
00434f3d        ebp_6 = neg.d(sbb.d(eax_43, eax_43, temp6_1 != 0)) + 1
00434f24        ebp_6 = 0
00434f4b        struct FringeObject* eax_47 = allocate_fringe_object(&g_game_base->subgame.__offset(0x35bbbc).d)
00434f53        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_left = eax_47
00434f78        set_bod_object(eax_47, *(g_game_base + ((ebx + edi_1 * 0xc) * 3 + ebp_6) * 0x38 + 0x451c4))
00434f7d        struct FringeObject* fringe_left = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_left
00434f89        fringe_left->bod.list_flags |= 0x20
00434f91        struct Vec3* eax_49 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_left->position
00434f94        eax_49->x = (esi_1 + 0x10)->x
00434f99        eax_49->y = (esi_1 + 0x10)->y
00434f9f        eax_49->z = (esi_1 + 0x10)->z
00434fb3        struct tColour out_2
00434fb3        struct tColour* eax_50 = get_track_skirt_color(&g_game_base->subgame, &out_2)
00434fbd        struct Color4f* edx_25 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_left->color
00434fc0        game_1 = game_2
00434fc4        ebx = 0
00434fc6        edx_25->r = eax_50->r
00434fcb        edx_25->g = eax_50->g
00434fd1        edx_25->b = eax_50->b
00434fd7        edx_25->a = eax_50->a
00434fec        if (is_neighbor_cell_solid(game_1, esi_1, 0, 0xffffffff) != 0)
004350e9        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_back = nullptr
00435000        if (is_neighbor_cell_solid(game_1, esi_1, 0xffffffff, 0xffffffff) != 1)
00435008        int32_t eax_54 = is_neighbor_cell_solid(game_1, esi_1, 0xffffffff, 0)
0043500d        eax_54.b -= 1
0043500f        char temp7_1 = eax_54.b
0043500f        eax_54.b = neg.b(eax_54.b)
00435016        ebx = neg.d(sbb.d(eax_54, eax_54, temp7_1 != 0)) + 1
00435026        int32_t ebp_9
00435026        if (is_neighbor_cell_solid(game_1, esi_1, 1, 0xffffffff) != 1)
00435033        int32_t eax_59 = is_neighbor_cell_solid(game_1, esi_1, 1, 0)
00435038        eax_59.b -= 1
0043503a        char temp8_1 = eax_59.b
0043503a        eax_59.b = neg.b(eax_59.b)
00435041        ebp_9 = neg.d(sbb.d(eax_59, eax_59, temp8_1 != 0)) + 1
00435028        ebp_9 = 0
0043504f        struct FringeObject* eax_63 = allocate_fringe_object(&g_game_base->subgame.__offset(0x35bbbc).d)
00435057        (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_back = eax_63
0043507c        set_bod_object(eax_63, *(g_game_base + ((ebx + edi_1 * 0xc) * 3 + ebp_9) * 0x38 + 0x453bc))
00435081        struct FringeObject* fringe_back = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_back
0043508d        fringe_back->bod.list_flags |= 0x20
00435095        struct Vec3* eax_65 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_back->position
00435098        eax_65->x = *(esi_1 + 0x10)
0043509d        eax_65->y = *(esi_1 + 0x14)
004350a3        eax_65->z = *(esi_1 + 0x18)
004350b7        struct tColour out_3
004350b7        int32_t* eax_66 = get_track_skirt_color(&g_game_base->subgame.scan_reset, &out_3)
004350c1        struct Color4f* edx_33 = &(esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_back->color
004350c4        game_1 = game_2
004350c8        ebx = 0
004350ca        edx_33->r = *eax_66
004350cf        edx_33->g = eax_66[1]
004350d5        edx_33->b = eax_66[2]
004350db        edx_33->a = eax_66[3]
004350ec        edx_1 = var_44_1
004350f3        if (((edx_1 - 0x5ccac8)->:0x5ccac8.b & 4) != 0)
004350f5        struct FringeObject* fringe_front_1 = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_front
004350ff        if (fringe_front_1 != 0)
00435101        fringe_front_1->bod.list_flags &= 0xffffffdf
00435104        struct FringeObject* fringe_back_1 = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_back
00435109        if (fringe_back_1 != 0)
0043510b        fringe_back_1->bod.list_flags &= 0xffffffdf
0043510e        struct FringeObject* fringe_right_1 = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_right
00435113        if (fringe_right_1 != 0)
00435115        fringe_right_1->bod.list_flags &= 0xffffffdf
00435118        struct FringeObject* fringe_left_1 = (esi_1 - 0x3bfac8)->runtime_cells[0][0].fringe_left
0043511d        if (fringe_left_1 != 0)
0043511f        fringe_left_1->bod.list_flags &= 0xffffffdf
00435126        esi_1 = &(*esi_1)[0][1]
00435129        cond:1_1 = var_4c_1 != 1
0043512a        var_4c_1 -= 1
0043512e        do while (cond:1_1)
0043513c        edx_1 = &(*edx_1)[1]
00435142        cond:2_1 = var_48 + 1 s< game_1->runtime_row_count
00435144        var_48 += 1
00435148        var_44_1 = edx_1
0043514c        do while (cond:2_1)
00435173        return 0
