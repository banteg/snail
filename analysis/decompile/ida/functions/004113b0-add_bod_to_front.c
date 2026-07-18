/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_bod_to_front @ 0x4113b0 */
/* selector: add_bod_to_front */

// Intrusive BodList member that inserts an unlinked BodNode at the front and sets its linked flag, reporting an error if the node is already owned by a list.
void __thiscall add_bod_to_front(BodList *list, BodNode *node)
{
  BodNode *first; // eax
  uint32_t list_flags; // eax
  struct BodNode *list_prev; // eax

  if ( (node->list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    first = list->first;
    if ( first )
    {
      first->list_prev = node;
      list->first->list_prev->list_next = list->first;
      list_prev = list->first->list_prev;
      list->first = list_prev;
      list_prev->list_prev = nullptr;
    }
    else
    {
      list->first = node;
      node->list_prev = nullptr;
      list->first->list_next = nullptr;
    }
    list_flags = node->list_flags;
    BYTE1(list_flags) |= 2u;
    node->list_flags = list_flags;
  }
}
