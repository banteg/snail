// queue_axis_aligned_textured_quad_uv @ 0x44a9b0 (cdecl)

#include "font_system.h"

int queue_axis_aligned_textured_quad_uv(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend)
{
    if (g_render_queue_active != 0) {
        int index = g_font_queue_count;
        if (index == 0x400)
            return report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
        if (width != 0.0f) {
            if (height != 0.0f) {
                int offset = index * sizeof(cFontPrintBuffer);
                cFontPrintBuffer* entry = (cFontPrintBuffer*)((char*)g_font_queue + offset);
                entry->flags = flags | 2;
                entry->texture_id = texture_id;
                entry->color = *color;
                entry->x0 = x;
                entry->y0 = y;
                entry->width = width;
                entry->height = height;
                entry->u0 = u0;
                entry->v0 = v0;
                entry->u1 = u1;
                entry->v1 = v1;
                entry->layer = layer;
                entry->blend = blend;
                g_font_queue_count = index + 1;
                return offset;
            }
        }
    }
    return 0;
}
