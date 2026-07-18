/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_sub_loc @ 0x439bc0 */
/* selector: remove_sub_loc */

// Windows `cRSubLoc::Remove()`: tears down one live SubLoc by removing its own BOD, clearing `SubRow::attachment_body` for entry tiles when required, and unlinking its four borrowed fringe BODs. Android preserves the authored name and the same Yi/row-body/own-body lifecycle; the Windows constructor table and both native callers independently confirm the owner.
void __thiscall remove_sub_loc(SubLoc *cell)
{
  int32_t track_cell_row_index; // eax
  uint8_t tile_id; // cl
  int v4; // eax
  char v5; // cl
  void **v6; // eax
  int v7; // ecx
  BodNode *v8; // eax
  BodList *p_active_bod_list; // edx
  struct BodNode *list_next; // ecx
  struct BodNode *list_prev; // ecx
  uint32_t list_flags; // eax
  BodList *v13; // ecx
  struct BodNode *v14; // eax
  struct BodNode *v15; // eax
  Fringe **p_fringe_front; // esi
  int v17; // edi
  Fringe *v18; // eax
  BodList *v19; // edx
  uint32_t v20; // ecx
  struct BodNode *v21; // ecx
  struct BodNode *v22; // ecx

  track_cell_row_index = get_track_cell_row_index(cell);
  tile_id = cell->tile_id;
  if ( tile_id == 29 || tile_id == 30 )
  {
    v4 = 61 * track_cell_row_index;
    v5 = unk_6410E0[(_DWORD)g_game_base + 4 * v4];
    v6 = &g_game_base->vtable + v4;
    if ( (v5 & 8) != 0 && (*(_DWORD *)((_BYTE *)&unk_641194 + (_DWORD)v6) & 0x200) != 0 )
    {
      v7 = *(_DWORD *)((char *)&unk_641194 + (_DWORD)v6);
      v8 = (BodNode *)((char *)&unk_641190 + (_DWORD)v6);
      p_active_bod_list = &g_game_base->active_bod_list;
      if ( (v7 & 0x200) != 0 )
      {
        if ( (v7 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          list_next = v8->list_next;
          if ( list_next )
            list_next->list_prev = v8->list_prev;
          list_prev = v8->list_prev;
          if ( list_prev )
            list_prev->list_next = v8->list_next;
          else
            p_active_bod_list->first = v8->list_next;
          v8->list_next = p_active_bod_list->free_top;
          p_active_bod_list->free_top = v8;
          v8->list_flags &= ~0x200u;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
  }
  list_flags = cell->bod.list_flags;
  if ( (list_flags & 0x200) != 0 )
  {
    v13 = &g_game_base->active_bod_list;
    if ( (list_flags & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      v14 = cell->bod.list_next;
      if ( v14 )
        v14->list_prev = cell->bod.list_prev;
      v15 = cell->bod.list_prev;
      if ( v15 )
        v15->list_next = cell->bod.list_next;
      else
        v13->first = cell->bod.list_next;
      cell->bod.list_next = v13->free_top;
      v13->free_top = &cell->bod;
      cell->bod.list_flags &= ~0x200u;
    }
  }
  p_fringe_front = &cell->fringe_front;
  v17 = 4;
  do
  {
    v18 = *p_fringe_front;
    if ( *p_fringe_front && (v18->bod.bod.list_flags & 0x200) != 0 )
    {
      v19 = &g_game_base->active_bod_list;
      v20 = v18->bod.bod.list_flags;
      if ( (v20 & 0x200) != 0 )
      {
        if ( (v20 & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          v21 = v18->bod.bod.list_next;
          if ( v21 )
            v21->list_prev = v18->bod.bod.list_prev;
          v22 = v18->bod.bod.list_prev;
          if ( v22 )
            v22->list_next = v18->bod.bod.list_next;
          else
            v19->first = v18->bod.bod.list_next;
          v18->bod.bod.list_next = v19->free_top;
          v19->free_top = &v18->bod.bod;
          v18->bod.bod.list_flags &= ~0x200u;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    ++p_fringe_front;
    --v17;
  }
  while ( v17 );
}
