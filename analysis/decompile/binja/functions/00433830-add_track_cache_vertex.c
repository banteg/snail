/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_track_cache_vertex @ 0x433830 */

0043383b        struct Vec3* vertices_1 = source->vertices
0043383e        int32_t eax_1 = source_index * 3
00433844        void* eax_2 = vertices_1 + (eax_1 << 2)
00433847        float* position_1 = position
0043384b        long double x87_r7_1 = fconvert.t(*(vertices_1 + (eax_1 << 2))) + fconvert.t(*position_1)
00433853        float var_8 = fconvert.s(fconvert.t(*(eax_2 + 4)) + fconvert.t(position_1[1]))
0043385d        int16_t eax_3
0043385d        eax_3.b = project_uv
00433863        float var_4 = fconvert.s(fconvert.t(*(eax_2 + 8)) + fconvert.t(position_1[2]))
00433867        if (eax_3.b != 0)
00433877        u = fconvert.s((x87_r7_1 + fconvert.t(4f)) * fconvert.t(0.125f))
0043388b        v = fconvert.s((fconvert.t(var_4) - fconvert.t(manager->build_cache_row_base)) * fconvert.t(0.125f))
0043389a        int32_t result = 0
0043389c        int32_t esi = *vertex_count
004338a0        if (esi s> 0)
004338a2        float* edx_1 = &vertices->z
004338a5        long double temp1_1 = fconvert.t((edx_1 - 8)->x)
004338a5        x87_r7_1 - temp1_1
004338ad        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338af        long double x87_r6_10 = fconvert.t((edx_1 - 8)->y)
004338b2        long double temp2_1 = fconvert.t(var_8)
004338b2        x87_r6_10 - temp2_1
004338bb        if ((((x87_r6_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_10, temp2_1) ? 1 : 0) << 0xa | (x87_r6_10 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338bd        long double x87_r6_11 = fconvert.t((edx_1 - 8)->z)
004338bf        long double temp3_1 = fconvert.t(var_4)
004338bf        x87_r6_11 - temp3_1
004338c8        if ((((x87_r6_11 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_11, temp3_1) ? 1 : 0) << 0xa | (x87_r6_11 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338ca        long double x87_r6_12 = fconvert.t((edx_1 - 8)->u)
004338cd        long double temp4_1 = fconvert.t(u)
004338cd        x87_r6_12 - temp4_1
004338d6        if ((((x87_r6_12 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_12, temp4_1) ? 1 : 0) << 0xa | (x87_r6_12 == temp4_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
004338de        long double x87_r6_14 = fconvert.t(1f) - fconvert.t(v)
004338e2        long double temp5_1 = fconvert.t((edx_1 - 8)->v)
004338e2        x87_r6_14 - temp5_1
004338ea        if ((((x87_r6_14 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_14, temp5_1) ? 1 : 0) << 0xa | (x87_r6_14 == temp5_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
00433958        return result
004338ec        result += 1
004338ed        edx_1 = &edx_1[6]
004338f2        do while (result s< esi)
004338f4        int32_t eax_4 = result * 3
004338ff        *(vertices + (eax_4 << 3)) = fconvert.s(x87_r7_1)
0043390c        void* eax_5 = vertices + (eax_4 << 3)
0043390f        *(eax_5 + 4) = var_8
00433916        *(eax_5 + 8) = var_4
0043391d        *(eax_5 + 0x10) = u
00433924        *(eax_5 + 0x14) = fconvert.s(fconvert.t(1f) - fconvert.t(v))
00433927        *(eax_5 + 0xc) = color
0043392c        int32_t edx_5 = *vertex_count + 1
0043392f        *vertex_count = edx_5
00433933        if (edx_5 s> max_vertices)
0043393a        report_errorf("Vertex Cache overflow increase RSEGMENTCACHE_VERTEX_MAX")
0043394b        return *vertex_count - 1
