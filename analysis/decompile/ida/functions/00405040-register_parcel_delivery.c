/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_parcel_delivery @ 0x405040 */
/* selector: register_parcel_delivery */

// Exact Windows `cRCompletion::RegisterParcel()`: records one delivered parcel, awards the per-parcel score event, and dispatches the final bonus. Android and iOS retain the same member.
void __thiscall register_parcel_delivery(cRCompletion *completion)
{
  if ( completion->delivered_parcel_count != completion->parcel_target_count )
  {
    add_subgoldy_score(&g_game_base->subgame.player, 4, 0);
    ++completion->delivered_parcel_count;
    play_sound_effect(&g_sound_effect_manager, 45);
    if ( completion->delivered_parcel_count == completion->parcel_target_count )
    {
      if ( completion->bonus_enabled != 0 )
      {
        add_subgoldy_score(&g_game_base->subgame.player, 5, completion->bonus_score);
        play_sound_effect(&g_sound_effect_manager, 49);
      }
      completion->state = COMPLETION_STATE_SUMMARY_PENDING;
    }
  }
}
