/*
 * mangled: _Z26ObjectProcScapeAcceleratorP8cRObjectiiiffPcS1_
 * demangled: ObjectProcScapeAccelerator(cRObject*, int, int, int, float, float, char*, char*)
 * address: 000392a8
 * size: 1172
 */

/* ObjectProcScapeAccelerator(cRObject*, int, int, int, float, float, char*, char*) */

void ObjectProcScapeAccelerator
               (cRObject *param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
               char *param_7,char *param_8)

{
  undefined2 uVar1;
  undefined2 uVar2;
  float fVar3;
  undefined4 uVar4;
  uint uVar5;
  float *pfVar6;
  undefined2 *puVar7;
  tColour *ptVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  bool bVar13;
  uint in_fpscr;
  uint uVar14;
  float fVar15;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar16;
  float fVar17;
  float fVar18;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  uint local_88;
  tColour *local_80;
  undefined2 *local_78;
  float *local_74;

  uVar5 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar5 + uVar5);
  cRObject::RequestColours(param_1);
  fVar15 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_78 = *(undefined2 **)(param_1 + 200);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  local_74 = *(float **)(param_1 + 0xa4);
  local_80 = *(tColour **)(param_1 + 0xb4);
  if (-1 < param_2) {
    VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    local_88 = 0;
    uVar14 = in_fpscr & 0xfffffff | (uint)((float)param_7 < 0.0) << 0x1f;
    bVar13 = SUB41(uVar14 >> 0x1f,0);
    do {
      VectorSignedToFloat(local_88,(byte)(uVar14 >> 0x16) & 3);
      if (-1 < param_3) {
        VectorSignedToFloat(param_3,(byte)(uVar14 >> 0x16) & 3);
        iVar9 = 0;
        fVar18 = (float)VectorSignedToFloat(param_4,(byte)(uVar14 >> 0x16) & 3);
        pfVar6 = local_74;
        ptVar8 = local_80;
        do {
          fVar17 = (float)VectorSignedToFloat(iVar9,(byte)(uVar14 >> 0x16) & 3);
          fVar15 = (float)Sin(fVar15);
          fVar15 = (float)param_8 + (1.0 - fVar15) * 9.0;
          if ((local_88 & 1) != 0) {
            fVar15 = fVar15 * 0.6;
          }
          if (bVar13) {
            fVar16 = -1.0;
          }
          else {
            uVar14 = uVar14 & 0xfffffff | (uint)((float)param_7 == 0.0) << 0x1e;
            fVar16 = (float)VectorSignedToFloat((uint)!SUB41(uVar14 >> 0x1e,0),
                                                (byte)(uVar14 >> 0x16) & 3);
          }
          fVar3 = (float)Sin(extraout_s0_01);
          *pfVar6 = fVar16 * fVar15 * fVar3;
          fVar16 = (float)Cos(extraout_s0);
          fVar17 = fVar17 * fVar18 * 0.2;
          pfVar6[2] = fVar17;
          pfVar6[1] = -(fVar15 * fVar16);
          if ((local_88 & 3) == 1) {
            fVar15 = (float)VectorSignedToFloat(local_88 & 1,(byte)(uVar14 >> 0x16) & 3);
            pfVar6[2] = fVar17 + (fVar15 + fVar15 + fVar15 + fVar15) * 10.0;
          }
          if (param_2 == local_88 || local_88 == 0) {
            fVar15 = (float)Sin(extraout_s0_00);
            fVar15 = (float)tColour::Grey(ptVar8,fVar15);
          }
          else {
            fVar15 = (float)RAND(extraout_s0_00,(char *)0x3f4ccccd);
            fVar15 = (float)tColour::Grey(ptVar8,fVar15);
          }
          uVar14 = uVar14 & 0xfffffff | (uint)(pfVar6[1] < -3.0) << 0x1f;
          if (SUB41(uVar14 >> 0x1f,0)) {
            *(float *)ptVar8 = *(float *)ptVar8 * 0.4;
            *(float *)(ptVar8 + 4) = *(float *)(ptVar8 + 4) * 0.4;
            *(float *)(ptVar8 + 8) = *(float *)(ptVar8 + 8) * 0.4;
          }
          iVar9 = iVar9 + 1;
          ptVar8 = ptVar8 + uVar5 * 0x10;
          pfVar6 = pfVar6 + uVar5 * 3;
        } while (iVar9 <= param_3);
      }
      local_88 = local_88 + 1;
      local_74 = local_74 + 3;
      local_80 = local_80 + 0x10;
    } while ((int)local_88 <= param_2);
    if (0 < param_2) {
      uVar12 = 0;
      uVar5 = uVar5 & 0xffff;
      local_80 = (tColour *)uVar5;
      do {
        local_80 = (tColour *)((int)local_80 + 1U & 0xffff);
        if (0 < param_3) {
          fVar15 = (float)VectorSignedToFloat(param_3,(byte)(uVar14 >> 0x16) & 3);
          puVar7 = local_78;
          ptVar8 = local_80;
          iVar9 = 0;
          uVar10 = uVar12;
          do {
            puVar7[2] = (short)uVar10 + 1;
            puVar7[1] = (short)uVar10;
            *puVar7 = 0;
            iVar11 = iVar9 + 1;
            puVar7[3] = (short)ptVar8;
            puVar7[4] = (short)ptVar8 + -1;
            if (uVar12 == param_2 - 1U) {
              uVar4 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar7 + 6) = uVar4;
            }
            else {
              uVar4 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar7 + 6) = uVar4;
            }
            fVar18 = (float)VectorSignedToFloat(iVar9,(byte)(uVar14 >> 0x16) & 3);
            uVar10 = uVar5 + (uVar10 & 0xffff);
            *(undefined4 *)(puVar7 + 8) = 0;
            *(undefined4 *)(puVar7 + 0xc) = 0x3f800000;
            *(undefined4 *)(puVar7 + 0x10) = 0x3f800000;
            *(undefined4 *)(puVar7 + 0x14) = 0;
            ptVar8 = (tColour *)(uVar5 + (int)ptVar8 & 0xffff);
            fVar17 = (float)VectorSignedToFloat(iVar11,(byte)(uVar14 >> 0x16) & 3);
            *(float *)(puVar7 + 0xe) = fVar18 / fVar15;
            *(float *)(puVar7 + 10) = fVar18 / fVar15;
            *(float *)(puVar7 + 0x16) = fVar17 / fVar15;
            *(float *)(puVar7 + 0x12) = fVar17 / fVar15;
            if (bVar13) {
              *(undefined4 *)(puVar7 + 8) = 0x3f800000;
              uVar1 = puVar7[3];
              *(undefined4 *)(puVar7 + 0xc) = 0;
              uVar2 = puVar7[2];
              *(undefined4 *)(puVar7 + 0x10) = 0;
              *(undefined4 *)(puVar7 + 0x14) = 0x3f800000;
              puVar7[2] = puVar7[1];
              puVar7[1] = uVar2;
              puVar7[3] = puVar7[4];
              puVar7[4] = uVar1;
            }
            puVar7 = puVar7 + param_2 * 0x18;
            iVar9 = iVar11;
          } while (iVar11 < param_3);
        }
        uVar12 = uVar12 + 1;
        local_78 = local_78 + 0x18;
      } while ((int)uVar12 < param_2);
    }
  }
  return;
}
