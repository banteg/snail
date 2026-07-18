/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_tip_widgets @ 0x4489e0 */
/* selector: kill_tip_widgets */

// Tip-owned helper that kills the live border widgets for one cRTip, including the main body and any optional OK or Disable buttons, then clears Tip::active.
void __thiscall kill_tip_widgets(Tip *tip)
{
  kill_border(&tip->widget_main->list_kind);
  if ( tip->widget_ok )
    kill_border(&tip->widget_ok->list_kind);
  if ( tip->widget_disable )
    kill_border(&tip->widget_disable->list_kind);
  tip->active = 0;
}
