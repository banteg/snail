/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_help_screen @ 0x4168d0 */
/* selector: update_help_screen */

// Handles the Help-screen Back action, tears down the shell-font scene, and returns control to the New Game front-end flow via state `2`. Cross-port Android and iOS symbols match this helper to `cRHelp::AI()`.
void __thiscall update_help_screen(cRHelp *help)
{
  FrontendWidgetFlag widget_flags; // eax

  widget_flags = help->back_button->widget_flags;
  if ( (widget_flags & 0x20) != 0 )
  {
    LOBYTE(widget_flags) = widget_flags & 0xDF;
    help->back_button->widget_flags = widget_flags;
    destroy_help_screen(help);
    g_game_base->players[0].frontend_state = 2;
    g_game_base->players[0].redispatch_requested = 1;
  }
}
