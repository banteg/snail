/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_jetpack_pickup @ 0x43d890 */
/* selector: spawn_track_jetpack_pickup */

// Allocates and seeds one live jetpack pickup from the active runtime row state. Cross-port Android and iOS symbols match this helper to `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`.
int __thiscall sub_43D890(char *this, int a2, int a3)
{
  __int64 v3; // rax
  char *v4; // esi
  float *v5; // ebx
  int v6; // eax
  double v7; // st7
  char *v8; // ecx
  char *v9; // eax
  int v10; // edx
  int v11; // edx
  int v12; // eax
  _DWORD *v13; // eax
  int v14; // ecx
  _DWORD *v15; // edx
  float v17; // [esp+Ch] [ebp-8h]
  int v18; // [esp+10h] [ebp-4h]

  v3 = (unsigned int)(this + 3497628);
  while ( *(_DWORD *)v3 )
  {
    ++HIDWORD(v3);
    LODWORD(v3) = v3 + 412;
    if ( SHIDWORD(v3) >= 1 )
      return v3;
  }
  v4 = this + 412 * HIDWORD(v3);
  *((_DWORD *)v4 + 874407) = 1;
  *((_DWORD *)v4 + 874408) = a3;
  v5 = (float *)(v4 + 3497588);
  v18 = *(_DWORD *)(a2 + 24);
  v17 = *(float *)(a2 + 20) + 1.5;
  *((_DWORD *)v4 + 874397) = *(_DWORD *)(a2 + 16);
  *((float *)v4 + 874398) = v17;
  *((_DWORD *)v4 + 874399) = v18;
  v6 = *(_DWORD *)(a2 + 64) & 7;
  if ( v6 == 3 && *(_BYTE *)(a2 - 24) == 14 && *(_BYTE *)(a2 + 228) == 14 )
  {
    v7 = *v5 + 0.5;
  }
  else
  {
    if ( v6 != 4 || *(_BYTE *)(a2 - 108) != 14 || *(_BYTE *)(a2 + 144) != 14 )
      goto LABEL_14;
    v7 = *v5 - 0.5;
  }
  *v5 = v7;
LABEL_14:
  v8 = v4 + 3497572;
  if ( (*((_DWORD *)v4 + 874394) & 0x200) != 0 )
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
      v11 = *(_DWORD *)(*(_DWORD *)v9 + 8);
      *(_DWORD *)v9 = v11;
      *(_DWORD *)(v11 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v9 = v8;
      *((_DWORD *)v4 + 874395) = 0;
      *(_DWORD *)(*(_DWORD *)v9 + 12) = 0;
    }
    v12 = *((_DWORD *)v4 + 874394);
    BYTE1(v12) |= 2u;
    *((_DWORD *)v4 + 874394) = v12;
  }
  v13 = allocate_sprite(unk_790F30, *(_DWORD *)(a3 + 896), 124, -1, -1);
  *((_DWORD *)v4 + 874418) = v13;
  v14 = v13[1];
  BYTE1(v14) |= 8u;
  v13[1] = v14;
  *(_DWORD *)(*((_DWORD *)v4 + 874418) + 120) = 0;
  *(_DWORD *)(*((_DWORD *)v4 + 874418) + 104) = 0;
  *(_DWORD *)(*((_DWORD *)v4 + 874418) + 108) = 0;
  *(_DWORD *)(*((_DWORD *)v4 + 874418) + 96) = 1069547520;
  *(_DWORD *)(*((_DWORD *)v4 + 874418) + 100) = 1069547520;
  v15 = (_DWORD *)(*((_DWORD *)v4 + 874418) + 72);
  *v15 = *(_DWORD *)v5;
  v15[1] = *((_DWORD *)v4 + 874398);
  v15[2] = *((_DWORD *)v4 + 874399);
  *((_DWORD *)v4 + 874419) = a2;
  *((_DWORD *)v4 + 874420) = 0;
  v3 = (__int64)*((float *)v4 + 874399);
  if ( (v3 & 1) != 0 )
    *((_DWORD *)v4 + 874420) = 0;
  else
    *((_DWORD *)v4 + 874420) = 1056964608;
  *((_DWORD *)v4 + 874421) = 1012010273;
  return v3;
}

