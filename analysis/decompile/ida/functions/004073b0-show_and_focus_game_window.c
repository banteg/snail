/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: show_and_focus_game_window @ 0x4073b0 */
/* selector: show_and_focus_game_window */

// Startup-only helper that shows the game window, brings it to the foreground, sets focus and active window state, refreshes the frame timestamp, and clears the mouse button latch bytes before the main loop begins.
int show_and_focus_game_window()
{
  int result; // eax

  flt_4DFAFC[1] = (double)(unsigned int)((int (*)(void))timeGetTime)() * 0.001;
  ((void (__stdcall *)(_DWORD, int))ShowWindow)(MEMORY[0x4DFAF0], 1);
  ((void (__stdcall *)(_DWORD))SetForegroundWindow)(MEMORY[0x4DFAF0]);
  ((void (__stdcall *)(_DWORD))SetFocus)(MEMORY[0x4DFAF0]);
  result = ((int (__stdcall *)(_DWORD))SetActiveWindow)(MEMORY[0x4DFAF0]);
  unk_4B7764[0] = 0;
  unk_4B7234[0] = 0;
  unk_4B7230[0] = 0;
  LOWORD(flt_4B763C[1]) = 0;
  unk_4B7765 = 0;
  unk_4B7235 = 0;
  unk_4B7231 = 0;
  return result;
}

