/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_object_edge @ 0x4305a0 */

004305a5        int32_t ebp = arg4
004305bb        long double st0 = vector_magnitude(*(arg1 + 0x60) + ebp * 0xc)
004305c0        long double temp1 = fconvert.t(0.899999976f)
004305c0        st0 - temp1
004305c6        void* eax
004305c6        eax.w = (st0 < temp1 ? 1 : 0) << 8 | (is_unordered.t(st0, temp1) ? 1 : 0) << 0xa | (st0 == temp1 ? 1 : 0) << 0xe
004305cb        if ((eax:1.b & 1) == 0)
004305d1        int32_t ebx_1 = data_503318
004305df        int32_t i_1 = 0
004305e9        struct Vec3 rhs
004305e9        if (ebx_1 s<= 0)
004306a3        label_4306a3:
004306a3        *(data_503300 + ebx_1 * 0x24) = 1
004306b7        *(data_503300 + data_503318 * 0x24 + 4) = arg2
004306cb        *(data_503300 + data_503318 * 0x24 + 8) = arg3
004306dc        *(data_503300 + data_503318 * 0x24 + 0xc) = ebp
004306ed        *(data_503300 + data_503318 * 0x24 + 0x10) = 0
004306f5        int32_t edx_7 = *(arg1 + 0x38)
004306f8        float* eax_23 = edx_7 + arg2 * 0xc
004306fb        void* ecx_4 = arg3 * 3
00430703        void* ecx_5 = edx_7 + (ecx_4 << 2)
00430706        rhs.x = fconvert.s(fconvert.t(*(edx_7 + (ecx_4 << 2))) - fconvert.t(*eax_23))
00430714        rhs.y = fconvert.s(fconvert.t(*(ecx_5 + 4)) - fconvert.t(eax_23[1]))
00430722        struct Vec3 vector
00430722        vector.x = rhs.x
00430726        vector.y = rhs.y
0043072a        rhs.z = fconvert.s(fconvert.t(*(ecx_5 + 8)) - fconvert.t(eax_23[2]))
00430732        vector.z = rhs.z
0043074c        *(data_503300 + data_503318 * 0x24 + 0x20) = fconvert.s(normalize_vector(&vector))
0043075e        float* eax_28 = data_503300 + data_503318 * 0x24 + 0x14
00430766        *eax_28 = vector.x
0043076c        eax_28[1] = vector.y
00430773        eax_28[2] = vector.z
0043077b        eax = data_503318 + 1
0043077c        data_503318 = eax
004305ef        int32_t edx_1 = *(arg1 + 0x38)
004305f5        float* eax_2 = edx_1 + arg3 * 0xc
00430601        int32_t* ebp_1 = data_503300 + 8
00430604        while (true)
00430607        int32_t eax_5 = ebp_1[-1] * 3
0043060a        long double x87_r7_1 = fconvert.t(*(edx_1 + (eax_5 << 2)))
0043060d        void* edi_1 = edx_1 + (eax_5 << 2)
00430614        long double temp2_1 = fconvert.t(*eax_2)
00430614        x87_r7_1 - temp2_1
00430616        float* eax_6
00430616        eax_6.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0043061b        if ((eax_6:1.b & 0x40) != 0)
00430621        long double x87_r7_2 = fconvert.t(*(edi_1 + 4))
00430624        long double temp3_1 = fconvert.t(eax_2[1])
00430624        x87_r7_2 - temp3_1
00430627        float* eax_7
00430627        eax_7.w = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
0043062c        if ((eax_7:1.b & 0x40) != 0)
00430632        long double x87_r7_3 = fconvert.t(*(edi_1 + 8))
00430635        long double temp4_1 = fconvert.t(eax_2[2])
00430635        x87_r7_3 - temp4_1
00430638        float* eax_8
00430638        eax_8.w = (x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe
0043063d        if ((eax_8:1.b & 0x40) != 0)
00430642        int32_t eax_10 = *ebp_1 * 3
00430645        long double x87_r7_4 = fconvert.t(*(edx_1 + (eax_10 << 2)))
00430648        void* edi_2 = edx_1 + (eax_10 << 2)
0043064b        int32_t eax_11 = arg2 * 3
0043064e        long double temp5_1 = fconvert.t(*(edx_1 + (eax_11 << 2)))
0043064e        x87_r7_4 - temp5_1
00430651        void* ebx_2 = edx_1 + (eax_11 << 2)
00430654        eax_11.w = (x87_r7_4 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp5_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp5_1 ? 1 : 0) << 0xe
00430659        if ((eax_11:1.b & 0x40) != 0)
0043065b        long double x87_r7_5 = fconvert.t(*(edi_2 + 4))
0043065e        long double temp6_1 = fconvert.t(*(ebx_2 + 4))
0043065e        x87_r7_5 - temp6_1
00430661        eax_11.w = (x87_r7_5 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp6_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp6_1 ? 1 : 0) << 0xe
00430666        if ((eax_11:1.b & 0x40) != 0)
00430668        long double x87_r7_6 = fconvert.t(*(edi_2 + 8))
0043066b        long double temp7_1 = fconvert.t(*(ebx_2 + 8))
0043066b        x87_r7_6 - temp7_1
0043066e        eax_11.w = (x87_r7_6 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp7_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp7_1 ? 1 : 0) << 0xe
00430673        if ((eax_11:1.b & 0x40) != 0)
0043078b        int32_t i = i_1
0043078f        int32_t ecx_11 = data_503300
00430798        void** esi_3 = i * 0x24
0043079b        eax = *(esi_3 + ecx_11)
004307a0        if ((eax.b & 1) != 0)
004307a2        eax.b &= 0xfe
004307a4        *(esi_3 + ecx_11) = eax
004307a7        int32_t eax_30 = data_503300
004307b2        *(esi_3 + eax_30) |= 2
004307bf        eax = arg1
004307c3        *(esi_3 + data_503300 + 0x10) = arg4
004307cb        if ((*(eax + 0x10) & 4) == 0)
004307cd        int32_t edx_15 = data_503300
004307d3        int32_t eax_31 = *(eax + 0x60)
004307dd        int32_t* ecx_15 = eax_31 + *(esi_3 + edx_15 + 0xc) * 0xc
004307e2        struct Vec3 lhs
004307e2        lhs.x = *ecx_15
004307e9        lhs.y = ecx_15[1]
004307f0        lhs.z = ecx_15[2]
004307fb        int32_t* eax_32 = eax_31 + *(esi_3 + edx_15 + 0x10) * 0xc
00430800        rhs.x = *eax_32
0043080c        rhs.y = eax_32[1]
0043081c        rhs.z = eax_32[2]
00430820        void out
00430820        cross_vectors(&out, &lhs, &rhs)
00430829        long double st0_2 = vector_magnitude(&out)
0043082e        long double temp8_1 = fconvert.t(0.0500000007f)
0043082e        st0_2 - temp8_1
00430839        if ((((st0_2 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp8_1) ? 1 : 0) << 0xa | (st0_2 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00430849        long double st0_3
00430849        st0_3, eax = dot_vector(&out, esi_3 + data_503300 + 0x14)
0043084e        long double temp9_1 = fconvert.t(0.00200000009f)
0043084e        st0_3 - temp9_1
00430854        eax.w = (st0_3 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp9_1) ? 1 : 0) << 0xa | (st0_3 == temp9_1 ? 1 : 0) << 0xe
00430859        if ((((st0_2 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp8_1) ? 1 : 0) << 0xa | (st0_2 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0 || (eax:1.b & 0x41) == 0)
00430868        if (i s< data_503318 - 1)
0043086a        void** eax_36 = esi_3
0043086c        int32_t ecx_23 = data_503300
00430872        i += 1
00430873        void* esi_4 = eax_36 + ecx_23 + 0x24
00430877        void* edi_5 = eax_36 + ecx_23
0043087f        eax_36 = &eax_36[9]
00430882        __builtin_memcpy(edi_5, esi_4, 0x24)
0043088d        do while (i s< data_503318 - 1)
00430895        int32_t eax_38 = data_503318 - 1
00430898        data_503318 = eax_38
004308a1        return eax_38
004307a0        break
00430679        ebx_1 = data_503318
00430683        ebp_1 = &ebp_1[9]
00430687        bool cond:0_1 = i_1 + 1 s< ebx_1
00430689        i_1 += 1
0043068d        if (not(cond:0_1))
00430693        ebp = arg4
00430697        goto label_4306a3
00430788        return eax
