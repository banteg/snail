/*
 * mangled: _ZN6cRSalt5SmokeER7tVector
 * demangled: cRSalt::Smoke(tVector&)
 * address: 0006f8d8
 * size: 272
 */

/* cRSalt::Smoke(tVector&) */

void __thiscall cRSalt::Smoke(cRSalt *this,tVector *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar5;
  float fVar6;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  if ((gConfig._28_4_ & 0x10) != 0) {
    iVar1 = cRSpriteManager::New((int)&gRSpriteManager,1,0x13,-1);
    iVar4 = *(int *)(this + 0x7c);
    *(undefined4 *)(iVar1 + 0x68) = 0;
    fVar5 = *(float *)(iVar4 + 0x54);
    *(undefined4 *)(iVar1 + 0x70) = 0;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
    *(float *)(iVar1 + 0x6c) = fVar5 * 0.008333334;
    *(float *)(iVar1 + 0x74) = fVar5 * 0.4166667;
    tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar4 = *(int *)(this + 0x7c);
    *(undefined4 *)(iVar1 + 0x60) = 0x3e99999a;
    *(undefined4 *)(iVar1 + 100) = 0x3fa66666;
    *(undefined4 *)(iVar1 + 0x2c) = local_30;
    *(undefined4 *)(iVar1 + 0x30) = uStack_2c;
    *(undefined4 *)(iVar1 + 0x34) = uStack_28;
    *(undefined4 *)(iVar1 + 0x38) = uStack_24;
    fVar5 = *(float *)(iVar4 + 0x54);
    *(undefined4 *)(iVar1 + 0x78) = 0;
    fVar6 = fVar5 * 0.0;
    *(float *)(iVar1 + 0x58) = fVar5 * 0.02;
    *(float *)(iVar1 + 0x54) = fVar6;
    *(float *)(iVar1 + 0x5c) = fVar6;
    uVar2 = *(undefined4 *)(param_1 + 4);
    uVar3 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)param_1;
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    *(undefined4 *)(iVar1 + 0x50) = uVar3;
    *(float *)(iVar1 + 0x4c) = *(float *)(iVar1 + 0x4c) + 1.0;
  }
  return;
}
