/*
 * mangled: _ZN6cRSlug2AIEv
 * demangled: cRSlug::AI()
 * address: 00078e8c
 * size: 1520
 */

/* cRSlug::AI() */

void cRSlug::AI(void)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  cRBod *in_r0;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  cRSprite *pcVar7;
  int iVar8;
  uint in_fpscr;
  uint uVar9;
  uint uVar10;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float in_s1;
  float extraout_s1;
  float extraout_s1_00;
  float in_s2;
  float extraout_s2;
  float extraout_s2_00;
  float in_s3;
  float extraout_s3;
  float extraout_s3_00;
  float fVar11;
  float fVar12;
  float fVar13;

  if (*(char *)(*(int *)(in_r0 + 0x7c) + 0x19) != '\0') {
    return;
  }
  switch(*(undefined4 *)(in_r0 + 0x74)) {
  case 0:
    return;
  case 1:
    if ((in_r0[0xc0] == (cRBod)0x0) || (G0RenderNextFlag == '\0')) {
      fVar13 = *(float *)(in_r0 + 0xc4);
    }
    else {
      fVar13 = *(float *)(in_r0 + 200);
      *(float *)(in_r0 + 0xc4) = fVar13;
      in_r0[0xc0] = (cRBod)0x0;
    }
    if (fVar13 == 0.0) {
      fVar13 = *(float *)(in_r0 + 0xdc);
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f | (uint)(fVar13 == 0.0) << 0x1e;
      uVar10 = uVar9 | (uint)NAN(fVar13) << 0x1c;
      *(float *)(in_r0 + 0xd8) = *(float *)(in_r0 + 0xd8) + fVar13;
      bVar2 = (byte)(uVar9 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(uVar10 >> 0x1c) & 1)) {
        pcVar7 = *(cRSprite **)(in_r0 + 0xa0);
        iVar6 = 0x6b;
      }
      else {
        pcVar7 = *(cRSprite **)(in_r0 + 0xa0);
        iVar6 = 0x6a;
      }
      cRSprite::SetTextureRef(pcVar7,iVar6,0);
      iVar6 = *(int *)(in_r0 + 0xa0);
      *(undefined4 *)(iVar6 + 0x28) = 1;
      fVar13 = (float)tColour::Set((tColour *)(iVar6 + 0x2c),extraout_s0_01,extraout_s1,extraout_s2,
                                   extraout_s3);
      fVar11 = *(float *)(in_r0 + 0xd8);
      uVar9 = uVar10 & 0xfffffff | (uint)(fVar11 < 0.0) << 0x1f;
      if (SUB41(uVar9 >> 0x1f,0)) {
        *(undefined4 *)(in_r0 + 0xd8) = 0;
        uVar4 = cRSubGame::BlinkRand((cRSubGame *)(Game + 0x718a0));
        *(undefined4 *)(in_r0 + 0xdc) = uVar4;
        fVar13 = extraout_s0_03;
      }
      else {
        uVar10 = uVar10 & 0xfffffff | (uint)(fVar11 < 1.0) << 0x1f | (uint)(fVar11 == 1.0) << 0x1e;
        uVar9 = uVar10 | (uint)NAN(fVar11) << 0x1c;
        bVar2 = (byte)(uVar10 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar9 >> 0x1c) & 1)) {
          *(undefined4 *)(in_r0 + 0xd8) = 0x3f800000;
          *(undefined4 *)(in_r0 + 0xdc) = 0xbe2aaaab;
        }
      }
    }
    else {
      fVar13 = fVar13 + *(float *)(in_r0 + 200);
      uVar10 = in_fpscr & 0xfffffff | (uint)(fVar13 < 1.0) << 0x1f | (uint)(fVar13 == 1.0) << 0x1e;
      uVar9 = uVar10 | (uint)NAN(fVar13) << 0x1c;
      *(float *)(in_r0 + 0xc4) = fVar13;
      bVar2 = (byte)(uVar10 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(uVar9 >> 0x1c) & 1)) {
        pcVar7 = *(cRSprite **)(in_r0 + 0xa0);
        *(undefined4 *)(pcVar7 + 0x28) = 5;
        cRSprite::SetTextureRef(pcVar7,0x6c,0);
        fVar13 = (float)tColour::Set((tColour *)(*(int *)(in_r0 + 0xa0) + 0x2c),extraout_s0_02,
                                     extraout_s1_00,extraout_s2_00,extraout_s3_00);
      }
      else {
        iVar6 = *(int *)(in_r0 + 0xa0);
        *(undefined4 *)(in_r0 + 0xc4) = 0;
        *(undefined4 *)(in_r0 + 0xd8) = 0x3f800000;
        *(undefined4 *)(in_r0 + 0xdc) = 0xbe2aaaab;
        *(undefined4 *)(iVar6 + 0x28) = 1;
        tColour::Set((tColour *)(iVar6 + 0x2c),in_s0,in_s1,in_s2,in_s3);
        fVar13 = (float)cRSprite::SetTextureRef(*(cRSprite **)(in_r0 + 0xa0),0x6b,0);
      }
    }
    iVar6 = *(int *)(in_r0 + 0xb4);
    fVar12 = *(float *)(iVar6 + 100);
    fVar11 = *(float *)(in_r0 + 100);
    uVar9 = uVar9 & 0xfffffff | (uint)(fVar11 < fVar12 + 1.0) << 0x1f;
    if ((SUB41(uVar9 >> 0x1f,0)) && (in_r0[0xcd] == (cRBod)0x0)) {
      in_r0[0xcd] = (cRBod)0x1;
      uVar4 = gRMathRand2();
      fVar13 = (float)VectorSignedToFloat(uVar4,(byte)(uVar9 >> 0x16) & 3);
      fVar13 = fVar13 * 3.0517578e-05;
      uVar9 = uVar9 & 0xfffffff | (uint)(fVar13 < 0.6) << 0x1f | (uint)(fVar13 == 0.6) << 0x1e;
      uVar10 = uVar9 | (uint)NAN(fVar13) << 0x1c;
      bVar2 = (byte)(uVar9 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(uVar10 >> 0x1c) & 1)) {
        iVar6 = *(int *)(in_r0 + 0xb4);
        fVar11 = *(float *)(in_r0 + 100);
        fVar12 = *(float *)(iVar6 + 100);
        fVar13 = extraout_s0_04;
      }
      else {
        uVar4 = gRMathRand2();
        VectorSignedToFloat(uVar4,(byte)(uVar10 >> 0x16) & 3);
        fVar13 = (float)VoicePlay((int)in_r0);
        iVar6 = *(int *)(in_r0 + 0xb4);
        fVar11 = *(float *)(in_r0 + 100);
        fVar12 = *(float *)(iVar6 + 100);
      }
    }
    if ((fVar11 < fVar12) && (in_r0[0xa8] == (cRBod)0x0)) {
      in_r0[0xa8] = (cRBod)0x1;
    }
    if ((*(int *)(in_r0 + 0xb8) == 1) && (fVar11 < *(float *)(iVar6 + 100) + 16.0)) {
      *(undefined4 *)(in_r0 + 0xb8) = 0;
      fVar13 = (float)cRVoiceManager::Play((int)&gVoiceManager,2,1);
      iVar6 = *(int *)(in_r0 + 0xb4);
      fVar11 = *(float *)(in_r0 + 100);
    }
    iVar8 = *(int *)(in_r0 + 0xa0);
    uVar4 = *(undefined4 *)(in_r0 + 0x60);
    uVar5 = *(undefined4 *)(in_r0 + 100);
    *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
    *(undefined4 *)(iVar8 + 0x4c) = uVar4;
    *(undefined4 *)(iVar8 + 0x50) = uVar5;
    if (*(float *)(iVar6 + 0x27fc) <= fVar11) {
      if (0.0 < *(float *)(iVar6 + 0x364)) {
        fVar13 = (float)Kill((cRSlug *)in_r0);
      }
      cREnemyManager::Register
                ((cREnemyManager *)(gGroup0 + *(int *)(in_r0 + 0x7c) + 0xc0700),
                 (tVector *)(in_r0 + 0x5c),fVar13,0x40000000,(cRBodPos *)0x1);
      iVar8 = *(int *)(in_r0 + 0xa0);
      iVar6 = *(int *)(in_r0 + 0xb4);
      goto LAB_00079074;
    }
    break;
  case 2:
    *(undefined4 *)(in_r0 + 0x74) = 3;
    fVar13 = (float)SRAND(in_s0,(char *)0x3dcccccd);
    fVar11 = (float)RAND(extraout_s0,(char *)0x3e4ccccd);
    uVar4 = RAND(extraout_s0_00,(char *)0x3e99999a);
    *(float *)(in_r0 + 0x80) = fVar13;
    *(float *)(in_r0 + 0x84) = fVar11 + 0.1;
    *(undefined4 *)(in_r0 + 0x88) = uVar4;
    if (*(int *)(in_r0 + 0x78) == 1) {
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
      if (SUB41(uVar9 >> 0x1f,0)) {
LAB_000793b0:
        fVar13 = -fVar13;
        uVar9 = uVar9 & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
        if (SUB41(uVar9 >> 0x1f,0)) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
      }
      else {
        bVar3 = false;
      }
      *(float *)(in_r0 + 0x80) = fVar13;
    }
    else if (*(int *)(in_r0 + 0x78) == 2) {
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
      if (!SUB41(uVar9 >> 0x1f,0)) goto LAB_000793b0;
      bVar3 = true;
      *(float *)(in_r0 + 0x80) = fVar13;
    }
    else {
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
      if (SUB41(uVar9 >> 0x1f,0)) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
    }
    if (bVar3) {
      fVar11 = -0.2;
    }
    else {
      uVar9 = uVar9 & 0xfffffff | (uint)(fVar13 == 0.0) << 0x1e;
      fVar11 = (float)VectorSignedToFloat((uint)!SUB41(uVar9 >> 0x1e,0),(byte)(uVar9 >> 0x16) & 3);
      fVar11 = fVar11 * 0.2;
    }
    *(undefined4 *)(in_r0 + 0x90) = 0;
    *(float *)(in_r0 + 0x80) = fVar11 + fVar13;
    fVar13 = *(float *)(*(int *)(in_r0 + 0x7c) + 0x54);
    *(undefined4 *)(in_r0 + 0x98) = 0;
    *(float *)(in_r0 + 0x94) = fVar13 * 0.008333334;
    *(float *)(in_r0 + 0x9c) = *(float *)(*(int *)(in_r0 + 0x7c) + 0x54) * 0.16666667;
    break;
  case 3:
    break;
  case 4:
    fVar13 = *(float *)(in_r0 + 0xac) + *(float *)(in_r0 + 0xb0);
    *(float *)(in_r0 + 0xac) = fVar13;
    if (6.2831855 < fVar13) {
      *(float *)(in_r0 + 0xac) = fVar13 - 6.2831855;
    }
    fVar13 = (float)Sin(in_s0);
    fVar12 = *(float *)(in_r0 + 100);
    iVar6 = *(int *)(in_r0 + 0xb4);
    fVar11 = *(float *)(iVar6 + 100);
    *(float *)(in_r0 + 0x5c) = fVar13 * 3.0;
    if ((fVar12 < fVar11) && (in_r0[0xa8] == (cRBod)0x0)) {
      in_r0[0xa8] = (cRBod)0x1;
    }
    iVar8 = *(int *)(in_r0 + 0xa0);
    uVar4 = *(undefined4 *)(in_r0 + 0x60);
    uVar5 = *(undefined4 *)(in_r0 + 100);
    *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
    *(undefined4 *)(iVar8 + 0x4c) = uVar4;
    *(undefined4 *)(iVar8 + 0x50) = uVar5;
    if (*(float *)(iVar6 + 0x27fc) <= fVar12) {
      if (0.0 < *(float *)(iVar6 + 0x364)) {
        Kill((cRSlug *)in_r0);
        iVar8 = *(int *)(in_r0 + 0xa0);
        iVar6 = *(int *)(in_r0 + 0xb4);
      }
      goto LAB_00079074;
    }
    break;
  default:
    iVar8 = *(int *)(in_r0 + 0xa0);
    iVar6 = *(int *)(in_r0 + 0xb4);
LAB_00079074:
    cVar1 = *(char *)(iVar6 + 0x374);
    fVar13 = *(float *)(iVar6 + 0x360) + *(float *)(in_r0 + 0x8c) + *(float *)(iVar6 + 0x34c);
    *(float *)(iVar8 + 0x7c) = fVar13;
    if (cVar1 != '\0') {
      *(float *)(iVar8 + 0x7c) = fVar13 + *(float *)(iVar6 + 0x390) + *(float *)(iVar6 + 0x38c);
    }
    VoiceAI((cRSlug *)in_r0);
    return;
  }
  *(undefined4 *)(in_r0 + 0x74) = 0;
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),in_r0);
  cRSprite::Kill(*(cRSprite **)(in_r0 + 0xa0));
  return;
}
