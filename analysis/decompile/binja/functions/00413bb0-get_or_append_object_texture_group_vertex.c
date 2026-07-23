/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_or_append_object_texture_group_vertex @ 0x413bb0 */

00413bc4        if (vertex_index s>= object->vertex_count)
00413bcb        report_errorf("VertexRef out of Range")
00413bd3        struct Vec3* source_vertices = object->vertices
00413bd6        int32_t source_float_index = vertex_index * 3
00413bd9        int32_t grouped_vertex_count = g_object_grouped_vertex_cursor
00413bdf        struct Vec3* source_vertex = source_vertices + (source_float_index << 2)
00413be2        float source_x = *(source_vertices + (source_float_index << 2))
00413be9        float source_y = source_vertex->y
00413bf0        float source_z = source_vertex->z
00413bf7        int32_t grouped_vertex_index = 0
00413bfb        if (grouped_vertex_count s> 0)
00413c0c        float* grouped_vertex_y_cursor = &g_object_grouped_vertex_scratch->y
00413c11        if ((object->flags & OBJECT_FLAG_DYNAMIC_VERTICES) == 0)
00413c40        long double x87_r7_4 = fconvert.t(grouped_vertex_y_cursor[-1])
00413c43        long double temp0_1 = fconvert.t(source_x)
00413c43        x87_r7_4 - temp0_1
00413c4c        if ((((x87_r7_4 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp0_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c4e        long double x87_r7_5 = fconvert.t(*grouped_vertex_y_cursor)
00413c50        long double temp1_1 = fconvert.t(source_y)
00413c50        x87_r7_5 - temp1_1
00413c59        if ((((x87_r7_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp1_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c5b        long double x87_r7_6 = fconvert.t(grouped_vertex_y_cursor[1])
00413c5e        long double temp3_1 = fconvert.t(source_z)
00413c5e        x87_r7_6 - temp3_1
00413c67        if ((((x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c69        long double x87_r7_7 = fconvert.t(grouped_vertex_y_cursor[3])
00413c6c        long double temp5_1 = fconvert.t(u)
00413c6c        x87_r7_7 - temp5_1
00413c75        if ((((x87_r7_7 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp5_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c7d        long double x87_r7_9 = fconvert.t(1f) - fconvert.t(v)
00413c81        long double temp6_1 = fconvert.t(grouped_vertex_y_cursor[4])
00413c81        x87_r7_9 - temp6_1
00413c89        if ((((x87_r7_9 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp6_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413d1f        return grouped_vertex_index
00413c16        if (grouped_vertex_y_cursor[5] == vertex_index)
00413c18        long double x87_r7_1 = fconvert.t(grouped_vertex_y_cursor[3])
00413c1b        long double temp2_1 = fconvert.t(u)
00413c1b        x87_r7_1 - temp2_1
00413c24        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413c2c        long double x87_r7_3 = fconvert.t(1f) - fconvert.t(v)
00413c30        long double temp4_1 = fconvert.t(grouped_vertex_y_cursor[4])
00413c30        x87_r7_3 - temp4_1
00413c38        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00413d1f        return grouped_vertex_index
00413c8f        grouped_vertex_index += 1
00413c90        grouped_vertex_y_cursor = &grouped_vertex_y_cursor[7]
00413c95        do while (grouped_vertex_index s< grouped_vertex_count)
00413cb1        g_object_grouped_vertex_scratch[grouped_vertex_index].x = fconvert.s(fconvert.t(source_x))
00413cbe        g_object_grouped_vertex_scratch[grouped_vertex_index].y = fconvert.s(fconvert.t(source_y))
00413ccb        g_object_grouped_vertex_scratch[grouped_vertex_index].z = fconvert.s(fconvert.t(source_z))
00413cd9        g_object_grouped_vertex_scratch[grouped_vertex_index].u = fconvert.s(fconvert.t(u))
00413ced        g_object_grouped_vertex_scratch[grouped_vertex_index].v = fconvert.s(fconvert.t(1f) - fconvert.t(v))
00413cf8        if ((object->flags & OBJECT_FLAG_USE_VERTEX_COLOURS) == 0)
00413d25        g_object_grouped_vertex_scratch[grouped_vertex_index].diffuse = 0xffffffff
00413d0f        pack_color_rgba_u8(&g_object_grouped_vertex_scratch[grouped_vertex_index].diffuse, &object->vertex_colours[vertex_index])
00413d33        g_object_grouped_vertex_scratch[grouped_vertex_index].source_vertex = vertex_index
00413d3c        int32_t eax_8 = g_object_grouped_vertex_cursor + 1
00413d3f        g_object_grouped_vertex_cursor = eax_8
00413d4a        return eax_8 - 1
