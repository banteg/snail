/*
 * mangled: _ZN6cRPath16BuildLoopTheLoopEfibPcS0_
 * demangled: cRPath::BuildLoopTheLoop(float, int, bool, char*, char*)
 * address: 00058728
 * size: 1328
 */

/* cRPath::BuildLoopTheLoop(float, int, bool, char*, char*) */

void cRPath::BuildLoopTheLoop(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

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
  float fVar8;
  int iVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar5 = 0;
  iVar6 = 0;
  iVar9 = (int)((float)(uint)param_3 * 6.2831855);
  fVar14 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar9 + 0xe;
  uVar10 = VectorSignedToFloat(iVar9 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar10;
  fVar8 = 0.3;
  if (param_4 != (char *)0x4) {
    fVar8 = 0.0;
  }
  fVar13 = fVar14 / 6.2831855;
  GetNodes((cRPath *)param_2);
  iVar2 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar12 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    uVar10 = *(undefined4 *)(param_2 + 0x48);
    ptVar3 = (tMatrix *)(iVar2 + iVar5);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    iVar6 = iVar6 + 1;
    fVar11 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar3 + 0x90) = (fVar11 * 0.5 - 4.0) - fVar8 * (fVar12 / 7.0);
    tMatrix::Identity(ptVar3);
    iVar2 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar5;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(float *)(iVar4 + 0x38) = fVar12;
    tMatrix::Identity((tMatrix *)(iVar2 + iVar5));
    iVar2 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar5;
    *(float *)(iVar4 + 0x38) = fVar12;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    uVar10 = *(undefined4 *)(iVar2 + iVar5 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0x3efae148;
    iVar5 = iVar5 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = uVar10;
  } while (iVar6 != 7);
  iVar6 = 0;
  iVar5 = (iVar9 + 7) * 0xa8;
  do {
    fVar11 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    uVar10 = *(undefined4 *)(param_2 + 0x48);
    ptVar3 = (tMatrix *)(iVar2 + iVar5);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    fVar12 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar3 + 0x90) = fVar12 * -0.5 + 4.0 + fVar8 * (1.0 - fVar11 / 6.0);
    tMatrix::Identity(ptVar3);
    uVar10 = VectorSignedToFloat(iVar6 + 7,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = iVar6 + 1;
    iVar2 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar5;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(undefined4 *)(iVar4 + 0x38) = uVar10;
    fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar5));
    iVar2 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar5;
    *(undefined4 *)(iVar4 + 0x38) = uVar10;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    uVar10 = *(undefined4 *)(iVar2 + iVar5 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0x3efae148;
    iVar5 = iVar5 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = uVar10;
  } while (iVar6 != 7);
  if (0 < iVar9) {
    iVar6 = 0x498;
    iVar5 = 0;
    while( true ) {
      fVar12 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      fVar12 = *(float *)(iVar2 + 0x90) +
               (fVar12 * (*(float *)(iVar2 + (iVar9 + 0xd) * 0xa8 + 0x90) - *(float *)(iVar2 + 0x90)
                         )) / fVar14;
      *(float *)(iVar2 + iVar6 + 0x90) = fVar12;
      fVar11 = (float)Sin(fVar11);
      ptVar3 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar6);
      *(undefined4 *)(ptVar3 + 0x98) = 0;
      *(undefined4 *)(ptVar3 + 0x94) = 0;
      *(undefined4 *)(ptVar3 + 0xa0) = 0;
      *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
      *(float *)(iVar2 + iVar6 + 0x90) = fVar12 + fVar11 * fVar8;
      fVar11 = (float)tMatrix::Identity(ptVar3);
      iVar2 = *(int *)(param_2 + 0x4c) + iVar6;
      *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
      fVar11 = (float)Sin(fVar11);
      iVar4 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar2 + 0x38) = fVar11 * fVar13 + 7.0;
      fVar11 = (float)Cos(extraout_s0);
      iVar2 = *(int *)(param_2 + 0x50);
      *(float *)(iVar4 + iVar6 + 0x34) = fVar13 - fVar11 * fVar13;
      fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar6));
      iVar2 = *(int *)(param_2 + 0x50) + iVar6;
      *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar6 + 0x90);
      fVar11 = (float)Sin(fVar11);
      iVar4 = *(int *)(param_2 + 0x50);
      *(float *)(iVar2 + 0x38) = fVar11 * (fVar13 - 0.49) + 7.0;
      fVar11 = (float)Cos(extraout_s0_00);
      iVar2 = *(int *)(param_2 + 0x4c) + iVar6;
      fVar12 = *(float *)(iVar2 + 0x38);
      *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar6) = 0x3f800000;
      *(undefined4 *)(iVar2 + 8) = 0;
      *(undefined4 *)(iVar2 + 4) = 0;
      *(undefined4 *)(iVar2 + 0x10) = 0;
      *(float *)(iVar2 + 0x18) = 7.0 - fVar12;
      *(float *)(iVar4 + iVar6 + 0x34) = fVar13 - (fVar13 - 0.49) * fVar11;
      *(float *)(iVar2 + 0x14) = fVar13 - *(float *)(iVar2 + 0x34);
      tVector::Normalize((tVector *)(iVar2 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar6);
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      iVar2 = *(int *)(param_2 + 0x50) + iVar6;
      fVar11 = *(float *)(iVar2 + 0x34);
      fVar12 = *(float *)(iVar2 + 0x38);
      *(undefined4 *)(*(int *)(param_2 + 0x50) + iVar6) = 0x3f800000;
      *(undefined4 *)(iVar2 + 8) = 0;
      *(undefined4 *)(iVar2 + 4) = 0;
      *(undefined4 *)(iVar2 + 0x10) = 0;
      *(float *)(iVar2 + 0x14) = fVar13 - fVar11;
      *(float *)(iVar2 + 0x18) = 7.0 - fVar12;
      tVector::Normalize((tVector *)(iVar2 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar6);
      iVar6 = iVar6 + 0xa8;
      fVar11 = (float)tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      if (iVar9 <= iVar5 + 1) break;
      iVar2 = *(int *)(param_2 + 0x4c);
      iVar5 = iVar5 + 1;
    }
    iVar2 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar5 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar9 = 0;
    iVar6 = 0;
    while( true ) {
      iVar7 = iVar6 + 0xa8;
      iVar4 = iVar2 + iVar6;
      iVar2 = iVar2 + iVar7;
      fVar14 = *(float *)(iVar2 + 0x38);
      fVar8 = *(float *)(iVar2 + 0x34);
      iVar9 = iVar9 + 1;
      *(float *)(iVar4 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar8 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar14 - *(float *)(iVar4 + 0x38);
      uVar10 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      iVar6 = *(int *)(param_2 + 0x50) + iVar6;
      iVar5 = *(int *)(param_2 + 0x50) + iVar7;
      fVar14 = *(float *)(iVar5 + 0x38);
      fVar8 = *(float *)(iVar5 + 0x34);
      fVar13 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar6 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar8 - *(float *)(iVar6 + 0x34);
      *(undefined4 *)(iVar4 + 0x8c) = uVar10;
      *(float *)(iVar6 + 0x88) = fVar14 - fVar13;
      uVar10 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar5 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar6 + 0x8c) = uVar10;
      if (iVar5 <= iVar9) break;
      iVar2 = *(int *)(param_2 + 0x4c);
      iVar6 = iVar7;
    }
    iVar2 = *(int *)(param_2 + 0x4c);
  }
  iVar6 = *(int *)(param_2 + 0x50) + iVar5 * 0xa8;
  iVar2 = iVar2 + iVar5 * 0xa8;
  *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x80) = 0;
  *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
