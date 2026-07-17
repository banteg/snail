/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_active_bod @ 0x433e80 */
/* selector: update_active_bod */

// Exact TrackRenderCacheSlot callback installed by initialize_active_bod: recycles one live cache BOD to the root free list once its cache-row base plus the native 24-unit span falls behind the current subgame cutoff.
void __thiscall update_active_bod(TrackRenderCacheSlot *slot)
{
  uint32_t list_flags; // eax
  BodList *p_active_bod_list; // edx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v5; // eax

  if ( slot->cache_row_base + 24.0 < g_game_base->subgame.player.interaction_max_z )
  {
    list_flags = slot->bod.bod.list_flags;
    p_active_bod_list = &g_game_base->active_bod_list;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        list_next = slot->bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = slot->bod.bod.list_prev;
        list_prev = slot->bod.bod.list_prev;
        if ( list_prev )
          list_prev->list_next = slot->bod.bod.list_next;
        else
          p_active_bod_list->first = slot->bod.bod.list_next;
        slot->bod.bod.list_next = p_active_bod_list->free_top;
        p_active_bod_list->free_top = &slot->bod.bod;
        v5 = slot->bod.bod.list_flags;
        BYTE1(v5) &= ~2u;
        slot->bod.bod.list_flags = v5;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
  }
}
