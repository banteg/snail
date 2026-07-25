/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_display_mode_view_state @ 0x412940 */
/* selector: update_display_mode_view_state */

// Updates the shared display-mode view-sample state against the authored view dimensions before the frame render pass.
uint8_t __thiscall update_display_mode_view_state(DisplayModeState *state)
{
  int32_t probe_count; // edi
  int32_t v4; // eax
  float y; // [esp+4h] [ebp-10h] BYREF
  float height; // [esp+8h] [ebp-Ch] BYREF
  float width; // [esp+Ch] [ebp-8h] BYREF
  float x; // [esp+10h] [ebp-4h] BYREF

  if ( !state->current_mode )
    return 0;
  get_authored_view_width();
  get_authored_view_height();
  probe_count = state->probe_count;
  do
  {
    if ( !read_next_display_mode_view_sample(state, &x, &y, &width, &height) )
      break;
    v4 = state->probe_count;
    y = (float)(int)(state->current_mode->height - (unsigned int)(__int64)(y + height));
  }
  while ( v4 == probe_count );
  return 1;
}
