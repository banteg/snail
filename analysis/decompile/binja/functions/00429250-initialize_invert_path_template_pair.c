/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_invert_path_template_pair @ 0x429250 */

00429264        self->kind = PATH_TEMPLATE_KIND_INVERT
0042926b        self->__offset(0x3c).b = 0
0042926f        self->__offset(0x40).d = 0
00429272        self->__offset(0x54).d = texture_a
00429275        self->__offset(0x50).d = 0x3f800000
00429278        self->segment_count = 0x22
0042927f        self->segment_count_f = 34f
00429286        allocate_path_template_samples(self)
0042928b        long double x87_r7 = float.t(self->__offset(0x54).d)
0042928e        struct PathTemplateSample* primary_samples_4 = self->primary_samples
00429291        self->__offset(0x9c).b = 1
004292a4        primary_samples_4->center_x = fconvert.s(x87_r7 * fconvert.t(0.5f) - fconvert.t(4f))
004292ad        self->primary_samples->rotation_scalar_98 = 0f
004292b6        self->primary_samples->rotation_scalar_94 = 0f
004292bf        self->primary_samples->special_scalar = 0f
004292c8        self->primary_samples->lateral_scale = 1f
004292d1        set_matrix_identity(self->primary_samples)
004292d6        struct PathTemplateSample* primary_samples = self->primary_samples
004292df        primary_samples->transform.position.x = primary_samples->center_x
004292e5        self->primary_samples->transform.position.y = 0f
004292eb        self->primary_samples->transform.position.z = 0f
004292f1        self->primary_samples->delta_length = 1f
004292fa        set_matrix_identity(self->__offset(0x5c).d)
0042930b        *(self->__offset(0x5c).d + 0x30) = self->primary_samples->center_x
00429311        *(self->__offset(0x5c).d + 0x34) = 0x3efae148
0042931b        *(self->__offset(0x5c).d + 0x38) = 0
00429321        *(self->__offset(0x5c).d + 0x8c) = 0x3f800000
00429339        self->primary_samples->__offset(0x1638).d = fconvert.s(fconvert.t(4f) - float.t(self->__offset(0x54).d) * fconvert.t(0.5f))
00429342        self->primary_samples->__offset(0x1640).d = 0x40490fdb
0042934f        self->primary_samples->__offset(0x163c).d = 0
00429358        self->primary_samples->__offset(0x1648).d = 0
00429361        self->primary_samples->__offset(0x1644).d = 0x3f800000
00429370        set_matrix_identity(&self->primary_samples[0x21])
00429375        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00429383        primary_samples_1->__offset(0x15d8).d = primary_samples_1->__offset(0x1638).d
0042938c        self->primary_samples->__offset(0x15dc).d = 0
00429395        self->primary_samples->__offset(0x15e0).d = 0x42040000
0042939e        self->primary_samples->__offset(0x1634).d = 0x3f800000
004293ad        set_matrix_identity(self->__offset(0x5c).d + 0x15a8)
004293be        *(self->__offset(0x5c).d + 0x15d8) = self->primary_samples->__offset(0x1638).d
004293c7        *(self->__offset(0x5c).d + 0x15dc) = 0x3efae148
004293d4        *(self->__offset(0x5c).d + 0x15e0) = 0x42040000
004293dd        int32_t i = 0xa8
004293e2        *(self->__offset(0x5c).d + 0x1634) = 0x3f800000
004293e8        int32_t texture_a_3 = 0
004293ea        texture_a = nullptr
004293f6        long double x87_r7_6 = float.t(texture_a)
004293fa        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00429405        texture_a = fconvert.s(x87_r7_6 * fconvert.t(0.196349546f))
00429423        *(&primary_samples_2->center_x + i) = fconvert.s((fconvert.t(primary_samples_2->__offset(0x1638).d) - fconvert.t(primary_samples_2->center_x)) * x87_r7_6 * fconvert.t(0.03125f) + fconvert.t(primary_samples_2->center_x))
00429439        *(&self->primary_samples->rotation_scalar_98 + i) = fconvert.s(fconvert.t(texture_a) * fconvert.t(0.5f))
00429443        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0042944d        *(&self->primary_samples->special_scalar + i) = 0
00429457        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
00429467        set_matrix_identity(self->primary_samples + i)
00429478        *(&self->primary_samples->transform.position + i) = 0
0042947f        *(&self->primary_samples->transform.position.z + i) = fconvert.s(float.t(texture_a_3 + 1))
00429486        *(&self->primary_samples->transform.position.y + i) = 0
0042948a        char* texture_a_1 = texture_a
00429494        texture_a = fconvert.s(cosine(texture_a_1))
00429499        long double st0_2 = sine(texture_a_1)
004294b1        float* edx_13 = &self->primary_samples->transform.basis_up + i
004294bc        *edx_13 = fconvert.s(st0_2)
004294c2        edx_13[1] = texture_a
004294c5        edx_13[2] = 0
004294c8        struct PathTemplateSample* primary_samples_5 = self->primary_samples
004294ea        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position.y + i)) - fconvert.t(*(primary_samples_5 + i - 0x74)))
004294f1        long double x87_r7_18 = fconvert.t(*(&primary_samples_5->transform.position.z + i)) - fconvert.t(*(primary_samples_5 + i - 0x70))
004294fb        *(&primary_samples_5->transform.basis_forward + i) = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position + i)) - fconvert.t(*(primary_samples_5 + i - 0x78)))
004294fd        *(&primary_samples_5->transform.basis_forward.y + i) = var_2c_1
00429508        *(&primary_samples_5->transform.basis_forward.z + i) = fconvert.s(x87_r7_18)
00429512        normalize_vector(&self->primary_samples->transform.basis_forward + i)
0042951a        struct Vec3* out = self->primary_samples + i
00429526        cross_vectors(out, out + 0x10, out + 0x20)
0042953a        __builtin_memcpy(self->__offset(0x5c).d + i, self->primary_samples + i, 0x40)
0042953c        struct PathTemplateSample* primary_samples_6 = self->primary_samples
00429542        texture_a_3 += 1
0042954a        long double x87_r7_22 = fconvert.t(*(&primary_samples_6->transform.basis_up + i)) * fconvert.t(0.49000001f)
00429558        texture_a = texture_a_3
00429562        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_6->transform.basis_up.y + i)) * fconvert.t(0.49000001f))
00429569        long double x87_r6_11 = fconvert.t(*(&primary_samples_6->transform.basis_up.z + i)) * fconvert.t(0.49000001f)
0042956f        float* eax_19 = self->__offset(0x5c).d + i + 0x30
00429573        i += 0xa8
00429585        *eax_19 = fconvert.s(x87_r7_22 + fconvert.t(*eax_19))
0042958e        eax_19[1] = fconvert.s(fconvert.t(var_20_1) + fconvert.t(eax_19[1]))
00429598        eax_19[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_11)) + fconvert.t(eax_19[2]))
0042959b        do while (i s< 0x15a8)
004295a4        int32_t i_1 = 0
004295a9        if (self->segment_count - 1 s> 0)
004295af        int32_t esi_3 = 0
004295b1        struct PathTemplateSample* primary_samples_7 = self->primary_samples
004295d5        float var_2c_2 = fconvert.s(fconvert.t(*(primary_samples_7 + esi_3 + 0xdc)) - fconvert.t(*(&primary_samples_7->transform.position.y + esi_3)))
004295dc        long double x87_r7_33 = fconvert.t(*(primary_samples_7 + esi_3 + 0xe0)) - fconvert.t(*(&primary_samples_7->transform.position.z + esi_3))
004295e3        *(&primary_samples_7->delta_dir_to_next + esi_3) = fconvert.s(fconvert.t(*(primary_samples_7 + esi_3 + 0xd8)) - fconvert.t(*(&primary_samples_7->transform.position + esi_3)))
004295e5        *(&primary_samples_7->delta_dir_to_next.y + esi_3) = var_2c_2
004295f0        *(&primary_samples_7->delta_dir_to_next.z + esi_3) = fconvert.s(x87_r7_33)
00429605        *(&self->primary_samples->delta_length + esi_3) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + esi_3))
0042960c        void* edx_20 = self->__offset(0x5c).d
00429630        float var_38_2 = fconvert.s(fconvert.t(*(edx_20 + esi_3 + 0xdc)) - fconvert.t(*(edx_20 + esi_3 + 0x34)))
00429637        long double x87_r7_40 = fconvert.t(*(edx_20 + esi_3 + 0xe0)) - fconvert.t(*(edx_20 + esi_3 + 0x38))
0042963e        *(edx_20 + esi_3 + 0x80) = fconvert.s(fconvert.t(*(edx_20 + esi_3 + 0xd8)) - fconvert.t(*(edx_20 + esi_3 + 0x30)))
00429640        *(edx_20 + esi_3 + 0x84) = var_38_2
0042964b        *(edx_20 + esi_3 + 0x88) = fconvert.s(x87_r7_40)
00429660        i_1 += 1
00429661        *(self->__offset(0x5c).d + esi_3 + 0x8c) = fconvert.s(normalize_vector(self->__offset(0x5c).d + esi_3 + 0x80))
0042966b        esi_3 += 0xa8
00429674        do while (i_1 s< self->segment_count - 1)
004296a4        int32_t* ecx_34 = &self->primary_samples[self->segment_count] - 0x28
004296b8        *ecx_34 = 0
004296c6        ecx_34[1] = 0
004296c9        ecx_34[2] = 0x3f800000
004296db        int32_t var_28_3 = 0x3f800000
004296e7        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
004296fd        int32_t* eax_37 = self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x28
00429705        *eax_37 = 0
0042970b        eax_37[1] = 0
00429710        eax_37[2] = 0x3f800000
00429725        *(self->__offset(0x5c).d + self->segment_count * 0xa8 - 0x1c) = 0x3f800000
00429738        request_object_vertices(self->_pad_00[0x24].d, (self->__offset(0x54).d + 1) * (self->segment_count + 1))
0042974a        request_object_facequads(self->_pad_00[0x24].d, (self->__offset(0x54).d * self->segment_count) << 1)
0042974f        void* eax_43 = self->_pad_00[0x24].d
00429752        int32_t edx_27 = *(eax_43 + 0x5c)
00429755        int32_t edi_3 = *(eax_43 + 0x38)
0042975f        int32_t i_2 = 0
00429761        int32_t var_40 = edi_3
00429767        if (self->segment_count s>= 0)
0042976d        int32_t ebx = 0
0042976f        int32_t ecx_46 = self->__offset(0x54).d
00429772        char* texture_a_2 = nullptr
00429776        texture_a = nullptr
0042977a        int32_t var_4c_1 = ecx_46
0042977e        if (ecx_46 s>= 0)
00429791        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042979a        long double x87_r7_43 = float.t(texture_a) - float.t(var_4c_1) * fconvert.t(0.5f)
0042979c        float* eax_50
0042979c        float ecx_50
0042979c        if (i_2 == self->segment_count)
004297f2        void* eax_51 = primary_samples_3 + ebx
00429803        edi_3 = var_40
00429848        float var_38_3 = fconvert.s(fconvert.t(*(eax_51 - 0x74)) + fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(*(eax_51 - 0xa4)))))
00429850        long double x87_r6_31 = fconvert.t(fconvert.s(fconvert.t(*(eax_51 - 0x70)) + fconvert.t(1f))) + x87_r7_43 * fconvert.t(*(eax_51 - 0xa0))
00429852        eax_50 = edi_3 + ((ecx_46 + 1) * i_2 + texture_a_2) * 0xc
00429859        *eax_50 = fconvert.s(fconvert.t(*(eax_51 - 0x78)) + fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(*(eax_51 - 0xa8)))))
00429863        eax_50[1] = var_38_3
00429866        ecx_50 = fconvert.s(x87_r6_31)
0042979e        float* eax_46 = primary_samples_3 + ebx
004297c6        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(eax_46[1]))) + fconvert.t(eax_46[0xd]))
004297d3        float var_28_4 = fconvert.s(x87_r7_43 * fconvert.t(eax_46[2]) + fconvert.t(eax_46[0xe]))
004297dc        eax_50 = edi_3 + ((ecx_46 + 1) * i_2 + texture_a_2) * 0xc
004297e3        *eax_50 = fconvert.s(fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(*eax_46))) + fconvert.t(eax_46[0xc]))
004297e9        eax_50[1] = var_2c_3
004297ec        ecx_50 = var_28_4
0042986c        eax_50[2] = ecx_50
0042986f        ecx_46 = self->__offset(0x54).d
00429872        texture_a_2 = &texture_a_2[1]
00429873        var_4c_1 = ecx_46
00429879        texture_a = texture_a_2
0042987d        do while (texture_a_2 s<= ecx_46)
00429886        i_2 += 1
00429887        ebx += 0xa8
0042988f        do while (i_2 s<= self->segment_count)
00429898        int32_t i_3 = 0
0042989c        if (self->segment_count s> 0)
004298a5        int32_t j = 0
004298a9        texture_a = nullptr
004298ad        if (self->__offset(0x54).d s> 0)
004298b5        int32_t eax_59 = i_3 & 0x80000007
004298ba        if (eax_59 s< 0)
004298c0        eax_59 = ((eax_59 - 1) | 0xfffffff8) + 1
004298d4        float var_54_1 = fconvert.s(float.t(eax_59) * fconvert.t(0.125f))
004298e2        float var_4c_2 = fconvert.s(float.t(eax_59 + 1) * fconvert.t(0.125f))
004298ed        int32_t ecx_54 = 0
004298f3        int32_t var_48_2 = 0
004298fd        texture_a = fconvert.s(float.t(texture_a) * fconvert.t(0.125f))
0042990b        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042991f        while (true)
0042991f        int32_t eax_66 = ecx_54 + ((self->__offset(0x54).d * i_3 + j) << 1)
00429922        if (ecx_54 != 0)
004299e8        int16_t* edi_6 = eax_66 * 0x30 + edx_27
004299eb        *edi_6 = 0
004299f0        ecx_54.w = self->__offset(0x54).w
004299f4        ecx_54.w += 1
004299fd        edi_6[1] = ecx_54.w * i_3.w + j.w + 1
00429a01        int32_t eax_74
00429a01        eax_74.w = self->__offset(0x54).w
00429a05        eax_74.w += 1
00429a0c        edi_6[2] = eax_74.w * i_3.w + j.w
00429a1e        edi_6[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
00429a36        edi_6[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
00429a3a        char* texture_path_1
00429a3a        char* texture_path_2
00429a3a        if (((j.b ^ i_3.b) & 1) != 0)
00429ad0        texture_path_1 = texture_path_2
00429a47        texture_path_1 = texture_path_2
00429a5a        *(edi_6 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00429a61        *(edi_6 + 0x10) = var_50_1
00429a64        *(edi_6 + 0x14) = var_54_1
00429a69        *(edi_6 + 0x18) = texture_a
00429a72        *(edi_6 + 0x1c) = var_54_1
00429a79        *(edi_6 + 0x20) = texture_a
00429a7c        *(edi_6 + 0x24) = var_4c_2
00429a81        *(edi_6 + 0x28) = var_50_1
00429a84        *(edi_6 + 0x2c) = var_4c_2
00429936        int16_t* edi_5 = eax_66 * 0x30 + edx_27
00429939        *edi_5 = 0
0042993e        eax_66.w = self->__offset(0x54).w
00429942        eax_66.w += 1
00429949        edi_5[1] = eax_66.w * i_3.w + j.w
0042994d        int32_t ecx_56
0042994d        ecx_56.w = self->__offset(0x54).w
00429951        ecx_56.w += 1
0042995d        edi_5[2] = ecx_56.w * i_3.w + j.w + 1
0042996e        edi_5[3] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w + 1
00429984        edi_5[4] = (self->__offset(0x54).w + 1) * (i_3.w + 1) + j.w
00429988        char* texture_path
00429988        char* arg4
00429988        if (((j.b ^ i_3.b) & 1) != 0)
004299d7        texture_path = arg4
0042998e        texture_path = arg4
004299a1        *(edi_5 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
004299a8        *(edi_5 + 0x10) = texture_a
004299ab        *(edi_5 + 0x14) = var_54_1
004299b0        *(edi_5 + 0x18) = var_50_1
004299b9        *(edi_5 + 0x1c) = var_54_1
004299c0        *(edi_5 + 0x20) = var_50_1
004299c3        *(edi_5 + 0x24) = var_4c_2
004299c8        *(edi_5 + 0x28) = texture_a
004299cb        *(edi_5 + 0x2c) = var_4c_2
00429a8c        bool cond:9_1 = var_48_2 + 1 s< 2
00429a8f        var_48_2 += 1
00429a93        if (not(cond:9_1))
00429a93        break
00429911        ecx_54 = var_48_2
00429a99        j += 1
00429aa2        texture_a = j
00429aa6        do while (j s< self->__offset(0x54).d)
00429aaf        i_3 += 1
00429ab2        do while (i_3 s< self->segment_count)
00429ac6        return finalize_path_template(self)
