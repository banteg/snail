/*
 * mangled: _ZN9cRSubGame9AddParcelEP7tVectorP10cRSubGoldy
 * demangled: cRSubGame::AddParcel(tVector*, cRSubGoldy*)
 * address: 0006f7a0
 * size: 292
 */

/* cRSubGame::AddParcel(tVector*, cRSubGoldy*) */

int cRSubGame::AddParcel(tVector *param_1,cRSubGoldy *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  iVar1 = cRParcelManager::New((cRParcelManager *)(param_1 + 0x31f770));
  if (iVar1 != 0) {
    uVar2 = *(undefined4 *)param_2;
    uVar3 = *(undefined4 *)(param_2 + 4);
    uVar4 = *(undefined4 *)(param_2 + 8);
    *(undefined4 *)(iVar1 + 0x2c) = 1;
    iVar5 = *(int *)(param_1 + 0xfe34);
    *(undefined4 *)(iVar1 + 0x10) = uVar2;
    *(undefined4 *)(iVar1 + 0x14) = uVar3;
    *(undefined4 *)(iVar1 + 0x18) = uVar4;
    *(tVector **)(iVar1 + 0x58) = param_1 + 0xfac4;
    iVar5 = cRSpriteManager::New((int)&gRSpriteManager,iVar5,0x6d,-1);
    uVar6 = *(uint *)(iVar5 + 4);
    *(int *)(iVar1 + 0x48) = iVar5;
    *(undefined4 *)(iVar5 + 0x68) = 0;
    *(undefined4 *)(iVar5 + 0x6c) = 0;
    *(undefined4 *)(iVar5 + 0x78) = 0;
    *(uint *)(iVar5 + 4) = uVar6 | 0x800;
    *(undefined4 *)(iVar5 + 0x28) = 7;
    tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar7 = *(int *)(iVar1 + 0x48);
    *(undefined4 *)(iVar7 + 100) = 0x3f800000;
    *(undefined4 *)(iVar7 + 0x60) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x2c) = local_38;
    *(undefined4 *)(iVar5 + 0x30) = uStack_34;
    *(undefined4 *)(iVar5 + 0x34) = uStack_30;
    *(undefined4 *)(iVar5 + 0x38) = uStack_2c;
    uVar2 = *(undefined4 *)(iVar1 + 0x14);
    uVar3 = *(undefined4 *)(iVar1 + 0x18);
    *(undefined4 *)(iVar7 + 0x48) = *(undefined4 *)(iVar1 + 0x10);
    *(undefined4 *)(iVar7 + 0x4c) = uVar2;
    *(undefined4 *)(iVar7 + 0x50) = uVar3;
    if (((int)*(float *)(param_2 + 8) & 1U) == 0) {
      *(undefined4 *)(iVar1 + 0x50) = 0x3f000000;
    }
    else {
      *(undefined4 *)(iVar1 + 0x50) = 0;
    }
    *(undefined4 *)(iVar1 + 0x54) = 0x3c520d21;
  }
  return iVar1;
}
