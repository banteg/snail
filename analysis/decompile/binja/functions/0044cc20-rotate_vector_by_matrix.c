/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_vector_by_matrix @ 0x44cc20 */

0044cc25        float edx = *arg1
0044cc2b        float edx_1 = arg1[1]
0044cc36        float ecx = arg1[2]
0044cc55        *arg1 = fconvert.s(fconvert.t(ecx) * fconvert.t(arg2[8]) + fconvert.t(edx_1) * fconvert.t(arg2[4]) + fconvert.t(edx) * fconvert.t(*arg2))
0044cc70        arg1[1] = fconvert.s(fconvert.t(ecx) * fconvert.t(arg2[9]) + fconvert.t(edx_1) * fconvert.t(arg2[5]) + fconvert.t(edx) * fconvert.t(arg2[1]))
0044cc8c        arg1[2] = fconvert.s(fconvert.t(ecx) * fconvert.t(arg2[0xa]) + fconvert.t(edx_1) * fconvert.t(arg2[6]) + fconvert.t(edx) * fconvert.t(arg2[2]))
0044cc92        return arg1
