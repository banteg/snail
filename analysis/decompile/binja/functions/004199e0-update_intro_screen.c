/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_intro_screen @ 0x4199e0 */

004199e0        void* eax_7 = data_4df904
004199ed        if (*(eax_7 + 0x24) == 0)
004199fb        char eax_1
004199fb        if (((*(*(eax_7 + 0x28c) + 0x3c)).w:1.b & 0x40) == 0)
004199fd        eax_1 = read_pressed_text_input_key_code()
00419a04        if (((*(*(eax_7 + 0x28c) + 0x3c)).w:1.b & 0x40) != 0 || eax_1 == 0xb)
00419a11        begin_frontend_fade_out(data_4df904 + 0x24, 0)
00419a20        if (*(data_4df904 + 0x24) == 4)
00419a24        destroy_intro_screen(arg1)
00419a29        int32_t eax_2 = arg1[2]
00419a2c        int32_t eax_3 = eax_2
00419a2f        if (eax_2 == 0)
00419a63        long double x87_r7_4 = fconvert.t(arg1[4]) * fconvert.t(60f)
00419a69        *arg1 = 0f
00419a6f        arg1[2] = 1
00419a7c        arg1[1] = fconvert.s(fconvert.t(1f) / x87_r7_4)
00419a31        int32_t temp1_1 = eax_3
00419a31        eax_3 -= 1
00419a32        if (temp1_1 == 1)
00419a37        long double x87_r7_2 = fconvert.t(arg1[1]) + fconvert.t(*arg1)
00419a39        *arg1 = fconvert.s(x87_r7_2)
00419a3b        long double temp2_1 = fconvert.t(1f)
00419a3b        x87_r7_2 - temp2_1
00419a41        eax_3.w = (x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe
00419a46        if ((eax_3:1.b & 0x41) == 0)
00419a52        begin_frontend_fade_out(data_4df904 + 0x24, 0)
00419a5a        int32_t eax_6 = arg1[2] i+ 1
00419a5b        arg1[2] = eax_6
00419a5f        return eax_6
00419a80        return eax_3
