/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: search_path_for_golb @ 0x415e30 */
/* selector: search_path_for_golb */

float *__thiscall sub_415E30(_DWORD *this, float *a2)
{
  float *result; // eax
  int v4; // ebx
  float *v5; // esi
  double v6; // st7
  double v7; // st7
  float v8; // [esp+8h] [ebp-20h]
  float *v9; // [esp+Ch] [ebp-1Ch]
  float v10; // [esp+10h] [ebp-18h]
  float v11; // [esp+14h] [ebp-14h]
  float v12; // [esp+18h] [ebp-10h]
  float v13[3]; // [esp+1Ch] [ebp-Ch] BYREF

  result = nullptr;
  v4 = 0;
  v9 = nullptr;
  v8 = 1000000000.0;
  if ( (int)*this > 0 )
  {
    v5 = (float *)(this + 4);
    do
    {
      v10 = *(v5 - 2) - *a2;
      v6 = *(v5 - 1) - a2[1];
      v13[0] = v10;
      v11 = v6;
      v7 = *v5 - a2[2];
      v13[1] = v11;
      v12 = v7;
      v13[2] = v12;
      if ( v12 > 0.0 && v12 < 30.0 )
      {
        vector_magnitude(v13);
        if ( v12 < (double)v8 )
        {
          v8 = v7;
          v9 = v5 - 3;
        }
      }
      ++v4;
      v5 += 6;
    }
    while ( v4 < *this );
    return v9;
  }
  return result;
}

