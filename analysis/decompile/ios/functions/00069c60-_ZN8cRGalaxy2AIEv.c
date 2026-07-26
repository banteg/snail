/*
 * mangled: _ZN8cRGalaxy2AIEv
 * demangled: cRGalaxy::AI()
 * address: 00069c60
 * size: 2008
 */

/* cRGalaxy::AI() */

void __thiscall cRGalaxy::AI(cRGalaxy *this)

{
  undefined *puVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  cRGalaxy *pcVar5;
  uint uVar6;
  int iVar7;
  int unaff_r5;
  bool bVar8;
  float fVar9;
  float fVar11;
  undefined8 uVar10;
  tColour atStack_40 [16];
  float local_30;
  float local_2c;
  undefined4 local_28;

  puVar1 = PTR__Game_001b60b8;
  if (*(int *)this == 0) goto LAB_00069f50;
  if (*(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) != *(float *)(*(int *)PTR__Game_001b60b8 + 0x44)
     ) {
    UnInit(this);
    Init2(this);
  }
  tColour::tColour(atStack_40);
  cRSubGame::HideScores(*(cRSubGame **)(this + 0x8e24));
  if (*(int *)(&DAT_00364944 + *(int *)puVar1) == 0) {
    unaff_r5 = *(int *)(PTR__gConfig_001b60d4 + 0xa0);
  }
  else if (*(int *)(&DAT_00364944 + *(int *)puVar1) == 1) {
    unaff_r5 = *(int *)(PTR__gConfig_001b60d4 + 0xe8);
  }
  if (-1 < unaff_r5) {
    iVar4 = 0;
    pcVar5 = this;
    do {
      iVar4 = iVar4 + 1;
      *(float *)(pcVar5 + 0x21c) =
           *(float *)(pcVar5 + 0x21c) +
           (*(float *)(pcVar5 + 0x220) - *(float *)(pcVar5 + 0x21c)) * 0.1;
      pcVar5 = pcVar5 + 0x2a0;
    } while (iVar4 != unaff_r5 + 1);
  }
  uVar10 = *(undefined8 *)(*(int *)(*(int *)PTR__Game_001b60b8 + 0x224) + 0x54);
  *(undefined4 *)(this + 0x8e38) = 0;
  fVar3 = (float)uVar10;
  fVar11 = (float)((ulonglong)uVar10 >> 0x20);
  if (*(int *)(this + 4) == 1) {
    iVar4 = *(int *)(this + 0x8e40);
    fVar9 = *(float *)(iVar4 + 0x214);
    if ((((*(float *)(iVar4 + 0x40) - fVar9 < fVar3) &&
         (fVar3 < fVar9 + *(float *)(iVar4 + 0x40) + *(float *)(iVar4 + 0x48))) &&
        (*(float *)(iVar4 + 0x44) - fVar9 < fVar11)) &&
       ((fVar11 < fVar9 + *(float *)(iVar4 + 0x44) + *(float *)(iVar4 + 0x4c) &&
        (*(undefined4 *)(this + 0x8e38) = 1, 0 < unaff_r5)))) {
      iVar4 = 1;
      pcVar5 = this;
      do {
        if (*(int *)(this + 0x8e34) == iVar4) {
          *(undefined4 *)(this + iVar4 * 0x2a0 + 0x220) = 0x3f800000;
        }
        else {
          *(undefined4 *)(pcVar5 + 0x4c0) = 0;
        }
        iVar4 = iVar4 + 1;
        pcVar5 = pcVar5 + 0x2a0;
      } while (iVar4 != unaff_r5 + 1);
    }
  }
  uVar6 = *(uint *)(*(int *)(this + 0x8e5c) + 0x194);
  bVar8 = (uVar6 & 0x20) != 0;
  if (bVar8) {
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) = uVar6 & 0xffffffdf;
    uVar6 = *(uint *)(this + 0x8e34);
  }
  if (bVar8) {
    *(uint *)(this + 0x8e34) = uVar6 - 5;
  }
  uVar6 = *(uint *)(*(int *)(this + 0x8e60) + 0x194);
  bVar8 = (uVar6 & 0x20) != 0;
  if (bVar8) {
    *(uint *)(*(int *)(this + 0x8e60) + 0x194) = uVar6 & 0xffffffdf;
    uVar6 = *(uint *)(this + 0x8e34);
  }
  if (bVar8) {
    *(uint *)(this + 0x8e34) = uVar6 - 1;
  }
  uVar6 = *(uint *)(*(int *)(this + 0x8e64) + 0x194);
  bVar8 = (uVar6 & 0x20) != 0;
  if (bVar8) {
    *(uint *)(*(int *)(this + 0x8e64) + 0x194) = uVar6 & 0xffffffdf;
    uVar6 = *(uint *)(this + 0x8e34);
  }
  if (bVar8) {
    *(uint *)(this + 0x8e34) = uVar6 + 1;
  }
  uVar6 = *(uint *)(*(int *)(this + 0x8e68) + 0x194);
  if ((uVar6 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x8e68) + 0x194) = uVar6 & 0xffffffdf;
    *(int *)(this + 0x8e34) = *(int *)(this + 0x8e34) + 5;
  }
  if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) {
    iVar4 = *(int *)(this + 0x8e34);
    if (iVar4 < 1) {
      iVar4 = 1;
    }
    else if (*(int *)(PTR__gConfig_001b60d4 + 0xa0) <= iVar4) {
      iVar4 = *(int *)(PTR__gConfig_001b60d4 + 0xa0);
    }
    *(int *)(this + 0x8e34) = iVar4;
    if (iVar4 == *(int *)(PTR__gConfig_001b60d4 + 0xa0)) {
LAB_00069fc4:
      *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
           *(uint *)(*(int *)(this + 0x8e68) + 0x194) | 0x8000;
      *(uint *)(*(int *)(this + 0x8e64) + 0x194) =
           *(uint *)(*(int *)(this + 0x8e64) + 0x194) | 0x8000;
    }
    else {
LAB_00069e18:
      *(uint *)(*(int *)(this + 0x8e68) + 0x194) =
           *(uint *)(*(int *)(this + 0x8e68) + 0x194) & 0xffff7fff;
      *(uint *)(*(int *)(this + 0x8e64) + 0x194) =
           *(uint *)(*(int *)(this + 0x8e64) + 0x194) & 0xffff7fff;
    }
  }
  else if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 1) {
    iVar4 = *(int *)(this + 0x8e34);
    if (iVar4 < 1) {
      iVar4 = 1;
    }
    else if (*(int *)(PTR__gConfig_001b60d4 + 0xe8) <= iVar4) {
      iVar4 = *(int *)(PTR__gConfig_001b60d4 + 0xe8);
    }
    *(int *)(this + 0x8e34) = iVar4;
    if (iVar4 == *(int *)(PTR__gConfig_001b60d4 + 0xe8)) goto LAB_00069fc4;
    goto LAB_00069e18;
  }
  if (*(int *)(this + 0x8e34) == 1) {
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) = *(uint *)(*(int *)(this + 0x8e5c) + 0x194) | 0x8000
    ;
    *(uint *)(*(int *)(this + 0x8e60) + 0x194) = *(uint *)(*(int *)(this + 0x8e60) + 0x194) | 0x8000
    ;
  }
  else {
    *(uint *)(*(int *)(this + 0x8e5c) + 0x194) =
         *(uint *)(*(int *)(this + 0x8e5c) + 0x194) & 0xffff7fff;
    *(uint *)(*(int *)(this + 0x8e60) + 0x194) =
         *(uint *)(*(int *)(this + 0x8e60) + 0x194) & 0xffff7fff;
  }
  if (*(int *)(this + 0xc) == 1) {
    iVar4 = -1;
    *(undefined4 *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x220) = 0x3f800000;
    iVar7 = *(int *)(this + 4);
  }
  else {
    if (*(int *)(this + 0x8e38) == 0) {
      if (*(int *)(this + 4) == 1) {
        iVar4 = *(int *)(this + 0x8e34);
        local_30 = *(float *)(this + iVar4 * 0x2a0 + 0x210) - fVar3;
        local_28 = *(undefined4 *)(this + iVar4 * 0x2a0 + 0x218);
        local_2c = *(float *)(this + iVar4 * 0x2a0 + 0x214) - fVar11;
        fVar3 = (float)tVector::Normalize((tVector *)&local_30);
        if ((24.0 <= fVar3) || (*(int *)(this + 0x8e38) != 0)) goto LAB_00069ff4;
        *(undefined4 *)(this + 0x8e38) = 2;
        iVar4 = *(int *)(this + 0x8e34);
        if (*(int *)(*(int *)PTR__Game_001b60b8 + 600) < 4) {
          *(undefined4 *)(this + iVar4 * 0x2a0 + 0x220) = 0x3f800000;
        }
        else {
          *(undefined4 *)(this + iVar4 * 0x2a0 + 0x220) = 0;
        }
      }
      else {
LAB_00069ff4:
        iVar4 = -1;
      }
      if (0 < *(int *)(PTR__gConfig_001b60d4 + 0xa0)) {
        iVar7 = 1;
        pcVar5 = this;
        do {
          local_30 = *(float *)(pcVar5 + 0x4b0) - (float)uVar10;
          local_2c = *(float *)(pcVar5 + 0x4b4) - (float)((ulonglong)uVar10 >> 0x20);
          local_28 = *(undefined4 *)(pcVar5 + 0x4b8);
          fVar3 = (float)tVector::Normalize((tVector *)&local_30);
          if ((24.0 <= fVar3) || (*(int *)(this + 0x8e38) != 0)) {
            iVar2 = *(int *)(this + 4);
            bVar8 = iVar2 == 1;
            if (bVar8) {
              iVar2 = *(int *)(this + 0x8e34);
            }
            if (bVar8 && iVar2 == iVar7) {
              *(undefined4 *)(this + iVar7 * 0x2a0 + 0x220) = 0x3f800000;
            }
            else {
              *(undefined4 *)(pcVar5 + 0x4c0) = 0;
            }
          }
          else {
            *(undefined4 *)(this + 0x8e38) = 2;
            iVar4 = iVar7;
            if (*(int *)(*(int *)PTR__Game_001b60b8 + 600) < 4) {
              *(undefined4 *)(pcVar5 + 0x4c0) = 0x3f800000;
            }
            else {
              *(undefined4 *)(pcVar5 + 0x4c0) = 0;
            }
          }
          iVar7 = iVar7 + 1;
          pcVar5 = pcVar5 + 0x2a0;
        } while (iVar7 <= *(int *)(PTR__gConfig_001b60d4 + 0xa0));
      }
    }
    else {
      iVar4 = -1;
    }
    iVar7 = *(int *)(this + 4);
  }
  if ((iVar7 == 1) && ((*(uint *)(*(int *)(this + 0x8e40) + 0x194) & 0x1000) == 0)) {
    BoxOn(this,*(int *)(this + 0x8e34));
  }
  iVar7 = *(int *)PTR__Game_001b60b8;
  if (*(char *)(iVar7 + 0x43df8) == '\0') {
    uVar6 = *(uint *)(*(int *)(this + 0x8e28) + 0x194);
    if ((uVar6 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x8e28) + 0x194) = uVar6 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(this + 0x10) = 3;
      return;
    }
    iVar2 = *(int *)(this + 4);
    if (iVar2 == 1) {
      uVar6 = *(uint *)(*(int *)(this + 0x8e50) + 0x194);
      if ((uVar6 & 0x20) != 0) {
        *(uint *)(*(int *)(this + 0x8e50) + 0x194) = uVar6 & 0xffffffdf;
        UnInit(this);
        *(undefined4 *)(*(int *)(this + 0x8e24) + 0x5c) = *(undefined4 *)(this + 0x8e34);
        iVar4 = *(int *)(this + 0x8e24);
        cRSubTracks::Load((cRSubTracks *)(iVar4 + 0x98),*(int *)(iVar4 + 0x58),
                          *(int *)(iVar4 + 0x5c));
        if ((*(int *)(*(int *)(this + 0x8e24) + 0x58) == 0) &&
           (*(int *)(&DAT_00303aa8 + *(int *)(this + 0x8e24)) == 1)) {
          *(undefined4 *)(this + 0x10) = 2;
          return;
        }
        *(undefined4 *)(this + 0x10) = 1;
        return;
      }
    }
    uVar6 = *(uint *)(*(int *)(this + 0x8e54) + 0x194);
    if ((uVar6 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x8e54) + 0x194) = uVar6 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(*(int *)(this + 0x8e24) + 0x5c) = *(undefined4 *)(this + 0x8e34);
      iVar4 = *(int *)(this + 0x8e24);
      cRSubTracks::Load((cRSubTracks *)(iVar4 + 0x98),*(int *)(iVar4 + 0x58),*(int *)(iVar4 + 0x5c))
      ;
      (&DAT_002e09cc)[*(int *)(this + 0x8e24)] = 1;
      cRSubHighScore::MiniLoad
                ((cRSubHighScore *)(&DAT_002a01a8 + *(int *)(this + 0x8e24)),
                 *(int *)(this + 0x8e34) + 0x16);
      *(int *)(&DAT_002e09d0 + *(int *)(this + 0x8e24)) = *(int *)(this + 0x8e24) + 0x2c0f08;
      *(undefined4 *)(this + 0x10) = 1;
      return;
    }
    if (((((*(int *)(iVar7 + 0x24) == 0) && (*(int *)(this + 0xc) != 1)) &&
         (*(int *)(this + 0x8e38) != 1)) &&
        ((*(int *)(this + 0x8e38) == 2 &&
         ((*(uint *)(*(int *)(iVar7 + 0x224) + 0x30) & 0x4000) != 0)))) &&
       (*(int *)(this + 0x8e34) != iVar4)) {
      if (iVar2 == 1) {
        BoxOff(this);
        BoxOn(this,iVar4);
        cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
      }
      else if (iVar2 == 0) {
        BoxOn(this,iVar4);
        cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
      }
    }
  }
LAB_00069f50:
  *(undefined4 *)(this + 0x10) = 0;
  return;
}
