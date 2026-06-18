/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_p_path_template_pair @ 0x425a40 */

00425a5b        self->kind = arg2 + 0x21
00425a5e        int32_t i_2 = 0
00425a6c        self->segment_count = &texture_a[2]
00425a73        self->is_mirrored_x = 0
00425a77        self->side_exit_mode = 0
00425a7a        self->width_cells = arg4
00425a7d        self->width_or_scale = 1f
00425a80        self->segment_count_f = fconvert.s(float.t(&texture_a[2]))
00425a8b        long double x87_r7_3 = (fconvert.t(arg6) - fconvert.t(arg5)) * fconvert.t(0.5f)
00425a91        long double temp1 = fconvert.t(0f)
00425a91        x87_r7_3 - temp1
00425a97        void* eax_2
00425a97        eax_2.w = (x87_r7_3 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1 ? 1 : 0) << 0xe | 0x3800
00425a9c        if ((eax_2:1.b & 1) != 0)
00425a9e        x87_r7_3 = fneg(x87_r7_3)
00425aa0        arg3 = fconvert.s(x87_r7_3)
00425aa6        allocate_path_template_samples(self)
00425aab        struct PathTemplateSample* primary_samples = self->primary_samples
00425ab2        self->special_runtime_flag_9c = 0
00425ab9        primary_samples->center_x = arg5
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
00425a54        &texture_a[1]
00425b46        (&self->primary_samples->center_x)[&texture_a[1] * 0x2a] = fconvert.s(fconvert.t(arg6))
00425b50        (&self->primary_samples->rotation_scalar_98)[&texture_a[1] * 0x2a] = 0
00425b5a        (&self->primary_samples->rotation_scalar_94)[&texture_a[1] * 0x2a] = 0
00425b64        (&self->primary_samples->special_scalar)[&texture_a[1] * 0x2a] = 0
00425b6e        (&self->primary_samples->lateral_scale)[&texture_a[1] * 0x2a] = 0x3f800000
00425b7a        set_matrix_identity(&self->primary_samples[&texture_a[1]])
00425b7f        struct PathTemplateSample* primary_samples_4 = self->primary_samples
00425b82        long double x87_r7_5 = float.t(&texture_a[1])
00425b94        primary_samples_4[&texture_a[1]].transform.position.x = (&primary_samples_4->center_x)[&texture_a[1] * 0x2a]
00425b9c        (&self->primary_samples->transform.position.y)[&texture_a[1] * 0x2a] = 0
00425ba3        (&self->primary_samples->transform.position.z)[&texture_a[1] * 0x2a] = fconvert.s(x87_r7_5)
00425baa        set_matrix_identity(&self->secondary_samples[&texture_a[1]])
00425bc0        float ebp = 0f
00425bc2        self->secondary_samples[&texture_a[1]].transform.position.x = (&self->primary_samples->center_x)[&texture_a[1] * 0x2a]
00425bc6        struct PathTemplateSample* secondary_samples = self->secondary_samples
00425bcd        arg5 = 0f
00425bd1        (&secondary_samples->transform.position.y)[&texture_a[1] * 0x2a] = 0x3efae148
00425bde        (&self->secondary_samples->transform.position.z)[&texture_a[1] * 0x2a] = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)))
00425be2        if (texture_a s> 0)
00425bec        void* edi_3 = 0xa8
00425bf9        enum PathTemplateKind kind = self->kind
00425c09        arg5 = fconvert.s(float.t(arg5) * fconvert.t(3.14159274f) / fconvert.t(fconvert.s(float.t(texture_a))))
00425c0d        if (kind == 0x21)
00425c6e        struct PathTemplateSample* secondary_samples_4 = secondary_samples
00425c8b        *(&self->primary_samples->center_x + edi_3) = fconvert.s(sine(fconvert.s(fconvert.t(arg5) + fconvert.t(1.57079637f))) * fconvert.t(arg3) - fconvert.t(arg3) + fconvert.t(0.5f))
00425c10        if (kind == 0x22)
00425c5b        *(&self->primary_samples->center_x + edi_3) = fconvert.s(fconvert.t(2f) - cosine(arg5) * fconvert.t(arg3) - fconvert.t(arg3) + fconvert.t(0.5f))
00425c13        if (kind == 0x23)
00425c1f        struct PathTemplateSample* secondary_samples_3 = secondary_samples
00425c8b        *(&self->primary_samples->center_x + edi_3) = fconvert.s((sine(fconvert.s(fconvert.t(arg5) + fconvert.t(1.57079637f))) + fconvert.t(1f)) * fconvert.t(arg3) + fconvert.t(0.5f))
00425c95        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
00425c9f        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
00425ca9        *(&self->primary_samples->special_scalar + edi_3) = 0
00425cb3        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
00425cc3        set_matrix_identity(self->primary_samples + edi_3)
00425cc8        struct PathTemplateSample* primary_samples_5 = self->primary_samples
00425ccb        ebp += 1
00425cda        long double x87_r7_26 = float.t(ebp)
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
00425d50        int32_t* edx_15 = self->primary_samples + edi_3 - 0x98
00425d63        *edx_15 = 0
00425d69        edx_15[1] = 0x3f800000
00425d6c        edx_15[2] = 0
00425d6f        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00425d93        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_3->transform.position.y + edi_3)) - fconvert.t(*(primary_samples_3 + edi_3 - 0x74)))
00425d9d        long double x87_r7_35 = fconvert.t(*(&primary_samples_3->transform.position.z + edi_3)) - fconvert.t(*(primary_samples_3 + edi_3 - 0x70))
00425da4        *(primary_samples_3 + edi_3 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_3->transform.position + edi_3)) - fconvert.t(*(primary_samples_3 + edi_3 - 0x78)))
00425da6        *(primary_samples_3 + edi_3 - 0x84) = var_2c_1
00425db1        *(primary_samples_3 + edi_3 - 0x80) = fconvert.s(x87_r7_35)
00425dbe        normalize_vector(self->primary_samples + edi_3 - 0x88)
00425dc8        void* eax_26 = self->primary_samples + edi_3
00425ddf        cross_vectors(eax_26 - 0xa8, eax_26 - 0x98, eax_26 - 0x88)
00425dfb        int32_t* eax_27 = edi_3 + self->secondary_samples - 0x98
00425e0e        *eax_27 = 0
00425e14        eax_27[1] = 0x3f800000
00425e17        eax_27[2] = 0
00425e1a        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
00425e3e        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position.y + edi_3)) - fconvert.t(*(edi_3 + secondary_samples_2 - 0x74)))
00425e48        long double x87_r7_43 = fconvert.t(*(&secondary_samples_2->transform.position.z + edi_3)) - fconvert.t(*(edi_3 + secondary_samples_2 - 0x70))
00425e4f        *(edi_3 + secondary_samples_2 - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position + edi_3)) - fconvert.t(*(edi_3 + secondary_samples_2 - 0x78)))
00425e51        *(edi_3 + secondary_samples_2 - 0x84) = var_14_1
00425e5c        *(edi_3 + secondary_samples_2 - 0x80) = fconvert.s(x87_r7_43)
00425e69        normalize_vector(edi_3 + self->secondary_samples - 0x88)
00425e71        void* eax_31 = self->secondary_samples + edi_3
00425e89        secondary_samples = cross_vectors(eax_31 - 0xa8, eax_31 - 0x98, eax_31 - 0x88)
00425eb2        edi_3 += 0xa8
00425eba        arg5 = ebp
00425ebe        do while (ebp s< texture_a)
00425ec7        int32_t i = 0
00425ecc        if (self->segment_count - 1 s> 0)
00425ed2        void* edi_4 = nullptr
00425ed7        void* eax_35 = self->primary_samples + edi_4
00425ef5        float var_14_2 = fconvert.s(fconvert.t(*(eax_35 + 0xdc)) - fconvert.t(*(eax_35 + 0x34)))
00425efc        long double x87_r7_51 = fconvert.t(*(eax_35 + 0xe0)) - fconvert.t(*(eax_35 + 0x38))
00425f03        *(eax_35 + 0x80) = fconvert.s(fconvert.t(*(eax_35 + 0xd8)) - fconvert.t(*(eax_35 + 0x30)))
00425f05        *(eax_35 + 0x84) = var_14_2
00425f10        *(eax_35 + 0x88) = fconvert.s(x87_r7_51)
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
00425fc4        int32_t* edx_31 = &self->primary_samples[self->segment_count] - 0x28
00425fd8        *edx_31 = 0
00425fe6        edx_31[1] = 0
00425fe9        edx_31[2] = 0x3f800000
00425ffb        int32_t var_10_3 = 0x3f800000
00426007        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0042601d        int32_t* ecx_53 = &self->secondary_samples[self->segment_count] - 0x28
00426025        *ecx_53 = 0
0042602b        ecx_53[1] = 0
00426030        ecx_53[2] = 0x3f800000
00426045        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
00426058        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0042606a        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0042606f        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
00426072        int32_t i_1 = 0
00426074        struct Vec3* vertices = strip_mesh->vertices
0042607d        arg5 = vertices
00426083        arg4 = strip_mesh->facequads
00426087        if (self->segment_count s>= 0)
0042608d        uint32_t width_cells = self->width_cells
00426090        uint32_t edi_5 = 0
00426094        arg3 = 0
00426098        texture_a = width_cells
0042609c        if (width_cells s>= 0)
004260af        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004260b8        long double x87_r7_61 = float.t(arg3) - float.t(texture_a) * fconvert.t(0.5f)
004260ba        int32_t* eax_62
004260ba        float ecx_65
004260ba        if (i_1 == self->segment_count)
00426111        void* eax_63 = primary_samples_2 + i_2
00426122        vertices = arg5
00426167        float var_20_2 = fconvert.s(fconvert.t(*(eax_63 - 0x74)) + fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(*(eax_63 - 0xa4)))))
0042616f        long double x87_r6_20 = fconvert.t(fconvert.s(fconvert.t(*(eax_63 - 0x70)) + fconvert.t(1f))) + x87_r7_61 * fconvert.t(*(eax_63 - 0xa0))
00426171        eax_62 = &vertices[(width_cells + 1) * i_1 + edi_5]
00426179        *eax_62 = fconvert.s(fconvert.t(*(eax_63 - 0x78)) + fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(*(eax_63 - 0xa8)))))
00426183        eax_62[1] = var_20_2
00426186        ecx_65 = fconvert.s(x87_r6_20)
004260bc        float* eax_58 = primary_samples_2 + i_2
004260e4        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(eax_58[1]))) + fconvert.t(eax_58[0xd]))
004260f1        float var_10_4 = fconvert.s(x87_r7_61 * fconvert.t(eax_58[2]) + fconvert.t(eax_58[0xe]))
004260fa        eax_62 = &vertices[(width_cells + 1) * i_1 + edi_5]
00426102        *eax_62 = fconvert.s(fconvert.t(fconvert.s(x87_r7_61 * fconvert.t(*eax_58))) + fconvert.t(eax_58[0xc]))
00426108        eax_62[1] = var_14_3
0042610b        ecx_65 = var_10_4
0042618c        eax_62[2] = ecx_65
0042618f        width_cells = self->width_cells
00426192        edi_5 += 1
00426193        texture_a = width_cells
00426199        arg3 = edi_5
0042619d        do while (edi_5 s<= width_cells)
004261a6        i_1 += 1
004261a7        i_2 += 0xa8
004261af        do while (i_1 s<= self->segment_count)
004261b5        i_2 = 0
004261bc        if (self->segment_count s> 0)
004261c5        int32_t j = 0
004261c9        arg3 = 0
004261cd        if (self->width_cells s> 0)
004261d5        char* eax_71 = i_2 & 0x80000007
004261da        if (eax_71 s< 0)
004261e0        eax_71 = ((eax_71 - 1) | 0xfffffff8) + 1
004261f4        texture_a = fconvert.s(float.t(eax_71) * fconvert.t(0.125f))
00426202        arg6 = fconvert.s(float.t(&eax_71[1]) * fconvert.t(0.125f))
0042620d        int32_t ecx_69 = 0
00426213        arg2 = 0
0042621d        arg3 = fconvert.s(float.t(arg3) * fconvert.t(0.125f))
0042622b        arg5 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
0042623f        while (true)
0042623f        int32_t eax_78 = ecx_69 + ((self->width_cells * i_2 + j) << 1)
00426242        if (ecx_69 != 0)
00426309        int16_t* ebp_3 = eax_78 * 0x30 i+ arg4
0042630c        *ebp_3 = 0
00426312        ecx_69.w = self->width_cells.w
00426316        ecx_69.w += 1
0042631f        ebp_3[1] = ecx_69.w * i_2.w + j.w + 1
00426323        float eax_86
00426323        eax_86.w = self->width_cells.w
00426327        eax_86.w += 1
0042632e        ebp_3[2] = eax_86.w * i_2.w + j.w
00426340        ebp_3[3] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
00426358        ebp_3[4] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
0042635c        char* texture_path_1
0042635c        char* arg8
0042635c        if (((j.b ^ i_2.b) & 1) != 0)
004263ec        texture_path_1 = arg8
00426366        texture_path_1 = arg8
00426379        *(ebp_3 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path_1, 0, 0)
00426380        *(ebp_3 + 0x10) = arg5
00426383        *(ebp_3 + 0x14) = texture_a
00426388        *(ebp_3 + 0x18) = arg3
00426391        *(ebp_3 + 0x1c) = texture_a
00426398        *(ebp_3 + 0x20) = arg3
0042639b        *(ebp_3 + 0x24) = arg6
004263a0        *(ebp_3 + 0x28) = arg5
004263a3        *(ebp_3 + 0x2c) = arg6
00426256        int16_t* ebp_2 = eax_78 * 0x30 i+ arg4
00426259        *ebp_2 = 0
0042625f        eax_78.w = self->width_cells.w
00426263        eax_78.w += 1
0042626a        ebp_2[1] = eax_78.w * i_2.w + j.w
0042626e        int32_t ecx_71
0042626e        ecx_71.w = self->width_cells.w
00426272        ecx_71.w += 1
0042627e        ebp_2[2] = ecx_71.w * i_2.w + j.w + 1
0042628f        ebp_2[3] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w + 1
004262a5        ebp_2[4] = (self->width_cells.w + 1) * (i_2.w + 1) + j.w
004262a9        char* texture_path
004262a9        if (((j.b ^ i_2.b) & 1) != 0)
004262f8        texture_path = texture_b
004262af        texture_path = texture_b
004262c2        *(ebp_2 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
004262c9        *(ebp_2 + 0x10) = arg3
004262cc        *(ebp_2 + 0x14) = texture_a
004262d1        *(ebp_2 + 0x18) = arg5
004262da        *(ebp_2 + 0x1c) = texture_a
004262e1        *(ebp_2 + 0x20) = arg5
004262e4        *(ebp_2 + 0x24) = arg6
004262e9        *(ebp_2 + 0x28) = arg3
004262ec        *(ebp_2 + 0x2c) = arg6
004263ab        bool cond:13_1 = arg2 + 1 s< 2
004263ae        arg2 += 1
004263b2        if (not(cond:13_1))
004263b2        break
00426231        ecx_69 = arg2
004263b8        j += 1
004263c1        arg3 = j
004263c5        do while (j s< self->width_cells)
004263ce        i_2 += 1
004263d1        do while (i_2 s< self->segment_count)
004263e5        return finalize_path_template(self)
