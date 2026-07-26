/*
 * mangled: _ZN10cRMainMenu4InitEv
 * demangled: cRMainMenu::Init()
 * address: 000697d4
 * size: 972
 */

/* cRMainMenu::Init() */

void cRMainMenu::Init(void)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 *in_r0;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 in_r1;
  int iVar5;
  int *piVar6;
  int iVar7;
  float fVar8;
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

  uVar2 = DAT_00069ba4;
  uVar4 = DAT_00069ba0;
  iVar7 = DAT_00069bb8 + 0x697f4;
  piVar6 = *(int **)(iVar7 + DAT_00069bbc);
  iVar5 = *piVar6;
  wprintf((char *)(iVar7 + DAT_00069bc0),in_r1,SUB84((double)*(float *)(iVar5 + 0x3c),0),
          (int)((ulonglong)(double)*(float *)(iVar5 + 0x3c) >> 0x20),
          (double)*(float *)(iVar5 + 0x40),(double)*(float *)(iVar5 + 0x44));
  cRFade::FadeIn((cRFade *)(*piVar6 + 0x24));
  cRStarManager::Hide((cRStarManager *)(*piVar6 + 0x4d440));
  RShellMusicPlay((char *)(iVar7 + DAT_00069bc4),0,(char *)(iVar7 + DAT_00069bc8));
  iVar5 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + *piVar6 + 0x3d8),
                     (char *)(iVar7 + DAT_00069bcc));
  fVar8 = (float)cRBackdrop::Change((cRBackdrop *)(*piVar6 + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + iVar5 * 0x1ac + *piVar6 + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar6 + 0xd14),fVar8);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar6 + 0xd14));
  *in_r0 = uVar3;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar3,0x14,iVar7 + DAT_00069bd0,0x14,uVar4,DAT_00069ba8,local_40,uStack_3c,
                 uStack_38,uStack_34,2,uVar2);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar6 + 0xd14));
  in_r0[1] = uVar3;
  tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar3,0x14,iVar7 + DAT_00069bd4,0x14,uVar4,uVar4,local_50,uStack_4c,uStack_48,
                 uStack_44,2,uVar2);
  cRBorder::SetBelow((cRBorder *)in_r0[1],(cRBorder *)*in_r0);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar6 + 0xd14));
  in_r0[2] = uVar3;
  tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar3,0x14,iVar7 + DAT_00069bd8,0x14,uVar4,uVar4,local_60,uStack_5c,uStack_58,
                 uStack_54,2,uVar2);
  cRBorder::SetBelow((cRBorder *)in_r0[2],(cRBorder *)in_r0[1]);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar6 + 0xd14));
  in_r0[3] = uVar3;
  tColour::tColour((tColour *)&local_70,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar3,0x40000014,iVar7 + DAT_00069bdc,0x14,uVar4,uVar4,local_70,uStack_6c,uStack_68
                 ,uStack_64,2,uVar2);
  cRBorder::SetBelow((cRBorder *)in_r0[3],(cRBorder *)in_r0[2]);
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar6 + 0xd14));
  fVar8 = *(float *)(*piVar6 + 0x40);
  bVar1 = fVar8 == DAT_00069bac;
  in_r0[4] = uVar4;
  if ((bVar1) || (fVar8 == DAT_00069bb0)) {
    tColour::tColour((tColour *)&local_80,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar4,0x20400812,0x8c,0x44100000,DAT_00069bb4,local_80,uStack_7c,uStack_78,
                   uStack_74,DAT_00069ba4,1);
  }
  else {
    tColour::tColour((tColour *)&local_90,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar4,0x20400812,0x8d,0x44000000,DAT_00069bb4,local_90,uStack_8c,uStack_88,
                   uStack_84,uVar2,1);
  }
  return;
}
