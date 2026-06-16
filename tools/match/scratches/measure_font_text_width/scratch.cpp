// measure_font_text_width @ 0x449e90 (cdecl)

#include "font_system.h"

float measure_font_text_width(char* text, int font_id, float scale)
{
    char* cursor = text;
    int font = font_id;
    float width = 0.0f;

    if (*cursor != '\0') {
        FontSheet* sheet = &g_font_sheets[font];
        do {
            int slot = font_slot_index_for_char(*cursor);
            ++cursor;
            width += sheet->glyph_width[slot] * sheet->spacing_scale *
                sheet->width_scale * scale;
        } while (*cursor != '\0');
    }

    FontSheet* sheet = &g_font_sheets[font];
    int space_slot = font_slot_index_for_char(' ');
    return width + (1.0f - sheet->width_scale) *
        sheet->glyph_width[space_slot] * sheet->spacing_scale * scale;
}
