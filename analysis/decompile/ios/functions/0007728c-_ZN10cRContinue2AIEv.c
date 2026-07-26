/*
 * mangled: _ZN10cRContinue2AIEv
 * demangled: cRContinue::AI()
 * address: 0007728c
 * size: 472
 */

/* cRContinue::AI() */

void __thiscall cRContinue::AI(cRContinue *this)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;

  puVar1 = PTR__Game_001b60b8;
  iVar3 = *(int *)PTR__Game_001b60b8;
  if (*(float *)(iVar3 + 0x3c) != *(float *)(iVar3 + 0x44)) {
    cRBorderManager::KillBorders((cRBorderManager *)(iVar3 + 0xd14));
    Init(this);
  }
  uVar4 = *(uint *)(*(int *)this + 0x194);
  if ((uVar4 & 0x20) != 0) {
    *(uint *)(*(int *)this + 0x194) = uVar4 & 0xffffffdf;
    cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 10;
    *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
    *(undefined4 *)(*(int *)puVar1 + 0x72bd0) = 0;
    *(undefined4 *)(&DAT_00376620 + *(int *)puVar1) = 1;
    puVar2 = PTR__gConfig_001b60d4;
    iVar3 = *(int *)puVar1;
    if (*(int *)(&DAT_00364944 + iVar3) == 0) {
      iVar5 = *(int *)(PTR__gConfig_001b60d4 + 0xd8);
      *(int *)(PTR__gConfig_001b60d4 + 0xd8) = iVar5 + -1;
      *(int *)(iVar3 + 0x72bd4) = iVar5 + -1;
      *(undefined4 *)(puVar2 + 0xa4) = *(undefined4 *)(puVar2 + 0xd8);
      *(undefined4 *)(*(int *)puVar1 + 0x8228c) = *(undefined4 *)(puVar2 + 0xd0);
      *(undefined4 *)(*(int *)puVar1 + 0x85fac) = *(undefined4 *)(puVar2 + 0xd4);
      return;
    }
    if (*(int *)(&DAT_00364944 + iVar3) != 1) {
      return;
    }
    iVar5 = *(int *)(PTR__gConfig_001b60d4 + 0xdc);
    *(int *)(PTR__gConfig_001b60d4 + 0xdc) = iVar5 + -1;
    *(int *)(iVar3 + 0x72bd4) = iVar5 + -1;
    *(undefined4 *)(puVar2 + 0xec) = *(undefined4 *)(puVar2 + 0xdc);
    *(undefined4 *)(*(int *)puVar1 + 0x8228c) = *(undefined4 *)(puVar2 + 0xe0);
    *(undefined4 *)(*(int *)puVar1 + 0x85fac) = *(undefined4 *)(puVar2 + 0xe4);
    return;
  }
  uVar4 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar4 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar4 & 0xffffffdf;
    cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 0x23;
    *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
    return;
  }
  uVar4 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar4 & 0x20) == 0) {
    return;
  }
  *(uint *)(*(int *)(this + 8) + 0x194) = uVar4 & 0xffffffdf;
  cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(*(int *)puVar1 + 0x15c) = 2;
  *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
  return;
}
