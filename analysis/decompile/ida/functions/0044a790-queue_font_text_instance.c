/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_font_text_instance @ 0x44a790 */
/* selector: queue_font_text_instance */

// FontPrint counterpart: copies one text run into the shared font print string buffer and appends the matching cFontPrintBuffer record with its font, position, alignment, colors, and render flags.
void __cdecl queue_font_text_instance(
        char *text,
        int32_t font_id,
        float text_scale,
        float x,
        float y,
        int32_t horizontal_align,
        float anchor_x,
        uint32_t flags,
        tColour *color,
        float text_wave_amplitude,
        uint8_t text_wave_enabled)
{
  int32_t v11; // eax
  char *v12; // ecx
  char *v13; // eax

  if ( g_render_queue_active && g_font_queue_count != 1024 )
  {
    v11 = g_font_queue_count;
    g_font_queue[v11].flags = flags | 1;
    g_font_queue[v11].font_id = font_id;
    g_font_queue[v11].text_scale = text_scale;
    g_font_queue[v11].x0 = x;
    g_font_queue[v11].y0 = y;
    g_font_queue[v11].horizontal_align = horizontal_align;
    g_font_queue[v11].anchor_x = anchor_x;
    v12 = g_font_text_cursor;
    g_font_queue[v11].text = g_font_text_cursor;
    g_font_queue[v11].color = *color;
    g_font_queue[v11].text_wave_amplitude = text_wave_amplitude;
    g_font_queue[v11].text_wave_enabled = text_wave_enabled;
    v13 = text;
    if ( *text )
    {
      while ( v12 - g_font_text_buffer <= 2046 )
      {
        *v12 = *v13;
        v12 = g_font_text_cursor + 1;
        ++v13;
        ++g_font_text_cursor;
        if ( !*v13 )
          goto LABEL_6;
      }
      *v12 = 0;
      ++g_font_text_cursor;
    }
    else
    {
LABEL_6:
      *v12 = 0;
      ++g_font_text_cursor;
      ++g_font_queue_count;
    }
  }
}
