/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_snail_jetpack @ 0x445860 */
/* selector: set_snail_jetpack */

// Authored `cRSnail::SetJetPack(int)`: maps the requested jetpack state onto the exact embedded Snail's jetpack animation channel.
void __thiscall set_snail_jetpack(Snail *snail, int32_t state)
{
  int32_t v3; // ebx
  int32_t selected_state; // eax
  uint8_t statea; // [esp+Ch] [ebp+4h]

  if ( state )
  {
    if ( state == 1 )
      v3 = 4;
    else
      v3 = state;
  }
  else
  {
    v3 = 0;
  }
  selected_state = snail->jetpack_channel.selected_state;
  statea = 1;
  if ( selected_state != v3 )
  {
    if ( selected_state == 4 )
    {
      set_weapon_animation(&snail->jetpack_channel, 1, 1u, 8);
      statea = 0;
      play_sound_effect(26);
    }
    if ( v3 )
    {
      if ( v3 == 4 )
      {
        set_weapon_animation(&snail->jetpack_channel, 1, statea, 4);
        set_weapon_animation(&snail->jetpack_channel, 0, 0, -1);
        play_sound_effect(16);
        snail->jetpack_channel.selected_state = 4;
        return;
      }
    }
    else
    {
      set_weapon_animation(&snail->jetpack_channel, -1, 0, -1);
    }
    snail->jetpack_channel.selected_state = v3;
  }
}
