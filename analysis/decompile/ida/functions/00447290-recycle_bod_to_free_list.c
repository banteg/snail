/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: recycle_bod_to_free_list @ 0x447290 */
/* selector: recycle_bod_to_free_list */

// Exact emitted `cLinkedList<cRBod>::Remove` helper: unlinks one active BOD, moves it onto the shared free-list head, and diagnoses invalid ownership or active-iteration removal. The same owned `BodList` body is inlined by pickup AI teardown paths.
void __thiscall recycle_bod_to_free_list(BodList *list, BodNode *node)
{
  uint32_t list_flags; // edx
  struct BodNode *list_next; // edx
  struct BodNode *list_prev; // edx
  uint32_t v5; // ecx

  list_flags = node->list_flags;
  if ( (list_flags & 0x200) != 0 )
  {
    if ( (list_flags & 0x40) != 0 )
    {
      report_errorf(aListRemoveNext);
    }
    else
    {
      list_next = node->list_next;
      if ( list_next != nullptr )
        list_next->list_prev = node->list_prev;
      list_prev = node->list_prev;
      if ( list_prev != nullptr )
        list_prev->list_next = node->list_next;
      else
        list->first = node->list_next;
      node->list_next = list->free_top;
      list->free_top = node;
      v5 = node->list_flags;
      BYTE1(v5) &= ~2u;
      node->list_flags = v5;
    }
  }
  else
  {
    report_errorf(aListRemove);
  }
}
