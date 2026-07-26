/*
 * mangled: _ZN9cRSubGame2AIEv
 * demangled: cRSubGame::AI()
 * address: 00082214
 * size: 6220
 */

/* cRSubGame::AI() */

void __thiscall cRSubGame::AI(cRSubGame *this)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  cRSubLoc *this_00;
  undefined4 uVar8;
  cRSubGame cVar9;
  int *piVar10;
  undefined4 uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  cRSubGame *pcVar15;
  cRSubGame *pcVar16;
  uint *puVar17;
  cRSubGoldy *pcVar18;
  uint in_fpscr;
  uint uVar19;
  float fVar20;
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
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s3;
  float extraout_s3_00;
  float fVar21;
  float extraout_s3_01;
  float extraout_s3_02;
  float fVar22;
  float fVar23;
  int local_19c;
  int local_18c;
  undefined4 local_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 local_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  uint local_134;
  uint uStack_130;
  uint uStack_12c;
  uint uStack_128;
  undefined2 local_124;
  undefined1 local_122;
  int local_34;

  iVar3 = DAT_000823e0;
  iVar6 = DAT_000823dc + 0x8222c;
  piVar10 = *(int **)(iVar6 + DAT_000823e0);
  if (0 < *(int *)(this + 0x14)) {
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + -1;
  }
  local_34 = *piVar10;
  fVar20 = (float)CalcRate();
  switch(*(undefined4 *)(this + 0x5c)) {
  case 0:
    *(undefined4 *)(this + 0x5c) = 1;
    iVar5 = DAT_000823e8;
    iVar12 = *(int *)(this + 0x332d9c);
    if (iVar12 != 1) {
      if (iVar12 != 0 && iVar12 != 3) {
        if (this[0x30fcc1] != (cRSubGame)0x0) {
          this[0x30fcc0] = (cRSubGame)0x1;
          StartLevel(this,*(int *)(*(int *)(this + 0x30fcc4) + 0x28));
          goto LAB_000822f8;
        }
        this[0x30fcc0] = (cRSubGame)0x0;
        fVar20 = (float)cRStarManager::Hide((cRStarManager *)(**(int **)(iVar6 + iVar5) + 0x4d440));
        goto LAB_00082384;
      }
      goto LAB_00083448;
    }
    break;
  case 1:
LAB_00082384:
    RAND(fVar20,(char *)0x3f800000);
    iVar5 = DAT_000823e4;
    iVar12 = *(int *)(iVar6 + DAT_000823e4);
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(iVar12 + 0x40);
    *(undefined4 *)(this + 0x48) = *(undefined4 *)(iVar12 + 0x48);
    switch(*(undefined4 *)(this + 0x60)) {
    case 0:
      iVar12 = cRGalaxy::AIControl((cRGalaxy *)
                                   (this + *(int *)(this + 0x3210c0) * 0x8e6c + 0x3210c4));
      if (iVar12 == 1) {
        *(undefined4 *)(this + 0x332d9c) = 3;
        if (*(int *)(this + 0x3210c0) == 0) {
          *(undefined4 *)(*(int *)(iVar6 + iVar5) + 0xa4) = *(undefined4 *)(this + 100);
        }
        else if (*(int *)(this + 0x3210c0) == 1) {
          *(undefined4 *)(*(int *)(iVar6 + iVar5) + 0xec) = *(undefined4 *)(this + 100);
        }
      }
      else {
        if (iVar12 != 2) {
          if (iVar12 == 3) {
            UnInit(this);
            *(undefined4 *)(**(int **)(iVar6 + DAT_00083508) + 0x15c) = 2;
            goto LAB_000822f8;
          }
          break;
        }
        *(undefined4 *)(this + 0x332d9c) = 1;
        if (*(int *)(this + 0x3210c0) == 0) {
          *(undefined4 *)(*(int *)(iVar6 + iVar5) + 0xa4) = *(undefined4 *)(this + 100);
        }
        else if (*(int *)(this + 0x3210c0) == 1) {
          *(undefined4 *)(*(int *)(iVar6 + iVar5) + 0xec) = *(undefined4 *)(this + 100);
        }
      }
LAB_00083448:
      StartLevel(this,*(int *)(this + 100));
      goto LAB_000822f8;
    case 1:
      iVar5 = cRGUI::AI((cRGUI *)(this + 0x321078));
      if (iVar5 == 1) goto LAB_00083598;
      if (iVar5 == 3) {
        UnInit(this);
        *(undefined4 *)(**(int **)(iVar6 + DAT_00083508) + 0x15c) = 2;
        goto LAB_000822f8;
      }
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      iVar12 = cRGalaxy::AIControl((cRGalaxy *)
                                   (this + *(int *)(this + 0x3210c0) * 0x8e6c + 0x3210c4));
      if (iVar12 == 1) {
        iVar5 = *(int *)(iVar6 + iVar5);
        *(undefined4 *)(this + 0x332d9c) = 2;
        *(undefined4 *)(iVar5 + 0xa4) = *(undefined4 *)(this + 100);
        StartLevel(this,*(int *)(this + 100));
        goto LAB_000822f8;
      }
      if (iVar12 == 3) {
        UnInit(this);
        *(undefined4 *)(**(int **)(iVar6 + DAT_00083508) + 0x15c) = 2;
        goto LAB_000822f8;
      }
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
LAB_00083598:
      *(undefined4 *)(this + 0x332d9c) = 2;
      StartLevel(this,0);
      goto LAB_000822f8;
    }
    break;
  case 2:
    cRQuit::AI((cRQuit *)(this + 8));
    fVar20 = DAT_00083af4;
    fVar22 = extraout_s0;
    if (this[0x30fcc0] == (cRSubGame)0x0) {
      local_18c = DAT_000823e8;
      goto LAB_00082424;
    }
    local_18c = DAT_00083508;
    if (*(char *)(**(int **)(iVar6 + DAT_00083508) + 0x4d3dc) != '\0') goto LAB_00082424;
    iVar5 = *(int *)(this + 0x60);
    if (iVar5 == 3) {
      tColour::tColour((tColour *)&local_144,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      iVar5 = *(int *)(iVar6 + DAT_00083b00);
      fVar22 = (float)OSDPrintUV(0xd,0x44110000,0x40c00000,0x42800000,0x42800000,0x1000000,local_144
                                 ,uStack_140,uStack_13c,uStack_138,*(undefined4 *)(iVar5 + 0x1b0),
                                 fVar20 - *(float *)(iVar5 + 0x1bc),*(undefined4 *)(iVar5 + 0x1b8),
                                 fVar20 - *(float *)(iVar5 + 0x1b4),7,DAT_00083afc);
      goto LAB_00082424;
    }
    fVar20 = *(float *)(this + 0x34) + *(float *)(this + 0x38);
    uVar13 = in_fpscr & 0xfffffff;
    uVar19 = uVar13 | (uint)(fVar20 < DAT_0008353c) << 0x1f | (uint)(fVar20 == DAT_0008353c) << 0x1e
    ;
    in_fpscr = uVar19 | (uint)(NAN(fVar20) || NAN(DAT_0008353c)) << 0x1c;
    *(float *)(this + 0x34) = fVar20;
    bVar2 = (byte)(uVar19 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      in_fpscr = uVar13 | (uint)(fVar20 < DAT_0008352c) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        iVar12 = *(int *)(this + 0x30);
      }
      else {
        uVar13 = uVar13 | (uint)(fVar20 < DAT_00083530) << 0x1f |
                 (uint)(fVar20 == DAT_00083530) << 0x1e;
        in_fpscr = uVar13 | (uint)(NAN(fVar20) || NAN(DAT_00083530)) << 0x1c;
        bVar2 = (byte)(uVar13 >> 0x18);
        if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
          iVar12 = *(int *)(this + 0x30);
        }
        else {
          iVar12 = *(int *)(this + 0x30);
        }
      }
    }
    else {
      *(undefined4 *)(this + 0x34) = DAT_00083524;
      iVar12 = *(int *)(this + 0x30) + 1;
      *(int *)(this + 0x30) = iVar12;
    }
    fVar20 = extraout_s0;
    fVar22 = extraout_s1;
    fVar23 = extraout_s2;
    fVar21 = extraout_s3;
    switch(iVar12) {
    case 0:
      goto LAB_000836cc;
    case 1:
      sprintf((char *)&local_134,(char *)(iVar6 + DAT_00083510),*(int *)(this + 0x30fcc4) + 0x54);
      fVar20 = extraout_s0_07;
      fVar22 = extraout_s1_01;
      fVar23 = extraout_s2_01;
      fVar21 = extraout_s3_01;
      break;
    case 2:
      if (iVar5 == 4) {
        *(undefined4 *)(this + 0x30) = 0;
        local_134 = local_134 & 0xffffff00;
      }
      else {
        sprintf((char *)&local_134,(char *)(iVar6 + DAT_00083520),
                *(undefined4 *)(*(int *)(this + 0x30fcc4) + 0x50));
        fVar20 = extraout_s0_09;
        fVar22 = extraout_s1_02;
        fVar23 = extraout_s2_02;
        fVar21 = extraout_s3_02;
      }
      break;
    case 3:
      sprintf((char *)&local_134,(char *)(iVar6 + DAT_0008350c),
              *(undefined4 *)(*(int *)(this + 0x30fcc4) + 0x4c));
      fVar20 = extraout_s0_06;
      fVar22 = extraout_s1_00;
      fVar23 = extraout_s2_00;
      fVar21 = extraout_s3_00;
      break;
    case 4:
LAB_000836cc:
      *(undefined4 *)(this + 0x30) = 0;
      if (iVar5 == 4) {
        puVar17 = (uint *)(iVar6 + DAT_00083b04);
        local_134 = *puVar17;
        uStack_130 = puVar17[1];
        uStack_12c = puVar17[2];
        uStack_128 = puVar17[3];
        local_124 = (undefined2)puVar17[4];
        local_122 = (undefined1)(puVar17[4] >> 0x10);
      }
      else {
        puVar17 = (uint *)(iVar6 + DAT_00083514);
        local_134 = *puVar17;
        uStack_130 = puVar17[1];
        uStack_12c = puVar17[2];
        uStack_128 = puVar17[3];
        local_124 = (undefined2)puVar17[4];
      }
    }
    tColour::tColour((tColour *)&local_154,fVar20,fVar22,fVar23,fVar21);
    fVar22 = (float)FontType(&local_134,0,0x3f800000,0x41a00000,DAT_00083528,0,0,0,0,DAT_00083524,0,
                             0,DAT_00083524,0x1000000,local_154,uStack_150,uStack_14c,uStack_148,0,0
                            );
