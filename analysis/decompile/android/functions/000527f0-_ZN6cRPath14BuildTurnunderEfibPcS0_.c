/*
 * mangled: _ZN6cRPath14BuildTurnunderEfibPcS0_
 * demangled: cRPath::BuildTurnunder(float, int, bool, char*, char*)
 * address: 000527f0
 * size: 1324
 */

/* cRPath::BuildTurnunder(float, int, bool, char*, char*) */

void cRPath::BuildTurnunder(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  tVector *this;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  tMatrix *ptVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  int iVar16;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar17;
  float fVar18;
  float fVar19;
  int iVar20;
  undefined4 uVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;

  fVar17 = DAT_00052a08;
  fVar19 = (float)(uint)param_3 * DAT_00052a08;
  *(char **)(param_2 + 0x48) = param_4;
  uVar5 = DAT_00052a30;
  *(undefined4 *)(param_2 + 0x44) = DAT_00052a30;
  *(undefined4 *)(param_2 + 0x2c) = 0x31;
  iVar11 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  uVar2 = DAT_00052a34;
  fVar1 = DAT_00052a14;
  fVar28 = DAT_00052a10;
  fVar25 = DAT_00052a0c;
  iVar20 = (int)fVar19;
  iVar15 = iVar20 + 8;
  fVar19 = (float)VectorSignedToFloat(iVar20,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar15;
  uVar21 = VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar21;
  GetNodes((cRPath *)param_2);
  iVar8 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar3 = 0;
  do {
    fVar24 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar9 = (tMatrix *)(iVar8 + iVar11);
    *(undefined4 *)(ptVar9 + 0x98) = uVar2;
    *(undefined4 *)(ptVar9 + 0x94) = uVar2;
    *(undefined4 *)(ptVar9 + 0xa0) = uVar2;
    *(undefined4 *)(ptVar9 + 0x9c) = uVar5;
    iVar13 = iVar3 + 1;
    uVar21 = VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar9 + 0x90) = -(fVar24 * fVar25 - fVar28);
    tMatrix::Identity(ptVar9);
    iVar3 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c) + iVar11;
    *(undefined4 *)(iVar8 + 0x8c) = uVar5;
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(undefined4 *)(iVar8 + 0x34) = uVar2;
    *(undefined4 *)(iVar8 + 0x38) = uVar21;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar11));
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar3 = *(int *)(param_2 + 0x50) + iVar11;
    *(undefined4 *)(iVar3 + 0x38) = uVar21;
    *(undefined4 *)(iVar3 + 0x8c) = uVar5;
    uVar21 = *(undefined4 *)(iVar8 + iVar11 + 0x90);
    *(float *)(iVar3 + 0x34) = fVar1;
    iVar11 = iVar11 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = uVar21;
    fVar22 = DAT_00052a18;
    fVar24 = DAT_00052a10;
    iVar3 = iVar13;
  } while (iVar13 != 6);
  iVar13 = (iVar20 + 6) * 0xa8;
  iVar3 = iVar13;
  iVar11 = iVar20 + 6;
  do {
    fVar25 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar9 = (tMatrix *)(iVar8 + iVar3);
    *(undefined4 *)(ptVar9 + 0x98) = uVar2;
    *(undefined4 *)(ptVar9 + 0x94) = uVar2;
    *(undefined4 *)(ptVar9 + 0xa0) = uVar2;
    *(undefined4 *)(ptVar9 + 0x9c) = uVar5;
    iVar12 = iVar11 + 1;
    uVar21 = VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar9 + 0x90) = -(fVar24 + fVar25 * fVar22);
    tMatrix::Identity(ptVar9);
    iVar8 = *(int *)(param_2 + 0x50);
    iVar11 = *(int *)(param_2 + 0x4c) + iVar3;
    *(undefined4 *)(iVar11 + 0x8c) = uVar5;
    *(undefined4 *)(iVar11 + 0x30) = *(undefined4 *)(iVar11 + 0x90);
    *(undefined4 *)(iVar11 + 0x34) = uVar2;
    *(undefined4 *)(iVar11 + 0x38) = uVar21;
    tMatrix::Identity((tMatrix *)(iVar8 + iVar3));
    iVar16 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar11 = iVar16 + iVar3;
    *(undefined4 *)(iVar11 + 0x38) = uVar21;
    *(undefined4 *)(iVar11 + 0x8c) = uVar5;
    uVar21 = *(undefined4 *)(iVar8 + iVar3 + 0x90);
    *(float *)(iVar11 + 0x34) = fVar1;
    iVar3 = iVar3 + 0xa8;
    *(undefined4 *)(iVar11 + 0x30) = uVar21;
    fVar28 = DAT_00052a24;
    fVar25 = DAT_00052a20;
    iVar11 = iVar12;
  } while (iVar12 != iVar15);
  if (0 < iVar20) {
    iVar3 = 0x3f0;
    iVar11 = 0;
    do {
      fVar26 = *(float *)(iVar8 + 0x90);
      fVar22 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
      fVar24 = *(float *)(iVar8 + iVar13 + 0x90);
      ptVar9 = (tMatrix *)(iVar8 + iVar3);
      *(undefined4 *)(ptVar9 + 0x98) = uVar2;
      *(undefined4 *)(ptVar9 + 0x94) = uVar2;
      *(undefined4 *)(ptVar9 + 0xa0) = uVar2;
      *(undefined4 *)(ptVar9 + 0x9c) = uVar5;
      *(float *)(ptVar9 + 0x90) = fVar26 + (fVar22 * (fVar24 - fVar26)) / fVar19;
      fVar24 = (float)tMatrix::Identity(ptVar9);
      iVar8 = *(int *)(param_2 + 0x4c) + iVar3;
      fVar26 = *(float *)(iVar8 + 0x90);
      fVar24 = (float)Sin(fVar24);
      fVar22 = (float)Sin(extraout_s0);
      uVar21 = VectorSignedToFloat(iVar11 + 6,(byte)(in_fpscr >> 0x16) & 3);
      iVar11 = iVar11 + 1;
      iVar15 = *(int *)(param_2 + 0x4c) + iVar3;
      *(undefined4 *)(iVar15 + 0x38) = uVar21;
      *(float *)(iVar8 + 0x30) = fVar26 + fVar24 * fVar22 * fVar25;
      fVar24 = (float)Cos(extraout_s0_00);
      iVar12 = *(int *)(param_2 + 0x4c) + iVar3;
      *(float *)(iVar15 + 0x34) = (fVar19 / fVar17 - fVar24 * (fVar19 / fVar17)) * fVar28;
      fVar24 = (float)Sin(extraout_s0_01);
      uVar4 = Sin(fVar24);
      fVar24 = (float)Sin(extraout_s0_02);
      uVar21 = Cos(fVar24);
      iVar15 = *(int *)(param_2 + 0x4c);
      *(uint *)(iVar12 + 0x10) = uVar4 ^ 0x80000000;
      iVar8 = iVar15 + iVar3 + -0xa8;
      iVar15 = iVar15 + iVar3;
      fVar27 = *(float *)(iVar8 + 0x38);
      fVar22 = *(float *)(iVar15 + 0x34);
      fVar18 = *(float *)(iVar15 + 0x38);
      fVar24 = *(float *)(iVar15 + 0x30);
      fVar26 = *(float *)(iVar8 + 0x30);
      fVar23 = *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar12 + 0x18) = uVar2;
      *(float *)(iVar15 + 0x28) = fVar18 - fVar27;
      *(float *)(iVar15 + 0x24) = fVar22 - fVar23;
      *(undefined4 *)(iVar12 + 0x14) = uVar21;
      *(float *)(iVar15 + 0x20) = fVar24 - fVar26;
      tVector::Normalize((tVector *)(iVar15 + 0x20));
      this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar3);
      tVector::Cross(this,this + 0x10,this + 0x20);
      iVar8 = *(int *)(param_2 + 0x4c);
      puVar14 = (undefined4 *)(iVar8 + iVar3);
      iVar16 = *(int *)(param_2 + 0x50);
      puVar10 = (undefined4 *)(iVar16 + iVar3);
      iVar3 = iVar3 + 0xa8;
      uVar21 = puVar14[1];
      uVar6 = puVar14[2];
      uVar7 = puVar14[3];
      *puVar10 = *puVar14;
      puVar10[1] = uVar21;
      puVar10[2] = uVar6;
      puVar10[3] = uVar7;
      uVar21 = puVar14[5];
      uVar6 = puVar14[6];
      uVar7 = puVar14[7];
      puVar10[4] = puVar14[4];
      puVar10[5] = uVar21;
      puVar10[6] = uVar6;
      puVar10[7] = uVar7;
      uVar21 = puVar14[9];
      uVar6 = puVar14[10];
      uVar7 = puVar14[0xb];
      puVar10[8] = puVar14[8];
      puVar10[9] = uVar21;
      puVar10[10] = uVar6;
      puVar10[0xb] = uVar7;
      uVar21 = puVar14[0xd];
      uVar6 = puVar14[0xe];
      uVar7 = puVar14[0xf];
      puVar10[0xc] = puVar14[0xc];
      puVar10[0xd] = uVar21;
      puVar10[0xe] = uVar6;
      puVar10[0xf] = uVar7;
      fVar24 = (float)puVar14[5];
      fVar22 = (float)puVar14[6];
      puVar10[0xc] = (float)puVar10[0xc] + fVar1 * (float)puVar14[4];
      puVar10[0xd] = (float)puVar10[0xd] + fVar1 * fVar24;
      puVar10[0xe] = (float)puVar10[0xe] + fVar1 * fVar22;
    } while (iVar11 < iVar20);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar3 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar15 = 0;
    iVar11 = 0;
    while( true ) {
      iVar13 = iVar11 + 0xa8;
      iVar20 = iVar8 + iVar11;
      iVar8 = iVar8 + iVar13;
      fVar25 = *(float *)(iVar8 + 0x38);
      fVar17 = *(float *)(iVar8 + 0x34);
      iVar15 = iVar15 + 1;
      *(float *)(iVar20 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar20 + 0x30);
      *(float *)(iVar20 + 0x84) = fVar17 - *(float *)(iVar20 + 0x34);
      *(float *)(iVar20 + 0x88) = fVar25 - *(float *)(iVar20 + 0x38);
      uVar5 = tVector::Normalize((tVector *)(iVar20 + 0x80));
      iVar11 = *(int *)(param_2 + 0x50) + iVar11;
      iVar3 = *(int *)(param_2 + 0x50) + iVar13;
      fVar25 = *(float *)(iVar3 + 0x38);
      fVar17 = *(float *)(iVar3 + 0x34);
      fVar28 = *(float *)(iVar11 + 0x38);
      *(float *)(iVar11 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar17 - *(float *)(iVar11 + 0x34);
      *(undefined4 *)(iVar20 + 0x8c) = uVar5;
      *(float *)(iVar11 + 0x88) = fVar25 - fVar28;
      uVar5 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar3 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar11 + 0x8c) = uVar5;
      if (iVar3 <= iVar15) break;
      iVar8 = *(int *)(param_2 + 0x4c);
      iVar11 = iVar13;
    }
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar16 = *(int *)(param_2 + 0x50);
  }
  uVar2 = DAT_00052a34;
  uVar5 = DAT_00052a30;
  iVar16 = iVar16 + iVar3 * 0xa8;
  iVar8 = iVar8 + iVar3 * 0xa8;
  *(undefined4 *)(iVar8 + 0x8c) = DAT_00052a30;
  *(undefined4 *)(iVar8 + 0x88) = uVar5;
  *(undefined4 *)(iVar8 + 0x84) = uVar2;
  *(undefined4 *)(iVar8 + 0x80) = uVar2;
  *(undefined4 *)(iVar16 + 0x8c) = uVar5;
  *(undefined4 *)(iVar16 + 0x80) = uVar2;
  *(undefined4 *)(iVar16 + 0x88) = uVar5;
  *(undefined4 *)(iVar16 + 0x84) = uVar2;
  CalcLengthZ((cRPath *)param_2);
  return;
}
