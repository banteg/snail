/*
 * mangled: _Z20ObjectProcClickStartP8cRObjectiffPc
 * demangled: ObjectProcClickStart(cRObject*, int, float, float, char*)
 * address: 00034098
 * size: 440
 */

/* ObjectProcClickStart(cRObject*, int, float, float, char*) */

void ObjectProcClickStart(cRObject *param_1,int param_2,float param_3,float param_4,char *param_5)

{
  short sVar1;
  undefined4 uVar2;
  int extraout_r1;
  int extraout_r1_00;
  float in_r3;
  undefined2 *puVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar9;
  float fVar10;
  char *in_stack_00000000;

  cRObject::RequestVertices(param_1,param_2 << 1);
  fVar8 = (float)cRObject::RequestFaceQuads(param_1,param_2);
  puVar3 = *(undefined2 **)(param_1 + 200);
  pfVar4 = *(float **)(param_1 + 0xa4);
  if (0 < param_2) {
    fVar10 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = 0;
    do {
      VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      iVar6 = iVar6 + 1;
      fVar8 = (float)Sin(fVar8);
      pfVar4[1] = 0.0;
      *pfVar4 = -(fVar8 * in_r3 * 1.13);
      fVar8 = (float)Cos(extraout_s0);
      pfVar4[2] = fVar8 * in_r3 * 1.13;
      fVar8 = (float)Sin(extraout_s0_00);
      pfVar4[4] = (float)param_5;
      pfVar4[3] = -(fVar8 * in_r3);
      fVar8 = (float)Cos(extraout_s0_01);
      pfVar4[5] = fVar8 * in_r3;
      pfVar4 = pfVar4 + 6;
      fVar8 = extraout_s0_02;
    } while (iVar6 < param_2);
    iVar6 = 0;
    iVar7 = param_2;
    do {
      iVar5 = iVar6 + 1;
      *puVar3 = 0;
      __aeabi_idivmod(iVar5,param_2);
      sVar1 = (short)(extraout_r1 << 1);
      puVar3[1] = sVar1 + 1;
      __aeabi_idivmod(iVar6,param_2);
      puVar3[4] = sVar1;
      sVar1 = (short)(extraout_r1_00 << 1);
      puVar3[3] = sVar1;
      puVar3[2] = sVar1 + 1;
      uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000000,(cTgaHeader *)0x0,0);
      fVar8 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(puVar3 + 10) = 0x3f800000;
      *(undefined4 *)(puVar3 + 0xe) = 0x3f800000;
      *(undefined4 *)(puVar3 + 0x12) = 0;
      *(undefined4 *)(puVar3 + 0x16) = 0;
      iVar7 = iVar7 + -1;
      fVar9 = (float)VectorSignedToFloat(param_2 - iVar5,(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = fVar8 * (1.0 / fVar10);
      fVar9 = fVar9 * (1.0 / fVar10);
      *(float *)(puVar3 + 0x10) = fVar8;
      *(float *)(puVar3 + 0xc) = fVar8;
      *(undefined4 *)(puVar3 + 6) = uVar2;
      *(float *)(puVar3 + 0x14) = fVar9;
      *(float *)(puVar3 + 8) = fVar9;
      puVar3 = puVar3 + 0x18;
      iVar6 = iVar5;
    } while (iVar5 < param_2);
  }
  return;
}
