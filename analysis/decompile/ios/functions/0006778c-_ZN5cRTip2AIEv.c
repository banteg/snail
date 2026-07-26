/*
 * mangled: _ZN5cRTip2AIEv
 * demangled: cRTip::AI()
 * address: 0006778c
 * size: 492
 */

/* cRTip::AI() */

void __thiscall cRTip::AI(cRTip *this)

{
  undefined *puVar1;
  int iVar2;
  float fVar3;

  puVar1 = PTR__Game_001b60b8;
  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x72b8a) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 0xc));
    return;
  }
  cRBorder::UnHideInit(*(cRBorder **)(this + 0xc));
  iVar2 = *(int *)(this + 0x10);
  if ((iVar2 == 0) || ((*(uint *)(iVar2 + 0x194) & 0x20) == 0)) {
    iVar2 = *(int *)(this + 0x14);
    if ((iVar2 == 0) || ((*(uint *)(iVar2 + 0x194) & 0x20) == 0)) {
      if ((**(uint **)(this + 8) & 2) == 0) {
        return;
      }
      fVar3 = *(float *)(this + 0x18);
      *(float *)(this + 0x18) = fVar3 + *(float *)(this + 0x1c);
      puVar1 = PTR__Game_001b60b8;
      if (1.0 < fVar3 + *(float *)(this + 0x1c)) {
        cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        if (*(int *)(this + 0x10) != 0) {
          cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
        }
        if (*(int *)(this + 0x14) != 0) {
          cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
        }
        *(undefined4 *)this = 0;
        return;
      }
      return;
    }
    *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0xffffffdf;
    puVar1 = PTR__Game_001b60b8;
    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = *(undefined4 *)(this + 4);
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    if (*(int *)(this + 0x10) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    }
    if (*(int *)(this + 0x14) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    }
  }
  else {
    *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0xffffffdf;
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = *(undefined4 *)(this + 4);
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    if (*(int *)(this + 0x10) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    }
    if (*(int *)(this + 0x14) != 0) {
      cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    }
  }
  *(undefined4 *)this = 0;
  cRBorderManager::UnHideBorders();
  *(undefined4 *)this = 0;
  return;
}
