/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_invincible_shell @ 0x444ae0 */
/* selector: start_invincible_shell */

// Arms the runner-owned invincible-shell controller when the native invincible bit becomes active, seeds its fade timers, raises the shared render bit, and plays `SFX2/INVINCIBLE.OGG`.
void __thiscall start_invincible_shell(InvincibleShellController *shell)
{
  int32_t state; // eax

  state = shell->state;
  if ( state )
  {
    if ( state == 3 )
      shell->state = 1;
  }
  else
  {
    shell->state = 1;
    shell->spin_phase = 0.0;
    shell->spin_phase_step = 0.033333335;
    shell->fade_progress = 0.0;
    shell->fade_step = 0.033333335;
    *((_DWORD *)MEMORY[0x4DF904] + 1101798) |= 0x20u;
    play_registered_sound_sample_scaled(48, 1.0);
  }
}

