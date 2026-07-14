/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_rgb @ 0x44dbd0 */
/* selector: set_color_rgb */

// Exact void `tColour::Set(float, float, float)` role: stores RGB at `+0/+4/+8` while preserving the existing alpha lane. Android retains the same overload.
void __thiscall set_color_rgb(tColour *color, float r, float g, float b)
{
  color->r = r;
  color->g = g;
  color->b = b;
}
