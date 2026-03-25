/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_detour_path_template_pair @ 0x42e720 */

0042e72d        int32_t i_3 = 0
0042e734        self->kind = 0xf
0042e73b        self->is_mirrored_x = 0
0042e73f        self->side_exit_mode = 0
0042e742        self->width_cells = arg2
0042e745        self->width_or_scale = 1f
0042e748        self->segment_count = 0x16
0042e74f        self->segment_count_f = 22f
0042e756        allocate_path_nodes(self)
0042e75b        long double x87_r7 = float.t(self->width_cells)
0042e75e        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042e761        self->special_runtime_flag_9c = 0
0042e773        primary_samples_3->center_x = fconvert.s(x87_r7 * fconvert.t(0.5f) - fconvert.t(4f))
0042e77c        self->primary_samples->rotation_scalar_98 = 0f
0042e785        self->primary_samples->rotation_scalar_94 = 0f
0042e78e        self->primary_samples->special_scalar = 0f
0042e797        self->primary_samples->lateral_scale = 1f
0042e7a0        set_matrix_identity(self->primary_samples)
0042e7a5        struct PathTemplateSample* primary_samples = self->primary_samples
0042e7ae        primary_samples->transform.position.x = primary_samples->center_x
0042e7b4        self->primary_samples->transform.position.y = 0f
0042e7ba        self->primary_samples->transform.position.z = 0f
0042e7c0        set_matrix_identity(self->secondary_samples)
0042e7d6        self->secondary_samples->transform.position.x = self->primary_samples->center_x
0042e7dc        self->secondary_samples->transform.position.y = 0.49000001f
0042e7e2        self->secondary_samples->transform.position.z = 0f
0042e7f7        self->primary_samples->__offset(0xe58).d = fconvert.s(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0042e800        self->primary_samples->__offset(0xe60).d = 0
0042e809        self->primary_samples->__offset(0xe5c).d = 0
0042e812        self->primary_samples->__offset(0xe68).d = 0
0042e81b        self->primary_samples->__offset(0xe64).d = 0x3f800000
0042e82a        set_matrix_identity(&self->primary_samples[0x15])
0042e82f        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042e83d        primary_samples_1->__offset(0xdf8).d = primary_samples_1->__offset(0xe58).d
0042e846        self->primary_samples->__offset(0xdfc).d = 0
0042e84f        self->primary_samples->__offset(0xe00).d = 0x41a80000
0042e85e        set_matrix_identity(&self->secondary_samples[0x15])
0042e869        struct PathTemplateTransform* transform = self->primary_samples->__offset(0xe58).d
0042e86f        self->secondary_samples->__offset(0xdf8).d = transform
0042e878        arg2 = 0
0042e87c        self->secondary_samples->__offset(0xdfc).d = 0x3efae148
0042e885        self->secondary_samples->__offset(0xe00).d = 0x41a80000
0042e88b        void* i = 0xa8
0042eb5f        while (i s< 0xdc8)
0042e890        long double x87_r7_6 = float.t(arg2)
0042e894        struct PathTemplateSample* primary_samples_7 = self->primary_samples
0042e897        struct PathTemplateTransform* transform_1 = transform
0042e8a0        float var_48_1 = fconvert.s(x87_r7_6 * fconvert.t(0.314159274f))
0042e8bb        *(&primary_samples_7->center_x + i) = fconvert.s(cosine(fconvert.s(x87_r7_6 * fconvert.t(0.471238911f))) * fconvert.t(primary_samples_7->center_x))
0042e8c5        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0042e8cf        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0042e8d9        *(&self->primary_samples->special_scalar + i) = 0
0042e8e3        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042e8f3        set_matrix_identity(self->primary_samples + i)
0042e8f8        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042e905        *(&primary_samples_5->transform.position + i) = *(&primary_samples_5->center_x + i)
0042e90f        int32_t eax_12 = arg2 + 1
0042e914        long double x87_r7_10 = float.t(eax_12)
0042e918        *(&self->primary_samples->transform.position.y + i) = 0
0042e923        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_10)
0042e92e        set_matrix_identity(i + self->secondary_samples)
0042e946        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0042e95a        *(&self->secondary_samples->transform.position.y + i) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + i)) + fconvert.t(0.49000001f))
0042e965        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_10)))
0042e969        if (i s<= 0xa8)
0042eb37        set_matrix_rotation_identity(self->primary_samples + i - 0xa8)
0042eb3f        transform = i + self->secondary_samples - 0xa8
0042eb46        set_matrix_rotation_identity(transform)
0042e986        int32_t* eax_15 = self->primary_samples + i - 0x98
0042e999        *eax_15 = 0
0042e99f        eax_15[1] = 0x3f800000
0042e9a2        eax_15[2] = 0
0042e9a5        struct PathTemplateSample* primary_samples_6 = self->primary_samples
0042e9c9        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_6->transform.position.y + i)) - fconvert.t(*(primary_samples_6 + i - 0x74)))
0042e9d3        long double x87_r7_19 = fconvert.t(*(&primary_samples_6->transform.position.z + i)) - fconvert.t(*(primary_samples_6 + i - 0x70))
0042e9da        *(primary_samples_6 + i - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_6->transform.position + i)) - fconvert.t(*(primary_samples_6 + i - 0x78)))
0042e9dc        *(primary_samples_6 + i - 0x84) = var_2c_1
0042e9e7        *(primary_samples_6 + i - 0x80) = fconvert.s(x87_r7_19)
0042e9f4        normalize_vector(self->primary_samples + i - 0x88)
0042e9fc        void* eax_19 = self->primary_samples + i
0042ea14        cross_vectors(eax_19 - 0xa8, eax_19 - 0x98, eax_19 - 0x88)
0042ea21        void* ebp_1 = self->primary_samples + i
0042ea47        rotate_matrix_world_z(ebp_1 - 0xa8, fconvert.s((fconvert.t(1f) - cosine(var_48_1)) * fconvert.t(0.5f) * fconvert.t(*(ebp_1 - 0x18)) * fconvert.t(0.392699093f)))
0042ea63        int32_t* eax_21 = i + self->secondary_samples - 0x98
0042ea76        *eax_21 = 0
0042ea7c        eax_21[1] = 0x3f800000
0042ea7f        eax_21[2] = 0
0042ea82        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042eaa6        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + i)) - fconvert.t(*(i + secondary_samples - 0x74)))
0042eab0        long double x87_r7_32 = fconvert.t(*(&secondary_samples->transform.position.z + i)) - fconvert.t(*(i + secondary_samples - 0x70))
0042eab7        *(i + secondary_samples - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + i)) - fconvert.t(*(i + secondary_samples - 0x78)))
0042eac1        *(i + secondary_samples - 0x84) = var_14_1
0042eac4        *(i + secondary_samples - 0x80) = fconvert.s(x87_r7_32)
0042ead1        normalize_vector(i + self->secondary_samples - 0x88)
0042ead9        void* eax_25 = self->secondary_samples + i
0042eaf1        cross_vectors(eax_25 - 0xa8, eax_25 - 0x98, eax_25 - 0x88)
0042eb00        long double x87_r7_36 = fconvert.t(1f) - cosine(var_48_1)
0042eb26        transform = rotate_matrix_world_z(i + self->secondary_samples - 0xa8, fconvert.s(x87_r7_36 * fconvert.t(0.5f) * fconvert.t(*(self->primary_samples + i - 0x18)) * fconvert.t(0.392699093f)))
0042eb4f        i += 0xa8
0042eb5b        arg2 = eax_12
0042eb68        int32_t i_1 = 0
0042eb6d        if (self->segment_count - 1 s> 0)
0042eb73        void* edi = nullptr
0042eb75        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042eb99        float var_14_2 = fconvert.s(fconvert.t(*(edi + primary_samples_4 + 0xdc)) - fconvert.t(*(&primary_samples_4->transform.position.y + edi)))
0042eba0        long double x87_r7_45 = fconvert.t(*(edi + primary_samples_4 + 0xe0)) - fconvert.t(*(&primary_samples_4->transform.position.z + edi))
0042eba7        *(&primary_samples_4->delta_dir_to_next + edi) = fconvert.s(fconvert.t(*(edi + primary_samples_4 + 0xd8)) - fconvert.t(*(&primary_samples_4->transform.position + edi)))
0042eba9        *(&primary_samples_4->delta_dir_to_next.y + edi) = var_14_2
0042ebb4        *(&primary_samples_4->delta_dir_to_next.z + edi) = fconvert.s(x87_r7_45)
0042ebc9        *(&self->primary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi))
0042ebd0        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042ebf4        float var_20_1 = fconvert.s(fconvert.t(*(edi + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi)))
0042ebfb        long double x87_r7_52 = fconvert.t(*(edi + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi))
0042ec02        *(&secondary_samples_1->delta_dir_to_next + edi) = fconvert.s(fconvert.t(*(edi + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi)))
0042ec04        *(&secondary_samples_1->delta_dir_to_next.y + edi) = var_20_1
0042ec0f        *(&secondary_samples_1->delta_dir_to_next.z + edi) = fconvert.s(x87_r7_52)
0042ec24        i_1 += 1
0042ec25        *(&self->secondary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi))
0042ec2f        edi += 0xa8
0042ec38        do while (i_1 s< self->segment_count - 1)
0042ec68        int32_t* ecx_48 = &self->primary_samples[self->segment_count] - 0x28
0042ec7c        *ecx_48 = 0
0042ec8a        ecx_48[1] = 0
0042ec8d        ecx_48[2] = 0x3f800000
0042ec9f        int32_t var_10_3 = 0x3f800000
0042ecab        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ecc1        int32_t* eax_45 = &self->secondary_samples[self->segment_count] - 0x28
0042ecc9        *eax_45 = 0
0042eccf        eax_45[1] = 0
0042ecd4        eax_45[2] = 0x3f800000
0042ece9        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ecfc        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0042ed0e        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0042ed13        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0042ed16        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0042ed19        struct Vec3* vertices = strip_mesh->vertices
0042ed23        int32_t i_2 = 0
0042ed27        struct Vec3* vertices_1 = vertices
0042ed2b        if (self->segment_count s>= 0)
0042ed31        uint32_t width_cells = self->width_cells
0042ed34        int32_t edi_1 = 0
0042ed38        arg2 = 0
0042ed3c        uint32_t width_cells_1 = width_cells
0042ed40        if (width_cells s>= 0)
0042ed53        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042ed5c        long double x87_r7_55 = float.t(arg2) - float.t(width_cells_1) * fconvert.t(0.5f)
0042ed5e        float* eax_57
0042ed5e        float ecx_63
0042ed5e        if (i_2 == self->segment_count)
0042edb5        void* eax_58 = primary_samples_2 + i_3
0042edc6        vertices = vertices_1
0042ee0b        float var_20_2 = fconvert.s(fconvert.t(*(eax_58 - 0x74)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_58 - 0xa4)))))
0042ee13        long double x87_r6_22 = fconvert.t(fconvert.s(fconvert.t(*(eax_58 - 0x70)) + fconvert.t(1f))) + x87_r7_55 * fconvert.t(*(eax_58 - 0xa0))
0042ee15        eax_57 = &vertices[(width_cells + 1) * i_2 + edi_1]
0042ee1d        *eax_57 = fconvert.s(fconvert.t(*(eax_58 - 0x78)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_58 - 0xa8)))))
0042ee27        eax_57[1] = var_20_2
0042ee2a        ecx_63 = fconvert.s(x87_r6_22)
0042ed60        float* eax_53 = primary_samples_2 + i_3
0042ed88        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(eax_53[1]))) + fconvert.t(eax_53[0xd]))
0042ed95        float var_10_4 = fconvert.s(x87_r7_55 * fconvert.t(eax_53[2]) + fconvert.t(eax_53[0xe]))
0042ed9e        eax_57 = &vertices[(width_cells + 1) * i_2 + edi_1]
0042eda6        *eax_57 = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*eax_53))) + fconvert.t(eax_53[0xc]))
0042edac        eax_57[1] = var_14_3
0042edaf        ecx_63 = var_10_4
0042ee30        eax_57[2] = ecx_63
0042ee33        width_cells = self->width_cells
0042ee36        edi_1 += 1
0042ee37        width_cells_1 = width_cells
0042ee3d        arg2 = edi_1
0042ee41        do while (edi_1 s<= width_cells)
0042ee4a        i_2 += 1
0042ee4b        i_3 += 0xa8
0042ee53        do while (i_2 s<= self->segment_count)
0042ee59        i_3 = 0
0042ee60        if (self->segment_count s> 0)
0042ee69        int32_t j = 0
0042ee6d        arg2 = 0
0042ee71        if (self->width_cells s> 0)
0042ee79        int32_t eax_66 = i_3 & 0x80000007
0042ee7e        if (eax_66 s< 0)
0042ee84        eax_66 = ((eax_66 - 1) | 0xfffffff8) + 1
0042ee98        float var_54_1 = fconvert.s(float.t(eax_66) * fconvert.t(0.125f))
0042eea6        float var_4c_1 = fconvert.s(float.t(eax_66 + 1) * fconvert.t(0.125f))
0042eeb1        int32_t ecx_67 = 0
0042eeb7        int32_t var_48_2 = 0
0042eec1        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0042eecf        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042eee3        while (true)
0042eee3        int32_t eax_73 = ecx_67 + ((self->width_cells * i_3 + j) << 1)
0042eee6        if (ecx_67 != 0)
0042efad        int16_t* ebp_4 = &facequads[eax_73]
0042efb0        *ebp_4 = 0
0042efb6        ecx_67.w = self->width_cells.w
0042efba        ecx_67.w += 1
0042efc3        ebp_4[1] = ecx_67.w * i_3.w + j.w + 1
0042efc7        struct ObjectFaceQuad* eax_81
0042efc7        eax_81.w = self->width_cells.w
0042efcb        eax_81.w += 1
0042efd2        ebp_4[2] = eax_81.w * i_3.w + j.w
0042efe4        ebp_4[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042effc        ebp_4[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042f000        char* texture_path_1
0042f000        if (((j.b ^ i_3.b) & 1) != 0)
0042f090        texture_path_1 = texture_b
0042f00a        texture_path_1 = texture_b
0042f01d        *(ebp_4 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0042f024        *(ebp_4 + 0x10) = var_50_1
0042f027        *(ebp_4 + 0x14) = var_54_1
0042f02c        *(ebp_4 + 0x18) = arg2
0042f035        *(ebp_4 + 0x1c) = var_54_1
0042f03c        *(ebp_4 + 0x20) = arg2
0042f03f        *(ebp_4 + 0x24) = var_4c_1
0042f044        *(ebp_4 + 0x28) = var_50_1
0042f047        *(ebp_4 + 0x2c) = var_4c_1
0042eefa        int16_t* ebp_3 = &facequads[eax_73]
0042eefd        *ebp_3 = 0
0042ef03        eax_73.w = self->width_cells.w
0042ef07        eax_73.w += 1
0042ef0e        ebp_3[1] = eax_73.w * i_3.w + j.w
0042ef12        int32_t ecx_69
0042ef12        ecx_69.w = self->width_cells.w
0042ef16        ecx_69.w += 1
0042ef22        ebp_3[2] = ecx_69.w * i_3.w + j.w + 1
0042ef33        ebp_3[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042ef49        ebp_3[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042ef4d        char* texture_path
0042ef4d        if (((j.b ^ i_3.b) & 1) != 0)
0042ef9c        texture_path = texture_a
0042ef53        texture_path = texture_a
0042ef66        *(ebp_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0042ef6d        *(ebp_3 + 0x10) = arg2
0042ef70        *(ebp_3 + 0x14) = var_54_1
0042ef75        *(ebp_3 + 0x18) = var_50_1
0042ef7e        *(ebp_3 + 0x1c) = var_54_1
0042ef85        *(ebp_3 + 0x20) = var_50_1
0042ef88        *(ebp_3 + 0x24) = var_4c_1
0042ef8d        *(ebp_3 + 0x28) = arg2
0042ef90        *(ebp_3 + 0x2c) = var_4c_1
0042f04f        bool cond:11_1 = var_48_2 + 1 s< 2
0042f052        var_48_2 += 1
0042f056        if (not(cond:11_1))
0042f056        break
0042eed5        ecx_67 = var_48_2
0042f05c        j += 1
0042f065        arg2 = j
0042f069        do while (j s< self->width_cells)
0042f072        i_3 += 1
0042f075        do while (i_3 s< self->segment_count)
0042f089        return finalize_path_template_record(self)
