/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: project_position_onto_track_attachment @ 0x4444b0 */

004444bf        int32_t eax
004444bf        int16_t x87control
004444bf        int16_t x87control_1
004444bf        eax, x87control_1 = __ftol(x87control, fconvert.t(arg2[2]))
004444d4        char* eax_1 = arg1 + eax * 0xf4 + 0x5ccac8
004444db        *arg3 = 0
004444e4        if ((*eax_1 & 0x40) != 0)
004444ea        struct TrackRowCell* cell = *(eax_1 + 0xa4)
004444f3        struct PathTemplate* template_record = cell->template_record
004444f6        int32_t eax_2 = get_track_cell_row_index(cell)
0044450f        int32_t ecx_5 = (__ftol(x87control_1, fconvert.t(arg2[2])) - eax_2) * 7
0044451d        float* eax_6 = template_record->primary_samples + ecx_5 * 0x18
00444520        if (template_record->kind == 0x2a)
0044453f        float var_40[0xc]
0044453f        int32_t eax_8 = compute_kind42_attachment_transform(eax_6[0x28], *arg2, arg2[1], &var_40, arg3)
0044454c        int32_t var_10
0044454c        *arg2 = var_10
0044454e        int32_t var_c
0044454e        arg2[1] = var_c
00444557        return eax_8
0044455a        long double x87_r7_2 = fconvert.t(arg2[1])
0044456f        long double x87_r7_3 = x87_r7_2 * fconvert.t(eax_6[6])
00444574        long double x87_r6_6 = fconvert.t(*arg2) - fconvert.t(eax_6[0x24])
004445bc        long double x87_r6_8 = x87_r6_6 * fconvert.t(eax_6[2]) + fconvert.t(fconvert.s(fconvert.t(eax_6[0xe]) + fconvert.t(cell->world_z)))
004445d0        long double x87_r5_13 = fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_6[0xd]) + fconvert.t(cell->floor_height))) + fconvert.t(fconvert.s(x87_r6_6 * fconvert.t(eax_6[1]))))) + fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(eax_6[5])))
004445d4        eax_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(eax_6[0xc]) + fconvert.t(cell->world_x) + fconvert.t(fconvert.s(x87_r6_6 * fconvert.t(*eax_6))))) + fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(eax_6[4]))))
004445d8        *arg2 = eax_1
004445e4        arg2[1] = fconvert.s(x87_r5_13)
004445f1        arg2[2] = fconvert.s(x87_r6_8 + x87_r7_3)
004445fa        return eax_1
