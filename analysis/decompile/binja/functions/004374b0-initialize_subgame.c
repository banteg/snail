/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgame @ 0x4374b0 */

004374b3        int32_t i_3 = 0xc80
004374be        void* __offset(Game, 0x3bfb0c) eax = &game->__offset(0x3bfb0c).d
004374df        int32_t i
004374c4        int32_t j_1 = 8
004374dc        int32_t j
004374c9        void* __offset(Game, 0x3bfb0c) edi_1 = eax
004374cd        eax += 0x54
004374d0        j = j_1
004374d0        j_1 -= 1
004374d1        (edi_1 - 0x3bfb0c)->__offset(0x3bfb0c).d = 0
004374d3        (edi_1 - 0x3bfb0c)->__offset(0x3bfb10).d = 0
004374d6        (edi_1 - 0x3bfb0c)->__offset(0x3bfb14).d = 0
004374d9        (edi_1 - 0x3bfb0c)->__offset(0x3bfb18).d = 0
004374dc        do while (j != 1)
004374de        i = i_3
004374de        i_3 -= 1
004374df        do while (i != 1)
004374e1        int32_t subgame_rebuild_selector = game->subgame_rebuild_selector
004374f1        if (subgame_rebuild_selector == 2 || subgame_rebuild_selector == 1)
004374f3        void* var_30_1 = &data_4dfb08
004374f8        int32_t var_34_1 = 0
004374fe        cache_music_file("music/mainmenu.ogg")
00437516        int32_t eax_2 = load_landscape_script_by_name(data_4df904 + 0x106c218, "Menubg.txt")
00437522        void* eax_3 = data_4df904
00437535        change_backdrop(eax_3 + 0x4ec10, eax_3 + eax_2 * 0x124 + 0x106c7bc, 0)
0043754b        set_border_justify_centre(data_4df904 + 0xb4c, 0x41c80000)
00437550        int32_t level_mode = game->level_mode
00437555        void* __offset(Game, 0x944150) eax_7
00437555        if (level_mode == 0)
0043757e        eax_7 = &game->__offset(0x68b4d0).d
00437584        label_437584:
00437584        game->__offset(0x68b4c8).d = eax_7
0043758d        game->__offset(0x355d94).d = (eax_7 - 0x944150)->__offset(0x944154).d
004375a1        __builtin_memcpy(&game->__offset(0x355d98).d, eax_7 + 8, 0x18)
00437558        if (level_mode == 1)
00437567        eax_7 = &game->__offset(0x7e7b10).d
0043756d        game->__offset(0x68b4c8).d = eax_7
00437576        game->__offset(0x355d94).d = (eax_7 - 0x944150)->__offset(0x944154).d
004375a1        __builtin_memcpy(&game->__offset(0x355d98).d, eax_7 + 8, 0x18)
0043755d        if (level_mode == 4)
0043755f        eax_7 = &game->__offset(0x944150).d
00437565        goto label_437584
004375a9        if (game->selected_level_record_persistent != 0)
004375b1        float replay_speed_scalar = game->selected_level_record->replay_speed_scalar
004375b4        game->_pad_00[0x30] = replay_speed_scalar.b
004375b4        game->_pad_00[0x31] = replay_speed_scalar:1.b
004375b4        game->_pad_00[0x32] = replay_speed_scalar:2.b
004375b4        game->_pad_00[0x33] = replay_speed_scalar:3.b
004375bd        game->_pad_00[9] = 0
004375c0        game->_pad_00[8] = 0
004375c3        game->_pad_00[0xc] = 0
004375c3        game->_pad_00[0xd] = 0
004375c3        game->_pad_00[0xe] = 0
004375c3        game->_pad_00[0xf] = 0
004375c6        game->_pad_00[0x10] = 0x89
004375c6        game->_pad_00[0x11] = 0x88
004375c6        game->_pad_00[0x12] = 8
004375c6        game->_pad_00[0x13] = 0x3d
004375d2        game->subgame_state = 0
004375d5        game->times_up.state = 0
0043760b        game->__offset(0x35bb88).d = allocate_border(data_4df904 + 0xb4c)
00437611        struct Color4f color
00437611        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00437633        initialize_frontend_widget(game->__offset(0x35bb88).d, &__dos_header.e_cblp, "0", 0x14, 400f, 14f, color_1, 3, 300f)
00437643        *(game->__offset(0x35bb88).d + 0x6f0) = 0x3fc00000
00437653        *(game->__offset(0x35bb88).d + 0x274) = 7
0043765f        *(game->__offset(0x35bb88).d + 0x2cc) = 0
0043766a        if (game->level_mode == 0)
0043769c        game->__offset(0x35bb90).d = allocate_border(data_4df904 + 0xb4c)
004376a2        struct Color4f* eax_12 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004376bb        initialize_frontend_sprite_button(game->__offset(0x35bb90).d, 0x400800, 0x7a, 0f, 58f, eax_12, 0f, 4)
004376c6        hide_border_init(game->__offset(0x35bb90).d)
004376d1        *(game->__offset(0x35bb90).d + 0x178) = 0
00437702        game->__offset(0x35bb94).d = allocate_border(data_4df904 + 0xb4c)
00437708        struct Color4f* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
0043772a        initialize_frontend_widget(game->__offset(0x35bb94).d, &__dos_header.e_cblp, "0", 0x14, 47f, 80f, color_2, 0, 0f)
00437735        hide_border_init(game->__offset(0x35bb94).d)
00437740        int32_t i_1 = 0
00437742        int32_t i_2 = 0
00437746        void* __offset(Game, 0x35bb98) esi_2 = &game->__offset(0x35bb98).d
0043774c        __builtin_strncpy(game->__offset(0x35bb94).d + 0x6f0, "333?", 4)
00437781        (esi_2 - 0x35bb98)->__offset(0x35bb98).d = allocate_border(data_4df904 + 0xb4c)
00437783        struct Color4f* eax_17
00437783        int32_t ecx_23
00437783        eax_17, ecx_23 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00437792        int32_t var_40_1 = ecx_23
004377ab        initialize_frontend_sprite_button((esi_2 - 0x35bb98)->__offset(0x35bb98).d, 0x400800, 0x7b, fconvert.s(float.t(i_2) * fconvert.t(24f) + fconvert.t(13f)), 430f, eax_17, 0f, 4)
004377b2        *((esi_2 - 0x35bb98)->__offset(0x35bb98).d + 0x178) = 0
004377ba        hide_border_init((esi_2 - 0x35bb98)->__offset(0x35bb98).d)
004377bf        i_1 += 1
004377c0        esi_2 += 4
004377c6        i_2 = i_1
004377ca        do while (i_1 s< 9)
004377d1        int32_t level_mode_1 = game->level_mode
004377dc        if (game->__offset(0xf935bc).d != level_mode_1)
00437818        if (level_mode_1 != 4)
00437830        border_add_text_number(game->__offset(0x35bb88).d, 0)
0043781e        zero_timer_counters()
004377f0        format_time_trial_string(&color)
00437802        rstrcpy_checked_ascii(game->__offset(0x35bb88).d + 0x2cc, 0x751478)
004377e1        if (level_mode_1 != 4)
00437830        border_add_text_number(game->__offset(0x35bb88).d, game->__offset(0xf93594).d)
004377f0        format_time_trial_string(&game->__offset(0xf93598).d)
00437802        rstrcpy_checked_ascii(game->__offset(0x35bb88).d + 0x2cc, 0x751478)
00437865        game->__offset(0x35bb8c).d = allocate_border(data_4df904 + 0xb4c)
0043786b        struct Color4f* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
0043788d        initialize_frontend_widget(game->__offset(0x35bb8c).d, &__dos_header.e_cblp, "0", 0x14, 40f, 14f, color_3, 3, -71f)
00437898        *(game->__offset(0x35bb8c).d + 0x6f0) = 0x3fc00000
004378a8        *(game->__offset(0x35bb8c).d + 0x274) = 7
004378b4        *(game->__offset(0x35bb8c).d + 0x2cc) = 0
004378c2        switch (game->level_mode)
004378d6        case 0
004378d6        border_add_text_number(game->__offset(0x35bb8c).d, game->__offset(0x355d94).d)
004378ea        case 1
004378ea        border_add_text_number(game->__offset(0x35bb8c).d, game->__offset(0x355d94).d)
00437921        case 2, 3
00437921        hide_border_init(game->__offset(0x35bb8c).d)
0043792c        hide_border_init(game->__offset(0x35bb88).d)
004378fe        case 4
004378fe        format_time_trial_string(&game->__offset(0x355d98).d)
00437911        rstrcpy_checked_ascii(game->__offset(0x35bb8c).d + 0x2cc, 0x751478)
00437931        void* eax_24 = data_4df904
00437941        if (*(eax_24 + 0x4f2e0) != 0 || game->level_mode == 7)
00437949        hide_border_init(game->__offset(0x35bb8c).d)
00437954        hide_border_init(game->__offset(0x35bb88).d)
00437959        eax_24 = data_4df904
00437964        if (*(eax_24 + 0x30d) != 0)
00437964        return 
0043796a        *(eax_24 + 0x30d) = 0
00437980        *(data_4df904 + 0x310) = 0
00437986        load_builtin_segment_definitions(&game->__offset(0x1b01ec).d, 0x4a63d0)
00437991        set_matrix_identity(&game->__offset(0x3bb79c).d)
004379a2        game->__offset(0x3bbb70).d = 0
004379a8        game->__offset(0x3bbb6c).d = game
004379ae        int32_t eax_26
004379ae        eax_26.b = game->__offset(0x3bb7cc).b
004379ae        eax_26:1.b = game->__offset(0x3bb7cd).b
004379ae        eax_26:2.b = game->__offset(0x3bb7ce).b
004379ae        eax_26:3.b = game->__offset(0x3bb7cf).b
004379b0        game->__offset(0x3bbb81).b = 0
004379b6        game->__offset(0x3be0c8).d = eax_26
004379b8        game->__offset(0x3bbb80).b = 0
004379be        int32_t eax_27
004379be        eax_27.b = game->__offset(0x3bb7d0).b
004379be        eax_27:1.b = game->__offset(0x3bb7d1).b
004379be        eax_27:2.b = game->__offset(0x3bb7d2).b
004379be        eax_27:3.b = game->__offset(0x3bb7d3).b
004379c1        game->__offset(0x3bbb68).d = 0
004379c7        game->__offset(0x3be0cc).d = eax_27
004379ca        int32_t ecx_47
004379ca        ecx_47.b = game->__offset(0x3bb7d4).b
004379ca        ecx_47:1.b = game->__offset(0x3bb7d5).b
004379ca        ecx_47:2.b = game->__offset(0x3bb7d6).b
004379ca        ecx_47:3.b = game->__offset(0x3bb7d7).b
004379cd        game->__offset(0x3be0d0).d = ecx_47
004379df        game->__offset(0x3bb768).d &= 0xffffffdf
004379e5        initialize_warning(&game->warning_actor)
004379ea        int32_t subgame_rebuild_selector_1 = game->subgame_rebuild_selector
004379fb        if (subgame_rebuild_selector_1 != 0 && subgame_rebuild_selector_1 != 3)
00437a07        if (game->selected_level_record_persistent == 0)
00437a18        switch (game->level_mode)
00437a22        case 0
00437a22        if (subgame_rebuild_selector_1 == 1)
00437a27        int32_t edx_16 = game->level_mode_arg + 1
00437a28        game->level_mode_arg = edx_16
00437a35        if (edx_16 s> data_4df9b8)
00437a46        data_4df9b8 = edx_16
00437a4b        save_config_file("SnailMail.cfg", &data_4df918, 0xc4)
00437a56        data_4df9bc = game->level_mode_arg
00437a22        goto label_437a62
00437a7c        case 1
00437a7c        initialize_challenge_setup_screen(&game->__offset(0x125ffe0).d)
00437a83        reset_subgame(game)
00437a8f        return 
00437a62        case 4
00437a62        label_437a62:
00437a62        initialize_galaxy(&game->__offset(0x1260020).d)
00437a69        reset_subgame(game)
00437a75        return 
00437a92        case 7
00437a92        game->subgame_state = 0
00437a95        reset_subgame(game)
00437aa1        return 
00437aa7        report_errorf("Unknown game mode")
00437ab1        reset_subgame(game)
00437abd        return 
00437ac4        float replay_speed_scalar_1 = game->selected_level_record->replay_speed_scalar
00437ac7        game->_pad_00[0x30] = replay_speed_scalar_1.b
00437ac7        game->_pad_00[0x31] = replay_speed_scalar_1:1.b
00437ac7        game->_pad_00[0x32] = replay_speed_scalar_1:2.b
00437ac7        game->_pad_00[0x33] = replay_speed_scalar_1:3.b
00437acc        reset_subgame(game)
00437ad8        return
