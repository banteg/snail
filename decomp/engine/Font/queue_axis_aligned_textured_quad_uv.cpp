// OSDPrintUV @ 0x44a9b0 (cdecl)

#include "font_system.h"

#pragma warning(disable: 4715)

int OSDPrintUV(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    int flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int blend_mode,
    float rotation)
{
    if (g_render_queue_active != 0) {
        int index = g_font_queue_count;
        if (index == 0x400)
            return report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
        if (width != 0.0f) {
            if (height != 0.0f) {
                int offset = index * sizeof(cFontPrintBuffer);
                g_font_queue[index].flags = flags | 2;
                g_font_queue[index].texture_id = texture_id;
                g_font_queue[index].color = *color;
                g_font_queue[index].x0 = x;
                g_font_queue[index].y0 = y;
                g_font_queue[index].width = width;
                g_font_queue[index].height = height;
                g_font_queue[index].u0 = u0;
                g_font_queue[index].v0 = v0;
                g_font_queue[index].u1 = u1;
                g_font_queue[index].v1 = v1;
                g_font_queue[index].blend_mode = blend_mode;
                g_font_queue[index].rotation = rotation;
                g_font_queue_count = index + 1;
                return offset;
            }
        }
    }
}
