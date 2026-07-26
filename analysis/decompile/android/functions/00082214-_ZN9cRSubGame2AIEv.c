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
  char *pcVar3;
  cRFade *this_00;
  int iVar4;
  int iVar5;
  cRSubLoc *this_01;
  undefined4 uVar6;
  cRSubGame cVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  cRSubGame *pcVar12;
  cRSubGame *pcVar13;
  cRSubGoldy *pcVar14;
  uint in_fpscr;
  uint uVar15;
  float fVar16;
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
  float fVar17;
  float extraout_s3_01;
  float extraout_s3_02;
  float fVar18;
  float fVar19;
  int local_19c;
  undefined4 local_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 local_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  uint local_134;
  char acStack_130 [4];
  char acStack_12c [4];
  char acStack_128 [4];
  char local_124 [2];
  undefined1 local_122;
  int local_34;

  if (0 < *(int *)(this + 0x14)) {
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + -1;
  }
  local_34 = __stack_chk_guard;
  fVar16 = (float)CalcRate();
  switch(*(undefined4 *)(this + 0x5c)) {
  case 0:
    *(undefined4 *)(this + 0x5c) = 1;
    iVar4 = *(int *)(this + 0x332d9c);
    if (iVar4 != 1) {
      if (iVar4 != 0 && iVar4 != 3) {
        if (this[0x30fcc1] != (cRSubGame)0x0) {
          this[0x30fcc0] = (cRSubGame)0x1;
          StartLevel(this,*(int *)(*(int *)(this + 0x30fcc4) + 0x28));
          goto LAB_000822f8;
        }
        this[0x30fcc0] = (cRSubGame)0x0;
        fVar16 = (float)cRStarManager::Hide((cRStarManager *)(Game + 0x4d440));
        goto LAB_00082384;
      }
      goto LAB_00083448;
    }
    break;
  case 1:
LAB_00082384:
    RAND(fVar16,(char *)0x3f800000);
    *(undefined4 *)(this + 0x44) = gConfig._64_4_;
    *(undefined4 *)(this + 0x48) = gConfig._72_4_;
    switch(*(undefined4 *)(this + 0x60)) {
    case 0:
      iVar4 = cRGalaxy::AIControl((cRGalaxy *)(this + *(int *)(this + 0x3210c0) * 0x8e6c + 0x3210c4)
                                 );
      if (iVar4 == 1) {
        *(undefined4 *)(this + 0x332d9c) = 3;
        if (*(int *)(this + 0x3210c0) == 0) {
          gConfig._164_4_ = *(undefined4 *)(this + 100);
        }
        else if (*(int *)(this + 0x3210c0) == 1) {
          gConfig._236_4_ = *(undefined4 *)(this + 100);
        }
      }
      else {
        if (iVar4 != 2) {
          if (iVar4 == 3) {
            UnInit(this);
            *(undefined4 *)(Game + 0x15c) = 2;
            goto LAB_000822f8;
          }
          break;
        }
        *(undefined4 *)(this + 0x332d9c) = 1;
        if (*(int *)(this + 0x3210c0) == 0) {
          gConfig._164_4_ = *(undefined4 *)(this + 100);
        }
        else if (*(int *)(this + 0x3210c0) == 1) {
          gConfig._236_4_ = *(undefined4 *)(this + 100);
        }
      }
LAB_00083448:
      StartLevel(this,*(int *)(this + 100));
      goto LAB_000822f8;
    case 1:
      iVar4 = cRGUI::AI((cRGUI *)(this + 0x321078));
      if (iVar4 == 1) goto LAB_00083598;
      if (iVar4 == 3) {
        UnInit(this);
        *(undefined4 *)(Game + 0x15c) = 2;
        goto LAB_000822f8;
      }
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      iVar4 = cRGalaxy::AIControl((cRGalaxy *)(this + *(int *)(this + 0x3210c0) * 0x8e6c + 0x3210c4)
                                 );
      if (iVar4 == 1) {
        gConfig._164_4_ = *(undefined4 *)(this + 100);
        *(undefined4 *)(this + 0x332d9c) = 2;
        StartLevel(this,*(int *)(this + 100));
        goto LAB_000822f8;
      }
      if (iVar4 == 3) {
        UnInit(this);
        *(undefined4 *)(Game + 0x15c) = 2;
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
    fVar16 = extraout_s0;
    if ((this[0x30fcc0] == (cRSubGame)0x0) || (*(char *)(Game + 0x4d3dc) != '\0'))
    goto LAB_00082424;
    iVar4 = *(int *)(this + 0x60);
    if (iVar4 == 3) {
      tColour::tColour((tColour *)&local_144,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      fVar16 = (float)OSDPrintUV(0xd,0x44110000,0x40c00000,0x42800000,0x42800000,0x1000000,local_144
                                 ,uStack_140,uStack_13c,uStack_138,gSpriteReference._432_4_,
                                 1.0 - (float)gSpriteReference._444_4_,gSpriteReference._440_4_,
                                 1.0 - (float)gSpriteReference._436_4_,7,0);
      goto LAB_00082424;
    }
    fVar16 = *(float *)(this + 0x34) + *(float *)(this + 0x38);
    uVar10 = in_fpscr & 0xfffffff;
    uVar15 = uVar10 | (uint)(fVar16 < 1.0) << 0x1f | (uint)(fVar16 == 1.0) << 0x1e;
    in_fpscr = uVar15 | (uint)NAN(fVar16) << 0x1c;
    *(float *)(this + 0x34) = fVar16;
    bVar2 = (byte)(uVar15 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      in_fpscr = uVar10 | (uint)(fVar16 < 0.2) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        iVar9 = *(int *)(this + 0x30);
      }
      else {
        uVar10 = uVar10 | (uint)(fVar16 < 0.8) << 0x1f | (uint)(fVar16 == 0.8) << 0x1e;
        in_fpscr = uVar10 | (uint)NAN(fVar16) << 0x1c;
        bVar2 = (byte)(uVar10 >> 0x18);
        if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
          iVar9 = *(int *)(this + 0x30);
        }
        else {
          iVar9 = *(int *)(this + 0x30);
        }
      }
    }
    else {
      *(undefined4 *)(this + 0x34) = 0;
      iVar9 = *(int *)(this + 0x30) + 1;
      *(int *)(this + 0x30) = iVar9;
    }
    fVar16 = extraout_s0;
    fVar18 = extraout_s1;
    fVar19 = extraout_s2;
    fVar17 = extraout_s3;
    switch(iVar9) {
    case 0:
      goto LAB_000836cc;
    case 1:
      sprintf((char *)&local_134,"Player: %s",*(int *)(this + 0x30fcc4) + 0x54);
      fVar16 = extraout_s0_07;
      fVar18 = extraout_s1_01;
      fVar19 = extraout_s2_01;
      fVar17 = extraout_s3_01;
      break;
    case 2:
      if (iVar4 == 4) {
        *(undefined4 *)(this + 0x30) = 0;
        local_134 = local_134 & 0xffffff00;
      }
      else {
        sprintf((char *)&local_134,"Difficulty: %i%%",
                *(undefined4 *)(*(int *)(this + 0x30fcc4) + 0x50));
        fVar16 = extraout_s0_09;
        fVar18 = extraout_s1_02;
        fVar19 = extraout_s2_02;
        fVar17 = extraout_s3_02;
      }
      break;
    case 3:
      sprintf((char *)&local_134,"Speed: %i%%",*(undefined4 *)(*(int *)(this + 0x30fcc4) + 0x4c));
      fVar16 = extraout_s0_06;
      fVar18 = extraout_s1_00;
      fVar19 = extraout_s2_00;
      fVar17 = extraout_s3_00;
      break;
    case 4:
LAB_000836cc:
      *(undefined4 *)(this + 0x30) = 0;
      if (iVar4 == 4) {
        local_134._0_1_ = 'R';
        local_134._1_1_ = 'e';
        local_134._2_1_ = 'p';
        local_134._3_1_ = 'l';
        acStack_130[0] = 'a';
        acStack_130[1] = 'y';
        acStack_130[2] = ':';
        acStack_130[3] = ' ';
        acStack_12c[0] = 'T';
        acStack_12c[1] = 'i';
        acStack_12c[2] = 'm';
        acStack_12c[3] = 'e';
        acStack_128[0] = ' ';
        acStack_128[1] = 'T';
        acStack_128[2] = 'r';
        acStack_128[3] = 'i';
        local_124[0] = 'a';
        local_124[1] = 'l';
        local_122 = 0;
      }
      else {
        local_134._0_1_ = 'R';
        local_134._1_1_ = 'e';
        local_134._2_1_ = 'p';
        local_134._3_1_ = 'l';
        acStack_130[0] = 'a';
        acStack_130[1] = 'y';
        acStack_130[2] = ':';
        acStack_130[3] = ' ';
        acStack_12c[0] = 'C';
        acStack_12c[1] = 'h';
        acStack_12c[2] = 'a';
        acStack_12c[3] = 'l';
        acStack_128[0] = 'l';
        acStack_128[1] = 'e';
        acStack_128[2] = 'n';
        acStack_128[3] = 'g';
        local_124[0] = 'e';
        local_124[1] = '\0';
      }
    }
    tColour::tColour((tColour *)&local_154,fVar16,fVar18,fVar19,fVar17);
    fVar16 = (float)FontType(&local_134,0,0x3f800000,0x41a00000,0x43dc0000,0,0,0,0,0,0,0,0,0x1000000
                             ,local_154,uStack_150,uStack_14c,uStack_148,0,0);
LAB_00082424:
    if ((this[0xfefc] == (cRSubGame)0x0) && (*(int *)(this + 0xfbcc) != 2)) {
      cRTime::Add((cRTime *)(this + 0xfd94),fVar16);
    }
    if (*(int *)(this + 0x60) == 7) {
      cRTutorial::AI((cRTutorial *)(this + 0x84));
    }
    cRSlugVoiceManager::AI((cRSlugVoiceManager *)(this + 0x8c4c));
    if (this[0x18] != (cRSubGame)0x0) {
      this[0x19] = (cRSubGame)0x0;
      this[0x18] = (cRSubGame)0x0;
      cRSpriteManager::Pause((cRSpriteManager *)&gRSpriteManager,false);
    }
    iVar4 = Game;
    if (this[0x30fcc0] == (cRSubGame)0x0) {
LAB_000824c4:
      if (*(char *)(Game + 0x4d3dc) != '\0') goto LAB_000824e8;
    }
    else {
      if (*(int *)(this + 0x3345bc) == 4) {
        if (*(int *)(Game + 0x24) == 0) {
          fVar16 = *(float *)(this + 0x3345f8) + *(float *)(this + 0x3345fc);
          uVar10 = in_fpscr & 0xfffffff | (uint)(fVar16 < 1.0) << 0x1f |
                   (uint)(fVar16 == 1.0) << 0x1e;
          in_fpscr = uVar10 | (uint)NAN(fVar16) << 0x1c;
          *(float *)(this + 0x3345f8) = fVar16;
          bVar2 = (byte)(uVar10 >> 0x18);
          if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
            this[0x10] = (cRSubGame)0x1;
            cRFade::Start((cRFade *)(iVar4 + 0x24),(_func_void *)0x0);
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
      if (*(int *)(Game + 0x24) == 0) {
        this_00 = (cRFade *)(Game + 0x24);
        this[0x10] = (cRSubGame)0x1;
        cRFade::Start(this_00,(_func_void *)0x0);
      }
    }
    iVar4 = Game;
    if ((this[0x10] != (cRSubGame)0x0) && (*(int *)(Game + 0x24) == 4)) {
      if (this[0x30fcc1] == (cRSubGame)0x0) {
        *(undefined4 *)(Game + 0x160) = *(undefined4 *)(Game + 0x15c);
        *(undefined4 *)(iVar4 + 0x15c) = 0x1b;
      }
      else {
        uVar6 = *(undefined4 *)(Game + 0x15c);
        *(undefined4 *)(Game + 0x15c) = 0x1a;
        *(undefined4 *)(iVar4 + 0x160) = uVar6;
      }
      if (*(float *)(Game + 0x4d3e0) <= 1.0) {
        *(undefined1 *)(Game + 0x4d3dc) = 0;
      }
      goto LAB_000822f8;
    }
    iVar4 = RShellInkey();
    if ((iVar4 == 0xb) && (*(int *)(Game + 0x24) == 0)) {
      this[0x19] = (cRSubGame)0x1;
      *(undefined4 *)(this + 0x5c) = 3;
      cRSpriteManager::Pause((cRSpriteManager *)&gRSpriteManager,true);
      if (*(int *)(this + 0xfbcc) == 2) {
        cRBorder::HideInit(*(cRBorder **)(this + 0xfbd0));
      }
      goto LAB_000822f8;
    }
    fVar18 = *(float *)(this + 0x1c);
    uVar10 = in_fpscr & 0xfffffff | (uint)(fVar18 < 0.0) << 0x1f | (uint)(fVar18 == 0.0) << 0x1e;
    uVar15 = uVar10 | (uint)NAN(fVar18) << 0x1c;
    bVar2 = (byte)(uVar10 >> 0x18);
    fVar16 = extraout_s0_00;
    if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) {
      fVar18 = fVar18 + *(float *)(this + 0x20);
      uVar10 = in_fpscr & 0xfffffff | (uint)(fVar18 < 1.0) << 0x1f | (uint)(fVar18 == 1.0) << 0x1e;
      uVar15 = uVar10 | (uint)NAN(fVar18) << 0x1c;
      *(float *)(this + 0x1c) = fVar18;
      bVar2 = (byte)(uVar10 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) {
        *(undefined4 *)(this + 0x1c) = 0;
      }
      if (*(int *)(this + 0xfbcc) == 2) {
        fVar16 = (float)cRBorder::UnHideInit(*(cRBorder **)(this + 0xfbd0));
      }
    }
    if (*this == (cRSubGame)0x0) {
      iVar9 = *(int *)(this + 0x60);
      iVar4 = *(int *)(this + 0x40);
      *(int *)(this + 0x3c) = iVar4;
      if (iVar9 == 2) goto LAB_00083790;
      iVar5 = (int)*(float *)(this + 0x122c0) + 0x30;
      if (iVar4 < iVar5) {
        *(int *)(this + 0x40) = iVar5;
        iVar4 = iVar5;
      }
    }
    else {
      iVar9 = *(int *)(this + 0x60);
      *(undefined4 *)(this + 0x3c) = 0;
      if (iVar9 == 2) {
LAB_00083790:
        *(int *)(this + 0x40) = *(int *)(this + 0x74);
        iVar4 = *(int *)(this + 0x74);
      }
      else {
        *(int *)(this + 0x40) = (int)*(float *)(this + 0x122c0) + 0x30;
        iVar4 = (int)*(float *)(this + 0x122c0) + 0x30;
      }
    }
    iVar11 = *(int *)(this + 0x3c);
    iVar5 = *(int *)(this + 0x78) + 0x28;
    if (iVar5 < iVar4) {
      *(int *)(this + 0x40) = iVar5;
      iVar4 = iVar5;
    }
    if (iVar11 < iVar4) {
      pcVar13 = this + iVar11 * 0xdc + 0x20df90;
      pcVar14 = (cRSubGoldy *)(this + 0xfac4);
      local_19c = iVar11 + 6;
      do {
        uVar10 = *(uint *)(pcVar13 + -0xb4);
        if ((uVar10 & 2) != 0) {
          fVar16 = (float)cLinkedList<cRBod>::AddAfter
                                    ((cLinkedList<cRBod> *)(Game + 0x358),
                                     (cRBod *)(this + iVar11 * 0xdc + 0x20dee0),
                                     (cRBod *)(Game + 0x7456c));
          **(uint **)(pcVar13 + -0x8c) = **(uint **)(pcVar13 + -0x8c) | 0x80000000;
          uVar10 = *(uint *)(pcVar13 + -0xb4);
        }
        if (((uVar10 & 0x10) != 0) && ((*(uint *)(this + 0x6c) & 0x800000) != 0)) {
          fVar16 = (float)AddParcel((tVector *)this,(cRSubGoldy *)(this + iVar11 * 0xdc + 0x20df60))
          ;
        }
        pcVar12 = this + iVar11 * 0x240 + 0x13b54;
        iVar4 = 0;
        do {
          if (((-1 < iVar11) && (iVar11 < *(int *)(this + 0x74))) &&
             ((*(uint *)(pcVar12 + -0x74) & 0x200) == 0)) {
            iVar9 = iVar11 * 0x240 + iVar4 * 0x48;
            if (((byte)this[iVar9 + 0x13b11] & 0x40) != 0) {
              if ((byte)((char)pcVar12[-0x48] - 0x1dU) < 2) {
                if (*(int *)(pcVar12 + -0x54) != 0) {
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar9 + 0x13adc),
                             (cRBod *)(this + 0x2d7c));
                  fVar16 = (float)VectorSignedToFloat(iVar11 % 8,(byte)(uVar15 >> 0x16) & 3);
                  *(float *)(pcVar12 + -0x58) = fVar16 * 0.125;
                  GetSkirtColour((tColourSmall *)this);
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(Game + 0x358),
                             (cRBod *)(this + iVar11 * 0xdc + 0x20df80),(cRBod *)(this + 0x2bf0));
                  uVar6 = *(undefined4 *)(pcVar12 + -100);
                  uVar8 = *(undefined4 *)(pcVar12 + -0x60);
                  *(undefined4 *)pcVar13 = *(undefined4 *)(pcVar12 + -0x68);
                  *(undefined4 *)(pcVar13 + 4) = uVar6;
                  *(undefined4 *)(pcVar13 + 8) = uVar8;
                }
              }
              else if (pcVar12[-0x48] == (cRSubGame)0xe) {
                cLinkedList<cRBod>::AddBefore
                          ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar9 + 0x13adc),
                           (cRBod *)(this + 0x2c48));
              }
              else {
                this_01 = (cRSubLoc *)(this + iVar9 + 0x13adc);
                iVar9 = cRSubLoc::IsRamp(this_01);
                if (iVar9 == 0) {
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this_01,
                             (cRBod *)(this + 0x2c1c));
                }
                else {
                  cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this_01,
                             (cRBod *)(this + 0x2c74));
                }
              }
              fVar16 = (float)(*(code *)**(undefined4 **)(pcVar12 + -0x78))
                                        (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc);
            }
            cVar7 = pcVar12[-0x48];
            if (cVar7 == (cRSubGame)0x17) {
              if ((((*(uint *)(this + 0x6c) & 0x800) != 0) && (*(int *)(this + 0x70) <= iVar11)) &&
                 (iVar11 < *(int *)(this + 0x78))) {
                fVar16 = (float)AddHealth(this,(cRSubLoc *)
                                               (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc),
                                          pcVar14);
                cVar7 = pcVar12[-0x48];
                goto LAB_00082810;
              }
LAB_00082838:
              if (((((byte)this[iVar11 * 0x240 + iVar4 * 0x48 + 0x13b10] & 0x10) == 0) &&
                  (cVar7 == (cRSubGame)0x1 || cVar7 == (cRSubGame)0x15)) &&
                 ((*(uint *)(this + 0x6c) & 2) != 0)) {
                fVar16 = (float)RAND(fVar16,(char *)0x3f800000);
                fVar18 = (1.0 - *(float *)(this + 0x321070)) * 0.2 + 0.8;
                uVar10 = uVar15 & 0xfffffff | (uint)(fVar16 < fVar18) << 0x1f |
                         (uint)(fVar16 == fVar18) << 0x1e;
                uVar15 = uVar10 | (uint)(NAN(fVar16) || NAN(fVar18)) << 0x1c;
                bVar2 = (byte)(uVar10 >> 0x18);
                fVar16 = extraout_s0_02;
                if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) {
                  if (iVar4 == 0) {
LAB_00083028:
                    cVar7 = *pcVar12;
                    if (((cVar7 != (cRSubGame)0x1) && (cVar7 != (cRSubGame)0x14)) &&
                       ((cVar7 != (cRSubGame)0x15 && (cVar7 != (cRSubGame)0x20)))) {
                      cVar7 = pcVar12[-0x48];
                      goto LAB_00082878;
                    }
                  }
                  else {
                    cVar7 = pcVar12[-0x90];
                    if (((cVar7 != (cRSubGame)0x1) && (cVar7 != (cRSubGame)0x14)) &&
                       ((cVar7 != (cRSubGame)0x15 && (cVar7 != (cRSubGame)0x20))))
                    goto LAB_00082fa0;
                    if (iVar4 != 7) goto LAB_00083028;
                  }
                  if (((*(int *)(this + 0x70) <= iVar11) && (iVar11 < *(int *)(this + 0x78))) &&
                     (*(int *)(this + 0xfbcc) != 2)) {
                    iVar9 = *(int *)(this + 0x60);
                    if (iVar9 == 4) {
                      fVar16 = (float)RAND(extraout_s0_02,(char *)0x3f800000);
                      fVar18 = *(float *)(this + 0x68) * 0.3 + 0.7;
                      uVar10 = uVar15 & 0xfffffff | (uint)(fVar16 < fVar18) << 0x1f |
                               (uint)(fVar16 == fVar18) << 0x1e;
                      uVar15 = uVar10 | (uint)(NAN(fVar16) || NAN(fVar18)) << 0x1c;
                      bVar2 = (byte)(uVar10 >> 0x18);
                      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) {
                        cVar7 = pcVar12[-0x48];
                        fVar16 = extraout_s0_08;
                        goto LAB_00082878;
                      }
                      iVar9 = *(int *)(this + 0x60);
                      fVar16 = extraout_s0_08;
                    }
                    if (iVar9 == 0) {
                      fVar16 = (float)RAND(fVar16,(char *)0x3f800000);
                      fVar18 = *(float *)(this + 0x68) * 0.6 + 0.4;
                      uVar10 = uVar15 & 0xfffffff | (uint)(fVar16 < fVar18) << 0x1f |
                               (uint)(fVar16 == fVar18) << 0x1e;
                      uVar15 = uVar10 | (uint)(NAN(fVar16) || NAN(fVar18)) << 0x1c;
                      bVar2 = (byte)(uVar10 >> 0x18);
                      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) {
                        cVar7 = pcVar12[-0x48];
                        fVar16 = extraout_s0_03;
                        goto LAB_00082878;
                      }
                    }
                    goto LAB_00082b74;
                  }
                }
