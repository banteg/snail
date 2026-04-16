/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_squidge @ 0x4449c0 */

004449c0        float var_4 = arg1
004449c1        long double x87_r7 = fconvert.t(arg1[1])
004449c4        long double temp0 = fconvert.t(0f)
004449c4        x87_r7 - temp0
004449d1        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
004449d6        long double x87_r7_2 = fconvert.t(arg1[2]) + fconvert.t(arg1[1])
004449d9        arg1[2] = fconvert.s(x87_r7_2)
004449e5        long double x87_r7_5 = (fconvert.t(arg1[1]) - x87_r7_2 * fconvert.t(0.150000006f)) * fconvert.t(0.819999993f)
004449eb        arg1[1] = fconvert.s(x87_r7_5)
004449f1        long double x87_r6_2 = fneg(fconvert.t(arg1[2]))
004449f3        var_4 = fconvert.s(x87_r6_2)
004449f7        *arg1 = fconvert.s(x87_r6_2)
004449f9        long double temp2_1 = fconvert.t(0f)
004449f9        x87_r7_5 - temp2_1
00444a04        if ((((x87_r7_5 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp2_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444a06        x87_r7_5 = fneg(x87_r7_5)
00444a08        long double temp4_1 = fconvert.t(0.00100000005f)
00444a08        x87_r7_5 - temp4_1
00444a13        if ((((x87_r7_5 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp4_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444a15        long double x87_r7_6 = fconvert.t(var_4)
00444a19        long double temp6_1 = fconvert.t(0f)
00444a19        x87_r7_6 - temp6_1
00444a1f        long double x87_r7_7 = fconvert.t(var_4)
00444a28        if ((((x87_r7_6 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp6_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp6_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444a2a        x87_r7_7 = fneg(x87_r7_7)
00444a2c        long double temp8_1 = fconvert.t(0.00100000005f)
00444a2c        x87_r7_7 - temp8_1
00444a37        if ((((x87_r7_7 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp8_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp8_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444a39        arg1[1] = 0
00444a3c        *arg1 = 0
00444a3e        long double x87_r7_8 = fconvert.t(arg1[4])
00444a41        long double temp1 = fconvert.t(0f)
00444a41        x87_r7_8 - temp1
00444a47        int16_t result = (x87_r7_8 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1 ? 1 : 0) << 0xe
00444a4c        if ((result:1.b & 0x40) == 0)
00444a51        long double x87_r7_10 = fconvert.t(arg1[5]) + fconvert.t(arg1[4])
00444a54        arg1[5] = fconvert.s(x87_r7_10)
00444a60        long double x87_r7_13 = (fconvert.t(arg1[4]) - x87_r7_10 * fconvert.t(0.150000006f)) * fconvert.t(0.819999993f)
00444a66        arg1[4] = fconvert.s(x87_r7_13)
00444a6c        long double x87_r6_4 = fneg(fconvert.t(arg1[5]))
00444a6e        var_4 = fconvert.s(x87_r6_4)
00444a72        arg1[3] = fconvert.s(x87_r6_4)
00444a75        long double temp3_1 = fconvert.t(0f)
00444a75        x87_r7_13 - temp3_1
00444a80        if ((((x87_r7_13 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp3_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444a82        x87_r7_13 = fneg(x87_r7_13)
00444a84        long double temp5_1 = fconvert.t(0.00100000005f)
00444a84        x87_r7_13 - temp5_1
00444a8a        result = (x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe
00444a8f        if ((result:1.b & 1) != 0)
00444a91        long double x87_r7_14 = fconvert.t(var_4)
00444a95        long double temp7_1 = fconvert.t(0f)
00444a95        x87_r7_14 - temp7_1
00444a9b        long double x87_r7_15 = fconvert.t(var_4)
00444aa4        if ((((x87_r7_14 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp7_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp7_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444aa6        x87_r7_15 = fneg(x87_r7_15)
00444aa8        long double temp9_1 = fconvert.t(0.00100000005f)
00444aa8        x87_r7_15 - temp9_1
00444aae        result = (x87_r7_15 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp9_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp9_1 ? 1 : 0) << 0xe
00444ab3        if ((result:1.b & 1) != 0)
00444ab5        arg1[4] = 0
00444ab8        arg1[3] = 0
00444abc        return result
