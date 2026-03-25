/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_supertramp_path_template_pair @ 0x423f10 */

00423f29        self->kind = PATH_TEMPLATE_KIND_SUPERTRAMP
00423f30        self->is_mirrored_x = 0
00423f34        self->side_exit_mode = 0
00423f37        self->width_cells = arg3
00423f3a        int16_t x87control
00423f3a        int32_t eax_1 = __ftol(x87control, fconvert.t(arg2) * fconvert.t(1.04615045f))
00423f56        self->width_or_scale = 1f
00423f59        self->segment_count = eax_1 + 8
00423f5c        self->segment_count_f = fconvert.s(float.t(eax_1 + 7))
00423f5f        long double x87_r7_3 = float.t(eax_1)
00423f6d        arg2 = fconvert.s(x87_r7_3 * fconvert.t(0.95588547f))
00423f71        allocate_path_nodes(self)
00423f76        uint32_t segment_count = self->segment_count
00423f79        self->special_runtime_flag_9c = 0
00423f81        arg3 = 0
00423f85        self->segment_count = segment_count - 1
00423f88        void* i = nullptr
00424045        while (i s< 0x498)
00423f8d        *(&self->primary_samples->center_x + i) = 0
00423f97        *(&self->primary_samples->rotation_scalar_98 + i) = 0
00423fa1        *(&self->primary_samples->rotation_scalar_94 + i) = 0
00423fab        *(&self->primary_samples->special_scalar + i) = 0
00423fb7        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
00423fc3        set_matrix_identity(i + self->primary_samples)
00423fcb        void* eax_7 = self->primary_samples + i
00423fcd        long double x87_r7_5 = float.t(arg3)
00423fd7        *(eax_7 + 0x30) = *(eax_7 + 0x90)
00423fe1        *(&self->primary_samples->transform.position.y + i) = 0
00423fe8        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_5)
00423fef        *(&self->primary_samples->delta_length + i) = 0x3f800000
00423ffd        set_matrix_identity(i + self->secondary_samples)
00424013        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0042401a        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
00424029        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_5)))
00424030        i += 0xa8
0042403d        *(i + self->secondary_samples - 0x1c) = 0x3f800000
00424041        arg3 += 1
0042404f        arg3 = 0
00424055        if (eax_1 s>= 0)
00424095        float var_24_1 = fconvert.s(fconvert.t(arg2) - fconvert.t(0.49000001f))
00424099        void* edi = 0x498
00424264        bool cond:1_1
004240b2        *(&self->primary_samples->center_x + edi) = 0
004240c0        *(&self->primary_samples->rotation_scalar_98 + edi) = 0
004240ca        *(&self->primary_samples->rotation_scalar_94 + edi) = 0
004240d6        *(&self->primary_samples->special_scalar + edi) = 0
004240e0        *(&self->primary_samples->lateral_scale + edi) = 0x3f800000
004240ec        float var_1c_2 = fconvert.s(float.t(arg3) * fconvert.t(1.04615045f) / fconvert.t(fconvert.s(x87_r7_3)))
004240f0        set_matrix_identity(edi + self->primary_samples)
004240f5        struct PathTemplateSample* primary_samples = self->primary_samples
00424107        *(&primary_samples->transform.position + edi) = *(&primary_samples->center_x + edi)
0042411d        *(&self->primary_samples->transform.position.z + edi) = fconvert.s(sine(var_1c_2) * fconvert.t(arg2) + fconvert.t(7f))
00424134        *(&self->primary_samples->transform.position.y + edi) = fconvert.s(fconvert.t(arg2) - cosine(var_1c_2) * fconvert.t(arg2))
0042413f        set_matrix_identity(edi + self->secondary_samples)
00424152        *(&self->secondary_samples->transform.position + edi) = *(&self->primary_samples->center_x + edi)
00424169        *(&self->secondary_samples->transform.position.z + edi) = fconvert.s(sine(var_1c_2) * fconvert.t(var_24_1) + fconvert.t(7f))
00424186        *(&self->secondary_samples->transform.position.y + edi) = fconvert.s(fconvert.t(arg2) - cosine(var_1c_2) * fconvert.t(var_24_1))
0042418d        int32_t* ecx_19 = edi + self->primary_samples
00424197        *ecx_19 = 0x3f800000
0042419d        ecx_19[1] = 0
004241a0        ecx_19[2] = 0
004241a6        *(&self->primary_samples->transform.basis_up + edi) = 0
004241aa        struct PathTemplateSample* primary_samples_1 = self->primary_samples
004241b4        *(&primary_samples_1->transform.basis_up.y + edi) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(&primary_samples_1->transform.position.y + edi)))
004241b7        struct PathTemplateSample* primary_samples_2 = self->primary_samples
004241c7        *(&primary_samples_2->transform.basis_up.z + edi) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&primary_samples_2->transform.position.z + edi)))
004241d1        normalize_vector(&self->primary_samples->transform.basis_up + edi)
004241db        struct Vec3* lhs = edi + self->primary_samples
004241e6        cross_vectors(lhs + 0x20, lhs, lhs + 0x10)
004241f8        int32_t* eax_25 = edi + self->secondary_samples
004241fe        *eax_25 = 0x3f800000
00424204        eax_25[1] = 0
00424207        eax_25[2] = 0
0042420d        *(&self->secondary_samples->transform.basis_up + edi) = 0
00424214        void* eax_27 = self->secondary_samples + edi
00424219        *(eax_27 + 0x14) = fconvert.s(fconvert.t(arg2) - fconvert.t(*(eax_27 + 0x34)))
0042421c        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042422c        *(&secondary_samples->transform.basis_up.z + edi) = fconvert.s(fconvert.t(7f) - fconvert.t(*(&secondary_samples->transform.position.z + edi)))
00424236        normalize_vector(&self->secondary_samples->transform.basis_up + edi)
0042423e        struct Vec3* lhs_1 = self->secondary_samples + edi
0042424a        cross_vectors(lhs_1 + 0x20, lhs_1, lhs_1 + 0x10)
00424258        edi += 0xa8
0042425e        cond:1_1 = arg3 + 1 s<= eax_1
00424260        arg3 += 1
00424264        do while (cond:1_1)
0042426d        int32_t i_1 = 0
00424271        if (self->segment_count s> 0)
00424277        void* edi_1 = nullptr
00424279        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0042429d        float var_8_1 = fconvert.s(fconvert.t(*(edi_1 + primary_samples_3 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_1)))
004242a4        long double x87_r7_41 = fconvert.t(*(edi_1 + primary_samples_3 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + edi_1))
004242ab        *(&primary_samples_3->delta_dir_to_next + edi_1) = fconvert.s(fconvert.t(*(edi_1 + primary_samples_3 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + edi_1)))
004242ad        *(&primary_samples_3->delta_dir_to_next.y + edi_1) = var_8_1
004242b8        *(&primary_samples_3->delta_dir_to_next.z + edi_1) = fconvert.s(x87_r7_41)
004242cd        *(&self->primary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_1))
004242d4        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
004242f8        float var_14_1 = fconvert.s(fconvert.t(*(edi_1 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_1)))
004242ff        long double x87_r7_48 = fconvert.t(*(edi_1 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_1))
00424306        *(&secondary_samples_1->delta_dir_to_next + edi_1) = fconvert.s(fconvert.t(*(edi_1 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_1)))
00424308        *(&secondary_samples_1->delta_dir_to_next.y + edi_1) = var_14_1
00424313        *(&secondary_samples_1->delta_dir_to_next.z + edi_1) = fconvert.s(x87_r7_48)
00424328        i_1 += 1
00424329        *(&self->secondary_samples->delta_length + edi_1) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_1))
00424333        edi_1 += 0xa8
0042433b        do while (i_1 s< self->segment_count)
00424350        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
00424362        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
00424367        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0042436a        int32_t i_2 = 0
0042436c        arg3 = 0
00424370        struct Vec3* vertices = strip_mesh->vertices
00424377        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0042437d        struct ObjectFaceQuad* facequads_1 = facequads
00424383        if (self->segment_count s>= 0)
00424389        int32_t var_28_1 = 0
0042438d        uint32_t width_cells = self->width_cells
00424390        float edi_2 = 0f
00424394        arg2 = 0f
00424398        uint32_t width_cells_1 = width_cells
0042439c        if (width_cells s>= 0)
004243b1        float* eax_44 = self->primary_samples + var_28_1
004243b3        i_2 = arg3
004243bd        long double x87_r7_51 = float.t(arg2) - float.t(width_cells_1) * fconvert.t(0.5f)
004243e5        float var_8_2 = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(eax_44[1]))) + fconvert.t(eax_44[0xd]))
004243f2        float var_4_2 = fconvert.s(x87_r7_51 * fconvert.t(eax_44[2]) + fconvert.t(eax_44[0xe]))
004243f6        int32_t eax_47 = (width_cells + 1) * i_2 i+ edi_2
004243f8        edi_2 += 1
004243f9        arg2 = edi_2
00424404        int32_t* ecx_39 = &vertices[eax_47]
0042440b        *ecx_39 = fconvert.s(fconvert.t(fconvert.s(x87_r7_51 * fconvert.t(*eax_44))) + fconvert.t(eax_44[0xc]))
00424411        ecx_39[1] = var_8_2
00424418        ecx_39[2] = var_4_2
0042441b        width_cells = self->width_cells
00424420        width_cells_1 = width_cells
00424424        do while (edi_2 s<= width_cells)
00424431        i_2 += 1
0042443a        arg3 = i_2
0042443e        var_28_1 += 0xa8
00424442        do while (i_2 s<= self->segment_count)
0042444b        int32_t i_3 = 0
0042444f        if (self->segment_count s> 0)
00424458        int32_t j = 0
0042445c        arg2 = 0f
00424460        if (self->width_cells s> 0)
00424468        int32_t eax_56 = i_3 & 0x80000007
0042446d        if (eax_56 s< 0)
00424473        eax_56 = ((eax_56 - 1) | 0xfffffff8) + 1
00424487        arg3 = fconvert.s(float.t(eax_56) * fconvert.t(0.125f))
00424495        float var_28_2 = fconvert.s(float.t(eax_56 + 1) * fconvert.t(0.125f))
004244a4        int32_t ecx_42 = 0
004244aa        int32_t var_24_2 = 0
004244b4        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
004244c2        float var_2c_1 = fconvert.s(float.t(j + 1) * fconvert.t(0.125f))
004244dc        while (true)
004244dc        int32_t eax_64 = ecx_42 + ((self->width_cells * i_3 + j) << 1)
004244df        if (ecx_42 != 0)
004245b0        int16_t* ebp_2 = eax_64 * 0x30 + facequads
004245b3        *ebp_2 = 0
004245b9        ecx_42.w = self->width_cells.w
004245bd        ecx_42.w += 1
004245c6        ebp_2[1] = ecx_42.w * i_3.w + j.w + 1
004245ca        int32_t eax_74
004245ca        eax_74.w = self->width_cells.w
004245ce        eax_74.w += 1
004245d5        ebp_2[2] = eax_74.w * i_3.w + j.w
004245e7        ebp_2[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
004245ff        ebp_2[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
00424603        char* texture_path_1
00424603        if (((j.b ^ i_3.b) & 1) != 0)
00424699        texture_path_1 = texture_c
0042460d        texture_path_1 = texture_c
00424620        *(ebp_2 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
00424627        *(ebp_2 + 0x10) = var_2c_1
0042462a        *(ebp_2 + 0x14) = arg3
0042462f        *(ebp_2 + 0x18) = arg2
00424638        *(ebp_2 + 0x1c) = arg3
0042463f        *(ebp_2 + 0x20) = arg2
00424642        *(ebp_2 + 0x24) = var_28_2
00424647        *(ebp_2 + 0x28) = var_2c_1
0042464a        *(ebp_2 + 0x2c) = var_28_2
004244eb        int16_t* ebp_1 = eax_64 * 0x30 + facequads
004244ee        *ebp_1 = 0
004244f4        facequads.w = self->width_cells.w
004244f8        facequads.w += 1
004244ff        ebp_1[1] = facequads.w * i_3.w + j.w
00424503        eax_64.w = self->width_cells.w
00424507        eax_64.w += 1
00424513        ebp_1[2] = eax_64.w * i_3.w + j.w + 1
00424524        ebp_1[3] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w + 1
00424533        ebp_1[4] = (self->width_cells.w + 1) * (i_3.w + 1) + j.w
0042453d        char* texture_path
0042453d        if (i_3 != self->segment_count - 1)
0042458e        int32_t var_40_8 = 0
00424592        int32_t var_44_6 = 0
00424597        if (((j.b ^ i_3.b) & 1) != 0)
00424547        texture_path = texture_b
0042459d        texture_path = texture_b
00424543        int32_t var_40_7 = 0
00424545        int32_t var_44_5 = 0
00424547        char* texture_path_2
00424547        texture_path = texture_path_2
0042455a        *(ebp_1 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
00424561        *(ebp_1 + 0x10) = arg2
00424564        *(ebp_1 + 0x14) = arg3
00424569        *(ebp_1 + 0x18) = var_2c_1
00424572        *(ebp_1 + 0x1c) = arg3
00424579        *(ebp_1 + 0x20) = var_2c_1
0042457c        *(ebp_1 + 0x24) = var_28_2
00424581        *(ebp_1 + 0x28) = arg2
00424584        *(ebp_1 + 0x2c) = var_28_2
00424652        bool cond:9_1 = var_24_2 + 1 s< 2
00424655        var_24_2 += 1
00424659        if (not(cond:9_1))
00424659        break
004244c8        ecx_42 = var_24_2
004244cc        facequads = facequads_1
0042465f        j += 1
00424666        facequads = facequads_1
0042466c        arg2 = j
00424670        do while (j s< self->width_cells)
0042467b        i_3 += 1
0042467e        do while (i_3 s< self->segment_count)
00424692        return finalize_path_template_record(self)
