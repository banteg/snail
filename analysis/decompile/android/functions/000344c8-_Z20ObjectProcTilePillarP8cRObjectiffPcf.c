/*
 * mangled: _Z20ObjectProcTilePillarP8cRObjectiffPcf
 * demangled: ObjectProcTilePillar(cRObject*, int, float, float, char*, float)
 * address: 000344c8
 * size: 560
 */

/* ObjectProcTilePillar(cRObject*, int, float, float, char*, float) */

void ObjectProcTilePillar
               (cRObject *param_1,int param_2,float param_3,float param_4,char *param_5,
               float param_6)

{
  short sVar1;
  undefined4 uVar2;
  short extraout_r1;
  float in_r3;
  undefined2 *puVar3;
  float *pfVar4;
  short sVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  char *in_stack_00000000;
  float in_stack_00000004;

  cRObject::RequestVertices(param_1,param_2 * 3);
  fVar7 = (float)cRObject::RequestFaceQuads(param_1,param_2 * 2);
  puVar3 = *(undefined2 **)(param_1 + 200);
  pfVar4 = *(float **)(param_1 + 0xa4);
  if (0 < param_2) {
    fVar9 = in_stack_00000004 * 0.5;
    sVar5 = 0;
    iVar6 = 0;
    fVar11 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    do {
      fVar10 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      iVar6 = iVar6 + 1;
      fVar8 = fVar10 / fVar11;
      fVar7 = (float)Sin(fVar7);
      pfVar4[1] = (float)param_5;
      *pfVar4 = fVar9 + fVar7 * in_r3 * 1.08 * (in_stack_00000004 + 1.0);
      fVar7 = (float)Cos(extraout_s0);
      pfVar4[2] = fVar7 * in_r3 * 1.08;
      fVar7 = (float)Sin(extraout_s0_00);
      pfVar4[4] = -1.0;
      pfVar4[3] = fVar9 + (in_stack_00000004 + 1.0) * fVar7 * in_r3 * 0.88;
      fVar7 = (float)Cos(extraout_s0_01);
      pfVar4[6] = fVar9;
      *puVar3 = 0;
      pfVar4[8] = 0.0;
      pfVar4[7] = (float)param_5 * 1.1;
      fVar10 = (fVar10 + 1.0) / fVar11;
      pfVar4[5] = fVar7 * in_r3 * 0.88;
      pfVar4 = pfVar4 + 9;
      __aeabi_idivmod(iVar6,param_2);
      puVar3[3] = sVar5;
      puVar3[2] = sVar5 + 1;
      sVar1 = extraout_r1 * 3;
      puVar3[4] = sVar1;
      puVar3[1] = sVar1 + 1;
      uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000000,(cTgaHeader *)0x0,0);
      puVar3[0x1a] = sVar5;
      *(undefined4 *)(puVar3 + 10) = 0;
      puVar3[0x19] = sVar1;
      *(float *)(puVar3 + 0xc) = fVar8;
      *(undefined4 *)(puVar3 + 0xe) = 0;
      *(float *)(puVar3 + 0x10) = fVar8;
      *(undefined4 *)(puVar3 + 0x12) = 0x3f800000;
      *(undefined4 *)(puVar3 + 0x16) = 0x3f800000;
      *(float *)(puVar3 + 8) = fVar10;
      puVar3[0x18] = 0;
      *(float *)(puVar3 + 0x14) = fVar10;
      puVar3[0x1b] = sVar5 + 2;
      puVar3[0x1c] = sVar1 + 2;
      sVar5 = sVar5 + 3;
      *(undefined4 *)(puVar3 + 6) = uVar2;
      uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000000,(cTgaHeader *)0x0,0);
      *(float *)(puVar3 + 0x28) = fVar8;
      *(float *)(puVar3 + 0x2c) = fVar10;
      *(float *)(puVar3 + 0x20) = fVar10;
      *(undefined4 *)(puVar3 + 0x22) = 0x3f800000;
      *(float *)(puVar3 + 0x24) = fVar8;
      *(undefined4 *)(puVar3 + 0x26) = 0x3f800000;
      *(undefined4 *)(puVar3 + 0x2a) = 0;
      *(undefined4 *)(puVar3 + 0x2e) = 0;
      *(undefined4 *)(puVar3 + 0x1e) = uVar2;
      puVar3 = puVar3 + 0x30;
      fVar7 = extraout_s0_02;
    } while (iVar6 < param_2);
  }
  return;
}
