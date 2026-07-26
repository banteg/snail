/*
 * mangled: _ZN9cRWarning4InitEv
 * demangled: cRWarning::Init()
 * address: 00070334
 * size: 208
 */

/* cRWarning::Init() */

void __thiscall cRWarning::Init(cRWarning *this)

{
  undefined4 uVar1;
  cRBorder *this_00;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;

  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x14) = uVar1;
  tColour::tColour((tColour *)&local_28,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar1,0x400802,0x51,0x43900000,0x42800000,local_28,uStack_24,uStack_20,uStack_1c,0,
                 1);
  this_00 = *(cRBorder **)(this + 0x14);
  *(undefined4 *)(this_00 + 0x16c) = 0;
  cRBorder::HideInit(this_00);
  *(undefined4 *)(this + 8) = 0x3daaaaab;
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 0x10) = 0x3c638e39;
  *(undefined4 *)this = 0;
  return;
}
