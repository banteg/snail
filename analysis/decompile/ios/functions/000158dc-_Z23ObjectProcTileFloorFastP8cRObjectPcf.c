/*
 * mangled: _Z23ObjectProcTileFloorFastP8cRObjectPcf
 * demangled: ObjectProcTileFloorFast(cRObject*, char*, float)
 * address: 000158dc
 * size: 264
 */

/* ObjectProcTileFloorFast(cRObject*, char*, float) */

void ObjectProcTileFloorFast(cRObject *param_1,char *param_2,float param_3)

{
  undefined4 uVar1;
  float *pfVar2;
  undefined2 *puVar3;
  float fVar4;

  cRObject::RequestVertices(param_1,4);
  cRObject::RequestFaceQuads(param_1,1);
  *(uint *)param_1 = *(uint *)param_1 | 0x8000080;
  pfVar2 = *(float **)(param_1 + 0xa4);
  puVar3 = *(undefined2 **)(param_1 + 200);
  pfVar2[3] = -0.5;
  pfVar2[8] = -0.5;
  pfVar2[9] = -0.5;
  pfVar2[0xb] = -0.5;
  *pfVar2 = param_3 + 0.5;
  pfVar2[2] = 0.5;
  pfVar2[5] = 0.5;
  pfVar2[6] = param_3 + 0.5;
  pfVar2[1] = 0.0;
  pfVar2[4] = 0.0;
  pfVar2[7] = 0.0;
  pfVar2[10] = 0.0;
  puVar3[2] = 1;
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[4] = 2;
  puVar3[3] = 3;
  uVar1 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_2,(cTgaHeader *)0x0,0);
  *(undefined4 *)(puVar3 + 10) = 0x3e000000;
  *(undefined4 *)(puVar3 + 0xc) = 0;
  *(undefined4 *)(puVar3 + 0xe) = 0x3e000000;
  *(undefined4 *)(puVar3 + 0x10) = 0;
  *(undefined4 *)(puVar3 + 0x12) = 0;
  *(undefined4 *)(puVar3 + 0x16) = 0;
  fVar4 = (param_3 + 1.0) * -0.125;
  *(float *)(puVar3 + 8) = fVar4;
  *(float *)(puVar3 + 0x14) = fVar4;
  *(undefined4 *)(puVar3 + 6) = uVar1;
  return;
}
