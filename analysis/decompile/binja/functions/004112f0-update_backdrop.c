/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_backdrop @ 0x4112f0 */

004112f6        int32_t eax
004112f6        eax.b = *(arg1 + 0x4c)
004112fb        if (eax.b != 0)
004112fd        change_backdrop_real(arg1)
00411302        *(arg1 + 0x4c) = 0
00411309        float* ebx = arg1 + 0x58
0041130c        int32_t var_4 = 8
0041137a        bool cond:1_1
00411314        float* esi_1 = ebx
00411316        int32_t i_1 = 8
0041136c        int32_t i
0041131e        long double x87_r7_2 = fconvert.t(esi_1[1]) + fconvert.t(*esi_1)
00411320        float var_8_1 = fconvert.s(x87_r7_2)
00411324        *esi_1 = fconvert.s(x87_r7_2)
00411326        long double x87_r7_3 = fconvert.t(var_8_1)
0041132a        long double temp0_1 = fconvert.t(6.28318548f)
0041132a        x87_r7_3 - temp0_1
00411330        eax.w = (x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe
00411335        if ((eax:1.b & 0x41) == 0)
00411341        *esi_1 = fconvert.s(fconvert.t(var_8_1) - fconvert.t(6.28318548f))
0041134e        esi_1[4] = fconvert.s(sine(*esi_1) * fconvert.t(esi_1[2]))
00411354        long double st0_2
00411354        st0_2, eax = cosine(*esi_1)
00411359        long double x87_r7_9 = st0_2 * fconvert.t(esi_1[3])
0041135f        esi_1 = &esi_1[0x30]
00411365        i = i_1
00411365        i_1 -= 1
00411366        esi_1[-0x2b] = fconvert.s(x87_r7_9)
0041136c        do while (i != 1)
00411372        ebx = &ebx[6]
00411375        cond:1_1 = var_4 != 1
00411376        var_4 -= 1
0041137a        do while (cond:1_1)
0041137c        int32_t result = *(arg1 + 0x3c)
00411385        if (result != 0xffffffff)
00411387        int32_t eax_3 = *(arg1 + 0x658)
0041138d        result = eax_3 - 1
0041138e        if (eax_3 == 1)
00411390        result.b = *(arg1 + 0x38)
00411397        if (result.b == 0)
004113a3        return render_backdrop(arg1)
004113a2        return draw_split_backdrop(arg1)
004113ac        return result
