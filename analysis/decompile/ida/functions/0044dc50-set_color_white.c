/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_white @ 0x44dc50 */
/* selector: set_color_white */

// Exact void `tColour::White()` role: tail-calls the recovered Grey helper with `1.0f`, producing opaque white. Android retains the same method.
void __thiscall set_color_white(tColour *color)
{
  set_color_grayscale(color, 1.0);
}

