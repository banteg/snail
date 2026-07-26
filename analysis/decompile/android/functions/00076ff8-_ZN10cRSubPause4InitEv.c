/*
 * mangled: _ZN10cRSubPause4InitEv
 * demangled: cRSubPause::Init()
 * address: 00076ff8
 * size: 468
 */

/* cRSubPause::Init() */

void __thiscall cRSubPause::Init(cRSubPause *this)

{
  undefined4 uVar1;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
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

  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 4) = uVar1;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar1,0x14,"End Game",0x14,0,0x43110000,local_40,uStack_3c,uStack_38,uStack_34,2,0)
  ;
  cRBorder::SetKeyLeft(*(cRBorder **)(this + 4),0xb);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)this = uVar1;
  tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar1,0x14,"Options",0x14,0,0x433e0000,local_50,uStack_4c,uStack_48,uStack_44,2,0);
  cRBorder::SetKeyLeft(*(cRBorder **)this,0x6f);
  cRBorder::RePosition(*(cRBorder **)this);
  cRBorder::SetBelow(*(cRBorder **)this,*(cRBorder **)(this + 4));
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 8) = uVar1;
  tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar1,0x14,"Resume",0x14,0,0x43a00000,local_60,uStack_5c,uStack_58,uStack_54,2,0);
  cRBorder::SetKeyLeft(*(cRBorder **)(this + 8),5);
  cRBorder::SetBelow(*(cRBorder **)(this + 8),*(cRBorder **)this);
  cRMouse::SetActive((cRMouse *)(Game + 0x228));
  return;
}
