/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_or_append_object_texture_group_vertex @ 0x413bb0 */

00413bc4        if (arg2 s>= *(arg1 + 0x2c))
00413bcb        report_errorf("VertexRef out of Range")
00413bd3        int32_t ecx = *(arg1 + 0x38)
00413bd6        int32_t eax_1 = arg2 * 3
00413bd9        int32_t object_grouped_vertex_cursor_1 = g_object_grouped_vertex_cursor
00413bdf        void* edx = ecx + (eax_1 << 2)
00413be2        float eax_2 = *(ecx + (eax_1 << 2))
00413be9        float ecx_1 = *(edx + 4)
00413bf0        float edx_1 = *(edx + 8)
00413bf7        int32_t result = 0
00413bfb        if (object_grouped_vertex_cursor_1 s> 0)
00413c0c        float* ecx_2 = &g_object_grouped_vertex_scratch->y
00413c11        if ((*(arg1 + 0x10) & 4) == 0)
00413c40        long double x87_r7_4 = fconvert.t((ecx_2 - 4)->x)
00413c43        long double temp0_1 = fconvert.t(eax_2)
00413c43        x87_r7_4 - temp0_1
00413c4c        if ((((x87_r7_4 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp0_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c4e        long double x87_r7_5 = fconvert.t((ecx_2 - 4)->y)
00413c50        long double temp1_1 = fconvert.t(ecx_1)
00413c50        x87_r7_5 - temp1_1
00413c59        if ((((x87_r7_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp1_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c5b        long double x87_r7_6 = fconvert.t((ecx_2 - 4)->z)
00413c5e        long double temp3_1 = fconvert.t(edx_1)
00413c5e        x87_r7_6 - temp3_1
00413c67        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c69        long double x87_r7_7 = fconvert.t((ecx_2 - 4)->u)
00413c6c        long double temp5_1 = fconvert.t(arg3)
00413c6c        x87_r7_7 - temp5_1
00413c75        if ((((x87_r7_7 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp5_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c7d        long double x87_r7_9 = fconvert.t(1f) - fconvert.t(arg4)
00413c81        long double temp6_1 = fconvert.t((ecx_2 - 4)->v)
00413c81        x87_r7_9 - temp6_1
00413c89        if ((((x87_r7_9 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp6_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413d1f        return result
00413c16        if ((ecx_2 - 4)->source_vertex == arg2)
00413c18        long double x87_r7_1 = fconvert.t((ecx_2 - 4)->u)
00413c1b        long double temp2_1 = fconvert.t(arg3)
00413c1b        x87_r7_1 - temp2_1
00413c24        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c2c        long double x87_r7_3 = fconvert.t(1f) - fconvert.t(arg4)
00413c30        long double temp4_1 = fconvert.t((ecx_2 - 4)->v)
00413c30        x87_r7_3 - temp4_1
00413c38        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413d1f        return result
00413c8f        result += 1
00413c90        ecx_2 = &ecx_2[7]
00413c95        do while (result s< object_grouped_vertex_cursor_1)
00413cae        float* esi_2 = result * 0x1c
00413cb1        *(esi_2 + g_object_grouped_vertex_scratch) = fconvert.s(fconvert.t(eax_2))
00413cbe        *(&g_object_grouped_vertex_scratch->y + esi_2) = fconvert.s(fconvert.t(ecx_1))
00413ccb        *(&g_object_grouped_vertex_scratch->z + esi_2) = fconvert.s(fconvert.t(edx_1))
00413cd9        *(&g_object_grouped_vertex_scratch->u + esi_2) = fconvert.s(fconvert.t(arg3))
00413ced        *(&g_object_grouped_vertex_scratch->v + esi_2) = fconvert.s(fconvert.t(1f) - fconvert.t(arg4))
00413cf8        if ((*(arg1 + 0x10) & 0x10000) == 0)
00413d25        *(&g_object_grouped_vertex_scratch->diffuse + esi_2) = 0xffffffff
00413d0f        pack_color_rgba_u8(&g_object_grouped_vertex_scratch->diffuse + esi_2, *(arg1 + 0x48) + (arg2 << 4))
00413d33        *(&g_object_grouped_vertex_scratch->source_vertex + esi_2) = arg2
00413d3c        int32_t eax_11 = g_object_grouped_vertex_cursor + 1
00413d3f        g_object_grouped_vertex_cursor = eax_11
00413d4a        return eax_11 - 1
