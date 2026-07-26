/*
 * mangled: _ZN6cRPath16BuildLoopTheLoopEfibPcS0_
 * demangled: cRPath::BuildLoopTheLoop(float, int, bool, char*, char*)
 * address: 00058728
 * size: 1328
 */

/* cRPath::BuildLoopTheLoop(float, int, bool, char*, char*) */

void cRPath::BuildLoopTheLoop(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  tVector *ptVar5;
  int iVar6;
  tMatrix *ptVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float fVar12;
  int iVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;

  fVar3 = DAT_0005897c;
  fVar21 = DAT_00058958;
  fVar12 = (float)(uint)param_3 * DAT_00058958;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(float *)(param_2 + 0x44) = fVar3;
  *(undefined1 *)(param_2 + 0x30) = 0;
  fVar4 = DAT_00058980;
  *(undefined4 *)(param_2 + 0x34) = 0;
  fVar1 = DAT_0005896c;
  fVar17 = DAT_00058968;
  fVar19 = DAT_00058964;
  fVar16 = DAT_00058960;
  fVar15 = DAT_0005895c;
  iVar9 = 0;
  iVar10 = 0;
  iVar13 = (int)fVar12;
  fVar12 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar13 + 0xe;
  uVar14 = VectorSignedToFloat(iVar13 + 0xe,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar14;
  if (param_4 != (char *)0x4) {
    fVar15 = fVar4;
  }
  fVar21 = fVar12 / fVar21;
  GetNodes((cRPath *)param_2);
  iVar6 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 1;
  do {
    fVar20 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    uVar14 = *(undefined4 *)(param_2 + 0x48);
    ptVar7 = (tMatrix *)(iVar6 + iVar9);
    *(float *)(ptVar7 + 0x98) = fVar4;
    *(float *)(ptVar7 + 0x94) = fVar4;
    *(float *)(ptVar7 + 0xa0) = fVar4;
    *(float *)(ptVar7 + 0x9c) = fVar3;
    iVar10 = iVar10 + 1;
    fVar18 = (float)VectorSignedToFloat(uVar14,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar7 + 0x90) = (fVar18 * fVar16 - fVar19) - fVar15 * (fVar20 / fVar17);
    tMatrix::Identity(ptVar7);
    iVar6 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c) + iVar9;
    *(float *)(iVar8 + 0x8c) = fVar3;
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(float *)(iVar8 + 0x34) = fVar4;
    *(float *)(iVar8 + 0x38) = fVar20;
    tMatrix::Identity((tMatrix *)(iVar6 + iVar9));
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar8 = *(int *)(param_2 + 0x50) + iVar9;
    *(float *)(iVar8 + 0x38) = fVar20;
    *(float *)(iVar8 + 0x8c) = fVar3;
    uVar14 = *(undefined4 *)(iVar6 + iVar9 + 0x90);
    *(float *)(iVar8 + 0x34) = fVar1;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar8 + 0x30) = uVar14;
    fVar2 = DAT_00058974;
    fVar20 = DAT_00058970;
    fVar18 = DAT_00058964;
  } while (iVar10 != 7);
  iVar10 = 0;
  iVar9 = (iVar13 + 7) * 0xa8;
  do {
    fVar16 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    uVar14 = *(undefined4 *)(param_2 + 0x48);
    ptVar7 = (tMatrix *)(iVar6 + iVar9);
    *(float *)(ptVar7 + 0x98) = fVar4;
    *(float *)(ptVar7 + 0x94) = fVar4;
    *(float *)(ptVar7 + 0xa0) = fVar4;
    *(float *)(ptVar7 + 0x9c) = fVar3;
    fVar19 = (float)VectorSignedToFloat(uVar14,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar7 + 0x90) = fVar18 + fVar19 * fVar20 + fVar15 * (fVar3 - fVar16 / fVar2);
    tMatrix::Identity(ptVar7);
    uVar14 = VectorSignedToFloat(iVar10 + 7,(byte)(in_fpscr >> 0x16) & 3);
    iVar10 = iVar10 + 1;
    iVar6 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c) + iVar9;
    *(float *)(iVar8 + 0x8c) = fVar3;
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(float *)(iVar8 + 0x34) = fVar4;
    *(undefined4 *)(iVar8 + 0x38) = uVar14;
    fVar19 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar9));
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar8 = *(int *)(param_2 + 0x50) + iVar9;
    *(undefined4 *)(iVar8 + 0x38) = uVar14;
    *(float *)(iVar8 + 0x8c) = fVar3;
    uVar14 = *(undefined4 *)(iVar6 + iVar9 + 0x90);
    *(float *)(iVar8 + 0x34) = fVar1;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar8 + 0x30) = uVar14;
    fVar16 = DAT_00058968;
  } while (iVar10 != 7);
  if (0 < iVar13) {
    iVar10 = 0x498;
    iVar9 = 0;
    while( true ) {
      fVar17 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
      fVar17 = *(float *)(iVar6 + 0x90) +
               (fVar17 * (*(float *)(iVar6 + (iVar13 + 0xd) * 0xa8 + 0x90) -
                         *(float *)(iVar6 + 0x90))) / fVar12;
      *(float *)(iVar6 + iVar10 + 0x90) = fVar17;
      fVar19 = (float)Sin(fVar19);
      ptVar7 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar10);
      *(float *)(ptVar7 + 0x98) = fVar4;
      *(float *)(ptVar7 + 0x94) = fVar4;
      *(float *)(ptVar7 + 0xa0) = fVar4;
      *(float *)(ptVar7 + 0x9c) = fVar3;
      *(float *)(iVar6 + iVar10 + 0x90) = fVar17 + fVar19 * fVar15;
      fVar19 = (float)tMatrix::Identity(ptVar7);
      iVar6 = *(int *)(param_2 + 0x4c) + iVar10;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
      fVar19 = (float)Sin(fVar19);
      iVar8 = *(int *)(param_2 + 0x4c);
      *(float *)(iVar6 + 0x38) = fVar16 + fVar19 * fVar21;
      fVar19 = (float)Cos(extraout_s0);
      iVar6 = *(int *)(param_2 + 0x50);
      *(float *)(iVar8 + iVar10 + 0x34) = fVar21 - fVar19 * fVar21;
      fVar19 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar10));
      iVar6 = *(int *)(param_2 + 0x50) + iVar10;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar10 + 0x90);
      fVar19 = (float)Sin(fVar19);
      iVar8 = *(int *)(param_2 + 0x50);
      *(float *)(iVar6 + 0x38) = fVar16 + fVar19 * (fVar21 - fVar1);
      fVar19 = (float)Cos(extraout_s0_00);
      iVar6 = *(int *)(param_2 + 0x4c) + iVar10;
      fVar17 = *(float *)(iVar6 + 0x38);
      *(float *)(*(int *)(param_2 + 0x4c) + iVar10) = fVar3;
      *(float *)(iVar6 + 8) = fVar4;
      *(float *)(iVar6 + 4) = fVar4;
      *(float *)(iVar6 + 0x10) = fVar4;
      *(float *)(iVar6 + 0x18) = fVar16 - fVar17;
      *(float *)(iVar8 + iVar10 + 0x34) = fVar21 - (fVar21 - fVar1) * fVar19;
      *(float *)(iVar6 + 0x14) = fVar21 - *(float *)(iVar6 + 0x34);
      tVector::Normalize((tVector *)(iVar6 + 0x10));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar10);
      tVector::Cross(ptVar5 + 0x20,ptVar5,ptVar5 + 0x10);
      iVar6 = *(int *)(param_2 + 0x50) + iVar10;
      fVar19 = *(float *)(iVar6 + 0x34);
      fVar17 = *(float *)(iVar6 + 0x38);
      *(float *)(*(int *)(param_2 + 0x50) + iVar10) = fVar3;
      *(float *)(iVar6 + 8) = fVar4;
      *(float *)(iVar6 + 4) = fVar4;
      *(float *)(iVar6 + 0x10) = fVar4;
      *(float *)(iVar6 + 0x14) = fVar21 - fVar19;
      *(float *)(iVar6 + 0x18) = fVar16 - fVar17;
      tVector::Normalize((tVector *)(iVar6 + 0x10));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x50) + iVar10);
      iVar10 = iVar10 + 0xa8;
      fVar19 = (float)tVector::Cross(ptVar5 + 0x20,ptVar5,ptVar5 + 0x10);
      if (iVar13 <= iVar9 + 1) break;
      iVar6 = *(int *)(param_2 + 0x4c);
      iVar9 = iVar9 + 1;
    }
    iVar6 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar9 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar13 = 0;
    iVar10 = 0;
    while( true ) {
      iVar11 = iVar10 + 0xa8;
      iVar8 = iVar6 + iVar10;
      iVar6 = iVar6 + iVar11;
      fVar15 = *(float *)(iVar6 + 0x38);
      fVar21 = *(float *)(iVar6 + 0x34);
      iVar13 = iVar13 + 1;
      *(float *)(iVar8 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar21 - *(float *)(iVar8 + 0x34);
      *(float *)(iVar8 + 0x88) = fVar15 - *(float *)(iVar8 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar10 = *(int *)(param_2 + 0x50) + iVar10;
      iVar9 = *(int *)(param_2 + 0x50) + iVar11;
      fVar15 = *(float *)(iVar9 + 0x38);
      fVar21 = *(float *)(iVar9 + 0x34);
      fVar16 = *(float *)(iVar10 + 0x38);
      *(float *)(iVar10 + 0x80) = *(float *)(iVar9 + 0x30) - *(float *)(iVar10 + 0x30);
      *(float *)(iVar10 + 0x84) = fVar21 - *(float *)(iVar10 + 0x34);
      *(undefined4 *)(iVar8 + 0x8c) = uVar14;
      *(float *)(iVar10 + 0x88) = fVar15 - fVar16;
      uVar14 = tVector::Normalize((tVector *)(iVar10 + 0x80));
      iVar9 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar10 + 0x8c) = uVar14;
      if (iVar9 <= iVar13) break;
      iVar6 = *(int *)(param_2 + 0x4c);
      iVar10 = iVar11;
    }
    iVar6 = *(int *)(param_2 + 0x4c);
  }
  fVar15 = DAT_00058980;
  fVar21 = DAT_0005897c;
  iVar10 = *(int *)(param_2 + 0x50) + iVar9 * 0xa8;
  iVar6 = iVar6 + iVar9 * 0xa8;
  *(float *)(iVar6 + 0x8c) = DAT_0005897c;
  *(float *)(iVar6 + 0x88) = fVar21;
  *(float *)(iVar6 + 0x84) = fVar15;
  *(float *)(iVar6 + 0x80) = fVar15;
  *(float *)(iVar10 + 0x8c) = fVar21;
  *(float *)(iVar10 + 0x80) = fVar15;
  *(float *)(iVar10 + 0x88) = fVar21;
  *(float *)(iVar10 + 0x84) = fVar15;
  CalcLengthZ((cRPath *)param_2);
  return;
}
