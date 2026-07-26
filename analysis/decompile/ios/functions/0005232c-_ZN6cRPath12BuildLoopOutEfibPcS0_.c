/*
 * mangled: _ZN6cRPath12BuildLoopOutEfibPcS0_
 * demangled: cRPath::BuildLoopOut(float, int, bool, char*, char*)
 * address: 0005232c
 * size: 2560
 */

/* cRPath::BuildLoopOut(float, int, bool, char*, char*) */

void cRPath::BuildLoopOut(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  tVector *ptVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint in_fpscr;
  float fVar6;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined1 *puVar12;
  float fVar13;
  float fVar14;
  int iVar16;
  undefined8 uVar15;

  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x2c) = 0x1d;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  iVar16 = (int)((float)param_2 * 6.2831855);
  fVar14 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
  uVar15 = CONCAT44(iVar16,fVar14);
  iVar3 = iVar16 + 0xe;
  *(int *)((int)param_1 + 0x38) = iVar3;
  fVar14 = fVar14 / 6.2831855;
  uVar7 = VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar7;
  uVar7 = RShellMemoryMalloc(iVar3 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar7;
  uVar7 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar7;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar1 = 0;
    iVar3 = 0;
    do {
      iVar1 = iVar1 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
      iVar4 = *(int *)((int)param_1 + 0x4c) + iVar3;
      iVar3 = iVar3 + 0xa8;
      *(undefined4 *)(iVar4 + 0x9c) = 0x3f800000;
    } while (iVar1 < *(int *)((int)param_1 + 0x38));
  }
  iVar1 = 0;
  iVar3 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 1;
  do {
    puVar12 = &DAT_40800000;
    fVar8 = (float)VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar10 = 0.3;
    fVar9 = 0.0;
    fVar13 = 0.49;
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                       (byte)(in_fpscr >> 0x16) & 3);
    iVar1 = iVar1 + 1;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x90) =
         (fVar6 * 0.5 - 4.0) - (fVar8 / 9.0) * 0.3;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)));
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x34) = fVar9;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x38) = fVar8;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar3 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x90);
    *(float *)(*(int *)((int)param_1 + 0x50) + iVar3 + 0x34) = fVar13;
    *(float *)(*(int *)((int)param_1 + 0x50) + iVar3 + 0x38) = fVar8;
    iVar4 = *(int *)((int)param_1 + 0x50) + iVar3;
    iVar3 = iVar3 + 0xa8;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  } while (iVar1 != 10);
  fVar8 = -0.5;
  iVar3 = (iVar16 + 10) * 0xa8;
  fVar6 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  fVar11 = -fVar14;
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x90) = (float)puVar12 + fVar6 * -0.5 + fVar10;
  *(float *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x98) = fVar9;
  *(float *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x94) = fVar9;
  *(float *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0xa0) = fVar9;
  *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)));
  iVar1 = iVar3 + *(int *)((int)param_1 + 0x4c);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(float *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x34) = fVar9;
  *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x38) = 0x41200000;
  *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(float *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x34) = fVar13;
  *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x38) = 0x41200000;
  *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  iVar1 = (iVar16 + 0xb) * 0xa8;
  fVar6 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x90) = (float)puVar12 + fVar6 * fVar8 + 0.2;
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x98) = fVar9;
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x94) = fVar9;
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0xa0) = fVar9;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x4c)));
  iVar4 = iVar1 + *(int *)((int)param_1 + 0x4c);
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x34) = fVar9;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x38) = 0x41300000;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x34) = fVar13;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x38) = 0x41300000;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  iVar1 = (iVar16 + 0xc) * 0xa8;
  fVar6 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x90) = (float)puVar12 + fVar6 * fVar8 + 0.1;
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x98) = fVar9;
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x94) = fVar9;
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0xa0) = fVar9;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x4c)));
  iVar4 = iVar1 + *(int *)((int)param_1 + 0x4c);
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x34) = fVar9;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x38) = 0x41400000;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(float *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x34) = fVar13;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x38) = 0x41400000;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  iVar16 = (iVar16 + 0xd) * 0xa8;
  fVar6 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar16 + 0x90) = (float)puVar12 + fVar6 * fVar8 + fVar9
  ;
  *(float *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0x98) = fVar9;
  *(float *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0x94) = fVar9;
  *(float *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0xa0) = fVar9;
  *(undefined4 *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar16 + *(int *)((int)param_1 + 0x4c)));
  iVar1 = iVar16 + *(int *)((int)param_1 + 0x4c);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(float *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0x34) = fVar9;
  *(undefined4 *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0x38) = 0x41500000;
  *(undefined4 *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar16 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar16 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar16 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(float *)(iVar16 + *(int *)((int)param_1 + 0x50) + 0x34) = fVar13;
  *(undefined4 *)(iVar16 + *(int *)((int)param_1 + 0x50) + 0x38) = 0x41500000;
  *(undefined4 *)(iVar16 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  if (0 < (int)((ulonglong)uVar15 >> 0x20)) {
    fVar13 = fVar14 + fVar13;
    iVar16 = 0;
    iVar1 = 0x690;
    do {
      fVar6 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
      iVar4 = *(int *)((int)param_1 + 0x4c);
      fVar9 = (fVar6 * 6.2831855) / (float)uVar15;
      *(float *)(iVar1 + iVar4 + 0x90) =
           *(float *)(iVar4 + 0x90) +
           (fVar6 * (*(float *)(iVar4 + iVar3 + 0x90) - *(float *)(iVar4 + 0x90))) / (float)uVar15;
      iVar4 = iVar1 + *(int *)((int)param_1 + 0x4c);
      fVar8 = *(float *)(iVar4 + 0x90);
      fVar6 = (float)Sin(fVar9 * 0.5 + 4.712389);
      *(float *)(iVar4 + 0x90) = fVar8 + fVar6 * 0.3;
      fVar8 = 10.0;
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x4c)));
      iVar4 = iVar1 + *(int *)((int)param_1 + 0x4c);
      *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
      iVar4 = *(int *)((int)param_1 + 0x4c);
      fVar6 = (float)Sin(fVar9);
      *(float *)(iVar1 + iVar4 + 0x38) = fVar8 + fVar6 * fVar14;
      iVar4 = *(int *)((int)param_1 + 0x4c);
      fVar6 = (float)Cos(fVar9);
      *(float *)(iVar1 + iVar4 + 0x34) = fVar11 + fVar6 * fVar14;
      tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x50)));
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x30) =
           *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x90);
      iVar4 = *(int *)((int)param_1 + 0x50);
      fVar6 = (float)Sin(fVar9);
      *(float *)(iVar1 + iVar4 + 0x38) = fVar8 + fVar6 * fVar13;
      iVar4 = *(int *)((int)param_1 + 0x50);
      fVar6 = (float)Cos(fVar9);
      *(float *)(iVar1 + iVar4 + 0x34) = fVar11 + fVar6 * fVar13;
      puVar5 = (undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c));
      puVar5[2] = 0;
      puVar5[1] = 0;
      *puVar5 = 0x3f800000;
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x10) = 0;
      iVar4 = iVar1 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar4 + 0x14) = -(fVar11 - *(float *)(iVar4 + 0x34));
      iVar4 = iVar1 + *(int *)((int)param_1 + 0x4c);
      *(float *)(iVar4 + 0x18) = -(fVar8 - *(float *)(iVar4 + 0x38));
      tVector::Normalize((tVector *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x10));
      ptVar2 = (tVector *)(iVar1 + *(int *)((int)param_1 + 0x4c));
      tVector::Cross(ptVar2 + 0x20,ptVar2,ptVar2 + 0x10);
      puVar5 = (undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50));
      puVar5[2] = 0;
      puVar5[1] = 0;
      *puVar5 = 0x3f800000;
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x10) = 0;
      iVar4 = iVar1 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar4 + 0x14) = -(fVar11 - *(float *)(iVar4 + 0x34));
      iVar4 = iVar1 + *(int *)((int)param_1 + 0x50);
      *(float *)(iVar4 + 0x18) = -(fVar8 - *(float *)(iVar4 + 0x38));
      tVector::Normalize((tVector *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x10));
      ptVar2 = (tVector *)(iVar1 + *(int *)((int)param_1 + 0x50));
      tVector::Cross(ptVar2 + 0x20,ptVar2,ptVar2 + 0x10);
      iVar1 = iVar1 + 0xa8;
      iVar16 = iVar16 + 1;
    } while (iVar16 != (int)((ulonglong)uVar15 >> 0x20));
  }
  iVar3 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar3 + -1) {
    iVar1 = 0;
    iVar16 = 0;
    do {
      iVar1 = iVar1 + 1;
      iVar3 = *(int *)((int)param_1 + 0x4c) + iVar16;
      iVar4 = *(int *)((int)param_1 + 0x4c) + 0xa8 + iVar16;
      fVar14 = *(float *)(iVar4 + 0x34);
      fVar6 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar14 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar6 - *(float *)(iVar3 + 0x38);
      iVar3 = iVar16 + *(int *)((int)param_1 + 0x4c);
      uVar7 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      *(undefined4 *)(iVar3 + 0x8c) = uVar7;
      iVar3 = *(int *)((int)param_1 + 0x50) + iVar16;
      iVar4 = *(int *)((int)param_1 + 0x50) + 0xa8 + iVar16;
      fVar14 = *(float *)(iVar4 + 0x34);
      fVar6 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar14 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar6 - *(float *)(iVar3 + 0x38);
      iVar3 = iVar16 + *(int *)((int)param_1 + 0x50);
      uVar7 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar16 = iVar16 + 0xa8;
      *(undefined4 *)(iVar3 + 0x8c) = uVar7;
      iVar3 = *(int *)((int)param_1 + 0x38);
    } while (iVar1 < iVar3 + -1);
  }
  iVar3 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar3 * 0xa8;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar3 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
