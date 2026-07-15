/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_axis_aligned_textured_quad @ 0x44a8b0 */
/* selector: queue_axis_aligned_textured_quad */

// Appends one axis-aligned textured quad with default `[0,1]` UVs into the shared 2D render queue, using the supplied texture, authored rectangle, tint, and render flags.
int32_t __cdecl queue_axis_aligned_textured_quad(
        int32_t texture_id,
        float x,
        float y,
        float width,
        float height,
        uint32_t flags,
        tColour *color,
        int32_t blend_mode)
{
  int32_t result; // eax
  int32_t v9; // ecx
  __int16 v10; // fps
  bool v11; // c0
  char v12; // c2
  bool v13; // c3
  __int16 v14; // fps
  bool v15; // c0
  char v16; // c2
  bool v17; // c3
  tColour *p_color; // esi
  float a; // edi

  LOBYTE(result) = g_render_queue_active;
  if ( g_render_queue_active )
  {
    v9 = g_font_queue_count;
    if ( g_font_queue_count == 1024 )
    {
      return report_errorf(aFontPrintBuffe);
    }
    else
    {
      v11 = width < 0.0;
      v12 = 0;
      v13 = width == 0.0;
      LOWORD(result) = v10;
      if ( width != 0.0 )
      {
        v15 = height < 0.0;
        v16 = 0;
        v17 = height == 0.0;
        LOWORD(result) = v14;
        if ( height != 0.0 )
        {
          result = 132 * g_font_queue_count;
          g_font_queue[result / 0x84u].flags = flags | 2;
          g_font_queue[result / 0x84u].texture_id = texture_id;
          p_color = &g_font_queue[v9].color;
          p_color->r = color->r;
          p_color->g = color->g;
          p_color->b = color->b;
          a = color->a;
          g_font_queue_count = v9 + 1;
          p_color->a = a;
          g_font_queue[result / 0x84u].x0 = x;
          g_font_queue[result / 0x84u].y0 = y;
          g_font_queue[result / 0x84u].width = width;
          g_font_queue[result / 0x84u].height = height;
          g_font_queue[result / 0x84u].u0 = 0.0;
          g_font_queue[result / 0x84u].v0 = 0.0;
          g_font_queue[result / 0x84u].u1 = 1.0;
          g_font_queue[result / 0x84u].v1 = 1.0;
          g_font_queue[result / 0x84u].blend_mode = blend_mode;
          g_font_queue[result / 0x84u].rotation = 0.0;
        }
      }
    }
  }
  return result;
}
