/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: remove_track_render_cache_bods @ 0x433f20 */
/* selector: remove_track_render_cache_bods */

// Unlinks the cRSegmentCache owner’s fixed 143x5 BOD grid from the shared active-bod list during subgame teardown.
void __thiscall remove_track_render_cache_bods(SegmentCache *manager)
{
  struct BodNode **p_list_next; // esi
  int v2; // edi
  BodList *p_active_bod_list; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // [esp+10h] [ebp-4h]

  p_list_next = &manager->slots[0][0].bod.bod.list_next;
  v6 = 143;
  do
  {
    v2 = 5;
    do
    {
      if ( ((unsigned int)*(p_list_next - 2) & 0x200) != 0 )
      {
        p_active_bod_list = &g_game_base->active_bod_list;
        v4 = (int)*(p_list_next - 2);
        if ( (v4 & 0x200) != 0 )
        {
          if ( (v4 & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
          }
          else
          {
            if ( *p_list_next )
              (*p_list_next)->list_prev = *(p_list_next - 1);
            v5 = (int)*(p_list_next - 1);
            if ( v5 )
              *(_DWORD *)(v5 + 12) = *p_list_next;
            else
              p_active_bod_list->first = *p_list_next;
            *p_list_next = p_active_bod_list->free_top;
            p_active_bod_list->free_top = (BodNode *)(p_list_next - 3);
            *(p_list_next - 2) = (struct BodNode *)((unsigned int)*(p_list_next - 2) & 0xFFFFFDFF);
          }
        }
        else
        {
          report_errorf(aListRemove);
        }
      }
      p_list_next += 15;
      --v2;
    }
    while ( v2 );
    --v6;
  }
  while ( v6 );
}
