/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_font_text_queue @ 0x44a730 */
/* selector: draw_font_text_queue */

// Void FontPrintRender counterpart: iterates the live cFontPrintBuffer queue backward and draws entries matching the supplied render mask. Its sole Windows caller discards EAX.
void __cdecl draw_font_text_queue(uint32_t render_mask)
{
  cFontPrintBuffer *v1; // esi
  int32_t v2; // ebx
  uint32_t flags; // eax

  if ( g_font_queue_count )
  {
    v1 = (cFontPrintBuffer *)(132 * g_font_queue_count + 7685352);
    v2 = g_font_queue_count;
    do
    {
      flags = v1[-1].flags;
      --v1;
      if ( (render_mask & flags & 0xFF000000) != 0 )
      {
        if ( (flags & 1) != 0 )
          draw_font_text_instance(v1);
        else
          draw_queued_font_quad_instance(v1);
      }
      --v2;
    }
    while ( v2 );
  }
}
