/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_vapour @ 0x4425f0 */

004425f0        int32_t eax_17 = *(arg1 + 0x80)
004425fc        if (eax_17 s< 2)
00442601        int32_t result
00442601        result.b = (*(arg1 + 4)).b & 0xdf
00442603        *(arg1 + 4) = result
00442609        return result
00442618        *(arg1 + 4) |= 0x20
00442620        *(*(arg1 + 0x24) + 0x2c) = (eax_17 << 2) + 0xfffffffc
0044262b        if (*(arg1 + 0x8c) != 0)
00442633        int32_t i = 0
00442637        if (*(arg1 + 0x80) s> 0)
00442639        int32_t edi_1 = 0
0044263b        int32_t eax_3 = *(arg1 + 0x90)
00442641        float* esi_1 = *(arg1 + 0x8c)
00442647        long double x87_r7_1 = fconvert.t(*(edi_1 + eax_3 + 0x38))
0044264b        long double temp0_1 = fconvert.t(*esi_1)
0044264b        x87_r7_1 - temp0_1
0044264d        float* edx_3 = edi_1 + eax_3 + 0x38
00442651        eax_3.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
00442656        if ((eax_3:1.b & 1) != 0)
0044265a        *edx_3 = *esi_1
00442662        i += 1
00442663        edi_1 += 0x40
00442668        do while (i s< *(arg1 + 0x80))
00442670        int32_t i_1 = 0
00442675        if (*(arg1 + 0x80) - 1 s> 0)
00442689        long double x87_r7_2 = fconvert.t(*(arg1 + 0x88))
0044268f        int32_t edx_7 = i_1 << 6
00442692        float* eax_7 = *(arg1 + 0x90) + edx_7
004426c4        float var_5c_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(eax_7[1]))) + fconvert.t(eax_7[0xd]))
004426ce        int32_t eax_9 = i_1 * 0x30
004426d1        float* esi_4 = *(*(arg1 + 0x24) + 0x38) + eax_9
004426d3        float var_58_1 = fconvert.s(x87_r7_2 * fconvert.t(eax_7[2]) + fconvert.t(eax_7[0xe]))
004426d7        *esi_4 = fconvert.s(fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(*eax_7))) + fconvert.t(eax_7[0xc]))
004426dd        esi_4[1] = var_5c_1
004426e4        esi_4[2] = var_58_1
004426f3        long double x87_r7_6 = fneg(fconvert.t(*(arg1 + 0x88)))
004426f5        float* esi_6 = *(arg1 + 0x90) + edx_7
00442721        float var_50_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(esi_6[1]))) + fconvert.t(esi_6[0xd]))
0044272e        float var_4c_1 = fconvert.s(x87_r7_6 * fconvert.t(esi_6[2]) + fconvert.t(esi_6[0xe]))
00442732        float* esi_9 = *(*(arg1 + 0x24) + 0x38) + eax_9 + 0xc
00442736        *esi_9 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(*esi_6))) + fconvert.t(esi_6[0xc]))
0044273c        esi_9[1] = var_50_1
00442743        esi_9[2] = var_4c_1
00442752        long double x87_r7_10 = fneg(fconvert.t(*(arg1 + 0x88)))
00442754        float* esi_11 = *(arg1 + 0x90) + edx_7
0044277c        float var_44_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_10 * fconvert.t(esi_11[1]))) + fconvert.t(esi_11[0x1d]))
00442789        float var_40_1 = fconvert.s(x87_r7_10 * fconvert.t(esi_11[2]) + fconvert.t(esi_11[0x1e]))
0044278d        float* esi_14 = *(*(arg1 + 0x24) + 0x38) + eax_9 + 0x18
00442795        *esi_14 = fconvert.s(fconvert.t(fconvert.s(x87_r7_10 * fconvert.t(*esi_11))) + fconvert.t(esi_11[0x1c]))
0044279b        esi_14[1] = var_44_1
004427a2        esi_14[2] = var_40_1
004427ab        long double x87_r7_13 = fconvert.t(*(arg1 + 0x88))
004427b1        float* edx_8 = edx_7 + *(arg1 + 0x90)
004427dd        float var_38_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_13 * fconvert.t(edx_8[1]))) + fconvert.t(edx_8[0x1d]))
004427ea        float var_34_1 = fconvert.s(x87_r7_13 * fconvert.t(edx_8[2]) + fconvert.t(edx_8[0x1e]))
004427ee        int32_t* edx_11 = *(*(arg1 + 0x24) + 0x38) + eax_9 + 0x24
004427f2        *edx_11 = fconvert.s(fconvert.t(fconvert.s(x87_r7_13 * fconvert.t(*edx_8))) + fconvert.t(edx_8[0x1c]))
004427f8        edx_11[1] = var_38_1
004427ff        edx_11[2] = var_34_1
00442802        int32_t edx_12 = *(arg1 + 0x80)
0044280b        if (edx_12 == 2)
00442815        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x14) = 0
0044281f        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x1c) = 0
0044282e        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x24) = 0x3f800000
00442838        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x2c) = 0x3f800000
00442842        if (i_1 != 0)
00442875        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x14) = 0x3f000000
0044287f        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x1c) = 0x3f000000
00442883        void* edx_14 = *(arg1 + 0x24)
00442886        if (i_1 == edx_12 - 2)
0044282e        *(*(edx_14 + 0x5c) + eax_9 + 0x24) = 0x3f800000
00442838        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x2c) = 0x3f800000
0044288b        *(*(edx_14 + 0x5c) + eax_9 + 0x24) = 0x3f000000
00442895        *(*(*(arg1 + 0x24) + 0x5c) + eax_9 + 0x2c) = 0x3f000000
0044284a        *(*(*(arg1 + 0x24) + 0x5c) + 0x14) = 0
00442853        *(*(*(arg1 + 0x24) + 0x5c) + 0x1c) = 0
0044285c        *(*(*(arg1 + 0x24) + 0x5c) + 0x24) = 0x3f000000
00442865        *(*(*(arg1 + 0x24) + 0x5c) + 0x2c) = 0x3f000000
0044289f        i_1 += 1
004428a3        do while (i_1 s< *(arg1 + 0x80) - 1)
004428aa        int32_t edx_27 = *(arg1 + 0x80)
004428c0        **(*(arg1 + 0x24) + 0xd4) = edx_27 * 2 - 2
004428c5        return edx_27 * 2 - 2
