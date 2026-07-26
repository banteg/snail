/*
 * mangled: _ZN8cRGalaxy2AIEv
 * demangled: cRGalaxy::AI()
 * address: 0005a62c
 * size: 2140
 */

/* cRGalaxy::AI() */

void __thiscall cRGalaxy::AI(cRGalaxy *this)

{
  float fVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int unaff_r8;
  cRGalaxy *pcVar8;
  bool bVar9;
  float fVar10;
  float fVar11;
  tColour atStack_5c [16];
  float local_4c;
  float local_48;
  undefined4 local_44;

  uVar6 = 0;
  if (*(int *)this == 0) goto LAB_0005a9ec;
  if (*(float *)(Game + 0x3c) != *(float *)(Game + 0x44)) {
    UnInit(this);
    Init2(this);
  }
  tColour::tColour(atStack_5c);
  cRSubGame::HideScores(*(cRSubGame **)(this + 0x8e24));
  iVar5 = gConfig._160_4_;
  if ((*(int *)(gOFOData + Game + 0x1ebc) != 0) &&
     (iVar5 = unaff_r8, *(int *)(gOFOData + Game + 0x1ebc) == 1)) {
    iVar5 = gConfig._232_4_;
  }
  if (-1 < iVar5) {
    iVar7 = 0;
    do {
      iVar3 = iVar7 * 0x2a0;
      iVar7 = iVar7 + 1;
      cRGalaxyStar::AI((cRGalaxyStar *)(this + iVar3 + 0x204));
    } while (iVar7 <= iVar5);
  }
  iVar7 = Game;
  iVar3 = *(int *)(Game + 0x224);
  fVar11 = *(float *)(iVar3 + 0x58);
  *(undefined4 *)(this + 0x8e38) = 0;
  fVar10 = *(float *)(iVar3 + 0x54);
  if (*(int *)(this + 4) == 1) {
    iVar3 = *(int *)(this + 0x8e40);
    fVar1 = *(float *)(iVar3 + 0x214);
    if ((((*(float *)(iVar3 + 0x40) - fVar1 < fVar10) &&
         (fVar10 < fVar1 + *(float *)(iVar3 + 0x40) + *(float *)(iVar3 + 0x48))) &&
        (*(float *)(iVar3 + 0x44) - fVar1 < fVar11)) &&
       ((fVar11 < fVar1 + *(float *)(iVar3 + 0x44) + *(float *)(iVar3 + 0x4c) &&
        (*(undefined4 *)(this + 0x8e38) = 1, 0 < iVar5)))) {
      iVar2 = *(int *)(this + 0x8e34);
      iVar3 = 1;
      pcVar8 = this;
      do {
        bVar9 = iVar2 == iVar3;
        iVar3 = iVar3 + 1;
        if (bVar9) {
          *(undefined4 *)(this + iVar2 * 0x2a0 + 0x220) = 0x3f800000;
        }
        else {
          *(undefined4 *)(pcVar8 + 0x4c0) = 0;
        }
        pcVar8 = pcVar8 + 0x2a0;
      } while (iVar3 <= iVar5);
    }
  }
  uVar4 = *(uint *)(*(int *)(this + 0x8e5c) + 0x194);
  if ((uVar4 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) = uVar4 & 0xffffffdf;
    *(int *)(this + 0x8e34) = *(int *)(this + 0x8e34) + -5;
  }
  uVar4 = *(uint *)(*(int *)(this + 0x8e60) + 0x194);
  if ((uVar4 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x8e60) + 0x194) = uVar4 & 0xffffffdf;
    *(int *)(this + 0x8e34) = *(int *)(this + 0x8e34) + -1;
  }
  uVar4 = *(uint *)(*(int *)(this + 0x8e64) + 0x194);
  if ((uVar4 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x8e64) + 0x194) = uVar4 & 0xffffffdf;
    *(int *)(this + 0x8e34) = *(int *)(this + 0x8e34) + 1;
  }
  uVar4 = *(uint *)(*(int *)(this + 0x8e68) + 0x194);
  bVar9 = (uVar4 & 0x20) != 0;
  if (bVar9) {
    *(uint *)(*(int *)(this + 0x8e68) + 0x194) = uVar4 & 0xffffffdf;
    iVar5 = *(int *)(this + 0x8e34) + 5;
    *(int *)(this + 0x8e34) = iVar5;
  }
  else {
    iVar5 = 0x8e34;
  }
  if (!bVar9) {
    iVar5 = *(int *)(this + iVar5);
  }
  if (*(int *)(gOFOData + iVar7 + 0x1ebc) == 0) {
    if (iVar5 < 1) {
      iVar5 = 1;
    }
    else if ((int)gConfig._160_4_ <= iVar5) {
      iVar5 = gConfig._160_4_;
    }
    bVar9 = iVar5 == gConfig._160_4_;
    *(int *)(this + 0x8e34) = iVar5;
    if (bVar9) {
      iVar5 = *(int *)(this + 0x8e64);
      *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
           *(uint *)(*(int *)(this + 0x8e68) + 0x194) | 0x8000;
      *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | 0x8000;
      iVar5 = *(int *)(this + 0x8e34);
      goto LAB_0005aa04;
    }
    iVar5 = *(int *)(this + 0x8e64);
    *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
         *(uint *)(*(int *)(this + 0x8e68) + 0x194) & 0xffff7fff;
    *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffff7fff;
    if (*(int *)(this + 0x8e34) != 1) goto LAB_0005aa0c;
LAB_0005a82c:
    iVar5 = *(int *)(this + 0x8e60);
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) = *(uint *)(*(int *)(this + 0x8e5c) + 0x194) | 0x8000
    ;
    *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | 0x8000;
    if (*(int *)(this + 0xc) == 1) goto LAB_0005a860;
