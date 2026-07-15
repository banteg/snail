/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_movement_flag_emitters @ 0x43a300 */
/* selector: update_movement_flag_emitters */

// Exact void `Player` member that iterates its 12 owned `GolbShot` slots at +0x450 and seeds one, two, or three live actors from an explicit `Player*` movement source. Both callers pass the same player as receiver and source.
void __thiscall update_movement_flag_emitters(Player *owner, Player *movement_source)
{
  uint32_t movement_flags; // eax
  int32_t v4; // ebx
  int32_t v5; // esi
  GolbShot *golb_shots; // edi

  movement_flags = movement_source->movement_flags;
  if ( (movement_flags & 0x69) != 0 )
  {
    v4 = 1;
  }
  else if ( (movement_flags & 0x12) != 0 )
  {
    v4 = 2;
  }
  else
  {
    if ( (movement_flags & 4) == 0 )
      return;
    v4 = 3;
  }
  v5 = 0;
  golb_shots = owner->golb_shots;
  do
  {
    if ( !golb_shots->state )
    {
      create_golb(golb_shots, owner, v4--, v5);
      if ( !v4 )
        break;
    }
    ++v5;
    ++golb_shots;
  }
  while ( v5 < 12 );
}
