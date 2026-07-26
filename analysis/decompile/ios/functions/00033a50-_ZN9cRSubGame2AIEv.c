/*
 * mangled: _ZN9cRSubGame2AIEv
 * demangled: cRSubGame::AI()
 * address: 00033a50
 * size: 7844
 */

/* cRSubGame::AI() */

void __thiscall cRSubGame::AI(cRSubGame *this)

{
  byte bVar1;
  undefined *puVar2;
  cRSubGame cVar3;
  char cVar4;
  cRSubGame *pcVar5;
  int iVar6;
  cRBorder *this_00;
  char *pcVar7;
  _func_void *p_Var8;
  undefined4 uVar9;
  cRSubLoc *pcVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  cRSubGame *pcVar15;
  cRSubGame *pcVar16;
  int iVar17;
  int iVar18;
  bool bVar19;
  bool bVar20;
  bool bVar21;
  uint in_fpscr;
  uint uVar22;
  uint uVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  longlong lVar27;
  cRSubGame *local_194;
  int local_190;
  cRSubGame *local_18c;
  uint local_188;
  char acStack_184 [4];
  char acStack_180 [4];
  char acStack_17c [4];
  undefined4 local_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 local_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  iVar17 = *(int *)(this + 0x54);
  if (iVar17 == 2) {
    fVar24 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x70),(byte)(in_fpscr >> 0x16) & 3);
    fVar24 = *(float *)(this + 0xf4ac) / fVar24;
    uVar14 = in_fpscr & 0xfffffff;
    in_fpscr = uVar14 | (uint)(fVar24 < 0.0) << 0x1f;
    if (SUB41(in_fpscr >> 0x1f,0)) {
      fVar24 = 0.0;
    }
    else {
      uVar14 = uVar14 | (uint)(fVar24 < 1.0) << 0x1f | (uint)(fVar24 == 1.0) << 0x1e;
      in_fpscr = uVar14 | (uint)NAN(fVar24) << 0x1c;
      bVar1 = (byte)(uVar14 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar24 = 1.0;
      }
    }
    iVar6 = *(int *)(this + 0x58);
    if (iVar6 == 3 || iVar6 == 1) {
      *(float *)(this + 0x4c) = *(float *)(this + 0x44) + fVar24 * 0.3;
    }
    else {
      *(float *)(this + 0x4c) = *(float *)(this + 0x44) + fVar24 * 0.2;
    }
    if (*(int *)(this + 0xf7fc) == 2) {
      if (iVar6 == 4 || iVar6 == 1) {
        fVar24 = 0.3;
      }
      else {
        fVar24 = 0.4;
      }
      fVar25 = *(float *)(this + 0xf81c);
      uVar14 = in_fpscr & 0xfffffff;
      in_fpscr = uVar14 | (uint)(fVar25 < 0.25) << 0x1f;
      if ((SUB41(in_fpscr >> 0x1f,0)) ||
         (uVar14 = uVar14 | (uint)(fVar25 < 0.75) << 0x1f | (uint)(fVar25 == 0.75) << 0x1e,
         in_fpscr = uVar14 | (uint)NAN(fVar25) << 0x1c, bVar1 = (byte)(uVar14 >> 0x18),
         !(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))) {
        fVar26 = *(float *)(this + 0x4c);
        fVar25 = (float)Sin((fVar25 + fVar25 + fVar25 + fVar25) * 3.1415927 + 1.5707964);
        iVar17 = *(int *)(this + 0x54);
        *(float *)(this + 0x4c) = fVar26 + (1.0 - fVar25) * 0.5 * fVar24;
      }
      else {
        *(float *)(this + 0x4c) = *(float *)(this + 0x4c) + fVar24;
      }
    }
    if (*(int *)(this + 0x11a18) == 1) {
      *(float *)(this + 0x4c) = *(float *)(this + 0x4c) + *(float *)(this + 0x11c18) * 0.5;
    }
  }
  else {
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(this + 0x44);
  }
  puVar2 = PTR__Game_001b60b8;
  switch(iVar17) {
  case 0:
    iVar17 = 1;
    iVar6 = *(int *)(this + 0x303aa8);
    *(undefined4 *)(this + 0x54) = 1;
    if (iVar6 != 1) {
      if (iVar6 == 3 || iVar6 == 0) goto LAB_000348c4;
      if (this[0x2e09cd] != (cRSubGame)0x0) {
        this[0x2e09cc] = (cRSubGame)0x1;
        StartLevel(this,*(int *)(*(int *)(this + 0x2e09d0) + 0x28));
        return;
      }
      this[0x2e09cc] = (cRSubGame)0x0;
      cRStarManager::Hide((cRStarManager *)(*(int *)PTR__Game_001b60b8 + 0x4e718));
      goto switchD_00033a80_caseD_1;
    }
    break;
  case 1:
switchD_00033a80_caseD_1:
    RAND(1.0,(char *)0x0);
    puVar2 = PTR__gConfig_001b60d4;
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(PTR__gConfig_001b60d4 + 0x40);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(puVar2 + 0x48);
    switch(*(undefined4 *)(this + 0x58)) {
    case 0:
      iVar17 = cRGalaxy::AIControl((cRGalaxy *)
                                   (this + *(int *)(this + 0x2f1dcc) * 0x8e6c + 0x2f1dd0));
      if (iVar17 == 1) {
        *(undefined4 *)(this + 0x303aa8) = 3;
        if (*(int *)(this + 0x2f1dcc) == 0) {
          *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa4) = *(undefined4 *)(this + 0x5c);
        }
        else if (*(int *)(this + 0x2f1dcc) == 1) {
          *(undefined4 *)(PTR__gConfig_001b60d4 + 0xec) = *(undefined4 *)(this + 0x5c);
        }
LAB_000348c4:
        StartLevel(this,*(int *)(this + 0x5c));
        return;
      }
      if (iVar17 == 2) {
        *(undefined4 *)(this + 0x303aa8) = 1;
        if (*(int *)(this + 0x2f1dcc) == 0) {
          *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa4) = *(undefined4 *)(this + 0x5c);
        }
        else if (*(int *)(this + 0x2f1dcc) == 1) {
          *(undefined4 *)(PTR__gConfig_001b60d4 + 0xec) = *(undefined4 *)(this + 0x5c);
        }
        goto LAB_000348c4;
      }
      if (iVar17 == 3) {
        UnInit(this);
        *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 2;
        return;
      }
      break;
    case 1:
      iVar17 = cRGUI::AI((cRGUI *)(this + 0x2f1d84));
      if (iVar17 == 1) goto switchD_00034244_caseD_7;
      if (iVar17 == 3) {
        UnInit(this);
        *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 2;
        return;
      }
      break;
    case 4:
      iVar17 = cRGalaxy::AIControl((cRGalaxy *)
                                   (this + *(int *)(this + 0x2f1dcc) * 0x8e6c + 0x2f1dd0));
      if (iVar17 == 1) {
        *(undefined4 *)(this + 0x303aa8) = 2;
        *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa4) = *(undefined4 *)(this + 0x5c);
        goto LAB_000348c4;
      }
      if (iVar17 == 3) {
        UnInit(this);
        *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 2;
        return;
      }
      break;
    case 7:
