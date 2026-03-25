/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_vapour @ 0x442500 */
/* selector: initialize_vapour */

char __thiscall sub_442500(_DWORD *this, int a2, int a3)
{
  int v4; // ecx
  int v5; // eax

  v4 = *(this + 9);
  *(this + 34) = a3;
  v5 = *(_DWORD *)(v4 + 84) + 1;
  *(this + 33) = v5;
  *(this + 36) = allocate_tracked_memory(v5 << 6, (int)aVapourTrail);
  return reset_vapour(this, 0);
}