LAB_0005aa40:
    if (*(int *)(this + 0x8e38) == 0) {
      if (*(int *)(this + 4) == 1) {
        pcVar8 = (cRGalaxy *)0x2a0;
        iVar5 = *(int *)(this + 0x8e34);
        local_4c = *(float *)(this + iVar5 * 0x2a0 + 0x210) - fVar10;
        local_44 = *(undefined4 *)(this + iVar5 * 0x2a0 + 0x218);
        local_48 = *(float *)(this + iVar5 * 0x2a0 + 0x214) - fVar11;
        fVar1 = (float)tVector::Normalize((tVector *)&local_4c);
        if ((24.0 <= fVar1) || (*(int *)(this + 0x8e38) != 0)) goto LAB_0005aa60;
        *(undefined4 *)(this + 0x8e38) = 2;
        iVar5 = *(int *)(this + 0x8e34);
        iVar7 = *(int *)(Game + 600);
        if (iVar7 < 4) {
          uVar6 = 0x3f800000;
          pcVar8 = this + iVar5 * 0x2a0;
        }
        else {
          uVar6 = 0;
        }
        if (iVar7 < 4) {
          *(undefined4 *)(pcVar8 + 0x220) = uVar6;
        }
        else {
          pcVar8 = this + (int)pcVar8 * iVar5;
        }
        if (3 < iVar7) {
          *(undefined4 *)(pcVar8 + 0x220) = uVar6;
        }
      }
      else {
LAB_0005aa60:
        iVar5 = -1;
      }
      if (0 < (int)gConfig._160_4_) {
        iVar7 = 1;
        pcVar8 = this;
        do {
          local_4c = *(float *)(pcVar8 + 0x4b0) - fVar10;
          local_44 = *(undefined4 *)(pcVar8 + 0x4b8);
          local_48 = *(float *)(pcVar8 + 0x4b4) - fVar11;
          fVar1 = (float)tVector::Normalize((tVector *)&local_4c);
          if ((24.0 <= fVar1) || (*(int *)(this + 0x8e38) != 0)) {
            if ((*(int *)(this + 4) == 1) && (*(int *)(this + 0x8e34) == iVar7)) {
              *(undefined4 *)(this + iVar7 * 0x2a0 + 0x220) = 0x3f800000;
            }
            else {
              *(undefined4 *)(pcVar8 + 0x4c0) = 0;
            }
          }
          else {
            *(undefined4 *)(this + 0x8e38) = 2;
            iVar5 = iVar7;
            if (*(int *)(Game + 600) < 4) {
              *(undefined4 *)(pcVar8 + 0x4c0) = 0x3f800000;
            }
            else {
              *(undefined4 *)(pcVar8 + 0x4c0) = 0;
            }
          }
          iVar7 = iVar7 + 1;
          pcVar8 = pcVar8 + 0x2a0;
        } while (iVar7 <= (int)gConfig._160_4_);
      }
    }
    else {
      iVar5 = -1;
    }
  }
  else {
    if (*(int *)(gOFOData + iVar7 + 0x1ebc) == 1) {
      if (iVar5 < 1) {
        iVar5 = 1;
      }
      else if ((int)gConfig._232_4_ <= iVar5) {
        iVar5 = gConfig._232_4_;
      }
      bVar9 = iVar5 == gConfig._232_4_;
      *(int *)(this + 0x8e34) = iVar5;
      if (bVar9) {
        iVar5 = *(int *)(this + 0x8e64);
        *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
             *(uint *)(*(int *)(this + 0x8e68) + 0x194) | 0x8000;
        *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | 0x8000;
        iVar5 = *(int *)(this + 0x8e34);
      }
      else {
        iVar5 = *(int *)(this + 0x8e64);
        *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
             *(uint *)(*(int *)(this + 0x8e68) + 0x194) & 0xffff7fff;
        *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffff7fff;
        iVar5 = *(int *)(this + 0x8e34);
      }
    }
LAB_0005aa04:
    if (iVar5 == 1) goto LAB_0005a82c;
LAB_0005aa0c:
    iVar5 = *(int *)(this + 0x8e60);
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) =
         *(uint *)(*(int *)(this + 0x8e5c) + 0x194) & 0xffff7fff;
    *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffff7fff;
    if (*(int *)(this + 0xc) != 1) goto LAB_0005aa40;
