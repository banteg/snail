/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_main_loop_display_state @ 0x406d70 */
/* selector: initialize_main_loop_display_state */

// Resets the display-mode/view-sample state, window deactivation latches, and object texture transform matrix, then tail-calls the adjacent main-loop timing initializer before startup enters the active frame loop.
void __cdecl initialize_main_loop_display_state()
{
  clear_display_mode_state(&g_display_mode_state);
  g_window_deactivated = 0;
  g_pending_window_deactivate = 0;
  set_matrix_identity(&g_object_texture_transform_matrix);
  initialize_main_loop_timing_state();
}
