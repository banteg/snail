/*
 * mangled: _ZN5cRGUI6UnInitEv
 * demangled: cRGUI::UnInit()
 * address: 00063fec
 * size: 396
 */

/* cRGUI::UnInit() */

void __thiscall cRGUI::UnInit(cRGUI *this)

{
  cRBorder *pcVar1;
  int iVar2;
  int iVar3;
  int *piVar4;

  iVar2 = *(int *)(*(int *)this + 0x60);
  iVar3 = DAT_00064178 + 0x64008;
  if (iVar2 == 1) {
    piVar4 = *(int **)(iVar3 + DAT_0006417c);
    cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0x10));
    cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0x18));
    cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0x1c));
    iVar2 = *piVar4;
    pcVar1 = *(cRBorder **)(this + 0x20);
  }
  else {
    if (iVar2 != 4) {
      if (iVar2 == 0) {
        piVar4 = *(int **)(iVar3 + DAT_0006417c);
        cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 4));
        cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 8));
        cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0xc));
        cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0x10));
        cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0x18));
      }
      goto LAB_00064088;
    }
    piVar4 = *(int **)(iVar3 + DAT_0006417c);
    cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 4));
    cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 8));
    cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0xc));
    cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0x10));
    iVar2 = *piVar4;
    pcVar1 = *(cRBorder **)(this + 0x18);
  }
  cRBorderManager::Kill((cRBorderManager *)(iVar2 + 0xd14),pcVar1);
  cRBorderManager::Kill((cRBorderManager *)(*piVar4 + 0xd14),*(cRBorder **)(this + 0x24));
LAB_00064088:
  gRegisterSaveFile((char *)(iVar3 + DAT_00064184),*(void **)(iVar3 + DAT_00064180),0x130);
  return;
}
