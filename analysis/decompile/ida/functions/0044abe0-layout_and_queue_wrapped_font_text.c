/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: layout_and_queue_wrapped_font_text @ 0x44abe0 */
/* selector: layout_and_queue_wrapped_font_text */

// Authored void `FontType(...)`: splits one text string into wrapped line runs, queues each run through `queue_font_text_instance`, and writes the aligned authored-space origin and measured bounds through four borrowed output pointers.
void __cdecl layout_and_queue_wrapped_font_text(
        char *text,
        int32_t font_id,
        float text_scale,
        float x,
        float y,
        float *out_x,
        float *out_y,
        float *out_width,
        float *out_height,
        float text_wave_amplitude,
        uint8_t shadow_enabled,
        int32_t horizontal_align,
        float anchor_x,
        uint32_t flags,
        tColour *color,
        uint8_t measure_only,
        uint8_t pulse_alpha)
{
  char *v17; // eax
  char v18; // bl
  double v19; // st7
  float v20; // [esp+0h] [ebp-430h]
  float v21; // [esp+14h] [ebp-41Ch]
  float v22; // [esp+18h] [ebp-418h]
  tColour self; // [esp+20h] [ebp-410h] BYREF
  char v25[1024]; // [esp+30h] [ebp-400h] BYREF

  noop_this_constructor(&self);
  self = *color;
  v22 = x;
  v21 = y;
  v17 = v25;
  do
  {
    v18 = *text;
    if ( *text == 62 || v18 == 0 )
    {
      *v17 = 0;
      if ( v17 != v25 )
      {
        v19 = measure_font_text_width(v25, font_id, text_scale) + x;
        if ( v19 > v22 )
          v22 = v19;
        if ( measure_only == 0 )
        {
          if ( pulse_alpha != 0 )
          {
            v20 = v21 * 0.0065449849;
            self.a = sine(v20);
          }
          queue_font_text_instance(
            v25,
            font_id,
            text_scale,
            x,
            v21,
            horizontal_align,
            anchor_x,
            flags,
            &self,
            text_wave_amplitude,
            shadow_enabled);
        }
      }
      v17 = v25;
      v21 = g_font_sheets[font_id].height_scale
          * g_font_sheets[font_id].spacing_scale
          * g_font_sheets[font_id].line_marker_y
          * text_scale
          + v21;
    }
    else
    {
      *v17++ = v18;
    }
    ++text;
  }
  while ( v18 != 0 );
  *out_x = x;
  *out_y = y;
  *out_width = v22 - x;
  *out_height = v21 - y;
  switch ( horizontal_align )
  {
    case 1:
      *out_x = anchor_x + 320.0;
      break;
    case 3:
      *out_x = anchor_x + 320.0 - *out_width;
      break;
    case 2:
      *out_x = anchor_x + 320.0 - *out_width * 0.5;
      break;
    default:
      break;
  }
}