LAB_00082fa0:
                cVar7 = pcVar12[-0x48];
              }
LAB_00082878:
              if (cVar7 == (cRSubGame)0x22) goto LAB_00082ba8;
LAB_00082880:
              iVar9 = iVar11 * 0x240 + iVar4 * 0x48;
              if (((((byte)this[iVar9 + 0x13b10] & 8) != 0) ||
                  (cVar7 != (cRSubGame)0x1 && cVar7 != (cRSubGame)0xf)) ||
                 (*(int *)(this + 0xfbcc) == 2)) goto LAB_00082b38;
              uVar10 = *(uint *)(this + 0x6c);
              if ((uVar10 & 0x10000) != 0) {
                fVar16 = (float)RAND(fVar16,(char *)0x3f800000);
                fVar18 = (1.0 - *(float *)(this + 0x321074)) * 0.02 + 0.98;
                uVar10 = uVar15 & 0xfffffff | (uint)(fVar16 < fVar18) << 0x1f |
                         (uint)(fVar16 == fVar18) << 0x1e;
                uVar15 = uVar10 | (uint)(NAN(fVar16) || NAN(fVar18)) << 0x1c;
                bVar2 = (byte)(uVar10 >> 0x18);
                fVar16 = extraout_s0_01;
                if (((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) &&
                    (*(int *)(this + 0x70) <= iVar11)) && (iVar11 < *(int *)(this + 0x78))) {
                  fVar16 = (float)cRSaltManager::Add((cRSaltManager *)(this + 0x4e78),
                                                     (tVector *)(this + iVar9 + 0x13aec));
                }
                goto LAB_00082b38;
              }
            }
            else {
LAB_00082810:
              if (cVar7 == (cRSubGame)0x18) {
                if ((iVar11 < *(int *)(this + 0x70)) || (*(int *)(this + 0x78) <= iVar11))
                goto LAB_00082838;
                fVar16 = (float)AddSpeedUp((cRSubLoc *)this,
                                           (cRSubGoldy *)
                                           (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc));
                cVar7 = pcVar12[-0x48];
              }
              if (cVar7 == (cRSubGame)0x19) {
                if ((iVar11 < *(int *)(this + 0x70)) || (*(int *)(this + 0x78) <= iVar11))
                goto LAB_00082838;
                fVar16 = (float)AddJetPack(this,(cRSubLoc *)
                                                (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc),
                                           pcVar14);
                cVar7 = pcVar12[-0x48];
              }
              if (cVar7 != (cRSubGame)0x21) goto LAB_00082838;
LAB_00082b74:
              fVar16 = (float)AddGarbage((cRSubLoc *)this,
                                         (cRSubGoldy *)
                                         (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc));
              cVar7 = pcVar12[-0x48];
              if (cVar7 != (cRSubGame)0x22) goto LAB_00082880;
LAB_00082ba8:
              if ((*(int *)(this + 0x70) <= iVar11) && (iVar11 < *(int *)(this + 0x78))) {
                fVar16 = (float)cRSaltManager::Add((cRSaltManager *)(this + 0x4e78),
                                                   (tVector *)
                                                   (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13aec))
                ;
                uVar10 = *(uint *)(this + 0x6c);
                goto LAB_000828d0;
              }
LAB_00082b38:
              uVar10 = *(uint *)(this + 0x6c);
            }
