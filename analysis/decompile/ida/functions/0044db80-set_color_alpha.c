/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_color_alpha @ 0x44db80 */
/* selector: set_color_alpha */

// Exact void `tColour::Alpha(float)` role: stores one float at the alpha lane `+0x0c`. Both Windows callers discard EAX, and the honest float/void source remains exact at 3/3 instructions without a synthetic integer return.
void __thiscall set_color_alpha(tColour *color, float alpha)
{
  color->a = alpha;
}

