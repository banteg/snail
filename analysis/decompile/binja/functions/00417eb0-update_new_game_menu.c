/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_new_game_menu @ 0x417eb0 */

00417eb0        int32_t var_4 = arg1
00417eb5        int32_t* esi = arg1
00417ed6        int16_t x87control
00417ed6        if (read_pressed_text_input_key_code().b != 0 || ((*(*(data_4df904 + 0x28c) + 0x3c)).w:1.b & 0x40) != 0)
00417ed8        int16_t eax
00417ed8        eax.b = esi[1].b
00417edf        esi[4] = 0
00417ee2        if (eax.b == 1)
00417ee7        unhide_border_init(esi[0xc])
00417eef        unhide_border_init(esi[0xf])
00417ef7        unhide_border_init(esi[0xd])
00417eff        unhide_border_init(esi[0xe])
00417f07        unhide_border_init(esi[0x10])
00417f0f        unhide_border_init(esi[0x11])
00417f20        x87control = capture_mouse_cursor(data_4df904 + 0x290)
00417f25        esi[1].b = 0
00417f2d        void* ecx_8 = esi[0xc]
00417f30        int32_t eax_2 = *(ecx_8 + 0x1a0)
00417f38        if ((eax_2.b & 0x20) != 0)
00417f3a        eax_2.b &= 0xdf
00417f3c        *(ecx_8 + 0x1a0) = eax_2
00417f44        destroy_main_menu()
00417f50        *(data_4df904 + 0x1b8) = 0xa
00417f60        *(data_4df904 + 0x30c) = 1
00417f6c        *(data_4df904 + 0x74658) = 0
00417f72        void* eax_4 = data_4df904
00417f79        *(eax_4 + 0x12e55e0) = 2
00417f84        return eax_4
00417f85        void* ecx_12 = esi[0xd]
00417f88        int32_t eax_5 = *(ecx_12 + 0x1a0)
00417f90        if ((eax_5.b & 0x20) != 0)
00417f92        eax_5.b &= 0xdf
00417f94        *(ecx_12 + 0x1a0) = eax_5
00417f9c        destroy_main_menu()
00417faa        *(data_4df904 + 0x1b8) = 0xa
00417fba        *(data_4df904 + 0x30c) = 1
00417fc0        void* eax_6 = data_4df904
00417fc6        *(eax_6 + 0x74658) = 4
00417fd1        return eax_6
00417fd2        void* ecx_16 = esi[0xf]
00417fd5        int32_t eax_7 = *(ecx_16 + 0x1a0)
00417fdd        if ((eax_7.b & 0x20) != 0)
00417fdf        eax_7.b &= 0xdf
00417fe1        *(ecx_16 + 0x1a0) = eax_7
00417fe9        destroy_main_menu()
00417ff4        *(data_4df904 + 0x1b8) = 0xa
00418004        *(data_4df904 + 0x30c) = 1
0041800f        *(data_4df904 + 0x74658) = 7
00418025        int32_t eax_9 = initialize_tutorial(data_4df904 + 0x7ee70)
0041802c        data_4df9d8 = 1
00418035        return eax_9
00418036        void* ecx_22 = esi[0xe]
00418039        int32_t eax_10 = *(ecx_22 + 0x1a0)
00418041        if ((eax_10.b & 0x20) != 0)
00418043        eax_10.b &= 0xdf
00418045        *(ecx_22 + 0x1a0) = eax_10
0041804d        destroy_main_menu()
0041805b        *(data_4df904 + 0x1b8) = 0xa
00418065        void* eax_11 = data_4df904
0041806a        *(eax_11 + 0x30c) = 1
00418076        *(data_4df904 + 0x74658) = 1
0041807e        return eax_11
0041807f        void* ecx_26 = esi[0x11]
00418082        int32_t eax_12 = *(ecx_26 + 0x1a0)
0041808a        void* eax_13
0041808a        if ((eax_12.b & 0x20) == 0)
004180b8        void* ecx_28 = esi[0x10]
004180bb        eax_13 = *(ecx_28 + 0x1a0)
004180c3        if ((eax_13.b & 0x20) != 0)
004180c5        eax_13.b &= 0xdf
004180c7        *(ecx_28 + 0x1a0) = eax_13
004180cf        destroy_main_menu()
004180da        *(data_4df904 + 0x1b8) = 0x1f
004180ea        *(data_4df904 + 0x30c) = 1
0041808c        eax_12.b &= 0xdf
0041808e        *(ecx_26 + 0x1a0) = eax_12
00418096        destroy_main_menu()
004180a1        *(data_4df904 + 0x1b8) = 4
004180b0        *(data_4df904 + 0x30c) = 1
004180f3        long double x87_r7_1 = fconvert.t(esi[5]) + fconvert.t(esi[4])
004180f6        esi[4] = fconvert.s(x87_r7_1)
004180f9        long double temp0 = fconvert.t(1f)
004180f9        x87_r7_1 - temp0
004180ff        eax_13.w = (x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe
00418104        if ((eax_13:1.b & 0x41) == 0)
0041810a        esi[4] = 0
00418112        int32_t i = 0
00418114        *(data_4df904 + 0x1066bec) = 0
0041811a        int32_t eax_15 = *esi
0041811c        i += 1
0041811f        if (eax_15 == 0)
004181fb        int32_t eax_28
004181fb        eax_28, x87control = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
00418210        void* ecx_45 = data_4df904
00418216        int32_t edx_18 = eax_28 * 0x1fac0
00418229        if (*(edx_18 + ecx_45 + 0x6ffae8) == 1)
0041822b        *(ecx_45 + 0x1066bec) = edx_18 + ecx_45 + 0x6ffae8
00418236        *(data_4df904 + 0x74658) = 0
00418126        if (eax_15 == 1)
004181a5        int32_t eax_24
004181a5        eax_24, x87control = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.000122070312f))
004181ba        void* ecx_40 = data_4df904
004181c0        int32_t edx_14 = eax_24 * 0x1fac0
004181d3        if (*(edx_14 + ecx_40 + 0x85c128) == 1)
004181d5        *(ecx_40 + 0x1066bec) = edx_14 + ecx_40 + 0x85c128
004181e0        *(data_4df904 + 0x74658) = 1
0041812b        if (eax_15 == 3)
00418144        int32_t eax_20
00418144        eax_20, x87control = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(0.00155639648f))
00418159        void* ecx_35 = data_4df904
0041815f        int32_t edx_10 = eax_20 * 0x1fac0
00418172        if (*(edx_10 + ecx_35 + 0x9b8768) == 1)
00418178        *(ecx_35 + 0x1066bec) = edx_10 + ecx_35 + 0x9b8768
00418183        *(data_4df904 + 0x74658) = 4
0041823e        void* ecx_47 = *esi + 1
0041823f        eax_13 = ecx_47
00418241        *esi = ecx_47
00418246        if (eax_13 == 5)
00418248        *esi = 0
00418256        if (*(data_4df904 + 0x1066bec) != 0)
0041827a        if (i s>= 0x3e8)
0041827a        break
0041827c        esi[1].b = 1
00418285        *(data_4df904 + 0x1b8) = 0xa
00418294        *(data_4df904 + 0x30c) = 1
004182a0        *(data_4df904 + 0x1066be8) = 1
004182ae        *(data_4df904 + 0x1066bf0) = 2
004182bd        *(data_4df904 + 0x1066be9) = 1
004182c3        esi[2] = 0
004182c6        esi[3] = 0x3991a2b4
004182d7        return destroy_main_menu()
0041825e        do while (i s< 0x3e8)
00418264        esi[2] = 0
00418267        esi[3] = 0x3991a2b4
00418273        return eax_13
