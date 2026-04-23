/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_attachment_follow_state @ 0x420cb0 */

00420cc2        uint32_t sample_index_2 = follow_state->sample_index
00420cc5        struct PathTemplate* template_record_6 = follow_state->template_record
00420cc9        struct PathTemplateSample* secondary_samples_4 = template_record_6->secondary_samples
00420cd5        uint32_t eax_2 = sample_index_2 * 0x15
00420cd8        long double x87_r7_1 = fconvert.t(path_factor) * fconvert.t((&secondary_samples_4->delta_length)[eax_2 * 2])
00420cdf        float* edx = &(&secondary_samples_4->delta_length)[eax_2 * 2]
00420ce6        float var_180 = fconvert.s(x87_r7_1)
00420cea        long double x87_r7_2 = x87_r7_1 + fconvert.t(follow_state->progress)
00420ced        long double temp1 = fconvert.t(*edx)
00420ced        x87_r7_2 - temp1
00420cef        eax_2.w = (x87_r7_2 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1 ? 1 : 0) << 0xe
00420cf4        if ((eax_2:1.b & 0x41) == 0)
00420ea1        struct PathTemplateSample* secondary_samples
00420d06        long double x87_r7_4 = fconvert.t(*edx) - fconvert.t(follow_state->progress)
00420d0a        follow_state->progress = 0f
00420d11        follow_state->sample_index = sample_index_2 + 1
00420d1f        var_180 = fconvert.s(fconvert.t(var_180) - x87_r7_4)
00420d23        if (sample_index_2 + 1 == template_record_6->segment_count << 1)
00420d30        play_voice_manager(0x751498, 4, 1, 0xffffffff)
00420d35        struct PathTemplate* template_record = follow_state->template_record
00420d38        uint32_t ecx
00420d38        ecx.b = template_record->special_runtime_flag_9c
00420d40        if (ecx.b != 0)
00420d46        uint32_t segment_count = template_record->segment_count
00420d49        uint32_t sample_index_4 = follow_state->sample_index
00420d51        if (sample_index_4 != segment_count - 1)
00420ddb        if (sample_index_4 == segment_count * 3 s/ 7)
00420de4        int32_t eax_12 = get_track_cell_row_index(follow_state->source_cell)
00420df7        void* eax_14 = *(data_4df904 + eax_12 * 0xf4 + 0x641184)
00420e03        *(eax_14 + 4) |= 0x80
00420e09        int32_t eax_15 = get_track_cell_row_index(follow_state->source_cell)
00420e23        void* esi_1 = *(*(data_4df904 + eax_15 * 0xf4 + 0x641184) + 0x38)
00420e29        int32_t eax_17 = get_track_cell_row_index(follow_state->source_cell)
00420e4a        *(*(data_4df904 + eax_17 * 0xf4 + 0x641184) + 0x24) = *(esi_1 + 0xa0)
00420e50        int32_t eax_20 = get_track_cell_row_index(follow_state->source_cell)
00420e6a        *(*(data_4df904 + eax_20 * 0xf4 + 0x641184) + 0x34) = 0x3f19999a
00420d56        int32_t eax_5 = get_track_cell_row_index(follow_state->source_cell)
00420d74        void* esi = *(*(data_4df904 + eax_5 * 0xf4 + 0x641184) + 0x38)
00420d77        int32_t eax_7 = get_track_cell_row_index(follow_state->source_cell)
00420d97        *(*(data_4df904 + eax_7 * 0xf4 + 0x641184) + 0x24) = *(esi + 0xa4)
00420d9d        int32_t eax_9 = get_track_cell_row_index(follow_state->source_cell)
00420db7        *(*(data_4df904 + eax_9 * 0xf4 + 0x641184) + 0x34) = 0x3f800000
00420e6d        template_record_6 = follow_state->template_record
00420e70        sample_index_2 = follow_state->sample_index
00420e76        if (sample_index_2 == template_record_6->segment_count)
00420ef0        long double x87_r7_10 = fconvert.t(var_180)
00420ef4        long double temp2 = fconvert.t(1f)
00420ef4        x87_r7_10 - temp2
00420efa        follow_state->active = 0
00420efe        template_record.w = (x87_r7_10 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2) ? 1 : 0) << 0xa | (x87_r7_10 == temp2 ? 1 : 0) << 0xe
00420f03        if ((template_record:1.b & 1) == 0)
00420f05        var_180 = 0.999000013f
00420f0d        struct PathTemplate* template_record_1 = follow_state->template_record
00420f30        long double x87_r7_12 = fconvert.t(path_factor) * fconvert.t(*(&template_record_1->secondary_samples[template_record_1->segment_count] - 0x1c))
00420f34        motion->z = fconvert.s(x87_r7_12)
00420f37        long double temp4 = fconvert.t(1f)
00420f37        x87_r7_12 - temp4
00420f3d        struct PathTemplateSample* eax_30
00420f3d        eax_30.w = (x87_r7_12 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp4) ? 1 : 0) << 0xa | (x87_r7_12 == temp4 ? 1 : 0) << 0xe
00420f42        if ((eax_30:1.b & 0x41) == 0)
00420f44        motion->z = 1f
00420f4b        struct PathTemplate* template_record_4 = follow_state->template_record
00420f52        if (template_record_4->kind != PATH_TEMPLATE_KIND_SUPERTRAMP)
00421077        out_position->z = fconvert.s(fconvert.t(*(&template_record_4->secondary_samples[template_record_4->segment_count] - 0x70)) + fconvert.t(follow_state->source_cell->anchor_position.z) + fconvert.t(template_record_4->width_or_scale) + fconvert.t(var_180))
00420f68        int32_t sample_override = 0xffffffff
00420f6a        int32_t mode = 0
00420f6c        int32_t set_id = 0xf
00420f6e        motion->y = fconvert.s(fconvert.t(motion->z) * fconvert.t(0.699999988f))
00420f71        struct PathTemplate* template_record_2 = follow_state->template_record
00420f74        long double x87_r7_15 = fconvert.t(out_position->x)
00420f7d        long double x87_r6_2 = fconvert.t(var_180) + fconvert.t(template_record_2->width_or_scale)
00420f80        struct PathTemplateSample* secondary_samples_2 = template_record_2->secondary_samples
00420f8c        uint32_t eax_33 = template_record_2->segment_count * 0x15
00420f98        void* eax_34 = secondary_samples_2 + (eax_33 << 3)
00420f9e        struct Vec3* ecx_34 = &follow_state->source_cell->anchor_position
00420fb7        long double x87_r6_3 = x87_r6_2 * fconvert.t(*(eax_34 - 0x80))
00420fd1        float var_11c_1 = fconvert.s(fconvert.t(*(eax_34 - 0x70)) + fconvert.t(ecx_34->z))
00420fe7        long double x87_r5_9 = fconvert.t(fconvert.s(fconvert.t(*(eax_34 - 0x74)) + fconvert.t(ecx_34->y))) + fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(*(eax_34 - 0x84))))
00420ff2        out_position->x = fconvert.s(fconvert.t(ecx_34->x) + fconvert.t(*(eax_34 - 0x78)) + fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(*(secondary_samples_2 + (eax_33 << 3) - 0x88)))))
00421005        out_position->y = fconvert.s(x87_r5_9)
00421012        out_position->z = fconvert.s(fconvert.t(var_11c_1) + x87_r6_3)
00421015        out_position->x = fconvert.s(x87_r7_15)
0042102c        follow_state->player->cutscene_pitch_cycle_step = fconvert.s(fconvert.t(*(data_4df904 + 0x74650)) * fconvert.t(0.0138888881f))
00421032        struct Player* player = follow_state->player
0042103b        player->cutscene_pitch_cycle = player->cutscene_pitch_cycle_step
00421046        play_voice_manager(0x751498, set_id, mode, sample_override)
0042107d        struct Player* player_1 = follow_state->player
00421090        player_1->heading_roll = fconvert.s(fconvert.t(follow_state->template_record->installed_heading_delta) + fconvert.t(player_1->heading_roll))
004210a1        return 3
00420e83        long double x87_r7_7 = fconvert.t(var_180) + fconvert.t(follow_state->progress)
00420e88        uint32_t edx_15 = sample_index_2 * 0x15
00420e8b        secondary_samples = template_record_6->secondary_samples
00420e8e        long double temp3_1 = fconvert.t((&secondary_samples->delta_length)[edx_15 * 2])
00420e8e        x87_r7_7 - temp3_1
00420e95        edx = &(&secondary_samples->delta_length)[edx_15 * 2]
00420e9c        secondary_samples.w = (x87_r7_7 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp3_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp3_1 ? 1 : 0) << 0xe
00420ea1        do while ((secondary_samples:1.b & 0x41) == 0)
00420eae        uint32_t sample_index_3 = follow_state->sample_index
00420eb1        float var_17c = fconvert.s(fconvert.t(var_180) + fconvert.t(follow_state->progress))
00420eb9        follow_state->progress = var_17c
00420ebc        struct PathTemplate* template_record_3 = follow_state->template_record
00420ec2        int32_t edi = template_record_3->segment_count - 1
00420ec5        uint32_t eax_24 = sample_index_3 << 3
00420ece        float var_168
00420ece        uint32_t eax_27
00420ece        void* ecx_31
00420ece        if (sample_index_3 != edi)
004210b3        eax_27 = (eax_24 - sample_index_3) * 0x18
004210b6        ecx_31 = template_record_3->primary_samples + eax_27
004210d3        var_168 = fconvert.s(fconvert.t(var_17c) / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_27)) * (fconvert.t(*(ecx_31 + 0x138)) - fconvert.t(*(ecx_31 + 0x90))) + fconvert.t(*(ecx_31 + 0x90)))
00420edc        eax_27 = (eax_24 - sample_index_3) * 0x18
00420edf        ecx_31 = template_record_3->primary_samples + eax_27
00420ee7        var_168 = *(ecx_31 + 0x90)
004210d9        float var_180_1
004210d9        if (sample_index_3 != edi)
00421109        var_180_1 = fconvert.s(fconvert.t(var_17c) / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_27)) * (fconvert.t(*(ecx_31 + 0x144)) - fconvert.t(*(ecx_31 + 0x9c))) + fconvert.t(*(ecx_31 + 0x9c)))
004210e1        var_180_1 = *(ecx_31 + 0x9c)
0042110f        float var_178
0042110f        if (sample_index_3 != edi)
0042113f        var_178 = fconvert.s(fconvert.t(var_17c) / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_27)) * (fconvert.t(*(ecx_31 + 0x148)) - fconvert.t(*(ecx_31 + 0xa0))) + fconvert.t(*(ecx_31 + 0xa0)))
00421117        var_178 = *(ecx_31 + 0xa0)
00421147        struct TransformMatrix var_164
00421147        struct Vec3* out_position_1
00421147        struct Vec3* esi_9
00421147        float* edi_1
00421147        if (template_record_3->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
004212dc        struct PathTemplateSample* secondary_samples_3 = template_record_3->secondary_samples
004212ec        void* esi_10 = secondary_samples_3 + eax_27
004212ef        struct TrackRowCell* source_cell = follow_state->source_cell
004212fc        float var_174_2 = fconvert.s(fconvert.t(var_17c) * fconvert.t(*(&secondary_samples_3->delta_dir_to_next + eax_27)) * fconvert.t(var_180_1) + fconvert.t(source_cell->anchor_position.x) + fconvert.t(*(esi_10 + 0x30)))
00421314        float var_170_2 = fconvert.s(fconvert.t(var_17c) * fconvert.t(*(esi_10 + 0x84)) * fconvert.t(var_180_1) + fconvert.t(source_cell->anchor_position.y) + fconvert.t(*(esi_10 + 0x34)))
00421328        float var_16c_2 = fconvert.s(fconvert.t(var_17c) * fconvert.t(*(esi_10 + 0x88)) + fconvert.t(source_cell->anchor_position.z) + fconvert.t(*(esi_10 + 0x38)))
0042132c        if (sample_index_3 != edi)
00421349        struct TransformMatrix from
00421349        __builtin_memcpy(&from, esi_10, 0x40)
0042134b        long double x87_r7_58 = fconvert.t(var_17c)
0042136d        struct TransformMatrix to
0042136d        int32_t ecx_62 = __builtin_memcpy(&to, &template_record_3->secondary_samples[sample_index_3 + 1], 0x40)
0042136f        from.position.z = 0
0042137a        from.position.y = 0
00421385        from.position.x = 0
00421390        to.position.z = 0
0042139b        to.position.y = 0
004213a6        to.position.x = 0
004213b4        int32_t var_194_3 = ecx_62
004213d3        linear_interpolate_matrix(&var_164, &from, &to, fconvert.s(x87_r7_58 / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_27))))
00421332        set_matrix_identity(&var_164)
004213ee        esi_9 = &follow_state->output_position
004213f1        out_position_1 = out_position
004213f8        edi_1 = &motion->y
004213fd        var_164.basis_right.x = fconvert.s(fconvert.t(var_164.basis_right.x) * fconvert.t(var_180_1))
00421409        var_164.basis_right.y = fconvert.s(fconvert.t(var_164.basis_right.y) * fconvert.t(var_180_1))
00421415        var_164.basis_right.z = fconvert.s(fconvert.t(var_164.basis_right.z) * fconvert.t(var_180_1))
0042141b        long double x87_r7_67 = fconvert.t((edi_1 - 4)->y) + fconvert.t(follow_state->vertical_offset)
0042141e        follow_state->vertical_offset = fconvert.s(x87_r7_67)
00421441        long double x87_r6_24 = fconvert.t(out_position->x) - fconvert.t(var_168)
00421484        float var_174_3 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r6_24 * fconvert.t(var_164.basis_right.x))) + fconvert.t(var_174_2))) + fconvert.t(fconvert.s(fconvert.t(var_164.basis_up.x) * x87_r7_67)))
00421497        esi_9->x.b = var_174_3.b
00421497        esi_9->x:1.b = var_174_3:1.b
00421497        esi_9->x:2.b = var_174_3:2.b
00421497        esi_9->x:3.b = var_174_3:3.b
004214a1        long double x87_r6_27 = x87_r6_24 * fconvert.t(var_164.basis_right.z) + fconvert.t(var_16c_2) + x87_r7_67 * fconvert.t(var_164.basis_up.z)
004214a3        esi_9->y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(var_164.basis_right.y) * x87_r6_24)) + fconvert.t(var_170_2))) + fconvert.t(fconvert.s(fconvert.t(var_164.basis_up.y) * x87_r7_67)))
004214ae        esi_9->z = fconvert.s(x87_r6_27)
004214ba        float* eax_58 = data_4df904 + 0x42fdb4
004214c1        *eax_58 = var_164.basis_right.x
004214c7        eax_58[1] = var_164.basis_right.y
004214ce        eax_58[2] = var_164.basis_right.z
004214db        float* edx_37 = data_4df904 + 0x42fdc4
004214e1        *edx_37 = var_164.basis_up.x
004214e7        edx_37[1] = var_164.basis_up.y
004214ee        edx_37[2] = var_164.basis_up.z
004214f7        float x_2 = var_164.basis_forward.x
004214fb        char* ecx_69 = data_4df904 + 0x42fdd4
00421501        *ecx_69 = x_2.b
00421501        ecx_69[1] = x_2:1.b
00421501        ecx_69[2] = x_2:2.b
00421501        ecx_69[3] = x_2:3.b
00421507        *(ecx_69 + 4) = var_164.basis_forward.y
0042150e        *(ecx_69 + 8) = var_164.basis_forward.z
0042114d        out_position_1 = out_position
0042115c        float* out_angle = &var_17c
00421167        struct TransformMatrix* transform = &var_164
00421168        float var_19c_2 = 0.49000001f
0042116d        struct TransformMatrix* var_1a0_1 = &var_164
0042116e        float var_1a0_2 = fconvert.s(fconvert.t(out_position_1->x) - fconvert.t(var_168))
00421171        float var_1a4 = var_178
00421174        compute_kind42_attachment_transform(var_1a4, var_1a0_2, var_19c_2, transform, out_angle)
00421179        uint32_t sample_index = follow_state->sample_index
00421189        if (sample_index == 0 || sample_index == follow_state->template_record->segment_count - 1)
00421192        struct TransformMatrix var_100
00421192        set_matrix_identity(&var_100)
004211a3        var_100.position.x = var_164.position.x
004211ad        var_100.position.y = var_164.position.y
004211c4        var_100.position.z = var_164.position.z
004211cb        bool cond:2_1 = follow_state->sample_index != 0
004211cd        struct TransformMatrix to_1
004211cd        __builtin_memcpy(&to_1, &var_164, 0x40)
004211cf        float progress
004211cf        if (cond:2_1)
004211e3        progress = fconvert.s(fconvert.t(1f) - fconvert.t(follow_state->progress))
004211d4        progress = follow_state->progress
00421200        out_position_1 = linear_interpolate_matrix(&var_164, &var_100, &to_1, progress)
0042120b        esi_9 = &follow_state->output_position
00421217        uint32_t ecx_51 = follow_state->sample_index * 0x15
0042121a        struct PathTemplateSample* secondary_samples_1 = follow_state->template_record->secondary_samples
00421234        edi_1 = &motion->y
0042123a        float y = var_164.position.y
0042123e        long double x87_r7_43 = fconvert.t((&secondary_samples_1->delta_dir_to_next.z)[ecx_51 * 2]) * fconvert.t(follow_state->progress) + fconvert.t(follow_state->source_cell->anchor_position.z) + fconvert.t((&secondary_samples_1->transform.position.z)[ecx_51 * 2])
0042124d        var_164.basis_right.x = fconvert.s(fconvert.t(var_164.basis_right.x) * fconvert.t(var_180_1))
00421259        var_164.basis_right.y = fconvert.s(fconvert.t(var_164.basis_right.y) * fconvert.t(var_180_1))
00421265        var_164.basis_right.z = fconvert.s(fconvert.t(var_164.basis_right.z) * fconvert.t(var_180_1))
0042126b        long double x87_r6_18 = fconvert.t((edi_1 - 4)->y) + fconvert.t(follow_state->vertical_offset)
0042126e        esi_9->x = var_164.position.x
00421270        float x = var_164.basis_right.x
00421274        follow_state->output_position.y = y
00421277        follow_state->vertical_offset = fconvert.s(x87_r6_18)
0042127a        follow_state->output_position.z = fconvert.s(x87_r7_43)
00421283        float* edx_28 = data_4df904 + 0x42fdb4
00421289        *edx_28 = x
0042128f        edx_28[1] = var_164.basis_right.y
00421296        edx_28[2] = var_164.basis_right.z
0042129f        float x_1 = var_164.basis_up.x
004212a3        char* ecx_55 = data_4df904 + 0x42fdc4
004212a9        *ecx_55 = x_1.b
004212a9        ecx_55[1] = x_1:1.b
004212a9        ecx_55[2] = x_1:2.b
004212a9        ecx_55[3] = x_1:3.b
004212af        *(ecx_55 + 4) = var_164.basis_up.y
004212b6        *(ecx_55 + 8) = var_164.basis_up.z
004212c2        float* eax_54 = data_4df904 + 0x42fdd4
004212c7        *eax_54 = var_164.basis_forward.x
004212cd        eax_54[1] = var_164.basis_forward.y
004212d4        eax_54[2] = var_164.basis_forward.z
00421515        float y_1 = var_164.basis_up.y
0042151c        follow_state->orientation_c = var_164.basis_up.x
0042151f        float z = var_164.basis_up.z
00421523        follow_state->orientation_d = y_1
00421526        struct PathTemplate* template_record_5 = follow_state->template_record
00421529        follow_state->orientation_e = z
0042152f        uint32_t sample_index_1 = follow_state->sample_index
00421539        uint32_t ecx_73 = sample_index_1 << 3
00421540        uint32_t ecx_76
00421540        if (sample_index_1 != template_record_5->segment_count - 1)
0042156b        struct PathTemplateSample* primary_samples = template_record_5->primary_samples
00421571        ecx_76 = (ecx_73 - sample_index_1) * 0x18
0042157b        long double x87_r7_71 = fconvert.t(*(primary_samples + ecx_76 + 0x140)) - fconvert.t(*(&primary_samples->rotation_scalar_98 + ecx_76))
00421582        void* ebx_1 = primary_samples + ecx_76
00421585        long double temp5_1 = fconvert.t(3.14159274f)
00421585        x87_r7_71 - temp5_1
0042158b        primary_samples.w = (x87_r7_71 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_71, temp5_1) ? 1 : 0) << 0xa | (x87_r7_71 == temp5_1 ? 1 : 0) << 0xe | 0x3800
00421590        if ((primary_samples:1.b & 0x41) != 0)
0042159a        long double temp6_1 = fconvert.t(-3.14159274f)
0042159a        x87_r7_71 - temp6_1
004215a0        primary_samples.w = (x87_r7_71 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_71, temp6_1) ? 1 : 0) << 0xa | (x87_r7_71 == temp6_1 ? 1 : 0) << 0xe | 0x3800
004215a5        if ((primary_samples:1.b & 1) != 0)
004215a7        x87_r7_71 = x87_r7_71 + fconvert.t(6.28318548f)
00421592        x87_r7_71 = x87_r7_71 - fconvert.t(6.28318548f)
004215c2        follow_state->orientation_b = fconvert.s(fconvert.t(follow_state->progress) / fconvert.t(*(&template_record_5->secondary_samples->delta_length + ecx_76)) * x87_r7_71 + fconvert.t(*(ebx_1 + 0x98)))
004215c5        struct PathTemplateSample* primary_samples_1 = template_record_5->primary_samples
004215d1        long double x87_r7_74 = fconvert.t(*(primary_samples_1 + ecx_76 + 0x13c)) - fconvert.t(*(&primary_samples_1->rotation_scalar_94 + ecx_76))
004215d8        void* ebx_2 = primary_samples_1 + ecx_76
004215db        long double temp7_1 = fconvert.t(3.14159274f)
004215db        x87_r7_74 - temp7_1
004215e1        primary_samples_1.w = (x87_r7_74 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_74, temp7_1) ? 1 : 0) << 0xa | (x87_r7_74 == temp7_1 ? 1 : 0) << 0xe | 0x3800
004215e6        if ((primary_samples_1:1.b & 0x41) != 0)
004215f0        long double temp10_1 = fconvert.t(-3.14159274f)
004215f0        x87_r7_74 - temp10_1
004215f6        primary_samples_1.w = (x87_r7_74 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_74, temp10_1) ? 1 : 0) << 0xa | (x87_r7_74 == temp10_1 ? 1 : 0) << 0xe | 0x3800
004215fb        if ((primary_samples_1:1.b & 1) != 0)
004215fd        x87_r7_74 = x87_r7_74 + fconvert.t(6.28318548f)
004215e8        x87_r7_74 = x87_r7_74 - fconvert.t(6.28318548f)
00421618        out_position_1 = out_position
0042161f        follow_state->orientation_a = fconvert.s(fconvert.t(follow_state->progress) / fconvert.t(*(&template_record_5->secondary_samples->delta_length + ecx_76)) * x87_r7_74 + fconvert.t(*(ebx_2 + 0x94)))
0042154a        ecx_76 = (ecx_73 - sample_index_1) * 0x18
00421554        follow_state->orientation_b = *(&template_record_5->primary_samples->rotation_scalar_98 + ecx_76)
00421561        follow_state->orientation_a = *(&template_record_5->primary_samples->rotation_scalar_94 + ecx_76)
00421631        struct Player* player_3 = follow_state->player
00421641        follow_state->orientation_b = fconvert.s((fconvert.t(follow_state->progress) / fconvert.t(*(&template_record_5->secondary_samples->delta_length + ecx_76)) + float.t(sample_index_1)) * fconvert.t(template_record_5->installed_heading_delta) / float.t(template_record_5->segment_count))
0042164b        struct PathTemplateSample* eax_69
0042164b        if (player_3->jetpack_gauge.state != 1)
00421653        long double x87_r7_82 = fconvert.t(out_position_1->x) - fconvert.t(var_168)
00421657        long double temp9_1 = fconvert.t(0f)
00421657        x87_r7_82 - temp9_1
0042165d        eax_69.w = (x87_r7_82 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_82, temp9_1) ? 1 : 0) << 0xa | (x87_r7_82 == temp9_1 ? 1 : 0) << 0xe | 0x3800
00421662        if ((eax_69:1.b & 1) != 0)
00421664        x87_r7_82 = fneg(x87_r7_82)
00421675        long double x87_r7_83 = float.t(template_record_5->width_cells) * fconvert.t(0.5f) + fconvert.t(0.300000012f)
00421677        x87_r7_82 - x87_r7_83
00421679        eax_69.w = (x87_r7_82 < x87_r7_83 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_82, x87_r7_83) ? 1 : 0) << 0xa | (x87_r7_82 == x87_r7_83 ? 1 : 0) << 0xe
0042167e        if ((eax_69:1.b & 0x41) == 0)
00421684        long double x87_r7_84 = fconvert.t(follow_state->vertical_offset)
00421687        long double temp11_1 = fconvert.t(0f)
00421687        x87_r7_84 - temp11_1
0042168d        eax_69.w = (x87_r7_84 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_84, temp11_1) ? 1 : 0) << 0xa | (x87_r7_84 == temp11_1 ? 1 : 0) << 0xe
00421692        if ((eax_69:1.b & 0x41) != 0)
0042169a        float* out_position_2 = out_position_1
0042169c        *out_position_2 = esi_9->x
004216a1        out_position_2[1] = esi_9->y
004216a7        out_position_2[2] = esi_9->z
004216ad        struct Player* player_2 = follow_state->player
004216bc        player_2->heading_roll = fconvert.s(fconvert.t(follow_state->template_record->installed_heading_delta) + fconvert.t(player_2->heading_roll))
004216c2        long double x87_r7_87 = fconvert.t(out_position_1->x)
004216c4        long double temp12 = fconvert.t(-4f)
004216c4        x87_r7_87 - temp12
004216ca        player_2.w = (x87_r7_87 < temp12 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_87, temp12) ? 1 : 0) << 0xa | (x87_r7_87 == temp12 ? 1 : 0) << 0xe
004216cf        if ((player_2:1.b & 1) != 0)
004216da        out_position_1->x = fconvert.s(fconvert.t(-4f))
004216e7        int32_t eax_72
004216e7        eax_72.b = follow_state->template_record->side_exit_mode == 0
004216f0        return eax_72
004216f3        long double x87_r7_89 = fconvert.t(out_position_1->x)
004216f5        long double temp13 = fconvert.t(4f)
004216f5        x87_r7_89 - temp13
004216fb        player_2.w = (x87_r7_89 < temp13 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_89, temp13) ? 1 : 0) << 0xa | (x87_r7_89 == temp13 ? 1 : 0) << 0xe
00421700        if ((player_2:1.b & 0x41) != 0)
00421729        out_position_1->x = fconvert.s(fconvert.t(out_position_1->x))
00421736        int32_t eax_74
00421736        eax_74.b = follow_state->template_record->side_exit_mode == 0
0042173f        return eax_74
0042170b        out_position_1->x = fconvert.s(fconvert.t(4f))
00421718        int32_t eax_73
00421718        eax_73.b = follow_state->template_record->side_exit_mode == 0
00421721        return eax_73
00421742        long double x87_r7_92 = fconvert.t(follow_state->vertical_offset)
00421745        long double temp8 = fconvert.t(0f)
00421745        x87_r7_92 - temp8
0042174b        eax_69.w = (x87_r7_92 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_92, temp8) ? 1 : 0) << 0xa | (x87_r7_92 == temp8 ? 1 : 0) << 0xe
00421750        if ((eax_69:1.b & 1) != 0)
00421752        follow_state->vertical_offset = 0f
00421759        (edi_1 - 4)->y = 0f
0042176b        return 0
