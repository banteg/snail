/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_border_init @ 0x401110 */
/* selector: unhide_border_init */

__int16 __thiscall sub_401110(_DWORD *this)
{
  int v1; // eax

  v1 = *(this + 104);
  *(this + 17) = 1065353216;
  BYTE1(v1) &= ~0x10u;
  *(this + 104) = v1;
  return v1;
}

