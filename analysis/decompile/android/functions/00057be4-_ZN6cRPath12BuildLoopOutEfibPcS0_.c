/*
 * mangled: _ZN6cRPath12BuildLoopOutEfibPcS0_
 * demangled: cRPath::BuildLoopOut(float, int, bool, char*, char*)
 * address: 00057be4
 * size: 1348
 */

/* cRPath::BuildLoopOut(float, int, bool, char*, char*) */

void cRPath::BuildLoopOut(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  tVector *ptVar5;
  undefined4 uVar6;
  int iVar7;
  tMatrix *ptVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint in_fpscr;
  float fVar13;
  float extraout_s0;
  float extraout_s0_00;
  float fVar14;
  int iVar15;
  undefined4 uVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;

  fVar22 = DAT_00057e18;
  fVar14 = (float)(uint)param_3 * DAT_00057e18;
  *(undefined1 *)(param_2 + 0x30) = 0;
  fVar4 = DAT_00057e40;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar11 = 0;
  iVar12 = 0;
  *(char **)(param_2 + 0x48) = param_4;
  *(float *)(param_2 + 0x44) = fVar4;
  *(undefined4 *)(param_2 + 0x2c) = 0x1d;
  uVar6 = DAT_00057e44;
  fVar1 = DAT_00057e2c;
  fVar21 = DAT_00057e28;
  fVar13 = DAT_00057e24;
  fVar19 = DAT_00057e20;
  fVar17 = DAT_00057e1c;
  iVar15 = (int)fVar14;
  fVar14 = (float)VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar15 + 0xe;
  uVar16 = VectorSignedToFloat(iVar15 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar16;
  fVar22 = fVar14 / fVar22;
  GetNodes((cRPath *)param_2);
  iVar7 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar20 = (float)VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
    uVar16 = *(undefined4 *)(param_2 + 0x48);
    ptVar8 = (tMatrix *)(iVar7 + iVar11);
    *(undefined4 *)(ptVar8 + 0x98) = uVar6;
    *(undefined4 *)(ptVar8 + 0x94) = uVar6;
    *(undefined4 *)(ptVar8 + 0xa0) = uVar6;
    *(float *)(ptVar8 + 0x9c) = fVar4;
    iVar12 = iVar12 + 1;
    fVar18 = (float)VectorSignedToFloat(uVar16,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar8 + 0x90) = (fVar18 * fVar17 - fVar19) - (fVar20 / fVar13) * fVar21;
    tMatrix::Identity(ptVar8);
    iVar7 = *(int *)(param_2 + 0x50);
    iVar9 = *(int *)(param_2 + 0x4c) + iVar11;
    *(float *)(iVar9 + 0x8c) = fVar4;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(iVar9 + 0x34) = uVar6;
    *(float *)(iVar9 + 0x38) = fVar20;
    tMatrix::Identity((tMatrix *)(iVar7 + iVar11));
    iVar7 = *(int *)(param_2 + 0x4c);
    iVar9 = *(int *)(param_2 + 0x50) + iVar11;
    *(float *)(iVar9 + 0x38) = fVar20;
    *(float *)(iVar9 + 0x8c) = fVar4;
    uVar16 = *(undefined4 *)(iVar7 + iVar11 + 0x90);
    *(float *)(iVar9 + 0x34) = fVar1;
    iVar11 = iVar11 + 0xa8;
    *(undefined4 *)(iVar9 + 0x30) = uVar16;
    fVar3 = DAT_00057e34;
    fVar2 = DAT_00057e30;
    fVar20 = DAT_00057e28;
    fVar18 = DAT_00057e20;
  } while (iVar12 != 10);
  iVar12 = 0;
  iVar9 = (iVar15 + 10) * 0xa8;
  iVar11 = iVar9;
  do {
    fVar17 = (float)VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
    uVar16 = *(undefined4 *)(param_2 + 0x48);
    ptVar8 = (tMatrix *)(iVar7 + iVar11);
    *(undefined4 *)(ptVar8 + 0x98) = uVar6;
    *(undefined4 *)(ptVar8 + 0x94) = uVar6;
    *(undefined4 *)(ptVar8 + 0xa0) = uVar6;
    *(float *)(ptVar8 + 0x9c) = fVar4;
    fVar19 = (float)VectorSignedToFloat(uVar16,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar8 + 0x90) = fVar18 + fVar19 * fVar2 + (fVar4 - fVar17 / fVar3) * fVar20;
    tMatrix::Identity(ptVar8);
    uVar16 = VectorSignedToFloat(iVar12 + 10,(byte)(in_fpscr >> 0x16) & 3);
    iVar12 = iVar12 + 1;
    iVar7 = *(int *)(param_2 + 0x50);
    iVar10 = *(int *)(param_2 + 0x4c) + iVar11;
    *(float *)(iVar10 + 0x8c) = fVar4;
    *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar10 + 0x90);
    *(undefined4 *)(iVar10 + 0x34) = uVar6;
    *(undefined4 *)(iVar10 + 0x38) = uVar16;
    fVar13 = (float)tMatrix::Identity((tMatrix *)(iVar7 + iVar11));
    iVar7 = *(int *)(param_2 + 0x4c);
    iVar10 = *(int *)(param_2 + 0x50) + iVar11;
    *(undefined4 *)(iVar10 + 0x38) = uVar16;
    *(float *)(iVar10 + 0x8c) = fVar4;
    uVar16 = *(undefined4 *)(iVar7 + iVar11 + 0x90);
    *(float *)(iVar10 + 0x34) = fVar1;
    iVar11 = iVar11 + 0xa8;
    *(undefined4 *)(iVar10 + 0x30) = uVar16;
    fVar19 = DAT_00057e3c;
    fVar17 = DAT_00057e28;
  } while (iVar12 != 4);
  fVar21 = -fVar22;
  if (0 < iVar15) {
    iVar12 = 0x690;
    iVar11 = 0;
    while( true ) {
      fVar18 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
      fVar18 = *(float *)(iVar7 + 0x90) +
               (fVar18 * (*(float *)(iVar7 + iVar9 + 0x90) - *(float *)(iVar7 + 0x90))) / fVar14;
      *(float *)(iVar7 + iVar12 + 0x90) = fVar18;
      fVar13 = (float)Sin(fVar13);
      ptVar8 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar12);
      *(undefined4 *)(ptVar8 + 0x98) = uVar6;
      *(undefined4 *)(ptVar8 + 0x94) = uVar6;
      *(undefined4 *)(ptVar8 + 0xa0) = uVar6;
      *(float *)(ptVar8 + 0x9c) = fVar4;
      *(float *)(iVar7 + iVar12 + 0x90) = fVar18 + fVar13 * fVar17;
      fVar13 = (float)tMatrix::Identity(ptVar8);
      iVar7 = *(int *)(param_2 + 0x4c) + iVar12;
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      fVar13 = (float)Sin(fVar13);
      iVar10 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar7 + 0x38) = fVar19 + fVar13 * fVar22;
      fVar13 = (float)Cos(extraout_s0);
      iVar7 = *(int *)(param_2 + 0x50);
      *(float *)(iVar10 + iVar12 + 0x34) = fVar21 + fVar13 * fVar22;
      fVar13 = (float)tMatrix::Identity((tMatrix *)(iVar7 + iVar12));
      iVar7 = *(int *)(param_2 + 0x50) + iVar12;
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar12 + 0x90);
      fVar13 = (float)Sin(fVar13);
      iVar10 = *(int *)(param_2 + 0x50);
      *(float *)(iVar7 + 0x38) = fVar19 + fVar13 * (fVar22 + fVar1);
      fVar13 = (float)Cos(extraout_s0_00);
      iVar7 = *(int *)(param_2 + 0x4c) + iVar12;
      fVar18 = *(float *)(iVar7 + 0x38);
      *(float *)(*(int *)(param_2 + 0x4c) + iVar12) = fVar4;
      *(undefined4 *)(iVar7 + 8) = uVar6;
      *(undefined4 *)(iVar7 + 4) = uVar6;
      *(undefined4 *)(iVar7 + 0x10) = uVar6;
      *(float *)(iVar7 + 0x18) = -(fVar19 - fVar18);
      *(float *)(iVar10 + iVar12 + 0x34) = fVar21 + (fVar22 + fVar1) * fVar13;
      *(float *)(iVar7 + 0x14) = -(fVar21 - *(float *)(iVar7 + 0x34));
      tVector::Normalize((tVector *)(iVar7 + 0x10));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar12);
      tVector::Cross(ptVar5 + 0x20,ptVar5,ptVar5 + 0x10);
      iVar7 = *(int *)(param_2 + 0x50) + iVar12;
      fVar13 = *(float *)(iVar7 + 0x34);
      fVar18 = *(float *)(iVar7 + 0x38);
      *(float *)(*(int *)(param_2 + 0x50) + iVar12) = fVar4;
      *(undefined4 *)(iVar7 + 8) = uVar6;
      *(undefined4 *)(iVar7 + 4) = uVar6;
      *(undefined4 *)(iVar7 + 0x10) = uVar6;
      *(float *)(iVar7 + 0x14) = -(fVar21 - fVar13);
      *(float *)(iVar7 + 0x18) = -(fVar19 - fVar18);
      tVector::Normalize((tVector *)(iVar7 + 0x10));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x50) + iVar12);
      iVar12 = iVar12 + 0xa8;
      fVar13 = (float)tVector::Cross(ptVar5 + 0x20,ptVar5,ptVar5 + 0x10);
      if (iVar15 <= iVar11 + 1) break;
      iVar7 = *(int *)(param_2 + 0x4c);
      iVar11 = iVar11 + 1;
    }
    iVar7 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar11 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar15 = 0;
    iVar12 = 0;
    while( true ) {
      iVar9 = iVar12 + 0xa8;
      iVar11 = iVar7 + iVar12;
      iVar7 = iVar7 + iVar9;
      fVar17 = *(float *)(iVar7 + 0x38);
      fVar22 = *(float *)(iVar7 + 0x34);
      iVar15 = iVar15 + 1;
      *(float *)(iVar11 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar22 - *(float *)(iVar11 + 0x34);
      *(float *)(iVar11 + 0x88) = fVar17 - *(float *)(iVar11 + 0x38);
      uVar6 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar12 = *(int *)(param_2 + 0x50) + iVar12;
      iVar7 = *(int *)(param_2 + 0x50) + iVar9;
      fVar17 = *(float *)(iVar7 + 0x38);
      fVar22 = *(float *)(iVar7 + 0x34);
      fVar19 = *(float *)(iVar12 + 0x38);
      *(float *)(iVar12 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar12 + 0x30);
      *(float *)(iVar12 + 0x84) = fVar22 - *(float *)(iVar12 + 0x34);
      *(undefined4 *)(iVar11 + 0x8c) = uVar6;
      *(float *)(iVar12 + 0x88) = fVar17 - fVar19;
      uVar6 = tVector::Normalize((tVector *)(iVar12 + 0x80));
      iVar11 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar12 + 0x8c) = uVar6;
      if (iVar11 <= iVar15) break;
      iVar7 = *(int *)(param_2 + 0x4c);
      iVar12 = iVar9;
    }
    iVar7 = *(int *)(param_2 + 0x4c);
  }
  uVar6 = DAT_00057e44;
  fVar22 = DAT_00057e40;
  iVar12 = *(int *)(param_2 + 0x50) + iVar11 * 0xa8;
  iVar7 = iVar7 + iVar11 * 0xa8;
  *(float *)(iVar7 + 0x8c) = DAT_00057e40;
  *(float *)(iVar7 + 0x88) = fVar22;
  *(undefined4 *)(iVar7 + 0x84) = uVar6;
  *(undefined4 *)(iVar7 + 0x80) = uVar6;
  *(float *)(iVar12 + 0x8c) = fVar22;
  *(undefined4 *)(iVar12 + 0x80) = uVar6;
  *(float *)(iVar12 + 0x88) = fVar22;
  *(undefined4 *)(iVar12 + 0x84) = uVar6;
  CalcLengthZ((cRPath *)param_2);
  return;
}
