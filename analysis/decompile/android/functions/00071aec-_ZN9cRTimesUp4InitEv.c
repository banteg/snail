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
  undefined4 uVar2;
  int iVar3;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  uVar1 = DAT_00071bb4;
  iVar3 = DAT_00071bc4 + 0x71b0c;
  if (*(int *)this == 0) {
    uVar2 = cRBorderManager::GetBorder
                      ((cRBorderManager *)(**(int **)(iVar3 + DAT_00071bc8) + 0xd14));
    *(undefined4 *)(this + 4) = uVar2;
    tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar2,0x400002,iVar3 + DAT_00071bcc,0x14,uVar1,DAT_00071bbc,local_30,uStack_2c,
                   uStack_28,uStack_24,2,uVar1);
    uVar2 = DAT_00071bc0;
    *(undefined4 *)(this + 8) = uVar1;
    *(undefined4 *)(this + 0xc) = uVar2;
    *(undefined4 *)this = 1;
  }
  return;
}
