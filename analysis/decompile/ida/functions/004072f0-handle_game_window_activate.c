/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: handle_game_window_activate @ 0x4072f0 */
/* selector: handle_game_window_activate */

// Runtime reactivation helper for the main window. It clears the inactive flag, reapplies fullscreen mode when configured, refreshes the frame timestamp, shows and focuses the game window, and clears the mouse button latch bytes after WM_ACTIVATE enters the active state.
int __usercall handle_game_window_activate@<eax>(int a1@<edi>)
{
  int result; // eax

  sub_449C00();
  sub_449C00();
  resume_audio_backend_if_paused(unk_753C58);
  unk_4B7654 = 0;
  if ( byte_4DF920[0] )
    set_fullscreen_mode(a1, 1);
  flt_4DFAFC[1] = (double)(unsigned int)((int (*)(void))timeGetTime)() * 0.001;
  ((void (__stdcall *)(_DWORD, int))ShowWindow)(MEMORY[0x4DFAF0], 1);
  ((void (__stdcall *)(_DWORD))SetForegroundWindow)(MEMORY[0x4DFAF0]);
  result = ((int (__stdcall *)(_DWORD))SetFocus)(MEMORY[0x4DFAF0]);
  unk_4B7764[0] = 0;
  unk_4B7234[0] = 0;
  unk_4B7230[0] = 0;
  LOWORD(flt_4B763C[1]) = 0;
  unk_4B7765 = 0;
  unk_4B7235 = 0;
  unk_4B7231 = 0;
  return result;
}

