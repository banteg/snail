/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_loopbow_path_template_pair @ 0x42ba80 */

0042ba92        int32_t i_1 = 0
0042ba98        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0042ba9b        float center_offset = 0f
0042ba9f        if (width_cells_arg == 4)
0042baa1        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0042baa4        center_offset = 0.5f
0042bab9        self->is_mirrored_x = 0
0042babd        self->side_exit_mode = 0
0042bac0        self->width_cells = width_cells_arg
0042bac8        int16_t x87control
0042bac8        int32_t curve_segment_count = ftol(x87control, fconvert.t(curve_scale) * fconvert.t(6.28318548f))
0042bade        self->width_or_scale = 1f
0042bae1        self->segment_count = curve_segment_count + 0xe
0042bae4        self->segment_count_f = fconvert.s(float.t(curve_segment_count + 0xe))
0042bae7        long double x87_r7_3 = float.t(curve_segment_count)
0042baeb        float curve_segment_count_f = fconvert.s(x87_r7_3)
0042baf5        float curve_radius = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
0042bafc        get_path_nodes(self)
0042bb01        self->has_entry_mesh_transition = 1
0042bb08        int32_t lead_sample_index = 0
0042bb0c        int32_t lead_sample_offset = 0
0042bbee        while (lead_sample_offset s< 0x498)
0042bb15        float lead_sample_z = fconvert.s(float.t(lead_sample_index))
0042bb38        *(&self->primary_samples->center_x + lead_sample_offset) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f) - fconvert.t(lead_sample_z) * fconvert.t(0.142857149f) * fconvert.t(center_offset))
0042bb42        *(&self->primary_samples->rotation_scalar_98 + lead_sample_offset) = 0
0042bb4c        *(&self->primary_samples->rotation_scalar_94 + lead_sample_offset) = 0
0042bb56        *(&self->primary_samples->special_scalar + lead_sample_offset) = 0
0042bb60        *(&self->primary_samples->lateral_scale + lead_sample_offset) = 0x3f800000
0042bb6e        set_matrix_identity(lead_sample_offset + self->primary_samples)
0042bb73        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042bb84        *(&primary_samples_4->transform.position + lead_sample_offset) = *(&primary_samples_4->center_x + lead_sample_offset)
0042bb8a        *(&self->primary_samples->transform.position.y + lead_sample_offset) = 0
0042bb91        *(&self->primary_samples->transform.position.z + lead_sample_offset) = fconvert.s(fconvert.t(lead_sample_z))
0042bb98        *(&self->primary_samples->delta_length + lead_sample_offset) = 0x3f800000
0042bba6        set_matrix_identity(lead_sample_offset + self->secondary_samples)
0042bbbc        *(&self->secondary_samples->transform.position + lead_sample_offset) = *(&self->primary_samples->center_x + lead_sample_offset)
0042bbc3        *(&self->secondary_samples->transform.position.y + lead_sample_offset) = 0x3efae148
0042bbd2        *(&self->secondary_samples->transform.position.z + lead_sample_offset) = fconvert.s(fconvert.t(lead_sample_z))
0042bbd9        lead_sample_offset += 0xa8
0042bbe6        *(lead_sample_offset + self->secondary_samples - 0x1c) = 0x3f800000
0042bbea        lead_sample_index += 1
0042bbfa        int32_t tail_index = 0
0042bc0d        int32_t tail_sample_offset = (curve_segment_count + 7) * 0xa8
0042bc38        *(&self->primary_samples->center_x + tail_sample_offset) = fconvert.s((fconvert.t(1f) - float.t(tail_index) * fconvert.t(0.166666672f)) * fconvert.t(center_offset) + fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0042bc42        *(&self->primary_samples->rotation_scalar_98 + tail_sample_offset) = 0
0042bc4c        *(&self->primary_samples->rotation_scalar_94 + tail_sample_offset) = 0
0042bc56        *(&self->primary_samples->special_scalar + tail_sample_offset) = 0
0042bc60        *(&self->primary_samples->lateral_scale + tail_sample_offset) = 0x3f800000
0042bc72        set_matrix_identity(tail_sample_offset + self->primary_samples)
0042bc77        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042bc84        *(&primary_samples_5->transform.position + tail_sample_offset) = *(&primary_samples_5->center_x + tail_sample_offset)
0042bc91        *(&self->primary_samples->transform.position.y + tail_sample_offset) = 0
0042bc95        long double x87_r7_17 = float.t(tail_index + 7)
0042bca0        *(&self->primary_samples->transform.position.z + tail_sample_offset) = fconvert.s(x87_r7_17)
0042bca9        *(&self->primary_samples->delta_length + tail_sample_offset) = 0x3f800000
0042bcb9        set_matrix_identity(tail_sample_offset + self->secondary_samples)
0042bcd0        *(&self->secondary_samples->transform.position + tail_sample_offset) = *(&self->primary_samples->center_x + tail_sample_offset)
0042bcd7        tail_index += 1
0042bcdb        *(&self->secondary_samples->transform.position.y + tail_sample_offset) = 0x3efae148
0042bce6        *(&self->secondary_samples->transform.position.z + tail_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_17)))
0042bced        tail_sample_offset += 0xa8
0042bcf6        *(tail_sample_offset + self->secondary_samples - 0x1c) = 0x3f800000
0042bcfe        do while (tail_index s< 7)
0042bd08        int32_t curve_index = 0
0042bd0e        if (curve_segment_count s> 0)
0042bd56        float secondary_radius = fconvert.s(fconvert.t(curve_radius) - fconvert.t(0.49000001f))
0042bd65        int32_t terminal_sample_offset_1 = (curve_segment_count + 0xe) * 0xa8
0042bd68        int32_t terminal_sample_offset = terminal_sample_offset_1
0042bd6c        int32_t curve_sample_offset = 0x498
0042bd79        while (true)
0042bd79        long double x87_r7_21 = float.t(curve_index)
0042bd7d        struct PathTemplateSample* primary_samples = self->primary_samples
0042bd80        int32_t terminal_sample_offset_2 = terminal_sample_offset_1
0042bd8d        float angle = fconvert.s(x87_r7_21 * fconvert.t(6.28318548f) / fconvert.t(curve_segment_count_f))
0042bda7        *(&primary_samples->center_x + curve_sample_offset) = fconvert.s((fconvert.t(*(primary_samples + terminal_sample_offset_1 - 0x18)) - fconvert.t(primary_samples->center_x)) * x87_r7_21 / fconvert.t(curve_segment_count_f) + fconvert.t(primary_samples->center_x))
0042bdbd        float* edi_3 = &self->primary_samples->center_x + curve_sample_offset
0042bdc4        float half_angle = fconvert.s(fconvert.t(angle) * fconvert.t(0.5f))
0042bde3        *edi_3 = fconvert.s(sine(fconvert.s(fconvert.t(half_angle) + fconvert.t(4.71238899f))) * fconvert.t(center_offset) + fconvert.t(*edi_3))
0042bde8        *(&self->primary_samples->rotation_scalar_98 + curve_sample_offset) = 0
0042bdf2        *(&self->primary_samples->rotation_scalar_94 + curve_sample_offset) = 0
0042bdfc        *(&self->primary_samples->special_scalar + curve_sample_offset) = 0
0042be06        *(&self->primary_samples->lateral_scale + curve_sample_offset) = 0x3f800000
0042be18        set_matrix_identity(curve_sample_offset + self->primary_samples)
0042be1d        struct PathTemplateSample* primary_samples_6 = self->primary_samples
0042be2f        *(&primary_samples_6->transform.position + curve_sample_offset) = *(&primary_samples_6->center_x + curve_sample_offset)
0042be48        *(&self->primary_samples->transform.position.z + curve_sample_offset) = fconvert.s(sine(angle) * fconvert.t(curve_radius) + fconvert.t(7f))
0042be67        *(&self->primary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fconvert.t(curve_radius) - cosine(angle) * fconvert.t(curve_radius))
0042be6e        set_matrix_identity(curve_sample_offset + self->secondary_samples)
0042be81        *(&self->secondary_samples->transform.position + curve_sample_offset) = *(&self->primary_samples->center_x + curve_sample_offset)
0042be98        *(&self->secondary_samples->transform.position.z + curve_sample_offset) = fconvert.s(sine(angle) * fconvert.t(secondary_radius) + fconvert.t(7f))
0042beb4        *(&self->secondary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fconvert.t(curve_radius) - cosine(angle) * fconvert.t(secondary_radius))
0042bed5        *(curve_sample_offset + self->primary_samples) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0042bedb        *(&self->primary_samples->transform.basis_up + curve_sample_offset) = 0
0042bee2        struct PathTemplateSample* primary_sample_cursor_first = self->primary_samples + curve_sample_offset
0042bee7        primary_sample_cursor_first->transform.basis_up.y = fconvert.s(fconvert.t(curve_radius) - fconvert.t(primary_sample_cursor_first->transform.position.y))
0042beea        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042befa        (curve_sample_offset + primary_samples_3)->transform.basis_up.z = fconvert.s(fconvert.t(7f) - fconvert.t(*(&primary_samples_3->transform.position.z + curve_sample_offset)))
0042bf04        normalize_vector(&self->primary_samples->transform.basis_up + curve_sample_offset)
0042bf0c        struct PathTemplateSample* primary_sample = self->primary_samples + curve_sample_offset
0042bf18        cross_vectors(&primary_sample->transform.basis_forward, primary_sample, &primary_sample->transform.basis_up)
0042bf3c        *(curve_sample_offset + self->secondary_samples) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0042bf42        *(&self->secondary_samples->transform.basis_up + curve_sample_offset) = 0
0042bf46        struct PathTemplateSample* secondary_samples_4 = self->secondary_samples
0042bf50        (curve_sample_offset + secondary_samples_4)->transform.basis_up.y = fconvert.s(fconvert.t(curve_radius) - fconvert.t(*(&secondary_samples_4->transform.position.y + curve_sample_offset)))
0042bf53        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042bf62        (secondary_samples + curve_sample_offset)->transform.basis_up.z = fconvert.s(fconvert.t(7f) - fconvert.t(*(&secondary_samples->transform.position.z + curve_sample_offset)))
0042bf6c        normalize_vector(&self->secondary_samples->transform.basis_up + curve_sample_offset)
0042bf76        struct PathTemplateSample* secondary_sample = curve_sample_offset + self->secondary_samples
0042bf81        cross_vectors(&secondary_sample->transform.basis_forward, secondary_sample, &secondary_sample->transform.basis_up)
0042bf8a        struct TransformMatrix var_40
0042bf8a        set_matrix_identity(&var_40)
0042bf99        float half_sine = fconvert.s(sine(half_angle))
0042bfb7        rotate_matrix_local_y(&var_40, fconvert.s(sine(half_angle) * fconvert.t(half_sine) * fconvert.t(0.52359879f)))
0042bfbc        struct PathTemplateSample* primary_samples_7 = self->primary_samples
0042bfd4        *(&primary_samples_7->transform.position.z + curve_sample_offset) = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position.z + curve_sample_offset)) - fconvert.t(7f))
0042bfd6        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042bfe7        *(&secondary_samples_1->transform.position.z + curve_sample_offset) = fconvert.s(fconvert.t(*(&secondary_samples_1->transform.position.z + curve_sample_offset)) - fconvert.t(7f))
0042bfec        multiply_matrix(curve_sample_offset + self->primary_samples, &var_40)
0042bffd        multiply_matrix(curve_sample_offset + self->secondary_samples, &var_40)
0042c002        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042c017        *(&primary_samples_1->transform.position.z + curve_sample_offset) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position.z + curve_sample_offset)) + fconvert.t(7f))
0042c019        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
0042c02a        *(&secondary_samples_2->transform.position.z + curve_sample_offset) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position.z + curve_sample_offset)) + fconvert.t(7f))
0042c03b        __builtin_memcpy(curve_sample_offset + self->secondary_samples, curve_sample_offset + self->primary_samples, 0x40)
0042c03d        struct PathTemplateSample* primary_samples_8 = self->primary_samples
0042c048        long double x87_r7_67 = fconvert.t(*(&primary_samples_8->transform.basis_up + curve_sample_offset)) * fconvert.t(0.49000001f)
0042c05c        float var_60_1 = fconvert.s(fconvert.t(*(&primary_samples_8->transform.basis_up.y + curve_sample_offset)) * fconvert.t(0.49000001f))
0042c063        long double x87_r6_18 = fconvert.t((&primary_samples_8->transform.basis_up + curve_sample_offset)->z) * fconvert.t(0.49000001f)
0042c06c        struct Vec3* secondary_position = &self->secondary_samples->transform.position + curve_sample_offset
0042c070        curve_sample_offset += 0xa8
0042c07c        secondary_position->x = fconvert.s(x87_r7_67 + fconvert.t(secondary_position->x))
0042c085        secondary_position->y = fconvert.s(fconvert.t(var_60_1) + fconvert.t(secondary_position->y))
0042c08f        secondary_position->z = fconvert.s(fconvert.t(fconvert.s(x87_r6_18)) + fconvert.t(secondary_position->z))
0042c097        bool cond:4_1 = curve_index + 1 s< curve_segment_count
0042c099        curve_index += 1
0042c09d        if (not(cond:4_1))
0042c09d        break
0042bd73        terminal_sample_offset_1 = terminal_sample_offset
0042c0a3        i_1 = 0
0042c0a8        int32_t delta_index = 0
0042c0ad        if (self->segment_count - 1 s> 0)
0042c0b3        int32_t delta_sample_offset = 0
0042c0b5        struct PathTemplateSample* primary_samples_9 = self->primary_samples
0042c0d9        float var_88_1 = fconvert.s(fconvert.t(*(delta_sample_offset + primary_samples_9 + 0xdc)) - fconvert.t(*(&primary_samples_9->transform.position.y + delta_sample_offset)))
0042c0e0        long double x87_r7_78 = fconvert.t(*(delta_sample_offset + primary_samples_9 + 0xe0)) - fconvert.t(*(&primary_samples_9->transform.position.z + delta_sample_offset))
0042c0e7        *(&primary_samples_9->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + primary_samples_9 + 0xd8)) - fconvert.t(*(&primary_samples_9->transform.position + delta_sample_offset)))
0042c0e9        *(&primary_samples_9->delta_dir_to_next.y + delta_sample_offset) = var_88_1
0042c0f4        *(&primary_samples_9->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_78)
0042c109        *(&self->primary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + delta_sample_offset))
0042c110        struct PathTemplateSample* secondary_samples_3 = self->secondary_samples
0042c134        float var_6c_1 = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_3 + 0xdc)) - fconvert.t(*(&secondary_samples_3->transform.position.y + delta_sample_offset)))
0042c13b        long double x87_r7_85 = fconvert.t(*(delta_sample_offset + secondary_samples_3 + 0xe0)) - fconvert.t(*(&secondary_samples_3->transform.position.z + delta_sample_offset))
0042c142        *(&secondary_samples_3->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_3 + 0xd8)) - fconvert.t(*(&secondary_samples_3->transform.position + delta_sample_offset)))
0042c144        *(&secondary_samples_3->delta_dir_to_next.y + delta_sample_offset) = var_6c_1
0042c14f        *(&secondary_samples_3->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_85)
0042c164        delta_index += 1
0042c165        *(&self->secondary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + delta_sample_offset))
0042c16f        delta_sample_offset += 0xa8
0042c178        do while (delta_index s< self->segment_count - 1)
0042c1cd        *(&self->primary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0042c1df        int32_t var_84_2 = 0x3f800000
0042c1eb        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042c214        *(&self->secondary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0042c229        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042c23c        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042c24e        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042c253        struct Object* object = self->bod.object
0042c256        struct ObjectFaceQuad* facequads = object->facequads
0042c259        struct Vec3* vertices = object->vertices
0042c263        int32_t i = 0
0042c26b        if (self->segment_count s>= 0)
0042c271        int32_t ebx = 0
0042c273        int32_t var_74_1 = 0
0042c277        uint32_t width_cells = self->width_cells
0042c27a        int32_t edi_9 = 0
0042c27e        int32_t var_9c = 0
0042c282        uint32_t width_cells_1 = width_cells
0042c286        if (width_cells s>= 0)
0042c299        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042c2a2        long double x87_r7_88 = float.t(var_9c) - float.t(width_cells_1) * fconvert.t(0.5f)
0042c2a4        if (i == self->segment_count)
0042c304        void* eax_64 = primary_samples_2 + ebx
0042c315        ebx = var_74_1
0042c382        vertices[(width_cells + 1) * i + edi_9].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(*(eax_64 - 0x78)) + fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(*(eax_64 - 0xa8)))))
    .y = fconvert.s(fconvert.t(*(eax_64 - 0x74)) + fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(*(eax_64 - 0xa4)))))
    .z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_64 - 0x70)) + fconvert.t(1f))) + x87_r7_88 * fconvert.t(*(eax_64 - 0xa0)))
}
0042c2a6        struct PathTemplateSample* primary_mesh_sample = primary_samples_2 + ebx
0042c2fc        vertices[(width_cells + 1) * i + edi_9].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
    .y = fconvert.s(fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
    .z = fconvert.s(x87_r7_88 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
}
0042c385        width_cells = self->width_cells
0042c388        edi_9 += 1
0042c38b        var_9c = edi_9
0042c38f        width_cells_1 = width_cells
0042c393        do while (edi_9 s<= width_cells)
0042c39c        i += 1
0042c39d        ebx += 0xa8
0042c3a5        var_74_1 = ebx
0042c3a9        do while (i s<= self->segment_count)
0042c3b2        int32_t edi_10 = 0
0042c3b6        if (self->segment_count s> 0)
0042c3c3        while (true)
0042c3c3        int32_t i_2 = 0
0042c3c9        if (self->width_cells s> 0)
0042c3d1        int32_t eax_76 = edi_10 & 0x80000007
0042c3d6        if (eax_76 s< 0)
0042c3dc        eax_76 = ((eax_76 - 1) | 0xfffffff8) + 1
0042c3f0        float var_7c_1 = fconvert.s(float.t(eax_76) * fconvert.t(0.125f))
0042c3fe        float var_90_1 = fconvert.s(float.t(eax_76 + 1) * fconvert.t(0.125f))
0042c409        int32_t ecx_70 = 0
0042c40f        int32_t var_94 = 0
0042c419        float var_80 = fconvert.s(float.t(i_2) * fconvert.t(0.125f))
0042c427        float var_9c_1 = fconvert.s(float.t(i_1 + 1) * fconvert.t(0.125f))
0042c43b        while (true)
0042c43b        int32_t eax_83 = ecx_70 + ((self->width_cells * edi_10 + i_1) << 1)
0042c43e        if (ecx_70 != 0)
0042c4ff        struct ObjectFaceQuad* facequads_1 = facequads
0042c50a        struct ObjectFaceQuad* face_second = &facequads_1[eax_83]
0042c50d        __builtin_memset(face_second, 0, 2)
0042c512        ecx_70.w = self->width_cells.w
0042c516        ecx_70.w += 1
0042c51f        face_second->vertex_0 = ecx_70.w * edi_10.w + i_1.w + 1
0042c523        facequads_1.w = self->width_cells.w
0042c527        facequads_1.w += 1
0042c52e        face_second->vertex_1 = facequads_1.w * edi_10.w + i_1.w
0042c540        face_second->vertex_2 = (self->width_cells.w + 1) * (edi_10.w + 1) + i_1.w
0042c558        face_second->vertex_3 = (self->width_cells.w + 1) * (edi_10.w + 1) + i_1.w + 1
0042c55c        char* texture_path_1
0042c55c        if (((i_1.b ^ edi_10.b) & 1) != 0)
0042c5f5        texture_path_1 = texture_b
0042c569        texture_path_1 = texture_b
0042c57c        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0042c583        face_second->uv[0].u = var_9c_1
0042c586        face_second->uv[0].v = var_7c_1
0042c58b        face_second->uv[1].u = var_80
0042c594        face_second->uv[1].v = var_7c_1
0042c59b        face_second->uv[2].u = var_80
0042c59e        face_second->uv[2].v = var_90_1
0042c5a3        face_second->uv[3].u = var_9c_1
0042c5a6        face_second->uv[3].v = var_90_1
0042c44b        int32_t ecx_72 = eax_83 * 0x30
0042c452        struct ObjectFaceQuad* face_first = ecx_72 + facequads
0042c455        __builtin_memset(face_first, 0, 2)
0042c45a        eax_83.w = self->width_cells.w
0042c45e        eax_83.w += 1
0042c465        face_first->vertex_0 = eax_83.w * edi_10.w + i_1.w
0042c469        ecx_72.w = self->width_cells.w
0042c46d        ecx_72.w += 1
0042c479        face_first->vertex_1 = ecx_72.w * edi_10.w + i_1.w + 1
0042c48a        face_first->vertex_2 = (self->width_cells.w + 1) * (edi_10.w + 1) + i_1.w + 1
0042c4a0        face_first->vertex_3 = (self->width_cells.w + 1) * (edi_10.w + 1) + i_1.w
0042c4a4        char* texture_path
0042c4a4        if (((i_1.b ^ edi_10.b) & 1) != 0)
0042c4f9        texture_path = texture_a
0042c4ad        texture_path = texture_a
0042c4c0        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0042c4c7        face_first->uv[0].u = var_80
0042c4ca        face_first->uv[0].v = var_7c_1
0042c4cf        face_first->uv[1].u = var_9c_1
0042c4d8        face_first->uv[1].v = var_7c_1
0042c4df        face_first->uv[2].u = var_9c_1
0042c4e2        face_first->uv[2].v = var_90_1
0042c4e7        face_first->uv[3].u = var_80
0042c4ea        face_first->uv[3].v = var_90_1
0042c5ae        bool cond:13_1 = var_94 + 1 s< 2
0042c5b1        var_94 += 1
0042c5b5        if (not(cond:13_1))
0042c5b5        break
0042c42d        ecx_70 = var_94
0042c5bb        i_1 += 1
0042c5c4        i_2 = i_1
0042c5c8        do while (i_1 s< self->width_cells)
0042c5d1        edi_10 += 1
0042c5d4        if (edi_10 s>= self->segment_count)
0042c5d4        break
0042c3be        i_1 = 0
0042c5dc        calc_path_length_z(self)
0042c5eb        return
