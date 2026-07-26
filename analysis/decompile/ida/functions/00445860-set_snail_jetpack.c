/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_snail_jetpack @ 0x445860 */
/* selector: set_snail_jetpack */

// Authored `cRSnail::SetJetPack(int)`: maps the requested jetpack state onto the exact embedded Snail's jetpack animation channel.
void __thiscall set_snail_jetpack(Snail *snail, int32_t state)
{
  int32_t target_state; // ebx
  int32_t selected_state; // eax
  uint8_t transition_immediate; // [esp+Ch] [ebp+4h]

  if ( state != 0 )
  {
    if ( state == 1 )
      target_state = 4;
    else
      target_state = state;
  }
  else
  {
    target_state = 0;
  }
  selected_state = snail->jetpack_channel.selected_state;
  transition_immediate = 1;
  if ( selected_state != target_state )
  {
    if ( selected_state == 4 )
    {
      set_weapon_animation(&snail->jetpack_channel, 1, 1u, 8);
      transition_immediate = 0;
      play_sound_effect(&g_sound_effect_manager, 26);
    }
    if ( target_state != 0 )
    {
      if ( target_state == 4 )
      {
        set_weapon_animation(&snail->jetpack_channel, 1, transition_immediate, 4);
        set_weapon_animation(&snail->jetpack_channel, 0, 0, -1);
        play_sound_effect(&g_sound_effect_manager, 16);
        snail->jetpack_channel.selected_state = 4;
        return;
      }
    }
    else
    {
      set_weapon_animation(&snail->jetpack_channel, -1, 0, -1);
    }
    snail->jetpack_channel.selected_state = target_state;
  }
}
