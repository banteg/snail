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
    while (*cursor != 0) {
        int slot = font_slot_index_for_char(*cursor);
        int font_id = entry->font_id;
        FontSheet* sheet = &g_font_sheets[font_id];

        float u0 = g_font_sheets[font_id].u0[slot];
        float u1 = g_font_sheets[font_id].v0[slot];
        int texture_page = g_font_sheets[font_id].texture_page[slot];
        float v0 = g_font_sheets[font_id].line_step;
        float v1 = g_font_sheets[font_id].line_marker_fraction;

        float wave_x = sine(g_font_wave_phase_a + wave_index) * entry->text_wave_amplitude * 2.0f;
        float wave_y = cosine(wave_index * 3.0f + g_font_wave_phase_a) * entry->text_wave_amplitude * 4.0f;
        wave_index = wave_index + 1.0f;

        float draw_x = (float)(int)(wave_x + cursor_x);
        float draw_y = (float)(int)(wave_y + entry->y0);

        if (slot != 0x35) {
            TextureRef** textures = &sheet->texture_ref_a;
            TextureRef* texture = textures[texture_page];
            float glyph_width = sheet->glyph_width[slot] * entry->text_scale * sheet->spacing_scale;
            float glyph_height = sheet->line_marker_y * entry->text_scale * sheet->spacing_scale;

            if (entry->text_wave_enabled != 0 && sheet->font_kind > 0) {
                Color4f shadow_color;
                shadow_color.set_color_rgba(0.0f, 0.0f, 0.0f, 0.800000012f);
                float shadow_offset = (float)sheet->font_kind;
                draw_textured_quad_immediate(
                    texture,
                    draw_x + shadow_offset,
                    draw_y + shadow_offset,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    glyph_width,
                    glyph_height,
                    u0,
                    v0,
                    u1,
                    v1,
                    &shadow_color,
                    2,
                    0);
            }

            draw_textured_quad_immediate(
                texture,
                draw_x,
                draw_y,
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                0.0f,
                glyph_width,
                glyph_height,
                u0,
                v0,
                u1,
                v1,
                &entry->color,
                1,
                0);
        }

        int advance = (int)sheet->glyph_width[slot];
        ++cursor;
        cursor_x = (float)advance * sheet->width_scale * sheet->spacing_scale
            * entry->text_scale + cursor_x;
    }

}
