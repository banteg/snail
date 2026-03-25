/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_turnoverdouble_path_template_pair @ 0x427640 */

00427655        int32_t i_2 = 0
00427659        self->kind = PATH_TEMPLATE_KIND_TURNOVERDOUBLE
00427660        self->is_mirrored_x = 0
00427664        self->side_exit_mode = 0
00427667        self->width_cells = arg3
0042766a        int16_t x87control
0042766a        int32_t i_6 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(9.42477798f))
00427685        self->width_or_scale = 1f
00427688        self->segment_count = i_6 + 8
0042768b        self->segment_count_f = fconvert.s(float.t(i_6 + 8))
0042768e        long double x87_r7_3 = float.t(i_6)
00427692        float var_48 = fconvert.s(x87_r7_3)
0042769c        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.0795774683f))
004276a0        allocate_path_template_samples(self)
004276a5        self->special_runtime_flag_9c = 0
004276ab        arg3 = 0
004276af        int32_t i = 0
00427777        while (i s< 0x3f0)
004276c3        *(&self->primary_samples->center_x + i) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
004276cd        *(&self->primary_samples->rotation_scalar_98 + i) = 0
004276d7        *(&self->primary_samples->rotation_scalar_94 + i) = 0
004276e1        *(&self->primary_samples->special_scalar + i) = 0
004276eb        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
004276f7        set_matrix_identity(self->primary_samples + i)
004276ff        void* eax_4 = self->primary_samples + i
00427701        long double x87_r7_8 = float.t(arg3)
0042770b        *(eax_4 + 0x30) = *(eax_4 + 0x90)
00427715        *(&self->primary_samples->transform.position.y + i) = 0
0042771c        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_8)
00427723        *(&self->primary_samples->delta_length + i) = 0x3f800000
0042772f        set_matrix_identity(self->secondary_samples + i)
00427745        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0042774c        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0042775b        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_8)))
00427762        i += 0xa8
0042776f        *(self->secondary_samples + i - 0x1c) = 0x3f800000
00427773        arg3 += 1
00427784        arg3 = i_6 + 6
00427799        int32_t edi_3 = (i_6 + 6) * 0xa8
00427870        int32_t i_1
004277b4        *(&self->primary_samples->center_x + edi_3) = fconvert.s(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f))
004277be        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
004277c8        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
004277d2        *(&self->primary_samples->special_scalar + edi_3) = 0
004277dc        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
004277e8        set_matrix_identity(self->primary_samples + edi_3)
004277ed        struct PathTemplateSample* primary_samples_1 = self->primary_samples
004277f0        long double x87_r7_13 = float.t(arg3)
00427802        *(&primary_samples_1->transform.position + edi_3) = *(&primary_samples_1->center_x + edi_3)
00427808        *(&self->primary_samples->transform.position.y + edi_3) = 0
0042780f        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_13)
00427816        *(&self->primary_samples->delta_length + edi_3) = 0x3f800000
00427822        set_matrix_identity(self->secondary_samples + edi_3)
00427838        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0042783f        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0042784e        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
00427859        *(&self->secondary_samples->delta_length + edi_3) = 0x3f800000
00427860        edi_3 += 0xa8
00427867        i_1 = 0xfffffffa - i_6 + arg3 + 1
00427869        arg3 += 1
00427870        do while (i_1 s< 2)
0042787a        arg3 = 0
00427880        if (i_6 s> 0)
0042788e        int32_t ebx = 0x3f0
00427aa4        bool cond:1_1
00427893        long double x87_r7_15 = float.t(arg3)
004278ad        long double x87_r7_17 = x87_r7_15 * fconvert.t(12.566371f) / fconvert.t(var_48)
004278b1        float var_50_1 = fconvert.s(x87_r7_17)
004278b5        long double temp1_1 = fconvert.t(6.28318548f)
004278b5        x87_r7_17 - temp1_1
004278bb        int32_t eax_18
004278bb        eax_18.w = (x87_r7_17 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp1_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp1_1 ? 1 : 0) << 0xe
004278c0        if ((eax_18:1.b & 0x41) == 0)
004278cc        var_50_1 = fconvert.s(fconvert.t(12.566371f) - fconvert.t(var_50_1))
004278da        struct PathTemplateSample* primary_samples_4 = self->primary_samples
004278dd        int32_t i_5 = i_1
004278f1        *(&primary_samples_4->center_x + ebx) = fconvert.s(sine(fconvert.s(fconvert.t(fconvert.s(x87_r7_15 * fconvert.t(6.28318548f) / fconvert.t(var_48))) + fconvert.t(1.57079637f))) * fconvert.t(primary_samples_4->center_x))
00427901        *(&self->primary_samples->rotation_scalar_98 + ebx) = fconvert.s(fneg(fconvert.t(var_50_1)))
0042790b        *(&self->primary_samples->rotation_scalar_94 + ebx) = 0
00427915        *(&self->primary_samples->special_scalar + ebx) = 0
0042791f        *(&self->primary_samples->lateral_scale + ebx) = 0x3f800000
00427929        struct TransformMatrix* transform = self->primary_samples + ebx
0042792b        set_matrix_identity(transform)
0042793a        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042793d        struct TransformMatrix* transform_1 = transform
0042794a        float var_40_4 = fconvert.s(sine(fconvert.s(fconvert.t(var_50_1) * fconvert.t(0.5f))))
00427954        long double x87_r7_30 = sine(var_50_1) * fconvert.t(var_40_4)
00427970        *(&self->primary_samples->transform.position + ebx) = fconvert.s(fconvert.t(*(&primary_samples_5->center_x + ebx)) - (x87_r7_30 + x87_r7_30))
0042797b        *(&self->primary_samples->transform.position.z + ebx) = fconvert.s(float.t(arg3 + 6))
00427996        *(&self->primary_samples->transform.position.y + ebx) = fconvert.s((fconvert.t(arg2) - cosine(var_50_1) * fconvert.t(arg2)) * fconvert.t(0.400000006f))
0042799f        float var_40_6 = fconvert.s(cosine(var_50_1))
004279a4        long double st0_6 = sine(var_50_1)
004279bc        float* ecx_25 = &self->primary_samples->transform.basis_up + ebx
004279c7        *ecx_25 = fconvert.s(st0_6)
004279cd        ecx_25[1] = var_40_6
004279d0        ecx_25[2] = 0
004279d6        void* eax_24 = self->primary_samples + ebx
004279e8        float var_2c_1 = fconvert.s(fconvert.t(*(eax_24 + 0x34)) - fconvert.t(*(eax_24 - 0x74)))
004279f2        float var_28_1 = fconvert.s(fconvert.t(*(eax_24 + 0x38)) - fconvert.t(*(eax_24 - 0x70)))
00427a01        *(eax_24 + 0x20) = fconvert.s(fconvert.t(*(eax_24 + 0x30)) - fconvert.t(*(eax_24 - 0x78)))
00427a07        *(eax_24 + 0x24) = var_2c_1
00427a0a        *(eax_24 + 0x28) = var_28_1
00427a14        normalize_vector(&self->primary_samples->transform.basis_forward + ebx)
00427a1e        struct Vec3* out = self->primary_samples + ebx
00427a29        cross_vectors(out, out + 0x10, out + 0x20)
00427a3d        __builtin_memcpy(self->secondary_samples + ebx, self->primary_samples + ebx, 0x40)
00427a3f        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00427a4e        long double x87_r7_49 = fconvert.t(*(&primary_samples_2->transform.basis_up + ebx)) * fconvert.t(0.49000001f)
00427a5c        i_1 = i_6
00427a66        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_2->transform.basis_up.y + ebx)) * fconvert.t(0.49000001f))
00427a6d        long double x87_r6_7 = fconvert.t(*(&primary_samples_2->transform.basis_up.z + ebx)) * fconvert.t(0.49000001f)
00427a73        float* eax_29 = &self->secondary_samples->transform.position + ebx
00427a77        ebx += 0xa8
00427a83        *eax_29 = fconvert.s(x87_r7_49 + fconvert.t(*eax_29))
00427a8c        eax_29[1] = fconvert.s(fconvert.t(var_20_1) + fconvert.t(eax_29[1]))
00427a96        eax_29[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_7)) + fconvert.t(eax_29[2]))
00427a9e        cond:1_1 = arg3 + 1 s< i_1
00427aa0        arg3 += 1
00427aa4        do while (cond:1_1)
00427aaa        i_2 = 0
00427ab2        if (self->segment_count - 1 s> 0)
00427ab8        int32_t edi_6 = 0
00427aba        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00427ade        float var_2c_2 = fconvert.s(fconvert.t(*(primary_samples_3 + edi_6 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_6)))
00427ae5        long double x87_r7_60 = fconvert.t(*(primary_samples_3 + edi_6 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + edi_6))
00427aec        *(&primary_samples_3->delta_dir_to_next + edi_6) = fconvert.s(fconvert.t(*(primary_samples_3 + edi_6 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + edi_6)))
00427aee        *(&primary_samples_3->delta_dir_to_next.y + edi_6) = var_2c_2
00427af9        *(&primary_samples_3->delta_dir_to_next.z + edi_6) = fconvert.s(x87_r7_60)
00427b0e        *(&self->primary_samples->delta_length + edi_6) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_6))
00427b15        struct PathTemplateSample* secondary_samples = self->secondary_samples
00427b39        float var_38_2 = fconvert.s(fconvert.t(*(secondary_samples + edi_6 + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + edi_6)))
00427b40        long double x87_r7_67 = fconvert.t(*(secondary_samples + edi_6 + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + edi_6))
00427b47        *(&secondary_samples->delta_dir_to_next + edi_6) = fconvert.s(fconvert.t(*(secondary_samples + edi_6 + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + edi_6)))
00427b49        *(&secondary_samples->delta_dir_to_next.y + edi_6) = var_38_2
00427b54        *(&secondary_samples->delta_dir_to_next.z + edi_6) = fconvert.s(x87_r7_67)
00427b69        i_2 += 1
00427b6a        *(&self->secondary_samples->delta_length + edi_6) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_6))
00427b74        edi_6 += 0xa8
00427b7d        do while (i_2 s< self->segment_count - 1)
00427bad        int32_t* ecx_38 = &self->primary_samples[self->segment_count] - 0x28
00427bc1        *ecx_38 = 0
00427bd7        ecx_38[1] = 0
00427bda        ecx_38[2] = 0x3f800000
00427bef        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
00427c05        int32_t* ecx_42 = &self->secondary_samples[self->segment_count] - 0x28
00427c11        *ecx_42 = 0
00427c17        ecx_42[1] = 0
00427c1a        ecx_42[2] = 0x3f800000
00427c2f        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
00427c42        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
00427c54        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
00427c59        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
00427c5c        struct ObjectFaceQuad* facequads = strip_mesh->facequads
00427c5f        struct Vec3* vertices = strip_mesh->vertices
00427c69        int32_t i_3 = 0
00427c6b        struct Vec3* vertices_1 = vertices
00427c71        if (self->segment_count s>= 0)
00427c77        int32_t esi_4 = 0
00427c79        uint32_t width_cells = self->width_cells
00427c7c        float edi_7 = 0f
00427c80        arg2 = 0f
00427c84        arg3 = width_cells
00427c88        if (width_cells s>= 0)
00427c9b        struct PathTemplateSample* primary_samples = self->primary_samples
00427ca4        long double x87_r7_70 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
00427ca6        int32_t* eax_59
00427ca6        float ecx_53
00427ca6        if (i_3 == self->segment_count)
00427cfc        void* eax_60 = primary_samples + esi_4
00427d0d        vertices = vertices_1
00427d52        float var_38_3 = fconvert.s(fconvert.t(*(eax_60 - 0x74)) + fconvert.t(fconvert.s(x87_r7_70 * fconvert.t(*(eax_60 - 0xa4)))))
00427d5a        long double x87_r6_27 = fconvert.t(fconvert.s(fconvert.t(*(eax_60 - 0x70)) + fconvert.t(1f))) + x87_r7_70 * fconvert.t(*(eax_60 - 0xa0))
00427d5c        eax_59 = &vertices[(width_cells + 1) * i_3 i+ edi_7]
00427d63        *eax_59 = fconvert.s(fconvert.t(*(eax_60 - 0x78)) + fconvert.t(fconvert.s(x87_r7_70 * fconvert.t(*(eax_60 - 0xa8)))))
00427d6d        eax_59[1] = var_38_3
00427d70        ecx_53 = fconvert.s(x87_r6_27)
00427ca8        float* eax_55 = primary_samples + esi_4
00427cd0        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_70 * fconvert.t(eax_55[1]))) + fconvert.t(eax_55[0xd]))
00427cdd        float var_28_3 = fconvert.s(x87_r7_70 * fconvert.t(eax_55[2]) + fconvert.t(eax_55[0xe]))
00427ce6        eax_59 = &vertices[(width_cells + 1) * i_3 i+ edi_7]
00427ced        *eax_59 = fconvert.s(fconvert.t(fconvert.s(x87_r7_70 * fconvert.t(*eax_55))) + fconvert.t(eax_55[0xc]))
00427cf3        eax_59[1] = var_2c_3
00427cf6        ecx_53 = var_28_3
00427d76        eax_59[2] = ecx_53
00427d79        width_cells = self->width_cells
00427d7c        edi_7 += 1
00427d7d        arg3 = width_cells
00427d83        arg2 = edi_7
00427d87        do while (edi_7 s<= width_cells)
00427d90        i_3 += 1
00427d91        esi_4 += 0xa8
00427d99        do while (i_3 s<= self->segment_count)
00427da2        int32_t i_4 = 0
00427da6        if (self->segment_count s> 0)
00427daf        int32_t j = 0
00427db3        arg2 = 0f
00427db7        if (self->width_cells s> 0)
00427dbf        int32_t eax_68 = i_4 & 0x80000007
00427dc4        if (eax_68 s< 0)
00427dca        eax_68 = ((eax_68 - 1) | 0xfffffff8) + 1
00427dde        arg3 = fconvert.s(float.t(eax_68) * fconvert.t(0.125f))
00427dec        float var_50_2 = fconvert.s(float.t(eax_68 + 1) * fconvert.t(0.125f))
00427df7        int32_t ecx_57 = 0
00427dfd        int32_t var_48_1 = 0
00427e07        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
00427e15        float var_4c_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
00427e29        while (true)
00427e29        int32_t eax_75 = ecx_57 + ((self->width_cells * i_4 + j) << 1)
00427e2c        if (ecx_57 != 0)
00427ef2        int16_t* ebx_3 = &facequads[eax_75]
00427ef5        *ebx_3 = 0
00427efa        ecx_57.w = self->width_cells.w
00427efe        ecx_57.w += 1
00427f07        ebx_3[1] = ecx_57.w * i_4.w + j.w + 1
00427f0b        struct ObjectFaceQuad* eax_83
00427f0b        eax_83.w = self->width_cells.w
00427f0f        eax_83.w += 1
00427f16        ebx_3[2] = eax_83.w * i_4.w + j.w
00427f28        ebx_3[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
00427f40        ebx_3[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
00427f44        char* texture_path_1
00427f44        char* arg5
00427f44        if (((j.b ^ i_4.b) & 1) != 0)
00427fd4        texture_path_1 = arg5
00427f4e        texture_path_1 = arg5
00427f61        *(ebx_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00427f68        *(ebx_3 + 0x10) = var_4c_1
00427f6b        *(ebx_3 + 0x14) = arg3
00427f70        *(ebx_3 + 0x18) = arg2
00427f79        *(ebx_3 + 0x1c) = arg3
00427f80        *(ebx_3 + 0x20) = arg2
00427f83        *(ebx_3 + 0x24) = var_50_2
00427f88        *(ebx_3 + 0x28) = var_4c_1
00427f8b        *(ebx_3 + 0x2c) = var_50_2
00427e40        int16_t* ebx_2 = &facequads[eax_75]
00427e43        *ebx_2 = 0
00427e48        eax_75.w = self->width_cells.w
00427e4c        eax_75.w += 1
00427e53        ebx_2[1] = eax_75.w * i_4.w + j.w
00427e57        int32_t ecx_59
00427e57        ecx_59.w = self->width_cells.w
00427e5b        ecx_59.w += 1
00427e67        ebx_2[2] = ecx_59.w * i_4.w + j.w + 1
00427e78        ebx_2[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
00427e8e        ebx_2[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
00427e92        char* texture_path
00427e92        if (((j.b ^ i_4.b) & 1) != 0)
00427ee1        texture_path = texture_b
00427e98        texture_path = texture_b
00427eab        *(ebx_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
00427eb2        *(ebx_2 + 0x10) = arg2
00427eb5        *(ebx_2 + 0x14) = arg3
00427eba        *(ebx_2 + 0x18) = var_4c_1
00427ec3        *(ebx_2 + 0x1c) = arg3
00427eca        *(ebx_2 + 0x20) = var_4c_1
00427ecd        *(ebx_2 + 0x24) = var_50_2
00427ed2        *(ebx_2 + 0x28) = arg2
00427ed5        *(ebx_2 + 0x2c) = var_50_2
00427f93        bool cond:10_1 = var_48_1 + 1 s< 2
00427f96        var_48_1 += 1
00427f9a        if (not(cond:10_1))
00427f9a        break
00427e1b        ecx_57 = var_48_1
00427fa0        j += 1
00427fa9        arg2 = j
00427fad        do while (j s< self->width_cells)
00427fb6        i_4 += 1
00427fb9        do while (i_4 s< self->segment_count)
00427fcd        return finalize_path_template(self)
