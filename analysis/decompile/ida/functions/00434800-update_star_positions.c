/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_star_positions @ 0x434800 */
/* selector: update_star_positions */

// Advances each star-field streak along its cached direction, resets wrapped entries against the current camera origin, and scales the visible sprite trail by both per-streak speed and the controller fade factor.
int __thiscall sub_434800(_DWORD *this, float a2)
{
  int result; // eax
  int v3; // edi
  int v4; // edx
  float *v5; // esi
  float *v6; // eax
  int v7; // eax
  _DWORD *v8; // esi
  _DWORD *v9; // eax
  int v10; // eax
  double v11; // st7
  double v12; // st6
  float *v13; // eax
  int v14; // eax
  double v15; // st7
  float v16; // [esp+4h] [ebp-24h]
  float v17; // [esp+8h] [ebp-20h]
  float v18; // [esp+Ch] [ebp-1Ch]
  float v19; // [esp+14h] [ebp-14h]
  float v20; // [esp+18h] [ebp-10h]
  float v21; // [esp+20h] [ebp-8h]
  float v22; // [esp+24h] [ebp-4h]

  result = *(this + 16);
  v3 = 0;
  if ( result > 0 )
  {
    v4 = 0;
    do
    {
      *(float *)(v4 + *(this + 15) + 36) = *(float *)(v4 + *(this + 15) + 32) + *(float *)(v4 + *(this + 15) + 36);
      v5 = (float *)(v4 + *(this + 15) + 36);
      if ( *v5 > 35.0 )
      {
        *v5 = 0.0;
        *(_DWORD *)(*(_DWORD *)(v4 + *(this + 15) + 28) + 140) = 0;
        v19 = *((float *)MEMORY[0x4DF904] + 438) * 50.0;
        v20 = *((float *)MEMORY[0x4DF904] + 439) * 50.0;
        v16 = *((float *)MEMORY[0x4DF904] + 437) * 50.0 + *((float *)MEMORY[0x4DF904] + 441);
        v17 = v19 + *((float *)MEMORY[0x4DF904] + 442);
        v18 = v20 + *((float *)MEMORY[0x4DF904] + 443);
        v6 = (float *)(*(_DWORD *)(v4 + *(this + 15) + 28) + 72);
        *v6 = v16;
        v6[1] = v17;
        v6[2] = v18;
        v7 = v4 + *(this + 15);
        v8 = (_DWORD *)(v7 + 16);
        v9 = (_DWORD *)(*(_DWORD *)(v7 + 28) + 84);
        *v9 = *v8;
        v9[1] = v8[1];
        v9[2] = v8[2];
        v10 = v4 + *(this + 15);
        v11 = *(float *)(v10 + 16) * 10.0;
        v21 = *(float *)(v10 + 20) * 10.0;
        v12 = *(float *)(v10 + 24) * 10.0;
        v13 = (float *)(*(_DWORD *)(v10 + 28) + 72);
        v22 = v12;
        *v13 = v11 + *v13;
        v13[1] = v21 + v13[1];
        v13[2] = v22 + v13[2];
        *(float *)(v4 + *(this + 15) + 36) = *(float *)(v4 + *(this + 15) + 32) * 10.0
                                           + *(float *)(v4 + *(this + 15) + 36);
      }
      v14 = v4 + *(this + 15);
      ++v3;
      v4 += 44;
      v15 = (*(float *)(v14 + 36) - 2.0) * *(float *)(v14 + 40);
      result = *(_DWORD *)(v14 + 28);
      *(float *)(result + 56) = v15 * 0.011428571 * a2;
    }
    while ( v3 < *(this + 16) );
  }
  return result;
}

