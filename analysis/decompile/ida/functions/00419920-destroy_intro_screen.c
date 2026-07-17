/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_intro_screen @ 0x419920 */
/* selector: destroy_intro_screen */

// Exact void Windows cRLogo::UnInit(): unlinks each active LogoLetter from the BOD lists and returns it to the shared free list. Its sole caller discards the loop count left in EAX.
void __thiscall destroy_intro_screen(Logo *logo)
{
  int32_t v2; // edi
  struct BodNode **p_list_next; // esi
  int v4; // eax
  BodList *p_active_bod_list; // ecx
  int v6; // eax
  struct BodNode *v7; // eax

  g_runtime_config.render_flags = logo->saved_render_flags;
  if ( g_game_base->players[0].high_score_entry_pending == 1 )
    g_game_base->players[0].frontend_state = 20;
  else
    g_game_base->players[0].frontend_state = 3;
  v2 = 0;
  if ( logo->renderable_count > 0 )
  {
    p_list_next = &logo->letters[0].renderable.bod.bod.list_next;
    do
    {
      v4 = (int)*(p_list_next - 2);
      p_active_bod_list = &g_game_base->active_bod_list;
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
          v6 = (int)*(p_list_next - 1);
          if ( v6 )
            *(_DWORD *)(v6 + 12) = *p_list_next;
          else
            p_active_bod_list->first = *p_list_next;
          *p_list_next = p_active_bod_list->free_top;
          p_active_bod_list->free_top = (BodNode *)(p_list_next - 3);
          v7 = *(p_list_next - 2);
          BYTE1(v7) &= ~2u;
          *(p_list_next - 2) = v7;
        }
      }
      else
      {
        report_errorf(aListRemove);
      }
      ++v2;
      p_list_next += 36;
    }
    while ( v2 < logo->renderable_count );
  }
}
