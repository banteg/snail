/*
 * mangled: _ZN6cRSalt5SmokeER7tVector
 * demangled: cRSalt::Smoke(tVector&)
 * address: 0006f8d8
 * size: 272
 */

/* cRSalt::Smoke(tVector&) */

void __thiscall cRSalt::Smoke(cRSalt *this,tVector *param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  fVar1 = DAT_0006f9ec;
  fVar9 = DAT_0006f9e8;
  if ((*(uint *)(*(int *)(DAT_0006fa04 + 0x6f8e8 + DAT_0006fa08) + 0x1c) & 0x10) != 0) {
    iVar3 = cRSpriteManager::New(*(int *)(DAT_0006fa04 + 0x6f8e8 + DAT_0006fa0c),1,0x13,-1);
    fVar8 = DAT_0006f9f4;
    fVar2 = DAT_0006f9f0;
    iVar6 = *(int *)(this + 0x7c);
    *(float *)(iVar3 + 0x68) = fVar9;
    fVar7 = *(float *)(iVar6 + 0x54);
    *(float *)(iVar3 + 0x70) = fVar9;
    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x800;
    *(float *)(iVar3 + 0x6c) = fVar7 * fVar8;
    *(float *)(iVar3 + 0x74) = fVar7 * fVar2;
    tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar6 = *(int *)(this + 0x7c);
    *(undefined4 *)(iVar3 + 0x60) = DAT_0006f9f8;
    fVar2 = DAT_0006f9fc;
    *(undefined4 *)(iVar3 + 100) = DAT_0006fa00;
    *(undefined4 *)(iVar3 + 0x2c) = local_30;
    *(undefined4 *)(iVar3 + 0x30) = uStack_2c;
    *(undefined4 *)(iVar3 + 0x34) = uStack_28;
    *(undefined4 *)(iVar3 + 0x38) = uStack_24;
    fVar8 = *(float *)(iVar6 + 0x54);
    *(float *)(iVar3 + 0x78) = fVar9;
    fVar9 = fVar8 * fVar9;
    *(float *)(iVar3 + 0x58) = fVar8 * fVar2;
    *(float *)(iVar3 + 0x54) = fVar9;
    *(float *)(iVar3 + 0x5c) = fVar9;
    uVar4 = *(undefined4 *)(param_1 + 4);
    uVar5 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)param_1;
    *(undefined4 *)(iVar3 + 0x4c) = uVar4;
    *(undefined4 *)(iVar3 + 0x50) = uVar5;
    *(float *)(iVar3 + 0x4c) = *(float *)(iVar3 + 0x4c) + fVar1;
  }
  return;
}
