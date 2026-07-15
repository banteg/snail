/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: highlight_border @ 0x402800 */
/* selector: highlight_border */

// Stable Windows harness identity for the authored void cRBorder::Highlight() member. It raises the hover blend target and selects hot padding; the copied float bits left in EAX are incidental.
void __thiscall highlight_border(FrontendWidget *widget)
{
  float hot_padding; // eax

  hot_padding = widget->hot_padding;
  widget->hover_blend_target = 1.0;
  widget->target_padding = hot_padding;
}
