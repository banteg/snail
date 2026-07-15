/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_textured_quad_corners @ 0x44aac0 */
/* selector: queue_textured_quad_corners */

// Appends one arbitrary four-corner textured quad with explicit per-corner positions and UV bounds into the shared 2D render queue. The backdrop and galaxy-line renderers use this helper.
int32_t __cdecl queue_textured_quad_corners(
        int32_t texture_id,
        float x0,
        float y0,
        float x1,
        float y1,
        float x2,
        float y2,
        float x3,
        float y3,
        int32_t unused_28,
        int32_t unused_2c,
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
  int32_t v20; // ecx
  tColour *p_color; // esi
  float a; // edi

  LOBYTE(result) = g_render_queue_active;
  if ( g_render_queue_active )
  {
    v20 = g_font_queue_count;
    if ( g_font_queue_count == 1024 )
    {
      return report_errorf(aFontPrintBuffe);
    }
    else
    {
      result = 132 * g_font_queue_count;
      g_font_queue[result / 0x84u].flags = flags | 2;
      g_font_queue[result / 0x84u].texture_id = texture_id;
      p_color = &g_font_queue[v20].color;
      p_color->r = color->r;
      p_color->g = color->g;
      p_color->b = color->b;
      a = color->a;
      g_font_queue_count = v20 + 1;
      p_color->a = a;
      g_font_queue[result / 0x84u].x0 = x0;
      g_font_queue[result / 0x84u].y0 = y0;
      g_font_queue[result / 0x84u].x1 = x1;
      g_font_queue[result / 0x84u].y1 = y1;
      g_font_queue[result / 0x84u].x2 = x2;
      g_font_queue[result / 0x84u].y2 = y2;
      g_font_queue[result / 0x84u].x3 = x3;
      g_font_queue[result / 0x84u].y3 = y3;
      g_font_queue[result / 0x84u].width = 0.0;
      g_font_queue[result / 0x84u].height = 0.0;
      g_font_queue[result / 0x84u].u0 = u0;
      g_font_queue[result / 0x84u].v0 = v0;
      g_font_queue[result / 0x84u].u1 = u1;
      g_font_queue[result / 0x84u].v1 = v1;
      g_font_queue[result / 0x84u].blend_mode = blend_mode;
      g_font_queue[result / 0x84u].rotation = rotation;
    }
  }
  return result;
}
