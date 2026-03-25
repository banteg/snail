/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_object_to_list @ 0x42fad0 */
/* selector: add_object_to_list */

_DWORD *__thiscall sub_42FAD0(_DWORD *this)
{
  int v2; // ecx
  _DWORD *v3; // edi

  if ( *this == *(this + 1) )
    report_errorf(aTooManyObjects);
  v2 = 11 * (*this)++;
  v3 = (_DWORD *)(*(this + 2) + 20 * v2);
  initialize_object(v3);
  return v3;
}

