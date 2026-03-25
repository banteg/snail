/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_vapour @ 0x4425f0 */
/* selector: update_vapour */

char __thiscall sub_4425F0(int this)
{
  int v1; // eax
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  float *v5; // esi
  float *v6; // edx
  int v7; // edi
  double v8; // st7
  float *v9; // eax
  double v10; // st7
  int v11; // eax
  float *v12; // esi
  double v13; // st7
  float *v14; // esi
  float *v15; // esi
  double v16; // st7
  float *v17; // esi
  float *v18; // esi
  double v19; // st7
  float *v20; // edx
  float *v21; // edx
  int v22; // edx
  int v23; // edx
  bool v24; // zf
  float v26; // [esp+0h] [ebp-60h]
  float v27; // [esp+4h] [ebp-5Ch]
  float v28; // [esp+8h] [ebp-58h]
  float v29; // [esp+Ch] [ebp-54h]
  float v30; // [esp+10h] [ebp-50h]
  float v31; // [esp+14h] [ebp-4Ch]
  float v32; // [esp+18h] [ebp-48h]
  float v33; // [esp+1Ch] [ebp-44h]
  float v34; // [esp+20h] [ebp-40h]
  float v35; // [esp+24h] [ebp-3Ch]
  float v36; // [esp+28h] [ebp-38h]
  float v37; // [esp+2Ch] [ebp-34h]
  float v38; // [esp+30h] [ebp-30h]
  float v39; // [esp+34h] [ebp-2Ch]
  float v40; // [esp+3Ch] [ebp-24h]
  float v41; // [esp+40h] [ebp-20h]
  float v42; // [esp+48h] [ebp-18h]
  float v43; // [esp+4Ch] [ebp-14h]
  float v44; // [esp+54h] [ebp-Ch]
  float v45; // [esp+58h] [ebp-8h]

  v1 = *(_DWORD *)(this + 128);
  if ( v1 >= 2 )
  {
    *(_DWORD *)(this + 4) |= 0x20u;
    *(_DWORD *)(*(_DWORD *)(this + 36) + 44) = 4 * v1 - 4;
    if ( *(_DWORD *)(this + 140) )
    {
      v3 = 0;
      if ( *(int *)(this + 128) > 0 )
      {
        v4 = 0;
        do
        {
          v5 = *(float **)(this + 140);
          v6 = (float *)(v4 + *(_DWORD *)(this + 144) + 56);
          if ( *v6 < (double)*v5 )
            *v6 = *v5;
          ++v3;
          v4 += 64;
        }
        while ( v3 < *(_DWORD *)(this + 128) );
      }
    }
    v7 = 0;
    if ( *(_DWORD *)(this + 128) - 1 <= 0 )
    {
LABEL_18:
      v2 = 2 * *(_DWORD *)(this + 128) - 2;
      **(_DWORD **)(*(_DWORD *)(this + 36) + 212) = v2;
      return v2;
    }
    while ( 1 )
    {
      v8 = *(float *)(this + 136);
      v9 = (float *)((v7 << 6) + *(_DWORD *)(this + 144));
      v38 = v8 * *v9;
      v39 = v8 * v9[1];
      v26 = v38 + v9[12];
      v27 = v39 + v9[13];
      v10 = v8 * v9[2] + v9[14];
      v11 = 48 * v7;
      v12 = (float *)(48 * v7 + *(_DWORD *)(*(_DWORD *)(this + 36) + 56));
      v28 = v10;
      *v12 = v26;
      v12[1] = v27;
      v12[2] = v28;
      v13 = -*(float *)(this + 136);
      v14 = (float *)((v7 << 6) + *(_DWORD *)(this + 144));
      v40 = v13 * *v14;
      v41 = v13 * v14[1];
      v29 = v40 + v14[12];
      v30 = v41 + v14[13];
      v31 = v13 * v14[2] + v14[14];
      v15 = (float *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 56) + 48 * v7 + 12);
      *v15 = v29;
      v15[1] = v30;
      v15[2] = v31;
      v16 = -*(float *)(this + 136);
      v17 = (float *)((v7 << 6) + *(_DWORD *)(this + 144));
      v42 = v16 * *v17;
      v43 = v16 * v17[1];
      v32 = v42 + v17[28];
      v33 = v43 + v17[29];
      v34 = v16 * v17[2] + v17[30];
      v18 = (float *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 56) + 48 * v7 + 24);
      *v18 = v32;
      v18[1] = v33;
      v18[2] = v34;
      v19 = *(float *)(this + 136);
      v20 = (float *)(*(_DWORD *)(this + 144) + (v7 << 6));
      v44 = v19 * *v20;
      v45 = v19 * v20[1];
      v35 = v44 + v20[28];
      v36 = v45 + v20[29];
      v37 = v19 * v20[2] + v20[30];
      v21 = (float *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 56) + 48 * v7 + 36);
      *v21 = v35;
      v21[1] = v36;
      v21[2] = v37;
      v22 = *(_DWORD *)(this + 128);
      if ( v22 == 2 )
      {
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + v11 + 20) = 0;
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + v11 + 28) = 0;
        v23 = *(_DWORD *)(this + 36);
      }
      else
      {
        if ( !v7 )
        {
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + 20) = 0;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + 28) = 0;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + 36) = 1056964608;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + 44) = 1056964608;
          goto LABEL_17;
        }
        v24 = v7 == v22 - 2;
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + v11 + 20) = 1056964608;
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + v11 + 28) = 1056964608;
        v23 = *(_DWORD *)(this + 36);
        if ( !v24 )
        {
          *(_DWORD *)(*(_DWORD *)(v23 + 92) + v11 + 36) = 1056964608;
          *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + v11 + 44) = 1056964608;
          goto LABEL_17;
        }
      }
      *(_DWORD *)(*(_DWORD *)(v23 + 92) + v11 + 36) = 1065353216;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 92) + v11 + 44) = 1065353216;
LABEL_17:
      if ( ++v7 >= *(_DWORD *)(this + 128) - 1 )
        goto LABEL_18;
    }
  }
  v2 = *(_DWORD *)(this + 4);
  LOBYTE(v2) = v2 & 0xDF;
  *(_DWORD *)(this + 4) = v2;
  return v2;
}

