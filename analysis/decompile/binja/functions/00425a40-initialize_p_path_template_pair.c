/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_p_path_template_pair @ 0x425a40 */

00425a5b        self->kind = variant + 0x21
00425a5e        int32_t i_2 = 0
00425a6c        self->segment_count = curve_segments + 2
00425a73        self->is_mirrored_x = 0
00425a77        self->side_exit_mode = 0
00425a7a        self->width_cells = width_cells_
00425a7d        self->width_or_scale = 1f
00425a80        self->segment_count_f = fconvert.s(float.t(curve_segments + 2))
00425a8b        long double x87_r7_3 = (fconvert.t(end_x) - fconvert.t(start_x)) * fconvert.t(0.5f)
00425a91        long double temp1 = fconvert.t(0f)
00425a91        x87_r7_3 - temp1
00425a9c        if ((((x87_r7_3 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00425a9e        x87_r7_3 = fneg(x87_r7_3)
00425aa0        scale_arg = fconvert.s(x87_r7_3)
00425aa6        get_path_nodes(self)
00425aab        struct PathTemplateSample* primary_samples = self->primary_samples
00425ab2        self->has_entry_mesh_transition = 0
00425ab9        primary_samples->center_x = start_x
00425ac2        self->primary_samples->rotation_scalar_98 = 0f
00425acb        self->primary_samples->rotation_scalar_94 = 0f
00425ad4        self->primary_samples->special_scalar = 0f
00425add        self->primary_samples->lateral_scale = 1f
00425ae6        set_matrix_identity(self->primary_samples)
00425aeb        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00425af4        primary_samples_1->transform.position.x = primary_samples_1->center_x
00425afa        self->primary_samples->transform.position.y = 0f
00425b00        self->primary_samples->transform.position.z = 0f
00425b06        set_matrix_identity(self->secondary_samples)
00425b1b        self->secondary_samples->transform.position.x = self->primary_samples->center_x
00425b21        self->secondary_samples->transform.position.y = 0.49000001f
00425b2d        self->secondary_samples->transform.position.z = 0f
00425b46        (&self->primary_samples->center_x)[(curve_segments + 1) * 0x2a] = fconvert.s(fconvert.t(end_x))
00425b50        (&self->primary_samples->rotation_scalar_98)[(curve_segments + 1) * 0x2a] = 0
00425b5a        (&self->primary_samples->rotation_scalar_94)[(curve_segments + 1) * 0x2a] = 0
00425b64        (&self->primary_samples->special_scalar)[(curve_segments + 1) * 0x2a] = 0
00425b6e        (&self->primary_samples->lateral_scale)[(curve_segments + 1) * 0x2a] = 0x3f800000
00425b7a        set_matrix_identity(&self->primary_samples[curve_segments + 1])
00425b7f        struct PathTemplateSample* primary_samples_4 = self->primary_samples
00425b82        long double x87_r7_5 = float.t(curve_segments + 1)
00425b94        (&primary_samples_4->transform.position)[(curve_segments + 1) * 0xe].x = (&primary_samples_4->center_x)[(curve_segments + 1) * 0x2a]
00425b9c        (&self->primary_samples->transform.position.y)[(curve_segments + 1) * 0x2a] = 0
00425ba3        (&self->primary_samples->transform.position.z)[(curve_segments + 1) * 0x2a] = fconvert.s(x87_r7_5)
00425baa        set_matrix_identity(&self->secondary_samples[curve_segments + 1])
00425bc2        (&self->secondary_samples->transform.position)[(curve_segments + 1) * 0xe].x = (&self->primary_samples->center_x)[(curve_segments + 1) * 0x2a]
00425bc6        struct PathTemplateSample* secondary_samples = self->secondary_samples
00425bcd        int32_t curve_index = 0
00425bd1        (&secondary_samples->transform.position.y)[(curve_segments + 1) * 0x2a] = 0x3efae148
00425bde        (&self->secondary_samples->transform.position.z)[(curve_segments + 1) * 0x2a] = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)))
00425be2        if (curve_segments s> 0)
00425bec        void* edi_3 = 0xa8
00425ebe        bool cond:6_1
00425bf9        enum PathTemplateKind kind = self->kind
00425c09        float curve_phase = fconvert.s(float.t(curve_index) * fconvert.t(3.14159274f) / fconvert.t(fconvert.s(float.t(curve_segments))))
00425c0d        if (kind == 0x21)
00425c6e        struct PathTemplateSample* secondary_samples_4 = secondary_samples
00425c8b        *(&self->primary_samples->center_x + edi_3) = fconvert.s(sine(fconvert.s(fconvert.t(curve_phase) + fconvert.t(1.57079637f))) * fconvert.t(scale_arg) - fconvert.t(scale_arg) + fconvert.t(0.5f))
00425c10        if (kind == 0x22)
00425c5b        *(&self->primary_samples->center_x + edi_3) = fconvert.s(fconvert.t(2f) - cosine(curve_phase) * fconvert.t(scale_arg) - fconvert.t(scale_arg) + fconvert.t(0.5f))
00425c13        if (kind == 0x23)
00425c1f        struct PathTemplateSample* secondary_samples_3 = secondary_samples
00425c8b        *(&self->primary_samples->center_x + edi_3) = fconvert.s((sine(fconvert.s(fconvert.t(curve_phase) + fconvert.t(1.57079637f))) + fconvert.t(1f)) * fconvert.t(scale_arg) + fconvert.t(0.5f))
00425c95        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
00425c9f        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
00425ca9        *(&self->primary_samples->special_scalar + edi_3) = 0
00425cb3        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
00425cc3        set_matrix_identity(self->primary_samples + edi_3)
00425cc8        struct PathTemplateSample* primary_samples_5 = self->primary_samples
00425cda        long double x87_r7_26 = float.t(curve_index + 1)
00425cde        *(&primary_samples_5->transform.position + edi_3) = *(&primary_samples_5->center_x + edi_3)
00425cea        *(&self->primary_samples->transform.position.y + edi_3) = 0
00425cf1        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_26)
00425cf8        set_matrix_identity(edi_3 + self->secondary_samples)
00425d10        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
00425d24        *(&self->secondary_samples->transform.position.y + edi_3) = fconvert.s(fconvert.t(*(&self->primary_samples->transform.position.y + edi_3)) + fconvert.t(0.49000001f))
00425d2f        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_26)))
00425d33        if (edi_3 s<= 0xa8)
00425e9a        set_matrix_rotation_identity(self->primary_samples + edi_3 - 0xa8)
00425ea2        secondary_samples = edi_3 + self->secondary_samples - 0xa8
00425ea9        set_matrix_rotation_identity(secondary_samples)
00425d6c        *(self->primary_samples + edi_3 - 0x98) = struct Vec3 {
    .x = 0
    .y = 1f
    .z = 0f
}
00425d6f        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00425d93        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_3->transform.position.y + edi_3)) - fconvert.t(*(primary_samples_3 + edi_3 - 0x74)))
00425d9d        long double x87_r7_35 = fconvert.t(*(&primary_samples_3->transform.position.z + edi_3)) - fconvert.t(*(primary_samples_3 + edi_3 - 0x70))
00425da4        *(primary_samples_3 + edi_3 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_3->transform.position + edi_3)) - fconvert.t(*(primary_samples_3 + edi_3 - 0x78)))
00425da6        *(primary_samples_3 + edi_3 - 0x84) = var_2c_1
00425db1        *(primary_samples_3 + edi_3 - 0x80) = fconvert.s(x87_r7_35)
00425dbe        normalize_vector(self->primary_samples + edi_3 - 0x88)
00425dc8        struct PathTemplateSample* primary_sample_cursor_reloaded = self->primary_samples + edi_3
00425ddf        cross_vectors(primary_sample_cursor_reloaded - 0xa8, primary_sample_cursor_reloaded - 0x98, primary_sample_cursor_reloaded - 0x88)
00425e17        *(edi_3 + self->secondary_samples - 0x98) = struct Vec3 {
    .x = 0
    .y = 1f
    .z = 0f
}
00425e1a        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
00425e3e        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position.y + edi_3)) - fconvert.t(*(edi_3 + secondary_samples_2 - 0x74)))
00425e48        long double x87_r7_43 = fconvert.t(*(&secondary_samples_2->transform.position.z + edi_3)) - fconvert.t(*(edi_3 + secondary_samples_2 - 0x70))
00425e4f        *(edi_3 + secondary_samples_2 - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position + edi_3)) - fconvert.t(*(edi_3 + secondary_samples_2 - 0x78)))
00425e51        *(edi_3 + secondary_samples_2 - 0x84) = var_14_1
00425e5c        *(edi_3 + secondary_samples_2 - 0x80) = fconvert.s(x87_r7_43)
00425e69        normalize_vector(edi_3 + self->secondary_samples - 0x88)
00425e71        struct PathTemplateSample* secondary_sample_cursor_reloaded = self->secondary_samples + edi_3
00425e89        secondary_samples = cross_vectors(secondary_sample_cursor_reloaded - 0xa8, secondary_sample_cursor_reloaded - 0x98, secondary_sample_cursor_reloaded - 0x88)
00425eb2        edi_3 += 0xa8
00425eb8        cond:6_1 = curve_index + 1 s< curve_segments
00425eba        curve_index += 1
00425ebe        do while (cond:6_1)
00425ec7        int32_t i = 0
00425ecc        if (self->segment_count - 1 s> 0)
00425ed2        void* edi_4 = nullptr
00425ed7        void* eax_33 = self->primary_samples + edi_4
00425ef5        float var_14_2 = fconvert.s(fconvert.t(*(eax_33 + 0xdc)) - fconvert.t(*(eax_33 + 0x34)))
00425efc        long double x87_r7_51 = fconvert.t(*(eax_33 + 0xe0)) - fconvert.t(*(eax_33 + 0x38))
00425f03        *(eax_33 + 0x80) = fconvert.s(fconvert.t(*(eax_33 + 0xd8)) - fconvert.t(*(eax_33 + 0x30)))
00425f05        *(eax_33 + 0x84) = var_14_2
00425f10        *(eax_33 + 0x88) = fconvert.s(x87_r7_51)
00425f25        *(&self->primary_samples->delta_length + edi_4) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_4))
00425f2c        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
00425f50        float var_20_1 = fconvert.s(fconvert.t(*(edi_4 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_4)))
00425f57        long double x87_r7_58 = fconvert.t(*(edi_4 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_4))
00425f5e        *(&secondary_samples_1->delta_dir_to_next + edi_4) = fconvert.s(fconvert.t(*(edi_4 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_4)))
00425f60        *(&secondary_samples_1->delta_dir_to_next.y + edi_4) = var_20_1
00425f6b        *(&secondary_samples_1->delta_dir_to_next.z + edi_4) = fconvert.s(x87_r7_58)
00425f80        i += 1
00425f81        *(&self->secondary_samples->delta_length + edi_4) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_4))
00425f8b        edi_4 += 0xa8
00425f94        do while (i s< self->segment_count - 1)
00425fe9        *(&self->primary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
00425ffb        int32_t var_10_3 = 0x3f800000
00426007        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00426030        *(&self->secondary_samples[self->segment_count] - 0x28) = struct Vec3 {
    .x = 0
    .y = 0f
    .z = 1f
}
00426045        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
00426058        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0042606a        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0042606f        struct Object* object = self->bod.object
00426072        int32_t i_1 = 0
00426074        struct Vec3* vertices = object->vertices
00426077        struct ObjectFaceQuad* facequads = object->facequads
0042607d        struct Vec3* mesh_vertices = vertices
00426087        if (self->segment_count s>= 0)
0042608d        uint32_t width_cells = self->width_cells
00426094        int32_t mesh_column = 0
00426098        int32_t mesh_width_cells = width_cells
0042609c        if (width_cells s>= 0)
0042619d        bool cond:8_1
004260af        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004260b8        long double x87_r7_61 = float.t(mesh_column) - float.t(mesh_width_cells) * fconvert.t(0.5f)
004260ba        int32_t* eax_59
004260ba        float ecx_63
004260ba        if (i_1 == self->segment_count)
00426111        void* eax_60 = primary_samples_2 + i_2
00426122        vertices = mesh_vertices
00426167        float var_20_2 = fconvert.s(fconvert.t(*(eax_60 - 0x74)) + fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(*(eax_60 - 0xa4)))))
0042616f        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_60 - 0x70)) + fconvert.t(1f))) + x87_r7_61 * fconvert.t(*(eax_60 - 0xa0))
00426171        eax_59 = &vertices[(width_cells + 1) * i_1 + mesh_column]
00426179        *eax_59 = fconvert.s(fconvert.t(*(eax_60 - 0x78)) + fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(*(eax_60 - 0xa8)))))
00426183        eax_59[1] = var_20_2
00426186        ecx_63 = fconvert.s(x87_r6_20)
004260bc        struct PathTemplateSample* primary_mesh_sample = primary_samples_2 + i_2
004260e4        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(primary_mesh_sample->transform.basis_right.y))) + fconvert.t(primary_mesh_sample->transform.position.y))
004260f1        float var_10_4 = fconvert.s(x87_r7_61 * fconvert.t(primary_mesh_sample->transform.basis_right.z) + fconvert.t(primary_mesh_sample->transform.position.z))
004260fa        eax_59 = &vertices[(width_cells + 1) * i_1 + mesh_column]
00426102        *eax_59 = fconvert.s(fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(primary_mesh_sample->transform.basis_right.x))) + fconvert.t(primary_mesh_sample->transform.position.x))
00426108        eax_59[1] = var_14_3
0042610b        ecx_63 = var_10_4
0042618c        eax_59[2] = ecx_63
0042618f        width_cells = self->width_cells
00426193        mesh_width_cells = width_cells
00426197        cond:8_1 = mesh_column + 1 s<= width_cells
00426199        mesh_column += 1
0042619d        do while (cond:8_1)
004261a6        i_1 += 1
004261a7        i_2 += 0xa8
004261af        do while (i_1 s<= self->segment_count)
004261b5        i_2 = 0
004261bc        if (self->segment_count s> 0)
004261c9        int32_t face_column = 0
004261cd        if (self->width_cells s> 0)
004261d5        int32_t eax_68 = i_2 & 0x80000007
004261da        if (eax_68 s< 0)
004261e0        eax_68 = ((eax_68 - 1) | 0xfffffff8) + 1
004261f4        float v0 = fconvert.s(float.t(eax_68) * fconvert.t(0.125f))
00426202        float v1 = fconvert.s(float.t(eax_68 + 1) * fconvert.t(0.125f))
004263c5        bool cond:12_1
00426213        int32_t face_pass = 0
0042621d        float u0 = fconvert.s(float.t(face_column) * fconvert.t(0.125f))
0042622b        float u1 = fconvert.s(float.t(face_column + 1) * fconvert.t(0.125f))
0042623f        while (true)
0042623f        int32_t eax_75 = face_pass + ((self->width_cells * i_2 + face_column) << 1)
00426242        int32_t face_width_plus_one_eax
00426242        int32_t face_width_plus_one_ecx
00426242        if (face_pass != 0)
00426309        struct ObjectFaceQuad* face_second = &facequads[eax_75]
0042630c        __builtin_memset(face_second, 0, 2)
00426312        face_width_plus_one_ecx.w = self->width_cells.w
00426316        face_width_plus_one_ecx.w += 1
0042631f        face_second->vertex_0 = face_width_plus_one_ecx.w * i_2.w + face_column.w + 1
00426323        face_width_plus_one_eax.w = self->width_cells.w
00426327        face_width_plus_one_eax.w += 1
0042632e        face_second->vertex_1 = face_width_plus_one_eax.w * i_2.w + face_column.w
00426332        face_width_plus_one_ecx.w = self->width_cells.w
00426339        face_width_plus_one_ecx.w += 1
00426340        face_second->vertex_2 = face_width_plus_one_ecx.w * (i_2.w + 1) + face_column.w
00426344        int32_t face_width_plus_one_edx
00426344        face_width_plus_one_edx.w = self->width_cells.w
00426348        face_width_plus_one_edx.w += 1
00426358        face_second->vertex_3 = face_width_plus_one_edx.w * (i_2.w + 1) + face_column.w + 1
0042635c        char* texture_path_1
0042635c        if (((face_column.b ^ i_2.b) & 1) != 0)
004263ec        texture_path_1 = texture_b
00426366        texture_path_1 = texture_b
00426379        face_second->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path_1, nullptr, 0)
00426380        face_second->uv[0].u = u1
00426383        face_second->uv[0].v = v0
00426388        face_second->uv[1].u = u0
00426391        face_second->uv[1].v = v0
00426398        face_second->uv[2].u = u0
0042639b        face_second->uv[2].v = v1
004263a0        face_second->uv[3].u = u1
004263a3        face_second->uv[3].v = v1
00426256        struct ObjectFaceQuad* face_first = &facequads[eax_75]
00426259        __builtin_memset(face_first, 0, 2)
0042625f        face_width_plus_one_eax.w = self->width_cells.w
00426263        face_width_plus_one_eax.w += 1
0042626a        face_first->vertex_0 = face_width_plus_one_eax.w * i_2.w + face_column.w
0042626e        face_width_plus_one_ecx.w = self->width_cells.w
00426272        face_width_plus_one_ecx.w += 1
0042627e        face_first->vertex_1 = face_width_plus_one_ecx.w * i_2.w + face_column.w + 1
00426282        face_width_plus_one_ecx.w = self->width_cells.w
00426286        face_width_plus_one_ecx.w += 1
0042628f        face_first->vertex_2 = face_width_plus_one_ecx.w * (i_2.w + 1) + face_column.w + 1
00426293        face_width_plus_one_ecx.w = self->width_cells.w
00426297        face_width_plus_one_ecx.w += 1
004262a5        face_first->vertex_3 = face_width_plus_one_ecx.w * (i_2.w + 1) + face_column.w
004262a9        char* texture_path
004262a9        if (((face_column.b ^ i_2.b) & 1) != 0)
004262f8        texture_path = texture_a
004262af        texture_path = texture_a
004262c2        face_first->texture_ref = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0)
004262c9        face_first->uv[0].u = u0
004262cc        face_first->uv[0].v = v0
004262d1        face_first->uv[1].u = u1
004262da        face_first->uv[1].v = v0
004262e1        face_first->uv[2].u = u1
004262e4        face_first->uv[2].v = v1
004262e9        face_first->uv[3].u = u0
004262ec        face_first->uv[3].v = v1
004263aa        int32_t face_pass_1 = face_pass + 1
004263b2        if (face_pass_1 s>= 2)
004263b2        break
00426231        face_pass = face_pass_1
004263bf        cond:12_1 = face_column + 1 s< self->width_cells
004263c1        face_column += 1
004263c5        do while (cond:12_1)
004263ce        i_2 += 1
004263d1        do while (i_2 s< self->segment_count)
004263d9        calc_path_length_z(self)
004263e5        return
