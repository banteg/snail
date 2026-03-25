/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_invert_path_template_pair @ 0x429250 */

00429264        self->kind = PATH_TEMPLATE_KIND_INVERT
0042926b        self->is_mirrored_x = 0
0042926f        self->side_exit_mode = 0
00429272        self->width_cells = texture_a
00429275        self->width_or_scale = 1f
00429278        self->segment_count = 0x22
0042927f        self->segment_count_f = 34f
00429286        allocate_path_template_samples(self)
0042928b        long double x87_r7 = float.t(self->width_cells)
0042928e        struct PathTemplateSample* primary_samples_4 = self->primary_samples
00429291        self->special_runtime_flag_9c = 1
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
004292fa        set_matrix_identity(self->secondary_samples)
0042930b        self->secondary_samples->transform.position.x = self->primary_samples->center_x
00429311        self->secondary_samples->transform.position.y = 0.49000001f
0042931b        self->secondary_samples->transform.position.z = 0f
00429321        self->secondary_samples->delta_length = 1f
00429339        self->primary_samples->__offset(0x1638).d = fconvert.s(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
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
004293ad        set_matrix_identity(&self->secondary_samples[0x21])
004293be        self->secondary_samples->__offset(0x15d8).d = self->primary_samples->__offset(0x1638).d
004293c7        self->secondary_samples->__offset(0x15dc).d = 0x3efae148
004293d4        self->secondary_samples->__offset(0x15e0).d = 0x42040000
004293dd        int32_t i = 0xa8
004293e2        self->secondary_samples->__offset(0x1634).d = 0x3f800000
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
0042953a        __builtin_memcpy(self->secondary_samples + i, self->primary_samples + i, 0x40)
0042953c        struct PathTemplateSample* primary_samples_6 = self->primary_samples
00429542        texture_a_3 += 1
0042954a        long double x87_r7_22 = fconvert.t(*(&primary_samples_6->transform.basis_up + i)) * fconvert.t(0.49000001f)
00429558        texture_a = texture_a_3
00429562        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_6->transform.basis_up.y + i)) * fconvert.t(0.49000001f))
00429569        long double x87_r6_11 = fconvert.t(*(&primary_samples_6->transform.basis_up.z + i)) * fconvert.t(0.49000001f)
0042956f        float* eax_19 = &self->secondary_samples->transform.position + i
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
0042960c        struct PathTemplateSample* secondary_samples = self->secondary_samples
00429630        float var_38_2 = fconvert.s(fconvert.t(*(secondary_samples + esi_3 + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + esi_3)))
00429637        long double x87_r7_40 = fconvert.t(*(secondary_samples + esi_3 + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + esi_3))
0042963e        *(&secondary_samples->delta_dir_to_next + esi_3) = fconvert.s(fconvert.t(*(secondary_samples + esi_3 + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + esi_3)))
00429640        *(&secondary_samples->delta_dir_to_next.y + esi_3) = var_38_2
0042964b        *(&secondary_samples->delta_dir_to_next.z + esi_3) = fconvert.s(x87_r7_40)
00429660        i_1 += 1
00429661        *(&self->secondary_samples->delta_length + esi_3) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + esi_3))
0042966b        esi_3 += 0xa8
00429674        do while (i_1 s< self->segment_count - 1)
004296a4        int32_t* ecx_34 = &self->primary_samples[self->segment_count] - 0x28
004296b8        *ecx_34 = 0
004296c6        ecx_34[1] = 0
004296c9        ecx_34[2] = 0x3f800000
004296db        int32_t var_28_3 = 0x3f800000
004296e7        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
004296fd        int32_t* eax_37 = &self->secondary_samples[self->segment_count] - 0x28
00429705        *eax_37 = 0
0042970b        eax_37[1] = 0
00429710        eax_37[2] = 0x3f800000
00429725        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
00429738        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0042974a        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0042974f        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
00429752        struct ObjectFaceQuad* facequads = strip_mesh->facequads
00429755        struct Vec3* vertices = strip_mesh->vertices
0042975f        int32_t i_2 = 0
00429761        struct Vec3* vertices_1 = vertices
00429767        if (self->segment_count s>= 0)
0042976d        int32_t ebx = 0
0042976f        uint32_t width_cells = self->width_cells
00429772        char* texture_a_2 = nullptr
00429776        texture_a = nullptr
0042977a        uint32_t width_cells_1 = width_cells
0042977e        if (width_cells s>= 0)
00429791        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042979a        long double x87_r7_43 = float.t(texture_a) - float.t(width_cells_1) * fconvert.t(0.5f)
0042979c        int32_t* eax_49
0042979c        float ecx_49
0042979c        if (i_2 == self->segment_count)
004297f2        void* eax_50 = primary_samples_3 + ebx
00429803        vertices = vertices_1
00429848        float var_38_3 = fconvert.s(fconvert.t(*(eax_50 - 0x74)) + fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(*(eax_50 - 0xa4)))))
00429850        long double x87_r6_31 = fconvert.t(fconvert.s(fconvert.t(*(eax_50 - 0x70)) + fconvert.t(1f))) + x87_r7_43 * fconvert.t(*(eax_50 - 0xa0))
00429852        eax_49 = &vertices[(width_cells + 1) * i_2 + texture_a_2]
00429859        *eax_49 = fconvert.s(fconvert.t(*(eax_50 - 0x78)) + fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(*(eax_50 - 0xa8)))))
00429863        eax_49[1] = var_38_3
00429866        ecx_49 = fconvert.s(x87_r6_31)
0042979e        float* eax_45 = primary_samples_3 + ebx
004297c6        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(eax_45[1]))) + fconvert.t(eax_45[0xd]))
004297d3        float var_28_4 = fconvert.s(x87_r7_43 * fconvert.t(eax_45[2]) + fconvert.t(eax_45[0xe]))
004297dc        eax_49 = &vertices[(width_cells + 1) * i_2 + texture_a_2]
004297e3        *eax_49 = fconvert.s(fconvert.t(fconvert.s(x87_r7_43 * fconvert.t(*eax_45))) + fconvert.t(eax_45[0xc]))
004297e9        eax_49[1] = var_2c_3
004297ec        ecx_49 = var_28_4
0042986c        eax_49[2] = ecx_49
0042986f        width_cells = self->width_cells
00429872        texture_a_2 = &texture_a_2[1]
00429873        width_cells_1 = width_cells
00429879        texture_a = texture_a_2
0042987d        do while (texture_a_2 s<= width_cells)
00429886        i_2 += 1
00429887        ebx += 0xa8
0042988f        do while (i_2 s<= self->segment_count)
00429898        int32_t i_3 = 0
0042989c        if (self->segment_count s> 0)
004298a5        int32_t j = 0
004298a9        texture_a = nullptr
004298ad        if (self->width_cells s> 0)
004298b5        int32_t eax_58 = i_3 & 0x80000007
004298ba        if (eax_58 s< 0)
004298c0        eax_58 = ((eax_58 - 1) | 0xfffffff8) + 1
004298d4        float var_54_1 = fconvert.s(float.t(eax_58) * fconvert.t(0.125f))
004298e2        float var_4c_1 = fconvert.s(float.t(eax_58 + 1) * fconvert.t(0.125f))
004298ed        int32_t ecx_53 = 0
004298f3        int32_t var_48_2 = 0
004298fd        texture_a = fconvert.s(float.t(texture_a) * fconvert.t(0.125f))
0042990b        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042991f        while (true)
0042991f        int32_t eax_65 = ecx_53 + ((self->width_cells * i_3 + j) << 1)
00429922        if (ecx_53 != 0)
004299e8        int16_t* edi_5 = eax_65 * 0x30 + facequads
004299eb        *edi_5 = 0
004299f0        ecx_53.w = self->width_cells.w
004299f4        ecx_53.w += 1
004299fd        edi_5[1] = ecx_53.w * i_3.w + j.w + 1
00429a01        struct ObjectFaceQuad* eax_73
00429a01        eax_73.w = self->width_cells.w
00429a05        eax_73.w += 1
00429a0c        edi_5[2] = eax_73.w * i_3.w + j.w
00429a1e        edi_5[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
00429a36        edi_5[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
00429a3a        char* texture_path_1
00429a3a        char* texture_path_2
00429a3a        if (((j.b ^ i_3.b) & 1) != 0)
00429ad0        texture_path_1 = texture_path_2
00429a47        texture_path_1 = texture_path_2
00429a5a        *(edi_5 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00429a61        *(edi_5 + 0x10) = var_50_1
00429a64        *(edi_5 + 0x14) = var_54_1
00429a69        *(edi_5 + 0x18) = texture_a
00429a72        *(edi_5 + 0x1c) = var_54_1
00429a79        *(edi_5 + 0x20) = texture_a
00429a7c        *(edi_5 + 0x24) = var_4c_1
00429a81        *(edi_5 + 0x28) = var_50_1
00429a84        *(edi_5 + 0x2c) = var_4c_1
00429936        int16_t* edi_4 = eax_65 * 0x30 + facequads
00429939        *edi_4 = 0
0042993e        eax_65.w = self->width_cells.w
00429942        eax_65.w += 1
00429949        edi_4[1] = eax_65.w * i_3.w + j.w
0042994d        int32_t ecx_55
0042994d        ecx_55.w = self->width_cells.w
00429951        ecx_55.w += 1
0042995d        edi_4[2] = ecx_55.w * i_3.w + j.w + 1
0042996e        edi_4[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
00429984        edi_4[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
00429988        char* texture_path
00429988        char* arg4
00429988        if (((j.b ^ i_3.b) & 1) != 0)
004299d7        texture_path = arg4
0042998e        texture_path = arg4
004299a1        *(edi_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
004299a8        *(edi_4 + 0x10) = texture_a
004299ab        *(edi_4 + 0x14) = var_54_1
004299b0        *(edi_4 + 0x18) = var_50_1
004299b9        *(edi_4 + 0x1c) = var_54_1
004299c0        *(edi_4 + 0x20) = var_50_1
004299c3        *(edi_4 + 0x24) = var_4c_1
004299c8        *(edi_4 + 0x28) = texture_a
004299cb        *(edi_4 + 0x2c) = var_4c_1
00429a8c        bool cond:9_1 = var_48_2 + 1 s< 2
00429a8f        var_48_2 += 1
00429a93        if (not(cond:9_1))
00429a93        break
00429911        ecx_53 = var_48_2
00429a99        j += 1
00429aa2        texture_a = j
00429aa6        do while (j s< self->width_cells)
00429aaf        i_3 += 1
00429ab2        do while (i_3 s< self->segment_count)
00429ac6        return finalize_path_template(self)
