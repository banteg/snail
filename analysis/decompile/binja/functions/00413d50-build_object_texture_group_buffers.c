/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_object_texture_group_buffers @ 0x413d50 */

00413d54        struct Object* object_1 = object
00413d5d        int32_t edi = 0
00413d61        if (object_1->vertex_count == 0)
00413d63        object_1->group_index_starts = nullptr
00413d69        object_1->group_texture_refs = nullptr
00413d6f        object_1->group_primitive_counts = nullptr
00413d75        object_1->render_buffers = nullptr
00413d7b        object_1->index_buffer = nullptr
00413d87        return
00413d96        object_1->flags |= OBJECT_FLAG_RENDER_BUFFERS_READY
00413da0        int32_t* eax_5 = allocate_tracked_memory(object_1->texture_group_count << 2, "DX TextureGroups")
00413dad        int32_t size = object_1->texture_group_count << 2
00413db1        object_1->group_index_starts = eax_5
00413db7        struct TextureRef** eax_6 = allocate_tracked_memory(size, "DX TextureGroupsTexture Ref")
00413dc4        int32_t size_1 = object_1->texture_group_count << 2
00413dc8        object_1->group_texture_refs = eax_6
00413dd6        object_1->group_primitive_counts = allocate_tracked_memory(size_1, "DX TextureGroupsTexture Primcount")
00413de1        g_object_grouped_vertex_scratch = get_archive_data_base()
00413de6        void* eax_9 = get_archive_data_end()
00413def        g_object_grouped_vertex_cursor = 0
00413df8        int32_t ecx_1 = 0
00413dfa        int32_t index_count = 0
00413dfc        int32_t var_14 = 0
00413e00        bool cond:0 = (object_1->flags.b & 4) == 0
00413e02        __builtin_memset(&object, 0, 4)
00413e06        if (not(cond:0))
00413e0f        int32_t vertex_index_4 = 0
00413e13        if (object_1->vertex_count s> 0)
00413e1c        int32_t var_c_1 = 0
00413e22        if (object_1->facequad_count s> 0)
00413e94        bool cond:4_1
00413e27        int32_t ecx_2 = 0
00413e29        char* eax_14 = object_1->facequads + edi
00413e2b        ecx_2.w = *(eax_14 + 2)
00413e31        if (ecx_2 != vertex_index_4)
00413e3c        int32_t ecx_3 = 0
00413e3e        ecx_3.w = *(eax_14 + 4)
00413e44        if (ecx_3 != vertex_index_4)
00413e4f        int32_t ecx_4 = 0
00413e51        ecx_4.w = *(eax_14 + 6)
00413e57        if (ecx_4 == vertex_index_4)
00413e7b        get_or_append_object_texture_group_vertex(object_1, vertex_index_4, *(eax_14 + 0x20), *(eax_14 + 0x24))
00413e65        if ((*eax_14 & 0x80) == 0)
00413e67        int32_t ecx_5 = 0
00413e69        ecx_5.w = *(eax_14 + 8)
00413e6f        if (ecx_5 == vertex_index_4)
00413e7b        get_or_append_object_texture_group_vertex(object_1, vertex_index_4, *(eax_14 + 0x28), *(eax_14 + 0x2c))
00413e7b        get_or_append_object_texture_group_vertex(object_1, vertex_index_4, *(eax_14 + 0x18), *(eax_14 + 0x1c))
00413e7b        get_or_append_object_texture_group_vertex(object_1, vertex_index_4, *(eax_14 + 0x10), *(eax_14 + 0x14))
00413e8b        edi += 0x30
00413e8e        cond:4_1 = var_c_1 + 1 s< object_1->facequad_count
00413e90        var_c_1 += 1
00413e94        do while (cond:4_1)
00413e96        ecx_1 = 0
00413e9a        edi = 0
00413e9f        vertex_index_4 += 1
00413ea2        do while (vertex_index_4 s< object_1->vertex_count)
00413eab        int32_t eax_19 = 0
00413eaf        int32_t var_c_2 = 0
00413eb3        if (object_1->texture_group_count s> 0)
00413eca        while (true)
00413eca        int32_t var_1c_1 = 0
00413ed1        int32_t edi_2 = ecx_1 * 0x30
00413ed8        object_1->group_texture_refs[eax_19] = *(&object_1->facequads->texture_ref + edi_2)
00413ee1        object_1->group_index_starts[eax_19] = index_count
00413eea        if (ecx_1 s< object_1->texture_group_ends[eax_19])
00413ef8        int16_t* esi_2 = eax_9 + (index_count << 1)
00413efb        int16_t* var_18_1 = eax_9 + (index_count << 1) + 0xa
00413f03        int16_t* ebp = eax_9 + (index_count << 1) + 4
00413f09        struct Object* object_2 = object
00413f0d        int16_t* var_20_1 = eax_9 + (index_count << 1) + 8
00413f19        int16_t* var_24_1 = eax_9 + (object_2 << 1) + 6
00413f1d        int16_t* var_28_1 = eax_9 + (object_2 << 1) + 2
00414062        bool cond:3_1
00413f21        struct ObjectFaceQuad* facequads = object_1->facequads
00413f28        void* eax_22 = edi_2 + facequads
00413f2c        int32_t vertex_index_2 = 0
00413f31        vertex_index_2.w = *(eax_22 + 2)
00413f3d        *esi_2 = get_or_append_object_texture_group_vertex(object_1, vertex_index_2, *(eax_22 + 0x10), *(&facequads->uv[0].v + edi_2))
00413f43        void* eax_25 = object_1->facequads + edi_2
00413f4c        int32_t vertex_index = 0
00413f4e        vertex_index.w = *(eax_25 + 4)
00413f5e        *var_28_1 = get_or_append_object_texture_group_vertex(object_1, vertex_index, *(eax_25 + 0x18), *(eax_25 + 0x1c))
00413f64        void* eax_28 = object_1->facequads + edi_2
00413f6d        int32_t vertex_index_1 = 0
00413f6f        vertex_index_1.w = *(eax_28 + 6)
00413f7b        *ebp = get_or_append_object_texture_group_vertex(object_1, vertex_index_1, *(eax_28 + 0x20), *(eax_28 + 0x24))
00413f89        int32_t eax_37
00413f89        if ((*(edi_2 + object_1->facequads) & 0x80) != 0)
00414016        object = &object->_pad_00[3]
00414021        esi_2 = &esi_2[3]
00414023        var_28_1 = &var_28_1[3]
0041402d        ebp = &ebp[3]
0041402f        var_24_1 = &var_24_1[3]
0041403f        var_20_1 = &var_20_1[3]
00414043        var_18_1 = &var_18_1[3]
00414047        eax_37 = var_1c_1 + 1
00413f92        *var_24_1 = *esi_2
00413f9d        *var_20_1 = *ebp
00413fa0        struct ObjectFaceQuad* facequads_1 = object_1->facequads
00413fa7        void* eax_32 = edi_2 + facequads_1
00413fab        int32_t vertex_index_3 = 0
00413fb0        vertex_index_3.w = *(eax_32 + 8)
00413fc7        *var_18_1 = get_or_append_object_texture_group_vertex(object_1, vertex_index_3, *(eax_32 + 0x28), *(&facequads_1->uv[3].v + edi_2))
00413fd1        object = &object->_pad_00[6]
00413fdc        esi_2 = &esi_2[6]
00413fde        var_28_1 = &var_28_1[6]
00413fe8        ebp = &ebp[6]
00413fea        var_24_1 = &var_24_1[6]
00413ffa        var_20_1 = &var_20_1[6]
00413ffe        var_18_1 = &var_18_1[6]
00414002        eax_37 = var_1c_1 + 2
0041404f        var_1c_1 = eax_37
00414058        edi_2 += 0x30
0041405b        cond:3_1 = var_14 + 1 s< object_1->texture_group_ends[var_c_2]
0041405e        var_14 += 1
00414062        do while (cond:3_1)
00414068        index_count = object
0041406c        eax_19 = var_c_2
00414078        object_1->group_primitive_counts[eax_19] = var_1c_1
0041407e        eax_19 += 1
00414081        var_c_2 = eax_19
00414085        if (eax_19 s>= object_1->texture_group_count)
00414085        break
00413ebb        ecx_1 = var_14
00414097        object_1->grouped_vertex_count = g_object_grouped_vertex_cursor
004140b4        object_1->render_buffers = create_object_vertex_buffer_resource(&g_direct3d_renderer, g_object_grouped_vertex_cursor, 0x142)
004140ba        struct ObjectIndexBuffer* eax_45 = create_object_index_buffer_resource(&g_object_index_buffer_factory, index_count)
004140bf        struct ObjectRenderBuffers* render_buffers = object_1->render_buffers
004140ca        object_1->index_buffer = eax_45
004140d0        struct ObjectVertexBuffer* vertex_buffer = render_buffers->vertex_buffer
004140e5        void* data
004140e5        vertex_buffer->vtbl->Lock(vertex_buffer, 0, g_object_grouped_vertex_cursor * 0x18, &data, 0)
004140ed        int32_t i = 0
004140f1        if (g_object_grouped_vertex_cursor s> 0)
004140f3        int32_t eax_47 = 0
004140f5        int32_t ecx_25 = 0
00414105        *(eax_47 + data + 0xc) = *(&g_object_grouped_vertex_scratch->diffuse + ecx_25)
00414113        int32_t* esi_6 = &g_object_grouped_vertex_scratch->u + ecx_25
00414119        *(eax_47 + data + 0x10) = *esi_6
00414124        *(eax_47 + data + 0x14) = esi_6[1]
00414132        int32_t* esi_9 = g_object_grouped_vertex_scratch + ecx_25
00414134        int32_t* edi_7 = data + eax_47
00414136        i += 1
00414139        ecx_25 += 0x1c
0041413c        *edi_7 = *esi_9
0041413e        eax_47 += 0x18
00414144        edi_7[1] = esi_9[1]
0041414a        edi_7[2] = esi_9[2]
00414155        do while (i s< g_object_grouped_vertex_cursor)
00414157        index_count = object
00414163        struct ObjectVertexBuffer* vertex_buffer_1 = object_1->render_buffers->vertex_buffer
00414169        vertex_buffer_1->vtbl->Unlock(vertex_buffer_1)
00414172        int32_t size_2 = index_count * 2
00414177        struct ObjectIndexBufferResource* buffer = object_1->index_buffer->buffer
00414183        int32_t data_1
00414183        buffer->vtbl->Lock(buffer, 0, size_2, &data_1, 0)
00414195        int32_t esi_13
00414195        int32_t edi_9
00414195        edi_9, esi_13 = __builtin_memcpy(data_1, eax_9, size_2 & 0xfffffffc)
0041419c        __builtin_memcpy(edi_9, esi_13, size_2 & 3)
004141a4        struct ObjectIndexBufferResource* buffer_1 = object_1->index_buffer->buffer
004141a9        buffer_1->vtbl->Unlock(buffer_1)
004141b3        if (((object_1->flags).w:1.b & 0x40) != 0)
004141c0        object_1->toon_index_buffer = create_object_index_buffer_resource(&g_object_index_buffer_factory, index_count)
004141cc        return
