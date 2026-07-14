// queue_font_text_instance @ 0x44a790 (cdecl)

#include "font_system.h"

void queue_font_text_instance(
    char* text,
    int font_id,
    float text_scale,
    float x,
    float y,
    int horizontal_align,
    float anchor_x,
    unsigned int flags,
    Color4f* color,
    float text_wave_amplitude,
    char text_wave_enabled)
{
    if (g_render_queue_active != 0) {
        int index = g_font_queue_count;
        if (index != FONT_QUEUE_CAPACITY) {
            int offset = index * sizeof(cFontPrintBuffer);
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->flags = flags | 1;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->font_id = font_id;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->text_scale = text_scale;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->x0 = x;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->y0 = y;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->horizontal_align = horizontal_align;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->anchor_x = anchor_x;
            char* cursor = g_font_text_cursor;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->text = cursor;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->color = *color;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->text_wave_amplitude = text_wave_amplitude;
            ((cFontPrintBuffer*)((char*)g_font_queue + offset))->text_wave_enabled = text_wave_enabled;

            register char* source = text;
            while (*source != '\0') {
                if (cursor - g_font_text_buffer > FONT_TEXT_BUFFER_CAPACITY - 2) {
                    *cursor = '\0';
                    char* next = g_font_text_cursor + 1;
                    g_font_text_cursor = next;
                    return;
                }
                *cursor = *source;
                cursor = g_font_text_cursor + 1;
                ++source;
                g_font_text_cursor = cursor;
            }

            *cursor = '\0';
            char* next = g_font_text_cursor + 1;
            int count = g_font_queue_count + 1;
            g_font_text_cursor = next;
            g_font_queue_count = count;
        }
    }
}
