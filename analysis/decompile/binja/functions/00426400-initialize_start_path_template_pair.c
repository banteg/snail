/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_start_path_template_pair @ 0x426400 */

00426419        self->kind = PATH_TEMPLATE_KIND_START
00426420        self->is_mirrored_x = 0
00426424        self->side_exit_mode = 0
00426427        self->width_cells = width_cells_
0042642a        int16_t x87control
0042642a        int32_t eax_1 = ftol(x87control, fconvert.t(length) * fconvert.t(3.14159274f))
00426446        self->width_or_scale = 1f
00426449        self->segment_count = eax_1 + 0x10
0042644c        self->segment_count_f = fconvert.s(float.t(eax_1 + 0xf))
0042644f        long double x87_r7_3 = float.t(eax_1)
0042645d        length = fconvert.s(x87_r7_3 * fconvert.t(0.318309873f))
00426461        allocate_path_template_samples(self)
00426466        long double x87_r7_5 = fconvert.t(length)
0042646a        uint32_t segment_count = self->segment_count
0042646d        self->has_entry_mesh_transition = 0
00426474        long double x87_r7_6 = x87_r7_5 + x87_r7_5
00426477        width_cells_ = 0
0042647b        self->segment_count = segment_count - 1
0042647e        void* i = nullptr
0042654c        while (i s< 0x348)
00426491        *(&self->primary_samples->center_x + i) = 0
0042649b        *(&self->primary_samples->rotation_scalar_98 + i) = 0
004264a5        *(&self->primary_samples->rotation_scalar_94 + i) = 0
004264af        *(&self->primary_samples->special_scalar + i) = 0
004264bb        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
004264c7        set_matrix_identity(i + self->primary_samples)
004264cc        struct PathTemplateSample* primary_samples = self->primary_samples
004264dc        *(&primary_samples->transform.position + i) = *(&primary_samples->center_x + i)
004264e2        *(&self->primary_samples->transform.position.y + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_6)))
004264e6        long double x87_r7_9 = float.t(width_cells_)
004264f1        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_9)
004264f8        *(&self->primary_samples->delta_length + i) = 0x3f800000
00426504        set_matrix_identity(self->secondary_samples + i)
0042651a        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
00426521        *(&self->secondary_samples->transform.position.y + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_6 + fconvert.t(0.49000001f))))
00426531        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_9)))
00426538        i += 0xa8
00426544        width_cells_ += 1
00426548        *(self->secondary_samples + i - 0x1c) = 0x3f800000
00426556        int32_t var_3c_1 = 0xb
00426561        width_cells_ = eax_1 + 5
00426571        int32_t edi_3 = (eax_1 + 5) * 0xa8
00426634        bool cond:1_1
00426577        *(&self->primary_samples->center_x + edi_3) = 0
00426581        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0042658b        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
00426595        *(&self->primary_samples->special_scalar + edi_3) = 0
0042659f        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
004265ad        set_matrix_identity(edi_3 + self->primary_samples)
004265b2        struct PathTemplateSample* primary_samples_1 = self->primary_samples
004265c3        *(&primary_samples_1->transform.position + edi_3) = *(&primary_samples_1->center_x + edi_3)
004265c9        *(&self->primary_samples->transform.position.y + edi_3) = 0
004265d0        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(float.t(width_cells_))
004265d7        *(&self->primary_samples->delta_length + edi_3) = 0x3f800000
004265e3        set_matrix_identity(self->secondary_samples + edi_3)
004265f5        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
004265fc        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0042660e        *(&self->secondary_samples->transform.position.z + edi_3) = *(&self->primary_samples->transform.position.z + edi_3)
00426619        *(&self->secondary_samples->delta_length + edi_3) = 0x3f800000
00426624        edi_3 += 0xa8
0042662b        cond:1_1 = var_3c_1 != 1
0042662c        width_cells_ += 1
00426630        var_3c_1 -= 1
00426634        do while (cond:1_1)
0042663e        width_cells_ = 0
00426644        if (eax_1 s> 0)
0042664a        void* edi_4 = 0x348
004268ae        bool cond:4_1
00426652        *(&self->primary_samples->center_x + edi_4) = 0
0042665c        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
00426666        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
00426670        *(&self->primary_samples->special_scalar + edi_4) = 0
0042667c        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
00426688        set_matrix_identity(edi_4 + self->primary_samples)
00426694        struct PathTemplateSample* primary_curve_sample = self->primary_samples + edi_4
0042669d        float center_x = primary_curve_sample->center_x
004266a3        long double x87_r7_13 = float.t(width_cells_ + 5)
004266a7        primary_curve_sample->transform.position.x = center_x
004266ad        float center_x_1 = center_x
004266b2        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
004266dc        *(&self->primary_samples->transform.position.y + edi_4) = fconvert.s((cosine(fconvert.s(float.t(width_cells_) * fconvert.t(3.14159274f) / fconvert.t(fconvert.s(x87_r7_3)))) + fconvert.t(1f)) * fconvert.t(length))
004266e7        set_matrix_identity(edi_4 + self->secondary_samples)
00426703        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
0042670a        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0042671e        *(&self->secondary_samples->transform.position.y + edi_4) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + edi_4)) + fconvert.t(0.49000001f))
00426722        if (edi_4 s<= 0x348)
00426885        set_matrix_rotation_identity(edi_4 + self->primary_samples - 0xa8)
00426894        set_matrix_rotation_identity(edi_4 + self->secondary_samples - 0xa8)
0042673f        struct Vec3* primary_right = edi_4 + self->primary_samples - 0xa8
00426752        primary_right->x = 0x3f800000
00426758        primary_right->y = 0f
0042675b        primary_right->z = 0f
0042675e        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00426782        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position.y + edi_4)) - fconvert.t(*(edi_4 + primary_samples_2 - 0x74)))
0042678c        long double x87_r7_28 = fconvert.t(*(&primary_samples_2->transform.position.z + edi_4)) - fconvert.t(*(edi_4 + primary_samples_2 - 0x70))
00426793        *(edi_4 + primary_samples_2 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position + edi_4)) - fconvert.t(*(edi_4 + primary_samples_2 - 0x78)))
00426795        *(edi_4 + primary_samples_2 - 0x84) = var_20_1
004267a0        *(edi_4 + primary_samples_2 - 0x80) = fconvert.s(x87_r7_28)
004267ad        normalize_vector(edi_4 + self->primary_samples - 0x88)
004267b5        struct PathTemplateSample* primary_sample_cursor_reloaded = self->primary_samples + edi_4
004267cd        cross_vectors(primary_sample_cursor_reloaded - 0x98, primary_sample_cursor_reloaded - 0x88, primary_sample_cursor_reloaded - 0xa8)
004267e9        struct Vec3* secondary_right = edi_4 + self->secondary_samples - 0xa8
004267fc        secondary_right->x = 0x3f800000
00426802        secondary_right->y = 0f
00426805        secondary_right->z = 0f
0042680b        void* eax_31 = self->secondary_samples + edi_4
00426829        float var_8_1 = fconvert.s(fconvert.t(*(eax_31 + 0x34)) - fconvert.t(*(eax_31 - 0x74)))
00426833        long double x87_r7_36 = fconvert.t(*(eax_31 + 0x38)) - fconvert.t(*(eax_31 - 0x70))
0042683a        *(eax_31 - 0x88) = fconvert.s(fconvert.t(*(eax_31 + 0x30)) - fconvert.t(*(eax_31 - 0x78)))
0042683c        *(eax_31 - 0x84) = var_8_1
00426847        *(eax_31 - 0x80) = fconvert.s(x87_r7_36)
00426854        normalize_vector(edi_4 + self->secondary_samples - 0x88)
0042685c        struct PathTemplateSample* secondary_sample_cursor_reloaded = self->secondary_samples + edi_4
00426874        cross_vectors(secondary_sample_cursor_reloaded - 0x98, secondary_sample_cursor_reloaded - 0x88, secondary_sample_cursor_reloaded - 0xa8)
004268a2        edi_4 += 0xa8
004268a8        cond:4_1 = width_cells_ + 1 s< eax_1
004268aa        width_cells_ += 1
004268ae        do while (cond:4_1)
004268b7        int32_t i_1 = 0
004268bb        if (self->segment_count s> 0)
004268c1        void* edi_5 = nullptr
004268c3        struct PathTemplateSample* primary_samples_3 = self->primary_samples
004268e7        float var_8_2 = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_5)))
004268ee        long double x87_r7_44 = fconvert.t(*(edi_5 + primary_samples_3 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + edi_5))
004268f5        *(&primary_samples_3->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + edi_5)))
004268f7        *(&primary_samples_3->delta_dir_to_next.y + edi_5) = var_8_2
00426902        *(&primary_samples_3->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_44)
00426917        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0042691e        struct PathTemplateSample* secondary_samples = self->secondary_samples
00426942        float var_14_1 = fconvert.s(fconvert.t(*(edi_5 + secondary_samples + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + edi_5)))
00426949        long double x87_r7_51 = fconvert.t(*(edi_5 + secondary_samples + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + edi_5))
00426950        *(&secondary_samples->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + secondary_samples + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + edi_5)))
00426952        *(&secondary_samples->delta_dir_to_next.y + edi_5) = var_14_1
0042695d        *(&secondary_samples->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_51)
00426972        i_1 += 1
00426973        *(&self->secondary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_5))
0042697d        edi_5 += 0xa8
00426985        do while (i_1 s< self->segment_count)
0042699a        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
004269ac        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
004269b1        struct Object* object = self->bod.object
004269b4        int32_t i_2 = 0
004269b6        struct Vec3* vertices = object->vertices
004269b9        struct ObjectFaceQuad* facequads = object->facequads
004269c9        if (self->segment_count s>= 0)
004269cf        int32_t ebx = 0
004269d1        uint32_t width_cells = self->width_cells
004269d4        float length_1 = 0f
004269d8        length = 0f
004269dc        width_cells_ = width_cells
004269e0        if (width_cells s>= 0)
004269ed        struct PathTemplateSample* primary_mesh_sample = self->primary_samples + ebx
004269f5        long double x87_r7_54 = float.t(length) - float.t(width_cells_) * fconvert.t(0.5f)
00426a1d        float var_8_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
00426a2a        float var_4_3 = fconvert.s(x87_r7_54 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
00426a2e        int32_t eax_51 = (width_cells + 1) * i_2 i+ length_1
00426a30        length_1 += 1
00426a31        length = length_1
00426a3c        struct Vec3* vertex = &vertices[eax_51]
00426a43        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_54 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
00426a49        vertex->y = var_8_3
00426a50        vertex->z = var_4_3
00426a53        width_cells = self->width_cells
00426a58        width_cells_ = width_cells
00426a5c        do while (length_1 s<= width_cells)
00426a61        i_2 += 1
00426a62        ebx += 0xa8
00426a6a        do while (i_2 s<= self->segment_count)
00426a73        int32_t i_3 = 0
00426a77        if (self->segment_count s> 0)
00426a80        int32_t j = 0
00426a84        length = 0f
00426a88        if (self->width_cells s> 0)
00426a90        int32_t eax_60 = i_3 & 0x80000007
00426a95        if (eax_60 s< 0)
00426a9b        eax_60 = ((eax_60 - 1) | 0xfffffff8) + 1
00426aaf        width_cells_ = fconvert.s(float.t(eax_60) * fconvert.t(0.125f))
00426abd        float var_40_1 = fconvert.s(float.t(eax_60 + 1) * fconvert.t(0.125f))
00426acc        int32_t ecx_58 = 0
00426ad2        int32_t var_3c_2 = 0
00426adc        length = fconvert.s(float.t(length) * fconvert.t(0.125f))
00426aea        float var_44_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
00426b00        while (true)
00426b00        int32_t eax_67 = ecx_58 + ((self->width_cells * i_3 + j) << 1)
00426b03        if (ecx_58 != 0)
00426bb9        struct ObjectFaceQuad* facequads_1 = facequads
00426bc4        struct ObjectFaceQuad* face_second = &facequads_1[eax_67]
00426bc7        __builtin_memcpy(face_second, "\x04\x00", 2)
00426bcd        ecx_58.w = self->width_cells.w
00426bd1        ecx_58.w += 1
00426bda        face_second->vertex_0 = ecx_58.w * i_3.w + j.w + 1
00426bde        facequads_1.w = self->width_cells.w
00426be2        facequads_1.w += 1
00426be9        face_second->vertex_1 = facequads_1.w * i_3.w + j.w
00426bfb        face_second->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
00426c13        face_second->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
00426c17        char* texture_path_1
00426c17        if (((j.b ^ i_3.b) & 1) != 0)
00426ca9        texture_path_1 = texture_a
00426c21        texture_path_1 = texture_a
00426c34        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
00426c3b        face_second->uv[0].u = var_44_1
00426c3e        face_second->uv[0].v = width_cells_
00426c43        face_second->uv[1].u = length
00426c4c        face_second->uv[1].v = width_cells_
00426c53        face_second->uv[2].u = length
00426c56        face_second->uv[2].v = var_40_1
00426c5b        face_second->uv[3].u = var_44_1
00426c5e        face_second->uv[3].v = var_40_1
00426b09        int32_t ecx_59 = eax_67 * 3
00426b0c        eax_67.w = self->width_cells.w
00426b10        int32_t ecx_60 = ecx_59 << 4
00426b13        eax_67.w += 1
00426b1c        struct ObjectFaceQuad* face_first = ecx_60 + facequads
00426b25        face_first->vertex_0 = eax_67.w * i_3.w + j.w
00426b29        ecx_60.w = self->width_cells.w
00426b2d        ecx_60.w += 1
00426b39        face_first->vertex_1 = ecx_60.w * i_3.w + j.w + 1
00426b4a        face_first->vertex_2 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
00426b60        face_first->vertex_3 = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
00426b64        char* texture_path
00426b64        if (((j.b ^ i_3.b) & 1) != 0)
00426bb3        texture_path = texture_a
00426b6a        texture_path = texture_a
00426b7d        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
00426b84        face_first->uv[0].u = length
00426b87        face_first->uv[0].v = width_cells_
00426b8c        face_first->uv[1].u = var_44_1
00426b95        face_first->uv[1].v = width_cells_
00426b9c        face_first->uv[2].u = var_44_1
00426b9f        face_first->uv[2].v = var_40_1
00426ba4        face_first->uv[3].u = length
00426ba7        face_first->uv[3].v = var_40_1
00426c66        bool cond:12_1 = var_3c_2 + 1 s< 2
00426c69        var_3c_2 += 1
00426c6d        if (not(cond:12_1))
00426c6d        break
00426af0        ecx_58 = var_3c_2
00426c73        j += 1
00426c7c        length = j
00426c80        do while (j s< self->width_cells)
00426c8b        i_3 += 1
00426c8e        do while (i_3 s< self->segment_count)
00426c96        finalize_path_template(self)
00426ca2        return
