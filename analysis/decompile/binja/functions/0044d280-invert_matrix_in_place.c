/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: invert_matrix_in_place @ 0x44d280 */

0044d292        float var_40
0044d292        __builtin_memcpy(&var_40, arg1, 0x40)
0044d2ad        float var_3c
0044d2ad        float var_38
0044d2ad        float var_10
0044d2ad        float var_c
0044d2ad        long double x87_r7_3 = fconvert.t(var_38) * fconvert.t(*(arg1 + 0x38)) + fconvert.t(var_c) * fconvert.t(var_3c) + fconvert.t(var_10) * fconvert.t(var_40)
0044d2b7        float var_30
0044d2b7        *(arg1 + 4) = var_30
0044d2c0        *(arg1 + 0x30) = fconvert.s(fneg(x87_r7_3))
0044d2c7        float var_28
0044d2c7        long double x87_r7_6 = fconvert.t(var_28) * fconvert.t(*(arg1 + 0x38))
0044d2d2        float var_20
0044d2d2        *(arg1 + 8) = var_20
0044d2d9        *(arg1 + 0x10) = var_3c
0044d2ea        float var_1c
0044d2ea        *(arg1 + 0x18) = var_1c
0044d2f2        *(arg1 + 0x20) = var_38
0044d2f7        *(arg1 + 0x24) = var_28
0044d2fd        float var_2c
0044d2fd        *(arg1 + 0x34) = fconvert.s(fneg(x87_r7_6 + fconvert.t(var_2c) * fconvert.t(var_c) + fconvert.t(var_30) * fconvert.t(var_10)))
0044d31d        float var_18
0044d31d        *(arg1 + 0x38) = fconvert.s(fneg(fconvert.t(var_18) * fconvert.t(*(arg1 + 0x38)) + fconvert.t(var_1c) * fconvert.t(var_c) + fconvert.t(var_20) * fconvert.t(var_10)))
0044d323        return arg1
