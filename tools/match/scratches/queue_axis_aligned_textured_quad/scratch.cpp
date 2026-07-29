// queue_axis_aligned_textured_quad @ 0x44a8b0 (cdecl)

#include "font_system.h"

#pragma warning(disable: 4715)

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
                float& stored_u0 = entry->u0;
                float& stored_v0 = entry->v0;
                float& stored_u1 = entry->u1;
                float& stored_v1 = entry->v1;
                stored_u0 = 0.0f;
                stored_v0 = 0.0f;
                stored_u1 = 1.0f;
                stored_v1 = 1.0f;
                entry->blend_mode = blend_mode;
                g_font_queue_count = index + 1;
                entry->rotation = 0.0f;
                return offset;
            }
        }
    }
}
