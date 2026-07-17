/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sbend_path_template_pair @ 0x42df00 */

0042df17        int32_t edi = 0
0042df19        self->kind = PATH_TEMPLATE_KIND_FAMILY_10
0042df20        self->is_mirrored_x = 0
0042df24        self->side_exit_mode = 0
0042df27        self->width_cells = width_cells_
0042df2a        int16_t x87control
0042df2a        int32_t eax_1 = ftol(x87control, fconvert.t(height) * fconvert.t(3.14159274f))
0042df3f        self->width_or_scale = 1f
0042df46        self->segment_count = eax_1 + 1
0042df4d        self->segment_count_f = fconvert.s(float.t(eax_1 + 1))
0042df50        allocate_path_template_samples(self)
0042df59        self->has_entry_mesh_transition = 0
0042df62        if (centered == 0)
0042df81        self->primary_samples->center_x = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
0042df67        self->primary_samples->center_x = 0f
0042df8a        self->primary_samples->rotation_scalar_98 = 0f
0042df93        self->primary_samples->rotation_scalar_94 = 0f
0042df9c        self->primary_samples->special_scalar = 0f
0042dfa5        self->primary_samples->lateral_scale = 1f
0042dfae        set_matrix_identity(self->primary_samples)
0042dfb3        struct PathTemplateSample* primary_samples = self->primary_samples
0042dfbc        primary_samples->transform.position.x = primary_samples->center_x
0042dfc2        self->primary_samples->transform.position.y = 0f
0042dfc8        self->primary_samples->transform.position.z = 0f
0042dfce        set_matrix_identity(self->secondary_samples)
0042dfdb        centered.d = 0
0042dfe5        self->secondary_samples->transform.position.x = self->primary_samples->center_x
0042dfeb        self->secondary_samples->transform.position.y = 0.49000001f
0042dff5        self->secondary_samples->transform.position.z = 0f
0042dff8        if (eax_1 s> 0)
0042e01a        int32_t ebx_1 = 0xa8
0042e1e1        bool cond:2_1
0042e02b        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042e03a        *(&primary_samples_1->center_x + ebx_1) = primary_samples_1->center_x
0042e048        *(&self->primary_samples->rotation_scalar_98 + ebx_1) = 0
0042e052        *(&self->primary_samples->rotation_scalar_94 + ebx_1) = 0
0042e05c        *(&self->primary_samples->special_scalar + ebx_1) = 0
0042e066        *(&self->primary_samples->lateral_scale + ebx_1) = 0x3f800000
0042e072        width_cells_ = fconvert.s(float.t(centered.d) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(float.t(eax_1))))
0042e076        set_matrix_identity(self->primary_samples + ebx_1)
0042e07b        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042e082        int32_t ecx_12 = *(&primary_samples_2->center_x + ebx_1)
0042e091        int32_t var_5c_1 = ecx_12
0042e092        *(&primary_samples_2->transform.position + ebx_1) = ecx_12
0042e0b0        *(&self->primary_samples->transform.position.y + ebx_1) = fconvert.s((fconvert.t(1f) - cosine(fconvert.s(fconvert.t(width_cells_) * fconvert.t(0.5f)))) * fconvert.t(0.5f) * fconvert.t(height))
0042e0e8        *(&self->primary_samples->transform.position.z + ebx_1) = fconvert.s((fconvert.t(1f) - cosine(fconvert.s(fconvert.t(width_cells_) * fconvert.t(1.5f)))) * fconvert.t(0.5f) * fconvert.t(z_amplitude) * fconvert.t(0.333333343f) + fconvert.t(1f))
0042e0f3        int32_t* edx_9 = &self->primary_samples->transform.basis_up + ebx_1
0042e0fb        *edx_9 = 0x3f800000
0042e101        edx_9[1] = 0
0042e104        edx_9[2] = 0
0042e107        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042e129        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position.y + ebx_1)) - fconvert.t(*(primary_samples_5 + ebx_1 - 0x74)))
0042e130        long double x87_r7_29 = fconvert.t(*(&primary_samples_5->transform.position.z + ebx_1)) - fconvert.t(*(primary_samples_5 + ebx_1 - 0x70))
0042e13a        *(&primary_samples_5->transform.basis_forward + ebx_1) = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position + ebx_1)) - fconvert.t(*(primary_samples_5 + ebx_1 - 0x78)))
0042e13c        *(&primary_samples_5->transform.basis_forward.y + ebx_1) = var_2c_1
0042e147        *(&primary_samples_5->transform.basis_forward.z + ebx_1) = fconvert.s(x87_r7_29)
0042e151        normalize_vector(&self->primary_samples->transform.basis_forward + ebx_1)
0042e15b        struct Vec3* rhs = self->primary_samples + ebx_1
0042e166        cross_vectors(rhs + 0x10, rhs + 0x20, rhs)
0042e17a        __builtin_memcpy(self->secondary_samples + ebx_1, self->primary_samples + ebx_1, 0x40)
0042e17c        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042e18b        long double x87_r7_33 = fconvert.t(*(&primary_samples_3->transform.basis_up + ebx_1)) * fconvert.t(0.49000001f)
0042e19f        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_3->transform.basis_up.y + ebx_1)) * fconvert.t(0.49000001f))
0042e1a6        long double x87_r6_4 = fconvert.t(*(&primary_samples_3->transform.basis_up.z + ebx_1)) * fconvert.t(0.49000001f)
0042e1ac        float* eax_16 = &self->secondary_samples->transform.position + ebx_1
0042e1b4        ebx_1 += 0xa8
0042e1c0        *eax_16 = fconvert.s(x87_r7_33 + fconvert.t(*eax_16))
0042e1c9        eax_16[1] = fconvert.s(fconvert.t(var_20_1) + fconvert.t(eax_16[1]))
0042e1d3        eax_16[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_4)) + fconvert.t(eax_16[2]))
0042e1db        cond:2_1 = centered.d + 1 s< eax_1
0042e1dd        centered.d += 1
0042e1e1        do while (cond:2_1)
0042e1e7        edi = 0
0042e1ec        int32_t i = 0
0042e1f1        if (self->segment_count - 1 s> 0)
0042e1fa        void* eax_20 = self->primary_samples + edi
0042e218        float var_2c_2 = fconvert.s(fconvert.t(*(eax_20 + 0xdc)) - fconvert.t(*(eax_20 + 0x34)))
0042e21f        long double x87_r7_44 = fconvert.t(*(eax_20 + 0xe0)) - fconvert.t(*(eax_20 + 0x38))
0042e226        *(eax_20 + 0x80) = fconvert.s(fconvert.t(*(eax_20 + 0xd8)) - fconvert.t(*(eax_20 + 0x30)))
0042e228        *(eax_20 + 0x84) = var_2c_2
0042e233        *(eax_20 + 0x88) = fconvert.s(x87_r7_44)
0042e248        *(&self->primary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi))
0042e24f        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042e273        float var_38_1 = fconvert.s(fconvert.t(*(secondary_samples + edi + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + edi)))
0042e27a        long double x87_r7_51 = fconvert.t(*(secondary_samples + edi + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + edi))
0042e281        *(&secondary_samples->delta_dir_to_next + edi) = fconvert.s(fconvert.t(*(secondary_samples + edi + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + edi)))
0042e283        *(&secondary_samples->delta_dir_to_next.y + edi) = var_38_1
0042e28e        *(&secondary_samples->delta_dir_to_next.z + edi) = fconvert.s(x87_r7_51)
0042e2a3        i += 1
0042e2a4        *(&self->secondary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi))
0042e2ae        edi += 0xa8
0042e2b7        do while (i s< self->segment_count - 1)
0042e2e7        int32_t* edx_21 = &self->primary_samples[self->segment_count] - 0x28
0042e2fb        *edx_21 = 0
0042e311        edx_21[1] = 0
0042e314        edx_21[2] = 0x3f800000
0042e329        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042e33f        int32_t* edx_23 = &self->secondary_samples[self->segment_count] - 0x28
0042e34b        *edx_23 = 0
0042e351        edx_23[1] = 0
0042e354        edx_23[2] = 0x3f800000
0042e369        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042e37c        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042e38e        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042e393        struct Object* object = self->bod.object
0042e396        int32_t i_1 = 0
0042e398        struct Vec3* vertices = object->vertices
0042e39b        struct ObjectFaceQuad* facequads = object->facequads
0042e3a7        width_cells_ = vertices
0042e3ab        if (self->segment_count s>= 0)
0042e3b1        int32_t ebx_2 = 0
0042e3b3        uint32_t width_cells = self->width_cells
0042e3b6        int32_t edi_3 = 0
0042e3ba        centered.d = 0
0042e3be        height = width_cells
0042e3c2        if (width_cells s>= 0)
0042e3d5        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042e3de        long double x87_r7_54 = float.t(centered.d) - float.t(height) * fconvert.t(0.5f)
0042e3e0        int32_t* eax_45
0042e3e0        float ecx_41
0042e3e0        if (i_1 == self->segment_count)
0042e436        void* eax_46 = primary_samples_4 + ebx_2
0042e447        vertices = width_cells_
0042e48c        float var_38_2 = fconvert.s(fconvert.t(*(eax_46 - 0x74)) + fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(*(eax_46 - 0xa4)))))
0042e494        long double x87_r6_24 = fconvert.t(fconvert.s(fconvert.t(*(eax_46 - 0x70)) + fconvert.t(1f))) + x87_r7_54 * fconvert.t(*(eax_46 - 0xa0))
0042e496        eax_45 = &vertices[(width_cells + 1) * i_1 + edi_3]
0042e49d        *eax_45 = fconvert.s(fconvert.t(*(eax_46 - 0x78)) + fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(*(eax_46 - 0xa8)))))
0042e4a7        eax_45[1] = var_38_2
0042e4aa        ecx_41 = fconvert.s(x87_r6_24)
0042e3e2        float* eax_41 = primary_samples_4 + ebx_2
0042e40a        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(eax_41[1]))) + fconvert.t(eax_41[0xd]))
0042e417        float var_28_3 = fconvert.s(x87_r7_54 * fconvert.t(eax_41[2]) + fconvert.t(eax_41[0xe]))
0042e420        eax_45 = &vertices[(width_cells + 1) * i_1 + edi_3]
0042e427        *eax_45 = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(*eax_41))) + fconvert.t(eax_41[0xc]))
0042e42d        eax_45[1] = var_2c_3
0042e430        ecx_41 = var_28_3
0042e4b0        eax_45[2] = ecx_41
0042e4b3        width_cells = self->width_cells
0042e4b6        edi_3 += 1
0042e4b7        height = width_cells
0042e4bd        centered.d = edi_3
0042e4c1        do while (edi_3 s<= width_cells)
0042e4ca        i_1 += 1
0042e4cb        ebx_2 += 0xa8
0042e4d3        do while (i_1 s<= self->segment_count)
0042e4dc        int32_t i_2 = 0
0042e4e0        if (self->segment_count s> 0)
0042e4e9        int32_t j = 0
0042e4ed        centered.d = 0
0042e4f1        if (self->width_cells s> 0)
0042e4f9        float eax_54 = i_2 & 0x80000007
0042e4fe        if (eax_54 s< 0)
0042e504        eax_54 = ((eax_54 i- 1) | 0xfffffff8) + 1
0042e518        height = fconvert.s(float.t(eax_54) * fconvert.t(0.125f))
0042e526        z_amplitude = fconvert.s(float.t(eax_54 i+ 1) * fconvert.t(0.125f))
0042e531        int32_t ecx_45 = 0
0042e537        int32_t var_48_1 = 0
0042e541        centered.d = fconvert.s(float.t(centered.d) * fconvert.t(0.125f))
0042e54f        width_cells_ = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042e563        while (true)
0042e563        int32_t eax_61 = ecx_45 + ((self->width_cells * i_2 + j) << 1)
0042e566        if (ecx_45 != 0)
0042e621        struct ObjectFaceQuad* facequads_1 = facequads
0042e62c        int16_t* ebx_4 = &facequads_1[eax_61]
0042e62f        *ebx_4 = 0
0042e634        ecx_45.w = self->width_cells.w
0042e638        ecx_45.w += 1
0042e641        ebx_4[1] = ecx_45.w * i_2.w + j.w + 1
0042e645        facequads_1.w = self->width_cells.w
0042e649        facequads_1.w += 1
0042e650        ebx_4[2] = facequads_1.w * i_2.w + j.w
0042e662        ebx_4[3] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0042e67a        ebx_4[4] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0042e67e        char* texture_path_1
0042e67e        if (((j.b ^ i_2.b) & 1) != 0)
0042e70e        texture_path_1 = texture_b
0042e688        texture_path_1 = texture_b
0042e697        int32_t edx_42 = centered.d
0042e69b        *(ebx_4 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path_1, 0, 0)
0042e6a2        *(ebx_4 + 0x10) = width_cells_
0042e6a5        *(ebx_4 + 0x14) = height
0042e6aa        *(ebx_4 + 0x18) = edx_42
0042e6b3        *(ebx_4 + 0x1c) = height
0042e6ba        *(ebx_4 + 0x20) = edx_42
0042e6bd        *(ebx_4 + 0x24) = z_amplitude
0042e6c2        *(ebx_4 + 0x28) = width_cells_
0042e6c5        *(ebx_4 + 0x2c) = z_amplitude
0042e573        int32_t ecx_47 = eax_61 * 0x30
0042e57a        int16_t* ebx_3 = ecx_47 + facequads
0042e57d        *ebx_3 = 0
0042e582        eax_61.w = self->width_cells.w
0042e586        eax_61.w += 1
0042e58d        ebx_3[1] = eax_61.w * i_2.w + j.w
0042e591        ecx_47.w = self->width_cells.w
0042e595        ecx_47.w += 1
0042e5a1        ebx_3[2] = ecx_47.w * i_2.w + j.w + 1
0042e5b2        ebx_3[3] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0042e5c8        ebx_3[4] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0042e5cc        char* texture_path
0042e5cc        if (((j.b ^ i_2.b) & 1) != 0)
0042e61b        texture_path = texture_a
0042e5d2        texture_path = texture_a
0042e5e5        *(ebx_3 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
0042e5ec        *(ebx_3 + 0x10) = centered.d
0042e5ef        *(ebx_3 + 0x14) = height
0042e5f4        *(ebx_3 + 0x18) = width_cells_
0042e5fd        *(ebx_3 + 0x1c) = height
0042e604        *(ebx_3 + 0x20) = width_cells_
0042e607        *(ebx_3 + 0x24) = z_amplitude
0042e60c        *(ebx_3 + 0x28) = centered.d
0042e60f        *(ebx_3 + 0x2c) = z_amplitude
0042e6cd        bool cond:11_1 = var_48_1 + 1 s< 2
0042e6d0        var_48_1 += 1
0042e6d4        if (not(cond:11_1))
0042e6d4        break
0042e555        ecx_45 = var_48_1
0042e6da        j += 1
0042e6e3        centered.d = j
0042e6e7        do while (j s< self->width_cells)
0042e6f0        i_2 += 1
0042e6f3        do while (i_2 s< self->segment_count)
0042e6fb        finalize_path_template(self)
0042e707        return
