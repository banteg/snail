/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_object_texture_group_buffers @ 0x413d50 */

00413d54        struct Object* object_1 = object
00413d5d        int32_t scan_face_byte_offset = 0
00413d61        if (object_1->vertex_count == 0)
00413d63        object_1->group_index_starts = nullptr
00413d69        object_1->group_texture_refs = nullptr
00413d6f        object_1->group_primitive_counts = nullptr
00413d75        object_1->render_buffers = nullptr
00413d7b        object_1->index_buffer = nullptr
00413d87        return
00413d96        object_1->flags |= OBJECT_FLAG_RENDER_BUFFERS_READY
00413da0        int32_t* allocated_group_index_starts = allocate_tracked_memory(object_1->texture_group_count << 2, "DX TextureGroups")
00413dad        int32_t size = object_1->texture_group_count << 2
00413db1        object_1->group_index_starts = allocated_group_index_starts
00413db7        struct TextureRef** allocated_group_texture_refs = allocate_tracked_memory(size, "DX TextureGroupsTexture Ref")
00413dc4        int32_t size_1 = object_1->texture_group_count << 2
00413dc8        object_1->group_texture_refs = allocated_group_texture_refs
00413dd6        object_1->group_primitive_counts = allocate_tracked_memory(size_1, "DX TextureGroupsTexture Primcount")
00413de1        g_object_grouped_vertex_scratch = get_archive_data_base()
00413de6        uint16_t* index_scratch = get_archive_data_end()
00413def        g_object_grouped_vertex_cursor = 0
00413df8        int32_t group_face_index = 0
00413dfa        int32_t index_count = 0
00413dfc        int32_t face_index = 0
00413e00        bool cond:0 = (object_1->flags.b & 4) == 0
00413e02        __builtin_memset(&object, 0, 4)
00413e06        if (not(cond:0))
00413e0f        int32_t source_vertex_index = 0
00413e13        if (object_1->vertex_count s> 0)
00413e1c        int32_t scan_face_index = 0
00413e22        if (object_1->facequad_count s> 0)
00413e94        bool cond:4_1
00413e27        int32_t ecx_1 = 0
00413e29        struct ObjectFaceQuad* scan_face = object_1->facequads + scan_face_byte_offset
00413e2b        ecx_1.w = scan_face->vertex_0
00413e31        if (ecx_1 != source_vertex_index)
00413e3c        int32_t ecx_2 = 0
00413e3e        ecx_2.w = scan_face->vertex_1
00413e44        if (ecx_2 != source_vertex_index)
00413e4f        int32_t ecx_3 = 0
00413e51        ecx_3.w = scan_face->vertex_2
00413e57        if (ecx_3 == source_vertex_index)
00413e7b        get_or_append_object_texture_group_vertex(object_1, source_vertex_index, scan_face->uv[2].u, scan_face->uv[2].v)
00413e65        if ((scan_face->.header_word.b & 0x80) == 0)
00413e67        int32_t ecx_4 = 0
00413e69        ecx_4.w = scan_face->vertex_3
00413e6f        if (ecx_4 == source_vertex_index)
00413e7b        get_or_append_object_texture_group_vertex(object_1, source_vertex_index, scan_face->uv[3].u, scan_face->uv[3].v)
00413e7b        get_or_append_object_texture_group_vertex(object_1, source_vertex_index, scan_face->uv[1].u, scan_face->uv[1].v)
00413e7b        get_or_append_object_texture_group_vertex(object_1, source_vertex_index, scan_face->uv[0].u, scan_face->uv[0].v)
00413e8b        scan_face_byte_offset += 0x30
00413e8e        cond:4_1 = scan_face_index + 1 s< object_1->facequad_count
00413e90        scan_face_index += 1
00413e94        do while (cond:4_1)
00413e96        group_face_index = 0
00413e9a        scan_face_byte_offset = 0
00413e9f        source_vertex_index += 1
00413ea2        do while (source_vertex_index s< object_1->vertex_count)
00413eab        int32_t group_index = 0
00413eaf        int32_t current_group_index = 0
00413eb3        if (object_1->texture_group_count s> 0)
00413eca        while (true)
00413eca        int32_t primitive_count = 0
00413ed1        int32_t face_byte_offset = group_face_index * 0x30
00413ed8        object_1->group_texture_refs[group_index] = *(&object_1->facequads->texture_ref + face_byte_offset)
00413ee1        object_1->group_index_starts[group_index] = index_count
00413eea        if (group_face_index s< object_1->texture_group_ends[group_index])
00413ef8        uint16_t* index_0_cursor = &index_scratch[index_count]
00413efb        uint16_t* index_5_cursor = &index_scratch[index_count + 5]
00413f03        uint16_t* index_2_cursor = &index_scratch[index_count + 2]
00413f09        int32_t index_count_base = object
00413f0d        uint16_t* index_4_cursor = &index_scratch[index_count + 4]
00413f19        uint16_t* index_3_cursor = &index_scratch[index_count_base + 3]
00413f1d        uint16_t* index_1_cursor = &index_scratch[index_count_base + 1]
00414062        bool cond:3_1
00413f21        struct ObjectFaceQuad* facequads = object_1->facequads
00413f28        struct ObjectFaceQuad* face_for_vertex_0 = face_byte_offset + facequads
00413f2c        int32_t vertex_index_2 = 0
00413f31        vertex_index_2.w = face_for_vertex_0->vertex_0
00413f3d        *index_0_cursor = get_or_append_object_texture_group_vertex(object_1, vertex_index_2, face_for_vertex_0->uv[0].u, *(&facequads->uv[0].v + face_byte_offset))
00413f43        struct ObjectFaceQuad* face_for_vertex_1 = object_1->facequads + face_byte_offset
00413f4c        int32_t vertex_index = 0
00413f4e        vertex_index.w = face_for_vertex_1->vertex_1
00413f5e        *index_1_cursor = get_or_append_object_texture_group_vertex(object_1, vertex_index, face_for_vertex_1->uv[1].u, face_for_vertex_1->uv[1].v)
00413f64        struct ObjectFaceQuad* face_for_vertex_2 = object_1->facequads + face_byte_offset
00413f6d        int32_t vertex_index_1 = 0
00413f6f        vertex_index_1.w = face_for_vertex_2->vertex_2
00413f7b        *index_2_cursor = get_or_append_object_texture_group_vertex(object_1, vertex_index_1, face_for_vertex_2->uv[2].u, face_for_vertex_2->uv[2].v)
00413f89        int32_t next_primitive_count
00413f89        if ((*(face_byte_offset + object_1->facequads) & 0x80) != 0)
00414016        object = &object->_pad_00[3]
00414021        index_0_cursor = &index_0_cursor[3]
00414023        index_1_cursor = &index_1_cursor[3]
0041402d        index_2_cursor = &index_2_cursor[3]
0041402f        index_3_cursor = &index_3_cursor[3]
0041403f        index_4_cursor = &index_4_cursor[3]
00414043        index_5_cursor = &index_5_cursor[3]
00414047        next_primitive_count = primitive_count + 1
00413f92        *index_3_cursor = *index_0_cursor
00413f9d        *index_4_cursor = *index_2_cursor
00413fa0        struct ObjectFaceQuad* facequads_1 = object_1->facequads
00413fa7        struct ObjectFaceQuad* face_for_vertex_3 = face_byte_offset + facequads_1
00413fab        int32_t vertex_index_3 = 0
00413fb0        vertex_index_3.w = face_for_vertex_3->vertex_3
00413fc7        *index_5_cursor = get_or_append_object_texture_group_vertex(object_1, vertex_index_3, face_for_vertex_3->uv[3].u, *(&facequads_1->uv[3].v + face_byte_offset))
00413fd1        object = &object->_pad_00[6]
00413fdc        index_0_cursor = &index_0_cursor[6]
00413fde        index_1_cursor = &index_1_cursor[6]
00413fe8        index_2_cursor = &index_2_cursor[6]
00413fea        index_3_cursor = &index_3_cursor[6]
00413ffa        index_4_cursor = &index_4_cursor[6]
00413ffe        index_5_cursor = &index_5_cursor[6]
00414002        next_primitive_count = primitive_count + 2
0041404f        primitive_count = next_primitive_count
00414058        face_byte_offset += 0x30
0041405b        cond:3_1 = face_index + 1 s< object_1->texture_group_ends[current_group_index]
0041405e        face_index += 1
00414062        do while (cond:3_1)
00414068        index_count = object
0041406c        group_index = current_group_index
00414078        object_1->group_primitive_counts[group_index] = primitive_count
0041407e        group_index += 1
00414081        current_group_index = group_index
00414085        if (group_index s>= object_1->texture_group_count)
00414085        break
00413ebb        group_face_index = face_index
00414097        object_1->grouped_vertex_count = g_object_grouped_vertex_cursor
004140b4        object_1->render_buffers = create_vertex_buffer(&g_direct3d_renderer, g_object_grouped_vertex_cursor, 0x142)
004140ba        struct ObjectIndexBuffer* allocated_index_buffer = create_index_buffer(&g_direct3d_renderer.index_buffer_factory, index_count)
004140bf        struct ObjectRenderBuffers* render_buffers = object_1->render_buffers
004140ca        object_1->index_buffer = allocated_index_buffer
004140d0        struct ObjectVertexBuffer* locked_vertex_buffer = render_buffers->vertex_buffer
004140e5        struct ObjectRenderVertex* locked_vertices
004140e5        locked_vertex_buffer->vtbl->Lock(locked_vertex_buffer, 0, g_object_grouped_vertex_cursor * 0x18, &locked_vertices, 0)
004140ed        int32_t upload_index = 0
004140f1        if (g_object_grouped_vertex_cursor s> 0)
004140f3        int32_t locked_vertex_byte_offset = 0
004140f5        int32_t grouped_vertex_byte_offset = 0
00414105        *(&locked_vertices->diffuse + locked_vertex_byte_offset) = *(&g_object_grouped_vertex_scratch->diffuse + grouped_vertex_byte_offset)
00414113        struct ObjectUv* grouped_vertex_uv = &g_object_grouped_vertex_scratch->u + grouped_vertex_byte_offset
00414119        *(&locked_vertices->u + locked_vertex_byte_offset) = grouped_vertex_uv->u
00414124        *(&locked_vertices->v + locked_vertex_byte_offset) = grouped_vertex_uv->v
00414132        struct Vec3* grouped_vertex_position = g_object_grouped_vertex_scratch + grouped_vertex_byte_offset
00414134        struct ObjectRenderVertex* locked_vertex = locked_vertices + locked_vertex_byte_offset
00414136        upload_index += 1
00414139        grouped_vertex_byte_offset += 0x1c
0041413c        locked_vertex->x = grouped_vertex_position->x
0041413e        locked_vertex_byte_offset += 0x18
00414144        locked_vertex->y = grouped_vertex_position->y
0041414a        locked_vertex->z = grouped_vertex_position->z
00414155        do while (upload_index s< g_object_grouped_vertex_cursor)
00414157        index_count = object
00414163        struct ObjectVertexBuffer* unlock_vertex_buffer = object_1->render_buffers->vertex_buffer
00414169        unlock_vertex_buffer->vtbl->Unlock(unlock_vertex_buffer)
00414172        int32_t index_byte_count = index_count * 2
00414177        struct ObjectIndexBufferResource* locked_index_buffer_resource = object_1->index_buffer->buffer
00414183        uint16_t* locked_indices
00414183        locked_index_buffer_resource->vtbl->Lock(locked_index_buffer_resource, 0, index_byte_count, &locked_indices, 0)
00414195        int32_t esi_10
00414195        int32_t edi_6
00414195        edi_6, esi_10 = __builtin_memcpy(locked_indices, index_scratch, index_byte_count & 0xfffffffc)
0041419c        __builtin_memcpy(edi_6, esi_10, index_byte_count & 3)
004141a4        struct ObjectIndexBufferResource* unlock_index_buffer_resource = object_1->index_buffer->buffer
004141a9        unlock_index_buffer_resource->vtbl->Unlock(unlock_index_buffer_resource)
004141b3        if (((object_1->flags).w:1.b & 0x40) != 0)
004141c0        object_1->toon_index_buffer = create_index_buffer(&g_direct3d_renderer.index_buffer_factory, index_count)
004141cc        return
