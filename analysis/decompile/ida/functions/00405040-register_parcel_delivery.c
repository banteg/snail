/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_parcel_delivery @ 0x405040 */
/* selector: register_parcel_delivery */

// Records one delivered parcel on the gameplay row-event display controller, awards the per-parcel score event, and dispatches the all-parcels-delivered bonus when the final parcel arrives.
int32_t __fastcall register_parcel_delivery(RowEventDisplayController *controller)
{
  int32_t result; // eax

  result = controller->delivered_parcel_count;
  if ( result != controller->parcel_target_count )
  {
    add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), SUBGOLDY_SCORE_PARCEL_DELIVER, 0);
    ++controller->delivered_parcel_count;
    play_sound_effect(45);
    result = controller->parcel_target_count;
    if ( controller->delivered_parcel_count == result )
    {
      result = controller->bonus_enabled;
      if ( result )
      {
        add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), SUBGOLDY_SCORE_BONUS, controller->bonus_score);
        play_sound_effect(49);
      }
      controller->state = 3;
    }
  }
  return result;
}
