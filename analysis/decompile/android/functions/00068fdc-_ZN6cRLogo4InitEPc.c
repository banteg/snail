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
  char *pcVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  char *pcVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 uVar11;
  char cVar12;
  int iVar13;
  undefined4 uVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  char *pcVar18;
  cRLogo *pcVar19;
  float *pfVar20;
  int iVar21;
  int iVar22;
  float fVar23;
  float extraout_s0;
  float fVar24;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;
  float extraout_s6;
  float extraout_s7;
  float extraout_s8;
  float extraout_s9;
  float extraout_s10;
  float fVar25;
  float extraout_s11;
  float fVar26;
  float extraout_s12;
  float fVar27;
  float extraout_s13;
  float fVar28;
  float fVar29;
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

  fVar29 = 0.2;
  cRFade::FadeIn((cRFade *)(Game + 0x24));
  *this = (cRLogo)0x0;
  RShellMusicPlay("introtext",0,"");
  iVar2 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"SpaceRed.txt");
  fVar23 = (float)cRBackdrop::Change((cRBackdrop *)(Game + 0x4d2e0),
                                     (cRLandscape *)(gSegmentText + iVar2 * 0x1ac + Game + 0x3dc),
                                     false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar23);
  cRStarManager::UnHide((cRStarManager *)(Game + 0x4d440));
  pcVar3 = (char *)RShellLoadFile(param_1,(int *)0x0);
  iVar2 = Game;
  *(undefined4 *)(this + 0x10) = gConfig._28_4_;
  tMatrix::tMatrix((tMatrix *)&local_84,extraout_s0,extraout_s1,extraout_s2,extraout_s3,extraout_s4,
                   extraout_s5,extraout_s6,extraout_s7,extraout_s8,extraout_s9,extraout_s10,
                   extraout_s11,extraout_s12,extraout_s13,-0.77301,0.634393);
  iVar5 = Game;
  *(undefined4 *)(iVar2 + 0x100) = local_84;
  *(undefined4 *)(iVar2 + 0x104) = uStack_80;
  *(undefined4 *)(iVar2 + 0x108) = uStack_7c;
  *(undefined4 *)(iVar2 + 0x10c) = uStack_78;
  *(undefined4 *)(iVar2 + 0x110) = local_74;
  *(undefined4 *)(iVar2 + 0x114) = uStack_70;
  *(undefined4 *)(iVar2 + 0x118) = uStack_6c;
  *(undefined4 *)(iVar2 + 0x11c) = uStack_68;
  *(undefined4 *)(iVar2 + 0x120) = local_64;
  *(undefined4 *)(iVar2 + 0x124) = uStack_60;
  *(undefined4 *)(iVar2 + 0x128) = uStack_5c;
  *(undefined4 *)(iVar2 + 300) = uStack_58;
  *(undefined4 *)(iVar2 + 0x130) = local_54;
  *(undefined4 *)(iVar2 + 0x134) = uStack_50;
  *(undefined4 *)(iVar2 + 0x138) = uStack_4c;
  *(undefined4 *)(iVar2 + 0x13c) = uStack_48;
  *(undefined4 *)(iVar5 + 0x21c) = 0x42c80000;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0x3ada740e;
  cRMouse::SetInActive((cRMouse *)(iVar5 + 0x228));
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0xc) = 0;
  local_44[0] = (char *)Rstrfind("Text Start:",pcVar3);
  iVar2 = Rstrfind(":",local_44[0]);
  local_44[0] = (char *)(iVar2 + 1);
  pcVar4 = (char *)Rstrfind("Text End:",pcVar3);
  pcVar18 = local_44[0];
  while (pcVar18 < pcVar4) {
    cVar12 = *pcVar18;
    if (cVar12 == '*') {
      pcVar18 = pcVar18 + 1;
      cVar12 = *pcVar18;
      local_44[0] = pcVar18;
    }
    else if (cVar12 != '\r' && cVar12 != '\0') {
      iVar2 = 0;
      fVar23 = 0.0;
      do {
        iVar2 = iVar2 + 1;
        iVar5 = FontASCIIRemap(cVar12);
        pcVar8 = local_44[0] + 1;
        cVar12 = local_44[0][1];
        uVar15 = (uint)(cVar12 != '\r' && cVar12 != '\0');
        fVar23 = fVar23 + *(float *)(RFont3D + (iVar5 + 0x580) * 4);
        local_44[0] = pcVar8;
      } while (cVar12 != '\r' && cVar12 != '\0');
      fVar23 = fVar23 * 0.5;
      while( true ) {
        cVar12 = pcVar18[uVar15];
        if (cVar12 != ' ') {
          iVar13 = *(int *)(this + 0x18);
          iVar5 = FontASCIIRemap(cVar12);
          cRBod::SetObject((cRBod *)(this + iVar13 * 0x84 + 0x1c),
                           *(cRObject **)(RFont3D + iVar5 * 0x2c + 0x24));
          tMatrix::Identity((tMatrix *)(this + *(int *)(this + 0x18) * 0x84 + 0x48));
          iVar5 = *(int *)(this + 0x18);
          *(undefined4 *)(this + iVar5 * 0x84 + 0x7c) = 0xc0800000;
          *(float *)(this + iVar5 * 0x84 + 0x78) = fVar23 + 0.0;
          *(float *)(this + iVar5 * 0x84 + 0x80) = fVar29 + 0.0;
          fVar24 = (float)tColourSmall::White((tColourSmall *)(this + iVar5 * 0x84 + 0x44));
          tColourSmall::Alpha((tColourSmall *)(this + *(int *)(this + 0x18) * 0x84 + 0x44),fVar24);
          iVar5 = *(int *)(this + 0x18);
          *(undefined4 *)(this + iVar5 * 0x84 + 0x98) = 0;
          *(undefined4 *)(this + iVar5 * 0x84 + 0x94) = 0;
          *(undefined4 *)(this + iVar5 * 0x84 + 0x90) = 0;
          this[iVar5 * 0x84 + 0x9c] = *(cRLogo *)(pcVar18 + uVar15);
          (*(code *)**(undefined4 **)(this + *(int *)(this + 0x18) * 0x84 + 0x1c))
                    (this + *(int *)(this + 0x18) * 0x84 + 0x1c);
          *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
          cVar12 = pcVar18[uVar15];
        }
        uVar15 = uVar15 + 1;
        iVar5 = FontASCIIRemap(cVar12);
        if (iVar2 <= (int)uVar15) break;
        fVar23 = fVar23 - *(float *)(RFont3D + (iVar5 + 0x580) * 4);
      }
      cVar12 = *local_44[0];
      pcVar18 = local_44[0];
    }
    if (cVar12 == '\r') {
      pcVar18 = pcVar18 + 2;
      fVar29 = fVar29 - 1.0;
      local_44[0] = pcVar18;
    }
  }
  iVar2 = *(int *)(this + 0x18);
  iVar5 = 0;
  *(undefined4 *)(this + 0x2101c) = 0;
  if (0 < iVar2) {
    iVar13 = 0;
    do {
      iVar10 = Game;
      if (iVar13 < iVar2) {
        iVar16 = 0;
        pcVar19 = this + iVar13 * 0x84 + 0x1c;
        do {
          iVar16 = iVar16 + 1;
          iVar17 = iVar16 + iVar13;
          if (iVar2 <= iVar17) break;
          pcVar1 = pcVar19 + 0xe8;
          pcVar19 = pcVar19 + 0x84;
        } while (iVar16 < 0x14 && *(float *)pcVar1 == *(float *)(this + iVar13 * 0x84 + 0x80));
        iVar2 = iVar16 * 6;
      }
      else {
        iVar2 = 0;
        iVar16 = 0;
        iVar17 = iVar13;
      }
      iVar6 = iVar5 * 0x84;
      if ((*(uint *)(this + iVar6 + 0x21024) & 0x200) == 0) {
        if (*(int *)(Game + 0x35c) == 0) {
          *(cRLogo **)(Game + 0x35c) =
               this + (int)("Java_com_sandlotgames_snailmail_MyOpenFeintDelegate_JNIOFOInit" +
                           iVar6 + 0x3b);
          *(undefined4 *)(this + iVar6 + 0x21028) = 0;
          *(undefined4 *)(*(int *)(iVar10 + 0x35c) + 0xc) = 0;
        }
        else {
          *(cRLogo **)(*(int *)(Game + 0x35c) + 8) =
               this + (int)("Java_com_sandlotgames_snailmail_MyOpenFeintDelegate_JNIOFOInit" +
                           iVar6 + 0x3b);
          *(int *)(*(int *)(*(int *)(iVar10 + 0x35c) + 8) + 0xc) = *(int *)(iVar10 + 0x35c);
          iVar6 = *(int *)(*(int *)(iVar10 + 0x35c) + 8);
          *(int *)(iVar10 + 0x35c) = iVar6;
          *(undefined4 *)(iVar6 + 8) = 0;
        }
        *(uint *)(this + iVar5 * 0x84 + 0x21024) = *(uint *)(this + iVar5 * 0x84 + 0x21024) | 0x200;
      }
      else {
        RShellError("List ADD");
      }
      iVar5 = *(int *)(this + 0x2101c);
      pcVar19 = this + iVar13 * 0x84 + 0x1c;
      uVar9 = *(undefined4 *)(this + iVar13 * 0x84 + 0x4c);
      uVar11 = *(undefined4 *)(this + iVar13 * 0x84 + 0x50);
      uVar14 = *(undefined4 *)(this + iVar13 * 0x84 + 0x54);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x2104c) = *(undefined4 *)(this + iVar13 * 0x84 + 0x48);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21050) = uVar9;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21054) = uVar11;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21058) = uVar14;
      *(cRLogo **)(this + iVar5 * 0x84 + 0x210a0) = pcVar19;
      uVar9 = *(undefined4 *)(this + iVar13 * 0x84 + 0x5c);
      uVar11 = *(undefined4 *)(this + iVar13 * 0x84 + 0x60);
      uVar14 = *(undefined4 *)(this + iVar13 * 0x84 + 100);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x2105c) = *(undefined4 *)(this + iVar13 * 0x84 + 0x58);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21060) = uVar9;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21064) = uVar11;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21068) = uVar14;
      uVar9 = *(undefined4 *)(this + iVar13 * 0x84 + 0x6c);
      uVar11 = *(undefined4 *)(this + iVar13 * 0x84 + 0x70);
      uVar14 = *(undefined4 *)(this + iVar13 * 0x84 + 0x74);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x2106c) = *(undefined4 *)(this + iVar13 * 0x84 + 0x68);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21070) = uVar9;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21074) = uVar11;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21078) = uVar14;
      uVar9 = *(undefined4 *)(this + iVar13 * 0x84 + 0x7c);
      uVar11 = *(undefined4 *)(this + iVar13 * 0x84 + 0x80);
      uVar14 = *(undefined4 *)(this + iVar13 * 0x84 + 0x84);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x2107c) = *(undefined4 *)(this + iVar13 * 0x84 + 0x78);
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21080) = uVar9;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21084) = uVar11;
      *(undefined4 *)(this + iVar5 * 0x84 + 0x21088) = uVar14;
      puVar7 = *(undefined4 **)(*(int *)(this + iVar5 * 0x84 + 0x21044) + 0x10c);
      uVar9 = **(undefined4 **)(*(int *)(this + iVar13 * 0x84 + 0x40) + 0x10c);
      puVar7[0x11] = iVar2;
      *puVar7 = uVar9;
      if (iVar16 != 0) {
        iVar2 = 0;
        do {
          iVar6 = 0;
          iVar10 = *(int *)(*(int *)(pcVar19 + 0x24) + 0x10c);
          iVar5 = iVar2;
          do {
            fVar27 = *(float *)(pcVar19 + 0x5c);
            fVar28 = *(float *)(pcVar19 + 0x60);
            pfVar20 = (float *)(*(int *)(iVar10 + 8) + iVar6);
            fVar23 = *pfVar20;
            fVar24 = pfVar20[1];
            fVar25 = *(float *)(this + iVar13 * 0x84 + 0x78);
            fVar26 = *(float *)(this + iVar13 * 0x84 + 0x7c);
            iVar22 = puVar7[2];
            iVar21 = iVar22 + iVar5;
            *(float *)(iVar21 + 8) =
                 (pfVar20[2] + *(float *)(pcVar19 + 100)) - *(float *)(this + iVar13 * 0x84 + 0x80);
            *(float *)(iVar22 + iVar5) = (fVar23 + fVar27) - fVar25;
            *(float *)(iVar21 + 4) = (fVar24 + fVar28) - fVar26;
            *(undefined4 *)(puVar7[2] + iVar5 + 0xc) =
                 *(undefined4 *)(*(int *)(iVar10 + 8) + iVar6 + 0xc);
            iVar22 = *(int *)(iVar10 + 8) + iVar6;
            iVar6 = iVar6 + 0x14;
            iVar21 = puVar7[2] + iVar5;
            iVar5 = iVar5 + 0x14;
            *(undefined4 *)(iVar21 + 0x10) = *(undefined4 *)(iVar22 + 0x10);
          } while (iVar6 != 0x50);
          iVar2 = iVar2 + 0x50;
          pcVar19 = pcVar19 + 0x84;
        } while (iVar2 != iVar16 * 0x50);
      }
      iVar2 = *(int *)(this + 0x18);
      iVar5 = *(int *)(this + 0x2101c) + 1;
      *(int *)(this + 0x2101c) = iVar5;
      iVar13 = iVar17;
    } while (iVar17 < iVar2);
  }
  local_44[0] = (char *)Rstrfind("Duration:",pcVar3);
  local_44[0] = (char *)Rstrfind(":",local_44[0]);
  fVar23 = (float)Rstrfloat(local_44);
  iVar2 = *(int *)(this + 0x2101c);
  *(float *)(this + 0x14) = fVar23;
  if (fVar23 == 0.0) {
    fVar23 = 0.0;
  }
  else {
    fVar23 = 1.0 / (fVar23 * 60.0);
  }
  if (0 < iVar2) {
    iVar5 = 0;
    pcVar19 = this + 0x2109c;
    do {
      iVar5 = iVar5 + 1;
      *(undefined4 *)(pcVar19 + -8) = 0;
      *(undefined4 *)(pcVar19 + -4) = 0;
      *(float *)pcVar19 = (3.0 - fVar29) * fVar23;
      pcVar19 = pcVar19 + 0x84;
    } while (iVar5 < iVar2);
  }
  RShellMemoryFree(pcVar3);
  return;
}
