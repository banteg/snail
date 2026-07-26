/*
 * mangled: _ZN8cRGalaxy6UnInitEv
 * demangled: cRGalaxy::UnInit()
 * address: 000686cc
 * size: 244
 */

/* cRGalaxy::UnInit() */

void __thiscall cRGalaxy::UnInit(cRGalaxy *this)

{
  undefined *puVar1;

  *(undefined4 *)this = 0;
  puVar1 = PTR__Game_001b60b8;
  cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  return;
}
