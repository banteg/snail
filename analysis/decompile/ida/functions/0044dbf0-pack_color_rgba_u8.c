/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: pack_color_rgba_u8 @ 0x44dbf0 */
/* selector: pack_color_rgba_u8 */

// Converts one four-float RGBA tuple in `[0,1]` into one packed BGRA8 color record for sprite and mesh draw paths.
ColorBGRA8 *__thiscall pack_color_rgba_u8(ColorBGRA8 *out, Color4f *color)
{
  out->r = (__int64)(color->r * 255.0);
  out->g = (__int64)(color->g * 255.0);
  out->b = (__int64)(color->b * 255.0);
  out->a = (__int64)(color->a * 255.0);
  return out;
}

