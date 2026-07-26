/*
 * mangled: _ZN6cRPath19BuildTurnoverDoubleEfibPcS0_
 * demangled: cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)
 * address: 00052d4c
 * size: 1288
 */

/* cRPath::BuildTurnoverDouble(float, int, bool, char*, char*) */

void cRPath::BuildTurnoverDouble(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  tVector *this;
  undefined4 uVar5;
  int iVar6;
  tMatrix *ptVar7;
  undefined4 *puVar8;
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
  float fVar15;
  int iVar16;
  undefined4 uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;

  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x2c) = 0x30;
  iVar9 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar16 = (int)((float)(uint)param_3 * 9.424778);
  iVar12 = iVar16 + 8;
  fVar22 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar12;
  uVar17 = VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar17;
  GetNodes((cRPath *)param_2);
  iVar6 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar3 = 0;
  do {
    fVar18 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar7 = (tMatrix *)(iVar6 + iVar9);
    *(undefined4 *)(ptVar7 + 0x98) = 0;
    *(undefined4 *)(ptVar7 + 0x94) = 0;
    *(undefined4 *)(ptVar7 + 0xa0) = 0;
    *(undefined4 *)(ptVar7 + 0x9c) = 0x3f800000;
    iVar10 = iVar3 + 1;
    uVar17 = VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar7 + 0x90) = fVar18 * 0.5 - 4.0;
    tMatrix::Identity(ptVar7);
    iVar3 = *(int *)(param_2 + 0x50);
    iVar6 = *(int *)(param_2 + 0x4c) + iVar9;
    *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(iVar6 + 0x34) = 0;
    *(undefined4 *)(iVar6 + 0x38) = uVar17;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar9));
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar3 = *(int *)(param_2 + 0x50) + iVar9;
    *(undefined4 *)(iVar3 + 0x38) = uVar17;
    *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
    uVar17 = *(undefined4 *)(iVar6 + iVar9 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = uVar17;
    iVar3 = iVar10;
  } while (iVar10 != 6);
  iVar9 = (iVar16 + 6) * 0xa8;
  iVar3 = iVar16 + 6;
  do {
    fVar18 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar7 = (tMatrix *)(iVar6 + iVar9);
    *(undefined4 *)(ptVar7 + 0x98) = 0;
    *(undefined4 *)(ptVar7 + 0x94) = 0;
    *(undefined4 *)(ptVar7 + 0xa0) = 0;
    *(undefined4 *)(ptVar7 + 0x9c) = 0x3f800000;
    iVar10 = iVar3 + 1;
    uVar17 = VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar7 + 0x90) = fVar18 * 0.5 - 4.0;
    tMatrix::Identity(ptVar7);
    iVar3 = *(int *)(param_2 + 0x50);
    iVar6 = *(int *)(param_2 + 0x4c) + iVar9;
    *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(iVar6 + 0x34) = 0;
    *(undefined4 *)(iVar6 + 0x38) = uVar17;
    fVar18 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar9));
    iVar13 = *(int *)(param_2 + 0x50);
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar3 = iVar13 + iVar9;
    *(undefined4 *)(iVar3 + 0x38) = uVar17;
    *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
    uVar17 = *(undefined4 *)(iVar6 + iVar9 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = uVar17;
    iVar3 = iVar10;
  } while (iVar10 != iVar12);
  if (0 < iVar16) {
    iVar3 = 0x3f0;
    iVar9 = 0;
    do {
      fVar19 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
      fVar21 = *(float *)(iVar6 + 0x90);
      fVar19 = (fVar19 * 12.566371) / fVar22;
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar19 < 6.2831855) << 0x1f |
              (uint)(fVar19 == 6.2831855) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar19) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar19 = 12.566371 - fVar19;
      }
      fVar18 = (float)Sin(fVar18);
      ptVar7 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar3);
      *(undefined4 *)(ptVar7 + 0x94) = 0;
      *(undefined4 *)(ptVar7 + 0xa0) = 0;
      *(undefined4 *)(ptVar7 + 0x9c) = 0x3f800000;
      *(float *)(ptVar7 + 0x98) = -fVar19;
      *(float *)(iVar6 + iVar3 + 0x90) = fVar21 * fVar18;
      fVar18 = (float)tMatrix::Identity(ptVar7);
      iVar6 = *(int *)(param_2 + 0x4c) + iVar3;
      fVar21 = *(float *)(iVar6 + 0x90);
      fVar18 = (float)Sin(fVar18);
      fVar19 = (float)Sin(extraout_s0);
      uVar17 = VectorSignedToFloat(iVar9 + 6,(byte)(in_fpscr >> 0x16) & 3);
      iVar9 = iVar9 + 1;
      iVar12 = *(int *)(param_2 + 0x4c) + iVar3;
      *(undefined4 *)(iVar12 + 0x38) = uVar17;
      *(float *)(iVar6 + 0x30) = fVar21 + fVar18 * fVar19 * -2.0;
      fVar18 = (float)Cos(extraout_s0_00);
      iVar10 = *(int *)(param_2 + 0x4c) + iVar3;
      *(float *)(iVar12 + 0x34) = (fVar22 / 12.566371 - fVar18 * (fVar22 / 12.566371)) * 0.4;
      uVar17 = Sin(extraout_s0_01);
      uVar4 = Cos(extraout_s0_02);
      iVar12 = *(int *)(param_2 + 0x4c);
      *(undefined4 *)(iVar10 + 0x10) = uVar17;
      iVar6 = iVar12 + iVar3 + -0xa8;
      iVar12 = iVar12 + iVar3;
      fVar14 = *(float *)(iVar6 + 0x30);
      fVar18 = *(float *)(iVar12 + 0x34);
      fVar21 = *(float *)(iVar12 + 0x38);
      fVar19 = *(float *)(iVar12 + 0x30);
      fVar20 = *(float *)(iVar6 + 0x38);
      fVar15 = *(float *)(iVar6 + 0x34);
      *(undefined4 *)(iVar10 + 0x18) = 0;
      *(float *)(iVar12 + 0x20) = fVar19 - fVar14;
      *(float *)(iVar12 + 0x24) = fVar18 - fVar15;
      *(undefined4 *)(iVar10 + 0x14) = uVar4;
      *(float *)(iVar12 + 0x28) = fVar21 - fVar20;
      tVector::Normalize((tVector *)(iVar12 + 0x20));
      this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar3);
      fVar18 = (float)tVector::Cross(this,this + 0x10,this + 0x20);
      iVar6 = *(int *)(param_2 + 0x4c);
      puVar11 = (undefined4 *)(iVar6 + iVar3);
      iVar13 = *(int *)(param_2 + 0x50);
      puVar8 = (undefined4 *)(iVar13 + iVar3);
      iVar3 = iVar3 + 0xa8;
      uVar17 = puVar11[1];
      uVar4 = puVar11[2];
      uVar5 = puVar11[3];
      *puVar8 = *puVar11;
      puVar8[1] = uVar17;
      puVar8[2] = uVar4;
      puVar8[3] = uVar5;
      uVar17 = puVar11[5];
      uVar4 = puVar11[6];
      uVar5 = puVar11[7];
      puVar8[4] = puVar11[4];
      puVar8[5] = uVar17;
      puVar8[6] = uVar4;
      puVar8[7] = uVar5;
      uVar17 = puVar11[9];
      uVar4 = puVar11[10];
      uVar5 = puVar11[0xb];
      puVar8[8] = puVar11[8];
      puVar8[9] = uVar17;
      puVar8[10] = uVar4;
      puVar8[0xb] = uVar5;
      uVar17 = puVar11[0xd];
      uVar4 = puVar11[0xe];
      uVar5 = puVar11[0xf];
      puVar8[0xc] = puVar11[0xc];
      puVar8[0xd] = uVar17;
      puVar8[0xe] = uVar4;
      puVar8[0xf] = uVar5;
      fVar19 = (float)puVar11[5];
      fVar21 = (float)puVar11[6];
      puVar8[0xc] = (float)puVar8[0xc] + (float)puVar11[4] * 0.49;
      puVar8[0xd] = (float)puVar8[0xd] + fVar19 * 0.49;
      puVar8[0xe] = (float)puVar8[0xe] + fVar21 * 0.49;
    } while (iVar9 < iVar16);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar3 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar12 = 0;
    iVar9 = 0;
    while( true ) {
      iVar10 = iVar9 + 0xa8;
      iVar16 = iVar6 + iVar9;
      iVar6 = iVar6 + iVar10;
      fVar18 = *(float *)(iVar6 + 0x38);
      fVar22 = *(float *)(iVar6 + 0x34);
      iVar12 = iVar12 + 1;
      *(float *)(iVar16 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar16 + 0x30);
      *(float *)(iVar16 + 0x84) = fVar22 - *(float *)(iVar16 + 0x34);
      *(float *)(iVar16 + 0x88) = fVar18 - *(float *)(iVar16 + 0x38);
      uVar17 = tVector::Normalize((tVector *)(iVar16 + 0x80));
      iVar9 = *(int *)(param_2 + 0x50) + iVar9;
      iVar3 = *(int *)(param_2 + 0x50) + iVar10;
      fVar18 = *(float *)(iVar3 + 0x38);
      fVar22 = *(float *)(iVar3 + 0x34);
      fVar19 = *(float *)(iVar9 + 0x38);
      *(float *)(iVar9 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x84) = fVar22 - *(float *)(iVar9 + 0x34);
      *(undefined4 *)(iVar16 + 0x8c) = uVar17;
      *(float *)(iVar9 + 0x88) = fVar18 - fVar19;
      uVar17 = tVector::Normalize((tVector *)(iVar9 + 0x80));
      iVar3 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar9 + 0x8c) = uVar17;
      if (iVar3 <= iVar12) break;
      iVar6 = *(int *)(param_2 + 0x4c);
      iVar9 = iVar10;
    }
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar13 = *(int *)(param_2 + 0x50);
  }
  iVar13 = iVar13 + iVar3 * 0xa8;
  iVar6 = iVar6 + iVar3 * 0xa8;
  *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x84) = 0;
  *(undefined4 *)(iVar6 + 0x80) = 0;
  *(undefined4 *)(iVar13 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar13 + 0x80) = 0;
  *(undefined4 *)(iVar13 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar13 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
