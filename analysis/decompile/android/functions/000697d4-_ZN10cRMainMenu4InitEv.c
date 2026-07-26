/*
 * mangled: _ZN10cRMainMenu4InitEv
 * demangled: cRMainMenu::Init()
 * address: 000697d4
 * size: 972
 */

/* cRMainMenu::Init() */

void cRMainMenu::Init(void)

{
  undefined4 *in_r0;
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r1;
  float fVar3;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
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

  wprintf("Main Menu Init Angle=%i AngleNext=%i AngleLast=%i",in_r1,
          SUB84((double)*(float *)(Game + 0x3c),0),
          (int)((ulonglong)(double)*(float *)(Game + 0x3c) >> 0x20),(double)*(float *)(Game + 0x40),
          (double)*(float *)(Game + 0x44));
  cRFade::FadeIn((cRFade *)(Game + 0x24));
  cRStarManager::Hide((cRStarManager *)(Game + 0x4d440));
  RShellMusicPlay("mainmenu",0,"");
  iVar1 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"Menubg.txt");
  fVar3 = (float)cRBackdrop::Change((cRBackdrop *)(Game + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + iVar1 * 0x1ac + Game + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar3);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *in_r0 = uVar2;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,0x14,&DAT_00092f24,0x14,0x41a00000,0x42f00000,local_40,uStack_3c,uStack_38,
                 uStack_34,2,0);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  in_r0[1] = uVar2;
  tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar2,0x14,"High Scores",0x14,0x41a00000,0x41a00000,local_50,uStack_4c,uStack_48,
                 uStack_44,2,0);
  cRBorder::SetBelow((cRBorder *)in_r0[1],(cRBorder *)*in_r0);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  in_r0[2] = uVar2;
  tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar2,0x14,"Options",0x14,0x41a00000,0x41a00000,local_60,uStack_5c,uStack_58,
                 uStack_54,2,0);
  cRBorder::SetBelow((cRBorder *)in_r0[2],(cRBorder *)in_r0[1]);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  in_r0[3] = uVar2;
  tColour::tColour((tColour *)&local_70,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar2,0x40000014,"Credits",0x14,0x41a00000,0x41a00000,local_70,uStack_6c,uStack_68,
                 uStack_64,2,0);
  cRBorder::SetBelow((cRBorder *)in_r0[3],(cRBorder *)in_r0[2]);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  fVar3 = *(float *)(Game + 0x40);
  in_r0[4] = uVar2;
  if ((fVar3 == 90.0) || (fVar3 == 270.0)) {
    tColour::tColour((tColour *)&local_80,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar2,0x20400812,0x8c,0x44100000,0x43d00000,local_80,uStack_7c,uStack_78,
                   uStack_74,0,1);
  }
  else {
    tColour::tColour((tColour *)&local_90,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar2,0x20400812,0x8d,0x44000000,0x43d00000,local_90,uStack_8c,uStack_88,
                   uStack_84,0,1);
  }
  return;
}
