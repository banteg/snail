/*
 * mangled: _ZN13cRSubRingStar6ShowerEP10cRSubGoldy
 * demangled: cRSubRingStar::Shower(cRSubGoldy*)
 * address: 0006de80
 * size: 268
 */

/* cRSubRingStar::Shower(cRSubGoldy*) */

void __thiscall cRSubRingStar::Shower(cRSubRingStar *this,cRSubGoldy *param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 uVar10;
  float extraout_s0;
  float extraout_s0_00;
  float fVar11;
  float fVar12;

  uVar7 = DAT_0006df8c;
  if ((*(uint *)(*(int *)(DAT_0006dfa4 + 0x6de90 + DAT_0006dfa8) + 0x1c) & 0x10) != 0) {
    iVar2 = cRSpriteManager::New
                      (*(int *)(DAT_0006dfa4 + 0x6de90 + DAT_0006dfac),*(int *)(param_1 + 0x370),
                       *(int *)(*(int *)(this + 4) + 0x1a0),-1);
    iVar9 = *(int *)this;
    *(undefined4 *)(iVar2 + 0x6c) = DAT_0006df94;
    *(undefined4 *)(iVar2 + 0x68) = uVar7;
    uVar3 = *(undefined4 *)(iVar9 + 0x2c);
    uVar6 = *(undefined4 *)(iVar9 + 0x30);
    uVar8 = *(undefined4 *)(iVar9 + 0x34);
    uVar10 = *(undefined4 *)(iVar9 + 0x38);
    *(undefined4 *)(iVar2 + 0x60) = DAT_0006df98;
    *(undefined4 *)(iVar2 + 100) = DAT_0006df9c;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x800;
    *(undefined4 *)(iVar2 + 0x2c) = uVar3;
    *(undefined4 *)(iVar2 + 0x30) = uVar6;
    *(undefined4 *)(iVar2 + 0x34) = uVar8;
    *(undefined4 *)(iVar2 + 0x38) = uVar10;
    fVar11 = *(float *)(this + 0x1c);
    fVar4 = (float)Sin(extraout_s0);
    fVar12 = *(float *)(this + 0x1c);
    fVar5 = (float)Cos(extraout_s0_00);
    fVar1 = DAT_0006dfa0;
    iVar9 = *(int *)this;
    *(undefined4 *)(iVar2 + 0x78) = uVar7;
    *(undefined4 *)(iVar2 + 0x5c) = uVar7;
    *(float *)(iVar2 + 0x54) = fVar11 * fVar4 * fVar1;
    uVar7 = *(undefined4 *)(iVar9 + 0x4c);
    uVar3 = *(undefined4 *)(iVar9 + 0x50);
    *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(iVar9 + 0x48);
    *(undefined4 *)(iVar2 + 0x4c) = uVar7;
    *(undefined4 *)(iVar2 + 0x50) = uVar3;
    *(float *)(iVar2 + 0x58) = fVar12 * fVar5 * fVar1;
  }
  return;
}
