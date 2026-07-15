/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_font_text_instance @ 0x44a360 */

0044a365        struct cFontPrintBuffer* entry_1 = entry
0044a36c        entry = entry_1->x0
0044a370        int32_t horizontal_align = entry_1->horizontal_align
0044a376        if (horizontal_align == 2)
0044a384        long double st0_1
0044a384        st0_1, horizontal_align = measure_font_text_width(entry_1->text, entry_1->font_id, entry_1->text_scale)
0044a39f        entry = fconvert.s(fconvert.t(entry_1->anchor_x) + fconvert.t(320f) - st0_1 * fconvert.t(0.5f))
0044a3a8        if (horizontal_align == 1)
0044a3b6        int80_t st0_2
0044a3b6        st0_2, horizontal_align = measure_font_text_width(entry_1->text, entry_1->font_id, entry_1->text_scale)
0044a3c9        entry = fconvert.s(fconvert.t(entry_1->anchor_x) + fconvert.t(320f))
0044a3d2        if (horizontal_align == 3)
0044a3e0        long double st0_3
0044a3e0        st0_3, horizontal_align = measure_font_text_width(entry_1->text, entry_1->font_id, entry_1->text_scale)
0044a3f3        entry = fconvert.s(fconvert.t(entry_1->anchor_x) + fconvert.t(320f) - st0_3)
0044a3f9        char* text = entry_1->text
0044a3fc        float var_38 = 0f
0044a404        char* text_1 = text
0044a408        horizontal_align.b = *text
0044a40c        while (horizontal_align.b != 0)
0044a415        int32_t eax_4 = font_slot_index_for_char(horizontal_align.b)
0044a41c        int32_t font_id = entry_1->font_id
0044a43a        float u0 = g_font_sheets[0].u0[eax_4 + font_id * 0x20a]
0044a444        float u1 = g_font_sheets[0].v0[eax_4 + font_id * 0x20a]
0044a455        int32_t ecx_9 = g_font_sheets[0].texture_page[eax_4 + font_id * 0x20a]
0044a468        float line_step = g_font_sheets[font_id].line_step
0044a46e        float line_marker_fraction = g_font_sheets[font_id].line_marker_fraction
0044a481        long double x87_r7_13 = sine(fconvert.s(fconvert.t(g_font_wave_phase_a) + fconvert.t(var_38))) * fconvert.t(entry_1->text_wave_amplitude)
0044a49d        int16_t x87control_1
0044a49d        long double st0_5
0044a49d        st0_5, x87control_1 = cosine(fconvert.s(fconvert.t(var_38) * fconvert.t(3f) + fconvert.t(g_font_wave_phase_a)))
0044a4a8        long double x87_r7_20 = st0_5 * fconvert.t(entry_1->text_wave_amplitude) * fconvert.t(4f)
0044a4b8        var_38 = fconvert.s(fconvert.t(var_38) + fconvert.t(1f))
0044a4c4        int32_t eax_7
0044a4c4        int16_t x87control_2
0044a4c4        eax_7, x87control_2 = ftol(x87control_1, fconvert.t(fconvert.s(x87_r7_13 + x87_r7_13)) + fconvert.t(entry))
0044a4d1        float x0 = fconvert.s(float.t(eax_7))
0044a4d8        int32_t eax_8
0044a4d8        int16_t x87control_3
0044a4d8        eax_8, x87control_3 = ftol(x87control_2, x87_r7_20 + fconvert.t(entry_1->y0))
0044a4e8        float y0 = fconvert.s(float.t(eax_8))
0044a4ec        if (eax_4 != 0x35)
0044a4f7        if (entry_1->text_wave_enabled != 0 && g_font_sheets[entry_1->font_id].font_kind s> 0)
0044a519        int32_t font_id_1 = entry_1->font_id
0044a54c        float var_34_1 = fconvert.s(float.t(g_font_sheets[font_id_1].font_kind))
0044a550        int32_t ebx_1 = font_id_1 * 0x20a
0044a552        struct tColour color
0044a552        struct tColour* color_1 = set_color_rgba(&color, 0f, 0f, 0f, 0.800000012f)
0044a57b        float u1_1 = u1
0044a57c        int32_t ecx_16 = ebx_1 + eax_4
0044a590        int32_t var_6c_1 = ecx_16
0044a5b7        int32_t var_88_1 = ecx_16
0044a5c3        int32_t var_8c_1 = ecx_16
0044a5c8        draw_textured_quad_immediate((&g_font_sheets[0].texture_ref_a)[ebx_1 + ecx_9], fconvert.s(fconvert.t(var_34_1) + fconvert.t(x0)), fconvert.s(fconvert.t(var_34_1) + fconvert.t(y0)), 0f, 0f, 0f, 0f, 0f, 0f, fconvert.s(fconvert.t(g_font_sheets[0].glyph_width[ecx_16]) * fconvert.t(entry_1->text_scale) * fconvert.t(g_font_sheets[font_id_1].spacing_scale)), fconvert.s(fconvert.t(g_font_sheets[font_id_1].line_marker_y) * fconvert.t(entry_1->text_scale) * fconvert.t(g_font_sheets[font_id_1].spacing_scale)), u0, line_step, u1, line_marker_fraction, color_1, 2, 0f)
0044a5cd        text = text_1
0044a5d4        int32_t font_id_2 = entry_1->font_id
0044a5f7        int32_t ecx_21 = font_id_2 * 0x828
0044a618        int32_t eax_16 = font_id_2 * 0x20a
0044a61b        int32_t var_68_2 = ecx_21
0044a62c        int32_t var_6c_3 = ecx_21
0044a65a        x87control_3 = draw_textured_quad_immediate((&g_font_sheets[0].texture_ref_a)[eax_16 + ecx_9], x0, y0, 0f, 0f, 0f, 0f, 0f, 0f, fconvert.s(fconvert.t(g_font_sheets[0].glyph_width[eax_16 + eax_4]) * fconvert.t(entry_1->text_scale) * fconvert.t(g_font_sheets[font_id_2].spacing_scale)), fconvert.s(fconvert.t(g_font_sheets[font_id_2].line_marker_y) * fconvert.t(entry_1->text_scale) * fconvert.t(g_font_sheets[font_id_2].spacing_scale)), u0, line_step, u1, line_marker_fraction, &entry_1->color, 1, 0f)
0044a662        int32_t font_id_3 = entry_1->font_id
0044a687        horizontal_align = ftol(x87control_3, fconvert.t(g_font_sheets[0].glyph_width[eax_4 + font_id_3 * 0x20a]))
0044a68c        int32_t horizontal_align_1 = horizontal_align
0044a690        horizontal_align.b = text[1]
0044a697        text = &text[1]
0044a6a0        text_1 = text
0044a6b1        entry = fconvert.s(float.t(horizontal_align_1) * fconvert.t(g_font_sheets[font_id_3].width_scale) * fconvert.t(g_font_sheets[font_id_3].spacing_scale) * fconvert.t(entry_1->text_scale) + fconvert.t(entry))
0044a6c2        return
