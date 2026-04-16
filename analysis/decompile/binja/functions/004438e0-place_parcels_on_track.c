/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: place_parcels_on_track @ 0x4438e0 */

004438e6        int32_t i_4 = *(arg1 + 0x40)
004438f4        if (i_4 == 1)
00443905        return place_challenge_parcels_on_track(arg1)
00443906        int32_t i_1 = 0
0044390f        if (i_4 == 0 || i_4 == 7)
00443915        void* i = nullptr
0044392d        while (i s< 0x106000)
00443917        *(i + &data_53d390) = 0
0044391d        *(i + 0x6489e8) = 0
00443923        i += 0x20c
00443935        int32_t i_3 = 0
00443939        float out_angle_1 = 0f
0044393d        int32_t i_6 = 0
00443941        int32_t i_8 = 0
00443945        float out_angle
00443945        int32_t var_208
00443945        int32_t var_190[0x64]
00443945        if (*(arg1 + 0xa874) s> 0)
00443952        int32_t* ebx_1 = arg1 + 0xa87c
00443958        int32_t (* var_1f4_1)[0x64] = &var_190
0044395c        int32_t* var_214_1 = ebx_1
00443964        int32_t eax_2 = 0
00443966        var_208 = 0
0044396a        int32_t var_200_1 = 0
0044396e        *var_1f4_1 = 0x2710
00443982        int32_t ecx_3 = i_8 * 0x20c
0044398d        while (true)
0044398d        int32_t edx_4 = 0
00443991        if (*ebx_1 s> 0)
0044399a        char* var_1f0_1 = &ebx_1[4]
0044399e        int32_t* out_angle_5 = &ebx_1[0x206]
004439a4        out_angle = out_angle_5
004439bb        while (true)
004439bb        if ((out_angle_5[-2].b & 1) != 0 && out_angle_5[-1] == eax_2)
004439c3        if (eax_2 != 0)
00443a34        *(ecx_3 + &data_6489f0) = i_1
00443a43        *((*(ecx_3 + 0x6489e8) << 4) + ecx_3 + 0x6487e8) = edx_4
00443a55        int32_t* eax_14 = (*(ecx_3 + 0x6489e8) << 4) + ecx_3 + 0x6487ec
00443a5c        *eax_14 = *out_angle_5
00443a61        eax_14[1] = out_angle_5[1]
00443a67        eax_14[2] = out_angle_5[2]
00443a6e        *(ecx_3 + 0x6489ec) = var_200_1
00443a7b        *(ecx_3 + 0x6489e8) += 1
004439d0        int32_t eax_7 = i_3 * 0x20c
004439d3        *(eax_7 + 0x53d398) = i_1
004439e2        *((*(eax_7 + &data_53d390) << 4) + eax_7 + 0x53d190) = edx_4
004439f4        int32_t* ebx_6 = (*(eax_7 + &data_53d390) << 4) + eax_7 + 0x53d194
004439fb        *ebx_6 = *out_angle_5
00443a00        ebx_6[1] = out_angle_5[1]
00443a0a        ebx_6[2] = out_angle_5[2]
00443a0d        *(eax_7 + 0x53d394) = 0
00443a1e        i_3 = i_6 + 1
00443a1f        *(eax_7 + &data_53d390) += 1
00443a2a        int32_t i_7 = i_3
00443a2e        out_angle_1 += 1
00443a8c        int32_t var_204_1 = 0
00443a94        char* var_1ec_1 = var_1f0_1
00443a9c        int32_t eax_22 = i_3 * 0x20c
00443bd6        bool cond:8_1
00443aaf        if (sx.d(*var_1ec_1) == var_200_1 + 0x30)
00443abb        if (var_200_1 != 0)
00443b4b        *(ecx_3 + &data_6489f0) = i_1
00443b60        *((*(ecx_3 + 0x6489e8) << 4) + ecx_3 + 0x6487e8) = edx_4
00443b76        float* edi_21 = (*(ecx_3 + 0x6489e8) << 4) + ecx_3 + 0x6487ec
00443b7d        int32_t var_1d8_1 = 0
00443b85        int32_t var_1d4_1 = 0
00443b95        *edi_21 = fconvert.s(float.t(var_204_1) - fconvert.t(4f) + fconvert.t(0.5f))
00443b9b        edi_21[1] = var_1d8_1
00443ba2        edi_21[2] = var_1d4_1
00443ba9        *(ecx_3 + 0x6489ec) = var_200_1
00443bb6        *(ecx_3 + 0x6489e8) += 1
00443ac5        *(eax_22 + 0x53d398) = i_1
00443ada        *((*(eax_22 + &data_53d390) << 4) + eax_22 + 0x53d190) = edx_4
00443af0        float* edi_14 = (*(eax_22 + &data_53d390) << 4) + eax_22 + 0x53d194
00443af7        int32_t var_1e4_1 = 0
00443aff        int32_t var_1e0_1 = 0
00443b07        eax_22 += 0x20c
00443b14        *edi_14 = fconvert.s(float.t(var_204_1) - fconvert.t(4f) + fconvert.t(0.5f))
00443b1a        edi_14[1] = var_1e4_1
00443b21        edi_14[2] = var_1e0_1
00443b28        *(eax_22 + 0x53d188) = 0
00443b39        i_3 += 1
00443b3a        *(eax_22 + 0x53d184) += 1
00443b41        out_angle_1 += 1
00443bcb        cond:8_1 = var_204_1 + 1 s< 8
00443bce        var_204_1 += 1
00443bd2        var_1ec_1 = &var_1ec_1[0x100]
00443bd6        do while (cond:8_1)
00443be4        edx_4 += 1
00443be5        out_angle_5 = out_angle i+ 0x38
00443be9        i_6 = i_3
00443bed        var_1f0_1 = &var_1f0_1[1]
00443bf1        ebx_1 = var_214_1
00443bf5        out_angle = out_angle_5
00443bfb        if (edx_4 s>= *ebx_1)
00443bfb        break
004439aa        eax_2 = var_200_1
00443c01        int32_t eax_23 = *(ecx_3 + 0x6489e8)
00443c09        if (eax_23 s> 0)
00443c0b        int32_t edx_5 = *(ecx_3 + &data_6489f0)
00443c21        int32_t __saved_edi
00443c21        if (eax_23 s< var_190[edx_5])
00443c23        (&__saved_edi)[edx_5 + 0x25] = eax_23
00443c29        if (eax_23 s> var_208)
00443c2b        var_208 = eax_23
00443c34        ecx_3 += 0x20c
00443c3a        i_8 += 1
00443c43        bool cond:5_1 = var_200_1 + 1 s< 0xa
00443c46        var_200_1 += 1
00443c4a        if (not(cond:5_1))
00443c4a        break
00443987        eax_2 = var_200_1
00443c58        i_1 += 1
00443c62        ebx_1 = &ebx_1[0x1088]
00443c6a        var_1f4_1 = &(*var_1f4_1)[1]
00443c6e        var_214_1 = ebx_1
00443c72        do while (i_1 s< *(arg1 + 0xa874))
00443c81        int32_t edi_31 = *(arg1 + 0x1b01e0)
00443c94        int32_t eax_28 = *(arg1 + 0xa874)
00443ca5        int32_t esi_1 = edi_31 * 0x50 s/ 0x64 - var_208
00443cb1        out_angle = out_angle_1
00443cb5        float out_angle_2
00443cb5        if (eax_28 s<= 0)
00443ce2        out_angle_2 = out_angle
00443cb7        int32_t var_214_2 = eax_28
00443cbb        out_angle_2 = out_angle
00443cbf        int32_t (* edx_14)[0x64] = &var_190
00443cde        bool cond:3_1
00443cc6        int32_t ecx_9 = *edx_14
00443cce        if (ecx_9 != 0x2710)
00443cd0        out_angle_2 += ecx_9
00443cd6        edx_14 = &(*edx_14)[1]
00443cd9        cond:3_1 = var_214_2 != 1
00443cda        var_214_2 -= 1
00443cde        do while (cond:3_1)
00443ce8        if (out_angle_2 s< edi_31)
00443cf0        void* var_228_1 = arg1 + 0x1b0150
00443cf6        report_errorf("Parcel Allocation could fail in %s.  Add more parcel Sets")
00443d08        int32_t ecx_13 = *(arg1 + 0x1b01e0) - esi_1
00443d0c        if (ecx_13 s> out_angle_1)
00443d14        void* var_228_2 = arg1 + 0x1b0150
00443d1a        ecx_13 = report_errorf("Parcel Allocation could fail in %s. Add more 0 parcels ")
00443d22        int32_t ebx_26 = 0
00443d26        int32_t var_210_1 = 0
00443d2a        int16_t x87control
00443d2a        if (esi_1 s> 0)
00443d30        int32_t i_2 = i_8
00443d36        while (i_2 s> 0)
00443d40        void* var_228_3 = &data_4a3f10
00443d45        int32_t var_22c_1 = ecx_13
00443d51        int32_t eax_31
00443d51        eax_31, x87control = __ftol(x87control, random_float_below(fconvert.s(float.t(i_8))))
00443d58        int32_t var_214_3 = 0
00443d68        int32_t edi_33 = eax_31 * 0x20c
00443d6b        int32_t eax_32 = *(edi_33 + 0x6489e8)
00443d75        var_210_1 = ebx_26 + eax_32
00443d79        if (eax_32 s> 0)
00443d7f        int32_t* ebx_28 = edi_33 + 0x6487ec
00443e59        bool cond:14_1
00443da8        float out_angle_3 = *(*(edi_33 + &data_6489f0) * 0x4220 + arg1 + 0xa878) + ebx_28[-1]
00443daa        out_angle = out_angle_3
00443db7        void* esi_3 = arg1 + out_angle_3 i* 0xf4
00443dc1        if ((*(esi_3 + 0x5ccac8) & 0x10) != 0)
00443dcd        void* var_228_4 = arg1 + 0x1b0150
00443dd3        report_errorf("Duplicate Parcel Request in %s.")
00443dec        long double x87_r7_9 = float.t(out_angle)
00443df0        *(esi_3 + 0x5ccac8) |= 0x11
00443dfc        *(esi_3 + 0x5ccb58) = *ebx_28
00443e01        *(esi_3 + 0x5ccb5c) = ebx_28[1]
00443e07        *(esi_3 + 0x5ccb60) = ebx_28[2]
00443e16        *(esi_3 + 0x5ccb60) = fconvert.s(x87_r7_9 + fconvert.t(*(esi_3 + 0x5ccb60)) + fconvert.t(0.5f))
00443e28        *(esi_3 + 0x5ccb5c) = fconvert.s(fconvert.t(*(esi_3 + 0x5ccb5c)) + fconvert.t(1f))
00443e35        if ((*(esi_3 + 0x5ccac8) & 0x20) != 0)
00443e43        *(esi_3 + 0x5ccb58) = fconvert.s(fconvert.t(*(esi_3 + 0x5ccb58)) * fconvert.t(-1f))
00443e50        ebx_28 = &ebx_28[4]
00443e53        cond:14_1 = var_214_3 + 1 s< *(edi_33 + 0x6489e8)
00443e55        var_214_3 += 1
00443e59        do while (cond:14_1)
00443e5f        int32_t eax_40 = *(edi_33 + &data_6489f0)
00443e65        int32_t ecx_29 = 0
00443e6b        i_2 = i_8
00443e71        int32_t var_208_2 = 0
00443e75        if (i_2 s> 0)
00443e7b        float out_angle_6 = i_2 - 1
00443e7e        int32_t* edx_21 = &data_648bf4
00443e83        int32_t* esi_4 = &data_6489f0
00443e88        out_angle = out_angle_6
00443e8c        int32_t* var_1f0_2 = &data_648bf4
00443e90        int32_t* var_1f4_2 = &data_6489f0
00443e9a        if (*esi_4 == eax_40)
00443ea2        if (ecx_29 s< out_angle_6)
00443ea4        int32_t* eax_41 = edx_21
00443eaa        int32_t var_214_4 = out_angle_6 i- ecx_29
00443f10        bool cond:16_1
00443eb0        int32_t j = 0
00443eb4        if (*eax_41 s> 0)
00443eb6        int32_t* ecx_30 = &eax_41[-0x103]
00443ebc        int32_t* esi_6 = &ecx_30[0x83]
00443ec2        int32_t* edi_34 = ecx_30
00443ec4        j += 1
00443ec5        ecx_30 = &ecx_30[4]
00443eca        *edi_34 = *esi_6
00443ecf        edi_34[1] = esi_6[1]
00443ed5        edi_34[2] = esi_6[2]
00443edb        edi_34[3] = esi_6[3]
00443ee2        do while (j s< *eax_41)
00443ee4        ecx_29 = var_208_2
00443eea        eax_41[-0x83] = *eax_41
00443ef3        eax_41[-0x81] = eax_41[2]
00443efc        eax_41[-0x82] = eax_41[1]
00443f06        eax_41 = &eax_41[0x83]
00443f0b        cond:16_1 = var_214_4 != 1
00443f0c        var_214_4 -= 1
00443f10        do while (cond:16_1)
00443f12        out_angle_6 = out_angle
00443f16        edx_21 = var_1f0_2
00443f1a        esi_4 = var_1f4_2
00443f22        ecx_29 -= 1
00443f23        esi_4 -= 0x20c
00443f29        edx_21 -= 0x20c
00443f2f        int32_t i_9 = i_8 - 1
00443f30        out_angle_6 -= 1
00443f31        i_8 = i_9
00443f35        out_angle = out_angle_6
00443f39        i_2 = i_9
00443f3b        ecx_29 += 1
00443f3c        esi_4 = &esi_4[0x83]
00443f42        edx_21 = &edx_21[0x83]
00443f4a        var_208_2 = ecx_29
00443f4e        var_1f4_2 = esi_4
00443f52        var_1f0_2 = edx_21
00443f56        do while (ecx_29 s< i_2)
00443f5c        ebx_26 = var_210_1
00443f60        ecx_13 = esi_1
00443f66        if (ebx_26 s>= ecx_13)
00443f66        break
00443f76        if (ebx_26 s< *(arg1 + 0x1b01e0))
00443f7c        int32_t ecx_31 = i_3 - 1
00443f7f        int32_t var_208_3 = ecx_31
00443f85        while (i_3 s> 0)
00443f8f        void* var_228_5 = &data_4a3f0c
00443f94        int32_t var_22c_3 = ecx_31
00443fa0        int32_t eax_43
00443fa0        eax_43, x87control = __ftol(x87control, random_float_below(fconvert.s(float.t(i_6))))
00443fb9        int32_t esi_10 = eax_43 * 0x20c
00443fc4        int32_t eax_45 = *(esi_10 + 0x53d398)
00443fcc        var_210_1 += *(esi_10 + &data_53d390)
00443fe0        out_angle = esi_10 + 0x53d190
00443ff0        int32_t eax_47 = *(eax_45 * 0x4220 + arg1 + 0xa878) + *(esi_10 + 0x53d190)
00443ff2        int32_t var_214_5 = eax_47
00443ffc        int32_t edx_39 = eax_47 * 0x3d
00443fff        eax_47.b = *(arg1 + (edx_39 << 2) + 0x5ccac8)
00444008        void* edi_36 = arg1 + (edx_39 << 2)
0044400b        if ((eax_47.b & 0x10) != 0)
00444016        void* var_228_6 = arg1 + 0x1b0150
0044401c        report_errorf("Duplicate Parcel Request in %s.")
0044403d        *(edi_36 + 0x5ccac8) |= 0x11
00444047        *(edi_36 + 0x5ccb58) = *(esi_10 + 0x53d194)
0044404c        *(edi_36 + 0x5ccb5c) = *(esi_10 + 0x53d198)
00444052        *(edi_36 + 0x5ccb60) = *(esi_10 + 0x53d19c)
00444061        *(edi_36 + 0x5ccb60) = fconvert.s(float.t(var_214_5) + fconvert.t(*(edi_36 + 0x5ccb60)) + fconvert.t(0.5f))
00444073        *(edi_36 + 0x5ccb5c) = fconvert.s(fconvert.t(*(edi_36 + 0x5ccb5c)) + fconvert.t(1f))
00444080        if ((*(edi_36 + 0x5ccac8) & 0x20) != 0)
0044408a        *(edi_36 + 0x5ccb58) = fconvert.s(fconvert.t(*(edi_36 + 0x5ccb58)) * fconvert.t(-1f))
00444092        if (eax_43 s< var_208_3)
00444094        float out_angle_4 = out_angle
00444098        int32_t j_2 = var_208_3 - eax_43
004440df        int32_t j_1
004440a4        j_1 = j_2
004440a4        j_2 -= 1
004440a7        *out_angle_4 = *(out_angle_4 i+ 0x20c)
004440ac        *(out_angle_4 i+ 4) = *(out_angle_4 i+ 0x210)
004440b2        *(out_angle_4 i+ 8) = *(out_angle_4 i+ 0x214)
004440b8        *(out_angle_4 i+ 0xc) = *(out_angle_4 i+ 0x218)
004440c1        *(out_angle_4 i+ 0x200) = *(out_angle_4 i+ 0x40c)
004440cd        *(out_angle_4 i+ 0x208) = *(out_angle_4 i+ 0x414)
004440d3        *(out_angle_4 i+ 0x204) = 0
004440dd        out_angle_4 += 0x20c
004440df        do while (j_1 != 1)
004440e9        i_3 -= 1
004440eb        ecx_31 = *(arg1 + 0x1b01e0)
004440f1        var_208_3 -= 1
004440f9        i_6 = i_3
004440ff        if (var_210_1 s>= ecx_31)
004440ff        break
0044410d        int32_t eax_52 = *(arg1 + 0x1b01e0)
00444115        if (var_210_1 != eax_52)
0044411d        void* var_228_7 = arg1 + 0x1b0150
0044411e        int32_t var_22c_5 = eax_52
00444124        report_errorf("Did not generate required Parcels(%i) in %s")
00444129        int32_t ecx_41 = *(arg1 + 0x1b01e8)
00444134        if (ecx_41 != 0)
00444142        *(arg1 + 0x1b01e8) = divs.dp.d(sx.q(*(arg1 + 0x1b01e0) * var_210_1), ecx_41)
00444148        *(arg1 + 0x1b01e0) = var_210_1
0044414e        i_4 = *(arg1 + 0x54)
00444153        int32_t i_5 = 0
0044415b        if (i_4 s> 0)
00444161        int32_t* esi_18 = arg1 + 0x5ccac8
00444167        char eax_57 = (*esi_18).b
00444173        if ((eax_57 & 1) != 0 && (eax_57 & 0x40) != 0)
0044417f        int32_t eax_58 = get_track_cell_row_index(esi_18[0x29])
0044418c        int32_t eax_59
0044418c        eax_59, x87control = __ftol(x87control, fconvert.t(esi_18[0x26]))
00444193        int32_t edi_39 = eax_59 - eax_58
00444195        if (eax_59 - eax_58 s< 0)
00444197        edi_39 = 0
00444199        struct TrackRowCell* cell = esi_18[0x29]
0044419f        struct PathTemplate* attachment_template_record = cell->attachment_template_record
004441a6        if (attachment_template_record->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
00444201        int32_t eax_65 = get_track_cell_row_index(cell)
00444212        get_path_position_at_node(*(esi_18[0x29] + 0x38), &esi_18[0x24], edi_39, eax_65, &esi_18[0x24])
004441d9        struct TransformMatrix transform
004441d9        x87control = compute_kind42_attachment_transform((&attachment_template_record->primary_samples->special_scalar)[edi_39 * 0x2a], esi_18[0x24], esi_18[0x25], &transform, &out_angle)
004441e5        float y = transform.position.y
004441ec        esi_18[0x24] = transform.position.x
004441f2        esi_18[0x25] = y
0044421e        i_4 = i_5 + 1
0044421f        esi_18 = &esi_18[0x3d]
00444227        i_5 = i_4
0044422b        do while (i_4 s< *(arg1 + 0x54))
0044423b        return i_4
