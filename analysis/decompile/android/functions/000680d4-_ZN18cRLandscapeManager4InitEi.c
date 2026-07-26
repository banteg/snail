/*
 * mangled: _ZN18cRLandscapeManager4InitEi
 * demangled: cRLandscapeManager::Init(int)
 * address: 000680d4
 * size: 220
 */

/* cRLandscapeManager::Init(int) */

void __thiscall cRLandscapeManager::Init(cRLandscapeManager *this,int param_1)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint in_fpscr;
  float fVar6;

  if (*(int *)(Game + 0x71900) != 7) {
    if (*(int *)(Game + 0x71900) != 1) {
      bVar3 = (bool)((byte)gConfig._164_4_ & 1);
      goto LAB_00068120;
    }
    uVar2 = gRMathRand2();
    fVar6 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    if (fVar6 * 3.0517578e-05 <= 0.5) {
      bVar3 = true;
      goto LAB_00068120;
    }
  }
  bVar3 = false;
LAB_00068120:
  fVar6 = (float)cRBackdrop::Change((cRBackdrop *)(Game + 0x4d2e0),
                                    (cRLandscape *)(this + param_1 * 0x1ac + 4),bVar3);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar6);
  iVar1 = Game;
  uVar2 = *(undefined4 *)(this + param_1 * 0x1ac + 0x194);
  uVar4 = *(undefined4 *)(this + param_1 * 0x1ac + 0x198);
  uVar5 = *(undefined4 *)(this + param_1 * 0x1ac + 0x19c);
  *(undefined4 *)(Game + 0x14) = *(undefined4 *)(this + param_1 * 0x1ac + 400);
  *(undefined4 *)(iVar1 + 0x18) = uVar2;
  *(undefined4 *)(iVar1 + 0x1c) = uVar4;
  *(undefined4 *)(iVar1 + 0x20) = uVar5;
  return;
}
