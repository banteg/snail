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

  iVar2 = *(int *)(*(int *)this + 0x60);
  if (iVar2 == 1) {
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x18));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x1c));
    pcVar1 = *(cRBorder **)(this + 0x20);
  }
  else {
    if (iVar2 != 4) {
      if (iVar2 == 0) {
        cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 4));
        cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 8));
        cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0xc));
        cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10));
        cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x18));
      }
      goto LAB_00064088;
    }
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 4));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 8));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0xc));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10));
    pcVar1 = *(cRBorder **)(this + 0x18);
  }
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),pcVar1);
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x24));
LAB_00064088:
  gRegisterSaveFile("asm.cfg",gConfig,0x130);
  return;
}
