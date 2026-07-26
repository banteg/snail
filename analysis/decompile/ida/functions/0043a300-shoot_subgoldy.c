/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shoot_subgoldy @ 0x43a300 */
/* selector: shoot_subgoldy */

// Exact void Windows `cRSubGoldy::Shoot(cRSubGoldy*)`: classifies the explicit source Goldy's shoot flags into a one-, two-, or three-projectile budget, then fills inactive entries in the receiver's 12-slot owned `GolbShot` bank at +0x450. Android preserves the authored symbol and body; all Windows and Android callsites pass the same Goldy as receiver and source.
void __thiscall shoot_subgoldy(Player *owner, Player *shoot_source)
{
  uint32_t shoot_flags; // eax
  int32_t v4; // ebx
  int32_t v5; // esi
  GolbShot *golb_shots; // edi

  shoot_flags = shoot_source->shoot_flags;
  if ( (shoot_flags & 0x69) != 0 )
  {
    v4 = 1;
  }
  else if ( (shoot_flags & 0x12) != 0 )
  {
    v4 = 2;
  }
  else
  {
    if ( (shoot_flags & 4) == 0 )
      return;
    v4 = 3;
  }
  v5 = 0;
  golb_shots = owner->golb_shots;
  do
  {
    if ( golb_shots->state == 0 )
    {
      create_golb(golb_shots, owner, v4--, v5);
      if ( v4 == 0 )
        break;
    }
    ++v5;
    ++golb_shots;
  }
  while ( v5 < 12 );
}
