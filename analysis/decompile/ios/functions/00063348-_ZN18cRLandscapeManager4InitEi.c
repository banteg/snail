/*
 * mangled: _ZN18cRLandscapeManager4InitEi
 * demangled: cRLandscapeManager::Init(int)
 * address: 00063348
 * size: 204
 */

/* cRLandscapeManager::Init(int) */

void __thiscall cRLandscapeManager::Init(cRLandscapeManager *this,int param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;

  if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) != 7) {
    if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) != 1) {
      bVar3 = (bool)((byte)*(undefined4 *)(PTR__gConfig_001b60d4 + 0xa4) & 1);
      goto LAB_0006338c;
    }
    uVar2 = gRMathRand2();
    fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    if (fVar8 * 3.0517578e-05 <= 0.5) {
      bVar3 = true;
      goto LAB_0006338c;
    }
  }
  bVar3 = false;
LAB_0006338c:
  puVar1 = PTR__Game_001b60b8;
  iVar7 = param_1 * 0x1ac;
  cRBackdrop::Change((cRBackdrop *)(*(int *)PTR__Game_001b60b8 + 0x4d2e0),
                     (cRLandscape *)(this + iVar7 + 4),bVar3);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar1 + 0xd14),0.0);
  iVar5 = *(int *)puVar1;
  uVar2 = *(undefined4 *)(this + iVar7 + 0x194);
  uVar4 = *(undefined4 *)(this + iVar7 + 0x198);
  uVar6 = *(undefined4 *)(this + iVar7 + 0x19c);
  *(undefined4 *)(iVar5 + 0x14) = *(undefined4 *)(this + iVar7 + 400);
  *(undefined4 *)(iVar5 + 0x18) = uVar2;
  *(undefined4 *)(iVar5 + 0x1c) = uVar4;
  *(undefined4 *)(iVar5 + 0x20) = uVar6;
  return;
}
