/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_attachment_follow_state @ 0x420cb0 */

00420cc2        uint32_t sample_index_3 = follow_state->sample_index
00420cc5        struct cRPath* template_record_6 = follow_state->template_record
00420cc9        struct PathTemplateSample* secondary_samples_4 = template_record_6->secondary_samples
00420cd5        uint32_t eax_2 = sample_index_3 * 0x15
00420cd8        long double x87_r7_1 = fconvert.t(path_factor) * fconvert.t((&secondary_samples_4->delta_length)[eax_2 * 2])
00420cdf        float* edx = &(&secondary_samples_4->delta_length)[eax_2 * 2]
00420ce6        float var_180 = fconvert.s(x87_r7_1)
00420cea        long double x87_r7_2 = x87_r7_1 + fconvert.t(follow_state->progress)
00420ced        long double temp1 = fconvert.t(*edx)
00420ced        x87_r7_2 - temp1
00420cf4        if ((((x87_r7_2 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00420ea1        long double x87_r7_7
00420ea1        long double temp3_1
00420d06        long double x87_r7_4 = fconvert.t(*edx) - fconvert.t(follow_state->progress)
00420d0a        follow_state->progress = 0f
00420d11        follow_state->sample_index = sample_index_3 + 1
00420d1f        var_180 = fconvert.s(fconvert.t(var_180) - x87_r7_4)
00420d23        if (sample_index_3 + 1 == template_record_6->segment_count << 1)
00420d30        play_voice_manager(&g_voice_manager, 4, 1, 0xffffffff)
00420d35        struct cRPath* template_record = follow_state->template_record
00420d40        if (template_record->has_entry_mesh_transition != 0)
00420d46        uint32_t segment_count = template_record->segment_count
00420d49        uint32_t sample_index_5 = follow_state->sample_index
00420d51        if (sample_index_5 != segment_count - 1)
00420ddb        if (sample_index_5 == segment_count * 3 s/ 7)
00420df7        struct cRSubLoc* primary_attachment_cell_transition_flags = (&g_game_base->subgame.runtime_rows[0].primary_attachment_cell)[get_track_cell_row_index(follow_state->source_cell) * 0x3d]
00420e03        primary_attachment_cell_transition_flags->bod.list_flags |= 0x80
00420e23        struct cRPath* entry_transition_template = (&g_game_base->subgame.runtime_rows[0].primary_attachment_cell)[get_track_cell_row_index(follow_state->source_cell) * 0x3d]->attachment_template_record
00420e29        int32_t eax_17 = get_track_cell_row_index(follow_state->source_cell)
00420e4a        (&g_game_base->subgame.runtime_rows[0].primary_attachment_cell)[eax_17 * 0x3d]->object = entry_transition_template->entry_transition_strip_mesh
00420e6a        (&g_game_base->subgame.runtime_rows[0].primary_attachment_cell)[get_track_cell_row_index(follow_state->source_cell) * 0x3d]->color.a = 0.600000024f
00420d74        struct cRPath* entry_base_template = (&g_game_base->subgame.runtime_rows[0].primary_attachment_cell)[get_track_cell_row_index(follow_state->source_cell) * 0x3d]->attachment_template_record
00420d77        int32_t eax_8 = get_track_cell_row_index(follow_state->source_cell)
00420d97        (&g_game_base->subgame.runtime_rows[0].primary_attachment_cell)[eax_8 * 0x3d]->object = entry_base_template->entry_base_strip_mesh
00420db7        (&g_game_base->subgame.runtime_rows[0].primary_attachment_cell)[get_track_cell_row_index(follow_state->source_cell) * 0x3d]->color.a = 1f
00420e6d        template_record_6 = follow_state->template_record
00420e70        sample_index_3 = follow_state->sample_index
00420e76        if (sample_index_3 == template_record_6->segment_count)
00420ef0        long double x87_r7_10 = fconvert.t(var_180)
00420ef4        long double temp2 = fconvert.t(1f)
00420ef4        x87_r7_10 - temp2
00420efa        follow_state->active = 0
00420f03        if ((((x87_r7_10 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2) ? 1 : 0) << 0xa | (x87_r7_10 == temp2 ? 1 : 0) << 0xe):1.b & 1) == 0)
00420f05        var_180 = 0.999000013f
00420f0d        struct cRPath* template_record_1 = follow_state->template_record
00420f30        long double x87_r7_12 = fconvert.t(path_factor) * fconvert.t(*(&template_record_1->secondary_samples[template_record_1->segment_count] - 0x1c))
00420f34        motion->z = fconvert.s(x87_r7_12)
00420f37        long double temp4 = fconvert.t(1f)
00420f37        x87_r7_12 - temp4
00420f42        if ((((x87_r7_12 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp4) ? 1 : 0) << 0xa | (x87_r7_12 == temp4 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00420f44        motion->z = 1f
00420f4b        struct cRPath* template_record_4 = follow_state->template_record
00420f52        if (template_record_4->kind != PATH_TEMPLATE_KIND_SUPERTRAMP)
00421077        out_position->z = fconvert.s(fconvert.t(*(&template_record_4->secondary_samples[template_record_4->segment_count] - 0x70)) + fconvert.t(follow_state->source_cell->anchor_position.z) + fconvert.t(template_record_4->width_or_scale) + fconvert.t(var_180))
00420f68        int32_t sample_override = 0xffffffff
00420f6a        uint32_t mode = 0
00420f6c        int32_t set_id = 0xf
00420f6e        motion->y = fconvert.s(fconvert.t(motion->z) * fconvert.t(0.699999988f))
00420f71        struct cRPath* template_record_2 = follow_state->template_record
00420f74        long double x87_r7_15 = fconvert.t(out_position->x)
00420f7d        long double x87_r6_2 = fconvert.t(var_180) + fconvert.t(template_record_2->width_or_scale)
00420f80        struct PathTemplateSample* secondary_samples_2 = template_record_2->secondary_samples
00420f8c        uint32_t eax_36 = template_record_2->segment_count * 0x15
00420f98        void* eax_37 = secondary_samples_2 + (eax_36 << 3)
00420f9e        struct Vec3* ecx_30 = &follow_state->source_cell->anchor_position
00420fb7        long double x87_r6_3 = x87_r6_2 * fconvert.t(*(eax_37 - 0x80))
00420fd1        float var_11c_1 = fconvert.s(fconvert.t(*(eax_37 - 0x70)) + fconvert.t(ecx_30->z))
00420fe7        long double x87_r5_9 = fconvert.t(fconvert.s(fconvert.t(*(eax_37 - 0x74)) + fconvert.t(ecx_30->y))) + fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(*(eax_37 - 0x84))))
00420ff2        out_position->x = fconvert.s(fconvert.t(ecx_30->x) + fconvert.t(*(eax_37 - 0x78)) + fconvert.t(fconvert.s(x87_r6_2 * fconvert.t(*(secondary_samples_2 + (eax_36 << 3) - 0x88)))))
00421015        *out_position = struct Vec3 {
    .y = fconvert.s(x87_r5_9)
    .z = fconvert.s(fconvert.t(var_11c_1) + x87_r6_3)
    .x = fconvert.s(x87_r7_15)
}
0042102c        follow_state->player->cutscene_pitch_cycle_step = fconvert.s(fconvert.t(g_game_base->subgame.subgame_rate) * fconvert.t(0.0138888881f))
00421032        struct Player* player = follow_state->player
0042103b        player->cutscene_pitch_cycle = player->cutscene_pitch_cycle_step
00421046        play_voice_manager(&g_voice_manager, set_id, mode, sample_override)
0042107d        struct Player* player_1 = follow_state->player
00421090        player_1->heading_roll = fconvert.s(fconvert.t(follow_state->template_record->installed_heading_delta) + fconvert.t(player_1->heading_roll))
004210a1        return 3
00420e83        x87_r7_7 = fconvert.t(var_180) + fconvert.t(follow_state->progress)
00420e88        uint32_t edx_13 = sample_index_3 * 0x15
00420e8b        struct PathTemplateSample* secondary_samples = template_record_6->secondary_samples
00420e8e        temp3_1 = fconvert.t((&secondary_samples->delta_length)[edx_13 * 2])
00420e8e        x87_r7_7 - temp3_1
00420e95        edx = &(&secondary_samples->delta_length)[edx_13 * 2]
00420ea1        do while ((((x87_r7_7 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp3_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00420eae        uint32_t sample_index_4 = follow_state->sample_index
00420eb1        float var_17c = fconvert.s(fconvert.t(var_180) + fconvert.t(follow_state->progress))
00420eb9        follow_state->progress = var_17c
00420ebc        struct cRPath* template_record_3 = follow_state->template_record
00420ec2        int32_t edi = template_record_3->segment_count - 1
00420ec5        uint32_t eax_25 = sample_index_4 << 3
00420ece        float center_x
00420ece        uint32_t eax_28
00420ece        if (sample_index_4 != edi)
004210b3        eax_28 = (eax_25 - sample_index_4) * 0x18
004210b6        struct PathTemplateSamplePairCursorView* primary_sample_pair = template_record_3->primary_samples + eax_28
004210d3        center_x = fconvert.s(fconvert.t(var_17c) / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_28)) * (fconvert.t(primary_sample_pair->next.center_x) - fconvert.t(primary_sample_pair->current.center_x)) + fconvert.t(primary_sample_pair->current.center_x))
00420edc        eax_28 = (eax_25 - sample_index_4) * 0x18
00420ee7        center_x = (template_record_3->primary_samples + eax_28)->current.center_x
004210d9        float lateral_scale
004210d9        struct PathTemplateSamplePairCursorView* primary_sample_pair_rejoined
004210d9        if (sample_index_4 != edi)
00421109        lateral_scale = fconvert.s(fconvert.t(var_17c) / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_28)) * (fconvert.t(primary_sample_pair_rejoined->next.lateral_scale) - fconvert.t(primary_sample_pair_rejoined->current.lateral_scale)) + fconvert.t(primary_sample_pair_rejoined->current.lateral_scale))
004210e1        lateral_scale = primary_sample_pair_rejoined->current.lateral_scale
0042110f        float special_scalar
0042110f        if (sample_index_4 != edi)
0042113f        special_scalar = fconvert.s(fconvert.t(var_17c) / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_28)) * (fconvert.t(primary_sample_pair_rejoined->next.special_scalar) - fconvert.t(primary_sample_pair_rejoined->current.special_scalar)) + fconvert.t(primary_sample_pair_rejoined->current.special_scalar))
00421117        special_scalar = primary_sample_pair_rejoined->current.special_scalar
00421147        struct TransformMatrix var_164
00421147        float* ebx
00421147        struct Vec3* esi_7
00421147        float* edi_1
00421147        if (template_record_3->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
004212dc        struct PathTemplateSample* secondary_samples_3 = template_record_3->secondary_samples
004212ec        struct PathTemplateSample* secondary_sample = secondary_samples_3 + eax_28
004212ef        struct cRSubLoc* source_cell = follow_state->source_cell
004212fc        float var_174_2 = fconvert.s(fconvert.t(var_17c) * fconvert.t(*(&secondary_samples_3->delta_dir_to_next + eax_28)) * fconvert.t(lateral_scale) + fconvert.t(source_cell->anchor_position.x) + fconvert.t(secondary_sample->transform.position.x))
00421314        float var_170_2 = fconvert.s(fconvert.t(var_17c) * fconvert.t(secondary_sample->delta_dir_to_next.y) * fconvert.t(lateral_scale) + fconvert.t(source_cell->anchor_position.y) + fconvert.t(secondary_sample->transform.position.y))
00421328        float var_16c_2 = fconvert.s(fconvert.t(var_17c) * fconvert.t(secondary_sample->delta_dir_to_next.z) + fconvert.t(source_cell->anchor_position.z) + fconvert.t(secondary_sample->transform.position.z))
0042132c        if (sample_index_4 != edi)
00421349        struct TransformMatrix from
00421349        __builtin_memcpy(&from, secondary_sample, 0x40)
0042134b        long double x87_r7_58 = fconvert.t(var_17c)
0042136d        struct TransformMatrix to
0042136d        int32_t ecx_56 = __builtin_memcpy(&to, &template_record_3->secondary_samples[sample_index_4 + 1], 0x40)
00421385        __builtin_memset(&from.position, 0, 0xc)
004213a6        __builtin_memset(&to.position, 0, 0xc)
004213b4        int32_t var_194_3 = ecx_56
004213d3        linear_interpolate_matrix(&var_164, &from, &to, fconvert.s(x87_r7_58 / fconvert.t(*(&template_record_3->secondary_samples->delta_length + eax_28))))
00421332        set_matrix_identity(&var_164)
004213ee        esi_7 = &follow_state->output_position
004213f1        ebx = out_position
004213f8        edi_1 = &motion->y
004213fb        char* ecx_58 = esi_7
00421415        var_164.basis_right = struct Vec3 {
    .x = fconvert.s(fconvert.t(var_164.basis_right.x) * fconvert.t(lateral_scale))
    .y = fconvert.s(fconvert.t(var_164.basis_right.y) * fconvert.t(lateral_scale))
    .z = fconvert.s(fconvert.t(var_164.basis_right.z) * fconvert.t(lateral_scale))
}
0042141b        long double x87_r7_67 = fconvert.t((edi_1 - 4)->y) + fconvert.t(follow_state->vertical_offset)
0042141e        follow_state->vertical_offset = fconvert.s(x87_r7_67)
0042143b        long double x87_r7_68 = x87_r7_67 * fconvert.t(var_164.basis_up.z)
00421441        long double x87_r6_24 = fconvert.t(out_position->x) - fconvert.t(center_x)
00421475        long double x87_r6_26 = x87_r6_24 * fconvert.t(var_164.basis_right.z) + fconvert.t(var_16c_2)
00421484        float var_174_3 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r6_24 * fconvert.t(var_164.basis_right.x))) + fconvert.t(var_174_2))) + fconvert.t(fconvert.s(fconvert.t(var_164.basis_up.x) * x87_r7_67)))
0042148c        long double x87_r5_23 = fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(var_164.basis_right.y) * x87_r6_24)) + fconvert.t(var_170_2))) + fconvert.t(fconvert.s(fconvert.t(var_164.basis_up.y) * x87_r7_67))
00421497        *ecx_58 = var_174_3.b
00421497        ecx_58[1] = var_174_3:1.b
00421497        ecx_58[2] = var_174_3:2.b
00421497        ecx_58[3] = var_174_3:3.b
004214a3        *(ecx_58 + 4) = fconvert.s(x87_r5_23)
004214ae        *(ecx_58 + 8) = fconvert.s(x87_r6_26 + x87_r7_68)
004214ce        g_game_base->subgame.player.body.transform.basis_right = var_164.basis_right
004214ee        g_game_base->subgame.player.body.transform.basis_up.x.12 = var_164.basis_up
004214f7        float x_3 = var_164.basis_forward.x
004214fb        struct Vec3* player_forward_reloaded = &g_game_base->subgame.player.body.transform.basis_forward
00421501        player_forward_reloaded->x.b = x_3.b
00421501        player_forward_reloaded->x:1.b = x_3:1.b
00421501        player_forward_reloaded->x:2.b = x_3:2.b
00421501        player_forward_reloaded->x:3.b = x_3:3.b
00421507        player_forward_reloaded->y = var_164.basis_forward.y
0042150e        player_forward_reloaded->z = var_164.basis_forward.z
0042114d        ebx = out_position
0042115c        float* out_angle = &var_17c
00421167        struct TransformMatrix* transform = &var_164
00421168        float y_3 = 0.49000001f
0042116d        struct TransformMatrix* var_1a0_1 = &var_164
0042116e        float x_4 = fconvert.s(fconvert.t(*ebx) - fconvert.t(center_x))
00421171        float radius = special_scalar
00421174        compute_kind42_attachment_transform(template_record_3, radius, x_4, y_3, transform, out_angle)
00421179        uint32_t sample_index = follow_state->sample_index
00421189        if (sample_index == 0 || sample_index == follow_state->template_record->segment_count - 1)
00421192        struct TransformMatrix var_100
00421192        set_matrix_identity(&var_100)
0042119b        float y = var_164.position.y
0042119f        float z_1 = var_164.position.z
004211a3        var_100.position.x = var_164.position.x
004211aa        uint32_t sample_index_1 = follow_state->sample_index
004211ad        var_100.position.y = y
004211c4        var_100.position.z = z_1
004211cd        struct TransformMatrix to_1
004211cd        __builtin_memcpy(&to_1, &var_164, 0x40)
004211cf        float progress
004211cf        if (sample_index_1 != 0)
004211e3        progress = fconvert.s(fconvert.t(1f) - fconvert.t(follow_state->progress))
004211d4        progress = follow_state->progress
00421200        linear_interpolate_matrix(&var_164, &var_100, &to_1, progress)
0042120b        esi_7 = &follow_state->output_position
00421217        uint32_t ecx_46 = follow_state->sample_index * 0x15
0042121a        struct PathTemplateSample* secondary_samples_1 = follow_state->template_record->secondary_samples
00421234        edi_1 = &motion->y
0042123a        float y_1 = var_164.position.y
0042123e        long double x87_r7_43 = fconvert.t((&secondary_samples_1->delta_dir_to_next.z)[ecx_46 * 2]) * fconvert.t(follow_state->progress) + fconvert.t(follow_state->source_cell->anchor_position.z) + fconvert.t((secondary_samples_1 + (ecx_46 << 3))->transform.position.z)
00421249        float x = var_164.position.x
00421265        var_164.basis_right = struct Vec3 {
    .x = fconvert.s(fconvert.t(var_164.basis_right.x) * fconvert.t(lateral_scale))
    .y = fconvert.s(fconvert.t(var_164.basis_right.y) * fconvert.t(lateral_scale))
    .z = fconvert.s(fconvert.t(var_164.basis_right.z) * fconvert.t(lateral_scale))
}
0042126b        long double x87_r6_18 = fconvert.t((edi_1 - 4)->y) + fconvert.t(follow_state->vertical_offset)
0042126e        esi_7->x = x
00421270        float x_1 = var_164.basis_right.x
00421274        follow_state->output_position.y = y_1
00421277        follow_state->vertical_offset = fconvert.s(x87_r6_18)
0042127a        follow_state->output_position.z = fconvert.s(x87_r7_43)
00421296        g_game_base->subgame.player.body.transform.basis_right.x.12 = struct Vec3 {
    .x = x_1
    .y = var_164.basis_right.y
    .z = var_164.basis_right.z
}
0042129f        float x_2 = var_164.basis_up.x
004212a3        struct Vec3* player_up = &g_game_base->subgame.player.body.transform.basis_up
004212a9        player_up->x.b = x_2.b
004212a9        player_up->x:1.b = x_2:1.b
004212a9        player_up->x:2.b = x_2:2.b
004212a9        player_up->x:3.b = x_2:3.b
004212af        player_up->y = var_164.basis_up.y
004212b6        player_up->z = var_164.basis_up.z
004212d4        g_game_base->subgame.player.body.transform.basis_forward.x.12 = var_164.basis_forward
00421515        float y_2 = var_164.basis_up.y
0042151c        follow_state->orientation_up.x = var_164.basis_up.x
0042151f        float z = var_164.basis_up.z
00421523        follow_state->orientation_up.y = y_2
00421526        struct cRPath* template_record_5 = follow_state->template_record
00421529        follow_state->orientation_up.z = z
0042152f        uint32_t sample_index_2 = follow_state->sample_index
00421539        uint32_t ecx_66 = sample_index_2 << 3
00421540        uint32_t ecx_69
00421540        if (sample_index_2 != template_record_5->segment_count - 1)
0042156b        struct PathTemplateSample* primary_samples = template_record_5->primary_samples
00421571        ecx_69 = (ecx_66 - sample_index_2) * 0x18
0042157b        long double x87_r7_71 = fconvert.t(*(primary_samples + ecx_69 + 0x140)) - fconvert.t(*(&primary_samples->rotation_scalar_98 + ecx_69))
00421585        long double temp5_1 = fconvert.t(3.14159274f)
00421585        x87_r7_71 - temp5_1
00421590        if ((((x87_r7_71 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_71, temp5_1) ? 1 : 0) << 0xa | (x87_r7_71 == temp5_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0042159a        long double temp6_1 = fconvert.t(-3.14159274f)
0042159a        x87_r7_71 - temp6_1
004215a5        if ((((x87_r7_71 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_71, temp6_1) ? 1 : 0) << 0xa | (x87_r7_71 == temp6_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004215a7        x87_r7_71 = x87_r7_71 + fconvert.t(6.28318548f)
00421592        x87_r7_71 = x87_r7_71 - fconvert.t(6.28318548f)
004215c2        follow_state->orientation_b = fconvert.s(fconvert.t(follow_state->progress) / fconvert.t(*(&template_record_5->secondary_samples->delta_length + ecx_69)) * x87_r7_71 + fconvert.t(*(&primary_samples->rotation_scalar_98 + ecx_69)))
004215c5        struct PathTemplateSample* primary_samples_1 = template_record_5->primary_samples
004215d1        long double x87_r7_74 = fconvert.t(*(primary_samples_1 + ecx_69 + 0x13c)) - fconvert.t(*(&primary_samples_1->rotation_scalar_94 + ecx_69))
004215db        long double temp7_1 = fconvert.t(3.14159274f)
004215db        x87_r7_74 - temp7_1
004215e6        if ((((x87_r7_74 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_74, temp7_1) ? 1 : 0) << 0xa | (x87_r7_74 == temp7_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
004215f0        long double temp10_1 = fconvert.t(-3.14159274f)
004215f0        x87_r7_74 - temp10_1
004215fb        if ((((x87_r7_74 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_74, temp10_1) ? 1 : 0) << 0xa | (x87_r7_74 == temp10_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
004215fd        x87_r7_74 = x87_r7_74 + fconvert.t(6.28318548f)
004215e8        x87_r7_74 = x87_r7_74 - fconvert.t(6.28318548f)
00421618        ebx = out_position
0042161f        follow_state->orientation_a = fconvert.s(fconvert.t(follow_state->progress) / fconvert.t(*(&template_record_5->secondary_samples->delta_length + ecx_69)) * x87_r7_74 + fconvert.t(*(&primary_samples_1->rotation_scalar_94 + ecx_69)))
0042154a        ecx_69 = (ecx_66 - sample_index_2) * 0x18
00421554        follow_state->orientation_b = *(&template_record_5->primary_samples->rotation_scalar_98 + ecx_69)
00421561        follow_state->orientation_a = *(&template_record_5->primary_samples->rotation_scalar_94 + ecx_69)
00421631        struct Player* player_3 = follow_state->player
00421641        follow_state->orientation_b = fconvert.s((fconvert.t(follow_state->progress) / fconvert.t(*(&template_record_5->secondary_samples->delta_length + ecx_69)) + float.t(sample_index_2)) * fconvert.t(template_record_5->installed_heading_delta) / float.t(template_record_5->segment_count))
0042164b        if (player_3->sub_hover.state != SUB_HOVER_STATE_ACTIVE)
00421653        long double x87_r7_82 = fconvert.t(*ebx) - fconvert.t(center_x)
00421657        long double temp9_1 = fconvert.t(0f)
00421657        x87_r7_82 - temp9_1
00421662        if ((((x87_r7_82 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_82, temp9_1) ? 1 : 0) << 0xa | (x87_r7_82 == temp9_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00421664        x87_r7_82 = fneg(x87_r7_82)
00421675        long double x87_r7_83 = float.t(template_record_5->width_cells) * fconvert.t(0.5f) + fconvert.t(0.300000012f)
00421677        x87_r7_82 - x87_r7_83
0042167e        if ((((x87_r7_82 < x87_r7_83 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_82, x87_r7_83) ? 1 : 0) << 0xa | (x87_r7_82 == x87_r7_83 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00421684        long double x87_r7_84 = fconvert.t(follow_state->vertical_offset)
00421687        long double temp11_1 = fconvert.t(0f)
00421687        x87_r7_84 - temp11_1
00421692        if ((((x87_r7_84 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_84, temp11_1) ? 1 : 0) << 0xa | (x87_r7_84 == temp11_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0042169a        struct Vec3* output_position_copy = ebx
0042169c        output_position_copy->x = esi_7->x
004216a1        output_position_copy->y = esi_7->y
004216a7        output_position_copy->z = esi_7->z
004216ad        struct Player* player_2 = follow_state->player
004216bc        player_2->heading_roll = fconvert.s(fconvert.t(follow_state->template_record->installed_heading_delta) + fconvert.t(player_2->heading_roll))
004216c2        long double x87_r7_87 = fconvert.t(*ebx)
004216c4        long double temp12 = fconvert.t(-4f)
004216c4        x87_r7_87 - temp12
004216cf        if ((((x87_r7_87 < temp12 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_87, temp12) ? 1 : 0) << 0xa | (x87_r7_87 == temp12 ? 1 : 0) << 0xe):1.b & 1) != 0)
004216d7        int32_t eax_74 = 0
004216da        *ebx = fconvert.s(fconvert.t(-4f))
004216e7        eax_74.b = follow_state->template_record->side_exit_mode == 0
004216f0        return eax_74
004216f3        long double x87_r7_89 = fconvert.t(*ebx)
004216f5        long double temp13 = fconvert.t(4f)
004216f5        x87_r7_89 - temp13
00421700        if ((((x87_r7_89 < temp13 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_89, temp13) ? 1 : 0) << 0xa | (x87_r7_89 == temp13 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00421726        int32_t eax_76 = 0
00421729        *ebx = fconvert.s(fconvert.t(*ebx))
00421736        eax_76.b = follow_state->template_record->side_exit_mode == 0
0042173f        return eax_76
00421708        int32_t eax_75 = 0
0042170b        *ebx = fconvert.s(fconvert.t(4f))
00421718        eax_75.b = follow_state->template_record->side_exit_mode == 0
00421721        return eax_75
00421742        long double x87_r7_92 = fconvert.t(follow_state->vertical_offset)
00421745        long double temp8 = fconvert.t(0f)
00421745        x87_r7_92 - temp8
00421750        if ((((x87_r7_92 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_92, temp8) ? 1 : 0) << 0xa | (x87_r7_92 == temp8 ? 1 : 0) << 0xe):1.b & 1) != 0)
00421752        follow_state->vertical_offset = 0f
00421759        (edi_1 - 4)->y = 0f
0042176b        return 0
