/*
 * mangled: _Z20ObjectProcWorldSkirtP8cRObjectPc
 * demangled: ObjectProcWorldSkirt(cRObject*, char*)
 * address: 00034a20
 * size: 336
 */

/* ObjectProcWorldSkirt(cRObject*, char*) */

void ObjectProcWorldSkirt(cRObject *param_1,char *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined2 *puVar3;

  cRObject::RequestVertices(param_1,4);
  cRObject::RequestFaceQuads(param_1,2);
  puVar3 = *(undefined2 **)(param_1 + 200);
  puVar2 = *(undefined4 **)(param_1 + 0xa4);
  puVar2[2] = 0x41800000;
  puVar2[6] = 0x41800000;
  *puVar2 = 0x41800000;
  puVar2[1] = 0xbdcccccd;
  puVar2[9] = 0xc1800000;
  puVar2[3] = 0xc1800000;
  puVar2[5] = 0x41800000;
  puVar2[4] = 0xbdcccccd;
  puVar2[8] = 0xc1800000;
  puVar2[7] = 0xbdcccccd;
  puVar2[0xb] = 0xc1800000;
  puVar2[10] = 0xbdcccccd;
  puVar3[1] = 0;
  puVar3[2] = 1;
  puVar3[3] = 3;
  puVar3[4] = 2;
  *puVar3 = 0;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar3[0x1a] = 1;
  *(undefined4 *)(puVar3 + 8) = 0x3f800000;
  puVar3[0x1b] = 3;
  *(undefined4 *)(puVar3 + 10) = 0x3f800000;
  puVar3[0x1c] = 2;
  *(undefined4 *)(puVar3 + 0xe) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x14) = 0x3f800000;
  puVar3[0x19] = 0;
  *(undefined4 *)(puVar3 + 0xc) = 0;
  *(undefined4 *)(puVar3 + 0x10) = 0;
  *(undefined4 *)(puVar3 + 0x12) = 0;
  *(undefined4 *)(puVar3 + 0x16) = 0;
  puVar3[0x18] = 0;
  *(undefined4 *)(puVar3 + 6) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  *(undefined4 *)(puVar3 + 0x2e) = 0;
  *(undefined4 *)(puVar3 + 0x2c) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x20) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x22) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x24) = 0;
  *(undefined4 *)(puVar3 + 0x26) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x28) = 0;
  *(undefined4 *)(puVar3 + 0x2a) = 0;
  *(undefined4 *)(puVar3 + 0x1e) = uVar1;
  return;
}
