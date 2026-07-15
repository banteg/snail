/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhighlight_border @ 0x4027e0 */
/* selector: unhighlight_border */

// Stable Windows harness identity for the authored void cRBorder::UnHighlight() member. It clears the hover blend target and restores idle padding; the copied float bits left in EAX are incidental.
void __thiscall unhighlight_border(FrontendWidget *widget)
{
  float idle_padding; // eax

  idle_padding = widget->idle_padding;
  widget->hover_blend_target = 0.0;
  widget->target_padding = idle_padding;
}
