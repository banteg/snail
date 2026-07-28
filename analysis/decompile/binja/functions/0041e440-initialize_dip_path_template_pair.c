/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_dip_path_template_pair @ 0x41e440 */

0041e459        self->kind = PATH_TEMPLATE_KIND_DIP
0041e460        self->is_mirrored_x = 0
0041e464        self->side_exit_mode = 0
0041e467        self->width_cells = width_cells_
0041e46a        int16_t x87control
0041e46a        int32_t curve_count = ftol(x87control, fconvert.t(curve_source) * fconvert.t(5f))
0041e480        self->width_or_scale = 1f
0041e487        self->segment_count = curve_count + 2
0041e48e        self->segment_count_f = fconvert.s(float.t(curve_count + 2))
0041e491        long double x87_r7_3 = float.t(curve_count)
0041e49f        float profile_radius = fconvert.s(x87_r7_3 * fconvert.t(0.0477464832f))
0041e4a3        get_path_nodes(self)
0041e4a8        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041e4ab        self->has_entry_mesh_transition = 0
0041e4b2        primary_samples_2->center_x = 0f
0041e4bb        self->primary_samples->rotation_scalar_98 = 0f
0041e4c4        self->primary_samples->rotation_scalar_94 = 0f
0041e4cd        self->primary_samples->special_scalar = 0f
0041e4d6        self->primary_samples->lateral_scale = 1f
0041e4df        set_matrix_identity(self->primary_samples)
0041e4e4        struct PathTemplateSample* primary_samples = self->primary_samples
0041e4ed        primary_samples->transform.position.x = primary_samples->center_x
0041e4f3        self->primary_samples->transform.position.y = 0f
0041e4f9        self->primary_samples->transform.position.z = 0f
0041e4ff        set_matrix_identity(self->secondary_samples)
0041e514        self->secondary_samples->transform.position.x = self->primary_samples->center_x
0041e521        self->secondary_samples->transform.position.y = 0.49000001f
0041e52d        self->secondary_samples->transform.position.z = 0f
0041e539        (&self->primary_samples->center_x)[(curve_count + 1) * 0x2a] = 0
0041e543        (&self->primary_samples->rotation_scalar_98)[(curve_count + 1) * 0x2a] = 0
0041e54d        (&self->primary_samples->rotation_scalar_94)[(curve_count + 1) * 0x2a] = 0
0041e557        (&self->primary_samples->special_scalar)[(curve_count + 1) * 0x2a] = 0
0041e561        (&self->primary_samples->lateral_scale)[(curve_count + 1) * 0x2a] = 0x3f800000
0041e56f        set_matrix_identity(&self->primary_samples[curve_count + 1])
0041e574        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041e581        long double x87_r7_5 = float.t(curve_count + 1)
0041e585        (&primary_samples_3->transform.position)[(curve_count + 1) * 0xe].x = (&primary_samples_3->center_x)[(curve_count + 1) * 0x2a]
0041e591        (&self->primary_samples->transform.position.y)[(curve_count + 1) * 0x2a] = 0
0041e598        (&self->primary_samples->transform.position.z)[(curve_count + 1) * 0x2a] = fconvert.s(x87_r7_5)
0041e59f        set_matrix_identity(&self->secondary_samples[curve_count + 1])
0041e5b5        int32_t curve_sample_index = 0
0041e5b7        (&self->secondary_samples->transform.position)[(curve_count + 1) * 0xe].x = (&self->primary_samples->center_x)[(curve_count + 1) * 0x2a]
0041e5c2        int32_t curve_phase_index = 0
0041e5c6        (&self->secondary_samples->transform.position.y)[(curve_count + 1) * 0x2a] = 0x3efae148
0041e5d3        (&self->secondary_samples->transform.position.z)[(curve_count + 1) * 0x2a] = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)))
0041e5d7        if (curve_count s> 0)
0041e5dd        int32_t curve_sample_offset = 0xa8
0041e5ef        *(&self->primary_samples->center_x + curve_sample_offset) = 0
0041e5fd        *(&self->primary_samples->rotation_scalar_98 + curve_sample_offset) = 0
0041e607        *(&self->primary_samples->rotation_scalar_94 + curve_sample_offset) = 0
0041e611        *(&self->primary_samples->special_scalar + curve_sample_offset) = 0
0041e61b        *(&self->primary_samples->lateral_scale + curve_sample_offset) = 0x3f800000
0041e62b        float angle = fconvert.s(float.t(curve_phase_index) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(x87_r7_3)))
0041e62f        set_matrix_identity(self->primary_samples + curve_sample_offset)
0041e634        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041e646        *(&primary_samples_4->transform.position + curve_sample_offset) = *(&primary_samples_4->center_x + curve_sample_offset)
0041e65f        curve_sample_index += 1
0041e665        *(&self->primary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fneg((fconvert.t(1f) - cosine(angle)) * fconvert.t(profile_radius)))
0041e669        long double x87_r7_14 = float.t(curve_sample_index)
0041e674        *(&self->primary_samples->transform.position.z + curve_sample_offset) = fconvert.s(x87_r7_14)
0041e67f        set_matrix_identity(curve_sample_offset + self->secondary_samples)
0041e696        *(&self->secondary_samples->transform.position + curve_sample_offset) = *(&self->primary_samples->center_x + curve_sample_offset)
0041e6bb        *(&self->secondary_samples->transform.position.y + curve_sample_offset) = fconvert.s(fconvert.t(0.49000001f) - (fconvert.t(1f) - cosine(angle)) * fconvert.t(profile_radius))
0041e6c6        *(&self->secondary_samples->transform.position.z + curve_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_14)))
0041e6ca        if (curve_sample_offset s<= 0xa8)
0041e82d        set_matrix_rotation_identity(self->primary_samples + curve_sample_offset - 0xa8)
0041e83c        set_matrix_rotation_identity(curve_sample_offset + self->secondary_samples - 0xa8)
0041e703        *(self->primary_samples + curve_sample_offset - 0xa8) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0041e706        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0041e72a        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position.y + curve_sample_offset)) - fconvert.t(*(primary_samples_5 + curve_sample_offset - 0x74)))
0041e734        long double x87_r7_25 = fconvert.t(*(&primary_samples_5->transform.position.z + curve_sample_offset)) - fconvert.t(*(primary_samples_5 + curve_sample_offset - 0x70))
0041e73b        *(primary_samples_5 + curve_sample_offset - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position + curve_sample_offset)) - fconvert.t(*(primary_samples_5 + curve_sample_offset - 0x78)))
0041e73d        *(primary_samples_5 + curve_sample_offset - 0x84) = var_2c_1
0041e748        *(primary_samples_5 + curve_sample_offset - 0x80) = fconvert.s(x87_r7_25)
0041e755        normalize_vector(self->primary_samples + curve_sample_offset - 0x88)
0041e75d        void* eax_21 = self->primary_samples + curve_sample_offset
0041e775        cross_vectors(eax_21 - 0x98, eax_21 - 0x88, eax_21 - 0xa8)
0041e7ad        *(curve_sample_offset + self->secondary_samples - 0xa8) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0041e7b3        void* eax_24 = self->secondary_samples + curve_sample_offset
0041e7d1        float var_14_1 = fconvert.s(fconvert.t(*(eax_24 + 0x34)) - fconvert.t(*(eax_24 - 0x74)))
0041e7db        long double x87_r7_33 = fconvert.t(*(eax_24 + 0x38)) - fconvert.t(*(eax_24 - 0x70))
0041e7e2        *(eax_24 - 0x88) = fconvert.s(fconvert.t(*(eax_24 + 0x30)) - fconvert.t(*(eax_24 - 0x78)))
0041e7e4        *(eax_24 - 0x84) = var_14_1
0041e7ef        *(eax_24 - 0x80) = fconvert.s(x87_r7_33)
0041e7fc        normalize_vector(curve_sample_offset + self->secondary_samples - 0x88)
0041e804        void* eax_27 = self->secondary_samples + curve_sample_offset
0041e81c        cross_vectors(eax_27 - 0x98, eax_27 - 0x88, eax_27 - 0xa8)
0041e845        curve_sample_offset += 0xa8
0041e84d        curve_phase_index = curve_sample_index
0041e851        do while (curve_sample_index s< curve_count)
0041e85a        int32_t delta_index = 0
0041e85f        if (self->segment_count - 1 s> 0)
0041e865        int32_t delta_sample_offset = 0
0041e86a        void* eax_33 = self->primary_samples + delta_sample_offset
0041e888        float var_14_2 = fconvert.s(fconvert.t(*(eax_33 + 0xdc)) - fconvert.t(*(eax_33 + 0x34)))
0041e88f        long double x87_r7_41 = fconvert.t(*(eax_33 + 0xe0)) - fconvert.t(*(eax_33 + 0x38))
0041e896        *(eax_33 + 0x80) = fconvert.s(fconvert.t(*(eax_33 + 0xd8)) - fconvert.t(*(eax_33 + 0x30)))
0041e898        *(eax_33 + 0x84) = var_14_2
0041e8a3        *(eax_33 + 0x88) = fconvert.s(x87_r7_41)
0041e8b8        *(&self->primary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + delta_sample_offset))
0041e8bf        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041e8e3        float var_20_1 = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + delta_sample_offset)))
0041e8ea        long double x87_r7_48 = fconvert.t(*(delta_sample_offset + secondary_samples + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + delta_sample_offset))
0041e8f1        *(&secondary_samples->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + delta_sample_offset)))
0041e8f3        *(&secondary_samples->delta_dir_to_next.y + delta_sample_offset) = var_20_1
0041e8fe        *(&secondary_samples->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_48)
0041e913        delta_index += 1
0041e914        *(&self->secondary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + delta_sample_offset))
0041e91e        delta_sample_offset += 0xa8
0041e927        do while (delta_index s< self->segment_count - 1)
0041e97c        *(&self->primary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0041e98e        int32_t var_10_3 = 0x3f800000
0041e99a        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041e9c3        *(&self->secondary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0041e9d8        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041e9eb        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0041e9fd        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0041ea02        struct Object* object = self->bod.object
0041ea05        struct ObjectFaceQuad* facequads = object->facequads
0041ea08        struct Vec3* vertices = object->vertices
0041ea12        int32_t i = 0
0041ea1a        if (self->segment_count s>= 0)
0041ea20        int32_t ebx_1 = 0
0041ea22        uint32_t width_cells = self->width_cells
0041ea25        float curve_source_1 = 0f
0041ea29        curve_source = 0f
0041ea2d        width_cells_ = width_cells
0041ea31        if (width_cells s>= 0)
0041ea44        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041ea4d        long double x87_r7_51 = float.t(curve_source) - float.t(width_cells_) * fconvert.t(0.5f)
0041ea4f        if (i == self->segment_count)
0041eaac        void* eax_63 = primary_samples_1 + ebx_1
0041eb28        vertices[(width_cells + 1) * i i+ curve_source_1].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(*(eax_63 - 0x78)) + fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(*(eax_63 - 0xa8)))))
    .y = fconvert.s(fconvert.t(*(eax_63 - 0x74)) + fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(*(eax_63 - 0xa4)))))
    .z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_63 - 0x70)) + fconvert.t(1f))) + x87_r7_51 * fconvert.t(*(eax_63 - 0xa0)))
}
0041ea51        struct PathTemplateSample* primary_mesh_sample = primary_samples_1 + ebx_1
0041eaa7        vertices[(width_cells + 1) * i i+ curve_source_1].x.12 = struct Vec3 {
    .x = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
    .y = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
    .z = fconvert.s(x87_r7_51 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
}
0041eb2b        width_cells = self->width_cells
0041eb2e        curve_source_1 += 1
0041eb31        curve_source = curve_source_1
0041eb35        width_cells_ = width_cells
0041eb39        do while (curve_source_1 s<= width_cells)
0041eb42        i += 1
0041eb43        ebx_1 += 0xa8
0041eb4b        do while (i s<= self->segment_count)
0041eb54        int32_t i_1 = 0
0041eb58        if (self->segment_count s> 0)
0041eb61        int32_t j = 0
0041eb65        curve_source = 0f
0041eb69        if (self->width_cells s> 0)
0041eb71        int32_t eax_75 = i_1 & 0x80000007
0041eb76        if (eax_75 s< 0)
0041eb7c        eax_75 = ((eax_75 - 1) | 0xfffffff8) + 1
0041eb90        width_cells_ = fconvert.s(float.t(eax_75) * fconvert.t(0.125f))
0041eb9e        float var_4c = fconvert.s(float.t(eax_75 + 1) * fconvert.t(0.125f))
0041ebad        int32_t ecx_60 = 0
0041ebb3        int32_t var_48_1 = 0
0041ebbd        curve_source = fconvert.s(float.t(curve_source) * fconvert.t(0.125f))
0041ebcb        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041ebe1        while (true)
0041ebe1        int32_t eax_82 = ecx_60 + ((self->width_cells * i_1 + j) << 1)
0041ebe4        if (ecx_60 != 0)
0041eca0        struct ObjectFaceQuad* facequads_1 = facequads
0041ecab        struct ObjectFaceQuad* face_second = &facequads_1[eax_82]
0041ecae        __builtin_memset(face_second, 0, 2)
0041ecb4        ecx_60.w = self->width_cells.w
0041ecb8        ecx_60.w += 1
0041ecc1        face_second->vertex_0 = ecx_60.w * i_1.w + j.w + 1
0041ecc5        facequads_1.w = self->width_cells.w
0041ecc9        facequads_1.w += 1
0041ecd0        face_second->vertex_1 = facequads_1.w * i_1.w + j.w
0041ece2        face_second->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
0041ecfa        face_second->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
0041ecfe        char* texture_path_1
0041ecfe        if (((j.b ^ i_1.b) & 1) != 0)
0041ed90        texture_path_1 = texture_b
0041ed08        texture_path_1 = texture_b
0041ed1b        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0041ed22        face_second->uv[0].u = var_50_1
0041ed25        face_second->uv[0].v = width_cells_
0041ed2a        face_second->uv[1].u = curve_source
0041ed33        face_second->uv[1].v = width_cells_
0041ed3a        face_second->uv[2].u = curve_source
0041ed3d        face_second->uv[2].v = var_4c
0041ed42        face_second->uv[3].u = var_50_1
0041ed45        face_second->uv[3].v = var_4c
0041ebf1        int32_t ecx_62 = eax_82 * 0x30
0041ebf8        struct ObjectFaceQuad* face_first = ecx_62 + facequads
0041ebfb        __builtin_memset(face_first, 0, 2)
0041ec01        eax_82.w = self->width_cells.w
0041ec05        eax_82.w += 1
0041ec0c        face_first->vertex_0 = eax_82.w * i_1.w + j.w
0041ec10        ecx_62.w = self->width_cells.w
0041ec14        ecx_62.w += 1
0041ec20        face_first->vertex_1 = ecx_62.w * i_1.w + j.w + 1
0041ec31        face_first->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
0041ec47        face_first->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
0041ec4b        char* texture_path
0041ec4b        if (((j.b ^ i_1.b) & 1) != 0)
0041ec9a        texture_path = texture_a
0041ec51        texture_path = texture_a
0041ec64        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0041ec6b        face_first->uv[0].u = curve_source
0041ec6e        face_first->uv[0].v = width_cells_
0041ec73        face_first->uv[1].u = var_50_1
0041ec7c        face_first->uv[1].v = width_cells_
0041ec83        face_first->uv[2].u = var_50_1
0041ec86        face_first->uv[2].v = var_4c
0041ec8b        face_first->uv[3].u = curve_source
0041ec8e        face_first->uv[3].v = var_4c
0041ed4d        bool cond:12_1 = var_48_1 + 1 s< 2
0041ed50        var_48_1 += 1
0041ed54        if (not(cond:12_1))
0041ed54        break
0041ebd1        ecx_60 = var_48_1
0041ed5a        j += 1
0041ed63        curve_source = j
0041ed67        do while (j s< self->width_cells)
0041ed72        i_1 += 1
0041ed75        do while (i_1 s< self->segment_count)
0041ed7d        calc_path_length_z(self)
0041ed89        return