switchD_00034244_caseD_7:
      *(undefined4 *)(this + 0x303aa8) = 2;
      StartLevel(this,0);
      return;
    }
switchD_00034244_caseD_2:
    iVar17 = *(int *)(this + 0x54);
    break;
  case 2:
    this_00 = *(cRBorder **)(this + 0xc);
    if (this_00 != (cRBorder *)0x0) {
      if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x72b8a) == '\0') {
        cRBorder::UnHideInit(this_00);
        uVar14 = *(uint *)(*(int *)(this + 0xc) + 0x194);
        if ((uVar14 & 0x20) != 0) {
          *(uint *)(*(int *)(this + 0xc) + 0x194) = uVar14 & 0xffffffdf;
          iVar17 = *(int *)puVar2;
          if ((*(int *)(iVar17 + 0x72bd0) != 0) ||
             ((((&DAT_000823cd)[iVar17] == '\0' ||
               (in_fpscr = in_fpscr & 0xfffffff |
                           (uint)(*(float *)(iVar17 + 0x82020) < -0.1) << 0x1f,
               !SUB41(in_fpscr >> 0x1f,0))) && (*(char *)(iVar17 + 0x82280) == '\0')))) {
            wprintf("Border Quit");
            KeySet('\x01');
          }
        }
      }
      else {
        cRBorder::HideInit(this_00);
        *(uint *)(*(int *)(this + 0xc) + 0x194) =
             *(uint *)(*(int *)(this + 0xc) + 0x194) & 0xffffffdf;
      }
    }
    if ((this[0x2e09cc] != (cRSubGame)0x0) &&
       (*(char *)(*(int *)PTR__Game_001b60b8 + 0x4e6b4) == '\0')) {
      iVar17 = *(int *)(this + 0x58);
      if (iVar17 == 3) {
        fVar24 = 1.0;
        tColour::tColour((tColour *)&local_38,1.0,1.0,1.0,0.8);
        OSDPrintUV(0xd,0x44110000,0x40c00000,0x42800000,0x42800000,0x1000000,local_38,uStack_34,
                   uStack_30,uStack_2c,*(undefined4 *)(PTR__gSpriteReference_001b61c8 + 0x1b0),
                   fVar24 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x1bc),
                   *(undefined4 *)(PTR__gSpriteReference_001b61c8 + 0x1b8),
                   fVar24 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x1b4),7,0);
      }
      else {
        fVar24 = *(float *)(this + 0x2c) + *(float *)(this + 0x30);
        uVar14 = in_fpscr & 0xfffffff;
        uVar22 = uVar14 | (uint)(fVar24 < 1.0) << 0x1f | (uint)(fVar24 == 1.0) << 0x1e;
        in_fpscr = uVar22 | (uint)NAN(fVar24) << 0x1c;
        *(float *)(this + 0x2c) = fVar24;
        bVar1 = (byte)(uVar22 >> 0x18);
        if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
          in_fpscr = uVar14 | (uint)(fVar24 < 0.2) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar25 = fVar24 / 0.2;
            iVar6 = *(int *)(this + 0x28);
            goto LAB_00034324;
          }
          fVar25 = 0.8;
          uVar14 = uVar14 | (uint)(fVar24 < 0.8) << 0x1f | (uint)(fVar24 == 0.8) << 0x1e;
          in_fpscr = uVar14 | (uint)NAN(fVar24) << 0x1c;
          bVar1 = (byte)(uVar14 >> 0x18);
          if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
            iVar6 = *(int *)(this + 0x28);
          }
          else {
            iVar6 = *(int *)(this + 0x28);
            fVar25 = ((1.0 - fVar24) / 0.2) * 0.8;
          }
        }
        else {
          fVar25 = 0.0;
          *(undefined4 *)(this + 0x2c) = 0;
          iVar6 = *(int *)(this + 0x28) + 1;
          *(int *)(this + 0x28) = iVar6;
LAB_00034324:
          fVar25 = fVar25 * 0.8;
        }
        switch(iVar6) {
        case 0:
        case 4:
          *(undefined4 *)(this + 0x28) = 0;
          if (iVar17 == 4) {
            local_188._0_1_ = 'R';
            local_188._1_1_ = 'e';
            local_188._2_1_ = 'p';
            local_188._3_1_ = 'l';
            acStack_184[0] = 'a';
            acStack_184[1] = 'y';
            acStack_184[2] = ':';
            acStack_184[3] = ' ';
            acStack_180[0] = 'T';
            acStack_180[1] = 'i';
            acStack_180[2] = 'm';
            acStack_180[3] = 'e';
            acStack_17c[0] = ' ';
            acStack_17c[1] = 'T';
            acStack_17c[2] = 'r';
            acStack_17c[3] = 'i';
            local_178 = CONCAT13(local_178._3_1_,0x6c61);
          }
          else {
            local_188._0_1_ = 'R';
            local_188._1_1_ = 'e';
            local_188._2_1_ = 'p';
            local_188._3_1_ = 'l';
            acStack_184[0] = 'a';
            acStack_184[1] = 'y';
            acStack_184[2] = ':';
            acStack_184[3] = ' ';
            acStack_180[0] = 'C';
            acStack_180[1] = 'h';
            acStack_180[2] = 'a';
            acStack_180[3] = 'l';
            acStack_17c[0] = 'l';
            acStack_17c[1] = 'e';
            acStack_17c[2] = 'n';
            acStack_17c[3] = 'g';
            local_178 = CONCAT22(local_178._2_2_,0x65);
          }
          break;
        case 1:
          _sprintf((char *)&local_188,"Player: %s",*(int *)(this + 0x2e09d0) + 0x54);
          break;
        case 2:
          if (iVar17 == 4) {
            *(undefined4 *)(this + 0x28) = 0;
            local_188 = local_188 & 0xffffff00;
          }
          else {
            _sprintf((char *)&local_188,"Difficulty: %i%%",
                     *(undefined4 *)(*(int *)(this + 0x2e09d0) + 0x50));
          }
          break;
        case 3:
          _sprintf((char *)&local_188,"Speed: %i%%",
                   *(undefined4 *)(*(int *)(this + 0x2e09d0) + 0x4c));
        }
        tColour::tColour((tColour *)&local_48,1.0,1.0,1.0,fVar25);
        FontType(&local_188,0,0x3f800000,0x41a00000,0x43dc0000,0,0,0,0,0,0,0,0,0x1000000,local_48,
                 uStack_44,uStack_40,uStack_3c,0,0);
      }
    }
    if ((this[0xf878] == (cRSubGame)0x0) && (*(int *)(this + 0xf550) != 2)) {
      *(float *)(this + 0xf718) = *(float *)(this + 0xf718) + 0.016666668;
      pcVar16 = this + 0xf72c;
      fVar24 = *(float *)pcVar16 + 0.016666668;
      uVar14 = in_fpscr & 0xfffffff | (uint)(fVar24 < 1.0) << 0x1f;
      in_fpscr = uVar14 | (uint)NAN(fVar24) << 0x1c;
      *(float *)pcVar16 = fVar24;
      if ((byte)(uVar14 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1)) {
        iVar17 = *(int *)(this + 0xf720);
        *(float *)pcVar16 = fVar24 - 1.0;
        iVar6 = iVar17 + 1;
        *(int *)(this + 0xf720) = iVar6;
        if (0x3b < iVar6) {
          *(int *)(this + 0xf720) = iVar17 + -0x3b;
          *(int *)(this + 0xf71c) = *(int *)(this + 0xf71c) + 1;
        }
      }
      *(int *)(this + 0xf724) = (int)(*(float *)(this + 0xf72c) * 100.0);
      *(int *)(this + 0xf728) = (int)(*(float *)(this + 0xf72c) * 1000.0);
    }
    if (*(int *)(this + 0x58) == 7) {
      cRTutorial::AI((cRTutorial *)(this + 0x7c));
    }
    pcVar16 = this + 0x85d8;
    fVar24 = *(float *)pcVar16;
    uVar14 = in_fpscr & 0xfffffff | (uint)(fVar24 < 0.0) << 0x1f | (uint)(fVar24 == 0.0) << 0x1e;
    uVar22 = uVar14 | (uint)NAN(fVar24) << 0x1c;
    bVar1 = (byte)(uVar14 >> 0x18);
    if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar22 >> 0x1c) & 1)) {
      fVar24 = fVar24 + *(float *)(this + 0x85dc);
      uVar14 = in_fpscr & 0xfffffff | (uint)(fVar24 < 1.0) << 0x1f | (uint)(fVar24 == 1.0) << 0x1e;
      uVar22 = uVar14 | (uint)NAN(fVar24) << 0x1c;
      *(float *)pcVar16 = fVar24;
      bVar1 = (byte)(uVar14 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar22 >> 0x1c) & 1)) {
        *(undefined4 *)pcVar16 = 0;
        this[0x85d4] = (cRSubGame)0x0;
      }
    }
    if (this[0x11] != (cRSubGame)0x0) {
      this[0x12] = (cRSubGame)0x0;
      this[0x11] = (cRSubGame)0x0;
      cRSpriteManager::Pause((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,false);
    }
    puVar2 = PTR__Game_001b60b8;
    p_Var8 = *(_func_void **)PTR__Game_001b60b8;
    if (this[0x2e09cc] == (cRSubGame)0x0) {
LAB_00034668:
      if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x4e6b4) != '\0') goto LAB_00034688;
    }
    else {
      iVar17 = *(int *)(this + 0x3052c8);
      if (iVar17 == 4) {
        p_Var8 = *(_func_void **)(p_Var8 + 0x24);
      }
      if (iVar17 == 4 && p_Var8 == (_func_void *)0x0) {
        this[0x10] = (cRSubGame)((char)iVar17 + -3);
        cRFade::Start((cRFade *)(*(int *)puVar2 + 0x24),p_Var8);
        if (this[0x2e09cc] == (cRSubGame)0x0) goto LAB_00034668;
      }
      uVar22 = uVar22 & 0xfffffff | (uint)(*(float *)(this + 0x14) == 0.0) << 0x1e;
      if ((!SUB41(uVar22 >> 0x1e,0)) || ((*(uint *)(*(int *)(this + 0xf874) + 4) & 0x4000) == 0))
      goto LAB_00034668;
LAB_00034688:
      puVar2 = PTR__Game_001b60b8;
      if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0) {
        this[0x10] = (cRSubGame)0x1;
        cRFade::Start((cRFade *)(*(int *)puVar2 + 0x24),(_func_void *)0x0);
      }
    }
    puVar2 = PTR__Game_001b60b8;
    if ((this[0x10] != (cRSubGame)0x0) &&
       (iVar17 = *(int *)PTR__Game_001b60b8, *(int *)(iVar17 + 0x24) == 4)) {
      if (this[0x2e09cd] == (cRSubGame)0x0) {
        *(undefined4 *)(iVar17 + 0x160) = *(undefined4 *)(iVar17 + 0x15c);
        *(undefined4 *)(*(int *)puVar2 + 0x15c) = 0x1b;
      }
      else {
        *(undefined4 *)(iVar17 + 0x160) = *(undefined4 *)(iVar17 + 0x15c);
        *(undefined4 *)(*(int *)puVar2 + 0x15c) = 0x1a;
      }
      if (1.0 < *(float *)(*(int *)PTR__Game_001b60b8 + 0x4e6b8)) {
        return;
      }
      *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x4e6b4) = 0;
      return;
    }
    cVar4 = RShellInkey();
    if ((cVar4 == '\v') && (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
      this[0x12] = (cRSubGame)0x1;
      puVar2 = PTR__gRSpriteManager_001b61e4;
      *(undefined4 *)(this + 0x54) = 3;
      cRSpriteManager::Pause((cRSpriteManager *)puVar2,true);
      if (*(int *)(this + 0xf550) != 2) {
        return;
      }
      cRBorder::HideInit(*(cRBorder **)(this + 0xf554));
      return;
    }
    fVar24 = *(float *)(this + 0x14);
    uVar14 = uVar22 & 0xfffffff | (uint)(fVar24 < 0.0) << 0x1f | (uint)(fVar24 == 0.0) << 0x1e;
    uVar23 = uVar14 | (uint)NAN(fVar24) << 0x1c;
    bVar1 = (byte)(uVar14 >> 0x18);
    if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1)) {
      fVar24 = fVar24 + *(float *)(this + 0x18);
      uVar14 = uVar22 & 0xfffffff | (uint)(fVar24 < 1.0) << 0x1f | (uint)(fVar24 == 1.0) << 0x1e;
      uVar23 = uVar14 | (uint)NAN(fVar24) << 0x1c;
      *(float *)(this + 0x14) = fVar24;
      bVar1 = (byte)(uVar14 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1)) {
        *(undefined4 *)(this + 0x14) = 0;
      }
      if (*(int *)(this + 0xf550) == 2) {
        cRBorder::UnHideInit(*(cRBorder **)(this + 0xf554));
      }
    }
    if (*this == (cRSubGame)0x0) {
      iVar6 = *(int *)(this + 0x58);
      iVar17 = *(int *)(this + 0x38);
      *(int *)(this + 0x34) = iVar17;
      if (iVar6 == 2) goto LAB_00034a98;
      iVar13 = (int)*(float *)(this + 0x11c3c) + 0x30;
      if (iVar17 < iVar13) {
        *(int *)(this + 0x38) = iVar13;
        iVar17 = iVar13;
      }
    }
    else {
      iVar6 = *(int *)(this + 0x58);
      *(undefined4 *)(this + 0x34) = 0;
      if (iVar6 == 2) {
LAB_00034a98:
        *(int *)(this + 0x38) = *(int *)(this + 0x6c);
        iVar17 = *(int *)(this + 0x6c);
      }
      else {
        *(int *)(this + 0x38) = (int)*(float *)(this + 0x11c3c) + 0x30;
        iVar17 = (int)*(float *)(this + 0x11c3c) + 0x30;
      }
    }
    iVar18 = *(int *)(this + 0x34);
    iVar13 = *(int *)(this + 0x70) + 0x28;
    if (iVar13 < iVar17) {
      *(int *)(this + 0x38) = iVar13;
      iVar17 = iVar13;
    }
    if (iVar18 < iVar17) {
      local_190 = iVar18 + 6;
      local_18c = this + iVar18 * 0xdc + 0x1e428c;
      do {
        uVar14 = *(uint *)(local_18c + -0xb4);
        if ((uVar14 & 2) != 0) {
          uVar14 = *(uint *)(local_18c + -0xac);
          iVar17 = *(int *)PTR__Game_001b60b8;
          if ((uVar14 & 0x200) == 0) {
            *(int *)(local_18c + -0xa8) = (int)&DAT_000751cc + iVar17;
            *(undefined4 *)(local_18c + -0xa4) = *(undefined4 *)((int)&DAT_000751d8 + iVar17);
            *(cRSubGame **)((int)&DAT_000751d8 + iVar17) = this + iVar18 * 0xdc + 0x1e41dc;
            if (*(int *)(local_18c + -0xa4) != 0) {
              *(cRSubGame **)(*(int *)(local_18c + -0xa4) + 8) = this + iVar18 * 0xdc + 0x1e41dc;
            }
            *(uint *)(local_18c + -0xac) = uVar14 | 0x200;
          }
          else {
            RShellError("List ADDafter");
          }
          **(uint **)(local_18c + -0x8c) = **(uint **)(local_18c + -0x8c) | 0x80000000;
          uVar14 = *(uint *)(local_18c + -0xb4);
        }
        if (((uVar14 & 0x10) != 0) && ((*(uint *)(this + 100) & 0x800000) != 0)) {
          AddParcel((tVector *)this,(cRSubGoldy *)(this + iVar18 * 0xdc + 0x1e425c));
        }
        fVar24 = (float)VectorSignedToFloat(iVar18 % 8,(byte)(uVar23 >> 0x16) & 3);
        pcVar16 = this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88);
        lVar27 = (ulonglong)(uint)(fVar24 * 0.125) << 0x20;
        iVar17 = 0;
        local_194 = this + local_190 * 0x220 + 0x13470;
        do {
          if (((-1 < iVar18) && (iVar18 < *(int *)(this + 0x6c))) &&
             (uVar14 = *(uint *)(pcVar16 + 4), (uVar14 & 0x200) == 0)) {
            pcVar5 = (cRSubGame *)(iVar17 * 0x44 + iVar18 * 0x220);
            if (((byte)(pcVar5 + (int)this)[0x1348b] & 0x40) != 0) {
              cVar3 = pcVar16[0x30];
              if ((byte)((char)cVar3 - 0x1dU) < 2) {
                if (*(int *)(pcVar16 + 0x24) != 0) {
                  *(cRSubGame **)(pcVar16 + 8) = this + 0x2704;
                  uVar9 = *(undefined4 *)(this + 10000);
                  *(int *)(pcVar16 + 0x20) = (int)((ulonglong)lVar27 >> 0x20);
                  *(undefined4 *)(pcVar16 + 0xc) = uVar9;
                  *(cRSubGame **)(this + 10000) = this + (int)(pcVar5 + 0x13458);
                  *(uint *)(pcVar16 + 4) = uVar14 | 0x200;
                  if (*(int *)(pcVar16 + 0xc) != 0) {
                    *(cRSubGame **)(*(int *)(pcVar16 + 0xc) + 8) = this + (int)(pcVar5 + 0x13458);
                  }
                  tColourSmall::Set((tColourSmall *)(this + iVar18 * 0xdc + 0x1e42a4),
                                    *(float *)(this + 0x1258),*(float *)(this + 0x125c),
                                    *(float *)(this + 0x1260),0.5);
                  uVar14 = *(uint *)(local_18c + -0xc);
                  if ((uVar14 & 0x200) == 0) {
                    *(cRSubGame **)(local_18c + -8) = this + 0x2578;
                    *(undefined4 *)(local_18c + -4) = *(undefined4 *)(this + 0x2584);
                    *(cRSubGame **)(this + 0x2584) = this + iVar18 * 0xdc + 0x1e427c;
                    if (*(int *)(local_18c + -4) != 0) {
                      *(cRSubGame **)(*(int *)(local_18c + -4) + 8) =
                           this + iVar18 * 0xdc + 0x1e427c;
                    }
                    *(uint *)(local_18c + -0xc) = uVar14 | 0x200;
                  }
                  else {
                    RShellError("List ADDafter");
                  }
                  _memcpy(local_18c,pcVar16 + 0x10,0xc);
                }
              }
              else {
                if (cVar3 == (cRSubGame)0xe) {
                  iVar6 = *(int *)PTR__Game_001b60b8;
                  pcVar5 = this + (int)(pcVar5 + 0x13458);
                  *(cRSubGame **)(pcVar16 + 0xc) = this + 0x25d0;
                  if (*(cRSubGame **)(iVar6 + 0x35c) == this + 0x25d0) {
                    *(cRSubGame **)(this + 0x25d8) = pcVar5;
                    *(cRSubGame **)(iVar6 + 0x35c) = pcVar5;
                    uVar14 = *(uint *)(pcVar16 + 4);
                    *(undefined4 *)(pcVar16 + 8) = 0;
                  }
                  else {
                    *(undefined4 *)(pcVar16 + 8) = *(undefined4 *)(this + 0x25d8);
                    *(cRSubGame **)(this + 0x25d8) = pcVar5;
                    *(cRSubGame **)(*(int *)(pcVar16 + 8) + 0xc) = pcVar5;
                  }
                }
                else {
                  pcVar15 = (cRSubGame *)(uint)(byte)((char)cVar3 - 2);
                  bVar21 = 7 < (byte)cVar3;
                  bVar19 = cVar3 == (cRSubGame)0x8;
                  if (!bVar19) {
                    bVar21 = (cRSubGame *)0x1 < pcVar15;
                  }
                  bVar20 = pcVar15 == (cRSubGame *)0x2;
                  if (!bVar21 || (bVar19 || bVar20)) {
                    pcVar5 = this + (int)(pcVar5 + 0x13458);
                    pcVar15 = this + 0x25fc;
                  }
                  if (bVar21 && (!bVar19 && !bVar20)) {
                    if ((((((cVar3 != (cRSubGame)0x9 && cVar3 != (cRSubGame)0xa) &&
                           cVar3 != (cRSubGame)0xb) && cVar3 != (cRSubGame)0xc) &&
                         cVar3 != (cRSubGame)0xd) && cVar3 != (cRSubGame)0x5) &&
                       (cVar3 != (cRSubGame)0x6 && cVar3 != (cRSubGame)0x7)) {
                      *(cRSubGame **)(pcVar16 + 8) = this + 0x25a4;
                      *(undefined4 *)(pcVar16 + 0xc) = *(undefined4 *)(this + 0x25b0);
                      *(cRSubGame **)(this + 0x25b0) = this + (int)(pcVar5 + 0x13458);
                      if (*(int *)(pcVar16 + 0xc) != 0) {
                        *(cRSubGame **)(*(int *)(pcVar16 + 0xc) + 8) =
                             this + (int)(pcVar5 + 0x13458);
                      }
                      *(uint *)(pcVar16 + 4) = uVar14 | 0x200;
                      goto LAB_00033d40;
                    }
                    pcVar5 = this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11);
                    pcVar15 = this + 0x25fc;
                  }
                  *(cRSubGame **)(pcVar16 + 8) = pcVar15;
                  *(undefined4 *)(pcVar16 + 0xc) = *(undefined4 *)(this + 0x2608);
                  *(cRSubGame **)(this + 0x2608) = pcVar5;
                  if (*(int *)(pcVar16 + 0xc) != 0) {
                    *(cRSubGame **)(*(int *)(pcVar16 + 0xc) + 8) = pcVar5;
                  }
                }
                *(uint *)(pcVar16 + 4) = uVar14 | 0x200;
              }
LAB_00033d40:
              (*(code *)**(undefined4 **)pcVar16)
                        (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11));
            }
            cVar3 = pcVar16[0x30];
            if (cVar3 != (cRSubGame)0x17) {
LAB_00033d7c:
              if (cVar3 == (cRSubGame)0x18) goto LAB_00033d94;
              if (cVar3 == (cRSubGame)0x19) {
                if ((iVar18 < *(int *)(this + 0x68)) || (*(int *)(this + 0x70) <= iVar18))
                goto LAB_00033d94;
                AddJetPack(this,(cRSubLoc *)
                                (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11)
                                ),(cRSubGoldy *)(this + 0xf448));
                cVar3 = pcVar16[0x30];
              }
              if (cVar3 != (cRSubGame)0x21) goto LAB_00033d94;
              goto LAB_0003521c;
            }
            if ((((*(uint *)(this + 100) & 0x800) != 0) && (*(int *)(this + 0x68) <= iVar18)) &&
               (iVar18 < *(int *)(this + 0x70))) {
              if (*(int *)(this + 0x2a1c) == 0) {
                iVar6 = 0;
              }
              else if (*(int *)(this + 0x2a84) == 0) {
                iVar6 = 1;
              }
              else if (*(int *)(this + 0x2aec) == 0) {
                iVar6 = 2;
              }
              else if (*(int *)(this + 0x2b54) == 0) {
                iVar6 = 3;
              }
              else if (*(int *)(this + 0x2bbc) == 0) {
                iVar6 = 4;
              }
              else if (*(int *)(this + 0x2c24) == 0) {
                iVar6 = 5;
              }
              else if (*(int *)(this + 0x2c8c) == 0) {
                iVar6 = 6;
              }
              else {
                if (*(int *)(this + 0x2cf4) != 0) goto LAB_00033d94;
                iVar6 = 7;
              }
              iVar13 = iVar6 * 0x68;
              *(undefined4 *)(this + iVar13 + 0x2a1c) = 1;
              *(cRSubGame **)(this + iVar13 + 0x2a20) = this + 0xf448;
              fVar25 = *(float *)(pcVar16 + 0x10);
              fVar24 = *(float *)(pcVar16 + 0x14);
              *(float *)(this + iVar13 + 0x2a08) = *(float *)(pcVar16 + 0x18) + 0.0;
              *(float *)(this + iVar13 + 0x2a04) = fVar24 + 0.6;
              *(float *)(this + iVar13 + 0x2a00) = fVar25 + 0.0;
              iVar11 = *(int *)PTR__Game_001b60b8;
              if ((*(uint *)(this + iVar13 + 0x29f4) & 0x200) == 0) {
                if (*(int *)(iVar11 + 0x35c) == 0) {
                  *(cRSubGame **)(iVar11 + 0x35c) = this + (int)(&DAT_000029f0 + iVar13);
                  *(undefined4 *)(this + iVar13 + 0x29f8) = 0;
                  *(undefined4 *)(*(int *)(iVar11 + 0x35c) + 0xc) = 0;
                }
                else {
                  *(cRSubGame **)(*(int *)(iVar11 + 0x35c) + 8) =
                       this + (int)(&DAT_000029f0 + iVar13);
                  *(int *)(*(int *)(*(int *)(iVar11 + 0x35c) + 8) + 0xc) = *(int *)(iVar11 + 0x35c);
                  iVar13 = *(int *)(*(int *)(iVar11 + 0x35c) + 8);
                  *(int *)(iVar11 + 0x35c) = iVar13;
                  *(undefined4 *)(iVar13 + 8) = 0;
                }
                *(uint *)(this + iVar6 * 0x68 + 0x29f4) =
                     *(uint *)(this + iVar6 * 0x68 + 0x29f4) | 0x200;
              }
              else {
                RShellError("List ADD");
              }
              iVar13 = cRSpriteManager::New
                                 ((int)PTR__gRSpriteManager_001b61e4,*(int *)(this + 0xf7b8),0x2b,-1
                                 );
              *(int *)(this + iVar6 * 0x68 + 0x2a48) = iVar13;
              *(uint *)(iVar13 + 4) = *(uint *)(iVar13 + 4) | 0x800;
              *(undefined4 *)(*(int *)(this + iVar6 * 0x68 + 0x2a48) + 0x78) = 0;
              *(undefined4 *)(*(int *)(this + iVar6 * 0x68 + 0x2a48) + 0x68) = 0;
              *(undefined4 *)(*(int *)(this + iVar6 * 0x68 + 0x2a48) + 0x6c) = 0;
              *(undefined4 *)(*(int *)(this + iVar6 * 0x68 + 0x2a48) + 0x60) = 0x3f19999a;
              *(undefined4 *)(*(int *)(this + iVar6 * 0x68 + 0x2a48) + 100) = 0x3f19999a;
              uVar9 = *(undefined4 *)(this + iVar6 * 0x68 + 0x2a04);
              uVar12 = *(undefined4 *)(this + iVar6 * 0x68 + 0x2a08);
              iVar13 = *(int *)(this + iVar6 * 0x68 + 0x2a48);
              *(undefined4 *)(iVar13 + 0x48) = *(undefined4 *)(this + iVar6 * 0x68 + 0x2a00);
              *(undefined4 *)(iVar13 + 0x4c) = uVar9;
              *(undefined4 *)(iVar13 + 0x50) = uVar12;
              *(cRSubGame **)(this + iVar6 * 0x68 + 0x2a4c) =
                   this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11);
              *(undefined4 *)(this + iVar6 * 0x68 + 0x2a50) = 0;
              if (((int)*(float *)(this + iVar6 * 0x68 + 0x2a08) & 1U) == 0) {
                *(undefined4 *)(this + iVar6 * 0x68 + 0x2a50) = 0x3f000000;
              }
              *(undefined4 *)(this + iVar6 * 0x68 + 0x2a54) = 0x3c520d21;
              cVar3 = pcVar16[0x30];
              goto LAB_00033d7c;
            }
