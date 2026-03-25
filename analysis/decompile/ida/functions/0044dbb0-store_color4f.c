/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: store_color4f @ 0x44dbb0 */
/* selector: store_color4f */

// Stores one four-float tuple into the destination `Color4f` slot and returns the third component register value left live by the helper epilogue. Callers treat it as a write-only color helper.
float __thiscall store_color4f(Color4f *color, float r, float g, float b, float a)
{
  float result; // st7

  color->r = r;
  color->g = g;
  color->b = b;
  color->a = a;
  return result;
}

