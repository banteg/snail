/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_subgame_rate @ 0x4404d0 */

004404d0        float var_4 = arg1
004404dc        int32_t result
004404dc        if (*(arg1 i+ 0x3c) != 2)
004405f0        result = *(arg1 i+ 0x30)
004405f3        *(arg1 i+ 0x38) = result
004404e5        long double x87_r7_2 = fconvert.t(*(arg1 i+ 0x3bb7d4)) / float.t(*(arg1 i+ 0x58))
004404eb        long double temp0_1 = fconvert.t(0f)
004404eb        x87_r7_2 - temp0_1
004404f6        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00440502        long double temp1_1 = fconvert.t(1f)
00440502        x87_r7_2 - temp1_1
0044050d        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00440511        x87_r7_2 = fconvert.t(1f)
004404fa        x87_r7_2 = fconvert.t(0f)
00440517        result = *(arg1 i+ 0x40)
00440522        long double x87_r7_7
00440522        if (result == 1 || result == 3)
00440548        x87_r7_7 = x87_r7_2 * fconvert.t(0.550000012f) + fconvert.t(*(arg1 i+ 0x30))
00440527        if (result != 4)
00440548        x87_r7_7 = x87_r7_2 * fconvert.t(0.200000003f) + fconvert.t(*(arg1 i+ 0x30))
00440532        x87_r7_7 = x87_r7_2 * fconvert.t(0.400000006f) + fconvert.t(*(arg1 i+ 0x30)) + fconvert.t(0.200000003f)
0044054b        int32_t edx_1 = *(arg1 i+ 0x3bbb28)
00440551        *(arg1 i+ 0x38) = fconvert.s(x87_r7_7)
00440556        if (edx_1 == 2)
0044055b        if (result != 1)
00440560        var_4 = 0.600000024f
00440568        if (result == 1 || result == 4)
0044056a        var_4 = 0.400000006f
00440572        long double x87_r7_9 = fconvert.t(*(arg1 i+ 0x3bbb48))
00440578        long double temp2_1 = fconvert.t(0.25)
00440578        x87_r7_9 - temp2_1
0044057e        result.w = (x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe
00440583        long double x87_r7_11
00440583        if ((result:1.b & 1) != 0)
004405aa        label_4405aa:
004405aa        int32_t var_c_1 = 2
004405b4        long double st0_1
004405b4        st0_1, result = sine(fconvert.s(fconvert.t(*(arg1 i+ 0x3bbb48)) * fconvert.t(12.566371f) + fconvert.t(1.57079637f)))
004405c8        x87_r7_11 = (fconvert.t(1f) - st0_1) * fconvert.t(0.5f) * fconvert.t(var_4)
00440585        long double x87_r7_10 = fconvert.t(*(arg1 i+ 0x3bbb48))
0044058b        long double temp3_1 = fconvert.t(0.75)
0044058b        x87_r7_10 - temp3_1
00440591        result.w = (x87_r7_10 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp3_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp3_1 ? 1 : 0) << 0xe
00440596        if ((result:1.b & 0x41) == 0)
00440596        goto label_4405aa
00440598        x87_r7_11 = fconvert.t(var_4)
004405cf        *(arg1 i+ 0x38) = fconvert.s(x87_r7_11 + fconvert.t(*(arg1 i+ 0x38)))
004405d9        if (*(arg1 i+ 0x3bdec0) == 1)
004405ea        *(arg1 i+ 0x38) = fconvert.s(fconvert.t(*(arg1 i+ 0x3be0c0)) * fconvert.t(0.5f) + fconvert.t(*(arg1 i+ 0x38)))
004405f8        return result
