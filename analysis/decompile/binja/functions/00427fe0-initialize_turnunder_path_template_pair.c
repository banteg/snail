/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_turnunder_path_template_pair @ 0x427fe0 */

00427ff5        int32_t i_2 = 0
00427ff9        self->kind = PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY
00428000        self->is_mirrored_x = 0
00428004        self->side_exit_mode = 0
00428007        self->width_cells = arg3
0042800a        int16_t x87control
0042800a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(6.28318548f))
00428025        self->width_or_scale = 1f
00428028        self->segment_count = eax_1 + 8
0042802b        self->segment_count_f = fconvert.s(float.t(eax_1 + 8))
0042802e        long double x87_r7_3 = float.t(eax_1)
00428032        float var_50 = fconvert.s(x87_r7_3)
0042803c        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.159154937f))
00428040        allocate_path_template_samples(self)
00428045        self->special_runtime_flag_9c = 0
0042804b        arg3 = 0
0042804f        void* i = nullptr
0042811d        while (i s< 0x3f0)
00428065        *(&self->primary_samples->center_x + i) = fconvert.s(fneg(float.t(self->width_cells) * fconvert.t(0.5f) - fconvert.t(4f)))
0042806f        *(&self->primary_samples->rotation_scalar_98 + i) = 0
00428079        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00428083        *(&self->primary_samples->special_scalar + i) = 0
0042808f        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0042809b        set_matrix_identity(i + self->primary_samples)
004280a3        void* eax_5 = self->primary_samples + i
004280a5        long double x87_r7_9 = float.t(arg3)
004280af        *(eax_5 + 0x30) = *(eax_5 + 0x90)
004280b9        *(&self->primary_samples->transform.position.y + i) = 0
004280c0        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_9)
004280c7        *(&self->primary_samples->delta_length + i) = 0x3f800000
004280d5        set_matrix_identity(i + self->secondary_samples)
004280eb        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
004280f2        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
00428101        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_9)))
00428108        i += 0xa8
00428115        *(i + self->secondary_samples - 0x1c) = 0x3f800000
00428119        arg3 += 1
0042812a        arg3 = eax_1 + 6
0042813f        int32_t edi_1 = (eax_1 + 6) * 0xa8
00428144        int32_t var_40 = edi_1
00428220        int32_t i_1
00428160        *(&self->primary_samples->center_x + edi_1) = fconvert.s(fneg(fconvert.t(4f) - float.t(self->width_cells) * fconvert.t(0.5f)))
0042816a        *(&self->primary_samples->rotation_scalar_98 + edi_1) = 0
00428174        *(&self->primary_samples->rotation_scalar_94 + edi_1) = 0
00428180        *(&self->primary_samples->special_scalar + edi_1) = 0
0042818a        *(&self->primary_samples->lateral_scale + edi_1) = 0x3f800000
00428196        set_matrix_identity(edi_1 + self->primary_samples)
0042819b        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042819e        long double x87_r7_15 = float.t(arg3)
004281b0        *(&primary_samples_2->transform.position + edi_1) = *(&primary_samples_2->center_x + edi_1)
004281b6        *(&self->primary_samples->transform.position.y + edi_1) = 0
004281bd        *(&self->primary_samples->transform.position.z + edi_1) = fconvert.s(x87_r7_15)
004281c6        *(&self->primary_samples->delta_length + edi_1) = 0x3f800000
004281d2        set_matrix_identity(edi_1 + self->secondary_samples)
004281e8        *(&self->secondary_samples->transform.position + edi_1) = *(&self->primary_samples->center_x + edi_1)
004281ef        *(&self->secondary_samples->transform.position.y + edi_1) = 0x3efae148
004281fe        *(&self->secondary_samples->transform.position.z + edi_1) = fconvert.s(fconvert.t(fconvert.s(x87_r7_15)))
00428209        *(&self->secondary_samples->delta_length + edi_1) = 0x3f800000
00428210        edi_1 += 0xa8
00428217        i_1 = 0xfffffffa - eax_1 + arg3 + 1
00428219        arg3 += 1
00428220        do while (i_1 s< 2)
0042822a        arg3 = 0
00428230        if (eax_1 s> 0)
0042823e        void* ebx = 0x3f0
0042845b        bool cond:1_1
00428243        long double x87_r7_17 = float.t(arg3)
00428247        struct PathTemplateSample* primary_samples = self->primary_samples
0042825a        float var_4c_1 = fconvert.s(x87_r7_17 * fconvert.t(-6.28318548f) / fconvert.t(var_50))
00428277        *(&primary_samples->center_x + ebx) = fconvert.s((fconvert.t(*(&primary_samples->center_x + var_40)) - fconvert.t(primary_samples->center_x)) * x87_r7_17 / fconvert.t(var_50) + fconvert.t(primary_samples->center_x))
00428285        *(&self->primary_samples->rotation_scalar_98 + ebx) = 0
0042828f        *(&self->primary_samples->rotation_scalar_94 + ebx) = 0
00428299        *(&self->primary_samples->special_scalar + ebx) = 0
004282a5        *(&self->primary_samples->lateral_scale + ebx) = 0x3f800000
004282af        struct TransformMatrix* transform = ebx + self->primary_samples
004282b1        set_matrix_identity(transform)
004282c0        struct PathTemplateSample* primary_samples_6 = self->primary_samples
004282c3        struct TransformMatrix* transform_1 = transform
004282d0        float var_44_3 = fconvert.s(sine(fconvert.s(fconvert.t(var_4c_1) * fconvert.t(0.5f))))
004282da        long double x87_r7_23 = sine(var_4c_1) * fconvert.t(var_44_3)
004282f6        *(&self->primary_samples->transform.position + ebx) = fconvert.s(fconvert.t(*(&primary_samples_6->center_x + ebx)) - (x87_r7_23 + x87_r7_23))
00428301        *(&self->primary_samples->transform.position.z + ebx) = fconvert.s(float.t(arg3 + 6))
0042831c        *(&self->primary_samples->transform.position.y + ebx) = fconvert.s((fconvert.t(arg2) - cosine(var_4c_1) * fconvert.t(arg2)) * fconvert.t(-0.200000003f))
00428336        float var_44_5 = fconvert.s(cosine(fconvert.s(sine(var_4c_1) * fconvert.t(1.04719758f))))
0042834c        long double st0_7 = sine(fconvert.s(sine(var_4c_1) * fconvert.t(1.04719758f)))
00428366        float* eax_25 = &self->primary_samples->transform.basis_up + ebx
00428371        *eax_25 = fconvert.s(fneg(st0_7))
00428377        eax_25[1] = var_44_5
0042837a        eax_25[2] = 0
0042837d        struct PathTemplateSample* primary_samples_5 = self->primary_samples
0042839f        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position.y + ebx)) - fconvert.t(*(ebx + primary_samples_5 - 0x74)))
004283a6        long double x87_r7_43 = fconvert.t(*(&primary_samples_5->transform.position.z + ebx)) - fconvert.t(*(ebx + primary_samples_5 - 0x70))
004283b0        *(&primary_samples_5->transform.basis_forward + ebx) = fconvert.s(fconvert.t(*(&primary_samples_5->transform.position + ebx)) - fconvert.t(*(ebx + primary_samples_5 - 0x78)))
004283b2        *(&primary_samples_5->transform.basis_forward.y + ebx) = var_2c_1
004283bd        *(&primary_samples_5->transform.basis_forward.z + ebx) = fconvert.s(x87_r7_43)
004283c7        normalize_vector(&self->primary_samples->transform.basis_forward + ebx)
004283d1        struct Vec3* out = ebx + self->primary_samples
004283dc        cross_vectors(out, out + 0x10, out + 0x20)
004283f4        __builtin_memcpy(ebx + self->secondary_samples, ebx + self->primary_samples, 0x40)
004283f6        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00428405        long double x87_r7_47 = fconvert.t(*(&primary_samples_3->transform.basis_up + ebx)) * fconvert.t(0.49000001f)
0042841d        float var_20_1 = fconvert.s(fconvert.t(*(&primary_samples_3->transform.basis_up.y + ebx)) * fconvert.t(0.49000001f))
00428424        long double x87_r6_12 = fconvert.t(*(&primary_samples_3->transform.basis_up.z + ebx)) * fconvert.t(0.49000001f)
0042842a        float* eax_32 = &self->secondary_samples->transform.position + ebx
0042842e        ebx += 0xa8
0042843a        *eax_32 = fconvert.s(x87_r7_47 + fconvert.t(*eax_32))
00428443        eax_32[1] = fconvert.s(fconvert.t(var_20_1) + fconvert.t(eax_32[1]))
0042844d        eax_32[2] = fconvert.s(fconvert.t(fconvert.s(x87_r6_12)) + fconvert.t(eax_32[2]))
00428455        cond:1_1 = arg3 + 1 s< eax_1
00428457        arg3 += 1
0042845b        do while (cond:1_1)
00428461        i_2 = 0
00428469        if (self->segment_count - 1 s> 0)
0042846f        void* edi_4 = nullptr
00428471        struct PathTemplateSample* primary_samples_4 = self->primary_samples
00428495        float var_2c_2 = fconvert.s(fconvert.t(*(edi_4 + primary_samples_4 + 0xdc)) - fconvert.t(*(&primary_samples_4->transform.position.y + edi_4)))
0042849c        long double x87_r7_58 = fconvert.t(*(edi_4 + primary_samples_4 + 0xe0)) - fconvert.t(*(&primary_samples_4->transform.position.z + edi_4))
004284a3        *(&primary_samples_4->delta_dir_to_next + edi_4) = fconvert.s(fconvert.t(*(edi_4 + primary_samples_4 + 0xd8)) - fconvert.t(*(&primary_samples_4->transform.position + edi_4)))
004284a5        *(&primary_samples_4->delta_dir_to_next.y + edi_4) = var_2c_2
004284b0        *(&primary_samples_4->delta_dir_to_next.z + edi_4) = fconvert.s(x87_r7_58)
004284c5        *(&self->primary_samples->delta_length + edi_4) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_4))
004284cc        struct PathTemplateSample* secondary_samples = self->secondary_samples
004284f0        float var_38_2 = fconvert.s(fconvert.t(*(edi_4 + secondary_samples + 0xdc)) - fconvert.t(*(&secondary_samples->transform.position.y + edi_4)))
004284f7        long double x87_r7_65 = fconvert.t(*(edi_4 + secondary_samples + 0xe0)) - fconvert.t(*(&secondary_samples->transform.position.z + edi_4))
004284fe        *(&secondary_samples->delta_dir_to_next + edi_4) = fconvert.s(fconvert.t(*(edi_4 + secondary_samples + 0xd8)) - fconvert.t(*(&secondary_samples->transform.position + edi_4)))
00428500        *(&secondary_samples->delta_dir_to_next.y + edi_4) = var_38_2
0042850b        *(&secondary_samples->delta_dir_to_next.z + edi_4) = fconvert.s(x87_r7_65)
00428520        i_2 += 1
00428521        *(&self->secondary_samples->delta_length + edi_4) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_4))
0042852b        edi_4 += 0xa8
00428534        do while (i_2 s< self->segment_count - 1)
00428564        int32_t* ecx_42 = &self->primary_samples[self->segment_count] - 0x28
00428578        *ecx_42 = 0
0042858e        ecx_42[1] = 0
00428591        ecx_42[2] = 0x3f800000
004285a6        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
004285bc        int32_t* ecx_46 = &self->secondary_samples[self->segment_count] - 0x28
004285c8        *ecx_46 = 0
004285ce        ecx_46[1] = 0
004285d1        ecx_46[2] = 0x3f800000
004285e6        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
004285f9        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0042860b        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
00428610        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
00428613        struct ObjectFaceQuad* facequads = strip_mesh->facequads
00428616        struct Vec3* vertices = strip_mesh->vertices
00428620        int32_t i_3 = 0
00428622        struct Vec3* vertices_1 = vertices
00428628        if (self->segment_count s>= 0)
0042862e        int32_t esi_4 = 0
00428630        uint32_t width_cells = self->width_cells
00428633        float edi_5 = 0f
00428637        arg2 = 0f
0042863b        arg3 = width_cells
0042863f        if (width_cells s>= 0)
00428652        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042865b        long double x87_r7_68 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0042865d        int32_t* eax_63
0042865d        float ecx_57
0042865d        if (i_3 == self->segment_count)
004286b3        void* eax_64 = primary_samples_1 + esi_4
004286c4        vertices = vertices_1
00428709        float var_38_3 = fconvert.s(fconvert.t(*(eax_64 - 0x74)) + fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*(eax_64 - 0xa4)))))
00428711        long double x87_r6_32 = fconvert.t(fconvert.s(fconvert.t(*(eax_64 - 0x70)) + fconvert.t(1f))) + x87_r7_68 * fconvert.t(*(eax_64 - 0xa0))
00428713        eax_63 = &vertices[(width_cells + 1) * i_3 i+ edi_5]
0042871a        *eax_63 = fconvert.s(fconvert.t(*(eax_64 - 0x78)) + fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*(eax_64 - 0xa8)))))
00428724        eax_63[1] = var_38_3
00428727        ecx_57 = fconvert.s(x87_r6_32)
0042865f        float* eax_59 = primary_samples_1 + esi_4
00428687        float var_2c_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(eax_59[1]))) + fconvert.t(eax_59[0xd]))
00428694        float var_28_3 = fconvert.s(x87_r7_68 * fconvert.t(eax_59[2]) + fconvert.t(eax_59[0xe]))
0042869d        eax_63 = &vertices[(width_cells + 1) * i_3 i+ edi_5]
004286a4        *eax_63 = fconvert.s(fconvert.t(fconvert.s(x87_r7_68 * fconvert.t(*eax_59))) + fconvert.t(eax_59[0xc]))
004286aa        eax_63[1] = var_2c_3
004286ad        ecx_57 = var_28_3
0042872d        eax_63[2] = ecx_57
00428730        width_cells = self->width_cells
00428733        edi_5 += 1
00428734        arg3 = width_cells
0042873a        arg2 = edi_5
0042873e        do while (edi_5 s<= width_cells)
00428747        i_3 += 1
00428748        esi_4 += 0xa8
00428750        do while (i_3 s<= self->segment_count)
00428759        int32_t i_4 = 0
0042875d        if (self->segment_count s> 0)
00428766        int32_t j = 0
0042876a        arg2 = 0f
0042876e        if (self->width_cells s> 0)
00428776        int32_t eax_72 = i_4 & 0x80000007
0042877b        if (eax_72 s< 0)
00428781        eax_72 = ((eax_72 - 1) | 0xfffffff8) + 1
00428795        arg3 = fconvert.s(float.t(eax_72) * fconvert.t(0.125f))
004287a3        float var_50_1 = fconvert.s(float.t(eax_72 + 1) * fconvert.t(0.125f))
004287ae        int32_t ecx_61 = 0
004287b4        int32_t var_4c_2 = 0
004287be        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
004287cc        float var_54_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
004287e0        while (true)
004287e0        int32_t eax_79 = ecx_61 + ((self->width_cells * i_4 + j) << 1)
004287e3        if (ecx_61 != 0)
004288a9        int16_t* ebx_3 = eax_79 * 0x30 + facequads
004288ac        *ebx_3 = 0
004288b1        ecx_61.w = self->width_cells.w
004288b5        ecx_61.w += 1
004288be        ebx_3[1] = ecx_61.w * i_4.w + j.w + 1
004288c2        struct ObjectFaceQuad* eax_87
004288c2        eax_87.w = self->width_cells.w
004288c6        eax_87.w += 1
004288cd        ebx_3[2] = eax_87.w * i_4.w + j.w
004288df        ebx_3[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
004288f7        ebx_3[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
004288fb        char* texture_path_1
004288fb        char* arg5
004288fb        if (((j.b ^ i_4.b) & 1) != 0)
00428991        texture_path_1 = arg5
00428908        texture_path_1 = arg5
0042891b        *(ebx_3 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00428922        *(ebx_3 + 0x10) = var_54_1
00428925        *(ebx_3 + 0x14) = arg3
0042892a        *(ebx_3 + 0x18) = arg2
00428933        *(ebx_3 + 0x1c) = arg3
0042893a        *(ebx_3 + 0x20) = arg2
0042893d        *(ebx_3 + 0x24) = var_50_1
00428942        *(ebx_3 + 0x28) = var_54_1
00428945        *(ebx_3 + 0x2c) = var_50_1
004287f7        int16_t* ebx_2 = eax_79 * 0x30 + facequads
004287fa        *ebx_2 = 0
004287ff        eax_79.w = self->width_cells.w
00428803        eax_79.w += 1
0042880a        ebx_2[1] = eax_79.w * i_4.w + j.w
0042880e        int32_t ecx_63
0042880e        ecx_63.w = self->width_cells.w
00428812        ecx_63.w += 1
0042881e        ebx_2[2] = ecx_63.w * i_4.w + j.w + 1
0042882f        ebx_2[3] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w + 1
00428845        ebx_2[4] = (self->width_cells.w + 1) * (i_4.w + 1) + j.w
00428849        char* texture_path
00428849        if (((j.b ^ i_4.b) & 1) != 0)
00428898        texture_path = texture_b
0042884f        texture_path = texture_b
00428862        *(ebx_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
00428869        *(ebx_2 + 0x10) = arg2
0042886c        *(ebx_2 + 0x14) = arg3
00428871        *(ebx_2 + 0x18) = var_54_1
0042887a        *(ebx_2 + 0x1c) = arg3
00428881        *(ebx_2 + 0x20) = var_54_1
00428884        *(ebx_2 + 0x24) = var_50_1
00428889        *(ebx_2 + 0x28) = arg2
0042888c        *(ebx_2 + 0x2c) = var_50_1
0042894d        bool cond:10_1 = var_4c_2 + 1 s< 2
00428950        var_4c_2 += 1
00428954        if (not(cond:10_1))
00428954        break
004287d2        ecx_61 = var_4c_2
0042895a        j += 1
00428963        arg2 = j
00428967        do while (j s< self->width_cells)
00428970        i_4 += 1
00428973        do while (i_4 s< self->segment_count)
00428987        return finalize_path_template(self)
