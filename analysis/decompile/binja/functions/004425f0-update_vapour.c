/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_vapour @ 0x4425f0 */

004425f0        int32_t point_count = vapour->point_count
004425fc        if (point_count s< 2)
004425fe        uint32_t list_flags = vapour->body.bod.bod.list_flags
00442601        list_flags.b &= 0xdf
00442603        vapour->body.bod.bod.list_flags = list_flags
00442609        return
00442618        vapour->body.bod.bod.list_flags |= 0x20
00442620        vapour->body.bod.object->vertex_count = (point_count << 2) + 0xfffffffc
0044262b        if (vapour->z_floor != 0)
00442633        int32_t i = 0
00442637        if (vapour->point_count s> 0)
00442639        int32_t edi_1 = 0
0044263b        struct TransformMatrix* points = vapour->points
00442641        float* z_floor = vapour->z_floor
00442647        long double x87_r7_1 = fconvert.t(*(&points->position.z + edi_1))
0044264b        long double temp0_1 = fconvert.t(*z_floor)
0044264b        x87_r7_1 - temp0_1
00442656        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044265a        *(&points->position.z + edi_1) = *z_floor
00442662        i += 1
00442663        edi_1 += 0x40
00442668        do while (i s< vapour->point_count)
00442670        int32_t i_1 = 0
00442675        if (vapour->point_count - 1 s> 0)
00442689        long double x87_r7_2 = fconvert.t(vapour->half_width)
00442692        float* eax_7 = &vapour->points[i_1]
004426c4        float var_5c_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(eax_7[1]))) + fconvert.t(eax_7[0xd]))
004426d1        float* esi_3 = &vapour->body.bod.object->vertices[i_1 * 4]
004426d3        float var_58_1 = fconvert.s(x87_r7_2 * fconvert.t(eax_7[2]) + fconvert.t(eax_7[0xe]))
004426d7        *esi_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(*eax_7))) + fconvert.t(eax_7[0xc]))
004426dd        esi_3[1] = var_5c_1
004426e4        esi_3[2] = var_58_1
004426f3        long double x87_r7_6 = fneg(fconvert.t(vapour->half_width))
004426f5        float* esi_5 = &vapour->points[i_1]
00442721        float var_50_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(esi_5[1]))) + fconvert.t(esi_5[0xd]))
0044272e        float var_4c_1 = fconvert.s(x87_r7_6 * fconvert.t(esi_5[2]) + fconvert.t(esi_5[0xe]))
00442732        float* esi_8 = &vapour->body.bod.object->vertices[i_1 * 4 + 1]
00442736        *esi_8 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(*esi_5))) + fconvert.t(esi_5[0xc]))
0044273c        esi_8[1] = var_50_1
00442743        esi_8[2] = var_4c_1
00442752        long double x87_r7_10 = fneg(fconvert.t(vapour->half_width))
00442754        float* esi_10 = &vapour->points[i_1]
0044277c        float var_44_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_10 * fconvert.t(esi_10[1]))) + fconvert.t(esi_10[0x1d]))
00442789        float var_40_1 = fconvert.s(x87_r7_10 * fconvert.t(esi_10[2]) + fconvert.t(esi_10[0x1e]))
0044278d        float* esi_13 = &vapour->body.bod.object->vertices[i_1 * 4 + 2]
00442795        *esi_13 = fconvert.s(fconvert.t(fconvert.s(x87_r7_10 * fconvert.t(*esi_10))) + fconvert.t(esi_10[0x1c]))
0044279b        esi_13[1] = var_44_1
004427a2        esi_13[2] = var_40_1
004427ab        long double x87_r7_13 = fconvert.t(vapour->half_width)
004427b1        float* edx_8 = &vapour->points[i_1]
004427dd        float var_38_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_13 * fconvert.t(edx_8[1]))) + fconvert.t(edx_8[0x1d]))
004427ea        float var_34_1 = fconvert.s(x87_r7_13 * fconvert.t(edx_8[2]) + fconvert.t(edx_8[0x1e]))
004427ee        float* edx_11 = &vapour->body.bod.object->vertices[i_1 * 4 + 3]
004427f2        *edx_11 = fconvert.s(fconvert.t(fconvert.s(x87_r7_13 * fconvert.t(*edx_8))) + fconvert.t(edx_8[0x1c]))
004427f8        edx_11[1] = var_38_1
004427ff        edx_11[2] = var_34_1
00442802        int32_t point_count_1 = vapour->point_count
0044280b        if (point_count_1 == 2)
00442815        vapour->body.bod.object->facequads[i_1].uv[0].v = 0
0044281f        vapour->body.bod.object->facequads[i_1].uv[1].v = 0
0044282e        vapour->body.bod.object->facequads[i_1].uv[2].v = 0x3f800000
00442838        vapour->body.bod.object->facequads[i_1].uv[3].v = 0x3f800000
00442842        if (i_1 != 0)
00442875        vapour->body.bod.object->facequads[i_1].uv[0].v = 0x3f000000
0044287f        vapour->body.bod.object->facequads[i_1].uv[1].v = 0x3f000000
00442883        struct Object* object = vapour->body.bod.object
00442886        if (i_1 == point_count_1 - 2)
0044282e        object->facequads[i_1].uv[2].v = 0x3f800000
00442838        vapour->body.bod.object->facequads[i_1].uv[3].v = 0x3f800000
0044288b        object->facequads[i_1].uv[2].v = 0x3f000000
00442895        vapour->body.bod.object->facequads[i_1].uv[3].v = 0x3f000000
0044284a        vapour->body.bod.object->facequads->uv[0].v = 0f
00442853        vapour->body.bod.object->facequads->uv[1].v = 0f
0044285c        vapour->body.bod.object->facequads->uv[2].v = 0.5f
00442865        vapour->body.bod.object->facequads->uv[3].v = 0.5f
0044289f        i_1 += 1
004428a3        do while (i_1 s< vapour->point_count - 1)
004428c0        *vapour->body.bod.object->group_primitive_counts = vapour->point_count * 2 - 2
004428c5        return
