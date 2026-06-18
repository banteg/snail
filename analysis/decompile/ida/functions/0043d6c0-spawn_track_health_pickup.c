/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_health_pickup @ 0x43d6c0 */
/* selector: spawn_track_health_pickup */

// Allocates and seeds one live health pickup from the active runtime row state. Cross-port Android and iOS symbols match this helper to `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`.
_DWORD *__fastcall sub_43D6C0(int a1, int a2, int a3, int a4)
{
  int v4; // ebx
  _DWORD *result; // eax
  int v6; // ebp
  int v7; // esi
  int v8; // eax
  char *v9; // ecx
  int v10; // edx
  int v11; // edx
  int v12; // ecx
  _DWORD *v13; // eax
  int v14; // ecx
  _DWORD *v15; // ecx
  int v16; // ebx
  float v18; // [esp+Ch] [ebp-8h]
  int v19; // [esp+10h] [ebp-4h]

  v4 = 0;
  result = (_DWORD *)(a1 + 3498040);
  while ( *result )
  {
    ++v4;
    result += 29;
    if ( v4 >= 8 )
      return result;
  }
  v6 = a3;
  v7 = a1 + 116 * v4;
  *(_DWORD *)(v7 + 3498040) = 1;
  *(_DWORD *)(v7 + 3498044) = a4;
  v19 = *(_DWORD *)(a3 + 24);
  v18 = *(float *)(a3 + 20) + 0.60000002;
  *(_DWORD *)(v7 + 3498000) = *(_DWORD *)(a3 + 16);
  *(float *)(v7 + 3498004) = v18;
  *(_DWORD *)(v7 + 3498008) = v19;
  v8 = v7 + 3497984;
  if ( (*(_DWORD *)(v7 + 3497988) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v9 = (char *)MEMORY[0x4DF904] + 1452;
    v10 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v10 )
    {
      *(_DWORD *)(v10 + 8) = v8;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v9 + 8) + 12) = *(_DWORD *)v9;
      v6 = a3;
      v11 = *(_DWORD *)(*(_DWORD *)v9 + 8);
      *(_DWORD *)v9 = v11;
      *(_DWORD *)(v11 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v9 = v8;
      *(_DWORD *)(v7 + 3497992) = 0;
      *(_DWORD *)(*(_DWORD *)v9 + 12) = 0;
    }
    v12 = *(_DWORD *)(v7 + 3497988);
    BYTE1(v12) |= 2u;
    *(_DWORD *)(v7 + 3497988) = v12;
  }
  v13 = allocate_sprite(g_sprite_manager, *(_DWORD *)(a4 + 896), 57, -1, -1);
  *(_DWORD *)(v7 + 3498084) = v13;
  v14 = v13[1];
  BYTE1(v14) |= 8u;
  v13[1] = v14;
  *(_DWORD *)(*(_DWORD *)(v7 + 3498084) + 120) = 0;
  *(_DWORD *)(*(_DWORD *)(v7 + 3498084) + 104) = 0;
  *(_DWORD *)(*(_DWORD *)(v7 + 3498084) + 108) = 0;
  *(_DWORD *)(*(_DWORD *)(v7 + 3498084) + 96) = 1058642330;
  *(_DWORD *)(*(_DWORD *)(v7 + 3498084) + 100) = 1058642330;
  v15 = (_DWORD *)(*(_DWORD *)(v7 + 3498084) + 72);
  *v15 = *(_DWORD *)(v7 + 3498000);
  v15[1] = *(_DWORD *)(v7 + 3498004);
  v15[2] = *(_DWORD *)(v7 + 3498008);
  *(_DWORD *)(v7 + 3498088) = v6;
  *(_DWORD *)(v7 + 3498092) = 0;
  if ( ((__int64)*(float *)(v7 + 3498008) & 1) != 0 )
    *(_DWORD *)(v7 + 3498092) = 0;
  else
    *(_DWORD *)(v7 + 3498092) = 1056964608;
  v16 = v4 + 30156;
  *(_DWORD *)(a1 + 116 * v16) = 1012010273;
  return (_DWORD *)(7 * v16);
}

