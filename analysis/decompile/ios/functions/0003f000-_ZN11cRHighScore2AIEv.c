/*
 * mangled: _ZN11cRHighScore2AIEv
 * demangled: cRHighScore::AI()
 * address: 0003f000
 * size: 2272
 */

/* cRHighScore::AI() */

void __thiscall cRHighScore::AI(cRHighScore *this)

{
  char cVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  cRHighScore *pcVar11;
  cRHighScore *pcVar12;
  int iVar13;
  bool bVar14;

  puVar2 = PTR__Game_001b60b8;
  if (this[0x10] == (cRHighScore)0x0) {
    uVar8 = *(uint *)(*(int *)(this + 0x20) + 0x194);
    if ((uVar8 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x20) + 0x194) = uVar8 & 0xffffffdf;
      puVar2 = PTR__Game_001b60b8;
      iVar5 = *(int *)PTR__Game_001b60b8;
      *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa8) = *(undefined4 *)(this + 8);
      cRBorderManager::KillBorders((cRBorderManager *)(iVar5 + 0xd14));
      *(undefined1 *)(*(int *)puVar2 + 0x2c1) = 0;
      *(undefined4 *)(*(int *)puVar2 + 0x2c4) = 0;
      cRBackdrop::SetZoom((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),0.0);
      iVar5 = *(int *)(this + 8);
      if (iVar5 == 1) {
        iVar5 = 3;
        *(undefined4 *)(this + 8) = 3;
      }
      else if (iVar5 == 3) {
        *(undefined4 *)(this + 8) = 0;
        iVar5 = 0;
      }
      else if (iVar5 == 0) {
        iVar5 = 1;
        *(undefined4 *)(this + 8) = 1;
      }
      *(int *)(PTR__gConfig_001b60d4 + 0xa8) = iVar5;
      Init((int)this,*(int *)(this + 8));
      return;
    }
    uVar8 = *(uint *)(*(int *)(this + 0x1c) + 0x194);
    if ((uVar8 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x1c) + 0x194) = uVar8 & 0xffffffdf;
      puVar2 = PTR__Game_001b60b8;
      if (*(int *)(this + 4) == 1) {
        *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 10;
        *(undefined1 *)(*(int *)puVar2 + 0x2c0) = 1;
      }
      else if (*(int *)(this + 4) == 0) {
        *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 4;
      }
      *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa8) = *(undefined4 *)(this + 8);
      puVar2 = PTR__Game_001b60b8;
      cRBorderManager::KillBorders((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      *(undefined1 *)(*(int *)puVar2 + 0x2c1) = 0;
      *(undefined4 *)(*(int *)puVar2 + 0x2c4) = 0;
      cRBackdrop::SetZoom((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),0.0);
      return;
    }
    SetExitNextPos(this);
    iVar5 = *(int *)PTR__Game_001b60b8;
    if (*(int *)(&DAT_00312d24 + iVar5) < 1) {
      return;
    }
    iVar13 = 0;
    iVar4 = 0;
    do {
      if (((*(int *)(*(int *)(&DAT_00312d20 + iVar5) + iVar4) == 1) &&
          (iVar5 = *(int *)(this + iVar13 * 4 + 0xcc), iVar5 != 0)) &&
         ((*(uint *)(iVar5 + 0x194) & 0x1020) == 0x20)) {
        *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffffffdf;
        puVar2 = PTR__Game_001b60b8;
        *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 10;
        *(undefined1 *)(*(int *)puVar2 + 0x2c0) = 1;
        iVar5 = *(int *)puVar2;
        *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa8) = *(undefined4 *)(this + 8);
        cRBorderManager::KillBorders((cRBorderManager *)(iVar5 + 0xd14));
        *(undefined1 *)(*(int *)puVar2 + 0x2c1) = 0;
        *(undefined4 *)(*(int *)puVar2 + 0x2c4) = 0;
        cRBackdrop::SetZoom((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),0.0);
        iVar5 = *(int *)(this + 8);
        if (iVar5 == 1) {
          cRSubHighScore::MiniLoad((cRSubHighScore *)(&DAT_00312d20 + *(int *)puVar2),iVar13 + 0xb);
        }
        else if (iVar5 == 3) {
          cRSubHighScore::MiniLoad((cRSubHighScore *)(&DAT_00312d20 + *(int *)puVar2),iVar13 + 0x4a)
          ;
        }
        else if (iVar5 == 0) {
          cRSubHighScore::MiniLoad((cRSubHighScore *)(&DAT_00312d20 + *(int *)puVar2),iVar13);
        }
        puVar2 = PTR__Game_001b60b8;
        *(int *)(&DAT_00353548 + *(int *)PTR__Game_001b60b8) = *(int *)PTR__Game_001b60b8 + 0x333a80
        ;
        (&DAT_00353544)[*(int *)puVar2] = 1;
        (&DAT_00353545)[*(int *)puVar2] = 1;
        *(undefined4 *)(&DAT_0035354c + *(int *)puVar2) = 0x12;
        *(undefined4 *)(&DAT_00364944 + *(int *)puVar2) = 0;
        *(undefined4 *)(*(int *)puVar2 + 0x72bd0) =
             *(undefined4 *)(*(int *)(&DAT_00353548 + *(int *)puVar2) + 0x2c);
      }
      iVar13 = iVar13 + 1;
      iVar4 = iVar4 + 0x38;
      iVar5 = *(int *)PTR__Game_001b60b8;
    } while (iVar13 < *(int *)(&DAT_00312d24 + iVar5));
    return;
  }
  if (*(int *)(*(int *)PTR__Game_001b60b8 + 0xbf0) == 0) {
    *(uint *)(*(int *)(this + 0x28) + 0x194) = *(uint *)(*(int *)(this + 0x28) + 0x194) | 0x10;
    *(uint *)(*(int *)(this + 0x28) + 0x194) = *(uint *)(*(int *)(this + 0x28) + 0x194) | 4;
    *(uint *)(*(int *)(this + 0x24) + 0x194) = *(uint *)(*(int *)(this + 0x24) + 0x194) | 0x10;
    *(uint *)(*(int *)(this + 0x24) + 0x194) = *(uint *)(*(int *)(this + 0x24) + 0x194) | 4;
    *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
         *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) | 0x10;
  }
  iVar5 = *(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c);
  uVar8 = *(uint *)(iVar5 + 0x194);
  if ((uVar8 & 0x4000) != 0) {
    *(uint *)(iVar5 + 0x194) = uVar8 & 0xffffbfff;
    puVar3 = PTR__gConfig_001b60d4;
    iVar5 = *(int *)puVar2;
    *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa8) = *(undefined4 *)(this + 8);
    cRBorderManager::KillBorders((cRBorderManager *)(iVar5 + 0xd14));
    *(undefined1 *)(*(int *)puVar2 + 0x2c1) = 0;
    *(undefined4 *)(*(int *)puVar2 + 0x2c4) = 0;
    cRBackdrop::SetZoom((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),0.0);
    cRSpriteManager::KillGame();
    Rstrcpy((char *)(*(int *)(this + 0x14) * 0x38 + *(int *)(&DAT_00312d20 + *(int *)puVar2) + 0x25)
            ,(char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
    Rstrcpy((char *)(*(int *)puVar2 + 0x148),
            (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
    Rstrcpy(puVar3 + 0x60,(char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
    cRSubHighScore::SaveMiniData((cRSubHighScore *)(&DAT_00312d20 + *(int *)puVar2));
    gRegisterSaveFile("ism.cfg",puVar3,0xf0);
    iVar5 = *(int *)puVar2;
    if (*(int *)(iVar5 + 0x72bd0) == 0) {
      cRSubHighScore::MiniDelete((cRSubHighScore *)(&DAT_00312d20 + iVar5),10);
      *(undefined4 *)(*(int *)puVar2 + 0x15c) = 2;
      *(undefined4 *)(&DAT_00376620 + *(int *)puVar2) = 2;
      *(undefined1 *)(*(int *)puVar2 + 0x2c0) = 1;
      iVar5 = *(int *)puVar2;
    }
    if (*(int *)(iVar5 + 0x72bd0) != 1) {
      return;
    }
    cRSubHighScore::MiniDelete((cRSubHighScore *)(&DAT_00312d20 + iVar5),0x15);
    *(undefined4 *)(*(int *)puVar2 + 0x15c) = 10;
    *(undefined4 *)(&DAT_00376620 + *(int *)puVar2) = 2;
    *(undefined1 *)(*(int *)puVar2 + 0x2c0) = 1;
    return;
  }
  if ((uVar8 & 0x20) == 0) {
    cVar1 = PTR__gConfig_001b60d4[0x60];
    bVar14 = cVar1 == '\0';
    if (bVar14) {
      cVar1 = *(char *)(iVar5 + 0x2c5);
    }
    if (!bVar14 || cVar1 != '\0') goto LAB_0003f0d4;
  }
  *(uint *)(iVar5 + 0x194) = uVar8 & 0xffffffdf;
  *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
       *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) & 0xffffffef;
  if (*(int *)(*(int *)puVar2 + 0xbf0) != 0) {
    return;
  }
  cKeyPad::Init((cKeyPad *)(*(int *)puVar2 + 0xbf0),
                *(cRBorder **)(this + *(int *)(this + 0x14) * 4 + 0x7c));
  *(uint *)(*(int *)(this + 0x28) + 0x194) = *(uint *)(*(int *)(this + 0x28) + 0x194) & 0xffffffef;
  *(uint *)(*(int *)(this + 0x28) + 0x194) = *(uint *)(*(int *)(this + 0x28) + 0x194) & 0xfffffffb;
  *(uint *)(*(int *)(this + 0x24) + 0x194) = *(uint *)(*(int *)(this + 0x24) + 0x194) & 0xffffffef;
  *(uint *)(*(int *)(this + 0x24) + 0x194) = *(uint *)(*(int *)(this + 0x24) + 0x194) & 0xfffffffb;
LAB_0003f0d4:
  puVar2 = PTR__Game_001b60b8;
  if (*(int *)(*(int *)PTR__Game_001b60b8 + 0xbf0) == 0) {
    uVar8 = *(uint *)(*(int *)(this + 0x28) + 0x194);
    if ((uVar8 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x28) + 0x194) = uVar8 & 0xffffffdf;
      *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
           *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) | 0x8000000;
    }
    uVar8 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar8 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar8 & 0xffffffdf;
      iVar5 = *(int *)puVar2;
      *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa8) = *(undefined4 *)(this + 8);
      cRBorderManager::KillBorders((cRBorderManager *)(iVar5 + 0xd14));
      *(undefined1 *)(*(int *)puVar2 + 0x2c1) = 0;
      *(undefined4 *)(*(int *)puVar2 + 0x2c4) = 0;
      cRBackdrop::SetZoom((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),0.0);
      cRSpriteManager::KillGame();
      iVar13 = *(int *)puVar2;
      iVar5 = *(int *)(this + 8);
      pcVar11 = *(cRHighScore **)(this + 0x14);
      if (iVar5 == 1) {
        this = pcVar11 + 0xb;
      }
      else if (iVar5 == 3) {
        this = pcVar11 + 0x4a;
      }
      else if (iVar5 == 0) {
        this = pcVar11;
      }
      cRSubHighScore::MiniDelete((cRSubHighScore *)(&DAT_00312d20 + iVar13),(int)this);
LAB_0003f1c4:
      if ((int)pcVar11 < 10) {
        while (iVar5 != 1) {
          if (iVar5 == 3) {
            iVar4 = (int)pcVar11 * 0x38 + iVar13;
            pcVar11 = pcVar11 + 1;
            *(undefined4 *)(&DAT_00313d58 + iVar4) = *(undefined4 *)(&DAT_00313d90 + iVar4);
            *(undefined4 *)(&DAT_00313d5c + iVar4) = *(undefined4 *)(&DAT_00313d94 + iVar4);
            *(undefined4 *)(&DAT_00313d60 + iVar4) = *(undefined4 *)(&DAT_00313d98 + iVar4);
            *(undefined4 *)(&DAT_00313d64 + iVar4) = *(undefined4 *)(&DAT_00313d9c + iVar4);
            *(undefined4 *)(&DAT_00313d68 + iVar4) = *(undefined4 *)(&DAT_00313da0 + iVar4);
            *(undefined4 *)(&DAT_00313d6c + iVar4) = *(undefined4 *)(&DAT_00313da4 + iVar4);
            *(undefined4 *)(&DAT_00313d70 + iVar4) = *(undefined4 *)(&DAT_00313da8 + iVar4);
            *(undefined4 *)(&DAT_00313d74 + iVar4) = *(undefined4 *)(&DAT_00313dac + iVar4);
            *(undefined4 *)(&DAT_00313d78 + iVar4) = *(undefined4 *)(&DAT_00313db0 + iVar4);
            *(undefined4 *)(&DAT_00313d7c + iVar4) = *(undefined4 *)(&DAT_00313db4 + iVar4);
            *(undefined4 *)(&DAT_00313d80 + iVar4) = *(undefined4 *)(&DAT_00313db8 + iVar4);
            *(undefined4 *)(&DAT_00313d84 + iVar4) = *(undefined4 *)(&DAT_00313dbc + iVar4);
            *(undefined4 *)(&DAT_00313d88 + iVar4) = *(undefined4 *)(&DAT_00313dc0 + iVar4);
            *(undefined4 *)(&DAT_00313d8c + iVar4) = *(undefined4 *)(&DAT_00313dc4 + iVar4);
            goto LAB_0003f1c4;
          }
          if (iVar5 != 0) goto LAB_0003f5f8;
          pcVar12 = pcVar11 + 1;
          iVar9 = (int)pcVar12 * 0x38 + iVar13;
          iVar4 = (int)pcVar11 * 0x38 + iVar13;
          uVar6 = *(undefined4 *)(&DAT_00312d2c + iVar9);
          uVar7 = *(undefined4 *)(&DAT_00312d30 + iVar9);
          uVar10 = *(undefined4 *)(&DAT_00312d34 + iVar9);
          *(undefined4 *)(&DAT_00312d28 + iVar4) = *(undefined4 *)(&DAT_00312d28 + iVar9);
          *(undefined4 *)(&DAT_00312d2c + iVar4) = uVar6;
          *(undefined4 *)(&DAT_00312d30 + iVar4) = uVar7;
          *(undefined4 *)(&DAT_00312d34 + iVar4) = uVar10;
          uVar6 = *(undefined4 *)(&DAT_00312d3c + iVar9);
          uVar7 = *(undefined4 *)(&DAT_00312d40 + iVar9);
          uVar10 = *(undefined4 *)(&DAT_00312d44 + iVar9);
          *(undefined4 *)(&DAT_00312d38 + iVar4) = *(undefined4 *)(&DAT_00312d38 + iVar9);
          *(undefined4 *)(&DAT_00312d3c + iVar4) = uVar6;
          *(undefined4 *)(&DAT_00312d40 + iVar4) = uVar7;
          *(undefined4 *)(&DAT_00312d44 + iVar4) = uVar10;
          uVar6 = *(undefined4 *)(&DAT_00312d4c + iVar9);
          uVar7 = *(undefined4 *)(&DAT_00312d50 + iVar9);
          uVar10 = *(undefined4 *)(&DAT_00312d54 + iVar9);
          *(undefined4 *)(&DAT_00312d48 + iVar4) = *(undefined4 *)(&DAT_00312d48 + iVar9);
          *(undefined4 *)(&DAT_00312d4c + iVar4) = uVar6;
          *(undefined4 *)(&DAT_00312d50 + iVar4) = uVar7;
          *(undefined4 *)(&DAT_00312d54 + iVar4) = uVar10;
          uVar6 = *(undefined4 *)(&DAT_00312d5c + iVar9);
          *(undefined4 *)(&DAT_00312d58 + iVar4) = *(undefined4 *)(&DAT_00312d58 + iVar9);
          *(undefined4 *)(&DAT_00312d5c + iVar4) = uVar6;
          pcVar11 = pcVar12;
          if (9 < (int)pcVar12) goto LAB_0003f23c;
        }
        iVar4 = (int)pcVar11 * 0x38 + iVar13;
        *(undefined4 *)(&DAT_00312f90 + iVar4) = *(undefined4 *)(&DAT_00312fc8 + iVar4);
        *(undefined4 *)(&DAT_00312f94 + iVar4) = *(undefined4 *)(&DAT_00312fcc + iVar4);
        *(undefined4 *)(&DAT_00312f98 + iVar4) = *(undefined4 *)(&DAT_00312fd0 + iVar4);
        *(undefined4 *)(&DAT_00312f9c + iVar4) = *(undefined4 *)(&DAT_00312fd4 + iVar4);
        *(undefined4 *)(&DAT_00312fa0 + iVar4) = *(undefined4 *)(&DAT_00312fd8 + iVar4);
        *(undefined4 *)(&DAT_00312fa4 + iVar4) = *(undefined4 *)(&DAT_00312fdc + iVar4);
        *(undefined4 *)(&DAT_00312fa8 + iVar4) = *(undefined4 *)(&DAT_00312fe0 + iVar4);
        *(undefined4 *)(&DAT_00312fac + iVar4) = *(undefined4 *)(&DAT_00312fe4 + iVar4);
        *(undefined4 *)(&DAT_00312fb0 + iVar4) = *(undefined4 *)(&DAT_00312fe8 + iVar4);
        *(undefined4 *)(&DAT_00312fb4 + iVar4) = *(undefined4 *)(&DAT_00312fec + iVar4);
        *(undefined4 *)(&DAT_00312fb8 + iVar4) = *(undefined4 *)(&DAT_00312ff0 + iVar4);
        *(undefined4 *)(&DAT_00312fbc + iVar4) = *(undefined4 *)(&DAT_00312ff4 + iVar4);
        *(undefined4 *)(&DAT_00312fc0 + iVar4) = *(undefined4 *)(&DAT_00312ff8 + iVar4);
        *(undefined4 *)(&DAT_00312fc4 + iVar4) = *(undefined4 *)(&DAT_00312ffc + iVar4);
LAB_0003f5f8:
        pcVar11 = pcVar11 + 1;
        goto LAB_0003f1c4;
      }
LAB_0003f23c:
      puVar2 = PTR__Game_001b60b8;
      iVar5 = *(int *)PTR__Game_001b60b8;
      if (*(int *)(iVar5 + 0x72bd0) == 0) {
        cRSubHighScore::MiniDelete((cRSubHighScore *)(&DAT_00312d20 + iVar5),10);
        *(undefined4 *)(*(int *)puVar2 + 0x15c) = 2;
        *(undefined4 *)(&DAT_00376620 + *(int *)puVar2) = 2;
        *(undefined1 *)(*(int *)puVar2 + 0x2c0) = 1;
        iVar5 = *(int *)puVar2;
      }
      if (*(int *)(iVar5 + 0x72bd0) == 1) {
        cRSubHighScore::MiniDelete((cRSubHighScore *)(&DAT_00312d20 + iVar5),0x15);
        *(undefined4 *)(*(int *)puVar2 + 0x15c) = 10;
        *(undefined4 *)(&DAT_00376620 + *(int *)puVar2) = 2;
        *(undefined1 *)(*(int *)puVar2 + 0x2c0) = 1;
      }
    }
  }
  return;
}
