/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: finalize_path_template @ 0x42c600 */

0042c609        uint32_t segment_count = self->segment_count
0042c60c        self->row_span_count = 0
0042c615        if (segment_count s> 0)
0042c61a        uint32_t ebp_1 = segment_count
0042c61c        float* edi_2 = &self->secondary_samples->transform.position.z
0042c63b        uint32_t i
0042c627        uint32_t eax_1
0042c627        int16_t x87control
0042c627        eax_1, x87control = ftol(x87control, fconvert.t((edi_2 - 0x38)->transform.position.z) + fconvert.t(1f))
0042c62f        if (eax_1 s> self->row_span_count)
0042c631        self->row_span_count = eax_1
0042c634        edi_2 = &edi_2[0x2a]
0042c63a        i = ebp_1
0042c63a        ebp_1 -= 1
0042c63b        do while (i != 1)
0042c63d        int32_t i_1 = 0
0042c641        if (segment_count s> 0)
0042c643        int32_t edi_3 = 0
0042c648        struct TransformMatrix* source = self->primary_samples + edi_3
0042c64e        invert_matrix_from_source(&source[1], source)
0042c656        struct TransformMatrix* source_1 = self->secondary_samples + edi_3
0042c65d        invert_matrix_from_source(&source_1[1], source_1)
0042c665        i_1 += 1
0042c666        edi_3 += 0xa8
0042c66e        do while (i_1 s< self->segment_count)
0042c673        int32_t i_2 = 0
0042c678        if (self->segment_count - 1 s> 0)
0042c67e        void* edi_4 = nullptr
0042c683        void* eax_5 = self->primary_samples + edi_4
0042c694        struct Vec3 var_c
0042c694        cross_vectors(&var_c, eax_5 + 0x20, eax_5 + 0xc8)
0042c6ad        *(&self->primary_samples->lateral_source + edi_4) = fconvert.s(dot_vector(&var_c, edi_4 + self->primary_samples))
0042c6b4        int16_t eax_8
0042c6b4        eax_8.b = self->is_mirrored_x
0042c6b9        if (eax_8.b != 0)
0042c6bb        struct PathTemplateSample* primary_samples_1 = self->primary_samples
0042c6d2        *(&primary_samples_1->lateral_source + edi_4) = fconvert.s(fconvert.t(*(&primary_samples_1->lateral_source + edi_4)) * fconvert.t(-1f))
0042c6d4        struct PathTemplateSample* primary_samples_2 = self->primary_samples
0042c6d7        long double x87_r7_6 = fconvert.t(*(&primary_samples_2->lateral_source + edi_4))
0042c6de        long double temp1_1 = fconvert.t(0f)
0042c6de        x87_r7_6 - temp1_1
0042c6eb        eax_8 = (x87_r7_6 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp1_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp1_1 ? 1 : 0) << 0xe
0042c6f0        if ((eax_8:1.b & 0x41) == 0)
0042c6f2        *(&primary_samples_2->lateral_source + edi_4) = 0
0042c6f8        struct PathTemplateSample* primary_samples = self->primary_samples
0042c6fb        long double x87_r7_7 = fconvert.t(*(&primary_samples->lateral_source + edi_4))
0042c702        long double temp2_1 = fconvert.t(-0.100000001f)
0042c702        x87_r7_7 - temp2_1
0042c714        if ((((x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0042c716        *(&primary_samples->lateral_source + edi_4) = 0xbdcccccd
0042c71f        i_2 += 1
0042c720        edi_4 += 0xa8
0042c729        do while (i_2 s< self->segment_count - 1)
0042c742        *(&self->primary_samples[self->segment_count] - 4) = 0
0042c74a        struct Object* object = self->bod.object
0042c74d        enum ObjectFlag flags = object->flags
0042c750        flags.b |= 0x80
0042c753        object->flags = flags
0042c756        struct Object* object_1 = self->bod.object
0042c761        object_1->flags &= ~OBJECT_FLAG_DISABLE_CULLING
0042c76a        return
