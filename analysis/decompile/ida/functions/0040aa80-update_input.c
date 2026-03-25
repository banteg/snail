/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input @ 0x40aa80 */
/* selector: update_input */

int __thiscall sub_40AA80(_DWORD *this)
{
  int result; // eax
  int v2; // edx

  result = *(this + 13);
  v2 = result ^ *(this + 3);
  *(this + 3) = result;
  *(this + 1) = result & v2;
  *(this + 4) = ~result;
  *(this + 13) = 0;
  *(this + 2) = v2 & ~result;
  return result;
}

