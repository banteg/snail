/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: handle_game_window_activate @ 0x4072f0 */
/* selector: handle_game_window_activate */

// Runtime reactivation helper for the main window. It clears the inactive flag, reapplies fullscreen mode when configured, refreshes the frame timestamp, shows and focuses the game window, and clears the mouse button latch bytes after WM_ACTIVATE enters the active state.
int handle_game_window_activate()
{
  int result; // eax

  debug_report_stub();
  debug_report_stub();
  resume_audio_backend_if_paused((AudioBackend *)g_audio_backend);
  g_window_deactivated = 0;
  if ( g_runtime_config.fullscreen_enabled )
    set_fullscreen_mode(1);
  g_previous_frame_timestamp_seconds = (double)(unsigned int)((int (*)(void))timeGetTime)() * 0.001;
  ((void (__stdcall *)(int, int))ShowWindow)(g_main_window, 1);
  ((void (__stdcall *)(int))SetForegroundWindow)(g_main_window);
  result = ((int (__stdcall *)(int))SetFocus)(g_main_window);
  g_left_mouse_button_latch[0] = 0;
  g_left_mouse_button_state[0] = 0;
  g_right_mouse_button_latch[0] = 0;
  LOWORD(g_current_frame_update_steps[1]) = 0;
  unk_4B7765 = 0;
  unk_4B7235 = 0;
  unk_4B7231 = 0;
  return result;
}
