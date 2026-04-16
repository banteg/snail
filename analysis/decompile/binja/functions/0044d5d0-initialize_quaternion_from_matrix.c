/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_quaternion_from_matrix @ 0x44d5d0 */

0044d5d0        int32_t __saved_esi_1
0044d5d0        int32_t __saved_esi = __saved_esi_1
0044d5d1        float* esi = arg2
0044d5d5        int32_t __saved_edi_1
0044d5d5        int32_t __saved_edi = __saved_edi_1
0044d5e0        long double x87_r7_3 = fconvert.t(esi[5]) + fconvert.t(*esi) + fconvert.t(esi[0xa]) + fconvert.t(1f)
0044d5ea        long double temp1 = fconvert.t(9.99999997e-07f)
0044d5ea        x87_r7_3 - temp1
0044d5f5        if ((((x87_r7_3 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d5fb        float var_c = fconvert.s(x87_r7_3)
0044d601        long double x87_r7_5 = fconvert.t(0.5f) / square_root()
0044d614        arg1[3] = fconvert.s(fconvert.t(0.25f) / x87_r7_5)
0044d61f        *arg1 = fconvert.s((fconvert.t(esi[6]) - fconvert.t(esi[9])) * x87_r7_5)
0044d629        arg1[1] = fconvert.s((fconvert.t(esi[8]) - fconvert.t(esi[2])) * x87_r7_5)
0044d634        arg1[2] = fconvert.s((fconvert.t(esi[1]) - fconvert.t(esi[4])) * x87_r7_5)
0044d63b        return arg1
0044d63e        long double x87_r7_7 = fconvert.t(*esi)
0044d640        long double temp2 = fconvert.t(esi[5])
0044d640        x87_r7_7 - temp2
0044d648        if ((((x87_r7_7 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2) ? 1 : 0) << 0xa | (x87_r7_7 == temp2 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044d64e        long double x87_r7_8 = fconvert.t(*esi)
0044d650        long double temp4_1 = fconvert.t(esi[0xa])
0044d650        x87_r7_8 - temp4_1
0044d658        if ((((x87_r7_8 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp4_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d71c        label_44d71c:
0044d71c        long double x87_r7_23 = fconvert.t(*esi) + fconvert.t(1f) - fconvert.t(esi[5]) - fconvert.t(esi[0xa])
0044d71f        arg2 = fconvert.s(x87_r7_23)
0044d723        long double temp7 = fconvert.t(0f)
0044d723        x87_r7_23 - temp7
0044d72e        if ((((x87_r7_23 < temp7 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp7) ? 1 : 0) << 0xa | (x87_r7_23 == temp7 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d737        double var_10_2 = fconvert.d(fconvert.t(arg2))
0044d73a        char* var_14_2 = "ERROR:sqrt %f\n"
0044d747        arg2 = 0f
0044d753        float var_c_2 = arg2
0044d754        long double st0_2 = square_root()
0044d759        long double x87_r7_26 = st0_2 + st0_2
0044d768        *arg1 = fconvert.s(x87_r7_26 * fconvert.t(0.25f))
0044d772        arg1[1] = fconvert.s((fconvert.t(esi[4]) + fconvert.t(esi[1])) / x87_r7_26)
0044d77d        arg1[2] = fconvert.s((fconvert.t(esi[8]) + fconvert.t(esi[2])) / x87_r7_26)
0044d788        arg1[3] = fconvert.s((fconvert.t(esi[9]) + fconvert.t(esi[6])) / x87_r7_26)
0044d78f        return arg1
0044d65e        long double x87_r7_9 = fconvert.t(esi[5])
0044d661        long double temp8_1 = fconvert.t(esi[0xa])
0044d661        x87_r7_9 - temp8_1
0044d669        if ((((x87_r7_9 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp8_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d669        goto label_44d79d
0044d669        goto label_44d67a
0044d6f0        long double x87_r7_18 = fconvert.t(esi[5])
0044d6f3        long double temp3_1 = fconvert.t(esi[0xa])
0044d6f3        x87_r7_18 - temp3_1
0044d6fb        if ((((x87_r7_18 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp3_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044d79d        label_44d79d:
0044d79d        long double x87_r7_31 = fconvert.t(esi[5]) + fconvert.t(1f) - fconvert.t(*esi) - fconvert.t(esi[0xa])
0044d7a0        arg2 = fconvert.s(x87_r7_31)
0044d7a4        long double temp5 = fconvert.t(0f)
0044d7a4        x87_r7_31 - temp5
0044d7af        if ((((x87_r7_31 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp5) ? 1 : 0) << 0xa | (x87_r7_31 == temp5 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d7b8        double var_10_3 = fconvert.d(fconvert.t(arg2))
0044d7bb        char* var_14_3 = "ERROR:sqt %f\n"
0044d7c8        arg2 = 0f
0044d7d4        float var_c_3 = arg2
0044d7d5        long double st0_3 = square_root()
0044d7da        long double x87_r7_34 = st0_3 + st0_3
0044d7e9        *arg1 = fconvert.s((fconvert.t(esi[4]) + fconvert.t(esi[1])) / x87_r7_34)
0044d7f3        arg1[1] = fconvert.s(x87_r7_34 * fconvert.t(0.25f))
0044d7fe        arg1[2] = fconvert.s((fconvert.t(esi[9]) + fconvert.t(esi[6])) / x87_r7_34)
0044d809        arg1[3] = fconvert.s((fconvert.t(esi[8]) + fconvert.t(esi[2])) / x87_r7_34)
0044d810        return arg1
0044d701        long double x87_r7_19 = fconvert.t(*esi)
0044d703        long double temp6_1 = fconvert.t(esi[0xa])
0044d703        x87_r7_19 - temp6_1
0044d70b        if ((((x87_r7_19 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_19, temp6_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d70b        goto label_44d71c
0044d67a        label_44d67a:
0044d67a        long double x87_r7_13 = fconvert.t(esi[0xa]) + fconvert.t(1f) - fconvert.t(*esi) - fconvert.t(esi[5])
0044d67d        arg2 = fconvert.s(x87_r7_13)
0044d681        long double temp9 = fconvert.t(0f)
0044d681        x87_r7_13 - temp9
0044d68c        if ((((x87_r7_13 < temp9 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp9) ? 1 : 0) << 0xa | (x87_r7_13 == temp9 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d695        double var_10_1 = fconvert.d(fconvert.t(arg2))
0044d698        char* var_14_1 = "ERROR:sqt %f\n"
0044d6a5        arg2 = 0f
0044d6b1        float var_c_1 = arg2
0044d6b2        long double st0_1 = square_root()
0044d6b7        long double x87_r7_16 = st0_1 + st0_1
0044d6c6        *arg1 = fconvert.s((fconvert.t(esi[8]) + fconvert.t(esi[2])) / x87_r7_16)
0044d6d0        arg1[1] = fconvert.s((fconvert.t(esi[9]) + fconvert.t(esi[6])) / x87_r7_16)
0044d6db        arg1[2] = fconvert.s(x87_r7_16 * fconvert.t(0.25f))
0044d6e6        arg1[3] = fconvert.s((fconvert.t(esi[4]) + fconvert.t(esi[1])) / x87_r7_16)
0044d6ed        return arg1
