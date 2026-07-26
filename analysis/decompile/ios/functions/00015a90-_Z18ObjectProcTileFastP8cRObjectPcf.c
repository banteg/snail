/*
 * mangled: _Z18ObjectProcTileFastP8cRObjectPcf
 * demangled: ObjectProcTileFast(cRObject*, char*, float)
 * address: 00015a90
 * size: 248
 */

/* ObjectProcTileFast(cRObject*, char*, float) */

void ObjectProcTileFast(cRObject *param_1,char *param_2,float param_3)

{
  undefined4 uVar1;
  float *pfVar2;
  undefined2 *puVar3;

  cRObject::RequestVertices(param_1,4);
  cRObject::RequestFaceQuads(param_1,1);
  *(uint *)param_1 = *(uint *)param_1 | 0x8000000;
  pfVar2 = *(float **)(param_1 + 0xa4);
  puVar3 = *(undefined2 **)(param_1 + 200);
  pfVar2[2] = 0.5;
  *pfVar2 = param_3 + 0.5;
  pfVar2[3] = -0.5;
  pfVar2[5] = 0.5;
  pfVar2[6] = param_3 + 0.5;
  pfVar2[8] = -0.5;
  pfVar2[9] = -0.5;
  pfVar2[0xb] = -0.5;
  pfVar2[1] = 0.0;
  pfVar2[4] = 0.0;
  pfVar2[7] = 0.0;
  pfVar2[10] = 0.0;
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[2] = 1;
  puVar3[3] = 3;
  puVar3[4] = 2;
  uVar1 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_2,(cTgaHeader *)0x0,0);
  *(undefined4 *)(puVar3 + 8) = 0;
  *(undefined4 *)(puVar3 + 0x12) = 0;
  *(undefined4 *)(puVar3 + 0x14) = 0;
  *(undefined4 *)(puVar3 + 10) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0xe) = 0x3f800000;
  *(undefined4 *)(puVar3 + 0x16) = 0;
  *(float *)(puVar3 + 0xc) = param_3 + 1.0;
  *(float *)(puVar3 + 0x10) = param_3 + 1.0;
  *(undefined4 *)(puVar3 + 6) = uVar1;
  return;
}
