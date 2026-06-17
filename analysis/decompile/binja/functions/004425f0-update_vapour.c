/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_vapour @ 0x4425f0 */

004425f0        int32_t point_count = trail->point_count
004425fc        if (point_count s< 2)
004425fe        int32_t flags = trail->flags
00442601        flags.b &= 0xdf
00442603        trail->flags = flags
00442609        return flags
00442618        trail->flags |= 0x20
00442620        trail->owner->vertex_count = (point_count << 2) + 0xfffffffc
0044262b        if (trail->z_floor != 0)
00442633        int32_t i = 0
00442637        if (trail->point_count s> 0)
00442639        int32_t edi_1 = 0
0044263b        struct TransformMatrix* points = trail->points
00442641        int32_t z_floor = trail->z_floor
00442647        long double x87_r7_1 = fconvert.t(*(&points->position.z + edi_1))
0044264b        long double temp0_1 = fconvert.t(*z_floor)
0044264b        x87_r7_1 - temp0_1
00442656        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044265a        *(&points->position.z + edi_1) = *z_floor
00442662        i += 1
00442663        edi_1 += 0x40
00442668        do while (i s< trail->point_count)
00442670        int32_t i_1 = 0
00442675        if (trail->point_count - 1 s> 0)
00442689        long double x87_r7_2 = fconvert.t(trail->half_width)
00442692        float* eax_7 = &trail->points[i_1]
004426c4        float var_5c_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(eax_7[1]))) + fconvert.t(eax_7[0xd]))
004426d1        float* esi_3 = &trail->owner->vertices[i_1]
004426d3        float var_58_1 = fconvert.s(x87_r7_2 * fconvert.t(eax_7[2]) + fconvert.t(eax_7[0xe]))
004426d7        *esi_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_2 * fconvert.t(*eax_7))) + fconvert.t(eax_7[0xc]))
004426dd        esi_3[1] = var_5c_1
004426e4        esi_3[2] = var_58_1
004426f3        long double x87_r7_6 = fneg(fconvert.t(trail->half_width))
004426f5        float* esi_5 = &trail->points[i_1]
00442721        float var_50_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(esi_5[1]))) + fconvert.t(esi_5[0xd]))
0044272e        float var_4c_1 = fconvert.s(x87_r7_6 * fconvert.t(esi_5[2]) + fconvert.t(esi_5[0xe]))
00442732        float* esi_8 = &trail->owner->vertices[i_1].corner_b
00442736        *esi_8 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(*esi_5))) + fconvert.t(esi_5[0xc]))
0044273c        esi_8[1] = var_50_1
00442743        esi_8[2] = var_4c_1
00442752        long double x87_r7_10 = fneg(fconvert.t(trail->half_width))
00442754        float* esi_10 = &trail->points[i_1]
0044277c        float var_44_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_10 * fconvert.t(esi_10[1]))) + fconvert.t(esi_10[0x1d]))
00442789        float var_40_1 = fconvert.s(x87_r7_10 * fconvert.t(esi_10[2]) + fconvert.t(esi_10[0x1e]))
0044278d        float* esi_13 = &trail->owner->vertices[i_1].corner_c
00442795        *esi_13 = fconvert.s(fconvert.t(fconvert.s(x87_r7_10 * fconvert.t(*esi_10))) + fconvert.t(esi_10[0x1c]))
0044279b        esi_13[1] = var_44_1
004427a2        esi_13[2] = var_40_1
004427ab        long double x87_r7_13 = fconvert.t(trail->half_width)
004427b1        float* edx_8 = &trail->points[i_1]
004427dd        float var_38_1 = fconvert.s(fconvert.t(fconvert.s(x87_r7_13 * fconvert.t(edx_8[1]))) + fconvert.t(edx_8[0x1d]))
004427ea        float var_34_1 = fconvert.s(x87_r7_13 * fconvert.t(edx_8[2]) + fconvert.t(edx_8[0x1e]))
004427ee        float* edx_11 = &trail->owner->vertices[i_1].corner_d
004427f2        *edx_11 = fconvert.s(fconvert.t(fconvert.s(x87_r7_13 * fconvert.t(*edx_8))) + fconvert.t(edx_8[0x1c]))
004427f8        edx_11[1] = var_38_1
004427ff        edx_11[2] = var_34_1
00442802        int32_t point_count_1 = trail->point_count
0044280b        if (point_count_1 == 2)
00442815        trail->owner->vertex_attributes[i_1 * 0xc + 5] = 0
0044281f        trail->owner->vertex_attributes[i_1 * 0xc + 7] = 0
0044282e        trail->owner->vertex_attributes[i_1 * 0xc + 9] = 0x3f800000
00442838        trail->owner->vertex_attributes[i_1 * 0xc + 0xb] = 0x3f800000
00442842        if (i_1 != 0)
00442875        trail->owner->vertex_attributes[i_1 * 0xc + 5] = 0x3f000000
0044287f        trail->owner->vertex_attributes[i_1 * 0xc + 7] = 0x3f000000
00442883        struct VapourTrailOwner* owner = trail->owner
00442886        if (i_1 == point_count_1 - 2)
0044282e        owner->vertex_attributes[i_1 * 0xc + 9] = 0x3f800000
00442838        trail->owner->vertex_attributes[i_1 * 0xc + 0xb] = 0x3f800000
0044288b        owner->vertex_attributes[i_1 * 0xc + 9] = 0x3f000000
00442895        trail->owner->vertex_attributes[i_1 * 0xc + 0xb] = 0x3f000000
0044284a        trail->owner->vertex_attributes[5] = 0
00442853        trail->owner->vertex_attributes[7] = 0
0044285c        trail->owner->vertex_attributes[9] = 0x3f000000
00442865        trail->owner->vertex_attributes[0xb] = 0x3f000000
0044289f        i_1 += 1
004428a3        do while (i_1 s< trail->point_count - 1)
004428aa        int32_t point_count_2 = trail->point_count
004428c0        *trail->owner->index_count_out = point_count_2 * 2 - 2
004428c5        return point_count_2 * 2 - 2
