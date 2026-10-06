// OSDPrint @ 0x44a8b0 (cdecl)

#include "font_system.h"

#pragma warning(disable: 4715)

int OSDPrint(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    int flags,
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
                g_font_queue[index].flags = flags | 2;
                g_font_queue[index].texture_id = texture_id;
                g_font_queue[index].color = *color;
                g_font_queue[index].x0 = x;
                g_font_queue[index].y0 = y;
                g_font_queue[index].width = width;
                g_font_queue[index].height = height;
                g_font_queue[index].u0 = 0.0f;
                g_font_queue[index].v0 = 0.0f;
                g_font_queue[index].u1 = 1.0f;
                g_font_queue[index].v1 = 1.0f;
                g_font_queue[index].blend_mode = blend_mode;
                g_font_queue_count = index + 1;
                g_font_queue[index].rotation = 0.0f;
                return offset;
            }
        }
    }
}
