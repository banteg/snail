/*
 * mangled: _ZN8cRGalaxy4InitEv
 * demangled: cRGalaxy::Init()
 * address: 0006a450
 * size: 588
 */

/* cRGalaxy::Init() */

void __thiscall cRGalaxy::Init(cRGalaxy *this)

{
  undefined *puVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;

  puVar1 = PTR__gConfig_001b60d4;
  iVar2 = Rstrcmp("Fluctuosa",PTR__gConfig_001b60d4 + 0x60);
  puVar3 = PTR__Game_001b60b8;
  if (iVar2 != 0) {
    iVar2 = *(int *)(&DAT_00364960 + *(int *)PTR__Game_001b60b8);
    if (iVar2 < *(int *)(puVar1 + 0xa4)) {
      *(int *)(puVar1 + 0xa4) = iVar2;
    }
    *(int *)(puVar1 + 0xa0) = iVar2;
    iVar2 = *(int *)(&DAT_0036d7cc + *(int *)puVar3);
    *(int *)(puVar1 + 0xe8) = iVar2;
    if (iVar2 < *(int *)(puVar1 + 0xec)) {
      *(int *)(puVar1 + 0xec) = iVar2;
    }
  }
  puVar3 = PTR__Game_001b60b8;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  *(undefined4 *)this = 1;
  cRStarManager::Hide((cRStarManager *)(*(int *)puVar3 + 0x4e718));
  RShellMusicPlay("mainmenu.mp4",0,"");
  iVar2 = *(int *)puVar3;
  if (*(int *)(&DAT_00364944 + iVar2) == 0) {
    puVar3 = (undefined *)
             cRLandscapeManager::Import((cRLandscapeManager *)(&DAT_003593d8 + iVar2),"StarMap.txt")
    ;
  }
  else if (*(int *)(&DAT_00364944 + iVar2) == 1) {
    puVar3 = (undefined *)
             cRLandscapeManager::Import
                       ((cRLandscapeManager *)(&DAT_003593d8 + iVar2),"StarMapPro.txt");
  }
  puVar1 = PTR__Game_001b60b8;
  cRBackdrop::Change((cRBackdrop *)(*(int *)PTR__Game_001b60b8 + 0x4d2e0),
                     (cRLandscape *)
                     (&DAT_003593dc + *(int *)PTR__Game_001b60b8 + (int)puVar3 * 0x1ac),false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar1 + 0xd14),0.0);
  cRMouse::SetActive((cRMouse *)(*(int *)puVar1 + 0x228));
  iVar4 = *(int *)(this + 0x8e24);
  iVar2 = *(int *)(iVar4 + 0x58);
  if (iVar2 != 0) goto LAB_0006a5c0;
  iVar2 = *(int *)(&DAT_00303aa8 + iVar4);
  if (iVar2 - 2U < 2) {
    *(undefined4 *)(this + 4) = 0;
    *(undefined4 *)(this + 0xc) = 0;
    puVar3 = PTR__gConfig_001b60d4;
    if (*(int *)(&DAT_002f1dcc + iVar4) == 0) {
      *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa4);
    }
    else if (*(int *)(&DAT_002f1dcc + iVar4) == 1) {
      iVar2 = Rstrcmp("Fluctuosa",PTR__gConfig_001b60d4 + 0x60);
      if (iVar2 != 0) {
        *(undefined4 *)(puVar3 + 0xe8) = *(undefined4 *)(&DAT_0036d7cc + *(int *)puVar1);
      }
      iVar4 = *(int *)(this + 0x8e24);
      *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(puVar3 + 0xec);
      iVar2 = *(int *)(&DAT_00303aa8 + iVar4);
      goto LAB_0006a5a0;
    }
    iVar2 = *(int *)(&DAT_00303aa8 + iVar4);
  }
LAB_0006a5a0:
  if (iVar2 == 1) {
    *(undefined4 *)(this + 4) = 1;
    *(undefined4 *)(this + 0xc) = 1;
    *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(*(int *)(this + 0x8e24) + 0x5c);
    iVar2 = *(int *)(*(int *)(this + 0x8e24) + 0x58);
  }
  else {
    iVar2 = *(int *)(iVar4 + 0x58);
  }
LAB_0006a5c0:
  if (iVar2 == 4) {
    *(undefined4 *)(this + 4) = 0;
    *(undefined4 *)(this + 0xc) = 2;
    *(undefined4 *)(this + 0x8e34) = *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa4);
  }
  Init2(this);
  return;
}