LAB_00033d94:
            if (((((byte)this[iVar17 * 0x44 + iVar18 * 0x220 + 0x1348a] & 0x10) == 0) &&
                (cVar3 == (cRSubGame)0x15 || cVar3 == (cRSubGame)0x1)) &&
               ((*(uint *)(this + 100) & 2) != 0)) {
              lVar27 = CONCAT44((int)((ulonglong)lVar27 >> 0x20),0x3f800000);
              fVar24 = (float)RAND(1.0,"G");
              fVar25 = ((float)lVar27 - *(float *)(this + 0x2f1d7c)) * 0.2 + 0.8;
              uVar14 = uVar23 & 0xfffffff | (uint)(fVar24 < fVar25) << 0x1f |
                       (uint)(fVar24 == fVar25) << 0x1e;
              uVar23 = uVar14 | (uint)(NAN(fVar24) || NAN(fVar25)) << 0x1c;
              bVar1 = (byte)(uVar14 >> 0x18);
              if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1)) {
                if (iVar17 == 0) {
LAB_000352f0:
                  cVar3 = pcVar16[0x74];
                  if (((cVar3 == (cRSubGame)0x1 || cVar3 == (cRSubGame)0x14) ||
                       cVar3 == (cRSubGame)0x15) || (cVar3 == (cRSubGame)0x20)) {
LAB_0003530c:
                    if ((*(int *)(this + 0x68) <= iVar18) &&
                       ((iVar18 < *(int *)(this + 0x70) && (*(int *)(this + 0xf550) != 2)))) {
                      iVar6 = *(int *)(this + 0x58);
                      if (iVar6 == 4) {
                        fVar24 = (float)RAND(1.0,"G2");
                        fVar25 = *(float *)(this + 0x60) * 0.3 + 0.7;
                        uVar14 = uVar23 & 0xfffffff | (uint)(fVar24 < fVar25) << 0x1f |
                                 (uint)(fVar24 == fVar25) << 0x1e;
                        uVar23 = uVar14 | (uint)(NAN(fVar24) || NAN(fVar25)) << 0x1c;
                        bVar1 = (byte)(uVar14 >> 0x18);
                        if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1))
                        goto LAB_000352e0;
                        iVar6 = *(int *)(this + 0x58);
                      }
                      if (iVar6 == 0) {
                        fVar24 = (float)RAND(1.0,"G3");
                        fVar25 = *(float *)(this + 0x60) * 0.6 + 0.4;
                        uVar14 = uVar23 & 0xfffffff | (uint)(fVar24 < fVar25) << 0x1f |
                                 (uint)(fVar24 == fVar25) << 0x1e;
                        uVar23 = uVar14 | (uint)(NAN(fVar24) || NAN(fVar25)) << 0x1c;
                        bVar1 = (byte)(uVar14 >> 0x18);
                        if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1))
                        goto LAB_000352e0;
                      }
