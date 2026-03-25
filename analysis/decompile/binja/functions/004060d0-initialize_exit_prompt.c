/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_exit_prompt @ 0x4060d0 */

004060e4        hide_all_borders(data_4df904 + 0xb4c)
004060eb        float* result = *arg1 - 2
004060f7        int32_t* var_140_2
004060f7        int32_t* var_140_5
004060f7        switch (result)
004063be        case nullptr, 5
004063be        int32_t var_138_12 = 0
004063dd        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004063e0        void var_a0
004063e0        int32_t* eax_25 = set_color_rgba(&var_a0, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004063fc        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0, 200f, eax_25, 2.80259693e-45f)
00406412        int32_t var_138_13 = 0xc2a00000
00406431        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406434        void var_130
00406434        int32_t* eax_27 = set_color_rgba(&var_130, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406450        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0, 330f, eax_27, 2.80259693e-45f)
0040645c        stack_widget_below(arg1[5], arg1[4])
00406471        int32_t var_138_15 = 0x42a00000
00406476        int32_t var_13c_3 = 2
00406490        arg1[6] = allocate_border(data_4df904 + 0xb4c)
00406498        void var_110
00406498        var_140_5 = set_color_rgba(&var_110, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004064ac        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0, 330f, var_140_5, 2.80259693e-45f)
004064c4        return stack_widget_below(arg1[6], arg1[4])
004064d6        case 1
004064d6        int32_t var_138_17 = 0
004064f2        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004064f5        void var_f0
004064f5        int32_t* eax_33 = set_color_rgba(&var_f0, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406511        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0, 200f, eax_33, 2.80259693e-45f)
00406526        int32_t var_138_18 = 0xc2a00000
00406545        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406548        void var_d0
00406548        int32_t* eax_36 = set_color_rgba(&var_d0, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406564        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0, 330f, eax_36, 2.80259693e-45f)
00406570        stack_widget_below(arg1[5], arg1[4])
00406586        int32_t var_138_20 = 0x42a00000
004065a8        arg1[6] = allocate_border(data_4df904 + 0xb4c)
004065ab        void var_b0
004065ab        int32_t* eax_38 = set_color_rgba(&var_b0, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004065c4        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0, 330f, eax_38, 2.80259693e-45f)
004065dc        return stack_widget_below(arg1[6], arg1[4])
004065ee        case 2
004065ee        int32_t var_138_22 = 0
0040660d        arg1[4] = allocate_border(data_4df904 + 0xb4c)
00406610        void var_90
00406610        int32_t* eax_42 = set_color_rgba(&var_90, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
0040662c        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0, 200f, eax_42, 2.80259693e-45f)
00406642        int32_t var_138_23 = 0xc2a00000
00406664        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406667        void var_70
00406667        int32_t* eax_44 = set_color_rgba(&var_70, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406686        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0x43ea0000, 373f, eax_44, 2.80259693e-45f)
00406692        stack_widget_below(arg1[5], arg1[4])
004066a8        int32_t var_138_25 = 0x42a00000
004066ca        arg1[6] = allocate_border(data_4df904 + 0xb4c)
004066cd        void var_50
004066cd        int32_t* eax_47 = set_color_rgba(&var_50, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004066e9        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0x440e0000, 296f, eax_47, 2.80259693e-45f)
00406701        return stack_widget_below(arg1[6], arg1[4])
00406712        case 3
00406712        int32_t var_138_27 = 0
00406731        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406734        void var_30
00406734        int32_t* eax_51 = set_color_rgba(&var_30, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406750        initialize_frontend_widget(arg1[5], 0x14, "Yes", 0x14, 0x43ec8000, 33f, eax_51, 0f)
00406766        int32_t var_138_28 = 0
00406785        arg1[6] = allocate_border(data_4df904 + 0xb4c)
0040678d        void var_10
0040678d        var_140_2 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004067a4        return initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0x440d8000, 108f, var_140_2, 0f)
0040610f        case 7
0040610f        int32_t var_138_1 = 0x430c0000
0040612e        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406131        void var_120
00406131        int32_t* eax_2
00406131        int32_t ecx_4
00406131        eax_2, ecx_4 = set_color_rgba(&var_120, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406140        int32_t var_144_1 = ecx_4
00406152        initialize_frontend_widget(arg1[5], 0x14, "Yes", 0x14, 0, fconvert.s(fconvert.t(arg1[3]) - fconvert.t(54f)), eax_2, 2.80259693e-45f)
00406168        int32_t var_138_2 = 0x43860000
0040618a        arg1[6] = allocate_border(data_4df904 + 0xb4c)
00406192        void var_20
00406192        var_140_2 = set_color_rgba(&var_20, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004067a4        return initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0, arg1[3], var_140_2, 2.80259693e-45f)
004061af        case 8
004061af        int32_t var_138_3 = 0
004061cb        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004061ce        void var_100
004061ce        int32_t* eax_7 = set_color_rgba(&var_100, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004061ea        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0, 200f, eax_7, 2.80259693e-45f)
00406200        int32_t var_138_4 = 0xc2a00000
00406222        arg1[5] = allocate_border(data_4df904 + 0xb4c)
00406225        void var_80
00406225        int32_t* eax_9 = set_color_rgba(&var_80, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406240        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0, arg1[3], eax_9, 2.80259693e-45f)
0040624c        stack_widget_below(arg1[5], arg1[4])
00406262        int32_t var_138_6 = 0x42a00000
00406267        int32_t var_13c_2 = 2
00406281        arg1[6] = allocate_border(data_4df904 + 0xb4c)
00406289        void var_e0
00406289        var_140_5 = set_color_rgba(&var_e0, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004064ac        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0, arg1[3], var_140_5, 2.80259693e-45f)
004064c4        return stack_widget_below(arg1[6], arg1[4])
004062a4        case 9
004062a4        int32_t var_138_7 = 0
004062c3        arg1[4] = allocate_border(data_4df904 + 0xb4c)
004062c6        void var_40
004062c6        int32_t* eax_15 = set_color_rgba(&var_40, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
004062e2        initialize_frontend_widget(arg1[4], &__dos_header.e_cblp, "Do you really want to quit?", 0x14, 0, 200f, eax_15, 2.80259693e-45f)
004062f7        int32_t var_138_8 = 0xc2a00000
00406319        arg1[5] = allocate_border(data_4df904 + 0xb4c)
0040631c        void var_c0
0040631c        int32_t* eax_18 = set_color_rgba(&var_c0, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406337        initialize_frontend_widget(arg1[5], 0x40000014, "Yes", 0x14, 0, arg1[3], eax_18, 2.80259693e-45f)
00406343        stack_widget_below(arg1[5], arg1[4])
00406358        int32_t var_138_10 = 0x42a00000
0040637a        arg1[6] = allocate_border(data_4df904 + 0xb4c)
0040637d        void var_60
0040637d        int32_t* eax_21 = set_color_rgba(&var_60, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00406395        initialize_frontend_widget(arg1[6], 0x14, "No", 0x14, 0, arg1[3], eax_21, 2.80259693e-45f)
004063ad        return stack_widget_below(arg1[6], arg1[4])
004067b0        return result
