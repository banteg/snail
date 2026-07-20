/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_halfpipe_path_template_pair @ 0x429b20 */

00429b3a        self->kind = PATH_TEMPLATE_KIND_NONLINEAR_42
00429b41        self->is_mirrored_x = 0
00429b45        self->side_exit_mode = 0
00429b48        self->width_cells = width_cells_
00429b4b        self->width_or_scale = 1f
00429b4e        self->segment_count = 0x42
00429b55        self->segment_count_f = 66f
00429b5c        struct PathTemplateSample* secondary_samples = allocate_path_template_samples(self)
00429b61        self->has_entry_mesh_transition = 0
00429b68        int32_t var_9c = 0
00429b6c        int32_t i = 0
00429c84        while (i s< 0xa80)
00429b6e        long double x87_r7_1 = float.t(var_9c)
00429b72        struct PathTemplateSample* secondary_samples_2 = secondary_samples
00429b73        float var_94_1 = fconvert.s(x87_r7_1)
00429baf        long double x87_r7_10 = ((fconvert.t(0.5f) - sine(fconvert.s(x87_r7_1 * fconvert.t(0.0625f) * fconvert.t(3.14159274f) + fconvert.t(1.57079637f))) * fconvert.t(0.5f)) * fconvert.t(0.949999988f) + fconvert.t(0.0500000007f)) * fconvert.t(4f)
00429bc4        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
00429bd2        *(&self->primary_samples->rotation_scalar_98 + i) = 0
00429be6        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00429bf2        *(&self->primary_samples->special_scalar + i) = fconvert.s((x87_r7_10 * x87_r7_10 + fconvert.t(16f)) / (x87_r7_10 + x87_r7_10))
00429bfc        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
00429c08        set_matrix_identity(self->primary_samples + i)
00429c10        struct PathTemplateSample* primary_leadin_sample = self->primary_samples + i
00429c1c        primary_leadin_sample->transform.position.x = primary_leadin_sample->center_x
00429c22        *(&self->primary_samples->transform.position.y + i) = 0
00429c29        *(&self->primary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_94_1))
00429c30        *(&self->primary_samples->delta_length + i) = 0x3f800000
00429c3c        set_matrix_identity(self->secondary_samples + i)
00429c52        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
00429c59        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
00429c68        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_94_1))
00429c6c        secondary_samples = self->secondary_samples
00429c6f        i += 0xa8
00429c7c        *(secondary_samples + i - 0x1c) = 0x3f800000
00429c80        var_9c += 1
00429c8a        int32_t var_9c_1 = 0
00429c8e        void* i_1 = 0x20d0
00429dc1        while (i_1 s< 0x2b50)
00429c97        struct PathTemplateSample* secondary_samples_3 = secondary_samples
00429cd6        long double x87_r7_25 = ((fconvert.t(0.5f) - sine(fconvert.s((fconvert.t(1f) - float.t(var_9c_1) * fconvert.t(0.0625f)) * fconvert.t(3.14159274f) + fconvert.t(1.57079637f))) * fconvert.t(0.5f)) * fconvert.t(0.949999988f) + fconvert.t(0.0500000007f)) * fconvert.t(4f)
00429ceb        *(&self->primary_samples->center_x + i_1) = fconvert.s(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
00429cf9        *(&self->primary_samples->rotation_scalar_98 + i_1) = 0
00429d0d        *(&self->primary_samples->rotation_scalar_94 + i_1) = 0
00429d1b        *(&self->primary_samples->special_scalar + i_1) = fconvert.s((x87_r7_25 * x87_r7_25 + fconvert.t(16f)) / (x87_r7_25 + x87_r7_25))
00429d25        *(&self->primary_samples->lateral_scale + i_1) = 0x3f800000
00429d31        set_matrix_identity(i_1 + self->primary_samples)
00429d36        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00429d4a        *(&primary_samples_1->transform.position + i_1) = *(&primary_samples_1->center_x + i_1)
00429d54        long double x87_r7_28 = float.t(var_9c_1 + 0x32)
00429d58        *(&self->primary_samples->transform.position.y + i_1) = 0
00429d63        *(&self->primary_samples->transform.position.z + i_1) = fconvert.s(x87_r7_28)
00429d6a        *(&self->primary_samples->delta_length + i_1) = 0x3f800000
00429d76        set_matrix_identity(self->secondary_samples + i_1)
00429d8c        *(&self->secondary_samples->transform.position + i_1) = *(&self->primary_samples->center_x + i_1)
00429d90        secondary_samples = self->secondary_samples
00429d93        *(&secondary_samples->transform.position.y + i_1) = 0x3efae148
00429d9e        *(&self->secondary_samples->transform.position.z + i_1) = fconvert.s(fconvert.t(fconvert.s(x87_r7_28)))
00429daa        *(&self->secondary_samples->delta_length + i_1) = 0x3f800000
00429db1        i_1 += 0xa8
00429dbd        var_9c_1 += 1
00429dc7        int32_t var_9c_2 = 0
00429f6e        float out_angle
00429de3        void* i_2 = 0xa80
00429f6e        while (i_2 s< 0x20d0)
00429dec        long double x87_r7_30 = float.t(var_9c_2)
00429df0        struct PathTemplateSample* primary_samples = self->primary_samples
00429dfb        out_angle = fconvert.s(x87_r7_30 * fconvert.t(0.184799567f))
00429e19        *(&primary_samples->center_x + i_2) = fconvert.s((fconvert.t(primary_samples->__offset(0x2160).d) - fconvert.t(primary_samples->center_x)) * x87_r7_30 * fconvert.t(0.0294117648f) + fconvert.t(primary_samples->center_x))
00429e25        *(&self->primary_samples->rotation_scalar_98 + i_2) = 0
00429e2f        *(&self->primary_samples->rotation_scalar_94 + i_2) = 0
00429e39        *(&self->primary_samples->special_scalar + i_2) = 0x40800000
00429e47        *(&self->primary_samples->lateral_scale + i_2) = 0x3f800000
00429e59        set_matrix_identity(i_2 + self->primary_samples)
00429e6c        *(&self->primary_samples->transform.position + i_2) = 0
00429e77        *(&self->primary_samples->transform.position.z + i_2) = fconvert.s(float.t(var_9c_2 + 0x10))
00429e7e        *(&self->primary_samples->transform.position.y + i_2) = 0
00429e89        struct Vec3* primary_up = &self->primary_samples->transform.basis_up + i_2
00429e91        primary_up->x = 0
00429e97        primary_up->y = 1f
00429e9a        primary_up->z = 0f
00429ea0        void* eax_19 = self->primary_samples + i_2
00429ebc        float var_8c_1 = fconvert.s(fconvert.t(*(eax_19 + 0x34)) - fconvert.t(*(eax_19 - 0x74)))
00429ec3        long double x87_r7_38 = fconvert.t(*(eax_19 + 0x38)) - fconvert.t(*(eax_19 - 0x70))
00429ecd        *(eax_19 + 0x20) = fconvert.s(fconvert.t(*(eax_19 + 0x30)) - fconvert.t(*(eax_19 - 0x78)))
00429ecf        *(eax_19 + 0x24) = var_8c_1
00429eda        *(eax_19 + 0x28) = fconvert.s(x87_r7_38)
00429ee4        normalize_vector(&self->primary_samples->transform.basis_forward + i_2)
00429eee        struct Vec3* primary_right = i_2 + self->primary_samples
00429ef9        cross_vectors(primary_right, primary_right + 0x10, primary_right + 0x20)
00429f0f        __builtin_memcpy(self->secondary_samples + i_2, i_2 + self->primary_samples, 0x40)
00429f14        struct Vec3* primary_up_reloaded = &self->primary_samples->transform.basis_up + i_2
00429f2c        float var_64_1 = fconvert.s(fconvert.t(primary_up_reloaded->y) * fconvert.t(0.49000001f))
00429f39        struct Vec3* secondary_position = &self->secondary_samples->transform.position + i_2
00429f41        i_2 += 0xa8
00429f4e        var_9c_2 += 1
00429f52        float var_60_1 = fconvert.s(fconvert.t(primary_up_reloaded->z) * fconvert.t(0.49000001f))
00429f58        secondary_position->x = fconvert.s(fconvert.t(primary_up_reloaded->x) * fconvert.t(0.49000001f) + fconvert.t(secondary_position->x))
00429f61        secondary_position->y = fconvert.s(fconvert.t(var_64_1) + fconvert.t(secondary_position->y))
00429f6b        secondary_position->z = fconvert.s(fconvert.t(var_60_1) + fconvert.t(secondary_position->z))
00429f77        int32_t i_3 = 0
00429f7c        if (self->segment_count - 1 s> 0)
00429f82        void* esi_2 = nullptr
00429f84        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00429fa8        float var_8c_2 = fconvert.s(fconvert.t(*(esi_2 + primary_samples_2 + 0xdc)) - fconvert.t(*(&primary_samples_2->transform.position.y + esi_2)))
00429faf        long double x87_r7_53 = fconvert.t(*(esi_2 + primary_samples_2 + 0xe0)) - fconvert.t(*(&primary_samples_2->transform.position.z + esi_2))
00429fb6        *(&primary_samples_2->delta_dir_to_next + esi_2) = fconvert.s(fconvert.t(*(esi_2 + primary_samples_2 + 0xd8)) - fconvert.t(*(&primary_samples_2->transform.position + esi_2)))
00429fb8        *(&primary_samples_2->delta_dir_to_next.y + esi_2) = var_8c_2
00429fc3        *(&primary_samples_2->delta_dir_to_next.z + esi_2) = fconvert.s(x87_r7_53)
00429fd8        *(&self->primary_samples->delta_length + esi_2) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + esi_2))
00429fdf        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042a003        float var_7c_1 = fconvert.s(fconvert.t(*(secondary_samples_1 + esi_2 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + esi_2)))
0042a00a        long double x87_r7_60 = fconvert.t(*(secondary_samples_1 + esi_2 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + esi_2))
0042a011        *(&secondary_samples_1->delta_dir_to_next + esi_2) = fconvert.s(fconvert.t(*(secondary_samples_1 + esi_2 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + esi_2)))
0042a013        *(&secondary_samples_1->delta_dir_to_next.y + esi_2) = var_7c_1
0042a01e        *(&secondary_samples_1->delta_dir_to_next.z + esi_2) = fconvert.s(x87_r7_60)
0042a033        i_3 += 1
0042a034        *(&self->secondary_samples->delta_length + esi_2) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + esi_2))
0042a03e        esi_2 += 0xa8
0042a047        do while (i_3 s< self->segment_count - 1)
0042a077        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
0042a08b        primary_terminal_delta->x = 0
0042a099        primary_terminal_delta->y = 0f
0042a09c        primary_terminal_delta->z = 1f
0042a0ae        int32_t var_88_3 = 0x3f800000
0042a0ba        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042a0d0        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
0042a0d8        secondary_terminal_delta->x = 0
0042a0de        secondary_terminal_delta->y = 0f
0042a0e3        secondary_terminal_delta->z = 1f
0042a0f8        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042a10b        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042a11d        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042a122        struct Object* object = self->bod.object
0042a129        struct ObjectFaceQuad* facequads = object->facequads
0042a12c        struct Vec3* vertices = object->vertices
0042a133        struct TransformMatrix transform
0042a133        set_matrix_identity(&transform)
0042a13b        int32_t i_4 = 0
0042a13f        if (self->segment_count s>= 0)
0042a145        void* eax_46 = nullptr
0042a147        void* var_84_1 = nullptr
0042a14b        uint32_t width_cells = self->width_cells
0042a14e        int32_t ebx = 0
0042a152        int32_t var_9c_3 = 0
0042a156        uint32_t width_cells_1 = width_cells
0042a15a        if (width_cells s>= 0)
0042a16d        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042a176        long double x87_r7_63 = float.t(var_9c_3) - float.t(width_cells_1) * fconvert.t(0.5f)
0042a178        struct Vec3* vertex
0042a178        float edx_36
0042a178        if (i_4 == self->segment_count)
0042a1ce        void* eax_52 = eax_46 + primary_samples_3
0042a224        float var_7c_2 = fconvert.s(fconvert.t(*(eax_52 - 0x74)) + fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(*(eax_52 - 0xa4)))))
0042a22c        long double x87_r6_47 = fconvert.t(fconvert.s(fconvert.t(*(eax_52 - 0x70)) + fconvert.t(1f))) + x87_r7_63 * fconvert.t(*(eax_52 - 0xa0))
0042a22e        vertex = &vertices[(width_cells + 1) * i_4 + ebx]
0042a235        vertex->x = fconvert.s(fconvert.t(*(eax_52 - 0x78)) + fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(*(eax_52 - 0xa8)))))
0042a23b        edx_36 = fconvert.s(x87_r6_47)
0042a23f        vertex->y = var_7c_2
0042a17a        struct PathTemplateSample* primary_mesh_sample = eax_46 + primary_samples_3
0042a1a6        float var_8c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0042a1b3        float var_88_4 = fconvert.s(x87_r7_63 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0042a1bc        vertex = &vertices[(width_cells + 1) * i_4 + ebx]
0042a1c3        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_63 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0042a1c5        edx_36 = var_88_4
0042a1c9        vertex->y = var_8c_3
0042a244        vertex->z = edx_36
0042a24c        int32_t i_6 = i_4 - 1
0042a24f        if (i_4 != self->segment_count)
0042a251        i_6 = i_4
0042a288        compute_kind42_attachment_transform(self, (&self->primary_samples->special_scalar)[i_6 * 0x2a], vertices[(self->width_cells + 1) * i_4 + ebx].x, 0f, &transform, &out_angle)
0042a29a        if (var_84_1 s> 0xa8 && i_4 != self->segment_count)
0042a2af        vertices[(self->width_cells + 1) * i_4 + ebx].x = fconvert.s(fconvert.t(transform.position.x))
0042a2c5        vertices[(self->width_cells + 1) * i_4 + ebx].y = fconvert.s(fconvert.t(transform.position.y))
0042a2c9        width_cells = self->width_cells
0042a2cc        eax_46 = var_84_1
0042a2d0        ebx += 1
0042a2d1        width_cells_1 = width_cells
0042a2d7        var_9c_3 = ebx
0042a2db        do while (ebx s<= width_cells)
0042a2e4        i_4 += 1
0042a2e5        eax_46 += 0xa8
0042a2ec        var_84_1 = eax_46
0042a2f0        do while (i_4 s<= self->segment_count)
0042a2f9        int32_t i_5 = 0
0042a2fd        if (self->segment_count s> 0)
0042a306        int32_t j = 0
0042a30a        int32_t j_1 = 0
0042a30e        if (self->width_cells s> 0)
0042a316        int32_t eax_79 = i_5 & 0x80000007
0042a31b        if (eax_79 s< 0)
0042a321        eax_79 = ((eax_79 - 1) | 0xfffffff8) + 1
0042a335        float var_84_2 = fconvert.s(float.t(eax_79) * fconvert.t(0.125f))
0042a343        float var_94_2 = fconvert.s(float.t(eax_79 + 1) * fconvert.t(0.125f))
0042a34e        int32_t ecx_52 = 0
0042a354        int32_t var_70_1 = 0
0042a35e        float var_9c_4 = fconvert.s(float.t(j_1) * fconvert.t(0.125f))
0042a36c        float var_74_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042a380        while (true)
0042a380        int32_t eax_86 = ecx_52 + ((self->width_cells * i_5 + j) << 1)
0042a383        if (ecx_52 != 0)
0042a444        struct ObjectFaceQuad* facequads_1 = facequads
0042a44f        struct ObjectFaceQuad* face_second = &facequads_1[eax_86]
0042a452        __builtin_memset(face_second, 0, 2)
0042a457        ecx_52.w = self->width_cells.w
0042a45b        ecx_52.w += 1
0042a464        face_second->vertex_0 = ecx_52.w * i_5.w + j.w + 1
0042a468        facequads_1.w = self->width_cells.w
0042a46c        facequads_1.w += 1
0042a473        face_second->vertex_1 = facequads_1.w * i_5.w + j.w
0042a485        face_second->vertex_2 = (self->width_cells.w + 1) * (i_5.w + 1) + j.w
0042a49d        face_second->vertex_3 = (self->width_cells.w + 1) * (i_5.w + 1) + j.w + 1
0042a4a1        char* texture_path_1
0042a4a1        if (((j.b ^ i_5.b) & 1) != 0)
0042a53a        texture_path_1 = texture_b
0042a4ae        texture_path_1 = texture_b
0042a4c1        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0042a4c8        face_second->uv[0].u = var_74_1
0042a4cb        face_second->uv[0].v = var_84_2
0042a4d0        face_second->uv[1].u = var_9c_4
0042a4d9        face_second->uv[1].v = var_84_2
0042a4e0        face_second->uv[2].u = var_9c_4
0042a4e3        face_second->uv[2].v = var_94_2
0042a4e8        face_second->uv[3].u = var_74_1
0042a4eb        face_second->uv[3].v = var_94_2
0042a390        int32_t ecx_54 = eax_86 * 0x30
0042a397        struct ObjectFaceQuad* face_first = ecx_54 + facequads
0042a39a        __builtin_memset(face_first, 0, 2)
0042a39f        eax_86.w = self->width_cells.w
0042a3a3        eax_86.w += 1
0042a3aa        face_first->vertex_0 = eax_86.w * i_5.w + j.w
0042a3ae        ecx_54.w = self->width_cells.w
0042a3b2        ecx_54.w += 1
0042a3be        face_first->vertex_1 = ecx_54.w * i_5.w + j.w + 1
0042a3cf        face_first->vertex_2 = (self->width_cells.w + 1) * (i_5.w + 1) + j.w + 1
0042a3e5        face_first->vertex_3 = (self->width_cells.w + 1) * (i_5.w + 1) + j.w
0042a3e9        char* texture_path
0042a3e9        if (((j.b ^ i_5.b) & 1) != 0)
0042a43e        texture_path = texture_a
0042a3f2        texture_path = texture_a
0042a405        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0042a40c        face_first->uv[0].u = var_9c_4
0042a40f        face_first->uv[0].v = var_84_2
0042a414        face_first->uv[1].u = var_74_1
0042a41d        face_first->uv[1].v = var_84_2
0042a424        face_first->uv[2].u = var_74_1
0042a427        face_first->uv[2].v = var_94_2
0042a42c        face_first->uv[3].u = var_9c_4
0042a42f        face_first->uv[3].v = var_94_2
0042a4f3        bool cond:13_1 = var_70_1 + 1 s< 2
0042a4f6        var_70_1 += 1
0042a4fa        if (not(cond:13_1))
0042a4fa        break
0042a372        ecx_52 = var_70_1
0042a500        j += 1
0042a509        j_1 = j
0042a50d        do while (j s< self->width_cells)
0042a516        i_5 += 1
0042a519        do while (i_5 s< self->segment_count)
0042a521        finalize_path_template(self)
0042a530        return
