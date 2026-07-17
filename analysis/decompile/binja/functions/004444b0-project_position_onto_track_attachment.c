/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: project_position_onto_track_attachment @ 0x4444b0 */

004444bf        int32_t eax
004444bf        int16_t x87control
004444bf        int16_t x87control_1
004444bf        eax, x87control_1 = ftol(x87control, fconvert.t(position->z))
004444c4        int32_t ecx = eax * 3
004444db        *out_angle = 0
004444db        *(out_angle + 1) = 0
004444db        *(out_angle + 2) = 0
004444db        *(out_angle + 3) = 0
004444e4        if ((*(&game->runtime_rows + ((eax + ecx * 0x14) << 2)) & 0x40) == 0)
004444e4        return
004444ea        SubLoc* cell = (&game->runtime_rows[0].primary_attachment_cell)[eax + ecx * 0x14]
004444f3        struct Path* attachment_template_record = cell->attachment_template_record
004444f6        int32_t eax_2 = get_track_cell_row_index(cell)
0044450f        int32_t ecx_5 = (ftol(x87control_1, fconvert.t(position->z)) - eax_2) * 7
0044451d        float* eax_6 = attachment_template_record->primary_samples + ecx_5 * 0x18
00444520        if (attachment_template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42)
0044453f        struct TransformMatrix transform
0044453f        compute_kind42_attachment_transform(attachment_template_record, eax_6[0x28], position->x, position->y, &transform, out_angle)
00444548        float y = transform.position.y
0044454c        position->x = transform.position.x
0044454e        position->y = y
00444557        return
0044455a        long double x87_r7_2 = fconvert.t(position->y)
0044456f        long double x87_r7_3 = x87_r7_2 * fconvert.t(eax_6[6])
00444574        long double x87_r6_6 = fconvert.t(position->x) - fconvert.t(eax_6[0x24])
004445bc        long double x87_r6_8 = x87_r6_6 * fconvert.t(eax_6[2]) + fconvert.t(fconvert.s(fconvert.t(eax_6[0xe]) + fconvert.t(cell->anchor_position.z)))
004445d0        long double x87_r5_13 = fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_6[0xd]) + fconvert.t(cell->anchor_position.y))) + fconvert.t(fconvert.s(x87_r6_6 * fconvert.t(eax_6[1]))))) + fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(eax_6[5])))
004445d8        position->x = fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_6[0xc]) + fconvert.t(cell->anchor_position.x) + fconvert.t(fconvert.s(x87_r6_6 * fconvert.t(*eax_6))))) + fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(eax_6[4]))))
004445e4        position->y = fconvert.s(x87_r5_13)
004445f1        position->z = fconvert.s(x87_r6_8 + x87_r7_3)
004445fa        return
