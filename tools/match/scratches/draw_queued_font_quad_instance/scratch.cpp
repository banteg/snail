// draw_queued_font_quad_instance @ 0x44a6d0 (cdecl)

#include "font_system.h"

int draw_queued_font_quad_instance(FontQueueEntry* entry)
{
    return draw_textured_quad_immediate(
        g_sprite_texture_table[entry->texture_id],
        entry->x0,
        entry->y0,
        entry->x1,
        entry->y1,
        entry->x2,
        entry->y2,
        entry->x3,
        entry->y3,
        entry->width,
        entry->height,
        entry->u0,
        entry->v0,
        entry->u1,
        entry->v1,
        &entry->color,
        entry->layer,
        entry->blend);
}
