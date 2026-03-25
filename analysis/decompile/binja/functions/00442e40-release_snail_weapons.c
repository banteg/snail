/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_snail_weapons @ 0x442e40 */

00442e46        char result = *(arg1 + 0x1934)
00442e4e        if (result == 0)
00442e5d        int32_t var_24_1 = 0
00442e74        float var_c_1 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442e7d        long double x87_r7_5 = random_float_below(1f) + fconvert.t(0.5f)
00442e95        float var_4_1 = fconvert.s(fconvert.t(*(*(arg1 + 0x100) + 0x418)))
00442eb1        *(arg1 + 0x15b0) = fconvert.s(fconvert.t(var_c_1) * fconvert.t(0.300000012f))
00442ec5        *(arg1 + 0x15b4) = fconvert.s(x87_r7_5 * fconvert.t(0.300000012f))
00442ed0        *(arg1 + 0x15b8) = fconvert.s(fconvert.t(var_4_1) * fconvert.t(0.300000012f))
00442edc        int32_t var_2c_1 = 0
00442ef3        float var_1c_3 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442ef7        long double st0_2 = random_float_below(1f)
00442f14        float var_4_2 = fconvert.s(fconvert.t(*(*(arg1 + 0x100) + 0x418)))
00442f30        *(arg1 + 0xa1c) = fconvert.s(fconvert.t(var_1c_3) * fconvert.t(0.300000012f))
00442f44        *(arg1 + 0xa20) = fconvert.s((st0_2 + fconvert.t(0.5f)) * fconvert.t(0.300000012f))
00442f4f        *(arg1 + 0xa24) = fconvert.s(fconvert.t(var_4_2) * fconvert.t(0.300000012f))
00442f5b        int32_t var_34_1 = 0
00442f72        float var_1c_5 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442f7b        long double x87_r7_21 = random_float_below(1f) + fconvert.t(0.5f)
00442f8d        float var_4_3 = fconvert.s(fconvert.t(*(*(arg1 + 0x100) + 0x418)))
00442faf        *(arg1 + 0x11d4) = fconvert.s(fconvert.t(var_1c_5) * fconvert.t(0.300000012f))
00442fc3        *(arg1 + 0x11d8) = fconvert.s(x87_r7_21 * fconvert.t(0.300000012f))
00442fce        *(arg1 + 0x11dc) = fconvert.s(fconvert.t(var_4_3) * fconvert.t(0.300000012f))
00442fda        int32_t var_3c_1 = 0
00442ff1        float var_1c_7 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00442ff5        long double st0_4 = random_float_below(1f)
00442ffa        void* eax_10 = *(arg1 + 0x100)
00443012        float var_4_4 = fconvert.s(fconvert.t(*(eax_10 + 0x418)))
00443031        *(arg1 + 0xdf8) = fconvert.s(fconvert.t(var_1c_7) * fconvert.t(0.300000012f))
00443045        *(arg1 + 0xdfc) = fconvert.s((st0_4 + fconvert.t(0.5f)) * fconvert.t(0.300000012f))
00443050        *(arg1 + 0xe00) = fconvert.s(fconvert.t(var_4_4) * fconvert.t(0.300000012f))
00443059        result = end_jetpack_hover(eax_10 + 0x2750)
0044305e        *(arg1 + 0x1934) = 1
00443069        return result
