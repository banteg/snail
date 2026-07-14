// draw_font_text_queue @ 0x44a730 (cdecl)

#include "font_system.h"

void draw_font_text_queue(unsigned int render_mask)
{
    int count = g_font_queue_count;
    if (count != 0) {
        cFontPrintBuffer* entry = &g_font_queue[count];
        int remaining = count;
        do {
            --entry;
            unsigned int flags = entry->flags;
            if ((flags & render_mask & 0xff000000) != 0) {
                if ((flags & 1) != 0)
                    draw_font_text_instance(entry);
                else
                    draw_queued_font_quad_instance(entry);
            }
        } while (--remaining != 0);
    }
}
