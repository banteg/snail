/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: multiply_matrices @ 0x44d060 */

0044d07c        *arg1 = fconvert.s(fconvert.t(*arg2) * fconvert.t(*arg3) + fconvert.t(arg2[1]) * fconvert.t(arg3[4]) + fconvert.t(arg2[2]) * fconvert.t(arg3[8]))
0044d093        arg1[1] = fconvert.s(fconvert.t(arg2[1]) * fconvert.t(arg3[5]) + fconvert.t(arg3[1]) * fconvert.t(*arg2) + fconvert.t(arg3[9]) * fconvert.t(arg2[2]))
0044d0ab        arg1[2] = fconvert.s(fconvert.t(arg2[1]) * fconvert.t(arg3[6]) + fconvert.t(arg3[2]) * fconvert.t(*arg2) + fconvert.t(arg3[0xa]) * fconvert.t(arg2[2]))
0044d0c3        arg1[4] = fconvert.s(fconvert.t(arg2[6]) * fconvert.t(arg3[8]) + fconvert.t(arg2[5]) * fconvert.t(arg3[4]) + fconvert.t(arg2[4]) * fconvert.t(*arg3))
0044d0dc        arg1[5] = fconvert.s(fconvert.t(arg2[6]) * fconvert.t(arg3[9]) + fconvert.t(arg2[5]) * fconvert.t(arg3[5]) + fconvert.t(arg2[4]) * fconvert.t(arg3[1]))
0044d0f5        arg1[6] = fconvert.s(fconvert.t(arg2[6]) * fconvert.t(arg3[0xa]) + fconvert.t(arg2[5]) * fconvert.t(arg3[6]) + fconvert.t(arg2[4]) * fconvert.t(arg3[2]))
0044d10d        arg1[8] = fconvert.s(fconvert.t(arg2[8]) * fconvert.t(*arg3) + fconvert.t(arg2[0xa]) * fconvert.t(arg3[8]) + fconvert.t(arg2[9]) * fconvert.t(arg3[4]))
0044d126        arg1[9] = fconvert.s(fconvert.t(arg3[9]) * fconvert.t(arg2[0xa]) + fconvert.t(arg3[5]) * fconvert.t(arg2[9]) + fconvert.t(arg3[1]) * fconvert.t(arg2[8]))
0044d13f        arg1[0xa] = fconvert.s(fconvert.t(arg3[0xa]) * fconvert.t(arg2[0xa]) + fconvert.t(arg3[6]) * fconvert.t(arg2[9]) + fconvert.t(arg3[2]) * fconvert.t(arg2[8]))
0044d15a        arg1[0xc] = fconvert.s(fconvert.t(arg2[0xe]) * fconvert.t(arg3[8]) + fconvert.t(arg2[0xd]) * fconvert.t(arg3[4]) + fconvert.t(arg2[0xc]) * fconvert.t(*arg3) + fconvert.t(arg3[0xc]))
0044d176        arg1[0xd] = fconvert.s(fconvert.t(arg2[0xe]) * fconvert.t(arg3[9]) + fconvert.t(arg2[0xd]) * fconvert.t(arg3[5]) + fconvert.t(arg2[0xc]) * fconvert.t(arg3[1]) + fconvert.t(arg3[0xd]))
0044d192        arg1[0xe] = fconvert.s(fconvert.t(arg2[0xe]) * fconvert.t(arg3[0xa]) + fconvert.t(arg2[0xd]) * fconvert.t(arg3[6]) + fconvert.t(arg2[0xc]) * fconvert.t(arg3[2]) + fconvert.t(arg3[0xe]))
0044d195        return arg3
