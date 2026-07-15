/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_font_text_instance @ 0x44a790 */

0044a797        if (g_render_queue_active == 0)
0044a797        return
0044a79d        int32_t font_queue_count_1 = g_font_queue_count
0044a7a9        if (font_queue_count_1 == 0x400)
0044a7a9        return
0044a7c5        g_font_queue[font_queue_count_1].flags = flags | 1
0044a7cf        g_font_queue[font_queue_count_1].font_id = font_id
0044a7dd        g_font_queue[font_queue_count_1].text_scale = text_scale
0044a7e7        g_font_queue[font_queue_count_1].x0 = x
0044a7f1        g_font_queue[font_queue_count_1].y0 = y
0044a7fb        g_font_queue[font_queue_count_1].horizontal_align = horizontal_align
0044a801        g_font_queue[font_queue_count_1].anchor_x = anchor_x
0044a807        char* font_text_cursor_1 = g_font_text_cursor
0044a80e        g_font_queue[font_queue_count_1].text = font_text_cursor_1
0044a816        void* edx_4 = &g_font_queue[font_queue_count_1].color
0044a81c        g_font_queue[font_queue_count_1].color.r = color->r
0044a825        *(edx_4 + 4) = color->g
0044a82b        *(edx_4 + 8) = color->b
0044a832        *(edx_4 + 0xc) = color->a
0044a839        g_font_queue[font_queue_count_1].text_wave_amplitude = text_wave_amplitude
0044a843        g_font_queue[font_queue_count_1].text_wave_enabled = text_wave_enabled
0044a849        char* text_1 = text
0044a851        while (*text_1 != 0)
0044a861        if (font_text_cursor_1 - &g_font_text_buffer s> 0x7fe)
0044a896        *font_text_cursor_1 = 0
0044a89f        g_font_text_cursor = &g_font_text_cursor[1]
0044a8a4        return
0044a865        *font_text_cursor_1 = *text_1
0044a86d        font_text_cursor_1 = &g_font_text_cursor[1]
0044a86e        text_1 = &text_1[1]
0044a86f        g_font_text_cursor = font_text_cursor_1
0044a87a        *font_text_cursor_1 = 0
0044a889        int32_t eax_5 = g_font_queue_count + 1
0044a88a        g_font_text_cursor = &g_font_text_cursor[1]
0044a890        g_font_queue_count = eax_5
0044a895        return
