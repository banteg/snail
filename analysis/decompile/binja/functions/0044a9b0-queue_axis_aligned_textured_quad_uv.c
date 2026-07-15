/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_axis_aligned_textured_quad_uv @ 0x44a9b0 */

0044a9b0        int32_t result
0044a9b0        result.b = g_render_queue_active
0044a9b7        if (result.b != 0)
0044a9bd        int32_t font_queue_count_1 = g_font_queue_count
0044a9c9        if (font_queue_count_1 == 0x400)
0044a9d0        report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h")
0044a9d8        return 0
0044a9d9        long double x87_r7_1 = fconvert.t(width)
0044a9dd        long double temp0_1 = fconvert.t(0f)
0044a9dd        x87_r7_1 - temp0_1
0044a9e3        result.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
0044a9e8        if ((result:1.b & 0x40) == 0)
0044a9ee        long double x87_r7_2 = fconvert.t(height)
0044a9f2        long double temp1_1 = fconvert.t(0f)
0044a9f2        x87_r7_2 - temp1_1
0044a9f8        result.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
0044a9fd        if ((result:1.b & 0x40) == 0)
0044aa11        result = font_queue_count_1 * 0x84
0044aa19        *(result + &g_font_queue) = flags | 2
0044aa23        *(result + &g_font_queue[0].texture_id) = texture_id
0044aa2c        float* edx_4 = result + &g_font_queue[0].color
0044aa33        *edx_4 = color->r
0044aa38        edx_4[1] = color->g
0044aa3e        edx_4[2] = color->b
0044aa41        float a = color->a
0044aa45        g_font_queue_count = font_queue_count_1 + 1
0044aa4b        edx_4[3] = a
0044aa52        *(result + &g_font_queue[0].x0) = x
0044aa5c        *(result + &g_font_queue[0].y0) = y
0044aa66        *(result + &g_font_queue[0].width) = width
0044aa70        *(result + &g_font_queue[0].height) = height
0044aa7a        *(result + &g_font_queue[0].u0) = u0
0044aa84        *(result + &g_font_queue[0].v0) = v0
0044aa8e        *(result + &g_font_queue[0].u1) = u1
0044aa98        *(result + &g_font_queue[0].v1) = v1
0044aaa2        *(result + &g_font_queue[0].blend_mode) = blend_mode
0044aaac        *(result + &g_font_queue[0].rotation) = rotation
0044aab3        return result
