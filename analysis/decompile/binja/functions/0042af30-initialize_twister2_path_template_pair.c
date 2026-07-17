/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_twister2_path_template_pair @ 0x42af30 */

0042af3d        int32_t i_3 = 0
0042af44        self->kind = PATH_TEMPLATE_KIND_TWISTER2
0042af4b        self->is_mirrored_x = 0
0042af4f        self->side_exit_mode = 0
0042af52        self->width_cells = width_cells_
0042af55        self->width_or_scale = 1f
0042af58        self->segment_count = 0x34
0042af5f        self->segment_count_f = 52f
0042af66        allocate_path_template_samples(self)
0042af6b        long double x87_r7 = float.t(self->width_cells)
0042af6e        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042af75        self->has_entry_mesh_transition = 0
0042af89        primary_samples_5->center_x = fconvert.s(x87_r7 * fconvert.t(0.5f) - fconvert.t(4f))
0042af8f        if (handedness == 0)
0042af91        struct PathTemplateSample* primary_samples = self->primary_samples
0042afa0        primary_samples->center_x = fconvert.s(fconvert.t(primary_samples->center_x) * fconvert.t(-1f))
0042afa9        self->primary_samples->rotation_scalar_98 = 0f
0042afb2        self->primary_samples->rotation_scalar_94 = 0f
0042afbb        self->primary_samples->special_scalar = 0f
0042afc4        self->primary_samples->lateral_scale = 1f
0042afcd        set_matrix_identity(self->primary_samples)
0042afd2        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042afdb        primary_samples_1->transform.position.x = primary_samples_1->center_x
0042afe1        self->primary_samples->transform.position.y = 0f
0042afe7        self->primary_samples->transform.position.z = 0f
0042afed        set_matrix_identity(self->secondary_samples)
0042b003        self->secondary_samples->transform.position.x = self->primary_samples->center_x
0042b009        self->secondary_samples->transform.position.y = 0.49000001f
0042b00f        self->secondary_samples->transform.position.z = 0f
0042b024        self->primary_samples->__offset(0x2208).d = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
0042b030        if (handedness == 0)
0042b032        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042b041        primary_samples_2->__offset(0x2208).d = fconvert.s(fconvert.t(primary_samples_2->__offset(0x2208).d) * fconvert.t(-1f))
0042b04a        self->primary_samples->__offset(0x2210).d = 0
0042b053        self->primary_samples->__offset(0x220c).d = 0
0042b05c        self->primary_samples->__offset(0x2218).d = 0
0042b065        self->primary_samples->__offset(0x2214).d = 0x3f800000
0042b074        set_matrix_identity(&self->primary_samples[0x33])
0042b079        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042b087        primary_samples_3->__offset(0x21a8).d = primary_samples_3->__offset(0x2208).d
0042b090        self->primary_samples->__offset(0x21ac).d = 0
0042b099        self->primary_samples->__offset(0x21b0).d = 0x424c0000
0042b0a8        set_matrix_identity(&self->secondary_samples[0x33])
0042b0b9        self->secondary_samples->__offset(0x21a8).d = self->primary_samples->__offset(0x2208).d
0042b0c2        self->secondary_samples->__offset(0x21ac).d = 0x3efae148
0042b0cb        int32_t width_cells_1 = 0
0042b0cd        self->secondary_samples->__offset(0x21b0).d = 0x424c0000
0042b0d3        width_cells_ = 0
0042b0d7        int32_t i = 0xa8
0042b3e5        while (i s< 0x2178)
0042b0e6        long double x87_r7_11 = float.t(width_cells_) * fconvert.t(0.251327425f)
0042b0ec        width_cells_ = fconvert.s(x87_r7_11)
0042b0fa        if (handedness == 0)
0042b106        width_cells_ = fconvert.s(fconvert.t(width_cells_) + fconvert.t(3.14159274f))
0042b132        *(&self->primary_samples->center_x + i) = fconvert.s(fconvert.t(2.5f) - (cosine(width_cells_) + fconvert.t(1f)) * fconvert.t(0.5f) * fconvert.t(5f))
0042b13c        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0042b146        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0042b150        *(&self->primary_samples->special_scalar + i) = 0
0042b15a        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042b16a        set_matrix_identity(self->primary_samples + i)
0042b16f        struct PathTemplateSample* primary_samples_6 = self->primary_samples
0042b17c        *(&primary_samples_6->transform.position + i) = *(&primary_samples_6->center_x + i)
0042b18d        width_cells_ = fconvert.s(sine(width_cells_))
0042b1a1        width_cells_1 += 1
0042b1aa        *(&self->primary_samples->transform.position.y + i) = fconvert.s(sine(fconvert.s(x87_r7_11 * fconvert.t(0.5f))) * fconvert.t(width_cells_) * fconvert.t(height))
0042b1ae        long double x87_r7_24 = float.t(width_cells_1)
0042b1b9        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_24)
0042b1c2        set_matrix_identity(self->secondary_samples + i)
0042b1da        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0042b1ee        *(&self->secondary_samples->transform.position.y + i) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + i)) + fconvert.t(0.49000001f))
0042b1f9        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_24)))
0042b1fd        if (i s<= 0xa8)
0042b3c1        set_matrix_rotation_identity(self->primary_samples + i - 0xa8)
0042b3d0        set_matrix_rotation_identity(self->secondary_samples + i - 0xa8)
0042b21a        int32_t* edx_15 = self->primary_samples + i - 0x98
0042b22d        *edx_15 = 0
0042b233        edx_15[1] = 0x3f800000
0042b236        edx_15[2] = 0
0042b239        struct PathTemplateSample* primary_samples_7 = self->primary_samples
0042b25d        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position.y + i)) - fconvert.t(*(primary_samples_7 + i - 0x74)))
0042b267        long double x87_r7_33 = fconvert.t(*(&primary_samples_7->transform.position.z + i)) - fconvert.t(*(primary_samples_7 + i - 0x70))
0042b26e        *(primary_samples_7 + i - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position + i)) - fconvert.t(*(primary_samples_7 + i - 0x78)))
0042b270        *(primary_samples_7 + i - 0x84) = var_2c_1
0042b27b        *(primary_samples_7 + i - 0x80) = fconvert.s(x87_r7_33)
0042b288        normalize_vector(self->primary_samples + i - 0x88)
0042b292        void* eax_22 = self->primary_samples + i
0042b2a9        cross_vectors(eax_22 - 0xa8, eax_22 - 0x98, eax_22 - 0x88)
0042b2b1        void* eax_23 = self->primary_samples + i
0042b2c8        cross_vectors(eax_23 - 0x98, eax_23 - 0x88, eax_23 - 0xa8)
0042b2d7        orthogonalize_matrix(self->primary_samples + i - 0xa8)
0042b2f3        int32_t* edx_21 = self->secondary_samples + i - 0x98
0042b306        *edx_21 = 0
0042b30c        edx_21[1] = 0x3f800000
0042b30f        edx_21[2] = 0
0042b312        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042b336        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + i)) - fconvert.t(*(secondary_samples + i - 0x74)))
0042b340        long double x87_r7_41 = fconvert.t(*(&secondary_samples->transform.position.z + i)) - fconvert.t(*(secondary_samples + i - 0x70))
0042b347        *(secondary_samples + i - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + i)) - fconvert.t(*(secondary_samples + i - 0x78)))
0042b349        *(secondary_samples + i - 0x84) = var_14_1
0042b354        *(secondary_samples + i - 0x80) = fconvert.s(x87_r7_41)
0042b361        normalize_vector(self->secondary_samples + i - 0x88)
0042b36b        void* eax_28 = self->secondary_samples + i
0042b382        cross_vectors(eax_28 - 0xa8, eax_28 - 0x98, eax_28 - 0x88)
0042b38a        void* eax_29 = self->secondary_samples + i
0042b3a1        cross_vectors(eax_29 - 0x98, eax_29 - 0x88, eax_29 - 0xa8)
0042b3b0        orthogonalize_matrix(self->secondary_samples + i - 0xa8)
0042b3d5        i += 0xa8
0042b3db        width_cells_ = width_cells_1
0042b3ee        int32_t i_1 = 0
0042b3f3        if (self->segment_count - 1 s> 0)
0042b3f9        void* edi = nullptr
0042b3fb        struct PathTemplateSample* primary_samples_8 = self->primary_samples
0042b41f        float var_14_2 = fconvert.s(fconvert.t(*(edi + primary_samples_8 + 0xdc)) - fconvert.t(*(&primary_samples_8->transform.position.y + edi)))
0042b426        long double x87_r7_49 = fconvert.t(*(edi + primary_samples_8 + 0xe0)) - fconvert.t(*(&primary_samples_8->transform.position.z + edi))
0042b42d        *(&primary_samples_8->delta_dir_to_next + edi) = fconvert.s(fconvert.t(*(edi + primary_samples_8 + 0xd8)) - fconvert.t(*(&primary_samples_8->transform.position + edi)))
0042b42f        *(&primary_samples_8->delta_dir_to_next.y + edi) = var_14_2
0042b43a        *(&primary_samples_8->delta_dir_to_next.z + edi) = fconvert.s(x87_r7_49)
0042b44f        *(&self->primary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi))
0042b456        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042b47a        float var_20_1 = fconvert.s(fconvert.t(*(edi + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi)))
0042b481        long double x87_r7_56 = fconvert.t(*(edi + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi))
0042b488        *(&secondary_samples_1->delta_dir_to_next + edi) = fconvert.s(fconvert.t(*(edi + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi)))
0042b48a        *(&secondary_samples_1->delta_dir_to_next.y + edi) = var_20_1
0042b495        *(&secondary_samples_1->delta_dir_to_next.z + edi) = fconvert.s(x87_r7_56)
0042b4aa        i_1 += 1
0042b4ab        *(&self->secondary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi))
0042b4b5        edi += 0xa8
0042b4be        do while (i_1 s< self->segment_count - 1)
0042b4ee        int32_t* ecx_53 = &self->primary_samples[self->segment_count] - 0x28
0042b502        *ecx_53 = 0
0042b510        ecx_53[1] = 0
0042b513        ecx_53[2] = 0x3f800000
0042b525        int32_t var_10_3 = 0x3f800000
0042b531        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042b547        int32_t* eax_48 = &self->secondary_samples[self->segment_count] - 0x28
0042b54f        *eax_48 = 0
0042b555        eax_48[1] = 0
0042b55a        eax_48[2] = 0x3f800000
0042b56f        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042b582        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042b594        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042b599        struct Object* object = self->bod.object
0042b59c        struct ObjectFaceQuad* facequads = object->facequads
0042b59f        struct Vec3* vertices = object->vertices
0042b5a9        int32_t i_2 = 0
0042b5ad        height = vertices
0042b5b1        if (self->segment_count s>= 0)
0042b5b7        uint32_t width_cells = self->width_cells
0042b5ba        int32_t edi_1 = 0
0042b5be        handedness.d = 0
0042b5c2        width_cells_ = width_cells
0042b5c6        if (width_cells s>= 0)
0042b5d9        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042b5e2        long double x87_r7_59 = float.t(handedness.d) - float.t(width_cells_) * fconvert.t(0.5f)
0042b5e4        int32_t* eax_60
0042b5e4        float ecx_68
0042b5e4        if (i_2 == self->segment_count)
0042b63b        void* eax_61 = primary_samples_4 + i_3
0042b64c        vertices = height
0042b691        float var_20_2 = fconvert.s(fconvert.t(*(eax_61 - 0x74)) + fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(*(eax_61 - 0xa4)))))
0042b699        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_61 - 0x70)) + fconvert.t(1f))) + x87_r7_59 * fconvert.t(*(eax_61 - 0xa0))
0042b69b        eax_60 = &vertices[(width_cells + 1) * i_2 + edi_1]
0042b6a3        *eax_60 = fconvert.s(fconvert.t(*(eax_61 - 0x78)) + fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(*(eax_61 - 0xa8)))))
0042b6ad        eax_60[1] = var_20_2
0042b6b0        ecx_68 = fconvert.s(x87_r6_20)
0042b5e6        float* eax_56 = primary_samples_4 + i_3
0042b60e        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(eax_56[1]))) + fconvert.t(eax_56[0xd]))
0042b61b        float var_10_4 = fconvert.s(x87_r7_59 * fconvert.t(eax_56[2]) + fconvert.t(eax_56[0xe]))
0042b624        eax_60 = &vertices[(width_cells + 1) * i_2 + edi_1]
0042b62c        *eax_60 = fconvert.s(fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(*eax_56))) + fconvert.t(eax_56[0xc]))
0042b632        eax_60[1] = var_14_3
0042b635        ecx_68 = var_10_4
0042b6b6        eax_60[2] = ecx_68
0042b6b9        width_cells = self->width_cells
0042b6bc        edi_1 += 1
0042b6bd        width_cells_ = width_cells
0042b6c3        handedness.d = edi_1
0042b6c7        do while (edi_1 s<= width_cells)
0042b6d0        i_2 += 1
0042b6d1        i_3 += 0xa8
0042b6d9        do while (i_2 s<= self->segment_count)
0042b6df        i_3 = 0
0042b6e6        if (self->segment_count s> 0)
0042b6ef        int32_t j = 0
0042b6f3        handedness.d = 0
0042b6f7        if (self->width_cells s> 0)
0042b6ff        int32_t eax_69 = i_3 & 0x80000007
0042b704        if (eax_69 s< 0)
0042b70a        eax_69 = ((eax_69 - 1) | 0xfffffff8) + 1
0042b71e        width_cells_ = fconvert.s(float.t(eax_69) * fconvert.t(0.125f))
0042b72c        float var_4c_1 = fconvert.s(float.t(eax_69 + 1) * fconvert.t(0.125f))
0042b737        int32_t ecx_72 = 0
0042b73d        int32_t var_48_1 = 0
0042b747        handedness.d = fconvert.s(float.t(handedness.d) * fconvert.t(0.125f))
0042b755        height = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042b769        while (true)
0042b769        int32_t eax_76 = ecx_72 + ((self->width_cells * i_3 + j) << 1)
0042b76c        if (ecx_72 != 0)
0042b828        struct ObjectFaceQuad* facequads_1 = facequads
0042b833        int16_t* ebp_2 = &facequads_1[eax_76]
0042b836        *ebp_2 = 0
0042b83c        ecx_72.w = self->width_cells.w
0042b840        ecx_72.w += 1
0042b849        ebp_2[1] = ecx_72.w * i_3.w + j.w + 1
0042b84d        facequads_1.w = self->width_cells.w
0042b851        facequads_1.w += 1
0042b858        ebp_2[2] = facequads_1.w * i_3.w + j.w
0042b86a        ebp_2[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042b882        ebp_2[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042b886        char* texture_path_1
0042b886        if (((j.b ^ i_3.b) & 1) != 0)
0042b916        texture_path_1 = texture_b
0042b890        texture_path_1 = texture_b
0042b89f        int32_t edx_50 = handedness.d
0042b8a3        *(ebp_2 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path_1, 0, 0)
0042b8aa        *(ebp_2 + 0x10) = height
0042b8ad        *(ebp_2 + 0x14) = width_cells_
0042b8b2        *(ebp_2 + 0x18) = edx_50
0042b8bb        *(ebp_2 + 0x1c) = width_cells_
0042b8c2        *(ebp_2 + 0x20) = edx_50
0042b8c5        *(ebp_2 + 0x24) = var_4c_1
0042b8ca        *(ebp_2 + 0x28) = height
0042b8cd        *(ebp_2 + 0x2c) = var_4c_1
0042b779        int32_t ecx_74 = eax_76 * 0x30
0042b780        int16_t* ebp_1 = ecx_74 + facequads
0042b783        *ebp_1 = 0
0042b789        eax_76.w = self->width_cells.w
0042b78d        eax_76.w += 1
0042b794        ebp_1[1] = eax_76.w * i_3.w + j.w
0042b798        ecx_74.w = self->width_cells.w
0042b79c        ecx_74.w += 1
0042b7a8        ebp_1[2] = ecx_74.w * i_3.w + j.w + 1
0042b7b9        ebp_1[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042b7cf        ebp_1[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042b7d3        char* texture_path
0042b7d3        if (((j.b ^ i_3.b) & 1) != 0)
0042b822        texture_path = texture_a
0042b7d9        texture_path = texture_a
0042b7ec        *(ebp_1 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
0042b7f3        *(ebp_1 + 0x10) = handedness.d
0042b7f6        *(ebp_1 + 0x14) = width_cells_
0042b7fb        *(ebp_1 + 0x18) = height
0042b804        *(ebp_1 + 0x1c) = width_cells_
0042b80b        *(ebp_1 + 0x20) = height
0042b80e        *(ebp_1 + 0x24) = var_4c_1
0042b813        *(ebp_1 + 0x28) = handedness.d
0042b816        *(ebp_1 + 0x2c) = var_4c_1
0042b8d5        bool cond:12_1 = var_48_1 + 1 s< 2
0042b8d8        var_48_1 += 1
0042b8dc        if (not(cond:12_1))
0042b8dc        break
0042b75b        ecx_72 = var_48_1
0042b8e2        j += 1
0042b8eb        handedness.d = j
0042b8ef        do while (j s< self->width_cells)
0042b8f8        i_3 += 1
0042b8fb        do while (i_3 s< self->segment_count)
0042b903        finalize_path_template(self)
0042b90f        return
