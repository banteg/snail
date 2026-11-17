/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: minimize_game_window @ 0x407490 */
/* selector: minimize_game_window */

// Posts WM_SIZE/SIZE_MINIMIZED to the process-owned main window after emitting the stripped software-minimize diagnostic.
BOOL minimize_game_window()
{
  debug_report_stub(aSoftwareMinimi);
  return PostMessageA(g_main_window, 5u, 1u, 0);
}
