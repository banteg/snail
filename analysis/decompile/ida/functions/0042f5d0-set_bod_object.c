/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_bod_object @ 0x42f5d0 */
/* selector: set_bod_object */

int __thiscall sub_42F5D0(_DWORD *this, int a2)
{
  int result; // eax

  *(this + 9) = a2;
  result = *(this + 1);
  LOBYTE(result) = result | 2;
  *(this + 1) = result;
  return result;
}

