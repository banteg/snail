/*
 * mangled: _ZN6cRSure2AIEv
 * demangled: cRSure::AI()
 * address: 00077724
 * size: 300
 */

/* cRSure::AI() */

void __thiscall cRSure::AI(cRSure *this)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;

  puVar1 = PTR__Game_001b60b8;
  iVar3 = *(int *)PTR__Game_001b60b8;
  if (*(float *)(iVar3 + 0x3c) != *(float *)(iVar3 + 0x44)) {
    cRBorderManager::KillBorders((cRBorderManager *)(iVar3 + 0xd14));
    Init(this);
  }
  uVar4 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar4 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar4 & 0xffffffdf;
    puVar2 = PTR__gConfig_001b60d4;
    iVar3 = *(int *)puVar1;
    *(undefined4 *)(PTR__gConfig_001b60d4 + 0xcc) = 0;
    if (*(int *)(&DAT_00364944 + iVar3) == 0) {
      *(undefined4 *)(puVar2 + 0xa4) = 1;
    }
    else if (*(int *)(&DAT_00364944 + iVar3) == 1) {
      *(undefined4 *)(puVar2 + 0xec) = 1;
    }
    cRBorderManager::KillBorders((cRBorderManager *)(iVar3 + 0xd14));
    puVar1 = PTR__Game_001b60b8;
    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 10;
    *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
    *(undefined4 *)(*(int *)puVar1 + 0x72bd0) = 0;
    *(undefined4 *)(&DAT_00376620 + *(int *)puVar1) = 2;
    return;
  }
  uVar4 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar4 & 0x20) == 0) {
    return;
  }
  *(uint *)(*(int *)(this + 8) + 0x194) = uVar4 & 0xffffffdf;
  cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(*(int *)puVar1 + 0x15c) = 0x21;
  *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
  return;
}
