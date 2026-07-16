/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: handle_game_window_deactivate @ 0x407440 */
/* selector: handle_game_window_deactivate */

// Runtime deactivation helper for the main window. When the game is active in fullscreen mode, it marks the window inactive, minimizes it, and clears the pending quit flag before returning.
char handle_game_window_deactivate()
{
  char result; // al

  result = g_window_deactivated;
  if ( !g_window_deactivated )
  {
    if ( g_runtime_config.fullscreen_enabled )
    {
      pause_audio_backend_if_running((AudioBackend *)g_audio_backend);
      g_window_deactivated = 1;
      ((void (__stdcall *)(int, int))ShowWindow)(g_main_window, 6);
    }
    result = g_pending_window_deactivate;
    if ( g_pending_window_deactivate )
      g_pending_window_deactivate = 0;
  }
  return result;
}
