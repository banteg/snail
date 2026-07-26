/*
 * mangled: _ZN6cRExit6UnInitEv
 * demangled: cRExit::UnInit()
 * address: 000624ec
 * size: 116
 */

/* cRExit::UnInit() */

void __thiscall cRExit::UnInit(cRExit *this)

{
  int *piVar1;

  piVar1 = *(int **)(DAT_00062560 + 0x624fc + DAT_00062564);
  cRBorderManager::Kill((cRBorderManager *)(*piVar1 + 0xd14),*(cRBorder **)(this + 0x10));
  cRBorderManager::Kill((cRBorderManager *)(*piVar1 + 0xd14),*(cRBorder **)(this + 0x14));
  cRBorderManager::Kill((cRBorderManager *)(*piVar1 + 0xd14),*(cRBorder **)(this + 0x18));
  cRBorderManager::UnHideBorders((cRBorderManager *)(*piVar1 + 0xd14));
  *(undefined4 *)(*piVar1 + 0x15c) = *(undefined4 *)(this + 8);
  return;
}
