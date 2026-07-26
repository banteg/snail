/*
 * mangled: _Z22ObjectProcTileWallFastP8cRObjectPcS1_S1_
 * demangled: ObjectProcTileWallFast(cRObject*, char*, char*, char*)
 * address: 00034e18
 * size: 464
 */

/* ObjectProcTileWallFast(cRObject*, char*, char*, char*) */

void ObjectProcTileWallFast(cRObject *param_1,char *param_2,char *param_3,char *param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined2 *puVar4;

  cRObject::RequestVertices(param_1,8);
  cRObject::RequestFaceQuads(param_1,3);
  puVar4 = *(undefined2 **)(param_1 + 200);
  puVar2 = *(undefined4 **)(param_1 + 0xa4);
  puVar2[2] = 0x3f000000;
  puVar2[1] = 0;
  *puVar2 = 0x3f000000;
  puVar2[6] = 0x3f000000;
  puVar2[0xc] = 0x3f000000;
  puVar2[0x12] = 0x3f000000;
  puVar2[0x15] = 0xbf000000;
  puVar2[3] = 0xbf000000;
  puVar2[9] = 0xbf000000;
  puVar2[0xf] = 0xbf000000;
  *puVar4 = 0;
  puVar2[5] = 0x3f000000;
  puVar2[4] = 0;
  puVar2[8] = 0xbf000000;
  puVar2[7] = 0;
  puVar2[0xb] = 0xbf000000;
  puVar2[10] = 0;
  puVar2[0xe] = 0x3f000000;
  puVar2[0xd] = 0x3f000000;
  puVar2[0x11] = 0x3f000000;
  puVar2[0x10] = 0x3f000000;
  puVar2[0x13] = 0x3f000000;
  puVar2[0x14] = 0xbf000000;
  puVar2[0x16] = 0x3f000000;
  puVar2[0x17] = 0xbf000000;
  puVar4[2] = 4;
  puVar4[1] = 0;
  puVar4[4] = 2;
  puVar4[3] = 6;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_4,(cTgaHeader *)0x0,0);
  puVar4[0x18] = 0;
  puVar4[0x19] = 5;
  puVar4[0x1a] = 1;
  puVar4[0x1b] = 3;
  puVar4[0x1c] = 7;
  *(undefined4 *)(puVar4 + 6) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_4,(cTgaHeader *)0x0,0);
  puVar4[0x30] = 0;
  puVar4[0x31] = 6;
  puVar4[0x32] = 7;
  puVar4[0x33] = 3;
  puVar4[0x34] = 2;
  *(undefined4 *)(puVar4 + 0x1e) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_3,(cTgaHeader *)0x0,0);
  iVar3 = 0;
  *(undefined4 *)(puVar4 + 0x36) = uVar1;
  do {
    iVar3 = iVar3 + 1;
    *(undefined4 *)(puVar4 + 8) = 0;
    *(undefined4 *)(puVar4 + 0xc) = 0x3f800000;
    *(undefined4 *)(puVar4 + 0x10) = 0x3f800000;
    *(undefined4 *)(puVar4 + 0x14) = 0;
    *(undefined4 *)(puVar4 + 10) = 0;
    *(undefined4 *)(puVar4 + 0xe) = 0;
    *(undefined4 *)(puVar4 + 0x12) = 0x3f800000;
    *(undefined4 *)(puVar4 + 0x16) = 0x3f800000;
    puVar4 = puVar4 + 0x18;
  } while (iVar3 != 3);
  return;
}
