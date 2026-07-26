/*
 * mangled: _Z18ObjectProcTileFastP8cRObjectPcf
 * demangled: ObjectProcTileFast(cRObject*, char*, float)
 * address: 00035a68
 * size: 256
 */

/* ObjectProcTileFast(cRObject*, char*, float) */

void ObjectProcTileFast(cRObject *param_1,char *param_2,float param_3)

{
  undefined4 uVar1;
  uint uVar2;
  float in_r2;
  float *pfVar3;
  undefined2 *puVar4;

  cRObject::RequestVertices(param_1,4);
  cRObject::RequestFaceQuads(param_1,1);
  puVar4 = *(undefined2 **)(param_1 + 200);
  pfVar3 = *(float **)(param_1 + 0xa4);
  uVar2 = *(uint *)param_1;
  pfVar3[2] = 0.5;
  pfVar3[1] = 0.0;
  pfVar3[9] = -0.5;
  pfVar3[3] = -0.5;
  pfVar3[5] = 0.5;
  pfVar3[4] = 0.0;
  *(uint *)param_1 = uVar2 | 0x8000000;
  pfVar3[8] = -0.5;
  pfVar3[6] = in_r2 + 0.5;
  *pfVar3 = in_r2 + 0.5;
  pfVar3[7] = 0.0;
  pfVar3[0xb] = -0.5;
  pfVar3[10] = 0.0;
  *puVar4 = 0;
  puVar4[2] = 1;
  puVar4[1] = 0;
  puVar4[3] = 3;
  puVar4[4] = 2;
  uVar1 = cRTextures::Add((cRTextures *)gTextureList,param_2,(cTgaHeader *)0x0,0);
  *(undefined4 *)(puVar4 + 0x16) = 0;
  *(undefined4 *)(puVar4 + 0xe) = 0x3f800000;
  *(undefined4 *)(puVar4 + 8) = 0;
  *(undefined4 *)(puVar4 + 10) = 0x3f800000;
  *(undefined4 *)(puVar4 + 0x12) = 0;
  *(undefined4 *)(puVar4 + 0x14) = 0;
  *(float *)(puVar4 + 0x10) = in_r2 + 1.0;
  *(float *)(puVar4 + 0xc) = in_r2 + 1.0;
  *(undefined4 *)(puVar4 + 6) = uVar1;
  return;
}
