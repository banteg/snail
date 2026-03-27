/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_tooltip @ 0x403be0 */
/* selector: reset_tooltip */

int32_t __fastcall reset_tooltip(FrontendWidgetTooltip *tooltip)
{
  int32_t result; // eax

  result = tooltip->state - 2;
  if ( tooltip->state != 2 )
  {
    result = tooltip->state - 3;
    if ( tooltip->state != 3 )
      return result;
    kill_border(tooltip->tooltip_widget->_pad_00);
    tooltip->tooltip_widget = nullptr;
  }
  tooltip->state = 1;
  return result;
}

