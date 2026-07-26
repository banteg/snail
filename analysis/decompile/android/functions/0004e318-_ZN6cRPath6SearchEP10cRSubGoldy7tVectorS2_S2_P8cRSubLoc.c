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
  float fVar3;
  float fVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  uint in_fpscr;
  float extraout_s0;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float local_138 [3];
  float local_12c [3];
  float *local_120;
  float *local_11c;
  float *local_118;
  float *local_114;
  undefined **local_110;
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

  iVar9 = *(int *)(param_1 + 0x38) + -1;
  local_110 = &__DT_PLTGOT;
  local_fc = param_6;
  local_100 = param_7;
  local_104 = param_8;
  param_6 = param_6 - param_9;
  fVar18 = *(float *)(param_12 + 0x18);
  fVar17 = *(float *)(param_12 + 0x14);
  fVar16 = *(float *)(param_12 + 0x10);
  param_7 = param_7 - param_10;
  param_8 = param_8 - param_11;
  if (-1 < iVar9) {
    local_10c = (tVector *)&local_e8;
    local_108 = (tVector *)&local_f4;
    local_11c = local_138;
    iVar10 = *(int *)(param_1 + 0x38) * 0xa8;
    local_118 = &local_ac;
    local_114 = local_12c;
    iVar8 = iVar9 * 0xa8;
    do {
      pfVar6 = (float *)(*(int *)(param_1 + 0x50) + iVar8);
      fVar12 = pfVar6[5];
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar12 < 0.0) << 0x1f | (uint)(fVar12 == 0.0) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar12) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar12 = fVar12 * 0.5;
        fVar13 = fVar16 + (float)*(undefined8 *)(pfVar6 + 0xc) + fVar12 * *pfVar6;
        fVar14 = fVar17 + (float)((ulonglong)*(undefined8 *)(pfVar6 + 0xc) >> 0x20) +
                 fVar12 * pfVar6[1];
        fVar15 = fVar18 + pfVar6[0xe] + fVar12 * pfVar6[2];
        local_d0 = param_6 - fVar13;
        local_cc = param_7 - fVar14;
        local_c8 = param_8 - fVar15;
        fVar12 = (float)tVector::Dot((tVector *)&local_d0,(tVector *)(pfVar6 + 4));
        uVar1 = in_fpscr & 0xfffffff | (uint)(fVar12 < 0.0) << 0x1f | (uint)(fVar12 == 0.0) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar12) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          local_dc = param_3 - fVar13;
          local_d8 = param_4 - fVar14;
          local_d4 = param_5 - fVar15;
          fVar4 = (float)tVector::Dot((tVector *)&local_dc,
                                      (tVector *)(*(int *)(param_1 + 0x50) + iVar8 + 0x10));
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar4 < 0.0) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            local_120 = (float *)(param_4 - param_7);
            local_e8 = param_3 - param_6;
            local_e4 = (float)local_120;
            local_e0 = param_5 - param_8;
            fVar4 = (float)tVector::Dot((tVector *)(*(int *)(param_1 + 0x50) + iVar8 + 0x10),
                                        local_10c);
            fVar4 = -fVar12 / fVar4;
            local_8c = param_8 + fVar4 * (param_5 - param_8);
            local_94 = param_6 + fVar4 * (param_3 - param_6);
            local_90 = param_7 + fVar4 * (float)local_120;
            local_f4 = local_94 - fVar13;
            local_f0 = local_90 - fVar14;
            local_ec = local_8c - fVar15;
            tVector::Dot(local_108,(tVector *)(*(int *)(param_1 + 0x50) + iVar8 + 0x10));
            pfVar6 = local_11c;
            fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),
                                                (byte)(in_fpscr >> 0x16) & 3);
            pfVar7 = (float *)(*(int *)(param_1 + 0x50) + iVar8);
            fVar13 = fVar12 * -0.5;
            local_ac = fVar16 + pfVar7[0xc] + fVar13 * *pfVar7;
            local_a8 = fVar17 + pfVar7[0xd] + fVar13 * pfVar7[1];
            local_a4 = fVar18 + pfVar7[0xe] + fVar13 * pfVar7[2];
            fVar12 = fVar12 * 0.5;
            local_a0 = fVar16 + pfVar7[0xc] + fVar12 * *pfVar7;
            local_9c = fVar17 + pfVar7[0xd] + fVar12 * pfVar7[1];
            local_98 = fVar18 + pfVar7[0xe] + fVar12 * pfVar7[2];
            if (*(int *)(param_1 + 0x38) + -1 == iVar9) {
              fVar12 = pfVar7[0x23];
              local_b0 = local_98 + fVar12 * pfVar7[10];
              local_b4 = local_9c + fVar12 * pfVar7[9];
              local_b8 = local_a0 + fVar12 * pfVar7[8];
              fVar13 = local_ac + fVar12 * pfVar7[8];
              fVar14 = local_a8 + fVar12 * pfVar7[9];
              fVar12 = local_a4 + fVar12 * pfVar7[10];
            }
            else {
              pfVar7 = (float *)(*(int *)(param_1 + 0x50) + iVar10);
              fVar14 = fVar17 + pfVar7[0xd] + fVar13 * pfVar7[1];
              local_b0 = fVar18 + pfVar7[0xe] + fVar12 * pfVar7[2];
              local_b8 = fVar16 + pfVar7[0xc] + fVar12 * *pfVar7;
              local_b4 = fVar17 + pfVar7[0xd] + fVar12 * pfVar7[1];
              fVar12 = fVar18 + pfVar7[0xe] + fVar13 * pfVar7[2];
              fVar13 = fVar16 + pfVar7[0xc] + fVar13 * *pfVar7;
            }
            local_120 = &local_94;
            fVar15 = local_118[1];
            fVar4 = local_118[2];
            *local_11c = *local_118;
            pfVar6[1] = fVar15;
            pfVar6[2] = fVar4;
            fVar3 = local_a0;
            fVar4 = local_b0;
            fVar15 = local_b4;
            pfVar6 = local_114;
            *local_114 = local_b8;
            pfVar6[1] = fVar15;
            pfVar6[2] = fVar4;
            iVar5 = PointTriangle(*local_120,local_120[1],local_120[2],fVar3,local_9c,local_98);
            pfVar6 = local_11c;
            if (iVar5 != 0) {
LAB_0004e68c:
              iVar10 = *(int *)(param_1 + 0x50) + iVar8;
              local_7c = local_fc - (fVar16 + *(float *)(iVar10 + 0x30));
              local_74 = local_104 - (fVar18 + *(float *)(iVar10 + 0x38));
              local_78 = local_100 - (fVar17 + *(float *)(iVar10 + 0x34));
              tVector::Rotate((tVector *)&local_7c,(tMatrix *)(iVar10 + 0x40));
              iVar8 = *(int *)(param_1 + 0x50) + iVar8;
              local_88 = param_3 - (fVar16 + *(float *)(iVar8 + 0x30));
              local_80 = param_5 - (fVar18 + *(float *)(iVar8 + 0x38));
              local_84 = param_4 - (fVar17 + *(float *)(iVar8 + 0x34));
              fVar16 = (float)tVector::Rotate((tVector *)&local_88,(tMatrix *)(iVar8 + 0x40));
              piVar11 = (int *)local_110[0xb8];
              iVar8 = *piVar11;
              *(undefined1 *)(iVar8 + 0x81779) = 0;
              cRSquidge::StartY((cRSquidge *)(iVar8 + 0x8535c),fVar16);
              iVar10 = *piVar11;
              *(undefined4 *)(iVar10 + 0x816ec) = 0;
              *(float *)(iVar10 + 0x816e8) = local_74;
              *(int *)(iVar10 + 0x816e4) = iVar9;
              *(int *)(iVar10 + 0x816dc) = param_1;
              *(float *)(iVar10 + 0x813c4) = local_78;
              *(undefined1 *)(iVar10 + 0x816d8) = 1;
              *(cRSubLoc **)(iVar10 + 0x816e0) = param_12;
              *(int *)(iVar10 + 0x81710) = iVar10 + 0x81364;
              *(undefined4 *)(iVar10 + 0x81770) = 0;
              iVar9 = cRSubLoc::Yi(param_12);
              iVar8 = *piVar11;
              *(undefined4 *)(param_1 + 0x80) =
                   *(undefined4 *)(gGroup0 + iVar9 * 0xdc + iVar10 + 0xd174);
              *(undefined4 *)(iVar8 + 0x816f0) = 0;
              *(undefined4 *)(iVar8 + 0x816f4) = 0;
              cRPathFollowGoldy::Traverse
                        (extraout_s0,(tVector *)(iVar8 + 0x816d8),*(tVector **)(iVar8 + 0x81774));
              return;
            }
            fVar15 = local_118[1];
            fVar4 = local_118[2];
            local_c4 = fVar13;
            local_c0 = fVar14;
            local_bc = fVar12;
            *local_11c = *local_118;
            pfVar6[1] = fVar15;
            pfVar6[2] = fVar4;
            fVar14 = local_b0;
            fVar13 = local_b4;
            fVar12 = local_c4;
            pfVar6 = local_114;
            *local_114 = local_b8;
            pfVar6[1] = fVar13;
            pfVar6[2] = fVar14;
            iVar5 = PointTriangle(*local_120,local_120[1],local_120[2],fVar12,local_c0,local_bc);
            if (iVar5 != 0) goto LAB_0004e68c;
          }
        }
      }
      iVar9 = iVar9 + -1;
      iVar8 = iVar8 + -0xa8;
      iVar10 = iVar10 + -0xa8;
    } while (-1 < iVar9);
  }
  return;
}
