/*
 * mangled: _ZN10cRSubPause6UnInitEv
 * demangled: cRSubPause::UnInit()
 * address: 000771f4
 * size: 100
 */

/* cRSubPause::UnInit() */

void __thiscall cRSubPause::UnInit(cRSubPause *this)

{
  int *piVar1;

  piVar1 = *(int **)(DAT_00077258 + 0x77204 + DAT_0007725c);
  cRBorderManager::Kill((cRBorderManager *)(*piVar1 + 0xd14),*(cRBorder **)this);
  cRBorderManager::Kill((cRBorderManager *)(*piVar1 + 0xd14),*(cRBorder **)(this + 4));
  cRBorderManager::Kill((cRBorderManager *)(*piVar1 + 0xd14),*(cRBorder **)(this + 8));
  cRMouse::SetInActive((cRMouse *)(*piVar1 + 0x228));
  return;
}
