/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_screw_path_template_pair @ 0x41eda0 */

0041edac        int32_t i_3 = 0
0041edb7        self->width_cells = width_cells_
0041edc4        self->kind = PATH_TEMPLATE_KIND_SCREW
0041edcf        self->is_mirrored_x = 0
0041edd3        self->side_exit_mode = 0
0041edd6        self->width_or_scale = 1f
0041edd9        self->segment_count = curve_source + 8
0041eddc        self->segment_count_f = fconvert.s(float.t(curve_source + 8))
0041eddf        allocate_path_template_samples(self)
0041ede4        self->has_entry_mesh_transition = 0
0041edea        width_cells_ = 0
0041edee        void* i = nullptr
0041ee9e        while (i s< 0x1f8)
0041edf3        *(&self->primary_samples->center_x + i) = 0x3f000000
0041ee01        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041ee0b        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041ee15        *(&self->primary_samples->special_scalar + i) = 0
0041ee1f        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041ee2b        set_matrix_identity(self->primary_samples + i)
0041ee30        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041ee33        long double x87_r7_1 = float.t(width_cells_)
0041ee45        *(&primary_samples_1->transform.position + i) = *(&primary_samples_1->center_x + i)
0041ee4b        *(&self->primary_samples->transform.position.y + i) = 0
0041ee52        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
0041ee5d        set_matrix_identity(i + self->secondary_samples)
0041ee73        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0041ee7a        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0041ee89        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
0041ee8d        i += 0xa8
0041ee9a        width_cells_ += 1
0041eead        int32_t width_cells_1 = curve_source + 3
0041eeb0        width_cells_ = width_cells_1
0041eec0        int32_t edi_3 = width_cells_1 * 0xa8
0041ef7a        struct TransformMatrix* transform
0041eecc        *(&self->primary_samples->center_x + edi_3) = 0xbf000000
0041eeda        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041eee4        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041eeee        *(&self->primary_samples->special_scalar + edi_3) = 0
0041eef8        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041ef08        set_matrix_identity(self->primary_samples + edi_3)
0041ef0d        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041ef10        long double x87_r7_3 = float.t(width_cells_)
0041ef22        *(&primary_samples_2->transform.position + edi_3) = *(&primary_samples_2->center_x + edi_3)
0041ef28        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041ef2f        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_3)
0041ef3a        set_matrix_identity(edi_3 + self->secondary_samples)
0041ef50        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0041ef5b        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0041ef66        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_3)))
0041ef6a        edi_3 += 0xa8
0041ef70        width_cells_1 += 1
0041ef71        transform = 0xfffffffd - curve_source + width_cells_1
0041ef73        width_cells_ = width_cells_1
0041ef7a        do while (transform s< 5)
0041ef84        int32_t width_cells_2 = 0
0041ef88        width_cells_ = 0
0041ef8c        if (curve_source s> 0)
0041ef96        void* edi_4 = 0x1f8
0041efa7        struct TransformMatrix* transform_1 = transform
0041efae        long double x87_r7_8 = float.t(width_cells_) * fconvert.t(6.28318548f) / fconvert.t(fconvert.s(float.t(curve_source)))
0041efb2        float var_4c_1 = fconvert.s(x87_r7_8)
0041efd0        *(&self->primary_samples->center_x + edi_4) = fconvert.s(cosine(fconvert.s(x87_r7_8 * fconvert.t(0.5f))) * fconvert.t(0.5f))
0041efde        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041efe8        *(&self->primary_samples->rotation_scalar_94 + edi_4) = fconvert.s(fconvert.t(var_4c_1))
0041eff2        *(&self->primary_samples->special_scalar + edi_4) = 0
0041effc        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041f00c        set_matrix_identity(self->primary_samples + edi_4)
0041f011        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041f025        long double x87_r7_13 = float.t(width_cells_2 + 3)
0041f029        *(&primary_samples_3->transform.position + edi_4) = *(&primary_samples_3->center_x + edi_4)
0041f033        *(&self->primary_samples->transform.position.y + edi_4) = 0
0041f03a        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
0041f045        set_matrix_identity(edi_4 + self->secondary_samples)
0041f04e        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0041f057        long double x87_r7_15 = sine(var_4c_1) * fconvert.t(0.49000001f)
0041f068        *(&self->secondary_samples->transform.position + edi_4) = fconvert.s(fconvert.t(*(&primary_samples_5->center_x + edi_4)) - x87_r7_15)
0041f083        *(&self->secondary_samples->transform.position.y + edi_4) = fconvert.s(cosine(var_4c_1) * fconvert.t(0.49000001f))
0041f08e        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0041f092        if (edi_4 s<= 0x1f8)
0041f212        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
0041f21a        transform = edi_4 + self->secondary_samples - 0xa8
0041f221        set_matrix_rotation_identity(transform)
0041f09e        float var_48_3 = fconvert.s(cosine(var_4c_1))
0041f0a3        long double st0_5 = sine(var_4c_1)
0041f0bd        struct Vec3* primary_up = self->primary_samples + edi_4 - 0x98
0041f0d3        primary_up->x = fconvert.s(fneg(st0_5))
0041f0d9        primary_up->y = var_48_3
0041f0dc        primary_up->z = 0f
0041f0e2        void* eax_26 = self->primary_samples + edi_4
0041f100        float var_2c_1 = fconvert.s(fconvert.t(*(eax_26 + 0x34)) - fconvert.t(*(eax_26 - 0x74)))
0041f10a        long double x87_r7_28 = fconvert.t(*(eax_26 + 0x38)) - fconvert.t(*(eax_26 - 0x70))
0041f111        *(eax_26 - 0x88) = fconvert.s(fconvert.t(*(eax_26 + 0x30)) - fconvert.t(*(eax_26 - 0x78)))
0041f113        *(eax_26 - 0x84) = var_2c_1
0041f11e        *(eax_26 - 0x80) = fconvert.s(x87_r7_28)
0041f12b        normalize_vector(self->primary_samples + edi_4 - 0x88)
0041f133        void* eax_29 = self->primary_samples + edi_4
0041f14b        cross_vectors(eax_29 - 0xa8, eax_29 - 0x98, eax_29 - 0x88)
0041f156        float var_48_4 = fconvert.s(cosine(var_4c_1))
0041f15b        long double st0_8 = sine(var_4c_1)
0041f175        struct Vec3* secondary_up = edi_4 + self->secondary_samples - 0x98
0041f18b        secondary_up->x = fconvert.s(fneg(st0_8))
0041f191        secondary_up->y = var_48_4
0041f194        secondary_up->z = 0f
0041f197        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041f1a2        void* eax_32 = edi_4 + secondary_samples
0041f1af        float var_14_1 = fconvert.s(fconvert.t(*(eax_32 + 0x34)) - fconvert.t(*(eax_32 - 0x74)))
0041f1b9        float var_10_1 = fconvert.s(fconvert.t(*(eax_32 + 0x38)) - fconvert.t(*(eax_32 - 0x70)))
0041f1ca        *(eax_32 - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + edi_4)) - fconvert.t(*(edi_4 + secondary_samples - 0x78)))
0041f1d0        *(eax_32 - 0x84) = var_14_1
0041f1d3        *(eax_32 - 0x80) = var_10_1
0041f1e0        normalize_vector(edi_4 + self->secondary_samples - 0x88)
0041f1ea        void* eax_35 = edi_4 + self->secondary_samples
0041f201        transform = cross_vectors(eax_35 - 0xa8, eax_35 - 0x98, eax_35 - 0x88)
0041f22e        width_cells_2 = width_cells_ + 1
0041f22f        edi_4 += 0xa8
0041f237        width_cells_ = width_cells_2
0041f23b        do while (width_cells_2 s< curve_source)
0041f241        i_3 = 0
0041f246        int32_t i_1 = 0
0041f24b        if (self->segment_count - 1 s> 0)
0041f251        void* edi_5 = nullptr
0041f253        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041f277        float var_14_2 = fconvert.s(fconvert.t(*(edi_5 + primary_samples_4 + 0xdc)) - fconvert.t(*(&primary_samples_4->transform.position.y + edi_5)))
0041f27e        long double x87_r7_47 = fconvert.t(*(edi_5 + primary_samples_4 + 0xe0)) - fconvert.t(*(&primary_samples_4->transform.position.z + edi_5))
0041f285        *(&primary_samples_4->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + primary_samples_4 + 0xd8)) - fconvert.t(*(&primary_samples_4->transform.position + edi_5)))
0041f287        *(&primary_samples_4->delta_dir_to_next.y + edi_5) = var_14_2
0041f292        *(&primary_samples_4->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_47)
0041f2a7        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041f2ae        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041f2d2        float var_20_2 = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_5)))
0041f2d9        long double x87_r7_54 = fconvert.t(*(edi_5 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_5))
0041f2e0        *(&secondary_samples_1->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_5)))
0041f2e2        *(&secondary_samples_1->delta_dir_to_next.y + edi_5) = var_20_2
0041f2ed        *(&secondary_samples_1->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_54)
0041f302        i_1 += 1
0041f303        *(&self->secondary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_5))
0041f30d        edi_5 += 0xa8
0041f316        do while (i_1 s< self->segment_count - 1)
0041f346        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
0041f35a        primary_terminal_delta->x = 0
0041f368        primary_terminal_delta->y = 0f
0041f36b        primary_terminal_delta->z = 1f
0041f37d        int32_t var_10_3 = 0x3f800000
0041f389        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041f39f        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
0041f3a7        secondary_terminal_delta->x = 0
0041f3ad        secondary_terminal_delta->y = 0f
0041f3b2        secondary_terminal_delta->z = 1f
0041f3c7        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041f3da        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0041f3ec        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0041f3f1        struct Object* object = self->bod.object
0041f3f4        int32_t i_2 = 0
0041f3f6        struct Vec3* vertices = object->vertices
0041f3f9        struct ObjectFaceQuad* facequads = object->facequads
0041f3ff        struct Vec3* vertices_1 = vertices
0041f409        if (self->segment_count s>= 0)
0041f40f        uint32_t width_cells = self->width_cells
0041f412        int32_t curve_source_1 = 0
0041f416        curve_source = 0
0041f41a        width_cells_ = width_cells
0041f41e        if (width_cells s>= 0)
0041f431        struct PathTemplateSample* primary_samples = self->primary_samples
0041f43a        long double x87_r7_57 = float.t(curve_source) - float.t(width_cells_) * fconvert.t(0.5f)
0041f43c        struct Vec3* vertex
0041f43c        float ecx_62
0041f43c        if (i_2 == self->segment_count)
0041f493        void* eax_64 = primary_samples + i_3
0041f4a4        vertices = vertices_1
0041f4e9        float var_20_3 = fconvert.s(fconvert.t(*(eax_64 - 0x74)) + fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(*(eax_64 - 0xa4)))))
0041f4f1        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_64 - 0x70)) + fconvert.t(1f))) + x87_r7_57 * fconvert.t(*(eax_64 - 0xa0))
0041f4f3        vertex = &vertices[(width_cells + 1) * i_2 + curve_source_1]
0041f4fb        vertex->x = fconvert.s(fconvert.t(*(eax_64 - 0x78)) + fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(*(eax_64 - 0xa8)))))
0041f505        vertex->y = var_20_3
0041f508        ecx_62 = fconvert.s(x87_r6_20)
0041f43e        struct PathTemplateSample* primary_mesh_sample = primary_samples + i_3
0041f466        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0041f473        float var_10_4 = fconvert.s(x87_r7_57 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0041f47c        vertex = &vertices[(width_cells + 1) * i_2 + curve_source_1]
0041f484        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_57 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0041f48a        vertex->y = var_14_3
0041f48d        ecx_62 = var_10_4
0041f50e        vertex->z = ecx_62
0041f511        width_cells = self->width_cells
0041f514        curve_source_1 += 1
0041f515        width_cells_ = width_cells
0041f51b        curve_source = curve_source_1
0041f51f        do while (curve_source_1 s<= width_cells)
0041f528        i_2 += 1
0041f529        i_3 += 0xa8
0041f531        do while (i_2 s<= self->segment_count)
0041f537        i_3 = 0
0041f53e        if (self->segment_count s> 0)
0041f547        int32_t j = 0
0041f54b        curve_source = 0
0041f54f        if (self->width_cells s> 0)
0041f557        int32_t eax_72 = i_3 & 0x80000007
0041f55c        if (eax_72 s< 0)
0041f562        eax_72 = ((eax_72 - 1) | 0xfffffff8) + 1
0041f576        width_cells_ = fconvert.s(float.t(eax_72) * fconvert.t(0.125f))
0041f584        float var_4c_2 = fconvert.s(float.t(eax_72 + 1) * fconvert.t(0.125f))
0041f58f        int32_t ecx_66 = 0
0041f595        int32_t var_48_5 = 0
0041f59f        curve_source = fconvert.s(float.t(curve_source) * fconvert.t(0.125f))
0041f5ad        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041f5bf        while (true)
0041f5c9        int32_t edx_37 = (ecx_66 + ((self->width_cells * i_3 + j) << 1)) * 0x30
0041f5ce        struct ObjectFaceQuad* face = edx_37 + facequads
0041f5d1        __builtin_memset(face, 0, 2)
0041f5d6        if (ecx_66 != 0)
0041f67c        edx_37.w = self->width_cells.w
0041f682        edx_37.w += 1
0041f68d        face->vertex_0 = edx_37.w * i_3.w + j.w + 1
0041f691        ecx_66.w = self->width_cells.w
0041f695        ecx_66.w += 1
0041f69f        face->vertex_1 = ecx_66.w * i_3.w + j.w
0041f6ae        face->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0041f6c5        face->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0041f6c9        char* texture_path_1
0041f6c9        if (((j.b ^ i_3.b) & 1) != 0)
0041f759        texture_path_1 = texture_b
0041f6d3        texture_path_1 = texture_b
0041f6e6        face->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0041f6ed        face->uv[0].u = var_50_1
0041f6f0        face->uv[0].v = width_cells_
0041f6f5        face->uv[1].u = curve_source
0041f6fe        face->uv[1].v = width_cells_
0041f705        face->uv[2].u = curve_source
0041f708        face->uv[2].v = var_4c_2
0041f70d        face->uv[3].u = var_50_1
0041f710        face->uv[3].v = var_4c_2
0041f5dc        ecx_66.w = self->width_cells.w
0041f5e2        ecx_66.w += 1
0041f5eb        face->vertex_0 = ecx_66.w * i_3.w + j.w
0041f5ef        edx_37.w = self->width_cells.w
0041f5f3        edx_37.w += 1
0041f5fc        face->vertex_1 = edx_37.w * i_3.w + j.w + 1
0041f610        face->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
0041f626        face->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0041f62a        char* texture_path
0041f62a        if (((j.b ^ i_3.b) & 1) != 0)
0041f679        texture_path = texture_a
0041f630        texture_path = texture_a
0041f643        face->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0041f64a        face->uv[0].u = curve_source
0041f64d        face->uv[0].v = width_cells_
0041f652        face->uv[1].u = var_50_1
0041f65b        face->uv[1].v = width_cells_
0041f662        face->uv[2].u = var_50_1
0041f665        face->uv[2].v = var_4c_2
0041f66a        face->uv[3].u = curve_source
0041f66d        face->uv[3].v = var_4c_2
0041f718        bool cond:13_1 = var_48_5 + 1 s< 2
0041f71b        var_48_5 += 1
0041f71f        if (not(cond:13_1))
0041f71f        break
0041f5b3        ecx_66 = var_48_5
0041f725        j += 1
0041f72e        curve_source = j
0041f732        do while (j s< self->width_cells)
0041f73b        i_3 += 1
0041f73e        do while (i_3 s< self->segment_count)
0041f746        finalize_path_template(self)
0041f752        return
