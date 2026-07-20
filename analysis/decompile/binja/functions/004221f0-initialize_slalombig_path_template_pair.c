/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_slalombig_path_template_pair @ 0x4221f0 */

004221fc        int32_t i_3 = 0
00422203        self->width_cells = width_cells_
00422206        self->kind = PATH_TEMPLATE_KIND_SLALOMBIG
0042220d        int32_t width_cells_1 = curve_segments + 4
00422212        self->is_mirrored_x = 0
00422216        self->side_exit_mode = 0
0042221c        self->width_or_scale = 1f
00422227        self->segment_count = width_cells_1 + 4
0042222e        self->segment_count_f = fconvert.s(float.t(width_cells_1 + 4))
00422231        allocate_path_template_samples(self)
00422236        self->has_entry_mesh_transition = 0
0042223d        width_cells_ = 0
00422241        void* i = nullptr
004222f1        while (i s< 0x2a0)
00422246        *(&self->primary_samples->center_x + i) = 0
00422250        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0042225a        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00422264        *(&self->primary_samples->special_scalar + i) = 0
0042226e        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042227e        set_matrix_identity(self->primary_samples + i)
00422283        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00422286        long double x87_r7_1 = float.t(width_cells_)
00422298        *(&primary_samples_1->transform.position + i) = *(&primary_samples_1->center_x + i)
0042229e        *(&self->primary_samples->transform.position.y + i) = 0
004222a5        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
004222b0        set_matrix_identity(i + self->secondary_samples)
004222c6        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
004222cd        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
004222dc        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
004222e0        i += 0xa8
004222ed        width_cells_ += 1
00422309        width_cells_ = width_cells_1
00422310        int32_t edi_3 = width_cells_1 * 0xa8
0042231c        *(&self->primary_samples->center_x + edi_3) = 0
00422326        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
00422330        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0042233a        *(&self->primary_samples->special_scalar + edi_3) = 0
00422344        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
00422354        set_matrix_identity(self->primary_samples + edi_3)
0042235c        void* eax_12 = self->primary_samples + edi_3
0042235e        long double x87_r7_3 = float.t(width_cells_)
00422368        *(eax_12 + 0x30) = *(eax_12 + 0x90)
00422372        *(&self->primary_samples->transform.position.y + edi_3) = 0
0042237b        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_3)
00422382        set_matrix_identity(edi_3 + self->secondary_samples)
00422398        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
004223a3        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
004223ae        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_3)))
004223b2        edi_3 += 0xa8
004223b8        width_cells_1 += 1
004223bb        width_cells_ = width_cells_1
004223c2        do while (0xfffffffc - curve_segments + width_cells_1 s< 4)
004223cc        int32_t width_cells_2 = 0
004223d0        width_cells_ = 0
004223d4        if (curve_segments s> 0)
004223de        void* edi_4 = 0x2a0
004223eb        long double x87_r7_7 = float.t(width_cells_) / fconvert.t(fconvert.s(float.t(curve_segments)))
004223fb        long double x87_r7_8 = x87_r7_7 - fconvert.t(0.5f)
00422401        long double temp1_1 = fconvert.t(0f)
00422401        x87_r7_8 - temp1_1
0042240c        float var_48_1
0042240c        if ((((x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00422418        var_48_1 = fconvert.s(x87_r7_8)
00422412        var_48_1 = fconvert.s(fneg(x87_r7_8))
0042241c        long double temp2_1 = fconvert.t(0f)
0042241c        x87_r7_8 - temp2_1
00422427        if ((((x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00422429        x87_r7_8 = fneg(x87_r7_8)
0042245d        *(&self->primary_samples->center_x + edi_4) = fconvert.s(sine(fconvert.s(x87_r7_7 * fconvert.t(6.28318548f))) * (fconvert.t(1f) - fconvert.t(fconvert.s(x87_r7_8))) * (fconvert.t(1f) - fconvert.t(var_48_1)) * fconvert.t(4.44444466f))
00422467        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
00422471        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0042247b        *(&self->primary_samples->special_scalar + edi_4) = 0
00422485        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
00422495        set_matrix_identity(self->primary_samples + edi_4)
0042249a        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004224aa        *(&primary_samples_2->transform.position + edi_4) = *(&primary_samples_2->center_x + edi_4)
004224b6        long double x87_r7_13 = float.t(width_cells_2 + 4)
004224ba        *(&self->primary_samples->transform.position.y + edi_4) = 0
004224c5        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
004224cc        set_matrix_identity(edi_4 + self->secondary_samples)
004224e8        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
004224ef        *(&self->secondary_samples->transform.position.y + edi_4) = 0x3efae148
004224fa        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
004224fe        if (edi_4 s<= 0x2a0)
004226a2        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
004226b1        set_matrix_rotation_identity(edi_4 + self->secondary_samples - 0xa8)
0042251b        struct Vec3* primary_forward = self->primary_samples + edi_4 - 0x98
0042252e        primary_forward->x = 0
00422534        primary_forward->y = 1f
00422537        primary_forward->z = 0f
0042253a        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0042255e        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position.y + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x74)))
00422568        long double x87_r7_20 = fconvert.t(*(&primary_samples_4->transform.position.z + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x70))
0042256f        *(primary_samples_4 + edi_4 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x78)))
00422571        *(primary_samples_4 + edi_4 - 0x84) = var_2c_1
0042257c        *(primary_samples_4 + edi_4 - 0x80) = fconvert.s(x87_r7_20)
00422589        normalize_vector(self->primary_samples + edi_4 - 0x88)
00422591        struct PathTemplateSample* primary_sample_cursor_reloaded = self->primary_samples + edi_4
004225b1        int32_t var_64_3 = cross_vectors(primary_sample_cursor_reloaded - 0xa8, primary_sample_cursor_reloaded - 0x98, primary_sample_cursor_reloaded - 0x88)
004225b2        void* eax_29 = self->primary_samples + edi_4
004225c6        rotate_matrix_local_z(eax_29 - 0xa8, fconvert.s(fconvert.t(*(eax_29 - 0x18)) * fconvert.t(0.261799395f)))
004225e2        struct Vec3* secondary_forward = edi_4 + self->secondary_samples - 0x98
004225f5        secondary_forward->x = 0
004225fb        secondary_forward->y = 1f
004225fe        secondary_forward->z = 0f
00422601        struct PathTemplateSample* secondary_samples = self->secondary_samples
00422625        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + edi_4)) - fconvert.t(*(edi_4 + secondary_samples - 0x74)))
0042262f        long double x87_r7_30 = fconvert.t(*(&secondary_samples->transform.position.z + edi_4)) - fconvert.t(*(edi_4 + secondary_samples - 0x70))
00422636        *(edi_4 + secondary_samples - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + edi_4)) - fconvert.t(*(edi_4 + secondary_samples - 0x78)))
00422638        *(edi_4 + secondary_samples - 0x84) = var_14_1
00422643        *(edi_4 + secondary_samples - 0x80) = fconvert.s(x87_r7_30)
00422650        normalize_vector(edi_4 + self->secondary_samples - 0x88)
0042265a        struct PathTemplateSample* secondary_sample_cursor_reloaded = edi_4 + self->secondary_samples
0042267c        int32_t var_64_6 = cross_vectors(secondary_sample_cursor_reloaded - 0xa8, secondary_sample_cursor_reloaded - 0x98, secondary_sample_cursor_reloaded - 0x88)
00422691        rotate_matrix_local_z(edi_4 + self->secondary_samples - 0xa8, fconvert.s(fconvert.t(*(self->primary_samples + edi_4 - 0x18)) * fconvert.t(0.261799395f)))
004226ba        width_cells_2 += 1
004226bb        edi_4 += 0xa8
004226c3        width_cells_ = width_cells_2
004226c7        do while (width_cells_2 s< curve_segments)
004226d0        int32_t i_1 = 0
004226d5        if (self->segment_count - 1 s> 0)
004226db        void* edi_5 = nullptr
004226dd        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00422701        float var_14_2 = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_5)))
00422708        long double x87_r7_40 = fconvert.t(*(edi_5 + primary_samples_3 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + edi_5))
0042270f        *(&primary_samples_3->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + edi_5)))
00422711        *(&primary_samples_3->delta_dir_to_next.y + edi_5) = var_14_2
0042271c        *(&primary_samples_3->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_40)
00422731        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
00422738        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0042275c        float var_20_1 = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_5)))
00422763        long double x87_r7_47 = fconvert.t(*(edi_5 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_5))
0042276a        *(&secondary_samples_1->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_5)))
0042276c        *(&secondary_samples_1->delta_dir_to_next.y + edi_5) = var_20_1
00422777        *(&secondary_samples_1->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_47)
0042278c        i_1 += 1
0042278d        *(&self->secondary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_5))
00422797        edi_5 += 0xa8
004227a0        do while (i_1 s< self->segment_count - 1)
004227d0        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
004227e4        primary_terminal_delta->x = 0
004227f2        primary_terminal_delta->y = 0f
004227f5        primary_terminal_delta->z = 1f
00422807        int32_t var_10_3 = 0x3f800000
00422813        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00422829        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
00422831        secondary_terminal_delta->x = 0
00422837        secondary_terminal_delta->y = 0f
0042283c        secondary_terminal_delta->z = 1f
00422851        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
00422864        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
00422876        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042287b        struct Object* object = self->bod.object
0042287e        struct Vec3* vertices = object->vertices
00422881        struct ObjectFaceQuad* facequads = object->facequads
0042288f        int32_t i_2 = 0
00422893        if (self->segment_count s>= 0)
00422899        int32_t ebx = 0
0042289b        uint32_t width_cells = self->width_cells
0042289e        int32_t curve_segments_1 = 0
004228a2        curve_segments = 0
004228a6        width_cells_ = width_cells
004228aa        if (width_cells s>= 0)
004228bd        struct PathTemplateSample* primary_samples = self->primary_samples
004228c6        long double x87_r7_50 = float.t(curve_segments) - float.t(width_cells_) * fconvert.t(0.5f)
004228c8        if (i_2 == self->segment_count)
00422925        void* eax_65 = primary_samples + ebx
00422974        i_3 = 0
0042297d        float var_20_2 = fconvert.s(fconvert.t(*(eax_65 - 0x74)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_65 - 0xa4)))))
00422985        int32_t* ecx_69 = &vertices[(width_cells + 1) * i_2 + curve_segments_1]
0042298c        long double x87_r6_28 = fconvert.t(fconvert.s(fconvert.t(*(eax_65 - 0x70)) + fconvert.t(1f))) + x87_r7_50 * fconvert.t(*(eax_65 - 0xa0))
0042298e        *ecx_69 = fconvert.s(fconvert.t(*(eax_65 - 0x78)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_65 - 0xa8)))))
00422994        ecx_69[1] = var_20_2
004229a1        ecx_69[2] = fconvert.s(x87_r6_28)
004228ca        struct PathTemplateSample* primary_mesh_sample = primary_samples + ebx
004228f2        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
004228ff        float var_10_4 = fconvert.s(x87_r7_50 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0042290c        int32_t* ecx_67 = &vertices[(width_cells + 1) * i_2 + curve_segments_1]
00422913        *ecx_67 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
00422919        ecx_67[1] = var_14_3
00422920        ecx_67[2] = var_10_4
004229a4        width_cells = self->width_cells
004229a7        curve_segments_1 += 1
004229aa        curve_segments = curve_segments_1
004229ae        width_cells_ = width_cells
004229b2        do while (curve_segments_1 s<= width_cells)
004229bb        i_2 += 1
004229bc        ebx += 0xa8
004229c4        do while (i_2 s<= self->segment_count)
004229cd        int32_t ebx_1 = 0
004229d1        if (self->segment_count s> 0)
004229de        while (true)
004229de        curve_segments = 0
004229e4        if (self->width_cells s> 0)
004229ec        int32_t eax_77 = ebx_1 & 0x80000007
004229f1        if (eax_77 s< 0)
004229f7        eax_77 = ((eax_77 - 1) | 0xfffffff8) + 1
00422a0b        width_cells_ = fconvert.s(float.t(eax_77) * fconvert.t(0.125f))
00422a19        float var_4c_2 = fconvert.s(float.t(eax_77 + 1) * fconvert.t(0.125f))
00422a24        int32_t ecx_70 = 0
00422a2a        int32_t var_48_3 = 0
00422a34        curve_segments = fconvert.s(float.t(curve_segments) * fconvert.t(0.125f))
00422a42        float var_50_1 = fconvert.s(float.t(i_3 + 1) * fconvert.t(0.125f))
00422a54        while (true)
00422a5e        int32_t edx_37 = (ecx_70 + ((self->width_cells * ebx_1 + i_3) << 1)) * 0x30
00422a63        struct ObjectFaceQuad* face = edx_37 + facequads
00422a66        __builtin_memset(face, 0, 2)
00422a6b        if (ecx_70 != 0)
00422b11        edx_37.w = self->width_cells.w
00422b17        edx_37.w += 1
00422b22        face->vertex_0 = edx_37.w * ebx_1.w + i_3.w + 1
00422b26        ecx_70.w = self->width_cells.w
00422b2a        ecx_70.w += 1
00422b34        face->vertex_1 = ecx_70.w * ebx_1.w + i_3.w
00422b43        face->vertex_2 = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w
00422b5a        face->vertex_3 = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w + 1
00422b5e        char* texture_path_1
00422b5e        if (((i_3.b ^ ebx_1.b) & 1) != 0)
00422bee        texture_path_1 = texture_b
00422b68        texture_path_1 = texture_b
00422b7b        face->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
00422b82        face->uv[0].u = var_50_1
00422b85        face->uv[0].v = width_cells_
00422b8a        face->uv[1].u = curve_segments
00422b93        face->uv[1].v = width_cells_
00422b9a        face->uv[2].u = curve_segments
00422b9d        face->uv[2].v = var_4c_2
00422ba2        face->uv[3].u = var_50_1
00422ba5        face->uv[3].v = var_4c_2
00422a71        ecx_70.w = self->width_cells.w
00422a77        ecx_70.w += 1
00422a80        face->vertex_0 = ecx_70.w * ebx_1.w + i_3.w
00422a84        edx_37.w = self->width_cells.w
00422a88        edx_37.w += 1
00422a91        face->vertex_1 = edx_37.w * ebx_1.w + i_3.w + 1
00422aa5        face->vertex_2 = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w + 1
00422abb        face->vertex_3 = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w
00422abf        char* texture_path
00422abf        if (((i_3.b ^ ebx_1.b) & 1) != 0)
00422b0e        texture_path = texture_a
00422ac5        texture_path = texture_a
00422ad8        face->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00422adf        face->uv[0].u = curve_segments
00422ae2        face->uv[0].v = width_cells_
00422ae7        face->uv[1].u = var_50_1
00422af0        face->uv[1].v = width_cells_
00422af7        face->uv[2].u = var_50_1
00422afa        face->uv[2].v = var_4c_2
00422aff        face->uv[3].u = curve_segments
00422b02        face->uv[3].v = var_4c_2
00422bad        bool cond:11_1 = var_48_3 + 1 s< 2
00422bb0        var_48_3 += 1
00422bb4        if (not(cond:11_1))
00422bb4        break
00422a48        ecx_70 = var_48_3
00422bba        i_3 += 1
00422bc3        curve_segments = i_3
00422bc7        do while (i_3 s< self->width_cells)
00422bd0        ebx_1 += 1
00422bd3        if (ebx_1 s>= self->segment_count)
00422bd3        break
004229d9        i_3 = 0
00422bdb        finalize_path_template(self)
00422be7        return
