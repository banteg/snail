/*
 * mangled: _Z15ObjectProcFenceP8cRObjectPcS1_S1_
 * demangled: ObjectProcFence(cRObject*, char*, char*, char*)
 * address: 00037724
 * size: 1212
 */

/* ObjectProcFence(cRObject*, char*, char*, char*) */

void ObjectProcFence(cRObject *param_1,char *param_2,char *param_3,char *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;
  tColour *this;
  float fVar5;

  cRObject::RequestVertices(param_1,0xc);
  cRObject::RequestColours(param_1);
  fVar5 = (float)cRObject::RequestFaceQuads(param_1,9);
  this = *(tColour **)(param_1 + 0xb4);
  puVar3 = *(undefined4 **)(param_1 + 0xa4);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  puVar4 = *(undefined2 **)(param_1 + 200);
  fVar5 = (float)tColour::Grey(this,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x10,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x20,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x30,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x40,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x50,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x60,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x70,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x80,fVar5);
  fVar5 = (float)tColour::Grey(this + 0x90,fVar5);
  fVar5 = (float)tColour::Grey(this + 0xa0,fVar5);
  tColour::Grey(this + 0xb0,fVar5);
  puVar3[2] = 0x3f266666;
  puVar3[5] = 0x3f266666;
  puVar3[1] = 0x3e4ccccd;
  puVar3[4] = 0x3e4ccccd;
  puVar3[8] = 0x3eb33333;
  puVar3[7] = 0x3e4ccccd;
  puVar3[0xb] = 0x3eb33333;
  puVar3[10] = 0x3e4ccccd;
  puVar3[0xd] = 0x3e800000;
  puVar3[0x12] = 0x3e99999a;
  puVar3[0xc] = 0x3e99999a;
  puVar3[0xe] = 0x3f1eb852;
  puVar3[0x10] = 0x3e800000;
  puVar3[0x11] = 0x3f1eb852;
  puVar3[0x13] = 0x3e800000;
  puVar3[0x15] = 0xbe99999a;
  puVar3[0xf] = 0xbe99999a;
  puVar3[0x14] = 0x3ec28f5c;
  puVar3[0x17] = 0x3ec28f5c;
  puVar3[0x16] = 0x3e800000;
  puVar3[0x19] = 0xbd4ccccd;
  puVar3[0x1a] = 0x3f266666;
  puVar3[0x1c] = 0xbd4ccccd;
  puVar3[3] = 0xbecccccd;
  puVar3[9] = 0xbecccccd;
  puVar3[0x1b] = 0xbecccccd;
  puVar3[0x1e] = 0x3ecccccd;
  *puVar3 = 0x3ecccccd;
  puVar3[6] = 0x3ecccccd;
  puVar3[0x18] = 0x3ecccccd;
  puVar3[0x1d] = 0x3f266666;
  puVar3[0x20] = 0x3eb33333;
  puVar3[0x1f] = 0xbd4ccccd;
  puVar3[0x21] = 0xbecccccd;
  puVar3[0x23] = 0x3eb33333;
  puVar3[0x22] = 0xbd4ccccd;
  puVar4[1] = 0;
  puVar4[2] = 1;
  puVar4[3] = 5;
  puVar4[4] = 4;
  *puVar4 = 0;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x19] = 0;
  puVar4[0x1a] = 4;
  puVar4[0x18] = 0;
  puVar4[0x1c] = 2;
  puVar4[0x1b] = 6;
  *(undefined4 *)(puVar4 + 6) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x30] = 0;
  puVar4[0x31] = 4;
  puVar4[0x32] = 5;
  puVar4[0x33] = 7;
  puVar4[0x34] = 6;
  *(undefined4 *)(puVar4 + 0x1e) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x48] = 0;
  puVar4[0x49] = 5;
  puVar4[0x4a] = 1;
  puVar4[0x4b] = 3;
  puVar4[0x4c] = 7;
  *(undefined4 *)(puVar4 + 0x36) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x60] = 0;
  puVar4[0x61] = 6;
  puVar4[0x62] = 7;
  puVar4[99] = 3;
  puVar4[100] = 2;
  *(undefined4 *)(puVar4 + 0x4e) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  puVar4[0x78] = 0;
  puVar4[0x79] = 8;
  puVar4[0x7a] = 9;
  puVar4[0x7b] = 1;
  puVar4[0x7c] = 0;
  *(undefined4 *)(puVar4 + 0x66) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_3,(cTgaHeader *)0x0,0);
  puVar4[0x92] = 0;
  puVar4[0x91] = 8;
  puVar4[0x90] = 0;
  puVar4[0x93] = 2;
  puVar4[0x94] = 10;
  *(undefined4 *)(puVar4 + 0x7e) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_4,(cTgaHeader *)0x0,0);
  puVar4[0xa8] = 0;
  puVar4[0xa9] = 1;
  puVar4[0xaa] = 9;
  puVar4[0xab] = 0xb;
  puVar4[0xac] = 3;
  *(undefined4 *)(puVar4 + 0x96) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_4,(cTgaHeader *)0x0,0);
  puVar4[0xc0] = 0;
  puVar4[0xc1] = 2;
  puVar4[0xc2] = 3;
  puVar4[0xc3] = 0xb;
  puVar4[0xc4] = 10;
  *(undefined4 *)(puVar4 + 0xae) = uVar1;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_3,(cTgaHeader *)0x0,0);
  iVar2 = 5;
  *(undefined4 *)(puVar4 + 0xc6) = uVar1;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(puVar4 + 0x80) = 0;
    *(undefined4 *)(puVar4 + 0x84) = 0x3f800000;
    *(undefined4 *)(puVar4 + 0x88) = 0;
    *(undefined4 *)(puVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(puVar4 + 0x82) = 0;
    *(undefined4 *)(puVar4 + 0x86) = 0;
    *(undefined4 *)(puVar4 + 0x8a) = 0x3f800000;
    *(undefined4 *)(puVar4 + 0x8e) = 0x3f800000;
    puVar4 = puVar4 + 0x18;
  } while (iVar2 != 9);
  return;
}
