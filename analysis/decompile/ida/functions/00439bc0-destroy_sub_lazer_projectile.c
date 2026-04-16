/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_wall2_ambient_hazard @ 0x439bc0 */
/* selector: destroy_wall2_ambient_hazard */

// Unlinks one live `Wall2` ambient-hazard actor and its attached body objects from the shared intrusive lists before the slot returns to the inactive pool.
_DWORD *__thiscall sub_439BC0(int this)
{
  int v2; // eax
  char v3; // cl
  int v4; // eax
  char v5; // cl
  char *v6; // eax
  int v7; // ecx
  _DWORD *v8; // eax
  char *v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  char *v13; // ecx
  int v14; // eax
  int v15; // eax
  _DWORD *v16; // esi
  int v17; // edi
  _DWORD *result; // eax
  char *v19; // edx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx

  v2 = get_track_cell_row_index((_DWORD *)this);
  v3 = *(_BYTE *)(this + 60);
  if ( v3 == 29 || v3 == 30 )
  {
    v4 = 61 * v2;
    v5 = unk_6410E0[(_DWORD)MEMORY[0x4DF904] + 4 * v4];
    v6 = (char *)MEMORY[0x4DF904] + 4 * v4;
    if ( (v5 & 8) != 0 && (*(int *)((_BYTE *)&unk_641194 + (_DWORD)v6) & 0x200) != 0 )
    {
      v7 = *(int *)((char *)&unk_641194 + (_DWORD)v6);
      v8 = (_DWORD *)((char *)&unk_641190 + (_DWORD)v6);
      v9 = (char *)MEMORY[0x4DF904] + 1448;
      if ( (v7 & 0x200) != 0 )
      {
        if ( (v7 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          v10 = v8[3];
          if ( v10 )
            *(_DWORD *)(v10 + 8) = v8[2];
          v11 = v8[2];
          if ( v11 )
            *(_DWORD *)(v11 + 12) = v8[3];
          else
            *((_DWORD *)v9 + 1) = v8[3];
          v8[3] = *((_DWORD *)v9 + 2);
          *((_DWORD *)v9 + 2) = v8;
          v8[1] &= ~0x200u;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
  }
  v12 = *(_DWORD *)(this + 4);
  if ( (v12 & 0x200) != 0 )
  {
    v13 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v12 & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      v14 = *(_DWORD *)(this + 12);
      if ( v14 )
        *(_DWORD *)(v14 + 8) = *(_DWORD *)(this + 8);
      v15 = *(_DWORD *)(this + 8);
      if ( v15 )
        *(_DWORD *)(v15 + 12) = *(_DWORD *)(this + 12);
      else
        *((_DWORD *)v13 + 1) = *(_DWORD *)(this + 12);
      *(_DWORD *)(this + 12) = *((_DWORD *)v13 + 2);
      *((_DWORD *)v13 + 2) = this;
      *(_DWORD *)(this + 4) &= ~0x200u;
    }
  }
  v16 = (_DWORD *)(this + 68);
  v17 = 4;
  do
  {
    result = (_DWORD *)*v16;
    if ( *v16 && (result[1] & 0x200) != 0 )
    {
      v19 = (char *)MEMORY[0x4DF904] + 1448;
      v20 = result[1];
      if ( (v20 & 0x200) != 0 )
      {
        if ( (v20 & 0x40) != 0 )
        {
          result = (_DWORD *)report_errorf(aListRemoveNext);
        }
        else
        {
          v21 = result[3];
          if ( v21 )
            *(_DWORD *)(v21 + 8) = result[2];
          v22 = result[2];
          if ( v22 )
            *(_DWORD *)(v22 + 12) = result[3];
          else
            *((_DWORD *)v19 + 1) = result[3];
          result[3] = *((_DWORD *)v19 + 2);
          *((_DWORD *)v19 + 2) = result;
          result[1] &= ~0x200u;
        }
      }
      else
      {
        result = (_DWORD *)report_errorf(aListRemove);
      }
    }
    ++v16;
    --v17;
  }
  while ( v17 );
  return result;
}

