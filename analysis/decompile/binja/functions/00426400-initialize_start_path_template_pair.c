/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_start_path_template_pair @ 0x426400 */

00426419        self->kind = PATH_TEMPLATE_KIND_START
00426420        self->__offset(0x3c).b = 0
00426424        self->__offset(0x40).d = 0
00426427        self->__offset(0x54).d = arg3
0042642a        int16_t x87control
0042642a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(3.14159274f))
00426446        self->__offset(0x50).d = 0x3f800000
00426449        self->segment_count = eax_1 + 0x10
0042644c        self->segment_count_f = fconvert.s(float.t(eax_1 + 0xf))
0042644f        long double x87_r7_3 = float.t(eax_1)
0042645d        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.318309873f))
00426461        allocate_path_template_samples(self)
00426466        long double x87_r7_5 = fconvert.t(arg2)
0042646a        uint32_t segment_count = self->segment_count
0042646d        self->__offset(0x9c).b = 0
00426474        long double x87_r7_6 = x87_r7_5 + x87_r7_5
00426477        arg3 = 0
0042647b        self->segment_count = segment_count - 1
0042647e        void* i = nullptr
0042654c        while (i s< 0x348)
00426491        *(&self->primary_samples->center_x + i) = 0
0042649b        *(&self->primary_samples->rotation_scalar_98 + i) = 0
004264a5        *(&self->primary_samples->rotation_scalar_94 + i) = 0
004264af        *(&self->primary_samples->special_scalar + i) = 0
004264bb        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
004264c7        set_matrix_identity(i + self->primary_samples)
004264cc        struct PathTemplateSample* primary_samples = self->primary_samples
004264dc        *(&primary_samples->transform.position + i) = *(&primary_samples->center_x + i)
004264e2        *(&self->primary_samples->transform.position.y + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_6)))
004264e6        long double x87_r7_9 = float.t(arg3)
004264f1        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_9)
004264f8        *(&self->primary_samples->delta_length + i) = 0x3f800000
00426504        set_matrix_identity(self->__offset(0x5c).d + i)
0042651a        *(self->__offset(0x5c).d + i + 0x30) = *(&self->primary_samples->center_x + i)
00426521        *(self->__offset(0x5c).d + i + 0x34) = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 + fconvert.t(0.49000001f))))
00426531        *(self->__offset(0x5c).d + i + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_9)))
00426538        i += 0xa8
00426544        arg3 += 1
00426548        *(self->__offset(0x5c).d + i - 0x1c) = 0x3f800000
00426556        int32_t var_3c_1 = 0xb
00426561        arg3 = eax_1 + 5
00426571        int32_t edi_3 = (eax_1 + 5) * 0xa8
00426634        bool cond:1_1
00426577        *(&self->primary_samples->center_x + edi_3) = 0
00426581        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0042658b        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
00426595        *(&self->primary_samples->special_scalar + edi_3) = 0
0042659f        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
004265ad        set_matrix_identity(edi_3 + self->primary_samples)
004265b2        struct PathTemplateSample* primary_samples_1 = self->primary_samples
004265c3        *(&primary_samples_1->transform.position + edi_3) = *(&primary_samples_1->center_x + edi_3)
004265c9        *(&self->primary_samples->transform.position.y + edi_3) = 0
004265d0        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(float.t(arg3))
004265d7        *(&self->primary_samples->delta_length + edi_3) = 0x3f800000
004265e3        set_matrix_identity(self->__offset(0x5c).d + edi_3)
004265f5        *(self->__offset(0x5c).d + edi_3 + 0x30) = *(&self->primary_samples->center_x + edi_3)
004265fc        *(self->__offset(0x5c).d + edi_3 + 0x34) = 0x3efae148
0042660e        *(self->__offset(0x5c).d + edi_3 + 0x38) = *(&self->primary_samples->transform.position.z + edi_3)
00426619        *(self->__offset(0x5c).d + edi_3 + 0x8c) = 0x3f800000
00426624        edi_3 += 0xa8
0042662b        cond:1_1 = var_3c_1 != 1
0042662c        arg3 += 1
00426630        var_3c_1 -= 1
00426634        do while (cond:1_1)
0042663e        arg3 = 0
00426644        if (eax_1 s> 0)
0042664a        void* edi_4 = 0x348
004268ae        bool cond:4_1
00426652        *(&self->primary_samples->center_x + edi_4) = 0
0042665c        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
00426666        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
00426670        *(&self->primary_samples->special_scalar + edi_4) = 0
0042667c        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
00426688        set_matrix_identity(edi_4 + self->primary_samples)
00426694        void* eax_23 = self->primary_samples + edi_4
0042669d        int32_t ecx_27 = *(eax_23 + 0x90)
004266a3        long double x87_r7_13 = float.t(arg3 + 5)
004266a7        *(eax_23 + 0x30) = ecx_27
004266ad        int32_t var_58_1 = ecx_27
004266b2        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
004266dc        *(&self->primary_samples->transform.position.y + edi_4) = fconvert.s((cosine(fconvert.s(float.t(arg3) * fconvert.t(3.14159274f) / fconvert.t(fconvert.s(x87_r7_3)))) + fconvert.t(1f)) * fconvert.t(arg2))
004266e7        set_matrix_identity(edi_4 + self->__offset(0x5c).d)
00426703        *(edi_4 + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + edi_4)
0042670a        *(edi_4 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0042671e        *(edi_4 + self->__offset(0x5c).d + 0x34) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + edi_4)) + fconvert.t(0.49000001f))
00426722        if (edi_4 s<= 0x348)
00426885        set_matrix_rotation_identity(edi_4 + self->primary_samples - 0xa8)
00426894        set_matrix_rotation_identity(edi_4 + self->__offset(0x5c).d - 0xa8)
0042673f        int32_t* eax_27 = edi_4 + self->primary_samples - 0xa8
00426752        *eax_27 = 0x3f800000
00426758        eax_27[1] = 0
0042675b        eax_27[2] = 0
0042675e        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00426782        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position.y + edi_4)) - fconvert.t(*(edi_4 + primary_samples_2 - 0x74)))
0042678c        long double x87_r7_28 = fconvert.t(*(&primary_samples_2->transform.position.z + edi_4)) - fconvert.t(*(edi_4 + primary_samples_2 - 0x70))
00426793        *(edi_4 + primary_samples_2 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position + edi_4)) - fconvert.t(*(edi_4 + primary_samples_2 - 0x78)))
00426795        *(edi_4 + primary_samples_2 - 0x84) = var_20_1
004267a0        *(edi_4 + primary_samples_2 - 0x80) = fconvert.s(x87_r7_28)
004267ad        normalize_vector(edi_4 + self->primary_samples - 0x88)
004267b5        void* eax_31 = self->primary_samples + edi_4
004267cd        cross_vectors(eax_31 - 0x98, eax_31 - 0x88, eax_31 - 0xa8)
004267e9        int32_t* ecx_38 = edi_4 + self->__offset(0x5c).d - 0xa8
004267fc        *ecx_38 = 0x3f800000
00426802        ecx_38[1] = 0
00426805        ecx_38[2] = 0
0042680b        void* eax_34 = self->__offset(0x5c).d + edi_4
00426829        float var_8_1 = fconvert.s(fconvert.t(*(eax_34 + 0x34)) - fconvert.t(*(eax_34 - 0x74)))
00426833        long double x87_r7_36 = fconvert.t(*(eax_34 + 0x38)) - fconvert.t(*(eax_34 - 0x70))
0042683a        *(eax_34 - 0x88) = fconvert.s(fconvert.t(*(eax_34 + 0x30)) - fconvert.t(*(eax_34 - 0x78)))
0042683c        *(eax_34 - 0x84) = var_8_1
00426847        *(eax_34 - 0x80) = fconvert.s(x87_r7_36)
00426854        normalize_vector(edi_4 + self->__offset(0x5c).d - 0x88)
0042685c        void* eax_37 = self->__offset(0x5c).d + edi_4
00426874        cross_vectors(eax_37 - 0x98, eax_37 - 0x88, eax_37 - 0xa8)
004268a2        edi_4 += 0xa8
004268a8        cond:4_1 = arg3 + 1 s< eax_1
004268aa        arg3 += 1
004268ae        do while (cond:4_1)
004268b7        int32_t i_1 = 0
004268bb        if (self->segment_count s> 0)
004268c1        void* edi_5 = nullptr
004268c3        struct PathTemplateSample* primary_samples_3 = self->primary_samples
004268e7        float var_8_2 = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_5)))
004268ee        long double x87_r7_44 = fconvert.t(*(edi_5 + primary_samples_3 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + edi_5))
004268f5        *(&primary_samples_3->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + edi_5)))
004268f7        *(&primary_samples_3->delta_dir_to_next.y + edi_5) = var_8_2
00426902        *(&primary_samples_3->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_44)
00426917        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0042691e        int32_t ecx_51 = self->__offset(0x5c).d
00426942        float var_14_1 = fconvert.s(fconvert.t(*(edi_5 + ecx_51 + 0xdc)) - fconvert.t(*(edi_5 + ecx_51 + 0x34)))
00426949        long double x87_r7_51 = fconvert.t(*(edi_5 + ecx_51 + 0xe0)) - fconvert.t(*(edi_5 + ecx_51 + 0x38))
00426950        *(edi_5 + ecx_51 + 0x80) = fconvert.s(fconvert.t(*(edi_5 + ecx_51 + 0xd8)) - fconvert.t(*(edi_5 + ecx_51 + 0x30)))
00426952        *(edi_5 + ecx_51 + 0x84) = var_14_1
0042695d        *(edi_5 + ecx_51 + 0x88) = fconvert.s(x87_r7_51)
00426972        i_1 += 1
00426973        *(edi_5 + self->__offset(0x5c).d + 0x8c) = fconvert.s(normalize_vector(edi_5 + self->__offset(0x5c).d + 0x80))
0042697d        edi_5 += 0xa8
00426985        do while (i_1 s< self->segment_count)
0042699a        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
004269ac        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
004269b1        void* eax_51 = self->_pad_00[0x24].d
004269b4        int32_t i_2 = 0
004269b6        int32_t edx_38 = *(eax_51 + 0x38)
004269b9        int32_t eax_52 = *(eax_51 + 0x5c)
004269c9        if (self->segment_count s>= 0)
004269cf        int32_t ebx = 0
004269d1        int32_t ecx_60 = self->__offset(0x54).d
004269d4        float edx_39 = 0f
004269d8        arg2 = 0f
004269dc        arg3 = ecx_60
004269e0        if (ecx_60 s>= 0)
004269ed        float* eax_55 = self->primary_samples + ebx
004269f5        long double x87_r7_54 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
00426a1d        float var_8_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(eax_55[1]))) + fconvert.t(eax_55[0xd]))
00426a2a        float var_4_3 = fconvert.s(x87_r7_54 * fconvert.t(eax_55[2]) + fconvert.t(eax_55[0xe]))
00426a2e        int32_t eax_58 = (ecx_60 + 1) * i_2 i+ edx_39
00426a30        edx_39 += 1
00426a31        arg2 = edx_39
00426a3c        float* ecx_62 = edx_38 + eax_58 * 0xc
00426a43        *ecx_62 = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(*eax_55))) + fconvert.t(eax_55[0xc]))
00426a49        ecx_62[1] = var_8_3
00426a50        ecx_62[2] = var_4_3
00426a53        ecx_60 = self->__offset(0x54).d
00426a58        arg3 = ecx_60
00426a5c        do while (edx_39 s<= ecx_60)
00426a61        i_2 += 1
00426a62        ebx += 0xa8
00426a6a        do while (i_2 s<= self->segment_count)
00426a73        int32_t i_3 = 0
00426a77        if (self->segment_count s> 0)
00426a80        int32_t j = 0
00426a84        arg2 = 0f
00426a88        if (self->__offset(0x54).d s> 0)
00426a90        int32_t eax_67 = i_3 & 0x80000007
00426a95        if (eax_67 s< 0)
00426a9b        eax_67 = ((eax_67 - 1) | 0xfffffff8) + 1
00426aaf        arg3 = fconvert.s(float.t(eax_67) * fconvert.t(0.125f))
00426abd        float var_40_1 = fconvert.s(float.t(eax_67 + 1) * fconvert.t(0.125f))
00426acc        int32_t ecx_63 = 0
00426ad2        int32_t var_3c_2 = 0
00426adc        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
00426aea        float var_44_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
00426b00        while (true)
00426b00        int32_t eax_74 = ecx_63 + ((self->__offset(0x54).d * i_3 + j) << 1)
00426b03        char* arg4
00426b03        if (ecx_63 != 0)
00426bc4        int16_t* ebp_2 = eax_74 * 0x30 + eax_52
00426bc7        *ebp_2 = 4
00426bcd        ecx_63.w = self->__offset(0x54).w
00426bd1        ecx_63.w += 1
00426bda        ebp_2[1] = ecx_63.w * i_3.w + j.w + 1
00426bde        int32_t eax_82
00426bde        eax_82.w = self->__offset(0x54).w
00426be2        eax_82.w += 1
00426be9        ebp_2[2] = eax_82.w * i_3.w + j.w
00426bfb        ebp_2[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
00426c13        ebp_2[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
00426c17        char* texture_path_2
00426c17        if (((j.b ^ i_3.b) & 1) != 0)
00426ca9        texture_path_2 = arg4
00426c21        texture_path_2 = arg4
00426c34        *(ebp_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_2, 0, 0)
00426c3b        *(ebp_2 + 0x10) = var_44_1
00426c3e        *(ebp_2 + 0x14) = arg3
00426c43        *(ebp_2 + 0x18) = arg2
00426c4c        *(ebp_2 + 0x1c) = arg3
00426c53        *(ebp_2 + 0x20) = arg2
00426c56        *(ebp_2 + 0x24) = var_40_1
00426c5b        *(ebp_2 + 0x28) = var_44_1
00426c5e        *(ebp_2 + 0x2c) = var_40_1
00426b09        int32_t ecx_64 = eax_74 * 3
00426b0c        eax_74.w = self->__offset(0x54).w
00426b13        eax_74.w += 1
00426b1c        void* ebp_1 = (ecx_64 << 4) + eax_52
00426b25        *(ebp_1 + 2) = eax_74.w * i_3.w + j.w
00426b29        int32_t ecx_65
00426b29        ecx_65.w = self->__offset(0x54).w
00426b2d        ecx_65.w += 1
00426b39        *(ebp_1 + 4) = ecx_65.w * i_3.w + j.w + 1
00426b4a        *(ebp_1 + 6) = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
00426b60        *(ebp_1 + 8) = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
00426b64        char* texture_path_1
00426b64        if (((j.b ^ i_3.b) & 1) != 0)
00426bb3        texture_path_1 = arg4
00426b6a        texture_path_1 = arg4
00426b7d        *(ebp_1 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00426b84        *(ebp_1 + 0x10) = arg2
00426b87        *(ebp_1 + 0x14) = arg3
00426b8c        *(ebp_1 + 0x18) = var_44_1
00426b95        *(ebp_1 + 0x1c) = arg3
00426b9c        *(ebp_1 + 0x20) = var_44_1
00426b9f        *(ebp_1 + 0x24) = var_40_1
00426ba4        *(ebp_1 + 0x28) = arg2
00426ba7        *(ebp_1 + 0x2c) = var_40_1
00426c66        bool cond:12_1 = var_3c_2 + 1 s< 2
00426c69        var_3c_2 += 1
00426c6d        if (not(cond:12_1))
00426c6d        break
00426af0        ecx_63 = var_3c_2
00426c73        j += 1
00426c7c        arg2 = j
00426c80        do while (j s< self->__offset(0x54).d)
00426c8b        i_3 += 1
00426c8e        do while (i_3 s< self->segment_count)
00426ca2        return finalize_path_template(self)
