// queue_axis_aligned_textured_quad @ 0x44a8b0 (cdecl)

#include "font_system.h"

int queue_axis_aligned_textured_quad(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    tColour* color,
    int blend_mode)
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
                entry->u0 = 0.0f;
                entry->v0 = 0.0f;
                entry->u1 = 1.0f;
                entry->v1 = 1.0f;
                entry->blend_mode = blend_mode;
                g_font_queue_count = index + 1;
                entry->rotation = 0.0f;
                return offset;
            }
        }
    }
    return 0;
}
