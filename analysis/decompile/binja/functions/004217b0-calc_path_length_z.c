/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_path_length_z @ 0x4217b0 */

004217c5        void* edx = *(arg1 + 4)
004217c8        int32_t esi = *(edx + 0x5c)
004217d4        int32_t eax_2 = *(arg1 + 0xc) * 0x15
004217d7        long double x87_r7_1 = fconvert.t(arg2) * fconvert.t(*(esi + (eax_2 << 3) + 0x8c))
004217e7        long double x87_r6_1 = x87_r7_1 + fconvert.t(*(arg1 + 0x10))
004217ea        long double temp1 = fconvert.t(*(esi + (eax_2 << 3) + 0x8c))
004217ea        x87_r6_1 - temp1
004217ec        float* eax_3
004217ec        eax_3.w = (x87_r6_1 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, temp1) ? 1 : 0) << 0xa | (x87_r6_1 == temp1 ? 1 : 0) << 0xe | 0x3800
004217f1        float var_ec
004217f1        if ((eax_3:1.b & 0x41) == 0)
0042183d        int32_t eax_7
004217f3        int32_t ecx_1 = *(arg1 + 0xc)
00421809        long double x87_r6_3 = fconvert.t(*(esi + ecx_1 * 0xa8 + 0x8c)) - fconvert.t(*(arg1 + 0x10))
0042180f        *(arg1 + 0x10) = 0
00421816        *(arg1 + 0xc) = ecx_1 + 1
0042181e        x87_r7_1 = x87_r7_1 - x87_r6_3
00421820        if (ecx_1 + 1 == *(edx + 0x44))
00421882        *arg1 = 0
004218ad        arg4[2] = fconvert.s(fconvert.t(arg2) * fconvert.t(*(*(edx + 0x5c) + *(edx + 0x44) * 0xa8 - 0x1c)))
004218b5        int32_t* edx_3 = *(arg1 + 0x24) + 0x1f4
004218bb        *edx_3 = *(arg1 + 0x18)
004218c0        edx_3[1] = *(arg1 + 0x1c)
004218c6        edx_3[2] = *(arg1 + 0x20)
004218c9        void* eax_18 = *(arg1 + 4)
004218d0        if (*(eax_18 + 0x38) != 0x1f)
004219d1        long double x87_r7_6 = x87_r7_1 + fconvert.t(*(*(eax_18 + 0x5c) + *(eax_18 + 0x44) * 0xa8 - 0x70)) + fconvert.t(*(*(arg1 + 8) + 0x18)) + fconvert.t(*(eax_18 + 0x50))
004219d5        arg3[2] = fconvert.s(x87_r7_6)
004219dc        *(*(arg1 + 0x24) + 0x1fc) = fconvert.s(x87_r7_6)
004219ed        return 3
004218e0        arg4[1] = fconvert.s(fconvert.t(arg4[2]) * fconvert.t(0.699999988f))
004218ec        var_ec = *arg3
004218f0        void* edx_5 = *(arg1 + 4)
004218f6        long double x87_r7_3 = x87_r7_1 + fconvert.t(*(edx_5 + 0x50))
004218f9        int32_t edx_6 = *(edx_5 + 0x5c)
00421906        int32_t eax_21 = *(edx_5 + 0x44) * 0x15
00421912        void* eax_22 = edx_6 + (eax_21 << 3)
00421918        float* edx_8 = *(arg1 + 8) + 0x10
0042192b        long double x87_r7_4 = x87_r7_3 * fconvert.t(*(eax_22 - 0x80))
00421945        float var_c4 = fconvert.s(fconvert.t(*(eax_22 - 0x70)) + fconvert.t(edx_8[2]))
00421955        long double x87_r6_16 = fconvert.t(fconvert.s(fconvert.t(*(eax_22 - 0x74)) + fconvert.t(edx_8[1]))) + fconvert.t(fconvert.s(x87_r7_3 * fconvert.t(*(eax_22 - 0x84))))
0042195d        *arg3 = fconvert.s(fconvert.t(*edx_8) + fconvert.t(*(eax_22 - 0x78)) + fconvert.t(fconvert.s(x87_r7_3 * fconvert.t(*(edx_6 + (eax_21 << 3) - 0x88)))))
0042196d        arg3[1] = fconvert.s(x87_r6_16)
00421978        arg3[2] = fconvert.s(fconvert.t(var_c4) + x87_r7_4)
0042197b        float eax_24 = var_ec
0042197f        *arg3 = eax_24
00421984        float* edx_13 = *(arg1 + 0x24) + 0x1f4
0042198d        *edx_13 = eax_24
00421992        edx_13[1] = arg3[1]
0042199d        edx_13[2] = arg3[2]
004219a6        return 3
00421822        esi = *(edx + 0x5c)
00421831        long double temp2_1 = fconvert.t(*(esi + (ecx_1 + 1) * 0xa8 + 0x8c))
00421831        x87_r7_1 - temp2_1
00421838        eax_7.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe | 0x3800
0042183d        do while ((eax_7:1.b & 0x41) == 0)
00421843        int32_t ebx = *(arg1 + 0xc)
00421846        float var_f0 = fconvert.s(x87_r7_1 + fconvert.t(*(arg1 + 0x10)))
0042184e        *(arg1 + 0x10) = var_f0
00421854        int32_t edi = *(edx + 0x44) - 1
00421857        int32_t eax_9 = ebx << 3
00421860        float var_e8
00421860        int32_t eax_12
00421860        void* ecx_8
00421860        if (ebx != edi)
004219ff        eax_12 = (eax_9 - ebx) * 0x18
00421a02        ecx_8 = *(edx + 0x58) + eax_12
00421a1f        var_e8 = fconvert.s(fconvert.t(var_f0) / fconvert.t(*(eax_12 + *(edx + 0x5c) + 0x8c)) * (fconvert.t(*(ecx_8 + 0x138)) - fconvert.t(*(ecx_8 + 0x90))) + fconvert.t(*(ecx_8 + 0x90)))
0042186e        eax_12 = (eax_9 - ebx) * 0x18
00421871        ecx_8 = *(edx + 0x58) + eax_12
00421879        var_e8 = *(ecx_8 + 0x90)
00421a25        float var_f4
00421a25        if (ebx != edi)
00421a55        var_f4 = fconvert.s(fconvert.t(var_f0) / fconvert.t(*(eax_12 + *(edx + 0x5c) + 0x8c)) * (fconvert.t(*(ecx_8 + 0x144)) - fconvert.t(*(ecx_8 + 0x9c))) + fconvert.t(*(ecx_8 + 0x9c)))
00421a2d        var_f4 = *(ecx_8 + 0x9c)
00421a5b        if (ebx != edi)
00421a8b        var_ec = fconvert.s(fconvert.t(var_f0) / fconvert.t(*(eax_12 + *(edx + 0x5c) + 0x8c)) * (fconvert.t(*(ecx_8 + 0x148)) - fconvert.t(*(ecx_8 + 0xa0))) + fconvert.t(*(ecx_8 + 0xa0)))
00421a63        var_ec = *(ecx_8 + 0xa0)
00421a93        float transform
00421a93        float var_bc_1
00421a93        float var_b8_1
00421a93        int32_t* ecx_21
00421a93        float* edx_18
00421a93        float* esi_11
00421a93        float var_bc
00421a93        float var_b8
00421a93        if (*(edx + 0x38) != 0x2a)
00421b3c        int32_t ecx_22 = *(edx + 0x5c)
00421b4c        void* esi_12 = eax_12 + ecx_22
00421b4f        void* ecx_23 = *(arg1 + 8)
00421b5c        float var_e4_2 = fconvert.s(fconvert.t(var_f0) * fconvert.t(*(eax_12 + ecx_22 + 0x80)) * fconvert.t(var_f4) + fconvert.t(*(esi_12 + 0x30)) + fconvert.t(*(ecx_23 + 0x10)))
00421b74        float var_e0_2 = fconvert.s(fconvert.t(var_f0) * fconvert.t(*(esi_12 + 0x84)) * fconvert.t(var_f4) + fconvert.t(*(esi_12 + 0x34)) + fconvert.t(*(ecx_23 + 0x14)))
00421b88        float var_dc_2 = fconvert.s(fconvert.t(var_f0) * fconvert.t(*(esi_12 + 0x88)) + fconvert.t(*(esi_12 + 0x38)) + fconvert.t(*(ecx_23 + 0x18)))
00421b8c        if (ebx != edi)
00421ba9        float var_40[0xc]
00421ba9        __builtin_memcpy(&var_40, esi_12, 0x40)
00421bcf        int32_t var_8_1 = 0
00421bda        int32_t var_c_1 = 0
00421be5        int32_t var_10_1 = 0
00421bf0        int32_t var_48_1 = 0
00421bfb        int32_t var_4c_1 = 0
00421c06        int32_t var_50_1 = 0
00421c14        float var_80[0xc]
00421c14        int32_t var_108_2 = __builtin_memcpy(&var_80, *(edx + 0x5c) + (ebx + 1) * 0xa8, 0x40)
00421c33        linear_interpolate_matrix(&transform, &var_40, &var_80, fconvert.s(fconvert.t(var_f0) / fconvert.t(*(eax_12 + *(edx + 0x5c) + 0x8c))))
00421b92        set_matrix_identity(&transform)
00421c40        edx_18 = arg4
00421c47        esi_11 = arg3
00421c4e        ecx_21 = &arg1[0x18]
00421c53        transform = fconvert.s(fconvert.t(transform) * fconvert.t(var_f4))
00421c5f        var_bc_1 = fconvert.s(fconvert.t(var_bc) * fconvert.t(var_f4))
00421c6b        var_b8_1 = fconvert.s(fconvert.t(var_b8) * fconvert.t(var_f4))
00421c75        *(arg1 + 0x14) = fconvert.s(fconvert.t(edx_18[1]) + fconvert.t(*(arg1 + 0x14)))
00421c7a        long double x87_r7_50 = fconvert.t(*esi_11) - fconvert.t(var_e8)
00421cae        *ecx_21 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(transform))) + fconvert.t(var_e4_2))
00421cbc        ecx_21[1] = fconvert.s(fconvert.t(fconvert.s(fconvert.t(var_bc_1) * x87_r7_50)) + fconvert.t(var_e0_2))
00421cc7        ecx_21[2] = fconvert.s(x87_r7_50 * fconvert.t(var_b8_1) + fconvert.t(var_dc_2))
00421a99        esi_11 = arg3
00421ab9        float* var_114_1 = &transform
00421ac0        compute_kind42_attachment_transform(var_ec, fconvert.s(fconvert.t(*esi_11) - fconvert.t(var_e8)), 0.49000001f, &transform, &var_ec)
00421ad4        int32_t ecx_19 = *(arg1 + 0xc) * 0x15
00421ad7        int32_t eax_34 = *(*(arg1 + 4) + 0x5c)
00421ada        edx_18 = arg4
00421af4        ecx_21 = &arg1[0x18]
00421af7        long double x87_r7_24 = fconvert.t(*(eax_34 + (ecx_19 << 3) + 0x88)) * fconvert.t(*(arg1 + 0x10)) + fconvert.t(*(*(arg1 + 8) + 0x18)) + fconvert.t(*(eax_34 + (ecx_19 << 3) + 0x38))
00421b06        transform = fconvert.s(fconvert.t(transform) * fconvert.t(var_f4))
00421b12        var_bc_1 = fconvert.s(fconvert.t(var_bc) * fconvert.t(var_f4))
00421b1e        var_b8_1 = fconvert.s(fconvert.t(var_b8) * fconvert.t(var_f4))
00421b25        long double x87_r6_36 = fconvert.t(edx_18[1]) + fconvert.t(*(arg1 + 0x14))
00421b28        int32_t var_90
00421b28        *ecx_21 = var_90
00421b2e        int32_t var_8c
00421b2e        *(arg1 + 0x1c) = var_8c
00421b31        *(arg1 + 0x14) = fconvert.s(x87_r6_36)
00421b34        *(arg1 + 0x20) = fconvert.s(x87_r7_24)
00421cd1        float* eax_40 = *(arg1 + 0x24) + 0x1c4
00421cd6        *eax_40 = transform
00421cdc        eax_40[1] = var_bc_1
00421ce3        eax_40[2] = var_b8_1
00421ced        int32_t* eax_42 = *(arg1 + 0x24) + 0x1d4
00421cf2        int32_t var_b0
00421cf2        *eax_42 = var_b0
00421cf8        int32_t var_ac
00421cf8        eax_42[1] = var_ac
00421cff        int32_t var_a8
00421cff        eax_42[2] = var_a8
00421d09        int32_t* eax_44 = *(arg1 + 0x24) + 0x1e4
00421d0e        int32_t var_a0
00421d0e        *eax_44 = var_a0
00421d14        int32_t var_9c
00421d14        eax_44[1] = var_9c
00421d1b        int32_t var_98
00421d1b        eax_44[2] = var_98
00421d1e        void* eax_45 = *(arg1 + 0x24)
00421d2e        *(eax_45 + 0x24c) = *(eax_45 + 0x258)
00421d33        *(eax_45 + 0x250) = *(eax_45 + 0x25c)
00421d3a        *(eax_45 + 0x254) = *(eax_45 + 0x260)
00421d3f        long double x87_r7_54 = fconvert.t(*esi_11) - fconvert.t(var_e8)
00421d43        long double temp3 = fconvert.t(0f)
00421d43        x87_r7_54 - temp3
00421d49        int32_t* eax_46
00421d49        eax_46.w = (x87_r7_54 < temp3 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_54, temp3) ? 1 : 0) << 0xa | (x87_r7_54 == temp3 ? 1 : 0) << 0xe | 0x3800
00421d4e        if ((eax_46:1.b & 1) != 0)
00421d50        x87_r7_54 = fneg(x87_r7_54)
00421d52        void* edi_15 = *(arg1 + 4)
00421d64        long double x87_r7_55 = float.t(*(edi_15 + 0x54)) * fconvert.t(0.5f) + fconvert.t(0.300000012f)
00421d66        x87_r7_54 - x87_r7_55
00421d68        eax_46.w = (x87_r7_54 < x87_r7_55 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_54, x87_r7_55) ? 1 : 0) << 0xa | (x87_r7_54 == x87_r7_55 ? 1 : 0) << 0xe
00421d6d        if ((eax_46:1.b & 0x41) != 0)
00421da9        if (*(edi_15 + 0x38) != 0x2a)
00421daf        *esi_11 = fconvert.s(fconvert.t(*esi_11) + fconvert.t(*edx_18))
00421dbc        return 0
00421d72        int32_t eax_47 = *ecx_21
00421d74        int32_t* edx_21 = *(arg1 + 0x24) + 0x1f4
00421d7a        *arg1 = 0
00421d80        *edx_21 = eax_47
00421d85        edx_21[1] = ecx_21[1]
00421d8d        edx_21[2] = ecx_21[2]
00421d99        int32_t result
00421d99        result.b = *(*(arg1 + 4) + 0x40) == 0
00421da2        return result
