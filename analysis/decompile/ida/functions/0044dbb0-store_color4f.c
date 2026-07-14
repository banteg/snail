/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: store_color4f @ 0x44dbb0 */
/* selector: store_color4f */

// Stable Windows harness identity for the authored `tColour::tColour(float, float, float, float)` constructor role. It stores RGBA at `+0/+4/+8/+12`; all callers treat it as write-only, so the final component register left live by the epilogue is not a return value.
void __thiscall store_color4f(tColour *color, float r, float g, float b, float a)
{
  color->r = r;
  color->g = g;
  color->b = b;
  color->a = a;
}

