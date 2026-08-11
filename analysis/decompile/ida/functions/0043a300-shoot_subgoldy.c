/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shoot_subgoldy @ 0x43a300 */
/* selector: shoot_subgoldy */

// Exact void Windows `cRSubGoldy::Shoot(cRSubGoldy*)`: classifies the explicit source Goldy's shoot flags into a one-, two-, or three-projectile budget, then fills inactive entries in the receiver's 12-slot owned `GolbShot` bank at +0x450. Android preserves the authored symbol and body; all Windows and Android callsites pass the same Goldy as receiver and source.
void __thiscall shoot_subgoldy(Player *owner, Player *shoot_source)
{
  uint32_t shoot_flags; // eax
  int32_t spawn_selector; // ebx
  int32_t shot_slot_index; // esi
  GolbShot *golb_shot_cursor; // edi

  shoot_flags = shoot_source->shoot_flags;
  if ( (shoot_flags & 0x69) != 0 )
  {
    spawn_selector = 1;
  }
  else if ( (shoot_flags & 0x12) != 0 )
  {
    spawn_selector = 2;
  }
  else
  {
    if ( (shoot_flags & 4) == 0 )
      return;
    spawn_selector = 3;
  }
  shot_slot_index = 0;
  golb_shot_cursor = owner->golb_shots;
  do
  {
    if ( golb_shot_cursor->state == 0 )
    {
      create_golb(golb_shot_cursor, owner, spawn_selector--, shot_slot_index);
      if ( spawn_selector == 0 )
        break;
    }
    ++shot_slot_index;
    ++golb_shot_cursor;
  }
  while ( shot_slot_index < 12 );
}
