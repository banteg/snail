// initialize_global_font_queue_colors @ 0x449c50 (cdecl)

#include "font_system.h"

void initialize_global_font_queue_colors()
{
    FontQueueEntry* entry = g_font_queue;
    for (int count = FONT_QUEUE_CAPACITY; count != 0; --count) {
        entry->color.noop_this_constructor();
        ++entry;
    }
}
