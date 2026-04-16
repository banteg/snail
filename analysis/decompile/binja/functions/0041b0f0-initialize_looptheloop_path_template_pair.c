/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_looptheloop_path_template_pair @ 0x41b0f0 */

0041b102        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0041b105        float var_54 = 0f
0041b109        if (arg3 == 4)
0041b10b        self->kind = PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY
0041b10e        var_54 = 0.300000012f
0041b120        self->is_mirrored_x = 0
0041b124        self->side_exit_mode = 0
0041b127        self->width_cells = arg3
0041b12a        int16_t x87control
0041b12a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(6.28318548f))
0041b145        self->width_or_scale = 1f
0041b148        self->segment_count = eax_1 + 0xe
0041b14b        self->segment_count_f = fconvert.s(float.t(eax_1 + 0xe))
0041b14e        long double x87_r7_3 = float.t(eax_1)
0041b152        float var_48 = fconvert.s(x87_r7_3)
0041b15c        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
0041b160        allocate_path_template_samples(self)
0041b165        self->special_runtime_flag_9c = 1
0041b16c        arg3 = 0
0041b170        void* i = nullptr
0041b252        while (i s< 0x498)
0041b179        float var_4c_1 = fconvert.s(float.t(arg3))
0041b19c        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f) - fconvert.t(var_4c_1) * fconvert.t(0.142857149f) * fconvert.t(var_54))
0041b1a6        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041b1b0        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041b1ba        *(&self->primary_samples->special_scalar + i) = 0
0041b1c4        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041b1d2        set_matrix_identity(i + self->primary_samples)
0041b1d7        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041b1e8        *(&primary_samples_3->transform.position + i) = *(&primary_samples_3->center_x + i)
0041b1ee        *(&self->primary_samples->transform.position.y + i) = 0
0041b1f5        *(&self->primary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_4c_1))
0041b1fc        *(&self->primary_samples->delta_length + i) = 0x3f800000
0041b20a        set_matrix_identity(i + self->secondary_samples)
0041b220        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0041b227        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0041b236        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_4c_1))
0041b23d        i += 0xa8
0041b24a        *(i + self->secondary_samples - 0x1c) = 0x3f800000
0041b24e        arg3 += 1
0041b25c        int32_t i_1 = 0
0041b25e        arg3 = 0
0041b271        int32_t edi_3 = (eax_1 + 7) * 0xa8
0041b29c        *(&self->primary_samples->center_x + edi_3) = fconvert.s((fconvert.t(1f) - float.t(arg3) * fconvert.t(0.166666672f)) * fconvert.t(var_54) + fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0041b2a6        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041b2b0        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041b2ba        *(&self->primary_samples->special_scalar + edi_3) = 0
0041b2c4        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041b2d6        set_matrix_identity(edi_3 + self->primary_samples)
0041b2db        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041b2e8        *(&primary_samples_4->transform.position + edi_3) = *(&primary_samples_4->center_x + edi_3)
0041b2f5        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041b2f9        long double x87_r7_17 = float.t(i_1 + 7)
0041b304        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_17)
0041b30d        *(&self->primary_samples->delta_length + edi_3) = 0x3f800000
0041b31d        set_matrix_identity(edi_3 + self->secondary_samples)
0041b333        i_1 += 1
0041b334        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0041b33b        arg3 = i_1
0041b33f        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0041b34a        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_17)))
0041b351        edi_3 += 0xa8
0041b35a        *(edi_3 + self->secondary_samples - 0x1c) = 0x3f800000
0041b362        do while (i_1 s< 7)
0041b36c        arg3 = 0
0041b372        if (eax_1 s> 0)
0041b3b7        float var_4c_2 = fconvert.s(fconvert.t(arg2) - fconvert.t(0.49000001f))
0041b3c6        int32_t ecx_23 = (eax_1 + 0xe) * 0xa8
0041b3c9        int32_t var_40_1 = ecx_23
0041b3cd        void* edi_4 = 0x498
0041b3d8        while (true)
0041b3d8        long double x87_r7_21 = float.t(arg3)
0041b3dc        struct PathTemplateSample* primary_samples = self->primary_samples
0041b3df        int32_t var_68_1 = ecx_23
0041b3ec        float var_44_1 = fconvert.s(x87_r7_21 * fconvert.t(6.28318548f) / fconvert.t(var_48))
0041b406        *(&primary_samples->center_x + edi_4) = fconvert.s((fconvert.t(*(primary_samples + ecx_23 - 0x18)) - fconvert.t(primary_samples->center_x)) * x87_r7_21 / fconvert.t(var_48) + fconvert.t(primary_samples->center_x))
0041b41c        float* ebx = &self->primary_samples->center_x + edi_4
0041b43a        *ebx = fconvert.s(sine(fconvert.s(fconvert.t(var_44_1) * fconvert.t(0.5f) + fconvert.t(4.71238899f))) * fconvert.t(var_54) + fconvert.t(*ebx))
0041b43f        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041b449        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0041b453        *(&self->primary_samples->special_scalar + edi_4) = 0
0041b45d        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041b46f        set_matrix_identity(edi_4 + self->primary_samples)
0041b474        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0041b486        *(&primary_samples_5->transform.position + edi_4) = *(&primary_samples_5->center_x + edi_4)
0041b49c        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(sine(var_44_1) * fconvert.t(arg2) + fconvert.t(7f))
0041b4b5        *(&self->primary_samples->transform.position.y + edi_4) = fconvert.s(fconvert.t(arg2) - cosine(var_44_1) * fconvert.t(arg2))
0041b4bc        set_matrix_identity(edi_4 + self->secondary_samples)
0041b4cf        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
0041b4e6        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(sine(var_44_1) * fconvert.t(var_4c_2) + fconvert.t(7f))
0041b503        *(&self->secondary_samples->transform.position.y + edi_4) = fconvert.s(fconvert.t(arg2) - cosine(var_44_1) * fconvert.t(var_4c_2))
0041b507        int32_t* eax_27 = edi_4 + self->primary_samples
0041b50e        *eax_27 = 0x3f800000
0041b514        eax_27[1] = 0
0041b51b        eax_27[2] = 0
0041b521        *(&self->primary_samples->transform.basis_up + edi_4) = 0
0041b528        void* eax_29 = self->primary_samples + edi_4
0041b52d        *(eax_29 + 0x14) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(eax_29 + 0x34)))
0041b530        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041b540        *(&primary_samples_2->transform.basis_up.z + edi_4) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&primary_samples_2->transform.position.z + edi_4)))
0041b54a        normalize_vector(&self->primary_samples->transform.basis_up + edi_4)
0041b552        struct Vec3* lhs = self->primary_samples + edi_4
0041b55e        cross_vectors(lhs + 0x20, lhs, lhs + 0x10)
0041b570        int32_t* edx_23 = edi_4 + self->secondary_samples
0041b576        *edx_23 = 0x3f800000
0041b57c        edx_23[1] = 0
0041b57f        edx_23[2] = 0
0041b585        *(&self->secondary_samples->transform.basis_up + edi_4) = 0
0041b589        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
0041b593        *(&secondary_samples_2->transform.basis_up.y + edi_4) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(&secondary_samples_2->transform.position.y + edi_4)))
0041b596        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041b5a5        *(&secondary_samples->transform.basis_up.z + edi_4) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&secondary_samples->transform.position.z + edi_4)))
0041b5af        normalize_vector(&self->secondary_samples->transform.basis_up + edi_4)
0041b5b9        struct Vec3* lhs_1 = edi_4 + self->secondary_samples
0041b5c4        cross_vectors(lhs_1 + 0x20, lhs_1, lhs_1 + 0x10)
0041b5d2        edi_4 += 0xa8
0041b5d8        bool cond:4_1 = arg3 + 1 s< eax_1
0041b5da        arg3 += 1
0041b5de        if (not(cond:4_1))
0041b5de        break
0041b3d4        ecx_23 = var_40_1
0041b5e7        int32_t i_2 = 0
0041b5ec        if (self->segment_count - 1 s> 0)
0041b5f2        void* edi_5 = nullptr
0041b5f7        void* eax_37 = self->primary_samples + edi_5
0041b615        float var_2c_1 = fconvert.s(fconvert.t(*(eax_37 + 0xdc)) - fconvert.t(*(eax_37 + 0x34)))
0041b61c        long double x87_r7_58 = fconvert.t(*(eax_37 + 0xe0)) - fconvert.t(*(eax_37 + 0x38))
0041b623        *(eax_37 + 0x80) = fconvert.s(fconvert.t(*(eax_37 + 0xd8)) - fconvert.t(*(eax_37 + 0x30)))
0041b625        *(eax_37 + 0x84) = var_2c_1
0041b630        *(eax_37 + 0x88) = fconvert.s(x87_r7_58)
0041b645        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041b64c        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041b670        float var_38_1 = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_5)))
0041b677        long double x87_r7_65 = fconvert.t(*(edi_5 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_5))
0041b67e        *(&secondary_samples_1->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_5)))
0041b680        *(&secondary_samples_1->delta_dir_to_next.y + edi_5) = var_38_1
0041b68b        *(&secondary_samples_1->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_65)
0041b6a0        i_2 += 1
0041b6a1        *(&self->secondary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_5))
0041b6ab        edi_5 += 0xa8
0041b6b4        do while (i_2 s< self->segment_count - 1)
0041b6e4        int32_t* edx_33 = &self->primary_samples[self->segment_count] - 0x28
0041b6f8        *edx_33 = 0
0041b706        edx_33[1] = 0
0041b709        edx_33[2] = 0x3f800000
0041b71b        int32_t var_28_2 = 0x3f800000
0041b727        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041b73d        int32_t* ecx_54 = &self->secondary_samples[self->segment_count] - 0x28
0041b745        *ecx_54 = 0
0041b74b        ecx_54[1] = 0
0041b750        ecx_54[2] = 0x3f800000
0041b765        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041b778        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0041b78a        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0041b78f        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0041b792        int32_t i_3 = 0
0041b794        struct Vec3* vertices = strip_mesh->vertices
0041b797        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0041b7a7        if (self->segment_count s>= 0)
0041b7ad        int32_t edx_36 = 0
0041b7af        int32_t var_48_1 = 0
0041b7b3        uint32_t width_cells = self->width_cells
0041b7b6        float ebx_3 = 0f
0041b7ba        arg2 = 0f
0041b7be        arg3 = width_cells
0041b7c2        if (width_cells s>= 0)
0041b7d5        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041b7de        long double x87_r7_68 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041b7e0        if (i_3 == self->segment_count)
0041b840        void* eax_68 = primary_samples_1 + edx_36
0041b896        float var_38_2 = fconvert.s(fconvert.t(*(eax_68 - 0x74)) + fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*(eax_68 - 0xa4)))))
0041b89e        int32_t* edx_38 = &vertices[(width_cells + 1) * i_3 i+ ebx_3]
0041b8a9        long double x87_r6_34 = fconvert.t(fconvert.s(fconvert.t(*(eax_68 - 0x70)) + fconvert.t(1f))) + x87_r7_68 * fconvert.t(*(eax_68 - 0xa0))
0041b8ab        *edx_38 = fconvert.s(fconvert.t(*(eax_68 - 0x78)) + fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*(eax_68 - 0xa8)))))
0041b8ad        edx_38[1] = var_38_2
0041b8b8        edx_38[2] = fconvert.s(x87_r6_34)
0041b8bb        edx_36 = var_48_1
0041b7e2        float* eax_60 = primary_samples_1 + edx_36
0041b80a        float var_2c_2 = fconvert.s(fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(eax_60[1]))) + fconvert.t(eax_60[0xd]))
0041b817        float var_28_3 = fconvert.s(x87_r7_68 * fconvert.t(eax_60[2]) + fconvert.t(eax_60[0xe]))
0041b824        int32_t* ecx_63 = &vertices[(width_cells + 1) * i_3 i+ ebx_3]
0041b82b        *ecx_63 = fconvert.s(fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*eax_60))) + fconvert.t(eax_60[0xc]))
0041b831        ecx_63[1] = var_2c_2
0041b838        ecx_63[2] = var_28_3
0041b8c1        width_cells = self->width_cells
0041b8c4        ebx_3 += 1
0041b8c7        arg2 = ebx_3
0041b8cb        arg3 = width_cells
0041b8cf        do while (ebx_3 s<= width_cells)
0041b8d8        i_3 += 1
0041b8d9        edx_36 += 0xa8
0041b8e1        var_48_1 = edx_36
0041b8e5        do while (i_3 s<= self->segment_count)
0041b8ee        int32_t i_4 = 0
0041b8f2        if (self->segment_count s> 0)
0041b8fb        int32_t j = 0
0041b8ff        arg2 = 0f
0041b903        if (self->width_cells s> 0)
0041b90b        int32_t eax_79 = i_4 & 0x80000007
0041b910        if (eax_79 s< 0)
0041b916        eax_79 = ((eax_79 - 1) | 0xfffffff8) + 1
0041b92a        arg3 = fconvert.s(float.t(eax_79) * fconvert.t(0.125f))
0041b938        float var_54_1 = fconvert.s(float.t(eax_79 + 1) * fconvert.t(0.125f))
0041b947        int32_t ecx_66 = 0
0041b94d        int32_t var_48_2 = 0
0041b957        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041b965        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041b97b        while (true)
0041b97b        int32_t eax_86 = ecx_66 + ((self->width_cells * i_4 + j) << 1)
0041b97e        if (ecx_66 != 0)
0041ba45        int16_t* ebp_2 = &facequads[eax_86]
0041ba48        *ebp_2 = 0
0041ba4e        ecx_66.w = self->width_cells.w
0041ba52        ecx_66.w += 1
0041ba5b        ebp_2[1] = ecx_66.w * i_4.w + j.w + 1
0041ba5f        struct ObjectFaceQuad* eax_94
0041ba5f        eax_94.w = self->width_cells.w
0041ba63        eax_94.w += 1
0041ba6a        ebp_2[2] = eax_94.w * i_4.w + j.w
0041ba7c        ebp_2[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
0041ba94        ebp_2[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
0041ba98        char* texture_path_1
0041ba98        char* arg5
0041ba98        if (((j.b ^ i_4.b) & 1) != 0)
0041bb30        texture_path_1 = arg5
0041baa5        texture_path_1 = arg5
0041bab8        *(ebp_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0041babf        *(ebp_2 + 0x10) = var_50_1
0041bac2        *(ebp_2 + 0x14) = arg3
0041bac7        *(ebp_2 + 0x18) = arg2
0041bad0        *(ebp_2 + 0x1c) = arg3
0041bad7        *(ebp_2 + 0x20) = arg2
0041bada        *(ebp_2 + 0x24) = var_54_1
0041badf        *(ebp_2 + 0x28) = var_50_1
0041bae2        *(ebp_2 + 0x2c) = var_54_1
0041b992        int16_t* ebp_1 = &facequads[eax_86]
0041b995        *ebp_1 = 0
0041b99b        eax_86.w = self->width_cells.w
0041b99f        eax_86.w += 1
0041b9a6        ebp_1[1] = eax_86.w * i_4.w + j.w
0041b9aa        int32_t ecx_68
0041b9aa        ecx_68.w = self->width_cells.w
0041b9ae        ecx_68.w += 1
0041b9ba        ebp_1[2] = ecx_68.w * i_4.w + j.w + 1
0041b9cb        ebp_1[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
0041b9e1        ebp_1[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
0041b9e5        char* texture_path
0041b9e5        if (((j.b ^ i_4.b) & 1) != 0)
0041ba34        texture_path = texture_b
0041b9eb        texture_path = texture_b
0041b9fe        *(ebp_1 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0041ba05        *(ebp_1 + 0x10) = arg2
0041ba08        *(ebp_1 + 0x14) = arg3
0041ba0d        *(ebp_1 + 0x18) = var_50_1
0041ba16        *(ebp_1 + 0x1c) = arg3
0041ba1d        *(ebp_1 + 0x20) = var_50_1
0041ba20        *(ebp_1 + 0x24) = var_54_1
0041ba25        *(ebp_1 + 0x28) = arg2
0041ba28        *(ebp_1 + 0x2c) = var_54_1
0041baea        bool cond:14_1 = var_48_2 + 1 s< 2
0041baed        var_48_2 += 1
0041baf1        if (not(cond:14_1))
0041baf1        break
0041b96b        ecx_66 = var_48_2
0041baf7        j += 1
0041bb00        arg2 = j
0041bb04        do while (j s< self->width_cells)
0041bb0f        i_4 += 1
0041bb12        do while (i_4 s< self->segment_count)
0041bb26        return finalize_path_template(self)
