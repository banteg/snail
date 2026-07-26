/*
 * mangled: _ZN8cRSplash6UnInitEv
 * demangled: cRSplash::UnInit()
 * address: 0006a8c0
 * size: 56
 */

/* cRSplash::UnInit() */

void __thiscall cRSplash::UnInit(cRSplash *this)

{
  int *piVar1;

  piVar1 = *(int **)(DAT_0006a8f8 + 0x6a8d0 + DAT_0006a8fc);
  cRBorderManager::Kill((cRBorderManager *)(*piVar1 + 0xd14),*(cRBorder **)(this + 8));
  *(undefined4 *)(*piVar1 + 0x15c) = 0xe;
  return;
}
