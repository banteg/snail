/*
 * mangled: _ZN7cRIntro4InitEv
 * demangled: cRIntro::Init()
 * address: 000674f8
 * size: 1332
 */

/* cRIntro::Init() */

void __thiscall cRIntro::Init(cRIntro *this)

{
  int iVar1;
  undefined4 uVar2;
  cRBorderManager *this_00;
  int iVar3;
  int iVar4;
  float fVar5;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float extraout_s2_05;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float extraout_s3_05;
  undefined4 local_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
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

  cRFade::FadeIn((cRFade *)(Game + 0x24));
  cRStarManager::Hide((cRStarManager *)(Game + 0x4d440));
  RShellMusicPlay("mainmenu",0,"");
  iVar1 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"Menubg.txt");
  fVar5 = (float)cRBackdrop::Change((cRBackdrop *)(Game + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + iVar1 * 0x1ac + Game + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar5);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x40) = uVar2;
  tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,0x40000014,"Tutorial",0x14,0x41a00000,0x42b40000,local_48,uStack_44,uStack_40
                 ,uStack_3c,2,0);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x30) = uVar2;
  tColour::tColour((tColour *)&local_58,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar2,0x40000014,"Postal Adventure",0x14,0x41a00000,0x41a00000,local_58,uStack_54,
                 uStack_50,uStack_4c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x30),*(cRBorder **)(this + 0x40));
  if (0 < (int)gConfig._208_4_) {
    *(uint *)(*(int *)(this + 0x30) + 0x194) = *(uint *)(*(int *)(this + 0x30) + 0x194) & 0xbfffffff
    ;
  }
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x34) = uVar2;
  tColour::tColour((tColour *)&local_68,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar2,0x40000014,"Pro-Challenge",0x14,0x41a00000,0x41a00000,local_68,uStack_64,
                 uStack_60,uStack_5c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x34),*(cRBorder **)(this + 0x30));
  this_00 = (cRBorderManager *)(Game + 0xd14);
  if (0 < (int)gConfig._224_4_) {
    *(uint *)(*(int *)(this + 0x34) + 0x194) = *(uint *)(*(int *)(this + 0x34) + 0x194) & 0xbfffffff
    ;
  }
  uVar2 = cRBorderManager::GetBorder(this_00);
  *(undefined4 *)(this + 0x38) = uVar2;
  tColour::tColour((tColour *)&local_78,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar2,0x40000014,"Time Trial",0x14,0x41a00000,0x41a00000,local_78,uStack_74,
                 uStack_70,uStack_6c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x38),*(cRBorder **)(this + 0x34));
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x3c) = uVar2;
  tColour::tColour((tColour *)&local_88,extraout_s0_03,extraout_s1_03,extraout_s2_03,extraout_s3_03)
  ;
  cRBorder::Init(uVar2,0x14,"Challenge Mode",0x14,0x41a00000,0x41a00000,local_88,uStack_84,uStack_80
                 ,uStack_7c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x3c),*(cRBorder **)(this + 0x38));
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x44) = uVar2;
  tColour::tColour((tColour *)&local_98,extraout_s0_04,extraout_s1_04,extraout_s2_04,extraout_s3_04)
  ;
  cRBorder::Init(uVar2,0x40000014,&DAT_00093600,0x14,0,0x43af0000,local_98,uStack_94,uStack_90,
                 uStack_8c,2,0xc3520000);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x48) = uVar2;
  tColour::tColour((tColour *)&local_a8,extraout_s0_05,extraout_s1_05,extraout_s2_05,extraout_s3_05)
  ;
  cRBorder::Init(uVar2,0x14,&DAT_00092f10,0x14,0x41a00000,0x43af0000,local_a8,uStack_a4,uStack_a0,
                 uStack_9c,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x48),*(cRBorder **)(this + 0x3c));
  if ((*(float *)(Game + 0x3c) == 90.0) || (*(float *)(Game + 0x3c) == 270.0)) {
    iVar3 = *(int *)(this + 0x44);
    iVar1 = *(int *)(this + 0x3c);
    *(undefined4 *)(iVar3 + 0x230) = *(undefined4 *)(iVar1 + 0x230);
    *(undefined4 *)(iVar3 + 0x6f0) = *(undefined4 *)(iVar1 + 0x6f0);
  }
  else {
    iVar3 = *(int *)(this + 0x44);
    iVar1 = *(int *)(this + 0x48);
    *(undefined4 *)(iVar3 + 0x230) = *(undefined4 *)(iVar1 + 0x230);
    *(undefined4 *)(iVar3 + 0x6f0) = *(undefined4 *)(iVar1 + 0x6f0);
    *(float *)(iVar3 + 600) = *(float *)(iVar3 + 600) + 20.0;
  }
  if (gConfig[0xc0] == '\0') {
    iVar1 = *(int *)(this + 0x34);
    iVar3 = *(int *)(this + 0x38);
    iVar4 = *(int *)(this + 0x3c);
    *(uint *)(*(int *)(this + 0x30) + 0x194) = *(uint *)(*(int *)(this + 0x30) + 0x194) | 0x8000;
    *(uint *)(iVar1 + 0x194) = *(uint *)(iVar1 + 0x194) | 0x8000;
    *(uint *)(iVar3 + 0x194) = *(uint *)(iVar3 + 0x194) | 0x8000;
    *(uint *)(iVar4 + 0x194) = *(uint *)(iVar4 + 0x194) | 0x8000;
  }
  return;
}
