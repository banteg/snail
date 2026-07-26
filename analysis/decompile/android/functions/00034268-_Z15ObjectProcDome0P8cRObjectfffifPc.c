/*
 * mangled: _Z15ObjectProcDome0P8cRObjectfffifPc
 * demangled: ObjectProcDome0(cRObject*, float, float, float, int, float, char*)
 * address: 00034268
 * size: 580
 */

/* ObjectProcDome0(cRObject*, float, float, float, int, float, char*) */

void ObjectProcDome0(cRObject *param_1,float param_2,float param_3,float param_4,int param_5,
                    float param_6,char *param_7)

{
  float *pfVar1;
  undefined2 *puVar2;
  short sVar3;
  short sVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  float in_r3;
  float *pfVar9;
  undefined2 *puVar10;
  uint in_fpscr;
  float fVar11;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float fVar12;
  float fVar13;
  float fVar14;
  int in_stack_00000000;
  char *in_stack_00000008;

  fVar13 = (float)VectorSignedToFloat(in_stack_00000000,(byte)(in_fpscr >> 0x16) & 3);
  cRObject::RequestVertices(param_1,(in_stack_00000000 + 1) * (in_stack_00000000 + 1));
  fVar11 = (float)cRObject::RequestFaceQuads(param_1,in_stack_00000000 * in_stack_00000000);
  pfVar9 = *(float **)(param_1 + 0xa4);
  if (0.0 <= fVar13) {
    fVar14 = 0.0;
    do {
      fVar12 = 0.0;
      pfVar1 = pfVar9;
      do {
        pfVar9 = pfVar1 + 3;
        fVar12 = fVar12 + 1.0;
        fVar11 = (float)Sin(fVar11);
        fVar5 = (float)Cos(extraout_s0);
        fVar6 = (float)Cos(extraout_s0_00);
        fVar7 = (float)Sin(extraout_s0_01);
        pfVar1[1] = (float)param_5 + ((float)param_7 / fVar13) * fVar14;
        *pfVar1 = -((fVar11 + fVar5) * in_r3);
        pfVar1[2] = (fVar6 - fVar7) * in_r3;
        fVar11 = (float)Cos(extraout_s0_02);
        pfVar1[2] = pfVar1[2] * fVar11;
        *pfVar1 = *pfVar1 * fVar11;
        fVar11 = extraout_s0_03;
        pfVar1 = pfVar9;
      } while (fVar12 <= fVar13);
      fVar14 = fVar14 + 1.0;
    } while (fVar14 <= fVar13);
  }
  puVar10 = *(undefined2 **)(param_1 + 200);
  fVar11 = 1.0 / fVar13;
  if (0.0 < fVar13) {
    fVar14 = 0.0;
    do {
      fVar12 = 0.0;
      fVar5 = fVar14 * fVar11 + 0.0;
      puVar2 = puVar10;
      do {
        puVar10 = puVar2 + 0x18;
        *(float *)(puVar2 + 8) = fVar5;
        *puVar2 = 0;
        *(float *)(puVar2 + 0xc) = fVar11 + fVar5;
        *(float *)(puVar2 + 0x10) = fVar11 + fVar5;
        *(float *)(puVar2 + 0x14) = fVar5;
        fVar6 = fVar12 * fVar11 + 0.0;
        *(float *)(puVar2 + 10) = fVar6;
        *(float *)(puVar2 + 0xe) = fVar6;
        sVar4 = (short)(int)(fVar14 + (fVar13 + 1.0) * fVar12);
        puVar2[1] = sVar4;
        sVar3 = sVar4 + (short)in_stack_00000000;
        puVar2[2] = sVar4 + 1;
        puVar2[4] = sVar3 + 1;
        puVar2[3] = sVar3 + 2;
        *(float *)(puVar2 + 0x16) = fVar11 + fVar6;
        *(float *)(puVar2 + 0x12) = fVar11 + fVar6;
        uVar8 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0,0);
        fVar12 = fVar12 + 1.0;
        *(undefined4 *)(puVar2 + 6) = uVar8;
        puVar2 = puVar10;
      } while (fVar12 < fVar13);
      fVar14 = fVar14 + 1.0;
    } while (fVar14 < fVar13);
  }
  return;
}
