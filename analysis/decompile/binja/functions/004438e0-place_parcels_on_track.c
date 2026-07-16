/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: place_parcels_on_track @ 0x4438e0 */

004438e6        int32_t level_mode = game->level_mode
004438f4        if (level_mode == 1)
004438f6        place_challenge_parcels_on_track(game)
00443905        return
00443906        int32_t i_1 = 0
0044390f        if (level_mode != 0 && level_mode != 7)
0044390a        return
00443915        int32_t i = 0
0044392d        while (i s< 0x106000)
00443917        *(i + &g_zero_parcel_buckets.candidate_count) = 0
0044391d        *(i + &g_parcel_set_buckets.candidate_count) = 0
00443923        i += 0x20c
00443935        int32_t i_3 = 0
00443939        float out_angle_1 = 0f
0044393d        int32_t i_4 = 0
00443941        int32_t i_6 = 0
00443945        float out_angle
00443945        int32_t var_208
00443945        int32_t var_190[0x64]
00443945        if (game->level_definition.segment_count s> 0)
00443952        int32_t* ebx_1 = &game->level_definition.segment_slots[0].row_count
00443958        int32_t (* var_1f4_1)[0x64] = &var_190
0044395c        int32_t* var_214_1 = ebx_1
00443964        int32_t eax_1 = 0
00443966        var_208 = 0
0044396a        int32_t var_200_1 = 0
0044396e        *var_1f4_1 = 0x10
0044396e        *(var_1f4_1 + 1) = 0x27
0044396e        *(var_1f4_1 + 2) = 0
0044396e        *(var_1f4_1 + 3) = 0
00443982        int32_t ecx_3 = i_6 * 0x20c
0044398d        while (true)
0044398d        int32_t edx_4 = 0
00443991        if ((ebx_1 - 0xa87c)->level_definition.segment_slots[0].row_count s> 0)
0044399a        char (* var_1f0_1)[0x8][0x100] = &ebx_1[4]
0044399e        struct Vec3* out_angle_5 = &ebx_1[0x206]
004439a4        out_angle = out_angle_5
004439bb        while (true)
004439bb        if (((out_angle_5 - 0xb094)->:0xb08c.b & 1) != 0 && (out_angle_5 - 0xb094)->level_definition.segment_slots[0].rows[0].parcel_set_id == eax_1)
004439c3        if (eax_1 != 0)
00443a34        *(ecx_3 + &g_parcel_set_buckets.segment_index) = i_1
00443a43        *((*(ecx_3 + &g_parcel_set_buckets.candidate_count) << 4) + ecx_3 + &g_parcel_set_buckets) = edx_4
00443a55        int32_t* eax_13 = (*(ecx_3 + &g_parcel_set_buckets.candidate_count) << 4) + ecx_3 + &(*g_parcel_set_buckets.candidates)[0].position
00443a5c        *eax_13 = out_angle_5->x
00443a61        eax_13[1] = out_angle_5->y
00443a67        eax_13[2] = out_angle_5->z
00443a6e        *(ecx_3 + &g_parcel_set_buckets.set_id) = var_200_1
00443a7b        *(ecx_3 + &g_parcel_set_buckets.candidate_count) += 1
004439d0        int32_t eax_6 = i_3 * 0x20c
004439d3        (&g_zero_parcel_buckets)[i_3].segment_index = i_1
004439e2        *(((&g_zero_parcel_buckets)[i_3].candidate_count << 4) + eax_6 + &g_zero_parcel_buckets) = edx_4
004439f4        int32_t* ebx_6 = ((&g_zero_parcel_buckets)[i_3].candidate_count << 4) + eax_6 + &(*g_zero_parcel_buckets.candidates)[0].position
004439fb        *ebx_6 = out_angle_5->x
00443a00        ebx_6[1] = out_angle_5->y
00443a0a        ebx_6[2] = out_angle_5->z
00443a0d        (&g_zero_parcel_buckets)[i_3].set_id = 0
00443a1e        i_3 = i_4 + 1
00443a1f        (&g_zero_parcel_buckets)[i_3].candidate_count += 1
00443a2a        int32_t i_5 = i_3
00443a2e        out_angle_1 += 1
00443a8c        int32_t var_204_1 = 0
00443a94        char (* var_1ec_1)[0x8][0x100] = var_1f0_1
00443a9c        int32_t eax_21 = i_3 * 0x20c
00443bd6        bool cond:8_1
00443aaf        if (sx.d((var_1ec_1 - 0xa88c)->:0xa88c.b) == var_200_1 + 0x30)
00443abb        if (var_200_1 != 0)
00443b4b        *(ecx_3 + &g_parcel_set_buckets.segment_index) = i_1
00443b60        *((*(ecx_3 + &g_parcel_set_buckets.candidate_count) << 4) + ecx_3 + &g_parcel_set_buckets) = edx_4
00443b76        int32_t* edi_21 = (*(ecx_3 + &g_parcel_set_buckets.candidate_count) << 4) + ecx_3 + &(*g_parcel_set_buckets.candidates)[0].position
00443b7d        int32_t var_1d8_1 = 0
00443b85        int32_t var_1d4_1 = 0
00443b95        *edi_21 = fconvert.s(float.t(var_204_1) - fconvert.t(4f) + fconvert.t(0.5f))
00443b9b        edi_21[1] = var_1d8_1
00443ba2        edi_21[2] = var_1d4_1
00443ba9        *(ecx_3 + &g_parcel_set_buckets.set_id) = var_200_1
00443bb6        *(ecx_3 + &g_parcel_set_buckets.candidate_count) += 1
00443ac5        *(eax_21 + &g_zero_parcel_buckets.segment_index) = i_1
00443ada        *((*(eax_21 + &g_zero_parcel_buckets.candidate_count) << 4) + eax_21 + &g_zero_parcel_buckets) = edx_4
00443af0        int32_t* edi_14 = (*(eax_21 + &g_zero_parcel_buckets.candidate_count) << 4) + eax_21 + &(*g_zero_parcel_buckets.candidates)[0].position
00443af7        int32_t var_1e4_1 = 0
00443aff        int32_t var_1e0_1 = 0
00443b07        eax_21 += 0x20c
00443b14        *edi_14 = fconvert.s(float.t(var_204_1) - fconvert.t(4f) + fconvert.t(0.5f))
00443b1a        edi_14[1] = var_1e4_1
00443b21        edi_14[2] = var_1e0_1
00443b28        *(eax_21 + 0x53d188) = 0
00443b39        i_3 += 1
00443b3a        *(eax_21 + 0x53d184) += 1
00443b41        out_angle_1 += 1
00443bcb        cond:8_1 = var_204_1 + 1 s< 8
00443bce        var_204_1 += 1
00443bd2        var_1ec_1 = &(*var_1ec_1)[1]
00443bd6        do while (cond:8_1)
00443be4        edx_4 += 1
00443be5        out_angle_5 = out_angle i+ 0x38
00443be9        i_4 = i_3
00443bed        var_1f0_1 = &(*var_1f0_1)[0][1]
00443bf1        ebx_1 = var_214_1
00443bf5        out_angle = out_angle_5
00443bfb        if (edx_4 s>= (ebx_1 - 0xa87c)->level_definition.segment_slots[0].row_count)
00443bfb        break
004439aa        eax_1 = var_200_1
00443c01        int32_t eax_22 = *(ecx_3 + &g_parcel_set_buckets.candidate_count)
00443c09        if (eax_22 s> 0)
00443c0b        int32_t edx_5 = *(ecx_3 + &g_parcel_set_buckets.segment_index)
00443c21        int32_t __saved_edi
00443c21        if (eax_22 s< var_190[edx_5])
00443c23        (&__saved_edi)[edx_5 + 0x25] = eax_22
00443c29        if (eax_22 s> var_208)
00443c2b        var_208 = eax_22
00443c34        ecx_3 += 0x20c
00443c3a        i_6 += 1
00443c43        bool cond:5_1 = var_200_1 + 1 s< 0xa
00443c46        var_200_1 += 1
00443c4a        if (not(cond:5_1))
00443c4a        break
00443987        eax_1 = var_200_1
00443c58        i_1 += 1
00443c62        ebx_1 = &ebx_1[0x1088]
00443c6a        var_1f4_1 = &(*var_1f4_1)[1]
00443c6e        var_214_1 = ebx_1
00443c72        do while (i_1 s< game->level_definition.segment_count)
00443c81        int32_t parcel_count_2 = game->level_definition.parcel_count
00443c94        int32_t segment_count = game->level_definition.segment_count
00443ca5        int32_t esi_1 = parcel_count_2 * 0x50 s/ 0x64 - var_208
00443cb1        out_angle = out_angle_1
00443cb5        float out_angle_2
00443cb5        if (segment_count s<= 0)
00443ce2        out_angle_2 = out_angle
00443cb7        int32_t segment_count_1 = segment_count
00443cbb        out_angle_2 = out_angle
00443cbf        int32_t (* edx_14)[0x64] = &var_190
00443cde        bool cond:3_1
00443cc6        int32_t ecx_9 = *edx_14
00443cce        if (ecx_9 != 0x2710)
00443cd0        out_angle_2 += ecx_9
00443cd6        edx_14 = &(*edx_14)[1]
00443cd9        cond:3_1 = segment_count_1 != 1
00443cda        segment_count_1 -= 1
00443cde        do while (cond:3_1)
00443ce8        if (out_angle_2 s< parcel_count_2)
00443cf6        report_errorf("Parcel Allocation could fail in %s.  Add more parcel Sets", &game->level_definition.level_display_name)
00443d08        int32_t ecx_13 = game->level_definition.parcel_count - esi_1
00443d0c        if (ecx_13 s> out_angle_1)
00443d1a        ecx_13 = report_errorf("Parcel Allocation could fail in %s. Add more 0 parcels ", &game->level_definition.level_display_name)
00443d22        int32_t ebx_26 = 0
00443d26        int32_t var_210_1 = 0
00443d2a        int16_t x87control
00443d2a        if (esi_1 s> 0)
00443d30        int32_t i_2 = i_6
00443d36        while (i_2 s> 0)
00443d40        void* var_228_3 = &data_4a3f10
00443d45        int32_t var_22c_1 = ecx_13
00443d51        int32_t eax_29
00443d51        eax_29, x87control = ftol(x87control, random_float_below(fconvert.s(float.t(i_6))))
00443d58        int32_t var_214_2 = 0
00443d6b        int32_t candidate_count = (&g_parcel_set_buckets)[eax_29].candidate_count
00443d75        var_210_1 = ebx_26 + candidate_count
00443d79        if (candidate_count s> 0)
00443d7f        int32_t* ebx_28 = eax_29 * 0x20c + &(*g_parcel_set_buckets.candidates)[0].position
00443e59        bool cond:14_1
00443da8        float out_angle_3 = game->level_definition.segment_slots[(&g_parcel_set_buckets)[eax_29].segment_index].row_base + ebx_28[-1]
00443daa        out_angle = out_angle_3
00443db7        void* esi_3 = game + out_angle_3 i* 0xf4
00443dc1        if ((*(esi_3 + &data_5ccac8) & 0x10) != 0)
00443dd3        report_errorf("Duplicate Parcel Request in %s.", &game->level_definition.level_display_name)
00443dec        long double x87_r7_9 = float.t(out_angle)
00443df0        *(esi_3 + &data_5ccac8) |= 0x11
00443dfc        *(esi_3 + &data_5ccb58) = *ebx_28
00443e01        *(esi_3 + &data_5ccb5c) = ebx_28[1]
00443e07        *(esi_3 + &data_5ccb60) = ebx_28[2]
00443e16        *(esi_3 + &data_5ccb60) = fconvert.s(x87_r7_9 + fconvert.t(*(esi_3 + &data_5ccb60)) + fconvert.t(0.5f))
00443e28        *(esi_3 + &data_5ccb5c) = fconvert.s(fconvert.t(*(esi_3 + &data_5ccb5c)) + fconvert.t(1f))
00443e35        if ((*(esi_3 + &data_5ccac8) & 0x20) != 0)
00443e43        *(esi_3 + &data_5ccb58) = fconvert.s(fconvert.t(*(esi_3 + &data_5ccb58)) * fconvert.t(-1f))
00443e50        ebx_28 = &ebx_28[4]
00443e53        cond:14_1 = var_214_2 + 1 s< (&g_parcel_set_buckets)[eax_29].candidate_count
00443e55        var_214_2 += 1
00443e59        do while (cond:14_1)
00443e5f        int32_t segment_index = (&g_parcel_set_buckets)[eax_29].segment_index
00443e65        int32_t ecx_29 = 0
00443e6b        i_2 = i_6
00443e71        int32_t var_208_2 = 0
00443e75        if (i_2 s> 0)
00443e7b        float out_angle_6 = i_2 - 1
00443e7e        int32_t* edx_21 = &data_648bf4
00443e83        int32_t* esi_4 = &g_parcel_set_buckets.segment_index
00443e88        out_angle = out_angle_6
00443e8c        int32_t* var_1f0_2 = &data_648bf4
00443e90        int32_t* var_1f4_2 = &g_parcel_set_buckets.segment_index
00443e9a        if ((esi_4 - 0x208)->segment_index == segment_index)
00443ea2        if (ecx_29 s< out_angle_6)
00443ea4        int32_t* eax_37 = edx_21
00443eaa        int32_t var_214_3 = out_angle_6 i- ecx_29
00443f10        bool cond:16_1
00443eb0        int32_t j = 0
00443eb4        if (*eax_37 s> 0)
00443eb6        int32_t* ecx_30 = &eax_37[-0x103]
00443ebc        int32_t* esi_6 = &ecx_30[0x83]
00443ec2        int32_t* edi_33 = ecx_30
00443ec4        j += 1
00443ec5        ecx_30 = &ecx_30[4]
00443eca        *edi_33 = *esi_6
00443ecf        edi_33[1] = esi_6[1]
00443ed5        edi_33[2] = esi_6[2]
00443edb        edi_33[3] = esi_6[3]
00443ee2        do while (j s< *eax_37)
00443ee4        ecx_29 = var_208_2
00443eea        eax_37[-0x83] = *eax_37
00443ef3        eax_37[-0x81] = eax_37[2]
00443efc        eax_37[-0x82] = eax_37[1]
00443f06        eax_37 = &eax_37[0x83]
00443f0b        cond:16_1 = var_214_3 != 1
00443f0c        var_214_3 -= 1
00443f10        do while (cond:16_1)
00443f12        out_angle_6 = out_angle
00443f16        edx_21 = var_1f0_2
00443f1a        esi_4 = var_1f4_2
00443f22        ecx_29 -= 1
00443f23        esi_4 -= 0x20c
00443f29        edx_21 -= 0x20c
00443f2f        int32_t i_7 = i_6 - 1
00443f30        out_angle_6 -= 1
00443f31        i_6 = i_7
00443f35        out_angle = out_angle_6
00443f39        i_2 = i_7
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
00443f76        if (ebx_26 s< game->level_definition.parcel_count)
00443f7c        int32_t parcel_count_1 = i_3 - 1
00443f7f        int32_t parcel_count_4 = parcel_count_1
00443f85        while (i_3 s> 0)
00443f8f        void* var_228_5 = &data_4a3f0c
00443f94        int32_t parcel_count_3 = parcel_count_1
00443fa0        int32_t eax_39
00443fa0        eax_39, x87control = ftol(x87control, random_float_below(fconvert.s(float.t(i_4))))
00443fc4        int32_t segment_index_1 = (&g_zero_parcel_buckets)[eax_39].segment_index
00443fcc        var_210_1 += (&g_zero_parcel_buckets)[eax_39].candidate_count
00443fe0        out_angle = &(&g_zero_parcel_buckets)[eax_39]
00443fee        int32_t edx_38
00443fee        edx_38.b = (&g_zero_parcel_buckets)[eax_39].candidates[0].row.b
00443fee        edx_38:1.b = (&(*g_zero_parcel_buckets.candidates)[0].row:1)[eax_39].candidates[0].row.b
00443fee        edx_38:2.b = (&(*g_zero_parcel_buckets.candidates)[0].row:2)[eax_39].candidates[0].row.b
00443fee        edx_38:3.b = (&(*g_zero_parcel_buckets.candidates)[0].row:3)[eax_39].candidates[0].row.b
00443ff0        int32_t eax_42 = game->level_definition.segment_slots[segment_index_1].row_base + edx_38
00443ffc        int32_t edx_39 = eax_42 * 0x3d
00444008        void* edi_35 = game + (edx_39 << 2)
0044400b        if ((*(&game->runtime_rows + (edx_39 << 2)) & 0x10) != 0)
0044401c        report_errorf("Duplicate Parcel Request in %s.", &game->level_definition.level_display_name)
00444033        char* ecx_36 = eax_39 * 0x20c + &(*g_zero_parcel_buckets.candidates)[0].position
0044403d        *(edi_35 + &data_5ccac8) |= 0x11
00444043        float esi_11
00444043        esi_11.b = *ecx_36
00444043        esi_11:1.b = ecx_36[1]
00444043        esi_11:2.b = ecx_36[2]
00444043        esi_11:3.b = ecx_36[3]
00444047        *(edi_35 + &data_5ccb58) = esi_11
0044404c        *(edi_35 + &data_5ccb5c) = *(ecx_36 + 4)
0044404f        int32_t ecx_37
0044404f        ecx_37.b = ecx_36[8]
0044404f        ecx_37:1.b = ecx_36[9]
00444052        *(edi_35 + &data_5ccb60) = ecx_37
00444061        *(edi_35 + &data_5ccb60) = fconvert.s(float.t(eax_42) + fconvert.t(*(edi_35 + &data_5ccb60)) + fconvert.t(0.5f))
00444073        *(edi_35 + &data_5ccb5c) = fconvert.s(fconvert.t(*(edi_35 + &data_5ccb5c)) + fconvert.t(1f))
00444080        if ((*(edi_35 + &data_5ccac8) & 0x20) != 0)
0044408a        *(edi_35 + &data_5ccb58) = fconvert.s(fconvert.t(*(edi_35 + &data_5ccb58)) * fconvert.t(-1f))
00444092        if (eax_39 s< parcel_count_4)
00444094        float out_angle_4 = out_angle
00444098        int32_t j_2 = parcel_count_4 - eax_39
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
004440eb        parcel_count_1 = game->level_definition.parcel_count
004440f1        parcel_count_4 -= 1
004440f9        i_4 = i_3
004440ff        if (var_210_1 s>= parcel_count_1)
004440ff        break
0044410d        int32_t parcel_count = game->level_definition.parcel_count
00444115        if (var_210_1 != parcel_count)
00444124        report_errorf("Did not generate required Parcels(%i) in %s", parcel_count, &game->level_definition.level_display_name)
00444129        int32_t parcel_quota = game->level_definition.parcel_quota
00444134        if (parcel_quota != 0)
00444142        game->level_definition.parcel_quota = divs.dp.d(sx.q(game->level_definition.parcel_count * var_210_1), parcel_quota)
00444148        game->level_definition.parcel_count = var_210_1
00444153        int32_t var_214_5 = 0
0044415b        if (game->runtime_row_count s<= 0)
0044415b        return
00444161        int32_t* esi_18 = &game->runtime_rows
0044422b        bool cond:12_1
00444167        char eax_53 = (*esi_18).b
00444173        if ((eax_53 & 1) != 0 && (eax_53 & 0x40) != 0)
0044417f        int32_t eax_54 = get_track_cell_row_index(esi_18[0x29])
0044418c        int32_t eax_55
0044418c        eax_55, x87control = ftol(x87control, fconvert.t(esi_18[0x26]))
00444193        int32_t node = eax_55 - eax_54
00444195        if (eax_55 - eax_54 s< 0)
00444197        node = 0
00444199        SubLoc* cell = esi_18[0x29]
0044419f        struct Path* attachment_template_record = cell->attachment_template_record
004441a6        if (attachment_template_record->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
00444201        int32_t row_index = get_track_cell_row_index(cell)
00444212        get_path_position_at_node(*(esi_18[0x29] + 0x38), &esi_18[0x24], node, row_index, &esi_18[0x24])
004441d9        struct TransformMatrix transform
004441d9        x87control = compute_kind42_attachment_transform(attachment_template_record, (&attachment_template_record->primary_samples->special_scalar)[node * 0x2a], esi_18[0x24], esi_18[0x25], &transform, &out_angle)
004441e5        float y = transform.position.y
004441ec        esi_18[0x24] = transform.position.x
004441f2        esi_18[0x25] = y
0044421f        esi_18 = &esi_18[0x3d]
00444225        cond:12_1 = var_214_5 + 1 s< game->runtime_row_count
00444227        var_214_5 += 1
0044422b        do while (cond:12_1)
0044423b        return
