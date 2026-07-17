/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_point_inside_track_attachment @ 0x42ca90 */

0042ca9f        float x = cell->anchor_position.x
0042caa1        uint32_t segment_count = self->segment_count
0042caa4        int32_t i = segment_count - 1
0042caa9        float y = cell->anchor_position.y
0042cab0        float z = cell->anchor_position.z
0042cab7        if (segment_count - 1 s>= 0)
0042cac9        int32_t esi_2 = i * 0xa8
0042cacc        struct PathTemplateSample* secondary_samples = self->secondary_samples
0042cb0d        struct Vec3 vector
0042cb0d        vector.x = fconvert.s(fconvert.t(probe.x) - (fconvert.t(x) + fconvert.t(*(&secondary_samples->transform.position + esi_2))))
0042cb21        vector.y = fconvert.s(fconvert.t(probe.y) - fconvert.t(fconvert.s(fconvert.t(y) + fconvert.t(*(&secondary_samples->transform.position.y + esi_2)))))
0042cb31        vector.z = fconvert.s(fconvert.t(probe.z) - fconvert.t(fconvert.s(fconvert.t(z) + fconvert.t((&secondary_samples->inverse_matrix + esi_2)->__offset(0xfffffffffffffff8).d))))
0042cb35        rotate_vector_by_matrix(&vector, &secondary_samples->inverse_matrix + esi_2)
0042cb3a        uint32_t width_cells = self->width_cells
0042cb3f        int32_t eax_7
0042cb3f        int32_t edx_2
0042cb3f        edx_2:eax_7 = sx.q(width_cells)
0042cb4e        long double x87_r7_9 = float.t(neg.d((eax_7 - edx_2) s>> 1)) - fconvert.t(0.300000012f)
0042cb54        long double temp2_1 = fconvert.t(vector.x)
0042cb54        x87_r7_9 - temp2_1
0042cb5d        if ((((x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0042cb61        int32_t eax_13
0042cb61        int32_t edx_3
0042cb61        edx_3:eax_13 = sx.q(width_cells)
0042cb6e        long double x87_r7_11 = float.t((eax_13 - edx_3) s>> 1) + fconvert.t(0.300000012f)
0042cb74        long double temp3_1 = fconvert.t(vector.x)
0042cb74        x87_r7_11 - temp3_1
0042cb7d        if ((((x87_r7_11 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp3_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042cb7f        long double x87_r7_12 = fconvert.t(vector.y)
0042cb83        long double temp4_1 = fconvert.t(-0.300000012f)
0042cb83        x87_r7_12 - temp4_1
0042cb8e        if ((((x87_r7_12 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp4_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0042cb90        long double x87_r7_13 = fconvert.t(vector.y)
0042cb94        long double temp5_1 = fconvert.t(0.300000012f)
0042cb94        x87_r7_13 - temp5_1
0042cb9f        if ((((x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0042cba1        long double x87_r7_14 = fconvert.t(vector.z)
0042cba5        long double temp6_1 = fconvert.t(0f)
0042cba5        x87_r7_14 - temp6_1
0042cbb0        if ((((x87_r7_14 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp6_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0042cbb5        long double x87_r7_15 = fconvert.t(vector.z)
0042cbb9        long double temp7_1 = fconvert.t(*(&self->secondary_samples->delta_length + esi_2))
0042cbb9        x87_r7_15 - temp7_1
0042cbc0        int16_t eax_18 = (x87_r7_15 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp7_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp7_1 ? 1 : 0) << 0xe
0042cbc5        if ((eax_18:1.b & 1) != 0)
0042cbe3        eax_18.b = 1
0042cbe9        return 1
0042cbc7        i -= 1
0042cbc8        esi_2 -= 0xa8
0042cbd0        do while (i s>= 0)
0042cbd8        int32_t eax_20
0042cbd8        eax_20.b = 0
0042cbde        return 0
