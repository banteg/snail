/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_frontend_widget_flag_after_delay @ 0x403f60 */
/* selector: queue_frontend_widget_flag_after_delay */

// Arms the shared border-manager delay lane for one front-end widget: stores the destination widget pointer and flag mask, starts the fixed `0.1` step timer, and optionally begins the global front-end fade when the widget requests it.
char __thiscall queue_frontend_widget_flag_after_delay(
        BorderManager *manager,
        FrontendWidget *widget,
        int32_t queued_flags)
{
  char result; // al

  result = manager->delayed_widget_active;
  if ( !result )
  {
    if ( (widget->widget_flags & 0x40000000) != 0 )
      result = begin_frontend_fade_out(&g_game_base->fade.state, 0);
    manager->delayed_widget = widget;
    manager->delayed_widget_active = 1;
    manager->delayed_widget_progress = 0.0;
    manager->delayed_widget_progress_step = 0.083333336;
    manager->delayed_widget_flags = queued_flags;
  }
  return result;
}
