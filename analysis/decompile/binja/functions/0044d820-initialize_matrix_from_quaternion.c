/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_matrix_from_quaternion @ 0x44d820 */

0044d825        float* ecx = arg2
0044d829        long double x87_r7 = fconvert.t(*ecx)
0044d82d        long double x87_r7_1 = x87_r7 * x87_r7
0044d832        long double x87_r6_2 = fconvert.t(ecx[1]) * fconvert.t(*ecx)
0044d839        float var_14 = fconvert.s(fconvert.t(ecx[2]) * fconvert.t(*ecx))
0044d842        float var_8 = fconvert.s(fconvert.t(ecx[3]) * fconvert.t(*ecx))
0044d846        long double x87_r5_4 = fconvert.t(ecx[1])
0044d84d        float var_4 = fconvert.s(x87_r5_4 * x87_r5_4)
0044d859        float var_c = fconvert.s(fconvert.t(ecx[2]) * fconvert.t(ecx[1]))
0044d863        float var_10 = fconvert.s(fconvert.t(ecx[3]) * fconvert.t(ecx[1]))
0044d867        long double x87_r5_10 = fconvert.t(ecx[2])
0044d86e        arg2 = fconvert.s(x87_r5_10 * x87_r5_10)
0044d877        long double x87_r5_13 = fconvert.t(ecx[3]) * fconvert.t(ecx[2])
0044d87e        long double x87_r4_5 = fconvert.t(arg2) + fconvert.t(var_4)
0044d88c        *arg1 = fconvert.s(fconvert.t(1f) - (x87_r4_5 + x87_r4_5))
0044d890        long double x87_r4_9 = x87_r6_2 - x87_r5_13
0044d894        arg1[4] = fconvert.s(x87_r4_9 + x87_r4_9)
0044d89b        long double x87_r4_12 = fconvert.t(var_10) + fconvert.t(var_14)
0044d8a1        arg1[8] = fconvert.s(x87_r4_12 + x87_r4_12)
0044d8a4        long double x87_r5_14 = x87_r5_13 + x87_r6_2
0044d8a8        arg1[1] = fconvert.s(x87_r5_14 + x87_r5_14)
0044d8b1        long double x87_r6_5 = fconvert.t(arg2) + x87_r7_1
0044d8bb        arg1[5] = fconvert.s(fconvert.t(1f) - (x87_r6_5 + x87_r6_5))
0044d8c2        long double x87_r6_9 = fconvert.t(var_c) - fconvert.t(var_8)
0044d8c8        arg1[9] = fconvert.s(x87_r6_9 + x87_r6_9)
0044d8cf        long double x87_r6_12 = fconvert.t(var_14) - fconvert.t(var_10)
0044d8d5        arg1[2] = fconvert.s(x87_r6_12 + x87_r6_12)
0044d8dc        long double x87_r6_15 = fconvert.t(var_c) + fconvert.t(var_8)
0044d8e2        arg1[6] = fconvert.s(x87_r6_15 + x87_r6_15)
0044d8e9        long double x87_r6_18 = fconvert.t(var_4) + x87_r7_1
0044d8f3        arg1[0xa] = fconvert.s(fconvert.t(1f) - (x87_r6_18 + x87_r6_18))
0044d8f8        arg1[0xb] = 0
0044d8fb        arg1[7] = 0
0044d8fe        arg1[3] = 0
0044d901        arg1[0xe] = 0
0044d904        arg1[0xd] = 0
0044d907        arg1[0xc] = 0
0044d90a        arg1[0xf] = 0x3f800000
0044d914        return arg1
