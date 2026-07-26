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
  int in_r0;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  uint in_fpscr;
  uint uVar11;
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
  float extraout_s1_02;
  float extraout_s1_03;
  double dVar12;
  float fVar13;
  int iVar14;

  if ((DAT_0038ca55 == '\0') || (10 < gAccelerometerCounter)) {
    wprintf("!@#");
    iVar9 = Game;
    *(undefined4 *)(Game + 0x48) = 0;
    *(undefined4 *)(iVar9 + 0x40) = 0x43870000;
    *(undefined4 *)(iVar9 + 0x3c) = 0x43870000;
    OFOrientation();
    return;
  }
  fVar4 = (float)ATan(in_s0,in_s1);
  fVar13 = *(float *)(in_r0 + 8);
  iVar9 = Game;
  if (fVar13 < 0.0) {
    uVar11 = in_fpscr & 0xfffffff | (uint)(fVar13 < -0.75) << 0x1f | (uint)(fVar13 == -0.75) << 0x1e
    ;
    bVar3 = (byte)(uVar11 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && (bool)(bVar3 >> 7) == NAN(fVar13)) goto LAB_0005b4ac;
  }
  else {
    uVar11 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.75) << 0x1f;
    if (SUB41(uVar11 >> 0x1f,0)) {
LAB_0005b4ac:
      fVar13 = (float)VectorSignedToFloat((int)((fVar4 * 180.0) / 3.1415927 + 360.0) % 0x168,
                                          (byte)(uVar11 >> 0x16) & 3);
      iVar6 = (int)((fVar13 + 45.0) / 90.0) % 4;
      fVar4 = (float)VectorSignedToFloat(iVar6 * 0x5a,(byte)(uVar11 >> 0x16) & 3);
      pfVar10 = (float *)(in_r0 + iVar6 * 4 + 0xc);
      iVar8 = 0;
      iVar14 = (int)(fVar13 - fVar4);
      if (iVar14 < 0) {
        iVar14 = -iVar14;
      }
      iVar7 = in_r0;
      if (0xb4 < iVar14) {
        iVar14 = 0x168 - iVar14;
      }
      do {
        if (iVar6 == iVar8) {
          fVar4 = *pfVar10;
          uVar2 = uVar11 & 0xfffffff;
          uVar11 = uVar2 | (uint)(fVar4 < 100.0) << 0x1f;
          if (SUB41(uVar11 >> 0x1f,0)) {
            dVar12 = (double)VectorSignedToFloat(iVar14,(byte)(uVar11 >> 0x16) & 3);
            uVar11 = uVar2 | (uint)(dVar12 < 22.5) << 0x1f;
            if (SUB41(uVar11 >> 0x1f,0)) {
              *pfVar10 = fVar4 + 1.0;
            }
          }
        }
        else {
          fVar4 = *(float *)(iVar7 + 0xc);
          uVar11 = uVar11 & 0xfffffff | (uint)(fVar4 < 0.0) << 0x1f | (uint)(fVar4 == 0.0) << 0x1e;
          bVar3 = (byte)(uVar11 >> 0x18);
          if (!(bool)(bVar3 >> 6 & 1) && (bool)(bVar3 >> 7) == NAN(fVar4)) {
            *(undefined4 *)(iVar7 + 0xc) = 0;
          }
        }
        iVar9 = Game;
        iVar8 = iVar8 + 1;
        iVar7 = iVar7 + 4;
      } while (iVar8 != 4);
      if ((90.0 < *(float *)(in_r0 + 0x18)) && (*(float *)(Game + 0x40) != 270.0)) {
        *(undefined4 *)(Game + 0x40) = 0x43870000;
      }
    }
  }
  gConfig._200_4_ = *(float *)(iVar9 + 0x3c);
  if (((*(int *)(iVar9 + 0x718fc) == 2 || *(int *)(iVar9 + 0x718fc) == 4) && (gConfig._8_4_ == 1))
     && (gDirectory[iVar9 + 0x2544] == '\0')) {
    if ((float)gConfig._200_4_ == 90.0) {
      *(undefined4 *)(iVar9 + 0x4c) = 0x3f800000;
    }
    else {
      if ((float)gConfig._200_4_ != 270.0) goto LAB_0005b5fc;
      *(undefined4 *)(iVar9 + 0x4c) = 0xbf800000;
    }
  }
  else {
LAB_0005b5fc:
    *(undefined4 *)(iVar9 + 0x4c) = 0;
  }
  if (((*(int *)(iVar9 + 0x718fc) != 2) || (gConfig._8_4_ != 0)) ||
     (gDirectory[iVar9 + 0x2544] != '\0')) {
    *(undefined4 *)(iVar9 + 0x48) = 0;
    goto LAB_0005b620;
  }
  iVar14 = (int)*(float *)(iVar9 + 0x3c);
  if (iVar14 == 0x5a) {
    fVar5 = (float)ACos(extraout_s0);
    fVar4 = extraout_s0_02;
    fVar13 = extraout_s1_02;
LAB_0005b6dc:
    *(float *)(iVar9 + 0x48) = (fVar5 * 180.0) / 3.1415927 - 90.0;
    iVar9 = Game;
  }
  else {
    fVar4 = extraout_s0;
    fVar13 = extraout_s1;
    if (iVar14 < 0x5b) {
      if (iVar14 == 0) {
        fVar5 = (float)ACos(extraout_s0);
        fVar4 = extraout_s0_00;
        fVar13 = extraout_s1_00;
        goto LAB_0005b6dc;
      }
    }
    else {
      if (iVar14 == 0xb4) {
        fVar5 = (float)ACos(extraout_s0);
        fVar4 = extraout_s0_03;
        fVar13 = extraout_s1_03;
      }
      else {
        if (iVar14 != 0x10e) goto LAB_0005b6f4;
        fVar5 = (float)ACos(extraout_s0);
        fVar4 = extraout_s0_01;
        fVar13 = extraout_s1_01;
      }
      *(float *)(iVar9 + 0x48) = (fVar5 * -180.0) / 3.1415927 + 90.0;
      iVar9 = Game;
    }
  }
LAB_0005b6f4:
  fVar5 = *(float *)(iVar9 + 0x48);
  if (80.0 < fVar5) {
    *(undefined4 *)(iVar9 + 0x48) = 0x42a00000;
    fVar5 = 80.0;
LAB_0005b710:
    if (-180.0 <= fVar5) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
LAB_0005b724:
    if (bVar1) {
      *(float *)(iVar9 + 0x48) = fVar5 + 360.0;
    }
  }
  else {
    if (-80.0 <= fVar5) {
      if (fVar5 <= 180.0) goto LAB_0005b710;
      fVar5 = fVar5 - 360.0;
      bVar1 = fVar5 < -180.0;
      *(float *)(iVar9 + 0x48) = fVar5;
      goto LAB_0005b724;
    }
    *(undefined4 *)(iVar9 + 0x48) = 0xc2a00000;
  }
  cRMouse::ClickScreen((bool)((char)iVar9 + '('),fVar4,fVar13);
LAB_0005b620:
  OFOrientation();
  return;
}
