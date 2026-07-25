/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: show_and_focus_game_window @ 0x4073b0 */
/* selector: show_and_focus_game_window */

// Startup-only helper that shows the game window, brings it to the foreground, sets focus and active window state, refreshes the frame timestamp, and clears the mouse button latch bytes before the main loop begins.
int show_and_focus_game_window()
{
  int result; // eax

  g_previous_frame_timestamp_seconds = (double)(unsigned int)((int (*)(void))timeGetTime)() * 0.001;
  ((void (__stdcall *)(int, int))ShowWindow)(g_main_window, 1);
  ((void (__stdcall *)(int))SetForegroundWindow)(g_main_window);
  ((void (__stdcall *)(int))SetFocus)(g_main_window);
  result = ((int (__stdcall *)(int))SetActiveWindow)(g_main_window);
  g_left_mouse_button_latch[0] = 0;
  g_left_mouse_button_state[0] = 0;
  g_right_mouse_button_latch[0] = 0;
  g_right_mouse_button_state[0] = 0;
  unk_4B7765 = 0;
  unk_4B7235 = 0;
  unk_4B7231 = 0;
  g_right_mouse_button_state[1] = 0;
  return result;
}
