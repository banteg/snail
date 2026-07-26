/*
 * mangled: _ZN10cRSubPause4InitEv
 * demangled: cRSubPause::Init()
 * address: 00019a2c
 * size: 468
 */

/* cRSubPause::Init() */

void __thiscall cRSubPause::Init(cRSubPause *this)

{
  undefined4 uVar1;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 4) = uVar1;
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x14,"End Game",0x14,0,0x43110000,local_30,uStack_2c,uStack_28,uStack_24,2,0)
  ;
  cRBorder::SetKeyLeft(*(cRBorder **)(this + 4),0xb);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)this = uVar1;
  tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,0.03);
  cRBorder::Init(uVar1,0x14,"Options",0x14,0,0x433e0000,local_40,uStack_3c,uStack_38,uStack_34,2,0);
  cRBorder::SetKeyLeft(*(cRBorder **)this,0x6f);
  cRBorder::RePosition(*(cRBorder **)this);
  cRBorder::SetBelow(*(cRBorder **)this,*(cRBorder **)(this + 4));
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 8) = uVar1;
  tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x14,"Resume",0x14,0,0x43a00000,local_50,uStack_4c,uStack_48,uStack_44,2,0);
  cRBorder::SetKeyLeft(*(cRBorder **)(this + 8),5);
  cRBorder::SetBelow(*(cRBorder **)(this + 8),*(cRBorder **)this);
  cRMouse::SetActive((cRMouse *)(*(int *)PTR__Game_001b60b8 + 0x228));
  return;
}
