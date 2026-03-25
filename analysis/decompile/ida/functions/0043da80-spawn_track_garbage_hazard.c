/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_garbage_hazard @ 0x43da80 */
/* selector: spawn_track_garbage_hazard */

// Allocates and seeds one live garbage hazard from the active runtime row state. Cross-port Android and iOS symbols match this helper to `cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)`.
_DWORD *__thiscall sub_43DA80(_DWORD *this, int a2, int a3)
{
  int v3; // eax
  _DWORD *i; // ecx
  _DWORD *result; // eax
  float *v7; // esi
  _DWORD *v8; // ebp
  float *v9; // ebx
  float *v10; // edi
  char *v11; // eax
  __int64 v12; // rax
  _DWORD *v13; // eax
  int v14; // edx
  float v15; // [esp+Ch] [ebp-8h]
  int v16; // [esp+10h] [ebp-4h]

  v3 = 0;
  for ( i = this + 877682; *i; i += 49 )
  {
    if ( ++v3 >= 50 )
      return (_DWORD *)report_warningf(aRunOutOfGarbag);
  }
  v7 = (float *)(this + 49 * v3);
  v7[877681] = *((float *)this + 877648);
  v8 = v7 + 877649;
  *(this + 877648) = v7 + 877649;
  v9 = (float *)(this + 49 * v3 + 877688);
  *((_DWORD *)v7 + 877697) = a3;
  *v9 = (random_float_below(0.40000001) + 1.0) * 0.60000002;
  *((_DWORD *)v7 + 877682) = 1;
  set_matrix_identity((_DWORD *)v7 + 877663);
  v16 = *(_DWORD *)(a2 + 24);
  v15 = *v9 + *(float *)(a2 + 20);
  v7[877675] = *(float *)(a2 + 16);
  v7[877676] = v15;
  *((_DWORD *)v7 + 877677) = v16;
  project_position_onto_track_attachment(this, v7 + 877675, v7 + 877689);
  v10 = (float *)(this + 978393);
  v11 = (char *)MEMORY[0x4DF904] + 1448;
  if ( ((_DWORD)v7[877650] & 0x200) != 0 )
  {
    report_errorf(aListAddbefore);
  }
  else
  {
    *((_DWORD *)v7 + 877652) = v10;
    if ( *((float **)v11 + 1) == v10 )
    {
      *((_DWORD *)v10 + 2) = v8;
      *((_DWORD *)v11 + 1) = v8;
      v7[877651] = 0.0;
    }
    else
    {
      v7[877651] = v10[2];
      *((_DWORD *)v10 + 2) = v8;
      *(_DWORD *)(*((_DWORD *)v7 + 877651) + 12) = v8;
    }
    *((_DWORD *)v7 + 877650) |= 0x200u;
  }
  v12 = (__int64)((double)next_math_random_value() * -0.00012207031);
  v13 = allocate_sprite(unk_790F30, *(_DWORD *)(*((_DWORD *)v7 + 877697) + 896), 114 - v12, -1, -1);
  *((_DWORD *)v7 + 877694) = v13;
  v14 = v13[1];
  BYTE1(v14) |= 8u;
  v13[1] = v14;
  *(_DWORD *)(*((_DWORD *)v7 + 877694) + 120) = 0;
  *(_DWORD *)(*((_DWORD *)v7 + 877694) + 104) = 0;
  *(_DWORD *)(*((_DWORD *)v7 + 877694) + 108) = 0;
  *(float *)(*((_DWORD *)v7 + 877694) + 96) = *v9;
  *(float *)(*((_DWORD *)v7 + 877694) + 100) = *v9;
  result = (_DWORD *)(*((_DWORD *)v7 + 877694) + 72);
  *result = *((_DWORD *)v7 + 877675);
  result[1] = *((_DWORD *)v7 + 877676);
  result[2] = *((_DWORD *)v7 + 877677);
  *((_DWORD *)v7 + 877695) = a2;
  *((_BYTE *)v7 + 3510784) = 0;
  return result;
}

