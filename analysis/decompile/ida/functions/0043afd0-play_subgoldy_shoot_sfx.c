/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_subgoldy_shoot_sfx @ 0x43afd0 */
/* selector: play_subgoldy_shoot_sfx */

// Void Windows `cRSubGoldy::PlayShootSfx()`: chooses one of the authored shoot-SFX families 17..18, 19..21, or 22..24 from `Player::shoot_flags` at +0x338, caches the sampled variant at Player +0x1cc, and attenuates playback while attachment-exit handling is active. Android and iOS preserve the authored symbol. Android's shared epilogue receives incompatible R0 residues from the no-sound, direct-play, and scaled-play paths, independently proving there is no result contract.
void __thiscall play_subgoldy_shoot_sfx(Player *player)
{
  uint32_t shoot_flags; // eax
  __int64 v3; // rax
  int32_t v4; // edi
  __int64 v5; // rax
  __int64 v6; // rax
  double v7; // st7
  float gain; // [esp+8h] [ebp-1Ch]
  Vec3 vector; // [esp+18h] [ebp-Ch] BYREF
  Vec3 v10; // 0:^14.12

  shoot_flags = player->shoot_flags;
  if ( (shoot_flags & 7) != 0 )
  {
    v3 = (__int64)((double)next_math_random_value() * 0.000061035156);
    player->shoot_sfx_variant_sample = v3;
    v4 = v3 + 17;
  }
  else if ( (shoot_flags & 0x18) != 0 )
  {
    v5 = (__int64)((double)next_math_random_value() * 0.000091552734);
    player->shoot_sfx_variant_sample = v5;
    v4 = v5 + 19;
  }
  else
  {
    if ( (shoot_flags & 0x60) == 0 )
      return;
    v6 = (__int64)((double)next_math_random_value() * 0.000091552734);
    player->shoot_sfx_variant_sample = v6;
    v4 = v6 + 22;
  }
  if ( v4 != -1 )
  {
    if ( player->attachment_exit_pending != 0 )
    {
      v10.x = g_game_base->players[0].body.transform.position.x - player->body.transform.position.x;
      v10.y = g_game_base->players[0].body.transform.position.y - player->body.transform.position.y;
      v10.z = g_game_base->players[0].body.transform.position.z - player->body.transform.position.z;
      vector = v10;
      v7 = 1.0 - normalize_vector(&vector) * 0.016666668;
      gain = v7;
      if ( v7 >= 0.0 )
      {
        if ( gain > 1.0 )
          gain = 1.0;
      }
      else
      {
        gain = 0.0;
      }
      play_sound_effect_scaled(&g_sound_effect_manager, v4, gain);
    }
    else
    {
      play_sound_effect(&g_sound_effect_manager, v4);
    }
  }
}
