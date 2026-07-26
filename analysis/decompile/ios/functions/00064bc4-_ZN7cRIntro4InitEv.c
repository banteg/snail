/*
 * mangled: _ZN7cRIntro4InitEv
 * demangled: cRIntro::Init()
 * address: 00064bc4
 * size: 1288
 */

/* cRIntro::Init() */

void __thiscall cRIntro::Init(cRIntro *this)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  puVar1 = PTR__Game_001b60b8;
  fVar4 = 20.0;
  fVar5 = 90.0;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  cRStarManager::Hide((cRStarManager *)(*(int *)puVar1 + 0x4e718));
  RShellMusicPlay("mainmenu.mp4",0,"");
  iVar2 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)puVar1),"Menubg.txt");
  cRBackdrop::Change((cRBackdrop *)(*(int *)puVar1 + 0x4d2e0),
                     (cRLandscape *)(&DAT_003593dc + *(int *)puVar1 + iVar2 * 0x1ac),false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar1 + 0xd14),25.0);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x40) = uVar3;
  tColour::tColour((tColour *)&local_38,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x40000014,"Tutorial",0x14,fVar4,fVar5,local_38,uStack_34,uStack_30,uStack_2c
                 ,2,0);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x30) = uVar3;
  tColour::tColour((tColour *)&local_48,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x40000014,"Postal Adventure",0x14,fVar4,fVar4,local_48,uStack_44,uStack_40,
                 uStack_3c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x30),*(cRBorder **)(this + 0x40));
  if (*(int *)(PTR__gConfig_001b60d4 + 0xcc) - 1U < 2) {
    *(uint *)(*(int *)(this + 0x30) + 0x194) = *(uint *)(*(int *)(this + 0x30) + 0x194) & 0xbfffffff
    ;
  }
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x34) = uVar3;
  tColour::tColour((tColour *)&local_58,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x40000014,"Pro-Challenge",0x14,fVar4,fVar4,local_58,uStack_54,uStack_50,
                 uStack_4c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x34),*(cRBorder **)(this + 0x30));
  if (*(int *)(PTR__gConfig_001b60d4 + 0xcc) - 1U < 2) {
    *(uint *)(*(int *)(this + 0x34) + 0x194) = *(uint *)(*(int *)(this + 0x34) + 0x194) & 0xbfffffff
    ;
  }
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x38) = uVar3;
  tColour::tColour((tColour *)&local_68,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x40000014,"Time Trial",0x14,fVar4,fVar4,local_68,uStack_64,uStack_60,
                 uStack_5c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x38),*(cRBorder **)(this + 0x34));
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x3c) = uVar3;
  tColour::tColour((tColour *)&local_78,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x14,"Challenge Mode",0x14,fVar4,fVar4,local_78,uStack_74,uStack_70,uStack_6c
                 ,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x3c),*(cRBorder **)(this + 0x38));
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x44) = uVar3;
  tColour::tColour((tColour *)&local_88,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x40000014,"Help",0x14,0,0x43af0000,local_88,uStack_84,uStack_80,uStack_7c,2,
                 0xc3520000);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x48) = uVar3;
  tColour::tColour((tColour *)&local_98,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x14,"Back",0x14,fVar4,0x43af0000,local_98,uStack_94,uStack_90,uStack_8c,2,0)
  ;
  cRBorder::SetBelow(*(cRBorder **)(this + 0x48),*(cRBorder **)(this + 0x3c));
  if ((*(float *)(*(int *)puVar1 + 0x3c) == fVar5) || (*(float *)(*(int *)puVar1 + 0x3c) == 270.0))
  {
    *(undefined4 *)(*(int *)(this + 0x44) + 0x6f0) = *(undefined4 *)(*(int *)(this + 0x3c) + 0x6f0);
    *(undefined4 *)(*(int *)(this + 0x44) + 0x230) = *(undefined4 *)(*(int *)(this + 0x3c) + 0x230);
  }
  else {
    *(undefined4 *)(*(int *)(this + 0x44) + 0x6f0) = *(undefined4 *)(*(int *)(this + 0x48) + 0x6f0);
    *(undefined4 *)(*(int *)(this + 0x44) + 0x230) = *(undefined4 *)(*(int *)(this + 0x48) + 0x230);
    *(float *)(*(int *)(this + 0x44) + 600) = *(float *)(*(int *)(this + 0x44) + 600) + fVar4;
  }
  if (PTR__gConfig_001b60d4[0xc0] == '\0') {
    *(uint *)(*(int *)(this + 0x30) + 0x194) = *(uint *)(*(int *)(this + 0x30) + 0x194) | 0x8000;
    *(uint *)(*(int *)(this + 0x34) + 0x194) = *(uint *)(*(int *)(this + 0x34) + 0x194) | 0x8000;
    *(uint *)(*(int *)(this + 0x38) + 0x194) = *(uint *)(*(int *)(this + 0x38) + 0x194) | 0x8000;
    *(uint *)(*(int *)(this + 0x3c) + 0x194) = *(uint *)(*(int *)(this + 0x3c) + 0x194) | 0x8000;
  }
  return;
}
