/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: highlight_border @ 0x402800 */
/* selector: highlight_border */

// Sets the active highlight state on one frontend border/widget so hover/selection visuals render in the highlighted style.
int32_t __thiscall highlight_border(FrontendWidget *widget)
{
  int32_t result; // eax

  result = LODWORD(widget->hot_padding);
  widget->hover_blend_target = 1.0;
  LODWORD(widget->target_padding) = result;
  return result;
}

