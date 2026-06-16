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
        if (index != 0x400) {
            int offset = index * sizeof(FontQueueEntry);
            ((FontQueueEntry*)((char*)g_font_queue + offset))->flags = flags | 1;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->font_id = font_id;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->text_scale = text_scale;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->x0 = x;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->y0 = y;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->horizontal_align = horizontal_align;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->anchor_x = anchor_x;
            char* cursor = g_font_text_cursor;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->text = cursor;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->color = *color;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->text_wave_amplitude = text_wave_amplitude;
            ((FontQueueEntry*)((char*)g_font_queue + offset))->text_wave_enabled = text_wave_enabled;

            if (*text != '\0') {
                do {
                    if (cursor - g_font_text_buffer > 0x7fe) {
                        *cursor = '\0';
                        char* next = g_font_text_cursor + 1;
                        g_font_text_cursor = next;
                        return;
                    }
                    *cursor = *text;
                    cursor = g_font_text_cursor + 1;
                    ++text;
                    g_font_text_cursor = cursor;
                } while (*text != '\0');
            }

            *cursor = '\0';
            char* next = g_font_text_cursor + 1;
            int count = g_font_queue_count + 1;
            g_font_text_cursor = next;
            g_font_queue_count = count;
        }
    }
}