LAB_0005a860:
    iVar5 = -1;
    *(undefined4 *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x220) = 0x3f800000;
  }
  if ((*(int *)(this + 4) == 1) && ((*(uint *)(*(int *)(this + 0x8e40) + 0x194) & 0x1000) == 0)) {
    BoxOn(this,*(int *)(this + 0x8e34));
  }
  if (*(char *)(Game + 0x43df8) == '\0') {
    uVar4 = *(uint *)(*(int *)(this + 0x8e28) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x8e28) + 0x194) = uVar4 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(this + 0x10) = 3;
      return;
    }
    iVar7 = *(int *)(this + 4);
    if (iVar7 == 1) {
      uVar4 = *(uint *)(*(int *)(this + 0x8e50) + 0x194);
      if ((uVar4 & 0x20) != 0) {
        *(uint *)(*(int *)(this + 0x8e50) + 0x194) = uVar4 & 0xffffffdf;
        UnInit(this);
        iVar5 = *(int *)(this + 0x8e24);
        iVar7 = *(int *)(this + 0x8e34);
        *(int *)(iVar5 + 100) = iVar7;
        cRSubTracks::Load((cRSubTracks *)(iVar5 + 0xa0),*(int *)(iVar5 + 0x60),iVar7);
        if ((*(int *)(*(int *)(this + 0x8e24) + 0x60) == 0) &&
           (*(int *)(gGroup0 + *(int *)(this + 0x8e24) + 0xc06f4) == 1 ||
            *(int *)(gGroup0 + *(int *)(this + 0x8e24) + 0xc06f4) == 4)) {
          *(undefined4 *)(this + 0x10) = 2;
          return;
        }
        uVar6 = 1;
LAB_0005a9ec:
        *(undefined4 *)(this + 0x10) = uVar6;
        return;
      }
    }
    uVar4 = *(uint *)(*(int *)(this + 0x8e54) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x8e54) + 0x194) = uVar4 & 0xffffffdf;
      UnInit(this);
      iVar5 = *(int *)(this + 0x8e24);
      iVar7 = *(int *)(this + 0x8e34);
      *(int *)(iVar5 + 100) = iVar7;
      cRSubTracks::Load((cRSubTracks *)(iVar5 + 0xa0),*(int *)(iVar5 + 0x60),iVar7);
      iVar7 = *(int *)(this + 0x8e24);
      iVar5 = *(int *)(this + 0x8e34);
      gGroup0[iVar7 + 0x9d618] = 1;
      cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + iVar7 + 0x5cdf4),iVar5 + 0x16);
      *(undefined4 *)(this + 0x10) = 1;
      *(int *)(gGroup0 + *(int *)(this + 0x8e24) + 0x9d61c) = *(int *)(this + 0x8e24) + 0x2f01fc;
      return;
    }
    if (((((*(int *)(Game + 0x24) == 0) && (*(int *)(this + 0xc) != 1)) &&
         (*(int *)(this + 0x8e38) != 1)) &&
        ((*(int *)(this + 0x8e38) == 2 && ((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) != 0)
         ))) && (*(int *)(this + 0x8e34) != iVar5)) {
      if (iVar7 == 1) {
        BoxOff(this);
      }
      else if (iVar7 != 0) goto LAB_0005a954;
      BoxOn(this,iVar5);
      cRSound::Play((int)&gRSound);
    }
  }
LAB_0005a954:
  *(undefined4 *)(this + 0x10) = 0;
  return;
}
