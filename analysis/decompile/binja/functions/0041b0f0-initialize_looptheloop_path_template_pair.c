/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_looptheloop_path_template_pair @ 0x41b0f0 */

0041b102        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0041b105        float loop_wiggle = 0f
0041b109        if (width_cells_ == 4)
0041b10b        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0041b10e        loop_wiggle = 0.300000012f
0041b120        self->is_mirrored_x = 0
0041b124        self->side_exit_mode = 0
0041b127        self->width_cells = width_cells_
0041b12f        int16_t x87control
0041b12f        int32_t curve_count = ftol(x87control, fconvert.t(curve_source) * fconvert.t(6.28318548f))
0041b145        self->width_or_scale = 1f
0041b148        self->segment_count = curve_count + 0xe
0041b14b        self->segment_count_f = fconvert.s(float.t(curve_count + 0xe))
0041b14e        long double x87_r7_3 = float.t(curve_count)
0041b152        float curve_count_f = fconvert.s(x87_r7_3)
0041b15c        float loop_radius = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
0041b160        get_path_nodes(self)
0041b165        self->has_entry_mesh_transition = 1
0041b16c        int32_t lead_sample_index = 0
0041b170        int32_t lead_sample_offset = 0
0041b252        while (lead_sample_offset s< 0x498)
0041b179        float lead_sample_z = fconvert.s(float.t(lead_sample_index))
0041b19c        *(&self->primary_samples->center_x + lead_sample_offset) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f) - fconvert.t(lead_sample_z) * fconvert.t(0.142857149f) * fconvert.t(loop_wiggle))
0041b1a6        *(&self->primary_samples->rotation_scalar_98 + lead_sample_offset) = 0
0041b1b0        *(&self->primary_samples->rotation_scalar_94 + lead_sample_offset) = 0
0041b1ba        *(&self->primary_samples->special_scalar + lead_sample_offset) = 0
0041b1c4        *(&self->primary_samples->lateral_scale + lead_sample_offset) = 0x3f800000
0041b1d2        set_matrix_identity(lead_sample_offset + self->primary_samples)
0041b1d7        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041b1e8        *(&primary_samples_3->transform.position + lead_sample_offset) = *(&primary_samples_3->center_x + lead_sample_offset)
0041b1ee        *(&self->primary_samples->transform.position.y + lead_sample_offset) = 0
0041b1f5        *(&self->primary_samples->transform.position.z + lead_sample_offset) = fconvert.s(fconvert.t(lead_sample_z))
0041b1fc        *(&self->primary_samples->delta_length + lead_sample_offset) = 0x3f800000
0041b20a        set_matrix_identity(lead_sample_offset + self->secondary_samples)
0041b220        *(&self->secondary_samples->transform.position + lead_sample_offset) = *(&self->primary_samples->center_x + lead_sample_offset)
0041b227        *(&self->secondary_samples->transform.position.y + lead_sample_offset) = 0x3efae148
0041b236        *(&self->secondary_samples->transform.position.z + lead_sample_offset) = fconvert.s(fconvert.t(lead_sample_z))
0041b23d        lead_sample_offset += 0xa8
0041b24a        *(lead_sample_offset + self->secondary_samples - 0x1c) = 0x3f800000
0041b24e        lead_sample_index += 1
0041b25e        int32_t tail_index = 0
0041b271        int32_t tail_sample_offset = (curve_count + 7) * 0xa8
0041b29c        *(&self->primary_samples->center_x + tail_sample_offset) = fconvert.s((fconvert.t(1f) - float.t(tail_index) * fconvert.t(0.166666672f)) * fconvert.t(loop_wiggle) + fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0041b2a6        *(&self->primary_samples->rotation_scalar_98 + tail_sample_offset) = 0
0041b2b0        *(&self->primary_samples->rotation_scalar_94 + tail_sample_offset) = 0
0041b2ba        *(&self->primary_samples->special_scalar + tail_sample_offset) = 0
0041b2c4        *(&self->primary_samples->lateral_scale + tail_sample_offset) = 0x3f800000
0041b2d6        set_matrix_identity(tail_sample_offset + self->primary_samples)
0041b2db        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041b2e8        *(&primary_samples_4->transform.position + tail_sample_offset) = *(&primary_samples_4->center_x + tail_sample_offset)
0041b2f5        *(&self->primary_samples->transform.position.y + tail_sample_offset) = 0
0041b2f9        long double x87_r7_17 = float.t(tail_index + 7)
0041b304        *(&self->primary_samples->transform.position.z + tail_sample_offset) = fconvert.s(x87_r7_17)
0041b30d        *(&self->primary_samples->delta_length + tail_sample_offset) = 0x3f800000
0041b31d        set_matrix_identity(tail_sample_offset + self->secondary_samples)
0041b334        *(&self->secondary_samples->transform.position + tail_sample_offset) = *(&self->primary_samples->center_x + tail_sample_offset)
0041b33b        tail_index += 1
0041b33f        *(&self->secondary_samples->transform.position.y + tail_sample_offset) = 0x3efae148
0041b34a        *(&self->secondary_samples->transform.position.z + tail_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_17)))
0041b351        tail_sample_offset += 0xa8
0041b35a        *(tail_sample_offset + self->secondary_samples - 0x1c) = 0x3f800000
0041b362        do while (tail_index s< 7)
0041b36c        int32_t curve_index = 0
0041b372        if (curve_count s> 0)
0041b3b7        float secondary_radius = fconvert.s(fconvert.t(loop_radius) - fconvert.t(0.49000001f))
0041b3cd        int32_t curve_sample_offset = 0x498
0041b5de        bool cond:4_1
0041b3d8        long double x87_r7_21 = float.t(curve_index)
0041b3dc        struct PathTemplateSample* primary_samples = self->primary_samples
0041b3df        int32_t var_68_1 = (curve_count + 0xe) * 0xa8
0041b3ec        float angle = fconvert.s(x87_r7_21 * fconvert.t(6.28318548f) / fconvert.t(curve_count_f))
0041b406        *(&primary_samples->center_x + curve_sample_offset) = fconvert.s((fconvert.t(*(&primary_samples[curve_count + 0xe] - 0x18)) - fconvert.t(primary_samples->center_x)) * x87_r7_21 / fconvert.t(curve_count_f) + fconvert.t(primary_samples->center_x))
0041b41c        float* ebx = &self->primary_samples->center_x + curve_sample_offset
0041b43a        *ebx = fconvert.s(sine(fconvert.s(fconvert.t(angle) * fconvert.t(0.5f) + fconvert.t(4.71238899f))) * fconvert.t(loop_wiggle) + fconvert.t(*ebx))
0041b43f        *(&self->primary_samples->rotation_scalar_98 + curve_sample_offset) = 0
0041b449        *(&self->primary_samples->rotation_scalar_94 + curve_sample_offset) = 0
0041b453        *(&self->primary_samples->special_scalar + curve_sample_offset) = 0
0041b45d        *(&self->primary_samples->lateral_scale + curve_sample_offset) = 0x3f800000
0041b46f        set_matrix_identity(curve_sample_offset + self->primary_samples)
0041b474        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0041b486        *(&primary_samples_5->transform.position + curve_sample_offset) = *(&primary_samples_5->center_x + curve_sample_offset)
0041b49c        *(&self->primary_samples->transform.position.z + curve_sample_offset) = fconvert.s(sine(angle) * fconvert.t(loop_radius) + fconvert.t(7f))
0041b4b5        *(&self->primary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fconvert.t(loop_radius) - cosine(angle) * fconvert.t(loop_radius))
0041b4bc        set_matrix_identity(curve_sample_offset + self->secondary_samples)
0041b4cf        *(&self->secondary_samples->transform.position + curve_sample_offset) = *(&self->primary_samples->center_x + curve_sample_offset)
0041b4e6        *(&self->secondary_samples->transform.position.z + curve_sample_offset) = fconvert.s(sine(angle) * fconvert.t(secondary_radius) + fconvert.t(7f))
0041b503        *(&self->secondary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fconvert.t(loop_radius) - cosine(angle) * fconvert.t(secondary_radius))
0041b51b        *(curve_sample_offset + self->primary_samples) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0041b521        *(&self->primary_samples->transform.basis_up + curve_sample_offset) = 0
0041b528        void* eax_26 = self->primary_samples + curve_sample_offset
0041b52d        *(eax_26 + 0x14) = fconvert.s(fconvert.t(loop_radius) - fconvert.t(*(eax_26 + 0x34)))
0041b530        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041b540        *(&primary_samples_2->transform.basis_up.z + curve_sample_offset) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&primary_samples_2->transform.position.z + curve_sample_offset)))
0041b54a        normalize_vector(&self->primary_samples->transform.basis_up + curve_sample_offset)
0041b552        struct Vec3* primary_right_reloaded = self->primary_samples + curve_sample_offset
0041b55e        cross_vectors(primary_right_reloaded + 0x20, primary_right_reloaded, primary_right_reloaded + 0x10)
0041b57f        *(curve_sample_offset + self->secondary_samples) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0041b585        *(&self->secondary_samples->transform.basis_up + curve_sample_offset) = 0
0041b589        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
0041b593        *(&secondary_samples_2->transform.basis_up.y + curve_sample_offset) = fconvert.s(fconvert.t(loop_radius) - fconvert.t(*(&secondary_samples_2->transform.position.y + curve_sample_offset)))
0041b596        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041b5a5        *(&secondary_samples->transform.basis_up.z + curve_sample_offset) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&secondary_samples->transform.position.z + curve_sample_offset)))
0041b5af        normalize_vector(&self->secondary_samples->transform.basis_up + curve_sample_offset)
0041b5b9        struct Vec3* secondary_right_reloaded = curve_sample_offset + self->secondary_samples
0041b5c4        cross_vectors(secondary_right_reloaded + 0x20, secondary_right_reloaded, secondary_right_reloaded + 0x10)
0041b5d2        curve_sample_offset += 0xa8
0041b5d8        cond:4_1 = curve_index + 1 s< curve_count
0041b5da        curve_index += 1
0041b5de        do while (cond:4_1)
0041b5e7        int32_t delta_index = 0
0041b5ec        if (self->segment_count - 1 s> 0)
0041b5f2        int32_t delta_sample_offset = 0
0041b5f7        void* eax_33 = self->primary_samples + delta_sample_offset
0041b615        float var_2c_1 = fconvert.s(fconvert.t(*(eax_33 + 0xdc)) - fconvert.t(*(eax_33 + 0x34)))
0041b61c        long double x87_r7_58 = fconvert.t(*(eax_33 + 0xe0)) - fconvert.t(*(eax_33 + 0x38))
0041b623        *(eax_33 + 0x80) = fconvert.s(fconvert.t(*(eax_33 + 0xd8)) - fconvert.t(*(eax_33 + 0x30)))
0041b625        *(eax_33 + 0x84) = var_2c_1
0041b630        *(eax_33 + 0x88) = fconvert.s(x87_r7_58)
0041b645        *(&self->primary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + delta_sample_offset))
0041b64c        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041b670        float var_38_1 = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + delta_sample_offset)))
0041b677        long double x87_r7_65 = fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + delta_sample_offset))
0041b67e        *(&secondary_samples_1->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + delta_sample_offset)))
0041b680        *(&secondary_samples_1->delta_dir_to_next.y + delta_sample_offset) = var_38_1
0041b68b        *(&secondary_samples_1->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_65)
0041b6a0        delta_index += 1
0041b6a1        *(&self->secondary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + delta_sample_offset))
0041b6ab        delta_sample_offset += 0xa8
0041b6b4        do while (delta_index s< self->segment_count - 1)
0041b709        *(&self->primary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0041b71b        int32_t var_28_2 = 0x3f800000
0041b727        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041b750        *(&self->secondary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0041b765        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041b778        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0041b78a        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0041b78f        struct Object* object = self->bod.object
0041b792        int32_t i = 0
0041b794        struct Vec3* vertices = object->vertices
0041b797        struct ObjectFaceQuad* facequads = object->facequads
0041b7a7        if (self->segment_count s>= 0)
0041b7ad        int32_t edx_34 = 0
0041b7af        int32_t var_48 = 0
0041b7b3        uint32_t width_cells = self->width_cells
0041b7b6        float curve_source_1 = 0f
0041b7ba        curve_source = 0f
0041b7be        width_cells_ = width_cells
0041b7c2        if (width_cells s>= 0)
0041b7d5        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041b7de        long double x87_r7_68 = float.t(curve_source) - float.t(width_cells_) * fconvert.t(0.5f)
0041b7e0        if (i == self->segment_count)
0041b840        void* eax_63 = primary_samples_1 + edx_34
0041b8b8        vertices[(width_cells + 1) * i i+ curve_source_1].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(*(eax_63 - 0x78)) + fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*(eax_63 - 0xa8)))))
    .y = fconvert.s(fconvert.t(*(eax_63 - 0x74)) + fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*(eax_63 - 0xa4)))))
    .z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_63 - 0x70)) + fconvert.t(1f))) + x87_r7_68 * fconvert.t(*(eax_63 - 0xa0)))
}
0041b8bb        edx_34 = var_48
0041b7e2        struct PathTemplateSample* primary_mesh_sample = primary_samples_1 + edx_34
0041b838        vertices[(width_cells + 1) * i i+ curve_source_1].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
    .y = fconvert.s(fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
    .z = fconvert.s(x87_r7_68 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
}
0041b8c1        width_cells = self->width_cells
0041b8c4        curve_source_1 += 1
0041b8c7        curve_source = curve_source_1
0041b8cb        width_cells_ = width_cells
0041b8cf        do while (curve_source_1 s<= width_cells)
0041b8d8        i += 1
0041b8d9        edx_34 += 0xa8
0041b8e1        var_48 = edx_34
0041b8e5        do while (i s<= self->segment_count)
0041b8ee        int32_t i_1 = 0
0041b8f2        if (self->segment_count s> 0)
0041b8fb        int32_t j = 0
0041b8ff        curve_source = 0f
0041b903        if (self->width_cells s> 0)
0041b90b        int32_t eax_74 = i_1 & 0x80000007
0041b910        if (eax_74 s< 0)
0041b916        eax_74 = ((eax_74 - 1) | 0xfffffff8) + 1
0041b92a        width_cells_ = fconvert.s(float.t(eax_74) * fconvert.t(0.125f))
0041b938        float var_54 = fconvert.s(float.t(eax_74 + 1) * fconvert.t(0.125f))
0041b947        int32_t ecx_63 = 0
0041b94d        int32_t var_48_1 = 0
0041b957        curve_source = fconvert.s(float.t(curve_source) * fconvert.t(0.125f))
0041b965        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041b97b        while (true)
0041b97b        int32_t eax_81 = ecx_63 + ((self->width_cells * i_1 + j) << 1)
0041b97e        if (ecx_63 != 0)
0041ba3a        struct ObjectFaceQuad* facequads_1 = facequads
0041ba45        struct ObjectFaceQuad* face_second = &facequads_1[eax_81]
0041ba48        __builtin_memset(face_second, 0, 2)
0041ba4e        ecx_63.w = self->width_cells.w
0041ba52        ecx_63.w += 1
0041ba5b        face_second->vertex_0 = ecx_63.w * i_1.w + j.w + 1
0041ba5f        facequads_1.w = self->width_cells.w
0041ba63        facequads_1.w += 1
0041ba6a        face_second->vertex_1 = facequads_1.w * i_1.w + j.w
0041ba7c        face_second->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
0041ba94        face_second->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
0041ba98        char* texture_path_1
0041ba98        if (((j.b ^ i_1.b) & 1) != 0)
0041bb30        texture_path_1 = texture_b
0041baa5        texture_path_1 = texture_b
0041bab8        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0041babf        face_second->uv[0].u = var_50_1
0041bac2        face_second->uv[0].v = width_cells_
0041bac7        face_second->uv[1].u = curve_source
0041bad0        face_second->uv[1].v = width_cells_
0041bad7        face_second->uv[2].u = curve_source
0041bada        face_second->uv[2].v = var_54
0041badf        face_second->uv[3].u = var_50_1
0041bae2        face_second->uv[3].v = var_54
0041b98b        int32_t ecx_65 = eax_81 * 0x30
0041b992        struct ObjectFaceQuad* face_first = ecx_65 + facequads
0041b995        __builtin_memset(face_first, 0, 2)
0041b99b        eax_81.w = self->width_cells.w
0041b99f        eax_81.w += 1
0041b9a6        face_first->vertex_0 = eax_81.w * i_1.w + j.w
0041b9aa        ecx_65.w = self->width_cells.w
0041b9ae        ecx_65.w += 1
0041b9ba        face_first->vertex_1 = ecx_65.w * i_1.w + j.w + 1
0041b9cb        face_first->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
0041b9e1        face_first->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
0041b9e5        char* texture_path
0041b9e5        if (((j.b ^ i_1.b) & 1) != 0)
0041ba34        texture_path = texture_a
0041b9eb        texture_path = texture_a
0041b9fe        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0041ba05        face_first->uv[0].u = curve_source
0041ba08        face_first->uv[0].v = width_cells_
0041ba0d        face_first->uv[1].u = var_50_1
0041ba16        face_first->uv[1].v = width_cells_
0041ba1d        face_first->uv[2].u = var_50_1
0041ba20        face_first->uv[2].v = var_54
0041ba25        face_first->uv[3].u = curve_source
0041ba28        face_first->uv[3].v = var_54
0041baea        bool cond:14_1 = var_48_1 + 1 s< 2
0041baed        var_48_1 += 1
0041baf1        if (not(cond:14_1))
0041baf1        break
0041b96b        ecx_63 = var_48_1
0041baf7        j += 1
0041bb00        curve_source = j
0041bb04        do while (j s< self->width_cells)
0041bb0f        i_1 += 1
0041bb12        do while (i_1 s< self->segment_count)
0041bb1a        calc_path_length_z(self)
0041bb26        return
