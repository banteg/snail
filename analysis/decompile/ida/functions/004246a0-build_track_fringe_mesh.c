/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_fringe_mesh @ 0x4246a0 */
/* selector: build_track_fringe_mesh */

int __thiscall sub_4246A0(int this, _BYTE *a2, float a3)
{
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  int *v6; // ebx
  int v7; // ebp
  float *v8; // esi
  int v9; // eax
  int v10; // ecx
  int v11; // edx
  float *v12; // ebx
  float *v13; // edx
  float *v14; // eax
  float *v15; // ebp
  float *v16; // eax
  double v17; // st7
  double v18; // st7
  float v19; // eax
  float *v20; // eax
  float *v21; // edx
  double v22; // st7
  double v23; // st7
  float v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int result; // eax
  int v28; // esi
  int v29; // [esp+10h] [ebp-68h]
  int v30; // [esp+10h] [ebp-68h]
  int v31; // [esp+14h] [ebp-64h]
  int v32; // [esp+18h] [ebp-60h]
  int v33; // [esp+1Ch] [ebp-5Ch]
  float v34; // [esp+20h] [ebp-58h] BYREF
  float v35; // [esp+24h] [ebp-54h]
  float v36; // [esp+28h] [ebp-50h]
  float v37; // [esp+2Ch] [ebp-4Ch]
  float v38; // [esp+30h] [ebp-48h]
  float v39; // [esp+34h] [ebp-44h]
  float v40; // [esp+38h] [ebp-40h]
  float v41; // [esp+3Ch] [ebp-3Ch]
  float v42; // [esp+40h] [ebp-38h]
  float v43; // [esp+44h] [ebp-34h]
  float v44; // [esp+48h] [ebp-30h]
  float v45; // [esp+4Ch] [ebp-2Ch]
  float v46; // [esp+50h] [ebp-28h]
  float v47; // [esp+54h] [ebp-24h]
  float v48; // [esp+58h] [ebp-20h]
  float v49; // [esp+60h] [ebp-18h]
  float v50; // [esp+64h] [ebp-14h]
  int v51; // [esp+68h] [ebp-10h] BYREF
  float v52; // [esp+6Ch] [ebp-Ch]
  float v53; // [esp+70h] [ebp-8h]

  v4 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 96), (int)v4);
  v5 = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, &v51);
  v6 = *(int **)(this + 132);
  *(_DWORD *)(this + 136) = *v5;
  *(_DWORD *)(this + 140) = v5[1];
  *(_DWORD *)(this + 144) = v5[2];
  *(_DWORD *)(this + 148) = v5[3];
  v7 = v6[4] | 0x100040;
  v6[5] = 5;
  v6[4] = v7;
  request_object_vertices(v6, 4 * *(_DWORD *)(this + 68) + 4);
  request_object_facequads(v6, 2 * *(_DWORD *)(this + 68));
  v33 = v6[23];
  v29 = 0;
  if ( *(int *)(this + 68) >= 0 )
  {
    v8 = (float *)(v6[14] + 20);
    do
    {
      v9 = *(_DWORD *)(this + 84);
      if ( *(_BYTE *)(this + 60) )
      {
        v31 = 1;
        v10 = *(_DWORD *)(this + 84);
        v32 = 0;
        v11 = v9 - 1;
      }
      else
      {
        v10 = 0;
        v11 = 1;
        v32 = *(_DWORD *)(this + 84);
        v31 = v9 - 1;
      }
      v12 = v8 - 5;
      v13 = (float *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 56) + 12 * (v11 + v29 * (v9 + 1)));
      v14 = v8 - 5;
      *v14 = *v13;
      v14[1] = v13[1];
      v15 = v8 - 2;
      v14[2] = v13[2];
      v16 = (float *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 56) + 12 * (v10 + v29 * (*(_DWORD *)(this + 84) + 1)));
      *v15 = *v16;
      v15[1] = v16[1];
      *v8 = v16[2];
      v37 = *(v8 - 2) - *(v8 - 5);
      v38 = *(v8 - 1) - *(v8 - 4);
      v17 = *v8 - *(v8 - 3);
      v34 = v37;
      v35 = v38;
      v39 = v17;
      v36 = v39;
      normalize_vector(&v34);
      v49 = v35 * 0.40000001;
      v50 = v36 * 0.40000001;
      v40 = v34 * 0.40000001 + *(v8 - 2);
      v41 = v49 + *(v8 - 1);
      v18 = v50 + *v8;
      v19 = v41;
      *v12 = v40;
      v12[1] = v19;
      v42 = v18;
      v12[2] = v42;
      v20 = (float *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 56) + 12 * (v31 + v29 * (*(_DWORD *)(this + 84) + 1)));
      v8[1] = *v20;
      v8[2] = v20[1];
      v8[3] = v20[2];
      v21 = (float *)(*(_DWORD *)(*(_DWORD *)(this + 36) + 56) + 12 * (v32 + v29 * (*(_DWORD *)(this + 84) + 1)));
      v8[4] = *v21;
      v8[5] = v21[1];
      v8[6] = v21[2];
      v43 = v8[4] - v8[1];
      v44 = v8[5] - v8[2];
      v22 = v8[6] - v8[3];
      v34 = v43;
      v35 = v44;
      v45 = v22;
      v36 = v45;
      normalize_vector(&v34);
      v52 = v35 * 0.40000001;
      v53 = v36 * 0.40000001;
      v46 = v34 * 0.40000001 + v8[4];
      v47 = v52 + v8[5];
      v23 = v53 + v8[6];
      v24 = v47;
      v8[1] = v46;
      v8[2] = v24;
      v48 = v23;
      v8[3] = v48;
      if ( a3 == -1.0 )
      {
        v25 = 4;
        do
        {
          if ( *v12 > 0.0 )
            *v12 = 0.0;
          v12 += 3;
          --v25;
        }
        while ( v25 );
      }
      else if ( a3 == 1.0 )
      {
        v26 = 4;
        do
        {
          if ( *v12 < 0.0 )
            *v12 = 0.0;
          v12 += 3;
          --v26;
        }
        while ( v26 );
      }
      v8 += 12;
      ++v29;
    }
    while ( v29 <= *(_DWORD *)(this + 68) );
  }
  result = *(_DWORD *)(this + 68);
  v30 = 0;
  if ( result > 0 )
  {
    v28 = v33 + 2;
    do
    {
      *(_DWORD *)(v28 + 10) = get_or_create_texture_ref(&texture_list, a2, 0, 0);
      *(_WORD *)v28 = 4 * v30 + 5;
      *(_WORD *)(v28 + 2) = 4 * v30 + 4;
      *(_WORD *)(v28 + 4) = 4 * v30;
      *(_WORD *)(v28 + 6) = 4 * v30 + 1;
      *(_DWORD *)(v28 + 38) = 1056964608;
      *(_DWORD *)(v28 + 42) = 0;
      *(_DWORD *)(v28 + 14) = 1056964608;
      *(_DWORD *)(v28 + 18) = 0;
      *(_DWORD *)(v28 + 22) = 1056964608;
      *(_DWORD *)(v28 + 26) = 1065353216;
      *(_DWORD *)(v28 + 30) = 1056964608;
      *(_DWORD *)(v28 + 34) = 1065353216;
      *(_DWORD *)(v28 + 58) = get_or_create_texture_ref(&texture_list, a2, 0, 0);
      *(_WORD *)(v28 + 48) = 4 * v30 + 6;
      *(_WORD *)(v28 + 50) = 4 * v30 + 7;
      *(_WORD *)(v28 + 52) = 4 * v30 + 3;
      *(_WORD *)(v28 + 54) = 4 * v30 + 2;
      *(_DWORD *)(v28 + 86) = 1056964608;
      *(_DWORD *)(v28 + 90) = 1065353216;
      *(_DWORD *)(v28 + 62) = 1056964608;
      *(_DWORD *)(v28 + 66) = 1065353216;
      *(_DWORD *)(v28 + 70) = 1056964608;
      *(_DWORD *)(v28 + 74) = 0;
      *(_DWORD *)(v28 + 78) = 1056964608;
      *(_DWORD *)(v28 + 82) = 0;
      result = v30 + 1;
      v28 += 96;
      ++v30;
    }
    while ( v30 < *(_DWORD *)(this + 68) );
  }
  return result;
}

