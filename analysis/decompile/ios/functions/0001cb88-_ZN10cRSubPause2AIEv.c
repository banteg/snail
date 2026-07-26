/*
 * mangled: _ZN10cRSubPause2AIEv
 * demangled: cRSubPause::AI()
 * address: 0001cb88
 * size: 460
 */

/* cRSubPause::AI() */

void __thiscall cRSubPause::AI(cRSubPause *this)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;

  uVar3 = *(uint *)(*(int *)this + 0x194);
  if ((uVar3 & 0x20) != 0) {
    *(uint *)(*(int *)this + 0x194) = uVar3 & 0xffffffdf;
    puVar1 = PTR__Game_001b60b8;
    *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x4e75c) = 0;
    *(undefined4 *)(*(int *)puVar1 + 0x4e758) = *(undefined4 *)(*(int *)puVar1 + 0x15c);
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 6;
    *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
    cRBorder::HideInit(*(cRBorder **)(this + 8));
    cRBorder::HideInit(*(cRBorder **)this);
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    return;
  }
  cRBorder::UnHideInit(*(cRBorder **)(this + 8));
  cRBorder::UnHideInit(*(cRBorder **)this);
  cRBorder::UnHideInit(*(cRBorder **)(this + 4));
  uVar3 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar3 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 8) + 0x194) = uVar3 & 0xffffffdf;
    puVar1 = PTR__Game_001b60b8;
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRMouse::SetInActive((cRMouse *)(*(int *)puVar1 + 0x228));
    *(undefined4 *)(*(int *)puVar1 + 0x72bcc) = 2;
    *(undefined1 *)(*(int *)puVar1 + 0x72b89) = 1;
    return;
  }
  uVar3 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar3 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar3 & 0xffffffdf;
    puVar1 = PTR__Game_001b60b8;
    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x4e788) =
         *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c);
    iVar2 = *(int *)puVar1;
    if (*(int *)(iVar2 + 0x72bd0) == 7) {
      *(undefined4 *)(iVar2 + 0x4e780) = 7;
    }
    else if ((&DAT_00353545)[iVar2] == '\0') {
      *(undefined4 *)(iVar2 + 0x4e780) = 2;
    }
    else {
      *(undefined4 *)(iVar2 + 0x4e780) = 3;
    }
    puVar1 = PTR__Game_001b60b8;
    *(undefined4 *)(&DAT_00376620 + *(int *)PTR__Game_001b60b8) = 2;
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 8;
    return;
  }
  return;
}
