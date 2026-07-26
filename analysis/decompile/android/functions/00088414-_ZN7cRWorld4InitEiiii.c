/*
 * mangled: _ZN7cRWorld4InitEiiii
 * demangled: cRWorld::Init(int, int, int, int)
 * address: 00088414
 * size: 700
 */

/* cRWorld::Init(int, int, int, int) */

void __thiscall cRWorld::Init(cRWorld *this,int param_1,int param_2,int param_3,int param_4)

{
  cRObject *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;

  *(int *)(this + 0x5c) = param_2;
  *(int *)(this + 100) = param_4;
  *(int *)(this + 0x60) = param_3;
  *(int *)(this + 0x58) = param_1;
  iVar11 = param_4 * param_2 * 2;
  iVar9 = param_4 * param_3 * 2;
  pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)this,pcVar1);
  pcVar1 = *(cRObject **)(this + 0x24);
  *(uint *)pcVar1 = *(uint *)pcVar1 | 0x1000;
  cRObject::RequestVertices(pcVar1,1);
  cRObject::RequestFaceQuads(*(cRObject **)(this + 0x24),1);
  iVar7 = *(int *)(this + 0x24);
  uVar2 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
  iVar4 = *(int *)(this + 0x5c);
  iVar3 = *(int *)(this + 0x24);
  *(undefined4 *)(iVar7 + 0x10c) = uVar2;
  iVar7 = *(int *)(iVar3 + 0x10c);
  uVar2 = RShellMemoryMalloc(iVar4 << 3,"World Row Index");
  iVar3 = *(int *)(this + 100);
  iVar4 = *(int *)(this + 0x5c);
  iVar10 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  *(undefined4 *)(iVar10 + 0x24) = 0;
  iVar3 = (iVar3 * iVar4 * 4) / 3;
  *(int *)(iVar10 + 0x28) = iVar3 * 3;
  *(undefined4 *)(iVar7 + 0x1c) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar3 * 6,"World Index Array");
  puVar5 = *(uint **)(this + 0x24);
  uVar8 = puVar5[0x43];
  *(int *)(uVar8 + 0x3c) = iVar11;
  *(undefined4 *)(uVar8 + 0x40) = 0;
  puVar5[2] = 0;
  *puVar5 = *puVar5 | 0x4400004;
  *(int *)(uVar8 + 4) = iVar11;
  *(undefined4 *)(iVar10 + 0x20) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar11 * 10,"Obj VertexUV");
  *(undefined4 *)(uVar8 + 8) = uVar2;
  puVar6 = *(undefined4 **)(*(int *)(this + 0x24) + 0x10c);
  puVar6[0xe] = 0;
  *puVar6 = 0;
  puVar6[0xb] = 0;
  puVar6[0xc] = 0;
  puVar6[0xd] = 0;
  pcVar1 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x2c),pcVar1);
  pcVar1 = *(cRObject **)(this + 0x50);
  *(uint *)pcVar1 = *(uint *)pcVar1 | 0x1000;
  cRObject::RequestVertices(pcVar1,1);
  cRObject::RequestFaceQuads(*(cRObject **)(this + 0x50),1);
  *(undefined4 *)(*(int *)(this + 0x50) + 8) = 5;
  cRSubGame::GetSkirtColour((tColourSmall *)(Game + 0x718a0));
  iVar7 = *(int *)(this + 0x50);
  uVar2 = RShellMemoryMalloc(0x5c,"Obj Vertex array");
  iVar3 = *(int *)(this + 0x60);
  iVar4 = *(int *)(this + 0x50);
  *(undefined4 *)(iVar7 + 0x10c) = uVar2;
  iVar4 = *(int *)(iVar4 + 0x10c);
  uVar2 = RShellMemoryMalloc(iVar3 << 3,"World Row Index");
  iVar10 = *(int *)(this + 100);
  iVar3 = *(int *)(this + 0x60);
  iVar7 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  *(undefined4 *)(iVar7 + 0x24) = 0;
  *(int *)(iVar7 + 0x28) = iVar10 * iVar3 * 3;
  *(undefined4 *)(iVar4 + 0x1c) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar10 * iVar3 * 6,"World Index Array");
  puVar5 = *(uint **)(this + 0x50);
  uVar8 = puVar5[0x43];
  *(int *)(uVar8 + 0x3c) = iVar9;
  *(undefined4 *)(uVar8 + 0x40) = 0;
  *puVar5 = *puVar5 | 0x4400004;
  *(int *)(uVar8 + 4) = iVar9;
  *(undefined4 *)(iVar7 + 0x20) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar9 * 10,"Obj VertexUV");
  *(undefined4 *)(uVar8 + 8) = uVar2;
  puVar6 = *(undefined4 **)(*(int *)(this + 0x50) + 0x10c);
  uVar2 = cRTextures::Add((cRTextures *)gTextureList,"Objects/Universe/Fringe.tga",(cTgaHeader *)0x0
                          ,0x400);
  iVar3 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar3 + 0x2c) = 0;
  *(undefined4 *)(iVar3 + 0x30) = 0;
  *(undefined4 *)(iVar3 + 0x34) = 0;
  *puVar6 = uVar2;
  return;
}