LAB_00082424:
    if ((this[0xfefc] == (cRSubGame)0x0) && (*(int *)(this + 0xfbcc) != 2)) {
      cRTime::Add((cRTime *)(this + 0xfd94),fVar22);
    }
    if (*(int *)(this + 0x60) == 7) {
      cRTutorial::AI((cRTutorial *)(this + 0x84));
    }
    cRSlugVoiceManager::AI((cRSlugVoiceManager *)(this + 0x8c4c));
    if (this[0x18] != (cRSubGame)0x0) {
      this[0x19] = (cRSubGame)0x0;
      this[0x18] = (cRSubGame)0x0;
      cRSpriteManager::Pause(*(cRSpriteManager **)(iVar6 + DAT_00083518),false);
    }
    if (this[0x30fcc0] == (cRSubGame)0x0) {
LAB_000824c4:
      if (*(char *)(**(int **)(iVar6 + local_18c) + 0x4d3dc) != '\0') goto LAB_000824e8;
    }
    else {
      if (*(int *)(this + 0x3345bc) == 4) {
        iVar5 = **(int **)(iVar6 + local_18c);
        if (*(int *)(iVar5 + 0x24) == 0) {
          fVar20 = *(float *)(this + 0x3345f8) + *(float *)(this + 0x3345fc);
          uVar13 = in_fpscr & 0xfffffff | (uint)(fVar20 < DAT_0008353c) << 0x1f |
                   (uint)(fVar20 == DAT_0008353c) << 0x1e;
          in_fpscr = uVar13 | (uint)(NAN(fVar20) || NAN(DAT_0008353c)) << 0x1c;
          *(float *)(this + 0x3345f8) = fVar20;
          bVar2 = (byte)(uVar13 >> 0x18);
          if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
            this[0x10] = (cRSubGame)0x1;
            cRFade::Start((cRFade *)(iVar5 + 0x24),(_func_void *)0x0);
          }
          goto LAB_000824a0;
        }
      }
      else {
LAB_000824a0:
        if (this[0x30fcc0] == (cRSubGame)0x0) goto LAB_000824c4;
      }
      in_fpscr = in_fpscr & 0xfffffff | (uint)(*(float *)(this + 0x1c) == 0.0) << 0x1e;
      if ((!SUB41(in_fpscr >> 0x1e,0)) || ((*(uint *)(*(int *)(this + 0xfef8) + 4) & 0x4000) == 0))
      goto LAB_000824c4;
