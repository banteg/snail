/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_nuke @ 0x4471e0 */
/* selector: update_nuke */

// Advances the 25-sprite collision ring effect by orbiting its sprite slots around the owner at radius `7.0` while the owning timer remains active. Cross-port Android symbols match this helper to `cRNuke::AI()`.
int32_t __thiscall update_nuke(NukeController *nuke)
{
  int32_t result; // eax
  double v3; // st7
  unsigned __int8 v5; // c0
  unsigned __int8 v6; // c3
  int v7; // ebx
  void **sprite_slots; // esi
  double v9; // st7
  double v10; // st7
  int v11; // [esp+4h] [ebp-4h]
  float v12; // [esp+4h] [ebp-4h]

  result = nuke->state;
  if ( nuke->state )
  {
    if ( !--result )
    {
      nuke->orbit_center_z = nuke->orbit_center_z_step + nuke->orbit_center_z;
      v3 = nuke->orbit_phase_step + nuke->orbit_phase;
      nuke->orbit_phase = v3;
      if ( !(v5 | v6) )
        nuke->orbit_phase = v3 - 6.2831855;
      v7 = 0;
      v11 = 0;
      sprite_slots = nuke->sprite_slots;
      do
      {
        v9 = (double)v11 * 0.039999999 * 6.2831855 + nuke->orbit_phase;
        *((_DWORD *)*sprite_slots + 20) = LODWORD(nuke->orbit_center_z);
        v12 = v9;
        *((float *)*sprite_slots + 18) = sine(v12) * 7.0;
        v10 = cosine(v12);
        result = (int32_t)*sprite_slots;
        ++v7;
        ++sprite_slots;
        v11 = v7;
        *(float *)(result + 76) = v10 * 7.0;
      }
      while ( v7 < 25 );
    }
  }
  return result;
}
