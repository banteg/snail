/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_screw_path_template_pair @ 0x41eda0 */

0041edac        int32_t i_3 = 0
0041edb7        self->__offset(0x54).d = arg3
0041edc4        self->kind = PATH_TEMPLATE_KIND_SCREW
0041edcf        self->__offset(0x3c).b = 0
0041edd3        self->__offset(0x40).d = 0
0041edd6        self->__offset(0x50).d = 0x3f800000
0041edd9        self->segment_count = arg2 + 8
0041eddc        self->segment_count_f = fconvert.s(float.t(arg2 + 8))
0041eddf        allocate_path_template_samples(self)
0041ede4        self->__offset(0x9c).b = 0
0041edea        arg3 = 0
0041edee        void* i = nullptr
0041ee9e        while (i s< 0x1f8)
0041edf3        *(&self->primary_samples->center_x + i) = 0x3f000000
0041ee01        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041ee0b        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041ee15        *(&self->primary_samples->special_scalar + i) = 0
0041ee1f        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041ee2b        set_matrix_identity(self->primary_samples + i)
0041ee30        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041ee33        long double x87_r7_1 = float.t(arg3)
0041ee45        *(&primary_samples_1->transform.position + i) = *(&primary_samples_1->center_x + i)
0041ee4b        *(&self->primary_samples->transform.position.y + i) = 0
0041ee52        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
0041ee5d        set_matrix_identity(i + self->__offset(0x5c).d)
0041ee73        *(i + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + i)
0041ee7a        *(i + self->__offset(0x5c).d + 0x34) = 0x3efae148
0041ee89        *(i + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
0041ee8d        i += 0xa8
0041ee9a        arg3 += 1
0041eead        int32_t ebp = arg2 + 3
0041eeb0        arg3 = ebp
0041eec0        int32_t edi_3 = ebp * 0xa8
0041ef7a        struct TransformMatrix* transform
0041eecc        *(&self->primary_samples->center_x + edi_3) = 0xbf000000
0041eeda        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041eee4        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041eeee        *(&self->primary_samples->special_scalar + edi_3) = 0
0041eef8        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041ef08        set_matrix_identity(self->primary_samples + edi_3)
0041ef0d        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041ef10        long double x87_r7_3 = float.t(arg3)
0041ef22        *(&primary_samples_2->transform.position + edi_3) = *(&primary_samples_2->center_x + edi_3)
0041ef28        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041ef2f        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_3)
0041ef3a        set_matrix_identity(edi_3 + self->__offset(0x5c).d)
0041ef50        *(edi_3 + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + edi_3)
0041ef5b        *(edi_3 + self->__offset(0x5c).d + 0x34) = 0x3efae148
0041ef66        *(edi_3 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_3)))
0041ef6a        edi_3 += 0xa8
0041ef70        ebp += 1
0041ef71        transform = 0xfffffffd - arg2 + ebp
0041ef73        arg3 = ebp
0041ef7a        do while (transform s< 5)
0041ef84        int32_t ebp_1 = 0
0041ef88        arg3 = 0
0041ef8c        if (arg2 s> 0)
0041ef96        void* edi_4 = 0x1f8
0041efa7        struct TransformMatrix* transform_1 = transform
0041efae        long double x87_r7_8 = float.t(arg3) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(float.t(arg2)))
0041efb2        float var_4c_1 = fconvert.s(x87_r7_8)
0041efd0        *(&self->primary_samples->center_x + edi_4) = fconvert.s(cosine(fconvert.s(x87_r7_8 * fconvert.t(0.5f))) * fconvert.t(0.5f))
0041efde        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041efe8        *(&self->primary_samples->rotation_scalar_94 + edi_4) = fconvert.s(fconvert.t(var_4c_1))
0041eff2        *(&self->primary_samples->special_scalar + edi_4) = 0
0041effc        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041f00c        set_matrix_identity(self->primary_samples + edi_4)
0041f011        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041f025        long double x87_r7_13 = float.t(ebp_1 + 3)
0041f029        *(&primary_samples_3->transform.position + edi_4) = *(&primary_samples_3->center_x + edi_4)
0041f033        *(&self->primary_samples->transform.position.y + edi_4) = 0
0041f03a        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
0041f045        set_matrix_identity(edi_4 + self->__offset(0x5c).d)
0041f04e        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0041f057        long double x87_r7_15 = sine(var_4c_1) * fconvert.t(0.49000001f)
0041f068        *(edi_4 + self->__offset(0x5c).d + 0x30) = fconvert.s(fconvert.t(*(&primary_samples_5->center_x + edi_4)) - x87_r7_15)
0041f083        *(edi_4 + self->__offset(0x5c).d + 0x34) = fconvert.s(cosine(var_4c_1) * fconvert.t(0.49000001f))
0041f08e        *(edi_4 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0041f092        if (edi_4 s<= 0x1f8)
0041f212        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
0041f21a        transform = edi_4 + self->__offset(0x5c).d - 0xa8
0041f221        set_matrix_rotation_identity(transform)
0041f09e        float var_48_3 = fconvert.s(cosine(var_4c_1))
0041f0a3        long double st0_5 = sine(var_4c_1)
0041f0bd        float* ecx_25 = self->primary_samples + edi_4 - 0x98
0041f0d3        *ecx_25 = fconvert.s(fneg(st0_5))
0041f0d9        ecx_25[1] = var_48_3
0041f0dc        ecx_25[2] = 0
0041f0e2        void* eax_26 = self->primary_samples + edi_4
0041f100        float var_2c_1 = fconvert.s(fconvert.t(*(eax_26 + 0x34)) - fconvert.t(*(eax_26 - 0x74)))
0041f10a        long double x87_r7_28 = fconvert.t(*(eax_26 + 0x38)) - fconvert.t(*(eax_26 - 0x70))
0041f111        *(eax_26 - 0x88) = fconvert.s(fconvert.t(*(eax_26 + 0x30)) - fconvert.t(*(eax_26 - 0x78)))
0041f113        *(eax_26 - 0x84) = var_2c_1
0041f11e        *(eax_26 - 0x80) = fconvert.s(x87_r7_28)
0041f12b        normalize_vector(self->primary_samples + edi_4 - 0x88)
0041f133        void* eax_29 = self->primary_samples + edi_4
0041f14b        cross_vectors(eax_29 - 0xa8, eax_29 - 0x98, eax_29 - 0x88)
0041f156        float var_48_4 = fconvert.s(cosine(var_4c_1))
0041f15b        long double st0_8 = sine(var_4c_1)
0041f175        float* edx_23 = edi_4 + self->__offset(0x5c).d - 0x98
0041f18b        *edx_23 = fconvert.s(fneg(st0_8))
0041f191        edx_23[1] = var_48_4
0041f194        edx_23[2] = 0
0041f197        int32_t ecx_33 = self->__offset(0x5c).d
0041f1a2        void* eax_32 = edi_4 + ecx_33
0041f1af        float var_14_1 = fconvert.s(fconvert.t(*(eax_32 + 0x34)) - fconvert.t(*(eax_32 - 0x74)))
0041f1b9        float var_10_1 = fconvert.s(fconvert.t(*(eax_32 + 0x38)) - fconvert.t(*(eax_32 - 0x70)))
0041f1ca        *(eax_32 - 0x88) = fconvert.s(fconvert.t(*(edi_4 + ecx_33 + 0x30)) - fconvert.t(*(edi_4 + ecx_33 - 0x78)))
0041f1d0        *(eax_32 - 0x84) = var_14_1
0041f1d3        *(eax_32 - 0x80) = var_10_1
0041f1e0        normalize_vector(edi_4 + self->__offset(0x5c).d - 0x88)
0041f1ea        void* eax_35 = edi_4 + self->__offset(0x5c).d
0041f201        transform = cross_vectors(eax_35 - 0xa8, eax_35 - 0x98, eax_35 - 0x88)
0041f22e        ebp_1 = arg3 + 1
0041f22f        edi_4 += 0xa8
0041f237        arg3 = ebp_1
0041f23b        do while (ebp_1 s< arg2)
0041f241        i_3 = 0
0041f246        int32_t i_1 = 0
0041f24b        if (self->segment_count - 1 s> 0)
0041f251        void* edi_5 = nullptr
0041f253        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041f277        float var_14_2 = fconvert.s(fconvert.t(*(edi_5 + primary_samples_4 + 0xdc)) - fconvert.t(*(&primary_samples_4->transform.position.y + edi_5)))
0041f27e        long double x87_r7_47 = fconvert.t(*(edi_5 + primary_samples_4 + 0xe0)) - fconvert.t(*(&primary_samples_4->transform.position.z + edi_5))
0041f285        *(&primary_samples_4->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + primary_samples_4 + 0xd8)) - fconvert.t(*(&primary_samples_4->transform.position + edi_5)))
0041f287        *(&primary_samples_4->delta_dir_to_next.y + edi_5) = var_14_2
0041f292        *(&primary_samples_4->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_47)
0041f2a7        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041f2ae        int32_t ecx_45 = self->__offset(0x5c).d
0041f2d2        float var_20_2 = fconvert.s(fconvert.t(*(edi_5 + ecx_45 + 0xdc)) - fconvert.t(*(edi_5 + ecx_45 + 0x34)))
0041f2d9        long double x87_r7_54 = fconvert.t(*(edi_5 + ecx_45 + 0xe0)) - fconvert.t(*(edi_5 + ecx_45 + 0x38))
0041f2e0        *(edi_5 + ecx_45 + 0x80) = fconvert.s(fconvert.t(*(edi_5 + ecx_45 + 0xd8)) - fconvert.t(*(edi_5 + ecx_45 + 0x30)))
0041f2e2        *(edi_5 + ecx_45 + 0x84) = var_20_2
0041f2ed        *(edi_5 + ecx_45 + 0x88) = fconvert.s(x87_r7_54)
0041f302        i_1 += 1
0041f303        *(edi_5 + self->__offset(0x5c).d + 0x8c) = fconvert.s(normalize_vector(edi_5 + self->__offset(0x5c).d + 0x80))
0041f30d        edi_5 += 0xa8
0041f316        do while (i_1 s< self->segment_count - 1)
0041f346        int32_t* edx_34 = &self->primary_samples[self->segment_count] - 0x28
0041f35a        *edx_34 = 0
0041f368        edx_34[1] = 0
0041f36b        edx_34[2] = 0x3f800000
0041f37d        int32_t var_10_3 = 0x3f800000
0041f389        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041f39f        int32_t* ecx_55 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
0041f3a7        *ecx_55 = 0
0041f3ad        ecx_55[1] = 0
0041f3b2        ecx_55[2] = 0x3f800000
0041f3c7        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
0041f3da        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
0041f3ec        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
0041f3f1        void* eax_59 = self->_pad_00[0x24].d
0041f3f4        int32_t i_2 = 0
0041f3f6        int32_t ebp_4 = *(eax_59 + 0x38)
0041f3f9        int32_t ecx_63 = *(eax_59 + 0x5c)
0041f3ff        int32_t var_44_4 = ebp_4
0041f409        if (self->segment_count s>= 0)
0041f40f        int32_t ecx_64 = self->__offset(0x54).d
0041f412        int32_t edi_6 = 0
0041f416        arg2 = 0
0041f41a        arg3 = ecx_64
0041f41e        if (ecx_64 s>= 0)
0041f431        struct PathTemplateSample* primary_samples = self->primary_samples
0041f43a        long double x87_r7_57 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041f43c        float* eax_66
0041f43c        float ecx_68
0041f43c        if (i_2 == self->segment_count)
0041f493        void* eax_67 = primary_samples + i_3
0041f4a4        ebp_4 = var_44_4
0041f4e9        float var_20_3 = fconvert.s(fconvert.t(*(eax_67 - 0x74)) + fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(*(eax_67 - 0xa4)))))
0041f4f1        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_67 - 0x70)) + fconvert.t(1f))) + x87_r7_57 * fconvert.t(*(eax_67 - 0xa0))
0041f4f3        eax_66 = ebp_4 + ((ecx_64 + 1) * i_2 + edi_6) * 0xc
0041f4fb        *eax_66 = fconvert.s(fconvert.t(*(eax_67 - 0x78)) + fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(*(eax_67 - 0xa8)))))
0041f505        eax_66[1] = var_20_3
0041f508        ecx_68 = fconvert.s(x87_r6_20)
0041f43e        float* eax_62 = primary_samples + i_3
0041f466        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(eax_62[1]))) + fconvert.t(eax_62[0xd]))
0041f473        float var_10_4 = fconvert.s(x87_r7_57 * fconvert.t(eax_62[2]) + fconvert.t(eax_62[0xe]))
0041f47c        eax_66 = ebp_4 + ((ecx_64 + 1) * i_2 + edi_6) * 0xc
0041f484        *eax_66 = fconvert.s(fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(*eax_62))) + fconvert.t(eax_62[0xc]))
0041f48a        eax_66[1] = var_14_3
0041f48d        ecx_68 = var_10_4
0041f50e        eax_66[2] = ecx_68
0041f511        ecx_64 = self->__offset(0x54).d
0041f514        edi_6 += 1
0041f515        arg3 = ecx_64
0041f51b        arg2 = edi_6
0041f51f        do while (edi_6 s<= ecx_64)
0041f528        i_2 += 1
0041f529        i_3 += 0xa8
0041f531        do while (i_2 s<= self->segment_count)
0041f537        i_3 = 0
0041f53e        if (self->segment_count s> 0)
0041f547        int32_t j = 0
0041f54b        arg2 = 0
0041f54f        if (self->__offset(0x54).d s> 0)
0041f557        int32_t eax_75 = i_3 & 0x80000007
0041f55c        if (eax_75 s< 0)
0041f562        eax_75 = ((eax_75 - 1) | 0xfffffff8) + 1
0041f576        arg3 = fconvert.s(float.t(eax_75) * fconvert.t(0.125f))
0041f584        float var_4c_2 = fconvert.s(float.t(eax_75 + 1) * fconvert.t(0.125f))
0041f58f        int32_t ecx_72 = 0
0041f595        int32_t var_48_5 = 0
0041f59f        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041f5ad        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041f5bf        while (true)
0041f5ce        int16_t* edi_7 = (ecx_72 + ((self->__offset(0x54).d * i_3 + j) << 1)) * 0x30 + ecx_63
0041f5d1        *edi_7 = 0
0041f5d6        int32_t edx_39
0041f5d6        if (ecx_72 != 0)
0041f67c        edx_39.w = self->__offset(0x54).w
0041f682        edx_39.w += 1
0041f68d        edi_7[1] = edx_39.w * i_3.w + j.w + 1
0041f691        ecx_72.w = self->__offset(0x54).w
0041f695        ecx_72.w += 1
0041f69f        edi_7[2] = ecx_72.w * i_3.w + j.w
0041f6ae        edi_7[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
0041f6c5        edi_7[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
0041f6c9        char* texture_path_1
0041f6c9        char* arg5
0041f6c9        if (((j.b ^ i_3.b) & 1) != 0)
0041f759        texture_path_1 = arg5
0041f6d3        texture_path_1 = arg5
0041f6e6        *(edi_7 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0041f6ed        *(edi_7 + 0x10) = var_50_1
0041f6f0        *(edi_7 + 0x14) = arg3
0041f6f5        *(edi_7 + 0x18) = arg2
0041f6fe        *(edi_7 + 0x1c) = arg3
0041f705        *(edi_7 + 0x20) = arg2
0041f708        *(edi_7 + 0x24) = var_4c_2
0041f70d        *(edi_7 + 0x28) = var_50_1
0041f710        *(edi_7 + 0x2c) = var_4c_2
0041f5dc        ecx_72.w = self->__offset(0x54).w
0041f5e2        ecx_72.w += 1
0041f5eb        edi_7[1] = ecx_72.w * i_3.w + j.w
0041f5ef        edx_39.w = self->__offset(0x54).w
0041f5f3        edx_39.w += 1
0041f5fc        edi_7[2] = edx_39.w * i_3.w + j.w + 1
0041f610        edi_7[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
0041f626        edi_7[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
0041f62a        char* texture_path
0041f62a        if (((j.b ^ i_3.b) & 1) != 0)
0041f679        texture_path = texture_b
0041f630        texture_path = texture_b
0041f643        *(edi_7 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0041f64a        *(edi_7 + 0x10) = arg2
0041f64d        *(edi_7 + 0x14) = arg3
0041f652        *(edi_7 + 0x18) = var_50_1
0041f65b        *(edi_7 + 0x1c) = arg3
0041f662        *(edi_7 + 0x20) = var_50_1
0041f665        *(edi_7 + 0x24) = var_4c_2
0041f66a        *(edi_7 + 0x28) = arg2
0041f66d        *(edi_7 + 0x2c) = var_4c_2
0041f718        bool cond:13_1 = var_48_5 + 1 s< 2
0041f71b        var_48_5 += 1
0041f71f        if (not(cond:13_1))
0041f71f        break
0041f5b3        ecx_72 = var_48_5
0041f725        j += 1
0041f72e        arg2 = j
0041f732        do while (j s< self->__offset(0x54).d)
0041f73b        i_3 += 1
0041f73e        do while (i_3 s< self->segment_count)
0041f752        return finalize_path_template(self)