LAB_000824e8:
      iVar5 = **(int **)(iVar6 + local_18c);
      if (*(int *)(iVar5 + 0x24) == 0) {
        this[0x10] = (cRSubGame)0x1;
        cRFade::Start((cRFade *)(iVar5 + 0x24),(_func_void *)0x0);
      }
    }
    fVar20 = DAT_0008353c;
    if ((this[0x10] != (cRSubGame)0x0) &&
       (iVar5 = **(int **)(iVar6 + local_18c), *(int *)(iVar5 + 0x24) == 4)) {
      if (this[0x30fcc1] == (cRSubGame)0x0) {
        *(undefined4 *)(iVar5 + 0x160) = *(undefined4 *)(iVar5 + 0x15c);
        *(undefined4 *)(iVar5 + 0x15c) = 0x1b;
      }
      else {
        uVar8 = *(undefined4 *)(iVar5 + 0x15c);
        *(undefined4 *)(iVar5 + 0x15c) = 0x1a;
        *(undefined4 *)(iVar5 + 0x160) = uVar8;
      }
      if (*(float *)(**(int **)(iVar6 + local_18c) + 0x4d3e0) <= fVar20) {
        *(undefined1 *)(**(int **)(iVar6 + local_18c) + 0x4d3dc) = 0;
      }
      goto LAB_000822f8;
    }
    iVar5 = RShellInkey();
    if ((iVar5 == 0xb) && (*(int *)(**(int **)(iVar6 + local_18c) + 0x24) == 0)) {
      this[0x19] = (cRSubGame)0x1;
      *(undefined4 *)(this + 0x5c) = 3;
      cRSpriteManager::Pause(*(cRSpriteManager **)(iVar6 + DAT_00083518),true);
      if (*(int *)(this + 0xfbcc) == 2) {
        cRBorder::HideInit(*(cRBorder **)(this + 0xfbd0));
      }
      goto LAB_000822f8;
    }
    fVar22 = *(float *)(this + 0x1c);
    uVar13 = in_fpscr & 0xfffffff | (uint)(fVar22 < 0.0) << 0x1f | (uint)(fVar22 == 0.0) << 0x1e;
    uVar19 = uVar13 | (uint)NAN(fVar22) << 0x1c;
    bVar2 = (byte)(uVar13 >> 0x18);
    fVar20 = extraout_s0_00;
    if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) {
      fVar22 = fVar22 + *(float *)(this + 0x20);
      uVar13 = in_fpscr & 0xfffffff | (uint)(fVar22 < DAT_000823f8) << 0x1f |
               (uint)(fVar22 == DAT_000823f8) << 0x1e;
      uVar19 = uVar13 | (uint)(NAN(fVar22) || NAN(DAT_000823f8)) << 0x1c;
      *(float *)(this + 0x1c) = fVar22;
      bVar2 = (byte)(uVar13 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) {
        *(undefined4 *)(this + 0x1c) = DAT_000823fc;
      }
      if (*(int *)(this + 0xfbcc) == 2) {
        fVar20 = (float)cRBorder::UnHideInit(*(cRBorder **)(this + 0xfbd0));
      }
    }
    if (*this == (cRSubGame)0x0) {
      iVar12 = *(int *)(this + 0x60);
      iVar5 = *(int *)(this + 0x40);
      *(int *)(this + 0x3c) = iVar5;
      if (iVar12 == 2) goto LAB_00083790;
      iVar7 = (int)*(float *)(this + 0x122c0) + 0x30;
      if (iVar5 < iVar7) {
        *(int *)(this + 0x40) = iVar7;
        iVar5 = iVar7;
      }
    }
    else {
      iVar12 = *(int *)(this + 0x60);
      *(undefined4 *)(this + 0x3c) = 0;
      if (iVar12 == 2) {
LAB_00083790:
        *(int *)(this + 0x40) = *(int *)(this + 0x74);
        iVar5 = *(int *)(this + 0x74);
      }
      else {
        *(int *)(this + 0x40) = (int)*(float *)(this + 0x122c0) + 0x30;
        iVar5 = (int)*(float *)(this + 0x122c0) + 0x30;
      }
    }
    iVar14 = *(int *)(this + 0x3c);
    iVar7 = *(int *)(this + 0x78) + 0x28;
    if (iVar7 < iVar5) {
      *(int *)(this + 0x40) = iVar7;
      iVar5 = iVar7;
    }
    if (iVar14 < iVar5) {
      pcVar16 = this + iVar14 * 0xdc + 0x20df90;
      pcVar18 = (cRSubGoldy *)(this + 0xfac4);
      local_19c = iVar14 + 6;
      do {
        uVar13 = *(uint *)(pcVar16 + -0xb4);
        if ((uVar13 & 2) != 0) {
          fVar20 = (float)cLinkedList<cRBod>::AddAfter
                                    ((cLinkedList<cRBod> *)(**(int **)(iVar6 + local_18c) + 0x358),
                                     (cRBod *)(this + iVar14 * 0xdc + 0x20dee0),
                                     (cRBod *)(**(int **)(iVar6 + local_18c) + 0x7456c));
          **(uint **)(pcVar16 + -0x8c) = **(uint **)(pcVar16 + -0x8c) | 0x80000000;
          uVar13 = *(uint *)(pcVar16 + -0xb4);
        }
        if (((uVar13 & 0x10) != 0) && ((*(uint *)(this + 0x6c) & 0x800000) != 0)) {
          fVar20 = (float)AddParcel((tVector *)this,(cRSubGoldy *)(this + iVar14 * 0xdc + 0x20df60))
          ;
        }
        pcVar15 = this + iVar14 * 0x240 + 0x13b54;
        iVar5 = 0;
        do {
          if (((-1 < iVar14) && (iVar14 < *(int *)(this + 0x74))) &&
             ((*(uint *)(pcVar15 + -0x74) & 0x200) == 0)) {
            iVar12 = iVar14 * 0x240 + iVar5 * 0x48;
            if (((byte)this[iVar12 + 0x13b11] & 0x40) != 0) {
              if ((byte)((char)pcVar15[-0x48] - 0x1dU) < 2) {
                if (*(int *)(pcVar15 + -0x54) != 0) {
                  piVar10 = *(int **)(iVar6 + local_18c);
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(*piVar10 + 0x358),
                             (cRBod *)(this + iVar12 + 0x13adc),(cRBod *)(this + 0x2d7c));
                  fVar20 = (float)VectorSignedToFloat(iVar14 % 8,(byte)(uVar19 >> 0x16) & 3);
                  *(float *)(pcVar15 + -0x58) = fVar20 * DAT_00082cdc;
                  GetSkirtColour((tColourSmall *)this);
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(*piVar10 + 0x358),
                             (cRBod *)(this + iVar14 * 0xdc + 0x20df80),(cRBod *)(this + 0x2bf0));
                  uVar8 = *(undefined4 *)(pcVar15 + -100);
                  uVar11 = *(undefined4 *)(pcVar15 + -0x60);
                  *(undefined4 *)pcVar16 = *(undefined4 *)(pcVar15 + -0x68);
                  *(undefined4 *)(pcVar16 + 4) = uVar8;
                  *(undefined4 *)(pcVar16 + 8) = uVar11;
                }
              }
              else if (pcVar15[-0x48] == (cRSubGame)0xe) {
                cLinkedList<cRBod>::AddBefore
                          ((cLinkedList<cRBod> *)(**(int **)(iVar6 + local_18c) + 0x358),
                           (cRBod *)(this + iVar12 + 0x13adc),(cRBod *)(this + 0x2c48));
              }
              else {
                this_00 = (cRSubLoc *)(this + iVar12 + 0x13adc);
                iVar12 = cRSubLoc::IsRamp(this_00);
                if (iVar12 == 0) {
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(**(int **)(iVar6 + local_18c) + 0x358),
                             (cRBod *)this_00,(cRBod *)(this + 0x2c1c));
                }
                else {
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(**(int **)(iVar6 + local_18c) + 0x358),
                             (cRBod *)this_00,(cRBod *)(this + 0x2c74));
                }
              }
              fVar20 = (float)(*(code *)**(undefined4 **)(pcVar15 + -0x78))
                                        (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc);
            }
            cVar9 = pcVar15[-0x48];
            if (cVar9 == (cRSubGame)0x17) {
              if ((((*(uint *)(this + 0x6c) & 0x800) != 0) && (*(int *)(this + 0x70) <= iVar14)) &&
                 (iVar14 < *(int *)(this + 0x78))) {
                fVar20 = (float)AddHealth(this,(cRSubLoc *)
                                               (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc),
                                          pcVar18);
                cVar9 = pcVar15[-0x48];
                goto LAB_00082810;
              }
LAB_00082838:
              pcVar4 = DAT_00082ce0;
              if (((((byte)this[iVar14 * 0x240 + iVar5 * 0x48 + 0x13b10] & 0x10) == 0) &&
                  (cVar9 == (cRSubGame)0x1 || cVar9 == (cRSubGame)0x15)) &&
                 ((*(uint *)(this + 0x6c) & 2) != 0)) {
                fVar20 = (float)RAND(fVar20,DAT_00082ce0);
                fVar22 = DAT_00082ce4 + ((float)pcVar4 - *(float *)(this + 0x321070)) * DAT_00082ce8
                ;
                uVar13 = uVar19 & 0xfffffff | (uint)(fVar20 < fVar22) << 0x1f |
                         (uint)(fVar20 == fVar22) << 0x1e;
                uVar19 = uVar13 | (uint)(NAN(fVar20) || NAN(fVar22)) << 0x1c;
                bVar2 = (byte)(uVar13 >> 0x18);
                fVar20 = extraout_s0_02;
                if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) {
                  if (iVar5 == 0) {
LAB_00083028:
                    cVar9 = *pcVar15;
                    if (((cVar9 != (cRSubGame)0x1) && (cVar9 != (cRSubGame)0x14)) &&
                       ((cVar9 != (cRSubGame)0x15 && (cVar9 != (cRSubGame)0x20)))) {
                      cVar9 = pcVar15[-0x48];
                      goto LAB_00082878;
                    }
                  }
                  else {
                    cVar9 = pcVar15[-0x90];
                    if (((cVar9 != (cRSubGame)0x1) && (cVar9 != (cRSubGame)0x14)) &&
                       ((cVar9 != (cRSubGame)0x15 && (cVar9 != (cRSubGame)0x20))))
                    goto LAB_00082fa0;
                    if (iVar5 != 7) goto LAB_00083028;
                  }
                  if (((*(int *)(this + 0x70) <= iVar14) && (iVar14 < *(int *)(this + 0x78))) &&
                     (*(int *)(this + 0xfbcc) != 2)) {
                    iVar12 = *(int *)(this + 0x60);
                    if (iVar12 == 4) {
                      fVar20 = (float)RAND(extraout_s0_02,(char *)0x3f800000);
                      fVar22 = DAT_00083534 + DAT_00083538 * *(float *)(this + 0x68);
                      uVar13 = uVar19 & 0xfffffff | (uint)(fVar20 < fVar22) << 0x1f |
                               (uint)(fVar20 == fVar22) << 0x1e;
                      uVar19 = uVar13 | (uint)(NAN(fVar20) || NAN(fVar22)) << 0x1c;
                      bVar2 = (byte)(uVar13 >> 0x18);
                      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) {
                        cVar9 = pcVar15[-0x48];
                        fVar20 = extraout_s0_08;
                        goto LAB_00082878;
                      }
                      iVar12 = *(int *)(this + 0x60);
                      fVar20 = extraout_s0_08;
                    }
                    if (iVar12 == 0) {
                      fVar20 = (float)RAND(fVar20,(char *)0x3f800000);
                      fVar22 = DAT_00082cec + DAT_00082cf0 * *(float *)(this + 0x68);
                      uVar13 = uVar19 & 0xfffffff | (uint)(fVar20 < fVar22) << 0x1f |
                               (uint)(fVar20 == fVar22) << 0x1e;
                      uVar19 = uVar13 | (uint)(NAN(fVar20) || NAN(fVar22)) << 0x1c;
                      bVar2 = (byte)(uVar13 >> 0x18);
                      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) {
                        cVar9 = pcVar15[-0x48];
                        fVar20 = extraout_s0_03;
                        goto LAB_00082878;
                      }
                    }
                    goto LAB_00082b74;
                  }
                }
