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
  undefined4 uVar3;
  int iVar4;
  uint in_fpscr;
  uint uVar5;
  uint uVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  fVar7 = *(float *)(this + 0x18) + *(float *)(this + 0x1c);
  uVar6 = in_fpscr & 0xfffffff | (uint)(fVar7 < 6.2831855) << 0x1f |
          (uint)(fVar7 == 6.2831855) << 0x1e;
  uVar5 = uVar6 | (uint)NAN(fVar7) << 0x1c;
  *(float *)(this + 0x18) = fVar7;
  bVar1 = (byte)(uVar6 >> 0x18);
  if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar5 >> 0x1c) & 1)) {
    uVar5 = in_fpscr & 0xfffffff | (uint)(fVar7 < 0.0) << 0x1f;
    if (SUB41(uVar5 >> 0x1f,0)) {
      *(float *)(this + 0x18) = fVar7 + 6.2831855;
    }
  }
  else {
    *(float *)(this + 0x18) = fVar7 - 6.2831855;
  }
  iVar4 = *(int *)this;
  if (iVar4 != 2) {
    if (iVar4 == 4) {
      *(float *)(this + 0x10) =
           *(float *)(this + 0x10) + (*(float *)(this + 0x14) - *(float *)(this + 0x10)) * 0.1;
      Draw();
      fVar7 = *(float *)(this + 0x14) - *(float *)(this + 0x10);
      if (fVar7 < 0.0) {
        uVar6 = uVar5 & 0xfffffff | (uint)(fVar7 < -0.01) << 0x1f | (uint)(fVar7 == -0.01) << 0x1e;
        uVar5 = uVar6 | (uint)NAN(fVar7) << 0x1c;
        bVar1 = (byte)(uVar6 >> 0x18);
        bVar2 = !(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar5 >> 0x1c) & 1);
      }
      else {
        uVar5 = uVar5 & 0xfffffff | (uint)(fVar7 < 0.01) << 0x1f;
        if (SUB41(uVar5 >> 0x1f,0)) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
      }
      if (bVar2) {
        *(undefined4 *)(this + 0x10) = 0;
        *(undefined4 *)(this + 8) = 0;
        *(undefined4 *)this = 1;
        uVar3 = gRMathRand2();
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
        uVar5 = uVar5 & 0xfffffff | (uint)(fVar7 * 3.0517578e-05 + 0.01 == 0.0) << 0x1e;
        if (SUB41(uVar5 >> 0x1e,0)) {
          *(undefined4 *)(this + 0xc) = 0;
        }
        else {
          uVar3 = gRMathRand2();
          fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
          *(float *)(this + 0xc) = 1.0 / ((fVar7 * 3.0517578e-05 + 0.01) * 60.0);
        }
      }
    }
    else if ((iVar4 == 1) && ((*(uint *)(*(int *)(this + 0x2c) + 0x194) & 0x8002) == 2)) {
      fVar7 = *(float *)(this + 8) + *(float *)(this + 0xc);
      uVar5 = uVar5 & 0xfffffff | (uint)(fVar7 < 1.0) << 0x1f | (uint)(fVar7 == 1.0) << 0x1e;
      uVar6 = uVar5 | (uint)NAN(fVar7) << 0x1c;
      *(float *)(this + 8) = fVar7;
      bVar1 = (byte)(uVar5 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar6 >> 0x1c) & 1)) {
        fVar9 = 0.0;
        *(undefined4 *)this = 2;
        *(undefined4 *)(this + 0x14) = 0x3f666666;
        *(undefined4 *)(this + 0x10) = 0;
        uVar3 = gRMathRand2();
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar6 >> 0x16) & 3);
        *(float *)(this + 0x18) = (fVar7 - 16384.0) * 6.1035156e-05 * 3.1415927;
        uVar3 = gRMathRand2();
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar6 >> 0x16) & 3);
        uVar5 = uVar6 & 0xfffffff | (uint)((fVar7 - 16384.0) * 6.1035156e-05 + 5.0 == 0.0) << 0x1e;
        if (!SUB41(uVar5 >> 0x1e,0)) {
          uVar3 = gRMathRand2();
          fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
          fVar7 = 1.0 / (((fVar7 - 16384.0) * 6.1035156e-05 + 5.0) * 60.0);
          fVar9 = (fVar7 + fVar7) * 3.1415927;
        }
        uVar3 = gRMathRand2();
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
        uVar5 = uVar5 & 0xfffffff | (uint)((fVar7 - 16384.0) * 6.1035156e-05 < 0.0) << 0x1f;
        if (SUB41(uVar5 >> 0x1f,0)) {
          fVar7 = -1.0;
        }
        else {
          uVar3 = gRMathRand2();
          fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
          uVar5 = uVar5 & 0xfffffff | (uint)((fVar7 - 16384.0) * 6.1035156e-05 == 0.0) << 0x1e;
          fVar7 = (float)VectorSignedToFloat((uint)!SUB41(uVar5 >> 0x1e,0),(byte)(uVar5 >> 0x16) & 3
                                            );
        }
        *(undefined4 *)(this + 8) = 0;
        *(undefined4 *)(this + 0xc) = 0x3f800000;
        *(float *)(this + 0x1c) = fVar9 * fVar7;
        fVar9 = *(float *)(*(int *)(this + 0x2c) + 0x23c);
        fVar8 = *(float *)(*(int *)(this + 0x2c) + 0x22c);
        uVar3 = gRMathRand2();
        iVar4 = *(int *)(this + 0x2c);
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
        *(float *)(this + 0x20) =
             fVar8 + fVar9 * 0.1 + fVar7 * 3.0517578e-05 * *(float *)(iVar4 + 0x23c) * 0.8;
        fVar9 = *(float *)(iVar4 + 0x240);
        fVar8 = *(float *)(iVar4 + 0x230);
        uVar3 = gRMathRand2();
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
        *(float *)(this + 0x24) =
             fVar8 + fVar9 * 0.1 +
             fVar7 * 3.0517578e-05 * *(float *)(*(int *)(this + 0x2c) + 0x240) * 0.8;
        uVar3 = gRMathRand2();
        fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(uVar5 >> 0x16) & 3);
        *(float *)(this + 0x28) = (fVar7 - 16384.0) * 6.1035156e-05 * 12.0 + 25.0;
      }
    }
    return;
  }
  fVar7 = *(float *)(this + 0x10) + (*(float *)(this + 0x14) - *(float *)(this + 0x10)) * 0.1;
  fVar9 = *(float *)(this + 0x14) - fVar7;
  *(float *)(this + 0x10) = fVar7;
  if (fVar9 < 0.0) {
    bVar2 = -0.01 < fVar9;
  }
  else if (0.01 <= fVar9) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (bVar2) {
    *(undefined4 *)(this + 0x14) = 0;
    *(undefined4 *)this = 4;
  }
  Draw();
  return;
}
