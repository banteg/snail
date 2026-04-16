/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: multiply_vector_by_matrix_copy @ 0x44cac0 */

0044cac7        int32_t var_c = *arg1
0044cace        int32_t var_8 = arg1[1]
0044cad5        int32_t var_4 = arg1[2]
0044cb14        float var_8_1 = fconvert.s(fconvert.t(arg3[9]) * fconvert.t(arg1[2]) + fconvert.t(arg3[1]) * fconvert.t(*arg1) + fconvert.t(arg3[5]) * fconvert.t(arg1[1]) + fconvert.t(arg3[0xd]))
0044cb36        float var_4_1 = fconvert.s(fconvert.t(arg3[0xa]) * fconvert.t(arg1[2]) + fconvert.t(arg3[2]) * fconvert.t(*arg1) + fconvert.t(arg3[6]) * fconvert.t(arg1[1]) + fconvert.t(arg3[0xe]))
0044cb3a        *arg2 = fconvert.s(fconvert.t(arg3[8]) * fconvert.t(arg1[2]) + fconvert.t(arg3[4]) * fconvert.t(arg1[1]) + fconvert.t(*arg3) * fconvert.t(*arg1) + fconvert.t(arg3[0xc]))
0044cb40        arg2[1] = var_8_1
0044cb47        arg2[2] = var_4_1
0044cb4d        return arg2
