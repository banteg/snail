/*
 * mangled: _ZN9cRTwinkle2AIEv
 * demangled: cRTwinkle::AI()
 * address: 00039fa4
 * size: 960
 */

/* cRTwinkle::AI() */

void __thiscall cRTwinkle::AI(cRTwinkle *this)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  uint in_fpscr;
  uint uVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  float local_3c;
  tColour atStack_38 [40];

  fVar8 = *(float *)(this + 0x18) + *(float *)(this + 0x1c);
  uVar3 = in_fpscr & 0xfffffff | (uint)(fVar8 < 6.2831855) << 0x1f |
          (uint)(fVar8 == 6.2831855) << 0x1e;
  uVar6 = uVar3 | (uint)NAN(fVar8) << 0x1c;
  *(float *)(this + 0x18) = fVar8;
  bVar1 = (byte)(uVar3 >> 0x18);
  if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar6 >> 0x1c) & 1)) {
    uVar6 = in_fpscr & 0xfffffff | (uint)(fVar8 < 0.0) << 0x1f;
    if (SUB41(uVar6 >> 0x1f,0)) {
      *(float *)(this + 0x18) = fVar8 + 6.2831855;
    }
  }
  else {
    *(float *)(this + 0x18) = fVar8 - 6.2831855;
  }
  uVar3 = *(uint *)this;
  if (uVar3 == 2) {
    fVar8 = *(float *)(this + 0x10) + (*(float *)(this + 0x14) - *(float *)(this + 0x10)) * 0.1;
    fVar13 = *(float *)(this + 0x14) - fVar8;
    *(float *)(this + 0x10) = fVar8;
    if (fVar13 < 0.0) {
      bVar5 = -0.01 < fVar13;
    }
    else if (0.01 <= fVar13) {
      bVar5 = false;
    }
    else {
      bVar5 = true;
    }
    if (bVar5) {
      *(undefined4 *)(this + 0x14) = 0;
      *(undefined4 *)this = 4;
    }
    tColour::tColour(atStack_38);
  }
  else if (uVar3 == 4) {
    *(float *)(this + 0x10) =
         *(float *)(this + 0x10) + (*(float *)(this + 0x14) - *(float *)(this + 0x10)) * 0.1;
    tColour::tColour((tColour *)&local_48);
    iVar4 = *(int *)(this + 0x2c);
    local_48 = *(undefined4 *)(iVar4 + 0x1b0);
    uStack_44 = *(undefined4 *)(iVar4 + 0x1b4);
    uStack_40 = *(undefined4 *)(iVar4 + 0x1b8);
    local_3c = *(float *)(this + 0x10) * *(float *)(iVar4 + 0x1bc);
    fVar8 = *(float *)(this + 0x14) - *(float *)(this + 0x10);
    if (fVar8 < 0.0) {
      uVar3 = uVar6 & 0xfffffff | (uint)(fVar8 < -0.01) << 0x1f | (uint)(fVar8 == -0.01) << 0x1e;
      uVar6 = uVar3 | (uint)NAN(fVar8) << 0x1c;
      bVar1 = (byte)(uVar3 >> 0x18);
      bVar5 = !(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar6 >> 0x1c) & 1);
    }
    else {
      uVar6 = uVar6 & 0xfffffff | (uint)(fVar8 < 0.01) << 0x1f;
      if (SUB41(uVar6 >> 0x1f,0)) {
        bVar5 = true;
      }
      else {
        bVar5 = false;
      }
    }
    if (bVar5) {
      *(undefined4 *)(this + 0x10) = 0;
      *(undefined4 *)this = 1;
      *(undefined4 *)(this + 8) = 0;
      uVar2 = gRMathRand2();
      fVar13 = 0.01;
      fVar9 = 3.0517578e-05;
      fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
      uVar6 = uVar6 & 0xfffffff | (uint)(fVar8 * 3.0517578e-05 + 0.01 == 0.0) << 0x1e;
      if (SUB41(uVar6 >> 0x1e,0)) {
        *(undefined4 *)(this + 0xc) = 0;
      }
      else {
        uVar2 = gRMathRand2();
        fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
        *(float *)(this + 0xc) = 1.0 / ((fVar13 + fVar8 * fVar9) * 60.0);
      }
    }
  }
  else {
    bVar5 = uVar3 == 1;
    if (bVar5) {
      uVar3 = *(uint *)(*(int *)(this + 0x2c) + 0x194) & 0x8002;
    }
    if (bVar5 && uVar3 == 2) {
      fVar13 = 1.0;
      fVar8 = *(float *)(this + 8) + *(float *)(this + 0xc);
      uVar6 = uVar6 & 0xfffffff | (uint)(fVar8 < 1.0) << 0x1f | (uint)(fVar8 == 1.0) << 0x1e;
      uVar7 = uVar6 | (uint)NAN(fVar8) << 0x1c;
      *(float *)(this + 8) = fVar8;
      bVar1 = (byte)(uVar6 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar7 >> 0x1c) & 1)) {
        *(uint *)this = uVar3;
        *(undefined4 *)(this + 0x10) = 0;
        *(undefined4 *)(this + 0x14) = 0x3f666666;
        uVar2 = gRMathRand2();
        fVar10 = 6.1035156e-05;
        fVar11 = 16384.0;
        fVar12 = 3.1415927;
        fVar9 = 5.0;
        fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar7 >> 0x16) & 3);
        *(float *)(this + 0x18) = (fVar8 - 16384.0) * 6.1035156e-05 * 3.1415927;
        uVar2 = gRMathRand2();
        fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar7 >> 0x16) & 3);
        uVar6 = uVar7 & 0xfffffff | (uint)(fVar9 + (fVar8 - fVar11) * fVar10 == 0.0) << 0x1e;
        if (SUB41(uVar6 >> 0x1e,0)) {
          fVar12 = 0.0;
        }
        else {
          uVar2 = gRMathRand2();
          fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
          fVar13 = fVar13 / ((fVar9 + (fVar8 - fVar11) * fVar10) * 60.0);
          fVar12 = (fVar13 + fVar13) * fVar12;
        }
        uVar2 = gRMathRand2();
        fVar9 = 16384.0;
        fVar13 = 6.1035156e-05;
        fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
        uVar6 = uVar6 & 0xfffffff | (uint)((fVar8 - 16384.0) * 6.1035156e-05 < 0.0) << 0x1f;
        if (SUB41(uVar6 >> 0x1f,0)) {
          fVar8 = -1.0;
        }
        else {
          uVar2 = gRMathRand2();
          fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
          uVar6 = uVar6 & 0xfffffff | (uint)((fVar8 - fVar9) * fVar13 == 0.0) << 0x1e;
          fVar8 = 0.0;
          if (!SUB41(uVar6 >> 0x1e,0)) {
            fVar8 = 1.0;
          }
        }
        *(undefined4 *)(this + 8) = 0;
        *(undefined4 *)(this + 0xc) = 0x3f800000;
        fVar11 = 0.1;
        fVar9 = 3.0517578e-05;
        *(float *)(this + 0x1c) = fVar12 * fVar8;
        fVar10 = 0.8;
        fVar13 = *(float *)(*(int *)(this + 0x2c) + 0x22c) +
                 *(float *)(*(int *)(this + 0x2c) + 0x23c) * 0.1;
        uVar2 = gRMathRand2();
        iVar4 = *(int *)(this + 0x2c);
        fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
        *(float *)(this + 0x20) = fVar13 + fVar8 * fVar9 * *(float *)(iVar4 + 0x23c) * fVar10;
        fVar13 = *(float *)(iVar4 + 0x230) + *(float *)(iVar4 + 0x240) * fVar11;
        uVar2 = gRMathRand2();
        fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
        *(float *)(this + 0x24) =
             fVar13 + fVar8 * fVar9 * *(float *)(*(int *)(this + 0x2c) + 0x240) * fVar10;
        uVar2 = gRMathRand2();
        fVar8 = (float)VectorSignedToFloat(uVar2,(byte)(uVar6 >> 0x16) & 3);
        *(float *)(this + 0x28) = (fVar8 - 16384.0) * 6.1035156e-05 * 12.0 + 25.0;
      }
    }
  }
  return;
}
