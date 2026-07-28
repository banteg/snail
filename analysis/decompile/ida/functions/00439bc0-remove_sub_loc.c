/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_sub_loc @ 0x439bc0 */
/* selector: remove_sub_loc */

// Windows `cRSubLoc::Remove()`: tears down one live cRSubLoc through the shared inlined `cLinkedList<cRBod>::Remove` owner, clearing `SubRow::attachment_body` for entry tiles when required and unlinking its four borrowed fringe BODs. Android preserves the authored name and the same Yi/row-body/own-body lifecycle; the Windows constructor table and both native callers independently confirm the owner.
void __thiscall remove_sub_loc(cRSubLoc *cell)
{
  int32_t track_cell_row_index; // eax
  SubLocTileId tile_id; // cl
  int32_t v4; // eax
  char flags; // cl
  GameRootRuntimeRowStrideAnchor *runtime_row_anchor; // eax
  uint32_t list_flags; // ecx
  BodBase *p_attachment_body; // eax
  BodList *p_active_bod_list; // edx
  struct BodNode *list_next; // ecx
  struct BodNode *list_prev; // ecx
  uint32_t v12; // eax
  BodList *v13; // ecx
  struct BodNode *v14; // eax
  struct BodNode *v15; // eax
  Fringe **p_fringe_front; // esi
  int i; // edi
  Fringe *v18; // eax
  BodList *v19; // edx
  uint32_t v20; // ecx
  struct BodNode *v21; // ecx
  struct BodNode *v22; // ecx

  track_cell_row_index = get_track_cell_row_index(cell);
  tile_id = cell->tile_id;
  if ( tile_id == SUBLOC_TILE_PATH_ENTRY_LOWERCASE || tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE )
  {
    v4 = track_cell_row_index;
    flags = g_game_base->subgame.runtime_rows[v4].flags;
    runtime_row_anchor = (GameRootRuntimeRowStrideAnchor *)(&g_game_base->vtable + v4 * 61);
    if ( (flags & 8) != 0 && (runtime_row_anchor->row.attachment_body.bod.list_flags & 0x200) != 0 )
    {
      list_flags = runtime_row_anchor->row.attachment_body.bod.list_flags;
      p_attachment_body = &runtime_row_anchor->row.attachment_body;
      p_active_bod_list = &g_game_base->active_bod_list;
      if ( (list_flags & 0x200) != 0 )
      {
        if ( (list_flags & 0x40) != 0 )
        {
          report_errorf(aListRemoveNext);
        }
        else
        {
          list_next = p_attachment_body->bod.list_next;
          if ( list_next != nullptr )
            list_next->list_prev = p_attachment_body->bod.list_prev;
          list_prev = p_attachment_body->bod.list_prev;
          if ( list_prev != nullptr )
            list_prev->list_next = p_attachment_body->bod.list_next;
          else
            p_active_bod_list->first = p_attachment_body->bod.list_next;
          p_attachment_body->bod.list_next = p_active_bod_list->free_top;
          p_active_bod_list->free_top = &p_attachment_body->bod;
          p_attachment_body->bod.list_flags &= ~0x200u;
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
    v13 = &g_game_base->active_bod_list;
    if ( (v12 & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      v14 = cell->bod.list_next;
      if ( v14 != nullptr )
        v14->list_prev = cell->bod.list_prev;
      v15 = cell->bod.list_prev;
      if ( v15 != nullptr )
        v15->list_next = cell->bod.list_next;
      else
        v13->first = cell->bod.list_next;
      cell->bod.list_next = v13->free_top;
      v13->free_top = &cell->bod;
      cell->bod.list_flags &= ~0x200u;
    }
  }
  p_fringe_front = &cell->fringe_front;
  for ( i = 4; i != 0; --i )
  {
    v18 = *p_fringe_front;
    if ( *p_fringe_front != nullptr && (v18->bod.bod.list_flags & 0x200) != 0 )
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
          if ( v21 != nullptr )
            v21->list_prev = v18->bod.bod.list_prev;
          v22 = v18->bod.bod.list_prev;
          if ( v22 != nullptr )
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
  }
}
