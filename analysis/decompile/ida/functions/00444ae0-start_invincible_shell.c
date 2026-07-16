/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_invincible_shell @ 0x444ae0 */
/* selector: start_invincible_shell */

// Authored `cRInvincible::Start()`: arms the embedded visual owner when the native invincible bit becomes active, seeds its spin/fade lanes, raises the shared render bit, and plays `SFX2/INVINCIBLE.OGG`.
void __thiscall start_invincible_shell(Invincible *invincible)
{
  InvincibleState state; // eax

  state = invincible->state;
  if ( state )
  {
    if ( state == INVINCIBLE_STATE_FADING_OUT )
      invincible->state = INVINCIBLE_STATE_FADING_IN;
  }
  else
  {
    invincible->state = INVINCIBLE_STATE_FADING_IN;
    invincible->spin_phase = 0.0;
    invincible->spin_phase_step = 0.033333335;
    invincible->fade_progress = 0.0;
    invincible->fade_step = 0.033333335;
    g_game_base->subgame.player.presentation.invincible_shell.body.bod.bod.list_flags |= 0x20u;
    play_registered_sound_sample_scaled((AudioBackend *)g_audio_backend, 48, 1.0);
  }
}