LAB_0003521c:
                      AddGarbage(this,(cRSubLoc *)
                                      (this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar18 * 0x88 + iVar17 * 0x11)),
                                 (cRSubGoldy *)(this + 0xf448));
                      cVar3 = pcVar16[0x30];
                      goto LAB_00033dd8;
                    }
                  }
                }
                else {
                  cVar3 = pcVar16[-0x14];
                  if (((cVar3 == (cRSubGame)0x1 || cVar3 == (cRSubGame)0x14) ||
                       cVar3 == (cRSubGame)0x15) || (cVar3 == (cRSubGame)0x20)) {
                    if (iVar17 != 7) goto LAB_000352f0;
                    goto LAB_0003530c;
                  }
                }
              }
LAB_000352e0:
              cVar3 = pcVar16[0x30];
            }
LAB_00033dd8:
            if (cVar3 == (cRSubGame)0x22) {
              if ((iVar18 < *(int *)(this + 0x68)) || (*(int *)(this + 0x70) <= iVar18))
              goto LAB_00034b74;
              cRSaltManager::Add((cRSaltManager *)(this + 0x4800),
                                 (tVector *)(this + iVar17 * 0x44 + iVar18 * 0x220 + 0x13468));
              uVar14 = *(uint *)(this + 100);
            }
            else {
              iVar6 = iVar17 * 0x44 + iVar18 * 0x220;
              if (((((byte)this[iVar6 + 0x1348a] & 8) == 0) &&
                  (cVar3 == (cRSubGame)0xf || cVar3 == (cRSubGame)0x1)) &&
                 (*(int *)(this + 0xf550) != 2)) {
                uVar14 = *(uint *)(this + 100);
                if ((uVar14 & 0x10000) == 0) goto LAB_00033e34;
                lVar27 = CONCAT44((int)((ulonglong)lVar27 >> 0x20),0x3f800000);
                fVar24 = (float)RAND(1.0,"S");
                fVar25 = ((float)lVar27 - *(float *)(this + 0x2f1d80)) * 0.02 + 0.98;
                uVar14 = uVar23 & 0xfffffff | (uint)(fVar24 < fVar25) << 0x1f |
                         (uint)(fVar24 == fVar25) << 0x1e;
                uVar23 = uVar14 | (uint)(NAN(fVar24) || NAN(fVar25)) << 0x1c;
                bVar1 = (byte)(uVar14 >> 0x18);
                if (((!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1)) &&
                    (*(int *)(this + 0x68) <= iVar18)) && (iVar18 < *(int *)(this + 0x70))) {
                  cRSaltManager::Add((cRSaltManager *)(this + 0x4800),
                                     (tVector *)(this + iVar6 + 0x13468));
                }
              }
