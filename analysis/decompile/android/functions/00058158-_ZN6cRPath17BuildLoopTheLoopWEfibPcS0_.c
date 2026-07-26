/*
 * mangled: _ZN6cRPath17BuildLoopTheLoopWEfibPcS0_
 * demangled: cRPath::BuildLoopTheLoopW(float, int, bool, char*, char*)
 * address: 00058158
 * size: 1428
 */

/* cRPath::BuildLoopTheLoopW(float, int, bool, char*, char*) */

void cRPath::BuildLoopTheLoopW(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  undefined4 uVar2;
  int iVar3;
  tMatrix *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  int iVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float unaff_s24;
  float fVar14;

  bVar9 = param_4 == (char *)0x4;
  uVar2 = 0;
  iVar6 = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  if (bVar9) {
    uVar2 = 7;
  }
  *(char **)(param_2 + 0x48) = param_4;
  if (bVar9) {
    *(undefined4 *)(param_2 + 0x2c) = uVar2;
  }
  else {
    unaff_s24 = 0.0;
  }
  *(undefined1 *)(param_2 + 0x30) = 0;
  if (bVar9) {
    unaff_s24 = 0.3;
  }
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar7 = 0;
  iVar10 = (int)((float)(uint)param_3 * 6.2831855);
  fVar14 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar10 + 0xe;
  uVar2 = VectorSignedToFloat(iVar10 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar2;
  fVar13 = fVar14 / 6.2831855;
  GetNodes((cRPath *)param_2);
  iVar3 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar12 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    uVar2 = *(undefined4 *)(param_2 + 0x48);
    ptVar4 = (tMatrix *)(iVar3 + iVar6);
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    iVar7 = iVar7 + 1;
    fVar11 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar4 + 0x90) = (fVar11 * 0.5 - 4.0) - unaff_s24 * (fVar12 / 7.0);
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(float *)(iVar5 + 0x38) = fVar12;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar6));
    iVar3 = *(int *)(param_2 + 0x4c);
    iVar5 = *(int *)(param_2 + 0x50) + iVar6;
    *(float *)(iVar5 + 0x38) = fVar12;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    uVar2 = *(undefined4 *)(iVar3 + iVar6 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = uVar2;
  } while (iVar7 != 7);
  iVar7 = 0;
  iVar6 = (iVar10 + 7) * 0xa8;
  do {
    fVar11 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    uVar2 = *(undefined4 *)(param_2 + 0x48);
    ptVar4 = (tMatrix *)(iVar3 + iVar6);
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    fVar12 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar4 + 0x90) = fVar12 * -0.5 + 4.0 + unaff_s24 * (1.0 - fVar11 / 6.0);
    tMatrix::Identity(ptVar4);
    uVar2 = VectorSignedToFloat(iVar7 + 7,(byte)(in_fpscr >> 0x16) & 3);
    iVar7 = iVar7 + 1;
    iVar3 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x38) = uVar2;
    fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar6));
    iVar3 = *(int *)(param_2 + 0x4c);
    iVar5 = *(int *)(param_2 + 0x50) + iVar6;
    *(undefined4 *)(iVar5 + 0x38) = uVar2;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    uVar2 = *(undefined4 *)(iVar3 + iVar6 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = uVar2;
  } while (iVar7 != 7);
  if (0 < iVar10) {
    iVar6 = 0x498;
    iVar3 = 0;
    do {
      fVar12 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
      iVar3 = iVar3 + 1;
      fVar11 = (float)Sin(fVar11);
      fVar11 = (float)Sin(fVar11);
      iVar7 = *(int *)(param_2 + 0x4c);
      fVar12 = *(float *)(iVar7 + 0x90) +
               (fVar12 * (*(float *)(iVar7 + (iVar10 + 0xd) * 0xa8 + 0x90) -
                         *(float *)(iVar7 + 0x90))) / fVar14;
      *(float *)(iVar7 + iVar6 + 0x90) = fVar12;
      fVar11 = (float)Sin(fVar11);
      ptVar4 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar6);
      *(undefined4 *)(ptVar4 + 0x98) = 0;
      *(undefined4 *)(ptVar4 + 0x94) = 0;
      *(undefined4 *)(ptVar4 + 0xa0) = 0;
      *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
      *(float *)(iVar7 + iVar6 + 0x90) = fVar12 + fVar11 * unaff_s24;
      fVar11 = (float)tMatrix::Identity(ptVar4);
      iVar7 = *(int *)(param_2 + 0x4c) + iVar6;
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      fVar11 = (float)Sin(fVar11);
      iVar5 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar7 + 0x38) = fVar11 * fVar13 + 7.0;
      fVar11 = (float)Cos(extraout_s0);
      iVar7 = *(int *)(param_2 + 0x50);
      *(float *)(iVar5 + iVar6 + 0x34) = fVar13 - fVar11 * fVar13;
      fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar7 + iVar6));
      iVar7 = *(int *)(param_2 + 0x50) + iVar6;
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar6 + 0x90);
      fVar11 = (float)Sin(fVar11);
      iVar5 = *(int *)(param_2 + 0x50);
      *(float *)(iVar7 + 0x38) = fVar11 * (fVar13 - 0.49) + 7.0;
      fVar11 = (float)Cos(extraout_s0_00);
      iVar7 = *(int *)(param_2 + 0x4c) + iVar6;
      fVar12 = *(float *)(iVar7 + 0x38);
      *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar6) = 0x3f800000;
      *(undefined4 *)(iVar7 + 8) = 0;
      *(undefined4 *)(iVar7 + 4) = 0;
      *(undefined4 *)(iVar7 + 0x10) = 0;
      *(float *)(iVar7 + 0x18) = 7.0 - fVar12;
      *(float *)(iVar5 + iVar6 + 0x34) = fVar13 - (fVar13 - 0.49) * fVar11;
      *(float *)(iVar7 + 0x14) = fVar13 - *(float *)(iVar7 + 0x34);
      tVector::Normalize((tVector *)(iVar7 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar6);
      fVar11 = (float)tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar6),fVar11);
      iVar7 = *(int *)(param_2 + 0x50) + iVar6;
      fVar11 = *(float *)(iVar7 + 0x34);
      fVar12 = *(float *)(iVar7 + 0x38);
      *(undefined4 *)(*(int *)(param_2 + 0x50) + iVar6) = 0x3f800000;
      *(undefined4 *)(iVar7 + 8) = 0;
      *(undefined4 *)(iVar7 + 4) = 0;
      *(undefined4 *)(iVar7 + 0x10) = 0;
      *(float *)(iVar7 + 0x14) = fVar13 - fVar11;
      *(float *)(iVar7 + 0x18) = 7.0 - fVar12;
      tVector::Normalize((tVector *)(iVar7 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar6);
      fVar11 = (float)tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      ptVar4 = (tMatrix *)(*(int *)(param_2 + 0x50) + iVar6);
      iVar6 = iVar6 + 0xa8;
      fVar11 = (float)tMatrix::RotLocalZ(ptVar4,fVar11);
    } while (iVar3 < iVar10);
    iVar3 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar6 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar10 = 0;
    iVar7 = 0;
    while( true ) {
      iVar8 = iVar7 + 0xa8;
      iVar5 = iVar3 + iVar7;
      iVar3 = iVar3 + iVar8;
      fVar14 = *(float *)(iVar3 + 0x38);
      fVar13 = *(float *)(iVar3 + 0x34);
      iVar10 = iVar10 + 1;
      *(float *)(iVar5 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar13 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x88) = fVar14 - *(float *)(iVar5 + 0x38);
      uVar2 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      iVar7 = *(int *)(param_2 + 0x50) + iVar7;
      iVar6 = *(int *)(param_2 + 0x50) + iVar8;
      fVar14 = *(float *)(iVar6 + 0x38);
      fVar13 = *(float *)(iVar6 + 0x34);
      fVar11 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar13 - *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar5 + 0x8c) = uVar2;
      *(float *)(iVar7 + 0x88) = fVar14 - fVar11;
      uVar2 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar6 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar7 + 0x8c) = uVar2;
      if (iVar6 <= iVar10) break;
      iVar3 = *(int *)(param_2 + 0x4c);
      iVar7 = iVar8;
    }
    iVar3 = *(int *)(param_2 + 0x4c);
  }
  iVar7 = *(int *)(param_2 + 0x50) + iVar6 * 0xa8;
  iVar3 = iVar3 + iVar6 * 0xa8;
  *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
