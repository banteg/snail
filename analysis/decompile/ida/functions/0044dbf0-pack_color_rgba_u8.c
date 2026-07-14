/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: pack_color_rgba_u8 @ 0x44dbf0 */
/* selector: pack_color_rgba_u8 */

// Exact Windows implementation of the authored `tColourSmall::operator=(tColour const&)` role: converts one four-float RGBA tuple in `[0,1]` into the four-byte BGRA record used by sprite and mesh draw paths. Android independently preserves the same `+2/+1/+0/+3` stores.
tColourSmall *__thiscall pack_color_rgba_u8(tColourSmall *out, tColour *color)
{
  out->r = (__int64)(color->r * 255.0);
  out->g = (__int64)(color->g * 255.0);
  out->b = (__int64)(color->b * 255.0);
  out->a = (__int64)(color->a * 255.0);
  return out;
}

