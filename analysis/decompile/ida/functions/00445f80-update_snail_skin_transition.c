/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_snail_skin_transition @ 0x445f80 */
/* selector: update_snail_skin_transition */

// Applies the currently selected snail-skin object to the shared player render owner and, when a timed skin change is armed, advances the transition progress until the swap completes.
void __thiscall update_snail_skin_transition(SnailSkinTransitionState *state)
{
  double v1; // st7

  *(_DWORD *)(*((_DWORD *)state->owner_render_state + 9) + 16) |= 8u;
  *(_DWORD *)(*((_DWORD *)state->owner_render_state + 9) + 24) = *(_DWORD *)&state->_pad_04[4 * state->selected_slot];
  if ( state->active == 1 )
  {
    v1 = state->progress_step + state->progress;
    state->progress = v1;
    if ( v1 > 1.0 )
    {
      state->progress = 0.0;
      state->active = 0;
      state->selected_slot = 0;
    }
  }
}

