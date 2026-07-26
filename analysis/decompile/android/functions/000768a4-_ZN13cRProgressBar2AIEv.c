/*
 * mangled: _ZN13cRProgressBar2AIEv
 * demangled: cRProgressBar::AI()
 * address: 000768a4
 * size: 716
 */

/* cRProgressBar::AI() */

void cRProgressBar::AI(void)

{
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float in_s1;
  float extraout_s1;
  float extraout_s1_00;
  float in_s2;
  float extraout_s2;
  float extraout_s2_00;
  float in_s3;
  float extraout_s3;
  float extraout_s3_00;
  float fVar1;
  float fVar2;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;

  fVar1 = (float)VectorSignedToFloat(*(undefined4 *)(Game + 0x71918),(byte)(in_fpscr >> 0x16) & 3);
  fVar2 = (float)VectorSignedToFloat(*(undefined4 *)(Game + 0x71910),(byte)(in_fpscr >> 0x16) & 3);
  fVar1 = (*(float *)(Game + 0x813c8) - fVar2) / (fVar1 - fVar2);
  if (fVar1 < 0.0) {
    fVar1 = 0.0;
  }
  else if (1.0 < fVar1) {
    fVar1 = 1.0;
  }
  fVar1 = (1.0 - fVar1) * 232.0 + 12.0;
  tColour::tColour((tColour *)&local_58,in_s0,in_s1,in_s2,in_s3);
  OSDPrintUV(0x88,0x41400000,(fVar1 + 150.0) - 39.0,0x42800000,0x42800000,0x1000000,local_58,
             uStack_54,uStack_50,uStack_4c,gSpriteReference._4368_4_,
             1.0 - (float)gSpriteReference._4380_4_,gSpriteReference._4376_4_,
             1.0 - (float)gSpriteReference._4372_4_,1,0);
  tColour::tColour((tColour *)&local_68,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  fVar2 = fVar1 * -0.00390625 + 1.0;
  OSDPrintUV(0x86,0x41500000,0x43160000,0x42800000,fVar1,0x1000000,local_68,uStack_64,uStack_60,
             uStack_5c,gSpriteReference._4304_4_,1.0 - (float)gSpriteReference._4316_4_,
             gSpriteReference._4312_4_,
             (1.0 - (float)gSpriteReference._4316_4_) * fVar2 +
             (1.0 - (float)gSpriteReference._4308_4_) * fVar1 * 0.00390625,1,0);
  tColour::tColour((tColour *)&local_78,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  OSDPrintUV(0x87,0x41500000,fVar1 + 150.0,0x42800000,256.0 - fVar1,0x1000000,local_78,uStack_74,
             uStack_70,uStack_6c,gSpriteReference._4336_4_,
             fVar2 * (1.0 - (float)gSpriteReference._4348_4_) +
             (1.0 - (float)gSpriteReference._4340_4_) * fVar1 * 0.00390625,gSpriteReference._4344_4_
             ,1.0 - (float)gSpriteReference._4340_4_,1,0);
  return;
}
