/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_border_manager @ 0x403fc0 */
/* selector: update_border_manager */

// Exact authored `cRBorderManager::AI()` member: advances the delayed-widget transition, clamps it after one normalized interval, waits for root fade state 4 when required, applies the queued flags to the borrowed cRBorder, and clears the active lane. Android and iOS confirm the owner and field order without transferring platform offsets.
void __thiscall update_border_manager(BorderManager *manager)
{
  double v1; // st7
  FrontendWidget *delayed_widget; // eax
  FrontendWidgetFlag widget_flags; // edx

  if ( manager->delayed_widget_active != 0 )
  {
    v1 = manager->delayed_widget_progress_step + manager->delayed_widget_progress;
    manager->delayed_widget_progress = v1;
    if ( v1 > 1.0 )
    {
      delayed_widget = manager->delayed_widget;
      manager->delayed_widget_progress = 1.0;
      widget_flags = delayed_widget->widget_flags;
      if ( (widget_flags & 0x40000000) == 0 || g_game_base->fade.state == 4 )
      {
        delayed_widget->widget_flags = widget_flags | manager->delayed_widget_flags;
        manager->delayed_widget_active = 0;
      }
    }
  }
}
