/*
 * mangled: _ZN10cRBackdrop10SetDistortEf
 * demangled: cRBackdrop::SetDistort(float)
 * address: 00041630
 * size: 468
 */

/* cRBackdrop::SetDistort(float) */

void __thiscall cRBackdrop::SetDistort(cRBackdrop *this,float param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  cRBackdrop *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint in_fpscr;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  ulonglong uVar13;

  uVar6 = 0;
  *(float *)(this + 0x6c) = param_1;
  uVar13 = (ulonglong)(uint)(param_1 * 0.9);
  do {
    uVar7 = 1 - uVar6;
    if (1 < uVar6) {
      uVar7 = 0;
    }
    iVar5 = 0;
    fVar8 = (float)VectorSignedToFloat(uVar6 - 5,(byte)(in_fpscr >> 0x16) & 3);
    pcVar4 = this + uVar6 * 0x1b8 + 0x88;
    fVar8 = fVar8 / 5.0;
    do {
      uVar3 = uVar7;
      if (iVar5 == 0) {
        uVar3 = uVar7 | 1;
      }
      if ((uVar3 == 0) && (uVar6 != 10 && iVar5 != 10)) {
        uVar2 = gRMathRand2();
        fVar10 = 3.0517578e-05;
        fVar12 = 6.2831855;
        fVar11 = 3.0;
        fVar9 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(pcVar4 + -0x18) = fVar9 * 3.0517578e-05 * 6.2831855;
        uVar2 = gRMathRand2();
        fVar9 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
        in_fpscr = in_fpscr & 0xfffffff |
                   (uint)(fVar9 * fVar10 + fVar9 * fVar10 + fVar11 == 0.0) << 0x1e;
        if (SUB41(in_fpscr >> 0x1e,0)) {
          fVar12 = 0.0;
        }
        else {
          uVar2 = gRMathRand2();
          fVar9 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
          fVar12 = (1.0 / ((fVar9 * fVar10 + fVar9 * fVar10 + fVar11) * 60.0)) * fVar12;
        }
        *(float *)(pcVar4 + -0x14) = fVar12;
        uVar2 = gRMathRand2();
        fVar10 = 16384.0;
        fVar12 = 6.1035156e-05;
        fVar9 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(pcVar4 + -0x10) = (fVar9 - 16384.0) * 6.1035156e-05 * (float)uVar13;
        uVar2 = gRMathRand2();
        fVar9 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(pcVar4 + -0xc) = (float)uVar13 * (fVar9 - fVar10) * fVar12;
      }
      else {
        *(undefined4 *)(pcVar4 + -0x18) = 0;
        *(undefined4 *)(pcVar4 + -0x14) = 0;
        *(undefined4 *)(pcVar4 + -0x10) = 0;
        *(undefined4 *)(pcVar4 + -0xc) = 0;
      }
      *(undefined4 *)(pcVar4 + 8) = 0;
      fVar9 = (float)VectorSignedToFloat(iVar5 + -5,(byte)(in_fpscr >> 0x16) & 3);
      iVar1 = iVar5 * 0x28;
      *(float *)(pcVar4 + 4) = fVar8;
      iVar5 = iVar5 + 1;
      *(float *)pcVar4 = fVar9 / 5.0;
      uVar2 = tVector::Normalize((tVector *)(this + iVar1 + uVar6 * 0x1b8 + 0x88));
      *(undefined4 *)(pcVar4 + 0xc) = uVar2;
      pcVar4 = pcVar4 + 0x28;
    } while (iVar5 != 0xb);
    uVar6 = uVar6 + 1;
  } while (uVar6 != 0xb);
  return;
}