LAB_000828d0:
            if ((((uVar10 & 0x80) != 0) && (pcVar12[-0x48] == (cRSubGame)0x12)) &&
               ((*(int *)(this + 0x70) <= iVar11 && (iVar11 < *(int *)(this + 0x78))))) {
              fVar16 = (float)AddSlug(this,(cRSubLoc *)
                                           (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc),pcVar14)
              ;
            }
            uVar10 = *(uint *)(pcVar13 + -0xb4);
            if ((uVar10 & 0x200) == 0) {
              cVar7 = pcVar12[-0x48];
              if (cVar7 == (cRSubGame)0x23) {
                if ((uVar10 & 0x400) == 0) {
                  if ((uVar10 & 0x2000) == 0) {
                    if ((uVar10 & 0x800) == 0) {
                      if ((uVar10 & 0x1000) != 0) {
                        fVar16 = (float)AddRing(this,(cRSubLoc *)
                                                     (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc
                                                     ),7,pcVar14,fVar16);
                        *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + -0x60);
                      }
                    }
                    else {
                      fVar16 = (float)AddRing(this,(cRSubLoc *)
                                                   (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc),
                                              6,pcVar14,fVar16);
                      *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + -0x60);
                    }
                  }
                  else {
                    fVar16 = (float)AddRing(this,(cRSubLoc *)
                                                 (this + iVar4 * 0x48 + iVar11 * 0x240 + 0x13adc),8,
                                            pcVar14,fVar16);
                    *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + -0x60);
                  }
                }
                else {
                  iVar5 = 5;
                  iVar9 = iVar11 * 0x240 + iVar4 * 0x48;
LAB_0008307c:
                  fVar16 = (float)AddRing(this,(cRSubLoc *)(this + iVar9 + 0x13adc),iVar5,pcVar14,
                                          fVar16);
                  *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + -0x60);
                }
              }
              else {
                if ((byte)((char)cVar7 - 2U) < 6) {
                  fVar19 = *(float *)(this + 0xfe30) + 10.0;
                  fVar18 = *(float *)(pcVar12 + -0x60);
                  uVar1 = uVar15 & 0xfffffff | (uint)(fVar18 < fVar19) << 0x1f |
                          (uint)(fVar18 == fVar19) << 0x1e;
                  uVar15 = uVar1 | (uint)(NAN(fVar18) || NAN(fVar19)) << 0x1c;
                  bVar2 = (byte)(uVar1 >> 0x18);
                  if ((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) &&
                     (iVar11 < *(int *)(this + 0x78))) {
                    if ((uVar10 & 0x2000) == 0) {
                      if ((uVar10 & 0x800) == 0) {
                        if ((uVar10 & 0x1000) == 0) {
                          if ((*(uint *)(this + 0x6c) & 8) != 0) {
                            fVar16 = (float)RAND(fVar16,(char *)0x3f800000);
                            uVar10 = uVar15 & 0xfffffff | (uint)(fVar16 < 0.7) << 0x1f |
                                     (uint)(fVar16 == 0.7) << 0x1e;
                            uVar15 = uVar10 | (uint)NAN(fVar16) << 0x1c;
                            bVar2 = (byte)(uVar10 >> 0x18);
                            fVar16 = extraout_s0_05;
                            if (((!(bool)(bVar2 >> 6 & 1) &&
                                  bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) ||
                                (*(int *)(this + 0x60) == 7)) &&
                               (2 < (byte)((char)pcVar12[-0x48] - 5U))) {
                              fVar16 = (float)AddRing(this,(cRSubLoc *)
                                                           (this + iVar4 * 0x48 + iVar11 * 0x240 +
                                                                   0x13adc),4,pcVar14,extraout_s0_05
                                                     );
                              if (*(int *)(this + 0xfec0) < 8) {
                                *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + -0x60);
                              }
                              else {
                                *(float *)(this + 0xfe30) = *(float *)(pcVar12 + -0x60) + 35.0;
                              }
                            }
                          }
                        }
                        else {
                          fVar16 = (float)AddRing(this,(cRSubLoc *)
                                                       (this + iVar4 * 0x48 + local_19c * 0x240 +
                                                               0x13adc),7,pcVar14,fVar16);
                          *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + 0xd20);
                        }
                        goto LAB_00082960;
                      }
                      iVar9 = 6;
                    }
                    else {
                      iVar9 = 8;
                    }
                    fVar16 = (float)AddRing(this,(cRSubLoc *)
                                                 (this + local_19c * 0x240 + iVar4 * 0x48 + 0x13adc)
                                            ,iVar9,pcVar14,fVar16);
                    *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + 0xd20);
                    goto LAB_00082960;
                  }
                }
                if ((byte)((char)cVar7 - 8U) < 3) {
                  fVar19 = *(float *)(this + 0xfe30) + 10.0;
                  fVar18 = *(float *)(pcVar12 + -0x60);
                  uVar1 = uVar15 & 0xfffffff | (uint)(fVar18 < fVar19) << 0x1f |
                          (uint)(fVar18 == fVar19) << 0x1e;
                  uVar15 = uVar1 | (uint)(NAN(fVar18) || NAN(fVar19)) << 0x1c;
                  bVar2 = (byte)(uVar1 >> 0x18);
                  if ((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) &&
                     (iVar11 < *(int *)(this + 0x78))) {
                    if ((uVar10 & 0x800) == 0) {
                      fVar16 = (float)RAND(fVar16,(char *)0x3f800000);
                      uVar10 = uVar15 & 0xfffffff | (uint)(fVar16 < 0.7) << 0x1f |
                               (uint)(fVar16 == 0.7) << 0x1e;
                      uVar15 = uVar10 | (uint)NAN(fVar16) << 0x1c;
                      bVar2 = (byte)(uVar10 >> 0x18);
                      fVar16 = extraout_s0_04;
                      if (((!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar15 >> 0x1c) & 1))
                          || (*(int *)(this + 0x60) == 7)) ||
                         ((*(uint *)(pcVar13 + -0xb4) & 0x800) != 0)) {
                        iVar5 = 2;
                        iVar9 = iVar4 * 0x48 + iVar11 * 0x240;
                        goto LAB_0008307c;
                      }
                    }
                    else {
                      fVar16 = (float)AddRing(this,(cRSubLoc *)
                                                   (this + iVar11 * 0x240 + iVar4 * 0x48 + 0x13adc),
                                              2,pcVar14,fVar16);
                      *(undefined4 *)(this + 0xfe30) = *(undefined4 *)(pcVar12 + -0x60);
                    }
                  }
                }
              }
            }
          }
