/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_vapour @ 0x442540 */
/* selector: reset_vapour */

char __thiscall sub_442540(_DWORD *this, int a2)
{
  int v2; // eax

  *(this + 32) = 0;
  *(this + 35) = a2;
  v2 = *(this + 1);
  LOBYTE(v2) = v2 & 0xDF;
  *(this + 1) = v2;
  return v2;
}

