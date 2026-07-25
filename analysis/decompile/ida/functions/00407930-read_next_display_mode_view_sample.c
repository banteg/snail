/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_next_display_mode_view_sample @ 0x407930 */
/* selector: read_next_display_mode_view_sample */

// Returns the next display-mode view sample or the current mode dimensions during the startup probe warm-up.
uint8_t __thiscall read_next_display_mode_view_sample(
        DisplayModeState *state,
        float *x,
        float *y,
        float *width,
        float *height)
{
  int32_t probe_count; // eax
  int32_t v7; // eax

  if ( state->probe_count >= 2 )
  {
    if ( state->queued_view_sample_count )
    {
      v7 = state->queued_view_sample_count - 1;
      state->queued_view_sample_count = v7;
      *x = state->view_samples[v7].x;
      *y = state->view_samples[state->queued_view_sample_count].y;
      *width = state->view_samples[state->queued_view_sample_count].width;
      *height = state->view_samples[state->queued_view_sample_count].height;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    *x = 0.0;
    *y = 0.0;
    *width = (float)state->current_mode->width;
    *height = (float)state->current_mode->height;
    probe_count = state->probe_count;
    state->queued_view_sample_count = 0;
    state->probe_count = probe_count + 1;
    return 1;
  }
}
