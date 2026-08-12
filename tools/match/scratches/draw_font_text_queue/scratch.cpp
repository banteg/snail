// FontPrintRender @ 0x44a730 (cdecl)

#include "font_system.h"
#include "render_scene.h"

void FontPrintRender(int render_mask)
{
    int count = g_font_queue_count;
    if (count != 0) {
        cFontPrintBuffer* entry = &g_font_queue[count];
        int remaining = count;
        do {
            --entry;
            unsigned int flags = entry->flags;
            if ((flags & render_mask & RENDER_SCENE_MASK) != 0) {
                if ((flags & 1) != 0)
                    FontPrintReal(entry);
                else
                    OSDPrintReal(entry);
            }
        } while (--remaining != 0);
    }
}
