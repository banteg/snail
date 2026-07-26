/*
 * mangled: _Z18ObjectProcScapeFlyP8cRObjectiiiffPcS1_
 * demangled: ObjectProcScapeFly(cRObject*, int, int, int, float, float, char*, char*)
 * address: 0003896c
 * size: 932
 */

/* ObjectProcScapeFly(cRObject*, int, int, int, float, float, char*, char*) */

void ObjectProcScapeFly(cRObject *param_1,int param_2,int param_3,int param_4,float param_5,
                       float param_6,char *param_7,char *param_8)

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
  float *pfVar12;
  uint in_fpscr;
  float fVar13;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar14;
  float fVar15;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  tColour *local_74;
  int local_70;
  undefined2 *local_6c;
  uint local_68;

  uVar3 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar3 + uVar3);
  cRObject::RequestColours(param_1);
  fVar13 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_6c = *(undefined2 **)(param_1 + 200);
  pfVar12 = *(float **)(param_1 + 0xa4);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  local_74 = *(tColour **)(param_1 + 0xb4);
  if (-1 < param_2) {
    fVar14 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar11 = 0;
    do {
      VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
      if (-1 < param_3) {
        iVar7 = 0;
        pfVar5 = pfVar12;
        ptVar10 = local_74;
        do {
          iVar7 = iVar7 + 1;
          fVar13 = (float)Sin(fVar13);
          *pfVar5 = (float)param_7 + fVar13 * (float)param_8;
          fVar13 = (float)Cos(extraout_s0);
          pfVar5[2] = (float)param_8 * -2.0 * fVar13;
          fVar13 = (float)Sin(extraout_s0_00);
          pfVar5[1] = ((float)param_8 + (float)param_8) * fVar13;
          pfVar5 = pfVar5 + uVar3 * 3;
          fVar13 = (float)RAND(extraout_s0_01,(char *)0x3f000000);
          fVar13 = (float)tColour::Grey(ptVar10,fVar13);
          ptVar10 = ptVar10 + uVar3 * 0x10;
        } while (iVar7 <= param_3);
      }
      iVar11 = iVar11 + 1;
      pfVar12 = pfVar12 + 3;
      local_74 = local_74 + 0x10;
    } while (iVar11 <= param_2);
    if (0 < param_2) {
      local_70 = 1;
      uVar3 = uVar3 & 0xffff;
      local_74 = (tColour *)0x0;
      uVar4 = param_2 - 1;
      local_68 = uVar3;
      do {
        local_68 = local_68 + 1 & 0xffff;
        if (0 < param_3) {
          if ((tColour *)uVar4 == local_74) {
            fVar15 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
            iVar11 = 0;
            fVar13 = (float)VectorSignedToFloat(local_70,(byte)(in_fpscr >> 0x16) & 3);
            puVar6 = local_6c;
            uVar9 = local_68;
            uVar8 = uVar4;
            do {
              puVar6[1] = (short)uVar8;
              puVar6[3] = (short)uVar9;
              *puVar6 = 0;
              puVar6[2] = (short)uVar8 + 1;
              puVar6[4] = (short)uVar9 + -1;
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
              *(float *)(puVar6 + 0x14) = fVar15 / fVar14;
              *(float *)(puVar6 + 8) = fVar15 / fVar14;
              *(float *)(puVar6 + 0x10) = fVar13 / fVar14;
              *(float *)(puVar6 + 0xc) = fVar13 / fVar14;
              puVar6 = puVar6 + param_2 * 0x18;
            } while (iVar11 < param_3);
          }
          else {
            fVar13 = (float)VectorSignedToFloat(local_70,(byte)(in_fpscr >> 0x16) & 3);
            iVar11 = 0;
            fVar15 = (float)VectorSignedToFloat(local_74,(byte)(in_fpscr >> 0x16) & 3);
            puVar6 = local_6c;
            uVar8 = local_68;
            ptVar10 = local_74;
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
              *(float *)(puVar6 + 0x14) = fVar15 / fVar14;
              *(float *)(puVar6 + 8) = fVar15 / fVar14;
              *(float *)(puVar6 + 0x10) = fVar13 / fVar14;
              *(float *)(puVar6 + 0xc) = fVar13 / fVar14;
              puVar6 = puVar6 + param_2 * 0x18;
            } while (iVar11 < param_3);
          }
        }
        local_74 = (tColour *)((int)local_74 + 1);
        local_6c = local_6c + 0x18;
        bVar1 = local_70 < param_2;
        local_70 = local_70 + 1;
      } while (bVar1);
    }
  }
  return;
}
