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
  char *pcVar4;
  cRBod *in_r0;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  cRSprite *pcVar8;
  int iVar9;
  int iVar10;
  uint in_fpscr;
  uint uVar11;
  uint uVar12;
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
  float fVar13;
  float fVar14;
  float fVar15;

  fVar15 = DAT_00079194;
  pcVar4 = DAT_00079184;
  iVar9 = DAT_000791a0 + 0x78eac;
  if (*(char *)(*(int *)(in_r0 + 0x7c) + 0x19) != '\0') {
    return;
  }
  switch(*(undefined4 *)(in_r0 + 0x74)) {
  case 0:
    return;
  case 1:
    if ((in_r0[0xc0] == (cRBod)0x0) || (**(char **)(iVar9 + DAT_000791a8) == '\0')) {
      fVar15 = *(float *)(in_r0 + 0xc4);
    }
    else {
      fVar15 = *(float *)(in_r0 + 200);
      *(float *)(in_r0 + 0xc4) = fVar15;
      in_r0[0xc0] = (cRBod)0x0;
    }
    fVar13 = DAT_000791b8;
    if (fVar15 == 0.0) {
      fVar15 = *(float *)(in_r0 + 0xdc);
      uVar11 = in_fpscr & 0xfffffff | (uint)(fVar15 < 0.0) << 0x1f | (uint)(fVar15 == 0.0) << 0x1e;
      uVar12 = uVar11 | (uint)NAN(fVar15) << 0x1c;
      *(float *)(in_r0 + 0xd8) = *(float *)(in_r0 + 0xd8) + fVar15;
      bVar2 = (byte)(uVar11 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(uVar12 >> 0x1c) & 1)) {
        pcVar8 = *(cRSprite **)(in_r0 + 0xa0);
        iVar7 = 0x6b;
      }
      else {
        pcVar8 = *(cRSprite **)(in_r0 + 0xa0);
        iVar7 = 0x6a;
      }
      cRSprite::SetTextureRef(pcVar8,iVar7,0);
      iVar7 = *(int *)(in_r0 + 0xa0);
      *(undefined4 *)(iVar7 + 0x28) = 1;
      fVar15 = (float)tColour::Set((tColour *)(iVar7 + 0x2c),extraout_s0_01,extraout_s1,extraout_s2,
                                   extraout_s3);
      uVar5 = DAT_000791b4;
      iVar7 = DAT_000791ac;
      fVar13 = *(float *)(in_r0 + 0xd8);
      uVar11 = uVar12 & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
      if (SUB41(uVar11 >> 0x1f,0)) {
        *(undefined4 *)(in_r0 + 0xd8) = DAT_000791c0;
        uVar5 = cRSubGame::BlinkRand((cRSubGame *)(**(int **)(iVar9 + iVar7) + 0x718a0));
        *(undefined4 *)(in_r0 + 0xdc) = uVar5;
        fVar15 = extraout_s0_03;
      }
      else {
        uVar12 = uVar12 & 0xfffffff | (uint)(fVar13 < DAT_000791b8) << 0x1f |
                 (uint)(fVar13 == DAT_000791b8) << 0x1e;
        uVar11 = uVar12 | (uint)(NAN(fVar13) || NAN(DAT_000791b8)) << 0x1c;
        bVar2 = (byte)(uVar12 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar11 >> 0x1c) & 1)) {
          *(float *)(in_r0 + 0xd8) = DAT_000791b8;
          *(undefined4 *)(in_r0 + 0xdc) = uVar5;
        }
      }
    }
    else {
      fVar15 = fVar15 + *(float *)(in_r0 + 200);
      uVar12 = in_fpscr & 0xfffffff | (uint)(fVar15 < DAT_000791b8) << 0x1f |
               (uint)(fVar15 == DAT_000791b8) << 0x1e;
      uVar11 = uVar12 | (uint)(NAN(fVar15) || NAN(DAT_000791b8)) << 0x1c;
      *(float *)(in_r0 + 0xc4) = fVar15;
      bVar2 = (byte)(uVar12 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(uVar11 >> 0x1c) & 1)) {
        pcVar8 = *(cRSprite **)(in_r0 + 0xa0);
        *(undefined4 *)(pcVar8 + 0x28) = 5;
        cRSprite::SetTextureRef(pcVar8,0x6c,0);
        fVar15 = (float)tColour::Set((tColour *)(*(int *)(in_r0 + 0xa0) + 0x2c),extraout_s0_02,
                                     extraout_s1_00,extraout_s2_00,extraout_s3_00);
      }
      else {
        iVar7 = *(int *)(in_r0 + 0xa0);
        *(undefined4 *)(in_r0 + 0xc4) = 0;
        *(float *)(in_r0 + 0xd8) = fVar13;
        *(undefined4 *)(in_r0 + 0xdc) = DAT_000791b4;
        *(undefined4 *)(iVar7 + 0x28) = 1;
        tColour::Set((tColour *)(iVar7 + 0x2c),in_s0,in_s1,in_s2,in_s3);
        fVar15 = (float)cRSprite::SetTextureRef(*(cRSprite **)(in_r0 + 0xa0),0x6b,0);
      }
    }
    iVar7 = *(int *)(in_r0 + 0xb4);
    fVar14 = *(float *)(iVar7 + 100);
    fVar13 = *(float *)(in_r0 + 100);
    uVar11 = uVar11 & 0xfffffff | (uint)(fVar13 < fVar14 + DAT_000791b8) << 0x1f;
    if ((SUB41(uVar11 >> 0x1f,0)) && (in_r0[0xcd] == (cRBod)0x0)) {
      in_r0[0xcd] = (cRBod)0x1;
      uVar5 = gRMathRand2();
      fVar15 = (float)VectorSignedToFloat(uVar5,(byte)(uVar11 >> 0x16) & 3);
      fVar15 = fVar15 * DAT_000791c8;
      uVar11 = uVar11 & 0xfffffff | (uint)(fVar15 < DAT_000791cc) << 0x1f |
               (uint)(fVar15 == DAT_000791cc) << 0x1e;
      uVar12 = uVar11 | (uint)(NAN(fVar15) || NAN(DAT_000791cc)) << 0x1c;
      bVar2 = (byte)(uVar11 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(uVar12 >> 0x1c) & 1)) {
        iVar7 = *(int *)(in_r0 + 0xb4);
        fVar13 = *(float *)(in_r0 + 100);
        fVar14 = *(float *)(iVar7 + 100);
        fVar15 = extraout_s0_04;
      }
      else {
        uVar5 = gRMathRand2();
        VectorSignedToFloat(uVar5,(byte)(uVar12 >> 0x16) & 3);
        fVar15 = (float)VoicePlay((int)in_r0);
        iVar7 = *(int *)(in_r0 + 0xb4);
        fVar13 = *(float *)(in_r0 + 100);
        fVar14 = *(float *)(iVar7 + 100);
      }
    }
    if ((fVar13 < fVar14) && (in_r0[0xa8] == (cRBod)0x0)) {
      in_r0[0xa8] = (cRBod)0x1;
    }
    iVar10 = DAT_000791b0;
    if ((*(int *)(in_r0 + 0xb8) == 1) && (fVar13 < DAT_000791c4 + *(float *)(iVar7 + 100))) {
      *(undefined4 *)(in_r0 + 0xb8) = 0;
      fVar15 = (float)cRVoiceManager::Play(*(int *)(iVar9 + iVar10),2,1);
      iVar7 = *(int *)(in_r0 + 0xb4);
      fVar13 = *(float *)(in_r0 + 100);
    }
    iVar10 = *(int *)(in_r0 + 0xa0);
    uVar5 = *(undefined4 *)(in_r0 + 0x60);
    uVar6 = *(undefined4 *)(in_r0 + 100);
    *(undefined4 *)(iVar10 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
    *(undefined4 *)(iVar10 + 0x4c) = uVar5;
    *(undefined4 *)(iVar10 + 0x50) = uVar6;
    if (*(float *)(iVar7 + 0x27fc) <= fVar13) {
      if (0.0 < *(float *)(iVar7 + 0x364)) {
        fVar15 = (float)Kill((cRSlug *)in_r0);
      }
      cREnemyManager::Register
                ((cREnemyManager *)(gGroup0 + *(int *)(in_r0 + 0x7c) + 0xc0700),
                 (tVector *)(in_r0 + 0x5c),fVar15,0x40000000,(cRBodPos *)0x1);
      iVar10 = *(int *)(in_r0 + 0xa0);
      iVar7 = *(int *)(in_r0 + 0xb4);
      goto LAB_00079074;
    }
    break;
  case 2:
    *(undefined4 *)(in_r0 + 0x74) = 3;
    fVar15 = (float)SRAND(in_s0,pcVar4);
    fVar13 = (float)RAND(extraout_s0,(char *)0x3e4ccccd);
    uVar5 = RAND(extraout_s0_00,(char *)0x3e99999a);
    *(float *)(in_r0 + 0x80) = fVar15;
    *(float *)(in_r0 + 0x84) = fVar13 + (float)pcVar4;
    *(undefined4 *)(in_r0 + 0x88) = uVar5;
    if (*(int *)(in_r0 + 0x78) == 1) {
      uVar11 = in_fpscr & 0xfffffff | (uint)(fVar15 < 0.0) << 0x1f;
      if (SUB41(uVar11 >> 0x1f,0)) {
LAB_000793b0:
        fVar15 = -fVar15;
        uVar11 = uVar11 & 0xfffffff | (uint)(fVar15 < 0.0) << 0x1f;
        if (SUB41(uVar11 >> 0x1f,0)) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
      }
      else {
        bVar3 = false;
      }
      *(float *)(in_r0 + 0x80) = fVar15;
    }
    else if (*(int *)(in_r0 + 0x78) == 2) {
      uVar11 = in_fpscr & 0xfffffff | (uint)(fVar15 < 0.0) << 0x1f;
      if (!SUB41(uVar11 >> 0x1f,0)) goto LAB_000793b0;
      bVar3 = true;
      *(float *)(in_r0 + 0x80) = fVar15;
    }
    else {
      uVar11 = in_fpscr & 0xfffffff | (uint)(fVar15 < 0.0) << 0x1f;
      if (SUB41(uVar11 >> 0x1f,0)) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
    }
    uVar5 = DAT_000791c0;
    fVar13 = DAT_0007918c;
    fVar14 = DAT_00079188;
    if (!bVar3) {
      uVar11 = uVar11 & 0xfffffff | (uint)(fVar15 == 0.0) << 0x1e;
      fVar14 = (float)VectorSignedToFloat((uint)!SUB41(uVar11 >> 0x1e,0),(byte)(uVar11 >> 0x16) & 3)
      ;
      fVar14 = fVar14 * DAT_0007919c;
    }
    *(undefined4 *)(in_r0 + 0x90) = DAT_000791c0;
    *(float *)(in_r0 + 0x80) = fVar14 + fVar15;
    fVar14 = *(float *)(*(int *)(in_r0 + 0x7c) + 0x54);
    *(undefined4 *)(in_r0 + 0x98) = uVar5;
    fVar15 = DAT_00079190;
    *(float *)(in_r0 + 0x94) = fVar14 * fVar13;
    *(float *)(in_r0 + 0x9c) = *(float *)(*(int *)(in_r0 + 0x7c) + 0x54) * fVar15;
    break;
  case 3:
    break;
  case 4:
    fVar13 = *(float *)(in_r0 + 0xac) + *(float *)(in_r0 + 0xb0);
    *(float *)(in_r0 + 0xac) = fVar13;
    if (fVar15 < fVar13) {
      *(float *)(in_r0 + 0xac) = fVar13 - fVar15;
    }
    fVar15 = (float)Sin(in_s0);
    fVar14 = *(float *)(in_r0 + 100);
    iVar7 = *(int *)(in_r0 + 0xb4);
    fVar13 = *(float *)(iVar7 + 100);
    *(float *)(in_r0 + 0x5c) = fVar15 * DAT_00079198;
    if ((fVar14 < fVar13) && (in_r0[0xa8] == (cRBod)0x0)) {
      in_r0[0xa8] = (cRBod)0x1;
    }
    iVar10 = *(int *)(in_r0 + 0xa0);
    uVar5 = *(undefined4 *)(in_r0 + 0x60);
    uVar6 = *(undefined4 *)(in_r0 + 100);
    *(undefined4 *)(iVar10 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
    *(undefined4 *)(iVar10 + 0x4c) = uVar5;
    *(undefined4 *)(iVar10 + 0x50) = uVar6;
    if (*(float *)(iVar7 + 0x27fc) <= fVar14) {
      if (0.0 < *(float *)(iVar7 + 0x364)) {
        Kill((cRSlug *)in_r0);
        iVar10 = *(int *)(in_r0 + 0xa0);
        iVar7 = *(int *)(in_r0 + 0xb4);
      }
      goto LAB_00079074;
    }
    break;
  default:
    iVar10 = *(int *)(in_r0 + 0xa0);
    iVar7 = *(int *)(in_r0 + 0xb4);
LAB_00079074:
    cVar1 = *(char *)(iVar7 + 0x374);
    fVar15 = *(float *)(iVar7 + 0x360) + *(float *)(in_r0 + 0x8c) + *(float *)(iVar7 + 0x34c);
    *(float *)(iVar10 + 0x7c) = fVar15;
    if (cVar1 != '\0') {
      *(float *)(iVar10 + 0x7c) = fVar15 + *(float *)(iVar7 + 0x390) + *(float *)(iVar7 + 0x38c);
    }
    VoiceAI((cRSlug *)in_r0);
    return;
  }
  *(undefined4 *)(in_r0 + 0x74) = 0;
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(**(int **)(iVar9 + DAT_000791ac) + 0x358),in_r0)
  ;
  cRSprite::Kill(*(cRSprite **)(in_r0 + 0xa0));
  return;
}
