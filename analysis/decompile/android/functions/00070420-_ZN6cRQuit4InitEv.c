/*
 * mangled: _ZN6cRQuit4InitEv
 * demangled: cRQuit::Init()
 * address: 00070420
 * size: 192
 */

/* cRQuit::Init() */

void __thiscall cRQuit::Init(cRQuit *this)

{
  undefined4 uVar1;
  cRBorder *this_00;
  float extraout_s0;
  float fVar2;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  *(undefined4 *)this = 1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 4) = uVar1;
  tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  fVar2 = (float)cRBorder::Init(uVar1,0x2040081c,0x52,0x41000000,0x41400000,local_30,uStack_2c,
                                uStack_28,uStack_24,0,1);
  cRBorder::Scale(*(cRBorder **)(this + 4),fVar2);
  this_00 = *(cRBorder **)(this + 4);
  *(undefined4 *)(this_00 + 0x16c) = 0;
  cRBorder::HideInit(this_00);
  return;
}
