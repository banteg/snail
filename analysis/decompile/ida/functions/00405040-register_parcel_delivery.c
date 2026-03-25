/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_parcel_delivery @ 0x405040 */
/* selector: register_parcel_delivery */

// Records one delivered parcel on the gameplay row-event display controller, awards the per-parcel score event, and dispatches the all-parcels-delivered bonus when the final parcel arrives.
void __thiscall sub_405040(int *this)
{
  if ( *(this + 10) != *(this + 7) )
  {
    add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), 4, 0);
    ++*(this + 10);
    play_sound_effect(45);
    if ( *(this + 10) == *(this + 7) )
    {
      if ( *(this + 8) )
      {
        add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), 5, *(this + 18));
        play_sound_effect(49);
      }
      *(this + 5) = 3;
    }
  }
}

