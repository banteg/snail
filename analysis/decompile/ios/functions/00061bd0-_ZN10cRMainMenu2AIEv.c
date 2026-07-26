/*
 * mangled: _ZN10cRMainMenu2AIEv
 * demangled: cRMainMenu::AI()
 * address: 00061bd0
 * size: 468
 */

/* cRMainMenu::AI() */

void __thiscall cRMainMenu::AI(cRMainMenu *this)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;

  puVar1 = PTR__Game_001b60b8;
  iVar2 = *(int *)PTR__Game_001b60b8;
  if (*(float *)(iVar2 + 0x3c) != *(float *)(iVar2 + 0x44)) {
    cRBorderManager::KillBorders((cRBorderManager *)(iVar2 + 0xd14));
    cRSpriteManager::KillGame();
    Init(this);
  }
  uVar3 = *(uint *)(*(int *)this + 0x194);
  if ((uVar3 & 0x20) != 0) {
    *(uint *)(*(int *)this + 0x194) = uVar3 & 0xffffffdf;
    cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    cRSpriteManager::KillGame();
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 2;
    *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
    MacOFGetHighScore();
    return;
  }
  uVar3 = *(uint *)(*(int *)(this + 0xc) + 0x194);
  if ((uVar3 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0xc) + 0x194) = uVar3 & 0xffffffdf;
    cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    cRSpriteManager::KillGame();
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 0xe;
    *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
    return;
  }
  uVar3 = *(uint *)(*(int *)(this + 0x10) + 0x194);
  if ((uVar3 & 0x20) == 0) {
    if ((*(uint *)(*(int *)(this + 8) + 0x194) & 0x20) != 0) {
      cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
      cRSpriteManager::KillGame();
      *(uint *)(*(int *)(this + 8) + 0x194) = *(uint *)(*(int *)(this + 8) + 0x194) & 0xffffffdf;
      *(undefined1 *)(*(int *)puVar1 + 0x4e75c) = 1;
      *(undefined4 *)(*(int *)puVar1 + 0x4e758) = 4;
      *(undefined4 *)(*(int *)puVar1 + 0x15c) = 6;
      return;
    }
    uVar3 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar3 & 0x20) == 0) {
      return;
    }
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar3 & 0xffffffdf;
    cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    cRSpriteManager::KillGame();
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 0x12;
    *(undefined4 *)(&DAT_003782b0 + *(int *)puVar1) = 0;
    return;
  }
  *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar3 & 0xffffffdf;
  MacOFOpen();
  return;
}
