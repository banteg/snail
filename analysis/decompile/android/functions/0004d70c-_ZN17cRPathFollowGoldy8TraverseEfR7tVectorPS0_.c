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
  uint uVar1;
  byte bVar2;
  cRSubLoc *pcVar3;
  uint uVar4;
  float *in_r2;
  float *pfVar5;
  int in_r3;
  int iVar6;
  int iVar7;
  tMatrix *ptVar8;
  float *pfVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  int iVar13;
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
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
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

  ptVar8 = *(tMatrix **)(param_2 + 4);
  iVar10 = *(int *)(param_2 + 0xc);
  fVar20 = *(float *)(iVar10 * 0xa8 + *(int *)(ptVar8 + 0x50) + 0x8c);
  fVar24 = fVar20 * (float)param_3;
  while( true ) {
    fVar16 = *(float *)(param_2 + 0x10);
    fVar14 = fVar16 + fVar24;
    uVar4 = in_fpscr & 0xfffffff | (uint)(fVar14 < fVar20) << 0x1f |
            (uint)(fVar14 == fVar20) << 0x1e;
    in_fpscr = uVar4 | (uint)(NAN(fVar14) || NAN(fVar20)) << 0x1c;
    bVar2 = (byte)(uVar4 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      iVar6 = *(int *)(ptVar8 + 0x38);
      *(float *)(param_2 + 0x10) = fVar14;
      if (iVar10 == iVar6 + -1) {
        iVar13 = iVar10 * 0xa8 + *(int *)(ptVar8 + 0x4c);
        pfVar5 = *(float **)(iVar13 + 0xa0);
        fVar20 = *(float *)(iVar13 + 0x90);
        fVar24 = *(float *)(iVar13 + 0x9c);
      }
      else {
        fVar24 = fVar14 / *(float *)(*(int *)(ptVar8 + 0x50) + iVar10 * 0xa8 + 0x8c);
        iVar13 = *(int *)(ptVar8 + 0x4c) + iVar10 * 0xa8;
        iVar7 = *(int *)(ptVar8 + 0x4c) + iVar10 * 0xa8 + 0xa8;
        fVar20 = *(float *)(iVar13 + 0x90) +
                 (*(float *)(iVar7 + 0x90) - *(float *)(iVar13 + 0x90)) * fVar24;
        pfVar5 = (float *)(*(float *)(iVar13 + 0xa0) +
                          fVar24 * (*(float *)(iVar7 + 0xa0) - *(float *)(iVar13 + 0xa0)));
        fVar24 = *(float *)(iVar13 + 0x9c) +
                 fVar24 * (*(float *)(iVar7 + 0x9c) - *(float *)(iVar13 + 0x9c));
      }
      if (*(int *)(ptVar8 + 0x2c) == 0x39) {
        cRPath::HalfPipePos(param_1,in_s1,in_s2,ptVar8,pfVar5);
        iVar10 = *(int *)(param_2 + 0xc);
        if ((iVar10 == 0) || (iVar6 = *(int *)(param_2 + 4), iVar10 == *(int *)(iVar6 + 0x38) + -1))
        {
          fVar14 = (float)tMatrix::Identity((tMatrix *)&local_184);
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
                    ((tMatrix *)&local_84,(tMatrix *)&local_184,(tMatrix *)&local_144,fVar14);
          iVar6 = *(int *)(param_2 + 4);
          iVar10 = *(int *)(param_2 + 0xc);
        }
        fVar15 = *(float *)(*(int *)(param_2 + 8) + 0x18);
        fVar16 = *(float *)(in_r3 + 4);
        iVar13 = iVar10 * 0xa8 + *(int *)(iVar6 + 0x50);
        fVar18 = *(float *)(iVar13 + 0x38);
        fVar14 = *(float *)(iVar13 + 0x88);
        *(undefined4 *)(param_2 + 0x2c) = local_54;
        *(undefined4 *)(param_2 + 0x30) = local_50;
        iVar13 = Game;
        pfVar5 = (float *)(Game + 0x81390);
        pfVar9 = (float *)(Game + 0x813a0);
        puVar12 = (undefined4 *)(Game + 0x813b0);
        *(float *)(param_2 + 0x34) = fVar15 + fVar18 + fVar14 * *(float *)(param_2 + 0x10);
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar16;
        *pfVar5 = local_84 * fVar24;
        *(float *)(iVar13 + 0x81394) = local_80 * fVar24;
        *(float *)(iVar13 + 0x81398) = local_7c * fVar24;
        *pfVar9 = local_74;
        *(float *)(iVar13 + 0x813a4) = local_70;
        *(float *)(iVar13 + 0x813a8) = local_6c;
        *puVar12 = local_64;
        *(undefined4 *)(iVar13 + 0x813b4) = uStack_60;
        *(undefined4 *)(iVar13 + 0x813b8) = uStack_5c;
      }
      else if (*(int *)(ptVar8 + 0x2c) == 0x3a) {
        cRPath::HalfPolePos(param_1,in_s1,in_s2,ptVar8,pfVar5);
        iVar10 = *(int *)(param_2 + 0xc);
        if ((iVar10 == 0) || (iVar6 = *(int *)(param_2 + 4), iVar10 == *(int *)(iVar6 + 0x38) + -1))
        {
          fVar14 = (float)tMatrix::Identity((tMatrix *)&local_144);
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
                    ((tMatrix *)&local_84,(tMatrix *)&local_144,(tMatrix *)&local_184,fVar14);
          iVar6 = *(int *)(param_2 + 4);
          iVar10 = *(int *)(param_2 + 0xc);
        }
        fVar15 = *(float *)(*(int *)(param_2 + 8) + 0x18);
        fVar16 = *(float *)(in_r3 + 4);
        iVar13 = iVar10 * 0xa8 + *(int *)(iVar6 + 0x50);
        fVar18 = *(float *)(iVar13 + 0x38);
        fVar14 = *(float *)(iVar13 + 0x88);
        *(undefined4 *)(param_2 + 0x2c) = local_54;
        *(undefined4 *)(param_2 + 0x30) = local_50;
        iVar13 = Game;
        pfVar5 = (float *)(Game + 0x81390);
        pfVar9 = (float *)(Game + 0x813a0);
        puVar12 = (undefined4 *)(Game + 0x813b0);
        *(float *)(param_2 + 0x34) = fVar15 + fVar18 + fVar14 * *(float *)(param_2 + 0x10);
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar16;
        *pfVar5 = local_84 * fVar24;
        *(float *)(iVar13 + 0x81394) = local_80 * fVar24;
        *(float *)(iVar13 + 0x81398) = local_7c * fVar24;
        *pfVar9 = local_74;
        *(float *)(iVar13 + 0x813a4) = local_70;
        *(float *)(iVar13 + 0x813a8) = local_6c;
        *puVar12 = local_64;
        *(undefined4 *)(iVar13 + 0x813b4) = uStack_60;
        *(undefined4 *)(iVar13 + 0x813b8) = uStack_5c;
      }
      else {
        iVar13 = *(int *)(param_2 + 8);
        fVar25 = *(float *)(iVar13 + 0x18);
        fVar26 = *(float *)(iVar13 + 0x10);
        fVar27 = *(float *)(iVar13 + 0x14);
        puVar12 = (undefined4 *)(iVar10 * 0xa8 + *(int *)(ptVar8 + 0x50));
        fVar23 = (float)puVar12[0x20];
        fVar19 = (float)puVar12[0x21];
        fVar16 = (float)puVar12[0xc];
        fVar15 = (float)puVar12[0xd];
        fVar18 = (float)puVar12[0xe];
        fVar21 = (float)puVar12[0x22];
        if (iVar10 == iVar6 + -1) {
          tMatrix::Identity((tMatrix *)&local_84);
        }
        else {
          local_c4 = *puVar12;
          uStack_c0 = puVar12[1];
          uStack_bc = puVar12[2];
          uStack_b8 = puVar12[3];
          puVar11 = (undefined4 *)(*(int *)(ptVar8 + 0x50) + iVar10 * 0xa8 + 0xa8);
          local_b4 = puVar12[4];
          uStack_b0 = puVar12[5];
          uStack_ac = puVar12[6];
          uStack_a8 = puVar12[7];
          local_a4 = puVar12[8];
          uStack_a0 = puVar12[9];
          uStack_9c = puVar12[10];
          uStack_98 = puVar12[0xb];
          uStack_88 = puVar12[0xf];
          local_104 = *puVar11;
          uStack_100 = puVar11[1];
          uStack_fc = puVar11[2];
          uStack_f8 = puVar11[3];
          local_f4 = puVar11[4];
          uStack_f0 = puVar11[5];
          uStack_ec = puVar11[6];
          uStack_e8 = puVar11[7];
          local_e4 = puVar11[8];
          uStack_e0 = puVar11[9];
          uStack_dc = puVar11[10];
          uStack_d8 = puVar11[0xb];
          uStack_c8 = puVar11[0xf];
          local_8c = 0;
          local_90 = 0;
          local_94 = 0;
          local_d4 = 0;
          local_cc = 0;
          local_d0 = 0;
          tMatrix::LinearInterpolate
                    ((tMatrix *)&local_84,(tMatrix *)&local_c4,(tMatrix *)&local_104,param_1);
        }
        iVar10 = Game;
        fVar22 = *(float *)(param_2 + 0x14) + *(float *)(in_r3 + 4);
        *(float *)(param_2 + 0x14) = fVar22;
        fVar17 = *in_r2 - fVar20;
        *(float *)(param_2 + 0x2c) =
             fVar26 + fVar16 + fVar14 * fVar23 * fVar24 + fVar17 * local_84 * fVar24 +
             fVar22 * local_74;
        *(float *)(param_2 + 0x34) =
             fVar25 + fVar18 + fVar14 * fVar21 + fVar17 * fVar24 * local_7c + fVar22 * local_6c;
        *(float *)(param_2 + 0x30) =
             fVar27 + fVar15 + fVar14 * fVar19 * fVar24 + fVar17 * local_80 * fVar24 +
             fVar22 * local_70;
        *(float *)(iVar10 + 0x81390) = local_84 * fVar24;
        *(float *)(iVar10 + 0x81394) = local_80 * fVar24;
        *(float *)(iVar10 + 0x81398) = fVar24 * local_7c;
        *(float *)(iVar10 + 0x813a0) = local_74;
        *(float *)(iVar10 + 0x813a4) = local_70;
        *(float *)(iVar10 + 0x813a8) = local_6c;
        *(undefined4 *)(iVar10 + 0x813b0) = local_64;
        *(undefined4 *)(iVar10 + 0x813b4) = uStack_60;
        *(undefined4 *)(iVar10 + 0x813b8) = uStack_5c;
        iVar6 = *(int *)(param_2 + 4);
        iVar10 = *(int *)(param_2 + 0xc);
      }
      iVar13 = *(int *)(iVar6 + 0x38);
      *(float *)(param_2 + 0x20) = local_74;
      *(float *)(param_2 + 0x24) = local_70;
      *(float *)(param_2 + 0x28) = local_6c;
      if (iVar10 == iVar13 + -1) {
        iVar13 = iVar10 * 0xa8 + *(int *)(iVar6 + 0x4c);
        *(undefined4 *)(param_2 + 0x1c) = *(undefined4 *)(iVar13 + 0x98);
        *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(iVar13 + 0x94);
      }
      else {
        fVar24 = *(float *)(*(int *)(iVar6 + 0x4c) + iVar10 * 0xa8 + 0x98);
        fVar14 = *(float *)(*(int *)(iVar6 + 0x4c) + iVar10 * 0xa8 + 0x140) - fVar24;
        uVar4 = in_fpscr & 0xfffffff | (uint)(fVar14 < 3.1415927) << 0x1f |
                (uint)(fVar14 == 3.1415927) << 0x1e;
        bVar2 = (byte)(uVar4 >> 0x18);
        if ((bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != NAN(fVar14)) {
          uVar4 = in_fpscr & 0xfffffff | (uint)(fVar14 < -3.1415927) << 0x1f;
          if (SUB41(uVar4 >> 0x1f,0)) {
            fVar14 = fVar14 + 6.2831855;
          }
        }
        else {
          fVar14 = fVar14 - 6.2831855;
        }
        iVar13 = *(int *)(iVar6 + 0x4c);
        *(float *)(param_2 + 0x1c) =
             fVar24 + (*(float *)(param_2 + 0x10) /
                      *(float *)(*(int *)(iVar6 + 0x50) + iVar10 * 0xa8 + 0x8c)) * fVar14;
        fVar24 = *(float *)(iVar13 + iVar10 * 0xa8 + 0x94);
        fVar14 = *(float *)(iVar13 + iVar10 * 0xa8 + 0x13c) - fVar24;
        uVar1 = uVar4 & 0xfffffff | (uint)(fVar14 < 3.1415927) << 0x1f |
                (uint)(fVar14 == 3.1415927) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar14) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
          in_fpscr = uVar4 & 0xfffffff | (uint)(fVar14 < -3.1415927) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar14 = fVar14 + 6.2831855;
          }
        }
        else {
          fVar14 = fVar14 - 6.2831855;
        }
        *(float *)(param_2 + 0x18) =
             fVar24 + (*(float *)(param_2 + 0x10) /
                      *(float *)(*(int *)(iVar6 + 0x50) + iVar10 * 0xa8 + 0x8c)) * fVar14;
      }
      uVar4 = in_fpscr & 0xfffffff | (uint)(*(float *)(iVar6 + 0x80) == 0.0) << 0x1e;
      if (!SUB41(uVar4 >> 0x1e,0)) {
        fVar24 = (float)VectorSignedToFloat(iVar10,(byte)(uVar4 >> 0x16) & 3);
        fVar14 = (float)VectorSignedToFloat(*(undefined4 *)(iVar6 + 0x38),(byte)(uVar4 >> 0x16) & 3)
        ;
        *(float *)(param_2 + 0x1c) =
             (*(float *)(iVar6 + 0x80) *
             (*(float *)(param_2 + 0x10) / *(float *)(iVar10 * 0xa8 + *(int *)(iVar6 + 0x50) + 0x8c)
             + fVar24)) / fVar14;
      }
      fVar24 = (float)VectorSignedToFloat(*(undefined4 *)(iVar6 + 0x48),(byte)(uVar4 >> 0x16) & 3);
      fVar20 = *in_r2 - fVar20;
      if (fVar20 < 0.0) {
        fVar20 = -fVar20;
      }
      if (fVar20 <= fVar24 * 0.5 + 0.3) {
        fVar24 = *(float *)(param_2 + 0x14);
      }
      else {
        fVar24 = *(float *)(param_2 + 0x14);
        if (fVar24 <= 0.0) {
          iVar10 = *(int *)(param_2 + 0x38);
          fVar24 = -4.0;
          fVar20 = *(float *)(param_2 + 0x30);
          fVar14 = *(float *)(param_2 + 0x34);
          *in_r2 = *(float *)(param_2 + 0x2c);
          in_r2[1] = fVar20;
          in_r2[2] = fVar14;
          *(float *)(iVar10 + 0x360) = *(float *)(iVar10 + 0x360) + *(float *)(iVar6 + 0x80);
          fVar20 = *in_r2;
          if ((-4.0 <= fVar20) && (fVar24 = fVar20, 4.0 < fVar20)) {
            fVar24 = 4.0;
          }
          uVar4 = *(uint *)(iVar6 + 0x34);
          *in_r2 = fVar24;
          if (uVar4 < 2) {
            return 1 - uVar4;
          }
          return 0;
        }
      }
      if (fVar24 < 0.0) {
        *(undefined4 *)(param_2 + 0x14) = 0;
        *(undefined4 *)(in_r3 + 4) = 0;
      }
      return 0;
    }
    iVar10 = iVar10 + 1;
    *(int *)(param_2 + 0xc) = iVar10;
    *(undefined4 *)(param_2 + 0x10) = 0;
    iVar6 = *(int *)(ptVar8 + 0x38);
    fVar24 = fVar24 - (fVar20 - fVar16);
    if (iVar10 == iVar6 * 2) {
      cRVoiceManager::Play((int)&gVoiceManager,4,1);
      ptVar8 = *(tMatrix **)(param_2 + 4);
      iVar10 = *(int *)(param_2 + 0xc);
      iVar6 = *(int *)(ptVar8 + 0x38);
      param_1 = extraout_s0;
      in_s1 = extraout_s1;
      in_s2 = extraout_s2;
    }
    iVar13 = Game;
    if (ptVar8[0x84] != (tMatrix)0x0) {
      if (iVar6 + -1 == iVar10) {
        iVar6 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar10 = Game;
        iVar7 = *(int *)(gGroup0 + iVar6 * 0xdc + iVar13 + 0xd16c);
        iVar13 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar6 = Game;
        pcVar3 = *(cRSubLoc **)(param_2 + 8);
        *(undefined4 *)(iVar7 + 0x24) =
             *(undefined4 *)
              (*(int *)(*(int *)(gGroup0 + iVar13 * 0xdc + iVar10 + 0xd16c) + 0x2c) + 0x8c);
        iVar10 = cRSubLoc::Yi(pcVar3);
        tColourSmall::Alpha((tColourSmall *)
                            (*(int *)(gGroup0 + iVar10 * 0xdc + iVar6 + 0xd16c) + 0x28),
                            extraout_s0_00);
        ptVar8 = *(tMatrix **)(param_2 + 4);
        iVar10 = *(int *)(param_2 + 0xc);
        iVar6 = *(int *)(ptVar8 + 0x38);
        param_1 = extraout_s0_01;
        in_s1 = extraout_s1_00;
        in_s2 = extraout_s2_00;
      }
      else if ((iVar6 * 3) / 7 == iVar10) {
        iVar6 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar10 = Game;
        pcVar3 = *(cRSubLoc **)(param_2 + 8);
        *(uint *)(*(int *)(gGroup0 + iVar6 * 0xdc + iVar13 + 0xd16c) + 4) =
             *(uint *)(*(int *)(gGroup0 + iVar6 * 0xdc + iVar13 + 0xd16c) + 4) | 0x80;
        iVar13 = cRSubLoc::Yi(pcVar3);
        iVar6 = Game;
        iVar7 = *(int *)(gGroup0 + iVar13 * 0xdc + iVar10 + 0xd16c);
        iVar13 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        iVar10 = Game;
        pcVar3 = *(cRSubLoc **)(param_2 + 8);
        *(undefined4 *)(iVar7 + 0x24) =
             *(undefined4 *)
              (*(int *)(*(int *)(gGroup0 + iVar13 * 0xdc + iVar6 + 0xd16c) + 0x2c) + 0x88);
        iVar6 = cRSubLoc::Yi(pcVar3);
        tColourSmall::Alpha((tColourSmall *)
                            (*(int *)(gGroup0 + iVar6 * 0xdc + iVar10 + 0xd16c) + 0x28),
                            extraout_s0_02);
        iVar10 = Game;
        iVar6 = cRSubLoc::Yi(*(cRSubLoc **)(param_2 + 8));
        ptVar8 = *(tMatrix **)(param_2 + 4);
        *(undefined4 *)(*(int *)(*(int *)(gGroup0 + iVar6 * 0xdc + iVar10 + 0xd16c) + 0x24) + 8) = 1
        ;
        iVar10 = *(int *)(param_2 + 0xc);
        iVar6 = *(int *)(ptVar8 + 0x38);
        param_1 = extraout_s0_03;
        in_s1 = extraout_s1_01;
        in_s2 = extraout_s2_01;
      }
    }
    if (iVar6 == iVar10) break;
    fVar20 = *(float *)(iVar10 * 0xa8 + *(int *)(ptVar8 + 0x50) + 0x8c);
  }
  iVar10 = *(int *)(ptVar8 + 0x50);
  iVar6 = *(int *)(ptVar8 + 0x2c);
  fVar20 = (float)param_3 * *(float *)((*(int *)(ptVar8 + 0x38) + -1) * 0xa8 + iVar10 + 0x8c);
  *param_2 = (tVector)0x0;
  if (1.0 <= fVar24) {
    fVar24 = 0.999;
  }
  fVar14 = 1.0;
  if (fVar20 <= 1.0) {
    fVar14 = fVar20;
  }
  *(float *)(in_r3 + 8) = fVar14;
  if (iVar6 == 0x26) {
    iVar13 = *(int *)(param_2 + 8);
    fVar18 = *(float *)(iVar13 + 0x18);
    iVar10 = (*(int *)(ptVar8 + 0x38) + -1) * 0xa8 + iVar10;
    fVar23 = *(float *)(iVar10 + 0x38);
    fVar15 = *(float *)(iVar10 + 0x28);
    iVar6 = *(int *)(param_2 + 0x38);
    pfVar5 = (float *)(Game + 0x718f4);
    *(float *)(in_r3 + 4) = fVar14 * 0.7;
    fVar20 = *(float *)(ptVar8 + 0x44);
    fVar14 = *(float *)(iVar13 + 0x14);
    fVar19 = *(float *)(iVar10 + 0x34);
    fVar16 = *(float *)(iVar10 + 0x24);
    in_r2[2] = fVar18 + fVar23 + (fVar24 + fVar20) * fVar15;
    in_r2[1] = fVar14 + fVar19 + (fVar24 + fVar20) * fVar16;
    fVar24 = *pfVar5 * 0.013888889;
    *(float *)(iVar6 + 0x2c4) = fVar24;
    *(float *)(iVar6 + 0x2c8) = fVar24;
    cRSound::Play((int)&gRSound);
    cRVoiceManager::Play((int)&gVoiceManager,0xf,0);
    ptVar8 = *(tMatrix **)(param_2 + 4);
  }
  else {
    in_r2[2] = *(float *)(*(int *)(param_2 + 8) + 0x18) +
               *(float *)((*(int *)(ptVar8 + 0x38) + -1) * 0xa8 + *(int *)(ptVar8 + 0x50) + 0x38) +
               *(float *)(ptVar8 + 0x44) + fVar24;
  }
  *(float *)(*(int *)(param_2 + 0x38) + 0x360) =
       *(float *)(*(int *)(param_2 + 0x38) + 0x360) + *(float *)(ptVar8 + 0x80);
  return 3;
}
