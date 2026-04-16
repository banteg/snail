/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_subgame @ 0x4374b0 */

004374b3        int32_t i_3 = 0xc80
004374be        int32_t* eax = &arg1[0x3bfb0c]
004374df        int32_t i
004374c4        int32_t j_1 = 8
004374dc        int32_t j
004374c9        int32_t* edi_1 = eax
004374cd        eax = &eax[0x15]
004374d0        j = j_1
004374d0        j_1 -= 1
004374d1        *edi_1 = 0
004374d3        edi_1[1] = 0
004374d6        edi_1[2] = 0
004374d9        edi_1[3] = 0
004374dc        do while (j != 1)
004374de        i = i_3
004374de        i_3 -= 1
004374df        do while (i != 1)
004374e1        int32_t eax_1 = *(arg1 + 0x1270fc8)
004374f1        if (eax_1 == 2 || eax_1 == 1)
004374f3        void* var_30_1 = &data_4dfb08
004374f8        int32_t var_34_1 = 0
004374fe        cache_music_file("music/mainmenu.ogg")
00437516        int32_t eax_3 = load_landscape_script_by_name(data_4df904 + 0x106c218, "Menubg.txt")
00437522        void* eax_4 = data_4df904
00437535        change_backdrop(eax_4 + 0x4ec10, eax_4 + eax_3 * 0x124 + 0x106c7bc, 0)
0043754b        set_border_justify_centre(data_4df904 + 0xb4c, 0x41c80000)
00437550        int32_t eax_5 = *(arg1 + 0x40)
00437555        void* eax_9
00437555        if (eax_5 == 0)
0043757e        eax_9 = &arg1[0x68b4d0]
00437584        label_437584:
00437584        *(arg1 + 0x68b4c8) = eax_9
0043758d        *(arg1 + 0x355d94) = *(eax_9 + 4)
004375a1        __builtin_memcpy(&arg1[0x355d98], eax_9 + 8, 0x18)
00437558        if (eax_5 == 1)
00437567        eax_9 = &arg1[0x7e7b10]
0043756d        *(arg1 + 0x68b4c8) = eax_9
00437576        *(arg1 + 0x355d94) = *(eax_9 + 4)
004375a1        __builtin_memcpy(&arg1[0x355d98], eax_9 + 8, 0x18)
0043755d        if (eax_5 == 4)
0043755f        eax_9 = &arg1[0x944150]
00437565        goto label_437584
004375a9        if (arg1[0xff25d1] != 0)
004375b4        *(arg1 + 0x30) = *(*(arg1 + 0xff25d4) + 0x48)
004375bd        arg1[9] = 0
004375c0        arg1[8] = 0
004375c3        *(arg1 + 0xc) = 0
004375c6        *(arg1 + 0x10) = 0x3d088889
004375d2        *(arg1 + 0x3c) = 0
004375d5        *(arg1 + 0x1272828) = 0
0043760b        *(arg1 + 0x35bb88) = allocate_border(data_4df904 + 0xb4c)
00437611        struct Color4f color
00437611        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
00437633        initialize_frontend_widget(*(arg1 + 0x35bb88), &__dos_header.e_cblp, "0", 0x14, 400f, 14f, color_1, 3, 300f)
00437643        *(*(arg1 + 0x35bb88) + 0x6f0) = 0x3fc00000
00437653        *(*(arg1 + 0x35bb88) + 0x274) = 7
0043765f        *(*(arg1 + 0x35bb88) + 0x2cc) = 0
0043766a        if (*(arg1 + 0x40) == 0)
0043769c        *(arg1 + 0x35bb90) = allocate_border(data_4df904 + 0xb4c)
004376a2        struct Color4f* eax_15 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004376bb        initialize_frontend_sprite_button(*(arg1 + 0x35bb90), 0x400800, 0x7a, 0f, 58f, eax_15, 0f, 4)
004376c6        hide_border_init(*(arg1 + 0x35bb90))
004376d1        *(*(arg1 + 0x35bb90) + 0x178) = 0
00437702        *(arg1 + 0x35bb94) = allocate_border(data_4df904 + 0xb4c)
00437708        struct Color4f* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
0043772a        initialize_frontend_widget(*(arg1 + 0x35bb94), &__dos_header.e_cblp, "0", 0x14, 47f, 80f, color_2, 0, 0f)
00437735        hide_border_init(*(arg1 + 0x35bb94))
00437740        int32_t i_1 = 0
00437742        int32_t i_2 = 0
00437746        int32_t* esi_2 = &arg1[0x35bb98]
0043774c        __builtin_strncpy(*(arg1 + 0x35bb94) + 0x6f0, "333?", 4)
00437781        *esi_2 = allocate_border(data_4df904 + 0xb4c)
00437783        struct Color4f* eax_20
00437783        int32_t ecx_23
00437783        eax_20, ecx_23 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00437792        int32_t var_40_1 = ecx_23
004377ab        initialize_frontend_sprite_button(*esi_2, 0x400800, 0x7b, fconvert.s(float.t(i_2) * fconvert.t(24f) + fconvert.t(13f)), 430f, eax_20, 0f, 4)
004377b2        *(*esi_2 + 0x178) = 0
004377ba        hide_border_init(*esi_2)
004377bf        i_1 += 1
004377c0        esi_2 = &esi_2[1]
004377c6        i_2 = i_1
004377ca        do while (i_1 s< 9)
004377d1        int32_t eax_21 = *(arg1 + 0x40)
004377dc        if (*(arg1 + 0xf935bc) != eax_21)
00437818        if (eax_21 != 4)
00437830        border_add_text_number(*(arg1 + 0x35bb88), 0)
0043781e        zero_timer_counters()
004377f0        format_time_trial_string(&color)
00437802        sub_44e5b0(*(arg1 + 0x35bb88) + 0x2cc, 0x751478)
004377e1        if (eax_21 != 4)
00437830        border_add_text_number(*(arg1 + 0x35bb88), *(arg1 + 0xf93594))
004377f0        format_time_trial_string(&arg1[0xf93598])
00437802        sub_44e5b0(*(arg1 + 0x35bb88) + 0x2cc, 0x751478)
00437865        *(arg1 + 0x35bb8c) = allocate_border(data_4df904 + 0xb4c)
0043786b        struct Color4f* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
0043788d        initialize_frontend_widget(*(arg1 + 0x35bb8c), &__dos_header.e_cblp, "0", 0x14, 40f, 14f, color_3, 3, -71f)
00437898        *(*(arg1 + 0x35bb8c) + 0x6f0) = 0x3fc00000
004378a8        *(*(arg1 + 0x35bb8c) + 0x274) = 7
004378b4        *(*(arg1 + 0x35bb8c) + 0x2cc) = 0
004378c2        switch (*(arg1 + 0x40))
004378d6        case 0
004378d6        border_add_text_number(*(arg1 + 0x35bb8c), *(arg1 + 0x355d94))
004378ea        case 1
004378ea        border_add_text_number(*(arg1 + 0x35bb8c), *(arg1 + 0x355d94))
00437921        case 2, 3
00437921        hide_border_init(*(arg1 + 0x35bb8c))
0043792c        hide_border_init(*(arg1 + 0x35bb88))
004378fe        case 4
004378fe        format_time_trial_string(&arg1[0x355d98])
00437911        sub_44e5b0(*(arg1 + 0x35bb8c) + 0x2cc, 0x751478)
00437931        void* result = data_4df904
00437941        if (*(result + 0x4f2e0) != 0 || *(arg1 + 0x40) == 7)
00437949        hide_border_init(*(arg1 + 0x35bb8c))
00437954        hide_border_init(*(arg1 + 0x35bb88))
00437959        result = data_4df904
00437964        if (*(result + 0x30d) != 0)
00437ad8        return result
0043796a        *(result + 0x30d) = 0
00437980        *(data_4df904 + 0x310) = 0
00437986        load_builtin_segment_definitions(&arg1[0x1b01ec], 0x4a63d0)
00437991        set_matrix_identity(&arg1[0x3bb79c])
004379a2        *(arg1 + 0x3bbb70) = 0
004379a8        *(arg1 + 0x3bbb6c) = arg1
004379ae        int32_t eax_29 = *(arg1 + 0x3bb7cc)
004379b0        arg1[0x3bbb81] = 0
004379b6        *(arg1 + 0x3be0c8) = eax_29
004379b8        arg1[0x3bbb80] = 0
004379be        int32_t eax_30 = *(arg1 + 0x3bb7d0)
004379c1        *(arg1 + 0x3bbb68) = 0
004379c7        *(arg1 + 0x3be0cc) = eax_30
004379cd        *(arg1 + 0x3be0d0) = *(arg1 + 0x3bb7d4)
004379df        *(arg1 + 0x3bb768) &= 0xffffffdf
004379e5        initialize_warning(&arg1[0x3bbb58])
004379ea        int32_t eax_31 = *(arg1 + 0x1270fc8)
004379fb        if (eax_31 != 0 && eax_31 != 3)
00437a07        if (arg1[0xff25d1] == 0)
00437a18        switch (*(arg1 + 0x40))
00437a22        case 0
00437a22        if (eax_31 == 1)
00437a27        int32_t edx_16 = *(arg1 + 0x44) + 1
00437a28        *(arg1 + 0x44) = edx_16
00437a35        if (edx_16 s> data_4df9b8)
00437a46        data_4df9b8 = edx_16
00437a4b        save_config_file("SnailMail.cfg", &data_4df918, 0xc4)
00437a56        data_4df9bc = *(arg1 + 0x44)
00437a62        initialize_galaxy(&arg1[0x1260020])
00437a75        return reset_subgame(arg1)
00437a7c        case 1
00437a7c        initialize_challenge_setup_screen(&arg1[0x125ffe0])
00437a8f        return reset_subgame(arg1)
00437a62        case 4
00437a62        initialize_galaxy(&arg1[0x1260020])
00437a75        return reset_subgame(arg1)
00437a92        case 7
00437a92        *(arg1 + 0x3c) = 0
00437aa1        return reset_subgame(arg1)
00437aa7        report_errorf("Unknown game mode")
00437abd        return reset_subgame(arg1)
00437ac7        *(arg1 + 0x30) = *(*(arg1 + 0xff25d4) + 0x48)
00437acc        return reset_subgame(arg1)
