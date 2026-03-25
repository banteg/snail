/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_grayscale @ 0x44db90 */
/* selector: set_color_grayscale */

// Stores one uniform grayscale RGB value into the destination color slot, forces alpha to `1.0`, and returns the grayscale input.
float __thiscall set_color_grayscale(Color4f *color, float intensity)
{
  float result; // st7

  color->a = 1.0;
  color->r = intensity;
  color->g = intensity;
  color->b = intensity;
  return result;
}

