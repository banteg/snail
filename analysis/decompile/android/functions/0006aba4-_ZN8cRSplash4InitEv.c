/*
 * mangled: _ZN8cRSplash4InitEv
 * demangled: cRSplash::Init()
 * address: 0006aba4
 * size: 508
 */

/* cRSplash::Init() */

void __thiscall cRSplash::Init(cRSplash *this)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;

  cRFade::FadeIn((cRFade *)(Game + 0x24));
  cRStarManager::Hide((cRStarManager *)(Game + 0x4d440));
  RShellMusicPlay("introtext",0,"");
  if (*(int *)(gOFOData + Game + 0x1ebc) == 0) {
    iVar1 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"Splash.txt");
  }
  else {
    iVar1 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"SplashPro.txt");
  }
  fVar3 = (float)cRBackdrop::Change((cRBackdrop *)(Game + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + iVar1 * 0x1ac + Game + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar3);
  iVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  iVar2 = *(int *)(gOFOData + Game + 0x1ebc);
  *(int *)(this + 8) = iVar1;
  if (iVar2 == 0) {
    tColour::tColour((tColour *)&local_28,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar2 = -0x7560;
  }
  else {
    if (iVar2 != 1) goto LAB_0006ad00;
    tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar2 = -0x7548;
    local_28 = local_38;
    uStack_24 = uStack_34;
    uStack_20 = uStack_30;
    uStack_1c = uStack_2c;
  }
  cRBorder::Init(iVar1,0x20400002,(int)&__DT_PLTGOT + iVar2,0x14,0,0x43ca8000,local_28,uStack_24,
                 uStack_20,uStack_1c,2,0);
  iVar1 = *(int *)(this + 8);
LAB_0006ad00:
  *(undefined4 *)(this + 0xc) = 0;
  *this = (cRSplash)0x0;
  *(undefined4 *)(iVar1 + 0x6e8) = 0x3f99999a;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0x3b888889;
  return;
}
