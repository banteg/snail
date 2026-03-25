/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_barrier_ai @ 0x440f80 */
/* selector: update_barrier_ai */

int __thiscall sub_440F80(_DWORD *this)
{
  int result; // eax
  int v2; // edx

  result = *(this + 14);
  v2 = *(_DWORD *)(result + 112);
  *(this + 5) = 1053609165;
  *(this + 6) = v2;
  return result;
}

