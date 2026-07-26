/*
 * mangled: _ZN8cRSplash4InitEv
 * demangled: cRSplash::Init()
 * address: 00063b8c
 * size: 488
 */

/* cRSplash::Init() */

void __thiscall cRSplash::Init(cRSplash *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;

  puVar1 = PTR__Game_001b60b8;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  cRStarManager::Hide((cRStarManager *)(*(int *)puVar1 + 0x4e718));
  RShellMusicPlay("introtext.mp4",0,"");
  iVar3 = *(int *)puVar1;
  if (*(int *)(&DAT_00364944 + iVar3) == 0) {
    iVar3 = cRLandscapeManager::Import((cRLandscapeManager *)(&DAT_003593d8 + iVar3),"Splash.txt");
  }
  else {
    iVar3 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(&DAT_003593d8 + iVar3),"SplashPro.txt");
  }
  puVar1 = PTR__Game_001b60b8;
  cRBackdrop::Change((cRBackdrop *)(*(int *)PTR__Game_001b60b8 + 0x4d2e0),
                     (cRLandscape *)(&DAT_003593dc + *(int *)PTR__Game_001b60b8 + iVar3 * 0x1ac),
                     false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar1 + 0xd14),0.0);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 8) = uVar2;
  if (*(int *)(&DAT_00364944 + *(int *)puVar1) == 0) {
    tColour::tColour((tColour *)&local_24,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x20400002,">Thanks For Playing!",0x14,0,0x43ca8000,local_24,uStack_20,
                   uStack_1c,uStack_18,2,0);
  }
  else if (*(int *)(&DAT_00364944 + *(int *)puVar1) == 1) {
    tColour::tColour((tColour *)&local_34,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x20400002,">Holy Flying Snails!",0x14,0,0x43ca8000,local_34,uStack_30,
                   uStack_2c,uStack_28,2,0);
  }
  *(undefined4 *)(*(int *)(this + 8) + 0x6e8) = 0x3f99999a;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0x3b888889;
  *this = (cRSplash)0x0;
  *(undefined4 *)(this + 0xc) = 0;
  return;
}
