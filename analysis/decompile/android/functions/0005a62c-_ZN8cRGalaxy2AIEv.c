/*
 * mangled: _ZN8cRGalaxy2AIEv
 * demangled: cRGalaxy::AI()
 * address: 0005a62c
 * size: 2140
 */

/* cRGalaxy::AI() */

void __thiscall cRGalaxy::AI(cRGalaxy *this)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  int unaff_r8;
  cRGalaxy *pcVar11;
  int iVar12;
  bool bVar13;
  float fVar14;
  float fVar15;
  tColour atStack_5c [16];
  float local_4c;
  float local_48;
  undefined4 local_44;

  iVar6 = DAT_0005abe4;
  iVar10 = DAT_0005abe0 + 0x5a64c;
  uVar8 = 0;
  if (*(int *)this == 0) goto LAB_0005a9ec;
  if (*(float *)(**(int **)(iVar10 + DAT_0005abe4) + 0x3c) !=
      *(float *)(**(int **)(iVar10 + DAT_0005abe4) + 0x44)) {
    UnInit(this);
    Init2(this);
  }
  tColour::tColour(atStack_5c);
  cRSubGame::HideScores(*(cRSubGame **)(this + 0x8e24));
  iVar7 = **(int **)(iVar10 + iVar6);
  if (*(int *)(gOFOData + iVar7 + 0x1ebc) == 0) {
    unaff_r8 = *(int *)(*(int *)(iVar10 + DAT_0005abec) + 0xa0);
  }
  else if (*(int *)(gOFOData + iVar7 + 0x1ebc) == 1) {
    unaff_r8 = *(int *)(*(int *)(iVar10 + DAT_0005abec) + 0xe8);
  }
  if (-1 < unaff_r8) {
    iVar7 = 0;
    do {
      iVar4 = iVar7 * 0x2a0;
      iVar7 = iVar7 + 1;
      cRGalaxyStar::AI((cRGalaxyStar *)(this + iVar4 + 0x204));
    } while (iVar7 <= unaff_r8);
    iVar7 = **(int **)(iVar10 + iVar6);
  }
  iVar4 = *(int *)(iVar7 + 0x224);
  fVar15 = *(float *)(iVar4 + 0x58);
  *(undefined4 *)(this + 0x8e38) = 0;
  fVar14 = *(float *)(iVar4 + 0x54);
  if (*(int *)(this + 4) == 1) {
    iVar4 = *(int *)(this + 0x8e40);
    fVar3 = *(float *)(iVar4 + 0x214);
    if ((((*(float *)(iVar4 + 0x40) - fVar3 < fVar14) &&
         (fVar14 < fVar3 + *(float *)(iVar4 + 0x40) + *(float *)(iVar4 + 0x48))) &&
        (*(float *)(iVar4 + 0x44) - fVar3 < fVar15)) &&
       ((fVar15 < fVar3 + *(float *)(iVar4 + 0x44) + *(float *)(iVar4 + 0x4c) &&
        (*(undefined4 *)(this + 0x8e38) = 1, uVar1 = DAT_0005abf8, uVar8 = DAT_0005abf4,
        0 < unaff_r8)))) {
      iVar12 = *(int *)(this + 0x8e34);
      iVar4 = 1;
      pcVar11 = this;
      do {
        bVar13 = iVar12 == iVar4;
        iVar4 = iVar4 + 1;
        if (bVar13) {
          *(undefined4 *)(this + iVar12 * 0x2a0 + 0x220) = uVar1;
        }
        else {
          *(undefined4 *)(pcVar11 + 0x4c0) = uVar8;
        }
        pcVar11 = pcVar11 + 0x2a0;
      } while (iVar4 <= unaff_r8);
    }
  }
  uVar5 = *(uint *)(*(int *)(this + 0x8e5c) + 0x194);
  if ((uVar5 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) = uVar5 & 0xffffffdf;
    *(int *)(this + 0x8e34) = *(int *)(this + 0x8e34) + -5;
  }
  uVar5 = *(uint *)(*(int *)(this + 0x8e60) + 0x194);
  if ((uVar5 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x8e60) + 0x194) = uVar5 & 0xffffffdf;
    *(int *)(this + 0x8e34) = *(int *)(this + 0x8e34) + -1;
  }
  uVar5 = *(uint *)(*(int *)(this + 0x8e64) + 0x194);
  if ((uVar5 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x8e64) + 0x194) = uVar5 & 0xffffffdf;
    *(int *)(this + 0x8e34) = *(int *)(this + 0x8e34) + 1;
  }
  uVar5 = *(uint *)(*(int *)(this + 0x8e68) + 0x194);
  bVar13 = (uVar5 & 0x20) != 0;
  if (bVar13) {
    *(uint *)(*(int *)(this + 0x8e68) + 0x194) = uVar5 & 0xffffffdf;
    iVar4 = *(int *)(this + 0x8e34) + 5;
    *(int *)(this + 0x8e34) = iVar4;
  }
  else {
    iVar4 = 0x8e34;
  }
  if (!bVar13) {
    iVar4 = *(int *)(this + iVar4);
  }
  if (*(int *)(gOFOData + iVar7 + 0x1ebc) == 0) {
    if (iVar4 < 1) {
      iVar4 = 1;
      iVar7 = *(int *)(*(int *)(iVar10 + DAT_0005abec) + 0xa0);
    }
    else {
      iVar7 = *(int *)(*(int *)(iVar10 + DAT_0005abec) + 0xa0);
      if (iVar7 <= iVar4) {
        iVar4 = iVar7;
      }
    }
    *(int *)(this + 0x8e34) = iVar4;
    if (iVar4 == iVar7) {
      iVar7 = *(int *)(this + 0x8e64);
      *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
           *(uint *)(*(int *)(this + 0x8e68) + 0x194) | 0x8000;
      *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) | 0x8000;
      iVar4 = *(int *)(this + 0x8e34);
      goto LAB_0005aa04;
    }
    iVar7 = *(int *)(this + 0x8e64);
    *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
         *(uint *)(*(int *)(this + 0x8e68) + 0x194) & 0xffff7fff;
    *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) & 0xffff7fff;
    if (*(int *)(this + 0x8e34) != 1) goto LAB_0005aa0c;
