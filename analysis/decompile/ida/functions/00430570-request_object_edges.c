/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_edges @ 0x430570 */
/* selector: request_object_edges */

_BYTE *__thiscall sub_430570(_DWORD *this, int a2)
{
  _BYTE *result; // eax

  result = (_BYTE *)*(this + 28);
  if ( !result )
  {
    *(this + 28) = a2;
    result = allocate_tracked_memory(36 * a2, (int)aObjectEdges);
    *(this + 29) = result;
  }
  return result;
}

