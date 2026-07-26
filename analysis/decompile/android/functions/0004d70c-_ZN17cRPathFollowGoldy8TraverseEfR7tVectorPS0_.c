/*
 * mangled: _ZN17cRPathFollowGoldy8TraverseEfR7tVectorPS0_
 * demangled: cRPathFollowGoldy::Traverse(float, tVector&, tVector*)
 * address: 0004d70c
 * size: 3000
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* cRPathFollowGoldy::Traverse(float, tVector&, tVector*) */

int cRPathFollowGoldy::Traverse(float param_1,tVector *param_2,tVector *param_3)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  undefined4 uVar4;
  cRSubLoc *pcVar5;
  uint uVar6;
  int iVar7;
  float *in_r2;
  int in_r3;
  int iVar8;
  int iVar9;
  tMatrix *ptVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  int iVar17;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float in_s1;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float in_s2;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float *pfVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float local_184;
  float fStack_180;
  float fStack_17c;
  undefined4 uStack_178;
  float local_174;
  float fStack_170;
  float fStack_16c;
  undefined4 uStack_168;
  undefined4 local_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 local_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  float local_144;
  float fStack_140;
  float fStack_13c;
  undefined4 uStack_138;
  float local_134;
  float fStack_130;
  float fStack_12c;
  undefined4 uStack_128;
  undefined4 local_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 local_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 local_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 local_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 local_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 uStack_c8;
  undefined4 local_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 local_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 local_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  float local_84;
  float local_80;
  float local_7c;
  undefined4 uStack_78;
  float local_74;
  float local_70;
  float local_6c;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;

  uVar4 = DAT_0004daa0;
  iVar9 = DAT_0004da98;
  iVar7 = DAT_0004da90;
  ptVar10 = *(tMatrix **)(param_2 + 4);
  iVar13 = *(int *)(param_2 + 0xc);
  fVar26 = *(float *)(iVar13 * 0xa8 + *(int *)(ptVar10 + 0x50) + 0x8c);
  iVar12 = DAT_0004da94 + 0x4d764;
  fVar29 = fVar26 * (float)param_3;
  while( true ) {
    fVar21 = *(float *)(param_2 + 0x10);
    fVar19 = fVar21 + fVar29;
    uVar6 = in_fpscr & 0xfffffff | (uint)(fVar19 < fVar26) << 0x1f |
            (uint)(fVar19 == fVar26) << 0x1e;
    in_fpscr = uVar6 | (uint)(NAN(fVar19) || NAN(fVar26)) << 0x1c;
    bVar3 = (byte)(uVar6 >> 0x18);
    if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      iVar7 = *(int *)(ptVar10 + 0x38);
      *(float *)(param_2 + 0x10) = fVar19;
      if (iVar13 == iVar7 + -1) {
        iVar9 = iVar13 * 0xa8 + *(int *)(ptVar10 + 0x4c);
        pfVar22 = *(float **)(iVar9 + 0xa0);
        fVar26 = *(float *)(iVar9 + 0x90);
        fVar29 = *(float *)(iVar9 + 0x9c);
      }
      else {
        fVar29 = fVar19 / *(float *)(*(int *)(ptVar10 + 0x50) + iVar13 * 0xa8 + 0x8c);
        iVar9 = *(int *)(ptVar10 + 0x4c) + iVar13 * 0xa8;
        iVar8 = *(int *)(ptVar10 + 0x4c) + iVar13 * 0xa8 + 0xa8;
        fVar26 = *(float *)(iVar9 + 0x90) +
                 (*(float *)(iVar8 + 0x90) - *(float *)(iVar9 + 0x90)) * fVar29;
        pfVar22 = (float *)(*(float *)(iVar9 + 0xa0) +
                           fVar29 * (*(float *)(iVar8 + 0xa0) - *(float *)(iVar9 + 0xa0)));
        fVar29 = *(float *)(iVar9 + 0x9c) +
                 fVar29 * (*(float *)(iVar8 + 0x9c) - *(float *)(iVar9 + 0x9c));
      }
      if (*(int *)(ptVar10 + 0x2c) == 0x39) {
        cRPath::HalfPipePos(param_1,in_s1,in_s2,ptVar10,pfVar22);
        iVar7 = *(int *)(param_2 + 0xc);
        if ((iVar7 == 0) || (iVar9 = *(int *)(param_2 + 4), iVar7 == *(int *)(iVar9 + 0x38) + -1)) {
          fVar19 = (float)tMatrix::Identity((tMatrix *)&local_184);
          local_154 = local_54;
          uStack_150 = local_50;
          uStack_14c = uStack_4c;
          local_144 = local_84;
          fStack_140 = local_80;
          fStack_13c = local_7c;
          uStack_138 = uStack_78;
          local_134 = local_74;
          fStack_130 = local_70;
          fStack_12c = local_6c;
          uStack_128 = uStack_68;
          local_124 = local_64;
          uStack_120 = uStack_60;
          uStack_11c = uStack_5c;
          uStack_118 = uStack_58;
          local_114 = local_54;
          uStack_110 = local_50;
          uStack_10c = uStack_4c;
          uStack_108 = uStack_48;
          tMatrix::LinearInterpolate
                    ((tMatrix *)&local_84,(tMatrix *)&local_184,(tMatrix *)&local_144,fVar19);
          iVar9 = *(int *)(param_2 + 4);
          iVar7 = *(int *)(param_2 + 0xc);
        }
        iVar13 = DAT_0004e314;
        fVar18 = *(float *)(*(int *)(param_2 + 8) + 0x18);
        fVar21 = *(float *)(in_r3 + 4);
        iVar8 = iVar7 * 0xa8 + *(int *)(iVar9 + 0x50);
        fVar20 = *(float *)(iVar8 + 0x38);
        fVar19 = *(float *)(iVar8 + 0x88);
        *(undefined4 *)(param_2 + 0x2c) = local_54;
        *(undefined4 *)(param_2 + 0x30) = local_50;
        iVar12 = **(int **)(iVar12 + iVar13);
        *(float *)(param_2 + 0x34) = fVar18 + fVar20 + fVar19 * *(float *)(param_2 + 0x10);
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar21;
        *(float *)(iVar12 + 0x81390) = local_84 * fVar29;
        *(float *)(iVar12 + 0x81394) = local_80 * fVar29;
        *(float *)(iVar12 + 0x81398) = local_7c * fVar29;
        *(float *)(iVar12 + 0x813a0) = local_74;
        *(float *)(iVar12 + 0x813a4) = local_70;
        *(float *)(iVar12 + 0x813a8) = local_6c;
        *(undefined4 *)(iVar12 + 0x813b0) = local_64;
        *(undefined4 *)(iVar12 + 0x813b4) = uStack_60;
        *(undefined4 *)(iVar12 + 0x813b8) = uStack_5c;
      }
      else if (*(int *)(ptVar10 + 0x2c) == 0x3a) {
        cRPath::HalfPolePos(param_1,in_s1,in_s2,ptVar10,pfVar22);
        iVar7 = *(int *)(param_2 + 0xc);
        if ((iVar7 == 0) || (iVar9 = *(int *)(param_2 + 4), iVar7 == *(int *)(iVar9 + 0x38) + -1)) {
          fVar19 = (float)tMatrix::Identity((tMatrix *)&local_144);
          local_114 = local_54;
          uStack_110 = local_50;
          uStack_10c = uStack_4c;
          local_184 = local_84;
          fStack_180 = local_80;
          fStack_17c = local_7c;
          uStack_178 = uStack_78;
          local_174 = local_74;
          fStack_170 = local_70;
          fStack_16c = local_6c;
          uStack_168 = uStack_68;
          local_164 = local_64;
          uStack_160 = uStack_60;
          uStack_15c = uStack_5c;
          uStack_158 = uStack_58;
          local_154 = local_54;
          uStack_150 = local_50;
          uStack_14c = uStack_4c;
          uStack_148 = uStack_48;
          tMatrix::LinearInterpolate
                    ((tMatrix *)&local_84,(tMatrix *)&local_144,(tMatrix *)&local_184,fVar19);
          iVar9 = *(int *)(param_2 + 4);
          iVar7 = *(int *)(param_2 + 0xc);
        }
        iVar13 = DAT_0004e314;
        fVar18 = *(float *)(*(int *)(param_2 + 8) + 0x18);
        fVar21 = *(float *)(in_r3 + 4);
        iVar8 = iVar7 * 0xa8 + *(int *)(iVar9 + 0x50);
        fVar20 = *(float *)(iVar8 + 0x38);
        fVar19 = *(float *)(iVar8 + 0x88);
        *(undefined4 *)(param_2 + 0x2c) = local_54;
        piVar11 = *(int **)(iVar12 + iVar13);
        *(undefined4 *)(param_2 + 0x30) = local_50;
        iVar12 = *piVar11;
        *(float *)(param_2 + 0x34) = fVar18 + fVar20 + fVar19 * *(float *)(param_2 + 0x10);
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar21;
        *(float *)(iVar12 + 0x81390) = local_84 * fVar29;
        *(float *)(iVar12 + 0x81394) = local_80 * fVar29;
        *(float *)(iVar12 + 0x81398) = local_7c * fVar29;
        *(float *)(iVar12 + 0x813a0) = local_74;
        *(float *)(iVar12 + 0x813a4) = local_70;
        *(float *)(iVar12 + 0x813a8) = local_6c;
        *(undefined4 *)(iVar12 + 0x813b0) = local_64;
        *(undefined4 *)(iVar12 + 0x813b4) = uStack_60;
        *(undefined4 *)(iVar12 + 0x813b8) = uStack_5c;
      }
      else {
        iVar9 = *(int *)(param_2 + 8);
        fVar30 = *(float *)(iVar9 + 0x18);
        fVar31 = *(float *)(iVar9 + 0x10);
        fVar32 = *(float *)(iVar9 + 0x14);
        puVar16 = (undefined4 *)(iVar13 * 0xa8 + *(int *)(ptVar10 + 0x50));
        fVar25 = (float)puVar16[0x20];
        fVar24 = (float)puVar16[0x21];
        fVar21 = (float)puVar16[0xc];
        fVar18 = (float)puVar16[0xd];
        fVar20 = (float)puVar16[0xe];
        fVar28 = (float)puVar16[0x22];
        if (iVar13 == iVar7 + -1) {
          tMatrix::Identity((tMatrix *)&local_84);
        }
        else {
          local_c4 = *puVar16;
          uStack_c0 = puVar16[1];
          uStack_bc = puVar16[2];
          uStack_b8 = puVar16[3];
          puVar15 = (undefined4 *)(*(int *)(ptVar10 + 0x50) + iVar13 * 0xa8 + 0xa8);
          local_b4 = puVar16[4];
          uStack_b0 = puVar16[5];
          uStack_ac = puVar16[6];
          uStack_a8 = puVar16[7];
          local_a4 = puVar16[8];
          uStack_a0 = puVar16[9];
          uStack_9c = puVar16[10];
          uStack_98 = puVar16[0xb];
          uStack_88 = puVar16[0xf];
          local_104 = *puVar15;
          uStack_100 = puVar15[1];
          uStack_fc = puVar15[2];
          uStack_f8 = puVar15[3];
          local_f4 = puVar15[4];
          uStack_f0 = puVar15[5];
          uStack_ec = puVar15[6];
          uStack_e8 = puVar15[7];
          local_e4 = puVar15[8];
          uStack_e0 = puVar15[9];
          uStack_dc = puVar15[10];
          uStack_d8 = puVar15[0xb];
          uStack_c8 = puVar15[0xf];
          local_8c = DAT_0004daa0;
          local_90 = DAT_0004daa0;
          local_94 = DAT_0004daa0;
          local_d4 = DAT_0004daa0;
          local_cc = DAT_0004daa0;
          local_d0 = DAT_0004daa0;
          tMatrix::LinearInterpolate
                    ((tMatrix *)&local_84,(tMatrix *)&local_c4,(tMatrix *)&local_104,param_1);
        }
        fVar27 = *(float *)(param_2 + 0x14) + *(float *)(in_r3 + 4);
        iVar7 = **(int **)(iVar12 + DAT_0004da98);
        *(float *)(param_2 + 0x14) = fVar27;
        fVar23 = *in_r2 - fVar26;
        *(float *)(param_2 + 0x2c) =
             fVar31 + fVar21 + fVar19 * fVar25 * fVar29 + fVar23 * local_84 * fVar29 +
             fVar27 * local_74;
        *(float *)(param_2 + 0x34) =
             fVar30 + fVar20 + fVar19 * fVar28 + fVar23 * fVar29 * local_7c + fVar27 * local_6c;
        *(float *)(param_2 + 0x30) =
             fVar32 + fVar18 + fVar19 * fVar24 * fVar29 + fVar23 * local_80 * fVar29 +
             fVar27 * local_70;
        *(float *)(iVar7 + 0x81390) = local_84 * fVar29;
        *(float *)(iVar7 + 0x81394) = local_80 * fVar29;
        *(float *)(iVar7 + 0x81398) = fVar29 * local_7c;
        *(float *)(iVar7 + 0x813a0) = local_74;
        *(float *)(iVar7 + 0x813a4) = local_70;
        *(float *)(iVar7 + 0x813a8) = local_6c;
        *(undefined4 *)(iVar7 + 0x813b0) = local_64;
        *(undefined4 *)(iVar7 + 0x813b4) = uStack_60;
        *(undefined4 *)(iVar7 + 0x813b8) = uStack_5c;
        iVar9 = *(int *)(param_2 + 4);
        iVar7 = *(int *)(param_2 + 0xc);
      }
      iVar12 = *(int *)(iVar9 + 0x38);
      *(float *)(param_2 + 0x20) = local_74;
      *(float *)(param_2 + 0x24) = local_70;
      *(float *)(param_2 + 0x28) = local_6c;
      fVar29 = DAT_0004daa4;
      if (iVar7 == iVar12 + -1) {
        iVar12 = iVar7 * 0xa8 + *(int *)(iVar9 + 0x4c);
        *(undefined4 *)(param_2 + 0x1c) = *(undefined4 *)(iVar12 + 0x98);
        *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(iVar12 + 0x94);
      }
      else {
        fVar19 = *(float *)(*(int *)(iVar9 + 0x4c) + iVar7 * 0xa8 + 0x98);
        fVar21 = *(float *)(*(int *)(iVar9 + 0x4c) + iVar7 * 0xa8 + 0x140) - fVar19;
        uVar6 = in_fpscr & 0xfffffff | (uint)(fVar21 < DAT_0004daa4) << 0x1f |
                (uint)(fVar21 == DAT_0004daa4) << 0x1e;
        bVar3 = (byte)(uVar6 >> 0x18);
        if ((bool)(bVar3 >> 6 & 1) || (bool)(bVar3 >> 7) != (NAN(fVar21) || NAN(DAT_0004daa4))) {
          uVar6 = in_fpscr & 0xfffffff | (uint)(fVar21 < DAT_0004e304) << 0x1f;
          if (SUB41(uVar6 >> 0x1f,0)) {
            fVar21 = fVar21 + DAT_0004e308;
          }
        }
        else {
          fVar21 = fVar21 - DAT_0004daa8;
        }
        iVar12 = *(int *)(iVar9 + 0x4c);
        *(float *)(param_2 + 0x1c) =
             fVar19 + (*(float *)(param_2 + 0x10) /
                      *(float *)(*(int *)(iVar9 + 0x50) + iVar7 * 0xa8 + 0x8c)) * fVar21;
        fVar19 = *(float *)(iVar12 + iVar7 * 0xa8 + 0x94);
        fVar21 = *(float *)(iVar12 + iVar7 * 0xa8 + 0x13c) - fVar19;
        uVar2 = uVar6 & 0xfffffff | (uint)(fVar21 < fVar29) << 0x1f |
                (uint)(fVar21 == fVar29) << 0x1e;
        in_fpscr = uVar2 | (uint)(NAN(fVar21) || NAN(fVar29)) << 0x1c;
        bVar3 = (byte)(uVar2 >> 0x18);
        if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
          in_fpscr = uVar6 & 0xfffffff | (uint)(fVar21 < DAT_0004e304) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar21 = fVar21 + DAT_0004e308;
          }
        }
        else {
          fVar21 = fVar21 - DAT_0004daa8;
        }
        *(float *)(param_2 + 0x18) =
             fVar19 + (*(float *)(param_2 + 0x10) /
                      *(float *)(*(int *)(iVar9 + 0x50) + iVar7 * 0xa8 + 0x8c)) * fVar21;
      }
      uVar6 = in_fpscr & 0xfffffff | (uint)(*(float *)(iVar9 + 0x80) == 0.0) << 0x1e;
      if (!SUB41(uVar6 >> 0x1e,0)) {
        fVar29 = (float)VectorSignedToFloat(iVar7,(byte)(uVar6 >> 0x16) & 3);
        fVar19 = (float)VectorSignedToFloat(*(undefined4 *)(iVar9 + 0x38),(byte)(uVar6 >> 0x16) & 3)
        ;
        *(float *)(param_2 + 0x1c) =
             (*(float *)(iVar9 + 0x80) *
             (*(float *)(param_2 + 0x10) / *(float *)(iVar7 * 0xa8 + *(int *)(iVar9 + 0x50) + 0x8c)
             + fVar29)) / fVar19;
      }
      uVar4 = DAT_0004e300;
      fVar29 = DAT_0004dab4;
      fVar19 = (float)VectorSignedToFloat(*(undefined4 *)(iVar9 + 0x48),(byte)(uVar6 >> 0x16) & 3);
      fVar26 = *in_r2 - fVar26;
      if (fVar26 < 0.0) {
        fVar26 = -fVar26;
      }
      if (fVar26 <= DAT_0004dab0 + fVar19 * DAT_0004daac) {
        fVar26 = *(float *)(param_2 + 0x14);
      }
      else {
        fVar26 = *(float *)(param_2 + 0x14);
        if (fVar26 <= 0.0) {
          iVar7 = *(int *)(param_2 + 0x38);
          fVar26 = *(float *)(param_2 + 0x30);
          fVar19 = *(float *)(param_2 + 0x34);
          *in_r2 = *(float *)(param_2 + 0x2c);
          in_r2[1] = fVar26;
          in_r2[2] = fVar19;
          *(float *)(iVar7 + 0x360) = *(float *)(iVar7 + 0x360) + *(float *)(iVar9 + 0x80);
          fVar26 = *in_r2;
          if ((fVar29 <= fVar26) && (fVar29 = fVar26, DAT_0004dab8 < fVar26)) {
            fVar29 = DAT_0004dab8;
          }
          uVar6 = *(uint *)(iVar9 + 0x34);
          *in_r2 = fVar29;
          if (uVar6 < 2) {
            return 1 - uVar6;
          }
          return 0;
        }
      }
      if (fVar26 < 0.0) {
        *(undefined4 *)(param_2 + 0x14) = DAT_0004e300;
        *(undefined4 *)(in_r3 + 4) = uVar4;
      }
      return 0;
    }
    iVar13 = iVar13 + 1;
    *(int *)(param_2 + 0xc) = iVar13;
    *(undefined4 *)(param_2 + 0x10) = uVar4;
    iVar8 = *(int *)(ptVar10 + 0x38);
    fVar29 = fVar29 - (fVar26 - fVar21);
    if (iVar13 == iVar8 * 2) {
      cRVoiceManager::Play(*(int *)(iVar12 + iVar7),4,1);
      ptVar10 = *(tMatrix **)(param_2 + 4);
      iVar13 = *(int *)(param_2 + 0xc);
      iVar8 = *(int *)(ptVar10 + 0x38);
      param_1 = extraout_s0;
      in_s1 = extraout_s1;
      in_s2 = extraout_s2;
    }
    if (ptVar10[0x84] != (tMatrix)0x0) {
      if (iVar8 + -1 == iVar13) {
        piVar11 = *(int **)(iVar12 + iVar9);
        iVar17 = *piVar11;
        iVar13 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar8 = *piVar11;
        iVar17 = *(int *)(gGroup0 + iVar13 * 0xdc + iVar17 + 0xd16c);
        iVar13 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar14 = *piVar11;
        pcVar5 = *(cRSubLoc **)(param_2 + 8);
        *(undefined4 *)(iVar17 + 0x24) =
             *(undefined4 *)
              (*(int *)(*(int *)(gGroup0 + iVar13 * 0xdc + iVar8 + 0xd16c) + 0x2c) + 0x8c);
        iVar13 = cRSubLoc::Yi(pcVar5);
        tColourSmall::Alpha((tColourSmall *)
                            (*(int *)(gGroup0 + iVar13 * 0xdc + iVar14 + 0xd16c) + 0x28),
                            extraout_s0_00);
        ptVar10 = *(tMatrix **)(param_2 + 4);
        iVar13 = *(int *)(param_2 + 0xc);
        iVar8 = *(int *)(ptVar10 + 0x38);
        param_1 = extraout_s0_01;
        in_s1 = extraout_s1_00;
        in_s2 = extraout_s2_00;
      }
      else if ((iVar8 * 3) / 7 == iVar13) {
        piVar11 = *(int **)(iVar12 + iVar9);
        iVar8 = *piVar11;
        iVar13 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar17 = *piVar11;
        pcVar5 = *(cRSubLoc **)(param_2 + 8);
        *(uint *)(*(int *)(gGroup0 + iVar13 * 0xdc + iVar8 + 0xd16c) + 4) =
             *(uint *)(*(int *)(gGroup0 + iVar13 * 0xdc + iVar8 + 0xd16c) + 4) | 0x80;
        iVar13 = cRSubLoc::Yi(pcVar5);
        iVar8 = *piVar11;
        iVar17 = *(int *)(gGroup0 + iVar13 * 0xdc + iVar17 + 0xd16c);
        iVar13 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar14 = *piVar11;
        pcVar5 = *(cRSubLoc **)(param_2 + 8);
        *(undefined4 *)(iVar17 + 0x24) =
             *(undefined4 *)
              (*(int *)(*(int *)(gGroup0 + iVar13 * 0xdc + iVar8 + 0xd16c) + 0x2c) + 0x88);
        iVar13 = cRSubLoc::Yi(pcVar5);
        tColourSmall::Alpha((tColourSmall *)
                            (*(int *)(gGroup0 + iVar13 * 0xdc + iVar14 + 0xd16c) + 0x28),
                            extraout_s0_02);
        iVar8 = *piVar11;
        iVar13 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        ptVar10 = *(tMatrix **)(param_2 + 4);
        *(undefined4 *)(*(int *)(*(int *)(gGroup0 + iVar13 * 0xdc + iVar8 + 0xd16c) + 0x24) + 8) = 1
        ;
        iVar13 = *(int *)(param_2 + 0xc);
        iVar8 = *(int *)(ptVar10 + 0x38);
        param_1 = extraout_s0_03;
        in_s1 = extraout_s1_01;
        in_s2 = extraout_s2_01;
      }
    }
    fVar19 = DAT_0004da8c;
    fVar26 = DAT_0004da88;
    if (iVar8 == iVar13) break;
    fVar26 = *(float *)(iVar13 * 0xa8 + *(int *)(ptVar10 + 0x50) + 0x8c);
  }
  iVar7 = *(int *)(ptVar10 + 0x50);
  bVar1 = DAT_0004da88 <= fVar29;
  iVar9 = *(int *)(ptVar10 + 0x2c);
  fVar21 = (float)param_3 * *(float *)((*(int *)(ptVar10 + 0x38) + -1) * 0xa8 + iVar7 + 0x8c);
  *param_2 = (tVector)0x0;
  if (bVar1) {
    fVar29 = fVar19;
  }
  if (fVar21 <= fVar26) {
    fVar26 = fVar21;
  }
  *(float *)(in_r3 + 8) = fVar26;
  if (iVar9 == 0x26) {
    iVar17 = *(int *)(param_2 + 8);
    fVar24 = *(float *)(iVar17 + 0x18);
    iVar7 = (*(int *)(ptVar10 + 0x38) + -1) * 0xa8 + iVar7;
    fVar28 = *(float *)(iVar7 + 0x38);
    fVar20 = *(float *)(iVar7 + 0x28);
    iVar8 = *(int *)(param_2 + 0x38);
    iVar13 = **(int **)(iVar12 + DAT_0004da98);
    iVar9 = *(int *)(iVar12 + DAT_0004da9c);
    *(float *)(in_r3 + 4) = fVar26 * DAT_0004dabc;
    fVar19 = *(float *)(ptVar10 + 0x44);
    fVar21 = *(float *)(iVar17 + 0x14);
    fVar25 = *(float *)(iVar7 + 0x34);
    fVar18 = *(float *)(iVar7 + 0x24);
    in_r2[2] = fVar24 + fVar28 + (fVar29 + fVar19) * fVar20;
    fVar26 = DAT_0004e2fc;
    in_r2[1] = fVar21 + fVar25 + (fVar29 + fVar19) * fVar18;
    fVar26 = *(float *)(iVar13 + 0x718f4) * fVar26;
    *(float *)(iVar8 + 0x2c4) = fVar26;
    *(float *)(iVar8 + 0x2c8) = fVar26;
    cRSound::Play(iVar9);
    cRVoiceManager::Play(*(int *)(iVar12 + DAT_0004e310),0xf,0);
    ptVar10 = *(tMatrix **)(param_2 + 4);
  }
  else {
    in_r2[2] = *(float *)(*(int *)(param_2 + 8) + 0x18) +
               *(float *)((*(int *)(ptVar10 + 0x38) + -1) * 0xa8 + *(int *)(ptVar10 + 0x50) + 0x38)
               + *(float *)(ptVar10 + 0x44) + fVar29;
  }
  *(float *)(*(int *)(param_2 + 0x38) + 0x360) =
       *(float *)(*(int *)(param_2 + 0x38) + 0x360) + *(float *)(ptVar10 + 0x80);
  return 3;
}
