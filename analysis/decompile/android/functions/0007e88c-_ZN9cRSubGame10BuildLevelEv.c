/*
 * mangled: _ZN9cRSubGame10BuildLevelEv
 * demangled: cRSubGame::BuildLevel()
 * address: 0007e88c
 * size: 6356
 */

/* cRSubGame::BuildLevel() */

void cRSubGame::BuildLevel(void)

{
  ushort uVar1;
  bool bVar2;
  bool bVar3;
  cRSubGame *in_r0;
  cRSubGame *pcVar4;
  cRSubGame *pcVar5;
  int iVar6;
  cRSubGame *pcVar7;
  cRSubGame *extraout_r1;
  cRSubGame *extraout_r1_00;
  cRSubGame *extraout_r1_01;
  cRSubGame *extraout_r1_02;
  cRSubGame *extraout_r1_03;
  cRSubGame *extraout_r1_04;
  cRSubGame *extraout_r1_05;
  cRSubGame *extraout_r1_06;
  cRSubGame *extraout_r1_07;
  cRSubGame *extraout_r1_08;
  cRObject *pcVar8;
  cRSubGame *extraout_r1_09;
  cRSubGame *extraout_r1_10;
  cRSubGame *extraout_r1_11;
  cRSubGame *extraout_r1_12;
  cRSubGame *extraout_r1_13;
  cRSubGame *extraout_r1_14;
  cRSubGame *extraout_r1_15;
  cRSubGame *extraout_r1_16;
  cRSubGame *extraout_r1_17;
  cRSubGame *extraout_r1_18;
  cRSubGame *extraout_r1_19;
  cRSubGame *extraout_r1_20;
  cRSubGame *extraout_r1_21;
  cRSubGame *extraout_r1_22;
  cRSubGame *extraout_r1_23;
  cRSubGame *extraout_r1_24;
  cRSubGame *extraout_r1_25;
  cRSubGame *extraout_r1_26;
  cRSubGame *extraout_r1_27;
  cRSubGame *pcVar9;
  int iVar10;
  cRSubGame *pcVar11;
  uint uVar12;
  cRSubGame cVar13;
  undefined1 uVar14;
  cRSubGame *pcVar15;
  int iVar16;
  cRSubGame *pcVar17;
  cRSubGame *pcVar18;
  int iVar19;
  cRSubGame *pcVar20;
  cRBod *this;
  int iVar21;
  int iVar22;
  cRSubGame *pcVar23;
  bool bVar24;
  bool bVar25;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float extraout_s0_06;
  float extraout_s0_07;
  float extraout_s0_08;
  float extraout_s0_09;
  float extraout_s0_10;
  float extraout_s0_11;
  float extraout_s0_12;
  float extraout_s0_13;
  float extraout_s0_14;
  float extraout_s0_15;
  float extraout_s0_16;
  float extraout_s0_17;
  float extraout_s0_18;
  float extraout_s0_19;
  float extraout_s0_20;
  float extraout_s0_21;
  float extraout_s0_22;
  float extraout_s0_23;
  float extraout_s0_24;
  float extraout_s0_25;
  float extraout_s0_26;
  float extraout_s0_27;
  float extraout_s0_28;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  undefined4 uVar30;
  char *pcVar31;
  float fVar32;
  cRSubGame *local_98;
  cRSubGame *local_94;
  int local_88;
  cRSubGame *local_74;
  cRSubGame *local_6c;
  int local_68;
  int local_64;
  cRSubGame *local_60;
  int local_38;

  pcVar4 = (cRSubGame *)(DAT_0007ea80 + 0x7e8b4);
  if (in_r0[0x30fcc0] == (cRSubGame)0x0) {
    iVar22 = *(int *)(in_r0 + 0x60);
    iVar16 = 0;
    if (iVar22 != 4 && iVar22 != 7) {
      fVar28 = (float)RAND(in_s0,(char *)0x47000000);
      iVar22 = *(int *)(in_r0 + 0x60);
      iVar16 = (int)fVar28;
      in_s0 = extraout_s0_28;
    }
  }
  else {
    iVar22 = *(int *)(in_r0 + 0x60);
    iVar16 = *(int *)(*(int *)(in_r0 + 0x30fcc4) + 0x68);
  }
  if (iVar22 != 1) {
    if (iVar22 == 4) {
      cRSubSolution::ReSet
                (*(cRSubSolution **)(in_r0 + 0x30fcbc),iVar16,*(int *)(in_r0 + 100),in_s0,
                 *(int *)(in_r0 + 0x4c),*(int *)(in_r0 + 0x6c),2);
      goto LAB_0007e910;
    }
    if (iVar22 != 0) goto LAB_0007e910;
  }
  cRSubSolution::ReSet
            (*(cRSubSolution **)(in_r0 + 0x30fcbc),iVar16,*(int *)(in_r0 + 100),in_s0,
             *(int *)(in_r0 + 0x4c),*(int *)(in_r0 + 0x6c),iVar22);
LAB_0007e910:
  *(undefined4 *)(in_r0 + 0x30fccc) = 0;
  if (*(int *)(in_r0 + 0x332d9c) == 3) {
    *(undefined4 *)(in_r0 + 0xfd90) = 0;
    *(undefined4 *)(in_r0 + 0x332d9c) = 1;
    cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(in_r0 + 0xfac4));
    if (*(int *)(in_r0 + 0x3210c0) == 0) {
      *(undefined4 *)(in_r0 + 0x13ab8) = 3;
    }
    else if (*(int *)(in_r0 + 0x3210c0) == 1) {
      *(undefined4 *)(in_r0 + 0x13ab8) = 8;
    }
  }
  iVar22 = DAT_0007ea84;
  cRTime::Zero((cRTime *)(in_r0 + 0xfd94));
  *(undefined4 *)(in_r0 + 0xfdac) = DAT_0007ea98;
  *(undefined4 *)(in_r0 + 0xfdb4) = 0;
  RandSeed(iVar16);
  cRTrack::Change(**(int **)(pcVar4 + iVar22) + 0x848);
  iVar16 = *(int *)(in_r0 + 0x60);
  if (((iVar16 == 0 || iVar16 == 7) || (iVar16 == 4)) || (iVar16 == 1)) {
    *(undefined4 *)(in_r0 + 0x70) = *(undefined4 *)(in_r0 + 0x14f8);
    *(undefined4 *)(in_r0 + 0x74) = *(undefined4 *)(in_r0 + 0x1590);
    if (iVar16 == 1) {
      fVar28 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0x1590),
                                          (byte)(in_fpscr >> 0x16) & 3);
      *(int *)(in_r0 + 0x74) =
           (int)(fVar28 * (DAT_0007ea7c + DAT_0007ea78 * *(float *)(in_r0 + 0x50)));
    }
    if (in_r0[0x1594] == (cRSubGame)0x0) {
      iVar16 = *(int *)(in_r0 + 0x152c) + *(int *)(in_r0 + 0x14f8);
      *(int *)(in_r0 + 0x74) = iVar16;
      if (0 < *(int *)(in_r0 + 0xa0)) {
        iVar6 = 0;
        pcVar9 = in_r0;
        do {
          iVar6 = iVar6 + 1;
          pcVar17 = pcVar9 + 0xa8;
          pcVar9 = pcVar9 + 0x34;
          iVar16 = iVar16 + *(int *)pcVar17;
        } while (iVar6 < *(int *)(in_r0 + 0xa0));
        *(int *)(in_r0 + 0x74) = iVar16;
      }
    }
    *(int *)(in_r0 + 0x78) = *(int *)(in_r0 + 0x74) - *(int *)(in_r0 + 0x152c);
    if (0xdab < *(int *)(in_r0 + 0x74)) {
      RShellError((char *)(pcVar4 + DAT_0007ea88),in_r0 + 0x15a8,0xdac);
    }
  }
  else if (iVar16 == 3) {
    *(int *)(in_r0 + 0x70) = *(int *)(in_r0 + 0x14f8);
    iVar16 = *(int *)(in_r0 + 0x152c) + *(int *)(in_r0 + 0x14f8) + *(int *)(in_r0 + 0xa8) * 0x10;
    *(int *)(in_r0 + 0x74) = iVar16;
    *(int *)(in_r0 + 0x78) = iVar16 - *(int *)(in_r0 + 0x152c);
  }
  iVar6 = 0;
  pcVar9 = in_r0 + 0x20dedc;
  iVar16 = 0;
  in_r0[2] = (cRSubGame)0x0;
  in_r0[0xfe74] = (cRSubGame)0x0;
  uVar30 = DAT_0007ea98;
  *(undefined4 *)(in_r0 + 4) = 0;
  do {
    *(undefined4 *)pcVar9 = 0;
    *(undefined4 *)(pcVar9 + 0xa0) = uVar30;
    iVar21 = iVar6 * 0x240;
    *(undefined4 *)(pcVar9 + 0x94) = 0;
    *(undefined4 *)(pcVar9 + 0xd0) = uVar30;
    *(undefined4 *)(pcVar9 + 0x98) = 0;
    pcVar17 = in_r0 + iVar21 + 0x13af8;
    *(undefined4 *)(pcVar9 + 0x8c) = uVar30;
    *(undefined4 *)(pcVar9 + 0x88) = uVar30;
    *(undefined4 *)(pcVar9 + 0x84) = uVar30;
    *(undefined4 *)(pcVar9 + 0x90) = 0;
    *(undefined4 *)(pcVar9 + 0xd4) = 0;
    *(undefined4 *)(pcVar9 + 0xd8) = 0;
    iVar10 = 0;
    do {
      iVar19 = iVar10 + 1;
      iVar10 = iVar21 + iVar10 * 0x48;
      in_r0[iVar10 + 0x13b11] = (cRSubGame)((byte)in_r0[iVar10 + 0x13b11] & 0x5f);
      pcVar17[0x15] = (cRSubGame)0x0;
      in_r0[iVar10 + 0x13b10] = (cRSubGame)((byte)in_r0[iVar10 + 0x13b10] & 0xa7);
      in_r0[iVar10 + 0x13b11] = (cRSubGame)((byte)in_r0[iVar10 + 0x13b11] & 0xaf);
      *(undefined2 *)(pcVar17 + 0x18) = 0;
      *(uint *)(pcVar17 + -0x18) = *(uint *)(pcVar17 + -0x18) & 0xffffff7f;
      fVar28 = (float)tColourSmall::White((tColourSmall *)(in_r0 + iVar10 + 0x13b04));
      *(undefined4 *)pcVar17 = uVar30;
      *(undefined4 *)(pcVar17 + 4) = uVar30;
      pcVar17 = pcVar17 + 0x48;
      iVar10 = iVar19;
    } while (iVar19 != 8);
    iVar10 = 0;
    pcVar17 = in_r0 + iVar21 + 0x13adc;
    do {
      iVar10 = iVar10 + 1;
      *(undefined4 *)(pcVar17 + 0x38) = 0;
      *(undefined4 *)(pcVar17 + 0x3c) = 0;
      *(undefined4 *)(pcVar17 + 0x40) = 0;
      *(undefined4 *)(pcVar17 + 0x44) = 0;
      pcVar17 = pcVar17 + 0x48;
    } while (iVar10 != 8);
    iVar6 = iVar6 + 1;
    pcVar9 = pcVar9 + 0xdc;
  } while (iVar6 != 0xe10);
  if ((in_r0[0x1594] != (cRSubGame)0x0) &&
     (iVar6 = *(int *)(in_r0 + 0xa0), pcVar9 = in_r0, 0 < iVar6)) {
    do {
      iVar16 = iVar16 + 1;
      pcVar9[0xac] = (cRSubGame)0x0;
      pcVar9 = pcVar9 + 0x34;
    } while (iVar16 < iVar6);
  }
  iVar16 = DAT_0007ea94;
  iVar21 = 0;
  bVar2 = false;
  local_60 = (cRSubGame *)0x0;
  pcVar17 = pcVar4 + DAT_0007ea90;
  bVar3 = false;
  local_64 = 0;
  local_38 = 0;
  pcVar9 = in_r0 + 0x1528;
  iVar6 = *(int *)(in_r0 + 0x74);
  pcVar23 = in_r0 + 0x1680;
  while( true ) {
    if (iVar6 <= iVar21) {
      wprintf((char *)(pcVar4 + DAT_0007fe18),iVar21);
      return;
    }
    bVar2 = (bool)(bVar2 ^ 1);
    if (iVar21 == 0) {
      bVar3 = true;
      *(undefined4 *)(in_r0 + 0x14f4) = 0;
      local_68 = *(int *)(in_r0 + 0x14f8);
      local_94 = in_r0 + 0x14f4;
    }
    else if ((*(int *)(in_r0 + 0x78) == iVar21) && (in_r0[0x1594] == (cRSubGame)0x0)) {
      bVar3 = true;
      *(int *)(in_r0 + 0x1528) = iVar21;
      local_68 = *(int *)(in_r0 + 0x152c);
      local_94 = pcVar9;
    }
    else {
      *(undefined4 *)(in_r0 + 0x68) = DAT_0007fe2c;
      if (in_r0[0x1594] == (cRSubGame)0x0) {
        iVar6 = local_38 * 0x34;
        local_38 = local_38 + 1;
        local_94 = in_r0 + iVar6 + 0xa4;
      }
      else if (bVar2) {
        bVar3 = true;
        *(int *)(in_r0 + 0x155c) = iVar21;
        local_94 = in_r0 + 0x155c;
      }
      else {
        if (*(int *)(in_r0 + 0x60) == 1) {
          fVar32 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0xa0),
                                              (byte)(in_fpscr >> 0x16) & 3);
          fVar28 = (float)RAND(fVar28,(char *)(fVar32 * (DAT_0007fe34 +
                                                        DAT_0007fe30 * *(float *)(in_r0 + 0x50))));
        }
        else {
          pcVar31 = (char *)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0xa0),
                                                (byte)(in_fpscr >> 0x16) & 3);
          fVar28 = (float)RAND(fVar28,pcVar31);
        }
        fVar28 = (float)VectorSignedToFloat((int)fVar28,(byte)(in_fpscr >> 0x16) & 3);
        local_94 = in_r0 + (int)(fVar28 * *(float *)(in_r0 + 0x68)) * 0x34 + 0xa4;
        in_r0[(int)(fVar28 * *(float *)(in_r0 + 0x68)) * 0x34 + 0xac] = (cRSubGame)0x1;
      }
      local_68 = *(int *)(local_94 + 4);
    }
    fVar28 = (float)SwitchMirror();
    *(int *)local_94 = iVar21;
    if (*(int *)(local_94 + 4) < 0) {
      fVar28 = (float)RShellError((char *)(pcVar4 + DAT_0007fe1c));
    }
    iVar6 = *(int *)(in_r0 + 0x74);
    if (iVar21 < iVar6 && 0 < local_68) break;
