/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_font_text_queue @ 0x44a730 */

0044a730        int32_t font_queue_count_1 = g_font_queue_count
0044a737        if (font_queue_count_1 == 0)
0044a737        return
0044a747        struct cFontPrintBuffer* entry = &g_font_queue[font_queue_count_1]
0044a74e        int32_t ebx_1 = font_queue_count_1
0044a77d        int32_t i
0044a750        int32_t eax = entry->__offset(0xffffffffffffff7c).d
0044a756        entry -= 0x84
0044a766        if ((eax & render_mask & 0xff000000) != 0)
0044a76b        if ((eax.b & 1) == 0)
0044a774        draw_queued_font_quad_instance(entry)
0044a76d        draw_font_text_instance(entry)
0044a77c        i = ebx_1
0044a77c        ebx_1 -= 1
0044a77d        do while (i != 1)
0044a782        return
