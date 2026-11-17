/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_main_loop_timing_state @ 0x406da0 */
/* selector: initialize_main_loop_timing_state */

// Seeds the mean update-step count, current-frame update-step count, and rendered-frame count to 1.0 before the active frame loop begins.
void initialize_main_loop_timing_state()
{
  g_mean_update_steps_per_frame = 1.0;
  g_current_frame_update_steps = 1.0;
  g_main_loop_frame_count = 1.0;
}
