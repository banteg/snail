/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: deactivate_sub_lazer_projectile @ 0x441740 */
/* selector: deactivate_sub_lazer_projectile */

// Exact void Windows `cRSubLazer::Kill()`: marks one SubLazer inactive and unlinks its inherited BOD node through GameRoot's active/free list after collision or path exit. Android preserves the authored method name; its apparent result is only the list-removal call value left in the return register.
void __thiscall deactivate_sub_lazer_projectile(SubLazer *sub_lazer)
{
  BodList *p_active_bod_list; // ecx
  uint32_t list_flags; // eax
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v6; // eax

  p_active_bod_list = &g_game_base->active_bod_list;
  list_flags = sub_lazer->body.bod.bod.list_flags;
  if ( (list_flags & 0x200) != 0 )
  {
    if ( (list_flags & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
      sub_lazer->state = 0;
    }
    else
    {
      list_next = sub_lazer->body.bod.bod.list_next;
      if ( list_next )
        list_next->list_prev = sub_lazer->body.bod.bod.list_prev;
      list_prev = sub_lazer->body.bod.bod.list_prev;
      if ( list_prev )
        list_prev->list_next = sub_lazer->body.bod.bod.list_next;
      else
        p_active_bod_list->first = sub_lazer->body.bod.bod.list_next;
      sub_lazer->body.bod.bod.list_next = p_active_bod_list->free_top;
      p_active_bod_list->free_top = &sub_lazer->body.bod.bod;
      v6 = sub_lazer->body.bod.bod.list_flags;
      sub_lazer->state = 0;
      BYTE1(v6) &= ~2u;
      sub_lazer->body.bod.bod.list_flags = v6;
    }
  }
  else
  {
    report_errorf(aListRemove);
    sub_lazer->state = 0;
  }
}
