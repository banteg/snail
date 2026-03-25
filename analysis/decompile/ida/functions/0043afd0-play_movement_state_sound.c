/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_movement_state_sound @ 0x43afd0 */
/* selector: play_movement_state_sound */

// Chooses one of three movement sound families from movement_flags and attenuates playback while attachment-exit handling is active.
void __thiscall sub_43AFD0(int this)
{
  int v2; // eax
  __int64 v3; // rax
  int v4; // edi
  __int64 v5; // rax
  __int64 v6; // rax
  double v7; // st7
  long double v8; // st7
  float v9; // [esp+8h] [ebp-1Ch]
  float v10; // [esp+Ch] [ebp-18h]
  float v11; // [esp+10h] [ebp-14h]
  float v12; // [esp+14h] [ebp-10h]
  float v13[3]; // [esp+18h] [ebp-Ch] BYREF

  v2 = *(_DWORD *)(this + 824);
  if ( (v2 & 7) != 0 )
  {
    v3 = (__int64)((double)next_math_random_value() * 0.000061035156);
    *(_DWORD *)(this + 460) = v3;
    v4 = v3 + 17;
  }
  else if ( (v2 & 0x18) != 0 )
  {
    v5 = (__int64)((double)next_math_random_value() * 0.000091552734);
    *(_DWORD *)(this + 460) = v5;
    v4 = v5 + 19;
  }
  else
  {
    if ( (v2 & 0x60) == 0 )
      return;
    v6 = (__int64)((double)next_math_random_value() * 0.000091552734);
    *(_DWORD *)(this + 460) = v6;
    v4 = v6 + 22;
  }
  if ( v4 != -1 )
  {
    if ( *(_BYTE *)(this + 1053) )
    {
      v10 = *((float *)MEMORY[0x4DF904] + 99) - *(float *)(this + 104);
      v11 = *((float *)MEMORY[0x4DF904] + 100) - *(float *)(this + 108);
      v7 = *((float *)MEMORY[0x4DF904] + 101) - *(float *)(this + 112);
      v13[1] = v11;
      v13[0] = v10;
      v12 = v7;
      v13[2] = v12;
      v8 = 1.0 - normalize_vector(v13) * 0.016666668;
      v9 = v8;
      if ( v8 >= 0.0 )
      {
        if ( v9 > 1.0 )
          v9 = 1.0;
        play_sound_effect_scaled(v4, v9);
      }
      else
      {
        play_sound_effect_scaled(v4, 0.0);
      }
    }
    else
    {
      play_sound_effect(v4);
    }
  }
}

