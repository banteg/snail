/*
 * mangled: _ZN6cRPath16BuildLoopTheLoopEfibPcS0_
 * demangled: cRPath::BuildLoopTheLoop(float, int, bool, char*, char*)
 * address: 00050cf4
 * size: 1908
 */

/* cRPath::BuildLoopTheLoop(float, int, bool, char*, char*) */

void cRPath::BuildLoopTheLoop(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  tVector *ptVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  longlong lVar17;
  undefined8 uVar18;

  uVar5 = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x2c) = 0;
  if (uVar5 == 4) {
    *(undefined4 *)((int)param_1 + 0x2c) = 0;
  }
  *(uint *)((int)param_1 + 0x48) = uVar5;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  lVar17 = (ulonglong)(uint)(int)((float)param_2 * 6.2831855) << 0x20;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  if (uVar5 == 4) {
    uVar18 = 0x3e99999a;
  }
  else {
    uVar18 = 0;
  }
  iVar1 = (int)((float)param_2 * 6.2831855) + 0xe;
  *(int *)((int)param_1 + 0x38) = iVar1;
  uVar11 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar11;
  uVar11 = RShellMemoryMalloc(iVar1 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar11;
  uVar11 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar11;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar3 = 0;
    iVar2 = 0;
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar6 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar6 + 0x9c) = 0x3f800000;
    } while (iVar3 < *(int *)((int)param_1 + 0x38));
  }
  iVar3 = 0;
  iVar2 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 1;
  do {
    fVar12 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = iVar3 + 1;
    fVar9 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                       (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90) =
         (fVar9 * 0.5 - 4.0) - (float)uVar18 * (fVar12 / 7.0);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = fVar12;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    *(float *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x38) = fVar12;
    iVar6 = *(int *)((int)param_1 + 0x50) + iVar2;
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
  } while (iVar3 != 7);
  iVar3 = 0;
  iVar2 = (int)((ulonglong)lVar17 >> 0x20) * 0xa8 + 0x498;
  do {
    uVar14 = 0x3f800000;
    fVar9 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                       (byte)(in_fpscr >> 0x16) & 3);
    fVar12 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x90) =
         fVar9 * -0.5 + 4.0 + (float)uVar18 * (1.0 - fVar12 / 6.0);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
    iVar6 = iVar3 + 7;
    iVar3 = iVar3 + 1;
    uVar11 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar11;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x8c) = uVar14;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50) + 0x30) =
         *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x90);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar11;
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x50);
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar6 + 0x8c) = uVar14;
  } while (iVar3 != 7);
  iVar2 = (int)((ulonglong)lVar17 >> 0x20);
  if (0 < iVar2) {
    fVar12 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = 0x498;
    iVar6 = 0;
    fVar9 = fVar12 / 6.2831855;
    fVar16 = fVar9 - 0.49;
    do {
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar10 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      iVar6 = iVar6 + 1;
      fVar15 = (fVar10 * 6.2831855) / fVar12;
      *(float *)(iVar7 + iVar3 + 0x90) =
           *(float *)(iVar7 + 0x90) +
           (fVar10 * (*(float *)(iVar7 + iVar1 * 0xa8 + -0x18) - *(float *)(iVar7 + 0x90))) / fVar12
      ;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      fVar13 = *(float *)(iVar7 + 0x90);
      fVar10 = (float)Sin(fVar15 * 0.5 + 4.712389);
      *(float *)(iVar7 + 0x90) = fVar13 + fVar10 * (float)uVar18;
      fVar13 = 7.0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x98) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x94) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)));
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar10 = (float)Sin(fVar15);
      *(float *)(iVar3 + iVar7 + 0x38) = fVar13 + fVar10 * fVar9;
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar10 = (float)Cos(fVar15);
      *(float *)(iVar3 + iVar7 + 0x34) = fVar9 - fVar10 * fVar9;
      tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50)));
      *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar3 + 0x30) =
           *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x90);
      iVar7 = *(int *)((int)param_1 + 0x50);
      fVar10 = (float)Sin(fVar15);
      *(float *)(iVar3 + iVar7 + 0x38) = fVar13 + fVar10 * fVar16;
      iVar7 = *(int *)((int)param_1 + 0x50);
      fVar10 = (float)Cos(fVar15);
      *(float *)(iVar3 + iVar7 + 0x34) = fVar9 - fVar10 * fVar16;
      puVar8 = (undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c));
      puVar8[2] = 0;
      puVar8[1] = 0;
      *puVar8 = 0x3f800000;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x10) = 0;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar7 + 0x14) = fVar9 - *(float *)(iVar7 + 0x34);
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar7 + 0x18) = fVar13 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x10));
      ptVar4 = (tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c));
      tVector::Cross(ptVar4 + 0x20,ptVar4,ptVar4 + 0x10);
      puVar8 = (undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50));
      puVar8[2] = 0;
      puVar8[1] = 0;
      *puVar8 = 0x3f800000;
      *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar3 + 0x10) = 0;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar7 + 0x14) = fVar9 - *(float *)(iVar7 + 0x34);
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar7 + 0x18) = fVar13 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x10));
      ptVar4 = (tVector *)(iVar3 + *(int *)((int)param_1 + 0x50));
      tVector::Cross(ptVar4 + 0x20,ptVar4,ptVar4 + 0x10);
      iVar3 = iVar3 + 0xa8;
    } while (iVar6 != iVar2);
  }
  iVar1 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar1 + -1) {
    iVar3 = 0;
    iVar2 = 0;
    do {
      iVar3 = iVar3 + 1;
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x4c);
      iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar9 = *(float *)(iVar6 + 0x34);
      fVar12 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar9 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar12 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x4c);
      uVar11 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      *(undefined4 *)(iVar1 + 0x8c) = uVar11;
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x50);
      iVar6 = iVar2 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar9 = *(float *)(iVar6 + 0x34);
      fVar12 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar9 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar12 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x50);
      uVar11 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar1 + 0x8c) = uVar11;
      iVar1 = *(int *)((int)param_1 + 0x38);
    } while (iVar3 < iVar1 + -1);
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
