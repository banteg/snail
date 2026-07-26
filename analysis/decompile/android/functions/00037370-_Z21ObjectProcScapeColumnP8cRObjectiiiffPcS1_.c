/*
 * mangled: _Z21ObjectProcScapeColumnP8cRObjectiiiffPcS1_
 * demangled: ObjectProcScapeColumn(cRObject*, int, int, int, float, float, char*, char*)
 * address: 00037370
 * size: 920
 */

/* ObjectProcScapeColumn(cRObject*, int, int, int, float, float, char*, char*) */

void ObjectProcScapeColumn
               (cRObject *param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
               char *param_7,char *param_8)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  float *pfVar5;
  undefined2 *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  tColour *ptVar10;
  int iVar11;
  uint in_fpscr;
  float fVar12;
  float extraout_s0;
  float extraout_s0_00;
  float fVar13;
  float fVar14;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  tColour *local_6c;
  float *local_68;
  uint local_64;
  undefined2 *local_60;

  uVar3 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar3 + uVar3);
  cRObject::RequestColours(param_1);
  fVar12 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_60 = *(undefined2 **)(param_1 + 200);
  local_68 = *(float **)(param_1 + 0xa4);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  local_6c = *(tColour **)(param_1 + 0xb4);
  if (-1 < param_2) {
    fVar14 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar11 = 0;
    do {
      VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
      if (-1 < param_3) {
        iVar7 = 0;
        pfVar5 = local_68;
        ptVar10 = local_6c;
        do {
          fVar12 = (float)Sin(fVar12);
          *pfVar5 = -((float)param_7 + fVar12 * (float)param_8);
          fVar12 = (float)Cos(extraout_s0);
          fVar13 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
          iVar7 = iVar7 + 1;
          pfVar5[1] = fVar13 * 80.0 - 40.0;
          pfVar5[2] = ((float)param_8 + (float)param_8) * fVar12;
          pfVar5 = pfVar5 + uVar3 * 3;
          fVar12 = (float)tColour::Grey(ptVar10,extraout_s0_00);
          ptVar10 = ptVar10 + uVar3 * 0x10;
        } while (iVar7 <= param_3);
      }
      iVar11 = iVar11 + 1;
      local_68 = local_68 + 3;
      local_6c = local_6c + 0x10;
    } while (iVar11 <= param_2);
    if (0 < param_2) {
      uVar3 = uVar3 & 0xffff;
      uVar4 = param_2 - 1;
      local_68 = (float *)0x1;
      local_6c = (tColour *)0x0;
      local_64 = uVar3;
      do {
        local_64 = local_64 + 1 & 0xffff;
        if (0 < param_3) {
          if ((tColour *)uVar4 == local_6c) {
            fVar13 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
            iVar11 = 0;
            fVar12 = (float)VectorSignedToFloat(local_68,(byte)(in_fpscr >> 0x16) & 3);
            puVar6 = local_60;
            uVar9 = local_64;
            uVar8 = uVar4;
            do {
              puVar6[1] = (short)uVar8;
              puVar6[3] = (short)uVar9;
              puVar6[2] = (short)uVar8 + 1;
              puVar6[4] = (short)uVar9 + -1;
              *puVar6 = 0;
              uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0
                                      ,0);
              iVar11 = iVar11 + 1;
              uVar8 = (uVar8 & 0xffff) + uVar3;
              *(undefined4 *)(puVar6 + 10) = 0;
              *(undefined4 *)(puVar6 + 0xe) = 0;
              *(undefined4 *)(puVar6 + 0x12) = 0x3f800000;
              *(undefined4 *)(puVar6 + 0x16) = 0x3f800000;
              uVar9 = uVar9 + uVar3 & 0xffff;
              *(undefined4 *)(puVar6 + 6) = uVar2;
              *(float *)(puVar6 + 0x14) = fVar13 / fVar14;
              *(float *)(puVar6 + 8) = fVar13 / fVar14;
              *(float *)(puVar6 + 0x10) = fVar12 / fVar14;
              *(float *)(puVar6 + 0xc) = fVar12 / fVar14;
              puVar6 = puVar6 + param_2 * 0x18;
            } while (iVar11 < param_3);
          }
          else {
            fVar12 = (float)VectorSignedToFloat(local_68,(byte)(in_fpscr >> 0x16) & 3);
            iVar11 = 0;
            fVar13 = (float)VectorSignedToFloat(local_6c,(byte)(in_fpscr >> 0x16) & 3);
            puVar6 = local_60;
            uVar8 = local_64;
            ptVar10 = local_6c;
            do {
              puVar6[1] = (short)ptVar10;
              puVar6[3] = (short)uVar8;
              puVar6[2] = (short)ptVar10 + 1;
              puVar6[4] = (short)uVar8 + -1;
              *puVar6 = 0;
              uVar2 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              iVar11 = iVar11 + 1;
              ptVar10 = (tColour *)(((uint)ptVar10 & 0xffff) + uVar3);
              *(undefined4 *)(puVar6 + 10) = 0;
              *(undefined4 *)(puVar6 + 0xe) = 0;
              *(undefined4 *)(puVar6 + 0x12) = 0x3f800000;
              *(undefined4 *)(puVar6 + 0x16) = 0x3f800000;
              uVar8 = uVar8 + uVar3 & 0xffff;
              *(undefined4 *)(puVar6 + 6) = uVar2;
              *(float *)(puVar6 + 0x14) = fVar13 / fVar14;
              *(float *)(puVar6 + 8) = fVar13 / fVar14;
              *(float *)(puVar6 + 0x10) = fVar12 / fVar14;
              *(float *)(puVar6 + 0xc) = fVar12 / fVar14;
              puVar6 = puVar6 + param_2 * 0x18;
            } while (iVar11 < param_3);
          }
        }
        local_60 = local_60 + 0x18;
        local_6c = (tColour *)((int)local_6c + 1);
        bVar1 = (int)local_68 < param_2;
        local_68 = (float *)((int)local_68 + 1);
      } while (bVar1);
    }
  }
  return;
}
