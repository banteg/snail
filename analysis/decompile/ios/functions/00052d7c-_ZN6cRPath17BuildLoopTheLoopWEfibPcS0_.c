/*
 * mangled: _ZN6cRPath17BuildLoopTheLoopWEfibPcS0_
 * demangled: cRPath::BuildLoopTheLoopW(float, int, bool, char*, char*)
 * address: 00052d7c
 * size: 2000
 */

/* cRPath::BuildLoopTheLoopW(float, int, bool, char*, char*) */

void cRPath::BuildLoopTheLoopW(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  tVector *ptVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar17;
  longlong lVar16;
  float fVar18;
  undefined8 uVar19;
  undefined4 uVar20;

  uVar7 = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x2c) = 0;
  if (uVar7 == 4) {
    *(undefined4 *)((int)param_1 + 0x2c) = 7;
  }
  *(uint *)((int)param_1 + 0x48) = uVar7;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  if (uVar7 == 4) {
    uVar20 = 0x3e99999a;
  }
  else {
    uVar20 = 0;
  }
  uVar19 = CONCAT44(uVar20,(int)((float)param_2 * 6.2831855));
  iVar1 = (int)((float)param_2 * 6.2831855) + 0xe;
  *(int *)((int)param_1 + 0x38) = iVar1;
  uVar20 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar20;
  uVar20 = RShellMemoryMalloc(iVar1 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar20;
  uVar20 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar20;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar5 = 0;
    iVar2 = 0;
    do {
      iVar5 = iVar5 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar8 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar8 + 0x9c) = 0x3f800000;
    } while (iVar5 < *(int *)((int)param_1 + 0x38));
  }
  iVar5 = 0;
  iVar2 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 1;
  do {
    fVar11 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
    iVar5 = iVar5 + 1;
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90) =
         (fVar10 * 0.5 - 4.0) - (float)((ulonglong)uVar19 >> 0x20) * (fVar11 / 7.0);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = fVar11;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    *(float *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x38) = fVar11;
    iVar8 = *(int *)((int)param_1 + 0x50) + iVar2;
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
  } while (iVar5 != 7);
  iVar5 = 0;
  iVar2 = (int)uVar19 * 0xa8 + 0x498;
  do {
    uVar12 = 0x3f800000;
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar11 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x90) =
         fVar10 * -0.5 + 4.0 + (float)((ulonglong)uVar19 >> 0x20) * (1.0 - fVar11 / 6.0);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
    iVar8 = iVar5 + 7;
    iVar5 = iVar5 + 1;
    uVar20 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar20;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x8c) = uVar12;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50) + 0x30) =
         *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x90);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar20;
    iVar8 = iVar2 + *(int *)((int)param_1 + 0x50);
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar8 + 0x8c) = uVar12;
  } while (iVar5 != 7);
  if (0 < (int)uVar19) {
    fVar10 = (float)VectorSignedToFloat((int)uVar19,(byte)(in_fpscr >> 0x16) & 3);
    lVar16 = (ulonglong)(uint)fVar10 << 0x20;
    iVar2 = 0x498;
    iVar5 = 0;
    fVar10 = fVar10 / 6.2831855;
    fVar11 = fVar10 - 0.49;
    do {
      fVar14 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = iVar5 + 1;
      fVar17 = (float)((ulonglong)lVar16 >> 0x20);
      fVar13 = (fVar14 * 6.2831855) / fVar17;
      fVar15 = fVar13 * 0.5;
      fVar3 = (float)Sin(fVar15);
      fVar4 = (float)Sin(fVar13 * 8.0);
      iVar8 = *(int *)((int)param_1 + 0x4c);
      fVar18 = fVar3 * fVar4 * 3.1415927 * 0.125;
      *(float *)(iVar8 + iVar2 + 0x90) =
           *(float *)(iVar8 + 0x90) +
           (fVar14 * (*(float *)(iVar8 + iVar1 * 0xa8 + -0x18) - *(float *)(iVar8 + 0x90))) / fVar17
      ;
      lVar16 = CONCAT44(fVar17,fVar15 + 4.712389);
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c);
      fVar4 = *(float *)(iVar8 + 0x90);
      fVar3 = (float)Sin(fVar15 + 4.712389);
      *(float *)(iVar8 + 0x90) = fVar4 + fVar3 * (float)((ulonglong)uVar19 >> 0x20);
      fVar4 = 7.0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c);
      *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
      iVar8 = *(int *)((int)param_1 + 0x4c);
      fVar3 = (float)Sin(fVar13);
      *(float *)(iVar2 + iVar8 + 0x38) = fVar4 + fVar3 * fVar10;
      iVar8 = *(int *)((int)param_1 + 0x4c);
      fVar3 = (float)Cos(fVar13);
      *(float *)(iVar2 + iVar8 + 0x34) = fVar10 - fVar3 * fVar10;
      tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
      *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
           *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
      iVar8 = *(int *)((int)param_1 + 0x50);
      fVar3 = (float)Sin(fVar13);
      *(float *)(iVar2 + iVar8 + 0x38) = fVar4 + fVar3 * fVar11;
      iVar8 = *(int *)((int)param_1 + 0x50);
      fVar3 = (float)Cos(fVar13);
      *(float *)(iVar2 + iVar8 + 0x34) = fVar10 - fVar3 * fVar11;
      puVar9 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c));
      puVar9[2] = 0;
      puVar9[1] = 0;
      *puVar9 = 0x3f800000;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x10) = 0;
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar8 + 0x14) = fVar10 - *(float *)(iVar8 + 0x34);
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar8 + 0x18) = fVar4 - *(float *)(iVar8 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x10));
      ptVar6 = (tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c));
      tVector::Cross(ptVar6 + 0x20,ptVar6,ptVar6 + 0x10);
      tMatrix::RotLocalZ((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)),fVar18);
      puVar9 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50));
      puVar9[2] = 0;
      puVar9[1] = 0;
      *puVar9 = 0x3f800000;
      *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x10) = 0;
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar8 + 0x14) = fVar10 - *(float *)(iVar8 + 0x34);
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar8 + 0x18) = fVar4 - *(float *)(iVar8 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)((int)param_1 + 0x50) + 0x10));
      ptVar6 = (tVector *)(iVar2 + *(int *)((int)param_1 + 0x50));
      tVector::Cross(ptVar6 + 0x20,ptVar6,ptVar6 + 0x10);
      tMatrix::RotLocalZ((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)),fVar18);
      iVar2 = iVar2 + 0xa8;
    } while (iVar5 != (int)uVar19);
  }
  iVar1 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar1 + -1) {
    iVar5 = 0;
    iVar2 = 0;
    do {
      iVar5 = iVar5 + 1;
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x4c);
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar10 = *(float *)(iVar8 + 0x34);
      fVar11 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar10 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar11 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x4c);
      uVar20 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      *(undefined4 *)(iVar1 + 0x8c) = uVar20;
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x50);
      iVar8 = iVar2 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar10 = *(float *)(iVar8 + 0x34);
      fVar11 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar10 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar11 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x50);
      uVar20 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar1 + 0x8c) = uVar20;
      iVar1 = *(int *)((int)param_1 + 0x38);
    } while (iVar5 < iVar1 + -1);
  }
  iVar1 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar1 * 0xa8;
  *(undefined4 *)(iVar1 + 0x84) = 0;
  *(undefined4 *)(iVar1 + 0x80) = 0;
  *(undefined4 *)(iVar1 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar1 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar1 + 0x84) = 0;
  *(undefined4 *)(iVar1 + 0x80) = 0;
  *(undefined4 *)(iVar1 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
