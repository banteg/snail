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
  cRObject *pcVar6;
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
  cRSubGame *pcVar7;
  int iVar8;
  cRSubGame *pcVar9;
  uint uVar10;
  cRSubGame cVar11;
  undefined1 uVar12;
  cRSubGame *pcVar13;
  int iVar14;
  cRSubGame *pcVar15;
  cRSubGame *pcVar16;
  int iVar17;
  cRSubGame *pcVar18;
  cRBod *this;
  int iVar19;
  int iVar20;
  bool bVar21;
  bool bVar22;
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
  float fVar23;
  float fVar24;
  float fVar25;
  undefined4 uVar26;
  char *pcVar27;
  float fVar28;
  cRSubGame *local_98;
  cRSubGame *local_94;
  undefined **local_8c;
  int local_88;
  cRSubGame *local_74;
  cRSubGame *local_6c;
  int local_68;
  int local_64;
  cRSubGame *local_60;
  int local_38;

  if (in_r0[0x30fcc0] == (cRSubGame)0x0) {
    iVar20 = *(int *)(in_r0 + 0x60);
    iVar14 = 0;
    if (iVar20 != 4 && iVar20 != 7) {
      fVar24 = (float)RAND(in_s0,(char *)0x47000000);
      iVar20 = *(int *)(in_r0 + 0x60);
      iVar14 = (int)fVar24;
      in_s0 = extraout_s0_28;
    }
  }
  else {
    iVar20 = *(int *)(in_r0 + 0x60);
    iVar14 = *(int *)(*(int *)(in_r0 + 0x30fcc4) + 0x68);
  }
  local_8c = &__DT_PLTGOT;
  if (iVar20 != 1) {
    if (iVar20 == 4) {
      cRSubSolution::ReSet
                (*(cRSubSolution **)(in_r0 + 0x30fcbc),iVar14,*(int *)(in_r0 + 100),in_s0,
                 *(int *)(in_r0 + 0x4c),*(int *)(in_r0 + 0x6c),2);
      goto LAB_0007e910;
    }
    if (iVar20 != 0) goto LAB_0007e910;
  }
  cRSubSolution::ReSet
            (*(cRSubSolution **)(in_r0 + 0x30fcbc),iVar14,*(int *)(in_r0 + 100),in_s0,
             *(int *)(in_r0 + 0x4c),*(int *)(in_r0 + 0x6c),iVar20);
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
  cRTime::Zero((cRTime *)(in_r0 + 0xfd94));
  *(undefined4 *)(in_r0 + 0xfdac) = 0;
  *(undefined4 *)(in_r0 + 0xfdb4) = 0;
  RandSeed(iVar14);
  cRTrack::Change(Game + 0x848);
  iVar14 = *(int *)(in_r0 + 0x60);
  if (((iVar14 == 0 || iVar14 == 7) || (iVar14 == 4)) || (iVar14 == 1)) {
    *(undefined4 *)(in_r0 + 0x70) = *(undefined4 *)(in_r0 + 0x14f8);
    *(undefined4 *)(in_r0 + 0x74) = *(undefined4 *)(in_r0 + 0x1590);
    if (iVar14 == 1) {
      fVar24 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0x1590),
                                          (byte)(in_fpscr >> 0x16) & 3);
      *(int *)(in_r0 + 0x74) = (int)(fVar24 * (*(float *)(in_r0 + 0x50) * 0.65 + 0.35));
    }
    if (in_r0[0x1594] == (cRSubGame)0x0) {
      iVar14 = *(int *)(in_r0 + 0x152c) + *(int *)(in_r0 + 0x14f8);
      *(int *)(in_r0 + 0x74) = iVar14;
      if (0 < *(int *)(in_r0 + 0xa0)) {
        iVar20 = 0;
        pcVar7 = in_r0;
        do {
          iVar20 = iVar20 + 1;
          pcVar15 = pcVar7 + 0xa8;
          pcVar7 = pcVar7 + 0x34;
          iVar14 = iVar14 + *(int *)pcVar15;
        } while (iVar20 < *(int *)(in_r0 + 0xa0));
        *(int *)(in_r0 + 0x74) = iVar14;
      }
    }
    *(int *)(in_r0 + 0x78) = *(int *)(in_r0 + 0x74) - *(int *)(in_r0 + 0x152c);
    if (0xdab < *(int *)(in_r0 + 0x74)) {
      RShellError("Track (%s) too long, Maximum Length %i",in_r0 + 0x15a8,0xdac);
    }
  }
  else if (iVar14 == 3) {
    *(int *)(in_r0 + 0x70) = *(int *)(in_r0 + 0x14f8);
    iVar14 = *(int *)(in_r0 + 0x152c) + *(int *)(in_r0 + 0x14f8) + *(int *)(in_r0 + 0xa8) * 0x10;
    *(int *)(in_r0 + 0x74) = iVar14;
    *(int *)(in_r0 + 0x78) = iVar14 - *(int *)(in_r0 + 0x152c);
  }
  iVar20 = 0;
  pcVar7 = in_r0 + 0x20dedc;
  iVar14 = 0;
  in_r0[2] = (cRSubGame)0x0;
  in_r0[0xfe74] = (cRSubGame)0x0;
  *(undefined4 *)(in_r0 + 4) = 0;
  do {
    *(undefined4 *)pcVar7 = 0;
    *(undefined4 *)(pcVar7 + 0xa0) = 0;
    iVar19 = iVar20 * 0x240;
    *(undefined4 *)(pcVar7 + 0x94) = 0;
    *(undefined4 *)(pcVar7 + 0xd0) = 0;
    *(undefined4 *)(pcVar7 + 0x98) = 0;
    pcVar15 = in_r0 + iVar19 + 0x13af8;
    *(undefined4 *)(pcVar7 + 0x8c) = 0;
    *(undefined4 *)(pcVar7 + 0x88) = 0;
    *(undefined4 *)(pcVar7 + 0x84) = 0;
    *(undefined4 *)(pcVar7 + 0x90) = 0;
    *(undefined4 *)(pcVar7 + 0xd4) = 0;
    *(undefined4 *)(pcVar7 + 0xd8) = 0;
    iVar8 = 0;
    do {
      iVar17 = iVar8 + 1;
      iVar8 = iVar19 + iVar8 * 0x48;
      in_r0[iVar8 + 0x13b11] = (cRSubGame)((byte)in_r0[iVar8 + 0x13b11] & 0x5f);
      pcVar15[0x15] = (cRSubGame)0x0;
      in_r0[iVar8 + 0x13b10] = (cRSubGame)((byte)in_r0[iVar8 + 0x13b10] & 0xa7);
      in_r0[iVar8 + 0x13b11] = (cRSubGame)((byte)in_r0[iVar8 + 0x13b11] & 0xaf);
      *(undefined2 *)(pcVar15 + 0x18) = 0;
      *(uint *)(pcVar15 + -0x18) = *(uint *)(pcVar15 + -0x18) & 0xffffff7f;
      fVar24 = (float)tColourSmall::White((tColourSmall *)(in_r0 + iVar8 + 0x13b04));
      *(undefined4 *)pcVar15 = 0;
      *(undefined4 *)(pcVar15 + 4) = 0;
      pcVar15 = pcVar15 + 0x48;
      iVar8 = iVar17;
    } while (iVar17 != 8);
    iVar8 = 0;
    pcVar15 = in_r0 + iVar19 + 0x13adc;
    do {
      iVar8 = iVar8 + 1;
      *(undefined4 *)(pcVar15 + 0x38) = 0;
      *(undefined4 *)(pcVar15 + 0x3c) = 0;
      *(undefined4 *)(pcVar15 + 0x40) = 0;
      *(undefined4 *)(pcVar15 + 0x44) = 0;
      pcVar15 = pcVar15 + 0x48;
    } while (iVar8 != 8);
    iVar20 = iVar20 + 1;
    pcVar7 = pcVar7 + 0xdc;
  } while (iVar20 != 0xe10);
  if ((in_r0[0x1594] != (cRSubGame)0x0) &&
     (iVar20 = *(int *)(in_r0 + 0xa0), pcVar7 = in_r0, 0 < iVar20)) {
    do {
      iVar14 = iVar14 + 1;
      pcVar7[0xac] = (cRSubGame)0x0;
      pcVar7 = pcVar7 + 0x34;
    } while (iVar14 < iVar20);
  }
  iVar20 = 0;
  bVar2 = false;
  local_60 = (cRSubGame *)0x0;
  bVar3 = false;
  local_64 = 0;
  local_38 = 0;
  pcVar7 = in_r0 + 0x1528;
  iVar14 = *(int *)(in_r0 + 0x74);
  pcVar15 = in_r0 + 0x1680;
  while( true ) {
    if (iVar14 <= iVar20) {
      wprintf("Track Length %i\n",iVar20);
      return;
    }
    bVar2 = (bool)(bVar2 ^ 1);
    if (iVar20 == 0) {
      bVar3 = true;
      *(undefined4 *)(in_r0 + 0x14f4) = 0;
      local_68 = *(int *)(in_r0 + 0x14f8);
      local_94 = in_r0 + 0x14f4;
    }
    else if ((*(int *)(in_r0 + 0x78) == iVar20) && (in_r0[0x1594] == (cRSubGame)0x0)) {
      bVar3 = true;
      *(int *)(in_r0 + 0x1528) = iVar20;
      local_68 = *(int *)(in_r0 + 0x152c);
      local_94 = pcVar7;
    }
    else {
      *(undefined4 *)(in_r0 + 0x68) = 0x3f800000;
      if (in_r0[0x1594] == (cRSubGame)0x0) {
        iVar14 = local_38 * 0x34;
        local_38 = local_38 + 1;
        local_94 = in_r0 + iVar14 + 0xa4;
      }
      else if (bVar2) {
        bVar3 = true;
        *(int *)(in_r0 + 0x155c) = iVar20;
        local_94 = in_r0 + 0x155c;
      }
      else {
        if (*(int *)(in_r0 + 0x60) == 1) {
          fVar28 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0xa0),
                                              (byte)(in_fpscr >> 0x16) & 3);
          fVar24 = (float)RAND(fVar24,(char *)(fVar28 * (*(float *)(in_r0 + 0x50) * 0.9 + 0.1)));
        }
        else {
          pcVar27 = (char *)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0xa0),
                                                (byte)(in_fpscr >> 0x16) & 3);
          fVar24 = (float)RAND(fVar24,pcVar27);
        }
        fVar24 = (float)VectorSignedToFloat((int)fVar24,(byte)(in_fpscr >> 0x16) & 3);
        local_94 = in_r0 + (int)(fVar24 * *(float *)(in_r0 + 0x68)) * 0x34 + 0xa4;
        in_r0[(int)(fVar24 * *(float *)(in_r0 + 0x68)) * 0x34 + 0xac] = (cRSubGame)0x1;
      }
      local_68 = *(int *)(local_94 + 4);
    }
    fVar24 = (float)SwitchMirror();
    *(int *)local_94 = iVar20;
    if (*(int *)(local_94 + 4) < 0) {
      fVar24 = (float)RShellError("Negative Segment Length");
    }
    iVar14 = *(int *)(in_r0 + 0x74);
    if (iVar20 < iVar14 && 0 < local_68) break;
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
  pcVar4 = (cRSubGame *)(local_68 + iVar20);
  local_88 = 0;
  pcVar18 = in_r0 + iVar20 * 0xdc + 0x20dfb4;
  local_74 = pcVar4;
