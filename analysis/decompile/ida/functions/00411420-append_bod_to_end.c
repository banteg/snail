/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: append_bod_to_end @ 0x411420 */
/* selector: append_bod_to_end */

// Intrusive BodList member that walks to the tail and appends an unlinked BodNode, setting its linked flag or reporting an error for duplicate ownership.
void __thiscall append_bod_to_end(BodList *list, BodNode *node)
{
  BodNode *first; // eax
  uint32_t v3; // eax
  struct BodNode *i; // ecx
  uint32_t list_flags; // eax

  if ( (node->list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddend);
  }
  else
  {
    first = list->first;
    if ( first )
    {
      for ( i = first->list_next; i; i = i->list_next )
        first = i;
      first->list_next = node;
      node->list_prev = first;
      list_flags = node->list_flags;
      node->list_next = nullptr;
      BYTE1(list_flags) |= 2u;
      node->list_flags = list_flags;
    }
    else
    {
      list->first = node;
      node->list_prev = nullptr;
      list->first->list_next = nullptr;
      v3 = node->list_flags;
      BYTE1(v3) |= 2u;
      node->list_flags = v3;
    }
  }
}
