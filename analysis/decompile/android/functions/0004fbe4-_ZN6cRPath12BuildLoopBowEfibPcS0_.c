/*
 * mangled: _ZN6cRPath12BuildLoopBowEfibPcS0_
 * demangled: cRPath::BuildLoopBow(float, int, bool, char*, char*)
 * address: 0004fbe4
 * size: 1624
 */

/* cRPath::BuildLoopBow(float, int, bool, char*, char*) */

void cRPath::BuildLoopBow(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  tVector *ptVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  tMatrix *ptVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float fVar16;
  int iVar17;
  undefined4 uVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  tMatrix atStack_a8 [68];

  fVar3 = DAT_0004fe60;
  fVar24 = DAT_0004fe3c;
  fVar16 = (float)(uint)param_3 * DAT_0004fe3c;
  *(char **)(param_2 + 0x48) = param_4;
  *(float *)(param_2 + 0x44) = fVar3;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  fVar19 = DAT_0004fe40;
  *(undefined1 *)(param_2 + 0x30) = 0;
  iVar9 = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  fVar4 = DAT_0004fe64;
  fVar1 = DAT_0004fe4c;
  fVar20 = DAT_0004fe48;
  fVar22 = DAT_0004fe44;
  iVar13 = 0;
  iVar17 = (int)fVar16;
  fVar25 = (float)VectorSignedToFloat(iVar17,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar17 + 0xe;
  uVar18 = VectorSignedToFloat(iVar17 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar18;
  fVar24 = fVar25 / fVar24;
  fVar16 = fVar4;
  if (param_4 == (char *)0x4) {
    fVar16 = fVar19;
  }
  GetNodes((cRPath *)param_2);
  iVar10 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar23 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
    uVar18 = *(undefined4 *)(param_2 + 0x48);
    ptVar11 = (tMatrix *)(iVar10 + iVar9);
    *(float *)(ptVar11 + 0x98) = fVar4;
    *(float *)(ptVar11 + 0x94) = fVar4;
    *(float *)(ptVar11 + 0xa0) = fVar4;
    *(float *)(ptVar11 + 0x9c) = fVar3;
    iVar13 = iVar13 + 1;
    fVar21 = (float)VectorSignedToFloat(uVar18,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar11 + 0x90) = (fVar21 * fVar19 - fVar22) - fVar16 * (fVar23 / fVar20);
    tMatrix::Identity(ptVar11);
    iVar10 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar9;
    *(float *)(iVar7 + 0x8c) = fVar3;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar4;
    *(float *)(iVar7 + 0x38) = fVar23;
    tMatrix::Identity((tMatrix *)(iVar10 + iVar9));
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar7 = *(int *)(param_2 + 0x50) + iVar9;
    *(float *)(iVar7 + 0x38) = fVar23;
    *(float *)(iVar7 + 0x8c) = fVar3;
    uVar18 = *(undefined4 *)(iVar10 + iVar9 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar1;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar7 + 0x30) = uVar18;
    fVar2 = DAT_0004fe54;
    fVar23 = DAT_0004fe50;
    fVar21 = DAT_0004fe44;
  } while (iVar13 != 7);
  iVar13 = 0;
  iVar9 = (iVar17 + 7) * 0xa8;
  do {
    fVar19 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
    uVar18 = *(undefined4 *)(param_2 + 0x48);
    ptVar11 = (tMatrix *)(iVar10 + iVar9);
    *(float *)(ptVar11 + 0x98) = fVar4;
    *(float *)(ptVar11 + 0x94) = fVar4;
    *(float *)(ptVar11 + 0xa0) = fVar4;
    *(float *)(ptVar11 + 0x9c) = fVar3;
    fVar22 = (float)VectorSignedToFloat(uVar18,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar11 + 0x90) = fVar21 + fVar22 * fVar23 + fVar16 * (fVar3 - fVar19 / fVar2);
    tMatrix::Identity(ptVar11);
    uVar18 = VectorSignedToFloat(iVar13 + 7,(byte)(in_fpscr >> 0x16) & 3);
    iVar13 = iVar13 + 1;
    iVar10 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar9;
    *(float *)(iVar7 + 0x8c) = fVar3;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar4;
    *(undefined4 *)(iVar7 + 0x38) = uVar18;
    fVar22 = (float)tMatrix::Identity((tMatrix *)(iVar10 + iVar9));
    iVar15 = *(int *)(param_2 + 0x50);
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar7 = iVar15 + iVar9;
    *(undefined4 *)(iVar7 + 0x38) = uVar18;
    *(float *)(iVar7 + 0x8c) = fVar3;
    uVar18 = *(undefined4 *)(iVar10 + iVar9 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar1;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar7 + 0x30) = uVar18;
    fVar19 = DAT_0004fe48;
  } while (iVar13 != 7);
  if (0 < iVar17) {
    iVar9 = 0x498;
    iVar13 = 0;
    do {
      fVar20 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
      iVar13 = iVar13 + 1;
      fVar20 = *(float *)(iVar10 + 0x90) +
               (fVar20 * (*(float *)(iVar10 + (iVar17 + 0xd) * 0xa8 + 0x90) -
                         *(float *)(iVar10 + 0x90))) / fVar25;
      *(float *)(iVar10 + iVar9 + 0x90) = fVar20;
      fVar22 = (float)Sin(fVar22);
      ptVar11 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar9);
      *(float *)(ptVar11 + 0x98) = fVar4;
      *(float *)(ptVar11 + 0x94) = fVar4;
      *(float *)(ptVar11 + 0xa0) = fVar4;
      *(float *)(ptVar11 + 0x9c) = fVar3;
      *(float *)(iVar10 + iVar9 + 0x90) = fVar20 + fVar22 * fVar16;
      fVar22 = (float)tMatrix::Identity(ptVar11);
      iVar10 = *(int *)(param_2 + 0x4c) + iVar9;
      *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar10 + 0x90);
      fVar22 = (float)Sin(fVar22);
      iVar7 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar10 + 0x38) = fVar19 + fVar22 * fVar24;
      fVar22 = (float)Cos(extraout_s0);
      iVar10 = *(int *)(param_2 + 0x50);
      *(float *)(iVar7 + iVar9 + 0x34) = fVar24 - fVar22 * fVar24;
      fVar22 = (float)tMatrix::Identity((tMatrix *)(iVar10 + iVar9));
      iVar10 = *(int *)(param_2 + 0x50) + iVar9;
      *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar9 + 0x90);
      fVar22 = (float)Sin(fVar22);
      iVar7 = *(int *)(param_2 + 0x50);
      *(float *)(iVar10 + 0x38) = fVar19 + fVar22 * (fVar24 - fVar1);
      fVar22 = (float)Cos(extraout_s0_00);
      iVar10 = *(int *)(param_2 + 0x4c) + iVar9;
      fVar20 = *(float *)(iVar10 + 0x38);
      *(float *)(*(int *)(param_2 + 0x4c) + iVar9) = fVar3;
      *(float *)(iVar10 + 8) = fVar4;
      *(float *)(iVar10 + 4) = fVar4;
      *(float *)(iVar10 + 0x10) = fVar4;
      *(float *)(iVar10 + 0x18) = fVar19 - fVar20;
      *(float *)(iVar7 + iVar9 + 0x34) = fVar24 - (fVar24 - fVar1) * fVar22;
      *(float *)(iVar10 + 0x14) = fVar24 - *(float *)(iVar10 + 0x34);
      tVector::Normalize((tVector *)(iVar10 + 0x10));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar9);
      tVector::Cross(ptVar5 + 0x20,ptVar5,ptVar5 + 0x10);
      iVar10 = *(int *)(param_2 + 0x50);
      iVar7 = iVar10 + iVar9;
      fVar22 = *(float *)(iVar7 + 0x34);
      fVar20 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar7 + 8) = fVar4;
      *(float *)(iVar7 + 4) = fVar4;
      *(float *)(iVar7 + 0x10) = fVar4;
      *(float *)(iVar10 + iVar9) = fVar3;
      *(float *)(iVar7 + 0x14) = fVar24 - fVar22;
      *(float *)(iVar7 + 0x18) = fVar19 - fVar20;
      tVector::Normalize((tVector *)(iVar7 + 0x10));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x50) + iVar9);
      tVector::Cross(ptVar5 + 0x20,ptVar5,ptVar5 + 0x10);
      fVar22 = (float)tMatrix::Identity(atStack_a8);
      fVar22 = (float)Sin(fVar22);
      fVar22 = (float)Sin(fVar22);
      tMatrix::RotLocalY(atStack_a8,fVar22);
      ptVar11 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar9);
      iVar10 = *(int *)(param_2 + 0x50) + iVar9;
      *(float *)(ptVar11 + 0x38) = *(float *)(ptVar11 + 0x38) - fVar19;
      *(float *)(iVar10 + 0x38) = *(float *)(iVar10 + 0x38) - fVar19;
      tMatrix::Multiply(ptVar11,atStack_a8);
      fVar22 = (float)tMatrix::Multiply((tMatrix *)(*(int *)(param_2 + 0x50) + iVar9),atStack_a8);
      iVar10 = *(int *)(param_2 + 0x4c);
      iVar15 = *(int *)(param_2 + 0x50);
      puVar14 = (undefined4 *)(iVar10 + iVar9);
      puVar12 = (undefined4 *)(iVar15 + iVar9);
      iVar9 = iVar9 + 0xa8;
      puVar14[0xe] = (float)puVar14[0xe] + fVar19;
      puVar12[0xe] = (float)puVar12[0xe] + fVar19;
      uVar18 = puVar14[1];
      uVar6 = puVar14[2];
      uVar8 = puVar14[3];
      *puVar12 = *puVar14;
      puVar12[1] = uVar18;
      puVar12[2] = uVar6;
      puVar12[3] = uVar8;
      uVar18 = puVar14[5];
      uVar6 = puVar14[6];
      uVar8 = puVar14[7];
      puVar12[4] = puVar14[4];
      puVar12[5] = uVar18;
      puVar12[6] = uVar6;
      puVar12[7] = uVar8;
      uVar18 = puVar14[9];
      uVar6 = puVar14[10];
      uVar8 = puVar14[0xb];
      puVar12[8] = puVar14[8];
      puVar12[9] = uVar18;
      puVar12[10] = uVar6;
      puVar12[0xb] = uVar8;
      uVar18 = puVar14[0xd];
      uVar6 = puVar14[0xe];
      uVar8 = puVar14[0xf];
      puVar12[0xc] = puVar14[0xc];
      puVar12[0xd] = uVar18;
      puVar12[0xe] = uVar6;
      puVar12[0xf] = uVar8;
      fVar20 = (float)puVar14[5];
      fVar21 = (float)puVar14[6];
      puVar12[0xc] = (float)puVar12[0xc] + fVar1 * (float)puVar14[4];
      puVar12[0xd] = (float)puVar12[0xd] + fVar1 * fVar20;
      puVar12[0xe] = (float)puVar12[0xe] + fVar1 * fVar21;
    } while (iVar13 < iVar17);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar9 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar17 = 0;
    iVar13 = 0;
    while( true ) {
      iVar15 = iVar13 + 0xa8;
      iVar7 = iVar10 + iVar13;
      iVar10 = iVar10 + iVar15;
      fVar24 = *(float *)(iVar10 + 0x38);
      fVar16 = *(float *)(iVar10 + 0x34);
      iVar17 = iVar17 + 1;
      *(float *)(iVar7 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar16 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar24 - *(float *)(iVar7 + 0x38);
      uVar18 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar13 = *(int *)(param_2 + 0x50) + iVar13;
      iVar9 = *(int *)(param_2 + 0x50) + iVar15;
      fVar24 = *(float *)(iVar9 + 0x38);
      fVar16 = *(float *)(iVar9 + 0x34);
      fVar19 = *(float *)(iVar13 + 0x38);
      *(float *)(iVar13 + 0x80) = *(float *)(iVar9 + 0x30) - *(float *)(iVar13 + 0x30);
      *(float *)(iVar13 + 0x84) = fVar16 - *(float *)(iVar13 + 0x34);
      *(undefined4 *)(iVar7 + 0x8c) = uVar18;
      *(float *)(iVar13 + 0x88) = fVar24 - fVar19;
      uVar18 = tVector::Normalize((tVector *)(iVar13 + 0x80));
      iVar9 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar13 + 0x8c) = uVar18;
      if (iVar9 <= iVar17) break;
      iVar10 = *(int *)(param_2 + 0x4c);
      iVar13 = iVar15;
    }
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar15 = *(int *)(param_2 + 0x50);
  }
  fVar24 = DAT_0004fe64;
  fVar16 = DAT_0004fe60;
  iVar15 = iVar15 + iVar9 * 0xa8;
  iVar10 = iVar10 + iVar9 * 0xa8;
  *(float *)(iVar10 + 0x8c) = DAT_0004fe60;
  *(float *)(iVar10 + 0x88) = fVar16;
  *(float *)(iVar10 + 0x84) = fVar24;
  *(float *)(iVar10 + 0x80) = fVar24;
  *(float *)(iVar15 + 0x8c) = fVar16;
  *(float *)(iVar15 + 0x80) = fVar24;
  *(float *)(iVar15 + 0x88) = fVar16;
  *(float *)(iVar15 + 0x84) = fVar24;
  CalcLengthZ((cRPath *)param_2);
  return;
}
