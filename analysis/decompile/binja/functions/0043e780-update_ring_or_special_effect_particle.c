/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_ring_or_special_effect_particle @ 0x43e780 */

0043e790        if (*(arg1[1] + 0x88) != 3)
0043e798        arg1[5] = fconvert.s(fconvert.t(arg1[6]) + fconvert.t(arg1[5]))
0043e79b        long double x87_r7_3 = fconvert.t(arg1[5])
0043e79e        long double temp0 = fconvert.t(6.28318548f)
0043e79e        x87_r7_3 - temp0
0043e7a4        void* eax
0043e7a4        eax.w = (x87_r7_3 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0) ? 1 : 0) << 0xa | (x87_r7_3 == temp0 ? 1 : 0) << 0xe
0043e7a9        if ((eax:1.b & 0x41) == 0)
0043e7b4        arg1[5] = fconvert.s(fconvert.t(arg1[5]) - fconvert.t(6.28318548f))
0043e7c0        long double x87_r7_7 = cosine(arg1[5]) * fconvert.t(arg1[7])
0043e7cb        long double st0_1 = sine(arg1[5])
0043e7d0        void* eax_1 = arg1[1]
0043e7de        float* ecx_2 = *arg1 + 0x48
0043e7ec        long double x87_r7_12 = fconvert.t(fconvert.s(x87_r7_7)) + fconvert.t(*(eax_1 + 0x6c))
0043e7ef        int32_t eax_3 = *(eax_1 + 0x70)
0043e7fa        *ecx_2 = fconvert.s(st0_1 * fconvert.t(arg1[7]) + fconvert.t(*(eax_1 + 0x68)))
0043e808        ecx_2[1] = fconvert.s(x87_r7_12)
0043e80b        ecx_2[2] = eax_3
0043e80e        void* result = arg1[1]
0043e819        if (*(result + 0x1e8) != 0)
0043e82d        return result
0043e824        return emit_ring_star_shower(arg1, *(result + 0x84))
