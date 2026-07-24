/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_frontend_widget_flag_after_delay @ 0x403f60 */
/* selector: queue_frontend_widget_flag_after_delay */

// Exact void BorderManager delayed-action helper: stores the destination widget and flag mask, starts the fixed `1/12` step timer, and optionally calls the root-owned cRFade::Start-compatible lane. All three Windows callers discard EAX; removing the synthetic result dependency leaves the natural void source exact at 22/22 instructions.
void __thiscall queue_frontend_widget_flag_after_delay(
        BorderManager *manager,
        FrontendWidget *widget,
        int32_t queued_flags)
{
  if ( !manager->delayed_widget_active )
  {
    if ( (widget->widget_flags & 0x40000000) != 0 )
      begin_frontend_fade_out(&g_game_base->fade, nullptr);
    manager->delayed_widget = widget;
    manager->delayed_widget_active = 1;
    manager->delayed_widget_progress = 0.0;
    manager->delayed_widget_progress_step = 0.083333336;
    manager->delayed_widget_flags = queued_flags;
  }
}
