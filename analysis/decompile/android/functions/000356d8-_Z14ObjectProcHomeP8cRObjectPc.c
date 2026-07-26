/*
 * mangled: _Z14ObjectProcHomeP8cRObjectPc
 * demangled: ObjectProcHome(cRObject*, char*)
 * address: 000356d8
 * size: 228
 */

/* ObjectProcHome(cRObject*, char*) */

void ObjectProcHome(cRObject *param_1,char *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined2 *puVar3;

  cRObject::RequestVertices(param_1,5);
  cRObject::RequestFaceQuads(param_1,2);
  puVar3 = *(undefined2 **)(param_1 + 200);
  puVar2 = *(undefined4 **)(param_1 + 0xa4);
  puVar2[1] = 0x3c23d70a;
  puVar2[2] = 0x3f000000;
  puVar2[6] = 0x3f000000;
  *puVar2 = 0x3f000000;
  puVar2[9] = 0xbf000000;
  puVar2[4] = 0x3c23d70a;
  puVar2[5] = 0x3f000000;
  puVar2[3] = 0xbf000000;
  puVar2[7] = 0x3c23d70a;
  puVar2[8] = 0xbf000000;
  *puVar3 = 0;
  puVar2[10] = 0x3c23d70a;
  puVar2[0xb] = 0xbf000000;
  puVar3[2] = 1;
  puVar3[1] = 0;
  puVar3[3] = 3;
  puVar3[4] = 2;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  *(undefined4 *)(puVar3 + 0x14) = 0x3dcccccd;
  *(undefined4 *)(puVar3 + 8) = 0x3dcccccd;
  *(undefined4 *)(puVar3 + 10) = 0x3dcccccd;
  *(undefined4 *)(puVar3 + 0xe) = 0x3dcccccd;
  *(undefined4 *)(puVar3 + 0x16) = 0x3f666666;
  *(undefined4 *)(puVar3 + 0xc) = 0x3f666666;
  *(undefined4 *)(puVar3 + 0x10) = 0x3f666666;
  *(undefined4 *)(puVar3 + 0x12) = 0x3f666666;
  *(undefined4 *)(puVar3 + 6) = uVar1;
  return;
}
