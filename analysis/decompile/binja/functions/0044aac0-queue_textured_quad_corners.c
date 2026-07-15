/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_textured_quad_corners @ 0x44aac0 */

0044aac0        int32_t result
0044aac0        result.b = g_render_queue_active
0044aac9        if (result.b != 0)
0044aacf        int32_t font_queue_count_1 = g_font_queue_count
0044aadb        if (font_queue_count_1 == 0x400)
0044aae2        report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h")
0044aaea        return 0
0044aafb        result = font_queue_count_1 * 0x84
0044ab03        *(result + &g_font_queue) = flags | 2
0044ab0d        *(result + &g_font_queue[0].texture_id) = texture_id
0044ab15        float* esi_4 = result + &g_font_queue[0].color
0044ab1c        *esi_4 = color->r
0044ab21        esi_4[1] = color->g
0044ab27        esi_4[2] = color->b
0044ab2a        float a = color->a
0044ab2d        g_font_queue_count = font_queue_count_1 + 1
0044ab33        esi_4[3] = a
0044ab3a        *(result + &g_font_queue[0].x0) = x0
0044ab44        *(result + &g_font_queue[0].y0) = y0
0044ab4e        *(result + &g_font_queue[0].x1) = x1
0044ab58        *(result + &g_font_queue[0].y1) = y1
0044ab62        *(result + &g_font_queue[0].x2) = x2
0044ab6c        *(result + &g_font_queue[0].y2) = y2
0044ab76        *(result + &g_font_queue[0].x3) = x3
0044ab80        *(result + &g_font_queue[0].y3) = y3
0044ab86        *(result + &g_font_queue[0].width) = 0
0044ab8c        *(result + &g_font_queue[0].height) = 0
0044ab96        *(result + &g_font_queue[0].u0) = u0
0044aba0        *(result + &g_font_queue[0].v0) = v0
0044abaa        *(result + &g_font_queue[0].u1) = u1
0044abb4        *(result + &g_font_queue[0].v1) = v1
0044abbe        *(result + &g_font_queue[0].blend_mode) = blend_mode
0044abca        *(result + &g_font_queue[0].rotation) = rotation
0044abd1        return result
