/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_hump_path_template_pair @ 0x41d030 */

0041d046        int32_t i_3 = 0
0041d049        self->kind = PATH_TEMPLATE_KIND_FAMILY_10
0041d050        self->__offset(0x3c).b = 0
0041d054        self->__offset(0x40).d = 0
0041d057        self->__offset(0x54).d = arg4
0041d05a        int16_t x87control
0041d05a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(4f))
0041d05f        int32_t ebp = eax_1 + 7
0041d068        self->__offset(0x50).d = 0x3f800000
0041d076        self->segment_count = ebp + 7
0041d07d        self->segment_count_f = fconvert.s(float.t(ebp + 7))
0041d080        long double x87_r7_3 = float.t(eax_1)
0041d08e        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.0954929665f))
0041d092        allocate_path_template_samples(self)
0041d097        self->__offset(0x9c).b = 0
0041d09d        arg4 = 0
0041d0a1        int32_t i = 0
0041d15c        while (i s< 0x498)
0041d0b5        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->__offset(0x54).d) * fconvert.t(0.5f) - fconvert.t(4f))
0041d0bf        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041d0c9        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041d0d3        *(&self->primary_samples->special_scalar + i) = 0
0041d0dd        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041d0ed        set_matrix_identity(self->primary_samples + i)
0041d0f5        void* eax_5 = self->primary_samples + i
0041d0f7        long double x87_r7_8 = float.t(arg4)
0041d101        *(eax_5 + 0x30) = *(eax_5 + 0x90)
0041d10b        *(&self->primary_samples->transform.position.y + i) = 0
0041d114        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_8)
0041d11b        set_matrix_identity(i + self->__offset(0x5c).d)
0041d131        *(i + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + i)
0041d138        *(i + self->__offset(0x5c).d + 0x34) = 0x3efae148
0041d143        *(i + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_8)))
0041d14b        i += 0xa8
0041d158        arg4 += 1
0041d174        arg4 = ebp
0041d17b        int32_t edi_3 = ebp * 0xa8
0041d23e        int32_t ecx_19
0041d196        *(&self->primary_samples->center_x + edi_3) = fconvert.s(fconvert.t(4f) - float.t(self->__offset(0x54).d) * fconvert.t(0.5f))
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
0041d1fe        set_matrix_identity(edi_3 + self->__offset(0x5c).d)
0041d214        *(edi_3 + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + edi_3)
0041d218        ecx_19 = self->__offset(0x5c).d
0041d21f        *(edi_3 + ecx_19 + 0x34) = 0x3efae148
0041d22a        *(edi_3 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0041d22e        edi_3 += 0xa8
0041d234        ebp += 1
0041d237        arg4 = ebp
0041d23e        do while (0xfffffff9 - eax_1 + ebp s< 7)
0041d248        arg4 = 0
0041d24e        if (eax_1 s> 0)
0041d254        void* edi_4 = 0x498
0041d4f5        bool cond:4_1
0041d25d        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041d260        int32_t var_60_1 = ecx_19
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
0041d31a        set_matrix_identity(edi_4 + self->__offset(0x5c).d)
0041d32d        *(edi_4 + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + edi_4)
0041d356        *(edi_4 + self->__offset(0x5c).d + 0x34) = fconvert.s((fconvert.t(1f) - cosine(var_44_1)) * fconvert.t(arg2) * fconvert.t(arg3) + fconvert.t(0.49000001f))
0041d361        *(edi_4 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_26)))
0041d365        if (edi_4 s<= 0x498)
0041d4cc        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
0041d4db        set_matrix_rotation_identity(edi_4 + self->__offset(0x5c).d - 0xa8)
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
0041d3fa        void* eax_27 = self->primary_samples + edi_4
0041d411        cross_vectors(eax_27 - 0x98, eax_27 - 0x88, eax_27 - 0xa8)
0041d42d        int32_t* eax_28 = edi_4 + self->__offset(0x5c).d - 0xa8
0041d440        *eax_28 = 0x3f800000
0041d446        eax_28[1] = 0
0041d449        eax_28[2] = 0
0041d44c        int32_t edx_21 = self->__offset(0x5c).d
0041d470        float var_14_1 = fconvert.s(fconvert.t(*(edi_4 + edx_21 + 0x34)) - fconvert.t(*(edi_4 + edx_21 - 0x74)))
0041d47a        long double x87_r7_46 = fconvert.t(*(edi_4 + edx_21 + 0x38)) - fconvert.t(*(edi_4 + edx_21 - 0x70))
0041d481        *(edi_4 + edx_21 - 0x88) = fconvert.s(fconvert.t(*(edi_4 + edx_21 + 0x30)) - fconvert.t(*(edi_4 + edx_21 - 0x78)))
0041d483        *(edi_4 + edx_21 - 0x84) = var_14_1
0041d48e        *(edi_4 + edx_21 - 0x80) = fconvert.s(x87_r7_46)
0041d49b        normalize_vector(edi_4 + self->__offset(0x5c).d - 0x88)
0041d4a3        void* eax_32 = self->__offset(0x5c).d + edi_4
0041d4bb        cross_vectors(eax_32 - 0x98, eax_32 - 0x88, eax_32 - 0xa8)
0041d4e4        ecx_19 = eax_1
0041d4e9        edi_4 += 0xa8
0041d4ef        cond:4_1 = arg4 + 1 s< ecx_19
0041d4f1        arg4 += 1
0041d4f5        do while (cond:4_1)
0041d4fe        int32_t i_1 = 0
0041d503        if (self->segment_count - 1 s> 0)
0041d509        void* edi_5 = nullptr
0041d50e        void* eax_37 = self->primary_samples + edi_5
0041d52c        float var_14_2 = fconvert.s(fconvert.t(*(eax_37 + 0xdc)) - fconvert.t(*(eax_37 + 0x34)))
0041d533        long double x87_r7_54 = fconvert.t(*(eax_37 + 0xe0)) - fconvert.t(*(eax_37 + 0x38))
0041d53a        *(eax_37 + 0x80) = fconvert.s(fconvert.t(*(eax_37 + 0xd8)) - fconvert.t(*(eax_37 + 0x30)))
0041d53c        *(eax_37 + 0x84) = var_14_2
0041d547        *(eax_37 + 0x88) = fconvert.s(x87_r7_54)
0041d55c        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041d563        int32_t ecx_46 = self->__offset(0x5c).d
0041d587        float var_20_1 = fconvert.s(fconvert.t(*(edi_5 + ecx_46 + 0xdc)) - fconvert.t(*(edi_5 + ecx_46 + 0x34)))
0041d58e        long double x87_r7_61 = fconvert.t(*(edi_5 + ecx_46 + 0xe0)) - fconvert.t(*(edi_5 + ecx_46 + 0x38))
0041d595        *(edi_5 + ecx_46 + 0x80) = fconvert.s(fconvert.t(*(edi_5 + ecx_46 + 0xd8)) - fconvert.t(*(edi_5 + ecx_46 + 0x30)))
0041d597        *(edi_5 + ecx_46 + 0x84) = var_20_1
0041d5a2        *(edi_5 + ecx_46 + 0x88) = fconvert.s(x87_r7_61)
0041d5b7        i_1 += 1
0041d5b8        *(edi_5 + self->__offset(0x5c).d + 0x8c) = fconvert.s(normalize_vector(edi_5 + self->__offset(0x5c).d + 0x80))
0041d5c2        edi_5 += 0xa8
0041d5cb        do while (i_1 s< self->segment_count - 1)
0041d5fb        int32_t* edx_33 = &self->primary_samples[self->segment_count] - 0x28
0041d60f        *edx_33 = 0
0041d61d        edx_33[1] = 0
0041d620        edx_33[2] = 0x3f800000
0041d632        int32_t var_10_3 = 0x3f800000
0041d63e        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041d654        int32_t* ecx_56 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
0041d65c        *ecx_56 = 0
0041d662        ecx_56[1] = 0
0041d667        ecx_56[2] = 0x3f800000
0041d67c        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
0041d68f        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
0041d6a1        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
0041d6a6        void* eax_58 = self->_pad_00[0x24].d
0041d6a9        int32_t i_2 = 0
0041d6ab        int32_t ebp_2 = *(eax_58 + 0x38)
0041d6ae        int32_t ecx_64 = *(eax_58 + 0x5c)
0041d6b4        arg4 = ebp_2
0041d6be        if (self->segment_count s>= 0)
0041d6c4        float ecx_65 = self->__offset(0x54).d
0041d6c7        float edi_6 = 0f
0041d6cb        arg2 = 0f
0041d6cf        arg3 = ecx_65
0041d6d3        if (ecx_65 s>= 0)
0041d6e6        struct PathTemplateSample* primary_samples = self->primary_samples
0041d6ef        long double x87_r7_64 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041d6f1        int32_t eax_65
0041d6f1        float ecx_69
0041d6f1        if (i_2 == self->segment_count)
0041d748        void* eax_66 = primary_samples + i_3
0041d759        ebp_2 = arg4
0041d79e        float var_20_2 = fconvert.s(fconvert.t(*(eax_66 - 0x74)) + fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*(eax_66 - 0xa4)))))
0041d7a6        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_66 - 0x70)) + fconvert.t(1f))) + x87_r7_64 * fconvert.t(*(eax_66 - 0xa0))
0041d7a8        eax_65 = ebp_2 + ((ecx_65 i+ 1) * i_2 i+ edi_6) * 0xc
0041d7b0        *eax_65 = fconvert.s(fconvert.t(*(eax_66 - 0x78)) + fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*(eax_66 - 0xa8)))))
0041d7ba        *(eax_65 + 4) = var_20_2
0041d7bd        ecx_69 = fconvert.s(x87_r6_20)
0041d6f3        float* eax_61 = primary_samples + i_3
0041d71b        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(eax_61[1]))) + fconvert.t(eax_61[0xd]))
0041d728        float var_10_4 = fconvert.s(x87_r7_64 * fconvert.t(eax_61[2]) + fconvert.t(eax_61[0xe]))
0041d731        eax_65 = ebp_2 + ((ecx_65 i+ 1) * i_2 i+ edi_6) * 0xc
0041d739        *eax_65 = fconvert.s(fconvert.t(fconvert.s(x87_r7_64 * fconvert.t(*eax_61))) + fconvert.t(eax_61[0xc]))
0041d73f        *(eax_65 + 4) = var_14_3
0041d742        ecx_69 = var_10_4
0041d7c3        *(eax_65 + 8) = ecx_69
0041d7c6        ecx_65 = self->__offset(0x54).d
0041d7c9        edi_6 += 1
0041d7ca        arg3 = ecx_65
0041d7d0        arg2 = edi_6
0041d7d4        do while (edi_6 s<= ecx_65)
0041d7dd        i_2 += 1
0041d7de        i_3 += 0xa8
0041d7e6        do while (i_2 s<= self->segment_count)
0041d7ec        i_3 = 0
0041d7f3        if (self->segment_count s> 0)
0041d7fc        int32_t j = 0
0041d800        arg2 = 0f
0041d804        if (self->__offset(0x54).d s> 0)
0041d80c        float eax_74 = i_3 & 0x80000007
0041d811        if (eax_74 s< 0)
0041d817        eax_74 = ((eax_74 i- 1) | 0xfffffff8) + 1
0041d82b        arg3 = fconvert.s(float.t(eax_74) * fconvert.t(0.125f))
0041d839        float var_4c_1 = fconvert.s(float.t(eax_74 i+ 1) * fconvert.t(0.125f))
0041d844        int32_t ecx_73 = 0
0041d84a        int32_t var_48_1 = 0
0041d854        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041d862        arg4 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041d876        while (true)
0041d876        int32_t eax_81 = ecx_73 + ((self->__offset(0x54).d * i_3 + j) << 1)
0041d879        if (ecx_73 != 0)
0041d940        int16_t* ebp_5 = eax_81 * 0x30 + ecx_64
0041d943        *ebp_5 = 0
0041d949        ecx_73.w = self->__offset(0x54).w
0041d94d        ecx_73.w += 1
0041d956        ebp_5[1] = ecx_73.w * i_3.w + j.w + 1
0041d95a        int32_t eax_89
0041d95a        eax_89.w = self->__offset(0x54).w
0041d95e        eax_89.w += 1
0041d965        ebp_5[2] = eax_89.w * i_3.w + j.w
0041d977        ebp_5[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
0041d98f        ebp_5[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
0041d993        char* texture_path_1
0041d993        char* texture_path_2
0041d993        if (((j.b ^ i_3.b) & 1) != 0)
0041da23        texture_path_1 = texture_path_2
0041d99d        texture_path_1 = texture_path_2
0041d9b0        *(ebp_5 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0041d9b7        *(ebp_5 + 0x10) = arg4
0041d9ba        *(ebp_5 + 0x14) = arg3
0041d9bf        *(ebp_5 + 0x18) = arg2
0041d9c8        *(ebp_5 + 0x1c) = arg3
0041d9cf        *(ebp_5 + 0x20) = arg2
0041d9d2        *(ebp_5 + 0x24) = var_4c_1
0041d9d7        *(ebp_5 + 0x28) = arg4
0041d9da        *(ebp_5 + 0x2c) = var_4c_1
0041d88d        int16_t* ebp_4 = eax_81 * 0x30 + ecx_64
0041d890        *ebp_4 = 0
0041d896        eax_81.w = self->__offset(0x54).w
0041d89a        eax_81.w += 1
0041d8a1        ebp_4[1] = eax_81.w * i_3.w + j.w
0041d8a5        int32_t ecx_75
0041d8a5        ecx_75.w = self->__offset(0x54).w
0041d8a9        ecx_75.w += 1
0041d8b5        ebp_4[2] = ecx_75.w * i_3.w + j.w + 1
0041d8c6        ebp_4[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
0041d8dc        ebp_4[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
0041d8e0        char* texture_path
0041d8e0        if (((j.b ^ i_3.b) & 1) != 0)
0041d92f        texture_path = texture_b
0041d8e6        texture_path = texture_b
0041d8f9        *(ebp_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0041d900        *(ebp_4 + 0x10) = arg2
0041d903        *(ebp_4 + 0x14) = arg3
0041d908        *(ebp_4 + 0x18) = arg4
0041d911        *(ebp_4 + 0x1c) = arg3
0041d918        *(ebp_4 + 0x20) = arg4
0041d91b        *(ebp_4 + 0x24) = var_4c_1
0041d920        *(ebp_4 + 0x28) = arg2
0041d923        *(ebp_4 + 0x2c) = var_4c_1
0041d9e2        bool cond:12_1 = var_48_1 + 1 s< 2
0041d9e5        var_48_1 += 1
0041d9e9        if (not(cond:12_1))
0041d9e9        break
0041d868        ecx_73 = var_48_1
0041d9ef        j += 1
0041d9f8        arg2 = j
0041d9fc        do while (j s< self->__offset(0x54).d)
0041da05        i_3 += 1
0041da08        do while (i_3 s< self->segment_count)
0041da1c        return finalize_path_template(self)
