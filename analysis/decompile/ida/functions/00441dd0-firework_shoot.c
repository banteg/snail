/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: firework_shoot @ 0x441dd0 */
/* selector: firework_shoot */

char __stdcall sub_441DD0(float *a1, int a2, int a3, int a4)
{
  char result; // al
  float *v7; // esi
  int v8; // ecx
  double v9; // st7
  bool v10; // zf
  int v11; // [esp+0h] [ebp-28h]
  int v12; // [esp+18h] [ebp-10h]
  float v13; // [esp+1Ch] [ebp-Ch]
  float v14; // [esp+30h] [ebp+8h]
  float v15; // [esp+34h] [ebp+Ch]
  int v16; // [esp+38h] [ebp+10h]
  int v17; // [esp+38h] [ebp+10h]

  result = byte_4DF934;
  if ( (byte_4DF934 & 0x10) != 0 )
  {
    result = a4;
    if ( a4 > 0 )
    {
      v12 = a4;
      do
      {
        v7 = (float *)allocate_sprite(unk_790F30, a2, a3, -1, -1);
        v8 = *((_DWORD *)v7 + 1);
        *((_DWORD *)v7 + 10) = 10;
        v7[34] = 4.0;
        *((_DWORD *)v7 + 1) = v8 | 0x802;
        v7[26] = 0.0;
        v9 = random_float_below(0.5);
        v7[28] = 0.0;
        v7[29] = 0.27777779;
        v7[27] = 1.0 / ((v9 + 0.80000001) * 60.0);
        *(float *)&v16 = random_float_below(0.30000001) + 0.69999999;
        *(float *)&v11 = *(float *)&v16 * 0.5;
        sub_44DBD0((_DWORD *)v7 + 11, v16, v11, 0);
        v7[24] = 0.5;
        v7[25] = 0.1;
        v14 = ((double)next_math_random_value() - 16384.0) * 0.000012207031;
        v15 = ((double)next_math_random_value() - 16384.0) * 0.000018310548 + 0.1;
        v17 = next_math_random_value();
        v7[37] = 0.0;
        v13 = ((double)v17 - 16384.0) * 0.000012207031;
        v7[21] = v13;
        v7[22] = v15;
        v7[23] = v14;
        v7 += 18;
        *v7 = *a1;
        result = v12 - 1;
        v10 = v12 == 1;
        v7[1] = a1[1];
        --v12;
        v7[2] = a1[2];
      }
      while ( !v10 );
    }
  }
  return result;
}

