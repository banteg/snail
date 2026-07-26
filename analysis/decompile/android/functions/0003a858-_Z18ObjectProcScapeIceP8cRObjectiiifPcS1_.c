/*
 * mangled: _Z18ObjectProcScapeIceP8cRObjectiiifPcS1_
 * demangled: ObjectProcScapeIce(cRObject*, int, int, int, float, char*, char*)
 * address: 0003a858
 * size: 1108
 */

/* ObjectProcScapeIce(cRObject*, int, int, int, float, char*, char*) */

void ObjectProcScapeIce(cRObject *param_1,int param_2,int param_3,int param_4,float param_5,
                       char *param_6,char *param_7)

{
  undefined2 uVar1;
  undefined2 uVar2;
  byte bVar3;
  bool bVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  float *pfVar9;
  undefined2 *puVar10;
  int iVar11;
  uint uVar12;
  tColour *this;
  uint uVar13;
  int iVar14;
  int iVar15;
  float *pfVar16;
  uint in_fpscr;
  uint uVar17;
  float fVar18;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float fVar19;
  float extraout_s3_00;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  tColour *local_70;
  uint local_68;
  undefined2 *local_60;

  uVar17 = in_fpscr & 0xfffffff | (uint)((float)param_6 < 0.0) << 0x1f;
  bVar4 = !SUB41(uVar17 >> 0x1f,0);
  if (bVar4) {
    uVar17 = in_fpscr & 0xfffffff | (uint)((float)param_6 == 0.0) << 0x1e;
    fVar24 = (float)VectorSignedToFloat((uint)!SUB41(uVar17 >> 0x1e,0),(byte)(uVar17 >> 0x16) & 3);
  }
  else {
    fVar24 = -1.0;
  }
  bVar4 = !bVar4;
  uVar6 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar6 + uVar6);
  cRObject::RequestColours(param_1);
  fVar18 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_60 = *(undefined2 **)(param_1 + 200);
  pfVar16 = *(float **)(param_1 + 0xa4);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  local_70 = *(tColour **)(param_1 + 0xb4);
  if (-1 < param_2) {
    uVar13 = uVar17 & 0xfffffff | (uint)((float)param_6 < 0.0) << 0x1f |
             (uint)((float)param_6 == 0.0) << 0x1e;
    uVar17 = uVar13 | (uint)NAN((float)param_6) << 0x1c;
    iVar15 = 0;
    bVar3 = (byte)(uVar13 >> 0x18);
    uVar13 = uVar17 >> 0x1c;
    do {
      if (-1 < param_3) {
        fVar23 = (float)VectorSignedToFloat(param_4,(byte)(uVar17 >> 0x16) & 3);
        iVar14 = 0;
        iVar11 = 0;
        fVar20 = (float)VectorSignedToFloat(iVar15,(byte)(uVar17 >> 0x16) & 3);
        this = local_70;
        do {
          while( true ) {
            pfVar9 = (float *)((int)pfVar16 + iVar14);
            if (bVar4) {
              fVar22 = -1.0;
            }
            else {
              uVar17 = uVar17 & 0xfffffff | (uint)((float)param_6 == 0.0) << 0x1e;
              fVar22 = (float)VectorSignedToFloat((uint)!SUB41(uVar17 >> 0x1e,0),
                                                  (byte)(uVar17 >> 0x16) & 3);
            }
            fVar18 = (float)SRAND(fVar18,(char *)0x3f800000);
            fVar18 = (float)param_6 + fVar24 * fVar23 * fVar20 + fVar22 * fVar18;
            fVar22 = fVar18 - (float)param_6;
            *pfVar9 = fVar18;
            uVar17 = uVar17 & 0xfffffff | (uint)(fVar22 < 0.0) << 0x1f;
            if (SUB41(uVar17 >> 0x1f,0)) {
              fVar22 = -fVar22;
            }
            fVar18 = (float)RAND(extraout_s0,(char *)0x41200000);
            fVar21 = (float)VectorSignedToFloat(iVar11,(byte)(uVar17 >> 0x16) & 3);
            pfVar9[2] = fVar23 * fVar21;
            pfVar9[1] = fVar22 / fVar23 + fVar18;
            fVar18 = (float)RAND(extraout_s0_00,(char *)0x3f800000);
            fVar18 = (float)tColour::Grey(this,fVar18);
            if (iVar15 == 0) break;
            if (iVar15 != 1) goto LAB_0003aa2c;
            fVar22 = pfVar9[-3];
            fVar18 = (float)SRAND(fVar18,(char *)0x3f800000);
            *pfVar9 = fVar22 + fVar18;
            fVar18 = extraout_s0_02;
            if (iVar11 == param_3) goto LAB_0003aac8;
LAB_0003aa34:
            iVar11 = iVar11 + 1;
            this = this + uVar6 * 0x10;
            iVar14 = iVar14 + uVar6 * 0xc;
            if (param_3 < iVar11) goto LAB_0003aafc;
          }
          if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)uVar13 & 1)) {
            fVar18 = (float)Sin(fVar18);
            *pfVar9 = fVar18 + (float)param_6;
            fVar18 = extraout_s0_03;
            fVar22 = extraout_s1_00;
            fVar21 = extraout_s2_00;
            fVar19 = extraout_s3_00;
          }
          else {
            fVar18 = (float)Sin(fVar18);
            *pfVar9 = fVar18 + (float)param_6;
            fVar18 = extraout_s0_01;
            fVar22 = extraout_s1;
            fVar21 = extraout_s2;
            fVar19 = extraout_s3;
          }
          pfVar9[1] = -3.1;
          fVar18 = (float)tColour::Set(this,fVar18,fVar22,fVar21,fVar19);
LAB_0003aa2c:
          if (iVar11 != param_3) goto LAB_0003aa34;
LAB_0003aac8:
          pfVar9[1] = pfVar16[1];
          *pfVar9 = *pfVar16;
          iVar11 = iVar11 + 1;
          uVar5 = *(undefined4 *)(local_70 + 4);
          uVar7 = *(undefined4 *)(local_70 + 8);
          uVar8 = *(undefined4 *)(local_70 + 0xc);
          *(undefined4 *)this = *(undefined4 *)local_70;
          *(undefined4 *)(this + 4) = uVar5;
          *(undefined4 *)(this + 8) = uVar7;
          *(undefined4 *)(this + 0xc) = uVar8;
          this = this + uVar6 * 0x10;
          iVar14 = iVar14 + uVar6 * 0xc;
        } while (iVar11 <= param_3);
      }
