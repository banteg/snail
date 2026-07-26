/*
 * mangled: _ZN10cRBackdrop10SetDistortEf
 * demangled: cRBackdrop::SetDistort(float)
 * address: 0003e46c
 * size: 516
 */

/* cRBackdrop::SetDistort(float) */

float __thiscall cRBackdrop::SetDistort(cRBackdrop *this,float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  float in_r1;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  uint in_fpscr;
  float extraout_s0;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;

  uVar14 = *(uint *)(this + 0x3c);
  *(float *)(this + 0x78) = in_r1;
  fVar5 = DAT_0003e680;
  fVar4 = DAT_0003e67c;
  fVar3 = DAT_0003e678;
  fVar2 = DAT_0003e674;
  fVar1 = DAT_0003e670;
  if (-1 < (int)uVar14) {
    uVar17 = 0;
    do {
      fVar9 = DAT_0003e690;
      fVar8 = DAT_0003e68c;
      fVar7 = DAT_0003e688;
      fVar6 = DAT_0003e684;
      uVar18 = 1 - uVar17;
      if (1 < uVar17) {
        uVar18 = 0;
      }
      uVar16 = 0;
      do {
        uVar11 = uVar18;
        if (uVar16 == 0) {
          uVar11 = uVar18 | 1;
        }
        iVar13 = uVar14 * uVar17 + uVar17 + uVar16;
        if (((uVar11 == 0) && (uVar16 != uVar14)) && (uVar17 != uVar14)) {
          iVar15 = *(int *)(this + 0x7c);
          uVar10 = gRMathRand2();
          iVar19 = *(int *)(this + 0x7c);
          iVar12 = iVar13 * 0x28;
          fVar23 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(iVar15 + iVar13 * 0x28) = fVar23 * fVar2 * fVar3;
          uVar10 = gRMathRand2();
          fVar23 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
          in_fpscr = in_fpscr & 0xfffffff |
                     (uint)(fVar23 * fVar2 + fVar23 * fVar2 + fVar4 == DAT_0003e670) << 0x1e;
          fVar23 = DAT_0003e670;
          if (!SUB41(in_fpscr >> 0x1e,0)) {
            uVar10 = gRMathRand2();
            fVar23 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
            fVar23 = (fVar9 / ((fVar23 * fVar2 + fVar23 * fVar2 + fVar4) * fVar8)) * fVar3;
          }
          *(float *)(iVar19 + iVar12 + 4) = fVar23;
          iVar13 = *(int *)(this + 0x7c);
          uVar10 = gRMathRand2();
          iVar19 = *(int *)(this + 0x7c);
          fVar23 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(iVar13 + iVar12 + 8) = (fVar23 - fVar6) * fVar7 * in_r1 * fVar5;
          uVar10 = gRMathRand2();
          uVar14 = *(uint *)(this + 0x3c);
          iVar15 = *(int *)(this + 0x7c) + iVar12;
          fVar23 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(iVar19 + iVar12 + 0xc) = in_r1 * fVar5 * (fVar23 - fVar6) * fVar7;
        }
        else {
          iVar12 = *(int *)(this + 0x7c);
          iVar15 = iVar12 + iVar13 * 0x28;
          *(float *)(iVar15 + 4) = fVar1;
          *(float *)(iVar12 + iVar13 * 0x28) = fVar1;
          *(float *)(iVar15 + 8) = fVar1;
          *(float *)(iVar15 + 0xc) = fVar1;
        }
        fVar23 = DAT_0003e694;
        fVar20 = (float)VectorSignedToFloat(uVar14,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(iVar15 + 0x20) = fVar1;
        iVar13 = uVar16 + -((int)uVar14 / 2);
        uVar16 = uVar16 + 1;
        fVar21 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
        fVar22 = (float)VectorSignedToFloat(uVar17 + -((int)uVar14 / 2),(byte)(in_fpscr >> 0x16) & 3
                                           );
        *(float *)(iVar15 + 0x1c) = fVar22 / (fVar20 * fVar23);
        *(float *)(iVar15 + 0x18) = fVar21 / (fVar20 * fVar23);
        uVar10 = tVector::Normalize((tVector *)(iVar15 + 0x18));
        uVar14 = *(uint *)(this + 0x3c);
        *(undefined4 *)(iVar15 + 0x24) = uVar10;
      } while ((int)uVar16 <= (int)uVar14);
      uVar17 = uVar17 + 1;
      param_1 = extraout_s0;
    } while (((int)uVar17 <= (int)uVar14) && (-1 < (int)uVar14));
  }
  return param_1;
}
