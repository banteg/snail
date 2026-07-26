/*
 * mangled: _ZN16cRPathFollowGolb8TraverseEfR7tVectorPS0_
 * demangled: cRPathFollowGolb::Traverse(float, tVector&, tVector*)
 * address: 0004d120
 * size: 1500
 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* cRPathFollowGolb::Traverse(float, tVector&, tVector*) */

int cRPathFollowGolb::Traverse(float param_1,tVector *param_2,tVector *param_3)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  float *in_r2;
  undefined4 uVar4;
  float *in_r3;
  int iVar5;
  int iVar6;
  tMatrix *ptVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  uint in_fpscr;
  float in_s1;
  float in_s2;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float *pfVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
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
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_54;
  undefined4 local_50;

  ptVar7 = *(tMatrix **)(param_2 + 4);
  fVar16 = *(float *)(*(int *)(param_2 + 0xc) * 0xa8 + *(int *)(ptVar7 + 0x50) + 0x8c);
  fVar20 = fVar16 * (float)param_3;
  iVar5 = *(int *)(param_2 + 0xc);
  fVar17 = *(float *)(param_2 + 0x10);
  while( true ) {
    fVar12 = fVar20 + fVar17;
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar12 < fVar16) << 0x1f |
            (uint)(fVar12 == fVar16) << 0x1e;
    in_fpscr = uVar1 | (uint)(NAN(fVar12) || NAN(fVar16)) << 0x1c;
    bVar2 = (byte)(uVar1 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      iVar9 = *(int *)(ptVar7 + 0x38);
      *(float *)(param_2 + 0x10) = fVar12;
      if (iVar5 == iVar9 + -1) {
        iVar10 = iVar5 * 0xa8 + *(int *)(ptVar7 + 0x4c);
        pfVar18 = *(float **)(iVar10 + 0xa0);
        fVar16 = *(float *)(iVar10 + 0x90);
        fVar17 = *(float *)(iVar10 + 0x9c);
      }
      else {
        fVar17 = fVar12 / *(float *)(*(int *)(ptVar7 + 0x50) + iVar5 * 0xa8 + 0x8c);
        iVar10 = *(int *)(ptVar7 + 0x4c) + iVar5 * 0xa8;
        iVar6 = *(int *)(ptVar7 + 0x4c) + iVar5 * 0xa8 + 0xa8;
        fVar16 = *(float *)(iVar10 + 0x90) +
                 (*(float *)(iVar6 + 0x90) - *(float *)(iVar10 + 0x90)) * fVar17;
        pfVar18 = (float *)(*(float *)(iVar10 + 0xa0) +
                           fVar17 * (*(float *)(iVar6 + 0xa0) - *(float *)(iVar10 + 0xa0)));
        fVar17 = *(float *)(iVar10 + 0x9c) +
                 fVar17 * (*(float *)(iVar6 + 0x9c) - *(float *)(iVar10 + 0x9c));
      }
      if (*(int *)(ptVar7 + 0x2c) == 0x39) {
        cRPath::HalfPipePos(param_1,in_s1,in_s2,ptVar7,pfVar18);
        iVar10 = *(int *)(param_2 + 4);
        fVar20 = *(float *)(*(int *)(param_2 + 8) + 0x18);
        iVar9 = *(int *)(param_2 + 0xc) * 0xa8 + *(int *)(iVar10 + 0x50);
        fVar13 = *(float *)(iVar9 + 0x38);
        fVar12 = in_r3[1];
        *(undefined4 *)(param_2 + 0x18) = local_54;
        *(undefined4 *)(param_2 + 0x1c) = local_50;
        iVar5 = *(int *)(param_2 + 0x24);
        *(float *)(param_2 + 0x20) =
             fVar20 + fVar13 + *(float *)(iVar9 + 0x88) * *(float *)(param_2 + 0x10);
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar12;
        *(float *)(iVar5 + 0x1a4) = local_84 * fVar17;
        *(float *)(iVar5 + 0x1a8) = local_80 * fVar17;
        *(float *)(iVar5 + 0x1ac) = local_7c * fVar17;
        *(undefined4 *)(iVar5 + 0x1b4) = local_74;
        *(undefined4 *)(iVar5 + 0x1b8) = uStack_70;
        *(undefined4 *)(iVar5 + 0x1bc) = uStack_6c;
        *(undefined4 *)(iVar5 + 0x1c4) = local_64;
        *(undefined4 *)(iVar5 + 0x1c8) = uStack_60;
        *(undefined4 *)(iVar5 + 0x1cc) = uStack_5c;
      }
      else if (*(int *)(ptVar7 + 0x2c) == 0x3a) {
        cRPath::HalfPolePos(param_1,in_s1,in_s2,ptVar7,pfVar18);
        iVar10 = *(int *)(param_2 + 4);
        fVar20 = *(float *)(*(int *)(param_2 + 8) + 0x18);
        iVar9 = *(int *)(param_2 + 0xc) * 0xa8 + *(int *)(iVar10 + 0x50);
        fVar13 = *(float *)(iVar9 + 0x38);
        fVar12 = in_r3[1];
        *(undefined4 *)(param_2 + 0x18) = local_54;
        *(undefined4 *)(param_2 + 0x1c) = local_50;
        iVar5 = *(int *)(param_2 + 0x24);
        *(float *)(param_2 + 0x20) =
             fVar20 + fVar13 + *(float *)(iVar9 + 0x88) * *(float *)(param_2 + 0x10);
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar12;
        *(float *)(iVar5 + 0x1a4) = local_84 * fVar17;
        *(float *)(iVar5 + 0x1a8) = local_80 * fVar17;
        *(float *)(iVar5 + 0x1ac) = local_7c * fVar17;
        *(undefined4 *)(iVar5 + 0x1b4) = local_74;
        *(undefined4 *)(iVar5 + 0x1b8) = uStack_70;
        *(undefined4 *)(iVar5 + 0x1bc) = uStack_6c;
        *(undefined4 *)(iVar5 + 0x1c4) = local_64;
        *(undefined4 *)(iVar5 + 0x1c8) = uStack_60;
        *(undefined4 *)(iVar5 + 0x1cc) = uStack_5c;
      }
      else {
        iVar10 = *(int *)(param_2 + 8);
        fVar24 = *(float *)(iVar10 + 0x18);
        fVar23 = *(float *)(iVar10 + 0x10);
        fVar25 = *(float *)(iVar10 + 0x14);
        puVar8 = (undefined4 *)(iVar5 * 0xa8 + *(int *)(ptVar7 + 0x50));
        fVar19 = (float)puVar8[0x20];
        fVar15 = (float)puVar8[0x21];
        fVar20 = (float)puVar8[0xc];
        fVar13 = (float)puVar8[0xd];
        fVar14 = (float)puVar8[0xe];
        fVar21 = (float)puVar8[0x22];
        if (iVar5 == iVar9 + -1) {
          tMatrix::Identity((tMatrix *)&local_84);
        }
        else {
          local_c4 = *puVar8;
          uStack_c0 = puVar8[1];
          uStack_bc = puVar8[2];
          uStack_b8 = puVar8[3];
          puVar11 = (undefined4 *)(*(int *)(ptVar7 + 0x50) + iVar5 * 0xa8 + 0xa8);
          local_b4 = puVar8[4];
          uStack_b0 = puVar8[5];
          uStack_ac = puVar8[6];
          uStack_a8 = puVar8[7];
          local_a4 = puVar8[8];
          uStack_a0 = puVar8[9];
          uStack_9c = puVar8[10];
          uStack_98 = puVar8[0xb];
          uStack_88 = puVar8[0xf];
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
        iVar5 = *(int *)(param_2 + 0x24);
        iVar10 = *(int *)(param_2 + 4);
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + in_r3[1];
        fVar22 = *in_r2 - fVar16;
        *(float *)(param_2 + 0x18) =
             fVar23 + fVar20 + fVar12 * fVar19 * fVar17 + fVar22 * fVar17 * local_84;
        *(float *)(param_2 + 0x20) = fVar24 + fVar14 + fVar12 * fVar21 + fVar22 * fVar17 * local_7c;
        *(float *)(param_2 + 0x1c) =
             fVar25 + fVar13 + fVar12 * fVar15 * fVar17 + fVar22 * fVar17 * local_80;
        *(float *)(iVar5 + 0x1a4) = fVar17 * local_84;
        *(float *)(iVar5 + 0x1a8) = fVar17 * local_80;
        *(float *)(iVar5 + 0x1ac) = fVar17 * local_7c;
        *(undefined4 *)(iVar5 + 0x1b4) = local_74;
        *(undefined4 *)(iVar5 + 0x1b8) = uStack_70;
        *(undefined4 *)(iVar5 + 0x1bc) = uStack_6c;
        *(undefined4 *)(iVar5 + 0x1c4) = local_64;
        *(undefined4 *)(iVar5 + 0x1c8) = uStack_60;
        *(undefined4 *)(iVar5 + 0x1cc) = uStack_5c;
      }
      fVar17 = (float)VectorSignedToFloat(*(undefined4 *)(iVar10 + 0x48),
                                          (byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(iVar5 + 0x22c) = *(undefined4 *)(iVar5 + 0x238);
      *(undefined4 *)(iVar5 + 0x230) = *(undefined4 *)(iVar5 + 0x23c);
      *(undefined4 *)(iVar5 + 0x234) = *(undefined4 *)(iVar5 + 0x240);
      fVar16 = *in_r2 - fVar16;
      if (fVar16 < 0.0) {
        fVar16 = -fVar16;
      }
      if (fVar16 <= fVar17 * 0.5 + 0.3) {
        if (1 < *(int *)(iVar10 + 0x2c) - 0x39U) {
          *in_r2 = *in_r2 + *in_r3;
        }
        iVar9 = 0;
      }
      else {
        *param_2 = (tVector)0x0;
        uVar3 = *(undefined4 *)(param_2 + 0x1c);
        uVar4 = *(undefined4 *)(param_2 + 0x20);
        iVar9 = 1 - *(uint *)(iVar10 + 0x34);
        if (1 < *(uint *)(iVar10 + 0x34)) {
          iVar9 = 0;
        }
        *(undefined4 *)(iVar5 + 0x1d4) = *(undefined4 *)(param_2 + 0x18);
        *(undefined4 *)(iVar5 + 0x1d8) = uVar3;
        *(undefined4 *)(iVar5 + 0x1dc) = uVar4;
      }
      return iVar9;
    }
    iVar9 = iVar5 + 1;
    *(int *)(param_2 + 0xc) = iVar9;
    *(undefined4 *)(param_2 + 0x10) = 0;
    fVar20 = fVar20 - (fVar16 - fVar17);
    if (iVar9 == *(int *)(ptVar7 + 0x38)) break;
    fVar16 = *(float *)(iVar9 * 0xa8 + *(int *)(ptVar7 + 0x50) + 0x8c);
    iVar5 = iVar9;
    fVar17 = 0.0;
  }
  iVar9 = *(int *)(ptVar7 + 0x2c);
  iVar10 = *(int *)(param_2 + 0x24);
  iVar5 = iVar5 * 0xa8 + *(int *)(ptVar7 + 0x50);
  fVar17 = *(float *)(iVar5 + 0x8c);
  *param_2 = (tVector)0x0;
  in_r3[2] = fVar17 * (float)param_3;
  uVar3 = *(undefined4 *)(param_2 + 0x1c);
  uVar4 = *(undefined4 *)(param_2 + 0x20);
  *(float *)(iVar10 + 0x1d4) = *(float *)(param_2 + 0x18);
  *(undefined4 *)(iVar10 + 0x1d8) = uVar3;
  *(undefined4 *)(iVar10 + 0x1dc) = uVar4;
  if (iVar9 != 0x26) {
    fVar20 = *(float *)(*(int *)(param_2 + 8) + 0x18) + *(float *)(iVar5 + 0x38) +
             *(float *)(ptVar7 + 0x44) + fVar20;
    in_r2[2] = fVar20;
    *(float *)(iVar10 + 0x1dc) = fVar20;
    return 3;
  }
  iVar9 = *(int *)(param_2 + 8);
  fVar19 = *(float *)(iVar5 + 0x38);
  fVar14 = *(float *)(iVar9 + 0x18);
  fVar13 = *(float *)(iVar5 + 0x28);
  in_r3[1] = in_r3[2] * 0.7;
  fVar17 = *(float *)(ptVar7 + 0x44);
  fVar16 = *(float *)(iVar9 + 0x14);
  fVar15 = *(float *)(iVar5 + 0x34);
  fVar12 = *(float *)(iVar5 + 0x24);
  in_r2[2] = fVar14 + fVar19 + (fVar20 + fVar17) * fVar13;
  in_r2[1] = fVar16 + fVar15 + (fVar20 + fVar17) * fVar12;
  fVar17 = in_r2[1];
  fVar16 = in_r2[2];
  *(float *)(iVar10 + 0x1d4) = *in_r2;
  *(float *)(iVar10 + 0x1d8) = fVar17;
  *(float *)(iVar10 + 0x1dc) = fVar16;
  return 3;
}
