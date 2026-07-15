/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_backdrop @ 0x4112f0 */
/* selector: update_backdrop */

// Advances the shared backdrop renderer, updates its distortion grid, and dispatches the split or warped draw path. Cross-port Android and iOS symbols match this helper to `cRBackdrop::AI()`.
int32_t __thiscall update_backdrop(Backdrop *backdrop)
{
  BackdropDistortCell *v2; // ebx
  float *p_phase; // esi
  int v4; // edi
  double v5; // st7
  int32_t result; // eax
  float v7; // [esp+4h] [ebp-8h]
  int v8; // [esp+8h] [ebp-4h]

  if ( backdrop->backdrop_change_queued )
  {
    change_backdrop_real(backdrop);
    backdrop->backdrop_change_queued = 0;
  }
  v2 = backdrop->distort_grid[0];
  v8 = 8;
  do
  {
    p_phase = &v2->phase;
    v4 = 8;
    do
    {
      v7 = p_phase[1] + *p_phase;
      *p_phase = v7;
      if ( v7 > 6.2831855 )
        *p_phase = v7 - 6.2831855;
      p_phase[4] = sine(*p_phase) * p_phase[2];
      v5 = cosine(*p_phase) * p_phase[3];
      p_phase += 48;
      --v4;
      *(p_phase - 43) = v5;
    }
    while ( v4 );
    ++v2;
    --v8;
  }
  while ( v8 );
  result = backdrop->active_primary_texture_id;
  if ( result != -1 )
  {
    result = backdrop->backdrop_render_enabled - 1;
    if ( backdrop->backdrop_render_enabled == 1 )
    {
      if ( backdrop->active_split_backdrop_pair )
        draw_split_backdrop((int *)backdrop);
      else
        render_backdrop(backdrop);
    }
  }
  return result;
}
