/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mirror_path_template_pair_x @ 0x421dc0 */

00421dc5        struct PathTemplate* source_1 = source
00421dcd        self->is_mirrored_x = 1
00421dd4        self->segment_count = source_1->segment_count
00421dda        self->segment_count_f = source_1->segment_count_f
00421de0        self->width_or_scale = source_1->width_or_scale
00421de8        self->width_cells = source_1->width_cells
00421deb        allocate_path_template_samples(self)
00421df6        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
00421df9        self->special_runtime_flag_9c = source_1->special_runtime_flag_9c
00421e05        strip_mesh->flags = source_1->strip_mesh->flags
00421e0b        self->kind = source_1->kind
00421e11        self->side_exit_mode = source_1->side_exit_mode
00421e17        int32_t i = 0
00421e1b        if (self->segment_count s> 0)
00421e21        void* eax_4 = nullptr
00421e32        *(&self->primary_samples->center_x + eax_4) = fconvert.s(fneg(fconvert.t(*(&source_1->primary_samples->center_x + eax_4))))
00421e46        *(&self->primary_samples->lateral_scale + eax_4) = *(&source_1->primary_samples->lateral_scale + eax_4)
00421e5c        *(&self->primary_samples->rotation_scalar_98 + eax_4) = fconvert.s(fneg(fconvert.t(*(&source_1->primary_samples->rotation_scalar_98 + eax_4))))
00421e72        *(&self->primary_samples->rotation_scalar_94 + eax_4) = fconvert.s(fneg(fconvert.t(*(&source_1->primary_samples->rotation_scalar_94 + eax_4))))
00421e86        *(&self->primary_samples->special_scalar + eax_4) = *(&source_1->primary_samples->special_scalar + eax_4)
00421ea0        __builtin_memcpy(eax_4 + self->primary_samples, eax_4 + source_1->primary_samples, 0x40)
00421ea5        float* ecx_16 = self->primary_samples + eax_4
00421eaf        *ecx_16 = fconvert.s(fconvert.t(*ecx_16) * fconvert.t(-1f))
00421eb1        struct PathTemplateSample* primary_samples = self->primary_samples
00421ec2        *(&primary_samples->transform.basis_up + eax_4) = fconvert.s(fconvert.t(*(&primary_samples->transform.basis_up + eax_4)) * fconvert.t(-1f))
00421ec4        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00421ed5        *(&primary_samples_1->transform.basis_forward + eax_4) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.basis_forward + eax_4)) * fconvert.t(-1f))
00421ed7        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00421ee8        *(&primary_samples_2->transform.position + eax_4) = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position + eax_4)) * fconvert.t(-1f))
00421ef0        int32_t* ecx_21 = &source_1->primary_samples->delta_dir_to_next + eax_4
00421ef7        int32_t* esi_6 = &self->primary_samples->delta_dir_to_next + eax_4
00421f00        *esi_6 = *ecx_21
00421f05        esi_6[1] = ecx_21[1]
00421f0b        esi_6[2] = ecx_21[2]
00421f0e        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00421f25        *(&primary_samples_3->delta_dir_to_next + eax_4) = fconvert.s(fconvert.t(*(&primary_samples_3->delta_dir_to_next + eax_4)) * fconvert.t(-1f))
00421f34        *(&self->primary_samples->delta_length + eax_4) = *(&source_1->primary_samples->delta_length + eax_4)
00421f4e        __builtin_memcpy(eax_4 + self->secondary_samples, eax_4 + source_1->secondary_samples, 0x40)
00421f53        float* ecx_28 = self->secondary_samples + eax_4
00421f5d        i += 1
00421f5e        *ecx_28 = fconvert.s(fconvert.t(*ecx_28) * fconvert.t(-1f))
00421f60        struct PathTemplateSample* secondary_samples = self->secondary_samples
00421f71        *(&secondary_samples->transform.basis_up + eax_4) = fconvert.s(fconvert.t(*(&secondary_samples->transform.basis_up + eax_4)) * fconvert.t(-1f))
00421f73        struct PathTemplateSample* secondary_samples_1 = self->secondary_samples
00421f84        *(&secondary_samples_1->transform.basis_forward + eax_4) = fconvert.s(fconvert.t(*(&secondary_samples_1->transform.basis_forward + eax_4)) * fconvert.t(-1f))
00421f86        struct PathTemplateSample* secondary_samples_2 = self->secondary_samples
00421f97        *(&secondary_samples_2->transform.position + eax_4) = fconvert.s(fconvert.t(*(&secondary_samples_2->transform.position + eax_4)) * fconvert.t(-1f))
00421f9f        int32_t* ecx_33 = &source_1->secondary_samples->delta_dir_to_next + eax_4
00421fa6        int32_t* esi_11 = &self->secondary_samples->delta_dir_to_next + eax_4
00421faf        *esi_11 = *ecx_33
00421fb4        esi_11[1] = ecx_33[1]
00421fba        esi_11[2] = ecx_33[2]
00421fbd        struct PathTemplateSample* secondary_samples_3 = self->secondary_samples
00421fc7        long double x87_r7_26 = fconvert.t(*(&secondary_samples_3->delta_dir_to_next + eax_4)) * fconvert.t(-1f)
00421fcd        float* ecx_35 = &secondary_samples_3->delta_dir_to_next + eax_4
00421fd4        eax_4 += 0xa8
00421fd9        *ecx_35 = fconvert.s(x87_r7_26)
00421fe5        *(eax_4 + self->secondary_samples - 0x1c) = *(eax_4 + source_1->secondary_samples - 0x1c)
00421fee        do while (i s< self->segment_count)
00422003        request_object_vertices(self->strip_mesh, (self->segment_count + 1) * (self->width_cells + 1))
00422015        request_object_facequads(self->strip_mesh, (self->segment_count * self->width_cells) << 1)
0042201a        struct PathTemplateStripMesh* strip_mesh_1 = self->strip_mesh
0042201d        source = nullptr
0042202c        if ((strip_mesh_1->flags & PATH_TEMPLATE_STRIP_MESH_FLAG_HAS_VERTEX_COLOURS) != 0)
0042202e        request_object_vertex_colours(strip_mesh_1)
00422033        strip_mesh_1 = self->strip_mesh
00422039        source = strip_mesh_1->vertex_colours
0042203d        struct ObjectFaceQuad* facequads = strip_mesh_1->facequads
00422040        struct Vec3* vertices = strip_mesh_1->vertices
0042204a        int32_t i_1 = 0
0042204c        struct Vec3* vertices_1 = vertices
00422052        if (self->segment_count s>= 0)
00422058        uint32_t width_cells = self->width_cells
0042205b        int32_t ecx_44 = 0
0042205f        if (width_cells s>= 0)
00422074        float* eax_12 = ((width_cells + 1) * i_1 + ecx_44) * 0xc
0042207c        *(eax_12 + vertices) = fconvert.s(fneg(fconvert.t(*(source_1->strip_mesh->vertices + eax_12))))
0042207f        self->width_cells
00422098        vertices[(self->:0x54.d + 1) * i_1 + ecx_44].y = source_1->strip_mesh->vertices[(self->:0x54.d + 1) * i_1 + ecx_44].y
0042209c        self->width_cells
004220b5        vertices[(self->:0x54.d + 1) * i_1 + ecx_44].z = source_1->strip_mesh->vertices[(self->:0x54.d + 1) * i_1 + ecx_44].z
004220c3        if ((self->strip_mesh->flags & PATH_TEMPLATE_STRIP_MESH_FLAG_HAS_VERTEX_COLOURS) != 0)
004220db        int32_t* esi_15 = &source_1->strip_mesh->vertex_colours[(self->:0x54.d + 1) * i_1 + ecx_44]
004220dd        int32_t* eax_31 = (((self->width_cells + 1) * i_1 + ecx_44) << 4) + source
004220e1        *eax_31 = *esi_15
004220e6        eax_31[1] = esi_15[1]
004220ec        eax_31[2] = esi_15[2]
004220f2        eax_31[3] = esi_15[3]
004220f5        vertices = vertices_1
004220f9        width_cells = self->width_cells
004220fc        ecx_44 += 1
004220ff        do while (ecx_44 s<= width_cells)
00422108        i_1 += 1
0042210b        do while (i_1 s<= self->segment_count)
00422114        int32_t var_8 = 0
0042211e        if (self->segment_count s> 0)
004221cb        bool cond:0_1
00422127        source = nullptr
00422131        if (self->width_cells s> 0)
00422137        int32_t i_2 = 0
004221a7        while (i_2 s< 2)
00422139        self->width_cells
0042215a        void* eax_36 = &facequads[i_2 + ((self->:0x54.d * var_8 + source) << 1)]
00422165        __builtin_memcpy(eax_36, &source_1->strip_mesh->facequads[i_2 + ((self->:0x54.d * var_8 + source) << 1)], 0x30)
0042216d        int16_t ecx_51 = *(eax_36 + 2)
00422171        *(eax_36 + 2) = *(eax_36 + 4)
00422175        *(eax_36 + 4) = ecx_51
0042217f        i_2 += 1
00422180        int16_t ecx_52 = *(eax_36 + 6)
00422184        *(eax_36 + 6) = *(eax_36 + 8)
00422188        *(eax_36 + 8) = ecx_52
0042218f        long double x87_r7_29 = fconvert.t(*(eax_36 + 0x10))
00422195        *(eax_36 + 0x10) = fconvert.s(fconvert.t(*(eax_36 + 0x18)))
00422198        *(eax_36 + 0x18) = fconvert.s(x87_r7_29)
0042219b        long double x87_r7_30 = fconvert.t(*(eax_36 + 0x20))
004221a1        *(eax_36 + 0x20) = fconvert.s(fconvert.t(*(eax_36 + 0x28)))
004221a4        *(eax_36 + 0x28) = fconvert.s(x87_r7_30)
004221b3        source = &source->__offset(0x1).d
004221b7        do while (&source->__offset(0x1).d s< self->width_cells)
004221c5        cond:0_1 = var_8 + 1 s< self->segment_count
004221c7        var_8 += 1
004221cb        do while (cond:0_1)
004221df        return finalize_path_template(self)
