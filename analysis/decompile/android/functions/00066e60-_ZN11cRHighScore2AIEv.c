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
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  cRHighScore *pcVar10;

  iVar4 = DAT_000674e8;
  iVar8 = DAT_000674e4 + 0x66e80;
  if (this[0x10] == (cRHighScore)0x0) {
    uVar7 = *(uint *)(*(int *)(this + 0x20) + 0x194);
    if ((uVar7 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x20) + 0x194) = uVar7 & 0xffffffdf;
      UnInit(this);
      iVar4 = *(int *)(this + 8);
      if (iVar4 == 1) {
        iVar4 = 3;
        *(undefined4 *)(this + 8) = 3;
      }
      else if (iVar4 == 3) {
        *(undefined4 *)(this + 8) = 0;
        iVar4 = 0;
      }
      else if (iVar4 == 0) {
        iVar4 = 1;
        *(undefined4 *)(this + 8) = 1;
      }
      *(int *)(*(int *)(iVar8 + DAT_000674ec) + 0xa8) = iVar4;
      Init(this,iVar4,-1);
      return;
    }
    uVar7 = *(uint *)(*(int *)(this + 0x1c) + 0x194);
    if ((uVar7 & 0x20) == 0) {
      SetExitNextPos(this);
      iVar1 = **(int **)(iVar8 + iVar4);
      if (0 < *(int *)(gGroup0 + iVar1 + 0xce698)) {
        iVar6 = 0;
        iVar5 = 0;
        pcVar10 = this;
        do {
          if (((*(int *)(*(int *)(gGroup0 + iVar1 + 0xce694) + iVar6) == 1) &&
              (iVar2 = *(int *)(pcVar10 + 0xcc), iVar2 != 0)) &&
             (uVar7 = *(uint *)(iVar2 + 0x194), (uVar7 & 0x1020) == 0x20)) {
            *(undefined1 *)(iVar1 + 0x2c0) = 1;
            *(uint *)(iVar2 + 0x194) = uVar7 & 0xffffffdf;
            *(undefined4 *)(iVar1 + 0x15c) = 10;
            UnInit(this);
            iVar1 = *(int *)(this + 8);
            if (iVar1 == 1) {
              cRSubHighScore::MiniLoad
                        ((cRSubHighScore *)(gGroup0 + **(int **)(iVar8 + iVar4) + 0xce694),
                         iVar5 + 0xb);
            }
            else if (iVar1 == 3) {
              cRSubHighScore::MiniLoad
                        ((cRSubHighScore *)(gGroup0 + **(int **)(iVar8 + iVar4) + 0xce694),
                         iVar5 + 0x4a);
            }
            else if (iVar1 == 0) {
              cRSubHighScore::MiniLoad
                        ((cRSubHighScore *)(gGroup0 + **(int **)(iVar8 + iVar4) + 0xce694),iVar5);
            }
            iVar1 = **(int **)(iVar8 + iVar4);
            uVar3 = *(undefined4 *)(gGroup0 + iVar1 + 980000);
            *(int *)(gDirectory + iVar1 + 0x2548) = iVar1 + 0x361a9c;
            gDirectory[iVar1 + 0x2545] = 1;
            *(undefined4 *)(gDirectory + iVar1 + 0x254c) = 0x12;
            *(undefined4 *)(gOFOData + iVar1 + 0x1ebc) = 0;
            *(undefined4 *)(iVar1 + 0x71900) = uVar3;
            gDirectory[iVar1 + 0x2544] = 1;
          }
          else {
            iVar1 = **(int **)(iVar8 + iVar4);
          }
          iVar5 = iVar5 + 1;
          iVar6 = iVar6 + 0x38;
          pcVar10 = pcVar10 + 4;
        } while (iVar5 < *(int *)(gGroup0 + iVar1 + 0xce698));
      }
      return;
    }
    *(uint *)(*(int *)(this + 0x1c) + 0x194) = uVar7 & 0xffffffdf;
    if (*(int *)(this + 4) == 1) {
      iVar4 = **(int **)(iVar8 + DAT_000674e8);
      *(undefined1 *)(iVar4 + 0x2c0) = 1;
      *(undefined4 *)(iVar4 + 0x15c) = 10;
    }
    else if (*(int *)(this + 4) == 0) {
      *(undefined4 *)(**(int **)(iVar8 + DAT_000674e8) + 0x15c) = 4;
    }
    UnInit(this);
    return;
  }
  iVar1 = **(int **)(iVar8 + DAT_000674e8);
  if (*(int *)(iVar1 + 0xbf0) == 0) {
    iVar6 = *(int *)(this + 0x24);
    *(uint *)(*(int *)(this + 0x28) + 0x194) = *(uint *)(*(int *)(this + 0x28) + 0x194) | 0x14;
    *(uint *)(iVar6 + 0x194) = *(uint *)(iVar6 + 0x194) | 0x14;
    *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
         *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) | 0x10;
  }
  iVar6 = *(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c);
  uVar7 = *(uint *)(iVar6 + 0x194);
  if ((uVar7 & 0x4000) == 0) {
    if (((uVar7 & 0x20) != 0) ||
       ((*(char *)(*(int *)(iVar8 + DAT_000674ec) + 0x60) == '\0' &&
        (*(char *)(iVar6 + 0x2c5) == '\0')))) {
      *(uint *)(iVar6 + 0x194) = uVar7 & 0xffffffdf;
      *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
           *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) & 0xffffffef;
      if (*(int *)(iVar1 + 0xbf0) != 0) {
        return;
      }
      cKeyPad::Init((cKeyPad *)(iVar1 + 0xbf0),
                    *(cRBorder **)(this + *(int *)(this + 0x14) * 4 + 0x7c));
      iVar6 = *(int *)(this + 0x24);
      iVar1 = **(int **)(iVar8 + iVar4);
      *(uint *)(*(int *)(this + 0x28) + 0x194) =
           *(uint *)(*(int *)(this + 0x28) + 0x194) & 0xffffffeb;
      *(uint *)(iVar6 + 0x194) = *(uint *)(iVar6 + 0x194) & 0xffffffeb;
    }
    if (*(int *)(iVar1 + 0xbf0) != 0) {
      return;
    }
    uVar7 = *(uint *)(*(int *)(this + 0x28) + 0x194);
    if ((uVar7 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x28) + 0x194) = uVar7 & 0xffffffdf;
      *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) =
           *(uint *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x194) | 0x8000000;
    }
    uVar7 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar7 & 0x20) == 0) {
      return;
    }
    *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar7 & 0xffffffdf;
    UnInit(this);
    cRSpriteManager::KillGame();
    cRSubHighScore::RemoveHighScore
              ((cRSubHighScore *)(gGroup0 + **(int **)(iVar8 + iVar4) + 0xce694),*(int *)(this + 8),
               *(int *)(this + 0x14));
    Exit();
    return;
  }
  *(uint *)(iVar6 + 0x194) = uVar7 & 0xffffbfff;
  UnInit(this);
  iVar1 = DAT_000674ec;
  cRSpriteManager::KillGame();
  piVar9 = *(int **)(iVar8 + iVar4);
  Rstrcpy((char *)(*(int *)(gDirectory + *piVar9 + 0x2540) + 0x54),
          (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
  Rstrcpy((char *)(*(int *)(gGroup0 + *piVar9 + 0xce694) + *(int *)(this + 0x14) * 0x38 + 0x25),
          (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
  Rstrcpy((char *)(*piVar9 + 0x148),
          (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
  Rstrcpy((char *)(*(int *)(iVar8 + iVar1) + 0x60),
          (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
  iVar6 = *piVar9;
  iVar4 = *(int *)(iVar6 + 0x71900);
  if (iVar4 == 4) {
    iVar5 = *(int *)(iVar6 + 0x71904) + 8;
    iVar4 = *(int *)(this + (*(int *)(this + 0x14) + 0x1e) * 4 + 4);
  }
  else {
    if (iVar4 == 1) {
      Rstrcpy(gGroup0 + iVar6 + (*(int *)(this + 0x14) + 0xb) * 0x38 + 0xce6c1,
              (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
      Rstrcpy(gGroup0 + *piVar9 + 0xcf6b9,
              (char *)(*(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c) + 0x2c4));
      iVar6 = *piVar9;
      goto LAB_000670a0;
    }
    if (iVar4 != 0) goto LAB_000670a0;
    if (*(int *)(gOFOData + iVar6 + 0x1ebc) == 0) {
      iVar5 = *(int *)(iVar6 + 0x71904);
      iVar4 = *(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c);
    }
    else {
      if (*(int *)(gOFOData + iVar6 + 0x1ebc) != 1) goto LAB_000670a0;
      iVar5 = *(int *)(iVar6 + 0x71904) + 0x4a;
      iVar4 = *(int *)(this + *(int *)(this + 0x14) * 4 + 0x7c);
    }
  }
  Rstrcpy(gGroup0 + iVar6 + iVar5 * 0x38 + 0xce6c1,(char *)(iVar4 + 0x2c4));
  iVar6 = *piVar9;
LAB_000670a0:
  cRSubHighScore::SaveMiniData((cRSubHighScore *)(gGroup0 + iVar6 + 0xce694));
  gRegisterSaveFile((char *)(iVar8 + DAT_000674f4),*(void **)(iVar8 + iVar1),0x130);
  Exit();
  return;
}
