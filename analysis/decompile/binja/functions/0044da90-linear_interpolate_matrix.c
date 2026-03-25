/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: linear_interpolate_matrix @ 0x44da90 */

0044da9d        invert_matrix_from_source(arg1, arg2)
0044daa9        multiply_matrix_in_place(arg1, arg3)
0044dab5        interpolate_matrix_rotation(arg1, arg4)
0044dabd        premultiply_matrix_in_place(arg1, arg2)
0044dac4        orthogonalize_matrix(arg1)
0044dae5        float var_4 = fconvert.s(fconvert.t(arg4) * fconvert.t(arg3[0xe]))
0044daef        long double x87_r6_5 = fconvert.t(1f) - fconvert.t(arg4)
0044db09        float var_1c = fconvert.s(x87_r6_5 * fconvert.t(arg2[0xe]))
0044db21        long double x87_r7_4 = fconvert.t(fconvert.s(x87_r6_5 * fconvert.t(arg2[0xd]))) + fconvert.t(fconvert.s(fconvert.t(arg4) * fconvert.t(arg3[0xd])))
0044db25        arg1[0xc] = fconvert.s(fconvert.t(fconvert.s(x87_r6_5 * fconvert.t(arg2[0xc]))) + fconvert.t(arg4) * fconvert.t(arg3[0xc]))
0044db37        arg1[0xd] = fconvert.s(x87_r7_4)
0044db3a        float result = fconvert.s(fconvert.t(var_1c) + fconvert.t(var_4))
0044db42        arg1[0xe] = result
0044db4a        return result
