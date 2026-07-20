/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_wibble_path_template_pair @ 0x4289a0 */

004289b4        self->kind = PATH_TEMPLATE_KIND_WIBBLE
004289bb        self->is_mirrored_x = 0
004289bf        self->side_exit_mode = 0
004289c2        self->width_cells = width_cells_
004289c5        self->width_or_scale = 1f
004289c8        self->segment_count = 0x20
004289cf        self->segment_count_f = 32f
004289d6        allocate_path_template_samples(self)
004289db        long double x87_r7 = float.t(self->width_cells)
004289de        struct PathTemplateSample* primary_samples_3 = self->primary_samples
004289e1        self->has_entry_mesh_transition = 0
004289f4        primary_samples_3->center_x = fconvert.s(x87_r7 * fconvert.t(0.5f) - fconvert.t(4f))
004289fd        self->primary_samples->rotation_scalar_98 = 0f
00428a06        self->primary_samples->rotation_scalar_94 = 0f
00428a0f        self->primary_samples->special_scalar = 0f
00428a18        self->primary_samples->lateral_scale = 1f
00428a21        set_matrix_identity(self->primary_samples)
00428a26        struct PathTemplateSample* primary_seed_sample = self->primary_samples
00428a2f        primary_seed_sample->transform.position.x = primary_seed_sample->center_x
00428a35        self->primary_samples->transform.position.y = 0f
00428a3b        self->primary_samples->transform.position.z = 0f
00428a41        self->primary_samples->delta_length = 1f
00428a4a        set_matrix_identity(self->secondary_samples)
00428a5b        self->secondary_samples->transform.position.x = self->primary_samples->center_x
00428a61        self->secondary_samples->transform.position.y = 0.49000001f
00428a6b        self->secondary_samples->transform.position.z = 0f
00428a71        self->secondary_samples->delta_length = 1f
00428a89        self->primary_samples->__offset(0x14e8).d = fconvert.s(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
00428a92        self->primary_samples->__offset(0x14f0).d = 0
00428a9b        self->primary_samples->__offset(0x14ec).d = 0
00428aa4        self->primary_samples->__offset(0x14f8).d = 0
00428aad        self->primary_samples->__offset(0x14f4).d = 0x3f800000
00428abc        set_matrix_identity(&self->primary_samples[0x1f])
00428ac1        struct PathTemplateSample* primary_samples = self->primary_samples
00428acf        primary_samples->__offset(0x1488).d = primary_samples->__offset(0x14e8).d
00428ad8        self->primary_samples->__offset(0x148c).d = 0
00428ae1        self->primary_samples->__offset(0x1490).d = 0x41f80000
00428aea        self->primary_samples->__offset(0x14e4).d = 0x3f800000
00428af9        set_matrix_identity(&self->secondary_samples[0x1f])
00428b0a        self->secondary_samples->__offset(0x1488).d = self->primary_samples->__offset(0x14e8).d
00428b13        self->secondary_samples->__offset(0x148c).d = 0x3efae148
00428b20        self->secondary_samples->__offset(0x1490).d = 0x41f80000
00428b29        int32_t i = 0xa8
00428b2e        self->secondary_samples->__offset(0x14e4).d = 0x3f800000
00428b34        int32_t width_cells_3 = 0
00428b36        width_cells_ = 0
00428b42        long double x87_r7_6 = float.t(width_cells_)
00428b46        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00428b6f        *(&primary_samples_1->center_x + i) = fconvert.s((fconvert.t(primary_samples_1->__offset(0x14e8).d) - fconvert.t(primary_samples_1->center_x)) * x87_r7_6 * fconvert.t(0.0333333351f) + fconvert.t(primary_samples_1->center_x))
00428b7b        *(&self->primary_samples->rotation_scalar_98 + i) = 0
00428b85        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00428b8f        *(&self->primary_samples->special_scalar + i) = 0
00428b99        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
00428ba9        set_matrix_identity(self->primary_samples + i)
00428bba        *(&self->primary_samples->transform.position + i) = 0
00428bc1        *(&self->primary_samples->transform.position.z + i) = fconvert.s(float.t(width_cells_3 + 1))
00428bd2        *(&self->primary_samples->transform.position.y + i) = 0
00428bd6        float var_40_2 = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 * fconvert.t(0.209439516f))) * fconvert.t(3f))
00428bf2        float var_40_3 = fconvert.s(cosine(fconvert.s(sine(var_40_2) * fconvert.t(0.300000012f))))
00428c08        long double st0_4 = sine(fconvert.s(sine(var_40_2) * fconvert.t(0.300000012f)))
00428c20        struct Vec3* primary_up = &self->primary_samples->transform.basis_up + i
00428c2b        primary_up->x = fconvert.s(st0_4)
00428c31        primary_up->y = var_40_3
00428c34        primary_up->z = 0f
00428c37        struct PathTemplateSample* primary_samples_4 = self->primary_samples
00428c59        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position.y + i)) - fconvert.t(*(primary_samples_4 + i - 0x74)))
00428c60        long double x87_r7_22 = fconvert.t(*(&primary_samples_4->transform.position.z + i)) - fconvert.t(*(primary_samples_4 + i - 0x70))
00428c6a        *(&primary_samples_4->transform.basis_forward + i) = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position + i)) - fconvert.t(*(primary_samples_4 + i - 0x78)))
00428c6c        *(&primary_samples_4->transform.basis_forward.y + i) = var_2c_1
00428c77        *(&primary_samples_4->transform.basis_forward.z + i) = fconvert.s(x87_r7_22)
00428c81        normalize_vector(&self->primary_samples->transform.basis_forward + i)
00428c89        struct Vec3* primary_right = self->primary_samples + i
00428c95        cross_vectors(primary_right, primary_right + 0x10, primary_right + 0x20)
00428ca9        __builtin_memcpy(self->secondary_samples + i, self->primary_samples + i, 0x40)
00428cab        struct PathTemplateSample* primary_samples_5 = self->primary_samples
00428cb1        width_cells_3 += 1
00428cb9        long double x87_r7_26 = fconvert.t(*(&primary_samples_5->transform.basis_up + i)) * fconvert.t(0.49000001f)
00428cc7        width_cells_ = width_cells_3
00428cd1        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_5->transform.basis_up.y + i)) * fconvert.t(0.49000001f))
00428cd8        long double x87_r6_11 = fconvert.t(*(&primary_samples_5->transform.basis_up.z + i)) * fconvert.t(0.49000001f)
00428cde        struct Vec3* secondary_position = &self->secondary_samples->transform.position + i
00428ce2        i += 0xa8
00428cf4        secondary_position->x = fconvert.s(x87_r7_26 + fconvert.t(secondary_position->x))
00428cfd        secondary_position->y = fconvert.s(fconvert.t(var_20_1) + fconvert.t(secondary_position->y))
00428d07        secondary_position->z = fconvert.s(fconvert.t(fconvert.s(x87_r6_11)) + fconvert.t(secondary_position->z))
00428d0a        do while (i s< 0x1458)
00428d13        int32_t i_1 = 0
00428d18        if (self->segment_count - 1 s> 0)
00428d1e        int32_t esi_4 = 0
00428d20        struct PathTemplateSample* primary_samples_6 = self->primary_samples
00428d44        float var_2c_2 = fconvert.s(fconvert.t(*(primary_samples_6 + esi_4 + 0xdc)) - fconvert.t(*(&primary_samples_6->transform.position.y + esi_4)))
00428d4b        long double x87_r7_37 = fconvert.t(*(primary_samples_6 + esi_4 + 0xe0)) - fconvert.t(*(&primary_samples_6->transform.position.z + esi_4))
00428d52        *(&primary_samples_6->delta_dir_to_next + esi_4) = fconvert.s(fconvert.t(*(primary_samples_6 + esi_4 + 0xd8)) - fconvert.t(*(&primary_samples_6->transform.position + esi_4)))
00428d54        *(&primary_samples_6->delta_dir_to_next.y + esi_4) = var_2c_2
00428d5f        *(&primary_samples_6->delta_dir_to_next.z + esi_4) = fconvert.s(x87_r7_37)
00428d74        *(&self->primary_samples->delta_length + esi_4) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + esi_4))
00428d7b        struct PathTemplateSample* secondary_samples = self->secondary_samples
00428d9f        float var_38_2 = fconvert.s(fconvert.t(*(secondary_samples + esi_4 + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + esi_4)))
00428da6        long double x87_r7_44 = fconvert.t(*(secondary_samples + esi_4 + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + esi_4))
00428dad        *(&secondary_samples->delta_dir_to_next + esi_4) = fconvert.s(fconvert.t(*(secondary_samples + esi_4 + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + esi_4)))
00428daf        *(&secondary_samples->delta_dir_to_next.y + esi_4) = var_38_2
00428dba        *(&secondary_samples->delta_dir_to_next.z + esi_4) = fconvert.s(x87_r7_44)
00428dcf        i_1 += 1
00428dd0        *(&self->secondary_samples->delta_length + esi_4) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + esi_4))
00428dda        esi_4 += 0xa8
00428de3        do while (i_1 s< self->segment_count - 1)
00428e13        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
00428e27        primary_terminal_delta->x = 0
00428e35        primary_terminal_delta->y = 0f
00428e38        primary_terminal_delta->z = 1f
00428e4a        int32_t var_28_3 = 0x3f800000
00428e56        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00428e6c        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
00428e74        secondary_terminal_delta->x = 0
00428e7a        secondary_terminal_delta->y = 0f
00428e7f        secondary_terminal_delta->z = 1f
00428e94        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
00428ea7        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
00428eb9        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
00428ebe        struct Object* object = self->bod.object
00428ec1        struct ObjectFaceQuad* facequads = object->facequads
00428ec4        struct Vec3* vertices = object->vertices
00428ece        int32_t i_2 = 0
00428ed0        struct Vec3* vertices_1 = vertices
00428ed6        if (self->segment_count s>= 0)
00428edc        int32_t ebx = 0
00428ede        uint32_t width_cells = self->width_cells
00428ee1        int32_t width_cells_2 = 0
00428ee5        width_cells_ = 0
00428ee9        uint32_t width_cells_1 = width_cells
00428eed        if (width_cells s>= 0)
00428f00        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00428f09        long double x87_r7_47 = float.t(width_cells_) - float.t(width_cells_1) * fconvert.t(0.5f)
00428f0b        struct Vec3* vertex
00428f0b        float ecx_48
00428f0b        if (i_2 == self->segment_count)
00428f61        void* eax_46 = primary_samples_2 + ebx
00428f72        vertices = vertices_1
00428fb7        float var_38_3 = fconvert.s(fconvert.t(*(eax_46 - 0x74)) + fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(*(eax_46 - 0xa4)))))
00428fbf        long double x87_r6_31 = fconvert.t(fconvert.s(fconvert.t(*(eax_46 - 0x70)) + fconvert.t(1f))) + x87_r7_47 * fconvert.t(*(eax_46 - 0xa0))
00428fc1        vertex = &vertices[(width_cells + 1) * i_2 + width_cells_2]
00428fc8        vertex->x = fconvert.s(fconvert.t(*(eax_46 - 0x78)) + fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(*(eax_46 - 0xa8)))))
00428fd2        vertex->y = var_38_3
00428fd5        ecx_48 = fconvert.s(x87_r6_31)
00428f0d        struct PathTemplateSample* primary_mesh_sample = primary_samples_2 + ebx
00428f35        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
00428f42        float var_28_4 = fconvert.s(x87_r7_47 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
00428f4b        vertex = &vertices[(width_cells + 1) * i_2 + width_cells_2]
00428f52        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_47 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
00428f58        vertex->y = var_2c_3
00428f5b        ecx_48 = var_28_4
00428fdb        vertex->z = ecx_48
00428fde        width_cells = self->width_cells
00428fe1        width_cells_2 += 1
00428fe2        width_cells_1 = width_cells
00428fe8        width_cells_ = width_cells_2
00428fec        do while (width_cells_2 s<= width_cells)
00428ff5        i_2 += 1
00428ff6        ebx += 0xa8
00428ffe        do while (i_2 s<= self->segment_count)
00429007        int32_t i_3 = 0
0042900b        if (self->segment_count s> 0)
00429014        int32_t j = 0
00429018        width_cells_ = 0
0042901c        if (self->width_cells s> 0)
00429024        int32_t eax_54 = i_3 & 0x80000007
00429029        if (eax_54 s< 0)
0042902f        eax_54 = ((eax_54 - 1) | 0xfffffff8) + 1
00429043        float var_54_1 = fconvert.s(float.t(eax_54) * fconvert.t(0.125f))
00429051        float var_4c_1 = fconvert.s(float.t(eax_54 + 1) * fconvert.t(0.125f))
0042905c        int32_t ecx_52 = 0
00429062        int32_t var_48_1 = 0
0042906c        width_cells_ = fconvert.s(float.t(width_cells_) * fconvert.t(0.125f))
0042907a        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042908e        while (true)
0042908e        int32_t eax_61 = ecx_52 + ((self->width_cells * i_3 + j) << 1)
00429091        if (ecx_52 != 0)
0042914c        struct ObjectFaceQuad* facequads_1 = facequads
00429157        struct ObjectFaceQuad* face_second = &facequads_1[eax_61]
0042915a        __builtin_memset(face_second, 0, 2)
0042915f        ecx_52.w = self->width_cells.w
00429163        ecx_52.w += 1
0042916c        face_second->vertex_0 = ecx_52.w * i_3.w + j.w + 1
00429170        facequads_1.w = self->width_cells.w
00429174        facequads_1.w += 1
0042917b        face_second->vertex_1 = facequads_1.w * i_3.w + j.w
0042918d        face_second->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
004291a5        face_second->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
004291a9        char* texture_path_1
004291a9        if (((j.b ^ i_3.b) & 1) != 0)
0042923f        texture_path_1 = texture_b
004291b6        texture_path_1 = texture_b
004291c9        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
004291d0        face_second->uv[0].u = var_50_1
004291d3        face_second->uv[0].v = var_54_1
004291d8        face_second->uv[1].u = width_cells_
004291e1        face_second->uv[1].v = var_54_1
004291e8        face_second->uv[2].u = width_cells_
004291eb        face_second->uv[2].v = var_4c_1
004291f0        face_second->uv[3].u = var_50_1
004291f3        face_second->uv[3].v = var_4c_1
0042909e        int32_t ecx_54 = eax_61 * 0x30
004290a5        struct ObjectFaceQuad* face_first = ecx_54 + facequads
004290a8        __builtin_memset(face_first, 0, 2)
004290ad        eax_61.w = self->width_cells.w
004290b1        eax_61.w += 1
004290b8        face_first->vertex_0 = eax_61.w * i_3.w + j.w
004290bc        ecx_54.w = self->width_cells.w
004290c0        ecx_54.w += 1
004290cc        face_first->vertex_1 = ecx_54.w * i_3.w + j.w + 1
004290dd        face_first->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
004290f3        face_first->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
004290f7        char* texture_path
004290f7        if (((j.b ^ i_3.b) & 1) != 0)
00429146        texture_path = texture_a
004290fd        texture_path = texture_a
00429110        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00429117        face_first->uv[0].u = width_cells_
0042911a        face_first->uv[0].v = var_54_1
0042911f        face_first->uv[1].u = var_50_1
00429128        face_first->uv[1].v = var_54_1
0042912f        face_first->uv[2].u = var_50_1
00429132        face_first->uv[2].v = var_4c_1
00429137        face_first->uv[3].u = width_cells_
0042913a        face_first->uv[3].v = var_4c_1
004291fb        bool cond:9_1 = var_48_1 + 1 s< 2
004291fe        var_48_1 += 1
00429202        if (not(cond:9_1))
00429202        break
00429080        ecx_52 = var_48_1
00429208        j += 1
00429211        width_cells_ = j
00429215        do while (j s< self->width_cells)
0042921e        i_3 += 1
00429221        do while (i_3 s< self->segment_count)
00429229        finalize_path_template(self)
00429235        return
