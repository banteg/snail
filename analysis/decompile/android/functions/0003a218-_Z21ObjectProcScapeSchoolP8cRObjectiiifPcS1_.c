/*
 * mangled: _Z21ObjectProcScapeSchoolP8cRObjectiiifPcS1_
 * demangled: ObjectProcScapeSchool(cRObject*, int, int, int, float, char*, char*)
 * address: 0003a218
 * size: 1344
 */

/* ObjectProcScapeSchool(cRObject*, int, int, int, float, char*, char*) */

void ObjectProcScapeSchool
               (cRObject *param_1,int param_2,int param_3,int param_4,float param_5,char *param_6,
               char *param_7)

{
  undefined2 uVar1;
  undefined2 uVar2;
  byte bVar3;
  bool bVar4;
  undefined4 uVar5;
  undefined4 extraout_r1;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  tColour *ptVar9;
  uint uVar10;
  undefined2 *puVar11;
  float *pfVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  tColour *ptVar16;
  uint uVar17;
  uint in_fpscr;
  uint uVar18;
  float fVar19;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar20;
  float fVar21;
  float fVar24;
  float fVar25;
  longlong lVar22;
  ulonglong uVar23;
  float fVar26;
  float fVar27;
  char *in_stack_00000008;
  tColour *local_90;
  float *local_8c;
  float *local_84;
  int local_80;
  undefined2 *local_7c;

  uVar18 = in_fpscr & 0xfffffff | (uint)((float)param_6 < 0.0) << 0x1f;
  if (SUB41(uVar18 >> 0x1f,0)) {
    fVar27 = -1.0;
  }
  else {
    uVar18 = in_fpscr & 0xfffffff | (uint)((float)param_6 == 0.0) << 0x1e;
    fVar27 = (float)VectorSignedToFloat((uint)!SUB41(uVar18 >> 0x1e,0),(byte)(uVar18 >> 0x16) & 3);
  }
  uVar6 = param_2 + 1;
  cRObject::RequestVertices(param_1,param_3 * uVar6 + uVar6);
  cRObject::RequestColours(param_1);
  fVar19 = (float)cRObject::RequestFaceQuads(param_1,param_2 * param_3);
  local_8c = *(float **)(param_1 + 0xa4);
  local_7c = *(undefined2 **)(param_1 + 200);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  ptVar9 = *(tColour **)(param_1 + 0xb4);
  if (-1 < param_2) {
    uVar10 = 0;
    local_80 = uVar6 * param_3;
    local_84 = local_8c + local_80 * 3;
    local_90 = ptVar9;
    do {
      if (-1 < param_3) {
        fVar24 = (float)VectorSignedToFloat(param_4,(byte)(uVar18 >> 0x16) & 3);
        lVar22 = (ulonglong)(uint)fVar24 << 0x20;
        uVar14 = 0;
        fVar26 = (float)VectorSignedToFloat(uVar10,(byte)(uVar18 >> 0x16) & 3);
        fVar24 = (float)param_6 + fVar26 * fVar27 * fVar24;
        fVar26 = fVar24 - (float)param_6;
        uVar18 = uVar18 & 0xfffffff | (uint)(fVar26 < 0.0) << 0x1f;
        pfVar12 = local_8c;
        ptVar16 = local_90;
        if (SUB41(uVar18 >> 0x1f,0)) {
          bVar4 = true;
        }
        else {
          bVar4 = false;
        }
        do {
          *pfVar12 = fVar24;
          fVar25 = (float)((ulonglong)lVar22 >> 0x20);
          fVar20 = fVar26;
          if (bVar4) {
            fVar20 = -fVar26;
          }
          fVar19 = (float)RAND(fVar19,(char *)0x3f800000);
          fVar21 = (float)VectorSignedToFloat(uVar14,(byte)(uVar18 >> 0x16) & 3);
          pfVar12[2] = fVar21 * fVar25;
          pfVar12[1] = (fVar20 / fVar25 + fVar19) - 3.0;
          fVar19 = (float)RAND(extraout_s0,(char *)0x3f800000);
          fVar19 = (float)tColour::Grey(ptVar16,fVar19);
          if (uVar10 == param_2) {
            fVar20 = pfVar12[1];
            fVar19 = (float)RAND(fVar19,(char *)0x40800000);
            pfVar12[1] = fVar20 + fVar19 + 5.0;
            fVar19 = (float)tColour::White();
          }
          if (uVar10 == 0) {
            fVar19 = (float)Sin(fVar19);
            pfVar12[1] = -9.0;
            *pfVar12 = fVar19 * 3.0;
            fVar19 = (float)__aeabi_idivmod(uVar14,param_3);
            VectorSignedToFloat(extraout_r1,(byte)(uVar18 >> 0x16) & 3);
            fVar19 = (float)Sin(fVar19);
            uVar18 = uVar18 & 0xfffffff | (uint)(fVar19 < 0.0) << 0x1f;
            if (SUB41(uVar18 >> 0x1f,0)) {
              fVar19 = (float)Sin(extraout_s0_01);
            }
            else {
              fVar19 = (float)Sin(extraout_s0_01);
            }
            fVar19 = (float)tColour::Grey(ptVar16,fVar19);
            lVar22 = CONCAT44(fVar25,pfVar12[1]);
          }
          else if (((uVar10 & 1) == 0) || ((uVar14 & 1) != 0)) {
            lVar22 = CONCAT44(fVar25,pfVar12[1]);
          }
          else {
            fVar20 = pfVar12[1];
            fVar19 = (float)RAND(fVar19,(char *)0x41200000);
            fVar20 = fVar20 + fVar19 + 5.0;
            lVar22 = CONCAT44(fVar25,fVar20);
            pfVar12[1] = fVar20;
            fVar19 = extraout_s0_00;
          }
          uVar14 = uVar14 + 1;
          ptVar16 = ptVar16 + uVar6 * 0x10;
          pfVar12[1] = (float)lVar22 * -2.0 + 16.0;
          pfVar12 = pfVar12 + uVar6 * 3;
        } while ((int)uVar14 <= param_3);
      }
      if (uVar10 == 0) {
        fVar19 = (float)Sin(fVar19);
        *local_84 = fVar19 * 3.0;
        fVar19 = extraout_s0_02;
      }
      uVar10 = uVar10 + 1;
      local_84[1] = local_8c[1];
      uVar5 = *(undefined4 *)(local_90 + 4);
      uVar7 = *(undefined4 *)(local_90 + 8);
      uVar8 = *(undefined4 *)(local_90 + 0xc);
      ptVar16 = ptVar9 + local_80 * 0x10;
      local_80 = local_80 + 1;
      local_84 = local_84 + 3;
      local_8c = local_8c + 3;
      *(undefined4 *)ptVar16 = *(undefined4 *)local_90;
      *(undefined4 *)(ptVar16 + 4) = uVar5;
      *(undefined4 *)(ptVar16 + 8) = uVar7;
      *(undefined4 *)(ptVar16 + 0xc) = uVar8;
      local_90 = local_90 + 0x10;
    } while ((int)uVar10 <= param_2);
    if (0 < param_2) {
      uVar18 = uVar18 & 0xfffffff | (uint)((float)param_6 < 0.0) << 0x1f |
               (uint)((float)param_6 == 0.0) << 0x1e;
      uVar14 = uVar18 | (uint)NAN((float)param_6) << 0x1c;
      uVar10 = 0;
      fVar27 = 0.5;
      uVar6 = uVar6 & 0xffff;
      bVar3 = (byte)(uVar18 >> 0x18);
      uVar18 = uVar14 >> 0x1c;
      local_84 = (float *)uVar6;
      do {
        local_84 = (float *)((int)local_84 + 1U & 0xffff);
        if (0 < param_3) {
          uVar23 = CONCAT44(uVar10,fVar27) & 0x1ffffffff;
          fVar27 = (float)uVar23;
          fVar19 = (float)VectorSignedToFloat((int)(uVar23 >> 0x20),(byte)(uVar14 >> 0x16) & 3);
          puVar11 = local_7c;
          pfVar12 = local_84;
          uVar15 = 0;
          uVar13 = uVar10;
          do {
            puVar11[2] = (short)uVar13 + 1;
            puVar11[1] = (short)uVar13;
            *puVar11 = 0;
            uVar17 = uVar15 + 1;
            puVar11[3] = (short)pfVar12;
            puVar11[4] = (short)pfVar12 + -1;
            if (param_2 - 1U == uVar10) {
              uVar5 = cRTextures::Add((cRTextures *)gTextureList,in_stack_00000008,(cTgaHeader *)0x0
                                      ,0);
              *(undefined4 *)(puVar11 + 6) = uVar5;
            }
            else {
              uVar5 = cRTextures::Add((cRTextures *)gTextureList,param_7,(cTgaHeader *)0x0,0);
              *(undefined4 *)(puVar11 + 6) = uVar5;
            }
            fVar24 = (float)VectorSignedToFloat(uVar15 & 1,(byte)(uVar14 >> 0x16) & 3);
            uVar13 = (uVar13 & 0xffff) + uVar6;
            pfVar12 = (float *)(uVar6 + (int)pfVar12 & 0xffff);
            fVar24 = fVar24 * fVar27;
            fVar20 = fVar19 * fVar27;
            *(float *)(puVar11 + 0x16) = fVar24;
            *(float *)(puVar11 + 0x12) = fVar24;
            fVar26 = fVar20 + fVar27;
            *(float *)(puVar11 + 8) = fVar20;
            *(float *)(puVar11 + 0x14) = fVar20;
            *(float *)(puVar11 + 0xc) = fVar26;
            *(float *)(puVar11 + 0x10) = fVar26;
            *(float *)(puVar11 + 0xe) = fVar24 + fVar27;
            *(float *)(puVar11 + 10) = fVar24 + fVar27;
            if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)uVar18 & 1)) {
              *(float *)(puVar11 + 0x10) = fVar20;
              uVar1 = puVar11[3];
              *(float *)(puVar11 + 0x14) = fVar26;
              uVar2 = puVar11[2];
              *(float *)(puVar11 + 8) = fVar26;
              *(float *)(puVar11 + 0xc) = fVar20;
              puVar11[2] = puVar11[1];
              puVar11[1] = uVar2;
              puVar11[3] = puVar11[4];
              puVar11[4] = uVar1;
            }
            puVar11 = puVar11 + param_2 * 0x18;
            uVar15 = uVar17;
          } while ((int)uVar17 < param_3);
        }
        uVar10 = uVar10 + 1;
        local_7c = local_7c + 0x18;
      } while ((int)uVar10 < param_2);
    }
  }
  return;
}
