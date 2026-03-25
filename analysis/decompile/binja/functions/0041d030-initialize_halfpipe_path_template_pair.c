/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_halfpipe_path_template_pair @ 0x41d030 */

0041d046        int32_t i_3 = 0
0041d049        self->kind = 0x10
0041d050        self->is_mirrored_x = 0
0041d054        self->side_exit_mode = 0
0041d057        self->width_cells = arg4
0041d05a        int16_t x87control
0041d05a        int32_t secondary_samples_4 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(4f))
0041d05f        int32_t ebp = secondary_samples_4 + 7
0041d068        self->width_or_scale = 1f
0041d076        self->segment_count = ebp + 7
0041d07d        self->segment_count_f = fconvert.s(float.t(ebp + 7))
0041d080        long double x87_r7_3 = float.t(secondary_samples_4)
0041d08e        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.0954929665f))
0041d092        allocate_path_nodes(self)
0041d097        self->special_runtime_flag_9c = 0
0041d09d        arg4 = 0
0041d0a1        int32_t i = 0
0041d15c        while (i s< 0x498)
0041d0b5        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
0041d0bf        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041d0c9        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041d0d3        *(&self->primary_samples->special_scalar + i) = 0
0041d0dd        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041d0ed        set_matrix_identity(self->primary_samples + i)
0041d0f5        void* eax_4 = self->primary_samples + i
0041d0f7        long double x87_r7_8 = float.t(arg4)
0041d101        *(eax_4 + 0x30) = *(eax_4 + 0x90)
0041d10b        *(&self->primary_samples->transform.position.y + i) = 0
0041d114        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_8)
0041d11b        set_matrix_identity(i + self->secondary_samples)
0041d131        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0041d138        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0041d143        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_8)))
0041d14b        i += 0xa8
0041d158        arg4 += 1
0041d174        arg4 = ebp
0041d17b        int32_t edi_3 = ebp * 0xa8
0041d23e        struct PathTemplateSample* secondary_samples
0041d196        *(&self->primary_samples->center_x + edi_3) = fconvert.s(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0041d1a0        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041d1aa        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041d1b4        *(&self->primary_samples->special_scalar + edi_3) = 0
0041d1be        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041d1ce        set_matrix_identity(self->primary_samples + edi_3)
0041d1d3        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041d1d6        long double x87_r7_13 = float.t(arg4)
0041d1e8        *(&primary_samples_2->transform.position + edi_3) = *(&primary_samples_2->center_x + edi_3)
0041d1f0        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041d1f7        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_13)
0041d1fe        set_matrix_identity(edi_3 + self->secondary_samples)
0041d214        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0041d218        secondary_samples = self->secondary_samples
0041d21f        *(&secondary_samples->transform.position.y + edi_3) = 0x3efae148
0041d22a        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0041d22e        edi_3 += 0xa8
0041d234        ebp += 1
0041d237        arg4 = ebp
0041d23e        do while (0xfffffff9 - secondary_samples_4 + ebp s< 7)
0041d248        arg4 = 0
0041d24e        if (secondary_samples_4 s> 0)
0041d254        void* edi_4 = 0x498
0041d4f5        bool cond:4_1
0041d25d        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041d260        struct PathTemplateSample* secondary_samples_3 = secondary_samples
0041d26b        float var_44_1 = fconvert.s(float.t(arg4) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(x87_r7_3)))
0041d28a        *(&primary_samples_4->center_x + edi_4) = fconvert.s(cosine(fconvert.s(fconvert.t(var_44_1) * fconvert.t(0.5f))) * fconvert.t(primary_samples_4->center_x))
0041d294        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041d29e        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0041d2a8        *(&self->primary_samples->special_scalar + edi_4) = 0
0041d2b2        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041d2c2        set_matrix_identity(self->primary_samples + edi_4)
0041d2c7        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041d2d9        *(&primary_samples_3->transform.position + edi_4) = *(&primary_samples_3->center_x + edi_4)
0041d300        *(&self->primary_samples->transform.position.y + edi_4) = fconvert.s((fconvert.t(1f) - cosine(var_44_1)) * fconvert.t(arg2) * fconvert.t(arg3))
0041d304        long double x87_r7_26 = float.t(arg4 + 7)
0041d30f        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_26)
0041d31a        set_matrix_identity(edi_4 + self->secondary_samples)
0041d32d        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
0041d356        *(&self->secondary_samples->transform.position.y + edi_4) = fconvert.s((fconvert.t(1f) - cosine(var_44_1)) * fconvert.t(arg2) * fconvert.t(arg3) + fconvert.t(0.49000001f))
0041d361        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_26)))
0041d365        if (edi_4 s<= 0x498)
0041d4cc        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
0041d4db        set_matrix_rotation_identity(edi_4 + self->secondary_samples - 0xa8)
0041d382        int32_t* edx_16 = self->primary_samples + edi_4 - 0xa8
0041d395        *edx_16 = 0x3f800000
0041d39b        edx_16[1] = 0
0041d39e        edx_16[2] = 0
0041d3a1        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041d3c5        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position.y + edi_4)) - fconvert.t(*(primary_samples_1 + edi_4 - 0x74)))
0041d3cf        long double x87_r7_38 = fconvert.t(*(&primary_samples_1->transform.position.z + edi_4)) - fconvert.t(*(primary_samples_1 + edi_4 - 0x70))
0041d3d6        *(primary_samples_1 + edi_4 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position + edi_4)) - fconvert.t(*(primary_samples_1 + edi_4 - 0x78)))
0041d3d8        *(primary_samples_1 + edi_4 - 0x84) = var_2c_1
0041d3e3        *(primary_samples_1 + edi_4 - 0x80) = fconvert.s(x87_r7_38)
0041d3f0        normalize_vector(self->primary_samples + edi_4 - 0x88)
0041d3fa        void* eax_26 = self->primary_samples + edi_4
0041d411        cross_vectors(eax_26 - 0x98, eax_26 - 0x88, eax_26 - 0xa8)
0041d42d        int32_t* eax_27 = edi_4 + self->secondary_samples - 0xa8
0041d440        *eax_27 = 0x3f800000
0041d446        eax_27[1] = 0
0041d449        eax_27[2] = 0
0041d44c        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
0041d470        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position.y + edi_4)) - fconvert.t(*(edi_4 + secondary_samples_2 - 0x74)))
0041d47a        long double x87_r7_46 = fconvert.t(*(&secondary_samples_2->transform.position.z + edi_4)) - fconvert.t(*(edi_4 + secondary_samples_2 - 0x70))
0041d481        *(edi_4 + secondary_samples_2 - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position + edi_4)) - fconvert.t(*(edi_4 + secondary_samples_2 - 0x78)))
0041d483        *(edi_4 + secondary_samples_2 - 0x84) = var_14_1
0041d48e        *(edi_4 + secondary_samples_2 - 0x80) = fconvert.s(x87_r7_46)
0041d49b        normalize_vector(edi_4 + self->secondary_samples - 0x88)
0041d4a3        void* eax_31 = self->secondary_samples + edi_4
0041d4bb        cross_vectors(eax_31 - 0x98, eax_31 - 0x88, eax_31 - 0xa8)
0041d4e4        secondary_samples = secondary_samples_4
0041d4e9        edi_4 += 0xa8
0041d4ef        cond:4_1 = arg4 + 1 s< secondary_samples
0041d4f1        arg4 += 1
0041d4f5        do while (cond:4_1)
0041d4fe        int32_t i_1 = 0
0041d503        if (self->segment_count - 1 s> 0)
0041d509        void* edi_5 = nullptr
0041d50e        void* eax_36 = self->primary_samples + edi_5
0041d52c        float var_14_2 = fconvert.s(fconvert.t(*(eax_36 + 0xdc)) - fconvert.t(*(eax_36 + 0x34)))
0041d533        long double x87_r7_54 = fconvert.t(*(eax_36 + 0xe0)) - fconvert.t(*(eax_36 + 0x38))
0041d53a        *(eax_36 + 0x80) = fconvert.s(fconvert.t(*(eax_36 + 0xd8)) - fconvert.t(*(eax_36 + 0x30)))
0041d53c        *(eax_36 + 0x84) = var_14_2
0041d547        *(eax_36 + 0x88) = fconvert.s(x87_r7_54)
0041d55c        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041d563        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041d587        float var_20_1 = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_5)))
0041d58e        long double x87_r7_61 = fconvert.t(*(edi_5 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_5))
0041d595        *(&secondary_samples_1->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_5)))
0041d597        *(&secondary_samples_1->delta_dir_to_next.y + edi_5) = var_20_1
0041d5a2        *(&secondary_samples_1->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_61)
0041d5b7        i_1 += 1
0041d5b8        *(&self->secondary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_5))
0041d5c2        edi_5 += 0xa8
0041d5cb        do while (i_1 s< self->segment_count - 1)
0041d5fb        int32_t* edx_32 = &self->primary_samples[self->segment_count] - 0x28
0041d60f        *edx_32 = 0
0041d61d        edx_32[1] = 0
0041d620        edx_32[2] = 0x3f800000
0041d632        int32_t var_10_3 = 0x3f800000
0041d63e        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041d654        int32_t* ecx_54 = &self->secondary_samples[self->segment_count] - 0x28
0041d65c        *ecx_54 = 0
0041d662        ecx_54[1] = 0
0041d667        ecx_54[2] = 0x3f800000
0041d67c        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041d68f        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0041d6a1        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0041d6a6        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0041d6a9        int32_t i_2 = 0
0041d6ab        struct Vec3* vertices = strip_mesh->vertices
0041d6ae        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0041d6b4        arg4 = vertices
0041d6be        if (self->segment_count s>= 0)
0041d6c4        uint32_t width_cells = self->width_cells
0041d6c7        float edi_6 = 0f
0041d6cb        arg2 = 0f
0041d6cf        arg3 = width_cells
0041d6d3        if (width_cells s>= 0)
0041d6e6        struct PathTemplateSample* primary_samples = self->primary_samples
0041d6ef        long double x87_r7_64 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041d6f1        int32_t* eax_63
0041d6f1        float ecx_65
0041d6f1        if (i_2 == self->segment_count)
0041d748        void* eax_64 = primary_samples + i_3
0041d759        vertices = arg4
0041d79e        float var_20_2 = fconvert.s(fconvert.t(*(eax_64 - 0x74)) + fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*(eax_64 - 0xa4)))))
0041d7a6        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_64 - 0x70)) + fconvert.t(1f))) + x87_r7_64 * fconvert.t(*(eax_64 - 0xa0))
0041d7a8        eax_63 = &vertices[(width_cells + 1) * i_2 i+ edi_6]
0041d7b0        *eax_63 = fconvert.s(fconvert.t(*(eax_64 - 0x78)) + fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*(eax_64 - 0xa8)))))
0041d7ba        eax_63[1] = var_20_2
0041d7bd        ecx_65 = fconvert.s(x87_r6_20)
0041d6f3        float* eax_59 = primary_samples + i_3
0041d71b        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(eax_59[1]))) + fconvert.t(eax_59[0xd]))
0041d728        float var_10_4 = fconvert.s(x87_r7_64 * fconvert.t(eax_59[2]) + fconvert.t(eax_59[0xe]))
0041d731        eax_63 = &vertices[(width_cells + 1) * i_2 i+ edi_6]
0041d739        *eax_63 = fconvert.s(fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*eax_59))) + fconvert.t(eax_59[0xc]))
0041d73f        eax_63[1] = var_14_3
0041d742        ecx_65 = var_10_4
0041d7c3        eax_63[2] = ecx_65
0041d7c6        width_cells = self->width_cells
0041d7c9        edi_6 += 1
0041d7ca        arg3 = width_cells
0041d7d0        arg2 = edi_6
0041d7d4        do while (edi_6 s<= width_cells)
0041d7dd        i_2 += 1
0041d7de        i_3 += 0xa8
0041d7e6        do while (i_2 s<= self->segment_count)
0041d7ec        i_3 = 0
0041d7f3        if (self->segment_count s> 0)
0041d7fc        int32_t j = 0
0041d800        arg2 = 0f
0041d804        if (self->width_cells s> 0)
0041d80c        float eax_72 = i_3 & 0x80000007
0041d811        if (eax_72 s< 0)
0041d817        eax_72 = ((eax_72 i- 1) | 0xfffffff8) + 1
0041d82b        arg3 = fconvert.s(float.t(eax_72) * fconvert.t(0.125f))
0041d839        float var_4c_1 = fconvert.s(float.t(eax_72 i+ 1) * fconvert.t(0.125f))
0041d844        int32_t ecx_69 = 0
0041d84a        int32_t var_48_1 = 0
0041d854        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041d862        arg4 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041d876        while (true)
0041d876        int32_t eax_79 = ecx_69 + ((self->width_cells * i_3 + j) << 1)
0041d879        if (ecx_69 != 0)
0041d940        int16_t* ebp_4 = &facequads[eax_79]
0041d943        *ebp_4 = 0
0041d949        ecx_69.w = self->width_cells.w
0041d94d        ecx_69.w += 1
0041d956        ebp_4[1] = ecx_69.w * i_3.w + j.w + 1
0041d95a        struct ObjectFaceQuad* eax_87
0041d95a        eax_87.w = self->width_cells.w
0041d95e        eax_87.w += 1
0041d965        ebp_4[2] = eax_87.w * i_3.w + j.w
0041d977        ebp_4[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0041d98f        ebp_4[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0041d993        char* texture_path_1
0041d993        char* texture_path_2
0041d993        if (((j.b ^ i_3.b) & 1) != 0)
0041da23        texture_path_1 = texture_path_2
0041d99d        texture_path_1 = texture_path_2
0041d9b0        *(ebp_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0041d9b7        *(ebp_4 + 0x10) = arg4
0041d9ba        *(ebp_4 + 0x14) = arg3
0041d9bf        *(ebp_4 + 0x18) = arg2
0041d9c8        *(ebp_4 + 0x1c) = arg3
0041d9cf        *(ebp_4 + 0x20) = arg2
0041d9d2        *(ebp_4 + 0x24) = var_4c_1
0041d9d7        *(ebp_4 + 0x28) = arg4
0041d9da        *(ebp_4 + 0x2c) = var_4c_1
0041d88d        int16_t* ebp_3 = &facequads[eax_79]
0041d890        *ebp_3 = 0
0041d896        eax_79.w = self->width_cells.w
0041d89a        eax_79.w += 1
0041d8a1        ebp_3[1] = eax_79.w * i_3.w + j.w
0041d8a5        int32_t ecx_71
0041d8a5        ecx_71.w = self->width_cells.w
0041d8a9        ecx_71.w += 1
0041d8b5        ebp_3[2] = ecx_71.w * i_3.w + j.w + 1
0041d8c6        ebp_3[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0041d8dc        ebp_3[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0041d8e0        char* texture_path
0041d8e0        if (((j.b ^ i_3.b) & 1) != 0)
0041d92f        texture_path = texture_b
0041d8e6        texture_path = texture_b
0041d8f9        *(ebp_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0041d900        *(ebp_3 + 0x10) = arg2
0041d903        *(ebp_3 + 0x14) = arg3
0041d908        *(ebp_3 + 0x18) = arg4
0041d911        *(ebp_3 + 0x1c) = arg3
0041d918        *(ebp_3 + 0x20) = arg4
0041d91b        *(ebp_3 + 0x24) = var_4c_1
0041d920        *(ebp_3 + 0x28) = arg2
0041d923        *(ebp_3 + 0x2c) = var_4c_1
0041d9e2        bool cond:12_1 = var_48_1 + 1 s< 2
0041d9e5        var_48_1 += 1
0041d9e9        if (not(cond:12_1))
0041d9e9        break
0041d868        ecx_69 = var_48_1
0041d9ef        j += 1
0041d9f8        arg2 = j
0041d9fc        do while (j s< self->width_cells)
0041da05        i_3 += 1
0041da08        do while (i_3 s< self->segment_count)
0041da1c        return finalize_path_template_record(self)