LAB_00082fa0:
                cVar9 = pcVar15[-0x48];
              }
LAB_00082878:
              if (cVar9 == (cRSubGame)0x22) goto LAB_00082ba8;
LAB_00082880:
              pcVar4 = DAT_00082ce0;
              iVar12 = iVar14 * 0x240 + iVar5 * 0x48;
              if (((((byte)this[iVar12 + 0x13b10] & 8) != 0) ||
                  (cVar9 != (cRSubGame)0x1 && cVar9 != (cRSubGame)0xf)) ||
                 (*(int *)(this + 0xfbcc) == 2)) goto LAB_00082b38;
              uVar13 = *(uint *)(this + 0x6c);
              if ((uVar13 & 0x10000) != 0) {
                fVar20 = (float)RAND(fVar20,DAT_00082ce0);
                fVar22 = DAT_00082ccc + ((float)pcVar4 - *(float *)(this + 0x321074)) * DAT_00082cd0
                ;
                uVar13 = uVar19 & 0xfffffff | (uint)(fVar20 < fVar22) << 0x1f |
                         (uint)(fVar20 == fVar22) << 0x1e;
                uVar19 = uVar13 | (uint)(NAN(fVar20) || NAN(fVar22)) << 0x1c;
                bVar2 = (byte)(uVar13 >> 0x18);
                fVar20 = extraout_s0_01;
                if (((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) &&
                    (*(int *)(this + 0x70) <= iVar14)) && (iVar14 < *(int *)(this + 0x78))) {
                  fVar20 = (float)cRSaltManager::Add((cRSaltManager *)(this + 0x4e78),
                                                     (tVector *)(this + iVar12 + 0x13aec));
                }
                goto LAB_00082b38;
              }
            }
            else {
LAB_00082810:
              if (cVar9 == (cRSubGame)0x18) {
                if ((iVar14 < *(int *)(this + 0x70)) || (*(int *)(this + 0x78) <= iVar14))
                goto LAB_00082838;
                fVar20 = (float)AddSpeedUp((cRSubLoc *)this,
                                           (cRSubGoldy *)
                                           (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc));
                cVar9 = pcVar15[-0x48];
              }
              if (cVar9 == (cRSubGame)0x19) {
                if ((iVar14 < *(int *)(this + 0x70)) || (*(int *)(this + 0x78) <= iVar14))
                goto LAB_00082838;
                fVar20 = (float)AddJetPack(this,(cRSubLoc *)
                                                (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc),
                                           pcVar18);
                cVar9 = pcVar15[-0x48];
              }
              if (cVar9 != (cRSubGame)0x21) goto LAB_00082838;
LAB_00082b74:
              fVar20 = (float)AddGarbage((cRSubLoc *)this,
                                         (cRSubGoldy *)
                                         (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc));
              cVar9 = pcVar15[-0x48];
              if (cVar9 != (cRSubGame)0x22) goto LAB_00082880;
LAB_00082ba8:
              if ((*(int *)(this + 0x70) <= iVar14) && (iVar14 < *(int *)(this + 0x78))) {
                fVar20 = (float)cRSaltManager::Add((cRSaltManager *)(this + 0x4e78),
                                                   (tVector *)
                                                   (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13aec))
                ;
                uVar13 = *(uint *)(this + 0x6c);
                goto LAB_000828d0;
              }
LAB_00082b38:
              uVar13 = *(uint *)(this + 0x6c);
            }
