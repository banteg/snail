/*
 * mangled: _ZN13cRDamageGuage2AIEv
 * demangled: cRDamageGuage::AI()
 * address: 000761ec
 * size: 1624
 */

/* cRDamageGuage::AI() */

void cRDamageGuage::AI(void)

{
  int iVar1;
  int *in_r0;
  int iVar2;
  byte bVar3;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float extraout_s0_06;
  float in_s1;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  float extraout_s1_06;
  float in_s2;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float extraout_s2_05;
  float extraout_s2_06;
  float in_s3;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float extraout_s3_05;
  float extraout_s3_06;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;

  iVar1 = Game;
  if (*(char *)(Game + 0x718b9) == '\x01') {
    iVar2 = *in_r0;
    fVar5 = (float)in_r0[8];
    bVar3 = 0;
    goto LAB_0007622c;
  }
  fVar5 = (float)in_r0[8] + ((float)in_r0[7] - (float)in_r0[8]) * 0.2;
  in_r0[8] = (int)fVar5;
  if (0.0 < (float)in_r0[9]) {
    fVar6 = (float)in_r0[9] + (float)in_r0[10];
    in_r0[9] = (int)fVar6;
    if (1.0 < fVar6) {
      in_r0[9] = 0;
    }
  }
  iVar2 = *in_r0;
  if (iVar2 == 1) {
    if (*(char *)(iVar1 + 0x8179c) == '\0') {
      fVar6 = (float)in_r0[4];
    }
    else {
      fVar6 = 1.0;
      in_r0[4] = 0x3f800000;
    }
    in_r0[4] = (int)(fVar6 + (float)in_r0[5]);
    if ((fVar6 + (float)in_r0[5] < 1.0) || (*(float *)(iVar1 + 0x813c4) != 0.49)) {
LAB_0007670c:
      bVar3 = *(byte *)(iVar1 + 0x718b9) ^ 1;
      goto LAB_0007622c;
    }
    *in_r0 = 2;
    cRVoiceManager::Play((int)&gVoiceManager,0xe,0);
    in_s0 = extraout_s0_05;
    in_s1 = extraout_s1_05;
    in_s2 = extraout_s2_05;
    in_s3 = extraout_s3_05;
  }
  else {
    if (iVar2 == 2) {
      fVar5 = (float)cRSnailSkin::Change((cRSnailSkin *)(iVar1 + 0x852d4),1,in_s0);
      Take(fVar5,SUB41(in_r0,0));
      in_r0[6] = 5;
      in_s0 = extraout_s0_03;
      in_s1 = extraout_s1_03;
      in_s2 = extraout_s2_03;
      in_s3 = extraout_s3_03;
      if (*(char *)(Game + 0x8179c) != '\0') {
        Take(extraout_s0_03,SUB41(in_r0,0));
        in_s0 = extraout_s0_06;
        in_s1 = extraout_s1_06;
        in_s2 = extraout_s2_06;
        in_s3 = extraout_s3_06;
      }
      iVar1 = Game;
      if (((((float)in_r0[7] == 0.0) && (*(float *)(Game + 0x813c4) == 0.49)) ||
          (0.0 < *(float *)(Game + 0x817a0))) ||
         ((0.0 < *(float *)(Game + 0x813e4) || (*(int *)(Game + 0x85300) != 0)))) {
        *in_r0 = 0;
        cRWarning::Stop((cRWarning *)(cRSubGame::GenerateLevel + iVar1 + 4));
        cRWarning::StopSample();
        iVar2 = *in_r0;
        fVar5 = (float)in_r0[8];
        bVar3 = *(byte *)(Game + 0x718b9) ^ 1;
        in_s0 = extraout_s0_04;
        in_s1 = extraout_s1_04;
        in_s2 = extraout_s2_04;
        in_s3 = extraout_s3_04;
      }
      else {
        fVar5 = (float)in_r0[8];
        iVar2 = *in_r0;
        bVar3 = *(byte *)(Game + 0x718b9) ^ 1;
      }
      goto LAB_0007622c;
    }
    if (((iVar2 != 0) || ((float)in_r0[7] != 1.0)) ||
       ((*(char *)(iVar1 + 0x81779) != '\0' || (*(char *)(iVar1 + 0x8179c) != '\0'))))
    goto LAB_0007670c;
    in_r0[4] = 0;
    *in_r0 = 1;
    in_r0[5] = 0x3e2aaaab;
    cRWarning::Start((cRWarning *)(cRSubGame::GenerateLevel + iVar1 + 4));
    in_s0 = extraout_s0;
    in_s1 = extraout_s1;
    in_s2 = extraout_s2;
    in_s3 = extraout_s3;
  }
  fVar5 = (float)in_r0[8];
  iVar2 = *in_r0;
  bVar3 = *(byte *)(Game + 0x718b9) ^ 1;
LAB_0007622c:
  if (fVar5 <= 0.999) {
    if (0.01 <= fVar5) {
      fVar6 = fVar5 * -308.0 + 351.0;
    }
    else {
      fVar6 = 396.0;
    }
  }
  else {
    fVar6 = 0.0;
  }
  if (bVar3 == 0) {
    fVar4 = (float)in_r0[1];
  }
  else {
    fVar4 = (float)in_r0[1] + (float)in_r0[2];
    in_r0[1] = (int)fVar4;
  }
  if (1.0 < fVar4) {
    in_r0[1] = (int)(fVar4 - 1.0);
  }
  if ((0.9 < fVar5) || (iVar2 != 0)) {
    Sin(in_s0);
    tColour::tColour((tColour *)&local_40,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    OSDPrintUV(0x4d,0x440c0000,0x428c0000,0x42800000,0x43c60000,0x1000000,local_40,uStack_3c,
               uStack_38,uStack_34,gSpriteReference._2480_4_,1.0 - (float)gSpriteReference._2492_4_,
               gSpriteReference._2488_4_,
               (1.0 - (float)gSpriteReference._2492_4_) * 0.2265625 +
               (1.0 - (float)gSpriteReference._2484_4_) * 396.0 * 0.001953125,1,0);
    in_s0 = extraout_s0_01;
    in_s1 = extraout_s1_01;
    in_s2 = extraout_s2_01;
    in_s3 = extraout_s3_01;
  }
  tColour::tColour((tColour *)&local_50,in_s0,in_s1,in_s2,in_s3);
  fVar5 = fVar6 * -0.001953125 + 1.0;
  OSDPrintUV(0x4b,0x440c0000,0x428c0000,0x42800000,fVar6,0x1000000,local_50,uStack_4c,uStack_48,
             uStack_44,gSpriteReference._2416_4_,1.0 - (float)gSpriteReference._2428_4_,
             gSpriteReference._2424_4_,
             (1.0 - (float)gSpriteReference._2428_4_) * fVar5 +
             (1.0 - (float)gSpriteReference._2420_4_) * fVar6 * 0.001953125,1,0);
  tColour::tColour((tColour *)&local_60,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  OSDPrintUV(0x4c,0x440c0000,fVar6 + 70.0,0x42800000,396.0 - fVar6,0x1000000,local_60,uStack_5c,
             uStack_58,uStack_54,gSpriteReference._2448_4_,
             fVar5 * (1.0 - (float)gSpriteReference._2460_4_) +
             (1.0 - (float)gSpriteReference._2452_4_) * fVar6 * 0.001953125,
             gSpriteReference._2456_4_,
             (1.0 - (float)gSpriteReference._2460_4_) * 0.2265625 +
             (1.0 - (float)gSpriteReference._2452_4_) * 396.0 * 0.001953125,1,0);
  return;
}
