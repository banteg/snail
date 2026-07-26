/*
 * mangled: _ZN6cRPath14BuildTurnunderEfibPcS0_
 * demangled: cRPath::BuildTurnunder(float, int, bool, char*, char*)
 * address: 000527f0
 * size: 1324
 */

/* cRPath::BuildTurnunder(float, int, bool, char*, char*) */

void cRPath::BuildTurnunder(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  uint uVar2;
  tVector *this;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  tMatrix *ptVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar14;
  int iVar15;
  undefined4 uVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;

  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = 0x31;
  iVar8 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar15 = (int)((float)(uint)param_3 * 6.2831855);
  iVar12 = iVar15 + 8;
  fVar22 = (float)VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar12;
  uVar16 = VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar16;
  GetNodes((cRPath *)param_2);
  iVar5 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar1 = 0;
  do {
    fVar19 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar6 = (tMatrix *)(iVar5 + iVar8);
    *(undefined4 *)(ptVar6 + 0x98) = 0;
    *(undefined4 *)(ptVar6 + 0x94) = 0;
    *(undefined4 *)(ptVar6 + 0xa0) = 0;
    *(undefined4 *)(ptVar6 + 0x9c) = 0x3f800000;
    iVar10 = iVar1 + 1;
    uVar16 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar6 + 0x90) = -(fVar19 * 0.5 - 4.0);
    tMatrix::Identity(ptVar6);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c) + iVar8;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x38) = uVar16;
    tMatrix::Identity((tMatrix *)(iVar1 + iVar8));
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar1 = *(int *)(param_2 + 0x50) + iVar8;
    *(undefined4 *)(iVar1 + 0x38) = uVar16;
    *(undefined4 *)(iVar1 + 0x8c) = 0x3f800000;
    uVar16 = *(undefined4 *)(iVar5 + iVar8 + 0x90);
    *(undefined4 *)(iVar1 + 0x34) = 0x3efae148;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar1 + 0x30) = uVar16;
    iVar1 = iVar10;
  } while (iVar10 != 6);
  iVar10 = (iVar15 + 6) * 0xa8;
  iVar1 = iVar10;
  iVar8 = iVar15 + 6;
  do {
    fVar19 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar6 = (tMatrix *)(iVar5 + iVar1);
    *(undefined4 *)(ptVar6 + 0x98) = 0;
    *(undefined4 *)(ptVar6 + 0x94) = 0;
    *(undefined4 *)(ptVar6 + 0xa0) = 0;
    *(undefined4 *)(ptVar6 + 0x9c) = 0x3f800000;
    iVar9 = iVar8 + 1;
    uVar16 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar6 + 0x90) = -(fVar19 * -0.5 + 4.0);
    tMatrix::Identity(ptVar6);
    iVar5 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c) + iVar1;
    *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(undefined4 *)(iVar8 + 0x34) = 0;
    *(undefined4 *)(iVar8 + 0x38) = uVar16;
    tMatrix::Identity((tMatrix *)(iVar5 + iVar1));
    iVar13 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar8 = iVar13 + iVar1;
    *(undefined4 *)(iVar8 + 0x38) = uVar16;
    *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
    uVar16 = *(undefined4 *)(iVar5 + iVar1 + 0x90);
    *(undefined4 *)(iVar8 + 0x34) = 0x3efae148;
    iVar1 = iVar1 + 0xa8;
    *(undefined4 *)(iVar8 + 0x30) = uVar16;
    iVar8 = iVar9;
  } while (iVar9 != iVar12);
  if (0 < iVar15) {
    iVar1 = 0x3f0;
    iVar8 = 0;
    do {
      fVar20 = *(float *)(iVar5 + 0x90);
      fVar17 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
      fVar19 = *(float *)(iVar5 + iVar10 + 0x90);
      ptVar6 = (tMatrix *)(iVar5 + iVar1);
      *(undefined4 *)(ptVar6 + 0x98) = 0;
      *(undefined4 *)(ptVar6 + 0x94) = 0;
      *(undefined4 *)(ptVar6 + 0xa0) = 0;
      *(undefined4 *)(ptVar6 + 0x9c) = 0x3f800000;
      *(float *)(ptVar6 + 0x90) = fVar20 + (fVar17 * (fVar19 - fVar20)) / fVar22;
      fVar19 = (float)tMatrix::Identity(ptVar6);
      iVar5 = *(int *)(param_2 + 0x4c) + iVar1;
      fVar20 = *(float *)(iVar5 + 0x90);
      fVar19 = (float)Sin(fVar19);
      fVar17 = (float)Sin(extraout_s0);
      uVar16 = VectorSignedToFloat(iVar8 + 6,(byte)(in_fpscr >> 0x16) & 3);
      iVar8 = iVar8 + 1;
      iVar12 = *(int *)(param_2 + 0x4c) + iVar1;
      *(undefined4 *)(iVar12 + 0x38) = uVar16;
      *(float *)(iVar5 + 0x30) = fVar20 + fVar19 * fVar17 * -2.0;
      fVar19 = (float)Cos(extraout_s0_00);
      iVar9 = *(int *)(param_2 + 0x4c) + iVar1;
      *(float *)(iVar12 + 0x34) = (fVar22 / 6.2831855 - fVar19 * (fVar22 / 6.2831855)) * -0.2;
      fVar19 = (float)Sin(extraout_s0_01);
      uVar2 = Sin(fVar19);
      fVar19 = (float)Sin(extraout_s0_02);
      uVar16 = Cos(fVar19);
      iVar12 = *(int *)(param_2 + 0x4c);
      *(uint *)(iVar9 + 0x10) = uVar2 ^ 0x80000000;
      iVar5 = iVar12 + iVar1 + -0xa8;
      iVar12 = iVar12 + iVar1;
      fVar21 = *(float *)(iVar5 + 0x38);
      fVar17 = *(float *)(iVar12 + 0x34);
      fVar14 = *(float *)(iVar12 + 0x38);
      fVar19 = *(float *)(iVar12 + 0x30);
      fVar20 = *(float *)(iVar5 + 0x30);
      fVar18 = *(float *)(iVar5 + 0x34);
      *(undefined4 *)(iVar9 + 0x18) = 0;
      *(float *)(iVar12 + 0x28) = fVar14 - fVar21;
      *(float *)(iVar12 + 0x24) = fVar17 - fVar18;
      *(undefined4 *)(iVar9 + 0x14) = uVar16;
      *(float *)(iVar12 + 0x20) = fVar19 - fVar20;
      tVector::Normalize((tVector *)(iVar12 + 0x20));
      this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar1);
      tVector::Cross(this,this + 0x10,this + 0x20);
      iVar5 = *(int *)(param_2 + 0x4c);
      puVar11 = (undefined4 *)(iVar5 + iVar1);
      iVar13 = *(int *)(param_2 + 0x50);
      puVar7 = (undefined4 *)(iVar13 + iVar1);
      iVar1 = iVar1 + 0xa8;
      uVar16 = puVar11[1];
      uVar3 = puVar11[2];
      uVar4 = puVar11[3];
      *puVar7 = *puVar11;
      puVar7[1] = uVar16;
      puVar7[2] = uVar3;
      puVar7[3] = uVar4;
      uVar16 = puVar11[5];
      uVar3 = puVar11[6];
      uVar4 = puVar11[7];
      puVar7[4] = puVar11[4];
      puVar7[5] = uVar16;
      puVar7[6] = uVar3;
      puVar7[7] = uVar4;
      uVar16 = puVar11[9];
      uVar3 = puVar11[10];
      uVar4 = puVar11[0xb];
      puVar7[8] = puVar11[8];
      puVar7[9] = uVar16;
      puVar7[10] = uVar3;
      puVar7[0xb] = uVar4;
      uVar16 = puVar11[0xd];
      uVar3 = puVar11[0xe];
      uVar4 = puVar11[0xf];
      puVar7[0xc] = puVar11[0xc];
      puVar7[0xd] = uVar16;
      puVar7[0xe] = uVar3;
      puVar7[0xf] = uVar4;
      fVar19 = (float)puVar11[5];
      fVar17 = (float)puVar11[6];
      puVar7[0xc] = (float)puVar7[0xc] + (float)puVar11[4] * 0.49;
      puVar7[0xd] = (float)puVar7[0xd] + fVar19 * 0.49;
      puVar7[0xe] = (float)puVar7[0xe] + fVar17 * 0.49;
    } while (iVar8 < iVar15);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar1 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar12 = 0;
    iVar8 = 0;
    while( true ) {
      iVar10 = iVar8 + 0xa8;
      iVar15 = iVar5 + iVar8;
      iVar5 = iVar5 + iVar10;
      fVar19 = *(float *)(iVar5 + 0x38);
      fVar22 = *(float *)(iVar5 + 0x34);
      iVar12 = iVar12 + 1;
      *(float *)(iVar15 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar15 + 0x30);
      *(float *)(iVar15 + 0x84) = fVar22 - *(float *)(iVar15 + 0x34);
      *(float *)(iVar15 + 0x88) = fVar19 - *(float *)(iVar15 + 0x38);
      uVar16 = tVector::Normalize((tVector *)(iVar15 + 0x80));
      iVar8 = *(int *)(param_2 + 0x50) + iVar8;
      iVar1 = *(int *)(param_2 + 0x50) + iVar10;
      fVar19 = *(float *)(iVar1 + 0x38);
      fVar22 = *(float *)(iVar1 + 0x34);
      fVar17 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar22 - *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar15 + 0x8c) = uVar16;
      *(float *)(iVar8 + 0x88) = fVar19 - fVar17;
      uVar16 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar1 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar8 + 0x8c) = uVar16;
      if (iVar1 <= iVar12) break;
      iVar5 = *(int *)(param_2 + 0x4c);
      iVar8 = iVar10;
    }
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar13 = *(int *)(param_2 + 0x50);
  }
  iVar13 = iVar13 + iVar1 * 0xa8;
  iVar5 = iVar5 + iVar1 * 0xa8;
  *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x84) = 0;
  *(undefined4 *)(iVar5 + 0x80) = 0;
  *(undefined4 *)(iVar13 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar13 + 0x80) = 0;
  *(undefined4 *)(iVar13 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar13 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
