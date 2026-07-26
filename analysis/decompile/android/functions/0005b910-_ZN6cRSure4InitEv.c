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
  cRBorder *pcVar2;
  int iVar3;
  float fVar4;
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

  cRFade::FadeIn((cRFade *)(Game + 0x24));
  fVar4 = (float)cRStarManager::Hide((cRStarManager *)(Game + 0x4d440));
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar4);
  if (*(int *)(gOFOData + Game + 0x1ebc) == 0) {
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)this = uVar1;
    tColour::tColour((tColour *)&local_40,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    iVar3 = -0x7dd0;
    local_50 = local_40;
    uStack_4c = uStack_3c;
    uStack_48 = uStack_38;
    uStack_44 = uStack_34;
  }
  else {
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)this = uVar1;
    tColour::tColour((tColour *)&local_50,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar3 = -0x7d7c;
  }
  cRBorder::Init(uVar1,0,(int)&__DT_PLTGOT + iVar3,0x14,0x41a00000,0x42e40000,local_50,uStack_4c,
                 uStack_48,uStack_44,2,0);
  *(undefined4 *)(*(int *)this + 0x264) = 0x42700000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 4) = uVar1;
  tColour::tColour((tColour *)&local_60,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar1,0x40000014,&DAT_000931e8,0x14,0x41a00000,0x41a00000,local_60,uStack_5c,
                 uStack_58,uStack_54,2,0);
  pcVar2 = *(cRBorder **)(this + 4);
  *(undefined4 *)(pcVar2 + 0x264) = 0x42700000;
  cRBorder::SetBelow(pcVar2,*(cRBorder **)this);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 8) = uVar1;
  tColour::tColour((tColour *)&local_70,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar1,0x14,&DAT_000931ec,0x14,0x41a00000,0x43240000,local_70,uStack_6c,uStack_68,
                 uStack_64,2,0);
  pcVar2 = *(cRBorder **)(this + 8);
  *(undefined4 *)(pcVar2 + 0x264) = 0x42700000;
  fVar4 = (float)cRBorder::SetRight(pcVar2,*(cRBorder **)(this + 4));
  cRBorderManager::CentreRow((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 8),false,fVar4)
  ;
  return;
}
