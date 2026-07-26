/*
 * mangled: _ZN6cRPath6SearchEP10cRSubGoldy7tVectorS2_S2_P8cRSubLoc
 * demangled: cRPath::Search(cRSubGoldy*, tVector, tVector, tVector, cRSubLoc*)
 * address: 0004e318
 * size: 1512
 */

/* cRPath::Search(cRSubGoldy*, tVector, tVector, tVector, cRSubLoc*) */

void cRPath::Search(int param_1,undefined4 param_2,float param_3,float param_4,float param_5,
                   float param_6,float param_7,float param_8,float param_9,float param_10,
                   float param_11,cRSubLoc *param_12)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  uint in_fpscr;
  float fVar13;
  float extraout_s0;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float local_138 [3];
  float local_12c [3];
  float *local_120;
  float *local_11c;
  float *local_118;
  float *local_114;
  int local_110;
  tVector *local_10c;
  tVector *local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;

  fVar13 = DAT_0004e3dc;
  iVar10 = *(int *)(param_1 + 0x38) + -1;
  local_110 = DAT_0004e3e0 + 0x4e35c;
  local_fc = param_6;
  local_100 = param_7;
  local_104 = param_8;
  param_6 = param_6 - param_9;
  fVar20 = *(float *)(param_12 + 0x18);
  fVar19 = *(float *)(param_12 + 0x14);
  fVar18 = *(float *)(param_12 + 0x10);
  param_7 = param_7 - param_10;
  param_8 = param_8 - param_11;
  if (-1 < iVar10) {
    local_10c = (tVector *)&local_e8;
    local_108 = (tVector *)&local_f4;
    local_11c = local_138;
    iVar11 = *(int *)(param_1 + 0x38) * 0xa8;
    local_118 = &local_ac;
    local_114 = local_12c;
    iVar9 = iVar10 * 0xa8;
    do {
      pfVar7 = (float *)(*(int *)(param_1 + 0x50) + iVar9);
      fVar14 = pfVar7[5];
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar14 < 0.0) << 0x1f | (uint)(fVar14 == 0.0) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar14) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar14 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar14 = fVar14 * fVar13;
        fVar15 = fVar18 + (float)*(undefined8 *)(pfVar7 + 0xc) + fVar14 * *pfVar7;
        fVar16 = fVar19 + (float)((ulonglong)*(undefined8 *)(pfVar7 + 0xc) >> 0x20) +
                 fVar14 * pfVar7[1];
        fVar17 = fVar20 + pfVar7[0xe] + fVar14 * pfVar7[2];
        local_d0 = param_6 - fVar15;
        local_cc = param_7 - fVar16;
        local_c8 = param_8 - fVar17;
        fVar14 = (float)tVector::Dot((tVector *)&local_d0,(tVector *)(pfVar7 + 4));
        uVar1 = in_fpscr & 0xfffffff | (uint)(fVar14 < 0.0) << 0x1f | (uint)(fVar14 == 0.0) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar14) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          local_dc = param_3 - fVar15;
          local_d8 = param_4 - fVar16;
          local_d4 = param_5 - fVar17;
          fVar5 = (float)tVector::Dot((tVector *)&local_dc,
                                      (tVector *)(*(int *)(param_1 + 0x50) + iVar9 + 0x10));
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar5 < 0.0) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            local_120 = (float *)(param_4 - param_7);
            local_e8 = param_3 - param_6;
            local_e4 = (float)local_120;
            local_e0 = param_5 - param_8;
            fVar5 = (float)tVector::Dot((tVector *)(*(int *)(param_1 + 0x50) + iVar9 + 0x10),
                                        local_10c);
            fVar5 = -fVar14 / fVar5;
            local_8c = param_8 + fVar5 * (param_5 - param_8);
            local_94 = param_6 + fVar5 * (param_3 - param_6);
            local_90 = param_7 + fVar5 * (float)local_120;
            local_f4 = local_94 - fVar15;
            local_f0 = local_90 - fVar16;
            local_ec = local_8c - fVar17;
            tVector::Dot(local_108,(tVector *)(*(int *)(param_1 + 0x50) + iVar9 + 0x10));
            pfVar7 = local_11c;
            fVar14 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),
                                                (byte)(in_fpscr >> 0x16) & 3);
            pfVar8 = (float *)(*(int *)(param_1 + 0x50) + iVar9);
            fVar15 = fVar14 * -0.5;
            local_ac = fVar18 + pfVar8[0xc] + fVar15 * *pfVar8;
            local_a8 = fVar19 + pfVar8[0xd] + fVar15 * pfVar8[1];
            local_a4 = fVar20 + pfVar8[0xe] + fVar15 * pfVar8[2];
            fVar14 = fVar14 * fVar13;
            local_a0 = fVar18 + pfVar8[0xc] + fVar14 * *pfVar8;
            local_9c = fVar19 + pfVar8[0xd] + fVar14 * pfVar8[1];
            local_98 = fVar20 + pfVar8[0xe] + fVar14 * pfVar8[2];
            if (*(int *)(param_1 + 0x38) + -1 == iVar10) {
              fVar14 = pfVar8[0x23];
              local_b0 = local_98 + fVar14 * pfVar8[10];
              local_b4 = local_9c + fVar14 * pfVar8[9];
              local_b8 = local_a0 + fVar14 * pfVar8[8];
              fVar15 = local_ac + fVar14 * pfVar8[8];
              fVar16 = local_a8 + fVar14 * pfVar8[9];
              fVar14 = local_a4 + fVar14 * pfVar8[10];
            }
            else {
              pfVar8 = (float *)(*(int *)(param_1 + 0x50) + iVar11);
              fVar16 = fVar19 + pfVar8[0xd] + fVar15 * pfVar8[1];
              local_b0 = fVar20 + pfVar8[0xe] + fVar14 * pfVar8[2];
              local_b8 = fVar18 + pfVar8[0xc] + fVar14 * *pfVar8;
              local_b4 = fVar19 + pfVar8[0xd] + fVar14 * pfVar8[1];
              fVar14 = fVar20 + pfVar8[0xe] + fVar15 * pfVar8[2];
              fVar15 = fVar18 + pfVar8[0xc] + fVar15 * *pfVar8;
            }
            local_120 = &local_94;
            fVar17 = local_118[1];
            fVar5 = local_118[2];
            *local_11c = *local_118;
            pfVar7[1] = fVar17;
            pfVar7[2] = fVar5;
            fVar4 = local_a0;
            fVar5 = local_b0;
            fVar17 = local_b4;
            pfVar7 = local_114;
            *local_114 = local_b8;
            pfVar7[1] = fVar17;
            pfVar7[2] = fVar5;
            iVar6 = PointTriangle(*local_120,local_120[1],local_120[2],fVar4,local_9c,local_98);
            pfVar7 = local_11c;
            if (iVar6 != 0) {
LAB_0004e68c:
              uVar3 = DAT_0004e3e8;
              iVar11 = *(int *)(param_1 + 0x50) + iVar9;
              local_7c = local_fc - (fVar18 + *(float *)(iVar11 + 0x30));
              local_74 = local_104 - (fVar20 + *(float *)(iVar11 + 0x38));
              local_78 = local_100 - (fVar19 + *(float *)(iVar11 + 0x34));
              tVector::Rotate((tVector *)&local_7c,(tMatrix *)(iVar11 + 0x40));
              iVar9 = *(int *)(param_1 + 0x50) + iVar9;
              local_88 = param_3 - (fVar18 + *(float *)(iVar9 + 0x30));
              local_80 = param_5 - (fVar20 + *(float *)(iVar9 + 0x38));
              local_84 = param_4 - (fVar19 + *(float *)(iVar9 + 0x34));
              fVar13 = (float)tVector::Rotate((tVector *)&local_88,(tMatrix *)(iVar9 + 0x40));
              piVar12 = *(int **)(local_110 + DAT_0004e3e4);
              iVar9 = *piVar12;
              *(undefined1 *)(iVar9 + 0x81779) = 0;
              cRSquidge::StartY((cRSquidge *)(iVar9 + 0x8535c),fVar13);
              iVar11 = *piVar12;
              *(undefined4 *)(iVar11 + 0x816ec) = uVar3;
              *(float *)(iVar11 + 0x816e8) = local_74;
              *(int *)(iVar11 + 0x816e4) = iVar10;
              *(int *)(iVar11 + 0x816dc) = param_1;
              *(float *)(iVar11 + 0x813c4) = local_78;
              *(undefined1 *)(iVar11 + 0x816d8) = 1;
              *(cRSubLoc **)(iVar11 + 0x816e0) = param_12;
              *(int *)(iVar11 + 0x81710) = iVar11 + 0x81364;
              *(undefined4 *)(iVar11 + 0x81770) = uVar3;
              iVar10 = cRSubLoc::Yi(param_12);
              iVar9 = *piVar12;
              *(undefined4 *)(param_1 + 0x80) =
                   *(undefined4 *)(gGroup0 + iVar10 * 0xdc + iVar11 + 0xd174);
              *(undefined4 *)(iVar9 + 0x816f0) = uVar3;
              *(undefined4 *)(iVar9 + 0x816f4) = uVar3;
              cRPathFollowGoldy::Traverse
                        (extraout_s0,(tVector *)(iVar9 + 0x816d8),*(tVector **)(iVar9 + 0x81774));
              return;
            }
            fVar17 = local_118[1];
            fVar5 = local_118[2];
            local_c4 = fVar15;
            local_c0 = fVar16;
            local_bc = fVar14;
            *local_11c = *local_118;
            pfVar7[1] = fVar17;
            pfVar7[2] = fVar5;
            fVar16 = local_b0;
            fVar15 = local_b4;
            fVar14 = local_c4;
            pfVar7 = local_114;
            *local_114 = local_b8;
            pfVar7[1] = fVar15;
            pfVar7[2] = fVar16;
            iVar6 = PointTriangle(*local_120,local_120[1],local_120[2],fVar14,local_c0,local_bc);
            if (iVar6 != 0) goto LAB_0004e68c;
          }
        }
      }
      iVar10 = iVar10 + -1;
      iVar9 = iVar9 + -0xa8;
      iVar11 = iVar11 + -0xa8;
    } while (-1 < iVar10);
  }
  return;
}
