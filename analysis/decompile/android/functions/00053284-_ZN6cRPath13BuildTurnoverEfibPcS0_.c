/*
 * mangled: _ZN6cRPath13BuildTurnoverEfibPcS0_
 * demangled: cRPath::BuildTurnover(float, int, bool, char*, char*)
 * address: 00053284
 * size: 1268
 */

/* cRPath::BuildTurnover(float, int, bool, char*, char*) */

void cRPath::BuildTurnover(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  tVector *this;
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
  int iVar19;
  undefined4 uVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;

  fVar17 = DAT_0005366c;
  fVar18 = (float)(uint)param_3 * DAT_0005366c;
  *(char **)(param_2 + 0x48) = param_4;
  uVar6 = DAT_00053688;
  *(undefined4 *)(param_2 + 0x44) = DAT_00053688;
  *(undefined4 *)(param_2 + 0x2c) = 0x2d;
  iVar11 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  uVar3 = DAT_0005368c;
  fVar1 = DAT_00053678;
  fVar28 = DAT_00053674;
  fVar25 = DAT_00053670;
  iVar19 = (int)fVar18;
  iVar15 = iVar19 + 8;
  fVar18 = (float)VectorSignedToFloat(iVar19,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar15;
  uVar20 = VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar20;
  GetNodes((cRPath *)param_2);
  iVar8 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar4 = 0;
  do {
    fVar24 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar9 = (tMatrix *)(iVar8 + iVar11);
    *(undefined4 *)(ptVar9 + 0x98) = uVar3;
    *(undefined4 *)(ptVar9 + 0x94) = uVar3;
    *(undefined4 *)(ptVar9 + 0xa0) = uVar3;
    *(undefined4 *)(ptVar9 + 0x9c) = uVar6;
    iVar13 = iVar4 + 1;
    uVar20 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar9 + 0x90) = fVar24 * fVar25 - fVar28;
    tMatrix::Identity(ptVar9);
    iVar4 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c) + iVar11;
    *(undefined4 *)(iVar8 + 0x8c) = uVar6;
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(undefined4 *)(iVar8 + 0x34) = uVar3;
    *(undefined4 *)(iVar8 + 0x38) = uVar20;
    tMatrix::Identity((tMatrix *)(iVar4 + iVar11));
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar11;
    *(undefined4 *)(iVar4 + 0x38) = uVar20;
    *(undefined4 *)(iVar4 + 0x8c) = uVar6;
    uVar20 = *(undefined4 *)(iVar8 + iVar11 + 0x90);
    *(float *)(iVar4 + 0x34) = fVar1;
    iVar11 = iVar11 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = uVar20;
    fVar21 = DAT_0005367c;
    fVar24 = DAT_00053674;
    iVar4 = iVar13;
  } while (iVar13 != 6);
  iVar13 = (iVar19 + 6) * 0xa8;
  iVar4 = iVar13;
  iVar11 = iVar19 + 6;
  do {
    fVar25 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar9 = (tMatrix *)(iVar8 + iVar4);
    *(undefined4 *)(ptVar9 + 0x98) = uVar3;
    *(undefined4 *)(ptVar9 + 0x94) = uVar3;
    *(undefined4 *)(ptVar9 + 0xa0) = uVar3;
    *(undefined4 *)(ptVar9 + 0x9c) = uVar6;
    iVar12 = iVar11 + 1;
    uVar20 = VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar9 + 0x90) = fVar24 + fVar25 * fVar21;
    tMatrix::Identity(ptVar9);
    iVar8 = *(int *)(param_2 + 0x50);
    iVar11 = *(int *)(param_2 + 0x4c) + iVar4;
    *(undefined4 *)(iVar11 + 0x8c) = uVar6;
    *(undefined4 *)(iVar11 + 0x30) = *(undefined4 *)(iVar11 + 0x90);
    *(undefined4 *)(iVar11 + 0x34) = uVar3;
    *(undefined4 *)(iVar11 + 0x38) = uVar20;
    tMatrix::Identity((tMatrix *)(iVar8 + iVar4));
    iVar16 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar11 = iVar16 + iVar4;
    *(undefined4 *)(iVar11 + 0x38) = uVar20;
    *(undefined4 *)(iVar11 + 0x8c) = uVar6;
    uVar20 = *(undefined4 *)(iVar8 + iVar4 + 0x90);
    *(float *)(iVar11 + 0x34) = fVar1;
    iVar4 = iVar4 + 0xa8;
    *(undefined4 *)(iVar11 + 0x30) = uVar20;
    fVar2 = DAT_00053684;
    fVar28 = DAT_00053680;
    fVar25 = DAT_0005366c;
    iVar11 = iVar12;
  } while (iVar12 != iVar15);
  if (0 < iVar19) {
    iVar4 = 0x3f0;
    iVar11 = 0;
    do {
      fVar26 = *(float *)(iVar8 + 0x90);
      fVar21 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
      fVar24 = *(float *)(iVar8 + iVar13 + 0x90);
      ptVar9 = (tMatrix *)(iVar8 + iVar4);
      *(undefined4 *)(ptVar9 + 0x94) = uVar3;
      *(undefined4 *)(ptVar9 + 0xa0) = uVar3;
      *(undefined4 *)(ptVar9 + 0x9c) = uVar6;
      *(float *)(ptVar9 + 0x90) = fVar26 + (fVar21 * (fVar24 - fVar26)) / fVar18;
      *(float *)(ptVar9 + 0x98) = -((fVar21 * fVar25) / fVar18);
      fVar24 = (float)tMatrix::Identity(ptVar9);
      iVar8 = *(int *)(param_2 + 0x4c) + iVar4;
      fVar26 = *(float *)(iVar8 + 0x90);
      fVar24 = (float)Sin(fVar24);
      fVar21 = (float)Sin(extraout_s0);
      uVar20 = VectorSignedToFloat(iVar11 + 6,(byte)(in_fpscr >> 0x16) & 3);
      iVar11 = iVar11 + 1;
      iVar15 = *(int *)(param_2 + 0x4c) + iVar4;
      *(undefined4 *)(iVar15 + 0x38) = uVar20;
      *(float *)(iVar8 + 0x30) = fVar26 + fVar24 * fVar21 * fVar28;
      fVar24 = (float)Cos(extraout_s0_00);
      iVar12 = *(int *)(param_2 + 0x4c) + iVar4;
      *(float *)(iVar15 + 0x34) = (fVar18 / fVar17 - fVar24 * (fVar18 / fVar17)) * fVar2;
      uVar20 = Sin(extraout_s0_01);
      uVar5 = Cos(extraout_s0_02);
      iVar15 = *(int *)(param_2 + 0x4c);
      *(undefined4 *)(iVar12 + 0x10) = uVar20;
      iVar8 = iVar15 + iVar4 + -0xa8;
      iVar15 = iVar15 + iVar4;
      fVar22 = *(float *)(iVar8 + 0x30);
      fVar24 = *(float *)(iVar15 + 0x34);
      fVar26 = *(float *)(iVar15 + 0x38);
      fVar21 = *(float *)(iVar15 + 0x30);
      fVar27 = *(float *)(iVar8 + 0x38);
      fVar23 = *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar12 + 0x18) = uVar3;
      *(float *)(iVar15 + 0x20) = fVar21 - fVar22;
      *(float *)(iVar15 + 0x24) = fVar24 - fVar23;
      *(undefined4 *)(iVar12 + 0x14) = uVar5;
      *(float *)(iVar15 + 0x28) = fVar26 - fVar27;
      tVector::Normalize((tVector *)(iVar15 + 0x20));
      this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar4);
      tVector::Cross(this,this + 0x10,this + 0x20);
      iVar8 = *(int *)(param_2 + 0x4c);
      puVar14 = (undefined4 *)(iVar8 + iVar4);
      iVar16 = *(int *)(param_2 + 0x50);
      puVar10 = (undefined4 *)(iVar16 + iVar4);
      iVar4 = iVar4 + 0xa8;
      uVar20 = puVar14[1];
      uVar5 = puVar14[2];
      uVar7 = puVar14[3];
      *puVar10 = *puVar14;
      puVar10[1] = uVar20;
      puVar10[2] = uVar5;
      puVar10[3] = uVar7;
      uVar20 = puVar14[5];
      uVar5 = puVar14[6];
      uVar7 = puVar14[7];
      puVar10[4] = puVar14[4];
      puVar10[5] = uVar20;
      puVar10[6] = uVar5;
      puVar10[7] = uVar7;
      uVar20 = puVar14[9];
      uVar5 = puVar14[10];
      uVar7 = puVar14[0xb];
      puVar10[8] = puVar14[8];
      puVar10[9] = uVar20;
      puVar10[10] = uVar5;
      puVar10[0xb] = uVar7;
      uVar20 = puVar14[0xd];
      uVar5 = puVar14[0xe];
      uVar7 = puVar14[0xf];
      puVar10[0xc] = puVar14[0xc];
      puVar10[0xd] = uVar20;
      puVar10[0xe] = uVar5;
      puVar10[0xf] = uVar7;
      fVar24 = (float)puVar14[5];
      fVar21 = (float)puVar14[6];
      puVar10[0xc] = (float)puVar10[0xc] + fVar1 * (float)puVar14[4];
      puVar10[0xd] = (float)puVar10[0xd] + fVar1 * fVar24;
      puVar10[0xe] = (float)puVar10[0xe] + fVar1 * fVar21;
    } while (iVar11 < iVar19);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar4 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar15 = 0;
    iVar11 = 0;
    while( true ) {
      iVar13 = iVar11 + 0xa8;
      iVar19 = iVar8 + iVar11;
      iVar8 = iVar8 + iVar13;
      fVar25 = *(float *)(iVar8 + 0x38);
      fVar17 = *(float *)(iVar8 + 0x34);
      iVar15 = iVar15 + 1;
      *(float *)(iVar19 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar19 + 0x30);
      *(float *)(iVar19 + 0x84) = fVar17 - *(float *)(iVar19 + 0x34);
      *(float *)(iVar19 + 0x88) = fVar25 - *(float *)(iVar19 + 0x38);
      uVar6 = tVector::Normalize((tVector *)(iVar19 + 0x80));
      iVar11 = *(int *)(param_2 + 0x50) + iVar11;
      iVar4 = *(int *)(param_2 + 0x50) + iVar13;
      fVar25 = *(float *)(iVar4 + 0x38);
      fVar17 = *(float *)(iVar4 + 0x34);
      fVar28 = *(float *)(iVar11 + 0x38);
      *(float *)(iVar11 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar17 - *(float *)(iVar11 + 0x34);
      *(undefined4 *)(iVar19 + 0x8c) = uVar6;
      *(float *)(iVar11 + 0x88) = fVar25 - fVar28;
      uVar6 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar4 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar11 + 0x8c) = uVar6;
      if (iVar4 <= iVar15) break;
      iVar8 = *(int *)(param_2 + 0x4c);
      iVar11 = iVar13;
    }
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar16 = *(int *)(param_2 + 0x50);
  }
  uVar3 = DAT_0005368c;
  uVar6 = DAT_00053688;
  iVar16 = iVar16 + iVar4 * 0xa8;
  iVar8 = iVar8 + iVar4 * 0xa8;
  *(undefined4 *)(iVar8 + 0x8c) = DAT_00053688;
  *(undefined4 *)(iVar8 + 0x88) = uVar6;
  *(undefined4 *)(iVar8 + 0x84) = uVar3;
  *(undefined4 *)(iVar8 + 0x80) = uVar3;
  *(undefined4 *)(iVar16 + 0x8c) = uVar6;
  *(undefined4 *)(iVar16 + 0x80) = uVar3;
  *(undefined4 *)(iVar16 + 0x88) = uVar6;
  *(undefined4 *)(iVar16 + 0x84) = uVar3;
  CalcLengthZ((cRPath *)param_2);
  return;
}