LAB_0007fbc8:
    if (*(int *)(in_r0 + 0x60) == 3) {
      if (!bVar3) {
        local_64 = local_64 + 1;
      }
    }
    else {
      local_64 = local_64 + 1;
    }
  }
  pcVar5 = (cRSubGame *)(local_68 + iVar21);
  local_88 = 0;
  pcVar20 = in_r0 + iVar21 * 0xdc + 0x20dfb4;
  local_74 = pcVar5;
LAB_0007ed78:
  pcVar11 = *(cRSubGame **)(in_r0 + 0x60);
  if (pcVar11 == (cRSubGame *)0x2) {
    iVar10 = local_88 * 10;
    pcVar7 = local_94;
  }
  else {
    iVar19 = *(int *)(in_r0 + 0x78);
    if (iVar21 < iVar19) {
      iVar10 = local_88 * 10;
    }
    else {
      local_94 = pcVar9;
      if ((((pcVar11 != (cRSubGame *)0x0 && pcVar11 != (cRSubGame *)0x4) &&
           (pcVar11 != (cRSubGame *)0x1)) && (pcVar11 != (cRSubGame *)0x7)) &&
         (pcVar11 != (cRSubGame *)0x3)) {
        local_94 = pcVar23;
      }
      if (iVar21 == iVar19) {
        iVar10 = 0;
        local_88 = 0;
      }
      else {
        iVar10 = local_88 * 10;
      }
    }
    pcVar5 = local_74 + -local_88;
    pcVar7 = local_94;
    if (((((iVar19 < (int)pcVar5) && (pcVar7 = pcVar23, pcVar23 != local_94)) &&
         ((pcVar7 = local_94, in_r0 + 0x16e8 != local_94 && (in_r0 + 0x171c != local_94)))) &&
        (((pcVar11 == (cRSubGame *)0x0 || pcVar11 == (cRSubGame *)0x4 ||
          (pcVar11 == (cRSubGame *)0x1)) ||
         ((pcVar11 == (cRSubGame *)0x7 || (pcVar11 == (cRSubGame *)0x3)))))) &&
       (pcVar11 = pcVar9, pcVar7 = pcVar9, pcVar9 != local_94)) {
      *(cRSubGame **)(in_r0 + 0x78) = pcVar5;
      *(cRSubGame **)(in_r0 + 0x74) = pcVar5 + (iVar6 - iVar19);
      pcVar7 = local_94;
    }
  }
  local_94 = pcVar7;
  cVar13 = in_r0[2];
  bVar24 = cVar13 != (cRSubGame)0x0;
  if (bVar24) {
    pcVar11 = *(cRSubGame **)(pcVar20 + -0xd8);
  }
  iVar6 = *(int *)(local_94 + 0x18);
  if (bVar24) {
    pcVar11 = (cRSubGame *)((uint)pcVar11 | 0x20);
  }
  *(cRSubGame **)(pcVar20 + -4) = local_94;
  if (bVar24) {
    *(cRSubGame **)(pcVar20 + -0xd8) = pcVar11;
  }
  uVar1 = *(ushort *)(iVar6 + iVar10);
  *(int *)pcVar20 = local_64;
  if ((uVar1 & 0x100) != 0) {
    pcVar5 = (cRSubGame *)(*(uint *)(pcVar20 + -0xd8) | 0x100);
    *(cRSubGame **)(pcVar20 + -0xd8) = pcVar5;
  }
  if ((uVar1 & 0x8000) != 0) {
    *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 0x8000;
  }
  uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
  if ((*(ushort *)(iVar6 + iVar10) & 2) == 0) {
    fVar32 = (float)VectorSignedToFloat(iVar21,(byte)(in_fpscr >> 0x16) & 3);
  }
  else {
    fVar32 = (float)VectorSignedToFloat(iVar21,(byte)(in_fpscr >> 0x16) & 3);
    iVar19 = **(int **)(pcVar4 + iVar22);
    *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 2;
    cRBod::SetObject((cRBod *)(in_r0 + iVar21 * 0xdc + 0x20dee0),
                     *(cRObject **)((uint)*(byte *)(iVar6 + iVar10 + 3) * 0xb0 + iVar19 + 0x47afc));
    *(undefined4 *)(*(int *)(pcVar20 + -0xb0) + 8) = 1;
    tMatrix::Identity((tMatrix *)(in_r0 + iVar21 * 0xdc + 0x20df0c));
    iVar6 = *(int *)(local_94 + 0x18);
    iVar19 = iVar6 + iVar10;
    uVar1 = *(ushort *)(iVar6 + iVar10);
    uVar12 = (uint)uVar1;
    uVar30 = VectorUnsignedToFloat((uint)*(byte *)(iVar19 + 6),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(pcVar20 + -0x78) = uVar30;
    uVar30 = VectorUnsignedToFloat((uint)*(byte *)(iVar19 + 7),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(pcVar20 + -0x74) = uVar30;
    fVar28 = (float)VectorUnsignedToFloat((uint)*(byte *)(iVar19 + 8),(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(pcVar20 + -0x70) = fVar28 + fVar32;
    uVar30 = DAT_0007fe24;
    pcVar5 = local_94;
    if ((uVar1 & 8) == 0) {
      cVar13 = in_r0[2];
      *(undefined4 *)(pcVar20 + -0x60) = DAT_0007fe24;
      *(undefined4 *)(pcVar20 + -0x58) = uVar30;
      *(undefined4 *)(pcVar20 + -0x5c) = uVar30;
    }
    else {
      *(undefined4 *)(pcVar20 + -0x60) = DAT_0007fe24;
      *(undefined4 *)(pcVar20 + -0x58) = uVar30;
      *(undefined4 *)(pcVar20 + -0x5c) = uVar30;
      *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 8;
      cVar13 = in_r0[2];
    }
  }
  uVar30 = DAT_0007f278;
  if ((uVar12 & 1) != 0) {
    uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
    *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 0x4001;
    pcVar5 = (cRSubGame *)(uint)*(byte *)(iVar6 + iVar10 + 2);
    *(undefined4 *)(pcVar20 + -0x50) = uVar30;
    *(undefined4 *)(pcVar20 + -0x54) = uVar30;
    *(cRSubGame **)(pcVar20 + -0x48) = pcVar5;
    uVar30 = VectorUnsignedToFloat((uint)*(byte *)(iVar6 + iVar10 + 5),(byte)(in_fpscr >> 0x16) & 3)
    ;
    *(undefined4 *)(pcVar20 + -0x4c) = uVar30;
  }
  if ((uVar12 & 8) != 0) {
    uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
    *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 8;
    pcVar5 = (cRSubGame *)(uint)*(byte *)(iVar6 + iVar10 + 4);
    *(cRSubGame **)(pcVar20 + -0x44) = pcVar5;
  }
  if ((uVar12 & 4) != 0) {
    uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
    pcVar5 = (cRSubGame *)(*(uint *)(pcVar20 + -0xd8) | 4);
    *(cRSubGame **)(pcVar20 + -0xd8) = pcVar5;
  }
  bVar24 = (uVar12 & 0x200) != 0;
  if (bVar24) {
    pcVar5 = *(cRSubGame **)(pcVar20 + -0xd8);
  }
  *(undefined4 *)(pcVar20 + -8) = DAT_0007f278;
  if (bVar24) {
    uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
  }
  pcVar11 = (cRSubGame *)0x0;
  if (bVar24) {
    pcVar5 = (cRSubGame *)((uint)pcVar5 | 0x200);
  }
  local_6c = (cRSubGame *)0x0;
  if (bVar24) {
    *(cRSubGame **)(pcVar20 + -0xd8) = pcVar5;
  }
  if ((uVar12 & 0x400) != 0) {
    uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
    *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 0x400;
  }
  if ((uVar12 & 0x2000) != 0) {
    uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
    *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 0x2000;
  }
  if ((uVar12 & 0x800) != 0) {
    uVar12 = (uint)*(ushort *)(iVar6 + iVar10);
    *(uint *)(pcVar20 + -0xd8) = *(uint *)(pcVar20 + -0xd8) | 0x800;
  }
  bVar24 = (uVar12 & 0x1000) != 0;
  if (bVar24) {
    uVar12 = *(uint *)(pcVar20 + -0xd8);
  }
  pcVar7 = (cRSubGame *)((uint)(iVar21 >> 0x1f) >> 0x1d);
  if (bVar24) {
    *(uint *)(pcVar20 + -0xd8) = uVar12 | 0x1000;
  }
  iVar6 = iVar21 * 0x240;
  pcVar18 = in_r0 + iVar6 + 0x13b14;
  do {
    pcVar5 = pcVar11;
    if (cVar13 != (cRSubGame)0x0) {
      pcVar7 = (cRSubGame *)(7 - (int)pcVar11);
      pcVar5 = local_98;
    }
    local_98 = pcVar5;
    iVar10 = iVar6 + (int)pcVar11 * 0x48;
    if (cVar13 != (cRSubGame)0x0) {
      local_98 = pcVar7;
    }
    in_r0[iVar10 + 0x13b10] = (cRSubGame)((byte)in_r0[iVar10 + 0x13b10] & 0xe0 | (byte)pcVar11 & 7);
    iVar19 = *(int *)(in_r0 + 0x70);
    *(undefined4 *)pcVar18 = 0;
    *(undefined4 *)(pcVar18 + 4) = 0;
    *(undefined4 *)(pcVar18 + 8) = 0;
    iVar10 = iVar19;
    if (iVar21 < iVar19) {
      iVar10 = 1;
    }
    uVar14 = (undefined1)iVar10;
    *(undefined4 *)(pcVar18 + 0xc) = 0;
    if (iVar19 <= iVar21) {
      if (iVar21 < *(int *)(in_r0 + 0x78)) {
        uVar14 = false;
      }
      else {
        uVar14 = true;
      }
    }
    this = (cRBod *)(in_r0 + iVar6 + (int)pcVar11 * 0x48 + 0x13adc);
    cRBod::SetObject(this,(cRObject *)0x0);
    pcVar5 = (cRSubGame *)
             LevelConvert(in_r0,(char)local_98[*(int *)(local_94 + 0x14) + local_88 * 8],iVar21,
                          (bool)uVar14);
    pcVar7 = extraout_r1;
    fVar28 = extraout_s0;
    switch(pcVar5) {
    case (cRSubGame *)0x20:
      goto LAB_0007f294;
    case (cRSubGame *)0x21:
      break;
    case (cRSubGame *)0x22:
      break;
    case (cRSubGame *)0x23:
      pcVar18[-8] = (cRSubGame)0x20;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) & 0xffffffdf;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x24:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0x17;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_17;
      fVar28 = extraout_s0_16;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x25:
      break;
    case (cRSubGame *)0x26:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44370));
      pcVar18[-8] = (cRSubGame)0x22;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_16;
      fVar28 = extraout_s0_15;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x27:
      break;
    case (cRSubGame *)0x28:
      uVar12 = *(uint *)(pcVar18 + -0x34);
      pcVar5 = local_60 + 1;
      if (pcVar5 == (cRSubGame *)0xf) {
        pcVar7 = (cRSubGame *)0x0;
      }
      *(uint *)(pcVar18 + -0x34) = uVar12 & 0xffffffdf;
      local_60 = pcVar7;
      if (pcVar5 != (cRSubGame *)0xf) {
        local_60 = pcVar5;
        if (pcVar5 == (cRSubGame *)0x8) {
          cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44134));
          *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
          pcVar5 = (cRSubGame *)
                   tColourSmall::Set((tColourSmall *)
                                     (in_r0 + (int)pcVar11 * 0x48 + iVar21 * 0x240 + 0x13b04),
                                     extraout_s0_26,extraout_s1,extraout_s2,extraout_s3);
          pcVar7 = extraout_r1_27;
          fVar28 = extraout_s0_27;
        }
        else {
          *(uint *)(pcVar18 + -0x34) = uVar12 & 0xffffffdf;
        }
      }
      pcVar18[-8] = (cRSubGame)0x16;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x29:
      break;
    case (cRSubGame *)0x2a:
      break;
    case (cRSubGame *)0x2b:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0x18;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_15;
      fVar28 = extraout_s0_14;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2c:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x43e48));
      pcVar18[-8] = (cRSubGame)0x1c;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_14;
      fVar28 = extraout_s0_13;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2d:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44370));
      pcVar18[-8] = (cRSubGame)0x15;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_13;
      fVar28 = extraout_s0_12;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2e:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44370));
      pcVar18[-8] = (cRSubGame)0x1;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_12;
      fVar28 = extraout_s0_11;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2f:
      break;
    case (cRSubGame *)0x30:
      if (*(int *)(in_r0 + 0x60) != 1) goto LAB_0007f288;
      fVar27 = (float)VectorSignedToFloat(pcVar11,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(pcVar20 + -0x50) = *(undefined4 *)(pcVar18 + -0x24);
      fVar29 = DAT_0007fe08;
      fVar26 = DAT_0007fe04;
      cVar13 = in_r0[2];
      *(undefined4 *)(pcVar20 + -0x48) = 0;
      uVar12 = *(uint *)(pcVar20 + -0xd8) & 0xffffbfff | 1;
      *(uint *)(pcVar20 + -0xd8) = uVar12;
      fVar26 = (fVar27 - fVar26) + fVar29;
      *(float *)(pcVar20 + -0x4c) = fVar32 + fVar29;
      *(float *)(pcVar20 + -0x54) = fVar26;
      if (cVar13 != (cRSubGame)0x0) {
        *(float *)(pcVar20 + -0x54) = -fVar26;
      }
      goto LAB_0007f28c;
    case (cRSubGame *)0x31:
      goto LAB_0007f288;
    case (cRSubGame *)0x32:
      goto LAB_0007f288;
    case (cRSubGame *)0x33:
      goto LAB_0007f288;
    case (cRSubGame *)0x34:
      goto LAB_0007f288;
    case (cRSubGame *)0x35:
      goto LAB_0007f288;
    case (cRSubGame *)0x36:
      goto LAB_0007f288;
    case (cRSubGame *)0x37:
      goto LAB_0007f288;
    case (cRSubGame *)0x38:
      goto LAB_0007f288;
    case (cRSubGame *)0x39:
LAB_0007f288:
      uVar12 = *(uint *)(pcVar20 + -0xd8);
LAB_0007f28c:
      if ((uVar12 & 0xc0) == 0) {
        pcVar5 = (cRSubGame *)
                 cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
        pcVar18[-8] = (cRSubGame)0xf;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        pcVar7 = extraout_r1_22;
        fVar28 = extraout_s0_21;
      }
      else {
LAB_0007f294:
        pcVar18[-8] = (cRSubGame)0x0;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) & 0xffffffdf;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x3a:
      break;
    case (cRSubGame *)0x3b:
      break;
    case (cRSubGame *)0x3c:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x447bc));
      uVar30 = DAT_0007f278;
      *(undefined4 *)(pcVar18 + -0x18) = DAT_0007f278;
      *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar18[-8] = (cRSubGame)0x6;
      pcVar7 = extraout_r1_02;
      fVar28 = extraout_s0_02;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x3d:
      goto LAB_0007f3e8;
    case (cRSubGame *)0x3e:
      if ((iVar21 < 1) || (pcVar18[-0x248] != (cRSubGame)0x3)) {
        pcVar5 = (cRSubGame *)
                 cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x447bc));
        uVar30 = DAT_0007fe24;
        *(undefined4 *)(pcVar18 + -0x18) = DAT_0007fe24;
        *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        pcVar18[-8] = (cRSubGame)0x3;
        pcVar7 = extraout_r1_21;
        fVar28 = extraout_s0_20;
      }
      else {
        pcVar5 = (cRSubGame *)
                 cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x447bc));
        uVar30 = DAT_0007fe24;
        *(undefined4 *)(pcVar18 + -0x18) = DAT_0007fe24;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
        pcVar18[-8] = (cRSubGame)0x9;
        pcVar18[-0x248] = (cRSubGame)0xc;
        pcVar7 = extraout_r1_24;
        fVar28 = extraout_s0_23;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x3f:
      break;
    case (cRSubGame *)0x40:
      pcVar18[-8] = (cRSubGame)0x0;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) & 0xffffffdf;
      pcVar5 = (cRSubGame *)SwitchMirror();
      pcVar7 = extraout_r1_20;
      fVar28 = extraout_s0_19;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x41:
      break;
    case (cRSubGame *)0x42:
      break;
    case (cRSubGame *)0x43:
      break;
    case (cRSubGame *)0x44:
      break;
    case (cRSubGame *)0x45:
      break;
    case (cRSubGame *)0x46:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0x13;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_19;
      fVar28 = extraout_s0_18;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x47:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0x11;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_18;
      fVar28 = extraout_s0_17;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x48:
      break;
    case (cRSubGame *)0x49:
      break;
    case (cRSubGame *)0x4a:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0x19;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_11;
      fVar28 = extraout_s0_10;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x4b:
      break;
    case (cRSubGame *)0x4c:
      break;
    case (cRSubGame *)0x4d:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0x12;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_10;
      fVar28 = extraout_s0_09;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x4e:
      break;
    case (cRSubGame *)0x4f:
      break;
    case (cRSubGame *)0x50:
      goto LAB_0007f638;
    case (cRSubGame *)0x51:
      break;
    case (cRSubGame *)0x52:
      pcVar18[-8] = (cRSubGame)0x23;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) & 0xffffffdf;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x53:
      break;
    case (cRSubGame *)0x54:
      break;
    case (cRSubGame *)0x55:
      break;
    case (cRSubGame *)0x56:
      break;
    case (cRSubGame *)0x57:
      break;
    case (cRSubGame *)0x58:
      break;
    case (cRSubGame *)0x59:
      break;
    case (cRSubGame *)0x5a:
      break;
    case (cRSubGame *)0x5b:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44790));
      uVar30 = DAT_0007f278;
      *(undefined4 *)(pcVar18 + -0x18) = DAT_0007f278;
      *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar18[-8] = (cRSubGame)0x5;
      pcVar7 = extraout_r1_08;
      fVar28 = extraout_s0_08;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x5c:
      break;
    case (cRSubGame *)0x5d:
      break;
    case (cRSubGame *)0x5e:
      break;
    case (cRSubGame *)0x5f:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0xf;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_07;
      fVar28 = extraout_s0_07;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x60:
      break;
    case (cRSubGame *)0x61:
      break;
    case (cRSubGame *)0x62:
      break;
    case (cRSubGame *)0x63:
      break;
    case (cRSubGame *)0x64:
      break;
    case (cRSubGame *)0x65:
      break;
    case (cRSubGame *)0x66:
      break;
    case (cRSubGame *)0x67:
      break;
    case (cRSubGame *)0x68:
      break;
    case (cRSubGame *)0x69:
      break;
    case (cRSubGame *)0x6a:
      break;
    case (cRSubGame *)0x6b:
      break;
    case (cRSubGame *)0x6c:
      break;
    case (cRSubGame *)0x6d:
      break;
    case (cRSubGame *)0x6e:
      break;
    case (cRSubGame *)0x6f:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44630));
      pcVar18[-8] = (cRSubGame)0x10;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_06;
      fVar28 = extraout_s0_06;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x70:
