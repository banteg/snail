/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_track_cache_vertex @ 0x433830 */

0043383b        struct Vec3* source_vertices = source->vertices
0043383e        int32_t source_vertex_component_index = source_index * 3
00433844        struct Vec3* source_vertex = source_vertices + (source_vertex_component_index << 2)
0043384b        long double x87_r7_1 = fconvert.t(*(source_vertices + (source_vertex_component_index << 2))) + fconvert.t(position->x)
00433853        struct Vec3 transformed
00433853        transformed.y = fconvert.s(fconvert.t(source_vertex->y) + fconvert.t(position->y))
0043385d        int16_t eax_1
0043385d        eax_1.b = project_uv
00433863        transformed.z = fconvert.s(fconvert.t(source_vertex->z) + fconvert.t(position->z))
00433867        if (eax_1.b != 0)
00433877        u = fconvert.s((x87_r7_1 + fconvert.t(4f)) * fconvert.t(0.125f))
0043388b        v = fconvert.s((fconvert.t(transformed.z) - fconvert.t(manager->build_cache_row_base)) * fconvert.t(0.125f))
0043389a        int32_t vertex_index = 0
0043389c        int32_t existing_vertex_count = *vertex_count
004338a0        if (existing_vertex_count s> 0)
004338a2        float* existing_vertex_z_cursor = &vertices->z
004338a5        long double temp1_1 = fconvert.t(existing_vertex_z_cursor[-2])
004338a5        x87_r7_1 - temp1_1
004338ad        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338af        long double x87_r6_10 = fconvert.t(existing_vertex_z_cursor[-1])
004338b2        long double temp2_1 = fconvert.t(transformed.y)
004338b2        x87_r6_10 - temp2_1
004338bb        if ((((x87_r6_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_10, temp2_1) ? 1 : 0) << 0xa | (x87_r6_10 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338bd        long double x87_r6_11 = fconvert.t(*existing_vertex_z_cursor)
004338bf        long double temp3_1 = fconvert.t(transformed.z)
004338bf        x87_r6_11 - temp3_1
004338c8        if ((((x87_r6_11 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_11, temp3_1) ? 1 : 0) << 0xa | (x87_r6_11 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338ca        long double x87_r6_12 = fconvert.t(existing_vertex_z_cursor[2])
004338cd        long double temp4_1 = fconvert.t(u)
004338cd        x87_r6_12 - temp4_1
004338d6        if ((((x87_r6_12 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_12, temp4_1) ? 1 : 0) << 0xa | (x87_r6_12 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338de        long double x87_r6_14 = fconvert.t(1f) - fconvert.t(v)
004338e2        long double temp5_1 = fconvert.t(existing_vertex_z_cursor[3])
004338e2        x87_r6_14 - temp5_1
004338ea        if ((((x87_r6_14 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_14, temp5_1) ? 1 : 0) << 0xa | (x87_r6_14 == temp5_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
00433958        return vertex_index
004338ec        vertex_index += 1
004338ed        existing_vertex_z_cursor = &existing_vertex_z_cursor[6]
004338f2        do while (vertex_index s< existing_vertex_count)
004338f4        int32_t staged_vertex_component_index = vertex_index * 3
004338ff        *(vertices + (staged_vertex_component_index << 3)) = fconvert.s(x87_r7_1)
0043390c        struct ObjectRenderVertex* staged_vertex = vertices + (staged_vertex_component_index << 3)
0043390f        staged_vertex->y = transformed.y
00433916        staged_vertex->z = transformed.z
0043391d        staged_vertex->u = u
00433924        staged_vertex->v = fconvert.s(fconvert.t(1f) - fconvert.t(v))
00433927        staged_vertex->diffuse = color
0043392c        int32_t next_vertex_count = *vertex_count + 1
0043392f        *vertex_count = next_vertex_count
00433933        if (next_vertex_count s> max_vertices)
0043393a        report_errorf("Vertex Cache overflow increase RSEGMENTCACHE_VERTEX_MAX")
0043394b        return *vertex_count - 1
