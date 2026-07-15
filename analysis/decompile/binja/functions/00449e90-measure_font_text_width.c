/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: measure_font_text_width @ 0x449e90 */

00449e91        char* text_1 = text
00449e9a        int32_t eax
00449e9a        eax.b = *text_1
00449e9d        text = nullptr
00449ea7        while (eax.b != 0)
00449ecd        eax = sx.d(font_slot_index_for_char(eax.b)) + font_id * 0x20a
00449ed2        text_1 = &text_1[1]
00449eda        long double x87_r7_2 = fconvert.t(g_font_sheets[0].glyph_width[eax]) * fconvert.t(g_font_sheets[font_id].spacing_scale)
00449ee0        eax.b = *text_1
00449ef3        text = fconvert.s(x87_r7_2 * fconvert.t(g_font_sheets[font_id].width_scale) * fconvert.t(scale) + fconvert.t(text))
00449f1f        int32_t eax_4 = sx.d(font_slot_index_for_char(0x20))
00449f45        return ((fconvert.t(1f) - fconvert.t(g_font_sheets[font_id].width_scale)) * fconvert.t(g_font_sheets[0].glyph_width[eax_4 + font_id * 0x20a]) * fconvert.t(g_font_sheets[font_id].spacing_scale) * fconvert.t(scale) + fconvert.t(text)).d
