/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect_at_position @ 0x44dce0 */
/* selector: play_sound_effect_at_position */

// Plays one effect id through the shared audio backend with distance attenuation and left-right pan derived from the supplied world position.
void __stdcall sub_44DCE0(int a1, float *a2)
{
  double v2; // st7
  double v3; // st7
  float v4; // [esp+4h] [ebp-1Ch]
  float v5; // [esp+4h] [ebp-1Ch]
  float v6; // [esp+8h] [ebp-18h]
  float v7; // [esp+Ch] [ebp-14h]
  float v8; // [esp+10h] [ebp-10h]
  float v9[3]; // [esp+14h] [ebp-Ch] BYREF
  float v10; // [esp+28h] [ebp+8h]

  v4 = 1.0e10;
  v6 = *a2 - *((float *)MEMORY[0x4DF904] + 139);
  v7 = a2[1] - *((float *)MEMORY[0x4DF904] + 140);
  v2 = a2[2] - *((float *)MEMORY[0x4DF904] + 141);
  v9[1] = v7;
  v9[0] = v6;
  v8 = v2;
  v9[2] = v8;
  vector_magnitude(v9);
  if ( v2 < 1.0e10 )
    v4 = v2;
  if ( v4 <= 25.0 )
  {
    v5 = 1.0 - v4 * 0.039999999;
    v3 = *a2 * -0.25 * 100.0;
    v10 = v3;
    if ( v3 >= -100.0 )
    {
      if ( v10 > 100.0 )
        v10 = 100.0;
    }
    else
    {
      v10 = -100.0;
    }
    play_sound_effect_backend(a1, v5, -1.0, v10);
  }
}