LAB_000828d0:
            if ((((uVar13 & 0x80) != 0) && (pcVar15[-0x48] == (cRSubGame)0x12)) &&
               ((*(int *)(this + 0x70) <= iVar14 && (iVar14 < *(int *)(this + 0x78))))) {
              fVar20 = (float)AddSlug(this,(cRSubLoc *)
                                           (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc),pcVar18)
              ;
            }
            uVar13 = *(uint *)(pcVar16 + -0xb4);
            if ((uVar13 & 0x200) == 0) {
              cVar9 = pcVar15[-0x48];
              if (cVar9 == (cRSubGame)0x23) {
                if ((uVar13 & 0x400) == 0) {
                  if ((uVar13 & 0x2000) == 0) {
                    if ((uVar13 & 0x800) == 0) {
                      if ((uVar13 & 0x1000) != 0) {
                        fVar20 = (float)AddRing(this,(cRSubLoc *)
                                                     (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc
                                                     ),7,pcVar18,fVar20);
                        *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + -0x60);
                      }
                    }
                    else {
                      fVar20 = (float)AddRing(this,(cRSubLoc *)
                                                   (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc),
                                              6,pcVar18,fVar20);
                      *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + -0x60);
                    }
                  }
                  else {
                    fVar20 = (float)AddRing(this,(cRSubLoc *)
                                                 (this + iVar5 * 0x48 + iVar14 * 0x240 + 0x13adc),8,
                                            pcVar18,fVar20);
                    *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + -0x60);
                  }
                }
                else {
                  iVar7 = 5;
                  iVar12 = iVar14 * 0x240 + iVar5 * 0x48;
LAB_0008307c:
                  fVar20 = (float)AddRing(this,(cRSubLoc *)(this + iVar12 + 0x13adc),iVar7,pcVar18,
                                          fVar20);
                  *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + -0x60);
                }
              }
              else {
                if ((byte)((char)cVar9 - 2U) < 6) {
                  fVar23 = DAT_00082cc8 + *(float *)(this + 0xfe30);
                  fVar22 = *(float *)(pcVar15 + -0x60);
                  uVar1 = uVar19 & 0xfffffff | (uint)(fVar22 < fVar23) << 0x1f |
                          (uint)(fVar22 == fVar23) << 0x1e;
                  uVar19 = uVar1 | (uint)(NAN(fVar22) || NAN(fVar23)) << 0x1c;
                  bVar2 = (byte)(uVar1 >> 0x18);
                  if ((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) &&
                     (iVar14 < *(int *)(this + 0x78))) {
                    if ((uVar13 & 0x2000) == 0) {
                      if ((uVar13 & 0x800) == 0) {
                        if ((uVar13 & 0x1000) == 0) {
                          if ((*(uint *)(this + 0x6c) & 8) != 0) {
                            fVar20 = (float)RAND(fVar20,(char *)0x3f800000);
                            uVar13 = uVar19 & 0xfffffff | (uint)(fVar20 < DAT_000834fc) << 0x1f |
                                     (uint)(fVar20 == DAT_000834fc) << 0x1e;
                            uVar19 = uVar13 | (uint)(NAN(fVar20) || NAN(DAT_000834fc)) << 0x1c;
                            bVar2 = (byte)(uVar13 >> 0x18);
                            fVar20 = extraout_s0_05;
                            if (((!(bool)(bVar2 >> 6 & 1) &&
                                  bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) ||
                                (*(int *)(this + 0x60) == 7)) &&
                               (2 < (byte)((char)pcVar15[-0x48] - 5U))) {
                              fVar20 = (float)AddRing(this,(cRSubLoc *)
                                                           (this + iVar5 * 0x48 + iVar14 * 0x240 +
                                                                   0x13adc),4,pcVar18,extraout_s0_05
                                                     );
                              if (*(int *)(this + 0xfec0) < 8) {
                                *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + -0x60);
                              }
                              else {
                                *(float *)(this + 0xfe30) =
                                     *(float *)(pcVar15 + -0x60) + DAT_00083500;
                              }
                            }
                          }
                        }
                        else {
                          fVar20 = (float)AddRing(this,(cRSubLoc *)
                                                       (this + iVar5 * 0x48 + local_19c * 0x240 +
                                                               0x13adc),7,pcVar18,fVar20);
                          *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + 0xd20);
                        }
                        goto LAB_00082960;
                      }
                      iVar12 = 6;
                    }
                    else {
                      iVar12 = 8;
                    }
                    fVar20 = (float)AddRing(this,(cRSubLoc *)
                                                 (this + local_19c * 0x240 + iVar5 * 0x48 + 0x13adc)
                                            ,iVar12,pcVar18,fVar20);
                    *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + 0xd20);
                    goto LAB_00082960;
                  }
                }
                if ((byte)((char)cVar9 - 8U) < 3) {
                  fVar23 = DAT_00082cc8 + *(float *)(this + 0xfe30);
                  fVar22 = *(float *)(pcVar15 + -0x60);
                  uVar1 = uVar19 & 0xfffffff | (uint)(fVar22 < fVar23) << 0x1f |
                          (uint)(fVar22 == fVar23) << 0x1e;
                  uVar19 = uVar1 | (uint)(NAN(fVar22) || NAN(fVar23)) << 0x1c;
                  bVar2 = (byte)(uVar1 >> 0x18);
                  if ((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) &&
                     (iVar14 < *(int *)(this + 0x78))) {
                    if ((uVar13 & 0x800) == 0) {
                      fVar20 = (float)RAND(fVar20,(char *)0x3f800000);
                      uVar13 = uVar19 & 0xfffffff | (uint)(fVar20 < DAT_000834fc) << 0x1f |
                               (uint)(fVar20 == DAT_000834fc) << 0x1e;
                      uVar19 = uVar13 | (uint)(NAN(fVar20) || NAN(DAT_000834fc)) << 0x1c;
                      bVar2 = (byte)(uVar13 >> 0x18);
                      fVar20 = extraout_s0_04;
                      if (((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar19 >> 0x1c) & 1))
                          || (*(int *)(this + 0x60) == 7)) ||
                         ((*(uint *)(pcVar16 + -0xb4) & 0x800) != 0)) {
                        iVar7 = 2;
                        iVar12 = iVar5 * 0x48 + iVar14 * 0x240;
                        goto LAB_0008307c;
                      }
                    }
                    else {
                      fVar20 = (float)AddRing(this,(cRSubLoc *)
                                                   (this + iVar14 * 0x240 + iVar5 * 0x48 + 0x13adc),
                                              2,pcVar18,fVar20);
                      *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar15 + -0x60);
                    }
                  }
                }
              }
            }
          }
