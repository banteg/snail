/*
 * mangled: _ZN7cRFlash5FlashER7tColour
 * demangled: cRFlash::Flash(tColour&)
 * address: 00042238
 * size: 60
 */

/* cRFlash::Flash(tColour&) */

void cRFlash::Flash(tColour *param_1)

{
  undefined4 *in_r1;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float in_s0;
  float in_s1;
  float in_s2;
  float in_s3;

  uVar1 = in_r1[1];
  uVar2 = in_r1[2];
  uVar3 = in_r1[3];
  *(undefined4 *)(param_1 + 0x14) = *in_r1;
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  *(undefined4 *)(param_1 + 0x1c) = uVar2;
  *(undefined4 *)(param_1 + 0x20) = uVar3;
  tColour::Set(param_1 + 4,in_s0,in_s1,in_s2,in_s3);
  return;
}
