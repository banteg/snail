/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_dip_path_template_pair @ 0x41e440 */

0041e459        self->kind = PATH_TEMPLATE_KIND_CAGE2
0041e460        self->is_mirrored_x = 0
0041e464        self->side_exit_mode = 0
0041e467        self->width_cells = arg3
0041e46a        int16_t x87control
0041e46a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(5f))
0041e480        self->width_or_scale = 1f
0041e487        self->segment_count = eax_1 + 2
0041e48e        self->segment_count_f = fconvert.s(float.t(eax_1 + 2))
0041e491        long double x87_r7_3 = float.t(eax_1)
0041e49f        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.0477464832f))
0041e4a3        allocate_path_template_samples(self)
0041e4a8        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041e4ab        self->special_runtime_flag_9c = 0
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
0041e539        (&self->primary_samples->center_x)[(eax_1 + 1) * 0x2a] = 0
0041e543        (&self->primary_samples->rotation_scalar_98)[(eax_1 + 1) * 0x2a] = 0
0041e54d        (&self->primary_samples->rotation_scalar_94)[(eax_1 + 1) * 0x2a] = 0
0041e557        (&self->primary_samples->special_scalar)[(eax_1 + 1) * 0x2a] = 0
0041e561        (&self->primary_samples->lateral_scale)[(eax_1 + 1) * 0x2a] = 0x3f800000
0041e56f        set_matrix_identity(&self->primary_samples[eax_1 + 1])
0041e574        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041e581        long double x87_r7_5 = float.t(eax_1 + 1)
0041e585        primary_samples_3[eax_1 + 1].transform.position.x = (&primary_samples_3->center_x)[(eax_1 + 1) * 0x2a]
0041e591        (&self->primary_samples->transform.position.y)[(eax_1 + 1) * 0x2a] = 0
0041e598        (&self->primary_samples->transform.position.z)[(eax_1 + 1) * 0x2a] = fconvert.s(x87_r7_5)
0041e59f        set_matrix_identity(&self->secondary_samples[eax_1 + 1])
0041e5b5        int32_t ebx_1 = 0
0041e5b7        self->secondary_samples[eax_1 + 1].transform.position.x = (&self->primary_samples->center_x)[(eax_1 + 1) * 0x2a]
0041e5c2        int32_t var_4c = 0
0041e5c6        (&self->secondary_samples->transform.position.y)[(eax_1 + 1) * 0x2a] = 0x3efae148
0041e5d3        (&self->secondary_samples->transform.position.z)[(eax_1 + 1) * 0x2a] = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)))
0041e5d7        if (eax_1 s> 0)
0041e5dd        void* edi_3 = 0xa8
0041e5ef        *(&self->primary_samples->center_x + edi_3) = 0
0041e5fd        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041e607        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041e611        *(&self->primary_samples->special_scalar + edi_3) = 0
0041e61b        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041e62b        float var_4c_1 = fconvert.s(float.t(var_4c) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(x87_r7_3)))
0041e62f        set_matrix_identity(self->primary_samples + edi_3)
0041e634        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041e646        *(&primary_samples_4->transform.position + edi_3) = *(&primary_samples_4->center_x + edi_3)
0041e65a        ebx_1 += 1
0041e665        *(&self->primary_samples->transform.position.y + edi_3) = fconvert.s(fneg((fconvert.t(1f) - cosine(var_4c_1)) * fconvert.t(arg2)))
0041e669        long double x87_r7_14 = float.t(ebx_1)
0041e674        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_14)
0041e67f        set_matrix_identity(edi_3 + self->secondary_samples)
0041e696        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0041e6bb        *(&self->secondary_samples->transform.position.y + edi_3) = fconvert.s(fconvert.t(0.49000001f) - (fconvert.t(1f) - cosine(var_4c_1)) * fconvert.t(arg2))
0041e6c6        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_14)))
0041e6ca        if (edi_3 s<= 0xa8)
0041e82d        set_matrix_rotation_identity(self->primary_samples + edi_3 - 0xa8)
0041e83c        set_matrix_rotation_identity(edi_3 + self->secondary_samples - 0xa8)
0041e6e7        int32_t* eax_20 = self->primary_samples + edi_3 - 0xa8
0041e6fa        *eax_20 = 0x3f800000
0041e700        eax_20[1] = 0
0041e703        eax_20[2] = 0
0041e706        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0041e72a        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position.y + edi_3)) - fconvert.t(*(primary_samples_5 + edi_3 - 0x74)))
0041e734        long double x87_r7_25 = fconvert.t(*(&primary_samples_5->transform.position.z + edi_3)) - fconvert.t(*(primary_samples_5 + edi_3 - 0x70))
0041e73b        *(primary_samples_5 + edi_3 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position + edi_3)) - fconvert.t(*(primary_samples_5 + edi_3 - 0x78)))
0041e73d        *(primary_samples_5 + edi_3 - 0x84) = var_2c_1
0041e748        *(primary_samples_5 + edi_3 - 0x80) = fconvert.s(x87_r7_25)
0041e755        normalize_vector(self->primary_samples + edi_3 - 0x88)
0041e75d        void* eax_24 = self->primary_samples + edi_3
0041e775        cross_vectors(eax_24 - 0x98, eax_24 - 0x88, eax_24 - 0xa8)
0041e791        int32_t* ecx_31 = edi_3 + self->secondary_samples - 0xa8
0041e7a4        *ecx_31 = 0x3f800000
0041e7aa        ecx_31[1] = 0
0041e7ad        ecx_31[2] = 0
0041e7b3        void* eax_27 = self->secondary_samples + edi_3
0041e7d1        float var_14_1 = fconvert.s(fconvert.t(*(eax_27 + 0x34)) - fconvert.t(*(eax_27 - 0x74)))
0041e7db        long double x87_r7_33 = fconvert.t(*(eax_27 + 0x38)) - fconvert.t(*(eax_27 - 0x70))
0041e7e2        *(eax_27 - 0x88) = fconvert.s(fconvert.t(*(eax_27 + 0x30)) - fconvert.t(*(eax_27 - 0x78)))
0041e7e4        *(eax_27 - 0x84) = var_14_1
0041e7ef        *(eax_27 - 0x80) = fconvert.s(x87_r7_33)
0041e7fc        normalize_vector(edi_3 + self->secondary_samples - 0x88)
0041e804        void* eax_30 = self->secondary_samples + edi_3
0041e81c        cross_vectors(eax_30 - 0x98, eax_30 - 0x88, eax_30 - 0xa8)
0041e845        edi_3 += 0xa8
0041e84d        var_4c = ebx_1
0041e851        do while (ebx_1 s< eax_1)
0041e85a        int32_t i = 0
0041e85f        if (self->segment_count - 1 s> 0)
0041e865        void* edi_4 = nullptr
0041e86a        void* eax_34 = self->primary_samples + edi_4
0041e888        float var_14_2 = fconvert.s(fconvert.t(*(eax_34 + 0xdc)) - fconvert.t(*(eax_34 + 0x34)))
0041e88f        long double x87_r7_41 = fconvert.t(*(eax_34 + 0xe0)) - fconvert.t(*(eax_34 + 0x38))
0041e896        *(eax_34 + 0x80) = fconvert.s(fconvert.t(*(eax_34 + 0xd8)) - fconvert.t(*(eax_34 + 0x30)))
0041e898        *(eax_34 + 0x84) = var_14_2
0041e8a3        *(eax_34 + 0x88) = fconvert.s(x87_r7_41)
0041e8b8        *(&self->primary_samples->delta_length + edi_4) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_4))
0041e8bf        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041e8e3        float var_20_1 = fconvert.s(fconvert.t(*(edi_4 + secondary_samples + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + edi_4)))
0041e8ea        long double x87_r7_48 = fconvert.t(*(edi_4 + secondary_samples + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + edi_4))
0041e8f1        *(&secondary_samples->delta_dir_to_next + edi_4) = fconvert.s(fconvert.t(*(edi_4 + secondary_samples + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + edi_4)))
0041e8f3        *(&secondary_samples->delta_dir_to_next.y + edi_4) = var_20_1
0041e8fe        *(&secondary_samples->delta_dir_to_next.z + edi_4) = fconvert.s(x87_r7_48)
0041e913        i += 1
0041e914        *(&self->secondary_samples->delta_length + edi_4) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_4))
0041e91e        edi_4 += 0xa8
0041e927        do while (i s< self->segment_count - 1)
0041e957        int32_t* edx_29 = &self->primary_samples[self->segment_count] - 0x28
0041e96b        *edx_29 = 0
0041e979        edx_29[1] = 0
0041e97c        edx_29[2] = 0x3f800000
0041e98e        int32_t var_10_3 = 0x3f800000
0041e99a        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041e9b0        int32_t* ecx_52 = &self->secondary_samples[self->segment_count] - 0x28
0041e9b8        *ecx_52 = 0
0041e9be        ecx_52[1] = 0
0041e9c3        ecx_52[2] = 0x3f800000
0041e9d8        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041e9eb        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0041e9fd        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0041ea02        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0041ea05        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0041ea08        struct Vec3* vertices = strip_mesh->vertices
0041ea12        int32_t i_1 = 0
0041ea1a        if (self->segment_count s>= 0)
0041ea20        int32_t ebx_2 = 0
0041ea22        uint32_t width_cells = self->width_cells
0041ea25        float edi_5 = 0f
0041ea29        arg2 = 0f
0041ea2d        arg3 = width_cells
0041ea31        if (width_cells s>= 0)
0041ea44        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041ea4d        long double x87_r7_51 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041ea4f        if (i_1 == self->segment_count)
0041eaac        void* eax_65 = primary_samples_1 + ebx_2
0041eb04        float var_20_2 = fconvert.s(fconvert.t(*(eax_65 - 0x74)) + fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(*(eax_65 - 0xa4)))))
0041eb0c        int32_t* ecx_63 = &vertices[(width_cells + 1) * i_1 i+ edi_5]
0041eb13        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_65 - 0x70)) + fconvert.t(1f))) + x87_r7_51 * fconvert.t(*(eax_65 - 0xa0))
0041eb15        *ecx_63 = fconvert.s(fconvert.t(*(eax_65 - 0x78)) + fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(*(eax_65 - 0xa8)))))
0041eb1b        ecx_63[1] = var_20_2
0041eb28        ecx_63[2] = fconvert.s(x87_r6_20)
0041ea51        float* eax_57 = primary_samples_1 + ebx_2
0041ea79        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(eax_57[1]))) + fconvert.t(eax_57[0xd]))
0041ea86        float var_10_4 = fconvert.s(x87_r7_51 * fconvert.t(eax_57[2]) + fconvert.t(eax_57[0xe]))
0041ea93        int32_t* ecx_61 = &vertices[(width_cells + 1) * i_1 i+ edi_5]
0041ea9a        *ecx_61 = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(*eax_57))) + fconvert.t(eax_57[0xc]))
0041eaa0        ecx_61[1] = var_14_3
0041eaa7        ecx_61[2] = var_10_4
0041eb2b        width_cells = self->width_cells
0041eb2e        edi_5 += 1
0041eb31        arg2 = edi_5
0041eb35        arg3 = width_cells
0041eb39        do while (edi_5 s<= width_cells)
0041eb42        i_1 += 1
0041eb43        ebx_2 += 0xa8
0041eb4b        do while (i_1 s<= self->segment_count)
0041eb54        int32_t i_2 = 0
0041eb58        if (self->segment_count s> 0)
0041eb61        int32_t j = 0
0041eb65        arg2 = 0f
0041eb69        if (self->width_cells s> 0)
0041eb71        int32_t eax_77 = i_2 & 0x80000007
0041eb76        if (eax_77 s< 0)
0041eb7c        eax_77 = ((eax_77 - 1) | 0xfffffff8) + 1
0041eb90        arg3 = fconvert.s(float.t(eax_77) * fconvert.t(0.125f))
0041eb9e        float var_4c_2 = fconvert.s(float.t(eax_77 + 1) * fconvert.t(0.125f))
0041ebad        int32_t ecx_64 = 0
0041ebb3        int32_t var_48_2 = 0
0041ebbd        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041ebcb        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041ebe1        while (true)
0041ebe1        int32_t eax_84 = ecx_64 + ((self->width_cells * i_2 + j) << 1)
0041ebe4        if (ecx_64 != 0)
0041ecab        int16_t* ebp_3 = &facequads[eax_84]
0041ecae        *ebp_3 = 0
0041ecb4        ecx_64.w = self->width_cells.w
0041ecb8        ecx_64.w += 1
0041ecc1        ebp_3[1] = ecx_64.w * i_2.w + j.w + 1
0041ecc5        struct ObjectFaceQuad* eax_92
0041ecc5        eax_92.w = self->width_cells.w
0041ecc9        eax_92.w += 1
0041ecd0        ebp_3[2] = eax_92.w * i_2.w + j.w
0041ece2        ebp_3[3] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0041ecfa        ebp_3[4] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0041ecfe        char* texture_path_1
0041ecfe        char* arg5
0041ecfe        if (((j.b ^ i_2.b) & 1) != 0)
0041ed90        texture_path_1 = arg5
0041ed08        texture_path_1 = arg5
0041ed1b        *(ebp_3 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path_1, 0, 0)
0041ed22        *(ebp_3 + 0x10) = var_50_1
0041ed25        *(ebp_3 + 0x14) = arg3
0041ed2a        *(ebp_3 + 0x18) = arg2
0041ed33        *(ebp_3 + 0x1c) = arg3
0041ed3a        *(ebp_3 + 0x20) = arg2
0041ed3d        *(ebp_3 + 0x24) = var_4c_2
0041ed42        *(ebp_3 + 0x28) = var_50_1
0041ed45        *(ebp_3 + 0x2c) = var_4c_2
0041ebf8        int16_t* ebp_2 = &facequads[eax_84]
0041ebfb        *ebp_2 = 0
0041ec01        eax_84.w = self->width_cells.w
0041ec05        eax_84.w += 1
0041ec0c        ebp_2[1] = eax_84.w * i_2.w + j.w
0041ec10        int32_t ecx_66
0041ec10        ecx_66.w = self->width_cells.w
0041ec14        ecx_66.w += 1
0041ec20        ebp_2[2] = ecx_66.w * i_2.w + j.w + 1
0041ec31        ebp_2[3] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0041ec47        ebp_2[4] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0041ec4b        char* texture_path
0041ec4b        if (((j.b ^ i_2.b) & 1) != 0)
0041ec9a        texture_path = texture_b
0041ec51        texture_path = texture_b
0041ec64        *(ebp_2 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
0041ec6b        *(ebp_2 + 0x10) = arg2
0041ec6e        *(ebp_2 + 0x14) = arg3
0041ec73        *(ebp_2 + 0x18) = var_50_1
0041ec7c        *(ebp_2 + 0x1c) = arg3
0041ec83        *(ebp_2 + 0x20) = var_50_1
0041ec86        *(ebp_2 + 0x24) = var_4c_2
0041ec8b        *(ebp_2 + 0x28) = arg2
0041ec8e        *(ebp_2 + 0x2c) = var_4c_2
0041ed4d        bool cond:12_1 = var_48_2 + 1 s< 2
0041ed50        var_48_2 += 1
0041ed54        if (not(cond:12_1))
0041ed54        break
0041ebd1        ecx_64 = var_48_2
0041ed5a        j += 1
0041ed63        arg2 = j
0041ed67        do while (j s< self->width_cells)
0041ed72        i_2 += 1
0041ed75        do while (i_2 s< self->segment_count)
0041ed89        return finalize_path_template(self)
