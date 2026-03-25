/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_matrix_world_z @ 0x44cf50 */

0044cf52        float edi = arg2
0044cf5e        arg2 = fconvert.s(cosine(edi))
0044cf63        int32_t result
0044cf63        long double st0_1
0044cf63        st0_1, result = sine(edi)
0044cf76        long double x87_r6_2 = fconvert.t(arg2) * fconvert.t(*arg1) + st0_1 * fconvert.t(arg1[4])
0044cf86        arg1[4] = fconvert.s(fconvert.t(arg2) * fconvert.t(arg1[4]) - st0_1 * fconvert.t(*arg1))
0044cf89        *arg1 = fconvert.s(x87_r6_2)
0044cf97        long double x87_r6_5 = st0_1 * fconvert.t(arg1[5]) + fconvert.t(arg2) * fconvert.t(arg1[1])
0044cfa7        arg1[5] = fconvert.s(fconvert.t(arg2) * fconvert.t(arg1[5]) - st0_1 * fconvert.t(arg1[1]))
0044cfaa        arg1[1] = fconvert.s(x87_r6_5)
0044cfb9        long double x87_r6_8 = st0_1 * fconvert.t(arg1[6]) + fconvert.t(arg2) * fconvert.t(arg1[2])
0044cfcb        arg1[6] = fconvert.s(fconvert.t(arg2) * fconvert.t(arg1[6]) - st0_1 * fconvert.t(arg1[2]))
0044cfce        arg1[2] = fconvert.s(x87_r6_8)
0044cfd2        return result
