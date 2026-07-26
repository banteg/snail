/*
 * mangled: _ZN9cRSubGolb5SmokeE7tVector
 * demangled: cRSubGolb::Smoke(tVector)
 * address: 00062c08
 * size: 260
 */

/* cRSubGolb::Smoke(tVector) */

void cRSubGolb::Smoke(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  iVar1 = cRSpriteManager::New
                    ((int)&gRSpriteManager,*(int *)(*(int *)(param_1 + 600) + 0x370),0x74,-1);
  iVar2 = *(int *)(param_1 + 0x250);
  *(undefined4 *)(iVar1 + 0x68) = 0;
  fVar5 = *(float *)(iVar2 + 0x54);
  *(undefined4 *)(iVar1 + 0x70) = 0;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
  *(float *)(iVar1 + 0x6c) = fVar5 * 0.16666667;
  *(float *)(iVar1 + 0x74) = fVar5 * 0.4166667;
  tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  *(undefined4 *)(iVar1 + 0x60) = 0x3dcccccd;
  *(undefined4 *)(iVar1 + 100) = 0x3f000000;
  *(undefined4 *)(iVar1 + 0x2c) = local_30;
  *(undefined4 *)(iVar1 + 0x30) = uStack_2c;
  *(undefined4 *)(iVar1 + 0x34) = uStack_28;
  *(undefined4 *)(iVar1 + 0x38) = uStack_24;
  fVar3 = *(float *)(param_1 + 0x234);
  fVar5 = *(float *)(param_1 + 0x230);
  fVar4 = *(float *)(param_1 + 0x22c);
  *(undefined4 *)(iVar1 + 0x78) = 0;
  *(float *)(iVar1 + 0x5c) = fVar3 * 0.4;
  *(float *)(iVar1 + 0x54) = fVar4 * 0.4;
  *(float *)(iVar1 + 0x58) = fVar5 * 0.4;
  *(undefined4 *)(iVar1 + 0x48) = param_2;
  *(undefined4 *)(iVar1 + 0x4c) = param_3;
  *(undefined4 *)(iVar1 + 0x50) = param_4;
  return;
}
