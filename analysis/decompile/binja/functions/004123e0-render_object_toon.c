/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_object_toon @ 0x4123e0 */

004123ee        enum ObjectFlag flags = object->flags
004123f4        if ((flags:1.b & 0x40) == 0)
004126b0        return flags
00412408        int32_t __saved_ebp_7
00412408        int32_t __saved_ebp_1 = __saved_ebp_7
00412421        int32_t __saved_ebp_8 = __saved_ebp_7
0041242e        void matrix_1
0041242e        build_perspective_projection_matrix(&matrix_1, data_5031d4, data_50316c, fconvert.s(fconvert.t(data_5031cc) + fconvert.t(0.00400000019f)), fconvert.s(fconvert.t(data_5031d0) + fconvert.t(30f)))
00412433        struct Direct3DDevice8* device = g_direct3d_renderer.device
00412442        device->vtbl->SetTransform(device, 3, &matrix_1)
00412448        void* eax_1 = data_5031b8
0041245e        float var_ac_1 = fconvert.s(fconvert.t(*(eax_1 + 0x30)) - fconvert.t(matrix->position.x))
0041246f        long double x87_r7_10 = fconvert.t(*(eax_1 + 0x38)) - fconvert.t(matrix->position.z)
0041247a        struct Vec3 vector
0041247a        vector.y = fconvert.s(fconvert.t(*(eax_1 + 0x34)) - fconvert.t(matrix->position.y))
00412483        struct TransformMatrix var_40
00412483        __builtin_memcpy(&var_40, matrix, 0x40)
00412491        vector.x = var_ac_1
00412495        vector.z = fconvert.s(x87_r7_10)
00412499        invert_matrix_in_place(&var_40)
004124a7        rotate_vector_by_matrix(&vector, &var_40)
004124b0        vector_magnitude(&vector)
004124bb        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
004124ca        device_1->vtbl->SetIndices(device_1, object->toon_index_buffer->buffer, 0)
004124d6        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
004124e6        device_2->vtbl->SetStreamSource(device_2, 0, object->render_buffers->vertex_buffer, 0x18)
004124ef        int32_t var_a0_1 = 0
004124f9        if (object->edge_count s> 0)
00412500        int32_t ebp_1 = 0
00412667        bool cond:0_1
00412508        int32_t esi_2 = 0
0041250f        struct ObjectIndexBufferResource* buffer = object->toon_index_buffer->buffer
0041251c        void* data
0041251c        buffer->vtbl->Lock(buffer, 0, object->vertex_count << 1, &data, 0)
00412522        char* eax_6 = object->edges + ebp_1
00412527        if ((*eax_6 & 1) == 0)
00412549        int32_t edx_10 = *(eax_6 + 0xc)
0041254c        struct Vec3* facequad_normals = object->facequad_normals
00412562        int32_t eax_9 = *(eax_6 + 4) * 3
00412568        struct Vec3* vertices = object->vertices
00412573        void* eax_10 = vertices + (eax_9 << 2)
00412594        struct Vec3 vector_1
00412594        vector_1.x = fconvert.s(fconvert.t(vector.x) - fconvert.t(*(vertices + (eax_9 << 2))))
00412598        vector_1.y = fconvert.s(fconvert.t(vector.y) - fconvert.t(*(eax_10 + 4)))
004125a4        vector_1.z = fconvert.s(fconvert.t(vector.z) - fconvert.t(*(eax_10 + 8)))
004125ad        float var_90_1 = fconvert.s(dot_vector(&vector_1, &facequad_normals[*(eax_6 + 0x10)]))
004125bb        long double x87_r7_21 = dot_vector(&vector_1, &facequad_normals[edx_10]) * fconvert.t(var_90_1)
004125bf        long double temp0_1 = fconvert.t(0.00999999978f)
004125bf        x87_r7_21 - temp0_1
004125ca        if ((((x87_r7_21 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp0_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004125d8        *data = *(&object->edges->vertex_a + ebp_1)
004125e7        *(data + 2) = *(&object->edges->vertex_b + ebp_1)
004125eb        esi_2 = 2
00412531        *data = *(eax_6 + 4)
00412540        *(data + 2) = *(&object->edges->vertex_b + ebp_1)
004125eb        esi_2 = 2
004125f6        struct ObjectIndexBufferResource* buffer_1 = object->toon_index_buffer->buffer
004125fb        buffer_1->vtbl->Unlock(buffer_1)
00412600        if (esi_2 s> 0)
0041260f        bind_texture_ref(get_sprite_texture(&g_sprite_manager, 0x5d))
00412616        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
0041261c        int32_t eax_19
0041261c        int32_t edx_17
0041261c        edx_17:eax_19 = sx.q(esi_2)
0041262c        int32_t primitive_count = (eax_19 - edx_17) s>> 1
00412637        device_4->vtbl->DrawIndexedPrimitive(device_4, 2, 0, object->grouped_vertex_count, 0, primitive_count)
0041264a        int32_t eax_23 = g_draw_primitive_call_count + 1
0041264b        g_render_triangle_count += primitive_count
00412651        g_draw_primitive_call_count = eax_23
0041265e        ebp_1 += 0x24
00412661        cond:0_1 = var_a0_1 + 1 s< object->edge_count
00412663        var_a0_1 += 1
00412667        do while (cond:0_1)
0041268d        build_perspective_projection_matrix(&matrix_1, data_5031d4, data_50316c, data_5031cc, data_5031d0)
00412692        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
004126a1        return device_3->vtbl->SetTransform(device_3, 3, &matrix_1)