LAB_00082960:
          iVar5 = iVar5 + 1;
          pcVar15 = pcVar15 + 0x48;
        } while (iVar5 != 8);
        iVar5 = *(int *)(this + 0x7c);
        while (iVar5 <= iVar14) {
          if (*(int *)(this + 0x60) != 2) {
            fVar20 = (float)cRWorld::Add((cRWorld *)(this + 0xf9f0),
                                         (cRSubLoc *)(this + iVar5 * 0x240 + 0x13adc));
            iVar5 = *(int *)(this + 0x7c);
          }
          iVar5 = iVar5 + 1;
          *(int *)(this + 0x7c) = iVar5;
        }
        iVar14 = iVar14 + 1;
        pcVar16 = pcVar16 + 0xdc;
        local_19c = local_19c + 1;
        *this = (cRSubGame)0x0;
      } while (iVar14 < *(int *)(this + 0x40));
      iVar12 = *(int *)(this + 0x60);
    }
    if (iVar12 == 4) {
      iVar5 = *(int *)(this + 0x8c58);
      pcVar4 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(this + 0x30fcd0),(cRTime *)(this + 0xfd94));
      Rstrcpy((char *)(iVar5 + 0x2c4),pcVar4);
      iVar5 = (*(int *)(this + 100) + 0x16) * 0x38;
      if (*(int *)(this + iVar5 + 0x2cf4a4) == 1) {
        iVar12 = *(int *)(this + 0x8c5c);
        pcVar4 = (char *)cRTimeTrial::TimeString
                                   ((cRTimeTrial *)(this + 0x30fcd0),
                                    (cRTime *)(this + iVar5 + 0x2cf4a8));
        Rstrcpy((char *)(iVar12 + 0x2c4),pcVar4);
      }
      else {
        cRBorder::HideInit(*(cRBorder **)(this + 0x8c5c));
      }
    }
    else {
      *(undefined1 *)(*(int *)(this + 0x8c58) + 0x2c4) = 0;
      cRBorder::AddTextNumber(*(int *)(this + 0x8c58));
      if (*(int *)(this + 0x2e2c) < *(int *)(this + 0xfd90)) {
        *(int *)(this + 0x2e2c) = *(int *)(this + 0xfd90);
        *(undefined1 *)(*(int *)(this + 0x8c5c) + 0x2c4) = 0;
        cRBorder::AddTextNumber(*(int *)(this + 0x8c5c));
      }
    }
    break;
  case 3:
    *(undefined4 *)(this + 0x5c) = 4;
    *(undefined4 *)(this + 0x1c) = *(undefined4 *)(this + 0x20);
    this[0x19] = (cRSubGame)0x1;
    cRSubPause::Init((cRSubPause *)(this + 0x24));
    goto LAB_00082a40;
  case 4:
LAB_00082a40:
    cRSubPause::AI((cRSubPause *)(this + 0x24));
    goto LAB_000822f8;
  case 5:
    break;
  case 6:
    break;
  case 7:
    if (this[0x30fcc1] == (cRSubGame)0x0) {
      this[0x30fcc0] = (cRSubGame)0x0;
      StartLevel(this,0);
      *(undefined4 *)(this + 0x5c) = 2;
      *(undefined4 *)(**(int **)(iVar6 + DAT_00083508) + 0x328) = 1;
    }
    else {
      this[0x30fcc0] = (cRSubGame)0x1;
      StartLevel(this,0);
      *(undefined4 *)(this + 0x5c) = 2;
      *(undefined4 *)(**(int **)(iVar6 + DAT_00082cd4) + 0x328) = 1;
    }
    goto LAB_000822f8;
  }
  CameraAI(this);
LAB_000822f8:
  if (local_34 != **(int **)(iVar6 + iVar3)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
