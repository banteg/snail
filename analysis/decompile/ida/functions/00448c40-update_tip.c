/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tip @ 0x448c40 */
/* selector: update_tip */

// Exact `cRTip::AI()` member: runs one Tip, handling hide or show state, button-click consumption, timed expiry, and the final teardown or frontend-state restore path.
void __thiscall update_tip(Tip *tip)
{
  FrontendWidget *widget_main; // ecx
  FrontendWidget *widget_ok; // ecx
  FrontendWidgetFlag widget_flags; // eax
  double v5; // st7

  widget_main = tip->widget_main;
  if ( g_game_base->subgame.subgame_pause_gate )
  {
    hide_border_init(widget_main);
  }
  else
  {
    unhide_border_init(widget_main);
    widget_ok = tip->widget_ok;
    if ( widget_ok && (widget_flags = widget_ok->widget_flags, (widget_flags & 0x20) != 0)
      || (widget_ok = tip->widget_disable) != nullptr
      && (widget_flags = widget_ok->widget_flags, (widget_flags & 0x20) != 0) )
    {
      LOBYTE(widget_flags) = widget_flags & 0xDF;
      widget_ok->widget_flags = widget_flags;
      g_game_base->players[0].frontend_state = tip->previous_outer_owner;
      kill_tip_widgets(tip);
      unhide_all_borders(&g_game_base->border_manager);
      tip->active = 0;
    }
    else if ( (tip->definition->flags & 2) != 0 )
    {
      v5 = tip->dismiss_step + tip->dismiss_progress;
      tip->dismiss_progress = v5;
      if ( v5 > 1.0 )
      {
        kill_tip_widgets(tip);
        tip->active = 0;
      }
    }
  }
}
