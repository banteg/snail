/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_supertramp_mesh @ 0x424ad0 */

00424ae7        set_bod_object(&self->fringe_mesh_bod, add_object_to_list(&g_object_list))
00424aec        struct Object* generated_mesh = self->fringe_mesh_bod.object
00424af2        enum ObjectFlag flags = generated_mesh->flags
00424af5        generated_mesh->blend_mode = 5
00424b02        generated_mesh->flags = flags | OBJECT_FLAG_DISABLE_CULLING
00424b12        request_object_vertices(generated_mesh, (self->segment_count << 2) + 6)
00424b21        request_object_facequads(generated_mesh, self->segment_count * 2 + 1)
00424b29        struct Vec3* generated_vertices = generated_mesh->vertices
00424b2c        struct ObjectFaceQuad* generated_facequads = generated_mesh->facequads
00424b2f        int32_t i = 0
00424b33        struct Vec3* generated_vertices_1 = generated_vertices
00424b37        if (self->segment_count s>= 0)
00424b3d        struct FringeVertexRowCursorView* row_cursor = generated_vertices + 0x14
00424b54        int32_t* edx_2 = &self->bod.object->vertices[(self->width_cells + 1) * i + 1]
00424b59        row_cursor->outer_a.x = *edx_2
00424b5e        row_cursor->outer_a.y = edx_2[1]
00424b64        row_cursor->outer_a.z = edx_2[2]
00424b7a        int32_t* eax_16 = &self->bod.object->vertices[(self->width_cells + 1) * i]
00424b7f        row_cursor->x = *eax_16
00424b84        row_cursor->y = eax_16[1]
00424b8a        row_cursor->z = eax_16[2]
00424bc2        struct Vec3 vector = struct Vec3 {
    .x = fconvert.s(fconvert.t(row_cursor->x) - fconvert.t(row_cursor->outer_a.x))
    .y = fconvert.s(fconvert.t(row_cursor->y) - fconvert.t(row_cursor->outer_a.y))
    .z = fconvert.s(fconvert.t(row_cursor->z) - fconvert.t(row_cursor->outer_a.z))
}
00424bc6        normalize_vector(&vector)
00424c24        row_cursor->outer_a = struct Vec3 {
    .x = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t(row_cursor->x))
    .y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t(row_cursor->y))
    .z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t(row_cursor->z))
}
00424c27        uint32_t width_cells = self->width_cells
00424c3b        int32_t* ecx_10 = &self->bod.object->vertices[(width_cells + 1) * i + width_cells] - 0xc
00424c41        row_cursor->outer_b.x = *ecx_10
00424c46        row_cursor->outer_b.y = ecx_10[1]
00424c4c        row_cursor->outer_b.z = ecx_10[2]
00424c4f        uint32_t width_cells_1 = self->width_cells
00424c66        int32_t* eax_31 = &self->bod.object->vertices[(width_cells_1 + 1) * i + width_cells_1]
00424c6b        row_cursor->inner_b.x = *eax_31
00424c70        row_cursor->inner_b.y = eax_31[1]
00424c76        row_cursor->inner_b.z = eax_31[2]
00424caf        vector = struct Vec3 {
    .x = fconvert.s(fconvert.t(row_cursor->inner_b.x) - fconvert.t(row_cursor->outer_b.x))
    .y = fconvert.s(fconvert.t(row_cursor->inner_b.y) - fconvert.t(row_cursor->outer_b.y))
    .z = fconvert.s(fconvert.t(row_cursor->inner_b.z) - fconvert.t(row_cursor->outer_b.z))
}
00424cb3        normalize_vector(&vector)
00424cce        i += 1
00424ccf        row_cursor = &row_cursor[1]
00424cf6        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t(row_cursor->__offset(0xfffffffffffffff8).d))
00424cfe        long double x87_r7_30 = fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t(row_cursor->outer_a.x:-4.d)
00424d05        row_cursor->__offset(0xffffffffffffffe8).d = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t(row_cursor->__offset(0xfffffffffffffff4).d))
00424d08        row_cursor->__offset(0xffffffffffffffec).d = var_20_1
00424d13        row_cursor->__offset(0xfffffffffffffff0).d = fconvert.s(x87_r7_30)
00424d1b        do while (i s<= self->segment_count)
00424d21        generated_vertices = generated_vertices_1
00424d28        int32_t ebp = 0
00424d2c        int32_t var_5c = 0
00424d30        if (self->segment_count s> 0)
00424d36        struct FringeFaceQuadPairCursorView* face_pair_cursor = &generated_facequads->vertex_0
00424d59        while (true)
00424d59        face_pair_cursor->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424d5c        int16_t ebp_1 = (ebp << 2).w
00424d5f        face_pair_cursor->vertex_0 = (ebp << 2).w + 4
00424d6c        face_pair_cursor->vertex_1 = ebp_1 + 5
00424d70        face_pair_cursor->vertex_2 = ebp_1 + 1
00424d79        face_pair_cursor->vertex_3 = ebp_1
00424d82        face_pair_cursor->uv[3].u = 0x3f000000
00424d85        face_pair_cursor->uv[3].v = 0x3f800000
00424d88        face_pair_cursor->uv[0].u = 0x3f000000
00424d8b        face_pair_cursor->uv[0].v = 0x3f800000
00424d90        face_pair_cursor->uv[1].u = 0x3f000000
00424d93        face_pair_cursor->uv[1].v = 0
00424d96        face_pair_cursor->uv[2].u = 0x3f000000
00424d9a        face_pair_cursor->uv[2].v = 0
00424da9        face_pair_cursor->second_face.texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424db2        face_pair_cursor->second_face.vertex_0 = ebp_1 + 7
00424db9        face_pair_cursor->second_face.vertex_1 = ebp_1 + 6
00424dc0        face_pair_cursor->second_face.vertex_2 = ebp_1 + 2
00424dc9        face_pair_cursor->second_face.vertex_3 = ebp_1 + 3
00424dcf        face_pair_cursor->second_face.uv[3].u = 0x3f000000
00424dd2        face_pair_cursor->second_face.uv[3].v = 0
00424dd5        face_pair_cursor->second_face.uv[0].u = 0x3f000000
00424dd8        face_pair_cursor->second_face.uv[0].v = 0
00424de0        face_pair_cursor->second_face.uv[1].u = 0x3f000000
00424de3        face_pair_cursor->second_face.uv[1].v = 0x3f800000
00424de6        face_pair_cursor->second_face.uv[2].u = 0x3f000000
00424ded        face_pair_cursor->second_face.uv[2].v = 0x3f800000
00424df4        face_pair_cursor = &face_pair_cursor[1]
00424df7        bool cond:2_1 = var_5c + 1 s< self->segment_count
00424df9        var_5c += 1
00424dfd        if (not(cond:2_1))
00424dfd        break
00424d3b        ebp = var_5c
00424e03        generated_vertices = generated_vertices_1
00424e07        uint32_t segment_count_1 = self->segment_count
00424e14        struct Vec3* final_row_first_edge = &generated_vertices[segment_count_1 * 4]
00424e83        *(((segment_count_1 * 3 + 3) << 4) + generated_vertices) = struct Vec3 {
    .x = fconvert.s((fconvert.t(final_row_first_edge->x) - fconvert.t(final_row_first_edge->__offset(0xffffffffffffffd0).d)) * fconvert.t(0.400000006f) + fconvert.t(final_row_first_edge->x))
    .y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(final_row_first_edge->y) - fconvert.t(final_row_first_edge->__offset(0xffffffffffffffd4).d))) * fconvert.t(0.400000006f))) + fconvert.t(final_row_first_edge->y))
    .z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(final_row_first_edge->z) - fconvert.t(final_row_first_edge->__offset(0xffffffffffffffd8).d))) * fconvert.t(0.400000006f))) + fconvert.t(final_row_first_edge->z))
}
00424e8f        struct Vec3* final_row_second_edge = &generated_vertices[self->segment_count * 4]
00424ee2        float var_20_3 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(final_row_second_edge->__offset(0x1c).d) - fconvert.t(final_row_second_edge->__offset(0xffffffffffffffec).d))) * fconvert.t(0.400000006f))) + fconvert.t(final_row_second_edge->__offset(0x1c).d))
00424eea        long double x87_r7_46 = fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(final_row_second_edge->__offset(0x20).d) - fconvert.t(final_row_second_edge->__offset(0xfffffffffffffff0).d))) * fconvert.t(0.400000006f))) + fconvert.t(final_row_second_edge->__offset(0x20).d)
00424ef1        final_row_second_edge->__offset(0x3c).d = fconvert.s((fconvert.t(final_row_second_edge->__offset(0x18).d) - fconvert.t(final_row_second_edge->__offset(0xffffffffffffffe8).d)) * fconvert.t(0.400000006f) + fconvert.t(final_row_second_edge->__offset(0x18).d))
00424ef3        final_row_second_edge->__offset(0x40).d = var_20_3
00424efe        final_row_second_edge->__offset(0x44).d = fconvert.s(x87_r7_46)
00424f01        uint32_t segment_count = self->segment_count
00424f0e        struct Vec3* first_cap_vertex_copy = ((segment_count * 3 + 3) << 4) + generated_vertices
00424f15        struct Vec3* final_row_copy = &generated_vertices[segment_count * 4]
00424f17        final_row_copy->x = first_cap_vertex_copy->x
00424f1c        final_row_copy->y = first_cap_vertex_copy->y
00424f24        final_row_copy->z = first_cap_vertex_copy->z
00424f32        struct Vec3* final_generated_row = &generated_vertices[self->segment_count * 4]
00424f3c        final_generated_row->__offset(0x18).d = final_generated_row->__offset(0x3c).d
00424f46        final_generated_row->__offset(0x1c).d = final_generated_row->__offset(0x40).d
00424f4c        final_generated_row->__offset(0x20).d = final_generated_row->__offset(0x44).d
00424f54        struct TextureRef* eax_56 = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424f5f        uint32_t ecx_33 = self->segment_count * 0x60
00424f62        *(&generated_facequads->texture_ref + ecx_33) = eax_56
00424f78        generated_facequads[self->segment_count * 2].vertex_0 = (self->segment_count.w << 2) + 1
00424f80        ecx_33.w = self->segment_count.w
00424f87        ecx_33.w <<= 2
00424f8e        int32_t ecx_34 = ecx_33 + 3
00424f91        generated_facequads[self->segment_count * 2].vertex_1 = ecx_34.w
00424f99        ecx_34.w = self->segment_count.w
00424fa0        ecx_34.w <<= 2
00424fa7        int32_t ecx_35 = ecx_34 + 5
00424faa        generated_facequads[self->segment_count * 2].vertex_2 = ecx_35.w
00424fb2        ecx_35.w = self->segment_count.w
00424fb9        ecx_35.w += 1
00424fc1        generated_facequads[self->segment_count * 2].vertex_3 = (ecx_35 << 2).w
00424fd6        generated_facequads[self->segment_count * 2].uv[0].u = 0x3f000000
00424fe3        generated_facequads[self->segment_count * 2].uv[0].v = 0
00424ff0        generated_facequads[self->segment_count * 2].uv[1].u = 0x3f000000
00424ffd        generated_facequads[self->segment_count * 2].uv[1].v = 0
0042500a        generated_facequads[self->segment_count * 2].uv[2].u = 0x3f000000
0042501c        generated_facequads[self->segment_count * 2].uv[2].v = 0x3f800000
0042502a        generated_facequads[self->segment_count * 2].uv[3].u = 0x3f000000
00425039        generated_facequads[self->segment_count * 2].uv[3].v = 0x3f800000
00425041        return
