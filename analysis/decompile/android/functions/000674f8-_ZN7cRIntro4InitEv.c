/*
 * mangled: _ZN7cRIntro4InitEv
 * demangled: cRIntro::Init()
 * address: 000674f8
 * size: 1332
 */

/* cRIntro::Init() */

void __thiscall cRIntro::Init(cRIntro *this)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  float fVar11;
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

  iVar8 = DAT_00067918;
  iVar7 = DAT_00067914;
  uVar2 = DAT_00067908;
  uVar6 = DAT_00067904;
  fVar1 = DAT_00067900;
  iVar9 = DAT_00067910 + 0x67518;
  piVar10 = *(int **)(iVar9 + DAT_00067914);
  cRFade::FadeIn((cRFade *)(*piVar10 + 0x24));
  cRStarManager::Hide((cRStarManager *)(*piVar10 + 0x4d440));
  RShellMusicPlay((char *)(iVar9 + DAT_0006791c),0,(char *)(iVar9 + DAT_00067920));
  iVar3 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + *piVar10 + 0x3d8),
                     (char *)(iVar9 + DAT_00067924));
  fVar11 = (float)cRBackdrop::Change((cRBackdrop *)(*piVar10 + 0x4d2e0),
                                     (cRLandscape *)
                                     (gSegmentText + iVar3 * 0x1ac + *piVar10 + 0x3dc),false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar10 + 0xd14),fVar11);
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar10 + 0xd14));
  *(undefined4 *)(this + 0x40) = uVar4;
  tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar4,0x40000014,iVar9 + DAT_00067928,0x14,fVar1,DAT_00067944,local_48,uStack_44,
                 uStack_40,uStack_3c,2,uVar6);
  uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar10 + 0xd14));
  *(undefined4 *)(this + 0x30) = uVar5;
  tColour::tColour((tColour *)&local_58,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  uVar4 = DAT_00067904;
  fVar11 = DAT_00067900;
  cRBorder::Init(uVar5,0x40000014,iVar9 + DAT_0006792c,0x14,fVar1,fVar1,local_58,uStack_54,uStack_50
                 ,uStack_4c,2,uVar6);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x30),*(cRBorder **)(this + 0x40));
  if (0 < *(int *)(*(int *)(iVar9 + iVar8) + 0xd0)) {
    *(uint *)(*(int *)(this + 0x30) + 0x194) = *(uint *)(*(int *)(this + 0x30) + 0x194) & 0xbfffffff
    ;
  }
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(**(int **)(iVar9 + iVar7) + 0xd14));
  *(undefined4 *)(this + 0x34) = uVar6;
  tColour::tColour((tColour *)&local_68,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar6,0x40000014,iVar9 + DAT_00067930,0x14,DAT_00067900,DAT_00067900,local_68,
                 uStack_64,uStack_60,uStack_5c,2,DAT_00067904);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x34),*(cRBorder **)(this + 0x30));
  piVar10 = *(int **)(iVar9 + iVar7);
  iVar7 = *piVar10;
  if (0 < *(int *)(*(int *)(iVar9 + iVar8) + 0xe0)) {
    *(uint *)(*(int *)(this + 0x34) + 0x194) = *(uint *)(*(int *)(this + 0x34) + 0x194) & 0xbfffffff
    ;
  }
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(iVar7 + 0xd14));
  *(undefined4 *)(this + 0x38) = uVar6;
  tColour::tColour((tColour *)&local_78,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar6,0x40000014,iVar9 + DAT_00067934,0x14,fVar11,fVar11,local_78,uStack_74,
                 uStack_70,uStack_6c,2,uVar4);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x38),*(cRBorder **)(this + 0x34));
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar10 + 0xd14));
  *(undefined4 *)(this + 0x3c) = uVar6;
  tColour::tColour((tColour *)&local_88,extraout_s0_03,extraout_s1_03,extraout_s2_03,extraout_s3_03)
  ;
  cRBorder::Init(uVar6,0x14,iVar9 + DAT_00067938,0x14,fVar11,fVar11,local_88,uStack_84,uStack_80,
                 uStack_7c,2,uVar4);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x3c),*(cRBorder **)(this + 0x38));
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar10 + 0xd14));
  *(undefined4 *)(this + 0x44) = uVar6;
  tColour::tColour((tColour *)&local_98,extraout_s0_04,extraout_s1_04,extraout_s2_04,extraout_s3_04)
  ;
  cRBorder::Init(uVar6,0x40000014,iVar9 + DAT_0006793c,0x14,uVar4,uVar2,local_98,uStack_94,uStack_90
                 ,uStack_8c,2,DAT_0006790c);
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar10 + 0xd14));
  *(undefined4 *)(this + 0x48) = uVar6;
  tColour::tColour((tColour *)&local_a8,extraout_s0_05,extraout_s1_05,extraout_s2_05,extraout_s3_05)
  ;
  cRBorder::Init(uVar6,0x14,iVar9 + DAT_00067940,0x14,fVar11,uVar2,local_a8,uStack_a4,uStack_a0,
                 uStack_9c,2,uVar4);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x48),*(cRBorder **)(this + 0x3c));
  if ((*(float *)(*piVar10 + 0x3c) == DAT_00067944) || (*(float *)(*piVar10 + 0x3c) == DAT_00067948)
     ) {
    iVar3 = *(int *)(this + 0x44);
    iVar7 = *(int *)(this + 0x3c);
    *(undefined4 *)(iVar3 + 0x230) = *(undefined4 *)(iVar7 + 0x230);
    *(undefined4 *)(iVar3 + 0x6f0) = *(undefined4 *)(iVar7 + 0x6f0);
  }
  else {
    iVar3 = *(int *)(this + 0x44);
    iVar7 = *(int *)(this + 0x48);
    *(undefined4 *)(iVar3 + 0x230) = *(undefined4 *)(iVar7 + 0x230);
    *(undefined4 *)(iVar3 + 0x6f0) = *(undefined4 *)(iVar7 + 0x6f0);
    *(float *)(iVar3 + 600) = *(float *)(iVar3 + 600) + fVar11;
  }
  if (*(char *)(*(int *)(iVar9 + iVar8) + 0xc0) == '\0') {
    iVar7 = *(int *)(this + 0x34);
    iVar8 = *(int *)(this + 0x38);
    iVar3 = *(int *)(this + 0x3c);
    *(uint *)(*(int *)(this + 0x30) + 0x194) = *(uint *)(*(int *)(this + 0x30) + 0x194) | 0x8000;
    *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) | 0x8000;
    *(uint *)(iVar8 + 0x194) = *(uint *)(iVar8 + 0x194) | 0x8000;
    *(uint *)(iVar3 + 0x194) = *(uint *)(iVar3 + 0x194) | 0x8000;
  }
  return;
}
