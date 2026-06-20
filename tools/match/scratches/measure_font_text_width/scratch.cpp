// measure_font_text_width @ 0x449e90 (cdecl)

#include "font_system.h"

float measure_font_text_width(char* text, int font_id, float scale)
{
    char* cursor = text;
    float width = 0.0f;

    if (*cursor != '\0') {
        int glyph_lane_base = font_id;
        int sheet_lane_base = font_id;
        glyph_lane_base <<= 6;
        sheet_lane_base <<= 6;
        glyph_lane_base += font_id;
        sheet_lane_base += font_id;
        glyph_lane_base = font_id + glyph_lane_base * 4;
        sheet_lane_base = font_id + sheet_lane_base * 4;
        glyph_lane_base <<= 1;
        sheet_lane_base <<= 3;
        do {
            int slot = (char)font_slot_index_for_char(*cursor);
            ++cursor;
            float glyph_width =
                ((float*)((char*)g_font_sheets + 0x40c))[glyph_lane_base + slot];
            glyph_width *= *(float*)((char*)g_font_sheets + sheet_lane_base + 0x818);
            glyph_width *= *(float*)((char*)g_font_sheets + sheet_lane_base + 0x81c);
            width += glyph_width * scale;
        } while (*cursor != '\0');
    }

    char space_slot = font_slot_index_for_char(' ');
    int glyph_lane_base = font_id;
    int sheet_lane_base = font_id;
    glyph_lane_base <<= 6;
    glyph_lane_base += font_id;
    sheet_lane_base <<= 6;
    sheet_lane_base += font_id;
    glyph_lane_base = font_id + glyph_lane_base * 4;
    sheet_lane_base = font_id + sheet_lane_base * 4;
    glyph_lane_base <<= 1;
    sheet_lane_base <<= 3;
    return width +
        (1.0f - *(float*)((char*)g_font_sheets + sheet_lane_base + 0x81c)) *
            ((float*)((char*)g_font_sheets + 0x40c))[glyph_lane_base + space_slot] *
            *(float*)((char*)g_font_sheets + sheet_lane_base + 0x818) * scale;
}
