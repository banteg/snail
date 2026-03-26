/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_nuke @ 0x4470e0 */
/* selector: uninit_nuke */

// Kills the 25 sprite slots owned by the collision ring-effect controller and clears its active state. Cross-port Android symbols match this helper to `cRNuke::UnInit()`.
void __thiscall uninit_nuke(NukeController *nuke)
{
  int *sprite_slots; // esi
  int v3; // edi

  if ( nuke->state == 1 )
  {
    sprite_slots = (int *)nuke->sprite_slots;
    v3 = 25;
    do
    {
      kill_sprite(*sprite_slots++);
      --v3;
    }
    while ( v3 );
    nuke->state = 0;
  }
}

