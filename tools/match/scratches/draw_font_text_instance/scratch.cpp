// draw_font_text_instance @ 0x44a360 (cdecl)

#include "font_system.h"

void draw_font_text_instance(cFontPrintBuffer* entry)
{
    float cursor_x = entry->x0;
    int alignment = entry->horizontal_align;

    if (alignment == 2) {
        float width = measure_font_text_width(entry->text, entry->font_id, entry->text_scale);
        cursor_x = entry->anchor_x + 320.0f - width * 0.5f;
    } else if (alignment == 1) {
        measure_font_text_width(entry->text, entry->font_id, entry->text_scale);
        cursor_x = entry->anchor_x + 320.0f;
    } else if (alignment == 3) {
        float width = measure_font_text_width(entry->text, entry->font_id, entry->text_scale);
        cursor_x = entry->anchor_x + 320.0f - width;
    }

    char* cursor = entry->text;
    float wave_index = 0.0f;
    for (; *cursor != 0; ++cursor) {
        int slot = font_slot_index_for_char(*cursor);
        int font_id = entry->font_id;

        float u0 = g_font_sheets[font_id].glyph_u0[slot];
        float u1 = g_font_sheets[font_id].glyph_u1[slot];
        float v0 = g_font_sheets[font_id].glyph_v0;
        float v1 = g_font_sheets[font_id].glyph_v1;
        int texture_page = g_font_sheets[font_id].texture_page[slot];

        float wave_x = sine(g_font_wave_phase_a + wave_index)
            * entry->text_wave_amplitude * 2.0f;
        float wave_y = cosine(wave_index * 3.0f + g_font_wave_phase_a)
            * entry->text_wave_amplitude * 4.0f;
        wave_index = wave_index + 1.0f;

        float draw_x = (float)(int)(wave_x + cursor_x);
        float draw_y = (float)(int)(wave_y + entry->y0);

        if (slot != 0x35) {
            if (entry->shadow_enabled != 0
                && g_font_sheets[entry->font_id].shadow_offset_pixels > 0) {
                tColour shadow_color;
                draw_textured_quad_immediate(
                    (&g_font_sheets[entry->font_id].texture_ref_a)[texture_page],
                    draw_x
                        + (float)g_font_sheets[entry->font_id]
                            .shadow_offset_pixels,
                    draw_y
                        + (float)g_font_sheets[entry->font_id]
                            .shadow_offset_pixels,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    g_font_sheets[entry->font_id].glyph_width[slot]
                        * entry->text_scale
                        * g_font_sheets[entry->font_id].spacing_scale,
                    g_font_sheets[entry->font_id].line_marker_y
                        * entry->text_scale
                        * g_font_sheets[entry->font_id].spacing_scale,
                    u0,
                    v0,
                    u1,
                    v1,
                    shadow_color.Set(
                        0.0f, 0.0f, 0.0f, 0.800000012f),
                    2,
                    0);
            }

            draw_textured_quad_immediate(
                (&g_font_sheets[entry->font_id].texture_ref_a)[texture_page],
                draw_x,
                draw_y,
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                g_font_sheets[entry->font_id].glyph_width[slot]
                    * entry->text_scale
                    * g_font_sheets[entry->font_id].spacing_scale,
                g_font_sheets[entry->font_id].line_marker_y
                    * entry->text_scale
                    * g_font_sheets[entry->font_id].spacing_scale,
                u0,
                v0,
                u1,
                v1,
                &entry->color,
                1,
                0);
        }

        int advance =
            (int)g_font_sheets[entry->font_id].glyph_width[slot];
        cursor_x = (float)advance
            * g_font_sheets[entry->font_id].width_scale
            * g_font_sheets[entry->font_id].spacing_scale
            * entry->text_scale
            + cursor_x;
    }

}