LAB_00034b74:
              uVar14 = *(uint *)(this + 100);
            }
LAB_00033e34:
            if ((((uVar14 & 0x80) != 0) && (pcVar16[0x30] == (cRSubGame)0x12)) &&
               ((*(int *)(this + 0x68) <= iVar18 && (iVar18 < *(int *)(this + 0x70))))) {
              AddSlug(this,(cRSubLoc *)
                           (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11)),
                      (cRSubGoldy *)(this + 0xf448));
            }
            uVar14 = *(uint *)(local_18c + -0xb4);
            if ((uVar14 & 0x200) == 0) {
              cVar3 = pcVar16[0x30];
              if (cVar3 == (cRSubGame)0x23) {
                if ((uVar14 & 0x400) == 0) {
                  if ((uVar14 & 0x2000) == 0) {
                    if ((uVar14 & 0x800) == 0) {
                      if ((uVar14 & 0x1000) == 0) goto LAB_00033ed0;
                      fVar24 = *(float *)(local_18c + 0x1c);
                      pcVar10 = (cRSubLoc *)
                                (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11)
                                );
                      iVar6 = 7;
                    }
                    else {
                      fVar24 = *(float *)(local_18c + 0x1c);
                      pcVar10 = (cRSubLoc *)
                                (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11)
                                );
                      iVar6 = 6;
                    }
                  }
                  else {
                    fVar24 = *(float *)(local_18c + 0x1c);
                    pcVar10 = (cRSubLoc *)
                              (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11));
                    iVar6 = 8;
                  }
                }
                else {
                  fVar24 = *(float *)(local_18c + 0x1c);
                  pcVar10 = (cRSubLoc *)
                            (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11));
                  iVar6 = 5;
                }
                AddRing(this,pcVar10,iVar6,(cRSubGoldy *)(this + 0xf448),fVar24);
                *(undefined4 *)(this + 0xf7b4) = *(undefined4 *)(pcVar16 + 0x18);
              }
              else if ((byte)((char)cVar3 - 2U) < 6) {
                pcVar5 = this + 0xf7b4;
                fVar25 = *(float *)pcVar5 + 10.0;
                fVar24 = *(float *)(pcVar16 + 0x18);
                uVar22 = uVar23 & 0xfffffff | (uint)(fVar24 < fVar25) << 0x1f |
                         (uint)(fVar24 == fVar25) << 0x1e;
                uVar23 = uVar22 | (uint)(NAN(fVar24) || NAN(fVar25)) << 0x1c;
                bVar1 = (byte)(uVar22 >> 0x18);
                if (((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar23 >> 0x1c) & 1)) ||
                   (*(int *)(this + 0x70) <= iVar18)) goto LAB_00034b7c;
                if ((uVar14 & 0x2000) != 0) {
                  fVar24 = *(float *)(local_18c + 0x1c);
                  pcVar10 = (cRSubLoc *)
                            (this + (int)(&PTR_caseD_6_00013458 + local_190 * 0x88 + iVar17 * 0x11))
                  ;
                  iVar6 = 8;
LAB_00035698:
                  AddRing(this,pcVar10,iVar6,(cRSubGoldy *)(this + 0xf448),fVar24);
                  *(undefined4 *)pcVar5 = *(undefined4 *)local_194;
                  goto LAB_00033ed0;
                }
                if ((uVar14 & 0x800) != 0) {
                  fVar24 = *(float *)(local_18c + 0x1c);
                  pcVar10 = (cRSubLoc *)
                            (this + (int)(&PTR_caseD_6_00013458 + local_190 * 0x88 + iVar17 * 0x11))
                  ;
                  iVar6 = 6;
                  goto LAB_00035698;
                }
                if ((uVar14 & 0x1000) != 0) {
                  fVar24 = *(float *)(local_18c + 0x1c);
                  pcVar10 = (cRSubLoc *)
                            (this + (int)(&PTR_caseD_6_00013458 + local_190 * 0x88 + iVar17 * 0x11))
                  ;
                  iVar6 = 7;
                  goto LAB_00035698;
                }
                if ((*(uint *)(this + 100) & 8) == 0) goto LAB_00033ed0;
                fVar24 = (float)RAND(1.0,"R");
                uVar14 = uVar23 & 0xfffffff | (uint)(fVar24 < 0.7) << 0x1f |
                         (uint)(fVar24 == 0.7) << 0x1e;
                uVar23 = uVar14 | (uint)NAN(fVar24) << 0x1c;
                bVar1 = (byte)(uVar14 >> 0x18);
                if ((((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar23 >> 0x1c) & 1)) &&
                    (*(int *)(this + 0x58) != 7)) || ((byte)((char)pcVar16[0x30] - 5U) < 3))
                goto LAB_00033ed0;
                AddRing(this,(cRSubLoc *)
                             (this + (int)(&PTR_caseD_6_00013458 + iVar18 * 0x88 + iVar17 * 0x11)),4
                        ,(cRSubGoldy *)(this + 0xf448),0.0);
                if (7 < *(int *)(this + 0xf83c)) {
                  *(float *)pcVar5 = *(float *)(pcVar16 + 0x18) + 35.0;
                  goto LAB_00033ed0;
                }
