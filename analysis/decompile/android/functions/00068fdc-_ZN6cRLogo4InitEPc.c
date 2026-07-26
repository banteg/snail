/*
 * mangled: _ZN6cRLogo4InitEPc
 * demangled: cRLogo::Init(char*)
 * address: 00068fdc
 * size: 1944
 */

/* cRLogo::Init(char*) */

void __thiscall cRLogo::Init(cRLogo *this,char *param_1)

{
  cRLogo *pcVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  char *pcVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  undefined4 uVar14;
  char cVar15;
  int iVar16;
  undefined4 uVar17;
  int iVar18;
  uint uVar19;
  int *piVar20;
  cRLogo *pcVar21;
  float *pfVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  float fVar26;
  float extraout_s0;
  float fVar27;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;
  float extraout_s6;
  float extraout_s7;
  float extraout_s8;
  float fVar28;
  float extraout_s9;
  float extraout_s10;
  float extraout_s11;
  float fVar29;
  float extraout_s12;
  float fVar30;
  float extraout_s13;
  float fVar31;
  float fVar32;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  char *local_44 [2];

  iVar2 = DAT_000693e0;
  iVar18 = DAT_000693dc;
  fVar32 = DAT_000693b8;
  iVar12 = DAT_000693d8 + 0x68fec;
  piVar20 = *(int **)(iVar12 + DAT_000693dc);
  cRFade::FadeIn((cRFade *)(*piVar20 + 0x24));
  iVar4 = DAT_000693e8;
  pcVar3 = (char *)(iVar12 + DAT_000693e4);
  *this = (cRLogo)0x0;
  uVar11 = DAT_000693c0;
  fVar28 = DAT_000693bc;
  RShellMusicPlay(pcVar3,0,(char *)(iVar12 + iVar4));
  iVar4 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + *piVar20 + 0x3d8),
                     (char *)(iVar12 + DAT_000693ec));
  fVar26 = (float)cRBackdrop::Change((cRBackdrop *)(*piVar20 + 0x4d2e0),
                                     (cRLandscape *)
                                     (gSegmentText + iVar4 * 0x1ac + *piVar20 + 0x3dc),false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar20 + 0xd14),fVar26);
  cRStarManager::UnHide((cRStarManager *)(*piVar20 + 0x4d440));
  pcVar5 = (char *)RShellLoadFile(param_1,(int *)0x0);
  fVar27 = DAT_000693cc;
  fVar26 = DAT_000693c4;
  iVar4 = *piVar20;
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(*(int *)(iVar12 + DAT_000693f0) + 0x1c);
  tMatrix::tMatrix((tMatrix *)&local_84,extraout_s0,extraout_s1,extraout_s2,extraout_s3,extraout_s4,
                   extraout_s5,extraout_s6,extraout_s7,extraout_s8,extraout_s9,extraout_s10,
                   extraout_s11,extraout_s12,extraout_s13,fVar27,fVar26);
  uVar14 = DAT_000693d0;
  iVar24 = *piVar20;
  *(undefined4 *)(iVar4 + 0x100) = local_84;
  *(undefined4 *)(iVar4 + 0x104) = uStack_80;
  *(undefined4 *)(iVar4 + 0x108) = uStack_7c;
  *(undefined4 *)(iVar4 + 0x10c) = uStack_78;
  *(undefined4 *)(iVar4 + 0x110) = local_74;
  *(undefined4 *)(iVar4 + 0x114) = uStack_70;
  *(undefined4 *)(iVar4 + 0x118) = uStack_6c;
  *(undefined4 *)(iVar4 + 0x11c) = uStack_68;
  *(undefined4 *)(iVar4 + 0x120) = local_64;
  *(undefined4 *)(iVar4 + 0x124) = uStack_60;
  *(undefined4 *)(iVar4 + 0x128) = uStack_5c;
  *(undefined4 *)(iVar4 + 300) = uStack_58;
  *(undefined4 *)(iVar4 + 0x130) = local_54;
  *(undefined4 *)(iVar4 + 0x134) = uStack_50;
  *(undefined4 *)(iVar4 + 0x138) = uStack_4c;
  *(undefined4 *)(iVar4 + 0x13c) = uStack_48;
  *(undefined4 *)(iVar24 + 0x21c) = uVar14;
  uVar14 = DAT_000693d4;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = uVar14;
  cRMouse::SetInActive((cRMouse *)(iVar24 + 0x228));
  pcVar3 = (char *)(iVar12 + DAT_000693f4);
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0xc) = 0;
  local_44[0] = (char *)Rstrfind(pcVar3,pcVar5);
  iVar4 = Rstrfind((char *)(iVar12 + iVar2),local_44[0]);
  local_44[0] = (char *)(iVar4 + 1);
  pcVar6 = (char *)Rstrfind((char *)(iVar12 + DAT_000693f8),pcVar5);
  pcVar3 = local_44[0];
  iVar4 = DAT_000693fc;
  while (pcVar3 < pcVar6) {
    cVar15 = *pcVar3;
    if (cVar15 == '*') {
      pcVar3 = pcVar3 + 1;
      cVar15 = *pcVar3;
      local_44[0] = pcVar3;
    }
    else if (cVar15 != '\r' && cVar15 != '\0') {
      iVar24 = 0;
      fVar26 = DAT_00069414;
      do {
        iVar24 = iVar24 + 1;
        iVar7 = FontASCIIRemap(cVar15);
        pcVar10 = local_44[0] + 1;
        cVar15 = local_44[0][1];
        uVar19 = (uint)(cVar15 != '\r' && cVar15 != '\0');
        fVar26 = fVar26 + *(float *)(*(int *)(iVar12 + iVar4) + (iVar7 + 0x580) * 4);
        local_44[0] = pcVar10;
      } while (cVar15 != '\r' && cVar15 != '\0');
      fVar26 = fVar26 * fVar28;
      while( true ) {
        cVar15 = pcVar3[uVar19];
        if (cVar15 != ' ') {
          iVar16 = *(int *)(this + 0x18);
          iVar7 = FontASCIIRemap(cVar15);
          cRBod::SetObject((cRBod *)(this + iVar16 * 0x84 + 0x1c),
                           *(cRObject **)(iVar7 * 0x2c + *(int *)(iVar12 + iVar4) + 0x24));
          tMatrix::Identity((tMatrix *)(this + *(int *)(this + 0x18) * 0x84 + 0x48));
          iVar7 = *(int *)(this + 0x18);
          *(undefined4 *)(this + iVar7 * 0x84 + 0x7c) = uVar11;
          *(float *)(this + iVar7 * 0x84 + 0x78) = fVar26 + 0.0;
          *(float *)(this + iVar7 * 0x84 + 0x80) = fVar32 + 0.0;
          fVar27 = (float)tColourSmall::White((tColourSmall *)(this + iVar7 * 0x84 + 0x44));
          tColourSmall::Alpha((tColourSmall *)(this + *(int *)(this + 0x18) * 0x84 + 0x44),fVar27);
          iVar7 = *(int *)(this + 0x18);
          *(undefined4 *)(this + iVar7 * 0x84 + 0x98) = 0;
          *(undefined4 *)(this + iVar7 * 0x84 + 0x94) = 0;
          *(undefined4 *)(this + iVar7 * 0x84 + 0x90) = 0;
          this[iVar7 * 0x84 + 0x9c] = *(cRLogo *)(pcVar3 + uVar19);
          (*(code *)**(undefined4 **)(this + *(int *)(this + 0x18) * 0x84 + 0x1c))
                    (this + *(int *)(this + 0x18) * 0x84 + 0x1c);
          *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
          cVar15 = pcVar3[uVar19];
        }
        uVar19 = uVar19 + 1;
        iVar7 = FontASCIIRemap(cVar15);
        if (iVar24 <= (int)uVar19) break;
        fVar26 = fVar26 - *(float *)(*(int *)(iVar12 + iVar4) + (iVar7 + 0x580) * 4);
      }
      cVar15 = *local_44[0];
      pcVar3 = local_44[0];
    }
    if (cVar15 == '\r') {
      pcVar3 = pcVar3 + 2;
      fVar32 = fVar32 - DAT_00069410;
      local_44[0] = pcVar3;
      iVar4 = DAT_000693fc;
    }
  }
  iVar4 = *(int *)(this + 0x18);
  iVar24 = 0;
  *(undefined4 *)(this + 0x2101c) = 0;
  if (0 < iVar4) {
    piVar20 = *(int **)(iVar12 + iVar18);
    pcVar3 = (char *)(iVar12 + DAT_00069400);
    iVar18 = 0;
    do {
      if (iVar18 < iVar4) {
        iVar7 = 0;
        pcVar21 = this + iVar18 * 0x84 + 0x1c;
        do {
          iVar7 = iVar7 + 1;
          iVar16 = iVar7 + iVar18;
          if (iVar4 <= iVar16) break;
          pcVar1 = pcVar21 + 0xe8;
          pcVar21 = pcVar21 + 0x84;
        } while (iVar7 < 0x14 && *(float *)pcVar1 == *(float *)(this + iVar18 * 0x84 + 0x80));
        iVar4 = iVar7 * 6;
      }
      else {
        iVar4 = 0;
        iVar7 = 0;
        iVar16 = iVar18;
      }
      iVar8 = iVar24 * 0x84;
      iVar13 = *piVar20;
      if ((*(uint *)(this + iVar8 + 0x21024) & 0x200) == 0) {
        if (*(int *)(iVar13 + 0x35c) == 0) {
          *(cRLogo **)(iVar13 + 0x35c) =
               this + (int)("Java_com_sandlotgames_snailmail_MyOpenFeintDelegate_JNIOFOInit" +
                           iVar8 + 0x3b);
          *(undefined4 *)(this + iVar8 + 0x21028) = 0;
          *(undefined4 *)(*(int *)(iVar13 + 0x35c) + 0xc) = 0;
        }
        else {
          *(cRLogo **)(*(int *)(iVar13 + 0x35c) + 8) =
               this + (int)("Java_com_sandlotgames_snailmail_MyOpenFeintDelegate_JNIOFOInit" +
                           iVar8 + 0x3b);
          *(int *)(*(int *)(*(int *)(iVar13 + 0x35c) + 8) + 0xc) = *(int *)(iVar13 + 0x35c);
          iVar8 = *(int *)(*(int *)(iVar13 + 0x35c) + 8);
          *(int *)(iVar13 + 0x35c) = iVar8;
          *(undefined4 *)(iVar8 + 8) = 0;
        }
        *(uint *)(this + iVar24 * 0x84 + 0x21024) =
             *(uint *)(this + iVar24 * 0x84 + 0x21024) | 0x200;
      }
      else {
        RShellError(pcVar3);
      }
      iVar24 = *(int *)(this + 0x2101c);
      pcVar21 = this + iVar18 * 0x84 + 0x1c;
      uVar11 = *(undefined4 *)(this + iVar18 * 0x84 + 0x4c);
      uVar14 = *(undefined4 *)(this + iVar18 * 0x84 + 0x50);
      uVar17 = *(undefined4 *)(this + iVar18 * 0x84 + 0x54);
      *(undefined4 *)(this + iVar24 * 0x84 + 0x2104c) = *(undefined4 *)(this + iVar18 * 0x84 + 0x48)
      ;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21050) = uVar11;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21054) = uVar14;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21058) = uVar17;
      *(cRLogo **)(this + iVar24 * 0x84 + 0x210a0) = pcVar21;
      uVar11 = *(undefined4 *)(this + iVar18 * 0x84 + 0x5c);
      uVar14 = *(undefined4 *)(this + iVar18 * 0x84 + 0x60);
      uVar17 = *(undefined4 *)(this + iVar18 * 0x84 + 100);
      *(undefined4 *)(this + iVar24 * 0x84 + 0x2105c) = *(undefined4 *)(this + iVar18 * 0x84 + 0x58)
      ;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21060) = uVar11;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21064) = uVar14;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21068) = uVar17;
      uVar11 = *(undefined4 *)(this + iVar18 * 0x84 + 0x6c);
      uVar14 = *(undefined4 *)(this + iVar18 * 0x84 + 0x70);
      uVar17 = *(undefined4 *)(this + iVar18 * 0x84 + 0x74);
      *(undefined4 *)(this + iVar24 * 0x84 + 0x2106c) = *(undefined4 *)(this + iVar18 * 0x84 + 0x68)
      ;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21070) = uVar11;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21074) = uVar14;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21078) = uVar17;
      uVar11 = *(undefined4 *)(this + iVar18 * 0x84 + 0x7c);
      uVar14 = *(undefined4 *)(this + iVar18 * 0x84 + 0x80);
      uVar17 = *(undefined4 *)(this + iVar18 * 0x84 + 0x84);
      *(undefined4 *)(this + iVar24 * 0x84 + 0x2107c) = *(undefined4 *)(this + iVar18 * 0x84 + 0x78)
      ;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21080) = uVar11;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21084) = uVar14;
      *(undefined4 *)(this + iVar24 * 0x84 + 0x21088) = uVar17;
      puVar9 = *(undefined4 **)(*(int *)(this + iVar24 * 0x84 + 0x21044) + 0x10c);
      uVar11 = **(undefined4 **)(*(int *)(this + iVar18 * 0x84 + 0x40) + 0x10c);
      puVar9[0x11] = iVar4;
      *puVar9 = uVar11;
      if (iVar7 != 0) {
        iVar4 = 0;
        do {
          iVar13 = 0;
          iVar8 = *(int *)(*(int *)(pcVar21 + 0x24) + 0x10c);
          iVar24 = iVar4;
          do {
            fVar30 = *(float *)(pcVar21 + 0x5c);
            fVar31 = *(float *)(pcVar21 + 0x60);
            pfVar22 = (float *)(*(int *)(iVar8 + 8) + iVar13);
            fVar28 = *pfVar22;
            fVar26 = pfVar22[1];
            fVar27 = *(float *)(this + iVar18 * 0x84 + 0x78);
            fVar29 = *(float *)(this + iVar18 * 0x84 + 0x7c);
            iVar25 = puVar9[2];
            iVar23 = iVar25 + iVar24;
            *(float *)(iVar23 + 8) =
                 (pfVar22[2] + *(float *)(pcVar21 + 100)) - *(float *)(this + iVar18 * 0x84 + 0x80);
            *(float *)(iVar25 + iVar24) = (fVar28 + fVar30) - fVar27;
            *(float *)(iVar23 + 4) = (fVar26 + fVar31) - fVar29;
            *(undefined4 *)(puVar9[2] + iVar24 + 0xc) =
                 *(undefined4 *)(*(int *)(iVar8 + 8) + iVar13 + 0xc);
            iVar25 = *(int *)(iVar8 + 8) + iVar13;
            iVar13 = iVar13 + 0x14;
            iVar23 = puVar9[2] + iVar24;
            iVar24 = iVar24 + 0x14;
            *(undefined4 *)(iVar23 + 0x10) = *(undefined4 *)(iVar25 + 0x10);
          } while (iVar13 != 0x50);
          iVar4 = iVar4 + 0x50;
          pcVar21 = pcVar21 + 0x84;
        } while (iVar4 != iVar7 * 0x50);
      }
      iVar4 = *(int *)(this + 0x18);
      iVar24 = *(int *)(this + 0x2101c) + 1;
      *(int *)(this + 0x2101c) = iVar24;
      iVar18 = iVar16;
    } while (iVar16 < iVar4);
  }
  local_44[0] = (char *)Rstrfind((char *)(iVar12 + DAT_00069404),pcVar5);
  local_44[0] = (char *)Rstrfind((char *)(iVar12 + iVar2),local_44[0]);
  fVar27 = (float)Rstrfloat(local_44);
  fVar32 = DAT_00069408 - fVar32;
  iVar4 = *(int *)(this + 0x2101c);
  *(float *)(this + 0x14) = fVar27;
  fVar28 = DAT_00069414;
  fVar26 = DAT_00069414;
  if (fVar27 != 0.0) {
    fVar26 = DAT_00069410 / (fVar27 * DAT_0006940c);
  }
  if (0 < iVar4) {
    iVar18 = 0;
    pcVar21 = this + 0x2109c;
    do {
      iVar18 = iVar18 + 1;
      *(float *)(pcVar21 + -8) = fVar28;
      *(float *)(pcVar21 + -4) = fVar28;
      *(float *)pcVar21 = fVar32 * fVar26;
      pcVar21 = pcVar21 + 0x84;
    } while (iVar18 < iVar4);
  }
  RShellMemoryFree(pcVar5);
  return;
}
