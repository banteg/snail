/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_subgame_level @ 0x437eb0 */

00437eb0        struct Game* game_1 = game
00437ec1        unhide_star_field(&g_game_base[0x4f33c])
00437ece        if (game->level_mode != 7)
00437ed7        unhide_gameplay_scores(game)
00437ed0        hide_gameplay_scores(game)
00437eef        int16_t x87control
00437eef        int32_t eax_3 = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
00437ef9        if (eax_3 u<= 4)
00437efb        char* var_1c_1
00437efb        switch (eax_3)
00437f02        case 0
00437f02        void* __saved_ebp_1 = &g_blank_text
00437f07        int32_t var_18_1 = 0
00437f08        var_1c_1 = "music/1.ogg"
00437f0f        case 1
00437f0f        void* __saved_ebp_2 = &g_blank_text
00437f14        int32_t var_18_2 = 0
00437f15        var_1c_1 = "music/2.ogg"
00437f29        case 2, 4
00437f29        void* __saved_ebp_4 = &g_blank_text
00437f2e        int32_t var_18_4 = 0
00437f2f        var_1c_1 = "music/3.ogg"
00437f1c        case 3
00437f1c        void* __saved_ebp_3 = &g_blank_text
00437f21        int32_t var_18_3 = 0
00437f22        var_1c_1 = "music/4.ogg"
00437f34        cache_music_file(var_1c_1)
00437f3c        game->__offset(0x1270fcc).d = 0x42480000
00437f4c        game->__offset(0x1270fd0).d = 0x42c80000
00437f56        initialize_enemy_manager(&game->__offset(0x1270fd4).d)
00437f61        initialize_damage_gauge(&game->__offset(0x3bbb28).d)
00437f77        initialize_sub_lazer_pool(&game->sub_lazers)
00437f82        initialize_salt_hazard_pool(&game->salt_hazards)
00437f8c        reset_voice_manager(0x751498)
00437fa0        int32_t __saved_ebp_16
00437fa0        int32_t edx
00437fa0        __saved_ebp_16, edx = load_frontend_level_by_mode_and_index(&game->level_segment_count, game->level_mode, level_index)
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
00438030        if (game->_pad_74622[0x13bbae].d != 0xbf800000)
00438057        game->_pad_00[0x30].d = fconvert.s(fconvert.t(game->_pad_74622[0x13bbae].d) * fconvert.t(0.00999999978f) * fconvert.t(0.900000036f) + fconvert.t(0.200000003f))
0043803a        game->_pad_00[0x30].d = fconvert.s(calc_slider_to_rate(0f))
00437fe4        if (level_mode == 1)
00437fec        int32_t __saved_ebp_6 = __saved_ebp_16
00437ffd        game->_pad_00[0x30].d = fconvert.s(calc_slider_to_rate(fconvert.s(float.t(data_4df958) * fconvert.t(0.00999999978f))))
0043809b        game->challenge_difficulty_scalar = fconvert.s(float.t(data_4df960) * fconvert.t(0.00999999978f))
0043800e        if (level_mode == 2)
00438021        game->_pad_00[0x30].d = fconvert.s(calc_slider_to_rate(data_4df95c))
004380b0        if (game->selected_level_record_active != 0 || game->selected_level_record_persistent != 0)
0043812a        struct SelectedLevelRecord* selected_level_record = game->selected_level_record
00438130        int32_t edx_3
00438130        edx_3.b = selected_level_record->__offset(0x1fab0).b
00438130        edx_3:1.b = selected_level_record->__offset(0x1fab1).b
00438130        edx_3:2.b = selected_level_record->__offset(0x1fab2).b
00438130        edx_3:3.b = selected_level_record->__offset(0x1fab3).b
00438136        game->__offset(0x125ffd8).d = edx_3
00438148        game->__offset(0x125ffdc).d = game->selected_level_record->__offset(0x1fab4).d
004380b2        int32_t level_mode_1 = game->level_mode
004380cb        if (level_mode_1 == 2 || level_mode_1 == 3 || level_mode_1 == 0 || level_mode_1 == 4 || level_mode_1 == 7)
00438110        game->__offset(0x125ffd8).d = fconvert.s(fconvert.t(game->_pad_74622[0x13bbb2].d) * fconvert.t(0.00999999978f))
00438122        game->__offset(0x125ffdc).d = fconvert.s(fconvert.t(game->_pad_74622[0x13bbb6].d) * fconvert.t(0.00999999978f))
004380d0        if (level_mode_1 == 1)
004380e4        game->__offset(0x125ffd8).d = fconvert.s(float.t(data_4df960) * fconvert.t(0.00999999978f) * fconvert.t(0.800000012f))
004380fc        game->__offset(0x125ffdc).d = fconvert.s(float.t(data_4df960) * fconvert.t(0.00999999978f) * fconvert.t(0.800000012f))
00438154        initialize_track_parcel_slots(&game->parcel_pool)
00438166        if (g_game_base[0x4f2e0] == 1)
0043816e        hide_border_init(game->__offset(0x35bb88).d)
00438179        hide_border_init(game->__offset(0x35bb8c).d)
00438181        int16_t x87control_1 = rebuild_track_runtime_from_segments(game, level_index)
0043818d        if (game->_pad_74622[0x13bbc2].d != 5)
00438248        int32_t eax_12
00438248        eax_12.b = game->_pad_74622[0x13bbba]
00438248        eax_12:1.b = game->_pad_74622[0x13bbbb]
00438248        eax_12:2.b = game->_pad_74622[0x13bbbc]
00438248        eax_12:3.b = game->_pad_74622[0x13bbbd]
00438255        activate_landscape_entry(&game->__offset(0xff7c00).d, eax_12)
00438193        int32_t __saved_ebp_10 = 0
004381a1        int32_t eax_8 = ftol(x87control_1, random_float_below(4f))
004381a9        int32_t level_index_1
004381a9        if (eax_8 u> 3)
00438200        level_index_1 = level_index
004381ab        switch (eax_8)
004381b2        case 0
004381f9        level_index_1 = load_landscape_script_by_name(&g_game_base[0x106c218], "SpaceBluesWhorl.txt")
004381ca        case 1
004381ca        level_index_1 = load_landscape_script_by_name(&g_game_base[0x106c218], "SpaceGreenWarp.txt")
004381e2        case 2
004381e2        level_index_1 = load_landscape_script_by_name(&g_game_base[0x106c218], "SpacePurple.txt")
004381e9        case 3
004381f9        level_index_1 = load_landscape_script_by_name(&g_game_base[0x106c218], "SpaceRed.txt")
0043820b        activate_landscape_entry(&game->__offset(0xff7c00).d, level_index_1)
00438210        int32_t __saved_ebp_13 = 0
00438216        long double st0_5 = random_float_below(1f)
0043821b        long double temp1_1 = fconvert.t(0.5f)
0043821b        st0_5 - temp1_1
00438229        if ((((st0_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp1_1) ? 1 : 0) << 0xa | (st0_5 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00438240        g_game_base[0x4ec64] = 0
00438231        g_game_base[0x4ec64] = 1
00438273        if ((0x200 & game->banners.slots[0].bod.bod.list_flags) == 0)
00438284        game->banners.slots[0].bod.bod.list_prev = &game->_pad_74622[0x2e157a]
00438287        struct BodNode* ecx_28
00438287        ecx_28.b = game->_pad_74622[0x2e1586]
00438287        ecx_28:1.b = game->_pad_74622[0x2e1587]
00438287        ecx_28:2.b = game->_pad_74622[0x2e1588]
00438287        ecx_28:3.b = game->_pad_74622[0x2e1589]
0043828a        game->banners.slots[0].bod.bod.list_next = ecx_28
0043828d        game->_pad_74622[0x2e1586] = (&game->banners).b
0043828d        game->_pad_74622[0x2e1587] = (&game->banners):1.b
0043828d        game->_pad_74622[0x2e1588] = (&game->banners):2.b
0043828d        game->_pad_74622[0x2e1589] = (&game->banners):3.b
00438290        struct BodNode* list_next = game->banners.slots[0].bod.bod.list_next
00438295        if (list_next != 0)
00438297        list_next->list_prev.b = (&game->banners).b
00438297        list_next->list_prev:1.b = (&game->banners):1.b
00438297        list_next->list_prev:2.b = (&game->banners):2.b
00438297        list_next->list_prev:3.b = (&game->banners):3.b
0043829a        game->banners.slots[0].bod.bod.list_flags |= 0x200
0043827a        report_errorf("List ADDafter")
0043829d        game->banners.slots[0].bod.position.z = 0f
004382a3        game->banners.slots[0].bod.position.y = 0f
004382a9        game->banners.slots[0].bod.position.x = 0
004382bf        game->banners.slots[0].owner_player = &game->__offset(0x3bb764).d
004382c8        game->banners.slots[0].bod.position.z = fconvert.s(float.t(game->first_block_row_count))
004382d9        game->banners.slots[0].bod.bod.list_flags &= 0xffffffdf
004382df        game->banners.slots[0].bod.color.a = 0.999000013f
004382ef        if ((0x200 & game->banners.slots[1].bod.bod.list_flags) == 0)
00438300        game->banners.slots[1].bod.bod.list_prev = &game->_pad_74622[0x2e157a]
00438303        struct BodNode* ecx_30
00438303        ecx_30.b = game->_pad_74622[0x2e1586]
00438303        ecx_30:1.b = game->_pad_74622[0x2e1587]
00438303        ecx_30:2.b = game->_pad_74622[0x2e1588]
00438303        ecx_30:3.b = game->_pad_74622[0x2e1589]
00438306        game->banners.slots[1].bod.bod.list_next = ecx_30
00438309        game->_pad_74622[0x2e1586] = (&game->banners.slots[1]).b
00438309        game->_pad_74622[0x2e1587] = (&game->banners.slots[1]):1.b
00438309        game->_pad_74622[0x2e1588] = (&game->banners.slots[1]):2.b
00438309        game->_pad_74622[0x2e1589] = (&game->banners.slots[1]):3.b
0043830c        struct BodNode* list_next_1 = game->banners.slots[1].bod.bod.list_next
00438311        if (list_next_1 != 0)
00438313        list_next_1->list_prev.b = (&game->banners.slots[1]).b
00438313        list_next_1->list_prev:1.b = (&game->banners.slots[1]):1.b
00438313        list_next_1->list_prev:2.b = (&game->banners.slots[1]):2.b
00438313        list_next_1->list_prev:3.b = (&game->banners.slots[1]):3.b
00438316        game->banners.slots[1].bod.bod.list_flags |= 0x200
004382f6        report_errorf("List ADDafter")
00438319        game->banners.slots[1].bod.position.z = 0f
0043831f        game->banners.slots[1].bod.position.y = 0f
00438325        game->banners.slots[1].bod.position.x = 0
0043832b        uint32_t list_flags = game->banners.slots[1].bod.bod.list_flags
0043833a        list_flags.b &= 0xdf
0043833c        game->banners.slots[1].owner_player = &game->__offset(0x3bb764).d
00438342        game->banners.slots[1].bod.bod.list_flags = list_flags
00438348        game->banners.slots[1].bod.position.z = fconvert.s(float.t(game->completion_row_start))
0043834e        game->banners.slots[1].bod.color.a = 0.999000013f
00438354        game->track_state_latch = 0
0043835a        game->replay_update_cursor = 0
00438360        game->times_up.state = 0
00438366        game->subgame_state = 2
00438378        *(g_game_base + 0x56c) = 1
00438389        release_mouse_cursor(&g_game_base[0x290])
00438391        game->__offset(0x3bbb70).d = 1
00438397        game->__offset(0x3be0d4).d = 0
0043839d        struct SubgameRuntime* runtime
0043839d        struct Player* edi_3
0043839d        runtime, edi_3 = initialize_subgoldy(&game->__offset(0x3bb764).d, 1)
004383b5        if ((0x200 & runtime->player.presentation.jetpack_channel.list_flags) == 0)
004383cc        char* ecx_35 = &g_game_base[0x5ac]
004383d2        void* edx_10
004383d2        edx_10.b = *ecx_35
004383d2        edx_10:1.b = ecx_35[1]
004383d2        edx_10:2.b = ecx_35[2]
004383d2        edx_10:3.b = ecx_35[3]
004383d6        if (edx_10 != 0)
004383e4        *(edx_10 + 8) = &runtime->player.presentation.jetpack_channel
004383e7        void* edx_12
004383e7        edx_12.b = *ecx_35
004383e7        edx_12:1.b = ecx_35[1]
004383e7        edx_12:2.b = ecx_35[2]
004383e7        edx_12:3.b = ecx_35[3]
004383ec        *(*(edx_12 + 8) + 0xc) = edx_12
004383ef        void* edx_13
004383ef        edx_13.b = *ecx_35
004383ef        edx_13:1.b = ecx_35[1]
004383ef        edx_13:2.b = ecx_35[2]
004383ef        edx_13:3.b = ecx_35[3]
004383f6        void* edx_14 = *(edx_13 + 8)
004383f9        *ecx_35 = edx_14.b
004383f9        ecx_35[1] = edx_14:1.b
004383f9        ecx_35[2] = edx_14:2.b
004383f9        ecx_35[3] = edx_14:3.b
004383fb        *(edx_14 + 8) = 0
004383d8        *ecx_35 = (&runtime->player.presentation.jetpack_channel).b
004383d8        ecx_35[1] = (&runtime->player.presentation.jetpack_channel):1.b
004383d8        ecx_35[2] = (&runtime->player.presentation.jetpack_channel):2.b
004383d8        ecx_35[3] = (&runtime->player.presentation.jetpack_channel):3.b
004383da        runtime->player.presentation.jetpack_channel._pad_08[0] = 0
004383da        runtime->player.presentation.jetpack_channel._pad_08[1] = 0
004383da        runtime->player.presentation.jetpack_channel._pad_08[2] = 0
004383da        runtime->player.presentation.jetpack_channel._pad_08[3] = 0
004383dd        void* edx_11
004383dd        edx_11.b = *ecx_35
004383dd        edx_11:1.b = ecx_35[1]
004383dd        edx_11:2.b = ecx_35[2]
004383dd        edx_11:3.b = ecx_35[3]
004383df        *(edx_11 + 0xc) = 0
004383fe        runtime->player.presentation.jetpack_channel.list_flags |= 0x200
004383bc        report_errorf("List ADD")
0043840f        if ((0x200 & runtime->player.presentation.weapon_channels[0].list_flags) == 0)
00438425        void** eax_20 = &g_game_base[0x5ac]
0043842a        void* edx_15 = *eax_20
0043842e        if (edx_15 != 0)
0043843c        *(edx_15 + 8) = &runtime->player.presentation.weapon_channels
0043843f        void* edx_17 = *eax_20
00438444        *(*(edx_17 + 8) + 0xc) = edx_17
0043844e        void* edx_19 = *(*eax_20 + 8)
00438451        *eax_20 = edx_19
00438453        *(edx_19 + 8) = 0
00438430        *eax_20 = &runtime->player.presentation.weapon_channels
00438432        runtime->player.__offset(0x2fd8).b = 0
00438432        runtime->player.__offset(0x2fd9).b = 0
00438432        runtime->player.__offset(0x2fda).b = 0
00438432        runtime->player.__offset(0x2fdb).b = 0
00438437        *(*eax_20 + 0xc) = 0
00438456        runtime->player.presentation.weapon_channels[0].list_flags |= 0x200
00438416        report_errorf("List ADD")
00438467        if ((0x200 & runtime->player.presentation.weapon_channels[1].list_flags) == 0)
0043847d        void** eax_23 = &g_game_base[0x5ac]
00438482        void* edx_20 = *eax_23
00438486        if (edx_20 != 0)
00438494        *(edx_20 + 8) = &runtime->player.presentation.weapon_channels[1]
00438497        void* edx_22 = *eax_23
0043849c        *(*(edx_22 + 8) + 0xc) = edx_22
004384a6        void* edx_24 = *(*eax_23 + 8)
004384a9        *eax_23 = edx_24
004384ab        *(edx_24 + 8) = 0
00438488        *eax_23 = &runtime->player.presentation.weapon_channels[1]
0043848a        runtime->player.presentation.weapon_channels[1]._pad_08[0] = 0
0043848a        runtime->player.presentation.weapon_channels[1]._pad_08[1] = 0
0043848a        runtime->player.presentation.weapon_channels[1]._pad_08[2] = 0
0043848a        runtime->player.presentation.weapon_channels[1]._pad_08[3] = 0
0043848f        *(*eax_23 + 0xc) = 0
004384ae        runtime->player.presentation.weapon_channels[1].list_flags |= 0x200
0043846e        report_errorf("List ADD")
004384bf        if ((0x200 & runtime->player.presentation.weapon_channels[2].list_flags) == 0)
004384d5        void** eax_26 = &g_game_base[0x5ac]
004384da        void* edx_25 = *eax_26
004384de        if (edx_25 != 0)
004384ec        *(edx_25 + 8) = &runtime->player.presentation.weapon_channels[2]
004384ef        void* edx_27 = *eax_26
004384f4        *(*(edx_27 + 8) + 0xc) = edx_27
004384fe        void* edx_29 = *(*eax_26 + 8)
00438501        *eax_26 = edx_29
00438503        *(edx_29 + 8) = 0
004384e0        *eax_26 = &runtime->player.presentation.weapon_channels[2]
004384e2        runtime->player.presentation.weapon_channels[2]._pad_08[0] = 0
004384e2        runtime->player.presentation.weapon_channels[2]._pad_08[1] = 0
004384e2        runtime->player.presentation.weapon_channels[2]._pad_08[2] = 0
004384e2        runtime->player.presentation.weapon_channels[2]._pad_08[3] = 0
004384e7        *(*eax_26 + 0xc) = 0
00438506        runtime->player.presentation.weapon_channels[2].list_flags |= 0x200
004384c6        report_errorf("List ADD")
00438517        if ((0x200 & runtime->player.presentation.invincible_shell.list_flags) == 0)
0043852d        void** eax_29 = &g_game_base[0x5ac]
00438532        void* edx_30 = *eax_29
00438536        if (edx_30 != 0)
00438544        *(edx_30 + 8) = &runtime->player.presentation.invincible_shell
00438547        void* edx_32 = *eax_29
0043854c        *(*(edx_32 + 8) + 0xc) = edx_32
00438556        void* edx_34 = *(*eax_29 + 8)
00438559        *eax_29 = edx_34
0043855b        *(edx_34 + 8) = 0
00438538        *eax_29 = &runtime->player.presentation.invincible_shell
0043853a        runtime->player.presentation.invincible_shell.list_prev.b = nullptr
0043853a        runtime->player.presentation.invincible_shell.list_prev:1.b = 0
0043853a        runtime->player.presentation.invincible_shell.list_prev:2.b = 0
0043853a        runtime->player.presentation.invincible_shell.list_prev:3.b = 0
0043853f        *(*eax_29 + 0xc) = 0
0043855e        runtime->player.presentation.invincible_shell.list_flags |= 0x200
0043851e        report_errorf("List ADD")
00438561        uint32_t list_flags_1 = runtime->player.presentation.invincible_shell.list_flags
00438567        list_flags_1.b |= 0x80
0043856a        runtime->player.presentation.invincible_shell.list_flags = list_flags_1
0043857e        if ((0x200 & runtime->player.presentation.list_flags) == 0)
00438594        void** eax_32 = &g_game_base[0x5ac]
00438599        void* edx_36 = *eax_32
0043859d        if (edx_36 != 0)
004385ab        *(edx_36 + 8) = &runtime->player.presentation
004385ae        void* edx_38 = *eax_32
004385b3        *(*(edx_38 + 8) + 0xc) = edx_38
004385bd        void* edx_40 = *(*eax_32 + 8)
004385c0        *eax_32 = edx_40
004385c2        *(edx_40 + 8) = 0
0043859f        *eax_32 = &runtime->player.presentation
004385a1        runtime->player.presentation._pad_08[0] = 0
004385a1        runtime->player.presentation._pad_08[1] = 0
004385a1        runtime->player.presentation._pad_08[2] = 0
004385a1        runtime->player.presentation._pad_08[3] = 0
004385a6        *(*eax_32 + 0xc) = 0
004385c5        runtime->player.presentation.list_flags |= 0x200
00438585        report_errorf("List ADD")
004385cb        if ((edi_3->_pad_00[4].d & 0x200) == 0)
004385e1        void** eax_34 = &g_game_base[0x5ac]
004385e6        void* ecx_41 = *eax_34
004385ea        if (ecx_41 != 0)
004385f8        *(ecx_41 + 8) = edi_3.b
004385f8        *(ecx_41 + 9) = edi_3:1.b
004385f8        *(ecx_41 + 0xa) = edi_3:2.b
004385f8        *(ecx_41 + 0xb) = edi_3:3.b
004385fb        void* ecx_43 = *eax_34
004385fd        void* edx_41
004385fd        edx_41.b = *(ecx_43 + 8)
004385fd        edx_41:1.b = *(ecx_43 + 9)
004385fd        edx_41:2.b = *(ecx_43 + 0xa)
004385fd        edx_41:3.b = *(ecx_43 + 0xb)
00438600        *(edx_41 + 0xc) = ecx_43
00438603        void* ecx_44 = *eax_34
00438605        void* ecx_45
00438605        ecx_45.b = *(ecx_44 + 8)
00438605        ecx_45:1.b = *(ecx_44 + 9)
00438605        ecx_45:2.b = *(ecx_44 + 0xa)
00438605        ecx_45:3.b = *(ecx_44 + 0xb)
00438608        *eax_34 = ecx_45
0043860a        *(ecx_45 + 8) = 0
0043860a        *(ecx_45 + 9) = 0
0043860a        *(ecx_45 + 0xa) = 0
0043860a        *(ecx_45 + 0xb) = 0
004385ec        *eax_34 = edi_3
004385ee        edi_3->_pad_00[8] = 0
004385ee        edi_3->_pad_00[9] = 0
004385ee        edi_3->_pad_00[0xa] = 0
004385ee        edi_3->_pad_00[0xb] = 0
004385f1        void* ecx_42 = *eax_34
004385f3        *(ecx_42 + 0xc) = 0
004385f3        *(ecx_42 + 0xd) = 0
004385f3        *(ecx_42 + 0xe) = 0
004385f3        *(ecx_42 + 0xf) = 0
0043860d        edi_3->_pad_00[4].d |= 0x200
004385d2        report_errorf("List ADD")
00438616        initialize_slug_voice_manager(&runtime->slug_voice_manager.active)
0043862f        if ((0x200 & runtime->barrier.bod.bod.list_flags) == 0)
00438640        runtime->barrier.bod.bod.list_prev = &runtime->barrier_sub_lazer_list_head
00438643        struct BodNode* edx_43
00438643        edx_43.b = runtime->barrier_sub_lazer_list_head.bod.list_next.b
00438643        edx_43:1.b = runtime->barrier_sub_lazer_list_head.bod.list_next:1.b
00438643        edx_43:2.b = runtime->barrier_sub_lazer_list_head.bod.list_next:2.b
00438643        edx_43:3.b = runtime->barrier_sub_lazer_list_head.bod.list_next:3.b
00438646        runtime->barrier.bod.bod.list_next = edx_43
00438649        runtime->barrier_sub_lazer_list_head.bod.list_next.b = (&runtime->barrier).b
00438649        runtime->barrier_sub_lazer_list_head.bod.list_next:1.b = (&runtime->barrier):1.b
00438649        runtime->barrier_sub_lazer_list_head.bod.list_next:2.b = (&runtime->barrier):2.b
00438649        runtime->barrier_sub_lazer_list_head.bod.list_next:3.b = (&runtime->barrier):3.b
0043864c        struct BodNode* list_next_2 = runtime->barrier.bod.bod.list_next
00438651        if (list_next_2 != 0)
00438653        list_next_2->list_prev.b = (&runtime->barrier).b
00438653        list_next_2->list_prev:1.b = (&runtime->barrier):1.b
00438653        list_next_2->list_prev:2.b = (&runtime->barrier):2.b
00438653        list_next_2->list_prev:3.b = (&runtime->barrier):3.b
00438656        runtime->barrier.bod.bod.list_flags |= 0x200
00438636        report_errorf("List ADDafter")
0043865c        runtime->barrier.owner_player = edi_3
00438665        if (runtime->level_mode == 0)
00438673        int32_t __saved_ebp_15 = runtime->level_definition.parcel_count
00438680        sprintf(&runtime->lives_text_widget->text_buffer, "0/%i")
0043868e        unhide_border_init(runtime->lives_icon_widget)
00438699        unhide_border_init(runtime->lives_text_widget)
004386aa        set_input_controller_pointer_authored_xy(0, 320f, 240f)
004386b7        set_input_controller_pointer_authored_xy(1, 320f, 240f)
004386c1        runtime->player.track_z_offset = 320f
004386c7        runtime->player.track_z_anchor = 320f
004386cd        runtime->unknown_000000[0] = 1
004386d0        calc_subgame_rate(runtime)
004386d9        return