LAB_0007ed78:
  pcVar9 = *(cRSubGame **)(in_r0 + 0x60);
  if (pcVar9 == (cRSubGame *)0x2) {
    iVar19 = local_88 * 10;
    pcVar5 = local_94;
  }
  else {
    iVar8 = *(int *)(in_r0 + 0x78);
    if (iVar20 < iVar8) {
      iVar19 = local_88 * 10;
    }
    else {
      local_94 = pcVar7;
      if ((((pcVar9 != (cRSubGame *)0x0 && pcVar9 != (cRSubGame *)0x4) &&
           (pcVar9 != (cRSubGame *)0x1)) && (pcVar9 != (cRSubGame *)0x7)) &&
         (pcVar9 != (cRSubGame *)0x3)) {
        local_94 = pcVar15;
      }
      if (iVar20 == iVar8) {
        iVar19 = 0;
        local_88 = 0;
      }
      else {
        iVar19 = local_88 * 10;
      }
    }
    pcVar4 = local_74 + -local_88;
    pcVar5 = local_94;
    if (((((iVar8 < (int)pcVar4) && (pcVar5 = pcVar15, pcVar15 != local_94)) &&
         ((pcVar5 = local_94, in_r0 + 0x16e8 != local_94 && (in_r0 + 0x171c != local_94)))) &&
        (((pcVar9 == (cRSubGame *)0x0 || pcVar9 == (cRSubGame *)0x4 || (pcVar9 == (cRSubGame *)0x1))
         || ((pcVar9 == (cRSubGame *)0x7 || (pcVar9 == (cRSubGame *)0x3)))))) &&
       (pcVar9 = pcVar7, pcVar5 = pcVar7, pcVar7 != local_94)) {
      *(cRSubGame **)(in_r0 + 0x78) = pcVar4;
      *(cRSubGame **)(in_r0 + 0x74) = pcVar4 + (iVar14 - iVar8);
      pcVar5 = local_94;
    }
  }
  local_94 = pcVar5;
  cVar11 = in_r0[2];
  bVar21 = cVar11 != (cRSubGame)0x0;
  if (bVar21) {
    pcVar9 = *(cRSubGame **)(pcVar18 + -0xd8);
  }
  iVar14 = *(int *)(local_94 + 0x18);
  if (bVar21) {
    pcVar9 = (cRSubGame *)((uint)pcVar9 | 0x20);
  }
  *(cRSubGame **)(pcVar18 + -4) = local_94;
  if (bVar21) {
    *(cRSubGame **)(pcVar18 + -0xd8) = pcVar9;
  }
  uVar1 = *(ushort *)(iVar14 + iVar19);
  *(int *)pcVar18 = local_64;
  if ((uVar1 & 0x100) != 0) {
    pcVar4 = (cRSubGame *)(*(uint *)(pcVar18 + -0xd8) | 0x100);
    *(cRSubGame **)(pcVar18 + -0xd8) = pcVar4;
  }
  if ((uVar1 & 0x8000) != 0) {
    *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 0x8000;
  }
  iVar8 = Game;
  uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
  if ((*(ushort *)(iVar14 + iVar19) & 2) == 0) {
    fVar28 = (float)VectorSignedToFloat(iVar20,(byte)(in_fpscr >> 0x16) & 3);
  }
  else {
    fVar28 = (float)VectorSignedToFloat(iVar20,(byte)(in_fpscr >> 0x16) & 3);
    *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 2;
    cRBod::SetObject((cRBod *)(in_r0 + iVar20 * 0xdc + 0x20dee0),
                     *(cRObject **)((uint)*(byte *)(iVar14 + iVar19 + 3) * 0xb0 + iVar8 + 0x47afc));
    *(undefined4 *)(*(int *)(pcVar18 + -0xb0) + 8) = 1;
    tMatrix::Identity((tMatrix *)(in_r0 + iVar20 * 0xdc + 0x20df0c));
    iVar14 = *(int *)(local_94 + 0x18);
    iVar8 = iVar14 + iVar19;
    uVar1 = *(ushort *)(iVar14 + iVar19);
    uVar10 = (uint)uVar1;
    uVar26 = VectorUnsignedToFloat((uint)*(byte *)(iVar8 + 6),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(pcVar18 + -0x78) = uVar26;
    uVar26 = VectorUnsignedToFloat((uint)*(byte *)(iVar8 + 7),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(pcVar18 + -0x74) = uVar26;
    fVar24 = (float)VectorUnsignedToFloat((uint)*(byte *)(iVar8 + 8),(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(pcVar18 + -0x70) = fVar24 + fVar28;
    pcVar4 = local_94;
    if ((uVar1 & 8) == 0) {
      cVar11 = in_r0[2];
      *(undefined4 *)(pcVar18 + -0x60) = 0;
      *(undefined4 *)(pcVar18 + -0x58) = 0;
      *(undefined4 *)(pcVar18 + -0x5c) = 0;
    }
    else {
      *(undefined4 *)(pcVar18 + -0x60) = 0;
      *(undefined4 *)(pcVar18 + -0x58) = 0;
      *(undefined4 *)(pcVar18 + -0x5c) = 0;
      *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 8;
      cVar11 = in_r0[2];
    }
  }
  if ((uVar10 & 1) != 0) {
    uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
    *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 0x4001;
    pcVar4 = (cRSubGame *)(uint)*(byte *)(iVar14 + iVar19 + 2);
    *(undefined4 *)(pcVar18 + -0x50) = 0;
    *(undefined4 *)(pcVar18 + -0x54) = 0;
    *(cRSubGame **)(pcVar18 + -0x48) = pcVar4;
    uVar26 = VectorUnsignedToFloat
                       ((uint)*(byte *)(iVar14 + iVar19 + 5),(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(pcVar18 + -0x4c) = uVar26;
  }
  if ((uVar10 & 8) != 0) {
    uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
    *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 8;
    pcVar4 = (cRSubGame *)(uint)*(byte *)(iVar14 + iVar19 + 4);
    *(cRSubGame **)(pcVar18 + -0x44) = pcVar4;
  }
  if ((uVar10 & 4) != 0) {
    uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
    pcVar4 = (cRSubGame *)(*(uint *)(pcVar18 + -0xd8) | 4);
    *(cRSubGame **)(pcVar18 + -0xd8) = pcVar4;
  }
  bVar21 = (uVar10 & 0x200) != 0;
  if (bVar21) {
    pcVar4 = *(cRSubGame **)(pcVar18 + -0xd8);
  }
  *(undefined4 *)(pcVar18 + -8) = 0;
  if (bVar21) {
    uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
  }
  pcVar9 = (cRSubGame *)0x0;
  if (bVar21) {
    pcVar4 = (cRSubGame *)((uint)pcVar4 | 0x200);
  }
  local_6c = (cRSubGame *)0x0;
  if (bVar21) {
    *(cRSubGame **)(pcVar18 + -0xd8) = pcVar4;
  }
  if ((uVar10 & 0x400) != 0) {
    uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
    *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 0x400;
  }
  if ((uVar10 & 0x2000) != 0) {
    uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
    *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 0x2000;
  }
  if ((uVar10 & 0x800) != 0) {
    uVar10 = (uint)*(ushort *)(iVar14 + iVar19);
    *(uint *)(pcVar18 + -0xd8) = *(uint *)(pcVar18 + -0xd8) | 0x800;
  }
  bVar21 = (uVar10 & 0x1000) != 0;
  if (bVar21) {
    uVar10 = *(uint *)(pcVar18 + -0xd8);
  }
  pcVar5 = (cRSubGame *)((uint)(iVar20 >> 0x1f) >> 0x1d);
  if (bVar21) {
    *(uint *)(pcVar18 + -0xd8) = uVar10 | 0x1000;
  }
  iVar14 = iVar20 * 0x240;
  pcVar16 = in_r0 + iVar14 + 0x13b14;
  do {
    pcVar4 = pcVar9;
    if (cVar11 != (cRSubGame)0x0) {
      pcVar5 = (cRSubGame *)(7 - (int)pcVar9);
      pcVar4 = local_98;
    }
    local_98 = pcVar4;
    iVar19 = iVar14 + (int)pcVar9 * 0x48;
    if (cVar11 != (cRSubGame)0x0) {
      local_98 = pcVar5;
    }
    in_r0[iVar19 + 0x13b10] = (cRSubGame)((byte)in_r0[iVar19 + 0x13b10] & 0xe0 | (byte)pcVar9 & 7);
    iVar8 = *(int *)(in_r0 + 0x70);
    *(undefined4 *)pcVar16 = 0;
    *(undefined4 *)(pcVar16 + 4) = 0;
    *(undefined4 *)(pcVar16 + 8) = 0;
    iVar19 = iVar8;
    if (iVar20 < iVar8) {
      iVar19 = 1;
    }
    uVar12 = (undefined1)iVar19;
    *(undefined4 *)(pcVar16 + 0xc) = 0;
    if (iVar8 <= iVar20) {
      if (iVar20 < *(int *)(in_r0 + 0x78)) {
        uVar12 = false;
      }
      else {
        uVar12 = true;
      }
    }
    this = (cRBod *)(in_r0 + iVar14 + (int)pcVar9 * 0x48 + 0x13adc);
    cRBod::SetObject(this,(cRObject *)0x0);
    pcVar4 = (cRSubGame *)
             LevelConvert(in_r0,(char)local_98[*(int *)(local_94 + 0x14) + local_88 * 8],iVar20,
                          (bool)uVar12);
    pcVar5 = extraout_r1;
    fVar24 = extraout_s0;
    switch(pcVar4) {
    case (cRSubGame *)0x20:
      goto LAB_0007f294;
    case (cRSubGame *)0x21:
      break;
    case (cRSubGame *)0x22:
      break;
    case (cRSubGame *)0x23:
      pcVar16[-8] = (cRSubGame)0x20;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) & 0xffffffdf;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x24:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0x17;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_17;
      fVar24 = extraout_s0_16;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x25:
      break;
    case (cRSubGame *)0x26:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44370));
      pcVar16[-8] = (cRSubGame)0x22;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_16;
      fVar24 = extraout_s0_15;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x27:
      break;
    case (cRSubGame *)0x28:
      uVar10 = *(uint *)(pcVar16 + -0x34);
      pcVar4 = local_60 + 1;
      if (pcVar4 == (cRSubGame *)0xf) {
        pcVar5 = (cRSubGame *)0x0;
      }
      *(uint *)(pcVar16 + -0x34) = uVar10 & 0xffffffdf;
      local_60 = pcVar5;
      if (pcVar4 != (cRSubGame *)0xf) {
        local_60 = pcVar4;
        if (pcVar4 == (cRSubGame *)0x8) {
          cRBod::SetObject(this,*(cRObject **)(Game + 0x44134));
          *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
          pcVar4 = (cRSubGame *)
                   tColourSmall::Set((tColourSmall *)
                                     (in_r0 + (int)pcVar9 * 0x48 + iVar20 * 0x240 + 0x13b04),
                                     extraout_s0_26,extraout_s1,extraout_s2,extraout_s3);
          pcVar5 = extraout_r1_27;
          fVar24 = extraout_s0_27;
        }
        else {
          *(uint *)(pcVar16 + -0x34) = uVar10 & 0xffffffdf;
        }
      }
      pcVar16[-8] = (cRSubGame)0x16;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x29:
      break;
    case (cRSubGame *)0x2a:
      break;
    case (cRSubGame *)0x2b:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0x18;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_15;
      fVar24 = extraout_s0_14;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2c:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x43e48));
      pcVar16[-8] = (cRSubGame)0x1c;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_14;
      fVar24 = extraout_s0_13;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2d:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44370));
      pcVar16[-8] = (cRSubGame)0x15;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_13;
      fVar24 = extraout_s0_12;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2e:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44370));
      pcVar16[-8] = (cRSubGame)0x1;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_12;
      fVar24 = extraout_s0_11;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x2f:
      break;
    case (cRSubGame *)0x30:
      if (*(int *)(in_r0 + 0x60) != 1) goto LAB_0007f288;
      fVar23 = (float)VectorSignedToFloat(pcVar9,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(pcVar18 + -0x50) = *(undefined4 *)(pcVar16 + -0x24);
      cVar11 = in_r0[2];
      *(undefined4 *)(pcVar18 + -0x48) = 0;
      uVar10 = *(uint *)(pcVar18 + -0xd8) & 0xffffbfff | 1;
      *(uint *)(pcVar18 + -0xd8) = uVar10;
      fVar23 = (fVar23 - 4.0) + 0.5;
      *(float *)(pcVar18 + -0x4c) = fVar28 + 0.5;
      *(float *)(pcVar18 + -0x54) = fVar23;
      if (cVar11 != (cRSubGame)0x0) {
        *(float *)(pcVar18 + -0x54) = -fVar23;
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
      uVar10 = *(uint *)(pcVar18 + -0xd8);
LAB_0007f28c:
      if ((uVar10 & 0xc0) == 0) {
        pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
        pcVar16[-8] = (cRSubGame)0xf;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        pcVar5 = extraout_r1_22;
        fVar24 = extraout_s0_21;
      }
      else {
LAB_0007f294:
        pcVar16[-8] = (cRSubGame)0x0;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) & 0xffffffdf;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x3a:
      break;
    case (cRSubGame *)0x3b:
      break;
    case (cRSubGame *)0x3c:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x447bc));
      *(undefined4 *)(pcVar16 + -0x18) = 0;
      *(undefined4 *)(pcVar16 + -0x1c) = 0;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar16[-8] = (cRSubGame)0x6;
      pcVar5 = extraout_r1_02;
      fVar24 = extraout_s0_02;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x3d:
      goto LAB_0007f3e8;
    case (cRSubGame *)0x3e:
      if ((iVar20 < 1) || (pcVar16[-0x248] != (cRSubGame)0x3)) {
        pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x447bc));
        *(undefined4 *)(pcVar16 + -0x18) = 0;
        *(undefined4 *)(pcVar16 + -0x1c) = 0;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        pcVar16[-8] = (cRSubGame)0x3;
        pcVar5 = extraout_r1_21;
        fVar24 = extraout_s0_20;
      }
      else {
        pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x447bc));
        *(undefined4 *)(pcVar16 + -0x18) = 0;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        *(undefined4 *)(pcVar16 + -0x1c) = 0;
        pcVar16[-8] = (cRSubGame)0x9;
        pcVar16[-0x248] = (cRSubGame)0xc;
        pcVar5 = extraout_r1_24;
        fVar24 = extraout_s0_23;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x3f:
      break;
    case (cRSubGame *)0x40:
      pcVar16[-8] = (cRSubGame)0x0;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) & 0xffffffdf;
      pcVar4 = (cRSubGame *)SwitchMirror();
      pcVar5 = extraout_r1_20;
      fVar24 = extraout_s0_19;
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
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0x13;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_19;
      fVar24 = extraout_s0_18;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x47:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0x11;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_18;
      fVar24 = extraout_s0_17;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x48:
      break;
    case (cRSubGame *)0x49:
      break;
    case (cRSubGame *)0x4a:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0x19;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_11;
      fVar24 = extraout_s0_10;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x4b:
      break;
    case (cRSubGame *)0x4c:
      break;
    case (cRSubGame *)0x4d:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0x12;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_10;
      fVar24 = extraout_s0_09;
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
      pcVar16[-8] = (cRSubGame)0x23;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) & 0xffffffdf;
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
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44790));
      *(undefined4 *)(pcVar16 + -0x18) = 0;
      *(undefined4 *)(pcVar16 + -0x1c) = 0;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar16[-8] = (cRSubGame)0x5;
      pcVar5 = extraout_r1_08;
      fVar24 = extraout_s0_08;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x5c:
      break;
    case (cRSubGame *)0x5d:
      break;
    case (cRSubGame *)0x5e:
      break;
    case (cRSubGame *)0x5f:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0xf;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_07;
      fVar24 = extraout_s0_07;
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
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44630));
      pcVar16[-8] = (cRSubGame)0x10;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_06;
      fVar24 = extraout_s0_06;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x70:
