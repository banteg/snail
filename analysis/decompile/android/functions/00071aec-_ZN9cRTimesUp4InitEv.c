/*
 * mangled: _ZN9cRTimesUp4InitEv
 * demangled: cRTimesUp::Init()
 * address: 00071aec
 * size: 200
 */

/* cRTimesUp::Init() */

void __thiscall cRTimesUp::Init(cRTimesUp *this)

{
  undefined4 uVar1;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  if (*(int *)this == 0) {
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 4) = uVar1;
    tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar1,0x400002,"Time\'s Up",0x14,0,0x43480000,local_30,uStack_2c,uStack_28,
                   uStack_24,2,0);
    *(undefined4 *)(this + 8) = 0;
    *(undefined4 *)(this + 0xc) = 0x3bb60b61;
    *(undefined4 *)this = 1;
  }
  return;
}
