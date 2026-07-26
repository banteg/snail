/*
 * mangled: _ZN13cRDamageGuage2AIEv
 * demangled: cRDamageGuage::AI()
 * address: 000761ec
 * size: 1624
 */

/* cRDamageGuage::AI() */

void cRDamageGuage::AI(void)

{
  bool bVar1;
  int iVar2;
  int *in_r0;
  int iVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar9;
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
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
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

  iVar7 = DAT_00076388;
  iVar6 = DAT_00076384 + 0x76208;
  iVar4 = **(int **)(iVar6 + DAT_00076388);
  if (*(char *)(iVar4 + 0x718b9) == '\x01') {
    iVar3 = *in_r0;
    fVar13 = (float)in_r0[8];
    bVar5 = 0;
    goto LAB_0007622c;
  }
  fVar13 = (float)in_r0[8] + ((float)in_r0[7] - (float)in_r0[8]) * DAT_0007637c;
  in_r0[8] = (int)fVar13;
  fVar9 = DAT_000763cc;
  if (0.0 < (float)in_r0[9]) {
    fVar12 = (float)in_r0[9] + (float)in_r0[10];
    in_r0[9] = (int)fVar12;
    if (fVar9 < fVar12) {
      in_r0[9] = (int)DAT_000763b0;
    }
  }
  fVar9 = DAT_000763cc;
  iVar3 = *in_r0;
  if (iVar3 == 1) {
    if (*(char *)(iVar4 + 0x8179c) == '\0') {
      fVar9 = (float)in_r0[4];
    }
    else {
      in_r0[4] = (int)DAT_000763cc;
    }
    bVar1 = fVar9 + (float)in_r0[5] < DAT_000763cc;
    in_r0[4] = (int)(fVar9 + (float)in_r0[5]);
    iVar2 = DAT_00076390;
    if ((bVar1) || (*(float *)(iVar4 + 0x813c4) != DAT_000763d0)) {
LAB_0007670c:
      bVar5 = *(byte *)(iVar4 + 0x718b9) ^ 1;
      goto LAB_0007622c;
    }
    *in_r0 = 2;
    cRVoiceManager::Play(*(int *)(iVar6 + iVar2),0xe,0);
    in_s0 = extraout_s0_05;
    in_s1 = extraout_s1_05;
    in_s2 = extraout_s2_05;
    in_s3 = extraout_s3_05;
  }
  else {
    if (iVar3 == 2) {
      fVar9 = (float)cRSnailSkin::Change((cRSnailSkin *)(iVar4 + 0x852d4),1,in_s0);
      Take(fVar9,SUB41(in_r0,0));
      piVar8 = *(int **)(iVar6 + iVar7);
      in_r0[6] = 5;
      iVar4 = *piVar8;
      in_s0 = extraout_s0_03;
      in_s1 = extraout_s1_03;
      in_s2 = extraout_s2_03;
      in_s3 = extraout_s3_03;
      if (*(char *)(iVar4 + 0x8179c) != '\0') {
        Take(extraout_s0_03,SUB41(in_r0,0));
        iVar4 = *piVar8;
        in_s0 = extraout_s0_06;
        in_s1 = extraout_s1_06;
        in_s2 = extraout_s2_06;
        in_s3 = extraout_s3_06;
      }
      if (((((float)in_r0[7] == 0.0) && (*(float *)(iVar4 + 0x813c4) == DAT_000763d0)) ||
          (0.0 < *(float *)(iVar4 + 0x817a0))) ||
         ((0.0 < *(float *)(iVar4 + 0x813e4) || (*(int *)(iVar4 + 0x85300) != 0)))) {
        *in_r0 = 0;
        cRWarning::Stop((cRWarning *)(cRSubGame::GenerateLevel + iVar4 + 4));
        piVar8 = *(int **)(iVar6 + iVar7);
        cRWarning::StopSample();
        iVar3 = *in_r0;
        fVar13 = (float)in_r0[8];
        bVar5 = *(byte *)(*piVar8 + 0x718b9) ^ 1;
        in_s0 = extraout_s0_04;
        in_s1 = extraout_s1_04;
        in_s2 = extraout_s2_04;
        in_s3 = extraout_s3_04;
      }
      else {
        fVar13 = (float)in_r0[8];
        iVar3 = *in_r0;
        bVar5 = *(byte *)(iVar4 + 0x718b9) ^ 1;
      }
      goto LAB_0007622c;
    }
    if (((iVar3 != 0) || ((float)in_r0[7] != DAT_000763cc)) ||
       ((*(char *)(iVar4 + 0x81779) != '\0' || (*(char *)(iVar4 + 0x8179c) != '\0'))))
    goto LAB_0007670c;
    in_r0[4] = (int)DAT_000763b0;
    *in_r0 = 1;
    in_r0[5] = DAT_00076380;
    cRWarning::Start((cRWarning *)(cRSubGame::GenerateLevel + iVar4 + 4));
    in_s0 = extraout_s0;
    in_s1 = extraout_s1;
    in_s2 = extraout_s2;
    in_s3 = extraout_s3;
  }
  fVar13 = (float)in_r0[8];
  iVar3 = *in_r0;
  bVar5 = *(byte *)(**(int **)(iVar6 + iVar7) + 0x718b9) ^ 1;
LAB_0007622c:
  fVar12 = DAT_000763cc;
  fVar9 = DAT_000763b0;
  if ((fVar13 <= DAT_00076374) && (fVar9 = DAT_000763c4, DAT_000763b8 <= fVar13)) {
    fVar9 = DAT_000763bc + fVar13 * DAT_000763c0;
  }
  if (bVar5 == 0) {
    fVar11 = (float)in_r0[1];
  }
  else {
    fVar11 = (float)in_r0[1] + (float)in_r0[2];
    in_r0[1] = (int)fVar11;
  }
  if (fVar12 < fVar11) {
    in_r0[1] = (int)(fVar11 - fVar12);
  }
  fVar12 = DAT_000763cc;
  iVar7 = DAT_0007638c;
  if ((DAT_00076378 < fVar13) || (iVar3 != 0)) {
    Sin(in_s0);
    tColour::tColour((tColour *)&local_40,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    iVar4 = *(int *)(iVar6 + iVar7);
    fVar13 = fVar12 - *(float *)(iVar4 + 0x9bc);
    OSDPrintUV(0x4d,0x440c0000,0x428c0000,0x42800000,DAT_000763c4,0x1000000,local_40,uStack_3c,
               uStack_38,uStack_34,*(undefined4 *)(iVar4 + 0x9b0),fVar13,
               *(undefined4 *)(iVar4 + 0x9b8),
               fVar13 * DAT_000763b4 +
               (fVar12 - *(float *)(iVar4 + 0x9b4)) * DAT_000763c4 * DAT_000763a8,1,DAT_000763b0);
    in_s0 = extraout_s0_01;
    in_s1 = extraout_s1_01;
    in_s2 = extraout_s2_01;
    in_s3 = extraout_s3_01;
  }
  fVar15 = DAT_000763cc;
  tColour::tColour((tColour *)&local_50,in_s0,in_s1,in_s2,in_s3);
  fVar11 = DAT_000763b0;
  fVar12 = DAT_000763ac;
  fVar13 = DAT_000763a8;
  iVar7 = *(int *)(iVar6 + iVar7);
  fVar10 = fVar15 + fVar9 * DAT_000763a4;
  fVar14 = fVar15 - *(float *)(iVar7 + 0x97c);
  OSDPrintUV(0x4b,0x440c0000,DAT_000763ac,0x42800000,fVar9,0x1000000,local_50,uStack_4c,uStack_48,
             uStack_44,*(undefined4 *)(iVar7 + 0x970),fVar14,*(undefined4 *)(iVar7 + 0x978),
             fVar14 * fVar10 + (fVar15 - *(float *)(iVar7 + 0x974)) * fVar9 * DAT_000763a8,1,
             DAT_000763b0);
  tColour::tColour((tColour *)&local_60,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  fVar14 = fVar15 - *(float *)(iVar7 + 0x99c);
  fVar15 = fVar15 - *(float *)(iVar7 + 0x994);
  OSDPrintUV(0x4c,0x440c0000,fVar9 + fVar12,0x42800000,DAT_000763c4 - fVar9,0x1000000,local_60,
             uStack_5c,uStack_58,uStack_54,*(undefined4 *)(iVar7 + 0x990),
             fVar10 * fVar14 + fVar15 * fVar9 * fVar13,*(undefined4 *)(iVar7 + 0x998),
             fVar14 * DAT_000763b4 + fVar15 * DAT_000763c4 * fVar13,1,fVar11);
  return;
}
