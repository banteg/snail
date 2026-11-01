/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_game_window_and_input_wrapper @ 0x4119c0 */
/* selector: initialize_game_window_and_input_wrapper */

// Small cdecl wrapper used by startup to forward the SnailMail window title to the window/input initializer body.
int __cdecl initialize_game_window_and_input_wrapper(char *window_name)
{
  return initialize_game_window_and_input(window_name);
}
