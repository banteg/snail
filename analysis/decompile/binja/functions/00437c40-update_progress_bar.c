/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_progress_bar @ 0x437c40 */

00437c40        void* eax = data_4df904
00437c48        long double x87_r7 = float.t(*(eax + 0x74668))
00437c60        long double x87_r7_1 = (fconvert.t(*(eax + 0x42fdec)) - x87_r7) / (float.t(*(eax + 0x74670)) - x87_r7)
00437c62        long double temp0 = fconvert.t(0f)
00437c62        x87_r7_1 - temp0
00437c68        eax.w = (x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe | 0x3800
00437c6d        if ((eax:1.b & 1) == 0)
00437c79        long double temp1_1 = fconvert.t(1f)
00437c79        x87_r7_1 - temp1_1
00437c7f        eax.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800
00437c84        if ((eax:1.b & 0x41) == 0)
00437c88        x87_r7_1 = fconvert.t(1f)
00437c71        x87_r7_1 = fconvert.t(0f)
00437ccd        float var_1c = fconvert.s((fconvert.t(1f) - x87_r7_1) * fconvert.t(232f) + fconvert.t(12f))
00437cdd        float var_18 = fconvert.s(fconvert.t(var_1c) + fconvert.t(150f))
00437ce1        struct Color4f color
00437ce1        struct Color4f* eax_1
00437ce1        int32_t ecx_1
00437ce1        eax_1, ecx_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00437d00        int32_t var_4c = ecx_1
00437d0e        queue_axis_aligned_textured_quad_uv(0x9d, 0x41400000, fconvert.s(fconvert.t(var_18) - fconvert.t(39f)), 64f, 64f, 0x1000000, eax_1, 0, 0, 0x3f800000, 0x3f800000, 3, 0)
00437d28        float var_14 = fconvert.s(fconvert.t(var_1c) * fconvert.t(0.00390625f))
00437d72        queue_axis_aligned_textured_quad_uv(0x9b, 0x41500000, 0x43160000, 64f, var_1c, 0x1000000, set_color_rgba(&color, 1f, 1f, 1f, 1f), 0, 0, 0x3f800000, var_14, 3, 0)
00437da3        int32_t* eax_4
00437da3        int32_t ecx_4
00437da3        eax_4, ecx_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00437db8        int32_t var_44_1 = ecx_4
00437ddc        return queue_axis_aligned_textured_quad_uv(0x9c, 0x41500000, var_18, 64f, fconvert.s(fconvert.t(256f) - fconvert.t(var_1c)), 0x1000000, eax_4, 0, var_14, 0x3f800000, 0x3f800000, 3, 0)
