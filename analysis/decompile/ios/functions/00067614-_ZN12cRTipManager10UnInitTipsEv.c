/*
 * mangled: _ZN12cRTipManager10UnInitTipsEv
 * demangled: cRTipManager::UnInitTips()
 * address: 00067614
 * size: 372
 */

/* cRTipManager::UnInitTips() */

void __thiscall cRTipManager::UnInitTips(cRTipManager *this)

{
  undefined *puVar1;
  int iVar2;

  puVar1 = PTR__Game_001b60b8;
  if (*(int *)(this + 0x2c) == 1) {
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    if (*(int *)(this + 0x3c) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    }
    if (*(int *)(this + 0x40) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    }
    *(undefined4 *)(this + 0x2c) = 0;
    iVar2 = *(int *)(this + 0x4c);
  }
  else {
    iVar2 = *(int *)(this + 0x4c);
  }
  puVar1 = PTR__Game_001b60b8;
  if (iVar2 == 1) {
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    if (*(int *)(this + 0x5c) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    }
    if (*(int *)(this + 0x60) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    }
    *(undefined4 *)(this + 0x4c) = 0;
    if (*(int *)(this + 0x6c) != 1) {
      return;
    }
  }
  else if (*(int *)(this + 0x6c) != 1) {
    return;
  }
  puVar1 = PTR__Game_001b60b8;
  cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  if (*(int *)(this + 0x7c) != 0) {
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  }
  if (*(int *)(this + 0x80) != 0) {
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  }
  *(undefined4 *)(this + 0x6c) = 0;
  return;
}