LAB_0007f638:
      if (pcVar4 == (cRSubGame *)0x50) {
        pcVar16[-8] = (cRSubGame)0x1e;
      }
      else if (pcVar4 == (cRSubGame *)0x70) {
        pcVar16[-8] = (cRSubGame)0x1d;
      }
      if (in_r0[2] == (cRSubGame)0x0) {
        *(cRSubGame **)(pcVar16 + -0xc) = in_r0 + *(int *)(pcVar18 + -0x44) * 0x120 + 0x310004;
      }
      else {
        *(cRSubGame **)(pcVar16 + -0xc) = in_r0 + *(int *)(pcVar18 + -0x44) * 0x120 + 0x310094;
      }
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) & 0xffffffdf;
      pcVar5 = local_6c;
      if (local_6c == (cRSubGame *)0x0) {
        cRBod::SetObject(this,*(cRObject **)(*(int *)(pcVar16 + -0xc) + 0x24));
        pcVar6 = *(cRObject **)(*(int *)(pcVar16 + -0xc) + 0x78);
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        fVar24 = (float)cRBod::SetObject((cRBod *)(in_r0 + iVar20 * 0xdc + 0x20df80),pcVar6);
        pcVar4 = *(cRSubGame **)(pcVar16 + -0xc);
        uVar26 = *(undefined4 *)(local_94 + 0x1c);
        *(uint *)(pcVar18 + -0x30) = *(uint *)(pcVar18 + -0x30) | 0x20;
        iVar19 = *(int *)(pcVar4 + 0x3c);
        *(undefined4 *)(pcVar18 + -0x38) = uVar26;
        pcVar5 = extraout_r1_09;
        if (0 < iVar19) {
          pcVar5 = (cRSubGame *)0x0;
          pcVar13 = in_r0 + iVar20 * 0xdc + 0x20df78;
          do {
            uVar10 = *(uint *)(pcVar13 + -0x9c);
            pcVar5 = pcVar5 + 1;
            bVar21 = (uVar10 & 0x40) != 0;
            if (bVar21) {
              *(uint *)(pcVar13 + -0x9c) = uVar10 | 0x80;
            }
            else {
              *(uint *)(pcVar13 + -0x9c) = uVar10 | 0x40;
            }
            iVar19 = *(int *)(pcVar4 + 0x3c);
            if (bVar21) {
              *(cRSubGame **)pcVar13 = in_r0 + iVar14 + (int)pcVar9 * 0x48 + 0x13adc;
            }
            else {
              *(cRSubGame **)(pcVar13 + -4) = in_r0 + iVar14 + (int)pcVar9 * 0x48 + 0x13adc;
            }
            pcVar13 = pcVar13 + 0xdc;
          } while ((int)pcVar5 < iVar19);
        }
        local_6c = (cRSubGame *)0x1;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x71:
      break;
    case (cRSubGame *)0x72:
      break;
    case (cRSubGame *)0x73:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44370));
      pcVar16[-8] = (cRSubGame)0x21;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_05;
      fVar24 = extraout_s0_05;
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
      if ((iVar20 < 1) || (pcVar16[-0x248] != (cRSubGame)0x3)) {
        pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44790));
        *(undefined4 *)(pcVar16 + -0x18) = 0;
        *(undefined4 *)(pcVar16 + -0x1c) = 0;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        pcVar16[-8] = (cRSubGame)0x2;
        pcVar5 = extraout_r1_04;
        fVar24 = extraout_s0_04;
      }
      else {
        pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44790));
        *(undefined4 *)(pcVar16 + -0x18) = 0;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        *(undefined4 *)(pcVar16 + -0x1c) = 0;
        pcVar16[-8] = (cRSubGame)0x8;
        pcVar16[-0x248] = (cRSubGame)0xb;
        pcVar5 = extraout_r1_26;
        fVar24 = extraout_s0_25;
      }
      goto LAB_0007f2a4;
    case (cRSubGame *)0x7c:
