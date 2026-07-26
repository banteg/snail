/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_object_toon @ 0x4123e0 */

004123f4        if (((object->flags).w:1.b & 0x40) == 0)
004123f4        return
00412408        int32_t __saved_ebp_7
00412408        int32_t __saved_ebp_1 = __saved_ebp_7
00412421        int32_t __saved_ebp_8 = __saved_ebp_7
0041242e        struct TransformMatrix projection
0041242e        build_perspective_projection_matrix(&projection, g_render_projection_param_a, g_render_projection_param_b, fconvert.s(fconvert.t(g_render_projection_near_z) + fconvert.t(0.00400000019f)), fconvert.s(fconvert.t(g_render_projection_far_z) + fconvert.t(30f)))
00412433        struct Direct3DDevice8* device = g_direct3d_renderer.device
00412442        device->vtbl->SetTransform(device, 3, &projection)
00412448        struct TransformMatrix* render_camera_source_matrix_1 = g_render_camera_source_matrix
0041245e        float var_ac_1 = fconvert.s(fconvert.t(render_camera_source_matrix_1->position.x) - fconvert.t(matrix->position.x))
0041246f        long double x87_r7_10 = fconvert.t(render_camera_source_matrix_1->position.z) - fconvert.t(matrix->position.z)
0041247a        struct Vec3 view_vector
0041247a        view_vector.y = fconvert.s(fconvert.t(render_camera_source_matrix_1->position.y) - fconvert.t(matrix->position.y))
00412483        struct TransformMatrix var_40
00412483        __builtin_memcpy(&var_40, matrix, 0x40)
00412485        float var_a4_1 = fconvert.s(x87_r7_10)
00412491        view_vector.x = var_ac_1
00412495        view_vector.z = var_a4_1
00412499        invert_matrix_in_place(&var_40)
004124a7        rotate_vector_by_matrix(&view_vector, &var_40)
004124b0        vector_magnitude(&view_vector)
004124bb        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
004124ca        device_1->vtbl->SetIndices(device_1, object->toon_index_buffer->buffer, 0)
004124d6        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
004124e6        device_2->vtbl->SetStreamSource(device_2, 0, object->render_buffers->vertex_buffer, 0x18)
004124ef        int32_t edge_index = 0
004124f9        if (object->edge_count s> 0)
00412500        int32_t edge_byte_offset = 0
00412667        bool cond:0_1
00412508        int32_t emitted_index_count = 0
0041250f        struct ObjectIndexBufferResource* toon_index_buffer = object->toon_index_buffer->buffer
0041251c        uint16_t* toon_indices
0041251c        toon_index_buffer->vtbl->Lock(toon_index_buffer, 0, object->vertex_count << 1, &toon_indices, 0)
00412522        struct ObjectToonEdge* edge = object->edges + edge_byte_offset
00412527        if ((edge->flags.b & 1) == 0)
00412549        int32_t normal_a_index = edge->normal_a
0041254c        struct Vec3* facequad_normals = object->facequad_normals
00412559        int32_t normal_b_1 = edge->normal_b
00412562        int32_t eax_8 = edge->vertex_a * 3
00412568        struct Vec3* vertices = object->vertices
00412573        struct Vec3* vertex = vertices + (eax_8 << 2)
004125a4        struct Vec3 edge_delta = struct Vec3 {
    .x = fconvert.s(fconvert.t(view_vector.x) - fconvert.t(*(vertices + (eax_8 << 2))))
    .y = fconvert.s(fconvert.t(view_vector.y) - fconvert.t(vertex->y))
    .z = fconvert.s(fconvert.t(view_vector.z) - fconvert.t(vertex->z))
}
004125ad        float side_b = fconvert.s(dot_vector(&edge_delta, &facequad_normals[normal_b_1]))
004125bb        long double x87_r7_21 = dot_vector(&edge_delta, &facequad_normals[normal_a_index]) * fconvert.t(side_b)
004125bf        long double temp0_1 = fconvert.t(0.00999999978f)
004125bf        x87_r7_21 - temp0_1
004125ca        if ((((x87_r7_21 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp0_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004125d8        *toon_indices = *(&object->edges->vertex_a + edge_byte_offset)
004125e7        toon_indices[1] = *(&object->edges->vertex_b + edge_byte_offset)
004125eb        emitted_index_count = 2
00412531        *toon_indices = edge->vertex_a.w
00412540        toon_indices[1] = *(&object->edges->vertex_b + edge_byte_offset)
004125eb        emitted_index_count = 2
004125f6        struct ObjectIndexBufferResource* toon_index_buffer_for_unlock = object->toon_index_buffer->buffer
004125fb        toon_index_buffer_for_unlock->vtbl->Unlock(toon_index_buffer_for_unlock)
00412600        if (emitted_index_count s> 0)
0041260f        bind_texture_ref(get_sprite_texture(&g_sprite_manager, 0x5d))
00412616        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
0041261c        int32_t eax_17
0041261c        int32_t edx_15
0041261c        edx_15:eax_17 = sx.q(emitted_index_count)
0041262c        int32_t primitive_count = (eax_17 - edx_15) s>> 1
00412637        device_4->vtbl->DrawIndexedPrimitive(device_4, 2, 0, object->grouped_vertex_count, 0, primitive_count)
0041264a        int32_t eax_21 = g_draw_primitive_call_count + 1
0041264b        g_render_triangle_count += primitive_count
00412651        g_draw_primitive_call_count = eax_21
0041265e        edge_byte_offset += 0x24
00412661        cond:0_1 = edge_index + 1 s< object->edge_count
00412663        edge_index += 1
00412667        do while (cond:0_1)
0041268d        build_perspective_projection_matrix(&projection, g_render_projection_param_a, g_render_projection_param_b, g_render_projection_near_z, g_render_projection_far_z)
00412692        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
004126a1        device_3->vtbl->SetTransform(device_3, 3, &projection)
004126b0        return
