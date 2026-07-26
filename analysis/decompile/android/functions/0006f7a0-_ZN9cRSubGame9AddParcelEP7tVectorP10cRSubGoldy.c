/*
 * mangled: _ZN9cRSubGame9AddParcelEP7tVectorP10cRSubGoldy
 * demangled: cRSubGame::AddParcel(tVector*, cRSubGoldy*)
 * address: 0006f7a0
 * size: 292
 */

/* cRSubGame::AddParcel(tVector*, cRSubGoldy*) */

int cRSubGame::AddParcel(tVector *param_1,cRSubGoldy *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  iVar6 = DAT_0006f8d0;
  iVar2 = cRParcelManager::New((cRParcelManager *)(param_1 + 0x31f770));
  uVar1 = DAT_0006f8c4;
  if (iVar2 != 0) {
    uVar3 = *(undefined4 *)param_2;
    uVar4 = *(undefined4 *)(param_2 + 4);
    uVar5 = *(undefined4 *)(param_2 + 8);
    iVar8 = *(int *)(iVar6 + 0x6f7d0 + DAT_0006f8d4);
    *(undefined4 *)(iVar2 + 0x2c) = 1;
    iVar6 = *(int *)(param_1 + 0xfe34);
    *(undefined4 *)(iVar2 + 0x10) = uVar3;
    *(undefined4 *)(iVar2 + 0x14) = uVar4;
    *(undefined4 *)(iVar2 + 0x18) = uVar5;
    *(tVector **)(iVar2 + 0x58) = param_1 + 0xfac4;
    iVar6 = cRSpriteManager::New(iVar8,iVar6,0x6d,-1);
    uVar7 = *(uint *)(iVar6 + 4);
    *(int *)(iVar2 + 0x48) = iVar6;
    *(undefined4 *)(iVar6 + 0x68) = uVar1;
    *(undefined4 *)(iVar6 + 0x6c) = uVar1;
    *(undefined4 *)(iVar6 + 0x78) = uVar1;
    *(uint *)(iVar6 + 4) = uVar7 | 0x800;
    *(undefined4 *)(iVar6 + 0x28) = 7;
    tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar8 = *(int *)(iVar2 + 0x48);
    *(undefined4 *)(iVar8 + 100) = 0x3f800000;
    *(undefined4 *)(iVar8 + 0x60) = 0x3f800000;
    *(undefined4 *)(iVar6 + 0x2c) = local_38;
    *(undefined4 *)(iVar6 + 0x30) = uStack_34;
    *(undefined4 *)(iVar6 + 0x34) = uStack_30;
    *(undefined4 *)(iVar6 + 0x38) = uStack_2c;
    uVar3 = *(undefined4 *)(iVar2 + 0x14);
    uVar4 = *(undefined4 *)(iVar2 + 0x18);
    *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(iVar2 + 0x10);
    *(undefined4 *)(iVar8 + 0x4c) = uVar3;
    *(undefined4 *)(iVar8 + 0x50) = uVar4;
    if (((int)*(float *)(param_2 + 8) & 1U) == 0) {
      *(undefined4 *)(iVar2 + 0x50) = DAT_0006f8c8;
    }
    else {
      *(undefined4 *)(iVar2 + 0x50) = uVar1;
    }
    *(undefined4 *)(iVar2 + 0x54) = DAT_0006f8cc;
  }
  return iVar2;
}
