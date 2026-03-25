/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: handle_game_window_deactivate @ 0x407440 */
/* selector: handle_game_window_deactivate */

// Runtime deactivation helper for the main window. When the game is active in fullscreen mode, it marks the window inactive, minimizes it, and clears the pending quit flag before returning.
char handle_game_window_deactivate()
{
  char result; // al

  result = unk_4B7654;
  if ( !unk_4B7654 )
  {
    if ( byte_4DF920[0] )
    {
      pause_audio_backend_if_running(unk_753C58);
      unk_4B7654 = 1;
      ((void (__stdcall *)(_DWORD, int))ShowWindow)(MEMORY[0x4DFAF0], 6);
    }
    result = dword_4DF860;
    if ( dword_4DF860 )
      dword_4DF860 = 0;
  }
  return result;
}