LAB_00034c0c:
                *(undefined4 *)(this + 0xf7b4) = *(undefined4 *)(pcVar16 + 0x18);
              }
              else {
LAB_00034b7c:
                if ((byte)((char)cVar3 - 8U) < 3) {
                  fVar25 = *(float *)(this + 0xf7b4) + 10.0;
                  fVar24 = *(float *)(pcVar16 + 0x18);
                  uVar22 = uVar23 & 0xfffffff | (uint)(fVar24 < fVar25) << 0x1f |
                           (uint)(fVar24 == fVar25) << 0x1e;
                  uVar23 = uVar22 | (uint)(NAN(fVar24) || NAN(fVar25)) << 0x1c;
                  bVar1 = (byte)(uVar22 >> 0x18);
                  if ((!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1)) &&
                     (iVar18 < *(int *)(this + 0x70))) {
                    if ((uVar14 & 0x800) != 0) {
                      AddRing(this,(cRSubLoc *)
                                   (this + (int)(&PTR_caseD_6_00013458 +
                                                iVar18 * 0x88 + iVar17 * 0x11)),2,
                              (cRSubGoldy *)(this + 0xf448),*(float *)(local_18c + 0x1c));
                      goto LAB_00034c0c;
                    }
                    fVar24 = (float)RAND(1.0,"R2");
                    uVar14 = uVar23 & 0xfffffff | (uint)(fVar24 < 0.7) << 0x1f |
                             (uint)(fVar24 == 0.7) << 0x1e;
                    uVar23 = uVar14 | (uint)NAN(fVar24) << 0x1c;
                    bVar1 = (byte)(uVar14 >> 0x18);
                    if (((!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar23 >> 0x1c) & 1)) ||
                        (*(int *)(this + 0x58) == 7)) ||
                       ((*(uint *)(local_18c + -0xb4) & 0x800) != 0)) {
                      AddRing(this,(cRSubLoc *)
                                   (this + (int)(&PTR_caseD_6_00013458 +
                                                iVar18 * 0x88 + iVar17 * 0x11)),2,
                              (cRSubGoldy *)(this + 0xf448),0.0);
                      *(undefined4 *)(this + 0xf7b4) = *(undefined4 *)(pcVar16 + 0x18);
                    }
                  }
                }
              }
            }
          }
