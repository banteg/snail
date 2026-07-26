/*
 * mangled: _ZN6cRPath12BuildLoopBowEfibPcS0_
 * demangled: cRPath::BuildLoopBow(float, int, bool, char*, char*)
 * address: 0005488c
 * size: 2196
 */

/* cRPath::BuildLoopBow(float, int, bool, char*, char*) */

void cRPath::BuildLoopBow(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  tVector *ptVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 *puVar11;
  uint in_fpscr;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  undefined4 uVar17;
  float fVar18;
  float fVar19;
  longlong lVar20;
  undefined8 uVar21;
  tMatrix atStack_88 [104];

  uVar5 = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x2c) = 0;
  if (uVar5 == 4) {
    *(undefined4 *)((int)param_1 + 0x2c) = 0;
  }
  *(uint *)((int)param_1 + 0x48) = uVar5;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  lVar20 = (ulonglong)(uint)(int)((float)param_2 * 6.2831855) << 0x20;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  if (uVar5 == 4) {
    uVar21 = 0x3f000000;
  }
  else {
    uVar21 = 0;
  }
  iVar1 = (int)((float)param_2 * 6.2831855) + 0xe;
  *(int *)((int)param_1 + 0x38) = iVar1;
  uVar14 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar14;
  uVar14 = RShellMemoryMalloc(iVar1 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar14;
  uVar14 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar14;
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
    fVar15 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = iVar3 + 1;
    fVar12 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90) =
         (fVar12 * 0.5 - 4.0) - (float)uVar21 * (fVar15 / 7.0);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = fVar15;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    *(float *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x38) = fVar15;
    iVar6 = *(int *)((int)param_1 + 0x50) + iVar2;
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
  } while (iVar3 != 7);
  iVar3 = 0;
  iVar2 = (int)((ulonglong)lVar20 >> 0x20) * 0xa8 + 0x498;
  do {
    uVar17 = 0x3f800000;
    fVar12 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar15 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90) =
         fVar12 * -0.5 + 4.0 + (float)uVar21 * (1.0 - fVar15 / 6.0);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    iVar6 = iVar3 + 7;
    iVar3 = iVar3 + 1;
    uVar14 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = uVar14;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x8c) = uVar17;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x38) = uVar14;
    iVar6 = *(int *)((int)param_1 + 0x50) + iVar2;
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar6 + 0x8c) = uVar17;
  } while (iVar3 != 7);
  iVar2 = (int)((ulonglong)lVar20 >> 0x20);
  if (0 < iVar2) {
    fVar12 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    lVar20 = (ulonglong)(uint)fVar12 << 0x20;
    iVar3 = 0x498;
    iVar6 = 0;
    fVar12 = fVar12 / 6.2831855;
    fVar15 = fVar12 - 0.49;
    do {
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar13 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      fVar19 = 7.0;
      iVar6 = iVar6 + 1;
      fVar16 = (float)((ulonglong)lVar20 >> 0x20);
      fVar18 = (fVar13 * 6.2831855) / fVar16;
      *(float *)(iVar7 + iVar3 + 0x90) =
           *(float *)(iVar7 + 0x90) +
           (fVar13 * (*(float *)(iVar7 + iVar1 * 0xa8 + -0x18) - *(float *)(iVar7 + 0x90))) / fVar16
      ;
      lVar20 = CONCAT44(fVar16,fVar18 * 0.5);
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      fVar16 = *(float *)(iVar7 + 0x90);
      fVar13 = (float)Sin(fVar18 * 0.5 + 4.712389);
      *(float *)(iVar7 + 0x90) = fVar16 + fVar13 * (float)uVar21;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x98) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x94) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)));
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar13 = (float)Sin(fVar18);
      *(float *)(iVar3 + iVar7 + 0x38) = fVar19 + fVar13 * fVar12;
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar13 = (float)Cos(fVar18);
      *(float *)(iVar3 + iVar7 + 0x34) = fVar12 - fVar13 * fVar12;
      tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50)));
      *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar3 + 0x30) =
           *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x90);
      iVar7 = *(int *)((int)param_1 + 0x50);
      fVar13 = (float)Sin(fVar18);
      *(float *)(iVar3 + iVar7 + 0x38) = fVar19 + fVar13 * fVar15;
      iVar7 = *(int *)((int)param_1 + 0x50);
      fVar13 = (float)Cos(fVar18);
      *(float *)(iVar3 + iVar7 + 0x34) = fVar12 - fVar13 * fVar15;
      puVar8 = (undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c));
      puVar8[2] = 0;
      puVar8[1] = 0;
      *puVar8 = 0x3f800000;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x10) = 0;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar7 + 0x14) = fVar12 - *(float *)(iVar7 + 0x34);
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar7 + 0x18) = fVar19 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x10));
      ptVar4 = (tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c));
      tVector::Cross(ptVar4 + 0x20,ptVar4,ptVar4 + 0x10);
      puVar8 = (undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50));
      puVar8[2] = 0;
      puVar8[1] = 0;
      *puVar8 = 0x3f800000;
      *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar3 + 0x10) = 0;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar7 + 0x14) = fVar12 - *(float *)(iVar7 + 0x34);
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar7 + 0x18) = fVar19 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x10));
      ptVar4 = (tVector *)(iVar3 + *(int *)((int)param_1 + 0x50));
      tVector::Cross(ptVar4 + 0x20,ptVar4,ptVar4 + 0x10);
      tMatrix::Identity(atStack_88);
      fVar13 = (float)Sin((float)lVar20);
      fVar16 = (float)Sin((float)lVar20);
      tMatrix::RotLocalY(atStack_88,fVar13 * 0.5235988 * fVar16);
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar7 + 0x38) = *(float *)(iVar7 + 0x38) - fVar19;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar7 + 0x38) = *(float *)(iVar7 + 0x38) - fVar19;
      tMatrix::Multiply((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)),atStack_88);
      tMatrix::Multiply((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50)),atStack_88);
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar7 + 0x38) = *(float *)(iVar7 + 0x38) + fVar19;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar7 + 0x38) = *(float *)(iVar7 + 0x38) + fVar19;
      puVar8 = (undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3);
      puVar11 = (undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar3);
      uVar14 = puVar8[1];
      uVar17 = puVar8[2];
      uVar9 = puVar8[3];
      *puVar11 = *puVar8;
      puVar11[1] = uVar14;
      puVar11[2] = uVar17;
      puVar11[3] = uVar9;
      uVar14 = puVar8[5];
      uVar17 = puVar8[6];
      uVar9 = puVar8[7];
      puVar11[4] = puVar8[4];
      puVar11[5] = uVar14;
      puVar11[6] = uVar17;
      puVar11[7] = uVar9;
      uVar14 = puVar8[9];
      uVar17 = puVar8[10];
      uVar9 = puVar8[0xb];
      puVar11[8] = puVar8[8];
      puVar11[9] = uVar14;
      puVar11[10] = uVar17;
      puVar11[0xb] = uVar9;
      uVar14 = puVar8[0xd];
      uVar17 = puVar8[0xe];
      uVar9 = puVar8[0xf];
      puVar11[0xc] = puVar8[0xc];
      puVar11[0xd] = uVar14;
      puVar11[0xe] = uVar17;
      puVar11[0xf] = uVar9;
      iVar7 = iVar3 + *(int *)((int)param_1 + 0x50);
      iVar10 = iVar3 + *(int *)((int)param_1 + 0x4c);
      iVar3 = iVar3 + 0xa8;
      fVar16 = *(float *)(iVar10 + 0x14);
      fVar13 = *(float *)(iVar10 + 0x18);
      *(float *)(iVar7 + 0x30) = *(float *)(iVar7 + 0x30) + *(float *)(iVar10 + 0x10) * 0.49;
      *(float *)(iVar7 + 0x34) = *(float *)(iVar7 + 0x34) + fVar16 * 0.49;
      *(float *)(iVar7 + 0x38) = *(float *)(iVar7 + 0x38) + fVar13 * 0.49;
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
      fVar12 = *(float *)(iVar6 + 0x34);
      fVar15 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar12 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar15 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x4c);
      uVar14 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      *(undefined4 *)(iVar1 + 0x8c) = uVar14;
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x50);
      iVar6 = iVar2 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar12 = *(float *)(iVar6 + 0x34);
      fVar15 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar1 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar1 + 0x30);
      *(float *)(iVar1 + 0x84) = fVar12 - *(float *)(iVar1 + 0x34);
      *(float *)(iVar1 + 0x88) = fVar15 - *(float *)(iVar1 + 0x38);
      iVar1 = iVar2 + *(int *)((int)param_1 + 0x50);
      uVar14 = tVector::Normalize((tVector *)(iVar1 + 0x80));
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar1 + 0x8c) = uVar14;
      iVar1 = *(int *)((int)param_1 + 0x38);
    } while (iVar3 < iVar1 + -1);
  }
  iVar1 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar1 * 0xa8;
  *(undefined4 *)(iVar1 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x84) = 0;
  *(undefined4 *)(iVar1 + 0x80) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar1 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar1 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x84) = 0;
  *(undefined4 *)(iVar1 + 0x80) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
