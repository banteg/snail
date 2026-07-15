/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sample_smtrack_heightmap @ 0x41a360 */

0041a36a        struct Object* source_1 = source
0041a36e        void* texture_ref = replacement->texture_ref
0041a374        long double x87_r7 = float.t(source_1->heightmap_sample_count)
0041a377        replacement = fconvert.s(x87_r7)
0041a381        struct Object* eax_1
0041a381        int16_t x87control
0041a381        int16_t x87control_1
0041a381        eax_1, x87control_1 = ftol(x87control, x87_r7 * fconvert.t(source_1->heightmap_sample_scale) / fconvert.t(source_1->heightmap_sample_divisor))
0041a38a        int32_t ecx = 0
0041a390        ecx.w = *(texture_ref + 0xc)
0041a394        int32_t edx = 0
0041a39a        edx.w = *(texture_ref + 0xe)
0041a39e        source = fconvert.s(float.t(eax_1))
0041a3b4        struct Vec3* vertices = source_1->vertices
0041a3d1        long double x87_r7_8 = fconvert.t(0f)
0041a3d7        long double x87_r6_4 = fconvert.t(0f)
0041a3dd        long double temp0 = fconvert.t(source)
0041a3dd        x87_r6_4 - temp0
0041a3e6        if ((((x87_r6_4 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, temp0) ? 1 : 0) << 0xa | (x87_r6_4 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0041a3e6        return
0041a3ed        char cubic_1 = cubic
0041a4bc        long double temp2_1
0041a3f1        long double x87_r6_5 = fconvert.t(0f)
0041a3f7        long double x87_r5_1 = fconvert.t(0f)
0041a3fd        long double temp1_1 = fconvert.t(replacement)
0041a3fd        x87_r5_1 - temp1_1
0041a406        if ((((x87_r5_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r5_1, temp1_1) ? 1 : 0) << 0xa | (x87_r5_1 == temp1_1 ? 1 : 0) << 0xe | 0x3000):1.b & 0x41) != 0)
0041a412        int32_t eax_4
0041a412        eax_4, x87control_1 = ftol(x87control_1, x87_r7_8 * fconvert.t(fconvert.s(float.t(edx) / (fconvert.t(source) + fconvert.t(1f)))))
0041a4a5        long double temp3_1
0041a41f        int32_t eax_5
0041a41f        eax_5, x87control_1 = ftol(x87control_1, x87_r6_5 * fconvert.t(fconvert.s(float.t(ecx) / (fconvert.t(replacement) + fconvert.t(1f)))))
0041a424        int32_t ecx_1 = 0
0041a426        int32_t edx_1 = 0
0041a428        ecx_1.w = *(texture_ref + 0xe)
0041a42c        edx_1.w = *(texture_ref + 0xc)
0041a438        int32_t eax_6 = 0
0041a43a        eax_6.b = *(texture_ref + 0x10)
0041a43d        int32_t edx_2 = 0
0041a442        void* ecx_6 = ((ecx_1 - eax_4 - 1) * edx_1 + eax_5) * (eax_6 u>> 3)
0041a445        edx_2.b = *(ecx_6 + texture_ref + 0x13)
0041a449        void* eax_8 = ecx_6 + texture_ref
0041a44c        int32_t ecx_7 = 0
0041a44e        ecx_7.b = *(eax_8 + 0x14)
0041a451        cubic.d = ecx_7
0041a455        int32_t ecx_8 = 0
0041a457        long double x87_r5_6 = float.t(cubic.d)
0041a45b        ecx_8.b = *(eax_8 + 0x12)
0041a45e        cubic.d = edx_2
0041a462        long double x87_r4_1 = float.t(cubic.d)
0041a466        cubic.d = ecx_8
0041a47a        long double x87_r5_10 = (x87_r5_6 + x87_r4_1 + float.t(cubic.d)) * fconvert.t(0.00392156886f) * fconvert.t(0.333333343f)
0041a480        if (cubic_1 != 0)
0041a486        x87_r5_10 = x87_r5_10 * x87_r5_10 * x87_r5_10
0041a48c        vertices = &vertices[1]
0041a493        vertices->__offset(0xfffffffffffffff8).d = fconvert.s(x87_r5_10 * fconvert.t(scale) + fconvert.t(base))
0041a496        x87_r6_5 = x87_r6_5 + fconvert.t(1f)
0041a49c        temp3_1 = fconvert.t(replacement)
0041a49c        x87_r6_5 - temp3_1
0041a4a5        do while ((((x87_r6_5 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_5, temp3_1) ? 1 : 0) << 0xa | (x87_r6_5 == temp3_1 ? 1 : 0) << 0xe | 0x3000):1.b & 0x41) != 0)
0041a4ad        x87_r7_8 = x87_r7_8 + fconvert.t(1f)
0041a4b3        temp2_1 = fconvert.t(source)
0041a4b3        x87_r7_8 - temp2_1
0041a4bc        do while ((((x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0041a4cb        return