LAB_00033ed0:
          iVar17 = iVar17 + 1;
          local_194 = local_194 + 0x44;
          pcVar16 = pcVar16 + 0x44;
        } while (iVar17 != 8);
        iVar17 = *(int *)(this + 0x74);
        while (iVar17 <= iVar18) {
          if (*(int *)(this + 0x58) != 2) {
            cRWorld::Add((cRWorld *)(this + 0xf378),
                         (cRSubLoc *)(this + (int)(&PTR_caseD_6_00013458 + iVar17 * 0x88)));
            iVar17 = *(int *)(this + 0x74);
          }
          iVar17 = iVar17 + 1;
          *(int *)(this + 0x74) = iVar17;
        }
        *this = (cRSubGame)0x0;
        iVar18 = iVar18 + 1;
        local_190 = local_190 + 1;
        local_18c = local_18c + 0xdc;
      } while (iVar18 < *(int *)(this + 0x38));
      iVar6 = *(int *)(this + 0x58);
    }
    if (iVar6 != 4) {
      *(undefined1 *)(*(int *)(this + 0x85e0) + 0x2c4) = 0;
      cRBorder::AddTextNumber(*(cRBorder **)(this + 0x85e0),*(int *)(this + 0xf714));
      if (*(int *)(this + 0x27b4) < *(int *)(this + 0xf714)) {
        *(int *)(this + 0x27b4) = *(int *)(this + 0xf714);
        *(undefined1 *)(*(int *)(this + 0x85e4) + 0x2c4) = 0;
        cRBorder::AddTextNumber(*(cRBorder **)(this + 0x85e4),*(int *)(this + 0x27b4));
        iVar17 = *(int *)(this + 0x54);
        break;
      }
      goto switchD_00034244_caseD_2;
    }
    iVar17 = *(int *)(this + 0x85e0);
    pcVar7 = (char *)cRTimeTrial::TimeString
                               ((cRTimeTrial *)(this + 0x2e09dc),(cRTime *)(this + 0xf718));
    Rstrcpy((char *)(iVar17 + 0x2c4),pcVar7);
    iVar17 = (*(int *)(this + 0x5c) + 0x16) * 0x38;
    if (*(int *)(this + iVar17 + 0x2a01b0) == 1) {
      iVar6 = *(int *)(this + 0x85e4);
      pcVar7 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(this + 0x2e09dc),
                                  (cRTime *)(this + (int)(&DAT_002a01b4 + iVar17)));
      Rstrcpy((char *)(iVar6 + 0x2c4),pcVar7);
      iVar17 = *(int *)(this + 0x54);
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x85e4));
      iVar17 = *(int *)(this + 0x54);
    }
    break;
  case 3:
    this[0x12] = (cRSubGame)0x1;
    *(undefined4 *)(this + 0x54) = 4;
    *(undefined4 *)(this + 0x14) = *(undefined4 *)(this + 0x18);
    cRSubPause::Init((cRSubPause *)(this + 0x1c));
    goto LAB_000343c4;
  case 4:
