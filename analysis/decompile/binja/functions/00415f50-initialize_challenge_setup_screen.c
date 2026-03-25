/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_challenge_setup_screen @ 0x415f50 */

00415f61        capture_mouse_cursor(data_4df904 + 0x290)
00415f66        void* eax = *arg1
00415f76        load_frontend_level_by_mode_and_index(eax + 0xa874, *(eax + 0x40), *(eax + 0x44))
00415f7d        int32_t eax_2 = *(*arg1 + 0x40)
00415f81        if (eax_2 != 1)
004161e5        return eax_2 - 1
00415f98        int32_t var_5c_1 = 0
00415fb4        arg1[8] = allocate_border(data_4df904 + 0xb4c)
00415fb7        struct Color4f color
00415fb7        struct Color4f* eax_5 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00415fd6        initialize_frontend_widget(arg1[8], 0x100004, "     Select Difficulty     >", 0x14, 0x41a00000, 80f, eax_5, 2.80259693e-45f)
00415fea        *(arg1[8] + 0x17c) = fconvert.s(float.t(data_4df960) * fconvert.t(0.00999999978f))
00415ff0        void* eax_6 = arg1[8]
00415ff9        *(eax_6 + 0x180) = *(eax_6 + 0x17c)
00416004        (**arg1[8])()
00416016        int32_t var_5c_2 = 0
00416032        arg1[7] = allocate_border(data_4df904 + 0xb4c)
00416035        struct Color4f color_1
00416035        struct Color4f* eax_9 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00416054        initialize_frontend_widget(arg1[7], 0x100004, "       Select Speed       >", 0x14, 0x41a00000, 145f, eax_9, 2.80259693e-45f)
00416068        *(arg1[7] + 0x17c) = fconvert.s(float.t(data_4df958) * fconvert.t(0.00999999978f))
0041606e        void* eax_10 = arg1[7]
00416077        *(eax_10 + 0x180) = *(eax_10 + 0x17c)
00416084        stack_widget_below(arg1[7], arg1[8])
0041608e        (**arg1[7])()
00416092        int32_t var_54_1 = 0
004160a1        if (*(*arg1 + 0xfb3050) == 1)
004160a3        var_54_1 = 0x42c80000
004160c4        int32_t var_5c_4 = var_54_1
004160db        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004160de        struct Color4f color_2
004160de        struct Color4f* eax_14 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
004160fd        initialize_frontend_widget(arg1[4], 0x40000016, "Play", 0x14, 0x41a00000, 250f, eax_14, 2.80259693e-45f)
00416109        stack_widget_below(arg1[4], arg1[7])
0041611f        int32_t var_5c_6 = 0xc2c80000
0041613e        arg1[9] = allocate_border(data_4df904 + 0xb4c)
00416141        struct Color4f color_3
00416141        struct Color4f* eax_17 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00416160        initialize_frontend_widget(arg1[9], 0x40000016, "Watch Replay", 0x14, 0x41a00000, 70f, eax_17, 2.80259693e-45f)
0041616c        stack_widget_below(arg1[9], arg1[7])
0041617a        if (*(*arg1 + 0xfb3050) != 1)
0041617f        hide_border_init(arg1[9])
00416195        int32_t var_5c_8 = 0
004161b1        arg1[6] = allocate_border(data_4df904 + 0xb4c)
004161b4        struct Color4f color_4
004161b4        struct Color4f* eax_20 = set_color_rgba(&color_4, 1f, 1f, 1f, 1f)
004161d0        initialize_frontend_widget(arg1[6], 0x16, "Back", 0x14, 0x41a00000, 20f, eax_20, 2.80259693e-45f)
004161dc        return stack_widget_below(arg1[6], arg1[9])
