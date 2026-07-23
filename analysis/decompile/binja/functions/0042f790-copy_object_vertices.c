/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_object_vertices @ 0x42f790 */

0042f793        int32_t vertex_index = 0
0042f797        if (object->vertex_count s<= 0)
0042f797        return
0042f79c        int32_t vertex_byte_offset = 0
0042f7a3        struct Vec3* source_vertex = vertex_byte_offset + object->vertices
0042f7a8        struct Vec3* copied_vertex = object->copied_vertices + vertex_byte_offset
0042f7aa        vertex_index += 1
0042f7ad        vertex_byte_offset += 0xc
0042f7b0        copied_vertex->x = source_vertex->x
0042f7b5        copied_vertex->y = source_vertex->y
0042f7bb        copied_vertex->z = source_vertex->z
0042f7c3        do while (vertex_index s< object->vertex_count)
0042f7c8        return
