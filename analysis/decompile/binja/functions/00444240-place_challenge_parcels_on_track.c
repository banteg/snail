/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: place_challenge_parcels_on_track @ 0x444240 */

00444263        int32_t eax
00444263        int16_t x87control
00444263        int16_t x87control_1
00444263        eax, x87control_1 = ftol(x87control, float.t(game->completion_bonus_x_source) * fconvert.t(50f) * fconvert.t(0.00999999978f) + fconvert.t(game->challenge_difficulty_scalar) * fconvert.t(50f))
00444269        game->level_definition.parcel_count = eax + 1
0044426f        game->level_definition.parcel_quota = eax + 1
00444275        int32_t* i = &data_53d390
0044428a        while (i s< 0x643390)
0044427a        *i = 0
00444280        i = &i[0x83]
0044428c        int32_t runtime_row_count_1 = game->runtime_row_count
0044428f        int32_t i_2 = 0
00444291        int32_t i_1 = 0
00444293        int32_t i_3 = 0
00444299        if (runtime_row_count_1 s> 0)
0044429b        int32_t* edx_1 = &g_parcel_group_survival_0
004442a0        runtime_row_count_1 = &game->runtime_rows[0].parcel_set_id
004442b2        if ((*(runtime_row_count_1 - 0x9c) & 1) != 0 && *runtime_row_count_1 == 0)
004442b4        *edx_1 = i_1
004442b6        i_2 += 1
004442b7        edx_1 = &edx_1[1]
004442bd        i_1 += 1
004442be        runtime_row_count_1 += 0xf4
004442c6        do while (i_1 s< game->runtime_row_count)
004442c8        i_3 = i_2
004442d2        int32_t edi_2 = 0
004442d6        float out_angle
004442d6        if (game->level_definition.parcel_count s> 0)
004442dc        int32_t ebx_1 = i_2 - 1
004442e7        while (i_2 s> 0)
004442f1        void* var_5c_1 = &data_4a5100
004442f6        int32_t runtime_row_count_2 = runtime_row_count_1
00444302        int32_t eax_3
00444302        eax_3, x87control_1 = ftol(x87control_1, random_float_below(fconvert.s(float.t(i_3))))
00444307        float out_angle_1 = *((eax_3 << 2) + &g_parcel_group_survival_0)
0044430e        int32_t* esi = (eax_3 << 2) + &g_parcel_group_survival_0
00444315        out_angle = out_angle_1
00444319        edi_2 += 1
00444320        int32_t ecx = out_angle_1 i* 0x3d
0044432d        runtime_row_count_1 = &game->unknown_000000[ecx << 2]
00444331        *(runtime_row_count_1 + 0x5ccac8) = *(&game->runtime_rows + (ecx << 2)) | 0x11
00444343        *(runtime_row_count_1 + 0x5ccb5c) = fconvert.s(fconvert.t(*(runtime_row_count_1 + 0x5ccb5c)) + fconvert.t(1f))
00444350        if ((*(runtime_row_count_1 + 0x5ccac8) & 0x20) != 0)
0044435e        *(runtime_row_count_1 + 0x5ccb58) = fconvert.s(fconvert.t(*(runtime_row_count_1 + 0x5ccb58)) * fconvert.t(-1f))
0044436d        if (((*(runtime_row_count_1 + 0x5ccac8)).w:1.b & 0x40) != 0)
0044437f        *(runtime_row_count_1 + 0x5ccb60) = fconvert.s(float.t(out_angle) + fconvert.t(*(runtime_row_count_1 + 0x5ccb60)) + fconvert.t(0.5f))
00444387        if (eax_3 s< ebx_1)
0044438b        runtime_row_count_1 = ebx_1 - eax_3
00444396        int32_t j
00444390        *esi = esi[1]
00444392        esi = &esi[1]
00444395        j = runtime_row_count_1
00444395        runtime_row_count_1 -= 1
00444396        do while (j != 1)
004443a3        ebx_1 -= 1
004443a6        i_3 -= 1
004443aa        if (edi_2 s>= game->level_definition.parcel_count)
004443aa        break
004442e1        i_2 = i_3
004443b6        game->level_definition.parcel_count = edi_2
004443c1        int32_t runtime_row_count = game->runtime_row_count
004443c9        int32_t runtime_row_count_3 = 0
004443d1        if (runtime_row_count s> 0)
004443d7        struct TrackAttachmentRuntimeRow (* esi_1)[0xc80] = &game->runtime_rows
004443dd        uint8_t flags = ((esi_1 - 0x5ccac8)->runtime_rows[0].flags).b
004443e9        if ((flags & 1) != 0 && (flags & 0x40) != 0)
004443f5        int32_t eax_5 = get_track_cell_row_index((esi_1 - 0x5ccac8)->runtime_rows[0].primary_attachment_cell)
00444402        int32_t eax_6
00444402        eax_6, x87control_1 = ftol(x87control_1, fconvert.t((esi_1 - 0x5ccac8)->runtime_rows[0].projection_payload.z))
00444409        int32_t node = eax_6 - eax_5
0044440b        if (eax_6 - eax_5 s< 0)
0044440d        node = 0
0044440f        struct TrackRowCell* primary_attachment_cell = (esi_1 - 0x5ccac8)->runtime_rows[0].primary_attachment_cell
00444415        struct Path* attachment_template_record = primary_attachment_cell->attachment_template_record
0044441c        if (attachment_template_record->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
00444471        int32_t row_index = get_track_cell_row_index(primary_attachment_cell)
00444482        get_path_position_at_node((esi_1 - 0x5ccac8)->runtime_rows[0].primary_attachment_cell->attachment_template_record, esi_1 + 0x90, node, row_index, esi_1 + 0x90)
0044444f        struct TransformMatrix transform
0044444f        x87control_1 = compute_kind42_attachment_transform(attachment_template_record, (&attachment_template_record->primary_samples->special_scalar)[node * 0x2a], (esi_1 - 0x5ccac8)->runtime_rows[0].projection_payload.x, (esi_1 - 0x5ccac8)->runtime_rows[0].projection_payload.y, &transform, &out_angle)
0044445c        (esi_1 - 0x5ccac8)->runtime_rows[0].projection_payload.x = transform.position.x
00444462        (esi_1 - 0x5ccac8)->runtime_rows[0].projection_payload.y = transform.position.y
0044448e        runtime_row_count = runtime_row_count_3 + 1
0044448f        esi_1 = &(*esi_1)[1]
00444497        runtime_row_count_3 = runtime_row_count
0044449b        do while (runtime_row_count s< game->runtime_row_count)
004444a8        return runtime_row_count
