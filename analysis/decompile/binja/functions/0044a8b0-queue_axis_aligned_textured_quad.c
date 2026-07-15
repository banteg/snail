/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_axis_aligned_textured_quad @ 0x44a8b0 */

0044a8b0        int32_t result
0044a8b0        result.b = g_render_queue_active
0044a8b9        if (result.b != 0)
0044a8bf        int32_t font_queue_count_1 = g_font_queue_count
0044a8cb        if (font_queue_count_1 == 0x400)
0044a8d2        report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h")
0044a8da        return 0
0044a8db        long double x87_r7_1 = fconvert.t(width)
0044a8df        long double temp0_1 = fconvert.t(0f)
0044a8df        x87_r7_1 - temp0_1
0044a8e5        result.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
0044a8ea        if ((result:1.b & 0x40) == 0)
0044a8f0        long double x87_r7_2 = fconvert.t(height)
0044a8f4        long double temp1_1 = fconvert.t(0f)
0044a8f4        x87_r7_2 - temp1_1
0044a8fa        result.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
0044a8ff        if ((result:1.b & 0x40) == 0)
0044a915        result = font_queue_count_1 * 0x84
0044a91d        *(result + &g_font_queue) = flags | 2
0044a927        *(result + &g_font_queue[0].texture_id) = texture_id
0044a92f        float* esi_4 = result + &g_font_queue[0].color
0044a936        *esi_4 = color->r
0044a93b        esi_4[1] = color->g
0044a941        esi_4[2] = color->b
0044a944        float a = color->a
0044a947        g_font_queue_count = font_queue_count_1 + 1
0044a94d        esi_4[3] = a
0044a954        *(result + &g_font_queue[0].x0) = x
0044a95e        *(result + &g_font_queue[0].y0) = y
0044a968        *(result + &g_font_queue[0].width) = width
0044a972        *(result + &g_font_queue[0].height) = height
0044a978        *(result + &g_font_queue[0].u0) = 0
0044a983        *(result + &g_font_queue[0].v0) = 0
0044a989        *(result + &g_font_queue[0].u1) = 0x3f800000
0044a98f        *(result + &g_font_queue[0].v1) = 0x3f800000
0044a99a        *(result + &g_font_queue[0].blend_mode) = blend_mode
0044a9a1        *(result + &g_font_queue[0].rotation) = 0
0044a9a8        return result
