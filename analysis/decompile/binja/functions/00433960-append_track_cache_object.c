/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_track_cache_object @ 0x433960 */

00433969        int32_t ebp = 0
00433979        int32_t var_10 = 0
0043397d        if (source->facequad_count s> 0)
00433aff        bool cond:3_1
00433994        struct Vec3 position_1
00433994        position_1.x = position->x
0043399b        position_1.y = position->y
004339a3        position_1.z = position->z
004339a7        void* eax_3 = source->facequads + ebp
004339cb        int32_t source_index_3 = 0
004339cd        source_index_3.w = *(eax_3 + 2)
004339e4        indices[*index_count] = add_track_cache_vertex(manager, source, &position_1, source_index_3, *(eax_3 + 0x10), *(eax_3 + 0x14), vertices, vertex_count, max_vertices, max_indices, color, project_uv)
004339ef        void* eax_5 = source->facequads + ebp
00433a13        int32_t source_index = 0
00433a15        source_index.w = *(eax_5 + 4)
00433a2c        indices[*index_count + 1] = add_track_cache_vertex(manager, source, &position_1, source_index, *(eax_5 + 0x18), *(eax_5 + 0x1c), vertices, vertex_count, max_vertices, max_indices, color, project_uv)
00433a38        void* eax_7 = source->facequads + ebp
00433a5d        int32_t source_index_1 = 0
00433a63        source_index_1.w = *(eax_7 + 6)
00433a75        indices[*index_count + 2] = add_track_cache_vertex(manager, source, &position_1, source_index_1, *(eax_7 + 0x20), *(eax_7 + 0x24), vertices, vertex_count, max_vertices, max_indices, color, project_uv)
00433a81        int32_t eax_9 = *index_count
00433a83        int32_t eax_15
00433a83        if ((*(source->facequads + ebp) & 0x80) != 0)
00433ae9        eax_15 = eax_9 + 3
00433a89        indices[eax_9 + 3] = indices[eax_9]
00433a8e        int32_t eax_10 = *index_count
00433a9e        indices[eax_10 + 4] = indices[eax_10 + 2]
00433ab4        void* eax_12 = source->facequads + ebp
00433ac4        int32_t source_index_2 = 0
00433ac7        source_index_2.w = *(eax_12 + 8)
00433add        indices[*index_count + 5] = add_track_cache_vertex(manager, source, &position_1, source_index_2, *(eax_12 + 0x28), *(eax_12 + 0x2c), vertices, vertex_count, max_vertices, max_indices, color, project_uv)
00433ae4        eax_15 = *index_count + 6
00433aec        *index_count = eax_15
00433af6        ebp += 0x30
00433af9        cond:3_1 = var_10 + 1 s< source->facequad_count
00433afb        var_10 += 1
00433aff        do while (cond:3_1)
00433b0a        int32_t result = *index_count
00433b11        if (result s<= max_indices)
00433b23        return result
00433b18        return report_errorf("Index Cache overflow increase RSEGMENTCACHE_INDEX_MAX", manager, var_10)
