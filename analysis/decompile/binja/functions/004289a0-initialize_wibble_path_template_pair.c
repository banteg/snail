/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_wibble_path_template_pair @ 0x4289a0 */

004289b4        self->kind = PATH_TEMPLATE_KIND_WIBBLE
004289bb        self->__offset(0x3c).b = 0
004289bf        self->__offset(0x40).d = 0
004289c2        self->__offset(0x54).d = texture_a
004289c5        self->__offset(0x50).d = 0x3f800000
004289c8        self->segment_count = 0x20
004289cf        self->segment_count_f = 32f
004289d6        allocate_path_template_samples(self)
004289db        long double x87_r7 = float.t(self->__offset(0x54).d)
004289de        struct PathTemplateSample* primary_samples_4 = self->primary_samples
004289e1        self->__offset(0x9c).b = 0
004289f4        primary_samples_4->center_x = fconvert.s(x87_r7 * fconvert.t(0.5f) - fconvert.t(4f))
004289fd        self->primary_samples->rotation_scalar_98 = 0f
00428a06        self->primary_samples->rotation_scalar_94 = 0f
00428a0f        self->primary_samples->special_scalar = 0f
00428a18        self->primary_samples->lateral_scale = 1f
00428a21        set_matrix_identity(self->primary_samples)
00428a26        struct PathTemplateSample* primary_samples = self->primary_samples
00428a2f        primary_samples->transform.position.x = primary_samples->center_x
00428a35        self->primary_samples->transform.position.y = 0f
00428a3b        self->primary_samples->transform.position.z = 0f
00428a41        self->primary_samples->delta_length = 1f
00428a4a        set_matrix_identity(self->__offset(0x5c).d)
00428a5b        *(self->__offset(0x5c).d + 0x30) = self->primary_samples->center_x
00428a61        *(self->__offset(0x5c).d + 0x34) = 0x3efae148
00428a6b        *(self->__offset(0x5c).d + 0x38) = 0
00428a71        *(self->__offset(0x5c).d + 0x8c) = 0x3f800000
00428a89        self->primary_samples->__offset(0x14e8).d = fconvert.s(fconvert.t(4f) - float.t(self->__offset(0x54).d) * fconvert.t(0.5f))
00428a92        self->primary_samples->__offset(0x14f0).d = 0
00428a9b        self->primary_samples->__offset(0x14ec).d = 0
00428aa4        self->primary_samples->__offset(0x14f8).d = 0
00428aad        self->primary_samples->__offset(0x14f4).d = 0x3f800000
00428abc        set_matrix_identity(&self->primary_samples[0x1f])
00428ac1        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00428acf        primary_samples_1->__offset(0x1488).d = primary_samples_1->__offset(0x14e8).d
00428ad8        self->primary_samples->__offset(0x148c).d = 0
00428ae1        self->primary_samples->__offset(0x1490).d = 0x41f80000
00428aea        self->primary_samples->__offset(0x14e4).d = 0x3f800000
00428af9        set_matrix_identity(self->__offset(0x5c).d + 0x1458)
00428b0a        *(self->__offset(0x5c).d + 0x1488) = self->primary_samples->__offset(0x14e8).d
00428b13        *(self->__offset(0x5c).d + 0x148c) = 0x3efae148
00428b20        *(self->__offset(0x5c).d + 0x1490) = 0x41f80000
00428b29        int32_t i = 0xa8
00428b2e        *(self->__offset(0x5c).d + 0x14e4) = 0x3f800000
00428b34        char* texture_a_2 = nullptr
00428b36        texture_a = nullptr
00428b42        long double x87_r7_6 = float.t(texture_a)
00428b46        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00428b6f        *(&primary_samples_2->center_x + i) = fconvert.s((fconvert.t(primary_samples_2->__offset(0x14e8).d) - fconvert.t(primary_samples_2->center_x)) * x87_r7_6 * fconvert.t(0.0333333351f) + fconvert.t(primary_samples_2->center_x))
00428b7b        *(&self->primary_samples->rotation_scalar_98 + i) = 0
00428b85        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00428b8f        *(&self->primary_samples->special_scalar + i) = 0
00428b99        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
00428ba9        set_matrix_identity(self->primary_samples + i)
00428bba        *(&self->primary_samples->transform.position + i) = 0
00428bc1        *(&self->primary_samples->transform.position.z + i) = fconvert.s(float.t(&texture_a_2[1]))
00428bd2        *(&self->primary_samples->transform.position.y + i) = 0
00428bd6        float var_40_2 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(0.209439516f))) * fconvert.t(3f))
00428bf2        float var_40_3 = fconvert.s(cosine(fconvert.s(sine(var_40_2) * fconvert.t(0.300000012f))))
00428c08        long double st0_4 = sine(fconvert.s(sine(var_40_2) * fconvert.t(0.300000012f)))
00428c20        float* edx_13 = &self->primary_samples->transform.basis_up + i
00428c2b        *edx_13 = fconvert.s(st0_4)
00428c31        edx_13[1] = var_40_3
00428c34        edx_13[2] = 0
00428c37        struct PathTemplateSample* primary_samples_5 = self->primary_samples
00428c59        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position.y + i)) - fconvert.t(*(primary_samples_5 + i - 0x74)))
00428c60        long double x87_r7_22 = fconvert.t(*(&primary_samples_5->transform.position.z + i)) - fconvert.t(*(primary_samples_5 + i - 0x70))
00428c6a        *(&primary_samples_5->transform.basis_forward + i) = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position + i)) - fconvert.t(*(primary_samples_5 + i - 0x78)))
00428c6c        *(&primary_samples_5->transform.basis_forward.y + i) = var_2c_1
00428c77        *(&primary_samples_5->transform.basis_forward.z + i) = fconvert.s(x87_r7_22)
00428c81        normalize_vector(&self->primary_samples->transform.basis_forward + i)
00428c89        struct Vec3* out = self->primary_samples + i
00428c95        cross_vectors(out, out + 0x10, out + 0x20)
00428ca9        __builtin_memcpy(self->__offset(0x5c).d + i, self->primary_samples + i, 0x40)
00428cab        struct PathTemplateSample* primary_samples_6 = self->primary_samples
00428cb1        texture_a_2 = &texture_a_2[1]
00428cb9        long double x87_r7_26 = fconvert.t(*(&primary_samples_6->transform.basis_up + i)) * fconvert.t(0.49000001f)
00428cc7        texture_a = texture_a_2
00428cd1        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_6->transform.basis_up.y + i)) * fconvert.t(0.49000001f))
00428cd8        long double x87_r6_11 = fconvert.t(*(&primary_samples_6->transform.basis_up.z + i)) * fconvert.t(0.49000001f)
00428cde        float* eax_19 = self->__offset(0x5c).d + i + 0x30
00428ce2        i += 0xa8
00428cf4        *eax_19 = fconvert.s(x87_r7_26 + fconvert.t(*eax_19))
00428cfd        eax_19[1] = fconvert.s(fconvert.t(var_20_1) + fconvert.t(eax_19[1]))
00428d07        eax_19[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_11)) + fconvert.t(eax_19[2]))
00428d0a        do while (i s< 0x1458)
00428d13        int32_t i_1 = 0
00428d18        if (self->segment_count - 1 s> 0)
00428d1e        int32_t esi_4 = 0
00428d20        struct PathTemplateSample* primary_samples_7 = self->primary_samples
00428d44        float var_2c_2 = fconvert.s(fconvert.t(*(primary_samples_7 + esi_4 + 0xdc)) - fconvert.t(*(&primary_samples_7->transform.position.y + esi_4)))
00428d4b        long double x87_r7_37 = fconvert.t(*(primary_samples_7 + esi_4 + 0xe0)) - fconvert.t(*(&primary_samples_7->transform.position.z + esi_4))
00428d52        *(&primary_samples_7->delta_dir_to_next + esi_4) = fconvert.s(fconvert.t(*(primary_samples_7 + esi_4 + 0xd8)) - fconvert.t(*(&primary_samples_7->transform.position + esi_4)))
00428d54        *(&primary_samples_7->delta_dir_to_next.y + esi_4) = var_2c_2
00428d5f        *(&primary_samples_7->delta_dir_to_next.z + esi_4) = fconvert.s(x87_r7_37)
00428d74        *(&self->primary_samples->delta_length + esi_4) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + esi_4))
00428d7b        void* edx_20 = self->__offset(0x5c).d
00428d9f        float var_38_2 = fconvert.s(fconvert.t(*(edx_20 + esi_4 + 0xdc)) - fconvert.t(*(edx_20 + esi_4 + 0x34)))
00428da6        long double x87_r7_44 = fconvert.t(*(edx_20 + esi_4 + 0xe0)) - fconvert.t(*(edx_20 + esi_4 + 0x38))
00428dad        *(edx_20 + esi_4 + 0x80) = fconvert.s(fconvert.t(*(edx_20 + esi_4 + 0xd8)) - fconvert.t(*(edx_20 + esi_4 + 0x30)))
00428daf        *(edx_20 + esi_4 + 0x84) = var_38_2
00428dba        *(edx_20 + esi_4 + 0x88) = fconvert.s(x87_r7_44)
00428dcf        i_1 += 1
00428dd0        *(self->__offset(0x5c).d + esi_4 + 0x8c) = fconvert.s(normalize_vector(self->__offset(0x5c).d + esi_4 + 0x80))
00428dda        esi_4 += 0xa8
00428de3        do while (i_1 s< self->segment_count - 1)
00428e13        int32_t* ecx_34 = &self->primary_samples[self->segment_count] - 0x28
00428e27        *ecx_34 = 0
00428e35        ecx_34[1] = 0
00428e38        ecx_34[2] = 0x3f800000
00428e4a        int32_t var_28_3 = 0x3f800000
00428e56        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00428e6c        int32_t* eax_37 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
00428e74        *eax_37 = 0
00428e7a        eax_37[1] = 0
00428e7f        eax_37[2] = 0x3f800000
00428e94        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
00428ea7        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
00428eb9        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
00428ebe        void* eax_43 = self->_pad_00[0x24].d
00428ec1        int32_t edx_27 = *(eax_43 + 0x5c)
00428ec4        int32_t edi_3 = *(eax_43 + 0x38)
00428ece        int32_t i_2 = 0
00428ed0        int32_t var_40_4 = edi_3
00428ed6        if (self->segment_count s>= 0)
00428edc        int32_t ebx = 0
00428ede        int32_t ecx_46 = self->__offset(0x54).d
00428ee1        char* texture_a_1 = nullptr
00428ee5        texture_a = nullptr
00428ee9        int32_t var_4c_1 = ecx_46
00428eed        if (ecx_46 s>= 0)
00428f00        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00428f09        long double x87_r7_47 = float.t(texture_a) - float.t(var_4c_1) * fconvert.t(0.5f)
00428f0b        float* eax_50
00428f0b        float ecx_50
00428f0b        if (i_2 == self->segment_count)
00428f61        void* eax_51 = primary_samples_3 + ebx
00428f72        edi_3 = var_40_4
00428fb7        float var_38_3 = fconvert.s(fconvert.t(*(eax_51 - 0x74)) + fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(*(eax_51 - 0xa4)))))
00428fbf        long double x87_r6_31 = fconvert.t(fconvert.s(fconvert.t(*(eax_51 - 0x70)) + fconvert.t(1f))) + x87_r7_47 * fconvert.t(*(eax_51 - 0xa0))
00428fc1        eax_50 = edi_3 + ((ecx_46 + 1) * i_2 + texture_a_1) * 0xc
00428fc8        *eax_50 = fconvert.s(fconvert.t(*(eax_51 - 0x78)) + fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(*(eax_51 - 0xa8)))))
00428fd2        eax_50[1] = var_38_3
00428fd5        ecx_50 = fconvert.s(x87_r6_31)
00428f0d        float* eax_46 = primary_samples_3 + ebx
00428f35        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(eax_46[1]))) + fconvert.t(eax_46[0xd]))
00428f42        float var_28_4 = fconvert.s(x87_r7_47 * fconvert.t(eax_46[2]) + fconvert.t(eax_46[0xe]))
00428f4b        eax_50 = edi_3 + ((ecx_46 + 1) * i_2 + texture_a_1) * 0xc
00428f52        *eax_50 = fconvert.s(fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(*eax_46))) + fconvert.t(eax_46[0xc]))
00428f58        eax_50[1] = var_2c_3
00428f5b        ecx_50 = var_28_4
00428fdb        eax_50[2] = ecx_50
00428fde        ecx_46 = self->__offset(0x54).d
00428fe1        texture_a_1 = &texture_a_1[1]
00428fe2        var_4c_1 = ecx_46
00428fe8        texture_a = texture_a_1
00428fec        do while (texture_a_1 s<= ecx_46)
00428ff5        i_2 += 1
00428ff6        ebx += 0xa8
00428ffe        do while (i_2 s<= self->segment_count)
00429007        int32_t i_3 = 0
0042900b        if (self->segment_count s> 0)
00429014        int32_t j = 0
00429018        texture_a = nullptr
0042901c        if (self->__offset(0x54).d s> 0)
00429024        int32_t eax_59 = i_3 & 0x80000007
00429029        if (eax_59 s< 0)
0042902f        eax_59 = ((eax_59 - 1) | 0xfffffff8) + 1
00429043        float var_54_1 = fconvert.s(float.t(eax_59) * fconvert.t(0.125f))
00429051        float var_4c_2 = fconvert.s(float.t(eax_59 + 1) * fconvert.t(0.125f))
0042905c        int32_t ecx_54 = 0
00429062        int32_t var_48_1 = 0
0042906c        texture_a = fconvert.s(float.t(texture_a) * fconvert.t(0.125f))
0042907a        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042908e        while (true)
0042908e        int32_t eax_66 = ecx_54 + ((self->__offset(0x54).d * i_3 + j) << 1)
00429091        if (ecx_54 != 0)
00429157        int16_t* edi_6 = eax_66 * 0x30 + edx_27
0042915a        *edi_6 = 0
0042915f        ecx_54.w = self->__offset(0x54).w
00429163        ecx_54.w += 1
0042916c        edi_6[1] = ecx_54.w * i_3.w + j.w + 1
00429170        int32_t eax_74
00429170        eax_74.w = self->__offset(0x54).w
00429174        eax_74.w += 1
0042917b        edi_6[2] = eax_74.w * i_3.w + j.w
0042918d        edi_6[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
004291a5        edi_6[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
004291a9        char* texture_path_1
004291a9        char* texture_path_2
004291a9        if (((j.b ^ i_3.b) & 1) != 0)
0042923f        texture_path_1 = texture_path_2
004291b6        texture_path_1 = texture_path_2
004291c9        *(edi_6 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
004291d0        *(edi_6 + 0x10) = var_50_1
004291d3        *(edi_6 + 0x14) = var_54_1
004291d8        *(edi_6 + 0x18) = texture_a
004291e1        *(edi_6 + 0x1c) = var_54_1
004291e8        *(edi_6 + 0x20) = texture_a
004291eb        *(edi_6 + 0x24) = var_4c_2
004291f0        *(edi_6 + 0x28) = var_50_1
004291f3        *(edi_6 + 0x2c) = var_4c_2
004290a5        int16_t* edi_5 = eax_66 * 0x30 + edx_27
004290a8        *edi_5 = 0
004290ad        eax_66.w = self->__offset(0x54).w
004290b1        eax_66.w += 1
004290b8        edi_5[1] = eax_66.w * i_3.w + j.w
004290bc        int32_t ecx_56
004290bc        ecx_56.w = self->__offset(0x54).w
004290c0        ecx_56.w += 1
004290cc        edi_5[2] = ecx_56.w * i_3.w + j.w + 1
004290dd        edi_5[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
004290f3        edi_5[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
004290f7        char* texture_path
004290f7        char* arg4
004290f7        if (((j.b ^ i_3.b) & 1) != 0)
00429146        texture_path = arg4
004290fd        texture_path = arg4
00429110        *(edi_5 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
00429117        *(edi_5 + 0x10) = texture_a
0042911a        *(edi_5 + 0x14) = var_54_1
0042911f        *(edi_5 + 0x18) = var_50_1
00429128        *(edi_5 + 0x1c) = var_54_1
0042912f        *(edi_5 + 0x20) = var_50_1
00429132        *(edi_5 + 0x24) = var_4c_2
00429137        *(edi_5 + 0x28) = texture_a
0042913a        *(edi_5 + 0x2c) = var_4c_2
004291fb        bool cond:9_1 = var_48_1 + 1 s< 2
004291fe        var_48_1 += 1
00429202        if (not(cond:9_1))
00429202        break
00429080        ecx_54 = var_48_1
00429208        j += 1
00429211        texture_a = j
00429215        do while (j s< self->__offset(0x54).d)
0042921e        i_3 += 1
00429221        do while (i_3 s< self->segment_count)
00429235        return finalize_path_template(self)
