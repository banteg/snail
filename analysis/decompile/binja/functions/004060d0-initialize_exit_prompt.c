/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_exit_prompt @ 0x4060d0 */

004060e4        hide_all_borders(data_4df904 + 0xb4c)
004060eb        int32_t result = *arg1 - 2
004060f7        struct Color4f* color
004060f7        struct Color4f* color_1
004060f7        switch (result)
004063dd        case 0, 5
004063dd        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004063e0        struct Color4f color_11
004063e0        struct Color4f* color_27 = set_color_rgba(&color_11, 1f, 1f, 1f, 1f)
004063fc        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0f, 200f, color_27, 2, 0f)
00406431        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406434        struct Color4f color_2
00406434        struct Color4f* color_28 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00406450        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0f, 330f, color_28, 2, -80f)
0040645c        stack_widget_below(arg1[5], arg1[4])
00406471        int32_t var_138_7 = 0x42a00000
00406476        int32_t var_13c_3 = 2
00406490        arg1[6] = allocate_border(data_4df904 + 0xb4c)
00406498        struct Color4f color_4
00406498        color_1 = set_color_rgba(&color_4, 1f, 1f, 1f, 1f)
004064ac        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0f, 330f, color_1, 2, 80f)
004064c4        return stack_widget_below(arg1[6], arg1[4])
004064f2        case 1
004064f2        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004064f5        struct Color4f color_6
004064f5        struct Color4f* color_29 = set_color_rgba(&color_6, 1f, 1f, 1f, 1f)
00406511        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0f, 200f, color_29, 2, 0f)
00406545        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406548        struct Color4f color_8
00406548        struct Color4f* color_30 = set_color_rgba(&color_8, 1f, 1f, 1f, 1f)
00406564        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0f, 330f, color_30, 2, -80f)
00406570        stack_widget_below(arg1[5], arg1[4])
004065a8        arg1[6] = allocate_border(data_4df904 + 0xb4c)
004065ab        struct Color4f color_10
004065ab        struct Color4f* color_31 = set_color_rgba(&color_10, 1f, 1f, 1f, 1f)
004065c4        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0f, 330f, color_31, 2, 80f)
004065dc        return stack_widget_below(arg1[6], arg1[4])
0040660d        case 2
0040660d        arg1[4] = allocate_border(data_4df904 + 0xb4c)
00406610        struct Color4f color_12
00406610        struct Color4f* color_32 = set_color_rgba(&color_12, 1f, 1f, 1f, 1f)
0040662c        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0f, 200f, color_32, 2, 0f)
00406664        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406667        struct Color4f color_14
00406667        struct Color4f* color_33 = set_color_rgba(&color_14, 1f, 1f, 1f, 1f)
00406686        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 468f, 373f, color_33, 2, -80f)
00406692        stack_widget_below(arg1[5], arg1[4])
004066ca        arg1[6] = allocate_border(data_4df904 + 0xb4c)
004066cd        struct Color4f color_16
004066cd        struct Color4f* color_34 = set_color_rgba(&color_16, 1f, 1f, 1f, 1f)
004066e9        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 568f, 296f, color_34, 2, 80f)
00406701        return stack_widget_below(arg1[6], arg1[4])
00406731        case 3
00406731        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406734        struct Color4f color_18
00406734        struct Color4f* color_35 = set_color_rgba(&color_18, 1f, 1f, 1f, 1f)
00406750        initialize_frontend_widget(arg1[5], 0x14, "Yes", 0x14, 473f, 33f, color_35, 0, 0f)
00406785        arg1[6] = allocate_border(data_4df904 + 0xb4c)
0040678d        struct Color4f color_20
0040678d        color = set_color_rgba(&color_20, 1f, 1f, 1f, 1f)
004067a4        return initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 566f, 108f, color, 0, 0f)
0040612e        case 7
0040612e        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406131        struct Color4f color_3
00406131        struct Color4f* color_21
00406131        int32_t ecx_4
00406131        color_21, ecx_4 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00406140        int32_t var_144_1 = ecx_4
00406152        initialize_frontend_widget(arg1[5], 0x14, "Yes", 0x14, 0f, fconvert.s(fconvert.t(arg1[3]) - fconvert.t(54f)), color_21, 2, 140f)
0040618a        arg1[6] = allocate_border(data_4df904 + 0xb4c)
00406192        struct Color4f color_19
00406192        color = set_color_rgba(&color_19, 1f, 1f, 1f, 1f)
004067a4        return initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0f, arg1[3], color, 2, 268f)
004061cb        case 8
004061cb        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004061ce        struct Color4f color_5
004061ce        struct Color4f* color_22 = set_color_rgba(&color_5, 1f, 1f, 1f, 1f)
004061ea        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0f, 200f, color_22, 2, 0f)
00406222        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406225        struct Color4f color_13
00406225        struct Color4f* color_23 = set_color_rgba(&color_13, 1f, 1f, 1f, 1f)
00406240        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0f, arg1[3], color_23, 2, -80f)
0040624c        stack_widget_below(arg1[5], arg1[4])
00406262        int32_t var_138_3 = 0x42a00000
00406267        int32_t var_13c_2 = 2
00406281        arg1[6] = allocate_border(data_4df904 + 0xb4c)
00406289        struct Color4f color_7
00406289        color_1 = set_color_rgba(&color_7, 1f, 1f, 1f, 1f)
004064ac        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0f, arg1[3], color_1, 2, 80f)
004064c4        return stack_widget_below(arg1[6], arg1[4])
004062c3        case 9
004062c3        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004062c6        struct Color4f color_17
004062c6        struct Color4f* color_24 = set_color_rgba(&color_17, 1f, 1f, 1f, 1f)
004062e2        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0f, 200f, color_24, 2, 0f)
00406319        arg1[5] = allocate_border(data_4df904 + 0xb4c)
0040631c        struct Color4f color_9
0040631c        struct Color4f* color_25 = set_color_rgba(&color_9, 1f, 1f, 1f, 1f)
00406337        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0f, arg1[3], color_25, 2, -80f)
00406343        stack_widget_below(arg1[5], arg1[4])
0040637a        arg1[6] = allocate_border(data_4df904 + 0xb4c)
0040637d        struct Color4f color_15
0040637d        struct Color4f* color_26 = set_color_rgba(&color_15, 1f, 1f, 1f, 1f)
00406395        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0f, arg1[3], color_26, 2, 80f)
004063ad        return stack_widget_below(arg1[6], arg1[4])
004067b0        return result
