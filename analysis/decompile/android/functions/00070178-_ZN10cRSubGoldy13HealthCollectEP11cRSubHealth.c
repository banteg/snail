/*
 * mangled: _ZN10cRSubGoldy13HealthCollectEP11cRSubHealth
 * demangled: cRSubGoldy::HealthCollect(cRSubHealth*)
 * address: 00070178
 * size: 392
 */

/* cRSubGoldy::HealthCollect(cRSubHealth*) */

void __thiscall cRSubGoldy::HealthCollect(cRSubGoldy *this,cRSubHealth *param_1)

{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float extraout_s0;
  float fVar7;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar8;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;

  if ((gConfig._28_4_ & 0x10) != 0) {
    iVar5 = 0;
    do {
      iVar1 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(this + 0x370),0x74,-1);
      *(undefined4 *)(iVar1 + 0x68) = 0;
      *(undefined4 *)(iVar1 + 0x6c) = 0x3d2aaaab;
      *(undefined4 *)(iVar1 + 0x78) = 0xb951b717;
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
      fVar7 = (float)tColour::tColour((tColour *)&local_60,extraout_s0,extraout_s1,extraout_s2,
                                      extraout_s3);
      VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      iVar6 = *(int *)(param_1 + 0x58);
      *(undefined4 *)(iVar1 + 0x60) = 0x3dcccccd;
      *(undefined4 *)(iVar1 + 100) = 0x3f000000;
      iVar5 = iVar5 + 1;
      *(undefined4 *)(iVar1 + 0x2c) = local_60;
      *(undefined4 *)(iVar1 + 0x30) = uStack_5c;
      *(undefined4 *)(iVar1 + 0x34) = uStack_58;
      *(undefined4 *)(iVar1 + 0x38) = uStack_54;
      uVar3 = *(undefined4 *)(iVar6 + 0x4c);
      uVar4 = *(undefined4 *)(iVar6 + 0x50);
      *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)(iVar6 + 0x48);
      *(undefined4 *)(iVar1 + 0x4c) = uVar3;
      *(undefined4 *)(iVar1 + 0x50) = uVar4;
      fVar7 = (float)Sin(fVar7);
      fVar2 = (float)Cos(extraout_s0_00);
      fVar8 = *(float *)(this + 0x410);
      *(float *)(iVar1 + 0x54) = fVar7 * 0.015;
      fVar7 = *(float *)(this + 0x408);
      *(float *)(iVar1 + 0x50) = *(float *)(iVar1 + 0x50) + fVar8 * 3.0;
      *(float *)(iVar1 + 0x48) = *(float *)(iVar1 + 0x48) + fVar7 * 3.0;
      *(float *)(iVar1 + 0x58) = fVar2 * 0.015;
      *(float *)(iVar1 + 0x4c) = *(float *)(iVar1 + 0x4c) + *(float *)(this + 0x40c) * 3.0;
      *(float *)(iVar1 + 0x5c) = fVar8 * 0.4;
    } while (iVar5 != 8);
  }
  return;
}
