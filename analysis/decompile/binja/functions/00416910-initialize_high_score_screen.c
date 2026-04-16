/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_high_score_screen @ 0x416910 */

0041691e        *(arg1 + 8) = arg2
0041692b        *(arg1 + 0x14) = arg3
0041692e        if (arg3 != 0xffffffff)
00416936        *(arg1 + 0x10) = 1
00416930        *(arg1 + 0x10) = 0
00416946        hide_star_field(data_4df904 + 0x4f33c)
00416957        hide_gameplay_scores(data_4df904 + 0x74618)
0041695c        void* __saved_ebx = &data_4dfb08
00416961        int32_t __saved_edi = 0
00416968        cache_music_file("music/mainmenu.ogg")
00416980        int32_t eax_2 = load_landscape_script_by_name(data_4df904 + 0x106c218, "Menubg.txt")
0041698d        void* eax_3 = data_4df904
004169a0        change_backdrop(eax_3 + 0x4ec10, eax_3 + eax_2 * 0x124 + 0x106c7bc, 0)
004169b6        set_border_justify_centre(data_4df904 + 0xb4c, 0x41c80000)
004169c6        capture_mouse_cursor(data_4df904 + 0x290)
004169dc        *(arg1 + 0x18) = allocate_border(data_4df904 + 0xb4c)
004169df        int32_t eax_6 = *(arg1 + 8)
004169e5        float var_c4
004169e5        struct Color4f color_2
004169e5        struct Color4f color_3
004169e5        void* eax_8
004169e5        if (eax_6 == 0)
00416a66        struct Color4f* color_14 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00416a7f        initialize_frontend_widget(*(arg1 + 0x18), 0, "Postal High Scores", 0x17, 0f, 64f, color_14, 2, 0f)
00416a84        eax_8 = data_4df904
00416a8f        *(eax_8 + 0x6ffae0) = eax_8 + 0x6ffae8
00416a9b        *(data_4df904 + 0x6ffae4) = 0xa
00416aa5        var_c4 = 27f
004169e8        if (eax_6 == 1)
00416a0a        struct Color4f* color_13 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00416a23        initialize_frontend_widget(*(arg1 + 0x18), 0, "Challenge High Scores", 0x17, 0f, 64f, color_13, 2, 0f)
00416a28        void* eax_9 = data_4df904
00416a33        *(eax_9 + 0x6ffae0) = eax_9 + 0x85c128
00416a3e        *(data_4df904 + 0x6ffae4) = 0xa
00416aa5        var_c4 = 27f
00416aad        eax_8.b = *(arg1 + 0x10)
00416ab2        if (eax_8.b != 0)
00416ac2        sub_44e5b0(*(arg1 + 0x18) + 0x2cc, "Enter your name here!")
00416acd        layout_frontend_widget(*(arg1 + 0x18))
00416ad3        int32_t ebx = 0
00416ad5        int32_t i = 0
00416ad8        int32_t var_cc = 0
00416adc        int32_t i_1 = 0
00416ae0        int32_t* esi = arg1 + 0x7c
00417043        struct Color4f color_1
00417043        struct Color4f color_4
00416ae3        esi[0x14] = 0
00416af1        int32_t ecx_17
00416af1        ecx_17.b = ebx != *(arg1 + 0x14)
00416af5        int32_t ecx_19 = (ecx_17 - 1) & 2
00416afa        void* ecx_20 = data_4df904
00416b0a        if (*(*(ecx_20 + 0x6ffae0) + i) == 1)
00416b10        int32_t eax_12 = *(arg1 + 8)
00416b16        if (eax_12 == 0)
00416d79        float y_2 = fconvert.s(float.t(var_cc) * fconvert.t(var_c4) + fconvert.t(111f))
00416da4        esi[-0x14] = allocate_border(ecx_20 + 0xb4c)
00416da7        struct Color4f color_7
00416da7        struct Color4f* color_20 = set_color_rgba(&color_7, 1f, 1f, 1f, 1f)
00416dc6        initialize_frontend_widget(esi[-0x14], ecx_19 | 0x20000000, "                                               ", 0x16, 0f, y_2, color_20, 1, -228f)
00416e00        esi[-0xa] = allocate_border(data_4df904 + 0xb4c)
00416e03        uint32_t widget_flags_1 = ecx_19 | 0x20400000
00416e09        struct Color4f color_11
00416e09        struct Color4f* color_21 = set_color_rgba(&color_11, 1f, 1f, 1f, 1f)
00416e21        initialize_frontend_widget(esi[-0xa], widget_flags_1, &data_4dfb08, 0x16, 0f, y_2, color_21, 1, -222f)
00416e2f        border_add_text_number(esi[-0xa], var_cc + 1)
00416e37        layout_frontend_widget(esi[-0xa])
00416e6f        *esi = allocate_border(data_4df904 + 0xb4c)
00416e71        struct Color4f color_9
00416e71        struct Color4f* color_22 = set_color_rgba(&color_9, 1f, 1f, 1f, 1f)
00416e97        initialize_frontend_widget(*esi, widget_flags_1, *(data_4df904 + 0x6ffae0) + i_1 + 0x54, 0x16, 0f, y_2, color_22, 1, -180f)
00416ea5        if (var_cc == *(arg1 + 0x14))
00416eb2        border_input_text_init(*esi, 0x10, &data_4df978, 0x10)
00416eb7        void* eax_40 = *esi
00416ebf        int32_t ecx_68
00416ebf        ecx_68:1.b = (*(eax_40 + 0x1a0)):1.b | 0x20
00416ec2        *(eax_40 + 0x1a0) = ecx_68
00416eca        layout_frontend_widget(*esi)
00416f02        esi[0xa] = allocate_border(data_4df904 + 0xb4c)
00416f05        struct Color4f color_6
00416f05        struct Color4f* color_23 = set_color_rgba(&color_6, 1f, 1f, 1f, 1f)
00416f1d        initialize_frontend_widget(esi[0xa], widget_flags_1, &data_4dfb08, 0x16, 0f, y_2, color_23, 3, 160f)
00416f3a        border_add_text_number(esi[0xa], *(*(data_4df904 + 0x6ffae0) + i_1 + 4))
00416f42        layout_frontend_widget(esi[0xa])
00416f7a        esi[0x14] = allocate_border(data_4df904 + 0xb4c)
00416f7d        struct Color4f color_8
00416f7d        struct Color4f* color_24 = set_color_rgba(&color_8, 1f, 1f, 1f, 1f)
00416f9b        initialize_frontend_widget(esi[0x14], ecx_19 | 0x20000014, "Replay", 0x16, 0f, y_2, color_24, 2, 125f)
00416fa3        hide_border_init(esi[0x14])
00416b1d        if (eax_12 == 1)
00416b37        float y_1 = fconvert.s(float.t(var_cc) * fconvert.t(var_c4) + fconvert.t(111f))
00416b5f        esi[-0x14] = allocate_border(ecx_20 + 0xb4c)
00416b62        struct Color4f* color_15 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00416b82        initialize_frontend_widget(esi[-0x14], ecx_19 | 0x20000000, "                                           ", 0x16, 0f, y_1, color_15, 1, -228f)
00416bb9        esi[-0xa] = allocate_border(data_4df904 + 0xb4c)
00416bbc        uint32_t widget_flags = ecx_19 | 0x20400000
00416bc2        struct Color4f* color_16 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00416bda        initialize_frontend_widget(esi[-0xa], widget_flags, &data_4dfb08, 0x16, 0f, y_1, color_16, 1, -222f)
00416be8        border_add_text_number(esi[-0xa], var_cc + 1)
00416bf0        layout_frontend_widget(esi[-0xa])
00416c28        *esi = allocate_border(data_4df904 + 0xb4c)
00416c2a        struct Color4f color_10
00416c2a        struct Color4f* color_17 = set_color_rgba(&color_10, 1f, 1f, 1f, 1f)
00416c51        initialize_frontend_widget(*esi, widget_flags, *(data_4df904 + 0x6ffae0) + i_1 + 0x54, 0x16, 0f, y_1, color_17, 1, -180f)
00416c5f        if (var_cc == *(arg1 + 0x14))
00416c6c        border_input_text_init(*esi, 0x10, &data_4df978, 0x10)
00416c71        void* eax_23 = *esi
00416c79        int32_t ecx_39
00416c79        ecx_39:1.b = (*(eax_23 + 0x1a0)):1.b | 0x20
00416c7c        *(eax_23 + 0x1a0) = ecx_39
00416c84        layout_frontend_widget(*esi)
00416cb8        esi[0xa] = allocate_border(data_4df904 + 0xb4c)
00416cbb        struct Color4f color_5
00416cbb        struct Color4f* color_18 = set_color_rgba(&color_5, 1f, 1f, 1f, 1f)
00416cd3        initialize_frontend_widget(esi[0xa], widget_flags, &data_4dfb08, 0x16, 0f, y_1, color_18, 3, 125f)
00416cf0        border_add_text_number(esi[0xa], *(*(data_4df904 + 0x6ffae0) + i_1 + 4))
00416cf8        layout_frontend_widget(esi[0xa])
00416d2f        esi[0x14] = allocate_border(data_4df904 + 0xb4c)
00416d32        struct Color4f color_12
00416d32        struct Color4f* color_19 = set_color_rgba(&color_12, 1f, 1f, 1f, 1f)
00416d50        initialize_frontend_widget(esi[0x14], ecx_19 | 0x20000014, "Replay", 0x16, 0f, y_1, color_19, 2, 170f)
00416d5a        if (*(arg1 + 0x10) != 0)
00416fa3        hide_border_init(esi[0x14])
00416fa8        ebx = var_cc
00416faf        if ((ebx.b & 1) != 0)
00416fc9        struct Color4f* eax_46 = set_color_rgba(&color_4, 0.329411775f, 0.184313729f, 0.419607848f, 0.699999988f)
00416fd3        float* ecx_83 = esi[-0x14] + 0x1bc
00416fe8        *ecx_83 = eax_46->r
00416ff2        ecx_83[1] = eax_46->g
00416ff8        ecx_83[2] = eax_46->b
00416ffe        ecx_83[3] = eax_46->a
00417005        struct Color4f* eax_48 = set_color_rgba(&color_1, 0.329411775f, 0.184313729f, 0.419607848f, 0.699999988f)
0041700f        float* ecx_86 = esi[0x14] + 0x1bc
00417015        *ecx_86 = eax_48->r
0041701a        ecx_86[1] = eax_48->g
00417020        ecx_86[2] = eax_48->b
00417026        ecx_86[3] = eax_48->a
0041702d        ebx += 1
0041702e        i = i_1 + 0x1fac0
00417033        esi = &esi[1]
0041703b        var_cc = ebx
0041703f        i_1 = i
00417043        do while (i s< 0x13cb80)
00417053        i.b = *(arg1 + 0x10)
00417060        float y_3 = fconvert.s(fconvert.t(var_c4) * fconvert.t(10f) + fconvert.t(111f))
00417064        if (i.b != 0)
0041709a        *(arg1 + 0x24) = allocate_border(data_4df904 + 0xb4c)
0041709d        struct Color4f* color_25 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
004170b9        initialize_frontend_widget(*(arg1 + 0x24), 0x20000014, "Cancel", 0x17, 0f, y_3, color_25, 2, -110f)
004170c3        sub_402790(*(arg1 + 0x24), 0xb)
004170f8        *(arg1 + 0x28) = allocate_border(data_4df904 + 0xb4c)
004170fb        struct Color4f* color_26 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00417113        initialize_frontend_widget(*(arg1 + 0x28), 0x20000014, "Submit", 0x17, 0f, y_3, color_26, 2, 55f)
0041712a        return sub_402790(*(arg1 + 0x28), 5)
0041715c        *(arg1 + 0x1c) = allocate_border(data_4df904 + 0xb4c)
0041715f        struct Color4f* color_27 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
0041717b        initialize_frontend_widget(*(arg1 + 0x1c), 0x20000014, "Back", 0x17, 0f, y_3, color_27, 2, -132f)
00417191        *(arg1 + 0x20) = allocate_border(data_4df904 + 0xb4c)
00417194        int32_t eax_57 = *(arg1 + 8)
0041719a        char* text
0041719a        float y
0041719a        struct Color4f* color
0041719a        if (eax_57 == 0)
004171d0        int32_t __saved_ebx_2 = 0x42040000
004171d5        int32_t __saved_edi_4 = 2
004171f4        color = set_color_rgba(&color_4, 1f, 1f, 1f, 1f)
004171f5        y = y_3
004171f6        int32_t var_ec_12 = 0
004171f8        int32_t var_f0_12 = 0x17
004171fa        text = "Challenge Scores"
0041719d        if (eax_57 != 1)
00417214        return eax_57 - 1
0041719f        int32_t __saved_ebx_1 = 0x42040000
004171a4        int32_t __saved_edi_3 = 2
004171c3        color = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
004171c4        y = y_3
004171c5        int32_t var_ec_11 = 0
004171c7        int32_t var_f0_11 = 0x17
004171c9        text = "Postal Scores"
00417207        return initialize_frontend_widget(*(arg1 + 0x20), 0x20000014, text, 0x17, 0f, y, color, 2, 33f)