LAB_0007f3e8:
      pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x44210));
      pcVar16[-8] = (cRSubGame)0xe;
      *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
      pcVar5 = extraout_r1_01;
      fVar24 = extraout_s0_01;
      goto LAB_0007f2a4;
    case (cRSubGame *)0x7d:
      if ((iVar20 < 1) || (pcVar16[-0x248] != (cRSubGame)0x3)) {
        pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x447e8));
        *(undefined4 *)(pcVar16 + -0x18) = 0;
        *(undefined4 *)(pcVar16 + -0x1c) = 0;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        pcVar16[-8] = (cRSubGame)0x4;
        pcVar5 = extraout_r1_03;
        fVar24 = extraout_s0_03;
      }
      else {
        pcVar4 = (cRSubGame *)cRBod::SetObject(this,*(cRObject **)(Game + 0x447e8));
        *(undefined4 *)(pcVar16 + -0x18) = 0;
        *(uint *)(pcVar16 + -0x34) = *(uint *)(pcVar16 + -0x34) | 0x20;
        *(undefined4 *)(pcVar16 + -0x1c) = 0;
        pcVar16[-8] = (cRSubGame)0xa;
        pcVar16[-0x248] = (cRSubGame)0xd;
        pcVar5 = extraout_r1_25;
        fVar24 = extraout_s0_24;
      }
      goto LAB_0007f2a4;
    }
    uVar26 = LevelConvert(in_r0,(char)local_98[*(int *)(local_94 + 0x14) + local_88 * 8],iVar20,true
                         );
    pcVar4 = (cRSubGame *)
             wprintf("TrackError:%c in Segment %s\n",uVar26,*(undefined4 *)(local_94 + 0x10));
    pcVar5 = extraout_r1_00;
    fVar24 = extraout_s0_00;