LAB_0007f638:
      if (pcVar5 == (cRSubGame *)0x50) {
        pcVar18[-8] = (cRSubGame)0x1e;
      }
      else if (pcVar5 == (cRSubGame *)0x70) {
        pcVar18[-8] = (cRSubGame)0x1d;
      }
      if (in_r0[2] == (cRSubGame)0x0) {
        *(cRSubGame **)(pcVar18 + -0xc) = in_r0 + *(int *)(pcVar20 + -0x44) * 0x120 + 0x310004;
      }
      else {
        *(cRSubGame **)(pcVar18 + -0xc) = in_r0 + *(int *)(pcVar20 + -0x44) * 0x120 + 0x310094;
      }
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) & 0xffffffdf;
      pcVar7 = local_6c;
      if (local_6c == (cRSubGame *)0x0) {
        cRBod::SetObject(this,*(cRObject **)(*(int *)(pcVar18 + -0xc) + 0x24));
        pcVar8 = *(cRObject **)(*(int *)(pcVar18 + -0xc) + 0x78);
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        fVar28 = (float)cRBod::SetObject((cRBod *)(in_r0 + iVar21 * 0xdc + 0x20df80),pcVar8);
        pcVar5 = *(cRSubGame **)(pcVar18 + -0xc);
        uVar30 = *(undefined4 *)(local_94 + 0x1c);
        *(uint *)(pcVar20 + -0x30) = *(uint *)(pcVar20 + -0x30) | 0x20;
        iVar10 = *(int *)(pcVar5 + 0x3c);
        *(undefined4 *)(pcVar20 + -0x38) = uVar30;
        pcVar7 = extraout_r1_09;
        if (0 < iVar10) {
          pcVar7 = (cRSubGame *)0x0;
          pcVar15 = in_r0 + iVar21 * 0xdc + 0x20df78;
          do {
            uVar12 = *(uint *)(pcVar15 + -0x9c);
            pcVar7 = pcVar7 + 1;
            bVar24 = (uVar12 & 0x40) != 0;
            if (bVar24) {
              *(uint *)(pcVar15 + -0x9c) = uVar12 | 0x80;
            }
            else {
              *(uint *)(pcVar15 + -0x9c) = uVar12 | 0x40;
            }
            iVar10 = *(int *)(pcVar5 + 0x3c);
            if (bVar24) {
              *(cRSubGame **)pcVar15 = in_r0 + iVar6 + (int)pcVar11 * 0x48 + 0x13adc;
            }
            else {
              *(cRSubGame **)(pcVar15 + -4) = in_r0 + iVar6 + (int)pcVar11 * 0x48 + 0x13adc;
            }
            pcVar15 = pcVar15 + 0xdc;
          } while ((int)pcVar7 < iVar10);
        }
        local_6c = (cRSubGame *)0x1;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x71:
      break;
    case (cRSubGame *)0x72:
      break;
    case (cRSubGame *)0x73:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44370));
      pcVar18[-8] = (cRSubGame)0x21;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_05;
      fVar28 = extraout_s0_05;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x74:
      break;
    case (cRSubGame *)0x75:
      break;
    case (cRSubGame *)0x76:
      break;
    case (cRSubGame *)0x77:
      break;
    case (cRSubGame *)0x78:
      break;
    case (cRSubGame *)0x79:
      break;
    case (cRSubGame *)0x7a:
      break;
    case (cRSubGame *)0x7b:
      if ((iVar21 < 1) || (pcVar18[-0x248] != (cRSubGame)0x3)) {
        pcVar5 = (cRSubGame *)
                 cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44790));
        uVar30 = DAT_0007f278;
        *(undefined4 *)(pcVar18 + -0x18) = DAT_0007f278;
        *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        pcVar18[-8] = (cRSubGame)0x2;
        pcVar7 = extraout_r1_04;
        fVar28 = extraout_s0_04;
      }
      else {
        pcVar5 = (cRSubGame *)
                 cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44790));
        uVar30 = DAT_0007fe24;
        *(undefined4 *)(pcVar18 + -0x18) = DAT_0007fe24;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
        pcVar18[-8] = (cRSubGame)0x8;
        pcVar18[-0x248] = (cRSubGame)0xb;
        pcVar7 = extraout_r1_26;
        fVar28 = extraout_s0_25;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x7c:
