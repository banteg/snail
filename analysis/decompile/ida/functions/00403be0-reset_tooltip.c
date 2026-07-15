/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_tooltip @ 0x403be0 */
/* selector: reset_tooltip */

// Exact authored void cRToolTip::ReSet() member: resets the embedded controller to its idle state and releases any live BorderManager-owned tooltip widget handle.
void __thiscall reset_tooltip(FrontendWidgetTooltip *tooltip)
{
  if ( tooltip->state != 2 )
  {
    if ( tooltip->state != 3 )
      return;
    kill_border(&tooltip->tooltip_widget->list_kind);
    tooltip->tooltip_widget = nullptr;
  }
  tooltip->state = 1;
}
