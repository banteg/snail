/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: place_challenge_parcels_on_track @ 0x444240 */

00444263        int32_t eax
00444263        int16_t x87control
00444263        int16_t x87control_1
00444263        eax, x87control_1 = __ftol(x87control, float.t(*(arg1 + 0x28)) * fconvert.t(50f) * fconvert.t(0.00999999978f) + fconvert.t(*(arg1 + 0x34)) * fconvert.t(50f))
00444269        *(arg1 + 0x1b01e0) = eax + 1
0044426f        *(arg1 + 0x1b01e8) = eax + 1
00444275        int32_t* i = &data_53d390
0044428a        while (i s< 0x643390)
0044427a        *i = 0
00444280        i = &i[0x83]
0044428c        int32_t* j_1 = *(arg1 + 0x54)
0044428f        int32_t i_2 = 0
00444291        int32_t i_1 = 0
00444293        int32_t i_4 = 0
00444299        if (j_1 s> 0)
0044429b        int32_t* edx_1 = &data_6447e8
004442a0        j_1 = arg1 + 0x5ccb64
004442b2        if ((j_1[-0x27].b & 1) != 0 && *j_1 == 0)
004442b4        *edx_1 = i_1
004442b6        i_2 += 1
004442b7        edx_1 = &edx_1[1]
004442bd        i_1 += 1
004442be        j_1 = &j_1[0x3d]
004442c6        do while (i_1 s< *(arg1 + 0x54))
004442c8        i_4 = i_2
004442d2        int32_t edi_2 = 0
004442d6        float out_angle
004442d6        if (*(arg1 + 0x1b01e0) s> 0)
004442dc        int32_t ebx_1 = i_2 - 1
004442e7        while (i_2 s> 0)
004442f1        void* var_5c_1 = &data_4a5100
004442f6        int32_t* j_2 = j_1
00444302        int32_t eax_3
00444302        eax_3, x87control_1 = __ftol(x87control_1, random_float_below(fconvert.s(float.t(i_4))))
00444307        float out_angle_1 = *((eax_3 << 2) + &data_6447e8)
0044430e        int32_t* esi = (eax_3 << 2) + &data_6447e8
00444315        out_angle = out_angle_1
00444319        edi_2 += 1
00444320        int32_t ecx = out_angle_1 i* 0x3d
0044432d        j_1 = arg1 + (ecx << 2)
00444331        j_1[0x1732b2] = *(arg1 + (ecx << 2) + 0x5ccac8) | 0x11
00444343        j_1[0x1732d7] = fconvert.s(fconvert.t(j_1[0x1732d7]) + fconvert.t(1f))
00444350        if ((j_1[0x1732b2].b & 0x20) != 0)
0044435e        j_1[0x1732d6] = fconvert.s(fconvert.t(j_1[0x1732d6]) * fconvert.t(-1f))
0044436d        if (((j_1[0x1732b2]).w:1.b & 0x40) != 0)
0044437f        j_1[0x1732d8] = fconvert.s(float.t(out_angle) + fconvert.t(j_1[0x1732d8]) + fconvert.t(0.5f))
00444387        if (eax_3 s< ebx_1)
0044438b        j_1 = ebx_1 - eax_3
00444396        int32_t* j
00444390        *esi = esi[1]
00444392        esi = &esi[1]
00444395        j = j_1
00444395        j_1 -= 1
00444396        do while (j != 1)
004443a3        ebx_1 -= 1
004443a6        i_4 -= 1
004443aa        if (edi_2 s>= *(arg1 + 0x1b01e0))
004443aa        break
004442e1        i_2 = i_4
004443b0        int32_t var_5c_2 = edi_2
004443b1        char* var_60_2 = "Challenge parcel count %i\n"
004443b6        *(arg1 + 0x1b01e0) = edi_2
004443c1        int32_t i_3 = *(arg1 + 0x54)
004443c9        int32_t i_5 = 0
004443d1        if (i_3 s> 0)
004443d7        int32_t* esi_1 = arg1 + 0x5ccac8
004443dd        char eax_5 = (*esi_1).b
004443e9        if ((eax_5 & 1) != 0 && (eax_5 & 0x40) != 0)
004443f5        int32_t eax_6 = get_track_cell_row_index(esi_1[0x29])
00444402        int32_t eax_7
00444402        eax_7, x87control_1 = __ftol(x87control_1, fconvert.t(esi_1[0x26]))
00444409        int32_t edi_4 = eax_7 - eax_6
0044440b        if (eax_7 - eax_6 s< 0)
0044440d        edi_4 = 0
0044440f        struct TrackRowCell* cell = esi_1[0x29]
00444415        struct PathTemplate* template_record = cell->template_record
0044441c        if (template_record->kind != PATH_TEMPLATE_KIND_NONLINEAR_42)
00444471        int32_t eax_13 = get_track_cell_row_index(cell)
00444482        get_path_position_at_node(*(esi_1[0x29] + 0x38), &esi_1[0x24], edi_4, eax_13, &esi_1[0x24])
0044444f        struct PathTemplateTransform transform
0044444f        x87control_1 = compute_kind42_attachment_transform((&template_record->primary_samples->special_scalar)[edi_4 * 0x2a], esi_1[0x24], esi_1[0x25], &transform, &out_angle)
00444458        float y = transform.position.y
0044445c        esi_1[0x24] = transform.position.x
00444462        esi_1[0x25] = y
0044448e        i_3 = i_5 + 1
0044448f        esi_1 = &esi_1[0x3d]
00444497        i_5 = i_3
0044449b        do while (i_3 s< *(arg1 + 0x54))
004444a8        return i_3
