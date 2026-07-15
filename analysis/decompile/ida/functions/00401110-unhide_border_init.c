/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_border_init @ 0x401110 */
/* selector: unhide_border_init */

// Stable Windows harness identity for the authored void cRBorder::UnHideInit() member. It restores hide_blend to one and clears the 0x1000 hide-transition flag.
void __thiscall unhide_border_init(FrontendWidget *widget)
{
  FrontendWidgetFlag widget_flags; // eax

  widget_flags = widget->widget_flags;
  widget->hide_blend = 1.0;
  BYTE1(widget_flags) &= ~0x10u;
  widget->widget_flags = widget_flags;
}
