/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: finalize_path_template @ 0x42c600 */

0042c603        int32_t ebx
0042c603        int32_t var_10 = ebx
0042c604        int32_t ebp
0042c604        int32_t var_14 = ebp
0042c605        int32_t esi
0042c605        int32_t var_18 = esi
0042c608        int32_t edi
0042c608        int32_t var_1c = edi
0042c608        int32_t* esp_1 = &var_1c
0042c609        uint32_t segment_count = self->segment_count
0042c60c        self->__offset(0x48).d = 0
0042c615        struct TransformMatrix* entry_source
0042c615        if (segment_count s> 0)
0042c61a        uint32_t ebp_1 = segment_count
0042c61c        float* edi_2 = &self->secondary_samples->transform.position.z
0042c63b        uint32_t i
0042c627        int32_t eax_1
0042c627        int16_t x87control
0042c627        eax_1, entry_source, x87control = __ftol(x87control, fconvert.t((edi_2 - 0x38)->transform.position.z) + fconvert.t(1f))
0042c62f        if (eax_1 s> self->__offset(0x48).d)
0042c631        self->__offset(0x48).d = eax_1
0042c634        edi_2 = &edi_2[0x2a]
0042c63a        i = ebp_1
0042c63a        ebp_1 -= 1
0042c63b        do while (i != 1)
0042c63d        int32_t i_1 = 0
0042c641        if (segment_count s> 0)
0042c643        int32_t edi_3 = 0
0042c648        void* eax_3 = self->primary_samples + edi_3
0042c64a        *(esp_1 - 4) = eax_3
0042c64e        struct TransformMatrix* source = invert_matrix_from_source(eax_3 + 0x40, entry_source)
0042c656        void* eax_4 = self->secondary_samples + edi_3
0042c659        *(esp_1 - 8) = eax_4
0042c659        esp_1 -= 8
0042c65d        entry_source = invert_matrix_from_source(eax_4 + 0x40, source)
0042c665        i_1 += 1
0042c666        edi_3 += 0xa8
0042c66e        do while (i_1 s< self->segment_count)
0042c673        int32_t i_2 = 0
0042c678        if (self->segment_count - 1 s> 0)
0042c67e        void* edi_4 = nullptr
0042c683        void* eax_7 = self->primary_samples + edi_4
0042c68e        *(esp_1 - 4) = eax_7 + 0xc8
0042c68f        *(esp_1 - 8) = eax_7 + 0x20
0042c694        cross_vectors(&esp_1[4])
0042c6a4        *(esp_1 - 4) = edi_4 + self->primary_samples
0042c6ad        *(&self->primary_samples->_pad_a4 + edi_4) = fconvert.s(dot_vector(&esp_1[4]))
0042c6b4        struct PathTemplateSample* eax_9
0042c6b4        eax_9.b = self->is_mirrored_x
0042c6b9        if (eax_9.b != 0)
0042c6bb        struct PathTemplateSample* primary_samples = self->primary_samples
0042c6d2        (&primary_samples->_pad_a4 + edi_4)->transform.basis_right.x = fconvert.s(fconvert.t(*(&primary_samples->_pad_a4 + edi_4)) * fconvert.t(-1f))
0042c6d4        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042c6d7        long double x87_r7_6 = fconvert.t(*(&primary_samples_1->_pad_a4 + edi_4))
0042c6de        long double temp1_1 = fconvert.t(0f)
0042c6de        x87_r7_6 - temp1_1
0042c6eb        eax_9.w = (x87_r7_6 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp1_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp1_1 ? 1 : 0) << 0xe
0042c6f0        if ((eax_9:1.b & 0x41) == 0)
0042c6f2        *(&primary_samples_1->_pad_a4 + edi_4) = 0
0042c6fb        long double x87_r7_7 = fconvert.t(*(&self->primary_samples->_pad_a4 + edi_4))
0042c702        long double temp2_1 = fconvert.t(-0.100000001f)
0042c702        x87_r7_7 - temp2_1
0042c70f        struct PathTemplateSample* eax_10
0042c70f        eax_10.w = (x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe
0042c714        if ((eax_10:1.b & 1) != 0)
0042c716        *(&eax_10->_pad_a4 + edi_4) = 0xbdcccccd
0042c71f        i_2 += 1
0042c720        edi_4 += 0xa8
0042c729        do while (i_2 s< self->segment_count - 1)
0042c732        *esp_1
0042c742        *(&self->primary_samples[self->segment_count] - 4) = 0
0042c74a        struct PathTemplateStripMesh* strip_mesh = self->strip_mesh
0042c750        enum PathTemplateStripMeshFlags ecx_11
0042c750        ecx_11.b = strip_mesh->flags.b | 0x80
0042c753        strip_mesh->flags = ecx_11
0042c756        struct PathTemplateStripMesh* strip_mesh_1 = self->strip_mesh
0042c75c        enum PathTemplateStripMeshFlags result = strip_mesh_1->flags & ~PATH_TEMPLATE_STRIP_MESH_FLAG_IMPORTED_X_MESH
0042c761        strip_mesh_1->flags = result
0042c732        esp_1[1]
0042c764        esp_1[2]
0042c765        esp_1[3]
0042c76a        return result