LAB_0007f3e8:
      pcVar5 = (cRSubGame *)
               cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x44210));
      pcVar18[-8] = (cRSubGame)0xe;
      *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
      pcVar7 = extraout_r1_01;
      fVar28 = extraout_s0_01;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x7d:
      if ((iVar21 < 1) || (pcVar18[-0x248] != (cRSubGame)0x3)) {
        pcVar5 = (cRSubGame *)
                 cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x447e8));
        uVar30 = DAT_0007f278;
        *(undefined4 *)(pcVar18 + -0x18) = DAT_0007f278;
        *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        pcVar18[-8] = (cRSubGame)0x4;
        pcVar7 = extraout_r1_03;
        fVar28 = extraout_s0_03;
      }
      else {
        pcVar5 = (cRSubGame *)
                 cRBod::SetObject(this,*(cRObject **)(**(int **)(pcVar4 + iVar22) + 0x447e8));
        uVar30 = DAT_0007fe24;
        *(undefined4 *)(pcVar18 + -0x18) = DAT_0007fe24;
        *(uint *)(pcVar18 + -0x34) = *(uint *)(pcVar18 + -0x34) | 0x20;
        *(undefined4 *)(pcVar18 + -0x1c) = uVar30;
        pcVar18[-8] = (cRSubGame)0xa;
        pcVar18[-0x248] = (cRSubGame)0xd;
        pcVar7 = extraout_r1_25;
        fVar28 = extraout_s0_24;
      }
      goto LAB_0007f2a4;
    }
    uVar30 = LevelConvert(in_r0,(char)local_98[*(int *)(local_94 + 0x14) + local_88 * 8],iVar21,true
                         );
    pcVar5 = (cRSubGame *)wprintf((char *)pcVar17,uVar30,*(undefined4 *)(local_94 + 0x10));
    pcVar7 = extraout_r1_00;
    fVar28 = extraout_s0_00;
