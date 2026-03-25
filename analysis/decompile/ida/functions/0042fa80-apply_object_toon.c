/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_object_toon @ 0x42fa80 */
/* selector: apply_object_toon */

_BYTE *__thiscall sub_42FA80(_DWORD *this, int a2)
{
  int v3; // eax
  _BYTE *result; // eax

  v3 = *(this + 11);
  *(this + 4) |= a2 | 0x4001;
  *(this + 2) = allocate_tracked_memory(12 * v3, (int)aObjectToonVert);
  result = allocate_tracked_memory(24 * *(this + 21), (int)aObjectToonFace);
  *(this + 3) = result;
  return result;
}

