/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_border_init @ 0x4010e0 */
/* selector: hide_border_init */

// Stable Windows harness identity for the authored void cRBorder::HideInit() member. It starts the 0x1000 hide transition once, clears hide_blend, and tail-calls the owned cRToolTip reset.
void __thiscall hide_border_init(FrontendWidget *widget)
{
  FrontendWidgetFlag widget_flags; // eax

  widget_flags = widget->widget_flags;
  if ( (BYTE1(widget_flags) & 0x10) == 0 )
  {
    BYTE1(widget_flags) |= 0x10u;
    widget->hide_blend = 0.0;
    widget->widget_flags = widget_flags;
    reset_tooltip(&widget->tooltip);
  }
}
