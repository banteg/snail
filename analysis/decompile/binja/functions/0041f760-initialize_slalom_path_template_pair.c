/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_slalom_path_template_pair @ 0x41f760 */

0041f76c        int32_t i_3 = 0
0041f773        self->width_cells = arg3
0041f776        self->kind = 0x16
0041f77d        uint32_t ebx = arg2 + 4
0041f782        self->is_mirrored_x = 0
0041f786        self->side_exit_mode = 0
0041f78c        self->width_or_scale = 1f
0041f797        self->segment_count = ebx + 4
0041f79e        self->segment_count_f = fconvert.s(float.t(ebx + 4))
0041f7a1        allocate_path_nodes(self)
0041f7a6        self->special_runtime_flag_9c = 0
0041f7ad        arg3 = 0
0041f7b1        void* i = nullptr
0041f861        while (i s< 0x2a0)
0041f7b6        *(&self->primary_samples->center_x + i) = 0
0041f7c0        *(&self->primary_samples->rotation_scalar_98 + i) = 0
0041f7ca        *(&self->primary_samples->rotation_scalar_94 + i) = 0
0041f7d4        *(&self->primary_samples->special_scalar + i) = 0
0041f7de        *(&self->primary_samples->lateral_scale + i) = 0x3f800000
0041f7ee        set_matrix_identity(self->primary_samples + i)
0041f7f3        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0041f7f6        long double x87_r7_1 = float.t(arg3)
0041f808        *(&primary_samples_1->transform.position + i) = *(&primary_samples_1->center_x + i)
0041f80e        *(&self->primary_samples->transform.position.y + i) = 0
0041f815        *(&self->primary_samples->transform.position.z + i) = fconvert.s(x87_r7_1)
0041f820        set_matrix_identity(i + self->secondary_samples)
0041f836        *(&self->secondary_samples->transform.position + i) = *(&self->primary_samples->center_x + i)
0041f83d        *(&self->secondary_samples->transform.position.y + i) = 0x3efae148
0041f84c        *(&self->secondary_samples->transform.position.z + i) = fconvert.s(fconvert.t(fconvert.s(x87_r7_1)))
0041f850        i += 0xa8
0041f85d        arg3 += 1
0041f879        arg3 = ebx
0041f880        int32_t edi_3 = ebx * 0xa8
0041f88c        *(&self->primary_samples->center_x + edi_3) = 0
0041f896        *(&self->primary_samples->rotation_scalar_98 + edi_3) = 0
0041f8a0        *(&self->primary_samples->rotation_scalar_94 + edi_3) = 0
0041f8aa        *(&self->primary_samples->special_scalar + edi_3) = 0
0041f8b4        *(&self->primary_samples->lateral_scale + edi_3) = 0x3f800000
0041f8c4        set_matrix_identity(self->primary_samples + edi_3)
0041f8cc        void* eax_12 = self->primary_samples + edi_3
0041f8ce        long double x87_r7_3 = float.t(arg3)
0041f8d8        *(eax_12 + 0x30) = *(eax_12 + 0x90)
0041f8e2        *(&self->primary_samples->transform.position.y + edi_3) = 0
0041f8eb        *(&self->primary_samples->transform.position.z + edi_3) = fconvert.s(x87_r7_3)
0041f8f2        set_matrix_identity(edi_3 + self->secondary_samples)
0041f908        *(&self->secondary_samples->transform.position + edi_3) = *(&self->primary_samples->center_x + edi_3)
0041f913        *(&self->secondary_samples->transform.position.y + edi_3) = 0x3efae148
0041f91e        *(&self->secondary_samples->transform.position.z + edi_3) = fconvert.s(fconvert.t(fconvert.s(x87_r7_3)))
0041f922        edi_3 += 0xa8
0041f928        ebx += 1
0041f92b        arg3 = ebx
0041f932        do while (0xfffffffc - arg2 + ebx s< 4)
0041f93c        uint32_t ebx_1 = 0
0041f940        arg3 = 0
0041f944        if (arg2 s> 0)
0041f94e        void* edi_4 = 0x2a0
0041f95b        long double x87_r7_7 = float.t(arg3) / fconvert.t(fconvert.s(float.t(arg2)))
0041f96b        long double x87_r7_8 = x87_r7_7 - fconvert.t(0.5f)
0041f971        long double temp1_1 = fconvert.t(0f)
0041f971        x87_r7_8 - temp1_1
0041f977        int32_t eax_17
0041f977        eax_17.w = (x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe | 0x3800
0041f97c        float var_48_1
0041f97c        if ((eax_17:1.b & 1) == 0)
0041f988        var_48_1 = fconvert.s(x87_r7_8)
0041f982        var_48_1 = fconvert.s(fneg(x87_r7_8))
0041f98c        long double temp2_1 = fconvert.t(0f)
0041f98c        x87_r7_8 - temp2_1
0041f992        eax_17.w = (x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe | 0x3800
0041f997        if ((eax_17:1.b & 1) != 0)
0041f999        x87_r7_8 = fneg(x87_r7_8)
0041f9cd        *(&self->primary_samples->center_x + edi_4) = fconvert.s(sine(fconvert.s(x87_r7_7 * fconvert.t(6.28318548f))) * (fconvert.t(1f) - fconvert.t(fconvert.s(x87_r7_8))) * (fconvert.t(1f) - fconvert.t(var_48_1)) * fconvert.t(5f))
0041f9d7        *(&self->primary_samples->rotation_scalar_98 + edi_4) = 0
0041f9e1        *(&self->primary_samples->rotation_scalar_94 + edi_4) = 0
0041f9eb        *(&self->primary_samples->special_scalar + edi_4) = 0
0041f9f5        *(&self->primary_samples->lateral_scale + edi_4) = 0x3f800000
0041fa05        set_matrix_identity(self->primary_samples + edi_4)
0041fa0a        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0041fa1a        *(&primary_samples_2->transform.position + edi_4) = *(&primary_samples_2->center_x + edi_4)
0041fa26        long double x87_r7_13 = float.t(ebx_1 + 4)
0041fa2a        *(&self->primary_samples->transform.position.y + edi_4) = 0
0041fa35        *(&self->primary_samples->transform.position.z + edi_4) = fconvert.s(x87_r7_13)
0041fa3c        set_matrix_identity(edi_4 + self->secondary_samples)
0041fa58        *(&self->secondary_samples->transform.position + edi_4) = *(&self->primary_samples->center_x + edi_4)
0041fa5f        *(&self->secondary_samples->transform.position.y + edi_4) = 0x3efae148
0041fa6a        *(&self->secondary_samples->transform.position.z + edi_4) = fconvert.s(fconvert.t(fconvert.s(x87_r7_13)))
0041fa6e        if (edi_4 s<= 0x2a0)
0041fc12        set_matrix_rotation_identity(self->primary_samples + edi_4 - 0xa8)
0041fc21        set_matrix_rotation_identity(edi_4 + self->secondary_samples - 0xa8)
0041fa8b        int32_t* eax_24 = self->primary_samples + edi_4 - 0x98
0041fa9e        *eax_24 = 0
0041faa4        eax_24[1] = 0x3f800000
0041faa7        eax_24[2] = 0
0041faaa        struct PathTemplateSample* primary_samples_4 = self->primary_samples
0041face        float var_2c_1 = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position.y + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x74)))
0041fad8        long double x87_r7_20 = fconvert.t(*(&primary_samples_4->transform.position.z + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x70))
0041fadf        *(primary_samples_4 + edi_4 - 0x88) = fconvert.s(fconvert.t(*(&primary_samples_4->transform.position + edi_4)) - fconvert.t(*(primary_samples_4 + edi_4 - 0x78)))
0041fae1        *(primary_samples_4 + edi_4 - 0x84) = var_2c_1
0041faec        *(primary_samples_4 + edi_4 - 0x80) = fconvert.s(x87_r7_20)
0041faf9        normalize_vector(self->primary_samples + edi_4 - 0x88)
0041fb01        void* eax_28 = self->primary_samples + edi_4
0041fb21        int32_t var_64_3 = cross_vectors(eax_28 - 0xa8, eax_28 - 0x98, eax_28 - 0x88)
0041fb22        void* eax_30 = self->primary_samples + edi_4
0041fb36        rotate_matrix_world_z(eax_30 - 0xa8, fconvert.s(fconvert.t(*(eax_30 - 0x18)) * fconvert.t(0.261799395f)))
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
0041fbca        void* eax_34 = edi_4 + self->secondary_samples
0041fbec        int32_t var_64_6 = cross_vectors(eax_34 - 0xa8, eax_34 - 0x98, eax_34 - 0x88)
0041fc01        rotate_matrix_world_z(edi_4 + self->secondary_samples - 0xa8, fconvert.s(fconvert.t(*(self->primary_samples + edi_4 - 0x18)) * fconvert.t(0.261799395f)))
0041fc2a        ebx_1 += 1
0041fc2b        edi_4 += 0xa8
0041fc33        arg3 = ebx_1
0041fc37        do while (ebx_1 s< arg2)
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
0041fd99        int32_t* eax_53 = &self->secondary_samples[self->segment_count] - 0x28
0041fda1        *eax_53 = 0
0041fda7        eax_53[1] = 0
0041fdac        eax_53[2] = 0x3f800000
0041fdc1        *(&self->secondary_samples[self->segment_count] - 0x1c) = 0x3f800000
0041fdd4        request_object_vertices(self->strip_mesh, (self->width_cells + 1) * (self->segment_count + 1))
0041fde6        request_object_facequads(self->strip_mesh, (self->width_cells * self->segment_count) << 1)
0041fdeb        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0041fdee        struct Vec3* vertices = strip_mesh->vertices
0041fdf1        struct ObjectFaceQuad* facequads = strip_mesh->facequads
0041fdff        int32_t i_2 = 0
0041fe03        if (self->segment_count s>= 0)
0041fe09        int32_t ebx_2 = 0
0041fe0b        uint32_t width_cells = self->width_cells
0041fe0e        int32_t edi_6 = 0
0041fe12        arg2 = 0
0041fe16        arg3 = width_cells
0041fe1a        if (width_cells s>= 0)
0041fe2d        struct PathTemplateSample* primary_samples = self->primary_samples
0041fe36        long double x87_r7_50 = float.t(arg2) - float.t(arg3) * fconvert.t(0.5f)
0041fe38        if (i_2 == self->segment_count)
0041fe95        void* eax_69 = primary_samples + ebx_2
0041fee4        i_3 = 0
0041feed        float var_20_2 = fconvert.s(fconvert.t(*(eax_69 - 0x74)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_69 - 0xa4)))))
0041fef5        int32_t* ecx_70 = &vertices[(width_cells + 1) * i_2 + edi_6]
0041fefc        long double x87_r6_28 = fconvert.t(fconvert.s(fconvert.t(*(eax_69 - 0x70)) + fconvert.t(1f))) + x87_r7_50 * fconvert.t(*(eax_69 - 0xa0))
0041fefe        *ecx_70 = fconvert.s(fconvert.t(*(eax_69 - 0x78)) + fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*(eax_69 - 0xa8)))))
0041ff04        ecx_70[1] = var_20_2
0041ff11        ecx_70[2] = fconvert.s(x87_r6_28)
0041fe3a        float* eax_61 = primary_samples + ebx_2
0041fe62        float var_14_3 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(eax_61[1]))) + fconvert.t(eax_61[0xd]))
0041fe6f        float var_10_4 = fconvert.s(x87_r7_50 * fconvert.t(eax_61[2]) + fconvert.t(eax_61[0xe]))
0041fe7c        int32_t* ecx_68 = &vertices[(width_cells + 1) * i_2 + edi_6]
0041fe83        *ecx_68 = fconvert.s(fconvert.t(fconvert.s(x87_r7_50 * fconvert.t(*eax_61))) + fconvert.t(eax_61[0xc]))
0041fe89        ecx_68[1] = var_14_3
0041fe90        ecx_68[2] = var_10_4
0041ff14        width_cells = self->width_cells
0041ff17        edi_6 += 1
0041ff1a        arg2 = edi_6
0041ff1e        arg3 = width_cells
0041ff22        do while (edi_6 s<= width_cells)
0041ff2b        i_2 += 1
0041ff2c        ebx_2 += 0xa8
0041ff34        do while (i_2 s<= self->segment_count)
0041ff3d        int32_t ebx_3 = 0
0041ff41        if (self->segment_count s> 0)
0041ff4e        while (true)
0041ff4e        arg2 = 0
0041ff54        if (self->width_cells s> 0)
0041ff5c        uint32_t eax_81 = ebx_3 & 0x80000007
0041ff61        if (eax_81 s< 0)
0041ff67        eax_81 = ((eax_81 - 1) | 0xfffffff8) + 1
0041ff7b        arg3 = fconvert.s(float.t(eax_81) * fconvert.t(0.125f))
0041ff89        float var_4c_2 = fconvert.s(float.t(eax_81 + 1) * fconvert.t(0.125f))
0041ff94        int32_t ecx_71 = 0
0041ff9a        int32_t var_48_3 = 0
0041ffa4        arg2 = fconvert.s(float.t(arg2) * fconvert.t(0.125f))
0041ffb2        float var_50_1 = fconvert.s(float.t(i_3 + 1) * fconvert.t(0.125f))
0041ffc4        while (true)
0041ffd3        int16_t* edi_7 = &facequads[ecx_71 + ((self->width_cells * ebx_3 + i_3) << 1)]
0041ffd6        *edi_7 = 0
0041ffdb        int32_t edx_38
0041ffdb        if (ecx_71 != 0)
00420081        edx_38.w = self->width_cells.w
00420087        edx_38.w += 1
00420092        edi_7[1] = edx_38.w * ebx_3.w + i_3.w + 1
00420096        ecx_71.w = self->width_cells.w
0042009a        ecx_71.w += 1
004200a4        edi_7[2] = ecx_71.w * ebx_3.w + i_3.w
004200b3        edi_7[3] = (self->width_cells.w + 1) * (ebx_3.w + 1) + i_3.w
004200ca        edi_7[4] = (self->width_cells.w + 1) * (ebx_3.w + 1) + i_3.w + 1
004200ce        char* texture_path_1
004200ce        char* arg5
004200ce        if (((i_3.b ^ ebx_3.b) & 1) != 0)
0042015e        texture_path_1 = arg5
004200d8        texture_path_1 = arg5
004200eb        *(edi_7 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path_1, 0, 0)
004200f2        *(edi_7 + 0x10) = var_50_1
004200f5        *(edi_7 + 0x14) = arg3
004200fa        *(edi_7 + 0x18) = arg2
00420103        *(edi_7 + 0x1c) = arg3
0042010a        *(edi_7 + 0x20) = arg2
0042010d        *(edi_7 + 0x24) = var_4c_2
00420112        *(edi_7 + 0x28) = var_50_1
00420115        *(edi_7 + 0x2c) = var_4c_2
0041ffe1        ecx_71.w = self->width_cells.w
0041ffe7        ecx_71.w += 1
0041fff0        edi_7[1] = ecx_71.w * ebx_3.w + i_3.w
0041fff4        edx_38.w = self->width_cells.w
0041fff8        edx_38.w += 1
00420001        edi_7[2] = edx_38.w * ebx_3.w + i_3.w + 1
00420015        edi_7[3] = (self->width_cells.w + 1) * (ebx_3.w + 1) + i_3.w + 1
0042002b        edi_7[4] = (self->width_cells.w + 1) * (ebx_3.w + 1) + i_3.w
0042002f        char* texture_path
0042002f        if (((i_3.b ^ ebx_3.b) & 1) != 0)
0042007e        texture_path = texture_b
00420035        texture_path = texture_b
00420048        *(edi_7 + 0xc) = get_or_create_texture_ref(&data_4b7790, texture_path, 0, 0)
0042004f        *(edi_7 + 0x10) = arg2
00420052        *(edi_7 + 0x14) = arg3
00420057        *(edi_7 + 0x18) = var_50_1
00420060        *(edi_7 + 0x1c) = arg3
00420067        *(edi_7 + 0x20) = var_50_1
0042006a        *(edi_7 + 0x24) = var_4c_2
0042006f        *(edi_7 + 0x28) = arg2
00420072        *(edi_7 + 0x2c) = var_4c_2
0042011d        bool cond:11_1 = var_48_3 + 1 s< 2
00420120        var_48_3 += 1
00420124        if (not(cond:11_1))
00420124        break
0041ffb8        ecx_71 = var_48_3
0042012a        i_3 += 1
00420133        arg2 = i_3
00420137        do while (i_3 s< self->width_cells)
00420140        ebx_3 += 1
00420143        if (ebx_3 s>= self->segment_count)
00420143        break
0041ff49        i_3 = 0
00420157        return finalize_path_template_record(self)
