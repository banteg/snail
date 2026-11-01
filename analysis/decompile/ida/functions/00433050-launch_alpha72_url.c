/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: launch_alpha72_url @ 0x433050 */
/* selector: launch_alpha72_url */

// Exact void completion-screen outbound-link helper that accepts the Alpha72.url path, minimizes the game window, and raises the pending-deactivate latch; the stripped Windows body does not read the path and its sole caller discards EAX.
void __cdecl launch_alpha72_url(char *url)
{
  minimize_game_window();
  g_pending_window_deactivate = 1;
}
