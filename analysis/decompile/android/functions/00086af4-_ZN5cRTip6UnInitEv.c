/*
 * mangled: _ZN5cRTip6UnInitEv
 * demangled: cRTip::UnInit()
 * address: 00086af4
 * size: 116
 */

/* cRTip::UnInit() */

void __thiscall cRTip::UnInit(cRTip *this)

{
  int iVar1;
  int iVar2;
  int *piVar3;

  iVar1 = DAT_00086b6c;
  iVar2 = DAT_00086b68 + 0x86b0c;
  piVar3 = *(int **)(iVar2 + DAT_00086b6c);
  cRBorderManager::Kill((cRBorderManager *)(*piVar3 + 0xd14),*(cRBorder **)(this + 0xc));
  if (*(cRBorder **)(this + 0x10) != (cRBorder *)0x0) {
    cRBorderManager::Kill((cRBorderManager *)(*piVar3 + 0xd14),*(cRBorder **)(this + 0x10));
  }
  if (*(cRBorder **)(this + 0x14) != (cRBorder *)0x0) {
    cRBorderManager::Kill
              ((cRBorderManager *)(**(int **)(iVar2 + iVar1) + 0xd14),*(cRBorder **)(this + 0x14));
  }
  *(undefined4 *)this = 0;
  return;
}
