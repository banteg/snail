// OSDPrintUV @ 0x44aac0 (cdecl)

#include "font_system.h"

#pragma warning(disable: 4715)

int OSDPrintUV(
    int texture_id,
    float x0,
    float y0,
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3,
    float unused_28,
    float unused_2c,
    int flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int blend_mode,
    float rotation)
{
    (void)unused_28;
    (void)unused_2c;

    if (g_render_queue_active != 0) {
        int index = g_font_queue_count;
        if (index == 0x400)
            return report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");

        int offset = index * sizeof(cFontPrintBuffer);
        g_font_queue[index].flags = flags | 2;
        g_font_queue[index].texture_id = texture_id;
        g_font_queue[index].color = *color;
        g_font_queue[index].x0 = x0;
        g_font_queue[index].y0 = y0;
        g_font_queue[index].x1 = x1;
        g_font_queue[index].y1 = y1;
        g_font_queue[index].x2 = x2;
        g_font_queue[index].y2 = y2;
        g_font_queue[index].x3 = x3;
        g_font_queue[index].y3 = y3;
        g_font_queue[index].width = 0.0f;
        g_font_queue[index].height = 0.0f;
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
