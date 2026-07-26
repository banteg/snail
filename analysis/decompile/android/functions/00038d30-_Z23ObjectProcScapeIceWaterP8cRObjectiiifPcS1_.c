/*
 * mangled: _Z23ObjectProcScapeIceWaterP8cRObjectiiifPcS1_
 * demangled: ObjectProcScapeIceWater(cRObject*, int, int, int, float, char*, char*)
 * address: 00038d30
 * size: 1364
 */

/* ObjectProcScapeIceWater(cRObject*, int, int, int, float, char*, char*) */

void ObjectProcScapeIceWater
               (cRObject *param_1,int param_2,int param_3,int param_4,float param_5,char *param_6,
               char *param_7)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  float *pfVar8;
  undefined2 *puVar9;
  int iVar10;
  tColour *this;
  uint uVar11;
  int iVar12;
  uint uVar13;
  float *pfVar14;
  int iVar15;
  int iVar16;
  bool bVar17;
  uint in_fpscr;
  float fVar18;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar19;
  float fVar20;
  char *in_stack_00000008;
  uint local_64;
  uint local_5c;
  undefined2 *local_58;

  uVar4 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar4 + uVar4);
  cRObject::RequestColours(param_1);
  fVar18 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  *(uint *)param_1 = *(uint *)param_1 | 0x10080;
  local_58 = *(undefined2 **)(param_1 + 200);
  iVar16 = *(int *)(param_1 + 0xb4);
  pfVar14 = *(float **)(param_1 + 0xa4);
  if (-1 < param_2) {
    iVar15 = 0;
    do {
      if (-1 < param_3) {
        puVar6 = (undefined4 *)(iVar16 + iVar15 * 0x10);
        iVar10 = 0;
        fVar20 = (float)VectorSignedToFloat(param_4,(byte)(in_fpscr >> 0x16) & 3);
        pfVar8 = pfVar14;
        iVar12 = iVar15;
        do {
          while( true ) {
            if (iVar15 == 0) {
              fVar19 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
              fVar18 = (float)Sin(fVar18);
              pfVar8[1] = -3.1;
              *pfVar8 = fVar18 - (float)param_6;
              fVar18 = extraout_s0_00;
            }
            else if (iVar15 == 1) {
              fVar19 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
              fVar18 = (float)Cos(fVar18);
              pfVar8[1] = -3.1;
              *pfVar8 = fVar18;
              fVar18 = extraout_s0_01;
            }
            else {
              fVar19 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
              fVar18 = (float)Sin(fVar18);
              pfVar8[1] = -3.1;
              *pfVar8 = fVar18 + (float)param_6;
              fVar18 = extraout_s0;
            }
            this = (tColour *)(iVar16 + iVar12 * 0x10);
            iVar12 = iVar12 + uVar4;
            pfVar8[2] = fVar20 * fVar19;
            fVar18 = (float)RAND(fVar18,(char *)0x3f800000);
            fVar18 = (float)tColour::Grey(this,fVar18);
            bVar17 = iVar10 == param_3;
            iVar10 = iVar10 + 1;
            if (bVar17) break;
            pfVar8 = pfVar8 + uVar4 * 3;
            if (param_3 < iVar10) goto LAB_00038ed4;
          }
          pfVar8[1] = pfVar14[1];
          *pfVar8 = *pfVar14;
          uVar3 = puVar6[1];
          uVar5 = puVar6[2];
          uVar7 = puVar6[3];
          *(undefined4 *)this = *puVar6;
          *(undefined4 *)(this + 4) = uVar3;
          *(undefined4 *)(this + 8) = uVar5;
          *(undefined4 *)(this + 0xc) = uVar7;
          pfVar8 = pfVar8 + uVar4 * 3;
        } while (iVar10 <= param_3);
      }
LAB_00038ed4:
      iVar15 = iVar15 + 1;
      pfVar14 = pfVar14 + 3;
    } while (iVar15 <= param_2);
    if (0 < param_2) {
      local_64 = 0;
      uVar4 = uVar4 & 0xffff;
      local_5c = uVar4;
      do {
        local_5c = local_5c + 1 & 0xffff;
        if (0 < param_3) {
          if (local_64 == 0) {
            if ((float)param_6 < 0.0) {
              uVar11 = 0;
              iVar16 = 0;
              puVar9 = local_58;
              uVar13 = local_5c;
              do {
                puVar9[1] = (short)uVar11;
                puVar9[3] = (short)uVar13;
                *puVar9 = 0;
                puVar9[2] = (short)uVar11 + 1;
                puVar9[4] = (short)uVar13 + -1;
                uVar3 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,
                                        (cTgaHeader *)0x0,0);
                iVar16 = iVar16 + 1;
                uVar1 = puVar9[3];
                uVar2 = puVar9[2];
                *(undefined4 *)(puVar9 + 10) = 0x3f800000;
                puVar9[2] = puVar9[1];
                *(undefined4 *)(puVar9 + 0xe) = 0x3f800000;
                puVar9[1] = uVar2;
                *(undefined4 *)(puVar9 + 0x12) = 0;
                puVar9[3] = puVar9[4];
                *(undefined4 *)(puVar9 + 0x16) = 0;
                puVar9[4] = uVar1;
                *(undefined4 *)(puVar9 + 8) = 0x3f800000;
                *(undefined4 *)(puVar9 + 0xc) = 0xbf800000;
                *(undefined4 *)(puVar9 + 0x10) = 0xbf800000;
                *(undefined4 *)(puVar9 + 0x14) = 0x3f800000;
                uVar11 = uVar4 + uVar11 & 0xffff;
                uVar13 = uVar4 + uVar13 & 0xffff;
                *(undefined4 *)(puVar9 + 6) = uVar3;
                puVar9 = puVar9 + param_2 * 0x18;
              } while (iVar16 < param_3);
            }
            else {
              uVar11 = 0;
              iVar16 = 0;
              puVar9 = local_58;
              uVar13 = local_5c;
              do {
                puVar9[1] = (short)uVar11;
                puVar9[3] = (short)uVar13;
                *puVar9 = 0;
                puVar9[2] = (short)uVar11 + 1;
                puVar9[4] = (short)uVar13 + -1;
                uVar3 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,
                                        (cTgaHeader *)0x0,0);
                iVar16 = iVar16 + 1;
                *(undefined4 *)(puVar9 + 10) = 0x3f800000;
                *(undefined4 *)(puVar9 + 0xc) = 0x3f800000;
                *(undefined4 *)(puVar9 + 0xe) = 0x3f800000;
                *(undefined4 *)(puVar9 + 0x10) = 0x3f800000;
                *(undefined4 *)(puVar9 + 0x12) = 0;
                *(undefined4 *)(puVar9 + 0x16) = 0;
                *(undefined4 *)(puVar9 + 8) = 0xbf800000;
                *(undefined4 *)(puVar9 + 0x14) = 0xbf800000;
                uVar11 = uVar4 + uVar11 & 0xffff;
                uVar13 = uVar4 + uVar13 & 0xffff;
                *(undefined4 *)(puVar9 + 6) = uVar3;
                puVar9 = puVar9 + param_2 * 0x18;
              } while (iVar16 < param_3);
            }
          }
          else if ((float)param_6 < 0.0) {
            iVar16 = 0;
            puVar9 = local_58;
            uVar13 = local_5c;
            uVar11 = local_64;
            do {
              puVar9[1] = (short)uVar11;
              puVar9[3] = (short)uVar13;
              *puVar9 = 0;
              puVar9[2] = (short)uVar11 + 1;
              puVar9[4] = (short)uVar13 + -1;
              uVar3 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              iVar16 = iVar16 + 1;
              uVar11 = uVar4 + (uVar11 & 0xffff);
              uVar1 = puVar9[3];
              uVar2 = puVar9[2];
              *(undefined4 *)(puVar9 + 10) = 0x3f800000;
              puVar9[2] = puVar9[1];
              *(undefined4 *)(puVar9 + 0xe) = 0x3f800000;
              puVar9[1] = uVar2;
              *(undefined4 *)(puVar9 + 0x12) = 0;
              puVar9[3] = puVar9[4];
              *(undefined4 *)(puVar9 + 0x16) = 0;
              puVar9[4] = uVar1;
              *(undefined4 *)(puVar9 + 8) = 0x3f800000;
              *(undefined4 *)(puVar9 + 0xc) = 0;
              *(undefined4 *)(puVar9 + 0x10) = 0;
              *(undefined4 *)(puVar9 + 0x14) = 0x3f800000;
              uVar13 = uVar4 + uVar13 & 0xffff;
              *(undefined4 *)(puVar9 + 6) = uVar3;
              puVar9 = puVar9 + param_2 * 0x18;
            } while (iVar16 < param_3);
          }
          else {
            iVar16 = 0;
            puVar9 = local_58;
            uVar13 = local_5c;
            uVar11 = local_64;
            do {
              puVar9[1] = (short)uVar11;
              puVar9[3] = (short)uVar13;
              *puVar9 = 0;
              puVar9[2] = (short)uVar11 + 1;
              puVar9[4] = (short)uVar13 + -1;
              uVar3 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              iVar16 = iVar16 + 1;
              uVar11 = uVar4 + (uVar11 & 0xffff);
              *(undefined4 *)(puVar9 + 8) = 0;
              *(undefined4 *)(puVar9 + 10) = 0x3f800000;
              *(undefined4 *)(puVar9 + 0xc) = 0x3f800000;
              *(undefined4 *)(puVar9 + 0xe) = 0x3f800000;
              *(undefined4 *)(puVar9 + 0x10) = 0x3f800000;
              *(undefined4 *)(puVar9 + 0x12) = 0;
              *(undefined4 *)(puVar9 + 0x14) = 0;
              *(undefined4 *)(puVar9 + 0x16) = 0;
              uVar13 = uVar4 + uVar13 & 0xffff;
              *(undefined4 *)(puVar9 + 6) = uVar3;
              puVar9 = puVar9 + param_2 * 0x18;
            } while (iVar16 < param_3);
          }
        }
        local_64 = local_64 + 1;
        local_58 = local_58 + 0x18;
      } while ((int)local_64 < param_2);
    }
  }
  return;
}
