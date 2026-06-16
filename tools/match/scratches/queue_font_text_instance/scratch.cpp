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
            *(unsigned int*)((char*)g_font_queue + offset + 0x00) = flags | 1;
            *(int*)((char*)g_font_queue + offset + 0x3c) = font_id;
            *(float*)((char*)g_font_queue + offset + 0x40) = text_scale;
            *(float*)((char*)g_font_queue + offset + 0x04) = x;
            *(float*)((char*)g_font_queue + offset + 0x08) = y;
            *(int*)((char*)g_font_queue + offset + 0x48) = horizontal_align;
            *(float*)((char*)g_font_queue + offset + 0x4c) = anchor_x;
            char* cursor = g_font_text_cursor;
            *(char**)((char*)g_font_queue + offset + 0x44) = cursor;
            *(Color4f*)((char*)g_font_queue + offset + 0x6c) = *color;
            *(float*)((char*)g_font_queue + offset + 0x34) = text_wave_amplitude;
            *(char*)((char*)g_font_queue + offset + 0x38) = text_wave_enabled;

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
