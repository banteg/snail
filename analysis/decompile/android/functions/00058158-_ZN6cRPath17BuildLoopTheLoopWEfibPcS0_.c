/*
 * mangled: _ZN6cRPath17BuildLoopTheLoopWEfibPcS0_
 * demangled: cRPath::BuildLoopTheLoopW(float, int, bool, char*, char*)
 * address: 00058158
 * size: 1428
 */

/* cRPath::BuildLoopTheLoopW(float, int, bool, char*, char*) */

void cRPath::BuildLoopTheLoopW(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  tVector *ptVar3;
  undefined4 uVar4;
  int iVar5;
  tMatrix *ptVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float fVar12;
  float fVar13;
  int iVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float unaff_s24;
  float fVar22;

  fVar12 = DAT_00058558;
  fVar20 = DAT_00058554;
  fVar13 = (float)(uint)param_3 * DAT_00058554;
  bVar11 = param_4 == (char *)0x4;
  uVar4 = 0;
  iVar8 = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(float *)(param_2 + 0x44) = fVar12;
  if (bVar11) {
    uVar4 = 7;
  }
  *(char **)(param_2 + 0x48) = param_4;
  fVar22 = DAT_0005858c;
  if (bVar11) {
    *(undefined4 *)(param_2 + 0x2c) = uVar4;
    fVar22 = unaff_s24;
  }
  *(undefined1 *)(param_2 + 0x30) = 0;
  if (bVar11) {
    fVar22 = DAT_0005855c;
  }
  *(undefined4 *)(param_2 + 0x34) = 0;
  fVar2 = DAT_0005858c;
  fVar18 = DAT_0005856c;
  fVar21 = DAT_00058568;
  fVar17 = DAT_00058564;
  fVar15 = DAT_00058560;
  iVar9 = 0;
  iVar14 = (int)fVar13;
  fVar13 = (float)VectorSignedToFloat(iVar14,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar14 + 0xe;
  uVar4 = VectorSignedToFloat(iVar14 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar4;
  fVar20 = fVar13 / fVar20;
  GetNodes((cRPath *)param_2);
  iVar5 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar19 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    uVar4 = *(undefined4 *)(param_2 + 0x48);
    ptVar6 = (tMatrix *)(iVar5 + iVar8);
    *(float *)(ptVar6 + 0x98) = fVar2;
    *(float *)(ptVar6 + 0x94) = fVar2;
    *(float *)(ptVar6 + 0xa0) = fVar2;
    *(float *)(ptVar6 + 0x9c) = fVar12;
    iVar9 = iVar9 + 1;
    fVar16 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar6 + 0x90) = (fVar16 * fVar15 - fVar17) - fVar22 * (fVar19 / fVar21);
    tMatrix::Identity(ptVar6);
    iVar5 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar8;
    *(float *)(iVar7 + 0x8c) = fVar12;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar2;
    *(float *)(iVar7 + 0x38) = fVar19;
    tMatrix::Identity((tMatrix *)(iVar5 + iVar8));
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar7 = *(int *)(param_2 + 0x50) + iVar8;
    *(float *)(iVar7 + 0x38) = fVar19;
    *(float *)(iVar7 + 0x8c) = fVar12;
    uVar4 = *(undefined4 *)(iVar5 + iVar8 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar18;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar7 + 0x30) = uVar4;
    fVar1 = DAT_00058574;
    fVar19 = DAT_00058570;
    fVar16 = DAT_00058564;
  } while (iVar9 != 7);
  iVar9 = 0;
  iVar8 = (iVar14 + 7) * 0xa8;
  do {
    fVar15 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    uVar4 = *(undefined4 *)(param_2 + 0x48);
    ptVar6 = (tMatrix *)(iVar5 + iVar8);
    *(float *)(ptVar6 + 0x98) = fVar2;
    *(float *)(ptVar6 + 0x94) = fVar2;
    *(float *)(ptVar6 + 0xa0) = fVar2;
    *(float *)(ptVar6 + 0x9c) = fVar12;
    fVar17 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar6 + 0x90) = fVar16 + fVar17 * fVar19 + fVar22 * (fVar12 - fVar15 / fVar1);
    tMatrix::Identity(ptVar6);
    uVar4 = VectorSignedToFloat(iVar9 + 7,(byte)(in_fpscr >> 0x16) & 3);
    iVar9 = iVar9 + 1;
    iVar5 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar8;
    *(float *)(iVar7 + 0x8c) = fVar12;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar2;
    *(undefined4 *)(iVar7 + 0x38) = uVar4;
    fVar17 = (float)tMatrix::Identity((tMatrix *)(iVar5 + iVar8));
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar7 = *(int *)(param_2 + 0x50) + iVar8;
    *(undefined4 *)(iVar7 + 0x38) = uVar4;
    *(float *)(iVar7 + 0x8c) = fVar12;
    uVar4 = *(undefined4 *)(iVar5 + iVar8 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar18;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar7 + 0x30) = uVar4;
    fVar15 = DAT_00058568;
  } while (iVar9 != 7);
  if (0 < iVar14) {
    iVar8 = 0x498;
    iVar5 = 0;
    do {
      fVar21 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = iVar5 + 1;
      fVar17 = (float)Sin(fVar17);
      fVar17 = (float)Sin(fVar17);
      iVar9 = *(int *)(param_2 + 0x4c);
      fVar21 = *(float *)(iVar9 + 0x90) +
               (fVar21 * (*(float *)(iVar9 + (iVar14 + 0xd) * 0xa8 + 0x90) -
                         *(float *)(iVar9 + 0x90))) / fVar13;
      *(float *)(iVar9 + iVar8 + 0x90) = fVar21;
      fVar17 = (float)Sin(fVar17);
      ptVar6 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar8);
      *(float *)(ptVar6 + 0x98) = fVar2;
      *(float *)(ptVar6 + 0x94) = fVar2;
      *(float *)(ptVar6 + 0xa0) = fVar2;
      *(float *)(ptVar6 + 0x9c) = fVar12;
      *(float *)(iVar9 + iVar8 + 0x90) = fVar21 + fVar17 * fVar22;
      fVar17 = DAT_0005856c;
      fVar21 = (float)tMatrix::Identity(ptVar6);
      iVar9 = *(int *)(param_2 + 0x4c) + iVar8;
      *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
      fVar21 = (float)Sin(fVar21);
      iVar7 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar9 + 0x38) = fVar15 + fVar21 * fVar20;
      fVar21 = (float)Cos(extraout_s0);
      iVar9 = *(int *)(param_2 + 0x50);
      *(float *)(iVar7 + iVar8 + 0x34) = fVar20 - fVar21 * fVar20;
      fVar21 = (float)tMatrix::Identity((tMatrix *)(iVar9 + iVar8));
      iVar9 = *(int *)(param_2 + 0x50) + iVar8;
      *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar8 + 0x90);
      fVar21 = (float)Sin(fVar21);
      iVar7 = *(int *)(param_2 + 0x50);
      *(float *)(iVar9 + 0x38) = fVar15 + fVar21 * (fVar20 - fVar17);
      fVar21 = (float)Cos(extraout_s0_00);
      iVar9 = *(int *)(param_2 + 0x4c) + iVar8;
      fVar18 = *(float *)(iVar9 + 0x38);
      *(float *)(*(int *)(param_2 + 0x4c) + iVar8) = fVar12;
      *(float *)(iVar9 + 8) = fVar2;
      *(float *)(iVar9 + 4) = fVar2;
      *(float *)(iVar9 + 0x10) = fVar2;
      *(float *)(iVar9 + 0x18) = fVar15 - fVar18;
      *(float *)(iVar7 + iVar8 + 0x34) = fVar20 - (fVar20 - fVar17) * fVar21;
      *(float *)(iVar9 + 0x14) = fVar20 - *(float *)(iVar9 + 0x34);
      tVector::Normalize((tVector *)(iVar9 + 0x10));
      ptVar3 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar8);
      fVar17 = (float)tVector::Cross(ptVar3 + 0x20,ptVar3,ptVar3 + 0x10);
      tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar8),fVar17);
      iVar9 = *(int *)(param_2 + 0x50) + iVar8;
      fVar17 = *(float *)(iVar9 + 0x34);
      fVar21 = *(float *)(iVar9 + 0x38);
      *(float *)(*(int *)(param_2 + 0x50) + iVar8) = fVar12;
      *(float *)(iVar9 + 8) = fVar2;
      *(float *)(iVar9 + 4) = fVar2;
      *(float *)(iVar9 + 0x10) = fVar2;
      *(float *)(iVar9 + 0x14) = fVar20 - fVar17;
      *(float *)(iVar9 + 0x18) = fVar15 - fVar21;
      tVector::Normalize((tVector *)(iVar9 + 0x10));
      ptVar3 = (tVector *)(*(int *)(param_2 + 0x50) + iVar8);
      fVar17 = (float)tVector::Cross(ptVar3 + 0x20,ptVar3,ptVar3 + 0x10);
      ptVar6 = (tMatrix *)(*(int *)(param_2 + 0x50) + iVar8);
      iVar8 = iVar8 + 0xa8;
      fVar17 = (float)tMatrix::RotLocalZ(ptVar6,fVar17);
    } while (iVar5 < iVar14);
    iVar5 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar8 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar14 = 0;
    iVar9 = 0;
    while( true ) {
      iVar10 = iVar9 + 0xa8;
      iVar7 = iVar5 + iVar9;
      iVar5 = iVar5 + iVar10;
      fVar12 = *(float *)(iVar5 + 0x38);
      fVar20 = *(float *)(iVar5 + 0x34);
      iVar14 = iVar14 + 1;
      *(float *)(iVar7 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar20 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar12 - *(float *)(iVar7 + 0x38);
      uVar4 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar9 = *(int *)(param_2 + 0x50) + iVar9;
      iVar8 = *(int *)(param_2 + 0x50) + iVar10;
      fVar12 = *(float *)(iVar8 + 0x38);
      fVar20 = *(float *)(iVar8 + 0x34);
      fVar13 = *(float *)(iVar9 + 0x38);
      *(float *)(iVar9 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x84) = fVar20 - *(float *)(iVar9 + 0x34);
      *(undefined4 *)(iVar7 + 0x8c) = uVar4;
      *(float *)(iVar9 + 0x88) = fVar12 - fVar13;
      uVar4 = tVector::Normalize((tVector *)(iVar9 + 0x80));
      iVar8 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar9 + 0x8c) = uVar4;
      if (iVar8 <= iVar14) break;
      iVar5 = *(int *)(param_2 + 0x4c);
      iVar9 = iVar10;
    }
    iVar5 = *(int *)(param_2 + 0x4c);
  }
  fVar20 = DAT_0005858c;
  uVar4 = DAT_00058588;
  iVar9 = *(int *)(param_2 + 0x50) + iVar8 * 0xa8;
  iVar5 = iVar5 + iVar8 * 0xa8;
  *(undefined4 *)(iVar5 + 0x8c) = DAT_00058588;
  *(undefined4 *)(iVar5 + 0x88) = uVar4;
  *(float *)(iVar5 + 0x84) = fVar20;
  *(float *)(iVar5 + 0x80) = fVar20;
  *(undefined4 *)(iVar9 + 0x8c) = uVar4;
  *(float *)(iVar9 + 0x80) = fVar20;
  *(undefined4 *)(iVar9 + 0x88) = uVar4;
  *(float *)(iVar9 + 0x84) = fVar20;
  CalcLengthZ((cRPath *)param_2);
  return;
}
