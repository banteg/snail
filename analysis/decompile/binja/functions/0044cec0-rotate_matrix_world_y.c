/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_matrix_world_y @ 0x44cec0 */

0044cec2        float edi = arg2
0044cece        arg2 = fconvert.s(cosine(edi))
0044ced3        int32_t result
0044ced3        long double st0_1
0044ced3        st0_1, result = sine(edi)
0044cee6        long double x87_r6_2 = st0_1 * fconvert.t(*arg1) + fconvert.t(arg2) * fconvert.t(arg1[8])
0044cef6        *arg1 = fconvert.s(fconvert.t(arg2) * fconvert.t(*arg1) - st0_1 * fconvert.t(arg1[8]))
0044cef8        arg1[8] = fconvert.s(x87_r6_2)
0044cf07        long double x87_r6_5 = st0_1 * fconvert.t(arg1[1]) + fconvert.t(arg2) * fconvert.t(arg1[9])
0044cf17        arg1[1] = fconvert.s(fconvert.t(arg2) * fconvert.t(arg1[1]) - st0_1 * fconvert.t(arg1[9]))
0044cf1a        arg1[9] = fconvert.s(x87_r6_5)
0044cf29        long double x87_r6_8 = st0_1 * fconvert.t(arg1[2]) + fconvert.t(arg2) * fconvert.t(arg1[0xa])
0044cf3b        arg1[2] = fconvert.s(fconvert.t(arg2) * fconvert.t(arg1[2]) - st0_1 * fconvert.t(arg1[0xa]))
0044cf3e        arg1[0xa] = fconvert.s(x87_r6_8)
0044cf42        return result
