/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_loopbow_path_template_pair @ 0x42ba80 */

0042ba92        int32_t i_4 = 0
0042ba98        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0042ba9b        float var_80 = 0f
0042ba9f        if (arg3 == 4)
0042baa1        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0042baa4        var_80 = 0.5f
0042bab9        self->is_mirrored_x = 0
0042babd        self->side_exit_mode = 0
0042bac0        self->width_cells = arg3
0042bac3        int16_t x87control
0042bac3        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(6.28318548f))
0042bade        self->width_or_scale = 1f
0042bae1        self->segment_count = eax_1 + 0xe
0042bae4        self->segment_count_f = fconvert.s(float.t(eax_1 + 0xe))
0042bae7        long double x87_r7_3 = float.t(eax_1)
0042baeb        float var_94 = fconvert.s(x87_r7_3)
0042baf5        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
0042bafc        allocate_path_template_samples(self)
0042bb01        self->special_runtime_flag_9c = 1
0042bb08        int32_t var_9c = 0
0042bb0c        void* i = nullptr
0042bbee        while (i s< 0x498)
0042bb15        float var_90_1 = fconvert.s(float.t(var_9c))
0042bb38        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f) - fconvert.t(var_90_1) * fconvert.t(0.142857149f) * fconvert.t(var_80))
0042bb42        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0042bb4c        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0042bb56        *(&self->primary_samples->special_scalar + i) = 0
0042bb60        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042bb6e        set_matrix_identity(i + self->primary_samples)
0042bb73        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042bb84        *(&primary_samples_4->transform.position + i) = *(&primary_samples_4->center_x + i)
0042bb8a        *(&self->primary_samples->transform.position.y + i) = 0
0042bb91        *(&self->primary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_90_1))
0042bb98        *(&self->primary_samples->delta_length + i) = 0x3f800000
0042bba6        set_matrix_identity(i + self->secondary_samples)
0042bbbc        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0042bbc3        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0042bbd2        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_90_1))
0042bbd9        i += 0xa8
0042bbe6        *(i + self->secondary_samples - 0x1c) = 0x3f800000
0042bbea        var_9c += 1
0042bbf8        int32_t i_1 = 0
0042bbfa        int32_t i_5 = 0
0042bc0d        int32_t edi_3 = (eax_1 + 7) * 0xa8
0042bc38        *(&self->primary_samples->center_x + edi_3) = fconvert.s((fconvert.t(1f) - float.t(i_5) * fconvert.t(0.166666672f)) * fconvert.t(var_80) + fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0042bc42        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0042bc4c        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0042bc56        *(&self->primary_samples->special_scalar + edi_3) = 0
0042bc60        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0042bc72        set_matrix_identity(edi_3 + self->primary_samples)
0042bc77        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042bc84        *(&primary_samples_5->transform.position + edi_3) = *(&primary_samples_5->center_x + edi_3)
0042bc91        *(&self->primary_samples->transform.position.y + edi_3) = 0
0042bc95        long double x87_r7_17 = float.t(i_1 + 7)
0042bca0        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_17)
0042bca9        *(&self->primary_samples->delta_length + edi_3) = 0x3f800000
0042bcb9        set_matrix_identity(edi_3 + self->secondary_samples)
0042bccf        i_1 += 1
0042bcd0        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0042bcd7        i_5 = i_1
0042bcdb        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0042bce6        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_17)))
0042bced        edi_3 += 0xa8
0042bcf6        *(edi_3 + self->secondary_samples - 0x1c) = 0x3f800000
0042bcfe        do while (i_1 s< 7)
0042bd08        int32_t var_9c_1 = 0
0042bd0e        if (eax_1 s> 0)
0042bd56        float var_90_2 = fconvert.s(fconvert.t(arg2) - fconvert.t(0.49000001f))
0042bd65        int32_t ecx_24 = (eax_1 + 0xe) * 0xa8
0042bd68        int32_t var_78_3 = ecx_24
0042bd6c        void* ebx = 0x498
0042bd79        while (true)
0042bd79        long double x87_r7_21 = float.t(var_9c_1)
0042bd7d        struct PathTemplateSample* primary_samples = self->primary_samples
0042bd80        int32_t var_b0_1 = ecx_24
0042bd8d        float var_74_1 = fconvert.s(x87_r7_21 * fconvert.t(6.28318548f) / fconvert.t(var_94))
0042bda7        *(&primary_samples->center_x + ebx) = fconvert.s((fconvert.t(*(primary_samples + ecx_24 - 0x18)) - fconvert.t(primary_samples->center_x)) * x87_r7_21 / fconvert.t(var_94) + fconvert.t(primary_samples->center_x))
0042bdbd        float* edi_4 = &self->primary_samples->center_x + ebx
0042bdc4        float var_98_1 = fconvert.s(fconvert.t(var_74_1) * fconvert.t(0.5f))
0042bde3        *edi_4 = fconvert.s(sine(fconvert.s(fconvert.t(var_98_1) + fconvert.t(4.71238899f))) * fconvert.t(var_80) + fconvert.t(*edi_4))
0042bde8        *(&self->primary_samples->rotation_scalar_98 + ebx) = 0
0042bdf2        *(&self->primary_samples->rotation_scalar_94 + ebx) = 0
0042bdfc        *(&self->primary_samples->special_scalar + ebx) = 0
0042be06        *(&self->primary_samples->lateral_scale + ebx) = 0x3f800000
0042be18        set_matrix_identity(ebx + self->primary_samples)
0042be1d        struct PathTemplateSample* primary_samples_6 = self->primary_samples
0042be2f        *(&primary_samples_6->transform.position + ebx) = *(&primary_samples_6->center_x + ebx)
0042be48        *(&self->primary_samples->transform.position.z + ebx) = fconvert.s(sine(var_74_1) * fconvert.t(arg2) + fconvert.t(7f))
0042be67        *(&self->primary_samples->transform.position.y + ebx) = fconvert.s(fconvert.t(arg2) - cosine(var_74_1) * fconvert.t(arg2))
0042be6e        set_matrix_identity(ebx + self->secondary_samples)
0042be81        *(&self->secondary_samples->transform.position + ebx) = *(&self->primary_samples->center_x + ebx)
0042be98        *(&self->secondary_samples->transform.position.z + ebx) = fconvert.s(sine(var_74_1) * fconvert.t(var_90_2) + fconvert.t(7f))
0042beb4        *(&self->secondary_samples->transform.position.y + ebx) = fconvert.s(fconvert.t(arg2) - cosine(var_74_1) * fconvert.t(var_90_2))
0042bec3        int32_t* eax_26 = ebx + self->primary_samples
0042becc        *eax_26 = 0x3f800000
0042bed2        eax_26[1] = 0
0042bed5        eax_26[2] = 0
0042bedb        *(&self->primary_samples->transform.basis_up + ebx) = 0
0042bee2        void* eax_28 = self->primary_samples + ebx
0042bee7        *(eax_28 + 0x14) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(eax_28 + 0x34)))
0042beea        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042befa        *(&primary_samples_3->transform.basis_up.z + ebx) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&primary_samples_3->transform.position.z + ebx)))
0042bf04        normalize_vector(&self->primary_samples->transform.basis_up + ebx)
0042bf0c        struct Vec3* lhs = self->primary_samples + ebx
0042bf18        cross_vectors(lhs + 0x20, lhs, lhs + 0x10)
0042bf2a        int32_t* edx_23 = ebx + self->secondary_samples
0042bf33        *edx_23 = 0x3f800000
0042bf39        edx_23[1] = 0
0042bf3c        edx_23[2] = 0
0042bf42        *(&self->secondary_samples->transform.basis_up + ebx) = 0
0042bf46        struct PathTemplateSample* secondary_samples_4 = self->secondary_samples
0042bf50        *(&secondary_samples_4->transform.basis_up.y + ebx) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(&secondary_samples_4->transform.position.y + ebx)))
0042bf53        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042bf62        *(&secondary_samples->transform.basis_up.z + ebx) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&secondary_samples->transform.position.z + ebx)))
0042bf6c        normalize_vector(&self->secondary_samples->transform.basis_up + ebx)
0042bf76        struct Vec3* lhs_1 = ebx + self->secondary_samples
0042bf81        cross_vectors(lhs_1 + 0x20, lhs_1, lhs_1 + 0x10)
0042bf8a        void transform
0042bf8a        set_matrix_identity(&transform)
0042bf99        float var_98_2 = fconvert.s(sine(var_98_1))
0042bfb7        rotate_matrix_world_y(&transform, fconvert.s(sine(var_98_1) * fconvert.t(var_98_2) * fconvert.t(0.52359879f)))
0042bfbc        struct PathTemplateSample* primary_samples_7 = self->primary_samples
0042bfd4        *(&primary_samples_7->transform.position.z + ebx) = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position.z + ebx)) - fconvert.t(7f))
0042bfd6        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042bfe7        *(&secondary_samples_1->transform.position.z + ebx) = fconvert.s(fconvert.t(*(&secondary_samples_1->transform.position.z + ebx)) - fconvert.t(7f))
0042bfe9        self->primary_samples
0042bfec        sub_44d1d0(&transform)
0042bff8        self->secondary_samples
0042bffd        sub_44d1d0(&transform)
0042c002        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042c017        *(&primary_samples_1->transform.position.z + ebx) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position.z + ebx)) + fconvert.t(7f))
0042c019        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
0042c02a        *(&secondary_samples_2->transform.position.z + ebx) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position.z + ebx)) + fconvert.t(7f))
0042c03b        __builtin_memcpy(ebx + self->secondary_samples, ebx + self->primary_samples, 0x40)
0042c03d        struct PathTemplateSample* primary_samples_8 = self->primary_samples
0042c048        long double x87_r7_67 = fconvert.t(*(&primary_samples_8->transform.basis_up + ebx)) * fconvert.t(0.49000001f)
0042c05c        float var_60_1 = fconvert.s(fconvert.t(*(&primary_samples_8->transform.basis_up.y + ebx)) * fconvert.t(0.49000001f))
0042c063        long double x87_r6_18 = fconvert.t(*(&primary_samples_8->transform.basis_up.z + ebx)) * fconvert.t(0.49000001f)
0042c06c        float* eax_40 = &self->secondary_samples->transform.position + ebx
0042c070        ebx += 0xa8
0042c07c        *eax_40 = fconvert.s(x87_r7_67 + fconvert.t(*eax_40))
0042c085        eax_40[1] = fconvert.s(fconvert.t(var_60_1) + fconvert.t(eax_40[1]))
0042c08f        eax_40[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_18)) + fconvert.t(eax_40[2]))
0042c097        bool cond:4_1 = var_9c_1 + 1 s< eax_1
0042c099        var_9c_1 += 1
0042c09d        if (not(cond:4_1))
0042c09d        break
0042bd73        ecx_24 = var_78_3
0042c0a3        i_4 = 0
0042c0a8        int32_t i_2 = 0
0042c0ad        if (self->segment_count - 1 s> 0)
0042c0b3        void* edi_10 = nullptr
0042c0b5        struct PathTemplateSample* primary_samples_9 = self->primary_samples
0042c0d9        float var_88_1 = fconvert.s(fconvert.t(*(edi_10 + primary_samples_9 + 0xdc)) - fconvert.t(*(&primary_samples_9->transform.position.y + edi_10)))
0042c0e0        long double x87_r7_78 = fconvert.t(*(edi_10 + primary_samples_9 + 0xe0)) - fconvert.t(*(&primary_samples_9->transform.position.z + edi_10))
0042c0e7        *(&primary_samples_9->delta_dir_to_next + edi_10) = fconvert.s(fconvert.t(*(edi_10 + primary_samples_9 + 0xd8)) - fconvert.t(*(&primary_samples_9->transform.position + edi_10)))
0042c0e9        *(&primary_samples_9->delta_dir_to_next.y + edi_10) = var_88_1
0042c0f4        *(&primary_samples_9->delta_dir_to_next.z + edi_10) = fconvert.s(x87_r7_78)
0042c109        *(&self->primary_samples->delta_length + edi_10) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_10))
0042c110        struct PathTemplateSample* secondary_samples_3 = self->secondary_samples
0042c134        float var_6c_1 = fconvert.s(fconvert.t(*(edi_10 + secondary_samples_3 + 0xdc)) - fconvert.t(*(&secondary_samples_3->transform.position.y + edi_10)))
0042c13b        long double x87_r7_85 = fconvert.t(*(edi_10 + secondary_samples_3 + 0xe0)) - fconvert.t(*(&secondary_samples_3->transform.position.z + edi_10))
0042c142        *(&secondary_samples_3->delta_dir_to_next + edi_10) = fconvert.s(fconvert.t(*(edi_10 + secondary_samples_3 + 0xd8)) - fconvert.t(*(&secondary_samples_3->transform.position + edi_10)))
0042c144        *(&secondary_samples_3->delta_dir_to_next.y + edi_10) = var_6c_1
0042c14f        *(&secondary_samples_3->delta_dir_to_next.z + edi_10) = fconvert.s(x87_r7_85)
0042c164        i_2 += 1
0042c165        *(&self->secondary_samples->delta_length + edi_10) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_10))
0042c16f        edi_10 += 0xa8
0042c178        do while (i_2 s< self->segment_count - 1)
0042c1a8        int32_t* edx_32 = &self->primary_samples[self->segment_count] - 0x28
0042c1bc        *edx_32 = 0
0042c1ca        edx_32[1] = 0
0042c1cd        edx_32[2] = 0x3f800000
0042c1df        int32_t var_84_2 = 0x3f800000
0042c1eb        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042c201        int32_t* ecx_64 = &self->secondary_samples[self->segment_count] - 0x28
0042c209        *ecx_64 = 0
0042c20f        ecx_64[1] = 0
0042c214        ecx_64[2] = 0x3f800000
0042c229        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042c23c        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0042c24e        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0042c253        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0042c256        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0042c259        struct Vec3* vertices = strip_mesh->vertices
0042c263        int32_t i_3 = 0
0042c26b        if (self->segment_count s>= 0)
0042c271        int32_t ebx_1 = 0
0042c273        int32_t var_74_2 = 0
0042c277        uint32_t width_cells = self->width_cells
0042c27a        int32_t edi_11 = 0
0042c27e        int32_t var_9c_2 = 0
0042c282        uint32_t width_cells_1 = width_cells
0042c286        if (width_cells s>= 0)
0042c299        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042c2a2        long double x87_r7_88 = float.t(var_9c_2) - float.t(width_cells_1) * fconvert.t(0.5f)
0042c2a4        if (i_3 == self->segment_count)
0042c304        void* eax_74 = primary_samples_2 + ebx_1
0042c315        ebx_1 = var_74_2
0042c35e        float var_6c_2 = fconvert.s(fconvert.t(*(eax_74 - 0x74)) + fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(*(eax_74 - 0xa4)))))
0042c366        int32_t* ecx_75 = &vertices[(width_cells + 1) * i_3 + edi_11]
0042c36d        long double x87_r6_38 = fconvert.t(fconvert.s(fconvert.t(*(eax_74 - 0x70)) + fconvert.t(1f))) + x87_r7_88 * fconvert.t(*(eax_74 - 0xa0))
0042c36f        *ecx_75 = fconvert.s(fconvert.t(*(eax_74 - 0x78)) + fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(*(eax_74 - 0xa8)))))
0042c375        ecx_75[1] = var_6c_2
0042c382        ecx_75[2] = fconvert.s(x87_r6_38)
0042c2a6        float* eax_66 = primary_samples_2 + ebx_1
0042c2ce        float var_88_2 = fconvert.s(fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(eax_66[1]))) + fconvert.t(eax_66[0xd]))
0042c2db        float var_84_3 = fconvert.s(x87_r7_88 * fconvert.t(eax_66[2]) + fconvert.t(eax_66[0xe]))
0042c2e8        int32_t* ecx_73 = &vertices[(width_cells + 1) * i_3 + edi_11]
0042c2ef        *ecx_73 = fconvert.s(fconvert.t(fconvert.s(x87_r7_88 * fconvert.t(*eax_66))) + fconvert.t(eax_66[0xc]))
0042c2f5        ecx_73[1] = var_88_2
0042c2fc        ecx_73[2] = var_84_3
0042c385        width_cells = self->width_cells
0042c388        edi_11 += 1
0042c38b        var_9c_2 = edi_11
0042c38f        width_cells_1 = width_cells
0042c393        do while (edi_11 s<= width_cells)
0042c39c        i_3 += 1
0042c39d        ebx_1 += 0xa8
0042c3a5        var_74_2 = ebx_1
0042c3a9        do while (i_3 s<= self->segment_count)
0042c3b2        int32_t edi_12 = 0
0042c3b6        if (self->segment_count s> 0)
0042c3c3        while (true)
0042c3c3        int32_t i_6 = 0
0042c3c9        if (self->width_cells s> 0)
0042c3d1        int32_t eax_86 = edi_12 & 0x80000007
0042c3d6        if (eax_86 s< 0)
0042c3dc        eax_86 = ((eax_86 - 1) | 0xfffffff8) + 1
0042c3f0        float var_7c_1 = fconvert.s(float.t(eax_86) * fconvert.t(0.125f))
0042c3fe        float var_90_3 = fconvert.s(float.t(eax_86 + 1) * fconvert.t(0.125f))
0042c409        int32_t ecx_76 = 0
0042c40f        int32_t var_94_1 = 0
0042c419        float var_80_1 = fconvert.s(float.t(i_6) * fconvert.t(0.125f))
0042c427        float var_9c_3 = fconvert.s(float.t(i_4 + 1) * fconvert.t(0.125f))
0042c43b        while (true)
0042c43b        int32_t eax_93 = ecx_76 + ((self->width_cells * edi_12 + i_4) << 1)
0042c43e        if (ecx_76 != 0)
0042c50a        int16_t* ebx_4 = &facequads[eax_93]
0042c50d        *ebx_4 = 0
0042c512        ecx_76.w = self->width_cells.w
0042c516        ecx_76.w += 1
0042c51f        ebx_4[1] = ecx_76.w * edi_12.w + i_4.w + 1
0042c523        struct ObjectFaceQuad* eax_101
0042c523        eax_101.w = self->width_cells.w
0042c527        eax_101.w += 1
0042c52e        ebx_4[2] = eax_101.w * edi_12.w + i_4.w
0042c540        ebx_4[3] = (self->width_cells.w + 1) * (edi_12.w + 1) + i_4.w
0042c558        ebx_4[4] = (self->width_cells.w + 1) * (edi_12.w + 1) + i_4.w + 1
0042c55c        char* texture_path_1
0042c55c        char* arg5
0042c55c        if (((i_4.b ^ edi_12.b) & 1) != 0)
0042c5f5        texture_path_1 = arg5
0042c569        texture_path_1 = arg5
0042c57c        *(ebx_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0042c583        *(ebx_4 + 0x10) = var_9c_3
0042c586        *(ebx_4 + 0x14) = var_7c_1
0042c58b        *(ebx_4 + 0x18) = var_80_1
0042c594        *(ebx_4 + 0x1c) = var_7c_1
0042c59b        *(ebx_4 + 0x20) = var_80_1
0042c59e        *(ebx_4 + 0x24) = var_90_3
0042c5a3        *(ebx_4 + 0x28) = var_9c_3
0042c5a6        *(ebx_4 + 0x2c) = var_90_3
0042c452        int16_t* ebx_3 = &facequads[eax_93]
0042c455        *ebx_3 = 0
0042c45a        eax_93.w = self->width_cells.w
0042c45e        eax_93.w += 1
0042c465        ebx_3[1] = eax_93.w * edi_12.w + i_4.w
0042c469        int32_t ecx_78
0042c469        ecx_78.w = self->width_cells.w
0042c46d        ecx_78.w += 1
0042c479        ebx_3[2] = ecx_78.w * edi_12.w + i_4.w + 1
0042c48a        ebx_3[3] = (self->width_cells.w + 1) * (edi_12.w + 1) + i_4.w + 1
0042c4a0        ebx_3[4] = (self->width_cells.w + 1) * (edi_12.w + 1) + i_4.w
0042c4a4        char* texture_path
0042c4a4        if (((i_4.b ^ edi_12.b) & 1) != 0)
0042c4f9        texture_path = texture_b
0042c4ad        texture_path = texture_b
0042c4c0        *(ebx_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0042c4c7        *(ebx_3 + 0x10) = var_80_1
0042c4ca        *(ebx_3 + 0x14) = var_7c_1
0042c4cf        *(ebx_3 + 0x18) = var_9c_3
0042c4d8        *(ebx_3 + 0x1c) = var_7c_1
0042c4df        *(ebx_3 + 0x20) = var_9c_3
0042c4e2        *(ebx_3 + 0x24) = var_90_3
0042c4e7        *(ebx_3 + 0x28) = var_80_1
0042c4ea        *(ebx_3 + 0x2c) = var_90_3
0042c5ae        bool cond:13_1 = var_94_1 + 1 s< 2
0042c5b1        var_94_1 += 1
0042c5b5        if (not(cond:13_1))
0042c5b5        break
0042c42d        ecx_76 = var_94_1
0042c5bb        i_4 += 1
0042c5c4        i_6 = i_4
0042c5c8        do while (i_4 s< self->width_cells)
0042c5d1        edi_12 += 1
0042c5d4        if (edi_12 s>= self->segment_count)
0042c5d4        break
0042c3be        i_4 = 0
0042c5eb        return finalize_path_template(self)
