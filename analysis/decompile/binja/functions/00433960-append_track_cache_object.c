/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_track_cache_object @ 0x433960 */

00433969        int32_t face_byte_offset = 0
00433979        int32_t face_index = 0
0043397d        if (source->facequad_count s> 0)
00433aff        bool cond:3_1
00433994        struct Vec3 local_position
00433994        local_position.x = position->x
0043399b        local_position.y = position->y
004339a3        local_position.z = position->z
004339a7        struct ObjectFaceQuad* face_vertex_0 = source->facequads + face_byte_offset
004339e4        indices[*index_count] = add_track_cache_vertex(manager, source, &local_position, face_vertex_0->vertex_0, face_vertex_0->uv[0].u, face_vertex_0->uv[0].v, vertices, vertex_count, max_vertices, max_indices, color, project_uv)
004339ef        struct ObjectFaceQuad* face_vertex_1 = source->facequads + face_byte_offset
00433a2c        indices[*index_count + 1] = add_track_cache_vertex(manager, source, &local_position, face_vertex_1->vertex_1, face_vertex_1->uv[1].u, face_vertex_1->uv[1].v, vertices, vertex_count, max_vertices, max_indices, color, project_uv)
00433a38        struct ObjectFaceQuad* face_vertex_2 = source->facequads + face_byte_offset
00433a75        indices[*index_count + 2] = add_track_cache_vertex(manager, source, &local_position, face_vertex_2->vertex_2, face_vertex_2->uv[2].u, face_vertex_2->uv[2].v, vertices, vertex_count, max_vertices, max_indices, color, project_uv)
00433a81        int32_t triangle_index_base = *index_count
00433a83        int32_t next_index_count
00433a83        if ((*(source->facequads + face_byte_offset) & 0x80) != 0)
00433ae9        next_index_count = triangle_index_base + 3
00433a89        indices[triangle_index_base + 3] = indices[triangle_index_base]
00433a8e        int32_t quad_index_base = *index_count
00433a9e        indices[quad_index_base + 4] = indices[quad_index_base + 2]
00433ab4        struct ObjectFaceQuad* face_vertex_3 = source->facequads + face_byte_offset
00433add        indices[*index_count + 5] = add_track_cache_vertex(manager, source, &local_position, face_vertex_3->vertex_3, face_vertex_3->uv[3].u, face_vertex_3->uv[3].v, vertices, vertex_count, max_vertices, max_indices, color, project_uv)
00433ae4        next_index_count = *index_count + 6
00433aec        *index_count = next_index_count
00433af6        face_byte_offset += 0x30
00433af9        cond:3_1 = face_index + 1 s< source->facequad_count
00433afb        face_index += 1
00433aff        do while (cond:3_1)
00433b0a        int32_t result = *index_count
00433b11        if (result s<= max_indices)
00433b23        return result
00433b18        return report_errorf("Index Cache overflow increase RSEGMENTCACHE_INDEX_MAX", manager, face_index)
