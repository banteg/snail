/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_loopout_path_template_pair @ 0x41c5f0 */

0041c609        self->kind = PATH_TEMPLATE_KIND_LOOPOUT
0041c610        self->is_mirrored_x = 0
0041c614        self->side_exit_mode = 0
0041c617        self->width_cells = width_cells_
0041c61a        int16_t x87control
0041c61a        int32_t eax_1 = ftol(x87control, fconvert.t(curve_source) * fconvert.t(6.28318548f))
0041c635        self->width_or_scale = 1f
0041c638        self->segment_count = eax_1 + 0xe
0041c63b        self->segment_count_f = fconvert.s(float.t(eax_1 + 0xe))
0041c63e        long double x87_r7_3 = float.t(eax_1)
0041c642        float var_48 = fconvert.s(x87_r7_3)
0041c64c        curve_source = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
0041c650        allocate_path_template_samples(self)
0041c655        self->has_entry_mesh_transition = 1
0041c65c        width_cells_ = 0
0041c660        void* i = nullptr
0041c742        while (i s< 0x690)
0041c669        float var_4c_1 = fconvert.s(float.t(width_cells_))
0041c68e        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f) - fconvert.t(var_4c_1) * fconvert.t(0.111111112f) * fconvert.t(0.300000012f))
0041c698        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041c6a2        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041c6ac        *(&self->primary_samples->special_scalar + i) = 0
0041c6b8        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041c6c4        set_matrix_identity(i + self->primary_samples)
0041c6cc        void* eax_5 = self->primary_samples + i
0041c6d8        *(eax_5 + 0x30) = *(eax_5 + 0x90)
0041c6de        *(&self->primary_samples->transform.position.y + i) = 0
0041c6e5        *(&self->primary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_4c_1))
0041c6ec        *(&self->primary_samples->delta_length + i) = 0x3f800000
0041c6fa        set_matrix_identity(i + self->secondary_samples)
0041c710        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0041c717        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0041c726        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(var_4c_1))
0041c72d        i += 0xa8
0041c73a        *(i + self->secondary_samples - 0x1c) = 0x3f800000
0041c73e        width_cells_ += 1
0041c74c        int32_t i_1 = 0
0041c74e        width_cells_ = 0
0041c761        int32_t edi_1 = (eax_1 + 0xa) * 0xa8
0041c764        int32_t var_40 = edi_1
0041c792        *(&self->primary_samples->center_x + edi_1) = fconvert.s((fconvert.t(1f) - float.t(width_cells_) * fconvert.t(0.333333343f)) * fconvert.t(0.300000012f) + fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f))
0041c79c        *(&self->primary_samples->rotation_scalar_98 + edi_1) = 0
0041c7a6        *(&self->primary_samples->rotation_scalar_94 + edi_1) = 0
0041c7b0        *(&self->primary_samples->special_scalar + edi_1) = 0
0041c7ba        *(&self->primary_samples->lateral_scale + edi_1) = 0x3f800000
0041c7cc        set_matrix_identity(edi_1 + self->primary_samples)
0041c7d1        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041c7de        *(&primary_samples_4->transform.position + edi_1) = *(&primary_samples_4->center_x + edi_1)
0041c7eb        *(&self->primary_samples->transform.position.y + edi_1) = 0
0041c7ef        long double x87_r7_17 = float.t(i_1 + 0xa)
0041c7fa        *(&self->primary_samples->transform.position.z + edi_1) = fconvert.s(x87_r7_17)
0041c803        *(&self->primary_samples->delta_length + edi_1) = 0x3f800000
0041c813        set_matrix_identity(edi_1 + self->secondary_samples)
0041c829        i_1 += 1
0041c82a        *(&self->secondary_samples->transform.position + edi_1) = *(&self->primary_samples->center_x + edi_1)
0041c831        width_cells_ = i_1
0041c835        *(&self->secondary_samples->transform.position.y + edi_1) = 0x3efae148
0041c840        *(&self->secondary_samples->transform.position.z + edi_1) = fconvert.s(fconvert.t(fconvert.s(x87_r7_17)))
0041c847        edi_1 += 0xa8
0041c850        *(edi_1 + self->secondary_samples - 0x1c) = 0x3f800000
0041c858        do while (i_1 s< 4)
0041c866        width_cells_ = 0
0041c86c        float var_20 = fconvert.s(fneg(fconvert.t(curve_source)))
0041c872        if (eax_1 s> 0)
0041c8b2        float var_44_1 = fconvert.s(fconvert.t(curve_source) + fconvert.t(0.49000001f))
0041c8b6        void* edi_2 = 0x690
0041cad5        bool cond:3_1
0041c8bb        long double x87_r7_23 = float.t(width_cells_)
0041c8bf        struct PathTemplateSample* primary_samples = self->primary_samples
0041c8c6        int32_t var_64_1 = var_40
0041c8d3        float var_4c_2 = fconvert.s(x87_r7_23 * fconvert.t(6.28318548f) / fconvert.t(var_48))
0041c8f0        *(&primary_samples->center_x + edi_2) = fconvert.s((fconvert.t(*(&primary_samples->center_x + var_40)) - fconvert.t(primary_samples->center_x)) * x87_r7_23 / fconvert.t(var_48) + fconvert.t(primary_samples->center_x))
0041c906        float* ebx = &self->primary_samples->center_x + edi_2
0041c926        *ebx = fconvert.s(sine(fconvert.s(fconvert.t(var_4c_2) * fconvert.t(0.5f) + fconvert.t(4.71238899f))) * fconvert.t(0.300000012f) + fconvert.t(*ebx))
0041c92b        *(&self->primary_samples->rotation_scalar_98 + edi_2) = 0
0041c935        *(&self->primary_samples->rotation_scalar_94 + edi_2) = 0
0041c941        *(&self->primary_samples->special_scalar + edi_2) = 0
0041c94b        *(&self->primary_samples->lateral_scale + edi_2) = 0x3f800000
0041c95b        set_matrix_identity(edi_2 + self->primary_samples)
0041c960        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041c972        *(&primary_samples_2->transform.position + edi_2) = *(&primary_samples_2->center_x + edi_2)
0041c988        *(&self->primary_samples->transform.position.z + edi_2) = fconvert.s(sine(var_4c_2) * fconvert.t(curve_source) + fconvert.t(10f))
0041c99f        *(&self->primary_samples->transform.position.y + edi_2) = fconvert.s(cosine(var_4c_2) * fconvert.t(curve_source) + fconvert.t(var_20))
0041c9aa        set_matrix_identity(edi_2 + self->secondary_samples)
0041c9bd        *(&self->secondary_samples->transform.position + edi_2) = *(&self->primary_samples->center_x + edi_2)
0041c9d4        *(&self->secondary_samples->transform.position.z + edi_2) = fconvert.s(sine(var_4c_2) * fconvert.t(var_44_1) + fconvert.t(10f))
0041c9ed        *(&self->secondary_samples->transform.position.y + edi_2) = fconvert.s(cosine(var_4c_2) * fconvert.t(var_44_1) + fconvert.t(var_20))
0041c9f1        struct Vec3* primary_right = edi_2 + self->primary_samples
0041c9fc        primary_right->x = 0x3f800000
0041ca06        primary_right->y = 0f
0041ca09        primary_right->z = 0f
0041ca0f        *(&self->primary_samples->transform.basis_up + edi_2) = 0
0041ca13        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041ca1f        *(&primary_samples_3->transform.basis_up.y + edi_2) = fconvert.s(fneg(fconvert.t(var_20) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_2))))
0041ca22        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0041ca34        *(&primary_samples_5->transform.basis_up.z + edi_2) = fconvert.s(fneg(fconvert.t(10f) - fconvert.t(*(&primary_samples_5->transform.position.z + edi_2))))
0041ca3e        normalize_vector(&self->primary_samples->transform.basis_up + edi_2)
0041ca48        struct Vec3* primary_right_reloaded = edi_2 + self->primary_samples
0041ca53        cross_vectors(primary_right_reloaded + 0x20, primary_right_reloaded, primary_right_reloaded + 0x10)
0041ca65        struct Vec3* secondary_right = edi_2 + self->secondary_samples
0041ca6b        secondary_right->x = 0x3f800000
0041ca71        secondary_right->y = 0f
0041ca74        secondary_right->z = 0f
0041ca7a        *(&self->secondary_samples->transform.basis_up + edi_2) = 0
0041ca81        void* eax_32 = self->secondary_samples + edi_2
0041ca88        *(eax_32 + 0x14) = fconvert.s(fneg(fconvert.t(var_20) - fconvert.t(*(eax_32 + 0x34))))
0041ca8b        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041ca9d        *(&secondary_samples->transform.basis_up.z + edi_2) = fconvert.s(fneg(fconvert.t(10f) - fconvert.t(*(&secondary_samples->transform.position.z + edi_2))))
0041caa7        normalize_vector(&self->secondary_samples->transform.basis_up + edi_2)
0041caaf        struct Vec3* secondary_right_reloaded = self->secondary_samples + edi_2
0041cabb        cross_vectors(secondary_right_reloaded + 0x20, secondary_right_reloaded, secondary_right_reloaded + 0x10)
0041cac9        edi_2 += 0xa8
0041cacf        cond:3_1 = width_cells_ + 1 s< eax_1
0041cad1        width_cells_ += 1
0041cad5        do while (cond:3_1)
0041cade        int32_t i_2 = 0
0041cae3        if (self->segment_count - 1 s> 0)
0041cae9        void* edi_3 = nullptr
0041caee        void* eax_38 = self->primary_samples + edi_3
0041cb0c        float var_2c_1 = fconvert.s(fconvert.t(*(eax_38 + 0xdc)) - fconvert.t(*(eax_38 + 0x34)))
0041cb13        long double x87_r7_64 = fconvert.t(*(eax_38 + 0xe0)) - fconvert.t(*(eax_38 + 0x38))
0041cb1a        *(eax_38 + 0x80) = fconvert.s(fconvert.t(*(eax_38 + 0xd8)) - fconvert.t(*(eax_38 + 0x30)))
0041cb1c        *(eax_38 + 0x84) = var_2c_1
0041cb27        *(eax_38 + 0x88) = fconvert.s(x87_r7_64)
0041cb3c        *(&self->primary_samples->delta_length + edi_3) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_3))
0041cb43        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041cb67        float var_38_1 = fconvert.s(fconvert.t(*(edi_3 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_3)))
0041cb6e        long double x87_r7_71 = fconvert.t(*(edi_3 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_3))
0041cb75        *(&secondary_samples_1->delta_dir_to_next + edi_3) = fconvert.s(fconvert.t(*(edi_3 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_3)))
0041cb77        *(&secondary_samples_1->delta_dir_to_next.y + edi_3) = var_38_1
0041cb82        *(&secondary_samples_1->delta_dir_to_next.z + edi_3) = fconvert.s(x87_r7_71)
0041cb97        i_2 += 1
0041cb98        *(&self->secondary_samples->delta_length + edi_3) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_3))
0041cba2        edi_3 += 0xa8
0041cbab        do while (i_2 s< self->segment_count - 1)
0041cbdb        struct Vec3* primary_terminal_delta = &self->primary_samples[self->segment_count] - 0x28
0041cbef        primary_terminal_delta->x = 0
0041cbfd        primary_terminal_delta->y = 0f
0041cc00        primary_terminal_delta->z = 1f
0041cc12        int32_t var_28_2 = 0x3f800000
0041cc1e        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041cc34        struct Vec3* secondary_terminal_delta = &self->secondary_samples[self->segment_count] - 0x28
0041cc3c        secondary_terminal_delta->x = 0
0041cc42        secondary_terminal_delta->y = 0f
0041cc47        secondary_terminal_delta->z = 1f
0041cc5c        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041cc6f        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0041cc81        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0041cc86        struct Object* object = self->bod.object
0041cc89        int32_t i_3 = 0
0041cc8b        struct Vec3* vertices = object->vertices
0041cc8e        struct ObjectFaceQuad* facequads = object->facequads
0041cc9e        if (self->segment_count s>= 0)
0041cca4        int32_t edx_36 = 0
0041cca6        int32_t var_48_1 = 0
0041ccaa        uint32_t width_cells = self->width_cells
0041ccad        float curve_source_1 = 0f
0041ccb1        curve_source = 0f
0041ccb5        width_cells_ = width_cells
0041ccb9        if (width_cells s>= 0)
0041cccc        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041ccd5        long double x87_r7_74 = float.t(curve_source) - float.t(width_cells_) * fconvert.t(0.5f)
0041ccd7        if (i_3 == self->segment_count)
0041cd37        void* eax_68 = primary_samples_1 + edx_36
0041cd8d        float var_38_2 = fconvert.s(fconvert.t(*(eax_68 - 0x74)) + fconvert.t(fconvert.s(x87_r7_74 * fconvert.t(*(eax_68 - 0xa4)))))
0041cd95        struct Vec3* terminal_vertex = &vertices[(width_cells + 1) * i_3 i+ curve_source_1]
0041cda0        long double x87_r6_34 = fconvert.t(fconvert.s(fconvert.t(*(eax_68 - 0x70)) + fconvert.t(1f))) + x87_r7_74 * fconvert.t(*(eax_68 - 0xa0))
0041cda2        terminal_vertex->x = fconvert.s(fconvert.t(*(eax_68 - 0x78)) + fconvert.t(fconvert.s(x87_r7_74 * fconvert.t(*(eax_68 - 0xa8)))))
0041cda4        terminal_vertex->y = var_38_2
0041cdaf        terminal_vertex->z = fconvert.s(x87_r6_34)
0041cdb2        edx_36 = var_48_1
0041ccd9        struct PathTemplateSample* primary_mesh_sample = primary_samples_1 + edx_36
0041cd01        float var_2c_2 = fconvert.s(fconvert.t(fconvert.s(x87_r7_74 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
0041cd0e        float var_28_3 = fconvert.s(x87_r7_74 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
0041cd1b        struct Vec3* vertex = &vertices[(width_cells + 1) * i_3 i+ curve_source_1]
0041cd22        vertex->x = fconvert.s(fconvert.t(fconvert.s(x87_r7_74 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
0041cd28        vertex->y = var_2c_2
0041cd2f        vertex->z = var_28_3
0041cdb8        width_cells = self->width_cells
0041cdbb        curve_source_1 += 1
0041cdbe        curve_source = curve_source_1
0041cdc2        width_cells_ = width_cells
0041cdc6        do while (curve_source_1 s<= width_cells)
0041cdcf        i_3 += 1
0041cdd0        edx_36 += 0xa8
0041cdd8        var_48_1 = edx_36
0041cddc        do while (i_3 s<= self->segment_count)
0041cde5        int32_t i_4 = 0
0041cde9        if (self->segment_count s> 0)
0041cdf2        int32_t j = 0
0041cdf6        curve_source = 0f
0041cdfa        if (self->width_cells s> 0)
0041ce02        int32_t eax_79 = i_4 & 0x80000007
0041ce07        if (eax_79 s< 0)
0041ce0d        eax_79 = ((eax_79 - 1) | 0xfffffff8) + 1
0041ce21        width_cells_ = fconvert.s(float.t(eax_79) * fconvert.t(0.125f))
0041ce2f        float var_4c_3 = fconvert.s(float.t(eax_79 + 1) * fconvert.t(0.125f))
0041ce3e        int32_t ecx_60 = 0
0041ce44        int32_t var_48_2 = 0
0041ce4e        curve_source = fconvert.s(float.t(curve_source) * fconvert.t(0.125f))
0041ce5c        float var_50_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0041ce72        while (true)
0041ce72        int32_t eax_86 = ecx_60 + ((self->width_cells * i_4 + j) << 1)
0041ce75        if (ecx_60 != 0)
0041cf31        struct ObjectFaceQuad* facequads_1 = facequads
0041cf3c        struct ObjectFaceQuad* face_second = &facequads_1[eax_86]
0041cf3f        __builtin_memset(face_second, 0, 2)
0041cf45        ecx_60.w = self->width_cells.w
0041cf49        ecx_60.w += 1
0041cf52        face_second->vertex_0 = ecx_60.w * i_4.w + j.w + 1
0041cf56        facequads_1.w = self->width_cells.w
0041cf5a        facequads_1.w += 1
0041cf61        face_second->vertex_1 = facequads_1.w * i_4.w + j.w
0041cf73        face_second->vertex_2 = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
0041cf8b        face_second->vertex_3 = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
0041cf8f        char* texture_path_1
0041cf8f        if (((j.b ^ i_4.b) & 1) != 0)
0041d021        texture_path_1 = texture_b
0041cf99        texture_path_1 = texture_b
0041cfac        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
0041cfb3        face_second->uv[0].u = var_50_1
0041cfb6        face_second->uv[0].v = width_cells_
0041cfbb        face_second->uv[1].u = curve_source
0041cfc4        face_second->uv[1].v = width_cells_
0041cfcb        face_second->uv[2].u = curve_source
0041cfce        face_second->uv[2].v = var_4c_3
0041cfd3        face_second->uv[3].u = var_50_1
0041cfd6        face_second->uv[3].v = var_4c_3
0041ce82        int32_t ecx_62 = eax_86 * 0x30
0041ce89        struct ObjectFaceQuad* face_first = ecx_62 + facequads
0041ce8c        __builtin_memset(face_first, 0, 2)
0041ce92        eax_86.w = self->width_cells.w
0041ce96        eax_86.w += 1
0041ce9d        face_first->vertex_0 = eax_86.w * i_4.w + j.w
0041cea1        ecx_62.w = self->width_cells.w
0041cea5        ecx_62.w += 1
0041ceb1        face_first->vertex_1 = ecx_62.w * i_4.w + j.w + 1
0041cec2        face_first->vertex_2 = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
0041ced8        face_first->vertex_3 = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
0041cedc        char* texture_path
0041cedc        if (((j.b ^ i_4.b) & 1) != 0)
0041cf2b        texture_path = texture_a
0041cee2        texture_path = texture_a
0041cef5        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
0041cefc        face_first->uv[0].u = curve_source
0041ceff        face_first->uv[0].v = width_cells_
0041cf04        face_first->uv[1].u = var_50_1
0041cf0d        face_first->uv[1].v = width_cells_
0041cf14        face_first->uv[2].u = var_50_1
0041cf17        face_first->uv[2].v = var_4c_3
0041cf1c        face_first->uv[3].u = curve_source
0041cf1f        face_first->uv[3].v = var_4c_3
0041cfde        bool cond:13_1 = var_48_2 + 1 s< 2
0041cfe1        var_48_2 += 1
0041cfe5        if (not(cond:13_1))
0041cfe5        break
0041ce62        ecx_60 = var_48_2
0041cfeb        j += 1
0041cff4        curve_source = j
0041cff8        do while (j s< self->width_cells)
0041d003        i_4 += 1
0041d006        do while (i_4 s< self->segment_count)
0041d00e        finalize_path_template(self)
0041d01a        return
