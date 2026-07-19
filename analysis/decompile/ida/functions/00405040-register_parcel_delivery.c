/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_parcel_delivery @ 0x405040 */
/* selector: register_parcel_delivery */

// Exact Windows `Completion::register_parcel_delivery`: records one delivered parcel, awards the per-parcel score event, and dispatches the final bonus. Android and iOS retain this member as `cRCompletion::RegisterParcel()`.
void __thiscall register_parcel_delivery(Completion *completion)
{
  if ( completion->delivered_parcel_count != completion->parcel_target_count )
  {
    add_subgoldy_score((Player *)((char *)&g_player_block + (_DWORD)g_game_base), 4, 0);
    ++completion->delivered_parcel_count;
    play_sound_effect(&g_sound_effect_manager, 45);
    if ( completion->delivered_parcel_count == completion->parcel_target_count )
    {
      if ( completion->bonus_enabled )
      {
        add_subgoldy_score((Player *)((char *)&g_player_block + (_DWORD)g_game_base), 5, completion->bonus_score);
        play_sound_effect(&g_sound_effect_manager, 49);
      }
      completion->state = COMPLETION_STATE_SUMMARY_PENDING;
    }
  }
}
