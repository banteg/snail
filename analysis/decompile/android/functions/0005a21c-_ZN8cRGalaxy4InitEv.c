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
  undefined4 extraout_r3;
  undefined4 uVar3;
  int unaff_r9;
  float fVar4;

  iVar1 = Rstrcmp("Fluctuosa",gConfig + 0x60);
  if (iVar1 != 0) {
    gConfig._160_4_ = *(undefined4 *)(gOFOData + Game + 0x1ed8);
    if ((int)gConfig._160_4_ < (int)gConfig._164_4_) {
      gConfig._164_4_ = gConfig._160_4_;
    }
    gConfig._232_4_ = *(undefined4 *)(&DAT_0039b7e8 + Game);
    if ((int)gConfig._232_4_ < (int)gConfig._236_4_) {
      gConfig._236_4_ = gConfig._232_4_;
    }
  }
  cRFade::FadeIn((cRFade *)(Game + 0x24));
  *(undefined4 *)this = 1;
  cRStarManager::Hide((cRStarManager *)(Game + 0x4d440));
  RShellMusicPlay("mainmenu",0,"");
  if (*(int *)(gOFOData + Game + 0x1ebc) == 0) {
    unaff_r9 = cRLandscapeManager::Import
                         ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"StarMap.txt");
  }
  else if (*(int *)(gOFOData + Game + 0x1ebc) == 1) {
    unaff_r9 = cRLandscapeManager::Import
                         ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"StarMapPro.txt");
  }
  fVar4 = (float)cRBackdrop::Change((cRBackdrop *)(Game + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + unaff_r9 * 0x1ac + Game + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar4);
  cRMouse::SetActive((cRMouse *)(Game + 0x228));
  iVar1 = *(int *)(this + 0x8e24);
  iVar2 = *(int *)(iVar1 + 0x60);
  if (iVar2 != 0) goto LAB_0005a370;
  iVar2 = *(int *)(gGroup0 + iVar1 + 0xc06f4);
  if (iVar2 - 2U < 2) {
    *(undefined4 *)(this + 0xc) = 0;
    *(undefined4 *)(this + 4) = 0;
    if (*(int *)(gGroup0 + iVar1 + 0xaea18) == 0) {
      *(undefined4 *)(this + 0x8e34) = gConfig._164_4_;
    }
    else if (*(int *)(gGroup0 + iVar1 + 0xaea18) == 1) {
      iVar2 = Rstrcmp("Fluctuosa",gConfig + 0x60);
      uVar3 = extraout_r3;
      if (iVar2 != 0) {
        uVar3 = *(undefined4 *)(&DAT_0039b7e8 + Game);
      }
      iVar1 = *(int *)(this + 0x8e24);
      if (iVar2 != 0) {
        gConfig._232_4_ = uVar3;
      }
      *(undefined4 *)(this + 0x8e34) = gConfig._236_4_;
      iVar2 = *(int *)(gGroup0 + iVar1 + 0xc06f4);
      goto LAB_0005a340;
    }
    iVar2 = *(int *)(gGroup0 + iVar1 + 0xc06f4);
  }
LAB_0005a340:
  if (iVar2 == 1 || iVar2 == 4) {
    *(undefined4 *)(this + 0xc) = 1;
    *(undefined4 *)(this + 4) = 1;
    *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(*(int *)(this + 0x8e24) + 100);
    iVar2 = *(int *)(*(int *)(this + 0x8e24) + 0x60);
  }
  else {
    iVar2 = *(int *)(iVar1 + 0x60);
  }
LAB_0005a370:
  if (iVar2 == 4) {
    *(undefined4 *)(this + 4) = 0;
    *(undefined4 *)(this + 0xc) = 2;
    *(undefined4 *)(this + 0x8e34) = gConfig._164_4_;
  }
  Init2(this);
  return;
}
