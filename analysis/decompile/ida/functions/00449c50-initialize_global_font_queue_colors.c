/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_global_font_queue_colors @ 0x449c50 */
/* selector: initialize_global_font_queue_colors */

// Runs the folded trivial tColour constructor over the +0x6c color member of all 1024 global cFontPrintBuffer entries at a 0x84-byte stride. Android independently preserves the authored cFontPrintBuffer class name, identical stride, and color-member offset.
void __cdecl initialize_global_font_queue_colors()
{
  tColour *p_color; // esi
  int v1; // edi

  p_color = &g_font_queue[0].color;
  v1 = 1024;
  do
  {
    noop_this_constructor(p_color);
    p_color = (tColour *)((char *)p_color + 132);
    --v1;
  }
  while ( v1 );
}
