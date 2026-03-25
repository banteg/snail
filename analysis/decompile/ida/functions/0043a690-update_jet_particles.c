/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_jet_particles @ 0x43a690 */
/* selector: update_jet_particles */

void __thiscall sub_43A690(int this)
{
  int v2; // esi
  int v3; // ecx
  double v4; // st7
  double v5; // st7
  int v6; // eax
  float *v7; // eax
  char *v8; // esi
  int v9; // eax
  _DWORD *v10; // eax
  int v11; // eax
  float *v12; // ecx
  double v13; // st7
  int v14; // [esp+4h] [ebp-50h]
  int v15; // [esp+8h] [ebp-4Ch]
  float v16; // [esp+Ch] [ebp-48h]
  float v17; // [esp+10h] [ebp-44h]
  float v18; // [esp+14h] [ebp-40h]
  float v19; // [esp+18h] [ebp-3Ch]
  float v20; // [esp+20h] [ebp-34h]
  float v21; // [esp+20h] [ebp-34h]
  float v22; // [esp+24h] [ebp-30h]
  float v23; // [esp+24h] [ebp-30h]
  float v24; // [esp+28h] [ebp-2Ch]
  float v25; // [esp+28h] [ebp-2Ch]
  float v26; // [esp+2Ch] [ebp-28h]
  float v27; // [esp+30h] [ebp-24h]
  float v28; // [esp+34h] [ebp-20h]
  float v29; // [esp+38h] [ebp-1Ch]
  float v30; // [esp+3Ch] [ebp-18h]
  _DWORD v31[4]; // [esp+44h] [ebp-10h] BYREF

  if ( *(_DWORD *)(this + 12) == 1
    && *(_DWORD *)(*(_DWORD *)(this + 512) + 3929052) == *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 512) + 3929148) + 188) )
  {
    v19 = (double)next_math_random_value() * 0.0000015258789 + 0.40000001;
    v2 = 0;
    v14 = 0;
    v18 = (double)next_math_random_value() * 0.0000015258789 + 0.12;
    while ( 1 )
    {
      v3 = 0;
      v15 = 0;
      v16 = (double)v14 * 0.071428575;
      v17 = (1.0 - v16) * v18 * *(float *)(this + 528);
      do
      {
        if ( v3 )
        {
          v20 = *(float *)(*(_DWORD *)(this + 512) + 3930432);
          v22 = *(float *)(*(_DWORD *)(this + 512) + 3930436);
          v24 = *(float *)(*(_DWORD *)(this + 512) + 3930440);
        }
        else
        {
          v20 = *(float *)(*(_DWORD *)(this + 512) + 3930420);
          v22 = *(float *)(*(_DWORD *)(this + 512) + 3930424);
          v24 = *(float *)(*(_DWORD *)(this + 512) + 3930428);
        }
        v4 = -(v16 * v19 * *(float *)(this + 528));
        v29 = v4 * *(float *)(*(_DWORD *)(this + 16) + 10716);
        v30 = v4 * *(float *)(*(_DWORD *)(this + 16) + 10720);
        v5 = v4 * *(float *)(*(_DWORD *)(this + 16) + 10724);
        v6 = this + 16 * (v3 + 2 * v2 + 2);
        v21 = v20 + v29;
        *(float *)(*(_DWORD *)v6 + 100) = v17;
        *(float *)(*(_DWORD *)v6 + 96) = v17;
        v23 = v22 + v30;
        v7 = (float *)(*(_DWORD *)v6 + 72);
        *v7 = v21;
        v7[1] = v23;
        v25 = v24 + v5;
        v7[2] = v25;
        if ( v2 == 14 )
        {
          if ( (double)next_math_random_value() * 0.000030517578 > 0.89999998 )
          {
            v8 = (char *)allocate_sprite(unk_790F30, *(_DWORD *)(*(_DWORD *)(this + 512) + 3914468), 33, -1, -1);
            v9 = *((_DWORD *)v8 + 1);
            BYTE1(v9) |= 8u;
            *((_DWORD *)v8 + 1) = v9;
            *((_DWORD *)v8 + 26) = 0;
            *((_DWORD *)v8 + 27) = 1041119460;
            *((_DWORD *)v8 + 28) = 0;
            *((_DWORD *)v8 + 29) = 0;
            v10 = set_color_rgba(v31, 1065353216, 1065353216, 1065353216, 1065353216);
            *((_DWORD *)v8 + 11) = *v10;
            *((_DWORD *)v8 + 12) = v10[1];
            *((_DWORD *)v8 + 13) = v10[2];
            v11 = v10[3];
            *((_DWORD *)v8 + 24) = 1036831949;
            *((_DWORD *)v8 + 25) = 1050253722;
            *((_DWORD *)v8 + 14) = v11;
            v12 = (float *)(v8 + 84);
            v8 += 72;
            v26 = *(float *)(*(_DWORD *)(this + 512) + 3914612) * 0.85000002;
            v27 = *(float *)(*(_DWORD *)(this + 512) + 3914616) * 0.85000002;
            v13 = *(float *)(*(_DWORD *)(this + 512) + 3914620) * 0.85000002;
            *((_DWORD *)v8 + 12) = 981668463;
            *v12 = v26;
            *(float *)v8 = v21;
            v28 = v13;
            v12[1] = v27;
            *((float *)v8 + 1) = v23;
            v12[2] = v28;
            *((float *)v8 + 2) = v25;
            v2 = v14;
          }
          v3 = v15;
        }
        v15 = ++v3;
      }
      while ( v3 < 2 );
      v14 = v2 + 1;
      if ( v2 + 1 >= 15 )
        break;
      ++v2;
    }
  }
}

