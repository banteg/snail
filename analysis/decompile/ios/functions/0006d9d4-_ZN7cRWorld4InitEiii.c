/*
 * mangled: _ZN7cRWorld4InitEiii
 * demangled: cRWorld::Init(int, int, int)
 * address: 0006d9d4
 * size: 912
 */

/* cRWorld::Init(int, int, int) */

void __thiscall cRWorld::Init(cRWorld *this,int param_1,int param_2,int param_3)

{
  undefined *this_00;
  cRObject *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;

  *(int *)(this + 0x60) = param_3;
  *(int *)(this + 0x58) = param_1;
  *(int *)(this + 0x5c) = param_2;
  this_00 = PTR__gObjectList_001b61cc;
  iVar5 = param_3 * param_2 * 2;
  pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
  cRBod::SetObject((cRBod *)this,pcVar1);
  **(uint **)(this + 0x24) = **(uint **)(this + 0x24) | 0x1000;
  cRObject::RequestVertices(*(cRObject **)(this + 0x24),1);
  cRObject::RequestFaceQuads(*(cRObject **)(this + 0x24),1);
  iVar3 = *(int *)(this + 0x24);
  uVar2 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
  *(undefined4 *)(iVar3 + 0x10c) = uVar2;
  iVar3 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  uVar2 = RShellMemoryMalloc(*(int *)(this + 0x5c) << 3,"World Row Index");
  *(undefined4 *)(iVar3 + 0x1c) = uVar2;
  *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x28) =
       *(int *)(this + 0x60) * *(int *)(this + 0x5c) * 4;
  *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x28) =
       (*(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x28) / 3) * 3;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x24) = 0;
  iVar3 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  uVar2 = RShellMemoryMalloc(*(int *)(iVar3 + 0x28) << 1,"World Index Array");
  *(undefined4 *)(iVar3 + 0x20) = uVar2;
  *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x3c) = iVar5;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x40) = 0;
  *(undefined4 *)(*(int *)(this + 0x24) + 8) = 0;
  **(uint **)(this + 0x24) = **(uint **)(this + 0x24) | 4;
  **(uint **)(this + 0x24) = **(uint **)(this + 0x24) | 0x4000000;
  **(uint **)(this + 0x24) = **(uint **)(this + 0x24) | 0x400000;
  *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 4) = iVar5;
  iVar3 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  uVar2 = RShellMemoryMalloc(iVar5 * 10,"Obj VertexUV");
  *(undefined4 *)(iVar3 + 8) = uVar2;
  **(undefined4 **)(*(int *)(this + 0x24) + 0x10c) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x2c) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x30) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x34) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x38) = 0;
  pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)this_00);
  cRBod::SetObject((cRBod *)(this + 0x2c),pcVar1);
  **(uint **)(this + 0x50) = **(uint **)(this + 0x50) | 0x1000;
  cRObject::RequestVertices(*(cRObject **)(this + 0x50),1);
  cRObject::RequestFaceQuads(*(cRObject **)(this + 0x50),1);
  *(undefined4 *)(*(int *)(this + 0x50) + 8) = 5;
  cRSubGame::GetSkirtColour
            ((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78),(tColourSmall *)(this + 0x54));
  iVar3 = *(int *)(this + 0x50);
  uVar2 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
  *(undefined4 *)(iVar3 + 0x10c) = uVar2;
  iVar3 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  uVar2 = RShellMemoryMalloc(*(int *)(this + 0x5c) << 3,"World Row Index");
  *(undefined4 *)(iVar3 + 0x1c) = uVar2;
  *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x28) =
       *(int *)(this + 0x60) * *(int *)(this + 0x5c) * 3;
  *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x28) =
       (*(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x28) / 3) * 3;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x24) = 0;
  iVar3 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  uVar2 = RShellMemoryMalloc(*(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x28) << 1,
                             "World Index Array");
  *(undefined4 *)(iVar3 + 0x20) = uVar2;
  *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x3c) = iVar5;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x40) = 0;
  **(uint **)(this + 0x50) = **(uint **)(this + 0x50) | 4;
  **(uint **)(this + 0x50) = **(uint **)(this + 0x50) | 0x4000000;
  **(uint **)(this + 0x50) = **(uint **)(this + 0x50) | 0x400000;
  *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 4) = iVar5;
  iVar3 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  uVar2 = RShellMemoryMalloc(iVar5 * 10,"Obj VertexUV");
  *(undefined4 *)(iVar3 + 8) = uVar2;
  puVar4 = *(undefined4 **)(*(int *)(this + 0x50) + 0x10c);
  uVar2 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,"Objects/Universe/Fringe.tga",
                          (cTgaHeader *)0x0,0x400);
  *puVar4 = uVar2;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x2c) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x30) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x34) = 0;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x38) = 0;
  return;
}
