/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cage2_path_template_pair @ 0x42e720 */

0042e72d        int32_t i_3 = 0
0042e734        self->kind = PATH_TEMPLATE_KIND_DETOUR
0042e73b        self->is_mirrored_x = 0
0042e73f        self->side_exit_mode = 0
0042e742        self->width_cells = width_cells_
0042e745        self->width_or_scale = 1f
0042e748        self->segment_count = 0x16
0042e74f        self->segment_count_f = 22f
0042e756        allocate_path_template_samples(self)
0042e75b        long double x87_r7 = float.t(self->width_cells)
0042e75e        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042e761        self->has_entry_mesh_transition = 0
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
0042e869        float terminal_center_x = self->primary_samples->__offset(0xe58).d
0042e86f        self->secondary_samples->__offset(0xdf8).d = terminal_center_x
0042e878        width_cells_ = 0
0042e87c        self->secondary_samples->__offset(0xdfc).d = 0x3efae148
0042e885        self->secondary_samples->__offset(0xe00).d = 0x41a80000
0042e88b        void* i = 0xa8
0042eb5f        while (i s< 0xdc8)
0042e890        long double x87_r7_6 = float.t(width_cells_)
0042e894        struct PathTemplateSample* primary_samples_7 = self->primary_samples
0042e897        float terminal_center_x_1 = terminal_center_x
0042e8a0        float var_48_1 = fconvert.s(x87_r7_6 * fconvert.t(0.314159274f))
0042e8bb        *(&primary_samples_7->center_x + i) = fconvert.s(cosine(fconvert.s(x87_r7_6 * fconvert.t(0.471238911f))) * fconvert.t(primary_samples_7->center_x))
0042e8c5        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0042e8cf        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0042e8d9        *(&self->primary_samples->special_scalar + i) = 0
0042e8e3        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042e8f3        set_matrix_identity(self->primary_samples + i)
0042e8f8        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042e905        *(&primary_samples_5->transform.position + i) = *(&primary_samples_5->center_x + i)
0042e90f        int32_t width_cells_2 = width_cells_ + 1
0042e914        long double x87_r7_10 = float.t(width_cells_2)
0042e918        *(&self->primary_samples->transform.position.y + i) = 0
0042e923        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_10)
0042e92e        set_matrix_identity(i + self->secondary_samples)
0042e946        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0042e95a        *(&self->secondary_samples->transform.position.y + i) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + i)) + fconvert.t(0.49000001f))
0042e965        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_10)))
0042e969        if (i s<= 0xa8)
0042eb37        set_matrix_rotation_identity(self->primary_samples + i - 0xa8)
0042eb46        set_matrix_rotation_identity(i + self->secondary_samples - 0xa8)
0042e986        struct Vec3* primary_up = self->primary_samples + i - 0x98
0042e999        primary_up->x = 0
0042e99f        primary_up->y = 1f
0042e9a2        primary_up->z = 0f
0042e9a5        struct PathTemplateSample* primary_samples_6 = self->primary_samples
0042e9c9        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_6->transform.position.y + i)) - fconvert.t(*(primary_samples_6 + i - 0x74)))
0042e9d3        long double x87_r7_19 = fconvert.t(*(&primary_samples_6->transform.position.z + i)) - fconvert.t(*(primary_samples_6 + i - 0x70))
0042e9da        *(primary_samples_6 + i - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_6->transform.position + i)) - fconvert.t(*(primary_samples_6 + i - 0x78)))
0042e9dc        *(primary_samples_6 + i - 0x84) = var_2c_1
0042e9e7        *(primary_samples_6 + i - 0x80) = fconvert.s(x87_r7_19)
0042e9f4        normalize_vector(self->primary_samples + i - 0x88)
0042e9fc        struct PathTemplateSample* primary_sample_cursor_reloaded = self->primary_samples + i
0042ea14        cross_vectors(primary_sample_cursor_reloaded - 0xa8, primary_sample_cursor_reloaded - 0x98, primary_sample_cursor_reloaded - 0x88)
0042ea21        void* ebp_1 = self->primary_samples + i
0042ea47        rotate_matrix_local_z(ebp_1 - 0xa8, fconvert.s((fconvert.t(1f) - cosine(var_48_1)) * fconvert.t(0.5f) * fconvert.t(*(ebp_1 - 0x18)) * fconvert.t(0.392699093f)))
0042ea63        struct Vec3* secondary_up = i + self->secondary_samples - 0x98
0042ea76        secondary_up->x = 0
0042ea7c        secondary_up->y = 1f
0042ea7f        secondary_up->z = 0f
0042ea82        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042eaa6        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + i)) - fconvert.t(*(i + secondary_samples - 0x74)))
0042eab0        long double x87_r7_32 = fconvert.t(*(&secondary_samples->transform.position.z + i)) - fconvert.t(*(i + secondary_samples - 0x70))
0042eab7        *(i + secondary_samples - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + i)) - fconvert.t(*(i + secondary_samples - 0x78)))
0042eac1        *(i + secondary_samples - 0x84) = var_14_1
0042eac4        *(i + secondary_samples - 0x80) = fconvert.s(x87_r7_32)
0042ead1        normalize_vector(i + self->secondary_samples - 0x88)
0042ead9        struct PathTemplateSample* secondary_sample_cursor_reloaded = self->secondary_samples + i
0042eaf1        cross_vectors(secondary_sample_cursor_reloaded - 0xa8, secondary_sample_cursor_reloaded - 0x98, secondary_sample_cursor_reloaded - 0x88)
0042eb00        long double x87_r7_36 = fconvert.t(1f) - cosine(var_48_1)
0042eb26        rotate_matrix_local_z(i + self->secondary_samples - 0xa8, fconvert.s(x87_r7_36 * fconvert.t(0.5f) * fconvert.t(*(self->primary_samples + i - 0x18)) * fconvert.t(0.392699093f)))
0042eb4f        i += 0xa8
0042eb5b        width_cells_ = width_cells_2
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
0042ec68        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
0042ec7c        primary_terminal_delta->x = 0
0042ec8a        primary_terminal_delta->y = 0f
0042ec8d        primary_terminal_delta->z = 1f
0042ec9f        int32_t var_10_3 = 0x3f800000
0042ecab        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ecc1        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
0042ecc9        secondary_terminal_delta->x = 0
0042eccf        secondary_terminal_delta->y = 0f
0042ecd4        secondary_terminal_delta->z = 1f
0042ece9        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042ecfc        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042ed0e        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042ed13        struct Object* object = self->bod.object
0042ed16        struct ObjectFaceQuad* facequads = object->facequads
0042ed19        struct Vec3* vertices = object->vertices
0042ed23        int32_t i_2 = 0
0042ed27        struct Vec3* vertices_1 = vertices
0042ed2b        if (self->segment_count s>= 0)
0042ed31        uint32_t width_cells = self->width_cells
0042ed34        int32_t width_cells_3 = 0
0042ed38        width_cells_ = 0
0042ed3c        uint32_t width_cells_1 = width_cells
0042ed40        if (width_cells s>= 0)
0042ed53        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042ed5c        long double x87_r7_55 = float.t(width_cells_) - float.t(width_cells_1) * fconvert.t(0.5f)
0042ed5e        struct Vec3* vertex
0042ed5e        float ecx_64
0042ed5e        if (i_2 == self->segment_count)
0042edb5        void* eax_50 = primary_samples_2 + i_3
0042edc6        vertices = vertices_1
0042ee0b        float var_20_2 = fconvert.s(fconvert.t(*(eax_50 - 0x74)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_50 - 0xa4)))))
0042ee13        long double x87_r6_22 = fconvert.t(fconvert.s(fconvert.t(*(eax_50 - 0x70)) + fconvert.t(1f))) + x87_r7_55 * fconvert.t(*(eax_50 - 0xa0))
0042ee15        vertex = &vertices[(width_cells + 1) * i_2 + width_cells_3]
0042ee1d        vertex->x = fconvert.s(fconvert.t(*(eax_50 - 0x78)) + fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(*(eax_50 - 0xa8)))))
0042ee27        vertex->y = var_20_2
0042ee2a        ecx_64 = fconvert.s(x87_r6_22)
0042ed60        struct PathTemplateSample* primary_mesh_sample = primary_samples_2 + i_3
0042ed88        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0042ed95        float var_10_4 = fconvert.s(x87_r7_55 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0042ed9e        vertex = &vertices[(width_cells + 1) * i_2 + width_cells_3]
0042eda6        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_55 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0042edac        vertex->y = var_14_3
0042edaf        ecx_64 = var_10_4
0042ee30        vertex->z = ecx_64
0042ee33        width_cells = self->width_cells
0042ee36        width_cells_3 += 1
0042ee37        width_cells_1 = width_cells
0042ee3d        width_cells_ = width_cells_3
0042ee41        do while (width_cells_3 s<= width_cells)
0042ee4a        i_2 += 1
0042ee4b        i_3 += 0xa8
0042ee53        do while (i_2 s<= self->segment_count)
0042ee59        i_3 = 0
0042ee60        if (self->segment_count s> 0)
0042ee69        int32_t j = 0
0042ee6d        width_cells_ = 0
0042ee71        if (self->width_cells s> 0)
0042ee79        int32_t eax_58 = i_3 & 0x80000007
0042ee7e        if (eax_58 s< 0)
0042ee84        eax_58 = ((eax_58 - 1) | 0xfffffff8) + 1
0042ee98        float var_54_1 = fconvert.s(float.t(eax_58) * fconvert.t(0.125f))
0042eea6        float var_4c_1 = fconvert.s(float.t(eax_58 + 1) * fconvert.t(0.125f))
0042eeb1        int32_t ecx_68 = 0
0042eeb7        int32_t var_48_2 = 0
0042eec1        width_cells_ = fconvert.s(float.t(width_cells_) * fconvert.t(0.125f))
0042eecf        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042eee3        while (true)
0042eee3        int32_t eax_65 = ecx_68 + ((self->width_cells * i_3 + j) << 1)
0042eee6        if (ecx_68 != 0)
0042efa2        struct ObjectFaceQuad* facequads_1 = facequads
0042efad        struct ObjectFaceQuad* face_second = &facequads_1[eax_65]
0042efb0        __builtin_memset(face_second, 0, 2)
0042efb6        ecx_68.w = self->width_cells.w
0042efba        ecx_68.w += 1
0042efc3        face_second->vertex_0 = ecx_68.w * i_3.w + j.w + 1
0042efc7        facequads_1.w = self->width_cells.w
0042efcb        facequads_1.w += 1
0042efd2        face_second->vertex_1 = facequads_1.w * i_3.w + j.w
0042efe4        face_second->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042effc        face_second->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042f000        char* texture_path_1
0042f000        if (((j.b ^ i_3.b) & 1) != 0)
0042f090        texture_path_1 = texture_b
0042f00a        texture_path_1 = texture_b
0042f01d        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0042f024        face_second->uv[0].u = var_50_1
0042f027        face_second->uv[0].v = var_54_1
0042f02c        face_second->uv[1].u = width_cells_
0042f035        face_second->uv[1].v = var_54_1
0042f03c        face_second->uv[2].u = width_cells_
0042f03f        face_second->uv[2].v = var_4c_1
0042f044        face_second->uv[3].u = var_50_1
0042f047        face_second->uv[3].v = var_4c_1
0042eef3        int32_t ecx_70 = eax_65 * 0x30
0042eefa        struct ObjectFaceQuad* face_first = ecx_70 + facequads
0042eefd        __builtin_memset(face_first, 0, 2)
0042ef03        eax_65.w = self->width_cells.w
0042ef07        eax_65.w += 1
0042ef0e        face_first->vertex_0 = eax_65.w * i_3.w + j.w
0042ef12        ecx_70.w = self->width_cells.w
0042ef16        ecx_70.w += 1
0042ef22        face_first->vertex_1 = ecx_70.w * i_3.w + j.w + 1
0042ef33        face_first->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0042ef49        face_first->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042ef4d        char* texture_path
0042ef4d        if (((j.b ^ i_3.b) & 1) != 0)
0042ef9c        texture_path = texture_a
0042ef53        texture_path = texture_a
0042ef66        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0042ef6d        face_first->uv[0].u = width_cells_
0042ef70        face_first->uv[0].v = var_54_1
0042ef75        face_first->uv[1].u = var_50_1
0042ef7e        face_first->uv[1].v = var_54_1
0042ef85        face_first->uv[2].u = var_50_1
0042ef88        face_first->uv[2].v = var_4c_1
0042ef8d        face_first->uv[3].u = width_cells_
0042ef90        face_first->uv[3].v = var_4c_1
0042f04f        bool cond:11_1 = var_48_2 + 1 s< 2
0042f052        var_48_2 += 1
0042f056        if (not(cond:11_1))
0042f056        break
0042eed5        ecx_68 = var_48_2
0042f05c        j += 1
0042f065        width_cells_ = j
0042f069        do while (j s< self->width_cells)
0042f072        i_3 += 1
0042f075        do while (i_3 s< self->segment_count)
0042f07d        finalize_path_template(self)
0042f089        return
