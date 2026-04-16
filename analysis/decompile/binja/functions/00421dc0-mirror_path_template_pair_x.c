/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mirror_path_template_pair_x @ 0x421dc0 */

00421dc5        struct PathTemplate* source_1 = source
00421dcd        self->__offset(0x3c).b = 1
00421dd4        self->segment_count = source_1->segment_count
00421dda        self->segment_count_f = source_1->segment_count_f
00421de0        self->__offset(0x50).d = source_1->__offset(0x50).d
00421de8        self->__offset(0x54).d = source_1->__offset(0x54).d
00421deb        allocate_path_template_samples(self)
00421df6        void* eax_2 = self->_pad_00[0x24].d
00421df9        self->__offset(0x9c).b = source_1->__offset(0x9c).b
00421e05        *(eax_2 + 0x10) = *(source_1->_pad_00[0x24].d + 0x10)
00421e0b        self->kind = source_1->kind
00421e11        self->__offset(0x40).d = source_1->__offset(0x40).d
00421e17        int32_t i = 0
00421e1b        if (self->segment_count s> 0)
00421e21        void* eax_5 = nullptr
00421e32        *(&self->primary_samples->center_x + eax_5) = fconvert.s(fneg(fconvert.t(*(&source_1->primary_samples->center_x + eax_5))))
00421e46        *(&self->primary_samples->lateral_scale + eax_5) = *(&source_1->primary_samples->lateral_scale + eax_5)
00421e5c        *(&self->primary_samples->rotation_scalar_98 + eax_5) = fconvert.s(fneg(fconvert.t(*(&source_1->primary_samples->rotation_scalar_98 + eax_5))))
00421e72        *(&self->primary_samples->rotation_scalar_94 + eax_5) = fconvert.s(fneg(fconvert.t(*(&source_1->primary_samples->rotation_scalar_94 + eax_5))))
00421e86        *(&self->primary_samples->special_scalar + eax_5) = *(&source_1->primary_samples->special_scalar + eax_5)
00421ea0        __builtin_memcpy(eax_5 + self->primary_samples, eax_5 + source_1->primary_samples, 0x40)
00421ea5        float* ecx_16 = self->primary_samples + eax_5
00421eaf        *ecx_16 = fconvert.s(fconvert.t(*ecx_16) * fconvert.t(-1f))
00421eb1        struct PathTemplateSample* primary_samples = self->primary_samples
00421ec2        *(&primary_samples->transform.basis_up + eax_5) = fconvert.s(fconvert.t(*(&primary_samples->transform.basis_up + eax_5)) * fconvert.t(-1f))
00421ec4        struct PathTemplateSample* primary_samples_1 = self->primary_samples
00421ed5        *(&primary_samples_1->transform.basis_forward + eax_5) = fconvert.s(fconvert.t(*(&primary_samples_1->transform.basis_forward + eax_5)) * fconvert.t(-1f))
00421ed7        struct PathTemplateSample* primary_samples_2 = self->primary_samples
00421ee8        *(&primary_samples_2->transform.position + eax_5) = fconvert.s(fconvert.t(*(&primary_samples_2->transform.position + eax_5)) * fconvert.t(-1f))
00421ef0        int32_t* ecx_21 = &source_1->primary_samples->delta_dir_to_next + eax_5
00421ef7        int32_t* esi_6 = &self->primary_samples->delta_dir_to_next + eax_5
00421f00        *esi_6 = *ecx_21
00421f05        esi_6[1] = ecx_21[1]
00421f0b        esi_6[2] = ecx_21[2]
00421f0e        struct PathTemplateSample* primary_samples_3 = self->primary_samples
00421f25        *(&primary_samples_3->delta_dir_to_next + eax_5) = fconvert.s(fconvert.t(*(&primary_samples_3->delta_dir_to_next + eax_5)) * fconvert.t(-1f))
00421f34        *(&self->primary_samples->delta_length + eax_5) = *(&source_1->primary_samples->delta_length + eax_5)
00421f4e        __builtin_memcpy(eax_5 + self->__offset(0x5c).d, eax_5 + source_1->__offset(0x5c).d, 0x40)
00421f53        float* ecx_28 = self->__offset(0x5c).d + eax_5
00421f5d        i += 1
00421f5e        *ecx_28 = fconvert.s(fconvert.t(*ecx_28) * fconvert.t(-1f))
00421f60        int32_t ecx_29 = self->__offset(0x5c).d
00421f71        *(eax_5 + ecx_29 + 0x10) = fconvert.s(fconvert.t(*(eax_5 + ecx_29 + 0x10)) * fconvert.t(-1f))
00421f73        int32_t ecx_31 = self->__offset(0x5c).d
00421f84        *(eax_5 + ecx_31 + 0x20) = fconvert.s(fconvert.t(*(eax_5 + ecx_31 + 0x20)) * fconvert.t(-1f))
00421f86        int32_t ecx_33 = self->__offset(0x5c).d
00421f97        *(eax_5 + ecx_33 + 0x30) = fconvert.s(fconvert.t(*(eax_5 + ecx_33 + 0x30)) * fconvert.t(-1f))
00421f9f        int32_t* ecx_36 = eax_5 + source_1->__offset(0x5c).d + 0x80
00421fa6        int32_t* esi_11 = eax_5 + self->__offset(0x5c).d + 0x80
00421faf        *esi_11 = *ecx_36
00421fb4        esi_11[1] = ecx_36[1]
00421fba        esi_11[2] = ecx_36[2]
00421fbd        int32_t ecx_38 = self->__offset(0x5c).d
00421fc7        long double x87_r7_26 = fconvert.t(*(eax_5 + ecx_38 + 0x80)) * fconvert.t(-1f)
00421fcd        float* ecx_39 = eax_5 + ecx_38 + 0x80
00421fd4        eax_5 += 0xa8
00421fd9        *ecx_39 = fconvert.s(x87_r7_26)
00421fe5        *(eax_5 + self->__offset(0x5c).d - 0x1c) = *(eax_5 + source_1->__offset(0x5c).d - 0x1c)
00421fee        do while (i s< self->segment_count)
00422003        request_object_vertices(self->_pad_00[0x24].d, (self->segment_count + 1) * (self->__offset(0x54).d + 1))
00422015        request_object_facequads(self->_pad_00[0x24].d, (self->segment_count * self->__offset(0x54).d) << 1)
0042201a        struct PathTemplateStripMesh* mesh = self->_pad_00[0x24].d
0042201d        __builtin_memset(&source, 0, 4)
0042202c        if ((mesh->flags & PATH_TEMPLATE_STRIP_MESH_FLAG_HAS_VERTEX_COLOURS) != 0)
0042202e        request_object_vertex_colours(mesh)
00422033        mesh = self->_pad_00[0x24].d
00422039        source = mesh->vertex_colours
0042203d        struct ObjectFaceQuad* facequads = mesh->facequads
00422040        struct Vec3* vertices = mesh->vertices
0042204a        int32_t i_1 = 0
0042204c        struct Vec3* vertices_1 = vertices
00422052        if (self->segment_count s>= 0)
00422058        int32_t eax_9 = self->__offset(0x54).d
0042205b        int32_t ecx_48 = 0
0042205f        if (eax_9 s>= 0)
00422074        float* eax_14 = ((eax_9 + 1) * i_1 + ecx_48) * 0xc
0042207c        *(eax_14 + vertices) = fconvert.s(fneg(fconvert.t(*(*(source_1->_pad_00[0x24].d + 0x38) + eax_14))))
00422098        vertices[(self->:0x54.d + 1) * i_1 + ecx_48].y = *(*(source_1->_pad_00[0x24].d + 0x38) + ((self->__offset(0x54).d + 1) * i_1 + ecx_48) * 0xc + 4)
004220b5        vertices[(self->:0x54.d + 1) * i_1 + ecx_48].z = *(*(source_1->_pad_00[0x24].d + 0x38) + ((self->__offset(0x54).d + 1) * i_1 + ecx_48) * 0xc + 8)
004220c3        if ((*(self->_pad_00[0x24].d + 0x10) & 0x10000) != 0)
004220d8        int32_t eax_32 = ((self->__offset(0x54).d + 1) * i_1 + ecx_48) << 4
004220db        int32_t* esi_15 = *(source_1->_pad_00[0x24].d + 0x48) + eax_32
004220dd        int32_t* eax_33 = &source->_pad_00[eax_32]
004220e1        *eax_33 = *esi_15
004220e6        eax_33[1] = esi_15[1]
004220ec        eax_33[2] = esi_15[2]
004220f2        eax_33[3] = esi_15[3]
004220f5        vertices = vertices_1
004220f9        eax_9 = self->__offset(0x54).d
004220fc        ecx_48 += 1
004220ff        do while (ecx_48 s<= eax_9)
00422108        i_1 += 1
0042210b        do while (i_1 s<= self->segment_count)
00422114        int32_t var_8 = 0
0042211e        if (self->segment_count s> 0)
004221cb        bool cond:0_1
00422124        int32_t eax_36 = self->__offset(0x54).d
00422127        __builtin_memset(&source, 0, 4)
00422131        if (eax_36 s> 0)
004221b7        bool cond:2_1
00422137        int32_t i_2 = 0
004221a7        while (i_2 s< 2)
0042215a        void* eax_38 = &facequads[i_2 + ((self->:0x54.d * var_8 + source) << 1)]
00422165        __builtin_memcpy(eax_38, *(source_1->_pad_00[0x24].d + 0x5c) + (i_2 + ((self->__offset(0x54).d * var_8 + source) << 1)) * 0x30, 0x30)
0042216d        int16_t ecx_55 = *(eax_38 + 2)
00422171        *(eax_38 + 2) = *(eax_38 + 4)
00422175        *(eax_38 + 4) = ecx_55
0042217f        i_2 += 1
00422180        int16_t ecx_56 = *(eax_38 + 6)
00422184        *(eax_38 + 6) = *(eax_38 + 8)
00422188        *(eax_38 + 8) = ecx_56
0042218f        long double x87_r7_29 = fconvert.t(*(eax_38 + 0x10))
00422195        *(eax_38 + 0x10) = fconvert.s(fconvert.t(*(eax_38 + 0x18)))
00422198        *(eax_38 + 0x18) = fconvert.s(x87_r7_29)
0042219b        long double x87_r7_30 = fconvert.t(*(eax_38 + 0x20))
004221a1        *(eax_38 + 0x20) = fconvert.s(fconvert.t(*(eax_38 + 0x28)))
004221a4        *(eax_38 + 0x28) = fconvert.s(x87_r7_30)
004221b1        cond:2_1 = &source->_pad_00[1] s< self->__offset(0x54).d
004221b3        source = &source->_pad_00[1]
004221b7        do while (cond:2_1)
004221c5        cond:0_1 = var_8 + 1 s< self->segment_count
004221c7        var_8 += 1
004221cb        do while (cond:0_1)
004221df        return finalize_path_template(self)
