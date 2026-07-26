/*
 * mangled: _ZN9cROptions6UnInitEv
 * demangled: cROptions::UnInit()
 * address: 00061e2c
 * size: 128
 */

/* cROptions::UnInit() */

void cROptions::UnInit(void)

{
  undefined *puVar1;

  puVar1 = PTR__Game_001b60b8;
  cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  gRegisterSaveFile("ism.cfg",PTR__gConfig_001b60d4,0xf0);
  return;
}
