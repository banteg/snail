/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_subgame_level @ 0x437eb0 */

00437eb0        struct Game* game_2 = game
00437ec1        unhide_star_field(data_4df904 + 0x4f33c)
00437ece        if (game->level_mode != 7)
00437ed7        unhide_gameplay_scores(game)
00437ed0        hide_gameplay_scores(game)
00437eef        int16_t x87control
00437eef        int32_t eax_3 = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
00437ef9        if (eax_3 u<= 4)
00437efb        char* var_1c_1
00437efb        switch (eax_3)
00437f02        case 0
00437f02        void* __saved_ebp_1 = &data_4dfb08
00437f07        int32_t var_18_1 = 0
00437f08        var_1c_1 = "music/1.ogg"
00437f0f        case 1
00437f0f        void* __saved_ebp_2 = &data_4dfb08
00437f14        int32_t var_18_2 = 0
00437f15        var_1c_1 = "music/2.ogg"
00437f29        case 2, 4
00437f29        void* __saved_ebp_4 = &data_4dfb08
00437f2e        int32_t var_18_4 = 0
00437f2f        var_1c_1 = "music/3.ogg"
00437f1c        case 3
00437f1c        void* __saved_ebp_3 = &data_4dfb08
00437f21        int32_t var_18_3 = 0
00437f22        var_1c_1 = "music/4.ogg"
00437f34        cache_music_file(var_1c_1)
00437f3c        game->__offset(0x1270fcc).d = 0x42480000
00437f4c        game->__offset(0x1270fd0).d = 0x42c80000
00437f56        initialize_enemy_manager(&game->__offset(0x1270fd4).d)
00437f61        initialize_damage_gauge(&game->__offset(0x3bbb28).d)
00437f77        initialize_sub_lazer_pool(&game->sub_lazer_pool)
00437f82        initialize_salt_hazard_pool(&game->salt_pool)
00437f8c        reset_voice_manager(0x751498)
00437fa0        int32_t __saved_ebp_16 = load_frontend_level_by_mode_and_index(&game->level_segment_count, game->level_mode, level_index)
00437fb7        if (game->selected_level_record_active != 0 || game->selected_level_record_persistent != 0)
00438062        float replay_speed_scalar = game->selected_level_record->replay_speed_scalar
00438065        game->_pad_00[0x30] = replay_speed_scalar.b
00438065        game->_pad_00[0x31] = replay_speed_scalar:1.b
00438065        game->_pad_00[0x32] = replay_speed_scalar:2.b
00438065        game->_pad_00[0x33] = replay_speed_scalar:3.b
00438071        game->level_mode = game->selected_level_record->replay_mode_id
0043807a        uint32_t challenge_difficulty_value = game->selected_level_record->challenge_difficulty_value
0043807d        game->_pad_00[0x2c] = challenge_difficulty_value.b
0043807d        game->_pad_00[0x2d] = challenge_difficulty_value:1.b
0043807d        game->_pad_00[0x2e] = challenge_difficulty_value:2.b
0043807d        game->_pad_00[0x2f] = challenge_difficulty_value:3.b
00438086        uint32_t challenge_speed_value = game->selected_level_record->challenge_speed_value
00438089        game->_pad_00[0x28] = challenge_speed_value.b
00438089        game->_pad_00[0x29] = challenge_speed_value:1.b
00438089        game->_pad_00[0x2a] = challenge_speed_value:2.b
00438089        game->_pad_00[0x2b] = challenge_speed_value:3.b
0043809b        game->challenge_difficulty_scalar = fconvert.s(float.t(game->selected_level_record->challenge_difficulty_value) * fconvert.t(0.00999999978f))
00437fbd        int32_t level_mode = game->level_mode
00437fc3        if (level_mode == 3)
00437fc5        int32_t edx_1 = data_4df95c
00437fcb        game->_pad_00[0x30] = edx_1.b
00437fcb        game->_pad_00[0x31] = edx_1:1.b
00437fcb        game->_pad_00[0x32] = edx_1:2.b
00437fcb        game->_pad_00[0x33] = edx_1:3.b
00437fdf        if (level_mode == 0 || level_mode == 4 || level_mode == 7)
00438030        if (game->__offset(0x1b01d0).d != 0xbf800000)
00438057        game->_pad_00[0x30].d = fconvert.s(fconvert.t(game->__offset(0x1b01d0).d) * fconvert.t(0.00999999978f) * fconvert.t(0.900000036f) + fconvert.t(0.200000003f))
0043803a        game->_pad_00[0x30].d = fconvert.s(calc_slider_to_rate(0f))
00437fe4        if (level_mode == 1)
00437fec        int32_t __saved_ebp_6 = __saved_ebp_16
00437ffd        game->_pad_00[0x30].d = fconvert.s(calc_slider_to_rate(fconvert.s(float.t(data_4df958) * fconvert.t(0.00999999978f))))
0043809b        game->challenge_difficulty_scalar = fconvert.s(float.t(data_4df960) * fconvert.t(0.00999999978f))
0043800e        if (level_mode == 2)
00438021        game->_pad_00[0x30].d = fconvert.s(calc_slider_to_rate(data_4df95c))
004380b0        if (game->selected_level_record_active != 0 || game->selected_level_record_persistent != 0)
00438136        game->__offset(0x125ffd8).d = game->selected_level_record->__offset(0x1fab0).d
00438148        game->__offset(0x125ffdc).d = game->selected_level_record->__offset(0x1fab4).d
004380b2        int32_t level_mode_1 = game->level_mode
004380cb        if (level_mode_1 == 2 || level_mode_1 == 3 || level_mode_1 == 0 || level_mode_1 == 4 || level_mode_1 == 7)
00438110        game->__offset(0x125ffd8).d = fconvert.s(fconvert.t(game->__offset(0x1b01d4).d) * fconvert.t(0.00999999978f))
00438122        game->__offset(0x125ffdc).d = fconvert.s(fconvert.t(game->__offset(0x1b01d8).d) * fconvert.t(0.00999999978f))
004380d0        if (level_mode_1 == 1)
004380e4        game->__offset(0x125ffd8).d = fconvert.s(float.t(data_4df960) * fconvert.t(0.00999999978f) * fconvert.t(0.800000012f))
004380fc        game->__offset(0x125ffdc).d = fconvert.s(float.t(data_4df960) * fconvert.t(0.00999999978f) * fconvert.t(0.800000012f))
00438154        initialize_track_parcel_slots(&game->parcel_pool)
00438166        if (*(data_4df904 + 0x4f2e0) == 1)
0043816e        hide_border_init(game->__offset(0x35bb88).d)
00438179        hide_border_init(game->__offset(0x35bb8c).d)
00438181        int16_t x87control_1 = rebuild_track_runtime_from_segments(game, level_index)
0043818d        if (game->__offset(0x1b01e4).d != 5)
00438255        activate_landscape_entry(&game->__offset(0xff7c00).d, game->__offset(0x1b01dc).d)
00438193        int32_t __saved_ebp_10 = 0
004381a1        int32_t eax_8 = __ftol(x87control_1, random_float_below(4f))
004381a9        int32_t level_index_1
004381a9        if (eax_8 u> 3)
00438200        level_index_1 = level_index
004381ab        switch (eax_8)
004381b2        case 0
004381f9        level_index_1 = load_landscape_script_by_name(data_4df904 + 0x106c218, "SpaceBluesWhorl.txt")
004381ca        case 1
004381ca        level_index_1 = load_landscape_script_by_name(data_4df904 + 0x106c218, "SpaceGreenWarp.txt")
004381e2        case 2
004381e2        level_index_1 = load_landscape_script_by_name(data_4df904 + 0x106c218, "SpacePurple.txt")
004381e9        case 3
004381f9        level_index_1 = load_landscape_script_by_name(data_4df904 + 0x106c218, "SpaceRed.txt")
0043820b        activate_landscape_entry(&game->__offset(0xff7c00).d, level_index_1)
00438210        int32_t __saved_ebp_13 = 0
00438216        long double st0_5 = random_float_below(1f)
0043821b        long double temp1_1 = fconvert.t(0.5f)
0043821b        st0_5 - temp1_1
00438229        if ((((st0_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp1_1) ? 1 : 0) << 0xa | (st0_5 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00438240        *(data_4df904 + 0x4ec64) = 0
00438231        *(data_4df904 + 0x4ec64) = 1
00438273        if ((0x200 & game->__offset(0x359084).d) == 0)
00438284        game->__offset(0x359088).d = &game->__offset(0x355b9c).d
0043828a        game->__offset(0x35908c).d = game->__offset(0x355ba8).d
0043828d        game->__offset(0x355ba8).d = &game->__offset(0x359080).d
00438290        void* ecx_30 = game->__offset(0x35908c).d
00438295        if (ecx_30 != 0)
00438297        *(ecx_30 + 8) = (&game->__offset(0x359080).d).b
00438297        *(ecx_30 + 9) = (&game->__offset(0x359080).d):1.b
00438297        *(ecx_30 + 0xa) = (&game->__offset(0x359080).d):2.b
00438297        *(ecx_30 + 0xb) = (&game->__offset(0x359080).d):3.b
0043829a        game->__offset(0x359084).d |= 0x200
0043827a        report_errorf("List ADDafter")
0043829d        game->__offset(0x359098).d = 0
004382a3        game->__offset(0x359094).d = 0
004382a9        game->__offset(0x359090).d = 0
004382af        int32_t edx_7 = game->__offset(0x359084).d
004382b5        long double x87_r7_25 = float.t(game->first_block_row_count)
004382bf        game->__offset(0x3590d4).d = &game->__offset(0x3bb764).d
004382c8        game->__offset(0x359098).d = fconvert.s(x87_r7_25)
004382d9        game->__offset(0x359084).d = edx_7 & 0xffffffdf
004382df        game->__offset(0x3590b4).d = 0x3f7fbe77
004382ef        if ((0x200 & game->__offset(0x3590e4).d) == 0)
00438300        game->__offset(0x3590e8).d = &game->__offset(0x355b9c).d
00438306        game->__offset(0x3590ec).d = game->__offset(0x355ba8).d
00438309        game->__offset(0x355ba8).d = &game->__offset(0x3590e0).d
0043830c        void* ecx_33 = game->__offset(0x3590ec).d
00438311        if (ecx_33 != 0)
00438313        *(ecx_33 + 8) = (&game->__offset(0x3590e0).d).b
00438313        *(ecx_33 + 9) = (&game->__offset(0x3590e0).d):1.b
00438313        *(ecx_33 + 0xa) = (&game->__offset(0x3590e0).d):2.b
00438313        *(ecx_33 + 0xb) = (&game->__offset(0x3590e0).d):3.b
00438316        game->__offset(0x3590e4).d |= 0x200
004382f6        report_errorf("List ADDafter")
00438319        game->__offset(0x3590f8).d = 0
0043831f        game->__offset(0x3590f4).d = 0
00438325        game->__offset(0x3590f0).d = 0
00438331        long double x87_r7_26 = float.t(game->completion_row_start)
0043833a        int32_t eax_15
0043833a        eax_15.b = game->__offset(0x3590e4).d.b & 0xdf
0043833c        game->__offset(0x359134).d = &game->__offset(0x3bb764).d
00438342        game->__offset(0x3590e4).d = eax_15
00438348        game->__offset(0x3590f8).d = fconvert.s(x87_r7_26)
0043834e        game->__offset(0x359114).d = 0x3f7fbe77
00438354        game->track_state_latch = 0
0043835a        game->replay_update_cursor = 0
00438360        game->times_up.state = 0
00438366        game->subgame_state = 2
00438378        *(data_4df904 + 0x56c) = 1
00438389        release_mouse_cursor(data_4df904 + 0x290)
00438391        game->__offset(0x3bbb70).d = 1
00438397        game->__offset(0x3be0d4).d = 0
0043839d        char* game_1 = initialize_subgoldy(&game->__offset(0x3bb764).d, 1)
004383b5        if ((0x200 & *(game_1 + 0x3bf2cc)) == 0)
004383cc        char* ecx_38 = data_4df904 + 0x5ac
004383d2        void* edx_10
004383d2        edx_10.b = *ecx_38
004383d2        edx_10:1.b = ecx_38[1]
004383d2        edx_10:2.b = ecx_38[2]
004383d2        edx_10:3.b = ecx_38[3]
004383d6        if (edx_10 != 0)
004383e4        *(edx_10 + 8) = &game_1[0x3bf2c8]
004383e7        void* edx_12
004383e7        edx_12.b = *ecx_38
004383e7        edx_12:1.b = ecx_38[1]
004383e7        edx_12:2.b = ecx_38[2]
004383e7        edx_12:3.b = ecx_38[3]
004383ec        *(*(edx_12 + 8) + 0xc) = edx_12
004383ef        void* edx_13
004383ef        edx_13.b = *ecx_38
004383ef        edx_13:1.b = ecx_38[1]
004383ef        edx_13:2.b = ecx_38[2]
004383ef        edx_13:3.b = ecx_38[3]
004383f6        void* edx_14 = *(edx_13 + 8)
004383f9        *ecx_38 = edx_14.b
004383f9        ecx_38[1] = edx_14:1.b
004383f9        ecx_38[2] = edx_14:2.b
004383f9        ecx_38[3] = edx_14:3.b
004383fb        *(edx_14 + 8) = 0
004383d8        *ecx_38 = (&game_1[0x3bf2c8]).b
004383d8        ecx_38[1] = (&game_1[0x3bf2c8]):1.b
004383d8        ecx_38[2] = (&game_1[0x3bf2c8]):2.b
004383d8        ecx_38[3] = (&game_1[0x3bf2c8]):3.b
004383da        *(game_1 + 0x3bf2d0) = 0
004383dd        void* edx_11
004383dd        edx_11.b = *ecx_38
004383dd        edx_11:1.b = ecx_38[1]
004383dd        edx_11:2.b = ecx_38[2]
004383dd        edx_11:3.b = ecx_38[3]
004383df        *(edx_11 + 0xc) = 0
004383fe        *(game_1 + 0x3bf2cc) |= 0x200
004383bc        report_errorf("List ADD")
0043840f        if ((0x200 & *(game_1 + 0x3be738)) == 0)
00438425        void** eax_20 = data_4df904 + 0x5ac
0043842a        void* edx_15 = *eax_20
0043842e        if (edx_15 != 0)
0043843c        *(edx_15 + 8) = &game_1[0x3be734]
0043843f        void* edx_17 = *eax_20
00438444        *(*(edx_17 + 8) + 0xc) = edx_17
0043844e        void* edx_19 = *(*eax_20 + 8)
00438451        *eax_20 = edx_19
00438453        *(edx_19 + 8) = 0
00438430        *eax_20 = &game_1[0x3be734]
00438432        game_1[0x3be73c] = 0
00438432        game_1[0x3be73d] = 0
00438432        game_1[0x3be73e] = 0
00438432        game_1[0x3be73f] = 0
00438437        *(*eax_20 + 0xc) = 0
00438456        *(game_1 + 0x3be738) |= 0x200
00438416        report_errorf("List ADD")
00438467        if ((0x200 & *(game_1 + 0x3beb14)) == 0)
0043847d        void** eax_23 = data_4df904 + 0x5ac
00438482        void* edx_20 = *eax_23
00438486        if (edx_20 != 0)
00438494        *(edx_20 + 8) = &game_1[0x3beb10]
00438497        void* edx_22 = *eax_23
0043849c        *(*(edx_22 + 8) + 0xc) = edx_22
004384a6        void* edx_24 = *(*eax_23 + 8)
004384a9        *eax_23 = edx_24
004384ab        *(edx_24 + 8) = 0
00438488        *eax_23 = &game_1[0x3beb10]
0043848a        game_1[0x3beb18] = 0
0043848a        game_1[0x3beb19] = 0
0043848a        game_1[0x3beb1a] = 0
0043848a        game_1[0x3beb1b] = 0
0043848f        *(*eax_23 + 0xc) = 0
004384ae        *(game_1 + 0x3beb14) |= 0x200
0043846e        report_errorf("List ADD")
004384bf        if ((0x200 & *(game_1 + 0x3beef0)) == 0)
004384d5        void** eax_26 = data_4df904 + 0x5ac
004384da        void* edx_25 = *eax_26
004384de        if (edx_25 != 0)
004384ec        *(edx_25 + 8) = &game_1[0x3beeec]
004384ef        void* edx_27 = *eax_26
004384f4        *(*(edx_27 + 8) + 0xc) = edx_27
004384fe        void* edx_29 = *(*eax_26 + 8)
00438501        *eax_26 = edx_29
00438503        *(edx_29 + 8) = 0
004384e0        *eax_26 = &game_1[0x3beeec]
004384e2        game_1[0x3beef4] = 0
004384e2        game_1[0x3beef5] = 0
004384e2        game_1[0x3beef6] = 0
004384e2        game_1[0x3beef7] = 0
004384e7        *(*eax_26 + 0xc) = 0
00438506        *(game_1 + 0x3beef0) |= 0x200
004384c6        report_errorf("List ADD")
00438517        if ((0x200 & *(game_1 + 0x3bf980)) == 0)
0043852d        void** eax_29 = data_4df904 + 0x5ac
00438532        void* edx_30 = *eax_29
00438536        if (edx_30 != 0)
00438544        *(edx_30 + 8) = &game_1[0x3bf97c]
00438547        void* edx_32 = *eax_29
0043854c        *(*(edx_32 + 8) + 0xc) = edx_32
00438556        void* edx_34 = *(*eax_29 + 8)
00438559        *eax_29 = edx_34
0043855b        *(edx_34 + 8) = 0
00438538        *eax_29 = &game_1[0x3bf97c]
0043853a        game_1[0x3bf984] = 0
0043853a        game_1[0x3bf985] = 0
0043853a        game_1[0x3bf986] = 0
0043853a        game_1[0x3bf987] = 0
0043853f        *(*eax_29 + 0xc) = 0
0043855e        *(game_1 + 0x3bf980) |= 0x200
0043851e        report_errorf("List ADD")
00438567        int32_t ecx_43
00438567        ecx_43.b = (*(game_1 + 0x3bf980)).b | 0x80
0043856a        *(game_1 + 0x3bf980) = ecx_43
0043857e        if ((0x200 & *(game_1 + 0x3be0ec)) == 0)
00438594        void** eax_32 = data_4df904 + 0x5ac
00438599        void* edx_36 = *eax_32
0043859d        if (edx_36 != 0)
004385ab        *(edx_36 + 8) = &game_1[0x3be0e8]
004385ae        void* edx_38 = *eax_32
004385b3        *(*(edx_38 + 8) + 0xc) = edx_38
004385bd        void* edx_40 = *(*eax_32 + 8)
004385c0        *eax_32 = edx_40
004385c2        *(edx_40 + 8) = 0
0043859f        *eax_32 = &game_1[0x3be0e8]
004385a1        game_1[0x3be0f0] = 0
004385a1        game_1[0x3be0f1] = 0
004385a1        game_1[0x3be0f2] = 0
004385a1        game_1[0x3be0f3] = 0
004385a6        *(*eax_32 + 0xc) = 0
004385c5        *(game_1 + 0x3be0ec) |= 0x200
00438585        report_errorf("List ADD")
004385cb        if ((game->__offset(0x3bb768).d & 0x200) == 0)
004385e1        int32_t* eax_34 = data_4df904 + 0x5ac
004385e6        void* ecx_45 = *eax_34
004385ea        if (ecx_45 != 0)
004385f8        *(ecx_45 + 8) = (&game->__offset(0x3bb764).d).b
004385f8        *(ecx_45 + 9) = (&game->__offset(0x3bb764).d):1.b
004385f8        *(ecx_45 + 0xa) = (&game->__offset(0x3bb764).d):2.b
004385f8        *(ecx_45 + 0xb) = (&game->__offset(0x3bb764).d):3.b
004385fb        void* ecx_47 = *eax_34
004385fd        void* edx_41
004385fd        edx_41.b = *(ecx_47 + 8)
004385fd        edx_41:1.b = *(ecx_47 + 9)
004385fd        edx_41:2.b = *(ecx_47 + 0xa)
004385fd        edx_41:3.b = *(ecx_47 + 0xb)
00438600        *(edx_41 + 0xc) = ecx_47
00438603        void* ecx_48 = *eax_34
00438605        void* ecx_49
00438605        ecx_49.b = *(ecx_48 + 8)
00438605        ecx_49:1.b = *(ecx_48 + 9)
00438605        ecx_49:2.b = *(ecx_48 + 0xa)
00438605        ecx_49:3.b = *(ecx_48 + 0xb)
00438608        *eax_34 = ecx_49
0043860a        *(ecx_49 + 8) = 0
0043860a        *(ecx_49 + 9) = 0
0043860a        *(ecx_49 + 0xa) = 0
0043860a        *(ecx_49 + 0xb) = 0
004385ec        *eax_34 = &game->__offset(0x3bb764).d
004385ee        game->__offset(0x3bb76c).d = 0
004385f1        void* ecx_46 = *eax_34
004385f3        *(ecx_46 + 0xc) = 0
004385f3        *(ecx_46 + 0xd) = 0
004385f3        *(ecx_46 + 0xe) = 0
004385f3        *(ecx_46 + 0xf) = 0
0043860d        game->__offset(0x3bb768).d |= 0x200
004385d2        report_errorf("List ADD")
00438616        initialize_slug_voice_manager(&game_1[0x35bb7c])
0043862f        if ((0x200 & *(game_1 + 0xff7bc8)) == 0)
00438640        *(game_1 + 0xff7bcc) = &game_1[0x355bd4]
00438643        int32_t edx_43
00438643        edx_43.b = game_1[0x355be0]
00438643        edx_43:1.b = game_1[0x355be1]
00438643        edx_43:2.b = game_1[0x355be2]
00438643        edx_43:3.b = game_1[0x355be3]
00438646        *(game_1 + 0xff7bd0) = edx_43
00438649        game_1[0x355be0] = (&game_1[0xff7bc4]).b
00438649        game_1[0x355be1] = (&game_1[0xff7bc4]):1.b
00438649        game_1[0x355be2] = (&game_1[0xff7bc4]):2.b
00438649        game_1[0x355be3] = (&game_1[0xff7bc4]):3.b
0043864c        void* ecx_52 = *(game_1 + 0xff7bd0)
00438651        if (ecx_52 != 0)
00438653        *(ecx_52 + 8) = (&game_1[0xff7bc4]).b
00438653        *(ecx_52 + 9) = (&game_1[0xff7bc4]):1.b
00438653        *(ecx_52 + 0xa) = (&game_1[0xff7bc4]):2.b
00438653        *(ecx_52 + 0xb) = (&game_1[0xff7bc4]):3.b
00438656        *(game_1 + 0xff7bc8) |= 0x200
00438636        report_errorf("List ADDafter")
00438659        int32_t eax_36 = *(game_1 + 0x40)
0043865c        *(game_1 + 0xff7bfc) = &game->__offset(0x3bb764).d
00438665        if (eax_36 == 0)
00438673        int32_t __saved_ebp_15 = *(game_1 + 0x1b01e0)
00438680        sub_48b32c(*(game_1 + 0x35bb94) + 0x2cc, "0/%i")
0043868e        unhide_border_init(*(game_1 + 0x35bb90))
00438699        unhide_border_init(*(game_1 + 0x35bb94))
004386aa        set_input_controller_pointer_authored_xy(0, 320f, 240f)
004386b7        set_input_controller_pointer_authored_xy(1, 320f, 240f)
004386c1        *(game_1 + 0x3bdea0) = 0x43a00000
004386c7        *(game_1 + 0x3bdea4) = 0x43a00000
004386cd        *game_1 = 1
004386d0        calc_subgame_rate(game_1)
004386d9        return
