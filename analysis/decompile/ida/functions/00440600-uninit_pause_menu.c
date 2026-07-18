/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_pause_menu @ 0x440600 */
/* selector: uninit_pause_menu */

// Destroys the three widgets owned by the embedded cRSubPause and releases the gameplay mouse cursor. Cross-port iOS and Android symbols identify the side-effect-only method as cRSubPause::UnInit(); the Windows reconstruction is exact at 22/22 instructions.
void __thiscall uninit_pause_menu(SubPause *pause)
{
  kill_border(&pause->options_widget->list_kind);
  kill_border(&pause->end_game_widget->list_kind);
  kill_border(&pause->resume_widget->list_kind);
  release_mouse_cursor(&g_game_base->players[0].mouse_cursor);
}