LAB_00082960:
          iVar4 = iVar4 + 1;
          pcVar12 = pcVar12 + 0x48;
        } while (iVar4 != 8);
        iVar4 = *(int *)(this + 0x7c);
        while (iVar4 <= iVar11) {
          if (*(int *)(this + 0x60) != 2) {
            fVar16 = (float)cRWorld::Add((cRWorld *)(this + 0xf9f0),
                                         (cRSubLoc *)(this + iVar4 * 0x240 + 0x13adc));
            iVar4 = *(int *)(this + 0x7c);
          }
          iVar4 = iVar4 + 1;
          *(int *)(this + 0x7c) = iVar4;
        }
        iVar11 = iVar11 + 1;
        pcVar13 = pcVar13 + 0xdc;
        local_19c = local_19c + 1;
        *this = (cRSubGame)0x0;
      } while (iVar11 < *(int *)(this + 0x40));
      iVar9 = *(int *)(this + 0x60);
    }
    if (iVar9 == 4) {
      iVar4 = *(int *)(this + 0x8c58);
      pcVar3 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(this + 0x30fcd0),(cRTime *)(this + 0xfd94));
      Rstrcpy((char *)(iVar4 + 0x2c4),pcVar3);
      iVar4 = (*(int *)(this + 100) + 0x16) * 0x38;
      if (*(int *)(this + iVar4 + 0x2cf4a4) == 1) {
        iVar9 = *(int *)(this + 0x8c5c);
        pcVar3 = (char *)cRTimeTrial::TimeString
                                   ((cRTimeTrial *)(this + 0x30fcd0),
                                    (cRTime *)(this + iVar4 + 0x2cf4a8));
        Rstrcpy((char *)(iVar9 + 0x2c4),pcVar3);
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
      *(undefined4 *)(Game + 0x328) = 1;
    }
    else {
      this[0x30fcc0] = (cRSubGame)0x1;
      StartLevel(this,0);
      *(undefined4 *)(this + 0x5c) = 2;
      *(undefined4 *)(Game + 0x328) = 1;
    }
    goto LAB_000822f8;
  }
  CameraAI(this);
LAB_000822f8:
  if (local_34 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
