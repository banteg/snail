/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_queued_font_quad_instance @ 0x44a6d0 */
/* selector: draw_queued_font_quad_instance */

// Void OSDPrintReal counterpart over one cFontPrintBuffer: forwards its stored coordinates, UVs, size mode, angle, and color into the shared immediate textured-quad helper. The queue drain discards EAX.
void __cdecl draw_queued_font_quad_instance(cFontPrintBuffer *entry)
{
  draw_textured_quad_immediate(
    LODWORD(g_sprite_texture_table[entry->texture_id]),
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
    (Color4f *)&entry->color,
    entry->blend_mode,
    entry->rotation);
}
