/*
 * mangled: _ZN7cRFlash4InitEi
 * demangled: cRFlash::Init(int)
 * address: 000422c0
 * size: 84
 */

/* cRFlash::Init(int) */

void cRFlash::Init(int param_1)

{
  undefined4 in_r1;
  float in_s0;
  float extraout_s0;
  float in_s1;
  float extraout_s1;
  float in_s2;
  float extraout_s2;
  float in_s3;
  float extraout_s3;

  *(undefined4 *)param_1 = in_r1;
  tColour::Set((tColour *)(param_1 + 4),in_s0,in_s1,in_s2,in_s3);
  tColour::Set((tColour *)(param_1 + 0x14),extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  return;
}
