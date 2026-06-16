// queue_textured_quad_corners @ 0x44aac0 (cdecl)

#include "font_system.h"

int queue_textured_quad_corners(
    int texture_id,
    float x0,
    float y0,
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3,
    int unused_28,
    int unused_2c,
    unsigned int flags,
    Color4f* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend)
{
    (void)unused_28;
    (void)unused_2c;

    if (g_render_queue_active != 0) {
        int index = g_font_queue_count;
        if (index == 0x400)
            return report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");

        int offset = index * sizeof(FontQueueEntry);
        FontQueueEntry* entry = (FontQueueEntry*)((char*)g_font_queue + offset);
        entry->flags = flags | 2;
        entry->texture_id = texture_id;
        entry->color = *color;
        g_font_queue_count = index + 1;
        entry->x0 = x0;
        entry->y0 = y0;
        entry->x1 = x1;
        entry->y1 = y1;
        entry->x2 = x2;
        entry->y2 = y2;
        entry->x3 = x3;
        entry->y3 = y3;
        entry->width = 0.0f;
        entry->height = 0.0f;
        entry->u0 = u0;
        entry->v0 = v0;
        entry->u1 = u1;
        entry->v1 = v1;
        entry->layer = layer;
        entry->blend = blend;
        return offset;
    }
    return 0;
}
