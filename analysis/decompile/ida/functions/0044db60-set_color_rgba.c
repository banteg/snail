/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_rgba @ 0x44db60 */
/* selector: set_color_rgba */

// Stores one four-float RGBA color tuple into the destination color/vector slot and returns the same destination pointer.
Color4f *__thiscall set_color_rgba(Color4f *color, float r, float g, float b, float a)
{
  color->r = r;
  color->g = g;
  color->b = b;
  color->a = a;
  return color;
}

