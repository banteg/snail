/*
 * mangled: _ZN7cRIntro2AIEv
 * demangled: cRIntro::AI()
 * address: 00065120
 * size: 1768
 */

/* cRIntro::AI() */

void __thiscall cRIntro::AI(cRIntro *this)

{
  byte bVar1;
  bool bVar2;
  undefined *puVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  uint uVar10;
  float fVar11;
  int iVar12;

  puVar3 = PTR__Game_001b60b8;
  iVar5 = *(int *)PTR__Game_001b60b8;
  uVar10 = in_fpscr & 0xfffffff |
           (uint)(*(float *)(iVar5 + 0x3c) == *(float *)(iVar5 + 0x44)) << 0x1e;
  if (!SUB41(uVar10 >> 0x1e,0)) {
    cRBorderManager::KillBorders((cRBorderManager *)(iVar5 + 0xd14));
    cRSpriteManager::KillGame();
    Init(this);
  }
  cVar4 = RShellInkey();
  if (((cVar4 == '\0') && ((*(uint *)(*(int *)(*(int *)puVar3 + 0x224) + 0x30) & 0x4000) == 0)) ||
     (*(undefined4 *)(this + 0x10) = 0, this[4] == (cRIntro)0x0)) {
    iVar5 = *(int *)(this + 0x30);
    uVar7 = *(uint *)(iVar5 + 0x194);
  }
  else {
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x30));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x34));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x40));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x38));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x3c));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x44));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x48));
    cRMouse::SetActive((cRMouse *)(*(int *)puVar3 + 0x228));
    iVar5 = *(int *)(this + 0x30);
    this[4] = (cRIntro)0x0;
    uVar7 = *(uint *)(iVar5 + 0x194);
  }
  if ((uVar7 & 0x20) == 0) {
    uVar7 = *(uint *)(*(int *)(this + 0x34) + 0x194);
    if ((uVar7 & 0x20) == 0) {
      uVar7 = *(uint *)(*(int *)(this + 0x38) + 0x194);
      if ((uVar7 & 0x20) == 0) {
        uVar7 = *(uint *)(*(int *)(this + 0x40) + 0x194);
        if ((uVar7 & 0x20) == 0) {
          uVar7 = *(uint *)(*(int *)(this + 0x3c) + 0x194);
          if ((uVar7 & 0x20) == 0) {
            uVar7 = *(uint *)(*(int *)(this + 0x48) + 0x194);
            if ((uVar7 & 0x20) == 0) {
              uVar7 = *(uint *)(*(int *)(this + 0x44) + 0x194);
              if ((uVar7 & 0x20) != 0) {
                *(uint *)(*(int *)(this + 0x44) + 0x194) = uVar7 & 0xffffffdf;
                puVar3 = PTR__Game_001b60b8;
                cRBorderManager::KillBorders
                          ((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
                cRSpriteManager::KillGame();
                *(undefined4 *)(*(int *)puVar3 + 0x15c) = 0x1f;
                *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
              }
            }
            else {
              *(uint *)(*(int *)(this + 0x48) + 0x194) = uVar7 & 0xffffffdf;
              puVar3 = PTR__Game_001b60b8;
              cRBorderManager::KillBorders((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
              cRSpriteManager::KillGame();
              *(undefined4 *)(*(int *)puVar3 + 0x15c) = 4;
              *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
            }
            fVar11 = *(float *)(this + 0x10) + *(float *)(this + 0x14);
            uVar10 = uVar10 & 0xfffffff | (uint)(fVar11 < 1.0) << 0x1f |
                     (uint)(fVar11 == 1.0) << 0x1e;
            uVar7 = uVar10 | (uint)NAN(fVar11) << 0x1c;
            *(float *)(this + 0x10) = fVar11;
            bVar1 = (byte)(uVar10 >> 0x18);
            if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar7 >> 0x1c) & 1)) {
              iVar9 = 0;
              iVar5 = 0;
              *(undefined4 *)(this + 0x10) = 0;
              do {
                iVar8 = *(int *)this;
                iVar9 = iVar9 + 1;
                if (iVar8 == 1) {
                  uVar6 = gRMathRand2();
                  puVar3 = PTR__Game_001b60b8;
                  fVar11 = (float)VectorSignedToFloat(uVar6,(byte)(uVar7 >> 0x16) & 3);
                  iVar8 = (int)(fVar11 * 3.0517578e-05 * 4.0) + 0xb;
                  iVar5 = *(int *)(&DAT_00312d28 + iVar8 * 0x38 + *(int *)PTR__Game_001b60b8);
                  if (iVar5 == 1) {
                    cRSubHighScore::MiniLoad
                              ((cRSubHighScore *)(&DAT_00312d20 + *(int *)PTR__Game_001b60b8),iVar8)
                    ;
                    iVar5 = *(int *)puVar3 + 0x72000;
                    *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 1;
                    iVar8 = *(int *)this;
                    bVar2 = true;
                  }
                  else {
LAB_0006527c:
                    iVar8 = *(int *)this;
LAB_00065280:
                    bVar2 = false;
                  }
                }
                else if (iVar8 == 3) {
                  uVar6 = gRMathRand2();
                  puVar3 = PTR__Game_001b60b8;
                  fVar11 = (float)VectorSignedToFloat(uVar6,(byte)(uVar7 >> 0x16) & 3);
                  iVar8 = (int)(fVar11 * 3.0517578e-05 * 51.0) + 0x16;
                  iVar12 = iVar8 * 0x38 + *(int *)PTR__Game_001b60b8;
                  iVar5 = iVar12 + 0x312000;
                  if (*(int *)(&DAT_00312d28 + iVar12) != 1) goto LAB_0006527c;
                  cRSubHighScore::MiniLoad
                            ((cRSubHighScore *)(&DAT_00312d20 + *(int *)PTR__Game_001b60b8),iVar8);
                  iVar5 = *(int *)puVar3 + 0x72000;
                  *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 4;
                  iVar8 = *(int *)this;
                  bVar2 = true;
                }
                else {
                  if (iVar8 != 0) goto LAB_00065280;
                  uVar6 = gRMathRand2();
                  puVar3 = PTR__Game_001b60b8;
                  fVar11 = (float)VectorSignedToFloat(uVar6,(byte)(uVar7 >> 0x16) & 3);
                  iVar12 = (int)(fVar11 * 3.0517578e-05 * 4.0);
                  iVar8 = iVar12 * 0x38 + *(int *)PTR__Game_001b60b8;
                  iVar5 = iVar8 + 0x312000;
                  if (*(int *)(&DAT_00312d28 + iVar8) != 1) goto LAB_0006527c;
                  cRSubHighScore::MiniLoad
                            ((cRSubHighScore *)(&DAT_00312d20 + *(int *)PTR__Game_001b60b8),iVar12);
                  iVar5 = *(int *)puVar3 + 0x72000;
                  *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 0;
                  iVar8 = *(int *)this;
                  bVar2 = true;
                }
                iVar8 = iVar8 + 1;
                if (iVar8 == 5) {
                  iVar5 = 0;
                }
                *(int *)this = iVar8;
                if (iVar8 == 5) {
                  *(int *)this = iVar5;
                }
                if (bVar2) {
                  if (iVar9 < 1000) {
                    this[4] = (cRIntro)0x1;
                    puVar3 = PTR__Game_001b60b8;
                    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 10;
                    *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
                    (&DAT_00353544)[*(int *)puVar3] = 1;
                    *(undefined4 *)(&DAT_0035354c + *(int *)puVar3) = 2;
                    (&DAT_00353545)[*(int *)puVar3] = 1;
                    *(undefined4 *)(this + 8) = 0;
                    *(undefined4 *)(this + 0xc) = 0x3991a2b4;
                    cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar3 + 0xd14));
                    cRSpriteManager::KillGame();
                    return;
                  }
                  break;
                }
              } while (iVar9 != 1000);
              *(undefined4 *)(this + 8) = 0;
              *(undefined4 *)(this + 0xc) = 0x3991a2b4;
            }
          }
          else {
            *(uint *)(*(int *)(this + 0x3c) + 0x194) = uVar7 & 0xffffffdf;
            puVar3 = PTR__Game_001b60b8;
            *(undefined4 *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) = 0;
            cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar3 + 0xd14));
            cRSpriteManager::KillGame();
            *(undefined4 *)(*(int *)puVar3 + 0x15c) = 10;
            *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
            *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 1;
          }
        }
        else {
          *(uint *)(*(int *)(this + 0x40) + 0x194) = uVar7 & 0xffffffdf;
          puVar3 = PTR__Game_001b60b8;
          *(undefined4 *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) = 0;
          cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar3 + 0xd14));
          cRSpriteManager::KillGame();
          *(undefined4 *)(*(int *)puVar3 + 0x15c) = 10;
          *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
          *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 7;
          cRTutorial::Init((cRTutorial *)(*(int *)puVar3 + 0x72bf4));
          PTR__gConfig_001b60d4[0xc0] = 1;
        }
      }
      else {
        *(uint *)(*(int *)(this + 0x38) + 0x194) = uVar7 & 0xffffffdf;
        puVar3 = PTR__Game_001b60b8;
        *(undefined4 *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) = 0;
        cRBorderManager::KillBorders((cRBorderManager *)(*(int *)puVar3 + 0xd14));
        cRSpriteManager::KillGame();
        *(undefined4 *)(*(int *)puVar3 + 0x15c) = 10;
        *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
        *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 4;
      }
    }
    else {
      *(uint *)(*(int *)(this + 0x34) + 0x194) = uVar7 & 0xffffffdf;
      puVar3 = PTR__Game_001b60b8;
      cRBorderManager::KillBorders((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      cRSpriteManager::KillGame();
      *(undefined4 *)(&DAT_00364944 + *(int *)puVar3) = 1;
      *(undefined4 *)(*(int *)puVar3 + 0x15c) = 10;
      *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
      *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 0;
      *(undefined4 *)(&DAT_00376620 + *(int *)puVar3) = 2;
      if (0 < *(int *)(PTR__gConfig_001b60d4 + 0xe0)) {
        *(undefined4 *)(*(int *)puVar3 + 0x15c) = 0x21;
        *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
      }
    }
  }
  else {
    *(uint *)(iVar5 + 0x194) = uVar7 & 0xffffffdf;
    puVar3 = PTR__Game_001b60b8;
    cRBorderManager::KillBorders((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    cRSpriteManager::KillGame();
    *(undefined4 *)(&DAT_00364944 + *(int *)puVar3) = 0;
    *(undefined4 *)(*(int *)puVar3 + 0x15c) = 10;
    *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
    *(undefined4 *)(*(int *)puVar3 + 0x72bd0) = 0;
    *(undefined4 *)(&DAT_00376620 + *(int *)puVar3) = 2;
    if (0 < *(int *)(PTR__gConfig_001b60d4 + 0xd0)) {
      *(undefined4 *)(*(int *)puVar3 + 0x15c) = 0x21;
      *(undefined1 *)(*(int *)puVar3 + 0x2c0) = 1;
    }
  }
  return;
}
