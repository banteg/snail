/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_grayscale @ 0x44db90 */
/* selector: set_color_grayscale */

// Exact void `tColour::Grey(float)` role: stores one uniform RGB value and forces alpha to `1.0`. Its callers treat it as a write-only method; the value left in EAX is incidental.
void __thiscall set_color_grayscale(tColour *color, float intensity)
{
  color->a = 1.0;
  color->r = intensity;
  color->g = intensity;
  color->b = intensity;
}

