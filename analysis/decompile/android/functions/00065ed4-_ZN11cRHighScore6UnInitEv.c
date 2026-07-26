/*
 * mangled: _ZN11cRHighScore6UnInitEv
 * demangled: cRHighScore::UnInit()
 * address: 00065ed4
 * size: 88
 */

/* cRHighScore::UnInit() */

void __thiscall cRHighScore::UnInit(cRHighScore *this)

{
  int iVar1;
  int *piVar2;
  float fVar3;

  piVar2 = *(int **)(DAT_00065f2c + 0x65ee4 + DAT_00065f30);
  iVar1 = *piVar2;
  *(undefined4 *)(*(int *)(DAT_00065f2c + 0x65ee4 + DAT_00065f34) + 0xa8) =
       *(undefined4 *)(this + 8);
  fVar3 = (float)cRBorderManager::KillBorders((cRBorderManager *)(iVar1 + 0xd14));
  iVar1 = *piVar2;
  *(undefined4 *)(iVar1 + 0x2c4) = 0;
  *(undefined1 *)(iVar1 + 0x2c1) = 0;
  cRBackdrop::SetZoom((cRBackdrop *)(iVar1 + 0x4d2e0),fVar3);
  return;
}
