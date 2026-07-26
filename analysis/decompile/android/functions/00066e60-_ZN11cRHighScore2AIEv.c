/*
 * mangled: _ZN11cRHighScore2AIEv
 * demangled: cRHighScore::AI()
 * address: 00066e60
 * size: 1668
 */

/* cRHighScore::AI() */

void __thiscall cRHighScore::AI(cRHighScore *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  cRHighScore *pcVar8;

  iVar3 = Game;
  if (this[0x10] == (cRHighScore)0x0) {
    uVar5 = *(uint *)(*(int *)(this + 0x20) + 0x194);
    if ((uVar5 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x20) + 0x194) = uVar5 & 0xffffffdf;
      UnInit(this);
      gConfig._168_4_ = *(undefined4 *)(this + 8);
      if (gConfig._168_4_ == 1) {
        gConfig._168_4_ = 3;
        *(undefined4 *)(this + 8) = 3;
      }
      else if (gConfig._168_4_ == 3) {
        *(undefined4 *)(this + 8) = 0;
        gConfig._168_4_ = 0;
      }
      else if (gConfig._168_4_ == 0) {
        gConfig._168_4_ = 1;
        *(undefined4 *)(this + 8) = 1;
      }
      Init(this,gConfig._168_4_,-1);
      return;
    }
    uVar5 = *(uint *)(*(int *)(this + 0x1c) + 0x194);
    if ((uVar5 & 0x20) == 0) {
      SetExitNextPos(this);
      if (0 < *(int *)(gGroup0 + Game + 0xce698)) {
        iVar3 = 0;
        iVar4 = 0;
        iVar7 = Game;
        pcVar8 = this;
        do {
          iVar6 = Game;
          if (((*(int *)(*(int *)(gGroup0 + iVar7 + 0xce694) + iVar3) == 1) &&
              (iVar1 = *(int *)(pcVar8 + 0xcc), iVar1 != 0)) &&
             (uVar5 = *(uint *)(iVar1 + 0x194), (uVar5 & 0x1020) == 0x20)) {
            *(undefined1 *)(iVar7 + 0x2c0) = 1;
            *(uint *)(iVar1 + 0x194) = uVar5 & 0xffffffdf;
            *(undefined4 *)(iVar7 + 0x15c) = 10;
            UnInit(this);
            iVar7 = *(int *)(this + 8);
            if (iVar7 == 1) {
              cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + Game + 0xce694),iVar4 + 0xb);
            }
            else if (iVar7 == 3) {
              cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + Game + 0xce694),iVar4 + 0x4a);
            }
            else if (iVar7 == 0) {
              cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + Game + 0xce694),iVar4);
            }
            iVar6 = Game;
            uVar2 = *(undefined4 *)(gGroup0 + Game + 980000);
            *(int *)(gDirectory + Game + 0x2548) = Game + 0x361a9c;
            gDirectory[iVar6 + 0x2545] = 1;
            *(undefined4 *)(gDirectory + iVar6 + 0x254c) = 0x12;
            *(undefined4 *)(gOFOData + iVar6 + 0x1ebc) = 0;
            *(undefined4 *)(iVar6 + 0x71900) = uVar2;
            gDirectory[iVar6 + 0x2544] = 1;
          }
          iVar4 = iVar4 + 1;
          iVar3 = iVar3 + 0x38;
          pcVar8 = pcVar8 + 4;
          iVar7 = iVar6;
        } while (iVar4 < *(int *)(gGroup0 + iVar6 + 0xce698));
      }
      return;
    }
    *(uint *)(*(int *)(this + 0x1c) + 0x194) = uVar5 & 0xffffffdf;
    iVar3 = Game;
    if (*(int *)(this + 4) == 1) {
      *(undefined1 *)(Game + 0x2c0) = 1;
      *(undefined4 *)(iVar3 + 0x15c) = 10;
    }
    else if (*(int *)(this + 4) == 0) {
      *(undefined4 *)(Game + 0x15c) = 4;
    }
    UnInit(this);
    return;
  }
  if (*(int *)(Game + 0xbf0) == 0) {
    iVar4 = *(int *)(this + 0x24);
    *(uint *)(*(int *)(this + 0x28) + 0x194) = *(uint *)(*(int *)(this + 0x28) + 0x194) | 0x14;
    *(uint *)(iVar4 + 0x194) = *(uint *)(iVar4 + 0x194) | 0x14;
    *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
         *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) | 0x10;
  }
  iVar4 = *(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c);
  uVar5 = *(uint *)(iVar4 + 0x194);
  if ((uVar5 & 0x4000) == 0) {
    if (((uVar5 & 0x20) != 0) || ((gConfig[0x60] == '\0' && (*(char *)(iVar4 + 0x2c5) == '\0')))) {
      *(uint *)(iVar4 + 0x194) = uVar5 & 0xffffffdf;
      *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
           *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) & 0xffffffef;
      if (*(int *)(iVar3 + 0xbf0) != 0) {
        return;
      }
      cKeyPad::Init((cKeyPad *)(iVar3 + 0xbf0),
                    *(cRBorder **)(this + *(int *)(this + 0x14) * 4 + 0x7c));
      iVar3 = Game;
      iVar4 = *(int *)(this + 0x24);
      *(uint *)(*(int *)(this + 0x28) + 0x194) =
           *(uint *)(*(int *)(this + 0x28) + 0x194) & 0xffffffeb;
      *(uint *)(iVar4 + 0x194) = *(uint *)(iVar4 + 0x194) & 0xffffffeb;
    }
    if (*(int *)(iVar3 + 0xbf0) != 0) {
      return;
    }
    uVar5 = *(uint *)(*(int *)(this + 0x28) + 0x194);
    if ((uVar5 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x28) + 0x194) = uVar5 & 0xffffffdf;
      *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
           *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) | 0x8000000;
    }
    uVar5 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar5 & 0x20) == 0) {
      return;
    }
    *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar5 & 0xffffffdf;
    UnInit(this);
    cRSpriteManager::KillGame();
    cRSubHighScore::RemoveHighScore
              ((cRSubHighScore *)(gGroup0 + Game + 0xce694),*(int *)(this + 8),*(int *)(this + 0x14)
              );
    Exit();
    return;
  }
  *(uint *)(iVar4 + 0x194) = uVar5 & 0xffffbfff;
  UnInit(this);
  cRSpriteManager::KillGame();
  Rstrcpy((char *)(*(int *)(gDirectory + Game + 0x2540) + 0x54),
          (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
  Rstrcpy((char *)(*(int *)(gGroup0 + Game + 0xce694) + *(int *)(this + 0x14) * 0x38 + 0x25),
          (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
  Rstrcpy((char *)(Game + 0x148),(char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4)
         );
  Rstrcpy(gConfig + 0x60,(char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
  iVar3 = *(int *)(Game + 0x71900);
  if (iVar3 == 4) {
    iVar4 = *(int *)(Game + 0x71904) + 8;
    iVar3 = *(int *)(this + (*(int *)(this + 0x14) + 0x1e) * 4 + 4);
  }
  else {
    if (iVar3 == 1) {
      Rstrcpy(gGroup0 + Game + (*(int *)(this + 0x14) + 0xb) * 0x38 + 0xce6c1,
              (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
      Rstrcpy(gGroup0 + Game + 0xcf6b9,
              (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
      goto LAB_000670a0;
    }
    if (iVar3 != 0) goto LAB_000670a0;
    if (*(int *)(gOFOData + Game + 0x1ebc) == 0) {
      iVar4 = *(int *)(Game + 0x71904);
      iVar3 = *(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c);
    }
    else {
      if (*(int *)(gOFOData + Game + 0x1ebc) != 1) goto LAB_000670a0;
      iVar4 = *(int *)(Game + 0x71904) + 0x4a;
      iVar3 = *(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c);
    }
  }
  Rstrcpy(gGroup0 + Game + iVar4 * 0x38 + 0xce6c1,(char *)(iVar3 + 0x2c4));
LAB_000670a0:
  cRSubHighScore::SaveMiniData((cRSubHighScore *)(gGroup0 + Game + 0xce694));
  gRegisterSaveFile("asm.cfg",gConfig,0x130);
  Exit();
  return;
}
