/*
 * mangled: _ZN13cRSubRingStar6ShowerEP10cRSubGoldy
 * demangled: cRSubRingStar::Shower(cRSubGoldy*)
 * address: 0006de80
 * size: 268
 */

/* cRSubRingStar::Shower(cRSubGoldy*) */

void __thiscall cRSubRingStar::Shower(cRSubRingStar *this,cRSubGoldy *param_1)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  float extraout_s0;
  float extraout_s0_00;
  float fVar9;
  float fVar10;

  if ((gConfig._28_4_ & 0x10) != 0) {
    iVar1 = cRSpriteManager::New
                      ((int)&gRSpriteManager,*(int *)(param_1 + 0x370),
                       *(int *)(*(int *)(this + 4) + 0x1a0),-1);
    iVar7 = *(int *)this;
    *(undefined4 *)(iVar1 + 0x6c) = 0x3de38e39;
    *(undefined4 *)(iVar1 + 0x68) = 0;
    uVar2 = *(undefined4 *)(iVar7 + 0x2c);
    uVar5 = *(undefined4 *)(iVar7 + 0x30);
    uVar6 = *(undefined4 *)(iVar7 + 0x34);
    uVar8 = *(undefined4 *)(iVar7 + 0x38);
    *(undefined4 *)(iVar1 + 0x60) = 0x3ecccccd;
    *(undefined4 *)(iVar1 + 100) = 0x3e4ccccd;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
    *(undefined4 *)(iVar1 + 0x2c) = uVar2;
    *(undefined4 *)(iVar1 + 0x30) = uVar5;
    *(undefined4 *)(iVar1 + 0x34) = uVar6;
    *(undefined4 *)(iVar1 + 0x38) = uVar8;
    fVar9 = *(float *)(this + 0x1c);
    fVar3 = (float)Sin(extraout_s0);
    fVar10 = *(float *)(this + 0x1c);
    fVar4 = (float)Cos(extraout_s0_00);
    iVar7 = *(int *)this;
    *(undefined4 *)(iVar1 + 0x78) = 0;
    *(undefined4 *)(iVar1 + 0x5c) = 0;
    *(float *)(iVar1 + 0x54) = fVar9 * fVar3 * 0.3;
    uVar2 = *(undefined4 *)(iVar7 + 0x4c);
    uVar5 = *(undefined4 *)(iVar7 + 0x50);
    *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)(iVar7 + 0x48);
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    *(undefined4 *)(iVar1 + 0x50) = uVar5;
    *(float *)(iVar1 + 0x58) = fVar10 * fVar4 * 0.3;
  }
  return;
}
