/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_twister_path_template_pair @ 0x42a540 */

0042a54d        int32_t i_3 = 0
0042a554        self->kind = PATH_TEMPLATE_KIND_TWISTER
0042a55b        self->is_mirrored_x = 0
0042a55f        self->side_exit_mode = 0
0042a562        self->width_cells = arg3
0042a565        self->width_or_scale = 1f
0042a568        self->segment_count = 0x22
0042a56f        self->segment_count_f = 34f
0042a576        allocate_path_template_samples(self)
0042a57b        long double x87_r7 = float.t(self->width_cells)
0042a57e        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042a585        self->special_runtime_flag_9c = 0
0042a599        primary_samples_5->center_x = fconvert.s(x87_r7 * fconvert.t(0.5f) - fconvert.t(4f))
0042a59f        if (arg4 == 0)
0042a5a1        struct PathTemplateSample* primary_samples = self->primary_samples
0042a5b0        primary_samples->center_x = fconvert.s(fconvert.t(primary_samples->center_x) * fconvert.t(-1f))
0042a5b9        self->primary_samples->rotation_scalar_98 = 0f
0042a5c2        self->primary_samples->rotation_scalar_94 = 0f
0042a5cb        self->primary_samples->special_scalar = 0f
0042a5d4        self->primary_samples->lateral_scale = 1f
0042a5dd        set_matrix_identity(self->primary_samples)
0042a5e2        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042a5eb        primary_samples_1->transform.position.x = primary_samples_1->center_x
0042a5f1        self->primary_samples->transform.position.y = 0f
0042a5f7        self->primary_samples->transform.position.z = 0f
0042a5fd        set_matrix_identity(self->secondary_samples)
0042a613        self->secondary_samples->transform.position.x = self->primary_samples->center_x
0042a619        self->secondary_samples->transform.position.y = 0.49000001f
0042a61f        self->secondary_samples->transform.position.z = 0f
0042a634        self->primary_samples->__offset(0x1638).d = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
0042a63a        struct PathTemplateSample* eax_4
0042a63a        eax_4.b = arg4
0042a640        if (eax_4.b == 0)
0042a642        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042a651        primary_samples_2->__offset(0x1638).d = fconvert.s(fconvert.t(primary_samples_2->__offset(0x1638).d) * fconvert.t(-1f))
0042a65a        self->primary_samples->__offset(0x1640).d = 0
0042a663        self->primary_samples->__offset(0x163c).d = 0
0042a66c        self->primary_samples->__offset(0x1648).d = 0
0042a675        self->primary_samples->__offset(0x1644).d = 0x3f800000
0042a684        set_matrix_identity(&self->primary_samples[0x21])
0042a689        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042a697        primary_samples_3->__offset(0x15d8).d = primary_samples_3->__offset(0x1638).d
0042a6a0        self->primary_samples->__offset(0x15dc).d = 0
0042a6a9        self->primary_samples->__offset(0x15e0).d = 0x42040000
0042a6b8        set_matrix_identity(&self->secondary_samples[0x21])
0042a6c9        self->secondary_samples->__offset(0x15d8).d = self->primary_samples->__offset(0x1638).d
0042a6d2        self->secondary_samples->__offset(0x15dc).d = 0x3efae148
0042a6db        int32_t ebp = 0
0042a6dd        self->secondary_samples->__offset(0x15e0).d = 0x42040000
0042a6e3        arg3 = 0
0042a6e7        int32_t i = 0xa8
0042a9f5        while (i s< 0x15a8)
0042a6f0        struct PathTemplateSample* eax_8
0042a6f0        eax_8.b = arg4
0042a6f6        long double x87_r7_11 = float.t(arg3) * fconvert.t(0.196349546f)
0042a6fc        arg3 = fconvert.s(x87_r7_11)
0042a70a        if (eax_8.b == 0)
0042a716        arg3 = fconvert.s(fconvert.t(arg3) + fconvert.t(3.14159274f))
0042a742        *(&self->primary_samples->center_x + i) = fconvert.s(fconvert.t(2.5f) - (cosine(arg3) + fconvert.t(1f)) * fconvert.t(0.5f) * fconvert.t(5f))
0042a74c        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0042a756        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0042a760        *(&self->primary_samples->special_scalar + i) = 0
0042a76a        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042a77a        set_matrix_identity(self->primary_samples + i)
0042a77f        struct PathTemplateSample* primary_samples_6 = self->primary_samples
0042a78c        *(&primary_samples_6->transform.position + i) = *(&primary_samples_6->center_x + i)
0042a79d        arg3 = fconvert.s(sine(arg3))
0042a7b1        ebp += 1
0042a7ba        *(&self->primary_samples->transform.position.y + i) = fconvert.s(sine(fconvert.s(x87_r7_11 * fconvert.t(0.5f))) * fconvert.t(arg3) * fconvert.t(arg2))
0042a7be        long double x87_r7_24 = float.t(ebp)
0042a7c9        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_24)
0042a7d2        set_matrix_identity(self->secondary_samples + i)
0042a7ea        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0042a7fe        *(&self->secondary_samples->transform.position.y + i) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + i)) + fconvert.t(0.49000001f))
0042a809        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_24)))
0042a80d        if (i s<= 0xa8)
0042a9d1        set_matrix_rotation_identity(self->primary_samples + i - 0xa8)
0042a9e0        set_matrix_rotation_identity(self->secondary_samples + i - 0xa8)
0042a82a        int32_t* edx_15 = self->primary_samples + i - 0x98
0042a83d        *edx_15 = 0
0042a843        edx_15[1] = 0x3f800000
0042a846        edx_15[2] = 0
0042a849        struct PathTemplateSample* primary_samples_7 = self->primary_samples
0042a86d        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position.y + i)) - fconvert.t(*(primary_samples_7 + i - 0x74)))
0042a877        long double x87_r7_33 = fconvert.t(*(&primary_samples_7->transform.position.z + i)) - fconvert.t(*(primary_samples_7 + i - 0x70))
0042a87e        *(primary_samples_7 + i - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position + i)) - fconvert.t(*(primary_samples_7 + i - 0x78)))
0042a880        *(primary_samples_7 + i - 0x84) = var_2c_1
0042a88b        *(primary_samples_7 + i - 0x80) = fconvert.s(x87_r7_33)
0042a898        normalize_vector(self->primary_samples + i - 0x88)
0042a8a2        void* eax_19 = self->primary_samples + i
0042a8b9        cross_vectors(eax_19 - 0xa8, eax_19 - 0x98, eax_19 - 0x88)
0042a8c1        void* eax_20 = self->primary_samples + i
0042a8d8        cross_vectors(eax_20 - 0x98, eax_20 - 0x88, eax_20 - 0xa8)
0042a8e7        orthogonalize_matrix(self->primary_samples + i - 0xa8)
0042a903        int32_t* edx_21 = self->secondary_samples + i - 0x98
0042a916        *edx_21 = 0
0042a91c        edx_21[1] = 0x3f800000
0042a91f        edx_21[2] = 0
0042a922        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042a946        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + i)) - fconvert.t(*(secondary_samples + i - 0x74)))
0042a950        long double x87_r7_41 = fconvert.t(*(&secondary_samples->transform.position.z + i)) - fconvert.t(*(secondary_samples + i - 0x70))
0042a957        *(secondary_samples + i - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + i)) - fconvert.t(*(secondary_samples + i - 0x78)))
0042a959        *(secondary_samples + i - 0x84) = var_14_1
0042a964        *(secondary_samples + i - 0x80) = fconvert.s(x87_r7_41)
0042a971        normalize_vector(self->secondary_samples + i - 0x88)
0042a97b        void* eax_25 = self->secondary_samples + i
0042a992        cross_vectors(eax_25 - 0xa8, eax_25 - 0x98, eax_25 - 0x88)
0042a99a        void* eax_26 = self->secondary_samples + i
0042a9b1        cross_vectors(eax_26 - 0x98, eax_26 - 0x88, eax_26 - 0xa8)
0042a9c0        orthogonalize_matrix(self->secondary_samples + i - 0xa8)
0042a9e5        i += 0xa8
0042a9eb        arg3 = ebp
0042a9fe        int32_t i_1 = 0
0042aa03        if (self->segment_count - 1 s> 0)
0042aa09        void* edi = nullptr
0042aa0b        struct PathTemplateSample* primary_samples_8 = self->primary_samples
0042aa2f        float var_14_2 = fconvert.s(fconvert.t(*(edi + primary_samples_8 + 0xdc)) - fconvert.t(*(&primary_samples_8->transform.position.y + edi)))
0042aa36        long double x87_r7_49 = fconvert.t(*(edi + primary_samples_8 + 0xe0)) - fconvert.t(*(&primary_samples_8->transform.position.z + edi))
0042aa3d        *(&primary_samples_8->delta_dir_to_next + edi) = fconvert.s(fconvert.t(*(edi + primary_samples_8 + 0xd8)) - fconvert.t(*(&primary_samples_8->transform.position + edi)))
0042aa3f        *(&primary_samples_8->delta_dir_to_next.y + edi) = var_14_2
0042aa4a        *(&primary_samples_8->delta_dir_to_next.z + edi) = fconvert.s(x87_r7_49)
0042aa5f        *(&self->primary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi))
0042aa66        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042aa8a        float var_20_1 = fconvert.s(fconvert.t(*(edi + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi)))
0042aa91        long double x87_r7_56 = fconvert.t(*(edi + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi))
0042aa98        *(&secondary_samples_1->delta_dir_to_next + edi) = fconvert.s(fconvert.t(*(edi + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi)))
0042aa9a        *(&secondary_samples_1->delta_dir_to_next.y + edi) = var_20_1
0042aaa5        *(&secondary_samples_1->delta_dir_to_next.z + edi) = fconvert.s(x87_r7_56)
0042aaba        i_1 += 1
0042aabb        *(&self->secondary_samples->delta_length + edi) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi))
0042aac5        edi += 0xa8
0042aace        do while (i_1 s< self->segment_count - 1)
0042aafe        int32_t* ecx_53 = &self->primary_samples[self->segment_count] - 0x28
0042ab12        *ecx_53 = 0
0042ab20        ecx_53[1] = 0
0042ab23        ecx_53[2] = 0x3f800000
0042ab35        int32_t var_10_3 = 0x3f800000
0042ab41        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ab57        int32_t* eax_45 = &self->secondary_samples[self->segment_count] - 0x28
0042ab5f        *eax_45 = 0
0042ab65        eax_45[1] = 0
0042ab6a        eax_45[2] = 0x3f800000
0042ab7f        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ab92        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0042aba4        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0042aba9        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0042abac        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0042abaf        struct Vec3* vertices = strip_mesh->vertices
0042abb9        int32_t i_2 = 0
0042abbd        arg2 = vertices
0042abc1        if (self->segment_count s>= 0)
0042abc7        uint32_t width_cells = self->width_cells
0042abca        int32_t edi_1 = 0
0042abce        arg4.d = 0
0042abd2        arg3 = width_cells
0042abd6        if (width_cells s>= 0)
0042abe9        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042abf2        long double x87_r7_59 = float.t(arg4.d) - float.t(arg3) * fconvert.t(0.5f)
0042abf4        int32_t* eax_57
0042abf4        float ecx_68
0042abf4        if (i_2 == self->segment_count)
0042ac4b        void* eax_58 = primary_samples_4 + i_3
0042ac5c        vertices = arg2
0042aca1        float var_20_2 = fconvert.s(fconvert.t(*(eax_58 - 0x74)) + fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(*(eax_58 - 0xa4)))))
0042aca9        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_58 - 0x70)) + fconvert.t(1f))) + x87_r7_59 * fconvert.t(*(eax_58 - 0xa0))
0042acab        eax_57 = &vertices[(width_cells + 1) * i_2 + edi_1]
0042acb3        *eax_57 = fconvert.s(fconvert.t(*(eax_58 - 0x78)) + fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(*(eax_58 - 0xa8)))))
0042acbd        eax_57[1] = var_20_2
0042acc0        ecx_68 = fconvert.s(x87_r6_20)
0042abf6        float* eax_53 = primary_samples_4 + i_3
0042ac1e        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(eax_53[1]))) + fconvert.t(eax_53[0xd]))
0042ac2b        float var_10_4 = fconvert.s(x87_r7_59 * fconvert.t(eax_53[2]) + fconvert.t(eax_53[0xe]))
0042ac34        eax_57 = &vertices[(width_cells + 1) * i_2 + edi_1]
0042ac3c        *eax_57 = fconvert.s(fconvert.t(fconvert.s(x87_r7_59 * fconvert.t(*eax_53))) + fconvert.t(eax_53[0xc]))
0042ac42        eax_57[1] = var_14_3
0042ac45        ecx_68 = var_10_4
0042acc6        eax_57[2] = ecx_68
0042acc9        width_cells = self->width_cells
0042accc        edi_1 += 1
0042accd        arg3 = width_cells
0042acd3        arg4.d = edi_1
0042acd7        do while (edi_1 s<= width_cells)
0042ace0        i_2 += 1
0042ace1        i_3 += 0xa8
0042ace9        do while (i_2 s<= self->segment_count)
0042acef        i_3 = 0
0042acf6        if (self->segment_count s> 0)
0042acff        int32_t j = 0
0042ad03        arg4.d = 0
0042ad07        if (self->width_cells s> 0)
0042ad0f        int32_t eax_66 = i_3 & 0x80000007
0042ad14        if (eax_66 s< 0)
0042ad1a        eax_66 = ((eax_66 - 1) | 0xfffffff8) + 1
0042ad2e        arg3 = fconvert.s(float.t(eax_66) * fconvert.t(0.125f))
0042ad3c        float var_4c_1 = fconvert.s(float.t(eax_66 + 1) * fconvert.t(0.125f))
0042ad47        int32_t ecx_72 = 0
0042ad4d        int32_t var_48_1 = 0
0042ad57        arg4.d = fconvert.s(float.t(arg4.d) * fconvert.t(0.125f))
0042ad65        arg2 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042ad79        while (true)
0042ad79        int32_t eax_73 = ecx_72 + ((self->width_cells * i_3 + j) << 1)
0042ad7c        if (ecx_72 != 0)
0042ae43        int16_t* ebp_3 = eax_73 * 0x30 + facequads
0042ae46        *ebp_3 = 0
0042ae4c        ecx_72.w = self->width_cells.w
0042ae50        ecx_72.w += 1
0042ae59        ebp_3[1] = ecx_72.w * i_3.w + j.w + 1
0042ae5d        struct ObjectFaceQuad* eax_81
0042ae5d        eax_81.w = self->width_cells.w
0042ae61        eax_81.w += 1
0042ae68        ebp_3[2] = eax_81.w * i_3.w + j.w
0042ae7a        ebp_3[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042ae92        ebp_3[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042ae96        char* texture_path_1
0042ae96        if (((j.b ^ i_3.b) & 1) != 0)
0042af26        texture_path_1 = texture_b
0042aea0        texture_path_1 = texture_b
0042aeaf        int32_t edx_50 = arg4.d
0042aeb3        *(ebp_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
0042aeba        *(ebp_3 + 0x10) = arg2
0042aebd        *(ebp_3 + 0x14) = arg3
0042aec2        *(ebp_3 + 0x18) = edx_50
0042aecb        *(ebp_3 + 0x1c) = arg3
0042aed2        *(ebp_3 + 0x20) = edx_50
0042aed5        *(ebp_3 + 0x24) = var_4c_1
0042aeda        *(ebp_3 + 0x28) = arg2
0042aedd        *(ebp_3 + 0x2c) = var_4c_1
0042ad90        int16_t* ebp_2 = eax_73 * 0x30 + facequads
0042ad93        *ebp_2 = 0
0042ad99        eax_73.w = self->width_cells.w
0042ad9d        eax_73.w += 1
0042ada4        ebp_2[1] = eax_73.w * i_3.w + j.w
0042ada8        int32_t ecx_74
0042ada8        ecx_74.w = self->width_cells.w
0042adac        ecx_74.w += 1
0042adb8        ebp_2[2] = ecx_74.w * i_3.w + j.w + 1
0042adc9        ebp_2[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042addf        ebp_2[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042ade3        char* texture_path
0042ade3        if (((j.b ^ i_3.b) & 1) != 0)
0042ae32        texture_path = texture_a
0042ade9        texture_path = texture_a
0042adfc        *(ebp_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0042ae03        *(ebp_2 + 0x10) = arg4.d
0042ae06        *(ebp_2 + 0x14) = arg3
0042ae0b        *(ebp_2 + 0x18) = arg2
0042ae14        *(ebp_2 + 0x1c) = arg3
0042ae1b        *(ebp_2 + 0x20) = arg2
0042ae1e        *(ebp_2 + 0x24) = var_4c_1
0042ae23        *(ebp_2 + 0x28) = arg4.d
0042ae26        *(ebp_2 + 0x2c) = var_4c_1
0042aee5        bool cond:12_1 = var_48_1 + 1 s< 2
0042aee8        var_48_1 += 1
0042aeec        if (not(cond:12_1))
0042aeec        break
0042ad6b        ecx_72 = var_48_1
0042aef2        j += 1
0042aefb        arg4.d = j
0042aeff        do while (j s< self->width_cells)
0042af08        i_3 += 1
0042af0b        do while (i_3 s< self->segment_count)
0042af1f        return finalize_path_template(self)