LAB_0005a82c:
    iVar7 = *(int *)(this + 0x8e60);
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) = *(uint *)(*(int *)(this + 0x8e5c) + 0x194) | 0x8000
    ;
    *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) | 0x8000;
    if (*(int *)(this + 0xc) == 1) goto LAB_0005a860;
LAB_0005aa40:
    if (*(int *)(this + 0x8e38) == 0) {
      if (*(int *)(this + 4) == 1) {
        pcVar11 = (cRGalaxy *)0x2a0;
        iVar7 = *(int *)(this + 0x8e34);
        local_4c = *(float *)(this + iVar7 * 0x2a0 + 0x210) - fVar14;
        local_44 = *(undefined4 *)(this + iVar7 * 0x2a0 + 0x218);
        local_48 = *(float *)(this + iVar7 * 0x2a0 + 0x214) - fVar15;
        fVar3 = (float)tVector::Normalize((tVector *)&local_4c);
        if ((DAT_0005abf0 <= fVar3) || (*(int *)(this + 0x8e38) != 0)) goto LAB_0005aa60;
        piVar9 = *(int **)(iVar10 + iVar6);
        *(undefined4 *)(this + 0x8e38) = 2;
        iVar7 = *(int *)(this + 0x8e34);
        iVar4 = *(int *)(*piVar9 + 600);
        uVar8 = DAT_0005abf4;
        if (iVar4 < 4) {
          pcVar11 = this + iVar7 * 0x2a0;
          uVar8 = DAT_0005abf8;
        }
        if (iVar4 < 4) {
          *(undefined4 *)(pcVar11 + 0x220) = uVar8;
        }
        else {
          pcVar11 = this + (int)pcVar11 * iVar7;
        }
        if (3 < iVar4) {
          *(undefined4 *)(pcVar11 + 0x220) = uVar8;
        }
      }
      else {
LAB_0005aa60:
        iVar7 = -1;
      }
      uVar1 = DAT_0005abf8;
      uVar8 = DAT_0005abf4;
      fVar3 = DAT_0005abf0;
      iVar4 = DAT_0005abec;
      if (0 < *(int *)(*(int *)(iVar10 + DAT_0005abec) + 0xa0)) {
        iVar12 = 1;
        pcVar11 = this;
        do {
          local_4c = *(float *)(pcVar11 + 0x4b0) - fVar14;
          local_44 = *(undefined4 *)(pcVar11 + 0x4b8);
          local_48 = *(float *)(pcVar11 + 0x4b4) - fVar15;
          fVar2 = (float)tVector::Normalize((tVector *)&local_4c);
          if ((fVar3 <= fVar2) || (*(int *)(this + 0x8e38) != 0)) {
            if ((*(int *)(this + 4) == 1) && (*(int *)(this + 0x8e34) == iVar12)) {
              *(undefined4 *)(this + iVar12 * 0x2a0 + 0x220) = uVar1;
            }
            else {
              *(undefined4 *)(pcVar11 + 0x4c0) = uVar8;
            }
          }
          else {
            piVar9 = *(int **)(iVar10 + iVar6);
            *(undefined4 *)(this + 0x8e38) = 2;
            iVar7 = iVar12;
            if (*(int *)(*piVar9 + 600) < 4) {
              *(undefined4 *)(pcVar11 + 0x4c0) = uVar1;
            }
            else {
              *(undefined4 *)(pcVar11 + 0x4c0) = uVar8;
            }
          }
          iVar12 = iVar12 + 1;
          pcVar11 = pcVar11 + 0x2a0;
        } while (iVar12 <= *(int *)(*(int *)(iVar10 + iVar4) + 0xa0));
      }
    }
    else {
      iVar7 = -1;
    }
  }
  else {
    if (*(int *)(gOFOData + iVar7 + 0x1ebc) == 1) {
      if (iVar4 < 1) {
        iVar7 = *(int *)(*(int *)(iVar10 + DAT_0005abec) + 0xe8);
        iVar4 = 1;
      }
      else {
        iVar7 = *(int *)(*(int *)(iVar10 + DAT_0005abec) + 0xe8);
        if (iVar7 <= iVar4) {
          iVar4 = iVar7;
        }
      }
      *(int *)(this + 0x8e34) = iVar4;
      if (iVar4 == iVar7) {
        iVar7 = *(int *)(this + 0x8e64);
        *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
             *(uint *)(*(int *)(this + 0x8e68) + 0x194) | 0x8000;
        *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) | 0x8000;
        iVar4 = *(int *)(this + 0x8e34);
      }
      else {
        iVar7 = *(int *)(this + 0x8e64);
        *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
             *(uint *)(*(int *)(this + 0x8e68) + 0x194) & 0xffff7fff;
        *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) & 0xffff7fff;
        iVar4 = *(int *)(this + 0x8e34);
      }
    }
