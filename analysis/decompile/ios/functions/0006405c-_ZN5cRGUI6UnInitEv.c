/*
 * mangled: _ZN5cRGUI6UnInitEv
 * demangled: cRGUI::UnInit()
 * address: 0006405c
 * size: 416
 */

/* cRGUI::UnInit() */

void __thiscall cRGUI::UnInit(cRGUI *this)

{
  undefined *puVar1;
  int iVar2;

  puVar1 = PTR__Game_001b60b8;
  iVar2 = *(int *)(*(int *)this + 0x58);
  if (iVar2 == 1) {
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    iVar2 = *(int *)puVar1;
  }
  else {
    if (iVar2 != 4) {
      if (iVar2 == 0) {
        cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
        cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
        cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
        cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
      }
      gRegisterSaveFile("ism.cfg",PTR__gConfig_001b60d4,0xf0);
      return;
    }
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    iVar2 = *(int *)puVar1;
  }
  cRBorderManager::Kill((cRBorder *)(iVar2 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  gRegisterSaveFile("ism.cfg",PTR__gConfig_001b60d4,0xf0);
  return;
}
