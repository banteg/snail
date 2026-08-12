/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_thanks_screen @ 0x4340c0 */
/* selector: uninit_thanks_screen */

// Authored `cRSplash::UnInit()` teardown: releases the post-run message widget and returns the front-end state machine to state 14. Android preserves the exact owner and lifecycle; iOS inlines the same teardown into `cRSplash::AI()`.
void __thiscall uninit_thanks_screen(cRSplash *splash)
{
  kill_border(&g_game_base->border_manager, splash->message_widget);
  g_game_base->players[0].frontend_state = 14;
}
