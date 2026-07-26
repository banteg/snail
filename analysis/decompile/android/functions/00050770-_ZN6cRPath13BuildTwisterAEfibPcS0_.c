/*
 * mangled: _ZN6cRPath13BuildTwisterAEfibPcS0_
 * demangled: cRPath::BuildTwisterA(float, int, bool, char*, char*)
 * address: 00050770
 * size: 1240
 */

/* cRPath::BuildTwisterA(float, int, bool, char*, char*) */

void cRPath::BuildTwisterA(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  tVector *ptVar5;
  undefined4 uVar6;
  int iVar7;
  tMatrix *ptVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint in_fpscr;
  float fVar14;
  float extraout_s0;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 uVar18;
  undefined4 uVar19;

  uVar6 = DAT_00050b50;
  *(undefined4 *)(param_2 + 0x2c) = 0x3b;
  *(undefined4 *)(param_2 + 0x44) = uVar6;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x40) = DAT_00050b28;
  *(undefined4 *)(param_2 + 0x38) = 0x22;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  GetNodes((cRPath *)param_2);
  uVar18 = DAT_00050b54;
  fVar17 = DAT_00050b30;
  fVar14 = DAT_00050b2c;
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  ptVar8 = *(tMatrix **)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  *(undefined4 *)(ptVar8 + 0x98) = uVar18;
  *(undefined4 *)(ptVar8 + 0x94) = uVar18;
  *(undefined4 *)(ptVar8 + 0xa0) = uVar18;
  uVar4 = DAT_00050b54;
  uVar6 = DAT_00050b50;
  fVar3 = DAT_00050b48;
  fVar2 = DAT_00050b44;
  fVar1 = DAT_00050b34;
  fVar16 = DAT_00050b2c;
  fVar17 = fVar15 * fVar14 - fVar17;
  iVar12 = 0;
  *(float *)(ptVar8 + 0x90) = fVar17;
  if (((uint)param_5 ^ 1) != 0) {
    *(float *)(ptVar8 + 0x90) = -fVar17;
  }
  *(undefined4 *)(ptVar8 + 0x9c) = DAT_00050b50;
  tMatrix::Identity(ptVar8);
  iVar9 = *(int *)(param_2 + 0x4c);
  ptVar8 = *(tMatrix **)(param_2 + 0x50);
  *(undefined4 *)(iVar9 + 0x38) = uVar18;
  *(undefined4 *)(iVar9 + 0x34) = uVar18;
  *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
  tMatrix::Identity(ptVar8);
  fVar17 = DAT_00050b30;
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  iVar7 = *(int *)(param_2 + 0x50);
  iVar9 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
  *(float *)(iVar7 + 0x34) = DAT_00050b34;
  fVar14 = DAT_00050b2c;
  *(undefined4 *)(iVar7 + 0x38) = uVar18;
  *(undefined4 *)(iVar9 + 0x1640) = uVar4;
  fVar17 = fVar15 * fVar14 - fVar17;
  *(undefined4 *)(iVar9 + 0x163c) = uVar4;
  *(undefined4 *)(iVar9 + 0x1648) = uVar4;
  *(undefined4 *)(iVar9 + 0x1644) = uVar6;
  uVar18 = DAT_00050b4c;
  *(float *)(iVar9 + 0x1638) = fVar17;
  if (((uint)param_5 ^ 1) != 0) {
    *(float *)(iVar9 + 0x1638) = -fVar17;
  }
  tMatrix::Identity((tMatrix *)(iVar9 + 0x15a8));
  iVar7 = *(int *)(param_2 + 0x4c);
  iVar9 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar7 + 0x15e0) = uVar18;
  *(undefined4 *)(iVar7 + 0x15d8) = *(undefined4 *)(iVar7 + 0x1638);
  *(undefined4 *)(iVar7 + 0x15dc) = uVar4;
  fVar14 = (float)tMatrix::Identity((tMatrix *)(iVar9 + 0x15a8));
  iVar9 = *(int *)(param_2 + 0x50);
  iVar7 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(iVar9 + 0x15e0) = uVar18;
  uVar18 = *(undefined4 *)(iVar7 + 0x1638);
  *(float *)(iVar9 + 0x15dc) = fVar1;
  *(undefined4 *)(iVar9 + 0x15d8) = uVar18;
  iVar9 = 0;
  do {
    iVar12 = iVar12 + 1;
    iVar11 = iVar9 + 0xa8;
    fVar14 = (float)Cos(fVar14);
    ptVar8 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar11);
    *(undefined4 *)(ptVar8 + 0x98) = uVar4;
    uVar19 = VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(ptVar8 + 0x94) = uVar4;
    *(undefined4 *)(ptVar8 + 0xa0) = uVar4;
    *(undefined4 *)(ptVar8 + 0x9c) = uVar6;
    *(float *)(iVar7 + iVar11 + 0x90) = fVar3 + (fVar16 + fVar14 * fVar16) * fVar2;
    fVar14 = (float)tMatrix::Identity(ptVar8);
    iVar13 = *(int *)(param_2 + 0x4c) + iVar11;
    *(undefined4 *)(iVar13 + 0x30) = *(undefined4 *)(iVar13 + 0x90);
    fVar14 = (float)Sin(fVar14);
    fVar17 = (float)Sin(extraout_s0);
    iVar7 = *(int *)(param_2 + 0x50);
    *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar11 + 0x38) = uVar19;
    *(float *)(iVar13 + 0x34) = fVar14 * fVar17 * (float)(uint)param_3;
    tMatrix::Identity((tMatrix *)(iVar7 + iVar11));
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar13 = iVar10 + iVar11;
    fVar14 = *(float *)(iVar13 + 0x34);
    iVar7 = *(int *)(param_2 + 0x50) + iVar11;
    uVar18 = *(undefined4 *)(iVar13 + 0x90);
    *(undefined4 *)(iVar7 + 0x38) = uVar19;
    *(undefined4 *)(iVar7 + 0x30) = uVar18;
    *(float *)(iVar7 + 0x34) = fVar14 + fVar1;
    if (iVar12 == 1) {
      tMatrix::RotIdentity((tMatrix *)(iVar10 + iVar9));
      fVar14 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar9));
    }
    else {
      iVar10 = iVar10 + iVar9;
      fVar15 = *(float *)(iVar13 + 0x38);
      fVar14 = *(float *)(iVar13 + 0x34);
      fVar17 = *(float *)(iVar13 + 0x30);
      *(undefined4 *)(iVar10 + 0x18) = uVar4;
      *(undefined4 *)(iVar10 + 0x14) = uVar6;
      *(undefined4 *)(iVar10 + 0x10) = uVar4;
      *(float *)(iVar10 + 0x24) = fVar14 - *(float *)(iVar10 + 0x34);
      *(float *)(iVar10 + 0x20) = fVar17 - *(float *)(iVar10 + 0x30);
      *(float *)(iVar10 + 0x28) = fVar15 - *(float *)(iVar10 + 0x38);
      tVector::Normalize((tVector *)(iVar10 + 0x20));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar9);
      tVector::Cross(ptVar5,ptVar5 + 0x10,ptVar5 + 0x20);
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar9);
      tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
      tMatrix::Orthoganalize((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar9));
      iVar7 = *(int *)(param_2 + 0x50) + iVar11;
      iVar13 = *(int *)(param_2 + 0x50) + iVar9;
      fVar15 = *(float *)(iVar7 + 0x38);
      fVar14 = *(float *)(iVar7 + 0x34);
      fVar17 = *(float *)(iVar7 + 0x30);
      *(undefined4 *)(iVar13 + 0x18) = uVar4;
      *(undefined4 *)(iVar13 + 0x14) = uVar6;
      *(undefined4 *)(iVar13 + 0x10) = uVar4;
      *(float *)(iVar13 + 0x24) = fVar14 - *(float *)(iVar13 + 0x34);
      *(float *)(iVar13 + 0x20) = fVar17 - *(float *)(iVar13 + 0x30);
      *(float *)(iVar13 + 0x28) = fVar15 - *(float *)(iVar13 + 0x38);
      tVector::Normalize((tVector *)(iVar13 + 0x20));
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x50) + iVar9);
      tVector::Cross(ptVar5,ptVar5 + 0x10,ptVar5 + 0x20);
      ptVar5 = (tVector *)(*(int *)(param_2 + 0x50) + iVar9);
      tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
      fVar14 = (float)tMatrix::Orthoganalize((tMatrix *)(*(int *)(param_2 + 0x50) + iVar9));
      if (iVar12 == 0x20) {
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar12 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar7 = 0;
          iVar9 = 0;
          do {
            iVar10 = iVar9 + 0xa8;
            iVar7 = iVar7 + 1;
            iVar13 = *(int *)(param_2 + 0x4c) + iVar9;
            iVar12 = *(int *)(param_2 + 0x4c) + iVar10;
            fVar16 = *(float *)(iVar12 + 0x38);
            fVar14 = *(float *)(iVar12 + 0x34);
            *(float *)(iVar13 + 0x80) = *(float *)(iVar12 + 0x30) - *(float *)(iVar13 + 0x30);
            *(float *)(iVar13 + 0x84) = fVar14 - *(float *)(iVar13 + 0x34);
            *(float *)(iVar13 + 0x88) = fVar16 - *(float *)(iVar13 + 0x38);
            uVar6 = tVector::Normalize((tVector *)(iVar13 + 0x80));
            iVar9 = *(int *)(param_2 + 0x50) + iVar9;
            iVar12 = *(int *)(param_2 + 0x50) + iVar10;
            fVar16 = *(float *)(iVar12 + 0x38);
            fVar14 = *(float *)(iVar12 + 0x34);
            fVar17 = *(float *)(iVar9 + 0x38);
            *(float *)(iVar9 + 0x80) = *(float *)(iVar12 + 0x30) - *(float *)(iVar9 + 0x30);
            *(float *)(iVar9 + 0x84) = fVar14 - *(float *)(iVar9 + 0x34);
            *(undefined4 *)(iVar13 + 0x8c) = uVar6;
            *(float *)(iVar9 + 0x88) = fVar16 - fVar17;
            uVar6 = tVector::Normalize((tVector *)(iVar9 + 0x80));
            iVar12 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar9 + 0x8c) = uVar6;
            iVar9 = iVar10;
          } while (iVar7 < iVar12);
        }
        uVar18 = DAT_00050b54;
        uVar6 = DAT_00050b50;
        iVar9 = *(int *)(param_2 + 0x50) + iVar12 * 0xa8;
        iVar12 = *(int *)(param_2 + 0x4c) + iVar12 * 0xa8;
        *(undefined4 *)(iVar12 + 0x8c) = DAT_00050b50;
        *(undefined4 *)(iVar12 + 0x88) = uVar6;
        *(undefined4 *)(iVar12 + 0x84) = uVar18;
        *(undefined4 *)(iVar12 + 0x80) = uVar18;
        *(undefined4 *)(iVar9 + 0x8c) = uVar6;
        *(undefined4 *)(iVar9 + 0x80) = uVar18;
        *(undefined4 *)(iVar9 + 0x88) = uVar6;
        *(undefined4 *)(iVar9 + 0x84) = uVar18;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar7 = *(int *)(param_2 + 0x4c);
    iVar9 = iVar11;
  } while( true );
}