LAB_000343c4:
    cRSubPause::AI((cRSubPause *)(this + 0x1c));
    return;
  case 7:
    if (this[0x2e09cd] != (cRSubGame)0x0) {
      this[0x2e09cc] = (cRSubGame)0x1;
      StartLevel(this,0);
      *(undefined4 *)(this + 0x54) = 2;
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x328) = 1;
      return;
    }
    this[0x2e09cc] = (cRSubGame)0x0;
    StartLevel(this,0);
    *(undefined4 *)(this + 0x54) = 2;
    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x328) = 1;
    return;
  }
  puVar2 = PTR__Game_001b60b8;
  iVar6 = *(int *)PTR__Game_001b60b8;
  local_88 = *(undefined4 *)(iVar6 + 0x100);
  uStack_84 = *(undefined4 *)(iVar6 + 0x104);
  uStack_80 = *(undefined4 *)(iVar6 + 0x108);
  uStack_7c = *(undefined4 *)(iVar6 + 0x10c);
  local_78 = *(undefined4 *)(iVar6 + 0x110);
  uStack_74 = *(undefined4 *)(iVar6 + 0x114);
  uStack_70 = *(undefined4 *)(iVar6 + 0x118);
  uStack_6c = *(undefined4 *)(iVar6 + 0x11c);
  local_68 = *(undefined4 *)(iVar6 + 0x120);
  uStack_64 = *(undefined4 *)(iVar6 + 0x124);
  uStack_60 = *(undefined4 *)(iVar6 + 0x128);
  uStack_5c = *(undefined4 *)(iVar6 + 300);
  local_58 = *(undefined4 *)(iVar6 + 0x130);
  uStack_54 = *(undefined4 *)(iVar6 + 0x134);
  uStack_50 = *(undefined4 *)(iVar6 + 0x138);
  uStack_4c = *(undefined4 *)(iVar6 + 0x13c);
  this[1] = (cRSubGame)0x0;
  if (iVar17 == 1) {
    tMatrix::Identity((tMatrix *)&local_188);
    local_154 = 0x40400000;
    *(undefined4 *)(*(int *)puVar2 + 0x21c) = 0x42f00000;
  }
  else {
    cRCameraman::AI((cRCameraman *)(this + 0xf630));
    if (*(int *)(this + 0x133dc) != 0) {
      local_188 = *(uint *)(this + 0x133e0);
      acStack_184 = *(char (*) [4])(this + 0x133e4);
      acStack_180 = *(char (*) [4])(this + 0x133e8);
      acStack_17c = *(char (*) [4])(this + 0x133ec);
      local_178 = *(undefined4 *)(this + 0x133f0);
      uStack_174 = *(undefined4 *)(this + 0x133f4);
      uStack_170 = *(undefined4 *)(this + 0x133f8);
      uStack_16c = *(undefined4 *)(this + 0x133fc);
      local_168 = *(undefined4 *)(this + 0x13400);
      uStack_164 = *(undefined4 *)(this + 0x13404);
      uStack_160 = *(undefined4 *)(this + 0x13408);
      uStack_15c = *(undefined4 *)(this + 0x1340c);
      local_158 = *(undefined4 *)(this + 0x13410);
      local_154 = *(undefined4 *)(this + 0x13414);
      uStack_150 = *(undefined4 *)(this + 0x13418);
      uStack_14c = *(undefined4 *)(this + 0x1341c);
      this[1] = this[0x13428];
      *(undefined4 *)(*(int *)puVar2 + 0x21c) = 0x42f00000;
      cVar3 = this[1];
      goto joined_r0x000340d0;
    }
    local_188 = *(uint *)(this + 0xf630);
    acStack_184 = *(char (*) [4])(this + 0xf634);
    acStack_180 = *(char (*) [4])(this + 0xf638);
    acStack_17c = *(char (*) [4])(this + 0xf63c);
    local_178 = *(undefined4 *)(this + 0xf640);
    uStack_174 = *(undefined4 *)(this + 0xf644);
    uStack_170 = *(undefined4 *)(this + 0xf648);
    uStack_16c = *(undefined4 *)(this + 0xf64c);
    local_168 = *(undefined4 *)(this + 0xf650);
    uStack_164 = *(undefined4 *)(this + 0xf654);
    uStack_160 = *(undefined4 *)(this + 0xf658);
    uStack_15c = *(undefined4 *)(this + 0xf65c);
    local_158 = *(undefined4 *)(this + 0xf660);
    local_154 = *(undefined4 *)(this + 0xf664);
    uStack_150 = *(undefined4 *)(this + 0xf668);
    uStack_14c = *(undefined4 *)(this + 0xf66c);
    this[1] = this[0xf6fc];
    *(undefined4 *)(*(int *)puVar2 + 0x21c) = *(undefined4 *)(this + 0xf6f8);
  }
  cVar3 = this[1];
joined_r0x000340d0:
  if (cVar3 == (cRSubGame)0x0) {
    tMatrix::LinearInterpolate
              ((tMatrix *)(*(int *)PTR__Game_001b60b8 + 0x100),(tMatrix *)&local_88,
               (tMatrix *)&local_188,0.9);
  }
  else {
    iVar17 = *(int *)PTR__Game_001b60b8;
    *(uint *)(iVar17 + 0x100) = local_188;
    *(char (*) [4])(iVar17 + 0x104) = acStack_184;
    *(char (*) [4])(iVar17 + 0x108) = acStack_180;
    *(char (*) [4])(iVar17 + 0x10c) = acStack_17c;
    *(undefined4 *)(iVar17 + 0x110) = local_178;
    *(undefined4 *)(iVar17 + 0x114) = uStack_174;
    *(undefined4 *)(iVar17 + 0x118) = uStack_170;
    *(undefined4 *)(iVar17 + 0x11c) = uStack_16c;
    *(undefined4 *)(iVar17 + 0x120) = local_168;
    *(undefined4 *)(iVar17 + 0x124) = uStack_164;
    *(undefined4 *)(iVar17 + 0x128) = uStack_160;
    *(undefined4 *)(iVar17 + 300) = uStack_15c;
    *(undefined4 *)(iVar17 + 0x130) = local_158;
    *(undefined4 *)(iVar17 + 0x134) = local_154;
    *(undefined4 *)(iVar17 + 0x138) = uStack_150;
    *(undefined4 *)(iVar17 + 0x13c) = uStack_14c;
    this[1] = (cRSubGame)0x0;
  }
  return;
}
