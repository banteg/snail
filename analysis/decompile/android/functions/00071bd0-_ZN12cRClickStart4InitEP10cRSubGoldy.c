/*
 * mangled: _ZN12cRClickStart4InitEP10cRSubGoldy
 * demangled: cRClickStart::Init(cRSubGoldy*)
 * address: 00071bd0
 * size: 276
 */

/* cRClickStart::Init(cRSubGoldy*) */

void __thiscall cRClickStart::Init(cRClickStart *this,cRSubGoldy *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x78) = uVar3;
  tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar3,0x400002,"Touch Screen to Start",0x14,0,0x43480000,local_38,uStack_34,
                 uStack_30,uStack_2c,2,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x78));
  iVar2 = Game;
  this[0x9c] = (cRClickStart)0x1;
  *(cRSubGoldy **)(this + 0x8c) = param_1;
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(iVar2 + 0x358),(cRBod *)this);
  iVar2 = Game;
  *(undefined4 *)(this + 0x74) = 2;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  cVar1 = gDirectory[iVar2 + 0x2544];
  *(undefined4 *)(*(int *)(this + 0x8c) + 0x2ec) = 0;
  if (cVar1 == '\0') {
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x78));
  }
  else {
    cRBorder::HideInit(*(cRBorder **)(this + 0x78));
  }
  return;
}
