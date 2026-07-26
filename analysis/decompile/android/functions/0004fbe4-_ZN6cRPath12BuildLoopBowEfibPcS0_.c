/*
 * mangled: _ZN6cRPath12BuildLoopBowEfibPcS0_
 * demangled: cRPath::BuildLoopBow(float, int, bool, char*, char*)
 * address: 0004fbe4
 * size: 1624
 */

/* cRPath::BuildLoopBow(float, int, bool, char*, char*) */

void cRPath::BuildLoopBow(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  tMatrix *ptVar7;
  undefined4 *puVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float fVar12;
  float fVar13;
  int iVar14;
  undefined4 uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  tMatrix atStack_a8 [68];

  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  iVar5 = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar9 = 0;
  iVar14 = (int)((float)(uint)param_3 * 6.2831855);
  fVar19 = (float)VectorSignedToFloat(iVar14,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar14 + 0xe;
  uVar15 = VectorSignedToFloat(iVar14 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar15;
  fVar18 = fVar19 / 6.2831855;
  fVar12 = 0.0;
  if (param_4 == (char *)0x4) {
    fVar12 = 0.5;
  }
  GetNodes((cRPath *)param_2);
  iVar6 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar17 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    uVar15 = *(undefined4 *)(param_2 + 0x48);
    ptVar7 = (tMatrix *)(iVar6 + iVar5);
    *(undefined4 *)(ptVar7 + 0x98) = 0;
    *(undefined4 *)(ptVar7 + 0x94) = 0;
    *(undefined4 *)(ptVar7 + 0xa0) = 0;
    *(undefined4 *)(ptVar7 + 0x9c) = 0x3f800000;
    iVar9 = iVar9 + 1;
    fVar16 = (float)VectorSignedToFloat(uVar15,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar7 + 0x90) = (fVar16 * 0.5 - 4.0) - fVar12 * (fVar17 / 7.0);
    tMatrix::Identity(ptVar7);
    iVar6 = *(int *)(param_2 + 0x50);
    iVar3 = *(int *)(param_2 + 0x4c) + iVar5;
    *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0;
    *(float *)(iVar3 + 0x38) = fVar17;
    tMatrix::Identity((tMatrix *)(iVar6 + iVar5));
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar3 = *(int *)(param_2 + 0x50) + iVar5;
    *(float *)(iVar3 + 0x38) = fVar17;
    *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
    uVar15 = *(undefined4 *)(iVar6 + iVar5 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar5 = iVar5 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = uVar15;
  } while (iVar9 != 7);
  iVar9 = 0;
  iVar5 = (iVar14 + 7) * 0xa8;
  do {
    fVar16 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    uVar15 = *(undefined4 *)(param_2 + 0x48);
    ptVar7 = (tMatrix *)(iVar6 + iVar5);
    *(undefined4 *)(ptVar7 + 0x98) = 0;
    *(undefined4 *)(ptVar7 + 0x94) = 0;
    *(undefined4 *)(ptVar7 + 0xa0) = 0;
    *(undefined4 *)(ptVar7 + 0x9c) = 0x3f800000;
    fVar17 = (float)VectorSignedToFloat(uVar15,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar7 + 0x90) = fVar17 * -0.5 + 4.0 + fVar12 * (1.0 - fVar16 / 6.0);
    tMatrix::Identity(ptVar7);
    uVar15 = VectorSignedToFloat(iVar9 + 7,(byte)(in_fpscr >> 0x16) & 3);
    iVar9 = iVar9 + 1;
    iVar6 = *(int *)(param_2 + 0x50);
    iVar3 = *(int *)(param_2 + 0x4c) + iVar5;
    *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0;
    *(undefined4 *)(iVar3 + 0x38) = uVar15;
    fVar16 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar5));
    iVar11 = *(int *)(param_2 + 0x50);
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar3 = iVar11 + iVar5;
    *(undefined4 *)(iVar3 + 0x38) = uVar15;
    *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
    uVar15 = *(undefined4 *)(iVar6 + iVar5 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar5 = iVar5 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = uVar15;
  } while (iVar9 != 7);
  if (0 < iVar14) {
    iVar5 = 0x498;
    iVar9 = 0;
    do {
      fVar17 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
      iVar9 = iVar9 + 1;
      fVar17 = *(float *)(iVar6 + 0x90) +
               (fVar17 * (*(float *)(iVar6 + (iVar14 + 0xd) * 0xa8 + 0x90) -
                         *(float *)(iVar6 + 0x90))) / fVar19;
      *(float *)(iVar6 + iVar5 + 0x90) = fVar17;
      fVar16 = (float)Sin(fVar16);
      ptVar7 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar5);
      *(undefined4 *)(ptVar7 + 0x98) = 0;
      *(undefined4 *)(ptVar7 + 0x94) = 0;
      *(undefined4 *)(ptVar7 + 0xa0) = 0;
      *(undefined4 *)(ptVar7 + 0x9c) = 0x3f800000;
      *(float *)(iVar6 + iVar5 + 0x90) = fVar17 + fVar16 * fVar12;
      fVar16 = (float)tMatrix::Identity(ptVar7);
      iVar6 = *(int *)(param_2 + 0x4c) + iVar5;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
      fVar16 = (float)Sin(fVar16);
      iVar3 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar6 + 0x38) = fVar16 * fVar18 + 7.0;
      fVar16 = (float)Cos(extraout_s0);
      iVar6 = *(int *)(param_2 + 0x50);
      *(float *)(iVar3 + iVar5 + 0x34) = fVar18 - fVar16 * fVar18;
      fVar16 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar5));
      iVar6 = *(int *)(param_2 + 0x50) + iVar5;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar5 + 0x90);
      fVar16 = (float)Sin(fVar16);
      iVar3 = *(int *)(param_2 + 0x50);
      *(float *)(iVar6 + 0x38) = fVar16 * (fVar18 - 0.49) + 7.0;
      fVar16 = (float)Cos(extraout_s0_00);
      iVar6 = *(int *)(param_2 + 0x4c) + iVar5;
      fVar17 = *(float *)(iVar6 + 0x38);
      *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar5) = 0x3f800000;
      *(undefined4 *)(iVar6 + 8) = 0;
      *(undefined4 *)(iVar6 + 4) = 0;
      *(undefined4 *)(iVar6 + 0x10) = 0;
      *(float *)(iVar6 + 0x18) = 7.0 - fVar17;
      *(float *)(iVar3 + iVar5 + 0x34) = fVar18 - (fVar18 - 0.49) * fVar16;
      *(float *)(iVar6 + 0x14) = fVar18 - *(float *)(iVar6 + 0x34);
      tVector::Normalize((tVector *)(iVar6 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar5);
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      iVar6 = *(int *)(param_2 + 0x50);
      iVar3 = iVar6 + iVar5;
      fVar16 = *(float *)(iVar3 + 0x34);
      fVar17 = *(float *)(iVar3 + 0x38);
      *(undefined4 *)(iVar3 + 8) = 0;
      *(undefined4 *)(iVar3 + 4) = 0;
      *(undefined4 *)(iVar3 + 0x10) = 0;
      *(undefined4 *)(iVar6 + iVar5) = 0x3f800000;
      *(float *)(iVar3 + 0x14) = fVar18 - fVar16;
      *(float *)(iVar3 + 0x18) = 7.0 - fVar17;
      tVector::Normalize((tVector *)(iVar3 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar5);
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      fVar16 = (float)tMatrix::Identity(atStack_a8);
      fVar16 = (float)Sin(fVar16);
      fVar16 = (float)Sin(fVar16);
      tMatrix::RotLocalY(atStack_a8,fVar16);
      ptVar7 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar5);
      iVar6 = *(int *)(param_2 + 0x50) + iVar5;
      *(float *)(ptVar7 + 0x38) = *(float *)(ptVar7 + 0x38) - 7.0;
      *(float *)(iVar6 + 0x38) = *(float *)(iVar6 + 0x38) - 7.0;
      tMatrix::Multiply(ptVar7,atStack_a8);
      fVar16 = (float)tMatrix::Multiply((tMatrix *)(*(int *)(param_2 + 0x50) + iVar5),atStack_a8);
      iVar6 = *(int *)(param_2 + 0x4c);
      iVar11 = *(int *)(param_2 + 0x50);
      puVar10 = (undefined4 *)(iVar6 + iVar5);
      puVar8 = (undefined4 *)(iVar11 + iVar5);
      iVar5 = iVar5 + 0xa8;
      puVar10[0xe] = (float)puVar10[0xe] + 7.0;
      puVar8[0xe] = (float)puVar8[0xe] + 7.0;
      uVar15 = puVar10[1];
      uVar2 = puVar10[2];
      uVar4 = puVar10[3];
      *puVar8 = *puVar10;
      puVar8[1] = uVar15;
      puVar8[2] = uVar2;
      puVar8[3] = uVar4;
      uVar15 = puVar10[5];
      uVar2 = puVar10[6];
      uVar4 = puVar10[7];
      puVar8[4] = puVar10[4];
      puVar8[5] = uVar15;
      puVar8[6] = uVar2;
      puVar8[7] = uVar4;
      uVar15 = puVar10[9];
      uVar2 = puVar10[10];
      uVar4 = puVar10[0xb];
      puVar8[8] = puVar10[8];
      puVar8[9] = uVar15;
      puVar8[10] = uVar2;
      puVar8[0xb] = uVar4;
      uVar15 = puVar10[0xd];
      uVar2 = puVar10[0xe];
      uVar4 = puVar10[0xf];
      puVar8[0xc] = puVar10[0xc];
      puVar8[0xd] = uVar15;
      puVar8[0xe] = uVar2;
      puVar8[0xf] = uVar4;
      fVar17 = (float)puVar10[5];
      fVar13 = (float)puVar10[6];
      puVar8[0xc] = (float)puVar8[0xc] + (float)puVar10[4] * 0.49;
      puVar8[0xd] = (float)puVar8[0xd] + fVar17 * 0.49;
      puVar8[0xe] = (float)puVar8[0xe] + fVar13 * 0.49;
    } while (iVar9 < iVar14);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar5 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar14 = 0;
    iVar9 = 0;
    while( true ) {
      iVar11 = iVar9 + 0xa8;
      iVar3 = iVar6 + iVar9;
      iVar6 = iVar6 + iVar11;
      fVar18 = *(float *)(iVar6 + 0x38);
      fVar12 = *(float *)(iVar6 + 0x34);
      iVar14 = iVar14 + 1;
      *(float *)(iVar3 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar12 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar18 - *(float *)(iVar3 + 0x38);
      uVar15 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar9 = *(int *)(param_2 + 0x50) + iVar9;
      iVar5 = *(int *)(param_2 + 0x50) + iVar11;
      fVar18 = *(float *)(iVar5 + 0x38);
      fVar12 = *(float *)(iVar5 + 0x34);
      fVar19 = *(float *)(iVar9 + 0x38);
      *(float *)(iVar9 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x84) = fVar12 - *(float *)(iVar9 + 0x34);
      *(undefined4 *)(iVar3 + 0x8c) = uVar15;
      *(float *)(iVar9 + 0x88) = fVar18 - fVar19;
      uVar15 = tVector::Normalize((tVector *)(iVar9 + 0x80));
      iVar5 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar9 + 0x8c) = uVar15;
      if (iVar5 <= iVar14) break;
      iVar6 = *(int *)(param_2 + 0x4c);
      iVar9 = iVar11;
    }
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar11 = *(int *)(param_2 + 0x50);
  }
  iVar11 = iVar11 + iVar5 * 0xa8;
  iVar6 = iVar6 + iVar5 * 0xa8;
  *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x84) = 0;
  *(undefined4 *)(iVar6 + 0x80) = 0;
  *(undefined4 *)(iVar11 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar11 + 0x80) = 0;
  *(undefined4 *)(iVar11 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar11 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
