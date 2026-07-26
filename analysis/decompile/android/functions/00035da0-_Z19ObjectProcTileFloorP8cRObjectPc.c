/*
 * mangled: _Z19ObjectProcTileFloorP8cRObjectPc
 * demangled: ObjectProcTileFloor(cRObject*, char*)
 * address: 00035da0
 * size: 584
 */

/* ObjectProcTileFloor(cRObject*, char*) */

void ObjectProcTileFloor(cRObject *param_1,char *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;

  cRObject::RequestVertices(param_1,8);
  cRObject::RequestFaceQuads(param_1,5);
  puVar4 = *(undefined2 **)(param_1 + 200);
  puVar3 = *(undefined4 **)(param_1 + 0xa4);
  puVar3[2] = 0x3f000000;
  puVar3[1] = 0xbdcccccd;
  uVar2 = *(uint *)param_1;
  puVar3[6] = 0x3f000000;
  *puVar3 = 0x3f000000;
  puVar3[3] = 0xbf000000;
  puVar3[9] = 0xbf000000;
  puVar3[0x12] = 0x3ecccccd;
  puVar3[0xc] = 0x3ecccccd;
  puVar3[0x15] = 0xbecccccd;
  puVar3[0xf] = 0xbecccccd;
  *puVar4 = 0;
  *(uint *)param_1 = uVar2 | 0x80;
  puVar3[5] = 0x3f000000;
  puVar3[4] = 0xbdcccccd;
  puVar3[8] = 0xbf000000;
  puVar3[7] = 0xbdcccccd;
  puVar3[0xb] = 0xbf000000;
  puVar3[10] = 0xbdcccccd;
  puVar3[0xe] = 0x3ecccccd;
  puVar3[0xd] = 0;
  puVar3[0x11] = 0x3ecccccd;
  puVar3[0x10] = 0;
  puVar3[0x14] = 0xbecccccd;
  puVar3[0x13] = 0;
  puVar3[0x17] = 0xbecccccd;
  puVar3[0x16] = 0;
  puVar4[1] = 0;
  puVar4[4] = 4;
  puVar4[3] = 5;
  puVar4[2] = 1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x1a] = 4;
  puVar4[0x1b] = 6;
  puVar4[0x1c] = 2;
  puVar4[0x19] = 0;
  puVar4[0x18] = 0;
  *(undefined4 *)(puVar4 + 6) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x31] = 4;
  puVar4[0x34] = 6;
  puVar4[0x33] = 7;
  puVar4[0x32] = 5;
  puVar4[0x30] = 0;
  *(undefined4 *)(puVar4 + 0x1e) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x4a] = 1;
  puVar4[0x49] = 5;
  puVar4[0x4b] = 3;
  puVar4[0x4c] = 7;
  puVar4[0x48] = 0;
  *(undefined4 *)(puVar4 + 0x36) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x61] = 6;
  puVar4[0x62] = 7;
  puVar4[99] = 3;
  puVar4[100] = 2;
  puVar4[0x60] = 0;
  *(undefined4 *)(puVar4 + 0x4e) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  *(undefined4 *)(puVar4 + 0x66) = uVar1;
  ObjectProcTileUV(param_1,8,4);
  return;
}
