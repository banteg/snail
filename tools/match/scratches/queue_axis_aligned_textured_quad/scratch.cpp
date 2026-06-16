// queue_axis_aligned_textured_quad @ 0x44a8b0 (cdecl)

#include "font_system.h"

int queue_axis_aligned_textured_quad(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    Color4f* color,
    int layer)
{
    if (g_font_queue_active != 0) {
        int index = g_font_queue_count;
        if (index == 0x400)
            return report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
        if (width != 0.0f) {
            if (height != 0.0f) {
                int offset = index * sizeof(FontQueueEntry);
                FontQueueEntry* entry = (FontQueueEntry*)((char*)g_font_queue + offset);
                entry->flags = flags | 2;
                entry->texture_id = texture_id;
                entry->color = *color;
                g_font_queue_count = index + 1;
                entry->x0 = x;
                entry->y0 = y;
                entry->width = width;
                entry->height = height;
                entry->u0 = 0.0f;
                entry->v0 = 0.0f;
                entry->u1 = 1.0f;
                entry->v1 = 1.0f;
                entry->layer = layer;
                entry->blend = 0;
                return offset;
            }
        }
    }
    return 0;
}
