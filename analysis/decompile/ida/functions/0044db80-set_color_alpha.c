/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_alpha @ 0x44db80 */
/* selector: set_color_alpha */

// Stores one float alpha value into the destination color slot's alpha lane and returns that same alpha value.
float __thiscall set_color_alpha(Color4f *color, float alpha)
{
  float result; // st7

  color->a = alpha;
  return result;
}

