/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_blink_random @ 0x4408a0 */
/* selector: advance_blink_random */

double __thiscall sub_4408A0(float *this)
{
  int v1; // edx

  v1 = (*((_DWORD *)this + 978368) + 1) % 24;
  *((_DWORD *)this + 978368) = v1;
  return *(this + v1 + 978369);
}

