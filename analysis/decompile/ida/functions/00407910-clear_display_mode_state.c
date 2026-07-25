/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clear_display_mode_state @ 0x407910 */
/* selector: clear_display_mode_state */

// Clears the queued display-mode view-sample count and current display-mode pointer.
void __thiscall clear_display_mode_state(DisplayModeState *state)
{
  state->current_mode = nullptr;
  state->queued_view_sample_count = 0;
}
