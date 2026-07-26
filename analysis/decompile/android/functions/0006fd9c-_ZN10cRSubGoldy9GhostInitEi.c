/*
 * mangled: _ZN10cRSubGoldy9GhostInitEi
 * demangled: cRSubGoldy::GhostInit(int)
 * address: 0006fd9c
 * size: 336
 */

/* cRSubGoldy::GhostInit(int) */

void __thiscall cRSubGoldy::GhostInit(cRSubGoldy *this,int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
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

  iVar1 = cRSpriteManager::New((int)&gRSpriteManager,param_1,0x8a,-1);
  uVar2 = *(uint *)(iVar1 + 4);
  *(undefined4 *)(iVar1 + 0x68) = 0;
  *(int *)(this + 0x8c) = iVar1;
  *(undefined4 *)(iVar1 + 0x6c) = 0;
  *(undefined4 *)(iVar1 + 0x78) = 0;
  *(uint *)(iVar1 + 4) = uVar2 | 0x800;
  tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  iVar3 = *(int *)(this + 0x8c);
  *(undefined4 *)(iVar3 + 0x48) = 0x40900000;
  *(undefined4 *)(iVar3 + 0x50) = 0;
  *(undefined4 *)(iVar3 + 0x60) = 0x3f000000;
  *(undefined4 *)(iVar3 + 100) = 0x3f000000;
  *(undefined4 *)(iVar3 + 0x4c) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x2c) = local_38;
  *(undefined4 *)(iVar1 + 0x30) = uStack_34;
  *(undefined4 *)(iVar1 + 0x34) = uStack_30;
  *(undefined4 *)(iVar1 + 0x38) = uStack_2c;
  iVar1 = cRSpriteManager::New((int)&gRSpriteManager,param_1,0x8a,-1);
  uVar2 = *(uint *)(iVar1 + 4);
  *(int *)(this + 0x90) = iVar1;
  *(undefined4 *)(iVar1 + 0x68) = 0;
  *(undefined4 *)(iVar1 + 0x6c) = 0;
  *(undefined4 *)(iVar1 + 0x78) = 0;
  *(uint *)(iVar1 + 4) = uVar2 | 0x800;
  tColour::tColour((tColour *)&local_48,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  iVar4 = *(int *)(this + 0x8c);
  iVar3 = *(int *)(this + 0x90);
  *(undefined4 *)(iVar3 + 100) = 0x3f000000;
  uVar2 = *(uint *)(iVar4 + 4);
  *(undefined4 *)(iVar3 + 0x48) = 0xc0900000;
  *(undefined4 *)(iVar3 + 0x50) = 0;
  *(undefined4 *)(iVar3 + 0x60) = 0x3f000000;
  *(uint *)(iVar4 + 4) = uVar2 & 0xffffffbf;
  *(undefined4 *)(iVar3 + 0x4c) = 0x3f800000;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xffffffbf;
  *(undefined4 *)(iVar1 + 0x2c) = local_48;
  *(undefined4 *)(iVar1 + 0x30) = uStack_44;
  *(undefined4 *)(iVar1 + 0x34) = uStack_40;
  *(undefined4 *)(iVar1 + 0x38) = uStack_3c;
  return;
}
