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
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
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

  uVar1 = DAT_000771cc;
  iVar3 = DAT_000771e0 + 0x77018;
  piVar4 = *(int **)(iVar3 + DAT_000771e4);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
  *(undefined4 *)(this + 4) = uVar2;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,0x14,iVar3 + DAT_000771e8,0x14,uVar1,DAT_000771d0,local_40,uStack_3c,
                 uStack_38,uStack_34,2,uVar1);
  cRBorder::SetKeyLeft(*(cRBorder **)(this + 4),0xb);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
  *(undefined4 *)this = uVar2;
  tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar2,0x14,iVar3 + DAT_000771ec,0x14,uVar1,DAT_000771d8,local_50,uStack_4c,
                 uStack_48,uStack_44,2,uVar1);
  cRBorder::SetKeyLeft(*(cRBorder **)this,0x6f);
  cRBorder::RePosition(*(cRBorder **)this);
  cRBorder::SetBelow(*(cRBorder **)this,*(cRBorder **)(this + 4));
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
  *(undefined4 *)(this + 8) = uVar2;
  tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar2,0x14,iVar3 + DAT_000771f0,0x14,uVar1,DAT_000771dc,local_60,uStack_5c,
                 uStack_58,uStack_54,2,uVar1);
  cRBorder::SetKeyLeft(*(cRBorder **)(this + 8),5);
  cRBorder::SetBelow(*(cRBorder **)(this + 8),*(cRBorder **)this);
  cRMouse::SetActive((cRMouse *)(*piVar4 + 0x228));
  return;
}
