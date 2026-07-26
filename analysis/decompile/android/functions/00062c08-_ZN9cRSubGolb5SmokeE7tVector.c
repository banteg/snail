/*
 * mangled: _ZN9cRSubGolb5SmokeE7tVector
 * demangled: cRSubGolb::Smoke(tVector)
 * address: 00062c08
 * size: 260
 */

/* cRSubGolb::Smoke(tVector) */

void cRSubGolb::Smoke(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  uVar1 = DAT_00062d0c;
  iVar3 = cRSpriteManager::New
                    (*(int *)(DAT_00062d24 + 0x62c34 + DAT_00062d28),
                     *(int *)(*(int *)(param_1 + 600) + 0x370),0x74,-1);
  fVar5 = DAT_00062d14;
  fVar2 = DAT_00062d10;
  iVar4 = *(int *)(param_1 + 0x250);
  *(undefined4 *)(iVar3 + 0x68) = uVar1;
  fVar7 = *(float *)(iVar4 + 0x54);
  *(undefined4 *)(iVar3 + 0x70) = uVar1;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x800;
  *(float *)(iVar3 + 0x6c) = fVar7 * fVar5;
  *(float *)(iVar3 + 0x74) = fVar7 * fVar2;
  tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  fVar2 = DAT_00062d18;
  *(undefined4 *)(iVar3 + 0x60) = DAT_00062d1c;
  *(undefined4 *)(iVar3 + 100) = DAT_00062d20;
  *(undefined4 *)(iVar3 + 0x2c) = local_30;
  *(undefined4 *)(iVar3 + 0x30) = uStack_2c;
  *(undefined4 *)(iVar3 + 0x34) = uStack_28;
  *(undefined4 *)(iVar3 + 0x38) = uStack_24;
  fVar7 = *(float *)(param_1 + 0x234);
  fVar5 = *(float *)(param_1 + 0x230);
  fVar6 = *(float *)(param_1 + 0x22c);
  *(undefined4 *)(iVar3 + 0x78) = uVar1;
  *(float *)(iVar3 + 0x5c) = fVar7 * fVar2;
  *(float *)(iVar3 + 0x54) = fVar2 * fVar6;
  *(float *)(iVar3 + 0x58) = fVar2 * fVar5;
  *(undefined4 *)(iVar3 + 0x48) = param_2;
  *(undefined4 *)(iVar3 + 0x4c) = param_3;
  *(undefined4 *)(iVar3 + 0x50) = param_4;
  return;
}
