/*
 * mangled: _Z15ObjectProcHouseP8cRObjectPc
 * demangled: ObjectProcHouse(cRObject*, char*)
 * address: 000357d8
 * size: 632
 */

/* ObjectProcHouse(cRObject*, char*) */

void ObjectProcHouse(cRObject *param_1,char *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined2 *puVar3;
  float fVar4;

  cRObject::RequestVertices(param_1,5);
  cRObject::RequestFaceQuads(param_1,2);
  puVar3 = *(undefined2 **)(param_1 + 200);
  puVar2 = *(undefined4 **)(param_1 + 0xa4);
  puVar2[2] = 0x3f000000;
  *puVar2 = 0x3f000000;
  puVar2[1] = 0;
  puVar2[6] = 0x3f000000;
  puVar2[0xc] = 0;
  puVar2[3] = 0xbf000000;
  puVar2[5] = 0x3f000000;
  puVar2[4] = 0;
  puVar2[9] = 0xbf000000;
  puVar2[8] = 0xbf000000;
  puVar2[7] = 0;
  puVar2[0xb] = 0xbf000000;
  puVar2[10] = 0;
  puVar2[0xe] = 0;
  puVar2[0xd] = 0x3f4ccccd;
  puVar3[1] = 4;
  puVar3[2] = 2;
  puVar3[3] = 0;
  puVar3[4] = 1;
  *puVar3 = 0;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar3[0x19] = 4;
  puVar3[0x1a] = 1;
  puVar3[0x1b] = 3;
  puVar3[0x18] = 0;
  puVar3[0x1c] = 2;
  *(undefined4 *)(puVar3 + 6) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  fVar4 = (float)puVar2[(uint)(ushort)puVar3[1] * 3];
  *(undefined4 *)(puVar3 + 0x1e) = uVar1;
  *(float *)(puVar3 + 8) = fVar4 + 0.5;
  *(float *)(puVar3 + 10) = (float)(puVar2 + (uint)(ushort)puVar3[1] * 3)[2] + 0.5;
  *(float *)(puVar3 + 0xc) = (float)puVar2[(uint)(ushort)puVar3[2] * 3] + 0.5;
  *(float *)(puVar3 + 0xe) = (float)puVar2[(uint)(ushort)puVar3[2] * 3 + 2] + 0.5;
  *(float *)(puVar3 + 0x10) = (float)puVar2[(uint)(ushort)puVar3[3] * 3] + 0.5;
  *(float *)(puVar3 + 0x12) = (float)puVar2[(uint)(ushort)puVar3[3] * 3 + 2] + 0.5;
  *(float *)(puVar3 + 0x14) = (float)puVar2[(uint)(ushort)puVar3[4] * 3] + 0.5;
  *(float *)(puVar3 + 0x16) = (float)puVar2[(uint)(ushort)puVar3[4] * 3 + 2] + 0.5;
  *(float *)(puVar3 + 0x20) = (float)puVar2[(uint)(ushort)puVar3[0x19] * 3] + 0.5;
  *(float *)(puVar3 + 0x22) = (float)puVar2[(uint)(ushort)puVar3[0x19] * 3 + 2] + 0.5;
  *(float *)(puVar3 + 0x24) = (float)puVar2[(uint)(ushort)puVar3[0x1a] * 3] + 0.5;
  *(float *)(puVar3 + 0x26) = (float)(puVar2 + (uint)(ushort)puVar3[0x1a] * 3)[2] + 0.5;
  *(float *)(puVar3 + 0x28) = (float)puVar2[(uint)(ushort)puVar3[0x1b] * 3] + 0.5;
  *(float *)(puVar3 + 0x2a) = (float)(puVar2 + (uint)(ushort)puVar3[0x1b] * 3)[2] + 0.5;
  *(float *)(puVar3 + 0x2c) = (float)puVar2[(uint)(ushort)puVar3[0x1c] * 3] + 0.5;
  *(float *)(puVar3 + 0x2e) = (float)(puVar2 + (uint)(ushort)puVar3[0x1c] * 3)[2] + 0.5;
  return;
}
