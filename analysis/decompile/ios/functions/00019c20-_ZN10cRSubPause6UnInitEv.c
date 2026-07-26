/*
 * mangled: _ZN10cRSubPause6UnInitEv
 * demangled: cRSubPause::UnInit()
 * address: 00019c20
 * size: 88
 */

/* cRSubPause::UnInit() */

void cRSubPause::UnInit(void)

{
  undefined *puVar1;

  puVar1 = PTR__Game_001b60b8;
  cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRMouse::SetInActive((cRMouse *)(*(int *)puVar1 + 0x228));
  return;
}
