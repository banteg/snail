/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_hill_valley_path_template_pair @ 0x42d570 */

0042d580        int32_t i_2 = 0
0042d583        self->kind = PATH_TEMPLATE_KIND_FAMILY_10
0042d58a        self->is_mirrored_x = 0
0042d58e        self->side_exit_mode = 0
0042d591        self->width_cells = width_cells_
0042d594        int16_t x87control
0042d594        int32_t eax_1 = ftol(x87control, fconvert.t(length))
0042d5aa        self->width_or_scale = 1f
0042d5b1        self->segment_count = eax_1 + 2
0042d5b8        self->segment_count_f = fconvert.s(float.t(eax_1 + 2))
0042d5bb        allocate_path_template_samples(self)
0042d5c4        self->has_entry_mesh_transition = 0
0042d5cc        if (centered == 0)
0042d5eb        self->primary_samples->center_x = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
0042d5d1        self->primary_samples->center_x = 0f
0042d5f4        self->primary_samples->rotation_scalar_98 = 0f
0042d5fd        self->primary_samples->rotation_scalar_94 = 0f
0042d606        self->primary_samples->special_scalar = 0f
0042d60f        self->primary_samples->lateral_scale = 1f
0042d618        set_matrix_identity(self->primary_samples)
0042d61d        struct PathTemplateSample* primary_seed_sample = self->primary_samples
0042d626        primary_seed_sample->transform.position.x = primary_seed_sample->center_x
0042d62c        self->primary_samples->transform.position.y = 0f
0042d632        self->primary_samples->transform.position.z = 0f
0042d638        set_matrix_identity(self->secondary_samples)
0042d649        self->secondary_samples->transform.position.x = self->primary_samples->center_x
0042d653        self->secondary_samples->transform.position.y = 0.49000001f
0042d65d        bool cond:0 = centered == 0
0042d661        self->secondary_samples->transform.position.z = 0f
0042d664        centered.d = eax_1 + 1
0042d668        int32_t edi_1 = (eax_1 + 1) << 3
0042d66f        int32_t edi_4
0042d66f        if (cond:0)
0042d696        edi_4 = (edi_1 - (eax_1 + 1)) * 0x18
0042d69f        *(&self->primary_samples->center_x + edi_4) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
0042d679        edi_4 = (edi_1 - (eax_1 + 1)) * 0x18
0042d67c        *(&self->primary_samples->center_x + edi_4) = 0
0042d6a9        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0042d6b3        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0042d6bd        *(&self->primary_samples->special_scalar + edi_4) = 0
0042d6c9        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0042d6d5        set_matrix_identity(edi_4 + self->primary_samples)
0042d6dd        void* eax_14 = self->primary_samples + edi_4
0042d6df        long double x87_r7_8 = float.t(centered.d)
0042d6e9        *(eax_14 + 0x30) = *(eax_14 + 0x90)
0042d6ef        centered.d = fconvert.s(x87_r7_8)
0042d6f3        *(&self->primary_samples->transform.position.y + edi_4) = 0
0042d6fc        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_8)
0042d703        set_matrix_identity(edi_4 + self->secondary_samples)
0042d70e        long double x87_r7_9 = fconvert.t(centered.d)
0042d719        int32_t ebp_1 = 0
0042d71b        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
0042d726        centered.d = 0
0042d72a        *(&self->secondary_samples->transform.position.y + edi_4) = 0x3efae148
0042d737        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_9)
0042d73b        if (eax_1 s> 0)
0042d745        void* edi_7 = 0xa8
0042d752        struct PathTemplateSample* primary_samples = self->primary_samples
0042d761        *(&primary_samples->center_x + edi_7) = primary_samples->center_x
0042d76f        *(&self->primary_samples->rotation_scalar_98 + edi_7) = 0
0042d779        *(&self->primary_samples->rotation_scalar_94 + edi_7) = 0
0042d783        *(&self->primary_samples->special_scalar + edi_7) = 0
0042d78f        *(&self->primary_samples->lateral_scale + edi_7) = 0x3f800000
0042d79f        centered.d = fconvert.s(float.t(0) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(float.t(eax_1))))
0042d7a3        set_matrix_identity(edi_7 + self->primary_samples)
0042d7af        void* eax_20 = self->primary_samples + edi_7
0042d7b8        *(eax_20 + 0x30) = *(eax_20 + 0x90)
0042d7cc        ebp_1 += 1
0042d7db        *(&self->primary_samples->transform.position.y + edi_7) = fconvert.s((fconvert.t(1f) - cosine(0f)) * fconvert.t(0.5f) * fconvert.t(height))
0042d7df        long double x87_r7_18 = float.t(ebp_1)
0042d7ea        *(&self->primary_samples->transform.position.z + edi_7) = fconvert.s(x87_r7_18)
0042d7f3        set_matrix_identity(self->secondary_samples + edi_7)
0042d80a        *(&self->secondary_samples->transform.position + edi_7) = *(&self->primary_samples->center_x + edi_7)
0042d835        *(&self->secondary_samples->transform.position.y + edi_7) = fconvert.s((fconvert.t(1f) - cosine(0f)) * fconvert.t(0.5f) * fconvert.t(height) + fconvert.t(0.49000001f))
0042d840        *(&self->secondary_samples->transform.position.z + edi_7) = fconvert.s(fconvert.t(fconvert.s(x87_r7_18)))
0042d844        if (edi_7 s<= 0xa8)
0042d9a7        set_matrix_rotation_identity(edi_7 + self->primary_samples - 0xa8)
0042d9b6        set_matrix_rotation_identity(self->secondary_samples + edi_7 - 0xa8)
0042d861        struct Vec3* primary_right = edi_7 + self->primary_samples - 0xa8
0042d874        primary_right->x = 0x3f800000
0042d87a        primary_right->y = 0f
0042d87d        primary_right->z = 0f
0042d880        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042d8a4        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position.y + edi_7)) - fconvert.t(*(edi_7 + primary_samples_2 - 0x74)))
0042d8ae        long double x87_r7_30 = fconvert.t(*(&primary_samples_2->transform.position.z + edi_7)) - fconvert.t(*(edi_7 + primary_samples_2 - 0x70))
0042d8b5        *(edi_7 + primary_samples_2 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position + edi_7)) - fconvert.t(*(edi_7 + primary_samples_2 - 0x78)))
0042d8b7        *(edi_7 + primary_samples_2 - 0x84) = var_2c_1
0042d8c2        *(edi_7 + primary_samples_2 - 0x80) = fconvert.s(x87_r7_30)
0042d8cf        normalize_vector(edi_7 + self->primary_samples - 0x88)
0042d8d7        void* eax_27 = self->primary_samples + edi_7
0042d8ef        cross_vectors(eax_27 - 0x98, eax_27 - 0x88, eax_27 - 0xa8)
0042d90b        struct Vec3* secondary_right = self->secondary_samples + edi_7 - 0xa8
0042d91e        secondary_right->x = 0x3f800000
0042d924        secondary_right->y = 0f
0042d927        secondary_right->z = 0f
0042d92d        void* eax_30 = self->secondary_samples + edi_7
0042d94b        float var_14_1 = fconvert.s(fconvert.t(*(eax_30 + 0x34)) - fconvert.t(*(eax_30 - 0x74)))
0042d955        long double x87_r7_38 = fconvert.t(*(eax_30 + 0x38)) - fconvert.t(*(eax_30 - 0x70))
0042d95c        *(eax_30 - 0x88) = fconvert.s(fconvert.t(*(eax_30 + 0x30)) - fconvert.t(*(eax_30 - 0x78)))
0042d95e        *(eax_30 - 0x84) = var_14_1
0042d969        *(eax_30 - 0x80) = fconvert.s(x87_r7_38)
0042d976        normalize_vector(self->secondary_samples + edi_7 - 0x88)
0042d97e        void* eax_33 = self->secondary_samples + edi_7
0042d996        cross_vectors(eax_33 - 0x98, eax_33 - 0x88, eax_33 - 0xa8)
0042d9bf        edi_7 += 0xa8
0042d9c7        centered.d = ebp_1
0042d9cb        do while (ebp_1 s< eax_1)
0042d9d4        int32_t i = 0
0042d9d9        if (self->segment_count - 1 s> 0)
0042d9df        int32_t edi_8 = 0
0042d9e4        void* eax_37 = self->primary_samples + edi_8
0042da02        float var_14_2 = fconvert.s(fconvert.t(*(eax_37 + 0xdc)) - fconvert.t(*(eax_37 + 0x34)))
0042da09        long double x87_r7_46 = fconvert.t(*(eax_37 + 0xe0)) - fconvert.t(*(eax_37 + 0x38))
0042da10        *(eax_37 + 0x80) = fconvert.s(fconvert.t(*(eax_37 + 0xd8)) - fconvert.t(*(eax_37 + 0x30)))
0042da12        *(eax_37 + 0x84) = var_14_2
0042da1d        *(eax_37 + 0x88) = fconvert.s(x87_r7_46)
0042da32        *(&self->primary_samples->delta_length + edi_8) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_8))
0042da39        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042da5d        float var_20_1 = fconvert.s(fconvert.t(*(secondary_samples + edi_8 + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + edi_8)))
0042da64        long double x87_r7_53 = fconvert.t(*(secondary_samples + edi_8 + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + edi_8))
0042da6b        *(&secondary_samples->delta_dir_to_next + edi_8) = fconvert.s(fconvert.t(*(secondary_samples + edi_8 + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + edi_8)))
0042da6d        *(&secondary_samples->delta_dir_to_next.y + edi_8) = var_20_1
0042da78        *(&secondary_samples->delta_dir_to_next.z + edi_8) = fconvert.s(x87_r7_53)
0042da8d        i += 1
0042da8e        *(&self->secondary_samples->delta_length + edi_8) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_8))
0042da98        edi_8 += 0xa8
0042daa1        do while (i s< self->segment_count - 1)
0042dad1        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
0042dae5        primary_terminal_delta->x = 0
0042daf3        primary_terminal_delta->y = 0f
0042daf6        primary_terminal_delta->z = 1f
0042db08        int32_t var_10_3 = 0x3f800000
0042db14        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042db2a        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
0042db32        secondary_terminal_delta->x = 0
0042db38        secondary_terminal_delta->y = 0f
0042db3d        secondary_terminal_delta->z = 1f
0042db52        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042db65        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042db77        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042db7c        struct Object* object = self->bod.object
0042db7f        int32_t i_1 = 0
0042db81        struct Vec3* vertices = object->vertices
0042db84        struct ObjectFaceQuad* facequads = object->facequads
0042db8a        width_cells_ = vertices
0042db94        if (self->segment_count s>= 0)
0042db9a        uint32_t width_cells = self->width_cells
0042db9d        int32_t edi_9 = 0
0042dba1        centered.d = 0
0042dba5        height = width_cells
0042dba9        if (width_cells s>= 0)
0042dbbc        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042dbc5        long double x87_r7_56 = float.t(centered.d) - float.t(height) * fconvert.t(0.5f)
0042dbc7        struct Vec3* vertex
0042dbc7        float ecx_62
0042dbc7        if (i_1 == self->segment_count)
0042dc1e        void* eax_63 = primary_samples_1 + i_2
0042dc2f        vertices = width_cells_
0042dc74        float var_20_2 = fconvert.s(fconvert.t(*(eax_63 - 0x74)) + fconvert.t(fconvert.s(x87_r7_56 * fconvert.t(*(eax_63 - 0xa4)))))
0042dc7c        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_63 - 0x70)) + fconvert.t(1f))) + x87_r7_56 * fconvert.t(*(eax_63 - 0xa0))
0042dc7e        vertex = &vertices[(width_cells + 1) * i_1 + edi_9]
0042dc86        vertex->x = fconvert.s(fconvert.t(*(eax_63 - 0x78)) + fconvert.t(fconvert.s(x87_r7_56 * fconvert.t(*(eax_63 - 0xa8)))))
0042dc90        vertex->y = var_20_2
0042dc93        ecx_62 = fconvert.s(x87_r6_20)
0042dbc9        struct PathTemplateSample* primary_mesh_sample = primary_samples_1 + i_2
0042dbf1        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_56 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0042dbfe        float var_10_4 = fconvert.s(x87_r7_56 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0042dc07        vertex = &vertices[(width_cells + 1) * i_1 + edi_9]
0042dc0f        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_56 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0042dc15        vertex->y = var_14_3
0042dc18        ecx_62 = var_10_4
0042dc99        vertex->z = ecx_62
0042dc9c        width_cells = self->width_cells
0042dc9f        edi_9 += 1
0042dca0        height = width_cells
0042dca6        centered.d = edi_9
0042dcaa        do while (edi_9 s<= width_cells)
0042dcb3        i_1 += 1
0042dcb4        i_2 += 0xa8
0042dcbc        do while (i_1 s<= self->segment_count)
0042dcc2        i_2 = 0
0042dcc9        if (self->segment_count s> 0)
0042dcd2        int32_t j = 0
0042dcd6        centered.d = 0
0042dcda        if (self->width_cells s> 0)
0042dce2        float eax_71 = i_2 & 0x80000007
0042dce7        if (eax_71 s< 0)
0042dced        eax_71 = ((eax_71 i- 1) | 0xfffffff8) + 1
0042dd01        height = fconvert.s(float.t(eax_71) * fconvert.t(0.125f))
0042dd0f        length = fconvert.s(float.t(eax_71 i+ 1) * fconvert.t(0.125f))
0042dd1a        int32_t ecx_66 = 0
0042dd20        int32_t var_48_1 = 0
0042dd2a        centered.d = fconvert.s(float.t(centered.d) * fconvert.t(0.125f))
0042dd38        width_cells_ = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042dd4c        while (true)
0042dd4c        int32_t eax_78 = ecx_66 + ((self->width_cells * i_2 + j) << 1)
0042dd4f        if (ecx_66 != 0)
0042de0b        struct ObjectFaceQuad* facequads_1 = facequads
0042de16        struct ObjectFaceQuad* face_second = &facequads_1[eax_78]
0042de19        __builtin_memset(face_second, 0, 2)
0042de1f        ecx_66.w = self->width_cells.w
0042de23        ecx_66.w += 1
0042de2c        face_second->vertex_0 = ecx_66.w * i_2.w + j.w + 1
0042de30        facequads_1.w = self->width_cells.w
0042de34        facequads_1.w += 1
0042de3b        face_second->vertex_1 = facequads_1.w * i_2.w + j.w
0042de4d        face_second->vertex_2 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0042de65        face_second->vertex_3 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0042de69        char* texture_path_1
0042de69        if (((j.b ^ i_2.b) & 1) != 0)
0042def9        texture_path_1 = texture_b
0042de73        texture_path_1 = texture_b
0042de82        int32_t edx_46 = centered.d
0042de86        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0042de8d        face_second->uv[0].u = width_cells_
0042de90        face_second->uv[0].v = height
0042de95        face_second->uv[1].u = edx_46
0042de9e        face_second->uv[1].v = height
0042dea5        face_second->uv[2].u = edx_46
0042dea8        face_second->uv[2].v = length
0042dead        face_second->uv[3].u = width_cells_
0042deb0        face_second->uv[3].v = length
0042dd5c        int32_t ecx_68 = eax_78 * 0x30
0042dd63        struct ObjectFaceQuad* face_first = ecx_68 + facequads
0042dd66        __builtin_memset(face_first, 0, 2)
0042dd6c        eax_78.w = self->width_cells.w
0042dd70        eax_78.w += 1
0042dd77        face_first->vertex_0 = eax_78.w * i_2.w + j.w
0042dd7b        ecx_68.w = self->width_cells.w
0042dd7f        ecx_68.w += 1
0042dd8b        face_first->vertex_1 = ecx_68.w * i_2.w + j.w + 1
0042dd9c        face_first->vertex_2 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0042ddb2        face_first->vertex_3 = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
0042ddb6        char* texture_path
0042ddb6        if (((j.b ^ i_2.b) & 1) != 0)
0042de05        texture_path = texture_a
0042ddbc        texture_path = texture_a
0042ddcf        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0042ddd6        face_first->uv[0].u = centered.d
0042ddd9        face_first->uv[0].v = height
0042ddde        face_first->uv[1].u = width_cells_
0042dde7        face_first->uv[1].v = height
0042ddee        face_first->uv[2].u = width_cells_
0042ddf1        face_first->uv[2].v = length
0042ddf6        face_first->uv[3].u = centered.d
0042ddf9        face_first->uv[3].v = length
0042deb8        bool cond:13_1 = var_48_1 + 1 s< 2
0042debb        var_48_1 += 1
0042debf        if (not(cond:13_1))
0042debf        break
0042dd3e        ecx_66 = var_48_1
0042dec5        j += 1
0042dece        centered.d = j
0042ded2        do while (j s< self->width_cells)
0042dedb        i_2 += 1
0042dede        do while (i_2 s< self->segment_count)
0042dee6        finalize_path_template(self)
0042def2        return
