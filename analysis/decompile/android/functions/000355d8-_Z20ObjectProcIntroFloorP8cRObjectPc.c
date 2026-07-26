/*
 * mangled: _Z20ObjectProcIntroFloorP8cRObjectPc
 * demangled: ObjectProcIntroFloor(cRObject*, char*)
 * address: 000355d8
 * size: 228
 */

/* ObjectProcIntroFloor(cRObject*, char*) */

void ObjectProcIntroFloor(cRObject *param_1,char *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined2 *puVar3;

  cRObject::RequestVertices(param_1,4);
  cRObject::RequestFaceQuads(param_1,1);
  puVar3 = *(undefined2 **)(param_1 + 200);
  puVar2 = *(undefined4 **)(param_1 + 0xa4);
  puVar2[1] = 0xbdcccccd;
  puVar2[2] = 0xc1000000;
  puVar2[6] = 0xc1000000;
  *puVar2 = 0xc1000000;
  puVar2[9] = 0x41000000;
  puVar2[4] = 0xbdcccccd;
  puVar2[5] = 0xc1000000;
  puVar2[3] = 0x41000000;
  puVar2[7] = 0xbdcccccd;
  puVar2[8] = 0x41000000;
  *puVar3 = 0;
  puVar2[10] = 0xbdcccccd;
  puVar2[0xb] = 0x41000000;
  puVar3[2] = 1;
  puVar3[1] = 0;
  puVar3[3] = 3;
  puVar3[4] = 2;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  *(undefined4 *)(puVar3 + 0x14) = 0;
  *(undefined4 *)(puVar3 + 8) = 0;
  *(undefined4 *)(puVar3 + 10) = 0;
  *(undefined4 *)(puVar3 + 0xe) = 0;
  *(undefined4 *)(puVar3 + 0x16) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0xc) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x10) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x12) = 0x3f800000;
  *(undefined4 *)(puVar3 + 6) = uVar1;
  return;
}
