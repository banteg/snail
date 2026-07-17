/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_garbage_hazard @ 0x43f130 */
/* selector: destroy_garbage_hazard */

// Exact `SubGarbage` teardown: removes the inherited BOD from the live lists, kills its sprite, and unlinks it from the pool's borrowed active-chain head after collision or expiry. Android retains the authored member as `cRSubGarbage::Kill()`.
SubGarbage *__thiscall destroy_garbage_hazard(SubGarbage *sub_garbage)
{
  BodList *p_active_bod_list; // ecx
  uint32_t list_flags; // eax
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v6; // eax
  SubgameRuntime *owner_game; // ecx
  SubGarbage *result; // eax
  SubGarbage *next_active; // ecx

  sub_garbage->state = 0;
  p_active_bod_list = &g_game_base->active_bod_list;
  list_flags = sub_garbage->body.bod.bod.list_flags;
  if ( (list_flags & 0x200) != 0 )
  {
    if ( (list_flags & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      list_next = sub_garbage->body.bod.bod.list_next;
      if ( list_next )
        list_next->list_prev = sub_garbage->body.bod.bod.list_prev;
      list_prev = sub_garbage->body.bod.bod.list_prev;
      if ( list_prev )
        list_prev->list_next = sub_garbage->body.bod.bod.list_next;
      else
        p_active_bod_list->first = sub_garbage->body.bod.bod.list_next;
      sub_garbage->body.bod.bod.list_next = p_active_bod_list->free_top;
      p_active_bod_list->free_top = &sub_garbage->body.bod.bod;
      v6 = sub_garbage->body.bod.bod.list_flags;
      BYTE1(v6) &= ~2u;
      sub_garbage->body.bod.bod.list_flags = v6;
    }
  }
  else
  {
    report_errorf(aListRemove);
  }
  kill_sprite((int)sub_garbage->sprite);
  owner_game = sub_garbage->owner_game;
  result = owner_game->garbage_hazards.active_head;
  if ( result == sub_garbage )
  {
    result = sub_garbage->next_active;
    owner_game->garbage_hazards.active_head = result;
  }
  else if ( result )
  {
    while ( 1 )
    {
      next_active = result->next_active;
      if ( next_active == sub_garbage )
        break;
      result = result->next_active;
      if ( !next_active )
        return result;
    }
    result->next_active = sub_garbage->next_active;
    sub_garbage->next_active = nullptr;
  }
  return result;
}
