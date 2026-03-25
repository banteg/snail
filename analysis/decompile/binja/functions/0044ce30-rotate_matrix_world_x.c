/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_matrix_world_x @ 0x44ce30 */

0044ce32        float edi = arg2
0044ce3e        arg2 = fconvert.s(cosine(edi))
0044ce43        int32_t result
0044ce43        long double st0_1
0044ce43        st0_1, result = sine(edi)
0044ce57        long double x87_r6_2 = st0_1 * fconvert.t(*(arg1 + 0x20)) + fconvert.t(arg2) * fconvert.t(*(arg1 + 0x10))
0044ce68        *(arg1 + 0x20) = fconvert.s(fconvert.t(arg2) * fconvert.t(*(arg1 + 0x20)) - st0_1 * fconvert.t(*(arg1 + 0x10)))
0044ce6b        *(arg1 + 0x10) = fconvert.s(x87_r6_2)
0044ce7a        long double x87_r6_5 = st0_1 * fconvert.t(*(arg1 + 0x24)) + fconvert.t(arg2) * fconvert.t(*(arg1 + 0x14))
0044ce8a        *(arg1 + 0x24) = fconvert.s(fconvert.t(arg2) * fconvert.t(*(arg1 + 0x24)) - st0_1 * fconvert.t(*(arg1 + 0x14)))
0044ce8d        *(arg1 + 0x14) = fconvert.s(x87_r6_5)
0044ce9c        long double x87_r6_8 = st0_1 * fconvert.t(*(arg1 + 0x28)) + fconvert.t(arg2) * fconvert.t(*(arg1 + 0x18))
0044ceae        *(arg1 + 0x28) = fconvert.s(fconvert.t(arg2) * fconvert.t(*(arg1 + 0x28)) - st0_1 * fconvert.t(*(arg1 + 0x18)))
0044ceb1        *(arg1 + 0x18) = fconvert.s(x87_r6_8)
0044ceb5        return result
