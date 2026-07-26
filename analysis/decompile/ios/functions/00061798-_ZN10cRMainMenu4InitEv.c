/*
 * mangled: _ZN10cRMainMenu4InitEv
 * demangled: cRMainMenu::Init()
 * address: 00061798
 * size: 948
 */

/* cRMainMenu::Init() */

void __thiscall cRMainMenu::Init(cRMainMenu *this)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
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
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  cRStarManager::Hide((cRStarManager *)(*(int *)PTR__Game_001b60b8 + 0x4e718));
  RShellMusicPlay("mainmenu.mp4",0,"");
  iVar2 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),"Menubg.txt"
                    );
  cRBackdrop::Change((cRBackdrop *)(*(int *)PTR__Game_001b60b8 + 0x4d2e0),
                     (cRLandscape *)(&DAT_003593dc + *(int *)PTR__Game_001b60b8 + iVar2 * 0x1ac),
                     false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14),25.0);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)this = uVar3;
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x14,"Play",0x14,0x41a00000,0x42f00000,local_30,uStack_2c,uStack_28,uStack_24
                 ,2,0);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 4) = uVar3;
  tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x14,"High Scores",0x14,0x41a00000,0x41a00000,local_40,uStack_3c,uStack_38,
                 uStack_34,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 4),*(cRBorder **)this);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 8) = uVar3;
  tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x14,"Options",0x14,0x41a00000,0x41a00000,local_50,uStack_4c,uStack_48,
                 uStack_44,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 8),*(cRBorder **)(this + 4));
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0xc) = uVar3;
  tColour::tColour((tColour *)&local_60,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x40000014,"Credits",0x14,0x41a00000,0x41a00000,local_60,uStack_5c,uStack_58,
                 uStack_54,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0xc),*(cRBorder **)(this + 8));
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)(this + 0x10) = uVar3;
  if ((*(float *)(*(int *)puVar1 + 0x40) == 90.0) || (*(float *)(*(int *)puVar1 + 0x40) == 270.0)) {
    tColour::tColour((tColour *)&local_70,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar3,0x20400812,0x8c,0x44100000,0x43d00000,local_70,uStack_6c,uStack_68,
                   uStack_64,0,1);
  }
  else {
    tColour::tColour((tColour *)&local_80,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar3,0x20400812,0x8d,0x44000000,0x43d00000,local_80,uStack_7c,uStack_78,
                   uStack_74,0,1);
  }
  return;
}
