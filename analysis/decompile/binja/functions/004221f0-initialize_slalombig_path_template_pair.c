/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_slalombig_path_template_pair @ 0x4221f0 */

004221fc        int32_t i_3 = 0
00422203        self->__offset(0x54).d = arg3
00422206        self->kind = PATH_TEMPLATE_KIND_SLALOMBIG
0042220d        uint32_t ebx = arg2 + 4
00422212        self->__offset(0x3c).b = 0
00422216        self->__offset(0x40).d = 0
0042221c        self->__offset(0x50).d = 0x3f800000
00422227        self->segment_count = ebx + 4
0042222e        self->segment_count_f = fconvert.s(float.t(ebx + 4))
00422231        allocate_path_template_samples(self)
00422236        self->__offset(0x9c).b = 0
0042223d        arg3 = 0
00422241        void* i = nullptr
004222f1        while (i s< 0x2a0)
00422246        *(&self->primary_samples->center_x + i) = 0
00422250        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0042225a        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00422264        *(&self->primary_samples->special_scalar + i) = 0
0042226e        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042227e        set_matrix_identity(self->primary_samples + i)
00422283        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00422286        long double x87_r7_1 = float.t(arg3)
00422298        *(&primary_samples_1->transform.position + i) = *(&primary_samples_1->center_x + i)
0042229e        *(&self->primary_samples->transform.position.y + i) = 0
004222a5        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
004222b0        set_matrix_identity(i + self->__offset(0x5c).d)
004222c6        *(i + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + i)
004222cd        *(i + self->__offset(0x5c).d + 0x34) = 0x3efae148
004222dc        *(i + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
004222e0        i += 0xa8
004222ed        arg3 += 1
00422309        arg3 = ebx
00422310        int32_t edi_3 = ebx * 0xa8
0042231c        *(&self->primary_samples->center_x + edi_3) = 0
00422326        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
00422330        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0042233a        *(&self->primary_samples->special_scalar + edi_3) = 0
00422344        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
00422354        set_matrix_identity(self->primary_samples + edi_3)
0042235c        void* eax_12 = self->primary_samples + edi_3
0042235e        long double x87_r7_3 = float.t(arg3)
00422368        *(eax_12 + 0x30) = *(eax_12 + 0x90)
00422372        *(&self->primary_samples->transform.position.y + edi_3) = 0
0042237b        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_3)
00422382        set_matrix_identity(edi_3 + self->__offset(0x5c).d)
00422398        *(edi_3 + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + edi_3)
004223a3        *(edi_3 + self->__offset(0x5c).d + 0x34) = 0x3efae148
004223ae        *(edi_3 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_3)))
004223b2        edi_3 += 0xa8
004223b8        ebx += 1
004223bb        arg3 = ebx
004223c2        do while (0xfffffffc - arg2 + ebx s< 4)
004223cc        uint32_t ebx_1 = 0
004223d0        arg3 = 0
004223d4        if (arg2 s> 0)
004223de        void* edi_4 = 0x2a0
004223eb        long double x87_r7_7 = float.t(arg3) / fconvert.t(fconvert.s(float.t(arg2)))
004223fb        long double x87_r7_8 = x87_r7_7 - fconvert.t(0.5f)
00422401        long double temp1_1 = fconvert.t(0f)
00422401        x87_r7_8 - temp1_1
00422407        int32_t eax_17
00422407        eax_17.w = (x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe | 0x3800
0042240c        float var_48_1
0042240c        if ((eax_17:1.b & 1) == 0)
00422418        var_48_1 = fconvert.s(x87_r7_8)
00422412        var_48_1 = fconvert.s(fneg(x87_r7_8))
0042241c        long double temp2_1 = fconvert.t(0f)
0042241c        x87_r7_8 - temp2_1
00422422        eax_17.w = (x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00422427        if ((eax_17:1.b & 1) != 0)
00422429        x87_r7_8 = fneg(x87_r7_8)
0042245d        *(&self->primary_samples->center_x + edi_4) = fconvert.s(sine(fconvert.s(x87_r7_7 * fconvert.t(6.28318548f))) * (fconvert.t(1f) - fconvert.t(fconvert.s(x87_r7_8))) * (fconvert.t(1f) - fconvert.t(var_48_1)) * fconvert.t(4.44444466f))
00422467        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
00422471        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0042247b        *(&self->primary_samples->special_scalar + edi_4) = 0
00422485        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
00422495        set_matrix_identity(self->primary_samples + edi_4)
0042249a        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004224aa        *(&primary_samples_2->transform.position + edi_4) = *(&primary_samples_2->center_x + edi_4)
004224b6        long double x87_r7_13 = float.t(ebx_1 + 4)
004224ba        *(&self->primary_samples->transform.position.y + edi_4) = 0
004224c5        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
004224cc        set_matrix_identity(edi_4 + self->__offset(0x5c).d)
004224e8        *(edi_4 + self->__offset(0x5c).d + 0x30) = *(&self->primary_samples->center_x + edi_4)
004224ef        *(edi_4 + self->__offset(0x5c).d + 0x34) = 0x3efae148
004224fa        *(edi_4 + self->__offset(0x5c).d + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
004224fe        if (edi_4 s<= 0x2a0)
004226a2        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
004226b1        set_matrix_rotation_identity(edi_4 + self->__offset(0x5c).d - 0xa8)
0042251b        int32_t* eax_24 = self->primary_samples + edi_4 - 0x98
0042252e        *eax_24 = 0
00422534        eax_24[1] = 0x3f800000
00422537        eax_24[2] = 0
0042253a        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042255e        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position.y + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x74)))
00422568        long double x87_r7_20 = fconvert.t(*(&primary_samples_4->transform.position.z + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x70))
0042256f        *(primary_samples_4 + edi_4 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x78)))
00422571        *(primary_samples_4 + edi_4 - 0x84) = var_2c_1
0042257c        *(primary_samples_4 + edi_4 - 0x80) = fconvert.s(x87_r7_20)
00422589        normalize_vector(self->primary_samples + edi_4 - 0x88)
00422591        void* eax_28 = self->primary_samples + edi_4
004225b1        int32_t var_64_3 = cross_vectors(eax_28 - 0xa8, eax_28 - 0x98, eax_28 - 0x88)
004225b2        void* eax_30 = self->primary_samples + edi_4
004225c6        rotate_matrix_world_z(eax_30 - 0xa8, fconvert.s(fconvert.t(*(eax_30 - 0x18)) * fconvert.t(0.261799395f)))
004225e2        int32_t* edx_22 = edi_4 + self->__offset(0x5c).d - 0x98
004225f5        *edx_22 = 0
004225fb        edx_22[1] = 0x3f800000
004225fe        edx_22[2] = 0
00422601        int32_t ecx_36 = self->__offset(0x5c).d
00422625        float var_14_1 = fconvert.s(fconvert.t(*(edi_4 + ecx_36 + 0x34)) - fconvert.t(*(edi_4 + ecx_36 - 0x74)))
0042262f        long double x87_r7_30 = fconvert.t(*(edi_4 + ecx_36 + 0x38)) - fconvert.t(*(edi_4 + ecx_36 - 0x70))
00422636        *(edi_4 + ecx_36 - 0x88) = fconvert.s(fconvert.t(*(edi_4 + ecx_36 + 0x30)) - fconvert.t(*(edi_4 + ecx_36 - 0x78)))
00422638        *(edi_4 + ecx_36 - 0x84) = var_14_1
00422643        *(edi_4 + ecx_36 - 0x80) = fconvert.s(x87_r7_30)
00422650        normalize_vector(edi_4 + self->__offset(0x5c).d - 0x88)
0042265a        void* eax_34 = edi_4 + self->__offset(0x5c).d
0042267c        int32_t var_64_6 = cross_vectors(eax_34 - 0xa8, eax_34 - 0x98, eax_34 - 0x88)
00422691        rotate_matrix_world_z(edi_4 + self->__offset(0x5c).d - 0xa8, fconvert.s(fconvert.t(*(self->primary_samples + edi_4 - 0x18)) * fconvert.t(0.261799395f)))
004226ba        ebx_1 += 1
004226bb        edi_4 += 0xa8
004226c3        arg3 = ebx_1
004226c7        do while (ebx_1 s< arg2)
004226d0        int32_t i_1 = 0
004226d5        if (self->segment_count - 1 s> 0)
004226db        void* edi_5 = nullptr
004226dd        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00422701        float var_14_2 = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_5)))
00422708        long double x87_r7_40 = fconvert.t(*(edi_5 + primary_samples_3 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + edi_5))
0042270f        *(&primary_samples_3->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + edi_5)))
00422711        *(&primary_samples_3->delta_dir_to_next.y + edi_5) = var_14_2
0042271c        *(&primary_samples_3->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_40)
00422731        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
00422738        int32_t edx_30 = self->__offset(0x5c).d
0042275c        float var_20_1 = fconvert.s(fconvert.t(*(edi_5 + edx_30 + 0xdc)) - fconvert.t(*(edi_5 + edx_30 + 0x34)))
00422763        long double x87_r7_47 = fconvert.t(*(edi_5 + edx_30 + 0xe0)) - fconvert.t(*(edi_5 + edx_30 + 0x38))
0042276a        *(edi_5 + edx_30 + 0x80) = fconvert.s(fconvert.t(*(edi_5 + edx_30 + 0xd8)) - fconvert.t(*(edi_5 + edx_30 + 0x30)))
0042276c        *(edi_5 + edx_30 + 0x84) = var_20_1
00422777        *(edi_5 + edx_30 + 0x88) = fconvert.s(x87_r7_47)
0042278c        i_1 += 1
0042278d        *(edi_5 + self->__offset(0x5c).d + 0x8c) = fconvert.s(normalize_vector(edi_5 + self->__offset(0x5c).d + 0x80))
00422797        edi_5 += 0xa8
004227a0        do while (i_1 s< self->segment_count - 1)
004227d0        int32_t* ecx_56 = &self->primary_samples[self->segment_count] - 0x28
004227e4        *ecx_56 = 0
004227f2        ecx_56[1] = 0
004227f5        ecx_56[2] = 0x3f800000
00422807        int32_t var_10_3 = 0x3f800000
00422813        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00422829        int32_t* eax_53 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
00422831        *eax_53 = 0
00422837        eax_53[1] = 0
0042283c        eax_53[2] = 0x3f800000
00422851        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
00422864        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
00422876        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
0042287b        void* eax_59 = self->_pad_00[0x24].d
0042287e        int32_t edx_37 = *(eax_59 + 0x38)
00422881        int32_t eax_60 = *(eax_59 + 0x5c)
0042288f        int32_t i_2 = 0
00422893        if (self->segment_count s>= 0)
00422899        int32_t ebx_2 = 0
0042289b        uint32_t ecx_68 = self->__offset(0x54).d
0042289e        int32_t edi_6 = 0
004228a2        arg2 = 0
004228a6        arg3 = ecx_68
004228aa        if (ecx_68 s>= 0)
004228bd        struct PathTemplateSample* primary_samples = self->primary_samples
004228c6        long double x87_r7_50 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
004228c8        if (i_2 == self->segment_count)
00422925        void* eax_71 = primary_samples + ebx_2
00422974        i_3 = 0
0042297d        float var_20_2 = fconvert.s(fconvert.t(*(eax_71 - 0x74)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_71 - 0xa4)))))
00422985        int32_t* ecx_72 = edx_37 + ((ecx_68 + 1) * i_2 + edi_6) * 0xc
0042298c        long double x87_r6_28 = fconvert.t(fconvert.s(fconvert.t(*(eax_71 - 0x70)) + fconvert.t(1f))) + x87_r7_50 * fconvert.t(*(eax_71 - 0xa0))
0042298e        *ecx_72 = fconvert.s(fconvert.t(*(eax_71 - 0x78)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_71 - 0xa8)))))
00422994        ecx_72[1] = var_20_2
004229a1        ecx_72[2] = fconvert.s(x87_r6_28)
004228ca        float* eax_63 = primary_samples + ebx_2
004228f2        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(eax_63[1]))) + fconvert.t(eax_63[0xd]))
004228ff        float var_10_4 = fconvert.s(x87_r7_50 * fconvert.t(eax_63[2]) + fconvert.t(eax_63[0xe]))
0042290c        int32_t* ecx_70 = edx_37 + ((ecx_68 + 1) * i_2 + edi_6) * 0xc
00422913        *ecx_70 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*eax_63))) + fconvert.t(eax_63[0xc]))
00422919        ecx_70[1] = var_14_3
00422920        ecx_70[2] = var_10_4
004229a4        ecx_68 = self->__offset(0x54).d
004229a7        edi_6 += 1
004229aa        arg2 = edi_6
004229ae        arg3 = ecx_68
004229b2        do while (edi_6 s<= ecx_68)
004229bb        i_2 += 1
004229bc        ebx_2 += 0xa8
004229c4        do while (i_2 s<= self->segment_count)
004229cd        int32_t ebx_3 = 0
004229d1        if (self->segment_count s> 0)
004229de        while (true)
004229de        arg2 = 0
004229e4        if (self->__offset(0x54).d s> 0)
004229ec        uint32_t eax_83 = ebx_3 & 0x80000007
004229f1        if (eax_83 s< 0)
004229f7        eax_83 = ((eax_83 - 1) | 0xfffffff8) + 1
00422a0b        arg3 = fconvert.s(float.t(eax_83) * fconvert.t(0.125f))
00422a19        float var_4c_2 = fconvert.s(float.t(eax_83 + 1) * fconvert.t(0.125f))
00422a24        int32_t ecx_73 = 0
00422a2a        int32_t var_48_3 = 0
00422a34        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
00422a42        float var_50_1 = fconvert.s(float.t(i_3 + 1) * fconvert.t(0.125f))
00422a54        while (true)
00422a63        int16_t* edi_7 = (ecx_73 + ((self->__offset(0x54).d * ebx_3 + i_3) << 1)) * 0x30 + eax_60
00422a66        *edi_7 = 0
00422a6b        int32_t edx_40
00422a6b        if (ecx_73 != 0)
00422b11        edx_40.w = self->__offset(0x54).w
00422b17        edx_40.w += 1
00422b22        edi_7[1] = edx_40.w * ebx_3.w + i_3.w + 1
00422b26        ecx_73.w = self->__offset(0x54).w
00422b2a        ecx_73.w += 1
00422b34        edi_7[2] = ecx_73.w * ebx_3.w + i_3.w
00422b43        edi_7[3] = (self->__offset(0x54).w + 1) * (ebx_3.w + 1) + i_3.w
00422b5a        edi_7[4] = (self->__offset(0x54).w + 1) * (ebx_3.w + 1) + i_3.w + 1
00422b5e        char* texture_path_1
00422b5e        char* arg5
00422b5e        if (((i_3.b ^ ebx_3.b) & 1) != 0)
00422bee        texture_path_1 = arg5
00422b68        texture_path_1 = arg5
00422b7b        *(edi_7 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00422b82        *(edi_7 + 0x10) = var_50_1
00422b85        *(edi_7 + 0x14) = arg3
00422b8a        *(edi_7 + 0x18) = arg2
00422b93        *(edi_7 + 0x1c) = arg3
00422b9a        *(edi_7 + 0x20) = arg2
00422b9d        *(edi_7 + 0x24) = var_4c_2
00422ba2        *(edi_7 + 0x28) = var_50_1
00422ba5        *(edi_7 + 0x2c) = var_4c_2
00422a71        ecx_73.w = self->__offset(0x54).w
00422a77        ecx_73.w += 1
00422a80        edi_7[1] = ecx_73.w * ebx_3.w + i_3.w
00422a84        edx_40.w = self->__offset(0x54).w
00422a88        edx_40.w += 1
00422a91        edi_7[2] = edx_40.w * ebx_3.w + i_3.w + 1
00422aa5        edi_7[3] = (self->__offset(0x54).w + 1) * (ebx_3.w + 1) + i_3.w + 1
00422abb        edi_7[4] = (self->__offset(0x54).w + 1) * (ebx_3.w + 1) + i_3.w
00422abf        char* texture_path
00422abf        if (((i_3.b ^ ebx_3.b) & 1) != 0)
00422b0e        texture_path = texture_b
00422ac5        texture_path = texture_b
00422ad8        *(edi_7 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
00422adf        *(edi_7 + 0x10) = arg2
00422ae2        *(edi_7 + 0x14) = arg3
00422ae7        *(edi_7 + 0x18) = var_50_1
00422af0        *(edi_7 + 0x1c) = arg3
00422af7        *(edi_7 + 0x20) = var_50_1
00422afa        *(edi_7 + 0x24) = var_4c_2
00422aff        *(edi_7 + 0x28) = arg2
00422b02        *(edi_7 + 0x2c) = var_4c_2
00422bad        bool cond:11_1 = var_48_3 + 1 s< 2
00422bb0        var_48_3 += 1
00422bb4        if (not(cond:11_1))
00422bb4        break
00422a48        ecx_73 = var_48_3
00422bba        i_3 += 1
00422bc3        arg2 = i_3
00422bc7        do while (i_3 s< self->__offset(0x54).d)
00422bd0        ebx_3 += 1
00422bd3        if (ebx_3 s>= self->segment_count)
00422bd3        break
004229d9        i_3 = 0
00422be7        return finalize_path_template(self)
