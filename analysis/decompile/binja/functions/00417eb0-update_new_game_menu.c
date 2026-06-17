/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_new_game_menu @ 0x417eb0 */

00417eb0        struct NewGameMenu* menu_1 = menu
00417ed6        int16_t x87control
00417ed6        if (read_pressed_text_input_key_code().b != 0 || ((*(*(data_4df904 + 0x28c) + 0x3c)).w:1.b & 0x40) != 0)
00417edd        bool cond:1_1 = menu->hide_for_replay_latch != 1
00417edf        menu->replay_probe_progress = 0f
00417ee2        if (not(cond:1_1))
00417ee7        unhide_border_init(menu->postal_button)
00417eef        unhide_border_init(menu->tutorial_button)
00417ef7        unhide_border_init(menu->challenge_button)
00417eff        unhide_border_init(menu->time_trial_button)
00417f07        unhide_border_init(menu->help_button)
00417f0f        unhide_border_init(menu->back_button)
00417f20        x87control = capture_mouse_cursor(data_4df904 + 0x290)
00417f25        menu->hide_for_replay_latch = 0
00417f2d        struct FrontendWidget* postal_button = menu->postal_button
00417f30        int32_t eax_3 = postal_button->__offset(0x1a0).d
00417f38        if ((eax_3.b & 0x20) != 0)
00417f3a        eax_3.b &= 0xdf
00417f3c        postal_button->__offset(0x1a0).d = eax_3
00417f44        destroy_main_menu()
00417f50        *(data_4df904 + 0x1b8) = 0xa
00417f60        *(data_4df904 + 0x30c) = 1
00417f6c        *(data_4df904 + 0x74658) = 0
00417f79        *(data_4df904 + 0x12e55e0) = 2
00417f84        return
00417f85        struct FrontendWidget* challenge_button = menu->challenge_button
00417f88        int32_t eax_6 = challenge_button->__offset(0x1a0).d
00417f90        if ((eax_6.b & 0x20) != 0)
00417f92        eax_6.b &= 0xdf
00417f94        challenge_button->__offset(0x1a0).d = eax_6
00417f9c        destroy_main_menu()
00417faa        *(data_4df904 + 0x1b8) = 0xa
00417fba        *(data_4df904 + 0x30c) = 1
00417fc6        *(data_4df904 + 0x74658) = 4
00417fd1        return
00417fd2        struct FrontendWidget* tutorial_button = menu->tutorial_button
00417fd5        int32_t eax_8 = tutorial_button->__offset(0x1a0).d
00417fdd        if ((eax_8.b & 0x20) != 0)
00417fdf        eax_8.b &= 0xdf
00417fe1        tutorial_button->__offset(0x1a0).d = eax_8
00417fe9        destroy_main_menu()
00417ff4        *(data_4df904 + 0x1b8) = 0xa
00418004        *(data_4df904 + 0x30c) = 1
0041800f        *(data_4df904 + 0x74658) = 7
00418025        initialize_tutorial(data_4df904 + 0x7ee70)
0041802c        data_4df9d8 = 1
00418035        return
00418036        struct FrontendWidget* time_trial_button = menu->time_trial_button
00418039        int32_t eax_10 = time_trial_button->__offset(0x1a0).d
00418041        if ((eax_10.b & 0x20) != 0)
00418043        eax_10.b &= 0xdf
00418045        time_trial_button->__offset(0x1a0).d = eax_10
0041804d        destroy_main_menu()
0041805b        *(data_4df904 + 0x1b8) = 0xa
0041806a        *(data_4df904 + 0x30c) = 1
00418076        *(data_4df904 + 0x74658) = 1
0041807e        return
0041807f        struct FrontendWidget* back_button = menu->back_button
00418082        int32_t eax_12 = back_button->__offset(0x1a0).d
0041808a        if ((eax_12.b & 0x20) == 0)
004180b8        struct FrontendWidget* help_button = menu->help_button
004180bb        void* eax_13 = help_button->__offset(0x1a0).d
004180c3        if ((eax_13.b & 0x20) != 0)
004180c5        eax_13.b &= 0xdf
004180c7        help_button->__offset(0x1a0).d = eax_13
004180cf        destroy_main_menu()
004180da        *(data_4df904 + 0x1b8) = 0x1f
004180ea        *(data_4df904 + 0x30c) = 1
0041808c        eax_12.b &= 0xdf
0041808e        back_button->__offset(0x1a0).d = eax_12
00418096        destroy_main_menu()
004180a1        *(data_4df904 + 0x1b8) = 4
004180b0        *(data_4df904 + 0x30c) = 1
004180f3        long double x87_r7_1 = fconvert.t(menu->replay_probe_step) + fconvert.t(menu->replay_probe_progress)
004180f6        menu->replay_probe_progress = fconvert.s(x87_r7_1)
004180f9        long double temp0 = fconvert.t(1f)
004180f9        x87_r7_1 - temp0
00418104        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00418104        return
0041810a        menu->replay_probe_progress = 0f
00418112        int32_t i = 0
00418114        *(data_4df904 + 0x1066bec) = 0
0041811a        int32_t replay_attract_bank_cursor = menu->replay_attract_bank_cursor
0041811c        i += 1
0041811f        if (replay_attract_bank_cursor == 0)
004181fb        int32_t eax_28
004181fb        eax_28, x87control = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
00418210        void* ecx_39 = data_4df904
00418216        int32_t edx_18 = eax_28 * 0x1fac0
00418229        if (*(edx_18 + ecx_39 + 0x6ffae8) == 1)
0041822b        *(ecx_39 + 0x1066bec) = edx_18 + ecx_39 + 0x6ffae8
00418236        *(data_4df904 + 0x74658) = 0
00418126        if (replay_attract_bank_cursor == 1)
004181a5        int32_t eax_24
004181a5        eax_24, x87control = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
004181ba        void* ecx_34 = data_4df904
004181c0        int32_t edx_14 = eax_24 * 0x1fac0
004181d3        if (*(edx_14 + ecx_34 + 0x85c128) == 1)
004181d5        *(ecx_34 + 0x1066bec) = edx_14 + ecx_34 + 0x85c128
004181e0        *(data_4df904 + 0x74658) = 1
0041812b        if (replay_attract_bank_cursor == 3)
00418144        int32_t eax_20
00418144        eax_20, x87control = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.00155639648f))
00418159        void* ecx_29 = data_4df904
0041815f        int32_t edx_10 = eax_20 * 0x1fac0
00418172        if (*(edx_10 + ecx_29 + 0x9b8768) == 1)
00418178        *(ecx_29 + 0x1066bec) = edx_10 + ecx_29 + 0x9b8768
00418183        *(data_4df904 + 0x74658) = 4
0041823e        int32_t ecx_41 = menu->replay_attract_bank_cursor + 1
00418241        menu->replay_attract_bank_cursor = ecx_41
00418246        if (ecx_41 == 5)
00418248        menu->replay_attract_bank_cursor = 0
00418256        if (*(data_4df904 + 0x1066bec) != 0)
0041827a        if (i s>= 0x3e8)
0041827a        break
0041827c        menu->hide_for_replay_latch = 1
00418285        *(data_4df904 + 0x1b8) = 0xa
00418294        *(data_4df904 + 0x30c) = 1
004182a0        *(data_4df904 + 0x1066be8) = 1
004182ae        *(data_4df904 + 0x1066bf0) = 2
004182bd        *(data_4df904 + 0x1066be9) = 1
004182c3        menu->attract_reset_progress = 0f
004182c6        menu->attract_reset_step = 0.000277777785f
004182cd        destroy_main_menu()
004182d7        return
0041825e        do while (i s< 0x3e8)
00418264        menu->attract_reset_progress = 0f
00418267        menu->attract_reset_step = 0.000277777785f
00418273        return
