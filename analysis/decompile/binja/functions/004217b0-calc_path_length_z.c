/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_path_length_z @ 0x4217b0 */

004217c5        struct Path* template_record_1 = state->template_record
004217c8        struct PathTemplateSample* secondary_samples_3 = template_record_1->secondary_samples
004217d4        int32_t eax_2 = state->sample_index * 0x15
004217d7        long double x87_r7_1 = fconvert.t(path_factor) * fconvert.t((&secondary_samples_3->delta_length)[eax_2 * 2])
004217e7        long double x87_r6_1 = x87_r7_1 + fconvert.t(state->progress)
004217ea        long double temp1 = fconvert.t((&secondary_samples_3->delta_length)[eax_2 * 2])
004217ea        x87_r6_1 - temp1
004217f1        float var_ec
004217f1        if ((((x87_r6_1 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, temp1) ? 1 : 0) << 0xa | (x87_r6_1 == temp1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0042183d        long double temp2_1
004217f3        int32_t sample_index = state->sample_index
00421809        long double x87_r6_3 = fconvert.t((&secondary_samples_3->delta_length)[sample_index * 0x2a]) - fconvert.t(state->progress)
0042180f        state->progress = 0f
00421816        state->sample_index = sample_index + 1
0042181e        x87_r7_1 = x87_r7_1 - x87_r6_3
00421820        if (sample_index + 1 == template_record_1->segment_count)
00421882        state->active = 0
004218ad        velocity->z = fconvert.s(fconvert.t(path_factor) * fconvert.t(*(&template_record_1->secondary_samples[template_record_1->segment_count] - 0x1c)))
004218b5        struct Vec3* edx_2 = &state->shot->flight_transform.position
004218bb        edx_2->x = state->output_position.x
004218c0        edx_2->y = state->output_position.y
004218c6        edx_2->z = state->output_position.z
004218c9        struct Path* template_record = state->template_record
004218d0        if (template_record->kind != PATH_TEMPLATE_KIND_SUPERTRAMP)
004219d1        long double x87_r7_6 = x87_r7_1 + fconvert.t(*(&template_record->secondary_samples[template_record->segment_count] - 0x70)) + fconvert.t(state->source_cell->anchor_position.z) + fconvert.t(template_record->width_or_scale)
004219d5        position->z = fconvert.s(x87_r7_6)
004219dc        state->shot->flight_transform.position.z = fconvert.s(x87_r7_6)
004219ed        return 3
004218e0        velocity->y = fconvert.s(fconvert.t(velocity->z) * fconvert.t(0.699999988f))
004218ea        float edx_3
004218ea        edx_3.b = position->x.b
004218ea        edx_3:1.b = position->x:1.b
004218ea        edx_3:2.b = position->x:2.b
004218ea        edx_3:3.b = position->x:3.b
004218ec        var_ec = edx_3
004218f0        struct Path* template_record_2 = state->template_record
004218f6        long double x87_r7_3 = x87_r7_1 + fconvert.t(template_record_2->width_or_scale)
004218f9        struct PathTemplateSample* secondary_samples_2 = template_record_2->secondary_samples
00421906        uint32_t eax_22 = template_record_2->segment_count * 0x15
00421912        void* eax_23 = secondary_samples_2 + (eax_22 << 3)
00421918        struct Vec3* edx_5 = &state->source_cell->anchor_position
0042192b        long double x87_r7_4 = x87_r7_3 * fconvert.t(*(eax_23 - 0x80))
00421945        float var_c4 = fconvert.s(fconvert.t(*(eax_23 - 0x70)) + fconvert.t(edx_5->z))
00421955        long double x87_r6_16 = fconvert.t(fconvert.s(fconvert.t(*(eax_23 - 0x74)) + fconvert.t(edx_5->y))) + fconvert.t(fconvert.s(x87_r7_3 * fconvert.t(*(eax_23 - 0x84))))
0042195d        position->x = fconvert.s(fconvert.t(edx_5->x) + fconvert.t(*(eax_23 - 0x78)) + fconvert.t(fconvert.s(x87_r7_3 * fconvert.t(*(secondary_samples_2 + (eax_22 << 3) - 0x88)))))
0042196d        position->y = fconvert.s(x87_r6_16)
00421978        position->z = fconvert.s(fconvert.t(var_c4) + x87_r7_4)
0042197b        float eax_25 = var_ec
0042197f        position->x.b = eax_25.b
0042197f        position->x:1.b = eax_25:1.b
0042197f        position->x:2.b = eax_25:2.b
0042197f        position->x:3.b = eax_25:3.b
00421984        int32_t* edx_10 = &state->shot->flight_transform.position
0042198d        *edx_10 = eax_25
00421992        edx_10[1] = position->y
0042199d        edx_10[2] = position->z
004219a6        return 3
00421822        secondary_samples_3 = template_record_1->secondary_samples
00421831        temp2_1 = fconvert.t((&secondary_samples_3->delta_length)[(sample_index + 1) * 0x2a])
00421831        x87_r7_1 - temp2_1
0042183d        do while ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00421843        int32_t sample_index_1 = state->sample_index
00421846        float var_f0 = fconvert.s(x87_r7_1 + fconvert.t(state->progress))
0042184e        state->progress = var_f0
00421854        int32_t edi = template_record_1->segment_count - 1
00421857        int32_t eax_11 = sample_index_1 << 3
00421860        float var_e8
00421860        int32_t eax_14
00421860        void* ecx_7
00421860        if (sample_index_1 != edi)
004219ff        eax_14 = (eax_11 - sample_index_1) * 0x18
00421a02        ecx_7 = template_record_1->primary_samples + eax_14
00421a1f        var_e8 = fconvert.s(fconvert.t(var_f0) / fconvert.t(*(&template_record_1->secondary_samples->delta_length + eax_14)) * (fconvert.t(*(ecx_7 + 0x138)) - fconvert.t(*(ecx_7 + 0x90))) + fconvert.t(*(ecx_7 + 0x90)))
0042186e        eax_14 = (eax_11 - sample_index_1) * 0x18
00421871        ecx_7 = template_record_1->primary_samples + eax_14
00421879        var_e8 = *(ecx_7 + 0x90)
00421a25        float var_f4
00421a25        if (sample_index_1 != edi)
00421a55        var_f4 = fconvert.s(fconvert.t(var_f0) / fconvert.t(*(&template_record_1->secondary_samples->delta_length + eax_14)) * (fconvert.t(*(ecx_7 + 0x144)) - fconvert.t(*(ecx_7 + 0x9c))) + fconvert.t(*(ecx_7 + 0x9c)))
00421a2d        var_f4 = *(ecx_7 + 0x9c)
00421a5b        if (sample_index_1 != edi)
00421a8b        var_ec = fconvert.s(fconvert.t(var_f0) / fconvert.t(*(&template_record_1->secondary_samples->delta_length + eax_14)) * (fconvert.t(*(ecx_7 + 0x148)) - fconvert.t(*(ecx_7 + 0xa0))) + fconvert.t(*(ecx_7 + 0xa0)))
00421a63        var_ec = *(ecx_7 + 0xa0)
00421a93        struct TransformMatrix var_c0
00421a93        struct Vec3* ecx_20
00421a93        struct Vec3* velocity_1
00421a93        struct Vec3* position_1
00421a93        if (template_record_1->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
00421b3c        struct PathTemplateSample* secondary_samples_1 = template_record_1->secondary_samples
00421b4c        void* esi_10 = eax_14 + secondary_samples_1
00421b4f        struct TrackRowCell* source_cell = state->source_cell
00421b5c        float var_e4_2 = fconvert.s(fconvert.t(var_f0) * fconvert.t(*(&secondary_samples_1->delta_dir_to_next + eax_14)) * fconvert.t(var_f4) + fconvert.t(*(esi_10 + 0x30)) + fconvert.t(source_cell->anchor_position.x))
00421b74        float var_e0_2 = fconvert.s(fconvert.t(var_f0) * fconvert.t(*(esi_10 + 0x84)) * fconvert.t(var_f4) + fconvert.t(*(esi_10 + 0x34)) + fconvert.t(source_cell->anchor_position.y))
00421b88        float var_dc_2 = fconvert.s(fconvert.t(var_f0) * fconvert.t(*(esi_10 + 0x88)) + fconvert.t(*(esi_10 + 0x38)) + fconvert.t(source_cell->anchor_position.z))
00421b8c        if (sample_index_1 != edi)
00421ba9        struct TransformMatrix from
00421ba9        __builtin_memcpy(&from, esi_10, 0x40)
00421bcd        struct TransformMatrix to
00421bcd        int32_t ecx_25 = __builtin_memcpy(&to, &template_record_1->secondary_samples[sample_index_1 + 1], 0x40)
00421be5        __builtin_memset(&from.position, 0, 0xc)
00421c06        __builtin_memset(&to.position, 0, 0xc)
00421c14        int32_t var_108_2 = ecx_25
00421c33        linear_interpolate_matrix(&var_c0, &from, &to, fconvert.s(fconvert.t(var_f0) / fconvert.t(*(&template_record_1->secondary_samples->delta_length + eax_14))))
00421b92        set_matrix_identity(&var_c0)
00421c40        velocity_1 = velocity
00421c47        position_1 = position
00421c4e        ecx_20 = &state->output_position
00421c51        int32_t* eax_37 = ecx_20
00421c53        var_c0.basis_right.x = fconvert.s(fconvert.t(var_c0.basis_right.x) * fconvert.t(var_f4))
00421c5f        var_c0.basis_right.y = fconvert.s(fconvert.t(var_c0.basis_right.y) * fconvert.t(var_f4))
00421c6b        var_c0.basis_right.z = fconvert.s(fconvert.t(var_c0.basis_right.z) * fconvert.t(var_f4))
00421c75        state->vertical_offset = fconvert.s(fconvert.t(velocity_1->y) + fconvert.t(state->vertical_offset))
00421c7a        long double x87_r7_50 = fconvert.t(position_1->x) - fconvert.t(var_e8)
00421c92        long double x87_r7_51 = x87_r7_50 * fconvert.t(var_c0.basis_right.z)
00421ca6        long double x87_r6_44 = fconvert.t(fconvert.s(fconvert.t(var_c0.basis_right.y) * x87_r7_50)) + fconvert.t(var_e0_2)
00421cae        *eax_37 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(var_c0.basis_right.x))) + fconvert.t(var_e4_2))
00421cbc        eax_37[1] = fconvert.s(x87_r6_44)
00421cc7        eax_37[2] = fconvert.s(x87_r7_51 + fconvert.t(var_dc_2))
00421a99        position_1 = position
00421ab9        struct TransformMatrix* var_114_1 = &var_c0
00421ac0        compute_kind42_attachment_transform(template_record_1, var_ec, fconvert.s(fconvert.t(position_1->x) - fconvert.t(var_e8)), 0.49000001f, &var_c0, &var_ec)
00421ad4        int32_t ecx_18 = state->sample_index * 0x15
00421ad7        struct PathTemplateSample* secondary_samples = state->template_record->secondary_samples
00421ada        velocity_1 = velocity
00421af4        ecx_20 = &state->output_position
00421af7        long double x87_r7_24 = fconvert.t((&secondary_samples->delta_dir_to_next.z)[ecx_18 * 2]) * fconvert.t(state->progress) + fconvert.t(state->source_cell->anchor_position.z) + fconvert.t((&secondary_samples->transform.position.z)[ecx_18 * 2])
00421b02        float x = var_c0.position.x
00421b06        var_c0.basis_right.x = fconvert.s(fconvert.t(var_c0.basis_right.x) * fconvert.t(var_f4))
00421b12        var_c0.basis_right.y = fconvert.s(fconvert.t(var_c0.basis_right.y) * fconvert.t(var_f4))
00421b1e        var_c0.basis_right.z = fconvert.s(fconvert.t(var_c0.basis_right.z) * fconvert.t(var_f4))
00421b28        ecx_20->x.b = x.b
00421b28        ecx_20->x:1.b = x:1.b
00421b28        ecx_20->x:2.b = x:2.b
00421b28        ecx_20->x:3.b = x:3.b
00421b2e        state->output_position.y = var_c0.position.y
00421b31        state->vertical_offset = fconvert.s(fconvert.t(velocity_1->y) + fconvert.t(state->vertical_offset))
00421b34        state->output_position.z = fconvert.s(x87_r7_24)
00421cd1        struct TransformMatrix* eax_39 = &state->shot->flight_transform
00421cd6        eax_39->basis_right.x = var_c0.basis_right.x
00421cdc        eax_39->basis_right.y = var_c0.basis_right.y
00421ce3        eax_39->basis_right.z = var_c0.basis_right.z
00421ced        struct Vec3* eax_41 = &state->shot->flight_transform.basis_up
00421cf2        eax_41->x = var_c0.basis_up.x
00421cf8        eax_41->y = var_c0.basis_up.y
00421cff        eax_41->z = var_c0.basis_up.z
00421d09        struct Vec3* eax_43 = &state->shot->flight_transform.basis_forward
00421d0e        eax_43->x = var_c0.basis_forward.x
00421d14        eax_43->y = var_c0.basis_forward.y
00421d1b        eax_43->z = var_c0.basis_forward.z
00421d1e        struct GolbShot* shot = state->shot
00421d2e        shot->velocity.x = shot->direction.x
00421d33        shot->velocity.y = shot->direction.y
00421d3a        shot->velocity.z = shot->direction.z
00421d3f        long double x87_r7_54 = fconvert.t(position_1->x) - fconvert.t(var_e8)
00421d43        long double temp3 = fconvert.t(0f)
00421d43        x87_r7_54 - temp3
00421d4e        if ((((x87_r7_54 < temp3 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_54, temp3) ? 1 : 0) << 0xa | (x87_r7_54 == temp3 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00421d50        x87_r7_54 = fneg(x87_r7_54)
00421d52        struct Path* template_record_3 = state->template_record
00421d64        long double x87_r7_55 = float.t(template_record_3->width_cells) * fconvert.t(0.5f) + fconvert.t(0.300000012f)
00421d66        x87_r7_54 - x87_r7_55
00421d6d        if ((((x87_r7_54 < x87_r7_55 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_54, x87_r7_55) ? 1 : 0) << 0xa | (x87_r7_54 == x87_r7_55 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00421da9        if (template_record_3->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
00421daf        position_1->x = fconvert.s(fconvert.t(position_1->x) + fconvert.t(velocity_1->x))
00421dbc        return 0
00421d72        int32_t eax_46
00421d72        eax_46.b = ecx_20->x.b
00421d72        eax_46:1.b = ecx_20->x:1.b
00421d72        eax_46:2.b = ecx_20->x:2.b
00421d72        eax_46:3.b = ecx_20->x:3.b
00421d74        struct Vec3* edx_17 = &state->shot->flight_transform.position
00421d7a        state->active = 0
00421d80        edx_17->x = eax_46
00421d85        edx_17->y = ecx_20->y
00421d8b        int32_t result = 0
00421d8d        edx_17->z = ecx_20->z
00421d99        result.b = state->template_record->side_exit_mode == 0
00421da2        return result
