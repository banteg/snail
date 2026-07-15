/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_help_screen @ 0x4168c0 */
/* selector: destroy_help_screen */

// Void cRHelp::UnInit(): clears the Help-screen shell-font scene before control returns to the owning front-end state. Its sole Windows caller discards EAX, and the exact body tail-calls void KillBorders.
void __thiscall destroy_help_screen(Help *help)
{
  kill_all_borders(&g_game_base->border_manager);
}
