/*
 * mangled: _ZN13cRProgressBar2AIEv
 * demangled: cRProgressBar::AI()
 * address: 000768a4
 * size: 716
 */

/* cRProgressBar::AI() */

void cRProgressBar::AI(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
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
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
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

  fVar3 = DAT_00076b84;
  fVar2 = DAT_00076b80;
  fVar8 = DAT_00076b7c;
  fVar7 = DAT_00076b74;
  fVar1 = DAT_00076b70;
  iVar5 = DAT_00076b94 + 0x768c0;
  iVar4 = **(int **)(iVar5 + DAT_00076b98);
  fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(iVar4 + 0x71918),(byte)(in_fpscr >> 0x16) & 3);
  fVar9 = (float)VectorSignedToFloat(*(undefined4 *)(iVar4 + 0x71910),(byte)(in_fpscr >> 0x16) & 3);
  fVar9 = (*(float *)(iVar4 + 0x813c8) - fVar9) / (fVar6 - fVar9);
  fVar6 = DAT_00076b80;
  if ((0.0 <= fVar9) && (fVar6 = fVar9, DAT_00076b70 < fVar9)) {
    fVar6 = DAT_00076b70;
  }
  fVar9 = DAT_00076b74 + (DAT_00076b70 - fVar6) * DAT_00076b78;
  tColour::tColour((tColour *)&local_58,in_s0,in_s1,in_s2,in_s3);
  fVar6 = DAT_00076b8c;
  fVar11 = fVar9 + fVar8;
  iVar4 = *(int *)(iVar5 + DAT_00076b9c);
  OSDPrintUV(0x88,fVar7,fVar11 - DAT_00076b88,0x42800000,0x42800000,0x1000000,local_58,uStack_54,
             uStack_50,uStack_4c,*(undefined4 *)(iVar4 + 0x1110),fVar1 - *(float *)(iVar4 + 0x111c),
             *(undefined4 *)(iVar4 + 0x1118),fVar1 - *(float *)(iVar4 + 0x1114),1,fVar2);
  tColour::tColour((tColour *)&local_68,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  fVar10 = fVar1 - *(float *)(iVar4 + 0x10dc);
  fVar7 = fVar1 + fVar9 * fVar6;
  OSDPrintUV(0x86,0x41500000,fVar8,0x42800000,fVar9,0x1000000,local_68,uStack_64,uStack_60,uStack_5c
             ,*(undefined4 *)(iVar4 + 0x10d0),fVar10,*(undefined4 *)(iVar4 + 0x10d8),
             fVar10 * fVar7 + (fVar1 - *(float *)(iVar4 + 0x10d4)) * fVar9 * fVar3,1,fVar2);
  tColour::tColour((tColour *)&local_78,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  fVar8 = fVar1 - *(float *)(iVar4 + 0x10f4);
  OSDPrintUV(0x87,0x41500000,fVar11,0x42800000,DAT_00076b90 - fVar9,0x1000000,local_78,uStack_74,
             uStack_70,uStack_6c,*(undefined4 *)(iVar4 + 0x10f0),
             fVar7 * (fVar1 - *(float *)(iVar4 + 0x10fc)) + fVar8 * fVar9 * fVar3,
             *(undefined4 *)(iVar4 + 0x10f8),fVar8,1,fVar2);
  return;
}
