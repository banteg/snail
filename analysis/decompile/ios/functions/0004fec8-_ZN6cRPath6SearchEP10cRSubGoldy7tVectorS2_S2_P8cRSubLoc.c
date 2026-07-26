/*
 * mangled: _ZN6cRPath6SearchEP10cRSubGoldy7tVectorS2_S2_P8cRSubLoc
 * demangled: cRPath::Search(cRSubGoldy*, tVector, tVector, tVector, cRSubLoc*)
 * address: 0004fec8
 * size: 1852
 */

/* cRPath::Search(cRSubGoldy*, tVector, tVector, tVector, cRSubLoc*) */

void cRPath::Search(int param_1,undefined4 param_2,float param_3,float param_4,float param_5,
                   float param_6,float param_7,float param_8,float param_9,float param_10,
                   float param_11,cRSubLoc *param_12)

{
  uint uVar1;
  byte bVar2;
  undefined *puVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  uint uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
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
  float local_70;
  float local_6c;
  float local_68;

  param_9 = param_6 - param_9;
  param_10 = param_7 - param_10;
  iVar7 = *(int *)(param_1 + 0x38) + -1;
  param_11 = param_8 - param_11;
  fVar20 = *(float *)(param_12 + 0x18);
  fVar19 = *(float *)(param_12 + 0x14);
  fVar18 = *(float *)(param_12 + 0x10);
  if (-1 < iVar7) {
    iVar6 = *(int *)(param_1 + 0x38) * 0xa8;
    do {
      iVar6 = iVar6 + -0xa8;
      pfVar5 = (float *)(iVar6 + *(int *)(param_1 + 0x50));
      fVar10 = pfVar5[5];
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar10 < 0.0) << 0x1f | (uint)(fVar10 == 0.0) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar10) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar17 = 0.5;
        fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar10 = fVar10 * 0.5;
        fVar13 = fVar18 + pfVar5[0xc] + fVar10 * *pfVar5;
        fVar12 = fVar19 + pfVar5[0xd] + fVar10 * pfVar5[1];
        fVar11 = fVar20 + pfVar5[0xe] + fVar10 * pfVar5[2];
        local_b8 = param_9 - fVar13;
        local_b4 = param_10 - fVar12;
        local_b0 = param_11 - fVar11;
        fVar10 = (float)tVector::Dot((tVector *)&local_b8,(tVector *)(pfVar5 + 4));
        uVar1 = in_fpscr & 0xfffffff | (uint)(fVar10 < 0.0) << 0x1f | (uint)(fVar10 == 0.0) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar10) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          local_c4 = param_3 - fVar13;
          local_c0 = param_4 - fVar12;
          local_bc = param_5 - fVar11;
          fVar4 = (float)tVector::Dot((tVector *)&local_c4,
                                      (tVector *)(iVar6 + *(int *)(param_1 + 0x50) + 0x10));
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar4 < 0.0) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar16 = param_3 - param_9;
            fVar15 = param_4 - param_10;
            fVar14 = param_5 - param_11;
            local_d0 = fVar16;
            local_cc = fVar15;
            local_c8 = fVar14;
            fVar4 = (float)tVector::Dot((tVector *)(iVar6 + *(int *)(param_1 + 0x50) + 0x10),
                                        (tVector *)&local_d0);
            fVar4 = -fVar10 / fVar4;
            fVar16 = param_9 + fVar16 * fVar4;
            fVar15 = param_10 + fVar15 * fVar4;
            fVar4 = param_11 + fVar14 * fVar4;
            local_dc = fVar16 - fVar13;
            local_d8 = fVar15 - fVar12;
            local_d4 = fVar4 - fVar11;
            tVector::Dot((tVector *)&local_dc,(tVector *)(iVar6 + *(int *)(param_1 + 0x50) + 0x10));
            iVar8 = *(int *)(param_1 + 0x50);
            pfVar5 = (float *)(iVar6 + iVar8);
            fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),
                                                (byte)(in_fpscr >> 0x16) & 3);
            fVar13 = fVar12 * -0.5;
            fVar12 = fVar12 * fVar17;
            local_94 = fVar18 + pfVar5[0xc] + *pfVar5 * fVar13;
            local_90 = fVar19 + pfVar5[0xd] + pfVar5[1] * fVar13;
            local_8c = fVar20 + pfVar5[0xe] + pfVar5[2] * fVar13;
            fVar11 = fVar18 + pfVar5[0xc] + fVar12 * *pfVar5;
            fVar10 = fVar20 + pfVar5[0xe] + fVar12 * pfVar5[2];
            if (*(int *)(param_1 + 0x38) + -1 == iVar7) {
              fVar13 = pfVar5[0x23];
              local_98 = fVar10 + fVar13 * pfVar5[10];
              local_9c = fVar19 + pfVar5[0xd] + fVar12 * pfVar5[1] + fVar13 * pfVar5[9];
              local_a0 = fVar11 + fVar13 * pfVar5[8];
              local_a4 = local_8c + fVar13 * pfVar5[10];
              local_a8 = local_90 + fVar13 * pfVar5[9];
              local_ac = local_94 + fVar13 * pfVar5[8];
            }
            else {
              pfVar5 = (float *)(iVar6 + iVar8 + 0xa8);
              local_a4 = fVar20 + pfVar5[0xe] + fVar13 * pfVar5[2];
              local_98 = fVar20 + pfVar5[0xe] + fVar12 * pfVar5[2];
              local_a8 = fVar19 + pfVar5[0xd] + fVar13 * pfVar5[1];
              local_9c = fVar19 + pfVar5[0xd] + fVar12 * pfVar5[1];
              local_ac = fVar18 + pfVar5[0xc] + fVar13 * *pfVar5;
              local_a0 = fVar18 + pfVar5[0xc] + fVar12 * *pfVar5;
            }
            fVar17 = local_8c - fVar10;
            fVar12 = local_94 - fVar11;
            fVar13 = (((fVar16 * fVar17 - fVar12 * fVar4) - fVar17 * fVar11) + fVar12 * fVar10) /
                     ((local_a0 - fVar11) * fVar17 - fVar12 * (local_98 - fVar10));
            uVar1 = in_fpscr & 0xfffffff;
            uVar9 = uVar1 | (uint)(fVar13 < 0.0) << 0x1f;
            local_88 = fVar16;
            local_84 = fVar15;
            local_80 = fVar4;
            if ((!SUB41(uVar9 >> 0x1f,0)) &&
               (uVar9 = uVar1 | (uint)(fVar13 < 1.0) << 0x1f | (uint)(fVar13 == 1.0) << 0x1e,
               bVar2 = (byte)(uVar9 >> 0x18),
               (bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != NAN(fVar13))) {
              if (fVar17 == 0.0) {
                fVar12 = ((fVar16 - fVar11) - (local_a0 - fVar11) * fVar13) / fVar12;
              }
              else {
                fVar12 = ((fVar4 - fVar10) - (local_98 - fVar10) * fVar13) / fVar17;
              }
              uVar9 = uVar1 | (uint)(fVar12 < 0.0) << 0x1f;
              if (!SUB41(uVar9 >> 0x1f,0)) {
                fVar13 = 1.0 - fVar13;
                uVar9 = uVar1 | (uint)(fVar12 < fVar13) << 0x1f | (uint)(fVar12 == fVar13) << 0x1e;
                bVar2 = (byte)(uVar9 >> 0x18);
                if ((bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != (NAN(fVar12) || NAN(fVar13)))
                goto LAB_000503a0;
              }
            }
            fVar12 = local_8c - local_a4;
            fVar10 = local_94 - local_ac;
            fVar11 = (((fVar16 * fVar12 - fVar4 * fVar10) - local_ac * fVar12) + local_a4 * fVar10)
                     / ((local_a0 - local_ac) * fVar12 - (local_98 - local_a4) * fVar10);
            uVar9 = uVar9 & 0xfffffff;
            in_fpscr = uVar9 | (uint)(fVar11 < 0.0) << 0x1f;
            if ((!SUB41(in_fpscr >> 0x1f,0)) &&
               (uVar1 = uVar9 | (uint)(fVar11 < 1.0) << 0x1f | (uint)(fVar11 == 1.0) << 0x1e,
               in_fpscr = uVar1 | (uint)NAN(fVar11) << 0x1c, bVar2 = (byte)(uVar1 >> 0x18),
               (bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1))) {
              if (fVar12 == 0.0) {
                fVar10 = ((fVar16 - local_ac) - (local_a0 - local_ac) * fVar11) / fVar10;
              }
              else {
                fVar10 = ((fVar4 - local_a4) - (local_98 - local_a4) * fVar11) / fVar12;
              }
              in_fpscr = uVar9 | (uint)(fVar10 < 0.0) << 0x1f;
              if (!SUB41(in_fpscr >> 0x1f,0)) {
                fVar11 = 1.0 - fVar11;
                uVar1 = uVar9 | (uint)(fVar10 < fVar11) << 0x1f | (uint)(fVar10 == fVar11) << 0x1e;
                in_fpscr = uVar1 | (uint)(NAN(fVar10) || NAN(fVar11)) << 0x1c;
                bVar2 = (byte)(uVar1 >> 0x18);
                if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
LAB_000503a0:
                  iVar8 = iVar6 + iVar8;
                  local_70 = param_6 - (fVar18 + *(float *)(iVar8 + 0x30));
                  local_6c = param_7 - (fVar19 + *(float *)(iVar8 + 0x34));
                  local_68 = param_8 - (fVar20 + *(float *)(iVar8 + 0x38));
                  tVector::Rotate((tVector *)&local_70,(tMatrix *)(iVar8 + 0x40));
                  iVar6 = iVar6 + *(int *)(param_1 + 0x50);
                  local_7c = param_3 - (fVar18 + *(float *)(iVar6 + 0x30));
                  local_78 = param_4 - (fVar19 + *(float *)(iVar6 + 0x34));
                  local_74 = param_5 - (fVar20 + *(float *)(iVar6 + 0x38));
                  tVector::Rotate((tVector *)&local_7c,(tMatrix *)(iVar6 + 0x40));
                  puVar3 = PTR__Game_001b60b8;
                  (&DAT_000823cd)[*(int *)PTR__Game_001b60b8] = 0;
                  cRSquidge::StartY((cRSquidge *)(*(int *)puVar3 + 0x85fb0),
                                    *(float *)(&DAT_000823c4 + *(int *)puVar3));
                  *(undefined1 *)(*(int *)puVar3 + 0x82334) = 1;
                  *(int *)(*(int *)puVar3 + 0x82338) = param_1;
                  *(cRSubLoc **)(*(int *)puVar3 + 0x8233c) = param_12;
                  *(int *)(*(int *)puVar3 + 0x82340) = iVar7;
                  *(float *)(*(int *)puVar3 + 0x82344) = local_68;
                  *(undefined4 *)(*(int *)puVar3 + 0x82348) = 0;
                  *(float *)(*(int *)puVar3 + 0x82020) = local_6c;
                  *(undefined4 *)(&DAT_000823c4 + *(int *)puVar3) = 0;
                  *(int *)(*(int *)puVar3 + 0x8236c) = *(int *)puVar3 + 0x81fc0;
                  iVar6 = *(int *)puVar3;
                  iVar8 = *(int *)(iVar6 + 0x82338);
                  iVar7 = cRSubLoc::Yi(param_12);
                  *(undefined4 *)(iVar8 + 0x80) =
                       *(undefined4 *)(&DAT_00256df0 + iVar7 * 0xdc + iVar6);
                  *(undefined4 *)(*(int *)puVar3 + 0x82350) = 0;
                  *(undefined4 *)(*(int *)puVar3 + 0x8234c) = 0;
                  iVar7 = *(int *)puVar3;
                  cRPathFollowGoldy::Traverse
                            ((cRPathFollowGoldy *)(iVar7 + 0x82334),
                             *(float *)(&DAT_000823c8 + iVar7),(tVector *)(iVar7 + 0x8201c),
                             (tVector *)(&UNK_000823c0 + iVar7));
                  return;
                }
              }
            }
          }
        }
      }
      iVar7 = iVar7 + -1;
    } while (iVar7 != -1);
  }
  return;
}
