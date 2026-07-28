/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_hump_path_template_pair @ 0x41d030 */

0041d046        int32_t i_2 = 0
0041d049        self->kind = PATH_TEMPLATE_KIND_FAMILY_10
0041d050        self->is_mirrored_x = 0
0041d054        self->side_exit_mode = 0
0041d057        self->width_cells = width_cells_
0041d05a        int16_t x87control
0041d05a        int32_t curve_count = ftol(x87control, fconvert.t(curve_source) * fconvert.t(4f))
0041d068        self->width_or_scale = 1f
0041d076        self->segment_count = curve_count + 0xe
0041d07d        self->segment_count_f = fconvert.s(float.t(curve_count + 0xe))
0041d080        long double x87_r7_3 = float.t(curve_count)
0041d08e        float profile_radius = fconvert.s(x87_r7_3 * fconvert.t(0.0954929665f))
0041d092        get_path_nodes(self)
0041d097        self->has_entry_mesh_transition = 0
0041d09d        int32_t approach_sample_index = 0
0041d0a1        int32_t approach_sample_offset = 0
0041d15c        while (approach_sample_offset s< 0x498)
0041d0b5        *(&self->primary_samples->center_x + approach_sample_offset) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
0041d0bf        *(&self->primary_samples->rotation_scalar_98 + approach_sample_offset) = 0
0041d0c9        *(&self->primary_samples->rotation_scalar_94 + approach_sample_offset) = 0
0041d0d3        *(&self->primary_samples->special_scalar + approach_sample_offset) = 0
0041d0dd        *(&self->primary_samples->lateral_scale + approach_sample_offset) = 0x3f800000
0041d0ed        set_matrix_identity(self->primary_samples + approach_sample_offset)
0041d0f5        void* eax_3 = self->primary_samples + approach_sample_offset
0041d0f7        long double x87_r7_8 = float.t(approach_sample_index)
0041d101        *(eax_3 + 0x30) = *(eax_3 + 0x90)
0041d10b        *(&self->primary_samples->transform.position.y + approach_sample_offset) = 0
0041d114        *(&self->primary_samples->transform.position.z + approach_sample_offset) = fconvert.s(x87_r7_8)
0041d11b        set_matrix_identity(approach_sample_offset + self->secondary_samples)
0041d131        *(&self->secondary_samples->transform.position + approach_sample_offset) = *(&self->primary_samples->center_x + approach_sample_offset)
0041d138        *(&self->secondary_samples->transform.position.y + approach_sample_offset) = 0x3efae148
0041d143        *(&self->secondary_samples->transform.position.z + approach_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_8)))
0041d14b        approach_sample_offset += 0xa8
0041d158        approach_sample_index += 1
0041d174        int32_t departure_index = curve_count + 7
0041d17b        int32_t departure_sample_offset = (curve_count + 7) * 0xa8
0041d23e        struct PathTemplateSample* secondary_samples
0041d23e        int32_t i
0041d196        *(&self->primary_samples->center_x + departure_sample_offset) = fconvert.s(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0041d1a0        *(&self->primary_samples->rotation_scalar_98 + departure_sample_offset) = 0
0041d1aa        *(&self->primary_samples->rotation_scalar_94 + departure_sample_offset) = 0
0041d1b4        *(&self->primary_samples->special_scalar + departure_sample_offset) = 0
0041d1be        *(&self->primary_samples->lateral_scale + departure_sample_offset) = 0x3f800000
0041d1ce        set_matrix_identity(self->primary_samples + departure_sample_offset)
0041d1d3        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041d1d6        long double x87_r7_13 = float.t(departure_index)
0041d1e8        *(&primary_samples_2->transform.position + departure_sample_offset) = *(&primary_samples_2->center_x + departure_sample_offset)
0041d1f0        *(&self->primary_samples->transform.position.y + departure_sample_offset) = 0
0041d1f7        *(&self->primary_samples->transform.position.z + departure_sample_offset) = fconvert.s(x87_r7_13)
0041d1fe        set_matrix_identity(departure_sample_offset + self->secondary_samples)
0041d214        *(&self->secondary_samples->transform.position + departure_sample_offset) = *(&self->primary_samples->center_x + departure_sample_offset)
0041d218        secondary_samples = self->secondary_samples
0041d21f        *(&secondary_samples->transform.position.y + departure_sample_offset) = 0x3efae148
0041d22a        *(&self->secondary_samples->transform.position.z + departure_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0041d22e        departure_sample_offset += 0xa8
0041d235        i = 0xfffffff9 - curve_count + departure_index + 1
0041d237        departure_index += 1
0041d23e        do while (i s< 7)
0041d248        int32_t curve_index = 0
0041d24e        if (curve_count s> 0)
0041d254        int32_t curve_sample_offset = 0x498
0041d4f5        int32_t eax_28
0041d25d        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041d260        struct PathTemplateSample* secondary_samples_3 = secondary_samples
0041d26b        float angle = fconvert.s(float.t(curve_index) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(x87_r7_3)))
0041d28a        *(&primary_samples_4->center_x + curve_sample_offset) = fconvert.s(cosine(fconvert.s(fconvert.t(angle) * fconvert.t(0.5f))) * fconvert.t(primary_samples_4->center_x))
0041d294        *(&self->primary_samples->rotation_scalar_98 + curve_sample_offset) = 0
0041d29e        *(&self->primary_samples->rotation_scalar_94 + curve_sample_offset) = 0
0041d2a8        *(&self->primary_samples->special_scalar + curve_sample_offset) = 0
0041d2b2        *(&self->primary_samples->lateral_scale + curve_sample_offset) = 0x3f800000
0041d2c2        set_matrix_identity(self->primary_samples + curve_sample_offset)
0041d2c7        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041d2d9        *(&primary_samples_3->transform.position + curve_sample_offset) = *(&primary_samples_3->center_x + curve_sample_offset)
0041d300        *(&self->primary_samples->transform.position.y + curve_sample_offset) = fconvert.s((fconvert.t(1f) - cosine(angle)) * fconvert.t(profile_radius) * fconvert.t(height_scale))
0041d304        long double x87_r7_26 = float.t(curve_index + 7)
0041d30f        *(&self->primary_samples->transform.position.z + curve_sample_offset) = fconvert.s(x87_r7_26)
0041d31a        set_matrix_identity(curve_sample_offset + self->secondary_samples)
0041d32d        *(&self->secondary_samples->transform.position + curve_sample_offset) = *(&self->primary_samples->center_x + curve_sample_offset)
0041d356        *(&self->secondary_samples->transform.position.y + curve_sample_offset) = fconvert.s((fconvert.t(1f) - cosine(angle)) * fconvert.t(profile_radius) * fconvert.t(height_scale) + fconvert.t(0.49000001f))
0041d361        *(&self->secondary_samples->transform.position.z + curve_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_26)))
0041d365        if (curve_sample_offset s<= 0x498)
0041d4cc        set_matrix_rotation_identity(self->primary_samples + curve_sample_offset - 0xa8)
0041d4db        set_matrix_rotation_identity(curve_sample_offset + self->secondary_samples - 0xa8)
0041d39e        *(self->primary_samples + curve_sample_offset - 0xa8) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0041d3a1        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041d3c5        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position.y + curve_sample_offset)) - fconvert.t(*(primary_samples_1 + curve_sample_offset - 0x74)))
0041d3cf        long double x87_r7_38 = fconvert.t(*(&primary_samples_1->transform.position.z + curve_sample_offset)) - fconvert.t(*(primary_samples_1 + curve_sample_offset - 0x70))
0041d3d6        *(primary_samples_1 + curve_sample_offset - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position + curve_sample_offset)) - fconvert.t(*(primary_samples_1 + curve_sample_offset - 0x78)))
0041d3d8        *(primary_samples_1 + curve_sample_offset - 0x84) = var_2c_1
0041d3e3        *(primary_samples_1 + curve_sample_offset - 0x80) = fconvert.s(x87_r7_38)
0041d3f0        normalize_vector(self->primary_samples + curve_sample_offset - 0x88)
0041d3fa        struct PathTemplateSample* primary_sample_cursor_reloaded = self->primary_samples + curve_sample_offset
0041d411        cross_vectors(primary_sample_cursor_reloaded - 0x98, primary_sample_cursor_reloaded - 0x88, primary_sample_cursor_reloaded - 0xa8)
0041d449        *(curve_sample_offset + self->secondary_samples - 0xa8) = struct Vec3 {
    .x = 0x3f800000
    .y = 0f
    .z = 0f
}
0041d44c        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
0041d470        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position.y + curve_sample_offset)) - fconvert.t(*(curve_sample_offset + secondary_samples_2 - 0x74)))
0041d47a        long double x87_r7_46 = fconvert.t(*(&secondary_samples_2->transform.position.z + curve_sample_offset)) - fconvert.t(*(curve_sample_offset + secondary_samples_2 - 0x70))
0041d481        *(curve_sample_offset + secondary_samples_2 - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position + curve_sample_offset)) - fconvert.t(*(curve_sample_offset + secondary_samples_2 - 0x78)))
0041d483        *(curve_sample_offset + secondary_samples_2 - 0x84) = var_14_1
0041d48e        *(curve_sample_offset + secondary_samples_2 - 0x80) = fconvert.s(x87_r7_46)
0041d49b        normalize_vector(curve_sample_offset + self->secondary_samples - 0x88)
0041d4a3        struct PathTemplateSample* secondary_sample_cursor_reloaded = self->secondary_samples + curve_sample_offset
0041d4bb        cross_vectors(secondary_sample_cursor_reloaded - 0x98, secondary_sample_cursor_reloaded - 0x88, secondary_sample_cursor_reloaded - 0xa8)
0041d4e9        curve_sample_offset += 0xa8
0041d4f1        curve_index = eax_28 + 1
0041d4f5        do while (eax_28 + 1 s< curve_count)
0041d4fe        int32_t delta_index = 0
0041d503        if (self->segment_count - 1 s> 0)
0041d509        int32_t delta_sample_offset = 0
0041d50e        void* eax_31 = self->primary_samples + delta_sample_offset
0041d52c        float var_14_2 = fconvert.s(fconvert.t(*(eax_31 + 0xdc)) - fconvert.t(*(eax_31 + 0x34)))
0041d533        long double x87_r7_54 = fconvert.t(*(eax_31 + 0xe0)) - fconvert.t(*(eax_31 + 0x38))
0041d53a        *(eax_31 + 0x80) = fconvert.s(fconvert.t(*(eax_31 + 0xd8)) - fconvert.t(*(eax_31 + 0x30)))
0041d53c        *(eax_31 + 0x84) = var_14_2
0041d547        *(eax_31 + 0x88) = fconvert.s(x87_r7_54)
0041d55c        *(&self->primary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + delta_sample_offset))
0041d563        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041d587        float var_20_1 = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + delta_sample_offset)))
0041d58e        long double x87_r7_61 = fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + delta_sample_offset))
0041d595        *(&secondary_samples_1->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + delta_sample_offset)))
0041d597        *(&secondary_samples_1->delta_dir_to_next.y + delta_sample_offset) = var_20_1
0041d5a2        *(&secondary_samples_1->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_61)
0041d5b7        delta_index += 1
0041d5b8        *(&self->secondary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + delta_sample_offset))
0041d5c2        delta_sample_offset += 0xa8
0041d5cb        do while (delta_index s< self->segment_count - 1)
0041d620        *(&self->primary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0041d632        int32_t var_10_3 = 0x3f800000
0041d63e        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041d667        *(&self->secondary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0041d67c        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041d68f        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0041d6a1        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0041d6a6        struct Object* object = self->bod.object
0041d6a9        int32_t i_1 = 0
0041d6ab        struct Vec3* vertices = object->vertices
0041d6ae        struct ObjectFaceQuad* facequads = object->facequads
0041d6b4        width_cells_ = vertices
0041d6be        if (self->segment_count s>= 0)
0041d6c4        uint32_t width_cells = self->width_cells
0041d6c7        float curve_source_1 = 0f
0041d6cb        curve_source = 0f
0041d6cf        height_scale = width_cells
0041d6d3        if (width_cells s>= 0)
0041d6e6        struct PathTemplateSample* primary_samples = self->primary_samples
0041d6ef        long double x87_r7_64 = float.t(curve_source) - float.t(height_scale) * fconvert.t(0.5f)
0041d6f1        int32_t* eax_57
0041d6f1        float ecx_65
0041d6f1        if (i_1 == self->segment_count)
0041d748        void* eax_58 = primary_samples + i_2
0041d759        vertices = width_cells_
0041d79e        float var_20_2 = fconvert.s(fconvert.t(*(eax_58 - 0x74)) + fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*(eax_58 - 0xa4)))))
0041d7a6        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_58 - 0x70)) + fconvert.t(1f))) + x87_r7_64 * fconvert.t(*(eax_58 - 0xa0))
0041d7a8        eax_57 = &vertices[(width_cells + 1) * i_1 i+ curve_source_1]
0041d7b0        *eax_57 = fconvert.s(fconvert.t(*(eax_58 - 0x78)) + fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*(eax_58 - 0xa8)))))
0041d7ba        eax_57[1] = var_20_2
0041d7bd        ecx_65 = fconvert.s(x87_r6_20)
0041d6f3        struct PathTemplateSample* primary_mesh_sample = primary_samples + i_2
0041d71b        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0041d728        float var_10_4 = fconvert.s(x87_r7_64 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0041d731        eax_57 = &vertices[(width_cells + 1) * i_1 i+ curve_source_1]
0041d739        *eax_57 = fconvert.s(fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0041d73f        eax_57[1] = var_14_3
0041d742        ecx_65 = var_10_4
0041d7c3        eax_57[2] = ecx_65
0041d7c6        width_cells = self->width_cells
0041d7c9        curve_source_1 += 1
0041d7ca        height_scale = width_cells
0041d7d0        curve_source = curve_source_1
0041d7d4        do while (curve_source_1 s<= width_cells)
0041d7dd        i_1 += 1
0041d7de        i_2 += 0xa8
0041d7e6        do while (i_1 s<= self->segment_count)
0041d7ec        i_2 = 0
0041d7f3        if (self->segment_count s> 0)
0041d7fc        int32_t j = 0
0041d800        curve_source = 0f
0041d804        if (self->width_cells s> 0)
0041d80c        float eax_66 = i_2 & 0x80000007
0041d811        if (eax_66 s< 0)
0041d817        eax_66 = ((eax_66 i- 1) | 0xfffffff8) + 1
0041d82b        height_scale = fconvert.s(float.t(eax_66) * fconvert.t(0.125f))
0041d839        float var_4c_1 = fconvert.s(float.t(eax_66 i+ 1) * fconvert.t(0.125f))
0041d844        int32_t ecx_69 = 0
0041d84a        int32_t var_48 = 0
0041d854        curve_source = fconvert.s(float.t(curve_source) * fconvert.t(0.125f))
0041d862        width_cells_ = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041d876        while (true)
0041d876        int32_t eax_73 = ecx_69 + ((self->width_cells * i_2 + j) << 1)
0041d879        if (ecx_69 != 0)
0041d935        struct ObjectFaceQuad* facequads_1 = facequads
0041d940        struct ObjectFaceQuad* face_second = &facequads_1[eax_73]
0041d943        __builtin_memset(face_second, 0, 2)
0041d949        ecx_69.w = self->width_cells.w
0041d94d        ecx_69.w += 1
0041d956        face_second->vertex_0 = ecx_69.w * i_2.w + j.w + 1
0041d95a        facequads_1.w = self->width_cells.w
0041d95e        facequads_1.w += 1
0041d965        face_second->vertex_1 = facequads_1.w * i_2.w + j.w
0041d977        face_second->vertex_2 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0041d98f        face_second->vertex_3 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0041d993        char* texture_path_1
0041d993        if (((j.b ^ i_2.b) & 1) != 0)
0041da23        texture_path_1 = texture_b
0041d99d        texture_path_1 = texture_b
0041d9b0        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0041d9b7        face_second->uv[0].u = width_cells_
0041d9ba        face_second->uv[0].v = height_scale
0041d9bf        face_second->uv[1].u = curve_source
0041d9c8        face_second->uv[1].v = height_scale
0041d9cf        face_second->uv[2].u = curve_source
0041d9d2        face_second->uv[2].v = var_4c_1
0041d9d7        face_second->uv[3].u = width_cells_
0041d9da        face_second->uv[3].v = var_4c_1
0041d886        int32_t ecx_71 = eax_73 * 0x30
0041d88d        struct ObjectFaceQuad* face_first = ecx_71 + facequads
0041d890        __builtin_memset(face_first, 0, 2)
0041d896        eax_73.w = self->width_cells.w
0041d89a        eax_73.w += 1
0041d8a1        face_first->vertex_0 = eax_73.w * i_2.w + j.w
0041d8a5        ecx_71.w = self->width_cells.w
0041d8a9        ecx_71.w += 1
0041d8b5        face_first->vertex_1 = ecx_71.w * i_2.w + j.w + 1
0041d8c6        face_first->vertex_2 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0041d8dc        face_first->vertex_3 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0041d8e0        char* texture_path
0041d8e0        if (((j.b ^ i_2.b) & 1) != 0)
0041d92f        texture_path = texture_a
0041d8e6        texture_path = texture_a
0041d8f9        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0041d900        face_first->uv[0].u = curve_source
0041d903        face_first->uv[0].v = height_scale
0041d908        face_first->uv[1].u = width_cells_
0041d911        face_first->uv[1].v = height_scale
0041d918        face_first->uv[2].u = width_cells_
0041d91b        face_first->uv[2].v = var_4c_1
0041d920        face_first->uv[3].u = curve_source
0041d923        face_first->uv[3].v = var_4c_1
0041d9e2        bool cond:12_1 = var_48 + 1 s< 2
0041d9e5        var_48 += 1
0041d9e9        if (not(cond:12_1))
0041d9e9        break
0041d868        ecx_69 = var_48
0041d9ef        j += 1
0041d9f8        curve_source = j
0041d9fc        do while (j s< self->width_cells)
0041da05        i_2 += 1
0041da08        do while (i_2 s< self->segment_count)
0041da10        calc_path_length_z(self)
0041da1c        return
