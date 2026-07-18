/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_nuke @ 0x4470e0 */
/* selector: uninit_nuke */

// Kills the 25 sprite slots owned by the exact 0x7c-byte cRNuke collision-ring effect at Player +0x150 and clears its active state. Android and iOS retain this method as `cRNuke::UnInit()`.
void __thiscall uninit_nuke(Nuke *nuke)
{
  Sprite **sprite_slots; // esi
  int v3; // edi

  if ( nuke->state == NUKE_STATE_ACTIVE )
  {
    sprite_slots = nuke->sprite_slots;
    v3 = 25;
    do
    {
      kill_sprite(*sprite_slots++);
      --v3;
    }
    while ( v3 );
    nuke->state = NUKE_STATE_INACTIVE;
  }
}
