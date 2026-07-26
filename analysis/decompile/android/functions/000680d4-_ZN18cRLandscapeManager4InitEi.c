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
  int iVar6;
  int *piVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;

  iVar8 = DAT_000681bc;
  iVar6 = DAT_000681b8 + 0x680ec;
  piVar7 = *(int **)(iVar6 + DAT_000681bc);
  iVar1 = *piVar7;
  if (*(int *)(iVar1 + 0x71900) != 7) {
    if (*(int *)(iVar1 + 0x71900) != 1) {
      bVar3 = (bool)((byte)*(undefined4 *)(*(int *)(iVar6 + DAT_000681c0) + 0xa4) & 1);
      goto LAB_00068120;
    }
    uVar2 = gRMathRand2();
    fVar9 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    if (fVar9 * DAT_000681b0 <= DAT_000681b4) {
      iVar1 = *piVar7;
      bVar3 = true;
      goto LAB_00068120;
    }
    iVar1 = *piVar7;
  }
  bVar3 = false;
LAB_00068120:
  fVar9 = (float)cRBackdrop::Change((cRBackdrop *)(iVar1 + 0x4d2e0),
                                    (cRLandscape *)(this + param_1 * 0x1ac + 4),bVar3);
  piVar7 = *(int **)(iVar6 + iVar8);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar7 + 0xd14),fVar9);
  uVar2 = *(undefined4 *)(this + param_1 * 0x1ac + 0x194);
  uVar4 = *(undefined4 *)(this + param_1 * 0x1ac + 0x198);
  uVar5 = *(undefined4 *)(this + param_1 * 0x1ac + 0x19c);
  iVar8 = *piVar7;
  *(undefined4 *)(iVar8 + 0x14) = *(undefined4 *)(this + param_1 * 0x1ac + 400);
  *(undefined4 *)(iVar8 + 0x18) = uVar2;
  *(undefined4 *)(iVar8 + 0x1c) = uVar4;
  *(undefined4 *)(iVar8 + 0x20) = uVar5;
  return;
}