LAB_0007f2a4:
    *(undefined4 *)(pcVar16 + -0x20) = 0;
    *(undefined4 *)(pcVar16 + -0x24) = 0;
    *(undefined4 *)(pcVar16 + -0x28) = 0;
    *(undefined4 *)(pcVar18 + -0x1c) = 0;
    *(undefined4 *)(pcVar18 + -0x20) = 0;
    *(undefined4 *)(pcVar18 + -0x24) = 0;
    cVar11 = pcVar16[-8];
    if ((byte)((char)cVar11 - 0x1dU) < 2) {
      fVar23 = (fVar28 + 0.5) - 0.5;
      uVar10 = gConfig._28_4_ & 0x20;
      *(float *)(pcVar16 + -0x20) = fVar23;
      if (uVar10 == 0) {
        *(uint *)(pcVar18 + -0x30) = *(uint *)(pcVar18 + -0x30) & 0xffffffdf;
        cVar11 = pcVar16[-8];
        pcVar4 = (cRSubGame *)local_8c;
      }
      else {
        *(float *)(pcVar18 + -0x1c) = fVar23;
        pcVar4 = (cRSubGame *)GetSkirtColour((tColourSmall *)(Game + 0x718a0));
        cVar11 = pcVar16[-8];
        pcVar5 = extraout_r1_23;
        fVar24 = extraout_s0_22;
      }
    }
    else {
      fVar23 = (float)VectorSignedToFloat(pcVar9,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(pcVar16 + -0x24) = 0;
      if ((byte)((char)cVar11 - 8U) < 3) {
        *(undefined4 *)(pcVar16 + -0x24) = 0x3f000000;
      }
      *(float *)(pcVar16 + -0x28) = (fVar23 - 4.0) + 0.5;
      *(float *)(pcVar16 + -0x20) = fVar28 + 0.5;
    }
    if (iVar20 < 4) {
      iVar19 = *(int *)(in_r0 + 0x60);
      bVar21 = iVar19 != 2;
      if (bVar21) {
        iVar19 = *(int *)(in_r0 + 0x3131d0);
      }
      if (bVar21) {
        *(undefined4 *)(pcVar16 + -0x24) = *(undefined4 *)(iVar19 + 0x34);
      }
    }
    if (cVar11 == (cRSubGame)0x1c) {
      *(float *)(pcVar16 + -0x24) = *(float *)(pcVar16 + -0x24) - 0.03;
    }
    if ((((((cVar11 == (cRSubGame)0x1 || cVar11 == (cRSubGame)0x15) || (cVar11 == (cRSubGame)0x14))
          || (cVar11 == (cRSubGame)0x21)) ||
         (((cVar11 == (cRSubGame)0x22 || (cVar11 == (cRSubGame)0xf)) ||
          ((cVar11 == (cRSubGame)0x10 ||
           ((cVar11 == (cRSubGame)0x17 || (cVar11 == (cRSubGame)0x18)))))))) ||
        (cVar11 == (cRSubGame)0x19)) ||
       ((((cVar11 == (cRSubGame)0x1a || (cVar11 == (cRSubGame)0x1b)) || (cVar11 == (cRSubGame)0x12))
        || ((cVar11 == (cRSubGame)0x13 || (cVar11 == (cRSubGame)0x11)))))) {
      pcVar4 = (cRSubGame *)(8 - (int)pcVar9);
      fVar23 = (float)VectorSignedToFloat(pcVar4,(byte)(in_fpscr >> 0x16) & 3);
      fVar25 = (float)VectorSignedToFloat(iVar20 % 8,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(pcVar16 + -0x18) = fVar25 * 0.125;
      *(float *)(pcVar16 + -0x1c) = fVar23 * 0.25 * 0.125;
      if (cVar11 != (cRSubGame)0x1f) goto LAB_0007f388;
LAB_0007fb70:
      *(float *)(pcVar16 + -0x28) = *(float *)(pcVar16 + -0x28) * 1.1;
    }
    else {
      if (cVar11 == (cRSubGame)0x1f) goto LAB_0007fb70;
LAB_0007f388:
      if (cVar11 == (cRSubGame)0x16) {
        if ((*(int *)(in_r0 + 0x60) != 3) || ((*(uint *)(in_r0 + 0x6c) & 0x400) != 0)) {
          *(undefined4 *)(pcVar16 + -0x24) = 0xc0400000;
        }
        *(float *)(pcVar16 + -0x20) = fVar28 + 0.5;
      }
    }
    if (pcVar9 == (cRSubGame *)0x7) break;
    pcVar9 = pcVar9 + 1;
    pcVar16 = pcVar16 + 0x48;
    cVar11 = in_r0[2];
  } while( true );
  iVar14 = *(int *)(in_r0 + 0x74);
  iVar20 = iVar20 + 1;
  local_88 = local_88 + 1;
  pcVar18 = pcVar18 + 0xdc;
  bVar22 = SBORROW4(local_68,local_88);
  iVar19 = local_68 - local_88;
  bVar21 = local_68 == local_88;
  if (local_88 < local_68) {
    bVar22 = SBORROW4(iVar14,iVar20);
    iVar19 = iVar14 - iVar20;
    bVar21 = iVar14 == iVar20;
  }
  local_74 = local_74 + 1;
  if (bVar21 || iVar19 < 0 != bVar22) goto LAB_0007fbc8;
  goto LAB_0007ed78;
}
