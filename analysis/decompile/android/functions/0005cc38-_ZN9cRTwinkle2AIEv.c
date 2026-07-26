/*
 * mangled: _ZN9cRTwinkle2AIEv
 * demangled: cRTwinkle::AI()
 * address: 0005cc38
 * size: 924
 */

/* cRTwinkle::AI() */

void __thiscall cRTwinkle::AI(cRTwinkle *this)

{
  byte bVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  uint in_fpscr;
  uint uVar7;
  uint uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;

  fVar9 = DAT_0005cfd4;
  fVar10 = *(float *)(this + 0x18) + *(float *)(this + 0x1c);
  uVar8 = in_fpscr & 0xfffffff | (uint)(fVar10 < DAT_0005cfd4) << 0x1f |
          (uint)(fVar10 == DAT_0005cfd4) << 0x1e;
  uVar7 = uVar8 | (uint)(NAN(fVar10) || NAN(DAT_0005cfd4)) << 0x1c;
  *(float *)(this + 0x18) = fVar10;
  bVar1 = (byte)(uVar8 >> 0x18);
  if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar7 >> 0x1c) & 1)) {
    uVar7 = in_fpscr & 0xfffffff | (uint)(fVar10 < 0.0) << 0x1f;
    if (SUB41(uVar7 >> 0x1f,0)) {
      *(float *)(this + 0x18) = fVar10 + fVar9;
    }
  }
  else {
    *(float *)(this + 0x18) = fVar10 - fVar9;
  }
  fVar9 = DAT_0005cfd8;
  iVar6 = *(int *)this;
  if (iVar6 != 2) {
    if (iVar6 == 4) {
      *(float *)(this + 0x10) =
           *(float *)(this + 0x10) +
           (*(float *)(this + 0x14) - *(float *)(this + 0x10)) * DAT_0005cff8;
      Draw();
      fVar9 = DAT_0005cfdc;
      fVar10 = *(float *)(this + 0x14) - *(float *)(this + 0x10);
      if (fVar10 < 0.0) {
        uVar8 = uVar7 & 0xfffffff | (uint)(fVar10 < DAT_0005d010) << 0x1f |
                (uint)(fVar10 == DAT_0005d010) << 0x1e;
        uVar7 = uVar8 | (uint)(NAN(fVar10) || NAN(DAT_0005d010)) << 0x1c;
        bVar1 = (byte)(uVar8 >> 0x18);
        bVar2 = !(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar7 >> 0x1c) & 1);
      }
      else {
        uVar7 = uVar7 & 0xfffffff | (uint)(fVar10 < DAT_0005d00c) << 0x1f;
        if (SUB41(uVar7 >> 0x1f,0)) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
      }
      if (bVar2) {
        *(float *)(this + 0x10) = DAT_0005cfdc;
        *(float *)(this + 8) = fVar9;
        *(undefined4 *)this = 1;
        fVar3 = DAT_0005d00c;
        uVar5 = gRMathRand2();
        fVar10 = DAT_0005cffc;
        fVar12 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
        uVar7 = uVar7 & 0xfffffff | (uint)(fVar3 + fVar12 * DAT_0005cffc == fVar9) << 0x1e;
        if (SUB41(uVar7 >> 0x1e,0)) {
          *(float *)(this + 0xc) = fVar9;
        }
        else {
          uVar5 = gRMathRand2();
          fVar9 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
          *(float *)(this + 0xc) = DAT_0005cfd8 / ((fVar3 + fVar9 * fVar10) * DAT_0005d014);
        }
      }
    }
    else if ((iVar6 == 1) && ((*(uint *)(*(int *)(this + 0x2c) + 0x194) & 0x8002) == 2)) {
      fVar10 = *(float *)(this + 8) + *(float *)(this + 0xc);
      uVar7 = uVar7 & 0xfffffff | (uint)(fVar10 < DAT_0005cfd8) << 0x1f |
              (uint)(fVar10 == DAT_0005cfd8) << 0x1e;
      uVar8 = uVar7 | (uint)(NAN(fVar10) || NAN(DAT_0005cfd8)) << 0x1c;
      *(float *)(this + 8) = fVar10;
      uVar5 = DAT_0005cfe0;
      fVar10 = DAT_0005cfdc;
      bVar1 = (byte)(uVar7 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar8 >> 0x1c) & 1)) {
        *(undefined4 *)this = 2;
        *(undefined4 *)(this + 0x14) = uVar5;
        *(float *)(this + 0x10) = fVar10;
        fVar3 = DAT_0005cfe4;
        uVar5 = gRMathRand2();
        fVar13 = DAT_0005cff0;
        fVar4 = DAT_0005cfec;
        fVar12 = DAT_0005cfe8;
        fVar11 = (float)VectorSignedToFloat(uVar5,(byte)(uVar8 >> 0x16) & 3);
        *(float *)(this + 0x18) = (fVar11 - fVar3) * DAT_0005cfe8 * DAT_0005cfec;
        uVar5 = gRMathRand2();
        fVar11 = (float)VectorSignedToFloat(uVar5,(byte)(uVar8 >> 0x16) & 3);
        uVar7 = uVar8 & 0xfffffff | (uint)(fVar13 + (fVar11 - fVar3) * fVar12 == fVar10) << 0x1e;
        if (!SUB41(uVar7 >> 0x1e,0)) {
          uVar5 = gRMathRand2();
          fVar10 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
          fVar9 = fVar9 / ((fVar13 + (fVar10 - fVar3) * fVar12) * DAT_0005d014);
          fVar10 = (fVar9 + fVar9) * fVar4;
        }
        uVar5 = gRMathRand2();
        fVar3 = DAT_0005cfe8;
        fVar9 = DAT_0005cfe4;
        fVar12 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
        uVar7 = uVar7 & 0xfffffff | (uint)((fVar12 - DAT_0005cfe4) * DAT_0005cfe8 < 0.0) << 0x1f;
        fVar12 = DAT_0005cff4;
        if (!SUB41(uVar7 >> 0x1f,0)) {
          uVar5 = gRMathRand2();
          fVar12 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
          uVar7 = uVar7 & 0xfffffff | (uint)((fVar12 - fVar9) * fVar3 == 0.0) << 0x1e;
          fVar12 = (float)VectorSignedToFloat((uint)!SUB41(uVar7 >> 0x1e,0),
                                              (byte)(uVar7 >> 0x16) & 3);
        }
        *(float *)(this + 8) = DAT_0005cfdc;
        *(float *)(this + 0xc) = DAT_0005cfd8;
        fVar4 = DAT_0005d000;
        fVar3 = DAT_0005cffc;
        fVar9 = DAT_0005cff8;
        *(float *)(this + 0x1c) = fVar10 * fVar12;
        fVar12 = *(float *)(*(int *)(this + 0x2c) + 0x23c);
        fVar13 = *(float *)(*(int *)(this + 0x2c) + 0x22c);
        uVar5 = gRMathRand2();
        iVar6 = *(int *)(this + 0x2c);
        fVar10 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
        *(float *)(this + 0x20) =
             fVar13 + fVar9 * fVar12 + fVar10 * fVar3 * fVar4 * *(float *)(iVar6 + 0x23c);
        fVar12 = *(float *)(iVar6 + 0x240);
        fVar13 = *(float *)(iVar6 + 0x230);
        uVar5 = gRMathRand2();
        fVar10 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
        *(float *)(this + 0x24) =
             fVar13 + fVar9 * fVar12 +
             fVar10 * fVar3 * fVar4 * *(float *)(*(int *)(this + 0x2c) + 0x240);
        uVar5 = gRMathRand2();
        fVar9 = (float)VectorSignedToFloat(uVar5,(byte)(uVar7 >> 0x16) & 3);
        *(float *)(this + 0x28) =
             DAT_0005d004 + (fVar9 - DAT_0005cfe4) * DAT_0005cfe8 * DAT_0005d008;
      }
    }
    return;
  }
  fVar9 = *(float *)(this + 0x10) +
          (*(float *)(this + 0x14) - *(float *)(this + 0x10)) * DAT_0005cff8;
  fVar10 = *(float *)(this + 0x14) - fVar9;
  *(float *)(this + 0x10) = fVar9;
  if (fVar10 < 0.0) {
    bVar2 = DAT_0005d010 < fVar10;
  }
  else if (DAT_0005d00c <= fVar10) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (bVar2) {
    *(float *)(this + 0x14) = DAT_0005cfdc;
    *(undefined4 *)this = 4;
  }
  Draw();
  return;
}