LAB_0005aa04:
    if (iVar4 == 1) goto LAB_0005a82c;
LAB_0005aa0c:
    iVar7 = *(int *)(this + 0x8e60);
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) =
         *(uint *)(*(int *)(this + 0x8e5c) + 0x194) & 0xffff7fff;
    *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) & 0xffff7fff;
    if (*(int *)(this + 0xc) != 1) goto LAB_0005aa40;
LAB_0005a860:
    iVar7 = -1;
    *(undefined4 *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x220) = DAT_0005abf8;
  }
  if ((*(int *)(this + 4) == 1) && ((*(uint *)(*(int *)(this + 0x8e40) + 0x194) & 0x1000) == 0)) {
    BoxOn(this,*(int *)(this + 0x8e34));
  }
  iVar6 = **(int **)(iVar10 + iVar6);
  if (*(char *)(iVar6 + 0x43df8) == '\0') {
    uVar5 = *(uint *)(*(int *)(this + 0x8e28) + 0x194);
    if ((uVar5 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x8e28) + 0x194) = uVar5 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(this + 0x10) = 3;
      return;
    }
    iVar4 = *(int *)(this + 4);
    if (iVar4 == 1) {
      uVar5 = *(uint *)(*(int *)(this + 0x8e50) + 0x194);
      if ((uVar5 & 0x20) != 0) {
        *(uint *)(*(int *)(this + 0x8e50) + 0x194) = uVar5 & 0xffffffdf;
        UnInit(this);
        iVar6 = *(int *)(this + 0x8e24);
        iVar10 = *(int *)(this + 0x8e34);
        *(int *)(iVar6 + 100) = iVar10;
        cRSubTracks::Load((cRSubTracks *)(iVar6 + 0xa0),*(int *)(iVar6 + 0x60),iVar10);
        if ((*(int *)(*(int *)(this + 0x8e24) + 0x60) == 0) &&
           (*(int *)(gGroup0 + *(int *)(this + 0x8e24) + 0xc06f4) == 1 ||
            *(int *)(gGroup0 + *(int *)(this + 0x8e24) + 0xc06f4) == 4)) {
          *(undefined4 *)(this + 0x10) = 2;
          return;
        }
        uVar8 = 1;
LAB_0005a9ec:
        *(undefined4 *)(this + 0x10) = uVar8;
        return;
      }
    }
    uVar5 = *(uint *)(*(int *)(this + 0x8e54) + 0x194);
    if ((uVar5 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x8e54) + 0x194) = uVar5 & 0xffffffdf;
      UnInit(this);
      iVar6 = *(int *)(this + 0x8e24);
      iVar10 = *(int *)(this + 0x8e34);
      *(int *)(iVar6 + 100) = iVar10;
      cRSubTracks::Load((cRSubTracks *)(iVar6 + 0xa0),*(int *)(iVar6 + 0x60),iVar10);
      iVar10 = *(int *)(this + 0x8e24);
      iVar6 = *(int *)(this + 0x8e34);
      gGroup0[iVar10 + 0x9d618] = 1;
      cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + iVar10 + 0x5cdf4),iVar6 + 0x16);
      *(undefined4 *)(this + 0x10) = 1;
      *(int *)(gGroup0 + *(int *)(this + 0x8e24) + 0x9d61c) = *(int *)(this + 0x8e24) + 0x2f01fc;
      return;
    }
    if (((((*(int *)(iVar6 + 0x24) == 0) && (*(int *)(this + 0xc) != 1)) &&
         (*(int *)(this + 0x8e38) != 1)) &&
        ((*(int *)(this + 0x8e38) == 2 &&
         ((*(uint *)(*(int *)(iVar6 + 0x224) + 0x30) & 0x4000) != 0)))) &&
       (*(int *)(this + 0x8e34) != iVar7)) {
      if (iVar4 == 1) {
        BoxOff(this);
      }
      else if (iVar4 != 0) goto LAB_0005a954;
      BoxOn(this,iVar7);
      cRSound::Play(*(int *)(iVar10 + DAT_0005abe8));
    }
  }
LAB_0005a954:
  *(undefined4 *)(this + 0x10) = 0;
  return;
}
