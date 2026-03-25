/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_snake_path_template_pair @ 0x423580 */

0042358c        int32_t i_4 = 0
00423594        self->kind = PATH_TEMPLATE_KIND_SNAKE
0042359b        self->is_mirrored_x = 0
0042359f        self->side_exit_mode = 0
004235a2        self->width_cells = texture_a
004235a5        self->width_or_scale = 1f
004235a8        self->segment_count = 0x1b
004235af        self->segment_count_f = 27f
004235b6        allocate_path_template_samples(self)
004235bb        self->special_runtime_flag_9c = 0
004235c1        texture_a = nullptr
004235c5        int32_t i = 0
0042365c        while (i s< 0x3f0)
004235ca        *(&self->primary_samples->center_x + i) = 0
004235d4        *(&self->primary_samples->rotation_scalar_98 + i) = 0
004235de        *(&self->primary_samples->rotation_scalar_94 + i) = 0
004235e8        *(&self->primary_samples->special_scalar + i) = 0
004235f2        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
004235fe        set_matrix_identity(self->primary_samples + i)
00423606        long double x87_r7_1 = float.t(texture_a)
0042360a        *(&self->primary_samples->transform.position + i) = 0
00423615        *(&self->primary_samples->transform.position.y + i) = 0
0042361c        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
00423625        set_matrix_identity(self->secondary_samples + i)
0042362d        i += 0xa8
00423637        *(self->secondary_samples + i - 0x78) = 0
0042363e        *(self->secondary_samples + i - 0x74) = 0x3efae148
00423649        *(self->secondary_samples + i - 0x70) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
00423658        texture_a = &texture_a[1]
00423662        char* texture_a_1 = 0x18
00423667        int32_t edi = 0xfc0
0042366c        texture_a = 0x18
00423727        struct PathTemplateSample* secondary_samples
00423682        *(&self->primary_samples->center_x + edi) = fconvert.s(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0042368c        *(&self->primary_samples->rotation_scalar_98 + edi) = 0
00423696        *(&self->primary_samples->rotation_scalar_94 + edi) = 0
004236a0        *(&self->primary_samples->special_scalar + edi) = 0
004236aa        *(&self->primary_samples->lateral_scale + edi) = 0x3f800000
004236ba        set_matrix_identity(self->primary_samples + edi)
004236bf        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004236c2        long double x87_r7_6 = float.t(texture_a)
004236d4        *(&primary_samples_2->transform.position + edi) = *(&primary_samples_2->center_x + edi)
004236da        *(&self->primary_samples->transform.position.y + edi) = 0
004236e1        *(&self->primary_samples->transform.position.z + edi) = fconvert.s(x87_r7_6)
004236ea        set_matrix_identity(self->secondary_samples + edi)
00423700        *(&self->secondary_samples->transform.position + edi) = *(&self->primary_samples->center_x + edi)
00423704        secondary_samples = self->secondary_samples
00423707        *(&secondary_samples->transform.position.y + edi) = 0x3efae148
00423712        *(&self->secondary_samples->transform.position.z + edi) = fconvert.s(fconvert.t(fconvert.s(x87_r7_6)))
00423716        edi += 0xa8
0042371c        texture_a_1 = &texture_a_1[1]
0042371d        texture_a = texture_a_1
00423727        do while (&texture_a_1[0xffffffe8] s< 3)
0042372d        texture_a = nullptr
00423731        int32_t i_1 = 0x3f0
004239ca        while (i_1 s< 0xfc0)
0042373a        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042373d        struct PathTemplateSample* secondary_samples_3 = secondary_samples
00423744        float var_48_1 = fconvert.s(float.t(texture_a) * fconvert.t(0.34906587f))
0042376f        *(&primary_samples_4->center_x + i_1) = fconvert.s((fconvert.t(0.5f) - cosine(fconvert.s(fconvert.t(var_48_1) * fconvert.t(0.5f))) * fconvert.t(0.5f)) * fconvert.t(primary_samples_4->__offset(0x1050).d))
00423779        *(&self->primary_samples->rotation_scalar_98 + i_1) = 0
00423783        *(&self->primary_samples->rotation_scalar_94 + i_1) = 0
0042378d        *(&self->primary_samples->special_scalar + i_1) = 0
00423797        *(&self->primary_samples->lateral_scale + i_1) = 0x3f800000
004237a7        set_matrix_identity(self->primary_samples + i_1)
004237ac        struct PathTemplateSample* primary_samples_3 = self->primary_samples
004237be        *(&primary_samples_3->transform.position + i_1) = *(&primary_samples_3->center_x + i_1)
004237db        *(&self->primary_samples->transform.position.y + i_1) = fconvert.s(fneg(fconvert.t(1f) - cosine(var_48_1)))
004237e6        long double x87_r7_19 = float.t(&texture_a[6])
004237ee        *(&self->primary_samples->transform.position.z + i_1) = fconvert.s(x87_r7_19)
004237f7        set_matrix_identity(self->secondary_samples + i_1)
0042380a        *(&self->secondary_samples->transform.position + i_1) = *(&self->primary_samples->center_x + i_1)
0042382b        *(&self->secondary_samples->transform.position.y + i_1) = fconvert.s(fconvert.t(0.49000001f) - (fconvert.t(1f) - cosine(var_48_1)))
00423836        *(&self->secondary_samples->transform.position.z + i_1) = fconvert.s(fconvert.t(fconvert.s(x87_r7_19)))
0042383a        if (i_1 s<= 0x3f0)
004239a1        set_matrix_rotation_identity(self->primary_samples + i_1 - 0xa8)
004239a9        secondary_samples = self->secondary_samples + i_1 - 0xa8
004239b0        set_matrix_rotation_identity(secondary_samples)
00423857        int32_t* edx_15 = self->primary_samples + i_1 - 0xa8
0042386a        *edx_15 = 0x3f800000
00423870        edx_15[1] = 0
00423873        edx_15[2] = 0
00423876        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042389a        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position.y + i_1)) - fconvert.t(*(primary_samples_1 + i_1 - 0x74)))
004238a4        long double x87_r7_29 = fconvert.t(*(&primary_samples_1->transform.position.z + i_1)) - fconvert.t(*(primary_samples_1 + i_1 - 0x70))
004238ab        *(primary_samples_1 + i_1 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.position + i_1)) - fconvert.t(*(primary_samples_1 + i_1 - 0x78)))
004238ad        *(primary_samples_1 + i_1 - 0x84) = var_2c_1
004238b8        *(primary_samples_1 + i_1 - 0x80) = fconvert.s(x87_r7_29)
004238c5        normalize_vector(self->primary_samples + i_1 - 0x88)
004238cf        void* eax_19 = self->primary_samples + i_1
004238e6        cross_vectors(eax_19 - 0x98, eax_19 - 0x88, eax_19 - 0xa8)
00423902        int32_t* eax_20 = self->secondary_samples + i_1 - 0xa8
00423915        *eax_20 = 0x3f800000
0042391b        eax_20[1] = 0
0042391e        eax_20[2] = 0
00423921        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
00423945        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position.y + i_1)) - fconvert.t(*(secondary_samples_2 + i_1 - 0x74)))
0042394f        long double x87_r7_37 = fconvert.t(*(&secondary_samples_2->transform.position.z + i_1)) - fconvert.t(*(secondary_samples_2 + i_1 - 0x70))
00423956        *(secondary_samples_2 + i_1 - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position + i_1)) - fconvert.t(*(secondary_samples_2 + i_1 - 0x78)))
00423958        *(secondary_samples_2 + i_1 - 0x84) = var_14_1
00423963        *(secondary_samples_2 + i_1 - 0x80) = fconvert.s(x87_r7_37)
00423970        normalize_vector(self->secondary_samples + i_1 - 0x88)
00423978        void* eax_24 = self->secondary_samples + i_1
00423990        secondary_samples = cross_vectors(eax_24 - 0x98, eax_24 - 0x88, eax_24 - 0xa8)
004239b9        i_1 += 0xa8
004239c6        texture_a = &texture_a[1]
004239d3        int32_t i_2 = 0
004239d8        if (self->segment_count - 1 s> 0)
004239de        int32_t edi_1 = 0
004239e3        void* eax_27 = self->primary_samples + edi_1
00423a01        float var_14_2 = fconvert.s(fconvert.t(*(eax_27 + 0xdc)) - fconvert.t(*(eax_27 + 0x34)))
00423a08        long double x87_r7_45 = fconvert.t(*(eax_27 + 0xe0)) - fconvert.t(*(eax_27 + 0x38))
00423a0f        *(eax_27 + 0x80) = fconvert.s(fconvert.t(*(eax_27 + 0xd8)) - fconvert.t(*(eax_27 + 0x30)))
00423a11        *(eax_27 + 0x84) = var_14_2
00423a1c        *(eax_27 + 0x88) = fconvert.s(x87_r7_45)
00423a31        *(&self->primary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_1))
00423a38        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
00423a5c        float var_20_1 = fconvert.s(fconvert.t(*(secondary_samples_1 + edi_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_1)))
00423a63        long double x87_r7_52 = fconvert.t(*(secondary_samples_1 + edi_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_1))
00423a6a        *(&secondary_samples_1->delta_dir_to_next + edi_1) = fconvert.s(fconvert.t(*(secondary_samples_1 + edi_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_1)))
00423a6c        *(&secondary_samples_1->delta_dir_to_next.y + edi_1) = var_20_1
00423a77        *(&secondary_samples_1->delta_dir_to_next.z + edi_1) = fconvert.s(x87_r7_52)
00423a8c        i_2 += 1
00423a8d        *(&self->secondary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_1))
00423a97        edi_1 += 0xa8
00423aa0        do while (i_2 s< self->segment_count - 1)
00423ad0        int32_t* edx_33 = &self->primary_samples[self->segment_count] - 0x28
00423ae4        *edx_33 = 0
00423af2        edx_33[1] = 0
00423af5        edx_33[2] = 0x3f800000
00423b07        int32_t var_10_3 = 0x3f800000
00423b13        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00423b29        int32_t* ecx_50 = &self->secondary_samples[self->segment_count] - 0x28
00423b31        *ecx_50 = 0
00423b37        ecx_50[1] = 0
00423b3c        ecx_50[2] = 0x3f800000
00423b51        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
00423b64        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
00423b76        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
00423b7b        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
00423b7e        int32_t i_3 = 0
00423b80        struct Vec3* vertices = strip_mesh->vertices
00423b83        struct ObjectFaceQuad* facequads = strip_mesh->facequads
00423b89        struct Vec3* vertices_1 = vertices
00423b93        if (self->segment_count s>= 0)
00423b99        uint32_t width_cells = self->width_cells
00423b9c        char* texture_a_2 = nullptr
00423ba0        texture_a = nullptr
00423ba4        uint32_t width_cells_1 = width_cells
00423ba8        if (width_cells s>= 0)
00423bbb        struct PathTemplateSample* primary_samples = self->primary_samples
00423bc4        long double x87_r7_55 = float.t(texture_a) - float.t(width_cells_1) * fconvert.t(0.5f)
00423bc6        int32_t* eax_54
00423bc6        float ecx_61
00423bc6        if (i_3 == self->segment_count)
00423c1d        void* eax_55 = primary_samples + i_4
00423c2e        vertices = vertices_1
00423c73        float var_20_2 = fconvert.s(fconvert.t(*(eax_55 - 0x74)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_55 - 0xa4)))))
00423c7b        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_55 - 0x70)) + fconvert.t(1f))) + x87_r7_55 * fconvert.t(*(eax_55 - 0xa0))
00423c7d        eax_54 = &vertices[(width_cells + 1) * i_3 + texture_a_2]
00423c85        *eax_54 = fconvert.s(fconvert.t(*(eax_55 - 0x78)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_55 - 0xa8)))))
00423c8f        eax_54[1] = var_20_2
00423c92        ecx_61 = fconvert.s(x87_r6_20)
00423bc8        float* eax_50 = primary_samples + i_4
00423bf0        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(eax_50[1]))) + fconvert.t(eax_50[0xd]))
00423bfd        float var_10_4 = fconvert.s(x87_r7_55 * fconvert.t(eax_50[2]) + fconvert.t(eax_50[0xe]))
00423c06        eax_54 = &vertices[(width_cells + 1) * i_3 + texture_a_2]
00423c0e        *eax_54 = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*eax_50))) + fconvert.t(eax_50[0xc]))
00423c14        eax_54[1] = var_14_3
00423c17        ecx_61 = var_10_4
00423c98        eax_54[2] = ecx_61
00423c9b        width_cells = self->width_cells
00423c9e        texture_a_2 = &texture_a_2[1]
00423c9f        width_cells_1 = width_cells
00423ca5        texture_a = texture_a_2
00423ca9        do while (texture_a_2 s<= width_cells)
00423cb2        i_3 += 1
00423cb3        i_4 += 0xa8
00423cbb        do while (i_3 s<= self->segment_count)
00423cc1        i_4 = 0
00423cc8        if (self->segment_count s> 0)
00423cd1        int32_t j = 0
00423cd5        texture_a = nullptr
00423cd9        if (self->width_cells s> 0)
00423ce1        int32_t eax_63 = i_4 & 0x80000007
00423ce6        if (eax_63 s< 0)
00423cec        eax_63 = ((eax_63 - 1) | 0xfffffff8) + 1
00423d00        float var_54_1 = fconvert.s(float.t(eax_63) * fconvert.t(0.125f))
00423d0e        float var_4c_1 = fconvert.s(float.t(eax_63 + 1) * fconvert.t(0.125f))
00423d19        int32_t ecx_65 = 0
00423d1f        int32_t var_48_2 = 0
00423d29        texture_a = fconvert.s(float.t(texture_a) * fconvert.t(0.125f))
00423d37        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
00423d4b        while (true)
00423d4b        int32_t eax_70 = ecx_65 + ((self->width_cells * i_4 + j) << 1)
00423d4e        if (ecx_65 != 0)
00423e15        int16_t* ebp_3 = &facequads[eax_70]
00423e18        *ebp_3 = 0
00423e1e        ecx_65.w = self->width_cells.w
00423e22        ecx_65.w += 1
00423e2b        ebp_3[1] = ecx_65.w * i_4.w + j.w + 1
00423e2f        struct ObjectFaceQuad* eax_78
00423e2f        eax_78.w = self->width_cells.w
00423e33        eax_78.w += 1
00423e3a        ebp_3[2] = eax_78.w * i_4.w + j.w
00423e4c        ebp_3[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
00423e64        ebp_3[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
00423e68        char* texture_path_1
00423e68        char* texture_path_2
00423e68        if (((j.b ^ i_4.b) & 1) != 0)
00423efe        texture_path_1 = texture_path_2
00423e75        texture_path_1 = texture_path_2
00423e88        *(ebp_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00423e8f        *(ebp_3 + 0x10) = var_50_1
00423e92        *(ebp_3 + 0x14) = var_54_1
00423e97        *(ebp_3 + 0x18) = texture_a
00423ea0        *(ebp_3 + 0x1c) = var_54_1
00423ea7        *(ebp_3 + 0x20) = texture_a
00423eaa        *(ebp_3 + 0x24) = var_4c_1
00423eaf        *(ebp_3 + 0x28) = var_50_1
00423eb2        *(ebp_3 + 0x2c) = var_4c_1
00423d62        int16_t* ebp_2 = &facequads[eax_70]
00423d65        *ebp_2 = 0
00423d6b        eax_70.w = self->width_cells.w
00423d6f        eax_70.w += 1
00423d76        ebp_2[1] = eax_70.w * i_4.w + j.w
00423d7a        int32_t ecx_67
00423d7a        ecx_67.w = self->width_cells.w
00423d7e        ecx_67.w += 1
00423d8a        ebp_2[2] = ecx_67.w * i_4.w + j.w + 1
00423d9b        ebp_2[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
00423db1        ebp_2[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
00423db5        char* texture_path
00423db5        char* arg4
00423db5        if (((j.b ^ i_4.b) & 1) != 0)
00423e04        texture_path = arg4
00423dbb        texture_path = arg4
00423dce        *(ebp_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
00423dd5        *(ebp_2 + 0x10) = texture_a
00423dd8        *(ebp_2 + 0x14) = var_54_1
00423ddd        *(ebp_2 + 0x18) = var_50_1
00423de6        *(ebp_2 + 0x1c) = var_54_1
00423ded        *(ebp_2 + 0x20) = var_50_1
00423df0        *(ebp_2 + 0x24) = var_4c_1
00423df5        *(ebp_2 + 0x28) = texture_a
00423df8        *(ebp_2 + 0x2c) = var_4c_1
00423eba        bool cond:12_1 = var_48_2 + 1 s< 2
00423ebd        var_48_2 += 1
00423ec1        if (not(cond:12_1))
00423ec1        break
00423d3d        ecx_65 = var_48_2
00423ec7        j += 1
00423ed0        texture_a = j
00423ed4        do while (j s< self->width_cells)
00423edd        i_4 += 1
00423ee0        do while (i_4 s< self->segment_count)
00423ef4        return finalize_path_template(self)
