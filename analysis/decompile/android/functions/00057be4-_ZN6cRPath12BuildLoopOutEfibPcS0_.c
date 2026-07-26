/*
 * mangled: _ZN6cRPath12BuildLoopOutEfibPcS0_
 * demangled: cRPath::BuildLoopOut(float, int, bool, char*, char*)
 * address: 00057be4
 * size: 1348
 */

/* cRPath::BuildLoopOut(float, int, bool, char*, char*) */

void cRPath::BuildLoopOut(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  int iVar2;
  tMatrix *ptVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  int iVar8;
  undefined4 uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar6 = 0;
  iVar7 = 0;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = 0x1d;
  iVar8 = (int)((float)(uint)param_3 * 6.2831855);
  fVar14 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar8 + 0xe;
  uVar9 = VectorSignedToFloat(iVar8 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar9;
  fVar13 = fVar14 / 6.2831855;
  GetNodes((cRPath *)param_2);
  iVar2 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar12 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    uVar9 = *(undefined4 *)(param_2 + 0x48);
    ptVar3 = (tMatrix *)(iVar2 + iVar6);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    iVar7 = iVar7 + 1;
    fVar11 = (float)VectorSignedToFloat(uVar9,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar3 + 0x90) = (fVar11 * 0.5 - 4.0) - (fVar12 / 9.0) * 0.3;
    tMatrix::Identity(ptVar3);
    iVar2 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(float *)(iVar4 + 0x38) = fVar12;
    tMatrix::Identity((tMatrix *)(iVar2 + iVar6));
    iVar2 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar6;
    *(float *)(iVar4 + 0x38) = fVar12;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    uVar9 = *(undefined4 *)(iVar2 + iVar6 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = uVar9;
  } while (iVar7 != 10);
  iVar7 = 0;
  iVar4 = (iVar8 + 10) * 0xa8;
  iVar6 = iVar4;
  do {
    fVar11 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    uVar9 = *(undefined4 *)(param_2 + 0x48);
    ptVar3 = (tMatrix *)(iVar2 + iVar6);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    fVar12 = (float)VectorSignedToFloat(uVar9,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar3 + 0x90) = fVar12 * -0.5 + 4.0 + (1.0 - fVar11 / 3.0) * 0.3;
    tMatrix::Identity(ptVar3);
    uVar9 = VectorSignedToFloat(iVar7 + 10,(byte)(in_fpscr >> 0x16) & 3);
    iVar7 = iVar7 + 1;
    iVar2 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x38) = uVar9;
    fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar6));
    iVar2 = *(int *)(param_2 + 0x4c);
    iVar5 = *(int *)(param_2 + 0x50) + iVar6;
    *(undefined4 *)(iVar5 + 0x38) = uVar9;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    uVar9 = *(undefined4 *)(iVar2 + iVar6 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = uVar9;
  } while (iVar7 != 4);
  fVar12 = -fVar13;
  if (0 < iVar8) {
    iVar7 = 0x690;
    iVar6 = 0;
    while( true ) {
      fVar10 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = *(float *)(iVar2 + 0x90) +
               (fVar10 * (*(float *)(iVar2 + iVar4 + 0x90) - *(float *)(iVar2 + 0x90))) / fVar14;
      *(float *)(iVar2 + iVar7 + 0x90) = fVar10;
      fVar11 = (float)Sin(fVar11);
      ptVar3 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar7);
      *(undefined4 *)(ptVar3 + 0x98) = 0;
      *(undefined4 *)(ptVar3 + 0x94) = 0;
      *(undefined4 *)(ptVar3 + 0xa0) = 0;
      *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
      *(float *)(iVar2 + iVar7 + 0x90) = fVar10 + fVar11 * 0.3;
      fVar11 = (float)tMatrix::Identity(ptVar3);
      iVar2 = *(int *)(param_2 + 0x4c) + iVar7;
      *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
      fVar11 = (float)Sin(fVar11);
      iVar5 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar2 + 0x38) = fVar11 * fVar13 + 10.0;
      fVar11 = (float)Cos(extraout_s0);
      iVar2 = *(int *)(param_2 + 0x50);
      *(float *)(iVar5 + iVar7 + 0x34) = fVar12 + fVar11 * fVar13;
      fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar7));
      iVar2 = *(int *)(param_2 + 0x50) + iVar7;
      *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar7 + 0x90);
      fVar11 = (float)Sin(fVar11);
      iVar5 = *(int *)(param_2 + 0x50);
      *(float *)(iVar2 + 0x38) = fVar11 * (fVar13 + 0.49) + 10.0;
      fVar11 = (float)Cos(extraout_s0_00);
      iVar2 = *(int *)(param_2 + 0x4c) + iVar7;
      fVar10 = *(float *)(iVar2 + 0x38);
      *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar7) = 0x3f800000;
      *(undefined4 *)(iVar2 + 8) = 0;
      *(undefined4 *)(iVar2 + 4) = 0;
      *(undefined4 *)(iVar2 + 0x10) = 0;
      *(float *)(iVar2 + 0x18) = -(10.0 - fVar10);
      *(float *)(iVar5 + iVar7 + 0x34) = fVar12 + (fVar13 + 0.49) * fVar11;
      *(float *)(iVar2 + 0x14) = -(fVar12 - *(float *)(iVar2 + 0x34));
      tVector::Normalize((tVector *)(iVar2 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar7);
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      iVar2 = *(int *)(param_2 + 0x50) + iVar7;
      fVar11 = *(float *)(iVar2 + 0x34);
      fVar10 = *(float *)(iVar2 + 0x38);
      *(undefined4 *)(*(int *)(param_2 + 0x50) + iVar7) = 0x3f800000;
      *(undefined4 *)(iVar2 + 8) = 0;
      *(undefined4 *)(iVar2 + 4) = 0;
      *(undefined4 *)(iVar2 + 0x10) = 0;
      *(float *)(iVar2 + 0x14) = -(fVar12 - fVar11);
      *(float *)(iVar2 + 0x18) = -(10.0 - fVar10);
      tVector::Normalize((tVector *)(iVar2 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar7);
      iVar7 = iVar7 + 0xa8;
      fVar11 = (float)tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      if (iVar8 <= iVar6 + 1) break;
      iVar2 = *(int *)(param_2 + 0x4c);
      iVar6 = iVar6 + 1;
    }
    iVar2 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar6 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar8 = 0;
    iVar7 = 0;
    while( true ) {
      iVar4 = iVar7 + 0xa8;
      iVar6 = iVar2 + iVar7;
      iVar2 = iVar2 + iVar4;
      fVar14 = *(float *)(iVar2 + 0x38);
      fVar13 = *(float *)(iVar2 + 0x34);
      iVar8 = iVar8 + 1;
      *(float *)(iVar6 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar13 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x88) = fVar14 - *(float *)(iVar6 + 0x38);
      uVar9 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar7 = *(int *)(param_2 + 0x50) + iVar7;
      iVar2 = *(int *)(param_2 + 0x50) + iVar4;
      fVar14 = *(float *)(iVar2 + 0x38);
      fVar13 = *(float *)(iVar2 + 0x34);
      fVar11 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar13 - *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar6 + 0x8c) = uVar9;
      *(float *)(iVar7 + 0x88) = fVar14 - fVar11;
      uVar9 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar6 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar7 + 0x8c) = uVar9;
      if (iVar6 <= iVar8) break;
      iVar2 = *(int *)(param_2 + 0x4c);
      iVar7 = iVar4;
    }
    iVar2 = *(int *)(param_2 + 0x4c);
  }
  iVar7 = *(int *)(param_2 + 0x50) + iVar6 * 0xa8;
  iVar2 = iVar2 + iVar6 * 0xa8;
  *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
