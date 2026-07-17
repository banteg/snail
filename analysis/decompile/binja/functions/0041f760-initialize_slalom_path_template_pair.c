/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_slalom_path_template_pair @ 0x41f760 */

0041f76c        int32_t i_3 = 0
0041f773        self->width_cells = width_cells_
0041f776        self->kind = PATH_TEMPLATE_KIND_SLALOM
0041f77d        int32_t width_cells_1 = curve_source + 4
0041f782        self->is_mirrored_x = 0
0041f786        self->side_exit_mode = 0
0041f78c        self->width_or_scale = 1f
0041f797        self->segment_count = width_cells_1 + 4
0041f79e        self->segment_count_f = fconvert.s(float.t(width_cells_1 + 4))
0041f7a1        allocate_path_template_samples(self)
0041f7a6        self->has_entry_mesh_transition = 0
0041f7ad        width_cells_ = 0
0041f7b1        void* i = nullptr
0041f861        while (i s< 0x2a0)
0041f7b6        *(&self->primary_samples->center_x + i) = 0
0041f7c0        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041f7ca        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041f7d4        *(&self->primary_samples->special_scalar + i) = 0
0041f7de        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041f7ee        set_matrix_identity(self->primary_samples + i)
0041f7f3        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041f7f6        long double x87_r7_1 = float.t(width_cells_)
0041f808        *(&primary_samples_1->transform.position + i) = *(&primary_samples_1->center_x + i)
0041f80e        *(&self->primary_samples->transform.position.y + i) = 0
0041f815        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
0041f820        set_matrix_identity(i + self->secondary_samples)
0041f836        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0041f83d        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0041f84c        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
0041f850        i += 0xa8
0041f85d        width_cells_ += 1
0041f879        width_cells_ = width_cells_1
0041f880        int32_t edi_3 = width_cells_1 * 0xa8
0041f88c        *(&self->primary_samples->center_x + edi_3) = 0
0041f896        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041f8a0        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041f8aa        *(&self->primary_samples->special_scalar + edi_3) = 0
0041f8b4        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041f8c4        set_matrix_identity(self->primary_samples + edi_3)
0041f8cc        void* eax_12 = self->primary_samples + edi_3
0041f8ce        long double x87_r7_3 = float.t(width_cells_)
0041f8d8        *(eax_12 + 0x30) = *(eax_12 + 0x90)
0041f8e2        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041f8eb        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_3)
0041f8f2        set_matrix_identity(edi_3 + self->secondary_samples)
0041f908        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0041f913        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0041f91e        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_3)))
0041f922        edi_3 += 0xa8
0041f928        width_cells_1 += 1
0041f92b        width_cells_ = width_cells_1
0041f932        do while (0xfffffffc - curve_source + width_cells_1 s< 4)
0041f93c        int32_t width_cells_2 = 0
0041f940        width_cells_ = 0
0041f944        if (curve_source s> 0)
0041f94e        void* edi_4 = 0x2a0
0041f95b        long double x87_r7_7 = float.t(width_cells_) / fconvert.t(fconvert.s(float.t(curve_source)))
0041f96b        long double x87_r7_8 = x87_r7_7 - fconvert.t(0.5f)
0041f971        long double temp1_1 = fconvert.t(0f)
0041f971        x87_r7_8 - temp1_1
0041f97c        float var_48_1
0041f97c        if ((((x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
0041f988        var_48_1 = fconvert.s(x87_r7_8)
0041f982        var_48_1 = fconvert.s(fneg(x87_r7_8))
0041f98c        long double temp2_1 = fconvert.t(0f)
0041f98c        x87_r7_8 - temp2_1
0041f997        if ((((x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0041f999        x87_r7_8 = fneg(x87_r7_8)
0041f9cd        *(&self->primary_samples->center_x + edi_4) = fconvert.s(sine(fconvert.s(x87_r7_7 * fconvert.t(6.28318548f))) * (fconvert.t(1f) - fconvert.t(fconvert.s(x87_r7_8))) * (fconvert.t(1f) - fconvert.t(var_48_1)) * fconvert.t(5f))
0041f9d7        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041f9e1        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0041f9eb        *(&self->primary_samples->special_scalar + edi_4) = 0
0041f9f5        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041fa05        set_matrix_identity(self->primary_samples + edi_4)
0041fa0a        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041fa1a        *(&primary_samples_2->transform.position + edi_4) = *(&primary_samples_2->center_x + edi_4)
0041fa26        long double x87_r7_13 = float.t(width_cells_2 + 4)
0041fa2a        *(&self->primary_samples->transform.position.y + edi_4) = 0
0041fa35        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
0041fa3c        set_matrix_identity(edi_4 + self->secondary_samples)
0041fa58        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
0041fa5f        *(&self->secondary_samples->transform.position.y + edi_4) = 0x3efae148
0041fa6a        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0041fa6e        if (edi_4 s<= 0x2a0)
0041fc12        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
0041fc21        set_matrix_rotation_identity(edi_4 + self->secondary_samples - 0xa8)
0041fa8b        int32_t* eax_25 = self->primary_samples + edi_4 - 0x98
0041fa9e        *eax_25 = 0
0041faa4        eax_25[1] = 0x3f800000
0041faa7        eax_25[2] = 0
0041faaa        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041face        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position.y + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x74)))
0041fad8        long double x87_r7_20 = fconvert.t(*(&primary_samples_4->transform.position.z + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x70))
0041fadf        *(primary_samples_4 + edi_4 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x78)))
0041fae1        *(primary_samples_4 + edi_4 - 0x84) = var_2c_1
0041faec        *(primary_samples_4 + edi_4 - 0x80) = fconvert.s(x87_r7_20)
0041faf9        normalize_vector(self->primary_samples + edi_4 - 0x88)
0041fb01        void* eax_29 = self->primary_samples + edi_4
0041fb21        int32_t var_64_3 = cross_vectors(eax_29 - 0xa8, eax_29 - 0x98, eax_29 - 0x88)
0041fb22        void* eax_31 = self->primary_samples + edi_4
0041fb36        rotate_matrix_local_z(eax_31 - 0xa8, fconvert.s(fconvert.t(*(eax_31 - 0x18)) * fconvert.t(0.261799395f)))
0041fb52        int32_t* edx_22 = edi_4 + self->secondary_samples - 0x98
0041fb65        *edx_22 = 0
0041fb6b        edx_22[1] = 0x3f800000
0041fb6e        edx_22[2] = 0
0041fb71        struct PathTemplateSample* secondary_samples = self->secondary_samples
0041fb95        float var_14_1 = fconvert.s(fconvert.t(*(&secondary_samples->transform.position.y + edi_4)) - fconvert.t(*(edi_4 + secondary_samples - 0x74)))
0041fb9f        long double x87_r7_30 = fconvert.t(*(&secondary_samples->transform.position.z + edi_4)) - fconvert.t(*(edi_4 + secondary_samples - 0x70))
0041fba6        *(edi_4 + secondary_samples - 0x88) = fconvert.s(fconvert.t(*(&secondary_samples->transform.position + edi_4)) - fconvert.t(*(edi_4 + secondary_samples - 0x78)))
0041fba8        *(edi_4 + secondary_samples - 0x84) = var_14_1
0041fbb3        *(edi_4 + secondary_samples - 0x80) = fconvert.s(x87_r7_30)
0041fbc0        normalize_vector(edi_4 + self->secondary_samples - 0x88)
0041fbca        void* eax_35 = edi_4 + self->secondary_samples
0041fbec        int32_t var_64_6 = cross_vectors(eax_35 - 0xa8, eax_35 - 0x98, eax_35 - 0x88)
0041fc01        rotate_matrix_local_z(edi_4 + self->secondary_samples - 0xa8, fconvert.s(fconvert.t(*(self->primary_samples + edi_4 - 0x18)) * fconvert.t(0.261799395f)))
0041fc2a        width_cells_2 += 1
0041fc2b        edi_4 += 0xa8
0041fc33        width_cells_ = width_cells_2
0041fc37        do while (width_cells_2 s< curve_source)
0041fc40        int32_t i_1 = 0
0041fc45        if (self->segment_count - 1 s> 0)
0041fc4b        void* edi_5 = nullptr
0041fc4d        struct PathTemplateSample* primary_samples_3 = self->primary_samples
0041fc71        float var_14_2 = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xdc)) - fconvert.t(*(&primary_samples_3->transform.position.y + edi_5)))
0041fc78        long double x87_r7_40 = fconvert.t(*(edi_5 + primary_samples_3 + 0xe0)) - fconvert.t(*(&primary_samples_3->transform.position.z + edi_5))
0041fc7f        *(&primary_samples_3->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + primary_samples_3 + 0xd8)) - fconvert.t(*(&primary_samples_3->transform.position + edi_5)))
0041fc81        *(&primary_samples_3->delta_dir_to_next.y + edi_5) = var_14_2
0041fc8c        *(&primary_samples_3->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_40)
0041fca1        *(&self->primary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->primary_samples->delta_dir_to_next + edi_5))
0041fca8        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
0041fccc        float var_20_1 = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xdc)) - fconvert.t(*(&secondary_samples_1->transform.position.y + edi_5)))
0041fcd3        long double x87_r7_47 = fconvert.t(*(edi_5 + secondary_samples_1 + 0xe0)) - fconvert.t(*(&secondary_samples_1->transform.position.z + edi_5))
0041fcda        *(&secondary_samples_1->delta_dir_to_next + edi_5) = fconvert.s(fconvert.t(*(edi_5 + secondary_samples_1 + 0xd8)) - fconvert.t(*(&secondary_samples_1->transform.position + edi_5)))
0041fcdc        *(&secondary_samples_1->delta_dir_to_next.y + edi_5) = var_20_1
0041fce7        *(&secondary_samples_1->delta_dir_to_next.z + edi_5) = fconvert.s(x87_r7_47)
0041fcfc        i_1 += 1
0041fcfd        *(&self->secondary_samples->delta_length + edi_5) = fconvert.s(normalize_vector(&self->secondary_samples->delta_dir_to_next + edi_5))
0041fd07        edi_5 += 0xa8
0041fd10        do while (i_1 s< self->segment_count - 1)
0041fd40        int32_t* ecx_55 = &self->primary_samples[self->segment_count] - 0x28
0041fd54        *ecx_55 = 0
0041fd62        ecx_55[1] = 0
0041fd65        ecx_55[2] = 0x3f800000
0041fd77        int32_t var_10_3 = 0x3f800000
0041fd83        *(&self->primary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041fd99        int32_t* eax_54 = &self->secondary_samples[self->segment_count] - 0x28
0041fda1        *eax_54 = 0
0041fda7        eax_54[1] = 0
0041fdac        eax_54[2] = 0x3f800000
0041fdc1        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041fdd4        request_object_vertices(self->bod.object, (self->width_cells + 1) * (self->segment_count + 1))
0041fde6        request_object_facequads(self->bod.object, (self->width_cells * self->segment_count) << 1)
0041fdeb        struct Object* object = self->bod.object
0041fdee        struct Vec3* vertices = object->vertices
0041fdf1        struct ObjectFaceQuad* facequads = object->facequads
0041fdff        int32_t i_2 = 0
0041fe03        if (self->segment_count s>= 0)
0041fe09        int32_t ebx = 0
0041fe0b        uint32_t width_cells = self->width_cells
0041fe0e        int32_t curve_source_1 = 0
0041fe12        curve_source = 0
0041fe16        width_cells_ = width_cells
0041fe1a        if (width_cells s>= 0)
0041fe2d        struct PathTemplateSample* primary_samples = self->primary_samples
0041fe36        long double x87_r7_50 = float.t(curve_source) - float.t(width_cells_) * fconvert.t(0.5f)
0041fe38        if (i_2 == self->segment_count)
0041fe95        void* eax_70 = primary_samples + ebx
0041fee4        i_3 = 0
0041feed        float var_20_2 = fconvert.s(fconvert.t(*(eax_70 - 0x74)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_70 - 0xa4)))))
0041fef5        int32_t* ecx_70 = &vertices[(width_cells + 1) * i_2 + curve_source_1]
0041fefc        long double x87_r6_28 = fconvert.t(fconvert.s(fconvert.t(*(eax_70 - 0x70)) + fconvert.t(1f))) + x87_r7_50 * fconvert.t(*(eax_70 - 0xa0))
0041fefe        *ecx_70 = fconvert.s(fconvert.t(*(eax_70 - 0x78)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_70 - 0xa8)))))
0041ff04        ecx_70[1] = var_20_2
0041ff11        ecx_70[2] = fconvert.s(x87_r6_28)
0041fe3a        float* eax_62 = primary_samples + ebx
0041fe62        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(eax_62[1]))) + fconvert.t(eax_62[0xd]))
0041fe6f        float var_10_4 = fconvert.s(x87_r7_50 * fconvert.t(eax_62[2]) + fconvert.t(eax_62[0xe]))
0041fe7c        int32_t* ecx_68 = &vertices[(width_cells + 1) * i_2 + curve_source_1]
0041fe83        *ecx_68 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*eax_62))) + fconvert.t(eax_62[0xc]))
0041fe89        ecx_68[1] = var_14_3
0041fe90        ecx_68[2] = var_10_4
0041ff14        width_cells = self->width_cells
0041ff17        curve_source_1 += 1
0041ff1a        curve_source = curve_source_1
0041ff1e        width_cells_ = width_cells
0041ff22        do while (curve_source_1 s<= width_cells)
0041ff2b        i_2 += 1
0041ff2c        ebx += 0xa8
0041ff34        do while (i_2 s<= self->segment_count)
0041ff3d        int32_t ebx_1 = 0
0041ff41        if (self->segment_count s> 0)
0041ff4e        while (true)
0041ff4e        curve_source = 0
0041ff54        if (self->width_cells s> 0)
0041ff5c        int32_t eax_82 = ebx_1 & 0x80000007
0041ff61        if (eax_82 s< 0)
0041ff67        eax_82 = ((eax_82 - 1) | 0xfffffff8) + 1
0041ff7b        width_cells_ = fconvert.s(float.t(eax_82) * fconvert.t(0.125f))
0041ff89        float var_4c_2 = fconvert.s(float.t(eax_82 + 1) * fconvert.t(0.125f))
0041ff94        int32_t ecx_71 = 0
0041ff9a        int32_t var_48_3 = 0
0041ffa4        curve_source = fconvert.s(float.t(curve_source) * fconvert.t(0.125f))
0041ffb2        float var_50_1 = fconvert.s(float.t(i_3 + 1) * fconvert.t(0.125f))
0041ffc4        while (true)
0041ffce        int32_t edx_38 = (ecx_71 + ((self->width_cells * ebx_1 + i_3) << 1)) * 0x30
0041ffd3        int16_t* edi_6 = edx_38 + facequads
0041ffd6        *edi_6 = 0
0041ffdb        if (ecx_71 != 0)
00420081        edx_38.w = self->width_cells.w
00420087        edx_38.w += 1
00420092        edi_6[1] = edx_38.w * ebx_1.w + i_3.w + 1
00420096        ecx_71.w = self->width_cells.w
0042009a        ecx_71.w += 1
004200a4        edi_6[2] = ecx_71.w * ebx_1.w + i_3.w
004200b3        edi_6[3] = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w
004200ca        edi_6[4] = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w + 1
004200ce        char* texture_path_1
004200ce        if (((i_3.b ^ ebx_1.b) & 1) != 0)
0042015e        texture_path_1 = texture_b
004200d8        texture_path_1 = texture_b
004200eb        *(edi_6 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path_1, 0, 0)
004200f2        *(edi_6 + 0x10) = var_50_1
004200f5        *(edi_6 + 0x14) = width_cells_
004200fa        *(edi_6 + 0x18) = curve_source
00420103        *(edi_6 + 0x1c) = width_cells_
0042010a        *(edi_6 + 0x20) = curve_source
0042010d        *(edi_6 + 0x24) = var_4c_2
00420112        *(edi_6 + 0x28) = var_50_1
00420115        *(edi_6 + 0x2c) = var_4c_2
0041ffe1        ecx_71.w = self->width_cells.w
0041ffe7        ecx_71.w += 1
0041fff0        edi_6[1] = ecx_71.w * ebx_1.w + i_3.w
0041fff4        edx_38.w = self->width_cells.w
0041fff8        edx_38.w += 1
00420001        edi_6[2] = edx_38.w * ebx_1.w + i_3.w + 1
00420015        edi_6[3] = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w + 1
0042002b        edi_6[4] = (self->width_cells.w + 1) * (ebx_1.w + 1) + i_3.w
0042002f        char* texture_path
0042002f        if (((i_3.b ^ ebx_1.b) & 1) != 0)
0042007e        texture_path = texture_a
00420035        texture_path = texture_a
00420048        *(edi_6 + 0xc) = get_or_create_texture_ref(&g_texture_refs, texture_path, 0, 0)
0042004f        *(edi_6 + 0x10) = curve_source
00420052        *(edi_6 + 0x14) = width_cells_
00420057        *(edi_6 + 0x18) = var_50_1
00420060        *(edi_6 + 0x1c) = width_cells_
00420067        *(edi_6 + 0x20) = var_50_1
0042006a        *(edi_6 + 0x24) = var_4c_2
0042006f        *(edi_6 + 0x28) = curve_source
00420072        *(edi_6 + 0x2c) = var_4c_2
0042011d        bool cond:11_1 = var_48_3 + 1 s< 2
00420120        var_48_3 += 1
00420124        if (not(cond:11_1))
00420124        break
0041ffb8        ecx_71 = var_48_3
0042012a        i_3 += 1
00420133        curve_source = i_3
00420137        do while (i_3 s< self->width_cells)
00420140        ebx_1 += 1
00420143        if (ebx_1 s>= self->segment_count)
00420143        break
0041ff49        i_3 = 0
0042014b        finalize_path_template(self)
00420157        return
