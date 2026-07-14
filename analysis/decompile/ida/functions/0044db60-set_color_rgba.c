/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_rgba @ 0x44db60 */
/* selector: set_color_rgba */

// Exact Windows `tColour::Set(float, float, float, float)` role: stores the four RGBA floats at `+0/+4/+8/+12` and returns the same destination pointer. Android preserves the class, method name, field order, and four stores.
tColour *__thiscall set_color_rgba(tColour *color, float r, float g, float b, float a)
{
  color->r = r;
  color->g = g;
  color->b = b;
  color->a = a;
  return color;
}

