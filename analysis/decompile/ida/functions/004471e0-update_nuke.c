/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_nuke @ 0x4471e0 */
/* selector: update_nuke */

// Advances the exact cRNuke owner by moving its 25 sprite slots around the containing player at radius `7.0`, using the +0x08/+0x0c z-step pair and +0x10/+0x14 phase pair. Android and iOS retain this method as `cRNuke::AI()`.
void __thiscall update_nuke(Nuke *nuke)
{
  double v2; // st7
  unsigned __int8 v4; // c0
  unsigned __int8 v5; // c3
  int v6; // ebx
  Sprite **sprite_slots; // esi
  double v8; // st7
  double v9; // st7
  Sprite *v10; // eax
  int v11; // [esp+4h] [ebp-4h]
  float v12; // [esp+4h] [ebp-4h]

  if ( nuke->state == NUKE_STATE_ACTIVE )
  {
    nuke->orbit_center_z = nuke->orbit_center_z_step + nuke->orbit_center_z;
    v2 = nuke->orbit_phase_step + nuke->orbit_phase;
    nuke->orbit_phase = v2;
    if ( !(v4 | v5) )
      nuke->orbit_phase = v2 - 6.2831855;
    v6 = 0;
    v11 = 0;
    sprite_slots = nuke->sprite_slots;
    do
    {
      v8 = (double)v11 * 0.039999999 * 6.2831855 + nuke->orbit_phase;
      (*sprite_slots)->position.z = nuke->orbit_center_z;
      v12 = v8;
      (*sprite_slots)->position.x = sine(v12) * 7.0;
      v9 = cosine(v12);
      v10 = *sprite_slots;
      ++v6;
      ++sprite_slots;
      v11 = v6;
      v10->position.y = v9 * 7.0;
    }
    while ( v6 < 25 );
  }
}
