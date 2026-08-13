/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_tip_widgets @ 0x4489e0 */
/* selector: kill_tip_widgets */

// Exact Windows `cRTip::UnInit()`: kills the live main border and optional OK or Disable buttons, then clears Tip::active. Android preserves the same method, owner offsets, three BorderManager::Kill calls, and final active-state clear.
void __thiscall kill_tip_widgets(cRTip *tip)
{
  kill_border(&g_game_base->border_manager, tip->widget_main);
  if ( tip->widget_ok != nullptr )
    kill_border(&g_game_base->border_manager, tip->widget_ok);
  if ( tip->widget_disable != nullptr )
    kill_border(&g_game_base->border_manager, tip->widget_disable);
  tip->active = 0;
}
