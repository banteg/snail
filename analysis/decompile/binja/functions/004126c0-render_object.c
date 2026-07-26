/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_object @ 0x4126c0 */

004126cb        enum ObjectFlag flags = object->flags
004126e9        if ((flags & OBJECT_FLAG_RENDER_BUFFERS_READY) == 0 || (flags & OBJECT_FLAG_RENDER_DISABLED) != 0 || object->vertex_count == 0)
004126e9        return
004126f0        refresh_object_vertex_buffer(object)
004126f9        struct Direct3DDevice8* device = g_direct3d_renderer.device
0041270e        struct TransformMatrix world_matrix
0041270e        __builtin_memcpy(&world_matrix, matrix, 0x40)
00412719        device->vtbl->SetTransform(device, 0x100, &world_matrix)
00412726        int32_t cull_front
00412726        if ((object->flags & OBJECT_FLAG_DISABLE_CULLING) == 0)
0041272c        cull_front = 1
00412728        cull_front = 0
0041272e        set_cull_mode(cull_front)
00412739        int32_t texture_group_index = 0
0041273d        if (object->texture_group_count s> 0)
0041274b        uint8_t render_pass_filter = g_object_render_pass_filter
00412753        if (render_pass_filter != 0)
00412789        if (render_pass_filter != 1 || after_sprites != render_pass_filter || (object->group_texture_refs[texture_group_index]->flags & TEXTURE_REF_HAS_ALPHA) != 0)
00412795        label_412795:
00412795        struct TextureRef* group_texture_to_bind = object->group_texture_refs[texture_group_index]
0041279a        if (group_texture_to_bind != 0)
004127a4        struct TextureRef* texture_to_bind
004127a4        if ((object->flags.b & 8) == 0)
004127ac        texture_to_bind = group_texture_to_bind
004127a9        texture_to_bind = object->override_texture_ref
004127ad        bind_texture_ref(texture_to_bind)
004127ba        if ((object->flags.b & 0x80) == 0)
00412801        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
0041280f        device_3->vtbl->SetTextureStageState(device_3, 0, 0x18, 0)
004127ca        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
004127cf        g_object_texture_transform_matrix.basis_forward.x = texture_u
004127d5        struct TransformMatrix* matrix_1 = &g_object_texture_transform_matrix
004127da        int32_t state = 0x10
004127dd        g_object_texture_transform_matrix.basis_forward.y = fconvert.s(fconvert.t(1f) - fconvert.t(texture_v))
004127e5        device_1->vtbl->SetTransform(device_1, state, matrix_1)
004127eb        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
004127f9        device_2->vtbl->SetTextureStageState(device_2, 0, 0x18, 2)
0041282d        if (color->a == 0x3f800000 || (object->group_texture_refs[texture_group_index]->flags & TEXTURE_REF_HAS_ALPHA) == 0)
0041286f        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
0041287b        device_4->vtbl->SetRenderState(device_4, 0x1b, 0)
00412833        set_blend_mode(object->blend_mode)
00412838        enum ObjectFlag flags_1 = object->flags
00412840        if ((flags_1.b & 0x50) != 0)
00412842        flags_1.b &= 0xbf
00412849        object->flags = flags_1
00412856        float g = color->g
0041285c        float b = color->b
00412862        float a = color->a
00412865        set_object_color(object, color->r)
00412887        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00412897        device_5->vtbl->SetStreamSource(device_5, 0, object->render_buffers->vertex_buffer, 0x18)
0041289d        struct Direct3DDevice8* device_6 = g_direct3d_renderer.device
004128aa        device_6->vtbl->SetVertexShader(device_6, 0x142)
004128b6        struct Direct3DDevice8* device_7 = g_direct3d_renderer.device
004128c3        device_7->vtbl->SetIndices(device_7, object->index_buffer->buffer, 0)
004128cf        struct Direct3DDevice8* device_8 = g_direct3d_renderer.device
004128f0        device_8->vtbl->DrawIndexedPrimitive(device_8, 4, 0, object->grouped_vertex_count, object->group_index_starts[texture_group_index], object->group_primitive_counts[texture_group_index])
0041290c        render_pass_filter = g_object_render_pass_filter
00412912        int32_t eax_8 = g_draw_primitive_call_count + 1
00412913        g_render_triangle_count += object->group_primitive_counts[texture_group_index]
00412919        g_draw_primitive_call_count = eax_8
00412769        if (after_sprites != 1 || (object->group_texture_refs[texture_group_index]->flags & TEXTURE_REF_HAS_ALPHA) == 0)
00412758        goto label_412795
00412921        texture_group_index += 1
00412924        do while (texture_group_index s< object->texture_group_count)
00412930        render_object_toon(object, matrix)
0041293f        return
