/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: pack_color_rgba_u8 @ 0x44dbf0 */
/* selector: pack_color_rgba_u8 */

// Converts one four-float RGBA tuple in `[0,1]` into packed 8-bit color channels for the sprite draw path.
_BYTE *__thiscall sub_44DBF0(_BYTE *this, float *a2)
{
  *(this + 2) = (__int64)(*a2 * 255.0);
  *(this + 1) = (__int64)(a2[1] * 255.0);
  *this = (__int64)(a2[2] * 255.0);
  *(this + 3) = (__int64)(a2[3] * 255.0);
  return this;
}

