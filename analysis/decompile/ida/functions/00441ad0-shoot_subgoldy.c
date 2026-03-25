/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shoot_subgoldy @ 0x441ad0 */
/* selector: shoot_subgoldy */

// Finds a free slot in the shared 20-shot pool, routes the request through `spawn_wall2_ambient_hazard`, and plays the positional player-fire cue from the supplied world position.
void __thiscall sub_441AD0(_DWORD *this, float *a2, _DWORD *a3)
{
  int v4; // eax
  _DWORD *i; // ecx
  float v6; // [esp+Ch] [ebp-14h]
  int v7; // [esp+10h] [ebp-10h]
  _DWORD v8[3]; // [esp+14h] [ebp-Ch] BYREF

  v4 = 0;
  for ( i = this + 32; *i; i += 44 )
  {
    if ( ++v4 >= 20 )
      return;
  }
  v7 = *((_DWORD *)a2 + 2);
  *(float *)v8 = *a2;
  v6 = (double)v4 * -0.0099999998 + a2[1];
  *(float *)&v8[1] = v6;
  v8[2] = v7;
  spawn_wall2_ambient_hazard((int)(this + 44 * v4), v8, a3);
  play_sound_effect_at_position(15, a2);
}

