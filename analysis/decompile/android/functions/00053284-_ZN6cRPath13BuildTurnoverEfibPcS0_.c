/*
 * mangled: _ZN6cRPath13BuildTurnoverEfibPcS0_
 * demangled: cRPath::BuildTurnover(float, int, bool, char*, char*)
 * address: 00053284
 * size: 1268
 */

/* cRPath::BuildTurnover(float, int, bool, char*, char*) */

void cRPath::BuildTurnover(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  undefined4 uVar2;
  tVector *this;
  undefined4 uVar3;
  int iVar4;
  tMatrix *ptVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  int iVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;

  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = 0x2d;
  iVar7 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar13 = (int)((float)(uint)param_3 * 6.2831855);
  iVar11 = iVar13 + 8;
  fVar21 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar11;
  uVar14 = VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar14;
  GetNodes((cRPath *)param_2);
  iVar4 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar1 = 0;
  do {
    fVar18 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar5 = (tMatrix *)(iVar4 + iVar7);
    *(undefined4 *)(ptVar5 + 0x98) = 0;
    *(undefined4 *)(ptVar5 + 0x94) = 0;
    *(undefined4 *)(ptVar5 + 0xa0) = 0;
    *(undefined4 *)(ptVar5 + 0x9c) = 0x3f800000;
    iVar9 = iVar1 + 1;
    uVar14 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar5 + 0x90) = fVar18 * 0.5 - 4.0;
    tMatrix::Identity(ptVar5);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(undefined4 *)(iVar4 + 0x38) = uVar14;
    tMatrix::Identity((tMatrix *)(iVar1 + iVar7));
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar1 = *(int *)(param_2 + 0x50) + iVar7;
    *(undefined4 *)(iVar1 + 0x38) = uVar14;
    *(undefined4 *)(iVar1 + 0x8c) = 0x3f800000;
    uVar14 = *(undefined4 *)(iVar4 + iVar7 + 0x90);
    *(undefined4 *)(iVar1 + 0x34) = 0x3efae148;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar1 + 0x30) = uVar14;
    iVar1 = iVar9;
  } while (iVar9 != 6);
  iVar9 = (iVar13 + 6) * 0xa8;
  iVar1 = iVar9;
  iVar7 = iVar13 + 6;
  do {
    fVar18 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar5 = (tMatrix *)(iVar4 + iVar1);
    *(undefined4 *)(ptVar5 + 0x98) = 0;
    *(undefined4 *)(ptVar5 + 0x94) = 0;
    *(undefined4 *)(ptVar5 + 0xa0) = 0;
    *(undefined4 *)(ptVar5 + 0x9c) = 0x3f800000;
    iVar8 = iVar7 + 1;
    uVar14 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar5 + 0x90) = fVar18 * -0.5 + 4.0;
    tMatrix::Identity(ptVar5);
    iVar4 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar1;
    *(undefined4 *)(iVar7 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar7 + 0x34) = 0;
    *(undefined4 *)(iVar7 + 0x38) = uVar14;
    tMatrix::Identity((tMatrix *)(iVar4 + iVar1));
    iVar12 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar7 = iVar12 + iVar1;
    *(undefined4 *)(iVar7 + 0x38) = uVar14;
    *(undefined4 *)(iVar7 + 0x8c) = 0x3f800000;
    uVar14 = *(undefined4 *)(iVar4 + iVar1 + 0x90);
    *(undefined4 *)(iVar7 + 0x34) = 0x3efae148;
    iVar1 = iVar1 + 0xa8;
    *(undefined4 *)(iVar7 + 0x30) = uVar14;
    iVar7 = iVar8;
  } while (iVar8 != iVar11);
  if (0 < iVar13) {
    iVar1 = 0x3f0;
    iVar7 = 0;
    do {
      fVar19 = *(float *)(iVar4 + 0x90);
      fVar15 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      fVar18 = *(float *)(iVar4 + iVar9 + 0x90);
      ptVar5 = (tMatrix *)(iVar4 + iVar1);
      *(undefined4 *)(ptVar5 + 0x94) = 0;
      *(undefined4 *)(ptVar5 + 0xa0) = 0;
      *(undefined4 *)(ptVar5 + 0x9c) = 0x3f800000;
      *(float *)(ptVar5 + 0x90) = fVar19 + (fVar15 * (fVar18 - fVar19)) / fVar21;
      *(float *)(ptVar5 + 0x98) = -((fVar15 * 6.2831855) / fVar21);
      fVar18 = (float)tMatrix::Identity(ptVar5);
      iVar4 = *(int *)(param_2 + 0x4c) + iVar1;
      fVar19 = *(float *)(iVar4 + 0x90);
      fVar18 = (float)Sin(fVar18);
      fVar15 = (float)Sin(extraout_s0);
      uVar14 = VectorSignedToFloat(iVar7 + 6,(byte)(in_fpscr >> 0x16) & 3);
      iVar7 = iVar7 + 1;
      iVar11 = *(int *)(param_2 + 0x4c) + iVar1;
      *(undefined4 *)(iVar11 + 0x38) = uVar14;
      *(float *)(iVar4 + 0x30) = fVar19 + fVar18 * fVar15 * -2.0;
      fVar18 = (float)Cos(extraout_s0_00);
      iVar8 = *(int *)(param_2 + 0x4c) + iVar1;
      *(float *)(iVar11 + 0x34) = (fVar21 / 6.2831855 - fVar18 * (fVar21 / 6.2831855)) * 0.4;
      uVar14 = Sin(extraout_s0_01);
      uVar2 = Cos(extraout_s0_02);
      iVar11 = *(int *)(param_2 + 0x4c);
      *(undefined4 *)(iVar8 + 0x10) = uVar14;
      iVar4 = iVar11 + iVar1 + -0xa8;
      iVar11 = iVar11 + iVar1;
      fVar16 = *(float *)(iVar4 + 0x30);
      fVar18 = *(float *)(iVar11 + 0x34);
      fVar19 = *(float *)(iVar11 + 0x38);
      fVar15 = *(float *)(iVar11 + 0x30);
      fVar20 = *(float *)(iVar4 + 0x38);
      fVar17 = *(float *)(iVar4 + 0x34);
      *(undefined4 *)(iVar8 + 0x18) = 0;
      *(float *)(iVar11 + 0x20) = fVar15 - fVar16;
      *(float *)(iVar11 + 0x24) = fVar18 - fVar17;
      *(undefined4 *)(iVar8 + 0x14) = uVar2;
      *(float *)(iVar11 + 0x28) = fVar19 - fVar20;
      tVector::Normalize((tVector *)(iVar11 + 0x20));
      this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar1);
      tVector::Cross(this,this + 0x10,this + 0x20);
      iVar4 = *(int *)(param_2 + 0x4c);
      puVar10 = (undefined4 *)(iVar4 + iVar1);
      iVar12 = *(int *)(param_2 + 0x50);
      puVar6 = (undefined4 *)(iVar12 + iVar1);
      iVar1 = iVar1 + 0xa8;
      uVar14 = puVar10[1];
      uVar2 = puVar10[2];
      uVar3 = puVar10[3];
      *puVar6 = *puVar10;
      puVar6[1] = uVar14;
      puVar6[2] = uVar2;
      puVar6[3] = uVar3;
      uVar14 = puVar10[5];
      uVar2 = puVar10[6];
      uVar3 = puVar10[7];
      puVar6[4] = puVar10[4];
      puVar6[5] = uVar14;
      puVar6[6] = uVar2;
      puVar6[7] = uVar3;
      uVar14 = puVar10[9];
      uVar2 = puVar10[10];
      uVar3 = puVar10[0xb];
      puVar6[8] = puVar10[8];
      puVar6[9] = uVar14;
      puVar6[10] = uVar2;
      puVar6[0xb] = uVar3;
      uVar14 = puVar10[0xd];
      uVar2 = puVar10[0xe];
      uVar3 = puVar10[0xf];
      puVar6[0xc] = puVar10[0xc];
      puVar6[0xd] = uVar14;
      puVar6[0xe] = uVar2;
      puVar6[0xf] = uVar3;
      fVar18 = (float)puVar10[5];
      fVar15 = (float)puVar10[6];
      puVar6[0xc] = (float)puVar6[0xc] + (float)puVar10[4] * 0.49;
      puVar6[0xd] = (float)puVar6[0xd] + fVar18 * 0.49;
      puVar6[0xe] = (float)puVar6[0xe] + fVar15 * 0.49;
    } while (iVar7 < iVar13);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar1 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar11 = 0;
    iVar7 = 0;
    while( true ) {
      iVar9 = iVar7 + 0xa8;
      iVar13 = iVar4 + iVar7;
      iVar4 = iVar4 + iVar9;
      fVar18 = *(float *)(iVar4 + 0x38);
      fVar21 = *(float *)(iVar4 + 0x34);
      iVar11 = iVar11 + 1;
      *(float *)(iVar13 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar13 + 0x30);
      *(float *)(iVar13 + 0x84) = fVar21 - *(float *)(iVar13 + 0x34);
      *(float *)(iVar13 + 0x88) = fVar18 - *(float *)(iVar13 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar13 + 0x80));
      iVar7 = *(int *)(param_2 + 0x50) + iVar7;
      iVar1 = *(int *)(param_2 + 0x50) + iVar9;
      fVar18 = *(float *)(iVar1 + 0x38);
      fVar21 = *(float *)(iVar1 + 0x34);
      fVar15 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar21 - *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar13 + 0x8c) = uVar14;
      *(float *)(iVar7 + 0x88) = fVar18 - fVar15;
      uVar14 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar1 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar7 + 0x8c) = uVar14;
      if (iVar1 <= iVar11) break;
      iVar4 = *(int *)(param_2 + 0x4c);
      iVar7 = iVar9;
    }
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar12 = *(int *)(param_2 + 0x50);
  }
  iVar12 = iVar12 + iVar1 * 0xa8;
  iVar4 = iVar4 + iVar1 * 0xa8;
  *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar12 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar12 + 0x80) = 0;
  *(undefined4 *)(iVar12 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar12 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
