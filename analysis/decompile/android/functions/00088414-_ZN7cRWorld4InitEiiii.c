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
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint *puVar7;
  undefined4 *puVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  cRObjects *this_00;
  char *pcVar17;

  iVar4 = DAT_000886d4;
  iVar10 = DAT_000886d0 + 0x88430;
  *(int *)(this + 0x5c) = param_2;
  this_00 = *(cRObjects **)(iVar10 + iVar4);
  *(int *)(this + 100) = param_4;
  *(int *)(this + 0x60) = param_3;
  *(int *)(this + 0x58) = param_1;
  iVar16 = param_4 * param_2 * 2;
  iVar14 = param_4 * param_3 * 2;
  pcVar1 = (cRObject *)cRObjects::Add(this_00);
  cRBod::SetObject((cRBod *)this,pcVar1);
  pcVar1 = *(cRObject **)(this + 0x24);
  *(uint *)pcVar1 = *(uint *)pcVar1 | 0x1000;
  cRObject::RequestVertices(pcVar1,1);
  cRObject::RequestFaceQuads(*(cRObject **)(this + 0x24),1);
  iVar11 = *(int *)(this + 0x24);
  pcVar17 = (char *)(iVar10 + DAT_000886d8);
  uVar2 = RShellMemoryMalloc(0x5c,pcVar17);
  iVar6 = *(int *)(this + 0x5c);
  iVar4 = *(int *)(this + 0x24);
  pcVar3 = (char *)(iVar10 + DAT_000886dc);
  *(undefined4 *)(iVar11 + 0x10c) = uVar2;
  iVar12 = *(int *)(iVar4 + 0x10c);
  uVar2 = RShellMemoryMalloc(iVar6 << 3,pcVar3);
  iVar6 = DAT_000886e0;
  iVar4 = *(int *)(this + 100);
  iVar11 = *(int *)(this + 0x5c);
  iVar15 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  *(undefined4 *)(iVar15 + 0x24) = 0;
  iVar4 = (iVar4 * iVar11 * 4) / 3;
  *(int *)(iVar15 + 0x28) = iVar4 * 3;
  *(undefined4 *)(iVar12 + 0x1c) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar4 * 6,(char *)(iVar10 + iVar6));
  puVar7 = *(uint **)(this + 0x24);
  uVar13 = puVar7[0x43];
  pcVar5 = (char *)(iVar10 + DAT_000886e4);
  *(int *)(uVar13 + 0x3c) = iVar16;
  *(undefined4 *)(uVar13 + 0x40) = 0;
  puVar7[2] = 0;
  *puVar7 = *puVar7 | 0x4400004;
  *(int *)(uVar13 + 4) = iVar16;
  *(undefined4 *)(iVar15 + 0x20) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar16 * 10,pcVar5);
  *(undefined4 *)(uVar13 + 8) = uVar2;
  puVar8 = *(undefined4 **)(*(int *)(this + 0x24) + 0x10c);
  puVar8[0xe] = 0;
  *puVar8 = 0;
  puVar8[0xb] = 0;
  puVar8[0xc] = 0;
  puVar8[0xd] = 0;
  pcVar1 = (cRObject *)cRObjects::Add(this_00);
  cRBod::SetObject((cRBod *)(this + 0x2c),pcVar1);
  pcVar1 = *(cRObject **)(this + 0x50);
  *(uint *)pcVar1 = *(uint *)pcVar1 | 0x1000;
  cRObject::RequestVertices(pcVar1,1);
  cRObject::RequestFaceQuads(*(cRObject **)(this + 0x50),1);
  piVar9 = *(int **)(iVar10 + DAT_000886e8);
  *(undefined4 *)(*(int *)(this + 0x50) + 8) = 5;
  cRSubGame::GetSkirtColour((tColourSmall *)(*piVar9 + 0x718a0));
  iVar12 = *(int *)(this + 0x50);
  uVar2 = RShellMemoryMalloc(0x5c,pcVar17);
  iVar4 = *(int *)(this + 0x60);
  iVar11 = *(int *)(this + 0x50);
  *(undefined4 *)(iVar12 + 0x10c) = uVar2;
  iVar11 = *(int *)(iVar11 + 0x10c);
  uVar2 = RShellMemoryMalloc(iVar4 << 3,pcVar3);
  iVar15 = *(int *)(this + 100);
  iVar4 = *(int *)(this + 0x60);
  iVar12 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  *(undefined4 *)(iVar12 + 0x24) = 0;
  *(int *)(iVar12 + 0x28) = iVar15 * iVar4 * 3;
  *(undefined4 *)(iVar11 + 0x1c) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar15 * iVar4 * 6,(char *)(iVar10 + iVar6));
  puVar7 = *(uint **)(this + 0x50);
  uVar13 = puVar7[0x43];
  *(int *)(uVar13 + 0x3c) = iVar14;
  *(undefined4 *)(uVar13 + 0x40) = 0;
  *puVar7 = *puVar7 | 0x4400004;
  *(int *)(uVar13 + 4) = iVar14;
  *(undefined4 *)(iVar12 + 0x20) = uVar2;
  uVar2 = RShellMemoryMalloc(iVar14 * 10,pcVar5);
  pcVar3 = (char *)(iVar10 + DAT_000886ec);
  *(undefined4 *)(uVar13 + 8) = uVar2;
  puVar8 = *(undefined4 **)(*(int *)(this + 0x50) + 0x10c);
  uVar2 = cRTextures::Add(*(cRTextures **)(iVar10 + DAT_000886f0),pcVar3,(cTgaHeader *)0x0,0x400);
  iVar4 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  *(undefined4 *)(iVar4 + 0x38) = 0;
  *(undefined4 *)(iVar4 + 0x2c) = 0;
  *(undefined4 *)(iVar4 + 0x30) = 0;
  *(undefined4 *)(iVar4 + 0x34) = 0;
  *puVar8 = uVar2;
  return;
}
