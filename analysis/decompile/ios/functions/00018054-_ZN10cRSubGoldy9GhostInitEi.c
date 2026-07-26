/*
 * mangled: _ZN10cRSubGoldy9GhostInitEi
 * demangled: cRSubGoldy::GhostInit(int)
 * address: 00018054
 * size: 388
 */

/* cRSubGoldy::GhostInit(int) */

void __thiscall cRSubGoldy::GhostInit(cRSubGoldy *this,int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  iVar2 = cRSpriteManager::New((int)PTR__gRSpriteManager_001b61e4,param_1,0x8a,-1);
  *(int *)(this + 0x8c) = iVar2;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x800;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x68) = 0;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x6c) = 0;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x78) = 0;
  iVar2 = *(int *)(this + 0x8c);
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
  *(undefined4 *)(iVar2 + 0x2c) = local_30;
  *(undefined4 *)(iVar2 + 0x30) = uStack_2c;
  *(undefined4 *)(iVar2 + 0x34) = uStack_28;
  *(undefined4 *)(iVar2 + 0x38) = uStack_24;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x60) = 0x3f000000;
  puVar1 = PTR__gRSpriteManager_001b61e4;
  *(undefined4 *)(*(int *)(this + 0x8c) + 100) = 0x3f000000;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x48) = 0x40900000;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x4c) = 0x3f800000;
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x50) = 0;
  iVar2 = cRSpriteManager::New((int)puVar1,param_1,0x8a,-1);
  *(int *)(this + 0x90) = iVar2;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x800;
  *(undefined4 *)(*(int *)(this + 0x90) + 0x68) = 0;
  *(undefined4 *)(*(int *)(this + 0x90) + 0x6c) = 0;
  *(undefined4 *)(*(int *)(this + 0x90) + 0x78) = 0;
  iVar2 = *(int *)(this + 0x90);
  tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
  *(undefined4 *)(iVar2 + 0x2c) = local_40;
  *(undefined4 *)(iVar2 + 0x30) = uStack_3c;
  *(undefined4 *)(iVar2 + 0x34) = uStack_38;
  *(undefined4 *)(iVar2 + 0x38) = uStack_34;
  *(undefined4 *)(*(int *)(this + 0x90) + 0x60) = 0x3f000000;
  *(undefined4 *)(*(int *)(this + 0x90) + 100) = 0x3f000000;
  *(undefined4 *)(*(int *)(this + 0x90) + 0x48) = 0xc0900000;
  *(undefined4 *)(*(int *)(this + 0x90) + 0x4c) = 0x3f800000;
  *(undefined4 *)(*(int *)(this + 0x90) + 0x50) = 0;
  *(uint *)(*(int *)(this + 0x8c) + 4) = *(uint *)(*(int *)(this + 0x8c) + 4) & 0xffffffbf;
  *(uint *)(*(int *)(this + 0x90) + 4) = *(uint *)(*(int *)(this + 0x90) + 4) & 0xffffffbf;
  return;
}
