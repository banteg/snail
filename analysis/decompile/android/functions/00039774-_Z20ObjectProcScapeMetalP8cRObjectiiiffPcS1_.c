/*
 * mangled: _Z20ObjectProcScapeMetalP8cRObjectiiiffPcS1_
 * demangled: ObjectProcScapeMetal(cRObject*, int, int, int, float, float, char*, char*)
 * address: 00039774
 * size: 1492
 */

/* ObjectProcScapeMetal(cRObject*, int, int, int, float, float, char*, char*) */

void ObjectProcScapeMetal
               (cRObject *param_1,int param_2,int param_3,int param_4,float param_5,float param_6,
               char *param_7,char *param_8)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined2 *puVar5;
  float *pfVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  tColour *ptVar10;
  int iVar11;
  uint uVar12;
  float *pfVar13;
  bool bVar14;
  uint in_fpscr;
  float fVar15;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float extraout_s0_06;
  float fVar16;
  float fVar17;
  float fVar18;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  tColour *local_7c;
  undefined2 *local_68;
  uint local_64;

  uVar4 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar4 + uVar4);
  cRObject::RequestColours(param_1);
  fVar15 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_68 = *(undefined2 **)(param_1 + 200);
  *(uint *)param_1 = *(uint *)param_1 | 0x10080;
  local_7c = *(tColour **)(param_1 + 0xb4);
  pfVar13 = *(float **)(param_1 + 0xa4);
  if (-1 < param_2) {
    VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar11 = 0;
    uVar12 = in_fpscr & 0xfffffff | (uint)((float)param_7 < 0.0) << 0x1f;
    bVar14 = SUB41(uVar12 >> 0x1f,0);
    do {
      while (VectorSignedToFloat(iVar11,(byte)(uVar12 >> 0x16) & 3), -1 < param_3) {
        fVar17 = -(float)param_8;
        if (bVar14) {
          if (param_2 != iVar11 && iVar11 != 0) {
            fVar18 = (float)VectorSignedToFloat(param_4,(byte)(uVar12 >> 0x16) & 3);
            iVar8 = 0;
            pfVar6 = pfVar13;
            ptVar10 = local_7c;
            do {
              fVar15 = (float)Sin(fVar15);
              *pfVar6 = fVar17 * fVar15 * 4.0;
              fVar15 = (float)Cos(extraout_s0_01);
              fVar16 = (float)VectorSignedToFloat(iVar8,(byte)(uVar12 >> 0x16) & 3);
              iVar8 = iVar8 + 1;
              pfVar6[2] = fVar18 * fVar16;
              pfVar6[1] = fVar15 * fVar17 * 0.9 + 5.0;
              pfVar6 = pfVar6 + uVar4 * 3;
              fVar15 = (float)RAND(extraout_s0_02,(char *)0x3f800000);
              fVar15 = (float)tColour::Grey(ptVar10,fVar15);
              ptVar10 = ptVar10 + uVar4 * 0x10;
            } while (iVar8 <= param_3);
          }
          else {
            fVar18 = (float)VectorSignedToFloat(param_4,(byte)(uVar12 >> 0x16) & 3);
            iVar8 = 0;
            pfVar6 = pfVar13;
            ptVar10 = local_7c;
            do {
              fVar15 = (float)Sin(fVar15);
              *pfVar6 = fVar15 * fVar17 * 4.0;
              fVar15 = (float)Cos(extraout_s0_05);
              fVar16 = (float)VectorSignedToFloat(iVar8,(byte)(uVar12 >> 0x16) & 3);
              iVar8 = iVar8 + 1;
              pfVar6[2] = fVar18 * fVar16;
              pfVar6[1] = fVar15 * fVar17 * 0.9 + 5.0;
              *pfVar6 = 0.0;
              fVar15 = (float)Sin(extraout_s0_06);
              fVar15 = (float)tColour::Grey(ptVar10,fVar15);
              pfVar6 = pfVar6 + uVar4 * 3;
              ptVar10 = ptVar10 + uVar4 * 0x10;
            } while (iVar8 <= param_3);
          }
        }
        else {
          if (param_2 != iVar11 && iVar11 != 0) {
            fVar18 = (float)VectorSignedToFloat(param_4,(byte)(uVar12 >> 0x16) & 3);
            iVar8 = 0;
            pfVar6 = pfVar13;
            ptVar10 = local_7c;
            do {
              fVar15 = (float)Sin(fVar15);
              uVar12 = uVar12 & 0xfffffff | (uint)((float)param_7 == 0.0) << 0x1e;
              fVar16 = (float)VectorSignedToFloat((uint)!SUB41(uVar12 >> 0x1e,0),
                                                  (byte)(uVar12 >> 0x16) & 3);
              *pfVar6 = (float)param_8 * fVar16 * fVar15 * 4.0;
              fVar15 = (float)Cos(extraout_s0);
              fVar16 = (float)VectorSignedToFloat(iVar8,(byte)(uVar12 >> 0x16) & 3);
              iVar8 = iVar8 + 1;
              pfVar6[2] = fVar18 * fVar16;
              pfVar6[1] = fVar15 * fVar17 * 0.9 + 5.0;
              pfVar6 = pfVar6 + uVar4 * 3;
              fVar15 = (float)RAND(extraout_s0_00,(char *)0x3f800000);
              fVar15 = (float)tColour::Grey(ptVar10,fVar15);
              ptVar10 = ptVar10 + uVar4 * 0x10;
            } while (iVar8 <= param_3);
            break;
          }
          fVar18 = (float)VectorSignedToFloat(param_4,(byte)(uVar12 >> 0x16) & 3);
          iVar8 = 0;
          pfVar6 = pfVar13;
          ptVar10 = local_7c;
          do {
            fVar15 = (float)Sin(fVar15);
            uVar12 = uVar12 & 0xfffffff | (uint)((float)param_7 == 0.0) << 0x1e;
            fVar16 = (float)VectorSignedToFloat((uint)!SUB41(uVar12 >> 0x1e,0),
                                                (byte)(uVar12 >> 0x16) & 3);
            *pfVar6 = (float)param_8 * fVar16 * fVar15 * 4.0;
            fVar15 = (float)Cos(extraout_s0_03);
            fVar16 = (float)VectorSignedToFloat(iVar8,(byte)(uVar12 >> 0x16) & 3);
            iVar8 = iVar8 + 1;
            pfVar6[2] = fVar18 * fVar16;
            pfVar6[1] = fVar15 * fVar17 * 0.9 + 5.0;
            *pfVar6 = 0.0;
            fVar15 = (float)Sin(extraout_s0_04);
            fVar15 = (float)tColour::Grey(ptVar10,fVar15);
            pfVar6 = pfVar6 + uVar4 * 3;
            ptVar10 = ptVar10 + uVar4 * 0x10;
          } while (iVar8 <= param_3);
        }
        local_7c = local_7c + 0x10;
        pfVar13 = pfVar13 + 3;
        iVar11 = iVar11 + 1;
        if (param_2 < iVar11) goto LAB_00039948;
      }
      iVar11 = iVar11 + 1;
      pfVar13 = pfVar13 + 3;
      local_7c = local_7c + 0x10;
    } while (iVar11 <= param_2);
LAB_00039948:
    if (0 < param_2) {
      uVar12 = 0;
      uVar4 = uVar4 & 0xffff;
      local_64 = uVar4;
      do {
        local_64 = local_64 + 1 & 0xffff;
        if (0 < param_3) {
          iVar11 = 0;
          puVar5 = local_68;
          uVar7 = local_64;
          uVar9 = uVar12;
          do {
            puVar5[2] = (short)uVar9 + 1;
            puVar5[1] = (short)uVar9;
            iVar11 = iVar11 + 1;
            *puVar5 = 0;
            puVar5[3] = (short)uVar7;
            puVar5[4] = (short)uVar7 + -1;
            if (uVar12 == param_2 - 1U) {
              uVar3 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar5 + 6) = uVar3;
            }
            else {
              uVar3 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar5 + 6) = uVar3;
            }
            *(undefined4 *)(puVar5 + 8) = 0;
            *(undefined4 *)(puVar5 + 0x14) = 0;
            *(undefined4 *)(puVar5 + 0xc) = 0x3f800000;
            *(undefined4 *)(puVar5 + 0x10) = 0x3f800000;
            *(undefined4 *)(puVar5 + 10) = 0x3f800000;
            *(undefined4 *)(puVar5 + 0xe) = 0x3f800000;
            *(undefined4 *)(puVar5 + 0x12) = 0;
            *(undefined4 *)(puVar5 + 0x16) = 0;
            if (uVar12 == 0) {
              *(undefined4 *)(puVar5 + 8) = 0xbf800000;
              *(undefined4 *)(puVar5 + 0x14) = 0xbf800000;
            }
            uVar9 = uVar4 + (uVar9 & 0xffff);
            uVar7 = uVar4 + uVar7 & 0xffff;
            if (bVar14) {
              uVar3 = *(undefined4 *)(puVar5 + 8);
              uVar1 = puVar5[3];
              uVar2 = puVar5[2];
              *(undefined4 *)(puVar5 + 8) = *(undefined4 *)(puVar5 + 0xc);
              *(undefined4 *)(puVar5 + 0xc) = uVar3;
              puVar5[2] = puVar5[1];
              uVar3 = *(undefined4 *)(puVar5 + 0x10);
              puVar5[1] = uVar2;
              puVar5[3] = puVar5[4];
              *(undefined4 *)(puVar5 + 0x10) = *(undefined4 *)(puVar5 + 0x14);
              puVar5[4] = uVar1;
              *(undefined4 *)(puVar5 + 0x14) = uVar3;
            }
            puVar5 = puVar5 + param_2 * 0x18;
          } while (iVar11 < param_3);
        }
        uVar12 = uVar12 + 1;
        local_68 = local_68 + 0x18;
      } while ((int)uVar12 < param_2);
    }
  }
  return;
}
