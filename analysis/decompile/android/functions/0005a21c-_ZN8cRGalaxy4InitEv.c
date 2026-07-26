/*
 * mangled: _ZN8cRGalaxy4InitEv
 * demangled: cRGalaxy::Init()
 * address: 0005a21c
 * size: 652
 */

/* cRGalaxy::Init() */

void __thiscall cRGalaxy::Init(cRGalaxy *this)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 extraout_r3;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int unaff_r9;
  float fVar12;

  iVar2 = DAT_0005a4b0;
  iVar6 = DAT_0005a4ac;
  iVar9 = DAT_0005a4a8 + 0x5a234;
  iVar10 = *(int *)(iVar9 + DAT_0005a4ac);
  iVar1 = Rstrcmp((char *)(iVar9 + DAT_0005a4b0),(char *)(iVar10 + 0x60));
  iVar4 = DAT_0005a4b4;
  if (iVar1 == 0) {
    iVar1 = **(int **)(iVar9 + DAT_0005a4b4);
  }
  else {
    iVar1 = **(int **)(iVar9 + DAT_0005a4b4);
    iVar7 = *(int *)(gOFOData + iVar1 + 0x1ed8);
    iVar5 = *(int *)(iVar9 + iVar6);
    if (iVar7 < *(int *)(iVar10 + 0xa4)) {
      *(int *)(iVar10 + 0xa4) = iVar7;
    }
    *(int *)(iVar10 + 0xa0) = iVar7;
    iVar10 = *(int *)(&DAT_0039b7e8 + iVar1);
    *(int *)(iVar5 + 0xe8) = iVar10;
    if (iVar10 < *(int *)(iVar5 + 0xec)) {
      *(int *)(iVar5 + 0xec) = iVar10;
    }
  }
  cRFade::FadeIn((cRFade *)(iVar1 + 0x24));
  piVar11 = *(int **)(iVar9 + iVar4);
  *(undefined4 *)this = 1;
  cRStarManager::Hide((cRStarManager *)(*piVar11 + 0x4d440));
  RShellMusicPlay((char *)(iVar9 + DAT_0005a4b8),0,(char *)(iVar9 + DAT_0005a4bc));
  iVar1 = *piVar11;
  if (*(int *)(gOFOData + iVar1 + 0x1ebc) == 0) {
    unaff_r9 = cRLandscapeManager::Import
                         ((cRLandscapeManager *)(gSegmentText + iVar1 + 0x3d8),
                          (char *)(iVar9 + DAT_0005a4c0));
    iVar1 = *piVar11;
  }
  else if (*(int *)(gOFOData + iVar1 + 0x1ebc) == 1) {
    unaff_r9 = cRLandscapeManager::Import
                         ((cRLandscapeManager *)(gSegmentText + iVar1 + 0x3d8),
                          (char *)(iVar9 + DAT_0005a4c4));
    iVar1 = *piVar11;
  }
  fVar12 = (float)cRBackdrop::Change((cRBackdrop *)(iVar1 + 0x4d2e0),
                                     (cRLandscape *)
                                     (gSegmentText + unaff_r9 * 0x1ac + iVar1 + 0x3dc),false);
  piVar11 = *(int **)(iVar9 + iVar4);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar11 + 0xd14),fVar12);
  cRMouse::SetActive((cRMouse *)(*piVar11 + 0x228));
  iVar4 = *(int *)(this + 0x8e24);
  iVar1 = *(int *)(iVar4 + 0x60);
  if (iVar1 != 0) goto LAB_0005a370;
  iVar1 = *(int *)(gGroup0 + iVar4 + 0xc06f4);
  if (iVar1 - 2U < 2) {
    *(undefined4 *)(this + 0xc) = 0;
    *(undefined4 *)(this + 4) = 0;
    if (*(int *)(gGroup0 + iVar4 + 0xaea18) == 0) {
      *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(*(int *)(iVar9 + iVar6) + 0xa4);
    }
    else if (*(int *)(gGroup0 + iVar4 + 0xaea18) == 1) {
      iVar1 = *(int *)(iVar9 + iVar6);
      iVar2 = Rstrcmp((char *)(iVar9 + iVar2),(char *)(iVar1 + 0x60));
      uVar3 = *(undefined4 *)(*(int *)(iVar9 + iVar6) + 0xec);
      uVar8 = extraout_r3;
      if (iVar2 != 0) {
        uVar8 = *(undefined4 *)(&DAT_0039b7e8 + *piVar11);
      }
      iVar4 = *(int *)(this + 0x8e24);
      if (iVar2 != 0) {
        *(undefined4 *)(iVar1 + 0xe8) = uVar8;
      }
      *(undefined4 *)(this + 0x8e34) = uVar3;
      iVar1 = *(int *)(gGroup0 + iVar4 + 0xc06f4);
      goto LAB_0005a340;
    }
    iVar1 = *(int *)(gGroup0 + iVar4 + 0xc06f4);
  }
LAB_0005a340:
  if (iVar1 == 1 || iVar1 == 4) {
    *(undefined4 *)(this + 0xc) = 1;
    *(undefined4 *)(this + 4) = 1;
    *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(*(int *)(this + 0x8e24) + 100);
    iVar1 = *(int *)(*(int *)(this + 0x8e24) + 0x60);
  }
  else {
    iVar1 = *(int *)(iVar4 + 0x60);
  }
LAB_0005a370:
  if (iVar1 == 4) {
    iVar6 = *(int *)(iVar9 + iVar6);
    *(undefined4 *)(this + 4) = 0;
    *(undefined4 *)(this + 0xc) = 2;
    *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(iVar6 + 0xa4);
  }
  Init2(this);
  return;
}
