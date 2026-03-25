/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_looptheloopw_path_template_pair @ 0x41bb40 */

0041bb52        self->kind = 0
0041bb55        float var_5c = 0f
0041bb59        if (arg3 == 4)
0041bb5b        self->kind = 6
0041bb62        var_5c = 0.300000012f
0041bb74        self->is_mirrored_x = 0
0041bb78        self->side_exit_mode = 0
0041bb7b        self->width_cells = arg3
0041bb7e        int16_t x87control
0041bb7e        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(6.28318548f))
0041bb99        self->width_or_scale = 1f
0041bb9c        self->segment_count = eax_1 + 0xe
0041bb9f        self->segment_count_f = fconvert.s(float.t(eax_1 + 0xe))
0041bba2        long double x87_r7_3 = float.t(eax_1)
0041bba6        float var_54 = fconvert.s(x87_r7_3)
0041bbb0        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
0041bbb4        allocate_path_nodes(self)
0041bbb9        self->special_runtime_flag_9c = 1
0041bbc0        arg3 = 0
0041bbc4        void* i = nullptr
0041bca6        while (i s< 0x498)
0041bbcd        float var_60_1 = fconvert.s(float.t(arg3))
0041bbf0        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f) - fconvert.t(var_60_1) * fconvert.t(0.142857149f) * fconvert.t(var_5c))
0041bbfa        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041bc04        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041bc0e        *(&self->primary_samples->special_scalar + i) = 0
0041bc18        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041bc26        set_matrix_identity(i + self->primary_samples)
0041bc2b        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041bc3c        *(&primary_samples_3->transform.position + i) = *(&primary_samples_3->center_x + i)
0041bc42        *(&self->primary_samples->transform.position.y + i) = 0
0041bc49        *(&self->primary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_60_1))
0041bc50        *(&self->primary_samples->delta_length + i) = 0x3f800000
0041bc5e        set_matrix_identity(i + self->secondary_samples)
0041bc74        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0041bc7b        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0041bc8a        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_60_1))
0041bc91        i += 0xa8
0041bc9e        *(i + self->secondary_samples - 0x1c) = 0x3f800000
0041bca2        arg3 += 1
0041bcb0        int32_t i_1 = 0
0041bcb2        arg3 = 0
0041bcc5        int32_t edi_3 = (eax_1 + 7) * 0xa8
0041bcf0        *(&self->primary_samples->center_x + edi_3) = fconvert.s((fconvert.t(1f) - float.t(arg3) * fconvert.t(0.166666672f)) * fconvert.t(var_5c) + fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0041bcfa        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041bd04        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041bd0e        *(&self->primary_samples->special_scalar + edi_3) = 0
0041bd18        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041bd2a        set_matrix_identity(edi_3 + self->primary_samples)
0041bd2f        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041bd3c        *(&primary_samples_4->transform.position + edi_3) = *(&primary_samples_4->center_x + edi_3)
0041bd49        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041bd4d        long double x87_r7_17 = float.t(i_1 + 7)
0041bd58        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_17)
0041bd61        *(&self->primary_samples->delta_length + edi_3) = 0x3f800000
0041bd71        set_matrix_identity(edi_3 + self->secondary_samples)
0041bd87        i_1 += 1
0041bd88        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0041bd8f        arg3 = i_1
0041bd93        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0041bd9e        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_17)))
0041bda5        edi_3 += 0xa8
0041bdae        *(edi_3 + self->secondary_samples - 0x1c) = 0x3f800000
0041bdb6        do while (i_1 s< 7)
0041bdc0        arg3 = 0
0041bdc6        if (eax_1 s> 0)
0041bdcc        int32_t ecx_21 = eax_1 + 0xe
0041be0b        float var_48_1 = fconvert.s(fconvert.t(arg2) - fconvert.t(0.49000001f))
0041be1a        int32_t ebx_1 = ecx_21 * 0xa8
0041be1d        int32_t var_44_1 = ebx_1
0041be21        void* edi_4 = 0x498
0041be2c        while (true)
0041be2c        long double x87_r7_21 = float.t(arg3)
0041be30        int32_t var_74_1 = ecx_21
0041be3b        long double x87_r7_23 = x87_r7_21 * fconvert.t(6.28318548f) / fconvert.t(var_54)
0041be3f        float var_50_1 = fconvert.s(x87_r7_23)
0041be49        float var_4c_1 = fconvert.s(x87_r7_23 * fconvert.t(0.5f))
0041be63        float var_40_1 = fconvert.s(sine(fconvert.s(fconvert.t(var_50_1) * fconvert.t(8f))))
0041be6d        long double x87_r7_29 = sine(var_4c_1) * fconvert.t(var_40_1)
0041be71        struct PathTemplateSample* primary_samples = self->primary_samples
0041be7d        float var_40_2 = fconvert.s(x87_r7_29 * fconvert.t(0.392699093f))
0041be99        *(&primary_samples->center_x + edi_4) = fconvert.s((fconvert.t(*(primary_samples + ebx_1 - 0x18)) - fconvert.t(primary_samples->center_x)) * fconvert.t(fconvert.s(x87_r7_21)) / fconvert.t(var_54) + fconvert.t(primary_samples->center_x))
0041bead        float* ebx_2 = &self->primary_samples->center_x + edi_4
0041bec5        *ebx_2 = fconvert.s(sine(fconvert.s(fconvert.t(var_4c_1) + fconvert.t(4.71238899f))) * fconvert.t(var_5c) + fconvert.t(*ebx_2))
0041beca        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041bed4        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0041bede        *(&self->primary_samples->special_scalar + edi_4) = 0
0041beea        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041befa        set_matrix_identity(edi_4 + self->primary_samples)
0041bf06        void* eax_24 = self->primary_samples + edi_4
0041bf0f        *(eax_24 + 0x30) = *(eax_24 + 0x90)
0041bf25        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(sine(var_50_1) * fconvert.t(arg2) + fconvert.t(7f))
0041bf3e        *(&self->primary_samples->transform.position.y + edi_4) = fconvert.s(fconvert.t(arg2) - cosine(var_50_1) * fconvert.t(arg2))
0041bf45        set_matrix_identity(edi_4 + self->secondary_samples)
0041bf58        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
0041bf6e        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(sine(var_50_1) * fconvert.t(var_48_1) + fconvert.t(7f))
0041bf8c        *(&self->secondary_samples->transform.position.y + edi_4) = fconvert.s(fconvert.t(arg2) - cosine(var_50_1) * fconvert.t(var_48_1))
0041bf97        int32_t* eax_28 = edi_4 + self->primary_samples
0041bf9d        *eax_28 = 0x3f800000
0041bfa3        eax_28[1] = 0
0041bfa6        eax_28[2] = 0
0041bfac        *(&self->primary_samples->transform.basis_up + edi_4) = 0
0041bfb3        void* eax_30 = self->primary_samples + edi_4
0041bfb8        *(eax_30 + 0x14) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(eax_30 + 0x34)))
0041bfbb        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041bfcb        *(&primary_samples_2->transform.basis_up.z + edi_4) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&primary_samples_2->transform.position.z + edi_4)))
0041bfd5        normalize_vector(&self->primary_samples->transform.basis_up + edi_4)
0041bfdd        struct Vec3* lhs = self->primary_samples + edi_4
0041bfe9        cross_vectors(lhs + 0x20, lhs, lhs + 0x10)
0041bffa        rotate_matrix_world_z(edi_4 + self->primary_samples, var_40_2)
0041c008        int32_t* edx_25 = edi_4 + self->secondary_samples
0041c012        *edx_25 = 0x3f800000
0041c018        edx_25[1] = 0
0041c01b        edx_25[2] = 0
0041c021        *(&self->secondary_samples->transform.basis_up + edi_4) = 0
0041c025        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
0041c02f        *(&secondary_samples_2->transform.basis_up.y + edi_4) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(&secondary_samples_2->transform.position.y + edi_4)))
0041c032        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041c041        *(&secondary_samples->transform.basis_up.z + edi_4) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&secondary_samples->transform.position.z + edi_4)))
0041c04b        normalize_vector(&self->secondary_samples->transform.basis_up + edi_4)
0041c055        struct Vec3* lhs_1 = edi_4 + self->secondary_samples
0041c060        cross_vectors(lhs_1 + 0x20, lhs_1, lhs_1 + 0x10)
0041c06d        rotate_matrix_world_z(edi_4 + self->secondary_samples, var_40_2)
0041c076        ecx_21 = eax_1
0041c07b        edi_4 += 0xa8
0041c081        bool cond:4_1 = arg3 + 1 s< ecx_21
0041c083        arg3 += 1
0041c087        if (not(cond:4_1))
0041c087        break
0041be28        ebx_1 = var_44_1
0041c090        int32_t i_2 = 0
0041c095        if (self->segment_count - 1 s> 0)
0041c09b        void* edi_5 = nullptr
0041c0a0        void* eax_40 = self->primary_samples + edi_5
0041c0be        float var_2c_1 = fconvert.s(fconvert.t(*(eax_40 + 0xdc)) - fconvert.t(*(eax_40 + 0x34)))
0041c0c5        long double x87_r7_70 = fconvert.t(*(eax_40 + 0xe0)) - fconvert.t(*(eax_40 + 0x38))
0041c0cc        *(eax_40 + 0x80) = fconvert.s(fconvert.t(*(eax_40 + 0xd8)) - fconvert.t(*(eax_40 + 0x30)))
0041c0ce        *(eax_40 + 0x84) = var_2c_1
0041c0d9        *(eax_40 + 0x88) = fconvert.s(x87_r7_70)
0041c0ee        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041c0f5        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041c119        float var_38_1 = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_5)))
0041c120        long double x87_r7_77 = fconvert.t(*(edi_5 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_5))
0041c127        *(&secondary_samples_1->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_5)))
0041c129        *(&secondary_samples_1->delta_dir_to_next.y + edi_5) = var_38_1
0041c134        *(&secondary_samples_1->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_77)
0041c149        i_2 += 1
0041c14a        *(&self->secondary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_5))
0041c154        edi_5 += 0xa8
0041c15d        do while (i_2 s< self->segment_count - 1)
0041c18d        int32_t* edx_35 = &self->primary_samples[self->segment_count] - 0x28
0041c1a1        *edx_35 = 0
0041c1af        edx_35[1] = 0
0041c1b2        edx_35[2] = 0x3f800000
0041c1c4        int32_t var_28_2 = 0x3f800000
0041c1d0        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041c1e6        int32_t* ecx_55 = &self->secondary_samples[self->segment_count] - 0x28
0041c1ee        *ecx_55 = 0
0041c1f4        ecx_55[1] = 0
0041c1f9        ecx_55[2] = 0x3f800000
0041c20e        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041c221        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0041c233        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0041c238        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0041c23b        int32_t i_3 = 0
0041c23d        struct Vec3* vertices = strip_mesh->vertices
0041c240        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0041c250        if (self->segment_count s>= 0)
0041c256        int32_t edx_38 = 0
0041c258        int32_t var_4c_2 = 0
0041c25c        uint32_t width_cells = self->width_cells
0041c25f        float ebx_6 = 0f
0041c263        arg2 = 0f
0041c267        arg3 = width_cells
0041c26b        if (width_cells s>= 0)
0041c27e        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041c287        long double x87_r7_80 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041c289        if (i_3 == self->segment_count)
0041c2e9        void* eax_71 = primary_samples_1 + edx_38
0041c33f        float var_38_2 = fconvert.s(fconvert.t(*(eax_71 - 0x74)) + fconvert.t(fconvert.s(x87_r7_80 * fconvert.t(*(eax_71 - 0xa4)))))
0041c347        int32_t* edx_40 = &vertices[(width_cells + 1) * i_3 i+ ebx_6]
0041c352        long double x87_r6_26 = fconvert.t(fconvert.s(fconvert.t(*(eax_71 - 0x70)) + fconvert.t(1f))) + x87_r7_80 * fconvert.t(*(eax_71 - 0xa0))
0041c354        *edx_40 = fconvert.s(fconvert.t(*(eax_71 - 0x78)) + fconvert.t(fconvert.s(x87_r7_80 * fconvert.t(*(eax_71 - 0xa8)))))
0041c356        edx_40[1] = var_38_2
0041c361        edx_40[2] = fconvert.s(x87_r6_26)
0041c364        edx_38 = var_4c_2
0041c28b        float* eax_63 = primary_samples_1 + edx_38
0041c2b3        float var_2c_2 = fconvert.s(fconvert.t(fconvert.s(x87_r7_80 * fconvert.t(eax_63[1]))) + fconvert.t(eax_63[0xd]))
0041c2c0        float var_28_3 = fconvert.s(x87_r7_80 * fconvert.t(eax_63[2]) + fconvert.t(eax_63[0xe]))
0041c2cd        int32_t* ecx_64 = &vertices[(width_cells + 1) * i_3 i+ ebx_6]
0041c2d4        *ecx_64 = fconvert.s(fconvert.t(fconvert.s(x87_r7_80 * fconvert.t(*eax_63))) + fconvert.t(eax_63[0xc]))
0041c2da        ecx_64[1] = var_2c_2
0041c2e1        ecx_64[2] = var_28_3
0041c36a        width_cells = self->width_cells
0041c36d        ebx_6 += 1
0041c370        arg2 = ebx_6
0041c374        arg3 = width_cells
0041c378        do while (ebx_6 s<= width_cells)
0041c381        i_3 += 1
0041c382        edx_38 += 0xa8
0041c38a        var_4c_2 = edx_38
0041c38e        do while (i_3 s<= self->segment_count)
0041c397        int32_t i_4 = 0
0041c39b        if (self->segment_count s> 0)
0041c3a4        int32_t j = 0
0041c3a8        arg2 = 0f
0041c3ac        if (self->width_cells s> 0)
0041c3b4        int32_t eax_82 = i_4 & 0x80000007
0041c3b9        if (eax_82 s< 0)
0041c3bf        eax_82 = ((eax_82 - 1) | 0xfffffff8) + 1
0041c3d3        arg3 = fconvert.s(float.t(eax_82) * fconvert.t(0.125f))
0041c3e1        float var_5c_1 = fconvert.s(float.t(eax_82 + 1) * fconvert.t(0.125f))
0041c3f0        int32_t ecx_67 = 0
0041c3f6        int32_t var_50_2 = 0
0041c400        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041c40e        float var_58_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041c424        while (true)
0041c424        int32_t eax_89 = ecx_67 + ((self->width_cells * i_4 + j) << 1)
0041c427        if (ecx_67 != 0)
0041c4f4        int16_t* ebp_2 = &facequads[eax_89]
0041c4f7        *ebp_2 = 0
0041c4fd        ecx_67.w = self->width_cells.w
0041c501        ecx_67.w += 1
0041c50a        ebp_2[1] = ecx_67.w * i_4.w + j.w + 1
0041c50e        struct ObjectFaceQuad* eax_97
0041c50e        eax_97.w = self->width_cells.w
0041c512        eax_97.w += 1
0041c519        ebp_2[2] = eax_97.w * i_4.w + j.w
0041c52b        ebp_2[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
0041c543        ebp_2[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
0041c547        char* texture_path_1
0041c547        char* arg5
0041c547        if (((j.b ^ i_4.b) & 1) != 0)
0041c5df        texture_path_1 = arg5
0041c554        texture_path_1 = arg5
0041c567        *(ebp_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0041c56e        *(ebp_2 + 0x10) = var_58_1
0041c571        *(ebp_2 + 0x14) = arg3
0041c576        *(ebp_2 + 0x18) = arg2
0041c57f        *(ebp_2 + 0x1c) = arg3
0041c586        *(ebp_2 + 0x20) = arg2
0041c589        *(ebp_2 + 0x24) = var_5c_1
0041c58e        *(ebp_2 + 0x28) = var_58_1
0041c591        *(ebp_2 + 0x2c) = var_5c_1
0041c43b        int16_t* ebp_1 = &facequads[eax_89]
0041c43e        *ebp_1 = 0
0041c444        eax_89.w = self->width_cells.w
0041c448        eax_89.w += 1
0041c44f        ebp_1[1] = eax_89.w * i_4.w + j.w
0041c453        int32_t ecx_69
0041c453        ecx_69.w = self->width_cells.w
0041c457        ecx_69.w += 1
0041c463        ebp_1[2] = ecx_69.w * i_4.w + j.w + 1
0041c474        ebp_1[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
0041c48a        ebp_1[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
0041c48e        char* texture_path
0041c48e        if (((j.b ^ i_4.b) & 1) != 0)
0041c4e3        texture_path = texture_b
0041c497        texture_path = texture_b
0041c4aa        *(ebp_1 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0041c4b1        *(ebp_1 + 0x10) = arg2
0041c4b4        *(ebp_1 + 0x14) = arg3
0041c4b9        *(ebp_1 + 0x18) = var_58_1
0041c4c2        *(ebp_1 + 0x1c) = arg3
0041c4c9        *(ebp_1 + 0x20) = var_58_1
0041c4cc        *(ebp_1 + 0x24) = var_5c_1
0041c4d1        *(ebp_1 + 0x28) = arg2
0041c4d4        *(ebp_1 + 0x2c) = var_5c_1
0041c599        bool cond:14_1 = var_50_2 + 1 s< 2
0041c59c        var_50_2 += 1
0041c5a0        if (not(cond:14_1))
0041c5a0        break
0041c414        ecx_67 = var_50_2
0041c5a6        j += 1
0041c5af        arg2 = j
0041c5b3        do while (j s< self->width_cells)
0041c5be        i_4 += 1
0041c5c1        do while (i_4 s< self->segment_count)
0041c5d5        return finalize_path_template_record(self)
