/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect_at_position @ 0x44dce0 */
/* selector: play_sound_effect_at_position */

// Windows cRSound positional overload: folds a one-listener minimum-distance loop over GamePlayer[0]'s owned camera transform position, then plays one effect id with 25-unit attenuation and left-right pan derived from the supplied Vector3 reference.
void __thiscall play_sound_effect_at_position(SoundEffectManager *manager, int32_t sound_id, Vec3 *position)
{
  double v3; // st7
  double v4; // st7
  float gain; // [esp+4h] [ebp-1Ch]
  float gaina; // [esp+4h] [ebp-1Ch]
  Vec3 vector; // [esp+14h] [ebp-Ch] BYREF
  float pan; // [esp+28h] [ebp+8h]
  Vec3 v9; // 0:^18.12

  gain = 1.0e10;
  v9.x = position->x - g_game_base->players[0].camera.body.transform.position.x;
  v9.y = position->y - g_game_base->players[0].camera.body.transform.position.y;
  v9.z = position->z - g_game_base->players[0].camera.body.transform.position.z;
  vector = v9;
  v3 = vector_magnitude(&vector);
  if ( v3 < 1.0e10 )
    gain = v3;
  if ( gain <= 25.0 )
  {
    gaina = 1.0 - gain * 0.039999999;
    v4 = position->x * -0.25 * 100.0;
    pan = v4;
    if ( v4 >= -100.0 )
    {
      if ( pan > 100.0 )
        pan = 100.0;
    }
    else
    {
      pan = -100.0;
    }
    play_sound_effect_backend(sound_id, gaina, -1.0, pan);
  }
}
