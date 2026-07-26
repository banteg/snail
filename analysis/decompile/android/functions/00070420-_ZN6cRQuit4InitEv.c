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
  undefined4 uVar2;
  cRBorder *this_00;
  int *piVar3;
  float extraout_s0;
  float fVar4;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  uVar1 = DAT_000704e0;
  piVar3 = *(int **)(DAT_000704ec + 0x70430 + DAT_000704f0);
  *(undefined4 *)this = 1;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar3 + 0xd14));
  *(undefined4 *)(this + 4) = uVar2;
  tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  fVar4 = (float)cRBorder::Init(uVar2,0x2040081c,0x52,0x41000000,DAT_000704e8,local_30,uStack_2c,
                                uStack_28,uStack_24,uVar1,1);
  cRBorder::Scale(*(cRBorder **)(this + 4),fVar4);
  this_00 = *(cRBorder **)(this + 4);
  *(undefined4 *)(this_00 + 0x16c) = uVar1;
  cRBorder::HideInit(this_00);
  return;
}
