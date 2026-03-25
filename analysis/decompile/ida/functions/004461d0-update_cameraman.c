/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_cameraman @ 0x4461d0 */
/* selector: update_cameraman */

// Builds the live follow-camera pose from player transform, attachment state, motion scalars, and backdrop zoom before handing the matrix back to `update_subgame_camera`. Cross-port Android and iOS symbols match this helper to `cRCameraman::AI()`.
int __thiscall sub_4461D0(int this)
{
  int v2; // eax
  const void *v3; // ebx
  int v4; // ecx
  double v5; // st7
  double v6; // st7
  double v7; // st6
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  double v11; // st7
  int v12; // ecx
  float *v13; // ecx
  double v14; // st7
  double v15; // st7
  double v16; // st6
  double v17; // st7
  float *v18; // esi
  int v19; // eax
  int v20; // eax
  int v21; // ecx
  double v22; // st7
  double v23; // st7
  int v24; // eax
  int result; // eax
  int v26; // [esp+0h] [ebp-64h]
  float v27; // [esp+Ch] [ebp-58h]
  float v28; // [esp+Ch] [ebp-58h]
  float v29; // [esp+Ch] [ebp-58h]
  float v30; // [esp+Ch] [ebp-58h]
  float v31; // [esp+Ch] [ebp-58h]
  float v32; // [esp+Ch] [ebp-58h]
  float v33; // [esp+Ch] [ebp-58h]
  float v34; // [esp+20h] [ebp-44h]
  float v35; // [esp+20h] [ebp-44h]
  float v36; // [esp+20h] [ebp-44h]
  float v37[16]; // [esp+24h] [ebp-40h] BYREF

  v2 = *(_DWORD *)(this + 192);
  *(_BYTE *)(this + 204) = 0;
  v3 = (const void *)(this + 64);
  *(float *)&v26 = *(float *)(v2 + 10596) * 0.40000001;
  qmemcpy(
    (void *)(this + 64),
    initialize_matrix_from_values(
      v37,
      1065353216,
      0,
      0,
      0,
      0,
      1064447263,
      1051064464,
      0,
      0,
      -1096419184,
      1064447263,
      0,
      v26,
      1072064102,
      -1090519040,
      1065353216),
    0x40u);
  orthogonalize_matrix((float *)(this + 64));
  v4 = *(_DWORD *)(this + 192);
  v5 = (double)*(int *)(*(_DWORD *)(this + 196) + 80);
  if ( v5 <= *(float *)(v4 + 10604) )
  {
    *(float *)(this + 116) = *(float *)(v4 + 10600) * 0.34999999 + *(float *)(this + 116);
  }
  else
  {
    v6 = *(float *)(v4 + 10604) / v5 * 1.4 - 0.40000001;
    if ( v6 >= 0.0 )
    {
      if ( v6 > 1.0 )
        v6 = 1.0;
    }
    else
    {
      v6 = 0.0;
    }
    v34 = 1.0 - v6;
    v7 = (1.0 - v6) * *(float *)(v4 + 10600) * 1.15 + *(float *)(this + 116);
    *(float *)(this + 116) = v7;
    *(float *)(this + 116) = v6 * 0.34999999 * *(float *)(v4 + 10600) + v7;
    v27 = v34 * 0.87249994;
    rotate_matrix_world_x((float *)(this + 64), v27);
  }
  v8 = *(_DWORD *)(this + 192);
  if ( *(_BYTE *)(v8 + 900) == 1
    && ((v9 = *(_DWORD *)(v8 + 904), v10 = *(_DWORD *)(v9 + 56), v10 == 16)
     || v10 == 8
     || v10 == 9
     || v10 == 10
     || v10 == 43
     || v10 == 45
     || v10 == 36
     || v10 == 14) )
  {
    v11 = (*(float *)(v8 + 112) - *(float *)(*(_DWORD *)(v8 + 908) + 24)) / *(float *)(v9 + 76);
    if ( v11 >= 0.0 )
    {
      if ( v11 > 1.0 )
        v11 = 1.0;
    }
    else
    {
      v11 = 0.0;
    }
    v28 = v11 * 6.2831855;
    *(float *)(this + 208) = (0.5 - cosine(v28) * 0.5) * 0.34999999;
  }
  else
  {
    *(_DWORD *)(this + 208) = 0;
  }
  v12 = *(_DWORD *)(this + 192);
  if ( *(float *)(v12 + 732) > 0.0 )
  {
    v29 = *(float *)(v12 + 732) * 4.712389 + 1.5707964;
    *(float *)(this + 208) = (0.5 - cosine(v29) * 0.5) * 0.23999999 + *(float *)(this + 208);
  }
  v13 = *(float **)(this + 192);
  v14 = (*(float *)(this + 208) - *(float *)(this + 212)) * 0.1 + *(float *)(this + 212);
  *(float *)(this + 212) = v14;
  *(float *)(this + 116) = v14 * v13[2650] + *(float *)(this + 116);
  *(float *)(this + 112) = v13[2649] * 0.33333334 + *(float *)(this + 112);
  v15 = v13[2651] + *(float *)(this + 120) + 0.40000001;
  *(float *)(this + 120) = v15;
  v16 = v15 - *(float *)(this + 184);
  if ( v16 <= 3.0 )
  {
    if ( v16 < 1.7 )
      *(float *)(this + 184) = v15 - 1.7;
  }
  else
  {
    *(float *)(this + 184) = v15 - 3.0;
  }
  v17 = (-2.0 - (v13[2650] - 0.49000001) * 5.0) * 0.017449999;
  v35 = v17;
  if ( v17 >= -1.2214999 )
  {
    if ( v35 > 1.2214999 )
      v35 = 1.2214999;
    rotate_matrix_world_x((float *)(this + 64), v35);
  }
  else
  {
    rotate_matrix_world_x((float *)(this + 64), -1.2214999);
  }
  v18 = *(float **)(this + 192);
  v30 = v18[214] * 3.1415927;
  v31 = (0.5 - cosine(v30) * 0.5) * v18[213] * 6.2831855 + v18[2649] * -8.0 * 0.017449999 * 0.17;
  rotate_matrix_world_z((float *)(this + 64), v31);
  if ( *(_BYTE *)(*(_DWORD *)(this + 192) + 900) == 1 )
  {
    set_matrix_identity(v37);
    rotate_matrix_world_z(v37, *(float *)(*(_DWORD *)(this + 192) + 924));
    multiply_matrix_in_place((void *)(this + 64), v37);
    rotate_matrix_world_z((float *)(this + 64), *(float *)(*(_DWORD *)(this + 192) + 928));
  }
  v19 = *(_DWORD *)(this + 192);
  if ( *(_BYTE *)(v19 + 1053) )
    rotate_matrix_world_z((float *)(this + 64), *(float *)(v19 + 1068));
  rotate_matrix_world_z((float *)(this + 64), *(float *)(*(_DWORD *)(this + 192) + 880));
  v20 = *(_DWORD *)(this + 192);
  if ( *(_BYTE *)(v20 + 900) == 1 && (v21 = *(_DWORD *)(v20 + 904), *(_DWORD *)(v21 + 56) == 24) )
  {
    v22 = (*(float *)(v20 + 112) - *(float *)(*(_DWORD *)(v20 + 908) + 24)) / *(float *)(v21 + 76);
    if ( v22 >= 0.0 )
    {
      if ( v22 > 1.0 )
        v22 = 1.0;
    }
    else
    {
      v22 = 0.0;
    }
    v32 = v22 * 6.2831855;
    v36 = 0.5 - cosine(v32) * 0.5;
    sub_449C00();
    v23 = v36 * 50.0 + 110.0;
  }
  else
  {
    v23 = 110.0;
  }
  v24 = *(_DWORD *)(this + 196);
  *(float *)(this + 200) = (v23 - *(float *)(this + 200)) * 0.30000001 + *(float *)(this + 200);
  v33 = *(float *)(v24 + 56) * 0.30000001;
  result = linear_interpolate_matrix((float *)this, (float *)(this + 128), (float *)(this + 64), v33);
  qmemcpy((void *)(this + 128), v3, 0x40u);
  return result;
}

