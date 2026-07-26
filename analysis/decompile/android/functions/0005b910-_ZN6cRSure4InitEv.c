/*
 * mangled: _ZN6cRSure4InitEv
 * demangled: cRSure::Init()
 * address: 0005b910
 * size: 660
 */

/* cRSure::Init() */

void __thiscall cRSure::Init(cRSure *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  cRBorder *pcVar6;
  int iVar7;
  int *piVar8;
  float fVar9;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
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

  iVar2 = DAT_0005bbb8;
  iVar7 = DAT_0005bbb4 + 0x5b92c;
  piVar8 = *(int **)(iVar7 + DAT_0005bbb8);
  cRFade::FadeIn((cRFade *)(*piVar8 + 0x24));
  fVar9 = (float)cRStarManager::Hide((cRStarManager *)(*piVar8 + 0x4d440));
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar8 + 0xd14),fVar9);
  iVar3 = *piVar8;
  if (*(int *)(gOFOData + iVar3 + 0x1ebc) == 0) {
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar3 + 0xd14));
    *(undefined4 *)this = uVar4;
    tColour::tColour((tColour *)&local_40,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    iVar3 = DAT_0005bbc8;
    local_50 = local_40;
    uStack_4c = uStack_3c;
    uStack_48 = uStack_38;
    uStack_44 = uStack_34;
  }
  else {
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar3 + 0xd14));
    *(undefined4 *)this = uVar4;
    tColour::tColour((tColour *)&local_50,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar3 = DAT_0005bbbc;
  }
  cRBorder::Init(uVar4,0,iVar7 + iVar3,0x14,0x41a00000,DAT_0005bba4,local_50,uStack_4c,uStack_48,
                 uStack_44,2,DAT_0005bba8);
  piVar8 = *(int **)(iVar7 + iVar2);
  *(undefined4 *)(*(int *)this + 0x264) = DAT_0005bbac;
  uVar4 = DAT_0005bba8;
  uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar8 + 0xd14));
  uVar1 = DAT_0005bbac;
  *(undefined4 *)(this + 4) = uVar5;
  tColour::tColour((tColour *)&local_60,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar5,0x40000014,iVar7 + DAT_0005bbc0,0x14,0x41a00000,0x41a00000,local_60,uStack_5c
                 ,uStack_58,uStack_54,2,uVar4);
  pcVar6 = *(cRBorder **)(this + 4);
  *(undefined4 *)(pcVar6 + 0x264) = uVar1;
  cRBorder::SetBelow(pcVar6,*(cRBorder **)this);
  uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar8 + 0xd14));
  *(undefined4 *)(this + 8) = uVar5;
  tColour::tColour((tColour *)&local_70,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar5,0x14,iVar7 + DAT_0005bbc4,0x14,0x41a00000,DAT_0005bbb0,local_70,uStack_6c,
                 uStack_68,uStack_64,2,uVar4);
  pcVar6 = *(cRBorder **)(this + 8);
  *(undefined4 *)(pcVar6 + 0x264) = uVar1;
  fVar9 = (float)cRBorder::SetRight(pcVar6,*(cRBorder **)(this + 4));
  cRBorderManager::CentreRow
            ((cRBorderManager *)(*piVar8 + 0xd14),*(cRBorder **)(this + 8),false,fVar9);
  return;
}