LAB_0003aafc:
      iVar15 = iVar15 + 1;
      pfVar16 = pfVar16 + 3;
      local_70 = local_70 + 0x10;
    } while (iVar15 <= param_2);
    if (0 < param_2) {
      uVar17 = 0;
      uVar6 = uVar6 & 0xffff;
      local_68 = uVar6;
      do {
        local_68 = local_68 + 1 & 0xffff;
        if (0 < param_3) {
          iVar15 = 0;
          puVar10 = local_60;
          uVar12 = local_68;
          uVar13 = uVar17;
          do {
            puVar10[1] = (short)uVar13;
            puVar10[3] = (short)uVar12;
            *puVar10 = 0;
            puVar10[2] = (short)uVar13 + 1;
            puVar10[4] = (short)uVar12 + -1;
            uVar5 = cRTextures::Add((cRTextures *)gTextureList,param_7,(cTgaHeader *)0x0,0);
            *(undefined4 *)(puVar10 + 8) = 0;
            *(undefined4 *)(puVar10 + 10) = 0x3f800000;
            *(undefined4 *)(puVar10 + 0xe) = 0x3f800000;
            *(undefined4 *)(puVar10 + 0x10) = 0x3f800000;
            *(undefined4 *)(puVar10 + 0x12) = 0;
            *(undefined4 *)(puVar10 + 0xc) = 0x3f800000;
            *(undefined4 *)(puVar10 + 0x14) = 0;
            *(undefined4 *)(puVar10 + 0x16) = 0;
            if (uVar17 == 0) {
              *(undefined4 *)(puVar10 + 8) = 0x3f800000;
              *(undefined4 *)(puVar10 + 10) = 0;
              *(undefined4 *)(puVar10 + 0xe) = 0x3e4ccccd;
              *(undefined4 *)(puVar10 + 0x10) = 0;
              *(undefined4 *)(puVar10 + 0x12) = 0x3e4ccccd;
            }
            uVar13 = uVar6 + (uVar13 & 0xffff);
            iVar15 = iVar15 + 1;
            uVar12 = uVar6 + uVar12 & 0xffff;
            *(undefined4 *)(puVar10 + 6) = uVar5;
            if (bVar4) {
              uVar1 = puVar10[1];
              uVar5 = *(undefined4 *)(puVar10 + 8);
              uVar2 = puVar10[3];
              *(undefined4 *)(puVar10 + 8) = *(undefined4 *)(puVar10 + 0xc);
              *(undefined4 *)(puVar10 + 0xc) = uVar5;
              puVar10[1] = puVar10[2];
              uVar5 = *(undefined4 *)(puVar10 + 0x14);
              puVar10[2] = uVar1;
              puVar10[3] = puVar10[4];
              *(undefined4 *)(puVar10 + 0x14) = *(undefined4 *)(puVar10 + 0x10);
              puVar10[4] = uVar2;
              *(undefined4 *)(puVar10 + 0x10) = uVar5;
            }
            puVar10 = puVar10 + param_2 * 0x18;
          } while (iVar15 < param_3);
        }
        uVar17 = uVar17 + 1;
        local_60 = local_60 + 0x18;
      } while ((int)uVar17 < param_2);
    }
  }
  return;
}
