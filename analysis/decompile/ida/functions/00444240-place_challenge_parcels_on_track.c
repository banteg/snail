/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: place_challenge_parcels_on_track @ 0x444240 */
/* selector: place_challenge_parcels_on_track */

// Scans parcel-capable runtime rows whose copied parcel id is zero and places challenge parcels from that filtered set. Cross-port Android and iOS symbols match this helper to `cRSubGame::PlaceParcelsSurvival()`.
int __thiscall sub_444240(int this)
{
  int v2; // eax
  int *v3; // eax
  int v4; // esi
  int v5; // eax
  int *v6; // edx
  _DWORD *v7; // ecx
  int v8; // edi
  int v9; // ebx
  __int64 v10; // rax
  _DWORD *v11; // esi
  float *v12; // ecx
  int v13; // ecx
  int result; // eax
  float *v15; // esi
  int v16; // edi
  _DWORD *v17; // ecx
  int v18; // ecx
  int v19; // eax
  float v20; // [esp+0h] [ebp-60h]
  int v21; // [esp+18h] [ebp-48h]
  int v22; // [esp+18h] [ebp-48h]
  int v23; // [esp+1Ch] [ebp-44h] BYREF
  int v24[16]; // [esp+20h] [ebp-40h] BYREF

  v2 = (__int64)((double)*(int *)(this + 40) * 50.0 * 0.0099999998 + *(float *)(this + 52) * 50.0) + 1;
  *(_DWORD *)(this + 1769952) = v2;
  *(_DWORD *)(this + 1769960) = v2;
  v3 = &MEMORY[0x53D390];
  do
  {
    *v3 = 0;
    v3 += 131;
  }
  while ( (int)v3 < (int)unk_643390 );
  v4 = 0;
  v5 = 0;
  v21 = 0;
  if ( *(int *)(this + 84) > 0 )
  {
    v6 = unk_6447E8;
    v7 = (int *)((char *)&unk_5CCB64 + this);
    do
    {
      if ( (*(_BYTE *)(v7 - 39) & 1) != 0 && !*v7 )
      {
        *v6 = v5;
        ++v4;
        ++v6;
      }
      ++v5;
      v7 += 61;
    }
    while ( v5 < *(_DWORD *)(this + 84) );
    v21 = v4;
  }
  v8 = 0;
  if ( *(int *)(this + 1769952) > 0 )
  {
    v9 = v4 - 1;
    while ( v4 > 0 )
    {
      v20 = (float)v21;
      v10 = (__int64)random_float_below(v20);
      v11 = (_DWORD *)(4 * v10 + 6572008);
      v23 = unk_6447E8[(_DWORD)v10];
      ++v8;
      v12 = (float *)(this + 244 * v23);
      *(int *)((char *)unk_5CCAC8 + (_DWORD)v12) |= 0x11u;
      v12[1520343] = v12[1520343] + 1.0;
      if ( (*((_BYTE *)unk_5CCAC8 + (_DWORD)v12) & 0x20) != 0 )
        v12[1520342] = v12[1520342] * -1.0;
      if ( (*(int *)((_BYTE *)unk_5CCAC8 + (_DWORD)v12) & 0x4000) != 0 )
        v12[1520344] = (double)v23 + v12[1520344] + 0.5;
      if ( (int)v10 < v9 )
      {
        v13 = v9 - v10;
        do
        {
          *v11 = v11[1];
          ++v11;
          --v13;
        }
        while ( v13 );
      }
      --v9;
      --v21;
      if ( v8 >= *(_DWORD *)(this + 1769952) )
        break;
      v4 = v21;
    }
  }
  *(_DWORD *)(this + 1769952) = v8;
  sub_449C00();
  result = *(_DWORD *)(this + 84);
  v22 = 0;
  if ( result > 0 )
  {
    v15 = (float *)((char *)unk_5CCAC8 + this);
    do
    {
      if ( (*(_DWORD *)v15 & 1) != 0 && (*(_DWORD *)v15 & 0x40) != 0 )
      {
        v16 = (__int64)v15[38] - get_track_cell_row_index(*((_DWORD **)v15 + 41));
        if ( v16 < 0 )
          v16 = 0;
        v17 = *((_DWORD **)v15 + 41);
        if ( *(_DWORD *)(v17[14] + 56) == 42 )
        {
          compute_kind42_attachment_transform(
            *(float *)(*(_DWORD *)(v17[14] + 88) + 168 * v16 + 160),
            v15[36],
            v15[37],
            (int)v24,
            (float *)&v23);
          v18 = v24[13];
          v15[36] = *(float *)&v24[12];
          *((_DWORD *)v15 + 37) = v18;
        }
        else
        {
          v19 = get_track_cell_row_index(v17);
          get_path_position_at_node(*(_DWORD **)(*((_DWORD *)v15 + 41) + 56), v15 + 36, v16, v19, v15 + 36);
        }
      }
      result = v22 + 1;
      v15 += 61;
      ++v22;
    }
    while ( v22 < *(_DWORD *)(this + 84) );
  }
  return result;
}

