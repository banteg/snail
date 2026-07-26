/*
 * mangled: _ZN6cRLogo4InitEPc
 * demangled: cRLogo::Init(char*)
 * address: 00065af4
 * size: 2500
 */

/* cRLogo::Init(char*) */

void __thiscall cRLogo::Init(cRLogo *this,char *param_1)

{
  cRLogo *pcVar1;
  undefined *puVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  int iVar12;
  undefined4 uVar13;
  float *pfVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  undefined4 uVar18;
  float *pfVar19;
  int iVar20;
  cRLogo *pcVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  ulonglong uVar29;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  char *local_34 [5];

  puVar2 = PTR__Game_001b60b8;
  uVar29 = 0x3e4ccccd;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  *this = (cRLogo)0x0;
  RShellMusicPlay("introtext.mp4",0,"");
  iVar4 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)puVar2),"SpaceRed.txt");
  cRBackdrop::Change((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),
                     (cRLandscape *)(&DAT_003593dc + *(int *)puVar2 + iVar4 * 0x1ac),false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar2 + 0xd14),0.0);
  cRStarManager::UnHide((cRStarManager *)(*(int *)puVar2 + 0x4e718));
  pcVar5 = (char *)RShellLoadFile(param_1,(int *)0x0);
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(PTR__gConfig_001b60d4 + 0x1c);
  iVar4 = *(int *)puVar2;
  tMatrix::tMatrix((tMatrix *)&local_80,1.0,0.0,0.0,0.0,0.0,0.634393,0.77301,0.0,0.0,-0.77301,
                   0.634393,0.0,0.0,0.0,0.0,1.0);
  *(undefined4 *)(iVar4 + 0x100) = local_80;
  *(undefined4 *)(iVar4 + 0x104) = uStack_7c;
  *(undefined4 *)(iVar4 + 0x108) = uStack_78;
  *(undefined4 *)(iVar4 + 0x10c) = uStack_74;
  *(undefined4 *)(iVar4 + 0x110) = local_70;
  *(undefined4 *)(iVar4 + 0x114) = uStack_6c;
  *(undefined4 *)(iVar4 + 0x118) = uStack_68;
  *(undefined4 *)(iVar4 + 0x11c) = uStack_64;
  *(undefined4 *)(iVar4 + 0x120) = local_60;
  *(undefined4 *)(iVar4 + 0x124) = uStack_5c;
  *(undefined4 *)(iVar4 + 0x128) = uStack_58;
  *(undefined4 *)(iVar4 + 300) = uStack_54;
  *(undefined4 *)(iVar4 + 0x130) = local_50;
  *(undefined4 *)(iVar4 + 0x134) = uStack_4c;
  *(undefined4 *)(iVar4 + 0x138) = uStack_48;
  *(undefined4 *)(iVar4 + 0x13c) = uStack_44;
  *(undefined4 *)(*(int *)puVar2 + 0x21c) = 0x42c80000;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0x3ada740e;
  cRMouse::SetInActive((cRMouse *)(*(int *)puVar2 + 0x228));
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  local_34[0] = (char *)Rstrfind("Text Start:",pcVar5);
  iVar4 = Rstrfind(":",local_34[0]);
  local_34[0] = (char *)(iVar4 + 1);
  pcVar6 = (char *)Rstrfind("Text End:",pcVar5);
  pcVar11 = local_34[0];
  while (pcVar11 < pcVar6) {
    cVar3 = *pcVar11;
    if (cVar3 == '*') {
      local_34[0] = pcVar11 + 1;
      pcVar10 = local_34[0];
    }
    else {
      pcVar10 = pcVar11;
      if (cVar3 != '\0' && cVar3 != '\r') {
        iVar4 = 0;
        fVar28 = 0.0;
        do {
          iVar7 = FontASCIIRemap(cVar3);
          iVar4 = iVar4 + 1;
          pcVar10 = local_34[0] + 1;
          cVar3 = local_34[0][1];
          fVar28 = fVar28 + *(float *)(PTR__RFont3D_001b61f4 + iVar7 * 4 + 0x1600);
          local_34[0] = pcVar10;
        } while (cVar3 != '\0' && cVar3 != '\r');
        iVar7 = 0;
        fVar28 = fVar28 * 0.5;
        while( true ) {
          cVar3 = pcVar11[iVar7];
          if (cVar3 != ' ') {
            iVar16 = *(int *)(this + 0x18);
            fVar22 = 0.0;
            iVar8 = FontASCIIRemap(cVar3);
            cRBod::SetObject((cRBod *)(this + iVar16 * 0x84 + 0x1c),
                             *(cRObject **)(PTR__RFont3D_001b61f4 + iVar8 * 0x2c + 0x24));
            tMatrix::Identity((tMatrix *)(this + *(int *)(this + 0x18) * 0x84 + 0x48));
            iVar8 = *(int *)(this + 0x18);
            *(float *)(this + iVar8 * 0x84 + 0x80) = fVar22;
            *(float *)(this + iVar8 * 0x84 + 0x78) = fVar22;
            *(undefined4 *)(this + iVar8 * 0x84 + 0x7c) = 0xc0800000;
            *(float *)(this + *(int *)(this + 0x18) * 0x84 + 0x7c) =
                 *(float *)(this + *(int *)(this + 0x18) * 0x84 + 0x7c) + fVar22;
            *(float *)(this + *(int *)(this + 0x18) * 0x84 + 0x78) =
                 *(float *)(this + *(int *)(this + 0x18) * 0x84 + 0x78) + fVar28;
            *(float *)(this + *(int *)(this + 0x18) * 0x84 + 0x80) =
                 *(float *)(this + *(int *)(this + 0x18) * 0x84 + 0x80) + (float)uVar29;
            tColourSmall::White((tColourSmall *)(this + *(int *)(this + 0x18) * 0x84 + 0x44));
            tColourSmall::Alpha((tColourSmall *)(this + *(int *)(this + 0x18) * 0x84 + 0x44),0.999);
            iVar8 = *(int *)(this + 0x18);
            *(float *)(this + iVar8 * 0x84 + 0x98) = fVar22;
            *(float *)(this + iVar8 * 0x84 + 0x94) = fVar22;
            *(float *)(this + iVar8 * 0x84 + 0x90) = fVar22;
            this[*(int *)(this + 0x18) * 0x84 + 0x9c] = *(cRLogo *)(pcVar11 + iVar7);
            (*(code *)**(undefined4 **)(this + *(int *)(this + 0x18) * 0x84 + 0x1c))
                      (this + *(int *)(this + 0x18) * 0x84 + 0x1c);
            *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
            cVar3 = pcVar11[iVar7];
          }
          iVar8 = FontASCIIRemap(cVar3);
          iVar7 = iVar7 + 1;
          pcVar10 = local_34[0];
          if (iVar7 == iVar4) break;
          fVar28 = fVar28 - *(float *)(PTR__RFont3D_001b61f4 + iVar8 * 4 + 0x1600);
        }
      }
    }
    pcVar11 = pcVar10;
    if (*pcVar10 == '\r') {
      pcVar11 = pcVar10 + 2;
      uVar29 = (ulonglong)(uint)((float)uVar29 - 1.0);
      local_34[0] = pcVar11;
    }
  }
  fVar28 = (float)uVar29;
  iVar4 = *(int *)(this + 0x18);
  *(undefined4 *)(this + 0x2101c) = 0;
  if (0 < iVar4) {
    iVar7 = 0;
    do {
      iVar8 = 0;
      pcVar21 = this + (iVar7 + 1) * 0x84 + 0x80;
      fVar28 = *(float *)(this + iVar7 * 0x84 + 0x80);
      while (iVar8 < 0x14 && fVar28 == *(float *)(this + iVar7 * 0x84 + 0x80)) {
        iVar8 = iVar8 + 1;
        iVar16 = iVar8 + iVar7;
        if (iVar4 <= iVar16) goto LAB_00066028;
        fVar28 = *(float *)pcVar21;
        pcVar21 = pcVar21 + 0x84;
      }
      iVar16 = iVar8 + iVar7;
LAB_00066028:
      iVar12 = *(int *)PTR__Game_001b60b8;
      iVar17 = *(int *)(this + 0x2101c);
      iVar4 = iVar17 * 0x84;
      if ((*(uint *)(this + iVar4 + 0x21024) & 0x200) == 0) {
        if (*(int *)(iVar12 + 0x35c) == 0) {
          *(cRLogo **)(iVar12 + 0x35c) = this + iVar4 + 0x21020;
          *(undefined4 *)(this + iVar4 + 0x21028) = 0;
          *(undefined4 *)(*(int *)(iVar12 + 0x35c) + 0xc) = 0;
        }
        else {
          *(cRLogo **)(*(int *)(iVar12 + 0x35c) + 8) = this + iVar4 + 0x21020;
          *(int *)(*(int *)(*(int *)(iVar12 + 0x35c) + 8) + 0xc) = *(int *)(iVar12 + 0x35c);
          iVar4 = *(int *)(*(int *)(iVar12 + 0x35c) + 8);
          *(int *)(iVar12 + 0x35c) = iVar4;
          *(undefined4 *)(iVar4 + 8) = 0;
        }
        *(uint *)(this + iVar17 * 0x84 + 0x21024) =
             *(uint *)(this + iVar17 * 0x84 + 0x21024) | 0x200;
      }
      else {
        RShellError("List ADD");
      }
      fVar28 = (float)uVar29;
      iVar7 = iVar7 * 0x84;
      pcVar21 = this + iVar7 + 0x1c;
      *(cRLogo **)(this + *(int *)(this + 0x2101c) * 0x84 + 0x210a0) = pcVar21;
      iVar4 = *(int *)(this + 0x2101c);
      uVar13 = *(undefined4 *)(this + iVar7 + 0x4c);
      uVar15 = *(undefined4 *)(this + iVar7 + 0x50);
      uVar18 = *(undefined4 *)(this + iVar7 + 0x54);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x2104c) = *(undefined4 *)(this + iVar7 + 0x48);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21050) = uVar13;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21054) = uVar15;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21058) = uVar18;
      uVar13 = *(undefined4 *)(this + iVar7 + 0x5c);
      uVar15 = *(undefined4 *)(this + iVar7 + 0x60);
      uVar18 = *(undefined4 *)(this + iVar7 + 100);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x2105c) = *(undefined4 *)(this + iVar7 + 0x58);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21060) = uVar13;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21064) = uVar15;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21068) = uVar18;
      uVar13 = *(undefined4 *)(this + iVar7 + 0x6c);
      uVar15 = *(undefined4 *)(this + iVar7 + 0x70);
      uVar18 = *(undefined4 *)(this + iVar7 + 0x74);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x2106c) = *(undefined4 *)(this + iVar7 + 0x68);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21070) = uVar13;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21074) = uVar15;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21078) = uVar18;
      uVar13 = *(undefined4 *)(this + iVar7 + 0x7c);
      uVar15 = *(undefined4 *)(this + iVar7 + 0x80);
      uVar18 = *(undefined4 *)(this + iVar7 + 0x84);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x2107c) = *(undefined4 *)(this + iVar7 + 0x78);
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21080) = uVar13;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21084) = uVar15;
      *(undefined4 *)(this + iVar4 * 0x84 + 0x21088) = uVar18;
      iVar4 = *(int *)(this + *(int *)(this + 0x2101c) * 0x84 + 0x21044);
      **(undefined4 **)(iVar4 + 0x10c) = **(undefined4 **)(*(int *)(this + iVar7 + 0x40) + 0x10c);
      *(int *)(*(int *)(iVar4 + 0x10c) + 0x44) = iVar8 * 6;
      if (0 < iVar8) {
        iVar12 = 0;
        iVar17 = 0;
        do {
          iVar9 = iVar17 + 0x14;
          iVar12 = iVar12 + 1;
          pfVar14 = (float *)(iVar17 + *(int *)(*(int *)(iVar4 + 0x10c) + 8));
          pfVar19 = *(float **)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8);
          fVar26 = *(float *)(pcVar21 + 0x60);
          fVar22 = pfVar19[1];
          fVar23 = *(float *)(this + iVar7 + 0x7c);
          *pfVar14 = (*pfVar19 + *(float *)(pcVar21 + 0x5c)) - *(float *)(this + iVar7 + 0x78);
          fVar24 = *(float *)(pcVar21 + 100);
          fVar27 = pfVar19[2];
          fVar25 = *(float *)(this + iVar7 + 0x80);
          pfVar14[1] = (fVar22 + fVar26) - fVar23;
          pfVar14[2] = (fVar27 + fVar24) - fVar25;
          *(undefined4 *)(iVar17 + *(int *)(*(int *)(iVar4 + 0x10c) + 8) + 0xc) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8) + 0xc);
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x10c) + 8) + iVar17 + 0x10) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8) + 0x10);
          fVar26 = *(float *)(pcVar21 + 0x5c);
          pfVar14 = (float *)(iVar9 + *(int *)(*(int *)(iVar4 + 0x10c) + 8));
          iVar20 = *(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8);
          fVar22 = *(float *)(iVar20 + 0x14);
          fVar23 = *(float *)(this + iVar7 + 0x78);
          fVar24 = *(float *)(iVar20 + 0x18);
          fVar27 = *(float *)(pcVar21 + 0x60);
          fVar25 = *(float *)(this + iVar7 + 0x7c);
          pfVar14[2] = (*(float *)(iVar20 + 0x1c) + *(float *)(pcVar21 + 100)) -
                       *(float *)(this + iVar7 + 0x80);
          pfVar14[1] = (fVar24 + fVar27) - fVar25;
          *pfVar14 = (fVar22 + fVar26) - fVar23;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x10c) + 8) + iVar9 + 0xc) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8) + 0x20);
          iVar20 = iVar17 + 0x28;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x10c) + 8) + iVar9 + 0x10) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8) + 0x24);
          pfVar14 = (float *)(iVar20 + *(int *)(*(int *)(iVar4 + 0x10c) + 8));
          iVar9 = *(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8);
          fVar22 = *(float *)(iVar9 + 0x2c);
          fVar26 = *(float *)(pcVar21 + 0x60);
          fVar23 = *(float *)(this + iVar7 + 0x7c);
          *pfVar14 = (*(float *)(iVar9 + 0x28) + *(float *)(pcVar21 + 0x5c)) -
                     *(float *)(this + iVar7 + 0x78);
          fVar24 = *(float *)(pcVar21 + 100);
          fVar27 = *(float *)(iVar9 + 0x30);
          fVar25 = *(float *)(this + iVar7 + 0x80);
          pfVar14[1] = (fVar22 + fVar26) - fVar23;
          pfVar14[2] = (fVar27 + fVar24) - fVar25;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x10c) + 8) + iVar20 + 0xc) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8) + 0x34);
          iVar9 = iVar17 + 0x3c;
          iVar17 = iVar17 + 0x50;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x10c) + 8) + iVar20 + 0x10) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8) + 0x38);
          pfVar14 = (float *)(iVar9 + *(int *)(*(int *)(iVar4 + 0x10c) + 8));
          iVar20 = *(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8);
          fVar22 = *(float *)(iVar20 + 0x40);
          fVar26 = *(float *)(pcVar21 + 0x60);
          fVar23 = *(float *)(this + iVar7 + 0x7c);
          *pfVar14 = (*(float *)(iVar20 + 0x3c) + *(float *)(pcVar21 + 0x5c)) -
                     *(float *)(this + iVar7 + 0x78);
          fVar24 = *(float *)(pcVar21 + 100);
          fVar27 = *(float *)(iVar20 + 0x44);
          fVar25 = *(float *)(this + iVar7 + 0x80);
          pfVar14[1] = (fVar22 + fVar26) - fVar23;
          pfVar14[2] = (fVar27 + fVar24) - fVar25;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x10c) + 8) + iVar9 + 0xc) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)(pcVar21 + 0x24) + 0x10c) + 8) + 0x48);
          pcVar1 = pcVar21 + 0x24;
          pcVar21 = pcVar21 + 0x84;
          *(undefined4 *)(*(int *)(*(int *)(iVar4 + 0x10c) + 8) + iVar9 + 0x10) =
               *(undefined4 *)(*(int *)(*(int *)(*(int *)pcVar1 + 0x10c) + 8) + 0x4c);
        } while (iVar12 != iVar8);
      }
      iVar4 = *(int *)(this + 0x18);
      *(int *)(this + 0x2101c) = *(int *)(this + 0x2101c) + 1;
      iVar7 = iVar16;
    } while (iVar16 < iVar4);
  }
  local_34[0] = (char *)Rstrfind("Duration:",pcVar5);
  local_34[0] = (char *)Rstrfind(":",local_34[0]);
  fVar22 = (float)Rstrfloat(local_34);
  *(float *)(this + 0x14) = fVar22;
  local_3c = 0;
  local_40 = 0;
  if (fVar22 == 0.0) {
    local_38 = 0.0;
  }
  else {
    local_38 = 1.0 / (fVar22 * 60.0);
  }
  local_38 = (3.0 - fVar28) * local_38;
  if (0 < *(int *)(this + 0x2101c)) {
    pcVar21 = this + 0x21094;
    iVar4 = 0;
    do {
      _memcpy(pcVar21,&local_40,0xc);
      iVar4 = iVar4 + 1;
      pcVar21 = pcVar21 + 0x84;
    } while (iVar4 < *(int *)(this + 0x2101c));
  }
  RShellMemoryFree(pcVar5);
  return;
}
