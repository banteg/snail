/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_dump_path_template_pair @ 0x41da30 */

0041da46        int32_t i_3 = 0
0041da49        self->kind = PATH_TEMPLATE_KIND_FAMILY_11
0041da50        self->__offset(0x3c).b = 0
0041da54        self->__offset(0x40).d = 0
0041da57        self->__offset(0x54).d = arg4
0041da5a        int16_t x87control
0041da5a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(4f))
0041da5f        int32_t ebp = eax_1 + 7
0041da68        self->__offset(0x50).d = 0x3f800000
0041da76        self->segment_count = ebp + 7
0041da7d        self->segment_count_f = fconvert.s(float.t(ebp + 7))
0041da80        long double x87_r7_3 = float.t(eax_1)
0041da8e        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.0954929665f))
0041da92        allocate_path_template_samples(self)
0041da97        self->__offset(0x9c).b = 0
0041da9d        arg4 = 0
0041daa1        void* i = nullptr
0041db60        while (i s< 0x498)
0041dab7        *(&self->primary_samples->center_x + i) = fconvert.s(fneg(float.t(self->__offset(0x54).d) * fconvert.t(0.5f) - fconvert.t(4f)))
0041dac1        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041dacb        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041dad5        *(&self->primary_samples->special_scalar + i) = 0
0041dae1        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041daf1        set_matrix_identity(i + self->primary_samples)
0041daf9        void* eax_5 = self->primary_samples + i
0041dafb        long double x87_r7_9 = float.t(arg4)
0041db05        *(eax_5 + 0x30) = *(eax_5 + 0x90)
0041db0f        *(&self->primary_samples->transform.position.y + i) = 0
0041db16        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_9)
0041db1f        set_matrix_identity(self->__offset(0x5c).d + i)
0041db35        *(self->__offset(0x5c).d + i + 0x30) = *(&self->primary_samples->center_x + i)
0041db3c        *(self->__offset(0x5c).d + i + 0x34) = 0x3efae148
0041db47        *(self->__offset(0x5c).d + i + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_9)))
0041db4f        i += 0xa8
0041db5c        arg4 += 1
0041db78        arg4 = ebp
0041db7f        int32_t edi_3 = ebp * 0xa8
0041dc46        int32_t ecx_19
0041db9c        *(&self->primary_samples->center_x + edi_3) = fconvert.s(fneg(fconvert.t(4f) - float.t(self->__offset(0x54).d) * fconvert.t(0.5f)))
0041dba6        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041dbb0        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041dbba        *(&self->primary_samples->special_scalar + edi_3) = 0
0041dbc4        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041dbd6        set_matrix_identity(edi_3 + self->primary_samples)
0041dbdb        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041dbde        long double x87_r7_15 = float.t(arg4)
0041dbf0        *(&primary_samples_2->transform.position + edi_3) = *(&primary_samples_2->center_x + edi_3)
0041dbf6        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041dbfd        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_15)
0041dc06        set_matrix_identity(self->__offset(0x5c).d + edi_3)
0041dc1c        *(self->__offset(0x5c).d + edi_3 + 0x30) = *(&self->primary_samples->center_x + edi_3)
0041dc20        ecx_19 = self->__offset(0x5c).d
0041dc27        *(ecx_19 + edi_3 + 0x34) = 0x3efae148
0041dc32        *(self->__offset(0x5c).d + edi_3 + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_15)))
0041dc36        edi_3 += 0xa8
0041dc3c        ebp += 1
0041dc3f        arg4 = ebp
0041dc46        do while (0xfffffff9 - eax_1 + ebp s< 7)
0041dc50        arg4 = 0
0041dc56        if (eax_1 s> 0)
0041dc5c        void* edi_4 = 0x498
0041deff        bool cond:4_1
0041dc65        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041dc68        int32_t var_60_1 = ecx_19
0041dc73        float var_44_1 = fconvert.s(float.t(arg4) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(x87_r7_3)))
0041dc92        *(&primary_samples_4->center_x + edi_4) = fconvert.s(cosine(fconvert.s(fconvert.t(var_44_1) * fconvert.t(0.5f))) * fconvert.t(primary_samples_4->center_x))
0041dc9c        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041dca6        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0041dcb0        *(&self->primary_samples->special_scalar + edi_4) = 0
0041dcba        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041dccc        set_matrix_identity(edi_4 + self->primary_samples)
0041dcd1        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041dce3        *(&primary_samples_3->transform.position + edi_4) = *(&primary_samples_3->center_x + edi_4)
0041dd0c        *(&self->primary_samples->transform.position.y + edi_4) = fconvert.s(fneg((fconvert.t(1f) - cosine(var_44_1)) * fconvert.t(arg2) * fconvert.t(arg3)))
0041dd10        long double x87_r7_29 = float.t(arg4 + 7)
0041dd1b        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_29)
0041dd24        set_matrix_identity(self->__offset(0x5c).d + edi_4)
0041dd37        *(self->__offset(0x5c).d + edi_4 + 0x30) = *(&self->primary_samples->center_x + edi_4)
0041dd60        *(self->__offset(0x5c).d + edi_4 + 0x34) = fconvert.s(fconvert.t(0.49000001f) - (fconvert.t(1f) - cosine(var_44_1)) * fconvert.t(arg2) * fconvert.t(arg3))
0041dd6b        *(self->__offset(0x5c).d + edi_4 + 0x38) = fconvert.s(fconvert.t(fconvert.s(x87_r7_29)))
0041dd6f        if (edi_4 s<= 0x498)
0041ded6        set_matrix_rotation_identity(edi_4 + self->primary_samples - 0xa8)
0041dee5        set_matrix_rotation_identity(self->__offset(0x5c).d + edi_4 - 0xa8)
0041dd8c        int32_t* edx_17 = edi_4 + self->primary_samples - 0xa8
0041dd9f        *edx_17 = 0x3f800000
0041dda5        edx_17[1] = 0
0041dda8        edx_17[2] = 0
0041ddab        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041ddcf        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position.y + edi_4)) - fconvert.t(*(edi_4 + primary_samples_1 - 0x74)))
0041ddd9        long double x87_r7_41 = fconvert.t(*(&primary_samples_1->transform.position.z + edi_4)) - fconvert.t(*(edi_4 + primary_samples_1 - 0x70))
0041dde0        *(edi_4 + primary_samples_1 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position + edi_4)) - fconvert.t(*(edi_4 + primary_samples_1 - 0x78)))
0041dde2        *(edi_4 + primary_samples_1 - 0x84) = var_2c_1
0041dded        *(edi_4 + primary_samples_1 - 0x80) = fconvert.s(x87_r7_41)
0041ddfa        normalize_vector(edi_4 + self->primary_samples - 0x88)
0041de04        void* eax_27 = edi_4 + self->primary_samples
0041de1b        cross_vectors(eax_27 - 0x98, eax_27 - 0x88, eax_27 - 0xa8)
0041de37        int32_t* eax_28 = self->__offset(0x5c).d + edi_4 - 0xa8
0041de4a        *eax_28 = 0x3f800000
0041de50        eax_28[1] = 0
0041de53        eax_28[2] = 0
0041de56        void* edx_22 = self->__offset(0x5c).d
0041de7a        float var_14_1 = fconvert.s(fconvert.t(*(edx_22 + edi_4 + 0x34)) - fconvert.t(*(edx_22 + edi_4 - 0x74)))
0041de84        long double x87_r7_49 = fconvert.t(*(edx_22 + edi_4 + 0x38)) - fconvert.t(*(edx_22 + edi_4 - 0x70))
0041de8b        *(edx_22 + edi_4 - 0x88) = fconvert.s(fconvert.t(*(edx_22 + edi_4 + 0x30)) - fconvert.t(*(edx_22 + edi_4 - 0x78)))
0041de8d        *(edx_22 + edi_4 - 0x84) = var_14_1
0041de98        *(edx_22 + edi_4 - 0x80) = fconvert.s(x87_r7_49)
0041dea5        normalize_vector(self->__offset(0x5c).d + edi_4 - 0x88)
0041dead        void* eax_32 = self->__offset(0x5c).d + edi_4
0041dec5        cross_vectors(eax_32 - 0x98, eax_32 - 0x88, eax_32 - 0xa8)
0041deee        ecx_19 = eax_1
0041def3        edi_4 += 0xa8
0041def9        cond:4_1 = arg4 + 1 s< ecx_19
0041defb        arg4 += 1
0041deff        do while (cond:4_1)
0041df08        int32_t i_1 = 0
0041df0d        if (self->segment_count - 1 s> 0)
0041df13        void* edi_5 = nullptr
0041df18        void* eax_37 = self->primary_samples + edi_5
0041df36        float var_14_2 = fconvert.s(fconvert.t(*(eax_37 + 0xdc)) - fconvert.t(*(eax_37 + 0x34)))
0041df3d        long double x87_r7_57 = fconvert.t(*(eax_37 + 0xe0)) - fconvert.t(*(eax_37 + 0x38))
0041df44        *(eax_37 + 0x80) = fconvert.s(fconvert.t(*(eax_37 + 0xd8)) - fconvert.t(*(eax_37 + 0x30)))
0041df46        *(eax_37 + 0x84) = var_14_2
0041df51        *(eax_37 + 0x88) = fconvert.s(x87_r7_57)
0041df66        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041df6d        int32_t ecx_46 = self->__offset(0x5c).d
0041df91        float var_20_1 = fconvert.s(fconvert.t(*(edi_5 + ecx_46 + 0xdc)) - fconvert.t(*(edi_5 + ecx_46 + 0x34)))
0041df98        long double x87_r7_64 = fconvert.t(*(edi_5 + ecx_46 + 0xe0)) - fconvert.t(*(edi_5 + ecx_46 + 0x38))
0041df9f        *(edi_5 + ecx_46 + 0x80) = fconvert.s(fconvert.t(*(edi_5 + ecx_46 + 0xd8)) - fconvert.t(*(edi_5 + ecx_46 + 0x30)))
0041dfa1        *(edi_5 + ecx_46 + 0x84) = var_20_1
0041dfac        *(edi_5 + ecx_46 + 0x88) = fconvert.s(x87_r7_64)
0041dfc1        i_1 += 1
0041dfc2        *(edi_5 + self->__offset(0x5c).d + 0x8c) = fconvert.s(normalize_vector(edi_5 + self->__offset(0x5c).d + 0x80))
0041dfcc        edi_5 += 0xa8
0041dfd5        do while (i_1 s< self->segment_count - 1)
0041e005        int32_t* edx_34 = &self->primary_samples[self->segment_count] - 0x28
0041e019        *edx_34 = 0
0041e027        edx_34[1] = 0
0041e02a        edx_34[2] = 0x3f800000
0041e03c        int32_t var_10_3 = 0x3f800000
0041e048        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041e05e        int32_t* ecx_56 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
0041e066        *ecx_56 = 0
0041e06c        ecx_56[1] = 0
0041e071        ecx_56[2] = 0x3f800000
0041e086        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
0041e099        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
0041e0ab        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
0041e0b0        void* eax_58 = self->_pad_00[0x24].d
0041e0b3        int32_t i_2 = 0
0041e0b5        int32_t ebp_3 = *(eax_58 + 0x38)
0041e0b8        int32_t ecx_64 = *(eax_58 + 0x5c)
0041e0be        arg4 = ebp_3
0041e0c8        if (self->segment_count s>= 0)
0041e0ce        float ecx_65 = self->__offset(0x54).d
0041e0d1        float edi_6 = 0f
0041e0d5        arg2 = 0f
0041e0d9        arg3 = ecx_65
0041e0dd        if (ecx_65 s>= 0)
0041e0f0        struct PathTemplateSample* primary_samples = self->primary_samples
0041e0f9        long double x87_r7_67 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041e0fb        int32_t eax_65
0041e0fb        float ecx_69
0041e0fb        if (i_2 == self->segment_count)
0041e152        void* eax_66 = primary_samples + i_3
0041e163        ebp_3 = arg4
0041e1a8        float var_20_2 = fconvert.s(fconvert.t(*(eax_66 - 0x74)) + fconvert.t(fconvert.s(x87_r7_67 * fconvert.t(*(eax_66 - 0xa4)))))
0041e1b0        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_66 - 0x70)) + fconvert.t(1f))) + x87_r7_67 * fconvert.t(*(eax_66 - 0xa0))
0041e1b2        eax_65 = ebp_3 + ((ecx_65 i+ 1) * i_2 i+ edi_6) * 0xc
0041e1ba        *eax_65 = fconvert.s(fconvert.t(*(eax_66 - 0x78)) + fconvert.t(fconvert.s(x87_r7_67 * fconvert.t(*(eax_66 - 0xa8)))))
0041e1c4        *(eax_65 + 4) = var_20_2
0041e1c7        ecx_69 = fconvert.s(x87_r6_20)
0041e0fd        float* eax_61 = primary_samples + i_3
0041e125        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_67 * fconvert.t(eax_61[1]))) + fconvert.t(eax_61[0xd]))
0041e132        float var_10_4 = fconvert.s(x87_r7_67 * fconvert.t(eax_61[2]) + fconvert.t(eax_61[0xe]))
0041e13b        eax_65 = ebp_3 + ((ecx_65 i+ 1) * i_2 i+ edi_6) * 0xc
0041e143        *eax_65 = fconvert.s(fconvert.t(fconvert.s(x87_r7_67 * fconvert.t(*eax_61))) + fconvert.t(eax_61[0xc]))
0041e149        *(eax_65 + 4) = var_14_3
0041e14c        ecx_69 = var_10_4
0041e1cd        *(eax_65 + 8) = ecx_69
0041e1d0        ecx_65 = self->__offset(0x54).d
0041e1d3        edi_6 += 1
0041e1d4        arg3 = ecx_65
0041e1da        arg2 = edi_6
0041e1de        do while (edi_6 s<= ecx_65)
0041e1e7        i_2 += 1
0041e1e8        i_3 += 0xa8
0041e1f0        do while (i_2 s<= self->segment_count)
0041e1f6        i_3 = 0
0041e1fd        if (self->segment_count s> 0)
0041e206        int32_t j = 0
0041e20a        arg2 = 0f
0041e20e        if (self->__offset(0x54).d s> 0)
0041e216        float eax_74 = i_3 & 0x80000007
0041e21b        if (eax_74 s< 0)
0041e221        eax_74 = ((eax_74 i- 1) | 0xfffffff8) + 1
0041e235        arg3 = fconvert.s(float.t(eax_74) * fconvert.t(0.125f))
0041e243        float var_4c_1 = fconvert.s(float.t(eax_74 i+ 1) * fconvert.t(0.125f))
0041e24e        int32_t ecx_73 = 0
0041e254        int32_t var_48_1 = 0
0041e25e        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041e26c        arg4 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041e280        while (true)
0041e280        int32_t eax_81 = ecx_73 + ((self->__offset(0x54).d * i_3 + j) << 1)
0041e283        if (ecx_73 != 0)
0041e34a        int16_t* ebp_6 = eax_81 * 0x30 + ecx_64
0041e34d        *ebp_6 = 0
0041e353        ecx_73.w = self->__offset(0x54).w
0041e357        ecx_73.w += 1
0041e360        ebp_6[1] = ecx_73.w * i_3.w + j.w + 1
0041e364        int32_t eax_89
0041e364        eax_89.w = self->__offset(0x54).w
0041e368        eax_89.w += 1
0041e36f        ebp_6[2] = eax_89.w * i_3.w + j.w
0041e381        ebp_6[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
0041e399        ebp_6[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
0041e39d        char* texture_path_1
0041e39d        char* arg6
0041e39d        if (((j.b ^ i_3.b) & 1) != 0)
0041e42d        texture_path_1 = arg6
0041e3a7        texture_path_1 = arg6
0041e3ba        *(ebp_6 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0041e3c1        *(ebp_6 + 0x10) = arg4
0041e3c4        *(ebp_6 + 0x14) = arg3
0041e3c9        *(ebp_6 + 0x18) = arg2
0041e3d2        *(ebp_6 + 0x1c) = arg3
0041e3d9        *(ebp_6 + 0x20) = arg2
0041e3dc        *(ebp_6 + 0x24) = var_4c_1
0041e3e1        *(ebp_6 + 0x28) = arg4
0041e3e4        *(ebp_6 + 0x2c) = var_4c_1
0041e297        int16_t* ebp_5 = eax_81 * 0x30 + ecx_64
0041e29a        *ebp_5 = 0
0041e2a0        eax_81.w = self->__offset(0x54).w
0041e2a4        eax_81.w += 1
0041e2ab        ebp_5[1] = eax_81.w * i_3.w + j.w
0041e2af        int32_t ecx_75
0041e2af        ecx_75.w = self->__offset(0x54).w
0041e2b3        ecx_75.w += 1
0041e2bf        ebp_5[2] = ecx_75.w * i_3.w + j.w + 1
0041e2d0        ebp_5[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
0041e2e6        ebp_5[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
0041e2ea        char* texture_path
0041e2ea        if (((j.b ^ i_3.b) & 1) != 0)
0041e339        texture_path = texture_b
0041e2f0        texture_path = texture_b
0041e303        *(ebp_5 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0041e30a        *(ebp_5 + 0x10) = arg2
0041e30d        *(ebp_5 + 0x14) = arg3
0041e312        *(ebp_5 + 0x18) = arg4
0041e31b        *(ebp_5 + 0x1c) = arg3
0041e322        *(ebp_5 + 0x20) = arg4
0041e325        *(ebp_5 + 0x24) = var_4c_1
0041e32a        *(ebp_5 + 0x28) = arg2
0041e32d        *(ebp_5 + 0x2c) = var_4c_1
0041e3ec        bool cond:12_1 = var_48_1 + 1 s< 2
0041e3ef        var_48_1 += 1
0041e3f3        if (not(cond:12_1))
0041e3f3        break
0041e272        ecx_73 = var_48_1
0041e3f9        j += 1
0041e402        arg2 = j
0041e406        do while (j s< self->__offset(0x54).d)
0041e40f        i_3 += 1
0041e412        do while (i_3 s< self->segment_count)
0041e426        return finalize_path_template(self)
