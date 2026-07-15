/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_axis_aligned_textured_quad_uv @ 0x44a9b0 */
/* selector: queue_axis_aligned_textured_quad_uv */

// Appends one axis-aligned textured quad with explicit UV bounds into the shared 2D render queue. Front-end widgets, progress bars, and the damage gauge all use this helper.
int32_t __cdecl queue_axis_aligned_textured_quad_uv(
        int32_t texture_id,
        float x,
        float y,
        float width,
        float height,
        uint32_t flags,
        tColour *color,
        float u0,
        float v0,
        float u1,
        float v1,
        int32_t blend_mode,
        float rotation)
{
  int32_t result; // eax
  int32_t v14; // ecx
  __int16 v15; // fps
  bool v16; // c0
  char v17; // c2
  bool v18; // c3
  __int16 v19; // fps
  bool v20; // c0
  char v21; // c2
  bool v22; // c3
  tColour *p_color; // edx
  float a; // esi

  LOBYTE(result) = g_render_queue_active;
  if ( g_render_queue_active )
  {
    v14 = g_font_queue_count;
    if ( g_font_queue_count == 1024 )
    {
      return report_errorf(aFontPrintBuffe);
    }
    else
    {
      v16 = width < 0.0;
      v17 = 0;
      v18 = width == 0.0;
      LOWORD(result) = v15;
      if ( width != 0.0 )
      {
        v20 = height < 0.0;
        v21 = 0;
        v22 = height == 0.0;
        LOWORD(result) = v19;
        if ( height != 0.0 )
        {
          result = 132 * g_font_queue_count;
          g_font_queue[result / 0x84u].flags = flags | 2;
          g_font_queue[result / 0x84u].texture_id = texture_id;
          p_color = &g_font_queue[v14].color;
          p_color->r = color->r;
          p_color->g = color->g;
          p_color->b = color->b;
          a = color->a;
          g_font_queue_count = v14 + 1;
          p_color->a = a;
          g_font_queue[result / 0x84u].x0 = x;
          g_font_queue[result / 0x84u].y0 = y;
          g_font_queue[result / 0x84u].width = width;
          g_font_queue[result / 0x84u].height = height;
          g_font_queue[result / 0x84u].u0 = u0;
          g_font_queue[result / 0x84u].v0 = v0;
          g_font_queue[result / 0x84u].u1 = u1;
          g_font_queue[result / 0x84u].v1 = v1;
          g_font_queue[result / 0x84u].blend_mode = blend_mode;
          g_font_queue[result / 0x84u].rotation = rotation;
        }
      }
    }
  }
  return result;
}
