/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_turnover_path_template_pair @ 0x426cb0 */

00426cc5        int32_t i_2 = 0
00426cc9        self->kind = PATH_TEMPLATE_KIND_TURNOVER
00426cd0        self->__offset(0x3c).b = 0
00426cd4        self->__offset(0x40).d = 0
00426cd7        self->__offset(0x54).d = arg3
00426cda        int16_t x87control
00426cda        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(6.28318548f))
00426cf5        self->__offset(0x50).d = 0x3f800000
00426cf8        self->segment_count = eax_1 + 8
00426cfb        self->segment_count_f = fconvert.s(float.t(eax_1 + 8))
00426cfe        long double x87_r7_3 = float.t(eax_1)
00426d02        float var_50 = fconvert.s(x87_r7_3)
00426d0c        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
00426d10        allocate_path_template_samples(self)
00426d15        self->__offset(0x9c).b = 0
00426d1b        arg3 = 0
00426d1f        int32_t i = 0
00426de7        while (i s< 0x3f0)
00426d33        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->__offset(0x54).d) * fconvert.t(0.5f) - fconvert.t(4f))
00426d3d        *(&self->primary_samples->rotation_scalar_98 + i) = 0
00426d47        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00426d51        *(&self->primary_samples->special_scalar + i) = 0
00426d5b        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
00426d67        set_matrix_identity(self->primary_samples + i)
00426d6f        void* eax_5 = self->primary_samples + i
00426d71        long double x87_r7_8 = float.t(arg3)
00426d7b        *(eax_5 + 0x30) = *(eax_5 + 0x90)
00426d85        *(&self->primary_samples->transform.position.y + i) = 0
00426d8c        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_8)
00426d93        *(&self->primary_samples->delta_length + i) = 0x3f800000
00426d9f        set_matrix_identity(self->__offset(0x5c).d + i)
00426db5        *(self->__offset(0x5c).d + i + 0x30) = *(&self->primary_samples->center_x + i)
00426dbc        *(self->__offset(0x5c).d + i + 0x34) = 0x3efae148
00426dcb        *(self->__offset(0x5c).d + i + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_8)))
00426dd2        i += 0xa8
00426ddf        *(self->__offset(0x5c).d + i - 0x1c) = 0x3f800000
00426de3        arg3 += 1
00426df4        arg3 = eax_1 + 6
00426e09        int32_t edi_1 = (eax_1 + 6) * 0xa8
00426e0e        int32_t var_40 = edi_1
00426ee4        int32_t i_1
00426e28        *(&self->primary_samples->center_x + edi_1) = fconvert.s(fconvert.t(4f) - float.t(self->__offset(0x54).d) * fconvert.t(0.5f))
00426e32        *(&self->primary_samples->rotation_scalar_98 + edi_1) = 0
00426e3c        *(&self->primary_samples->rotation_scalar_94 + edi_1) = 0
00426e46        *(&self->primary_samples->special_scalar + edi_1) = 0
00426e50        *(&self->primary_samples->lateral_scale + edi_1) = 0x3f800000
00426e5c        set_matrix_identity(self->primary_samples + edi_1)
00426e61        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00426e64        long double x87_r7_13 = float.t(arg3)
00426e76        *(&primary_samples_2->transform.position + edi_1) = *(&primary_samples_2->center_x + edi_1)
00426e7c        *(&self->primary_samples->transform.position.y + edi_1) = 0
00426e83        *(&self->primary_samples->transform.position.z + edi_1) = fconvert.s(x87_r7_13)
00426e8a        *(&self->primary_samples->delta_length + edi_1) = 0x3f800000
00426e96        set_matrix_identity(self->__offset(0x5c).d + edi_1)
00426eac        *(self->__offset(0x5c).d + edi_1 + 0x30) = *(&self->primary_samples->center_x + edi_1)
00426eb3        *(self->__offset(0x5c).d + edi_1 + 0x34) = 0x3efae148
00426ec2        *(self->__offset(0x5c).d + edi_1 + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
00426ecd        *(self->__offset(0x5c).d + edi_1 + 0x8c) = 0x3f800000
00426ed4        edi_1 += 0xa8
00426edb        i_1 = 0xfffffffa - eax_1 + arg3 + 1
00426edd        arg3 += 1
00426ee4        do while (i_1 s< 2)
00426eee        arg3 = 0
00426ef4        if (eax_1 s> 0)
00426f02        int32_t ebx = 0x3f0
004270f5        bool cond:1_1
00426f07        long double x87_r7_15 = float.t(arg3)
00426f0b        struct PathTemplateSample* primary_samples = self->primary_samples
00426f1e        float var_4c_1 = fconvert.s(x87_r7_15 * fconvert.t(6.28318548f) / fconvert.t(var_50))
00426f3b        *(&primary_samples->center_x + ebx) = fconvert.s((fconvert.t(*(&primary_samples->center_x + var_40)) - fconvert.t(primary_samples->center_x)) * x87_r7_15 / fconvert.t(var_50) + fconvert.t(primary_samples->center_x))
00426f4d        *(&self->primary_samples->rotation_scalar_98 + ebx) = fconvert.s(fneg(fconvert.t(var_4c_1)))
00426f59        *(&self->primary_samples->rotation_scalar_94 + ebx) = 0
00426f63        *(&self->primary_samples->special_scalar + ebx) = 0
00426f6d        *(&self->primary_samples->lateral_scale + ebx) = 0x3f800000
00426f77        struct TransformMatrix* transform = self->primary_samples + ebx
00426f79        set_matrix_identity(transform)
00426f88        struct PathTemplateSample* primary_samples_5 = self->primary_samples
00426f8b        struct TransformMatrix* transform_1 = transform
00426f98        float var_44_3 = fconvert.s(sine(fconvert.s(fconvert.t(var_4c_1) * fconvert.t(0.5f))))
00426fa2        long double x87_r7_23 = sine(var_4c_1) * fconvert.t(var_44_3)
00426fbe        *(&self->primary_samples->transform.position + ebx) = fconvert.s(fconvert.t(*(&primary_samples_5->center_x + ebx)) - (x87_r7_23 + x87_r7_23))
00426fc9        *(&self->primary_samples->transform.position.z + ebx) = fconvert.s(float.t(arg3 + 6))
00426fe4        *(&self->primary_samples->transform.position.y + ebx) = fconvert.s((fconvert.t(arg2) - cosine(var_4c_1) * fconvert.t(arg2)) * fconvert.t(0.400000006f))
00426fed        float var_44_5 = fconvert.s(cosine(var_4c_1))
00426ff2        long double st0_5 = sine(var_4c_1)
0042700a        float* ecx_25 = &self->primary_samples->transform.basis_up + ebx
00427015        *ecx_25 = fconvert.s(st0_5)
0042701b        ecx_25[1] = var_44_5
0042701e        ecx_25[2] = 0
00427024        void* eax_27 = self->primary_samples + ebx
0042703d        float var_2c_1 = fconvert.s(fconvert.t(*(eax_27 + 0x34)) - fconvert.t(*(eax_27 - 0x74)))
00427044        long double x87_r7_38 = fconvert.t(*(eax_27 + 0x38)) - fconvert.t(*(eax_27 - 0x70))
0042704e        *(eax_27 + 0x20) = fconvert.s(fconvert.t(*(eax_27 + 0x30)) - fconvert.t(*(eax_27 - 0x78)))
00427050        *(eax_27 + 0x24) = var_2c_1
0042705b        *(eax_27 + 0x28) = fconvert.s(x87_r7_38)
00427065        normalize_vector(&self->primary_samples->transform.basis_forward + ebx)
0042706f        struct Vec3* out = self->primary_samples + ebx
0042707a        cross_vectors(out, out + 0x10, out + 0x20)
0042708e        __builtin_memcpy(self->__offset(0x5c).d + ebx, self->primary_samples + ebx, 0x40)
00427090        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042709f        long double x87_r7_42 = fconvert.t(*(&primary_samples_3->transform.basis_up + ebx)) * fconvert.t(0.49000001f)
004270b7        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_3->transform.basis_up.y + ebx)) * fconvert.t(0.49000001f))
004270be        long double x87_r6_12 = fconvert.t(*(&primary_samples_3->transform.basis_up.z + ebx)) * fconvert.t(0.49000001f)
004270c4        float* eax_32 = self->__offset(0x5c).d + ebx + 0x30
004270c8        ebx += 0xa8
004270d4        *eax_32 = fconvert.s(x87_r7_42 + fconvert.t(*eax_32))
004270dd        eax_32[1] = fconvert.s(fconvert.t(var_20_1) + fconvert.t(eax_32[1]))
004270e7        eax_32[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_12)) + fconvert.t(eax_32[2]))
004270ef        cond:1_1 = arg3 + 1 s< eax_1
004270f1        arg3 += 1
004270f5        do while (cond:1_1)
004270fb        i_2 = 0
00427103        if (self->segment_count - 1 s> 0)
00427109        void* edi_4 = nullptr
0042710b        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042712f        float var_2c_2 = fconvert.s(fconvert.t(*(edi_4 + primary_samples_4 + 0xdc)) - fconvert.t(*(&primary_samples_4->transform.position.y + edi_4)))
00427136        long double x87_r7_53 = fconvert.t(*(edi_4 + primary_samples_4 + 0xe0)) - fconvert.t(*(&primary_samples_4->transform.position.z + edi_4))
0042713d        *(&primary_samples_4->delta_dir_to_next + edi_4) = fconvert.s(fconvert.t(*(edi_4 + primary_samples_4 + 0xd8)) - fconvert.t(*(&primary_samples_4->transform.position + edi_4)))
0042713f        *(&primary_samples_4->delta_dir_to_next.y + edi_4) = var_2c_2
0042714a        *(&primary_samples_4->delta_dir_to_next.z + edi_4) = fconvert.s(x87_r7_53)
0042715f        *(&self->primary_samples->delta_length + edi_4) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_4))
00427166        int32_t edx_27 = self->__offset(0x5c).d
0042718a        float var_38_2 = fconvert.s(fconvert.t(*(edi_4 + edx_27 + 0xdc)) - fconvert.t(*(edi_4 + edx_27 + 0x34)))
00427191        long double x87_r7_60 = fconvert.t(*(edi_4 + edx_27 + 0xe0)) - fconvert.t(*(edi_4 + edx_27 + 0x38))
00427198        *(edi_4 + edx_27 + 0x80) = fconvert.s(fconvert.t(*(edi_4 + edx_27 + 0xd8)) - fconvert.t(*(edi_4 + edx_27 + 0x30)))
0042719a        *(edi_4 + edx_27 + 0x84) = var_38_2
004271a5        *(edi_4 + edx_27 + 0x88) = fconvert.s(x87_r7_60)
004271ba        i_2 += 1
004271bb        *(edi_4 + self->__offset(0x5c).d + 0x8c) = fconvert.s(normalize_vector(edi_4 + self->__offset(0x5c).d + 0x80))
004271c5        edi_4 += 0xa8
004271ce        do while (i_2 s< self->segment_count - 1)
004271fe        int32_t* ecx_39 = &self->primary_samples[self->segment_count] - 0x28
00427212        *ecx_39 = 0
00427228        ecx_39[1] = 0
0042722b        ecx_39[2] = 0x3f800000
00427240        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00427256        int32_t* ecx_43 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
00427262        *ecx_43 = 0
00427268        ecx_43[1] = 0
0042726b        ecx_43[2] = 0x3f800000
00427280        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
00427293        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
004272a5        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
004272aa        void* eax_57 = self->_pad_00[0x24].d
004272ad        int32_t edx_35 = *(eax_57 + 0x5c)
004272b0        int32_t ebx_1 = *(eax_57 + 0x38)
004272ba        int32_t i_3 = 0
004272bc        int32_t var_40_1 = ebx_1
004272c2        if (self->segment_count s>= 0)
004272c8        int32_t esi_4 = 0
004272ca        int32_t ecx_51 = self->__offset(0x54).d
004272cd        float edi_5 = 0f
004272d1        arg2 = 0f
004272d5        arg3 = ecx_51
004272d9        if (ecx_51 s>= 0)
004272ec        struct PathTemplateSample* primary_samples_1 = self->primary_samples
004272f5        long double x87_r7_63 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
004272f7        float* eax_64
004272f7        float ecx_55
004272f7        if (i_3 == self->segment_count)
0042734d        void* eax_65 = primary_samples_1 + esi_4
0042735e        ebx_1 = var_40_1
004273a3        float var_38_3 = fconvert.s(fconvert.t(*(eax_65 - 0x74)) + fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(*(eax_65 - 0xa4)))))
004273ab        long double x87_r6_32 = fconvert.t(fconvert.s(fconvert.t(*(eax_65 - 0x70)) + fconvert.t(1f))) + x87_r7_63 * fconvert.t(*(eax_65 - 0xa0))
004273ad        eax_64 = ebx_1 + ((ecx_51 + 1) * i_3 i+ edi_5) * 0xc
004273b4        *eax_64 = fconvert.s(fconvert.t(*(eax_65 - 0x78)) + fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(*(eax_65 - 0xa8)))))
004273be        eax_64[1] = var_38_3
004273c1        ecx_55 = fconvert.s(x87_r6_32)
004272f9        float* eax_60 = primary_samples_1 + esi_4
00427321        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(eax_60[1]))) + fconvert.t(eax_60[0xd]))
0042732e        float var_28_3 = fconvert.s(x87_r7_63 * fconvert.t(eax_60[2]) + fconvert.t(eax_60[0xe]))
00427337        eax_64 = ebx_1 + ((ecx_51 + 1) * i_3 i+ edi_5) * 0xc
0042733e        *eax_64 = fconvert.s(fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(*eax_60))) + fconvert.t(eax_60[0xc]))
00427344        eax_64[1] = var_2c_3
00427347        ecx_55 = var_28_3
004273c7        eax_64[2] = ecx_55
004273ca        ecx_51 = self->__offset(0x54).d
004273cd        edi_5 += 1
004273ce        arg3 = ecx_51
004273d4        arg2 = edi_5
004273d8        do while (edi_5 s<= ecx_51)
004273e1        i_3 += 1
004273e2        esi_4 += 0xa8
004273ea        do while (i_3 s<= self->segment_count)
004273f3        int32_t i_4 = 0
004273f7        if (self->segment_count s> 0)
00427400        int32_t j = 0
00427404        arg2 = 0f
00427408        if (self->__offset(0x54).d s> 0)
00427410        int32_t eax_73 = i_4 & 0x80000007
00427415        if (eax_73 s< 0)
0042741b        eax_73 = ((eax_73 - 1) | 0xfffffff8) + 1
0042742f        arg3 = fconvert.s(float.t(eax_73) * fconvert.t(0.125f))
0042743d        float var_50_1 = fconvert.s(float.t(eax_73 + 1) * fconvert.t(0.125f))
00427448        int32_t ecx_59 = 0
0042744e        int32_t var_4c_2 = 0
00427458        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
00427466        float var_54_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042747a        while (true)
0042747a        int32_t eax_80 = ecx_59 + ((self->__offset(0x54).d * i_4 + j) << 1)
0042747d        if (ecx_59 != 0)
00427543        int16_t* ebx_4 = eax_80 * 0x30 + edx_35
00427546        *ebx_4 = 0
0042754b        ecx_59.w = self->__offset(0x54).w
0042754f        ecx_59.w += 1
00427558        ebx_4[1] = ecx_59.w * i_4.w + j.w + 1
0042755c        int32_t eax_88
0042755c        eax_88.w = self->__offset(0x54).w
00427560        eax_88.w += 1
00427567        ebx_4[2] = eax_88.w * i_4.w + j.w
00427579        ebx_4[3] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w
00427591        ebx_4[4] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w + 1
00427595        char* texture_path_1
00427595        char* arg5
00427595        if (((j.b ^ i_4.b) & 1) != 0)
0042762b        texture_path_1 = arg5
004275a2        texture_path_1 = arg5
004275b5        *(ebx_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
004275bc        *(ebx_4 + 0x10) = var_54_1
004275bf        *(ebx_4 + 0x14) = arg3
004275c4        *(ebx_4 + 0x18) = arg2
004275cd        *(ebx_4 + 0x1c) = arg3
004275d4        *(ebx_4 + 0x20) = arg2
004275d7        *(ebx_4 + 0x24) = var_50_1
004275dc        *(ebx_4 + 0x28) = var_54_1
004275df        *(ebx_4 + 0x2c) = var_50_1
00427491        int16_t* ebx_3 = eax_80 * 0x30 + edx_35
00427494        *ebx_3 = 0
00427499        eax_80.w = self->__offset(0x54).w
0042749d        eax_80.w += 1
004274a4        ebx_3[1] = eax_80.w * i_4.w + j.w
004274a8        int32_t ecx_61
004274a8        ecx_61.w = self->__offset(0x54).w
004274ac        ecx_61.w += 1
004274b8        ebx_3[2] = ecx_61.w * i_4.w + j.w + 1
004274c9        ebx_3[3] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w + 1
004274df        ebx_3[4] = (self->__offset(0x54).w + 1) * (i_4.w + 1) + j.w
004274e3        char* texture_path
004274e3        if (((j.b ^ i_4.b) & 1) != 0)
00427532        texture_path = texture_b
004274e9        texture_path = texture_b
004274fc        *(ebx_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
00427503        *(ebx_3 + 0x10) = arg2
00427506        *(ebx_3 + 0x14) = arg3
0042750b        *(ebx_3 + 0x18) = var_54_1
00427514        *(ebx_3 + 0x1c) = arg3
0042751b        *(ebx_3 + 0x20) = var_54_1
0042751e        *(ebx_3 + 0x24) = var_50_1
00427523        *(ebx_3 + 0x28) = arg2
00427526        *(ebx_3 + 0x2c) = var_50_1
004275e7        bool cond:10_1 = var_4c_2 + 1 s< 2
004275ea        var_4c_2 += 1
004275ee        if (not(cond:10_1))
004275ee        break
0042746c        ecx_59 = var_4c_2
004275f4        j += 1
004275fd        arg2 = j
00427601        do while (j s< self->__offset(0x54).d)
0042760a        i_4 += 1
0042760d        do while (i_4 s< self->segment_count)
00427621        return finalize_path_template(self)
