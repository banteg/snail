/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_snail_jetpack @ 0x445860 */
/* selector: set_snail_jetpack */

void __thiscall set_snail_jetpack(GlobalJetpackPresentationController *controller, int32_t state)
{
  int32_t v3; // ebx
  int32_t selected_state; // eax

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
  selected_state = controller->jetpack_channel.selected_state;
  LOBYTE(state) = 1;
  if ( selected_state != v3 )
  {
    if ( selected_state == 4 )
    {
      set_weapon_animation(&controller->jetpack_channel, 1, 1, 8);
      LOBYTE(state) = 0;
      play_sound_effect(26);
    }
    if ( v3 )
    {
      if ( v3 == 4 )
      {
        set_weapon_animation(&controller->jetpack_channel, 1, state, 4);
        set_weapon_animation(&controller->jetpack_channel, 0, 0, -1);
        play_sound_effect(16);
        controller->jetpack_channel.selected_state = 4;
        return;
      }
    }
    else
    {
      set_weapon_animation(&controller->jetpack_channel, -1, 0, -1);
    }
    controller->jetpack_channel.selected_state = v3;
  }
}

