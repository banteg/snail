/*
 * mangled: _ZN10cRContinue4InitEv
 * demangled: cRContinue::Init()
 * address: 00061900
 * size: 732
 */

/* cRContinue::Init() */

void __thiscall cRContinue::Init(cRContinue *this)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  cRBorder *pcVar4;
  undefined4 uVar5;
  cRBorder *pcVar6;
  int iVar7;
  int *piVar8;
  float fVar9;
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
  undefined4 uVar10;
  undefined4 uVar11;
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

  iVar1 = DAT_00061bf4;
  iVar7 = DAT_00061bf0 + 0x6191c;
  piVar8 = *(int **)(iVar7 + DAT_00061bf4);
  cRFade::FadeIn((cRFade *)(*piVar8 + 0x24));
  fVar9 = (float)cRStarManager::Hide((cRStarManager *)(*piVar8 + 0x4d440));
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar8 + 0xd14),fVar9);
  iVar2 = *piVar8;
  if (*(int *)(gOFOData + iVar2 + 0x1ebc) == 0) {
    uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
    uVar10 = DAT_00061be4;
    uVar11 = DAT_00061be0;
    uVar5 = DAT_00061bdc;
    *(undefined4 *)this = uVar3;
    tColour::tColour((tColour *)&local_48,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    cRBorder::Init(uVar3,0x40000014,iVar7 + DAT_00061c04,0x14,uVar5,DAT_00061be8,local_48,uStack_44,
                   uStack_40,uStack_3c,2,uVar11);
    iVar2 = *piVar8;
    *(undefined4 *)(*(int *)this + 0x264) = uVar10;
    uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
    *(undefined4 *)(this + 4) = uVar3;
    tColour::tColour((tColour *)&local_58,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    iVar2 = DAT_00061c08;
    local_78 = local_58;
    uStack_74 = uStack_54;
    uStack_70 = uStack_50;
    uStack_6c = uStack_4c;
  }
  else {
    uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
    uVar10 = DAT_00061be4;
    uVar11 = DAT_00061be0;
    uVar5 = DAT_00061bdc;
    *(undefined4 *)this = uVar3;
    tColour::tColour((tColour *)&local_68,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar3,0x40000014,iVar7 + DAT_00061bf8,0x14,uVar5,DAT_00061be8,local_68,uStack_64,
                   uStack_60,uStack_5c,2,uVar11);
    iVar2 = *piVar8;
    *(undefined4 *)(*(int *)this + 0x264) = uVar10;
    uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
    *(undefined4 *)(this + 4) = uVar3;
    tColour::tColour((tColour *)&local_78,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    iVar2 = DAT_00061bfc;
  }
  cRBorder::Init(uVar3,0x14,iVar7 + iVar2,0x14,uVar5,uVar5,local_78,uStack_74,uStack_70,uStack_6c,2,
                 uVar11);
  pcVar4 = *(cRBorder **)(this + 4);
  *(undefined4 *)(pcVar4 + 0x264) = uVar10;
  cRBorder::SetBelow(pcVar4,*(cRBorder **)this);
  uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(**(int **)(iVar7 + iVar1) + 0xd14));
  *(undefined4 *)(this + 8) = uVar5;
  tColour::tColour((tColour *)&local_88,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar5,0x14,iVar7 + DAT_00061c00,0x14,DAT_00061bdc,DAT_00061bec,local_88,uStack_84,
                 uStack_80,uStack_7c,2,DAT_00061be0);
  pcVar4 = *(cRBorder **)(this + 8);
  pcVar6 = *(cRBorder **)(this + 4);
  *(undefined4 *)(pcVar4 + 0x264) = DAT_00061be4;
  cRBorder::SetBelow(pcVar4,pcVar6);
  return;
}
