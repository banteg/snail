/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhighlight_border @ 0x4027e0 */
/* selector: unhighlight_border */

// Clears the active highlight state on one frontend border/widget and restores its non-highlighted visual bits.
int32_t __thiscall unhighlight_border(FrontendWidget *widget)
{
  int32_t result; // eax

  result = LODWORD(widget->idle_padding);
  widget->hover_blend_target = 0.0;
  LODWORD(widget->target_padding) = result;
  return result;
}

