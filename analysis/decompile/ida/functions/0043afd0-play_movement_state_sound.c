/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_movement_state_sound @ 0x43afd0 */
/* selector: play_movement_state_sound */

// Void `Player` member that chooses one of three movement sound families from `movement_flags` and attenuates playback while attachment-exit handling is active. Both direct `update_subgoldy` callsites discard EAX, and its two returns expose only incidental sound-manager call results.
void __thiscall play_movement_state_sound(Player *player)
{
  uint32_t movement_flags; // eax
  __int64 v3; // rax
  int32_t v4; // edi
  __int64 v5; // rax
  __int64 v6; // rax
  double v7; // st7
  float v8; // [esp+8h] [ebp-1Ch]
  Vec3 vector; // [esp+18h] [ebp-Ch] BYREF
  Vec3 v10; // 0:^14.12

  movement_flags = player->movement_flags;
  if ( (movement_flags & 7) != 0 )
  {
    v3 = (__int64)((double)next_math_random_value() * 0.000061035156);
    player->movement_sound_variant_sample = v3;
    v4 = v3 + 17;
  }
  else if ( (movement_flags & 0x18) != 0 )
  {
    v5 = (__int64)((double)next_math_random_value() * 0.000091552734);
    player->movement_sound_variant_sample = v5;
    v4 = v5 + 19;
  }
  else
  {
    if ( (movement_flags & 0x60) == 0 )
      return;
    v6 = (__int64)((double)next_math_random_value() * 0.000091552734);
    player->movement_sound_variant_sample = v6;
    v4 = v6 + 22;
  }
  if ( v4 != -1 )
  {
    if ( player->attachment_exit_pending )
    {
      v10.x = g_game_base->players[0].body.transform.position.x - player->body.transform.position.x;
      v10.y = g_game_base->players[0].body.transform.position.y - player->body.transform.position.y;
      v10.z = g_game_base->players[0].body.transform.position.z - player->body.transform.position.z;
      vector = v10;
      v7 = 1.0 - normalize_vector(&vector) * 0.016666668;
      v8 = v7;
      if ( v7 >= 0.0 )
      {
        if ( v8 > 1.0 )
          v8 = 1.0;
      }
      else
      {
        v8 = 0.0;
      }
      play_sound_effect_scaled(&g_sound_effect_manager, v4, v8);
    }
    else
    {
      play_sound_effect(&g_sound_effect_manager, v4);
    }
  }
}
