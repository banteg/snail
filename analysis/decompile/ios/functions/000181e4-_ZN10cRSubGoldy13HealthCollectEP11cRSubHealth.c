/*
 * mangled: _ZN10cRSubGoldy13HealthCollectEP11cRSubHealth
 * demangled: cRSubGoldy::HealthCollect(cRSubHealth*)
 * address: 000181e4
 * size: 400
 */

/* cRSubGoldy::HealthCollect(cRSubHealth*) */

void __thiscall cRSubGoldy::HealthCollect(cRSubGoldy *this,cRSubHealth *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint in_fpscr;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0) {
    iVar5 = 0;
    do {
      iVar1 = cRSpriteManager::New
                        ((int)PTR__gRSpriteManager_001b61e4,*(int *)(this + 0x370),0x74,-1);
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
      *(undefined4 *)(iVar1 + 0x68) = 0;
      *(undefined4 *)(iVar1 + 0x6c) = 0x3d2aaaab;
      *(undefined4 *)(iVar1 + 0x78) = 0xb951b717;
      tColour::tColour((tColour *)&local_38,1.0,0.75,0.75,1.0);
      fVar7 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = iVar5 + 1;
      *(undefined4 *)(iVar1 + 0x2c) = local_38;
      *(undefined4 *)(iVar1 + 0x30) = uStack_34;
      *(undefined4 *)(iVar1 + 0x34) = uStack_30;
      *(undefined4 *)(iVar1 + 0x38) = uStack_2c;
      *(undefined4 *)(iVar1 + 0x60) = 0x3dcccccd;
      *(undefined4 *)(iVar1 + 100) = 0x3f000000;
      iVar2 = *(int *)(param_1 + 0x58);
      fVar8 = fVar7 * 6.2831855 * 0.125;
      uVar3 = *(undefined4 *)(iVar2 + 0x4c);
      uVar4 = *(undefined4 *)(iVar2 + 0x50);
      *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)(iVar2 + 0x48);
      *(undefined4 *)(iVar1 + 0x4c) = uVar3;
      *(undefined4 *)(iVar1 + 0x50) = uVar4;
      fVar7 = (float)Sin(fVar8);
      fVar8 = (float)Cos(fVar8);
      *(float *)(iVar1 + 0x5c) = *(float *)(this + 0x408) * 0.4;
      fVar6 = *(float *)(this + 0x408);
      *(float *)(iVar1 + 0x58) = fVar8 * 0.015;
      fVar8 = *(float *)(this + 0x404);
      *(float *)(iVar1 + 0x54) = fVar7 * 0.015;
      *(float *)(iVar1 + 0x48) = *(float *)(iVar1 + 0x48) + *(float *)(this + 0x400) * 3.0;
      *(float *)(iVar1 + 0x4c) = *(float *)(iVar1 + 0x4c) + fVar8 * 3.0;
      *(float *)(iVar1 + 0x50) = *(float *)(iVar1 + 0x50) + fVar6 * 3.0;
    } while (iVar5 != 8);
  }
  return;
}
