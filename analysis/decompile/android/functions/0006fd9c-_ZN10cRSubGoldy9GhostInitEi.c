/*
 * mangled: _ZN10cRSubGoldy9GhostInitEi
 * demangled: cRSubGoldy::GhostInit(int)
 * address: 0006fd9c
 * size: 336
 */

/* cRSubGoldy::GhostInit(int) */

void __thiscall cRSubGoldy::GhostInit(cRSubGoldy *this,int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  uVar2 = DAT_0006fef0;
  uVar1 = DAT_0006feec;
  iVar6 = *(int *)(DAT_0006fefc + 0x6fdc0 + DAT_0006ff00);
  iVar4 = cRSpriteManager::New(iVar6,param_1,0x8a,-1);
  uVar5 = *(uint *)(iVar4 + 4);
  *(undefined4 *)(iVar4 + 0x68) = uVar1;
  *(int *)(this + 0x8c) = iVar4;
  *(undefined4 *)(iVar4 + 0x6c) = uVar1;
  *(undefined4 *)(iVar4 + 0x78) = uVar1;
  *(uint *)(iVar4 + 4) = uVar5 | 0x800;
  tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  iVar7 = *(int *)(this + 0x8c);
  *(undefined4 *)(iVar7 + 0x48) = DAT_0006fef4;
  *(undefined4 *)(iVar7 + 0x50) = uVar1;
  *(undefined4 *)(iVar7 + 0x60) = uVar2;
  *(undefined4 *)(iVar7 + 100) = uVar2;
  *(undefined4 *)(iVar7 + 0x4c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x2c) = local_38;
  *(undefined4 *)(iVar4 + 0x30) = uStack_34;
  *(undefined4 *)(iVar4 + 0x34) = uStack_30;
  *(undefined4 *)(iVar4 + 0x38) = uStack_2c;
  iVar4 = cRSpriteManager::New(iVar6,param_1,0x8a,-1);
  uVar5 = *(uint *)(iVar4 + 4);
  *(int *)(this + 0x90) = iVar4;
  *(undefined4 *)(iVar4 + 0x68) = uVar1;
  *(undefined4 *)(iVar4 + 0x6c) = uVar1;
  *(undefined4 *)(iVar4 + 0x78) = uVar1;
  *(uint *)(iVar4 + 4) = uVar5 | 0x800;
  tColour::tColour((tColour *)&local_48,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  uVar3 = DAT_0006fef8;
  iVar7 = *(int *)(this + 0x8c);
  iVar6 = *(int *)(this + 0x90);
  *(undefined4 *)(iVar6 + 100) = uVar2;
  uVar5 = *(uint *)(iVar7 + 4);
  *(undefined4 *)(iVar6 + 0x48) = uVar3;
  *(undefined4 *)(iVar6 + 0x50) = uVar1;
  *(undefined4 *)(iVar6 + 0x60) = uVar2;
  *(uint *)(iVar7 + 4) = uVar5 & 0xffffffbf;
  *(undefined4 *)(iVar6 + 0x4c) = 0x3f800000;
  *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) & 0xffffffbf;
  *(undefined4 *)(iVar4 + 0x2c) = local_48;
  *(undefined4 *)(iVar4 + 0x30) = uStack_44;
  *(undefined4 *)(iVar4 + 0x34) = uStack_40;
  *(undefined4 *)(iVar4 + 0x38) = uStack_3c;
  return;
}
