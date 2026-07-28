/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_worm_path_template_pair @ 0x420170 */

00420180        int32_t i = 0
00420183        self->kind = PATH_TEMPLATE_KIND_WORM
00420186        self->is_mirrored_x = 0
0042018a        self->side_exit_mode = 0
0042018d        self->width_cells = 0x10
00420194        self->width_or_scale = 4f
0042019b        self->segment_count = 0x18
0042019e        self->segment_count_f = 96f
004201a5        get_path_nodes(self)
004201aa        self->has_entry_mesh_transition = 0
004201b1        int32_t entrance_sample_index = 0
004201b5        int32_t entrance_sample_offset = 0
0042026c        while (entrance_sample_offset s< 0x2a0)
004201ba        *(&self->primary_samples->center_x + entrance_sample_offset) = 0
004201c4        *(&self->primary_samples->rotation_scalar_98 + entrance_sample_offset) = 0
004201ce        *(&self->primary_samples->rotation_scalar_94 + entrance_sample_offset) = 0
004201d8        *(&self->primary_samples->special_scalar + entrance_sample_offset) = 0
004201e2        *(&self->primary_samples->lateral_scale + entrance_sample_offset) = 0x3f800000
004201f4        set_matrix_identity(entrance_sample_offset + self->primary_samples)
004201f9        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00420201        long double x87_r7_1 = float.t(entrance_sample_index)
00420213        *(&primary_samples_1->transform.position + entrance_sample_offset) = *(&primary_samples_1->center_x + entrance_sample_offset)
00420219        *(&self->primary_samples->transform.position.y + entrance_sample_offset) = 0x3efae148
00420223        *(&self->primary_samples->transform.position.z + entrance_sample_offset) = fconvert.s(x87_r7_1 * fconvert.t(self->width_or_scale))
0042022c        set_matrix_identity(self->secondary_samples + entrance_sample_offset)
00420242        *(&self->secondary_samples->transform.position + entrance_sample_offset) = *(&self->primary_samples->center_x + entrance_sample_offset)
00420249        *(&self->secondary_samples->transform.position.y + entrance_sample_offset) = 0x3efae148
00420253        entrance_sample_offset += 0xa8
00420259        *(self->secondary_samples + entrance_sample_offset - 0x70) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)) * fconvert.t(self->width_or_scale))
00420268        entrance_sample_index += 1
00420277        int32_t exit_sample_offset = 0xd20
0042027c        int32_t exit_sample_index = 0x14
00420283        *(&self->primary_samples->center_x + exit_sample_offset) = 0
0042028d        *(&self->primary_samples->rotation_scalar_98 + exit_sample_offset) = 0
00420297        *(&self->primary_samples->rotation_scalar_94 + exit_sample_offset) = 0
004202a1        *(&self->primary_samples->special_scalar + exit_sample_offset) = 0
004202ab        *(&self->primary_samples->lateral_scale + exit_sample_offset) = 0x3f800000
004202bd        set_matrix_identity(exit_sample_offset + self->primary_samples)
004202c2        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004202c5        long double x87_r7_5 = float.t(exit_sample_index)
004202d7        *(&primary_samples_2->transform.position + exit_sample_offset) = *(&primary_samples_2->center_x + exit_sample_offset)
004202dd        *(&self->primary_samples->transform.position.y + exit_sample_offset) = 0x3efae148
004202eb        *(&self->primary_samples->transform.position.z + exit_sample_offset) = fconvert.s(x87_r7_5 * fconvert.t(self->width_or_scale))
004202f4        set_matrix_identity(self->secondary_samples + exit_sample_offset)
0042030a        *(&self->secondary_samples->transform.position + exit_sample_offset) = *(&self->primary_samples->center_x + exit_sample_offset)
00420311        *(&self->secondary_samples->transform.position.y + exit_sample_offset) = 0x3efae148
0042031f        exit_sample_offset += 0xa8
00420326        exit_sample_index += 1
0042032d        *(self->secondary_samples + exit_sample_offset - 0x70) = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)) * fconvert.t(self->width_or_scale))
00420334        do while (exit_sample_index - 0x14 s< 4)
0042033a        int32_t middle_index = 0
0042033c        int32_t middle_sample_offset = 0x2a0
004205b1        while (middle_sample_offset s< 0xd20)
00420344        *(&self->primary_samples->center_x + middle_sample_offset) = 0
0042034e        *(&self->primary_samples->rotation_scalar_98 + middle_sample_offset) = 0
00420358        *(&self->primary_samples->rotation_scalar_94 + middle_sample_offset) = 0
00420362        *(&self->primary_samples->special_scalar + middle_sample_offset) = 0
0042036e        *(&self->primary_samples->lateral_scale + middle_sample_offset) = 0x3f800000
0042037e        set_matrix_identity(middle_sample_offset + self->primary_samples)
00420386        void* eax_16 = self->primary_samples + middle_sample_offset
0042038e        *(eax_16 + 0x30) = *(eax_16 + 0x90)
0042039b        *(&self->primary_samples->transform.position.y + middle_sample_offset) = 0x3efae148
004203a3        long double x87_r7_9 = float.t(middle_index + 4)
004203b1        *(&self->primary_samples->transform.position.z + middle_sample_offset) = fconvert.s(x87_r7_9 * fconvert.t(self->width_or_scale))
004203ba        set_matrix_identity(self->secondary_samples + middle_sample_offset)
004203d6        *(&self->secondary_samples->transform.position + middle_sample_offset) = *(&self->primary_samples->center_x + middle_sample_offset)
004203dd        *(&self->secondary_samples->transform.position.y + middle_sample_offset) = 0x3efae148
004203eb        *(&self->secondary_samples->transform.position.z + middle_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_9)) * fconvert.t(self->width_or_scale))
004203ef        if (middle_sample_offset s<= 0x2a0)
00420590        set_matrix_rotation_identity(middle_sample_offset + self->primary_samples - 0xa8)
0042059f        set_matrix_rotation_identity(self->secondary_samples + middle_sample_offset - 0xa8)
00420428        *(middle_sample_offset + self->primary_samples - 0x98) = struct Vec3 {
    .x = 0
    .y = 1f
    .z = 0f
}
0042042b        struct PathTemplateSample* primary_samples = self->primary_samples
0042044f        float var_50_1 = fconvert.s(fconvert.t(*(&primary_samples->transform.position.y + middle_sample_offset)) - fconvert.t(*(middle_sample_offset + primary_samples - 0x74)))
00420459        long double x87_r7_18 = fconvert.t(*(&primary_samples->transform.position.z + middle_sample_offset)) - fconvert.t(*(middle_sample_offset + primary_samples - 0x70))
00420460        *(middle_sample_offset + primary_samples - 0x88) = fconvert.s(fconvert.t(*(&primary_samples->transform.position + middle_sample_offset)) - fconvert.t(*(middle_sample_offset + primary_samples - 0x78)))
00420462        *(middle_sample_offset + primary_samples - 0x84) = var_50_1
0042046d        *(middle_sample_offset + primary_samples - 0x80) = fconvert.s(x87_r7_18)
0042047a        normalize_vector(middle_sample_offset + self->primary_samples - 0x88)
00420484        struct PathTemplateSample* primary_sample_cursor_first = middle_sample_offset + self->primary_samples
0042049b        cross_vectors(primary_sample_cursor_first - 0xa8, primary_sample_cursor_first - 0x98, primary_sample_cursor_first - 0x88)
004204a3        struct PathTemplateSample* primary_sample_cursor_second = middle_sample_offset + self->primary_samples
004204ba        cross_vectors(primary_sample_cursor_second - 0x98, primary_sample_cursor_second - 0x88, primary_sample_cursor_second - 0xa8)
004204f2        *(self->secondary_samples + middle_sample_offset - 0x98) = struct Vec3 {
    .x = 0
    .y = 1f
    .z = 0f
}
004204f8        void* eax_25 = self->secondary_samples + middle_sample_offset
00420516        float var_38_1 = fconvert.s(fconvert.t(*(eax_25 + 0x34)) - fconvert.t(*(eax_25 - 0x74)))
00420520        long double x87_r7_26 = fconvert.t(*(eax_25 + 0x38)) - fconvert.t(*(eax_25 - 0x70))
00420527        *(eax_25 - 0x88) = fconvert.s(fconvert.t(*(eax_25 + 0x30)) - fconvert.t(*(eax_25 - 0x78)))
00420529        *(eax_25 - 0x84) = var_38_1
00420534        *(eax_25 - 0x80) = fconvert.s(x87_r7_26)
00420541        normalize_vector(self->secondary_samples + middle_sample_offset - 0x88)
00420549        struct PathTemplateSample* secondary_sample_cursor_first = self->secondary_samples + middle_sample_offset
00420561        cross_vectors(secondary_sample_cursor_first - 0xa8, secondary_sample_cursor_first - 0x98, secondary_sample_cursor_first - 0x88)
00420569        struct PathTemplateSample* secondary_sample_cursor_second = self->secondary_samples + middle_sample_offset
0042057f        cross_vectors(secondary_sample_cursor_second - 0x98, secondary_sample_cursor_second - 0x88, secondary_sample_cursor_second - 0xa8)
004205a4        middle_sample_offset += 0xa8
004205aa        middle_index += 1
004205ba        int32_t delta_index = 0
004205bf        if (self->segment_count - 1 s> 0)
004205c5        int32_t delta_sample_offset = 0
004205ca        void* eax_31 = self->primary_samples + delta_sample_offset
004205e8        float var_38_2 = fconvert.s(fconvert.t(*(eax_31 + 0xdc)) - fconvert.t(*(eax_31 + 0x34)))
004205ef        long double x87_r7_34 = fconvert.t(*(eax_31 + 0xe0)) - fconvert.t(*(eax_31 + 0x38))
004205f6        *(eax_31 + 0x80) = fconvert.s(fconvert.t(*(eax_31 + 0xd8)) - fconvert.t(*(eax_31 + 0x30)))
004205f8        *(eax_31 + 0x84) = var_38_2
00420603        *(eax_31 + 0x88) = fconvert.s(x87_r7_34)
00420618        *(&self->primary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + delta_sample_offset))
0042061f        struct PathTemplateSample* secondary_samples = self->secondary_samples
00420643        float var_44_1 = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + delta_sample_offset)))
0042064a        long double x87_r7_41 = fconvert.t(*(delta_sample_offset + secondary_samples + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + delta_sample_offset))
00420651        *(&secondary_samples->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + delta_sample_offset)))
00420653        *(&secondary_samples->delta_dir_to_next.y + delta_sample_offset) = var_44_1
0042065e        *(&secondary_samples->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_41)
00420673        delta_index += 1
00420674        *(&self->secondary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + delta_sample_offset))
0042067e        delta_sample_offset += 0xa8
00420687        do while (delta_index s< self->segment_count - 1)
004206e4        *(&self->primary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
004206fc        *(&self->primary_samples[self->segment_count] - 0x1c) = self->width_or_scale
00420727        *(&self->secondary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0042073f        *(&self->secondary_samples[self->segment_count] - 0x1c) = self->width_or_scale
00420743        struct Object* object = self->bod.object
00420746        enum ObjectFlag flags = object->flags
00420749        flags.b |= 0x80
0042074c        object->flags = flags
0042075b        request_object_vertices(self->bod.object, (self->segment_count + 1) * self->width_cells)
0042076d        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
00420775        request_object_vertex_colours(self->bod.object)
0042077a        struct Object* object_1 = self->bod.object
0042077d        int32_t edi = 0
0042077f        int32_t var_80 = 0
0042078c        object_1->flags |= OBJECT_FLAG_USE_VERTEX_COLOURS
0042078f        struct Object* object_2 = self->bod.object
00420792        struct Vec3* vertices = object_2->vertices
00420795        struct ObjectFaceQuad* facequads = object_2->facequads
00420798        struct tColour* vertex_colours = object_2->vertex_colours
0042079b        uint32_t segment_count = self->segment_count
004207a8        uint32_t segment_count_2 = segment_count
004207ac        if (segment_count s>= 0)
004207b2        void* var_7c_1 = nullptr
004207be        while (true)
004207be        uint32_t width_cells = self->width_cells
004207c1        int32_t i_2 = 0
004207d1        uint32_t width_cells_1 = width_cells
004207d9        if (width_cells s> 0)
004207e2        float r
004207e2        float g
004207e2        float b
004207e2        float a
004207e2        if (edi s>= self->segment_count)
00420983        a = 0f
0042098f        b = 0f
00420991        g = 0f
00420999        r = 0f
0042099b        struct Vec3* previous_row_vertex = &vertices[(edi - 1) * width_cells + i]
0042099e        struct Vec3* terminal_vertex = &vertices[width_cells * edi + i]
004209a3        terminal_vertex->x = previous_row_vertex->x
004209a8        terminal_vertex->y = previous_row_vertex->y
004209ae        terminal_vertex->z = previous_row_vertex->z
004209b9        int32_t ecx_73 = (self->width_cells * edi + i) * 3
004209c7        (&vertices->z)[ecx_73] = fconvert.s(fconvert.t((&vertices->z)[ecx_73]) + fconvert.t(self->width_or_scale))
004207ef        struct PathTemplateSample* primary_mesh_sample = self->primary_samples + var_7c_1
004207f1        void* var_94_7 = var_7c_1
004207f8        long double x87_r7_47 = fconvert.t(primary_mesh_sample->lateral_scale) * fconvert.t(4f)
004207fe        float var_80_1 = fconvert.s(x87_r7_47)
00420805        float var_3c_3 = fconvert.s(x87_r7_47 * fconvert.t(primary_mesh_sample->transform.basis_up.x))
00420810        float var_38_3 = fconvert.s(fconvert.t(var_80_1) * fconvert.t(primary_mesh_sample->transform.basis_up.y))
0042081b        float var_34_3 = fconvert.s(fconvert.t(var_80_1) * fconvert.t(primary_mesh_sample->transform.basis_up.z))
00420823        float var_78_1 = fconvert.s(float.t(i_2))
00420838        long double st0_5 = cosine(fconvert.s(fconvert.t(var_78_1) / float.t(width_cells_1) * fconvert.t(6.28318548f)))
0042084a        struct PathTemplateSample* primary_mesh_sample_reloaded = var_7c_1 + self->primary_samples
0042086c        float var_48_2 = fconvert.s(fconvert.t(var_80_1) * fconvert.t(primary_mesh_sample_reloaded->transform.basis_right.x))
00420877        float var_44_2 = fconvert.s(fconvert.t(var_80_1) * fconvert.t(primary_mesh_sample_reloaded->transform.basis_right.y))
00420882        float var_40_2 = fconvert.s(fconvert.t(var_80_1) * fconvert.t(primary_mesh_sample_reloaded->transform.basis_right.z))
00420896        long double st0_6 = sine(fconvert.s(fconvert.t(var_78_1) / float.t(self->width_cells) * fconvert.t(6.28318548f)))
004208a8        struct Vec3* primary_position = &self->primary_samples->transform.position + var_7c_1
00420932        long double x87_r7_72 = fconvert.t(fconvert.s(float.t(var_80) * fconvert.t(6.28318548f) / float.t(segment_count_2)))
00420958        vertices[self->width_cells * edi + i].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(fconvert.s(fconvert.t(var_48_2) * st0_6)) + fconvert.t(primary_position->x) + fconvert.t(fconvert.s(fconvert.t(var_3c_3) * st0_5)))
    .y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(var_44_2) * st0_6)) + fconvert.t(primary_position->y))) + fconvert.t(fconvert.s(fconvert.t(var_38_3) * st0_5)))
    .z = fconvert.s(fconvert.t(fconvert.s(st0_6 * fconvert.t(var_40_2) + fconvert.t(primary_position->z))) + fconvert.t(fconvert.s(fconvert.t(var_34_3) * st0_5)))
}
0042096c        a = fconvert.s(fconvert.t(0.5f) - cosine(fconvert.s(x87_r7_72 + x87_r7_72)) * fconvert.t(0.5f))
0042096f        b = 1f
00420974        g = 1f
00420979        r = 1f
004209da        store_color4f(&vertex_colours[self->width_cells * edi + i], r, g, b, a)
004209e7        int32_t edx_47 = (self->width_cells * edi + i) * 3
004209ea        long double x87_r7_79 = fconvert.t((&vertices->y)[edx_47])
004209ee        long double temp2_1 = fconvert.t(0f)
004209ee        x87_r7_79 - temp2_1
004209fd        if ((((x87_r7_79 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_79, temp2_1) ? 1 : 0) << 0xa | (x87_r7_79 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00420a07        (&vertices->y)[edx_47] = fconvert.s(fconvert.t((&vertices->y)[edx_47]) * fconvert.t(0.300000012f))
00420a09        width_cells = self->width_cells
00420a0c        i += 1
00420a0f        i_2 = i
00420a13        width_cells_1 = width_cells
00420a17        do while (i s< width_cells)
00420a21        uint32_t segment_count_1 = self->segment_count
00420a24        edi += 1
00420a2d        var_80 = edi
00420a31        var_7c_1 += 0xa8
00420a35        segment_count_2 = segment_count_1
00420a39        if (edi s> segment_count_1)
00420a39        break
004207b8        i = 0
00420a3f        i = 0
00420a44        int32_t i_1 = 0
00420a4a        if (self->segment_count s> 0)
00420a53        int32_t j = 0
00420a57        int32_t j_2 = 0
00420a5b        if (self->width_cells s> 0)
00420a72        float var_80_2 = fconvert.s(float.t(i_1) * fconvert.t(0.125f))
00420a80        float var_74 = fconvert.s(float.t(i + 1) * fconvert.t(0.125f))
00420a88        int32_t j_3 = j + 1
00420a8b        int32_t edx_50 = 0
00420a8d        int32_t j_1 = j_3
00420a91        int32_t var_70_5 = 0
00420ab7        while (true)
00420abd        int32_t ecx_85 = (edx_50 + ((self->width_cells * i + j) << 1)) * 0x30
00420ac0        struct ObjectFaceQuad* face = facequads + ecx_85
00420ac4        __builtin_memset(face, 0, 2)
00420ac9        if (edx_50 != 0)
00420b15        ecx_85.w = i.w
00420b18        ecx_85.w *= self->width_cells.w
00420b22        face->vertex_0 = (mods.dp.d(sx.q(j_3), self->width_cells)).w + ecx_85.w
00420b33        face->vertex_1 = i.w * self->width_cells.w + j.w
00420b3e        face->vertex_2 = (i.w + 1) * self->width_cells.w + j.w
00420b4c        self->width_cells
00420b51        face->vertex_3 = (mods.dp.d(sx.q(j_1), self->width_cells)).w + (i.w + 1) * self->width_cells.w
00420acb        edx_50.w = i.w
00420ad1        edx_50.w *= self->width_cells.w
00420ad8        face->vertex_0 = edx_50.w + j.w
00420aee        face->vertex_1 = (mods.dp.d(sx.q(j_3), self->width_cells)).w + i.w * self->width_cells.w
00420b00        face->vertex_2 = (mods.dp.d(sx.q(j_1), self->width_cells)).w + (i.w + 1) * self->width_cells.w
00420b0b        face->vertex_3 = (i.w + 1) * self->width_cells.w + j.w
00420b60        char* texture_path_1
00420b60        if (((j.b ^ i.b) & 1) != 0)
00420b73        texture_path_1 = texture_path
00420b69        texture_path_1 = texture_path
00420b7e        face->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
00420b8a        float var_6c_4 = fconvert.s(float.t(self->width_cells))
00420b92        long double x87_r7_90 = fconvert.t(fconvert.s(float.t(j_2))) / fconvert.t(var_6c_4)
00420b9a        long double x87_r6_20 = fconvert.t(fconvert.s(float.t(j_1))) / fconvert.t(var_6c_4)
00420ba2        if (var_70_5 != 0)
00420bcc        face->uv[0].u = fconvert.s(x87_r6_20)
00420bd3        face->uv[0].v = var_80_2
00420bd8        face->uv[1].u = fconvert.s(x87_r7_90)
00420bdf        face->uv[1].v = var_80_2
00420be2        face->uv[2].u = fconvert.s(x87_r7_90)
00420be9        face->uv[2].v = var_74
00420bec        face->uv[3].u = fconvert.s(x87_r6_20)
00420bef        face->uv[3].v = var_74
00420bac        face->uv[0].u = fconvert.s(x87_r7_90)
00420baf        face->uv[0].v = var_80_2
00420bb6        face->uv[1].u = fconvert.s(x87_r6_20)
00420bb9        face->uv[1].v = var_80_2
00420bbe        face->uv[2].u = fconvert.s(x87_r6_20)
00420bc1        face->uv[2].v = var_74
00420bc4        face->uv[3].u = fconvert.s(x87_r7_90)
00420bc7        face->uv[3].v = var_74
00420bf3        bool cond:11_1 = var_70_5 + 1 s< 2
00420bf6        var_70_5 += 1
00420bfa        if (not(cond:11_1))
00420bfa        break
00420aa3        edx_50 = var_70_5
00420aa7        j_3 = j_1
00420c00        j = j_1
00420c09        j_2 = j
00420c0d        do while (j s< self->width_cells)
00420c16        i += 1
00420c19        i_1 = i
00420c1d        do while (i s< self->segment_count)
00420c25        calc_path_length_z(self)
00420c34        return
