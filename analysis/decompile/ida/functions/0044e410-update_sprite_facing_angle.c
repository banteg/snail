/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sprite_facing_angle @ 0x44e410 */
/* selector: update_sprite_facing_angle */

// Refreshes the sprite angle lane at `+0x7c` from motion delta in camera space, with the optional smoothing timer carried in `+0x8c/+0x90`.
void __thiscall update_sprite_facing_angle(int sprite, float *matrix)
{
  double v3; // st7
  double v4; // st7
  float *v5; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  float *v10; // eax
  float v11; // [esp-8h] [ebp-24h]
  float v12; // [esp-8h] [ebp-24h]
  float v13; // [esp-4h] [ebp-20h]
  float v14; // [esp-4h] [ebp-20h]
  float v15; // [esp+4h] [ebp-18h]
  float v16; // [esp+4h] [ebp-18h]
  float v17; // [esp+8h] [ebp-14h]
  float v18; // [esp+8h] [ebp-14h]
  float v19; // [esp+Ch] [ebp-10h]
  float v20; // [esp+Ch] [ebp-10h]
  float v21; // [esp+10h] [ebp-Ch] BYREF
  float v22; // [esp+14h] [ebp-8h]
  float v23; // [esp+18h] [ebp-4h]

  if ( (*(_DWORD *)(sprite + 4) & 0x400) != 0 )
  {
    if ( *(float *)(sprite + 140) == 0.0 )
    {
      v15 = *(float *)(sprite + 72) - *(float *)(sprite + 60);
      v3 = *(float *)(sprite + 76) - *(float *)(sprite + 64);
      v21 = v15;
      v17 = v3;
      v4 = *(float *)(sprite + 80) - *(float *)(sprite + 68);
      v22 = v17;
      v19 = v4;
      v23 = v19;
      v5 = rotate_vector_by_matrix(&v21, matrix);
      v13 = v5[1];
      v11 = *v5;
      v23 = v5[2];
      v6 = atan2_positive(v11, v13);
      *(_DWORD *)(sprite + 140) = 981668463;
      *(float *)(sprite + 124) = v6 + 7.0685835;
    }
    v7 = *(float *)(sprite + 144) + *(float *)(sprite + 140);
    *(float *)(sprite + 140) = v7;
    if ( v7 > 1.0 )
      *(_DWORD *)(sprite + 140) = 0;
  }
  else
  {
    v16 = *(float *)(sprite + 72) - *(float *)(sprite + 60);
    v8 = *(float *)(sprite + 76) - *(float *)(sprite + 64);
    v21 = v16;
    v18 = v8;
    v9 = *(float *)(sprite + 80) - *(float *)(sprite + 68);
    v22 = v18;
    v20 = v9;
    v23 = v20;
    v10 = rotate_vector_by_matrix(&v21, matrix);
    v14 = v10[1];
    v12 = *v10;
    v23 = v10[2];
    *(float *)(sprite + 124) = atan2_positive(v12, v14) + 7.0685835;
  }
}
