/*
 * mangled: _ZN10cRBackdrop10SetDistortEf
 * demangled: cRBackdrop::SetDistort(float)
 * address: 0003e46c
 * size: 516
 */

/* cRBackdrop::SetDistort(float) */

float __thiscall cRBackdrop::SetDistort(cRBackdrop *this,float param_1)

{
  undefined4 uVar1;
  float in_r1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint in_fpscr;
  float extraout_s0;
  float fVar11;
  float fVar12;
  float fVar13;

  uVar5 = *(uint *)(this + 0x3c);
  *(float *)(this + 0x78) = in_r1;
  if (-1 < (int)uVar5) {
    uVar8 = 0;
    do {
      uVar9 = 1 - uVar8;
      if (1 < uVar8) {
        uVar9 = 0;
      }
      uVar7 = 0;
      do {
        uVar2 = uVar9;
        if (uVar7 == 0) {
          uVar2 = uVar9 | 1;
        }
        iVar4 = uVar5 * uVar8 + uVar8 + uVar7;
        if (((uVar2 == 0) && (uVar7 != uVar5)) && (uVar8 != uVar5)) {
          iVar6 = *(int *)(this + 0x7c);
          uVar1 = gRMathRand2();
          iVar10 = *(int *)(this + 0x7c);
          iVar3 = iVar4 * 0x28;
          fVar11 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(iVar6 + iVar4 * 0x28) = fVar11 * 3.0517578e-05 * 6.2831855;
          uVar1 = gRMathRand2();
          fVar11 = 0.0;
          fVar12 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
          in_fpscr = in_fpscr & 0xfffffff |
                     (uint)(fVar12 * 3.0517578e-05 + fVar12 * 3.0517578e-05 + 3.0 == 0.0) << 0x1e;
          if (!SUB41(in_fpscr >> 0x1e,0)) {
            uVar1 = gRMathRand2();
            fVar11 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
            fVar11 = (1.0 / ((fVar11 * 3.0517578e-05 + fVar11 * 3.0517578e-05 + 3.0) * 60.0)) *
                     6.2831855;
          }
          *(float *)(iVar10 + iVar3 + 4) = fVar11;
          iVar4 = *(int *)(this + 0x7c);
          uVar1 = gRMathRand2();
          iVar10 = *(int *)(this + 0x7c);
          fVar11 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(iVar4 + iVar3 + 8) = (fVar11 - 16384.0) * 6.1035156e-05 * in_r1 * 0.9;
          uVar1 = gRMathRand2();
          uVar5 = *(uint *)(this + 0x3c);
          iVar6 = *(int *)(this + 0x7c) + iVar3;
          fVar11 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(iVar10 + iVar3 + 0xc) = in_r1 * 0.9 * (fVar11 - 16384.0) * 6.1035156e-05;
        }
        else {
          iVar3 = *(int *)(this + 0x7c);
          iVar6 = iVar3 + iVar4 * 0x28;
          *(undefined4 *)(iVar6 + 4) = 0;
          *(undefined4 *)(iVar3 + iVar4 * 0x28) = 0;
          *(undefined4 *)(iVar6 + 8) = 0;
          *(undefined4 *)(iVar6 + 0xc) = 0;
        }
        fVar11 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
        *(undefined4 *)(iVar6 + 0x20) = 0;
        iVar4 = uVar7 + -((int)uVar5 / 2);
        uVar7 = uVar7 + 1;
        fVar12 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
        fVar13 = (float)VectorSignedToFloat(uVar8 + -((int)uVar5 / 2),(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(iVar6 + 0x1c) = fVar13 / (fVar11 * 0.5);
        *(float *)(iVar6 + 0x18) = fVar12 / (fVar11 * 0.5);
        uVar1 = tVector::Normalize((tVector *)(iVar6 + 0x18));
        uVar5 = *(uint *)(this + 0x3c);
        *(undefined4 *)(iVar6 + 0x24) = uVar1;
      } while ((int)uVar7 <= (int)uVar5);
      uVar8 = uVar8 + 1;
      param_1 = extraout_s0;
    } while (((int)uVar8 <= (int)uVar5) && (-1 < (int)uVar5));
  }
  return param_1;
}
