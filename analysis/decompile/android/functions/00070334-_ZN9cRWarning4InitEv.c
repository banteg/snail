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
  undefined4 uVar2;
  cRBorder *this_00;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;

  uVar1 = DAT_00070404;
  uVar2 = cRBorderManager::GetBorder
                    ((cRBorderManager *)(**(int **)(DAT_00070418 + 0x70344 + DAT_0007041c) + 0xd14))
  ;
  *(undefined4 *)(this + 0x14) = uVar2;
  tColour::tColour((tColour *)&local_28,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,0x400802,0x51,0x43900000,DAT_0007040c,local_28,uStack_24,uStack_20,uStack_1c,
                 uVar1,1);
  this_00 = *(cRBorder **)(this + 0x14);
  *(undefined4 *)(this_00 + 0x16c) = uVar1;
  cRBorder::HideInit(this_00);
  *(undefined4 *)(this + 8) = DAT_00070410;
  *(undefined4 *)(this + 0xc) = uVar1;
  uVar2 = DAT_00070414;
  *(undefined4 *)(this + 4) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar2;
  *(undefined4 *)this = 0;
  return;
}
