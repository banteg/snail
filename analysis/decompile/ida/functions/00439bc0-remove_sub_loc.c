/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_sub_loc @ 0x439bc0 */
/* selector: remove_sub_loc */

// Unlinks the BOD nodes owned by a live TrackRowCell/fringe runtime entry. Tile
// 29/30 rows also clear the row-colour BOD record before the cell and its four
// directional fringe objects return to the shared free list.
// The raw IDA text still infers an incidental pointer return; the canonical
// cRSubLoc::Remove contract is the void thiscall recorded in the type sync.
_DWORD *__thiscall remove_sub_loc(TrackRowCell *cell)
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

  v2 = get_track_cell_row_index(cell);
  v3 = cell->tile_id;
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
  v12 = cell->bod.list_flags;
  if ( (v12 & 0x200) != 0 )
  {
    v13 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v12 & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      v14 = (int)cell->bod.list_next;
      if ( v14 )
        *(_DWORD *)(v14 + 8) = cell->bod.list_prev;
      v15 = (int)cell->bod.list_prev;
      if ( v15 )
        *(_DWORD *)(v15 + 12) = cell->bod.list_next;
      else
        *((_DWORD *)v13 + 1) = cell->bod.list_next;
      cell->bod.list_next = (BodNode *)*((_DWORD *)v13 + 2);
      *((_DWORD *)v13 + 2) = cell;
      cell->bod.list_flags &= ~0x200u;
    }
  }
  v16 = (_DWORD *)&cell->fringe_front;
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
