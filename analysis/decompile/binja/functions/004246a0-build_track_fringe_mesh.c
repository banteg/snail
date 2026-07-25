/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_mesh @ 0x4246a0 */

004246b7        set_bod_object(&self->fringe_mesh_bod, add_object_to_list(&g_object_list))
004246cd        struct tColour out
004246cd        struct tColour* eax_1 = get_track_skirt_color(&g_game_base->subgame, &out)
004246da        struct Object* generated_mesh = self->fringe_mesh_bod.object
004246e0        self->fringe_mesh_bod.color.r = eax_1->r
004246e5        self->fringe_mesh_bod.color.g = eax_1->g
004246eb        self->fringe_mesh_bod.color.b = eax_1->b
004246f1        self->fringe_mesh_bod.color.a = eax_1->a
004246f7        enum ObjectFlag ebp_1 = generated_mesh->flags | OBJECT_FLAG_TINT_DIRTY | OBJECT_FLAG_DISABLE_CULLING
004246fd        generated_mesh->blend_mode = 5
00424704        generated_mesh->flags = ebp_1
00424714        request_object_vertices(generated_mesh, (self->segment_count << 2) + 4)
00424721        request_object_facequads(generated_mesh, self->segment_count << 1)
00424729        struct ObjectFaceQuad* facequads = generated_mesh->facequads
00424735        uint32_t var_68 = 0
0042473d        if (self->segment_count s>= 0)
00424743        struct FringeVertexRowCursorView* row_cursor = generated_mesh->vertices + 0x14
004249da        bool cond:2_1
0042474b        int32_t var_64_1
0042474b        uint32_t width_cells_1
0042474b        uint32_t width_cells
0042474b        uint32_t width_cells_2
0042474b        int32_t edx_2
0042474b        if (self->is_mirrored_x == 0)
00424767        width_cells = self->width_cells
0042476a        width_cells_2 = 0
0042476c        edx_2 = 1
00424771        width_cells_1 = width_cells
00424778        var_64_1 = width_cells - 1
0042474d        width_cells = self->width_cells
00424750        var_64_1 = 1
00424758        width_cells_2 = width_cells
0042475a        width_cells_1 = 0
00424762        edx_2 = width_cells - 1
0042477d        struct Vec3* generated_row = row_cursor - 0x14
00424790        int32_t* edx_4 = &self->bod.object->vertices[(width_cells + 1) * var_68 + edx_2]
00424797        generated_row->x = *edx_4
0042479c        generated_row->y = edx_4[1]
004247a5        generated_row->z = edx_4[2]
004247be        int32_t* eax_18 = &self->bod.object->vertices[(self->width_cells + 1) * var_68 + width_cells_2]
004247c3        row_cursor->x = *eax_18
004247c8        row_cursor->y = eax_18[1]
004247ce        row_cursor->z = eax_18[2]
00424805        struct Vec3 vector = struct Vec3 {
    .x = fconvert.s(fconvert.t(row_cursor->x) - fconvert.t(generated_row->x))
    .y = fconvert.s(fconvert.t(row_cursor->y) - fconvert.t(row_cursor->outer_a.y))
    .z = fconvert.s(fconvert.t(row_cursor->z) - fconvert.t(row_cursor->outer_a.z))
}
00424809        normalize_vector(&vector)
00424868        *generated_row = struct Vec3 {
    .x = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t(row_cursor->x))
    .y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t(row_cursor->y))
    .z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t(row_cursor->z))
}
00424883        int32_t* eax_27 = &self->bod.object->vertices[(self->width_cells + 1) * var_68 + var_64_1]
0042488a        row_cursor->outer_b.x = *eax_27
0042488f        row_cursor->outer_b.y = eax_27[1]
00424899        row_cursor->outer_b.z = eax_27[2]
004248b3        int32_t* edx_17 = &self->bod.object->vertices[(self->width_cells + 1) * var_68 + width_cells_1]
004248b8        row_cursor->inner_b.x = *edx_17
004248bd        row_cursor->inner_b.y = edx_17[1]
004248c3        row_cursor->inner_b.z = edx_17[2]
004248fc        vector = struct Vec3 {
    .x = fconvert.s(fconvert.t(row_cursor->inner_b.x) - fconvert.t(row_cursor->outer_b.x))
    .y = fconvert.s(fconvert.t(row_cursor->inner_b.y) - fconvert.t(row_cursor->outer_b.y))
    .z = fconvert.s(fconvert.t(row_cursor->inner_b.z) - fconvert.t(row_cursor->outer_b.z))
}
00424900        normalize_vector(&vector)
0042490b        long double x87_r7_25 = fconvert.t(vector.x) * fconvert.t(0.400000006f)
0042491b        out.g = fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))
00424929        out.b = fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))
0042493f        float var_24_1 = fconvert.s(fconvert.t(out.g) + fconvert.t(row_cursor->inner_b.y))
00424947        long double x87_r7_30 = fconvert.t(out.b) + fconvert.t(row_cursor->inner_b.z)
0042494e        row_cursor->outer_b.x = fconvert.s(x87_r7_25 + fconvert.t(row_cursor->inner_b.x))
00424951        row_cursor->outer_b.y = var_24_1
00424958        long double x87_r7_31 = fconvert.t(clamp_side)
0042495f        long double temp1_1 = fconvert.t(-1f)
0042495f        x87_r7_31 - temp1_1
00424969        row_cursor->outer_b.z = fconvert.s(x87_r7_30)
00424971        if ((((x87_r7_31 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp1_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00424995        long double x87_r7_33 = fconvert.t(clamp_side)
0042499c        long double temp2_1 = fconvert.t(1f)
0042499c        x87_r7_33 - temp2_1
004249a7        if ((((x87_r7_33 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp2_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
004249a9        int32_t i_3 = 4
004249c7        int32_t i
004249ae        long double x87_r7_34 = fconvert.t(generated_row->x)
004249b0        long double temp4_1 = fconvert.t(0f)
004249b0        x87_r7_34 - temp4_1
004249bb        if ((((x87_r7_34 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp4_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004249bd        generated_row->x = 0
004249c3        generated_row = &generated_row[1]
004249c6        i = i_3
004249c6        i_3 -= 1
004249c7        do while (i != 1)
00424973        int32_t i_2 = 4
00424991        int32_t i_1
00424978        long double x87_r7_32 = fconvert.t(generated_row->x)
0042497a        long double temp3_1 = fconvert.t(0f)
0042497a        x87_r7_32 - temp3_1
00424985        if ((((x87_r7_32 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp3_1) ? 1 : 0) << 0xa | (x87_r7_32 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00424987        generated_row->x = 0
0042498d        generated_row = &generated_row[1]
00424990        i_1 = i_2
00424990        i_2 -= 1
00424991        do while (i_1 != 1)
004249d1        row_cursor = &row_cursor[1]
004249d4        cond:2_1 = var_68 + 1 s<= self->segment_count
004249d6        var_68 += 1
004249da        do while (cond:2_1)
004249e3        int32_t var_68_1 = 0
004249ed        if (self->segment_count s<= 0)
004249ed        return
004249fc        struct FringeFaceQuadPairCursorView* face_pair_cursor = &facequads->vertex_0
00424abd        bool cond:1_1
00424a16        face_pair_cursor->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424a1b        int16_t ebp_6 = (var_68_1 << 2).w
00424a31        face_pair_cursor->vertex_0 = ebp_6 + 5
00424a34        face_pair_cursor->vertex_1 = (var_68_1 << 2).w + 4
00424a3b        face_pair_cursor->vertex_2 = ebp_6
00424a3f        face_pair_cursor->vertex_3 = ebp_6 + 1
00424a45        face_pair_cursor->uv[3].u = 0x3f000000
00424a48        face_pair_cursor->uv[3].v = 0
00424a4b        face_pair_cursor->uv[0].u = 0x3f000000
00424a4e        face_pair_cursor->uv[0].v = 0
00424a51        face_pair_cursor->uv[1].u = 0x3f000000
00424a54        face_pair_cursor->uv[1].v = 0x3f800000
00424a57        face_pair_cursor->uv[2].u = 0x3f000000
00424a5a        face_pair_cursor->uv[2].v = 0x3f800000
00424a6e        face_pair_cursor->second_face.texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00424a77        face_pair_cursor->second_face.vertex_0 = ebp_6 + 6
00424a7e        face_pair_cursor->second_face.vertex_1 = ebp_6 + 7
00424a85        face_pair_cursor->second_face.vertex_2 = ebp_6 + 3
00424a89        face_pair_cursor->second_face.vertex_3 = ebp_6 + 2
00424a92        face_pair_cursor->second_face.uv[3].u = 0x3f000000
00424a95        face_pair_cursor->second_face.uv[3].v = 0x3f800000
00424a98        face_pair_cursor->second_face.uv[0].u = 0x3f000000
00424a9b        face_pair_cursor->second_face.uv[0].v = 0x3f800000
00424aa0        face_pair_cursor->second_face.uv[1].u = 0x3f000000
00424aa3        face_pair_cursor->second_face.uv[1].v = 0
00424aa6        face_pair_cursor->second_face.uv[2].u = 0x3f000000
00424aa9        face_pair_cursor->second_face.uv[2].v = 0
00424ab4        face_pair_cursor = &face_pair_cursor[1]
00424ab7        cond:1_1 = var_68_1 + 1 s< self->segment_count
00424ab9        var_68_1 += 1
00424abd        do while (cond:1_1)
00424aca        return
