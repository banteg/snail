/*
 * mangled: _ZN14cAccelerometer2AIEv
 * demangled: cAccelerometer::AI()
 * address: 0005b400
 * size: 1140
 */

/* cAccelerometer::AI() */

void cAccelerometer::AI(void)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  double dVar4;
  undefined4 uVar5;
  int in_r0;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  uint in_fpscr;
  uint uVar14;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float in_s1;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float fVar15;
  float extraout_s1_02;
  float extraout_s1_03;
  double dVar16;
  float fVar17;
  int iVar18;
  float fVar19;

  iVar11 = DAT_0005b7dc + 0x5b418;
  if ((*(char *)(*(int *)(iVar11 + DAT_0005b7e0) + 0xbd) == '\0') ||
     (10 < **(int **)(iVar11 + DAT_0005b7e4))) {
    wprintf((char *)(iVar11 + DAT_0005b7e8));
    fVar19 = DAT_0005b7b0;
    iVar11 = **(int **)(iVar11 + DAT_0005b7ec);
    *(undefined4 *)(iVar11 + 0x48) = DAT_0005b7b4;
    *(float *)(iVar11 + 0x40) = fVar19;
    *(float *)(iVar11 + 0x3c) = fVar19;
    OFOrientation();
    return;
  }
  fVar6 = (float)ATan(in_s0,in_s1);
  fVar15 = DAT_0005b7c4;
  fVar19 = DAT_0005b7c0;
  uVar5 = DAT_0005b7b4;
  dVar4 = DAT_0005b7a8;
  fVar17 = *(float *)(in_r0 + 8);
  if (fVar17 < 0.0) {
    uVar14 = in_fpscr & 0xfffffff | (uint)(fVar17 < DAT_0005b7c8) << 0x1f |
             (uint)(fVar17 == DAT_0005b7c8) << 0x1e;
    bVar3 = (byte)(uVar14 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && (bool)(bVar3 >> 7) == (NAN(fVar17) || NAN(DAT_0005b7c8)))
    goto LAB_0005b4ac;
LAB_0005b644:
    iVar18 = **(int **)(iVar11 + DAT_0005b7ec);
    iVar12 = DAT_0005b7ec;
  }
  else {
    uVar14 = in_fpscr & 0xfffffff | (uint)(fVar17 < DAT_0005b7b8) << 0x1f;
    if (!SUB41(uVar14 >> 0x1f,0)) goto LAB_0005b644;
LAB_0005b4ac:
    fVar17 = (float)VectorSignedToFloat((int)((fVar6 * DAT_0005b804) / DAT_0005b7fc + DAT_0005b7f8)
                                        % 0x168,(byte)(uVar14 >> 0x16) & 3);
    iVar7 = (int)((fVar17 + DAT_0005b7bc) / DAT_0005b800) % 4;
    fVar6 = (float)VectorSignedToFloat(iVar7 * 0x5a,(byte)(uVar14 >> 0x16) & 3);
    pfVar13 = (float *)(in_r0 + iVar7 * 4 + 0xc);
    iVar9 = 0;
    iVar18 = (int)(fVar17 - fVar6);
    if (iVar18 < 0) {
      iVar18 = -iVar18;
    }
    iVar8 = in_r0;
    if (0xb4 < iVar18) {
      iVar18 = 0x168 - iVar18;
    }
    do {
      if (iVar7 == iVar9) {
        fVar6 = *pfVar13;
        uVar2 = uVar14 & 0xfffffff;
        uVar14 = uVar2 | (uint)(fVar6 < fVar15) << 0x1f;
        if (SUB41(uVar14 >> 0x1f,0)) {
          dVar16 = (double)VectorSignedToFloat(iVar18,(byte)(uVar14 >> 0x16) & 3);
          uVar14 = uVar2 | (uint)(dVar16 < dVar4) << 0x1f;
          if (SUB41(uVar14 >> 0x1f,0)) {
            *pfVar13 = fVar6 + fVar19;
          }
        }
      }
      else {
        fVar6 = *(float *)(iVar8 + 0xc);
        uVar14 = uVar14 & 0xfffffff | (uint)(fVar6 < 0.0) << 0x1f | (uint)(fVar6 == 0.0) << 0x1e;
        bVar3 = (byte)(uVar14 >> 0x18);
        if (!(bool)(bVar3 >> 6 & 1) && (bool)(bVar3 >> 7) == NAN(fVar6)) {
          *(undefined4 *)(iVar8 + 0xc) = uVar5;
        }
      }
      iVar12 = DAT_0005b7ec;
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 + 4;
    } while (iVar9 != 4);
    if (*(float *)(in_r0 + 0x18) <= DAT_0005b800) goto LAB_0005b644;
    iVar18 = **(int **)(iVar11 + DAT_0005b7ec);
    if (*(float *)(iVar18 + 0x40) != DAT_0005b7b0) {
      *(float *)(iVar18 + 0x40) = DAT_0005b7b0;
    }
  }
  iVar7 = DAT_0005b7f0;
  fVar19 = *(float *)(iVar18 + 0x3c);
  iVar8 = *(int *)(iVar18 + 0x718fc);
  iVar9 = *(int *)(iVar11 + DAT_0005b7f0);
  *(float *)(iVar9 + 200) = fVar19;
  if (((iVar8 == 2 || iVar8 == 4) && (*(int *)(iVar9 + 8) == 1)) &&
     (gDirectory[iVar18 + 0x2544] == '\0')) {
    if (fVar19 == DAT_0005b800) {
      *(float *)(iVar18 + 0x4c) = DAT_0005b7c0;
    }
    else {
      if (fVar19 != DAT_0005b7b0) goto LAB_0005b5fc;
      *(undefined4 *)(iVar18 + 0x4c) = DAT_0005b7d8;
    }
  }
  else {
LAB_0005b5fc:
    *(undefined4 *)(iVar18 + 0x4c) = DAT_0005b7b4;
  }
  if (((*(int *)(iVar18 + 0x718fc) != 2) || (*(int *)(*(int *)(iVar11 + iVar7) + 8) != 0)) ||
     (gDirectory[iVar18 + 0x2544] != '\0')) {
    *(undefined4 *)(iVar18 + 0x48) = DAT_0005b7b4;
    goto LAB_0005b620;
  }
  iVar7 = (int)*(float *)(iVar18 + 0x3c);
  if (iVar7 == 0x5a) {
    fVar6 = (float)ACos(extraout_s0);
    piVar10 = *(int **)(iVar11 + iVar12);
    fVar6 = fVar6 * DAT_0005b804;
    fVar19 = extraout_s0_02;
    fVar15 = extraout_s1_02;
LAB_0005b6dc:
    *(float *)(iVar18 + 0x48) = fVar6 / DAT_0005b7fc - DAT_0005b800;
    iVar18 = *piVar10;
  }
  else {
    fVar19 = extraout_s0;
    fVar15 = extraout_s1;
    if (iVar7 < 0x5b) {
      if (iVar7 == 0) {
        fVar6 = (float)ACos(extraout_s0);
        piVar10 = *(int **)(iVar11 + iVar12);
        fVar6 = fVar6 * DAT_0005b804;
        fVar19 = extraout_s0_00;
        fVar15 = extraout_s1_00;
        goto LAB_0005b6dc;
      }
    }
    else {
      if (iVar7 == 0xb4) {
        fVar6 = (float)ACos(extraout_s0);
        piVar10 = *(int **)(iVar11 + iVar12);
        fVar6 = fVar6 * DAT_0005b808;
        fVar19 = extraout_s0_03;
        fVar15 = extraout_s1_03;
      }
      else {
        if (iVar7 != 0x10e) goto LAB_0005b6f4;
        fVar6 = (float)ACos(extraout_s0);
        piVar10 = *(int **)(iVar11 + iVar12);
        fVar6 = fVar6 * DAT_0005b808;
        fVar19 = extraout_s0_01;
        fVar15 = extraout_s1_01;
      }
      *(float *)(iVar18 + 0x48) = fVar6 / DAT_0005b7fc + DAT_0005b800;
      iVar18 = *piVar10;
    }
  }
LAB_0005b6f4:
  fVar6 = DAT_0005b7cc;
  fVar17 = *(float *)(iVar18 + 0x48);
  if (DAT_0005b7cc < fVar17) {
    *(float *)(iVar18 + 0x48) = DAT_0005b7cc;
    fVar17 = fVar6;
LAB_0005b710:
    if (DAT_0005b808 <= fVar17) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
LAB_0005b724:
    if (bVar1) {
      *(float *)(iVar18 + 0x48) = fVar17 + DAT_0005b7f8;
    }
  }
  else {
    if (DAT_0005b7f4 <= fVar17) {
      if (fVar17 <= DAT_0005b804) goto LAB_0005b710;
      fVar17 = fVar17 - DAT_0005b7f8;
      bVar1 = fVar17 < DAT_0005b808;
      *(float *)(iVar18 + 0x48) = fVar17;
      goto LAB_0005b724;
    }
    *(float *)(iVar18 + 0x48) = DAT_0005b7f4;
  }
  cRMouse::ClickScreen((bool)((char)iVar18 + '('),fVar19,fVar15);
LAB_0005b620:
  OFOrientation();
  return;
}
