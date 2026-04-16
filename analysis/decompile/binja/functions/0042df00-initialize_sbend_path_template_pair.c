/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sbend_path_template_pair @ 0x42df00 */

0042df17        int32_t edi = 0
0042df19        self->kind = PATH_TEMPLATE_KIND_FAMILY_10
0042df20        self->__offset(0x3c).b = 0
0042df24        self->__offset(0x40).d = 0
0042df27        self->__offset(0x54).d = arg2
0042df2a        int16_t x87control
0042df2a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg3) * fconvert.t(3.14159274f))
0042df3f        self->__offset(0x50).d = 0x3f800000
0042df46        self->segment_count = eax_1 + 1
0042df4d        self->segment_count_f = fconvert.s(float.t(eax_1 + 1))
0042df50        allocate_path_template_samples(self)
0042df59        self->__offset(0x9c).b = 0
0042df62        if (arg5 == 0)
0042df81        self->primary_samples->center_x = fconvert.s(float.t(self->__offset(0x54).d) * fconvert.t(0.5f) - fconvert.t(4f))
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
0042dfce        set_matrix_identity(self->__offset(0x5c).d)
0042dfdb        arg5.d = 0
0042dfe5        *(self->__offset(0x5c).d + 0x30) = self->primary_samples->center_x
0042dfeb        *(self->__offset(0x5c).d + 0x34) = 0x3efae148
0042dff5        *(self->__offset(0x5c).d + 0x38) = 0
0042dff8        if (eax_1 s> 0)
0042e01a        int32_t ebx_1 = 0xa8
0042e1e1        bool cond:2_1
0042e02b        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042e03a        *(&primary_samples_1->center_x + ebx_1) = primary_samples_1->center_x
0042e048        *(&self->primary_samples->rotation_scalar_98 + ebx_1) = 0
0042e052        *(&self->primary_samples->rotation_scalar_94 + ebx_1) = 0
0042e05c        *(&self->primary_samples->special_scalar + ebx_1) = 0
0042e066        *(&self->primary_samples->lateral_scale + ebx_1) = 0x3f800000
0042e072        arg2 = fconvert.s(float.t(arg5.d) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(float.t(eax_1))))
0042e076        set_matrix_identity(self->primary_samples + ebx_1)
0042e07b        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042e082        int32_t ecx_12 = *(&primary_samples_2->center_x + ebx_1)
0042e091        int32_t var_5c_1 = ecx_12
0042e092        *(&primary_samples_2->transform.position + ebx_1) = ecx_12
0042e0b0        *(&self->primary_samples->transform.position.y + ebx_1) = fconvert.s((fconvert.t(1f) - cosine(fconvert.s(fconvert.t(arg2) * fconvert.t(0.5f)))) * fconvert.t(0.5f) * fconvert.t(arg3))
0042e0e8        *(&self->primary_samples->transform.position.z + ebx_1) = fconvert.s((fconvert.t(1f) - cosine(fconvert.s(fconvert.t(arg2) * fconvert.t(1.5f)))) * fconvert.t(0.5f) * fconvert.t(arg4) * fconvert.t(0.333333343f) + fconvert.t(1f))
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
0042e17a        __builtin_memcpy(self->__offset(0x5c).d + ebx_1, self->primary_samples + ebx_1, 0x40)
0042e17c        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042e18b        long double x87_r7_33 = fconvert.t(*(&primary_samples_3->transform.basis_up + ebx_1)) * fconvert.t(0.49000001f)
0042e19f        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_3->transform.basis_up.y + ebx_1)) * fconvert.t(0.49000001f))
0042e1a6        long double x87_r6_4 = fconvert.t(*(&primary_samples_3->transform.basis_up.z + ebx_1)) * fconvert.t(0.49000001f)
0042e1ac        float* eax_15 = self->__offset(0x5c).d + ebx_1 + 0x30
0042e1b4        ebx_1 += 0xa8
0042e1c0        *eax_15 = fconvert.s(x87_r7_33 + fconvert.t(*eax_15))
0042e1c9        eax_15[1] = fconvert.s(fconvert.t(var_20_1) + fconvert.t(eax_15[1]))
0042e1d3        eax_15[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_4)) + fconvert.t(eax_15[2]))
0042e1db        cond:2_1 = arg5.d + 1 s< eax_1
0042e1dd        arg5.d += 1
0042e1e1        do while (cond:2_1)
0042e1e7        edi = 0
0042e1ec        int32_t i = 0
0042e1f1        if (self->segment_count - 1 s> 0)
0042e1fa        void* eax_19 = self->primary_samples + edi
0042e218        float var_2c_2 = fconvert.s(fconvert.t(*(eax_19 + 0xdc)) - fconvert.t(*(eax_19 + 0x34)))
0042e21f        long double x87_r7_44 = fconvert.t(*(eax_19 + 0xe0)) - fconvert.t(*(eax_19 + 0x38))
0042e226        *(eax_19 + 0x80) = fconvert.s(fconvert.t(*(eax_19 + 0xd8)) - fconvert.t(*(eax_19 + 0x30)))
0042e228        *(eax_19 + 0x84) = var_2c_2
0042e233        *(eax_19 + 0x88) = fconvert.s(x87_r7_44)
0042e248        *(&self->primary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi))
0042e24f        void* ecx_23 = self->__offset(0x5c).d
0042e273        float var_38_1 = fconvert.s(fconvert.t(*(ecx_23 + edi + 0xdc)) - fconvert.t(*(ecx_23 + edi + 0x34)))
0042e27a        long double x87_r7_51 = fconvert.t(*(ecx_23 + edi + 0xe0)) - fconvert.t(*(ecx_23 + edi + 0x38))
0042e281        *(ecx_23 + edi + 0x80) = fconvert.s(fconvert.t(*(ecx_23 + edi + 0xd8)) - fconvert.t(*(ecx_23 + edi + 0x30)))
0042e283        *(ecx_23 + edi + 0x84) = var_38_1
0042e28e        *(ecx_23 + edi + 0x88) = fconvert.s(x87_r7_51)
0042e2a3        i += 1
0042e2a4        *(self->__offset(0x5c).d + edi + 0x8c) = fconvert.s(normalize_vector(self->__offset(0x5c).d + edi + 0x80))
0042e2ae        edi += 0xa8
0042e2b7        do while (i s< self->segment_count - 1)
0042e2e7        int32_t* edx_21 = &self->primary_samples[self->segment_count] - 0x28
0042e2fb        *edx_21 = 0
0042e311        edx_21[1] = 0
0042e314        edx_21[2] = 0x3f800000
0042e329        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042e33f        int32_t* edx_23 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
0042e34b        *edx_23 = 0
0042e351        edx_23[1] = 0
0042e354        edx_23[2] = 0x3f800000
0042e369        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
0042e37c        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
0042e38e        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
0042e393        void* eax_38 = self->_pad_00[0x24].d
0042e396        int32_t i_1 = 0
0042e398        uint32_t esi_3 = *(eax_38 + 0x38)
0042e39b        int32_t eax_39 = *(eax_38 + 0x5c)
0042e3a7        arg2 = esi_3
0042e3ab        if (self->segment_count s>= 0)
0042e3b1        int32_t ebx_2 = 0
0042e3b3        float ecx_39 = self->__offset(0x54).d
0042e3b6        int32_t edi_3 = 0
0042e3ba        arg5.d = 0
0042e3be        arg3 = ecx_39
0042e3c2        if (ecx_39 s>= 0)
0042e3d5        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042e3de        long double x87_r7_54 = float.t(arg5.d) - float.t(arg3) * fconvert.t(0.5f)
0042e3e0        int32_t eax_46
0042e3e0        float ecx_43
0042e3e0        if (i_1 == self->segment_count)
0042e436        void* eax_47 = primary_samples_4 + ebx_2
0042e447        esi_3 = arg2
0042e48c        float var_38_2 = fconvert.s(fconvert.t(*(eax_47 - 0x74)) + fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(*(eax_47 - 0xa4)))))
0042e494        long double x87_r6_24 = fconvert.t(fconvert.s(fconvert.t(*(eax_47 - 0x70)) + fconvert.t(1f))) + x87_r7_54 * fconvert.t(*(eax_47 - 0xa0))
0042e496        eax_46 = esi_3 + ((ecx_39 i+ 1) * i_1 + edi_3) * 0xc
0042e49d        *eax_46 = fconvert.s(fconvert.t(*(eax_47 - 0x78)) + fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(*(eax_47 - 0xa8)))))
0042e4a7        *(eax_46 + 4) = var_38_2
0042e4aa        ecx_43 = fconvert.s(x87_r6_24)
0042e3e2        float* eax_42 = primary_samples_4 + ebx_2
0042e40a        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(eax_42[1]))) + fconvert.t(eax_42[0xd]))
0042e417        float var_28_3 = fconvert.s(x87_r7_54 * fconvert.t(eax_42[2]) + fconvert.t(eax_42[0xe]))
0042e420        eax_46 = esi_3 + ((ecx_39 i+ 1) * i_1 + edi_3) * 0xc
0042e427        *eax_46 = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(*eax_42))) + fconvert.t(eax_42[0xc]))
0042e42d        *(eax_46 + 4) = var_2c_3
0042e430        ecx_43 = var_28_3
0042e4b0        *(eax_46 + 8) = ecx_43
0042e4b3        ecx_39 = self->__offset(0x54).d
0042e4b6        edi_3 += 1
0042e4b7        arg3 = ecx_39
0042e4bd        arg5.d = edi_3
0042e4c1        do while (edi_3 s<= ecx_39)
0042e4ca        i_1 += 1
0042e4cb        ebx_2 += 0xa8
0042e4d3        do while (i_1 s<= self->segment_count)
0042e4dc        int32_t i_2 = 0
0042e4e0        if (self->segment_count s> 0)
0042e4e9        int32_t j = 0
0042e4ed        arg5.d = 0
0042e4f1        if (self->__offset(0x54).d s> 0)
0042e4f9        float eax_55 = i_2 & 0x80000007
0042e4fe        if (eax_55 s< 0)
0042e504        eax_55 = ((eax_55 i- 1) | 0xfffffff8) + 1
0042e518        arg3 = fconvert.s(float.t(eax_55) * fconvert.t(0.125f))
0042e526        arg4 = fconvert.s(float.t(eax_55 i+ 1) * fconvert.t(0.125f))
0042e531        int32_t ecx_47 = 0
0042e537        int32_t var_48_1 = 0
0042e541        arg5.d = fconvert.s(float.t(arg5.d) * fconvert.t(0.125f))
0042e54f        arg2 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042e563        while (true)
0042e563        int32_t eax_62 = ecx_47 + ((self->__offset(0x54).d * i_2 + j) << 1)
0042e566        if (ecx_47 != 0)
0042e62c        int16_t* ebx_4 = eax_62 * 0x30 + eax_39
0042e62f        *ebx_4 = 0
0042e634        ecx_47.w = self->__offset(0x54).w
0042e638        ecx_47.w += 1
0042e641        ebx_4[1] = ecx_47.w * i_2.w + j.w + 1
0042e645        int32_t eax_70
0042e645        eax_70.w = self->__offset(0x54).w
0042e649        eax_70.w += 1
0042e650        ebx_4[2] = eax_70.w * i_2.w + j.w
0042e662        ebx_4[3] = (self->__offset(0x54).w + 1) * (i_2.w + 1) + j.w
0042e67a        ebx_4[4] = (self->__offset(0x54).w + 1) * (i_2.w + 1) + j.w + 1
0042e67e        char* texture_path_1
0042e67e        if (((j.b ^ i_2.b) & 1) != 0)
0042e70e        texture_path_1 = texture_b
0042e688        texture_path_1 = texture_b
0042e697        int32_t edx_42 = arg5.d
0042e69b        *(ebx_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0042e6a2        *(ebx_4 + 0x10) = arg2
0042e6a5        *(ebx_4 + 0x14) = arg3
0042e6aa        *(ebx_4 + 0x18) = edx_42
0042e6b3        *(ebx_4 + 0x1c) = arg3
0042e6ba        *(ebx_4 + 0x20) = edx_42
0042e6bd        *(ebx_4 + 0x24) = arg4
0042e6c2        *(ebx_4 + 0x28) = arg2
0042e6c5        *(ebx_4 + 0x2c) = arg4
0042e57a        int16_t* ebx_3 = eax_62 * 0x30 + eax_39
0042e57d        *ebx_3 = 0
0042e582        eax_62.w = self->__offset(0x54).w
0042e586        eax_62.w += 1
0042e58d        ebx_3[1] = eax_62.w * i_2.w + j.w
0042e591        int32_t ecx_49
0042e591        ecx_49.w = self->__offset(0x54).w
0042e595        ecx_49.w += 1
0042e5a1        ebx_3[2] = ecx_49.w * i_2.w + j.w + 1
0042e5b2        ebx_3[3] = (self->__offset(0x54).w + 1) * (i_2.w + 1) + j.w + 1
0042e5c8        ebx_3[4] = (self->__offset(0x54).w + 1) * (i_2.w + 1) + j.w
0042e5cc        char* texture_path
0042e5cc        if (((j.b ^ i_2.b) & 1) != 0)
0042e61b        texture_path = texture_a
0042e5d2        texture_path = texture_a
0042e5e5        *(ebx_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0042e5ec        *(ebx_3 + 0x10) = arg5.d
0042e5ef        *(ebx_3 + 0x14) = arg3
0042e5f4        *(ebx_3 + 0x18) = arg2
0042e5fd        *(ebx_3 + 0x1c) = arg3
0042e604        *(ebx_3 + 0x20) = arg2
0042e607        *(ebx_3 + 0x24) = arg4
0042e60c        *(ebx_3 + 0x28) = arg5.d
0042e60f        *(ebx_3 + 0x2c) = arg4
0042e6cd        bool cond:11_1 = var_48_1 + 1 s< 2
0042e6d0        var_48_1 += 1
0042e6d4        if (not(cond:11_1))
0042e6d4        break
0042e555        ecx_47 = var_48_1
0042e6da        j += 1
0042e6e3        arg5.d = j
0042e6e7        do while (j s< self->__offset(0x54).d)
0042e6f0        i_2 += 1
0042e6f3        do while (i_2 s< self->segment_count)
0042e707        return finalize_path_template(self)
