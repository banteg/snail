/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sweep_path_template_pair @ 0x422c00 */

00422c0c        int32_t i_4 = 0
00422c14        self->kind = PATH_TEMPLATE_KIND_SWEEP
00422c1b        self->__offset(0x3c).b = 0
00422c1f        self->__offset(0x40).d = 0
00422c22        self->__offset(0x54).d = texture_a
00422c25        self->__offset(0x50).d = 0x3f800000
00422c28        self->segment_count = 0x1e
00422c2f        self->segment_count_f = 30f
00422c36        allocate_path_template_samples(self)
00422c3b        self->__offset(0x9c).b = 0
00422c41        texture_a = nullptr
00422c45        int32_t i = 0
00422cfc        while (i s< 0x1f8)
00422c59        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->__offset(0x54).d) * fconvert.t(0.5f) - fconvert.t(4f))
00422c63        *(&self->primary_samples->rotation_scalar_98 + i) = 0
00422c6d        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00422c77        *(&self->primary_samples->special_scalar + i) = 0
00422c81        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
00422c8d        set_matrix_identity(self->primary_samples + i)
00422c95        void* eax_3 = self->primary_samples + i
00422c97        long double x87_r7_4 = float.t(texture_a)
00422ca1        *(eax_3 + 0x30) = *(eax_3 + 0x90)
00422cab        *(&self->primary_samples->transform.position.y + i) = 0
00422cb4        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_4)
00422cbb        set_matrix_identity(i + self->__offset(0x5c).d)
00422cd1        *(i + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + i)
00422cd8        *(i + self->__offset(0x5c).d + 0x34) = 0x3efae148
00422ce3        *(i + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_4)))
00422ceb        i += 0xa8
00422cf8        texture_a = &texture_a[1]
00422d02        char* texture_a_1 = 0x1b
00422d07        int32_t edi = 0x11b8
00422d0c        texture_a = 0x1b
00422d22        *(&self->primary_samples->center_x + edi) = fconvert.s(fconvert.t(4f) - float.t(self->__offset(0x54).d) * fconvert.t(0.5f))
00422d2c        *(&self->primary_samples->rotation_scalar_98 + edi) = 0
00422d36        *(&self->primary_samples->rotation_scalar_94 + edi) = 0
00422d40        *(&self->primary_samples->special_scalar + edi) = 0
00422d4a        *(&self->primary_samples->lateral_scale + edi) = 0x3f800000
00422d5a        set_matrix_identity(self->primary_samples + edi)
00422d5f        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00422d62        long double x87_r7_9 = float.t(texture_a)
00422d74        *(&primary_samples_1->transform.position + edi) = *(&primary_samples_1->center_x + edi)
00422d7c        *(&self->primary_samples->transform.position.y + edi) = 0
00422d83        *(&self->primary_samples->transform.position.z + edi) = fconvert.s(x87_r7_9)
00422d8a        set_matrix_identity(edi + self->__offset(0x5c).d)
00422da0        *(edi + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + edi)
00422da7        *(edi + self->__offset(0x5c).d + 0x34) = 0x3efae148
00422db2        *(edi + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_9)))
00422db6        edi += 0xa8
00422dbc        texture_a_1 = &texture_a_1[1]
00422dbd        texture_a = texture_a_1
00422dc7        do while (&texture_a_1[0xffffffe5] s< 3)
00422dcd        texture_a = nullptr
00422dd1        int32_t i_1 = 0x1f8
00423042        while (i_1 s< 0x11b8)
00422dda        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00422de3        float var_48_1 = fconvert.s(float.t(texture_a) * fconvert.t(0.130899698f))
00422dfa        *(&primary_samples_2->center_x + i_1) = fconvert.s(cosine(var_48_1) * fconvert.t(primary_samples_2->center_x))
00422e04        *(&self->primary_samples->rotation_scalar_98 + i_1) = 0
00422e0e        *(&self->primary_samples->rotation_scalar_94 + i_1) = 0
00422e18        *(&self->primary_samples->special_scalar + i_1) = 0
00422e22        *(&self->primary_samples->lateral_scale + i_1) = 0x3f800000
00422e32        set_matrix_identity(self->primary_samples + i_1)
00422e3e        void* eax_14 = self->primary_samples + i_1
00422e47        *(eax_14 + 0x30) = *(eax_14 + 0x90)
00422e68        *(&self->primary_samples->transform.position.y + i_1) = fconvert.s(sine(var_48_1) * fconvert.t(-0.300000012f))
00422e6c        long double x87_r7_17 = float.t(&texture_a[3])
00422e77        *(&self->primary_samples->transform.position.z + i_1) = fconvert.s(x87_r7_17)
00422e7e        set_matrix_identity(i_1 + self->__offset(0x5c).d)
00422e96        *(i_1 + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + i_1)
00422eaa        *(i_1 + self->__offset(0x5c).d + 0x34) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + i_1)) + fconvert.t(0.49000001f))
00422eb5        *(i_1 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_17)))
00422eb9        if (i_1 s<= 0x1f8)
00423019        set_matrix_rotation_identity(self->primary_samples + i_1 - 0xa8)
00423028        set_matrix_rotation_identity(i_1 + self->__offset(0x5c).d - 0xa8)
00422ed6        int32_t* ecx_29 = self->primary_samples + i_1 - 0x98
00422ee9        *ecx_29 = 0
00422eef        ecx_29[1] = 0x3f800000
00422ef2        ecx_29[2] = 0
00422ef8        void* eax_20 = self->primary_samples + i_1
00422f16        float var_2c_1 = fconvert.s(fconvert.t(*(eax_20 + 0x34)) - fconvert.t(*(eax_20 - 0x74)))
00422f20        long double x87_r7_26 = fconvert.t(*(eax_20 + 0x38)) - fconvert.t(*(eax_20 - 0x70))
00422f27        *(eax_20 - 0x88) = fconvert.s(fconvert.t(*(eax_20 + 0x30)) - fconvert.t(*(eax_20 - 0x78)))
00422f29        *(eax_20 - 0x84) = var_2c_1
00422f34        *(eax_20 - 0x80) = fconvert.s(x87_r7_26)
00422f41        normalize_vector(self->primary_samples + i_1 - 0x88)
00422f49        void* eax_23 = self->primary_samples + i_1
00422f61        cross_vectors(eax_23 - 0xa8, eax_23 - 0x98, eax_23 - 0x88)
00422f7d        int32_t* ecx_35 = i_1 + self->__offset(0x5c).d - 0x98
00422f90        *ecx_35 = 0
00422f96        ecx_35[1] = 0x3f800000
00422f99        ecx_35[2] = 0
00422f9f        void* eax_26 = self->__offset(0x5c).d + i_1
00422fbd        float var_14_1 = fconvert.s(fconvert.t(*(eax_26 + 0x34)) - fconvert.t(*(eax_26 - 0x74)))
00422fc7        long double x87_r7_34 = fconvert.t(*(eax_26 + 0x38)) - fconvert.t(*(eax_26 - 0x70))
00422fce        *(eax_26 - 0x88) = fconvert.s(fconvert.t(*(eax_26 + 0x30)) - fconvert.t(*(eax_26 - 0x78)))
00422fd0        *(eax_26 - 0x84) = var_14_1
00422fdb        *(eax_26 - 0x80) = fconvert.s(x87_r7_34)
00422fe8        normalize_vector(i_1 + self->__offset(0x5c).d - 0x88)
00422ff0        void* eax_29 = self->__offset(0x5c).d + i_1
00423008        cross_vectors(eax_29 - 0xa8, eax_29 - 0x98, eax_29 - 0x88)
00423031        i_1 += 0xa8
0042303e        texture_a = &texture_a[1]
0042304b        int32_t i_2 = 0
00423050        if (self->segment_count - 1 s> 0)
00423056        void* edi_1 = nullptr
0042305b        void* eax_32 = self->primary_samples + edi_1
00423079        float var_14_2 = fconvert.s(fconvert.t(*(eax_32 + 0xdc)) - fconvert.t(*(eax_32 + 0x34)))
00423080        long double x87_r7_42 = fconvert.t(*(eax_32 + 0xe0)) - fconvert.t(*(eax_32 + 0x38))
00423087        *(eax_32 + 0x80) = fconvert.s(fconvert.t(*(eax_32 + 0xd8)) - fconvert.t(*(eax_32 + 0x30)))
00423089        *(eax_32 + 0x84) = var_14_2
00423094        *(eax_32 + 0x88) = fconvert.s(x87_r7_42)
004230a9        *(&self->primary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_1))
004230b0        int32_t ecx_47 = self->__offset(0x5c).d
004230d4        float var_20_1 = fconvert.s(fconvert.t(*(edi_1 + ecx_47 + 0xdc)) - fconvert.t(*(edi_1 + ecx_47 + 0x34)))
004230db        long double x87_r7_49 = fconvert.t(*(edi_1 + ecx_47 + 0xe0)) - fconvert.t(*(edi_1 + ecx_47 + 0x38))
004230e2        *(edi_1 + ecx_47 + 0x80) = fconvert.s(fconvert.t(*(edi_1 + ecx_47 + 0xd8)) - fconvert.t(*(edi_1 + ecx_47 + 0x30)))
004230e4        *(edi_1 + ecx_47 + 0x84) = var_20_1
004230ef        *(edi_1 + ecx_47 + 0x88) = fconvert.s(x87_r7_49)
00423104        i_2 += 1
00423105        *(edi_1 + self->__offset(0x5c).d + 0x8c) = fconvert.s(normalize_vector(edi_1 + self->__offset(0x5c).d + 0x80))
0042310f        edi_1 += 0xa8
00423118        do while (i_2 s< self->segment_count - 1)
00423148        int32_t* edx_34 = &self->primary_samples[self->segment_count] - 0x28
0042315c        *edx_34 = 0
0042316a        edx_34[1] = 0
0042316d        edx_34[2] = 0x3f800000
0042317f        int32_t var_10_3 = 0x3f800000
0042318b        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
004231a1        int32_t* ecx_57 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
004231a9        *ecx_57 = 0
004231af        ecx_57[1] = 0
004231b4        ecx_57[2] = 0x3f800000
004231c9        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
004231dc        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
004231ee        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
004231f3        void* eax_53 = self->_pad_00[0x24].d
004231f6        int32_t i_3 = 0
004231f8        int32_t ebp = *(eax_53 + 0x38)
004231fb        int32_t ecx_65 = *(eax_53 + 0x5c)
00423201        int32_t var_40_4 = ebp
0042320b        if (self->segment_count s>= 0)
00423211        int32_t ecx_66 = self->__offset(0x54).d
00423214        char* texture_a_2 = nullptr
00423218        texture_a = nullptr
0042321c        int32_t var_4c_1 = ecx_66
00423220        if (ecx_66 s>= 0)
00423233        struct PathTemplateSample* primary_samples = self->primary_samples
0042323c        long double x87_r7_52 = float.t(texture_a) - float.t(var_4c_1) * fconvert.t(0.5f)
0042323e        int32_t* eax_60
0042323e        float ecx_70
0042323e        if (i_3 == self->segment_count)
00423295        void* eax_61 = primary_samples + i_4
004232a6        ebp = var_40_4
004232eb        float var_20_2 = fconvert.s(fconvert.t(*(eax_61 - 0x74)) + fconvert.t(fconvert.s(x87_r7_52 * fconvert.t(*(eax_61 - 0xa4)))))
004232f3        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_61 - 0x70)) + fconvert.t(1f))) + x87_r7_52 * fconvert.t(*(eax_61 - 0xa0))
004232f5        eax_60 = ebp + ((ecx_66 + 1) * i_3 + texture_a_2) * 0xc
004232fd        *eax_60 = fconvert.s(fconvert.t(*(eax_61 - 0x78)) + fconvert.t(fconvert.s(x87_r7_52 * fconvert.t(*(eax_61 - 0xa8)))))
00423307        eax_60[1] = var_20_2
0042330a        ecx_70 = fconvert.s(x87_r6_20)
00423240        float* eax_56 = primary_samples + i_4
00423268        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_52 * fconvert.t(eax_56[1]))) + fconvert.t(eax_56[0xd]))
00423275        float var_10_4 = fconvert.s(x87_r7_52 * fconvert.t(eax_56[2]) + fconvert.t(eax_56[0xe]))
0042327e        eax_60 = ebp + ((ecx_66 + 1) * i_3 + texture_a_2) * 0xc
00423286        *eax_60 = fconvert.s(fconvert.t(fconvert.s(x87_r7_52 * fconvert.t(*eax_56))) + fconvert.t(eax_56[0xc]))
0042328c        eax_60[1] = var_14_3
0042328f        ecx_70 = var_10_4
00423310        eax_60[2] = ecx_70
00423313        ecx_66 = self->__offset(0x54).d
00423316        texture_a_2 = &texture_a_2[1]
00423317        var_4c_1 = ecx_66
0042331d        texture_a = texture_a_2
00423321        do while (texture_a_2 s<= ecx_66)
0042332a        i_3 += 1
0042332b        i_4 += 0xa8
00423333        do while (i_3 s<= self->segment_count)
00423339        i_4 = 0
00423340        if (self->segment_count s> 0)
00423349        int32_t j = 0
0042334d        texture_a = nullptr
00423351        if (self->__offset(0x54).d s> 0)
00423359        int32_t eax_69 = i_4 & 0x80000007
0042335e        if (eax_69 s< 0)
00423364        eax_69 = ((eax_69 - 1) | 0xfffffff8) + 1
00423378        float var_54_1 = fconvert.s(float.t(eax_69) * fconvert.t(0.125f))
00423386        float var_4c_2 = fconvert.s(float.t(eax_69 + 1) * fconvert.t(0.125f))
00423391        int32_t ecx_74 = 0
00423397        int32_t var_48_2 = 0
004233a1        texture_a = fconvert.s(float.t(texture_a) * fconvert.t(0.125f))
004233af        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
004233c3        while (true)
004233c3        int32_t eax_76 = ecx_74 + ((self->__offset(0x54).d * i_4 + j) << 1)
004233c6        if (ecx_74 != 0)
0042348d        int16_t* ebp_3 = eax_76 * 0x30 + ecx_65
00423490        *ebp_3 = 0
00423496        ecx_74.w = self->__offset(0x54).w
0042349a        ecx_74.w += 1
004234a3        ebp_3[1] = ecx_74.w * i_4.w + j.w + 1
004234a7        int32_t eax_84
004234a7        eax_84.w = self->__offset(0x54).w
004234ab        eax_84.w += 1
004234b2        ebp_3[2] = eax_84.w * i_4.w + j.w
004234c4        ebp_3[3] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w
004234dc        ebp_3[4] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w + 1
004234e0        char* texture_path_1
004234e0        char* texture_path_3
004234e0        if (((j.b ^ i_4.b) & 1) != 0)
00423576        texture_path_1 = texture_path_3
004234ed        texture_path_1 = texture_path_3
00423500        *(ebp_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00423507        *(ebp_3 + 0x10) = var_50_1
0042350a        *(ebp_3 + 0x14) = var_54_1
0042350f        *(ebp_3 + 0x18) = texture_a
00423518        *(ebp_3 + 0x1c) = var_54_1
0042351f        *(ebp_3 + 0x20) = texture_a
00423522        *(ebp_3 + 0x24) = var_4c_2
00423527        *(ebp_3 + 0x28) = var_50_1
0042352a        *(ebp_3 + 0x2c) = var_4c_2
004233da        int16_t* ebp_2 = eax_76 * 0x30 + ecx_65
004233dd        *ebp_2 = 0
004233e3        eax_76.w = self->__offset(0x54).w
004233e7        eax_76.w += 1
004233ee        ebp_2[1] = eax_76.w * i_4.w + j.w
004233f2        int32_t ecx_76
004233f2        ecx_76.w = self->__offset(0x54).w
004233f6        ecx_76.w += 1
00423402        ebp_2[2] = ecx_76.w * i_4.w + j.w + 1
00423413        ebp_2[3] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w + 1
00423429        ebp_2[4] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w
0042342d        char* texture_path
0042342d        char* texture_path_2
0042342d        if (((j.b ^ i_4.b) & 1) != 0)
0042347c        texture_path = texture_path_2
00423433        texture_path = texture_path_2
00423446        *(ebp_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0042344d        *(ebp_2 + 0x10) = texture_a
00423450        *(ebp_2 + 0x14) = var_54_1
00423455        *(ebp_2 + 0x18) = var_50_1
0042345e        *(ebp_2 + 0x1c) = var_54_1
00423465        *(ebp_2 + 0x20) = var_50_1
00423468        *(ebp_2 + 0x24) = var_4c_2
0042346d        *(ebp_2 + 0x28) = texture_a
00423470        *(ebp_2 + 0x2c) = var_4c_2
00423532        bool cond:12_1 = var_48_2 + 1 s< 2
00423535        var_48_2 += 1
00423539        if (not(cond:12_1))
00423539        break
004233b5        ecx_74 = var_48_2
0042353f        j += 1
00423548        texture_a = j
0042354c        do while (j s< self->__offset(0x54).d)
00423555        i_4 += 1
00423558        do while (i_4 s< self->segment_count)
0042356c        return finalize_path_template(self)
