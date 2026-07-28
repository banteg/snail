/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_twister_path_template_pair @ 0x42a540 */

0042a54d        int32_t i_1 = 0
0042a554        self->kind = PATH_TEMPLATE_KIND_TWISTER
0042a55b        self->is_mirrored_x = 0
0042a55f        self->side_exit_mode = 0
0042a562        self->width_cells = width_cells_
0042a565        self->width_or_scale = 1f
0042a568        self->segment_count = 0x22
0042a56f        self->segment_count_f = 34f
0042a576        get_path_nodes(self)
0042a57b        long double x87_r7 = float.t(self->width_cells)
0042a57e        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042a585        self->has_entry_mesh_transition = 0
0042a599        primary_samples_5->center_x = fconvert.s(x87_r7 * fconvert.t(0.5f) - fconvert.t(4f))
0042a59f        if (handedness == 0)
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
0042a640        if (handedness == 0)
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
0042a6dd        self->secondary_samples->__offset(0x15e0).d = 0x42040000
0042a6e3        int32_t interior_index = 0
0042a6e7        int32_t interior_sample_offset = 0xa8
0042a9f5        while (interior_sample_offset s< 0x15a8)
0042a6f6        double base_phase = (float.t(interior_index) * fconvert.t(0.196349546f)).q
0042a6fc        float curve_phase = fconvert.s(base_phase)
0042a70a        if (handedness == 0)
0042a716        curve_phase = fconvert.s(fconvert.t(curve_phase) + fconvert.t(3.14159274f))
0042a742        *(&self->primary_samples->center_x + interior_sample_offset) = fconvert.s(fconvert.t(2.5f) - (cosine(curve_phase) + fconvert.t(1f)) * fconvert.t(0.5f) * fconvert.t(5f))
0042a74c        *(&self->primary_samples->rotation_scalar_98 + interior_sample_offset) = 0
0042a756        *(&self->primary_samples->rotation_scalar_94 + interior_sample_offset) = 0
0042a760        *(&self->primary_samples->special_scalar + interior_sample_offset) = 0
0042a76a        *(&self->primary_samples->lateral_scale + interior_sample_offset) = 0x3f800000
0042a77a        set_matrix_identity(self->primary_samples + interior_sample_offset)
0042a77f        struct PathTemplateSample* primary_samples_6 = self->primary_samples
0042a78c        *(&primary_samples_6->transform.position + interior_sample_offset) = *(&primary_samples_6->center_x + interior_sample_offset)
0042a79d        float curve_phase_sine = fconvert.s(sine(curve_phase))
0042a7ba        *(&self->primary_samples->transform.position.y + interior_sample_offset) = fconvert.s(sine(fconvert.s(base_phase * fconvert.t(0.5f))) * fconvert.t(curve_phase_sine) * fconvert.t(height))
0042a7be        long double x87_r7_23 = float.t(interior_index + 1)
0042a7c9        *(&self->primary_samples->transform.position.z + interior_sample_offset) = fconvert.s(x87_r7_23)
0042a7d2        set_matrix_identity(self->secondary_samples + interior_sample_offset)
0042a7ea        *(&self->secondary_samples->transform.position + interior_sample_offset) = *(&self->primary_samples->center_x + interior_sample_offset)
0042a7fe        *(&self->secondary_samples->transform.position.y + interior_sample_offset) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + interior_sample_offset)) + fconvert.t(0.49000001f))
0042a809        *(&self->secondary_samples->transform.position.z + interior_sample_offset) = fconvert.s(fconvert.t(fconvert.s(x87_r7_23)))
0042a80d        if (interior_sample_offset s<= 0xa8)
0042a9d1        set_matrix_rotation_identity(self->primary_samples + interior_sample_offset - 0xa8)
0042a9e0        set_matrix_rotation_identity(self->secondary_samples + interior_sample_offset - 0xa8)
0042a846        *(self->primary_samples + interior_sample_offset - 0x98) = struct Vec3 {
    .x = 0
    .y = 1f
    .z = 0f
}
0042a849        struct PathTemplateSample* primary_samples_7 = self->primary_samples
0042a86d        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position.y + interior_sample_offset)) - fconvert.t(*(primary_samples_7 + interior_sample_offset - 0x74)))
0042a877        long double x87_r7_32 = fconvert.t(*(&primary_samples_7->transform.position.z + interior_sample_offset)) - fconvert.t(*(primary_samples_7 + interior_sample_offset - 0x70))
0042a87e        *(primary_samples_7 + interior_sample_offset - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_7->transform.position + interior_sample_offset)) - fconvert.t(*(primary_samples_7 + interior_sample_offset - 0x78)))
0042a880        *(primary_samples_7 + interior_sample_offset - 0x84) = var_2c_1
0042a88b        *(primary_samples_7 + interior_sample_offset - 0x80) = fconvert.s(x87_r7_32)
0042a898        normalize_vector(self->primary_samples + interior_sample_offset - 0x88)
0042a8a2        struct PathTemplateSample* primary_sample_cursor = self->primary_samples + interior_sample_offset
0042a8b9        cross_vectors(primary_sample_cursor - 0xa8, primary_sample_cursor - 0x98, primary_sample_cursor - 0x88)
0042a8c1        struct PathTemplateSample* primary_sample_cursor_reloaded = self->primary_samples + interior_sample_offset
0042a8d8        cross_vectors(primary_sample_cursor_reloaded - 0x98, primary_sample_cursor_reloaded - 0x88, primary_sample_cursor_reloaded - 0xa8)
0042a8e7        orthogonalize_matrix(self->primary_samples + interior_sample_offset - 0xa8)
0042a91f        *(self->secondary_samples + interior_sample_offset - 0x98) = struct Vec3 {
    .x = 0
    .y = 1f
    .z = 0f
}
0042a922        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042a946        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + interior_sample_offset)) - fconvert.t(*(secondary_samples + interior_sample_offset - 0x74)))
0042a950        long double x87_r7_40 = fconvert.t(*(&secondary_samples->transform.position.z + interior_sample_offset)) - fconvert.t(*(secondary_samples + interior_sample_offset - 0x70))
0042a957        *(secondary_samples + interior_sample_offset - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + interior_sample_offset)) - fconvert.t(*(secondary_samples + interior_sample_offset - 0x78)))
0042a959        *(secondary_samples + interior_sample_offset - 0x84) = var_14_1
0042a964        *(secondary_samples + interior_sample_offset - 0x80) = fconvert.s(x87_r7_40)
0042a971        normalize_vector(self->secondary_samples + interior_sample_offset - 0x88)
0042a97b        struct PathTemplateSample* secondary_sample_cursor = self->secondary_samples + interior_sample_offset
0042a992        cross_vectors(secondary_sample_cursor - 0xa8, secondary_sample_cursor - 0x98, secondary_sample_cursor - 0x88)
0042a99a        struct PathTemplateSample* secondary_sample_cursor_reloaded = self->secondary_samples + interior_sample_offset
0042a9b1        cross_vectors(secondary_sample_cursor_reloaded - 0x98, secondary_sample_cursor_reloaded - 0x88, secondary_sample_cursor_reloaded - 0xa8)
0042a9c0        orthogonalize_matrix(self->secondary_samples + interior_sample_offset - 0xa8)
0042a9e5        interior_sample_offset += 0xa8
0042a9eb        interior_index += 1
0042a9fe        int32_t delta_index = 0
0042aa03        if (self->segment_count - 1 s> 0)
0042aa09        int32_t delta_sample_offset = 0
0042aa0b        struct PathTemplateSample* primary_samples_8 = self->primary_samples
0042aa2f        float var_14_2 = fconvert.s(fconvert.t(*(delta_sample_offset + primary_samples_8 + 0xdc)) - fconvert.t(*(&primary_samples_8->transform.position.y + delta_sample_offset)))
0042aa36        long double x87_r7_48 = fconvert.t(*(delta_sample_offset + primary_samples_8 + 0xe0)) - fconvert.t(*(&primary_samples_8->transform.position.z + delta_sample_offset))
0042aa3d        *(&primary_samples_8->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + primary_samples_8 + 0xd8)) - fconvert.t(*(&primary_samples_8->transform.position + delta_sample_offset)))
0042aa3f        *(&primary_samples_8->delta_dir_to_next.y + delta_sample_offset) = var_14_2
0042aa4a        *(&primary_samples_8->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_48)
0042aa5f        *(&self->primary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + delta_sample_offset))
0042aa66        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042aa8a        float var_20_1 = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + delta_sample_offset)))
0042aa91        long double x87_r7_55 = fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + delta_sample_offset))
0042aa98        *(&secondary_samples_1->delta_dir_to_next + delta_sample_offset) = fconvert.s(fconvert.t(*(delta_sample_offset + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + delta_sample_offset)))
0042aa9a        *(&secondary_samples_1->delta_dir_to_next.y + delta_sample_offset) = var_20_1
0042aaa5        *(&secondary_samples_1->delta_dir_to_next.z + delta_sample_offset) = fconvert.s(x87_r7_55)
0042aaba        delta_index += 1
0042aabb        *(&self->secondary_samples->delta_length + delta_sample_offset) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + delta_sample_offset))
0042aac5        delta_sample_offset += 0xa8
0042aace        do while (delta_index s< self->segment_count - 1)
0042ab23        *(&self->primary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0042ab35        int32_t var_10_3 = 0x3f800000
0042ab41        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ab6a        *(&self->secondary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
0042ab7f        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ab92        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042aba4        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042aba9        struct Object* object = self->bod.object
0042abac        struct ObjectFaceQuad* facequads = object->facequads
0042abaf        struct Vec3* vertices = object->vertices
0042abb9        int32_t i = 0
0042abbd        height = vertices
0042abc1        if (self->segment_count s>= 0)
0042abc7        uint32_t width_cells = self->width_cells
0042abca        int32_t edi = 0
0042abce        handedness.d = 0
0042abd2        width_cells_ = width_cells
0042abd6        if (width_cells s>= 0)
0042abe9        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042abf2        long double x87_r7_58 = float.t(handedness.d) - float.t(width_cells_) * fconvert.t(0.5f)
0042abf4        int32_t* eax_54
0042abf4        float ecx_67
0042abf4        if (i == self->segment_count)
0042ac4b        void* eax_55 = primary_samples_4 + i_1
0042ac5c        vertices = height
0042aca1        float var_20_2 = fconvert.s(fconvert.t(*(eax_55 - 0x74)) + fconvert.t(fconvert.s(x87_r7_58 * fconvert.t(*(eax_55 - 0xa4)))))
0042aca9        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_55 - 0x70)) + fconvert.t(1f))) + x87_r7_58 * fconvert.t(*(eax_55 - 0xa0))
0042acab        eax_54 = &vertices[(width_cells + 1) * i + edi]
0042acb3        *eax_54 = fconvert.s(fconvert.t(*(eax_55 - 0x78)) + fconvert.t(fconvert.s(x87_r7_58 * fconvert.t(*(eax_55 - 0xa8)))))
0042acbd        eax_54[1] = var_20_2
0042acc0        ecx_67 = fconvert.s(x87_r6_20)
0042abf6        struct PathTemplateSample* primary_mesh_sample = primary_samples_4 + i_1
0042ac1e        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_58 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0042ac2b        float var_10_4 = fconvert.s(x87_r7_58 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0042ac34        eax_54 = &vertices[(width_cells + 1) * i + edi]
0042ac3c        *eax_54 = fconvert.s(fconvert.t(fconvert.s(x87_r7_58 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0042ac42        eax_54[1] = var_14_3
0042ac45        ecx_67 = var_10_4
0042acc6        eax_54[2] = ecx_67
0042acc9        width_cells = self->width_cells
0042accc        edi += 1
0042accd        width_cells_ = width_cells
0042acd3        handedness.d = edi
0042acd7        do while (edi s<= width_cells)
0042ace0        i += 1
0042ace1        i_1 += 0xa8
0042ace9        do while (i s<= self->segment_count)
0042acef        i_1 = 0
0042acf6        if (self->segment_count s> 0)
0042acff        int32_t j = 0
0042ad03        handedness.d = 0
0042ad07        if (self->width_cells s> 0)
0042ad0f        int32_t eax_63 = i_1 & 0x80000007
0042ad14        if (eax_63 s< 0)
0042ad1a        eax_63 = ((eax_63 - 1) | 0xfffffff8) + 1
0042ad2e        width_cells_ = fconvert.s(float.t(eax_63) * fconvert.t(0.125f))
0042ad3c        float var_4c_1 = fconvert.s(float.t(eax_63 + 1) * fconvert.t(0.125f))
0042ad47        int32_t ecx_71 = 0
0042ad4d        int32_t var_48_1 = 0
0042ad57        handedness.d = fconvert.s(float.t(handedness.d) * fconvert.t(0.125f))
0042ad65        height = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042ad79        while (true)
0042ad79        int32_t eax_70 = ecx_71 + ((self->width_cells * i_1 + j) << 1)
0042ad7c        if (ecx_71 != 0)
0042ae38        struct ObjectFaceQuad* facequads_1 = facequads
0042ae43        struct ObjectFaceQuad* face_second = &facequads_1[eax_70]
0042ae46        __builtin_memset(face_second, 0, 2)
0042ae4c        ecx_71.w = self->width_cells.w
0042ae50        ecx_71.w += 1
0042ae59        face_second->vertex_0 = ecx_71.w * i_1.w + j.w + 1
0042ae5d        facequads_1.w = self->width_cells.w
0042ae61        facequads_1.w += 1
0042ae68        face_second->vertex_1 = facequads_1.w * i_1.w + j.w
0042ae7a        face_second->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
0042ae92        face_second->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
0042ae96        char* texture_path_1
0042ae96        if (((j.b ^ i_1.b) & 1) != 0)
0042af26        texture_path_1 = texture_b
0042aea0        texture_path_1 = texture_b
0042aeaf        int32_t edx_48 = handedness.d
0042aeb3        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0042aeba        face_second->uv[0].u = height
0042aebd        face_second->uv[0].v = width_cells_
0042aec2        face_second->uv[1].u = edx_48
0042aecb        face_second->uv[1].v = width_cells_
0042aed2        face_second->uv[2].u = edx_48
0042aed5        face_second->uv[2].v = var_4c_1
0042aeda        face_second->uv[3].u = height
0042aedd        face_second->uv[3].v = var_4c_1
0042ad89        int32_t ecx_73 = eax_70 * 0x30
0042ad90        struct ObjectFaceQuad* face_first = ecx_73 + facequads
0042ad93        __builtin_memset(face_first, 0, 2)
0042ad99        eax_70.w = self->width_cells.w
0042ad9d        eax_70.w += 1
0042ada4        face_first->vertex_0 = eax_70.w * i_1.w + j.w
0042ada8        ecx_73.w = self->width_cells.w
0042adac        ecx_73.w += 1
0042adb8        face_first->vertex_1 = ecx_73.w * i_1.w + j.w + 1
0042adc9        face_first->vertex_2 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w + 1
0042addf        face_first->vertex_3 = (self->width_cells.w + 1) * (i_1.w + 1) + j.w
0042ade3        char* texture_path
0042ade3        if (((j.b ^ i_1.b) & 1) != 0)
0042ae32        texture_path = texture_a
0042ade9        texture_path = texture_a
0042adfc        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0042ae03        face_first->uv[0].u = handedness.d
0042ae06        face_first->uv[0].v = width_cells_
0042ae0b        face_first->uv[1].u = height
0042ae14        face_first->uv[1].v = width_cells_
0042ae1b        face_first->uv[2].u = height
0042ae1e        face_first->uv[2].v = var_4c_1
0042ae23        face_first->uv[3].u = handedness.d
0042ae26        face_first->uv[3].v = var_4c_1
0042aee5        bool cond:12_1 = var_48_1 + 1 s< 2
0042aee8        var_48_1 += 1
0042aeec        if (not(cond:12_1))
0042aeec        break
0042ad6b        ecx_71 = var_48_1
0042aef2        j += 1
0042aefb        handedness.d = j
0042aeff        do while (j s< self->width_cells)
0042af08        i_1 += 1
0042af0b        do while (i_1 s< self->segment_count)
0042af13        calc_path_length_z(self)
0042af1f        return
