/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_object_list @ 0x42f990 */
/* selector: initialize_object_list */

_BYTE *__thiscall sub_42F990(_DWORD *this, int a2)
{
  int v2; // esi
  _BYTE *result; // eax
  int v5; // ebx

  v2 = a2;
  *this = 0;
  *(this + 1) = a2;
  result = allocate_tracked_memory(220 * a2, (int)aObjectList);
  *(this + 2) = result;
  if ( a2 > 0 )
  {
    v5 = 0;
    do
    {
      result = (_BYTE *)initialize_object((_DWORD *)(*(this + 2) + v5));
      v5 += 220;
      --v2;
    }
    while ( v2 );
  }
  return result;
}

