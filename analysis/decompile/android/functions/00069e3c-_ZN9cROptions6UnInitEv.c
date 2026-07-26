/*
 * mangled: _ZN9cROptions6UnInitEv
 * demangled: cROptions::UnInit()
 * address: 00069e3c
 * size: 152
 */

/* cROptions::UnInit() */

void __thiscall cROptions::UnInit(cROptions *this)

{
  int iVar1;
  int *piVar2;

  iVar1 = DAT_00069ed4 + 0x69e54;
  piVar2 = *(int **)(iVar1 + DAT_00069ed8);
  cRBorderManager::Kill((cRBorderManager *)(*piVar2 + 0xd14),*(cRBorder **)(this + 0x10));
  cRBorderManager::Kill((cRBorderManager *)(*piVar2 + 0xd14),*(cRBorder **)(this + 0x1c));
  cRBorderManager::Kill((cRBorderManager *)(*piVar2 + 0xd14),*(cRBorder **)(this + 0x18));
  cRBorderManager::Kill((cRBorderManager *)(*piVar2 + 0xd14),*(cRBorder **)(this + 0x14));
  cRBorderManager::Kill((cRBorderManager *)(*piVar2 + 0xd14),*(cRBorder **)(this + 0x20));
  gRegisterSaveFile((char *)(iVar1 + DAT_00069ee0),*(void **)(iVar1 + DAT_00069edc),0x130);
  return;
}
