/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_dip_path_template_pair @ 0x425050 */

0042505c        int32_t i_4 = 0
00425064        self->kind = 0x20
0042506b        self->is_mirrored_x = 0
0042506f        self->side_exit_mode = 0
00425072        self->width_cells = texture_a
00425075        self->width_or_scale = 1f
00425078        self->segment_count = 0x46
0042507f        self->segment_count_f = 70f
00425086        allocate_path_nodes(self)
0042508b        self->special_runtime_flag_9c = 0
00425091        texture_a = nullptr
00425095        int32_t i = 0
0042513d        while (i s< 0x2a0)
0042509a        *(&self->primary_samples->center_x + i) = 0
004250a4        *(&self->primary_samples->rotation_scalar_98 + i) = 0
004250ae        *(&self->primary_samples->rotation_scalar_94 + i) = 0
004250b8        *(&self->primary_samples->special_scalar + i) = 0
004250c2        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
004250ce        set_matrix_identity(self->primary_samples + i)
004250d6        void* eax_3 = self->primary_samples + i
004250d8        long double x87_r7_1 = float.t(texture_a)
004250e2        *(eax_3 + 0x30) = *(eax_3 + 0x90)
004250ec        *(&self->primary_samples->transform.position.y + i) = 0
004250f5        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
004250fc        set_matrix_identity(i + self->secondary_samples)
00425112        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
00425119        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
00425124        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
0042512c        i += 0xa8
00425139        texture_a = &texture_a[1]
00425143        char* texture_a_1 = 0x42
00425148        int32_t edi = 0x2b50
0042514d        texture_a = 0x42
00425154        *(&self->primary_samples->center_x + edi) = 0
0042515e        *(&self->primary_samples->rotation_scalar_98 + edi) = 0
00425168        *(&self->primary_samples->rotation_scalar_94 + edi) = 0
00425172        *(&self->primary_samples->special_scalar + edi) = 0
0042517c        *(&self->primary_samples->lateral_scale + edi) = 0x3f800000
0042518c        set_matrix_identity(self->primary_samples + edi)
00425191        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00425194        long double x87_r7_3 = float.t(texture_a)
004251a6        *(&primary_samples_3->transform.position + edi) = *(&primary_samples_3->center_x + edi)
004251ae        *(&self->primary_samples->transform.position.y + edi) = 0
004251b5        *(&self->primary_samples->transform.position.z + edi) = fconvert.s(x87_r7_3)
004251bc        set_matrix_identity(edi + self->secondary_samples)
004251d2        *(&self->secondary_samples->transform.position + edi) = *(&self->primary_samples->center_x + edi)
004251d9        *(&self->secondary_samples->transform.position.y + edi) = 0x3efae148
004251e4        *(&self->secondary_samples->transform.position.z + edi) = fconvert.s(fconvert.t(fconvert.s(x87_r7_3)))
004251e8        edi += 0xa8
004251ee        texture_a_1 = &texture_a_1[1]
004251ef        texture_a = texture_a_1
004251f9        do while (&texture_a_1[0xffffffbe] s< 4)
004251ff        char* texture_a_2 = nullptr
00425201        void* i_1 = 0x2a0
00425206        texture_a = nullptr
0042520e        long double x87_r7_6 = float.t(texture_a) * fconvert.t(0.0161290318f)
0042521c        float var_4c_1 = fconvert.s(x87_r7_6 * fconvert.t(12.566371f))
00425220        long double x87_r7_7 = x87_r7_6 - fconvert.t(0.5f)
00425226        long double temp1_1 = fconvert.t(0f)
00425226        x87_r7_7 - temp1_1
0042522c        void* eax_11
0042522c        eax_11.w = (x87_r7_7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp1_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp1_1 ? 1 : 0) << 0xe | 0x3800
00425231        float var_48_1
00425231        if ((eax_11:1.b & 1) == 0)
0042523d        var_48_1 = fconvert.s(x87_r7_7)
00425237        var_48_1 = fconvert.s(fneg(x87_r7_7))
00425241        long double temp2_1 = fconvert.t(0f)
00425241        x87_r7_7 - temp2_1
00425247        eax_11.w = (x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe | 0x3800
0042524c        if ((eax_11:1.b & 1) != 0)
0042524e        x87_r7_7 = fneg(x87_r7_7)
00425282        *(&self->primary_samples->center_x + i_1) = fconvert.s(sine(var_4c_1) * (fconvert.t(1f) - fconvert.t(fconvert.s(x87_r7_7))) * (fconvert.t(1f) - fconvert.t(var_48_1)) * fconvert.t(4.44444466f))
0042528c        *(&self->primary_samples->rotation_scalar_98 + i_1) = 0
00425296        *(&self->primary_samples->rotation_scalar_94 + i_1) = 0
004252a2        *(&self->primary_samples->special_scalar + i_1) = 0
004252ac        *(&self->primary_samples->lateral_scale + i_1) = 0x3f800000
004252bc        set_matrix_identity(i_1 + self->primary_samples)
004252c1        struct PathTemplateSample* primary_samples_1 = self->primary_samples
004252d8        struct PathTemplateSample* primary_samples_4 = primary_samples_1
004252d9        *(&primary_samples_1->transform.position + i_1) = *(&primary_samples_1->center_x + i_1)
004252f6        *(&self->primary_samples->transform.position.y + i_1) = fconvert.s(fconvert.t(1f) - cosine(fconvert.s(fconvert.t(var_4c_1) * fconvert.t(0.5f))))
004252fa        long double x87_r7_16 = float.t(&texture_a_2[4])
00425308        *(&self->primary_samples->transform.position.z + i_1) = fconvert.s(x87_r7_16)
0042530f        set_matrix_identity(i_1 + self->secondary_samples)
00425327        *(&self->secondary_samples->transform.position + i_1) = *(&self->primary_samples->center_x + i_1)
0042533b        *(&self->secondary_samples->transform.position.y + i_1) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + i_1)) + fconvert.t(0.49000001f))
00425346        *(&self->secondary_samples->transform.position.z + i_1) = fconvert.s(fconvert.t(fconvert.s(x87_r7_16)))
0042534a        if (i_1 s<= 0x2a0)
004254eb        set_matrix_rotation_identity(i_1 + self->primary_samples - 0xa8)
004254fa        set_matrix_rotation_identity(i_1 + self->secondary_samples - 0xa8)
00425367        int32_t* ecx_27 = i_1 + self->primary_samples - 0x98
0042537a        *ecx_27 = 0
00425380        ecx_27[1] = 0x3f800000
00425383        ecx_27[2] = 0
00425389        void* eax_20 = self->primary_samples + i_1
004253a7        float var_2c_1 = fconvert.s(fconvert.t(*(eax_20 + 0x34)) - fconvert.t(*(eax_20 - 0x74)))
004253b1        long double x87_r7_25 = fconvert.t(*(eax_20 + 0x38)) - fconvert.t(*(eax_20 - 0x70))
004253b8        *(eax_20 - 0x88) = fconvert.s(fconvert.t(*(eax_20 + 0x30)) - fconvert.t(*(eax_20 - 0x78)))
004253ba        *(eax_20 - 0x84) = var_2c_1
004253c5        *(eax_20 - 0x80) = fconvert.s(x87_r7_25)
004253d2        normalize_vector(i_1 + self->primary_samples - 0x88)
004253da        void* eax_23 = self->primary_samples + i_1
004253fa        int32_t var_68_4 = cross_vectors(eax_23 - 0xa8, eax_23 - 0x98, eax_23 - 0x88)
004253fb        void* eax_25 = self->primary_samples + i_1
0042540f        rotate_matrix_world_z(eax_25 - 0xa8, fconvert.s(fconvert.t(*(eax_25 - 0x18)) * fconvert.t(0.261799395f)))
0042542b        int32_t* edx_22 = i_1 + self->secondary_samples - 0x98
0042543e        *edx_22 = 0
00425444        edx_22[1] = 0x3f800000
00425447        edx_22[2] = 0
0042544a        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042546e        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + i_1)) - fconvert.t(*(i_1 + secondary_samples - 0x74)))
00425478        long double x87_r7_35 = fconvert.t(*(&secondary_samples->transform.position.z + i_1)) - fconvert.t(*(i_1 + secondary_samples - 0x70))
0042547f        *(i_1 + secondary_samples - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + i_1)) - fconvert.t(*(i_1 + secondary_samples - 0x78)))
00425481        *(i_1 + secondary_samples - 0x84) = var_14_1
0042548c        *(i_1 + secondary_samples - 0x80) = fconvert.s(x87_r7_35)
00425499        normalize_vector(i_1 + self->secondary_samples - 0x88)
004254a3        void* eax_29 = i_1 + self->secondary_samples
004254c5        int32_t var_68_7 = cross_vectors(eax_29 - 0xa8, eax_29 - 0x98, eax_29 - 0x88)
004254da        rotate_matrix_world_z(i_1 + self->secondary_samples - 0xa8, fconvert.s(fconvert.t(*(i_1 + self->primary_samples - 0x18)) * fconvert.t(0.261799395f)))
004254ff        i_1 += 0xa8
00425505        texture_a_2 = &texture_a_2[1]
0042550c        texture_a = texture_a_2
00425510        do while (i_1 s< 0x2b50)
00425519        int32_t i_2 = 0
0042551e        if (self->segment_count - 1 s> 0)
00425524        void* edi_1 = nullptr
00425526        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042554a        float var_14_2 = fconvert.s(fconvert.t(*(edi_1 + primary_samples_2 + 0xdc)) - fconvert.t(*(&primary_samples_2->transform.position.y + edi_1)))
00425551        long double x87_r7_45 = fconvert.t(*(edi_1 + primary_samples_2 + 0xe0)) - fconvert.t(*(&primary_samples_2->transform.position.z + edi_1))
00425558        *(&primary_samples_2->delta_dir_to_next + edi_1) = fconvert.s(fconvert.t(*(edi_1 + primary_samples_2 + 0xd8)) - fconvert.t(*(&primary_samples_2->transform.position + edi_1)))
0042555a        *(&primary_samples_2->delta_dir_to_next.y + edi_1) = var_14_2
00425565        *(&primary_samples_2->delta_dir_to_next.z + edi_1) = fconvert.s(x87_r7_45)
0042557a        *(&self->primary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_1))
00425581        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
004255a5        float var_20_1 = fconvert.s(fconvert.t(*(edi_1 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_1)))
004255ac        long double x87_r7_52 = fconvert.t(*(edi_1 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_1))
004255b3        *(&secondary_samples_1->delta_dir_to_next + edi_1) = fconvert.s(fconvert.t(*(edi_1 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_1)))
004255b5        *(&secondary_samples_1->delta_dir_to_next.y + edi_1) = var_20_1
004255c0        *(&secondary_samples_1->delta_dir_to_next.z + edi_1) = fconvert.s(x87_r7_52)
004255d5        i_2 += 1
004255d6        *(&self->secondary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_1))
004255e0        edi_1 += 0xa8
004255e9        do while (i_2 s< self->segment_count - 1)
00425619        int32_t* ecx_55 = &self->primary_samples[self->segment_count] - 0x28
0042562d        *ecx_55 = 0
0042563b        ecx_55[1] = 0
0042563e        ecx_55[2] = 0x3f800000
00425650        int32_t var_10_3 = 0x3f800000
0042565c        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00425672        int32_t* eax_48 = &self->secondary_samples[self->segment_count] - 0x28
0042567a        *eax_48 = 0
00425680        eax_48[1] = 0
00425685        eax_48[2] = 0x3f800000
0042569a        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
004256ad        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
004256bf        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
004256c4        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
004256c7        struct ObjectFaceQuad* facequads = strip_mesh->facequads
004256ca        struct Vec3* vertices = strip_mesh->vertices
004256d4        int32_t i_3 = 0
004256d8        struct Vec3* vertices_1 = vertices
004256dc        if (self->segment_count s>= 0)
004256e2        uint32_t width_cells = self->width_cells
004256e5        char* texture_a_3 = nullptr
004256e9        texture_a = nullptr
004256ed        uint32_t width_cells_1 = width_cells
004256f1        if (width_cells s>= 0)
00425704        struct PathTemplateSample* primary_samples = self->primary_samples
0042570d        long double x87_r7_55 = float.t(texture_a) - float.t(width_cells_1) * fconvert.t(0.5f)
0042570f        int32_t* eax_60
0042570f        float ecx_70
0042570f        if (i_3 == self->segment_count)
00425766        void* eax_61 = primary_samples + i_4
00425777        vertices = vertices_1
004257bc        float var_20_2 = fconvert.s(fconvert.t(*(eax_61 - 0x74)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_61 - 0xa4)))))
004257c4        long double x87_r6_28 = fconvert.t(fconvert.s(fconvert.t(*(eax_61 - 0x70)) + fconvert.t(1f))) + x87_r7_55 * fconvert.t(*(eax_61 - 0xa0))
004257c6        eax_60 = &vertices[(width_cells + 1) * i_3 + texture_a_3]
004257ce        *eax_60 = fconvert.s(fconvert.t(*(eax_61 - 0x78)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_61 - 0xa8)))))
004257d8        eax_60[1] = var_20_2
004257db        ecx_70 = fconvert.s(x87_r6_28)
00425711        float* eax_56 = primary_samples + i_4
00425739        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(eax_56[1]))) + fconvert.t(eax_56[0xd]))
00425746        float var_10_4 = fconvert.s(x87_r7_55 * fconvert.t(eax_56[2]) + fconvert.t(eax_56[0xe]))
0042574f        eax_60 = &vertices[(width_cells + 1) * i_3 + texture_a_3]
00425757        *eax_60 = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*eax_56))) + fconvert.t(eax_56[0xc]))
0042575d        eax_60[1] = var_14_3
00425760        ecx_70 = var_10_4
004257e1        eax_60[2] = ecx_70
004257e4        width_cells = self->width_cells
004257e7        texture_a_3 = &texture_a_3[1]
004257e8        width_cells_1 = width_cells
004257ee        texture_a = texture_a_3
004257f2        do while (texture_a_3 s<= width_cells)
004257fb        i_3 += 1
004257fc        i_4 += 0xa8
00425804        do while (i_3 s<= self->segment_count)
0042580a        i_4 = 0
00425811        if (self->segment_count s> 0)
0042581a        int32_t j = 0
0042581e        texture_a = nullptr
00425822        if (self->width_cells s> 0)
0042582a        int32_t eax_69 = i_4 & 0x80000007
0042582f        if (eax_69 s< 0)
00425835        eax_69 = ((eax_69 - 1) | 0xfffffff8) + 1
00425849        float var_54_1 = fconvert.s(float.t(eax_69) * fconvert.t(0.125f))
00425857        float var_4c_2 = fconvert.s(float.t(eax_69 + 1) * fconvert.t(0.125f))
00425862        int32_t ecx_74 = 0
00425868        int32_t var_48_2 = 0
00425872        texture_a = fconvert.s(float.t(texture_a) * fconvert.t(0.125f))
00425880        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
00425892        while (true)
004258a1        int16_t* edi_2 = &facequads[ecx_74 + ((self->width_cells * i_4 + j) << 1)]
004258a4        *edi_2 = 0
004258a9        int32_t edx_38
004258a9        if (ecx_74 != 0)
0042594f        edx_38.w = self->width_cells.w
00425955        edx_38.w += 1
00425960        edi_2[1] = edx_38.w * i_4.w + j.w + 1
00425964        ecx_74.w = self->width_cells.w
00425968        ecx_74.w += 1
00425972        edi_2[2] = ecx_74.w * i_4.w + j.w
00425981        edi_2[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
00425998        edi_2[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
0042599c        char* texture_path_1
0042599c        char* texture_path_2
0042599c        if (((j.b ^ i_4.b) & 1) != 0)
00425a32        texture_path_1 = texture_path_2
004259a9        texture_path_1 = texture_path_2
004259bc        *(edi_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
004259c3        *(edi_2 + 0x10) = var_50_1
004259c6        *(edi_2 + 0x14) = var_54_1
004259cb        *(edi_2 + 0x18) = texture_a
004259d4        *(edi_2 + 0x1c) = var_54_1
004259db        *(edi_2 + 0x20) = texture_a
004259de        *(edi_2 + 0x24) = var_4c_2
004259e3        *(edi_2 + 0x28) = var_50_1
004259e6        *(edi_2 + 0x2c) = var_4c_2
004258af        ecx_74.w = self->width_cells.w
004258b5        ecx_74.w += 1
004258be        edi_2[1] = ecx_74.w * i_4.w + j.w
004258c2        edx_38.w = self->width_cells.w
004258c6        edx_38.w += 1
004258cf        edi_2[2] = edx_38.w * i_4.w + j.w + 1
004258e3        edi_2[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
004258f9        edi_2[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
004258fd        char* texture_path
004258fd        char* arg4
004258fd        if (((j.b ^ i_4.b) & 1) != 0)
0042594c        texture_path = arg4
00425903        texture_path = arg4
00425916        *(edi_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0042591d        *(edi_2 + 0x10) = texture_a
00425920        *(edi_2 + 0x14) = var_54_1
00425925        *(edi_2 + 0x18) = var_50_1
0042592e        *(edi_2 + 0x1c) = var_54_1
00425935        *(edi_2 + 0x20) = var_50_1
00425938        *(edi_2 + 0x24) = var_4c_2
0042593d        *(edi_2 + 0x28) = texture_a
00425940        *(edi_2 + 0x2c) = var_4c_2
004259ee        bool cond:12_1 = var_48_2 + 1 s< 2
004259f1        var_48_2 += 1
004259f5        if (not(cond:12_1))
004259f5        break
00425886        ecx_74 = var_48_2
004259fb        j += 1
00425a04        texture_a = j
00425a08        do while (j s< self->width_cells)
00425a11        i_4 += 1
00425a14        do while (i_4 s< self->segment_count)
00425a28        return finalize_path_template_record(self)
