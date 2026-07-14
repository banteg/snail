/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_black @ 0x44dc60 */
/* selector: set_color_black */

// Exact void `tColour::Black()` role: tail-calls the recovered Grey helper with `0.0f`, producing opaque black. Android retains the same method.
void __thiscall set_color_black(tColour *color)
{
  set_color_grayscale(color, 0.0);
}

