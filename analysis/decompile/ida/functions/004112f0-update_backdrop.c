/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_backdrop @ 0x4112f0 */
/* selector: update_backdrop */

// Advances the shared backdrop renderer, updates its distortion grid, and dispatches the split or warped draw path. Cross-port Android and iOS symbols match this helper to `cRBackdrop::AI()`.
int32_t __thiscall update_backdrop(Backdrop *backdrop)
{
  struct BackdropDistortCell *column_start; // ebx
  struct BackdropDistortCell *cell; // esi
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
  column_start = backdrop->distort_grid[0];
  v8 = 8;
  do
  {
    cell = column_start;
    v4 = 8;
    do
    {
      v7 = cell->phase_step + cell->phase;
      cell->phase = v7;
      if ( v7 > 6.2831855 )
        cell->phase = v7 - 6.2831855;
      cell->current_x_offset = sine(cell->phase) * cell->x_offset;
      v5 = cosine(cell->phase) * cell->y_offset;
      cell += 8;
      --v4;
      cell[-8].current_y_offset = v5;
    }
    while ( v4 );
    ++column_start;
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
        return draw_split_backdrop(backdrop);
      else
        render_backdrop(backdrop);
    }
  }
  return result;
}
