/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_sound_effect_at_position @ 0x44dce0 */

0044dce3        void* eax = data_4df904
0044dce9        float* esi = arg2
0044dced        float var_1c = 1e+10f
0044dd11        long double x87_r7_5 = fconvert.t(esi[2]) - fconvert.t(*(eax + 0x234))
0044dd1f        float var_8 = fconvert.s(fconvert.t(esi[1]) - fconvert.t(*(eax + 0x230)))
0044dd27        float var_c = fconvert.s(fconvert.t(*esi) - fconvert.t(*(eax + 0x22c)))
0044dd33        float var_4 = fconvert.s(x87_r7_5)
0044dd37        long double st0 = vector_magnitude(&var_c)
0044dd3c        long double temp1 = fconvert.t(1e+10f)
0044dd3c        st0 - temp1
0044dd42        float result
0044dd42        result.w = (st0 < temp1 ? 1 : 0) << 8 | (is_unordered.t(st0, temp1) ? 1 : 0) << 0xa | (st0 == temp1 ? 1 : 0) << 0xe | 0x3800
0044dd47        if ((result:1.b & 1) != 0)
0044dd49        var_1c = fconvert.s(st0)
0044dd51        long double x87_r7_8 = fconvert.t(var_1c)
0044dd55        long double temp2 = fconvert.t(25f)
0044dd55        x87_r7_8 - temp2
0044dd5b        result.w = (x87_r7_8 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2) ? 1 : 0) << 0xa | (x87_r7_8 == temp2 ? 1 : 0) << 0xe
0044dd60        if ((result:1.b & 0x41) == 0)
0044ddd8        return result
0044dd7e        long double x87_r7_14 = fconvert.t(*esi) * fconvert.t(-0.25f) * fconvert.t(100f)
0044dd84        arg2 = fconvert.s(x87_r7_14)
0044dd88        long double temp3_1 = fconvert.t(-100f)
0044dd88        x87_r7_14 - temp3_1
0044dd8e        result.w = (x87_r7_14 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp3_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp3_1 ? 1 : 0) << 0xe
0044dd93        if ((result:1.b & 1) == 0)
0044dd9f        long double x87_r7_15 = fconvert.t(arg2)
0044dda3        long double temp4_1 = fconvert.t(100f)
0044dda3        x87_r7_15 - temp4_1
0044dda9        result.w = (x87_r7_15 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp4_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp4_1 ? 1 : 0) << 0xe
0044ddae        if ((result:1.b & 0x41) == 0)
0044ddb0        arg2 = 100f
0044dd95        arg2 = -100f
0044ddcc        return play_sound_effect_backend(arg1, fconvert.s(fconvert.t(1f) - fconvert.t(var_1c) * fconvert.t(0.0399999991f)), -1f, arg2)
