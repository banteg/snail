/*
 * mangled: _ZN10cRContinue4InitEv
 * demangled: cRContinue::Init()
 * address: 00061900
 * size: 732
 */

/* cRContinue::Init() */

void __thiscall cRContinue::Init(cRContinue *this)

{
  undefined4 uVar1;
  cRBorder *pcVar2;
  cRBorder *pcVar3;
  int iVar4;
  float fVar5;
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
  fVar5 = (float)cRStarManager::Hide((cRStarManager *)(Game + 0x4d440));
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar5);
  if (*(int *)(gOFOData + Game + 0x1ebc) == 0) {
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)this = uVar1;
    tColour::tColour((tColour *)&local_48,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    cRBorder::Init(uVar1,0x40000014,"Continue Adventure",0x14,0x41a00000,0x43060000,local_48,
                   uStack_44,uStack_40,uStack_3c,2,0);
    iVar4 = Game;
    *(undefined4 *)(*(int *)this + 0x264) = 0x428c0000;
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
    *(undefined4 *)(this + 4) = uVar1;
    tColour::tColour((tColour *)&local_58,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    iVar4 = -0x7b3c;
    local_78 = local_58;
    uStack_74 = uStack_54;
    uStack_70 = uStack_50;
    uStack_6c = uStack_4c;
  }
  else {
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)this = uVar1;
    tColour::tColour((tColour *)&local_68,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar1,0x40000014,"Continue Challenge",0x14,0x41a00000,0x43060000,local_68,
                   uStack_64,uStack_60,uStack_5c,2,0);
    iVar4 = Game;
    *(undefined4 *)(*(int *)this + 0x264) = 0x428c0000;
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
    *(undefined4 *)(this + 4) = uVar1;
    tColour::tColour((tColour *)&local_78,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    iVar4 = -0x7b14;
  }
  cRBorder::Init(uVar1,0x14,(int)&__DT_PLTGOT + iVar4,0x14,0x41a00000,0x41a00000,local_78,uStack_74,
                 uStack_70,uStack_6c,2,0);
  pcVar2 = *(cRBorder **)(this + 4);
  *(undefined4 *)(pcVar2 + 0x264) = 0x428c0000;
  cRBorder::SetBelow(pcVar2,*(cRBorder **)this);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 8) = uVar1;
  tColour::tColour((tColour *)&local_88,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar1,0x14,&DAT_00092f10,0x14,0x41a00000,0x43240000,local_88,uStack_84,uStack_80,
                 uStack_7c,2,0);
  pcVar2 = *(cRBorder **)(this + 8);
  pcVar3 = *(cRBorder **)(this + 4);
  *(undefined4 *)(pcVar2 + 0x264) = 0x428c0000;
  cRBorder::SetBelow(pcVar2,pcVar3);
  return;
}
