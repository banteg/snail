/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_duplicate_vertices @ 0x419f50 */
/* selector: initialize_duplicate_vertices */

_BYTE *__thiscall sub_419F50(_DWORD *this, int a2)
{
  _BYTE *result; // eax

  *this = 0;
  result = allocate_tracked_memory(10 * a2, (int)aDuplicateVerti);
  *(this + 1) = result;
  return result;
}

