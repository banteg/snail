/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_font_text_instance @ 0x44a360 */

0044a36c        float cursor_x = entry->x0
0044a370        int32_t horizontal_align = entry->horizontal_align
0044a376        if (horizontal_align == 2)
0044a384        long double st0_1 = measure_font_text_width(entry->text, entry->font_id, entry->text_scale)
0044a39f        cursor_x = fconvert.s(fconvert.t(entry->anchor_x) + fconvert.t(320f) - st0_1 * fconvert.t(0.5f))
0044a3a8        if (horizontal_align == 1)
0044a3b6        measure_font_text_width(entry->text, entry->font_id, entry->text_scale)
0044a3c9        cursor_x = fconvert.s(fconvert.t(entry->anchor_x) + fconvert.t(320f))
0044a3d2        if (horizontal_align == 3)
0044a3e0        long double st0_3 = measure_font_text_width(entry->text, entry->font_id, entry->text_scale)
0044a3f3        cursor_x = fconvert.s(fconvert.t(entry->anchor_x) + fconvert.t(320f) - st0_3)
0044a3f9        char* text_cursor = entry->text
0044a3fc        float wave_index = 0f
0044a404        char* text_resume = text_cursor
0044a408        char current_char = *text_cursor
0044a40c        while (current_char != 0)
0044a415        int32_t glyph_slot = font_slot_index_for_char(current_char)
0044a41c        int32_t font_id = entry->font_id
0044a43a        float atlas_u0 = g_font_sheets[0].u0[glyph_slot + font_id * 0x20a]
0044a444        float atlas_u1 = g_font_sheets[0].v0[glyph_slot + font_id * 0x20a]
0044a455        int32_t texture_page = g_font_sheets[0].texture_page[glyph_slot + font_id * 0x20a]
0044a468        float atlas_v0 = g_font_sheets[font_id].line_step
0044a46e        float atlas_v1 = g_font_sheets[font_id].line_marker_fraction
0044a481        long double x87_r7_13 = sine(fconvert.s(fconvert.t(g_font_wave_phase_a) + fconvert.t(wave_index))) * fconvert.t(entry->text_wave_amplitude)
0044a49d        int16_t x87control_1
0044a49d        long double st0_5
0044a49d        st0_5, x87control_1 = cosine(fconvert.s(fconvert.t(wave_index) * fconvert.t(3f) + fconvert.t(g_font_wave_phase_a)))
0044a4a8        long double x87_r7_20 = st0_5 * fconvert.t(entry->text_wave_amplitude) * fconvert.t(4f)
0044a4b8        wave_index = fconvert.s(fconvert.t(wave_index) + fconvert.t(1f))
0044a4c4        int32_t eax_6
0044a4c4        int16_t x87control_2
0044a4c4        eax_6, x87control_2 = ftol(x87control_1, fconvert.t(fconvert.s(x87_r7_13 + x87_r7_13)) + fconvert.t(cursor_x))
0044a4d1        float draw_x = fconvert.s(float.t(eax_6))
0044a4d8        int32_t eax_7
0044a4d8        int16_t x87control_3
0044a4d8        eax_7, x87control_3 = ftol(x87control_2, x87_r7_20 + fconvert.t(entry->y0))
0044a4e8        float draw_y = fconvert.s(float.t(eax_7))
0044a4ec        if (glyph_slot != 0x35)
0044a4f7        if (entry->text_wave_enabled != 0 && g_font_sheets[entry->font_id].font_kind s> 0)
0044a519        int32_t font_id_1 = entry->font_id
0044a54c        float shadow_offset = fconvert.s(float.t(g_font_sheets[font_id_1].font_kind))
0044a550        int32_t ebx_1 = font_id_1 * 0x20a
0044a552        struct tColour color
0044a552        struct tColour* shadow_color = set_color_rgba(&color, 0f, 0f, 0f, 0.800000012f)
0044a57b        float atlas_u1_1 = atlas_u1
0044a57c        int32_t ecx_15 = ebx_1 + glyph_slot
0044a590        int32_t var_6c_1 = ecx_15
0044a5b7        int32_t var_88_1 = ecx_15
0044a5c3        int32_t var_8c_1 = ecx_15
0044a5c8        draw_textured_quad_immediate((&g_font_sheets[0].texture_ref_a)[ebx_1 + texture_page], fconvert.s(fconvert.t(shadow_offset) + fconvert.t(draw_x)), fconvert.s(fconvert.t(shadow_offset) + fconvert.t(draw_y)), 0f, 0f, 0f, 0f, 0f, 0f, fconvert.s(fconvert.t(g_font_sheets[0].glyph_width[ecx_15]) * fconvert.t(entry->text_scale) * fconvert.t(g_font_sheets[font_id_1].spacing_scale)), fconvert.s(fconvert.t(g_font_sheets[font_id_1].line_marker_y) * fconvert.t(entry->text_scale) * fconvert.t(g_font_sheets[font_id_1].spacing_scale)), atlas_u0, atlas_v0, atlas_u1, atlas_v1, shadow_color, 2, 0f)
0044a5cd        text_cursor = text_resume
0044a5d4        int32_t font_id_2 = entry->font_id
0044a5f7        int32_t ecx_20 = font_id_2 * 0x828
0044a618        int32_t eax_15 = font_id_2 * 0x20a
0044a61b        int32_t var_68_2 = ecx_20
0044a62c        int32_t var_6c_3 = ecx_20
0044a65a        x87control_3 = draw_textured_quad_immediate((&g_font_sheets[0].texture_ref_a)[eax_15 + texture_page], draw_x, draw_y, 0f, 0f, 0f, 0f, 0f, 0f, fconvert.s(fconvert.t(g_font_sheets[0].glyph_width[eax_15 + glyph_slot]) * fconvert.t(entry->text_scale) * fconvert.t(g_font_sheets[font_id_2].spacing_scale)), fconvert.s(fconvert.t(g_font_sheets[font_id_2].line_marker_y) * fconvert.t(entry->text_scale) * fconvert.t(g_font_sheets[font_id_2].spacing_scale)), atlas_u0, atlas_v0, atlas_u1, atlas_v1, &entry->color, 1, 0f)
0044a662        int32_t font_id_3 = entry->font_id
0044a687        int32_t glyph_advance = ftol(x87control_3, fconvert.t(g_font_sheets[0].glyph_width[glyph_slot + font_id_3 * 0x20a]))
0044a690        current_char = text_cursor[1]
0044a697        text_cursor = &text_cursor[1]
0044a6a0        text_resume = text_cursor
0044a6b1        cursor_x = fconvert.s(float.t(glyph_advance) * fconvert.t(g_font_sheets[font_id_3].width_scale) * fconvert.t(g_font_sheets[font_id_3].spacing_scale) * fconvert.t(entry->text_scale) + fconvert.t(cursor_x))
0044a6c2        return