LAB_0007f2a4:
    uVar30 = DAT_0007f278;
    *(undefined4 *)(pcVar18 + -0x20) = DAT_0007f278;
    *(undefined4 *)(pcVar18 + -0x24) = uVar30;
    *(undefined4 *)(pcVar18 + -0x28) = uVar30;
    *(undefined4 *)(pcVar20 + -0x1c) = uVar30;
    *(undefined4 *)(pcVar20 + -0x20) = uVar30;
    *(undefined4 *)(pcVar20 + -0x24) = uVar30;
    cVar13 = pcVar18[-8];
    if ((byte)((char)cVar13 - 0x1dU) < 2) {
      uVar12 = *(uint *)(*(int *)(pcVar4 + iVar16) + 0x1c);
      fVar26 = (fVar32 + DAT_0007fe08) - DAT_0007fe08;
      *(float *)(pcVar18 + -0x20) = fVar26;
      if ((uVar12 & 0x20) == 0) {
        *(uint *)(pcVar20 + -0x30) = *(uint *)(pcVar20 + -0x30) & 0xffffffdf;
        cVar13 = pcVar18[-8];
        pcVar5 = pcVar4;
      }
      else {
        *(float *)(pcVar20 + -0x1c) = fVar26;
        pcVar5 = (cRSubGame *)
                 GetSkirtColour((tColourSmall *)(**(int **)(pcVar4 + iVar22) + 0x718a0));
        cVar13 = pcVar18[-8];
        pcVar7 = extraout_r1_23;
        fVar28 = extraout_s0_22;
      }
    }
    else {
      fVar27 = (float)VectorSignedToFloat(pcVar11,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(pcVar18 + -0x24) = uVar30;
      fVar29 = DAT_0007f268;
      fVar26 = DAT_0007f264;
      if ((byte)((char)cVar13 - 8U) < 3) {
        *(float *)(pcVar18 + -0x24) = DAT_0007f268;
      }
      *(float *)(pcVar18 + -0x28) = (fVar27 - fVar26) + fVar29;
      *(float *)(pcVar18 + -0x20) = fVar32 + DAT_0007f268;
    }
    if (iVar21 < 4) {
      iVar10 = *(int *)(in_r0 + 0x60);
      bVar24 = iVar10 != 2;
      if (bVar24) {
        iVar10 = *(int *)(in_r0 + 0x3131d0);
      }
      if (bVar24) {
        *(undefined4 *)(pcVar18 + -0x24) = *(undefined4 *)(iVar10 + 0x34);
      }
    }
    if (cVar13 == (cRSubGame)0x1c) {
      *(float *)(pcVar18 + -0x24) = *(float *)(pcVar18 + -0x24) - DAT_0007f26c;
    }
    if ((((((cVar13 == (cRSubGame)0x1 || cVar13 == (cRSubGame)0x15) || (cVar13 == (cRSubGame)0x14))
          || (cVar13 == (cRSubGame)0x21)) ||
         (((cVar13 == (cRSubGame)0x22 || (cVar13 == (cRSubGame)0xf)) ||
          ((cVar13 == (cRSubGame)0x10 ||
           ((cVar13 == (cRSubGame)0x17 || (cVar13 == (cRSubGame)0x18)))))))) ||
        (cVar13 == (cRSubGame)0x19)) ||
       ((((cVar13 == (cRSubGame)0x1a || (cVar13 == (cRSubGame)0x1b)) || (cVar13 == (cRSubGame)0x12))
        || ((cVar13 == (cRSubGame)0x13 || (cVar13 == (cRSubGame)0x11)))))) {
      pcVar5 = (cRSubGame *)(8 - (int)pcVar11);
      fVar26 = (float)VectorSignedToFloat(pcVar5,(byte)(in_fpscr >> 0x16) & 3);
      fVar29 = (float)VectorSignedToFloat(iVar21 % 8,(byte)(in_fpscr >> 0x16) & 3);
      fVar26 = fVar26 * DAT_0007f270 * DAT_0007f274;
      *(float *)(pcVar18 + -0x18) = fVar29 * DAT_0007f274;
      *(float *)(pcVar18 + -0x1c) = fVar26;
      if (cVar13 != (cRSubGame)0x1f) goto LAB_0007f388;
LAB_0007fb70:
      *(float *)(pcVar18 + -0x28) = *(float *)(pcVar18 + -0x28) * DAT_0007fe0c;
    }
    else {
      if (cVar13 == (cRSubGame)0x1f) goto LAB_0007fb70;
LAB_0007f388:
      if (cVar13 == (cRSubGame)0x16) {
        if ((*(int *)(in_r0 + 0x60) != 3) || ((*(uint *)(in_r0 + 0x6c) & 0x400) != 0)) {
          *(undefined4 *)(pcVar18 + -0x24) = DAT_0007fe10;
        }
        *(float *)(pcVar18 + -0x20) = fVar32 + DAT_0007fe08;
      }
    }
    if (pcVar11 == (cRSubGame *)0x7) break;
    pcVar11 = pcVar11 + 1;
    pcVar18 = pcVar18 + 0x48;
    cVar13 = in_r0[2];
  } while( true );
  iVar6 = *(int *)(in_r0 + 0x74);
  iVar21 = iVar21 + 1;
  local_88 = local_88 + 1;
  pcVar20 = pcVar20 + 0xdc;
  bVar25 = SBORROW4(local_68,local_88);
  iVar10 = local_68 - local_88;
  bVar24 = local_68 == local_88;
  if (local_88 < local_68) {
    bVar25 = SBORROW4(iVar6,iVar21);
    iVar10 = iVar6 - iVar21;
    bVar24 = iVar6 == iVar21;
  }
  local_74 = local_74 + 1;
  if (bVar24 || iVar10 < 0 != bVar25) goto LAB_0007fbc8;
  goto LAB_0007ed78;
}
