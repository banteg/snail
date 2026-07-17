/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: clear_active_landscape_entries @ 0x418a30 */
/* selector: clear_active_landscape_entries */

// Clears the active 10-slot landscape-entry runtime pool by zeroing each live slot state and unlinking it from the shared BOD active/free list. `destroy_subgame` uses it when the current landscape set is torn down.
void __thiscall clear_active_landscape_entries(LandscapeManager *manager)
{
  struct BodNode **p_list_next; // esi
  int v2; // ebp
  BodList *p_active_bod_list; // ecx
  int v4; // eax
  int v5; // eax
  struct BodNode *v6; // eax

  p_list_next = &manager->active_entries[0].bod.bod.bod.list_next;
  v2 = 10;
  do
  {
    if ( (((unsigned __int16)*(p_list_next - 2) >> 8) & 2) != 0 )
    {
      p_list_next[29] = nullptr;
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
          v6 = *(p_list_next - 2);
          BYTE1(v6) &= ~2u;
          *(p_list_next - 2) = v6;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
    }
    p_list_next += 36;
    --v2;
  }
  while ( v2 );
}
