/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_invincible_shell @ 0x444ae0 */
/* selector: start_invincible_shell */

// Arms the runner-owned invincible-shell controller when the native invincible bit becomes active, seeds its fade timers, raises the shared render bit, and plays `SFX2/INVINCIBLE.OGG`.
void __thiscall sub_444AE0(_DWORD *this)
{
  int v1; // eax

  v1 = *(this + 32);
  if ( v1 )
  {
    if ( v1 == 3 )
      *(this + 32) = 1;
  }
  else
  {
    *(this + 32) = 1;
    *(this + 33) = 0;
    *(this + 34) = 1023969417;
    *(this + 35) = 0;
    *(this + 36) = 1023969417;
    *((_DWORD *)MEMORY[0x4DF904] + 1101798) |= 0x20u;
    play_registered_sound_sample_scaled(48, 1.0);
  }
}

