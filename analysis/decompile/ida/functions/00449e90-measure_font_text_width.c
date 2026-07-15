/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: measure_font_text_width @ 0x449e90 */
/* selector: measure_font_text_width */

// Accumulates atlas slot widths for one string using the registered font's spacing scalar and trailing space padding.
float __cdecl measure_font_text_width(char *text, int32_t font_id, float scale)
{
  char *v3; // ebp
  char v4; // al
  double v5; // st7
  float texta; // [esp+Ch] [ebp+4h]

  v3 = text;
  v4 = *text;
  texta = 0.0;
  if ( v4 )
  {
    do
    {
      ++v3;
      v5 = g_font_sheets[font_id].glyph_width[(char)font_slot_index_for_char(v4)] * g_font_sheets[font_id].spacing_scale;
      v4 = *v3;
      texta = v5 * g_font_sheets[font_id].width_scale * scale + texta;
    }
    while ( *v3 );
  }
  return (1.0 - g_font_sheets[font_id].width_scale)
       * g_font_sheets[font_id].glyph_width[(char)font_slot_index_for_char(32)]
       * g_font_sheets[font_id].spacing_scale
       * scale
       + texta;
}
