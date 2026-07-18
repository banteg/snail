/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_thanks_screen @ 0x4340c0 */
/* selector: uninit_thanks_screen */

void __thiscall uninit_thanks_screen(ThanksScreen *thanks_screen)
{
  kill_border(&thanks_screen->message_widget->list_kind);
  g_game_base->players[0].frontend_state = 14;
}
