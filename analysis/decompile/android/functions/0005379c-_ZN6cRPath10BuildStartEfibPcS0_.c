/*
 * mangled: _ZN6cRPath10BuildStartEfibPcS0_
 * demangled: cRPath::BuildStart(float, int, bool, char*, char*)
 * address: 0005379c
 * size: 1112
 */

/* cRPath::BuildStart(float, int, bool, char*, char*) */

void cRPath::BuildStart(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  tVector *ptVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  tMatrix *ptVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint in_fpscr;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  int iVar17;
  float fVar18;
  undefined4 uVar19;
  float fVar20;
  float fVar21;
  undefined4 uVar22;

  uVar3 = DAT_00053968;
  fVar13 = DAT_00053964;
  fVar16 = (float)(uint)param_3 * DAT_00053964;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x2c) = 0x2c;
  *(undefined4 *)(param_2 + 0x44) = uVar3;
  *(undefined1 *)(param_2 + 0x30) = 0;
  iVar9 = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  fVar12 = DAT_00053970;
  uVar1 = DAT_0005396c;
  iVar10 = 0;
  iVar17 = (int)fVar16;
  fVar16 = (float)VectorSignedToFloat(iVar17,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar17 + 0x10;
  fVar16 = fVar16 / fVar13;
  uVar19 = VectorSignedToFloat(iVar17 + 0xf,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar19;
  GetNodes((cRPath *)param_2);
  iVar5 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  *(int *)(param_2 + 0x38) = *(int *)(param_2 + 0x38) + -1;
  do {
    uVar19 = VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    ptVar6 = (tMatrix *)(iVar5 + iVar9);
    *(undefined4 *)(ptVar6 + 0x90) = uVar1;
    *(undefined4 *)(ptVar6 + 0x98) = uVar1;
    *(undefined4 *)(ptVar6 + 0x94) = uVar1;
    *(undefined4 *)(ptVar6 + 0xa0) = uVar1;
    *(undefined4 *)(ptVar6 + 0x9c) = uVar3;
    iVar10 = iVar10 + 1;
    tMatrix::Identity(ptVar6);
    iVar5 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar9;
    *(undefined4 *)(iVar7 + 0x8c) = uVar3;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(float *)(iVar7 + 0x34) = fVar16 + fVar16;
    *(undefined4 *)(iVar7 + 0x38) = uVar19;
    tMatrix::Identity((tMatrix *)(iVar5 + iVar9));
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar9;
    *(undefined4 *)(iVar4 + 0x38) = uVar19;
    iVar7 = iVar5 + iVar9;
    *(undefined4 *)(iVar4 + 0x8c) = uVar3;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(float *)(iVar4 + 0x34) = fVar16 + fVar16 + fVar12;
    fVar13 = DAT_00053970;
  } while (iVar10 != 5);
  iVar10 = iVar17 + 5;
  iVar9 = iVar10 * 0xa8;
  do {
    ptVar6 = (tMatrix *)(iVar5 + iVar9);
    *(undefined4 *)(ptVar6 + 0x90) = uVar1;
    *(undefined4 *)(ptVar6 + 0x98) = uVar1;
    *(undefined4 *)(ptVar6 + 0x94) = uVar1;
    *(undefined4 *)(ptVar6 + 0xa0) = uVar1;
    *(undefined4 *)(ptVar6 + 0x9c) = uVar3;
    tMatrix::Identity(ptVar6);
    uVar19 = VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    iVar5 = *(int *)(param_2 + 0x50);
    iVar10 = iVar10 + 1;
    iVar7 = *(int *)(param_2 + 0x4c) + iVar9;
    *(undefined4 *)(iVar7 + 0x8c) = uVar3;
    *(undefined4 *)(iVar7 + 0x34) = uVar1;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar7 + 0x38) = uVar19;
    tMatrix::Identity((tMatrix *)(iVar5 + iVar9));
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar9;
    *(undefined4 *)(iVar4 + 0x8c) = uVar3;
    iVar7 = iVar5 + iVar9;
    *(float *)(iVar4 + 0x34) = fVar13;
    iVar9 = iVar9 + 0xa8;
    *(undefined4 *)(iVar4 + 0x38) = *(undefined4 *)(iVar7 + 0x38);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
  } while (iVar10 != iVar17 + 0x10);
  if (0 < iVar17) {
    iVar10 = 0;
    iVar9 = 0x2a0;
    do {
      iVar8 = iVar9 + 0xa8;
      ptVar6 = (tMatrix *)(iVar5 + iVar8);
      *(undefined4 *)(ptVar6 + 0x90) = uVar1;
      *(undefined4 *)(ptVar6 + 0x98) = uVar1;
      *(undefined4 *)(ptVar6 + 0x94) = uVar1;
      *(undefined4 *)(ptVar6 + 0xa0) = uVar1;
      *(undefined4 *)(ptVar6 + 0x9c) = uVar3;
      fVar12 = (float)tMatrix::Identity(ptVar6);
      VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
      iVar7 = *(int *)(param_2 + 0x4c) + iVar8;
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      uVar22 = VectorSignedToFloat(iVar10 + 5,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(iVar7 + 0x38) = uVar22;
      fVar12 = (float)Cos(fVar12);
      iVar5 = *(int *)(param_2 + 0x50);
      *(float *)(iVar7 + 0x34) = fVar16 + fVar12 * fVar16;
      tMatrix::Identity((tMatrix *)(iVar5 + iVar8));
      iVar11 = *(int *)(param_2 + 0x4c);
      iVar7 = iVar11 + iVar8;
      fVar12 = *(float *)(iVar7 + 0x34);
      iVar4 = iVar11 + iVar9;
      iVar5 = *(int *)(param_2 + 0x50) + iVar8;
      uVar19 = *(undefined4 *)(iVar7 + 0x90);
      *(undefined4 *)(iVar5 + 0x38) = uVar22;
      *(undefined4 *)(iVar5 + 0x30) = uVar19;
      *(float *)(iVar5 + 0x34) = fVar12 + fVar13;
      if (iVar10 == 0) {
        tMatrix::RotIdentity((tMatrix *)(iVar11 + iVar9));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar9));
        if (iVar17 < 2) break;
      }
      else {
        fVar15 = *(float *)(iVar7 + 0x38);
        fVar20 = *(float *)(iVar4 + 0x30);
        fVar12 = *(float *)(iVar7 + 0x34);
        fVar18 = *(float *)(iVar4 + 0x34);
        fVar14 = *(float *)(iVar7 + 0x30);
        *(undefined4 *)(iVar4 + 8) = uVar1;
        *(undefined4 *)(iVar11 + iVar9) = uVar3;
        *(undefined4 *)(iVar4 + 4) = uVar1;
        *(float *)(iVar4 + 0x24) = fVar12 - fVar18;
        *(float *)(iVar4 + 0x20) = fVar14 - fVar20;
        *(float *)(iVar4 + 0x28) = fVar15 - *(float *)(iVar4 + 0x38);
        tVector::Normalize((tVector *)(iVar4 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar9);
        tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
        iVar7 = *(int *)(param_2 + 0x50);
        iVar4 = iVar7 + iVar9;
        iVar5 = iVar7 + iVar8;
        fVar20 = *(float *)(iVar4 + 0x30);
        fVar15 = *(float *)(iVar5 + 0x38);
        fVar12 = *(float *)(iVar5 + 0x34);
        fVar14 = *(float *)(iVar5 + 0x30);
        fVar18 = *(float *)(iVar4 + 0x34);
        fVar21 = *(float *)(iVar4 + 0x38);
        *(undefined4 *)(iVar4 + 8) = uVar1;
        *(undefined4 *)(iVar7 + iVar9) = uVar3;
        *(undefined4 *)(iVar4 + 4) = uVar1;
        *(float *)(iVar4 + 0x20) = fVar14 - fVar20;
        *(float *)(iVar4 + 0x24) = fVar12 - fVar18;
        *(float *)(iVar4 + 0x28) = fVar15 - fVar21;
        tVector::Normalize((tVector *)(iVar4 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_2 + 0x50) + iVar9);
        tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
        if (iVar17 <= iVar10 + 1) break;
      }
      iVar10 = iVar10 + 1;
      iVar5 = *(int *)(param_2 + 0x4c);
      iVar9 = iVar8;
    } while( true );
  }
  if (0 < *(int *)(param_2 + 0x38)) {
    iVar9 = 0;
    iVar5 = 0;
    do {
      iVar7 = iVar5 + 0xa8;
      iVar9 = iVar9 + 1;
      iVar17 = *(int *)(param_2 + 0x4c) + iVar5;
      iVar10 = *(int *)(param_2 + 0x4c) + iVar7;
      fVar12 = *(float *)(iVar10 + 0x38);
      fVar13 = *(float *)(iVar10 + 0x34);
      *(float *)(iVar17 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar17 + 0x30);
      *(float *)(iVar17 + 0x84) = fVar13 - *(float *)(iVar17 + 0x34);
      *(float *)(iVar17 + 0x88) = fVar12 - *(float *)(iVar17 + 0x38);
      uVar3 = tVector::Normalize((tVector *)(iVar17 + 0x80));
      iVar5 = *(int *)(param_2 + 0x50) + iVar5;
      iVar10 = *(int *)(param_2 + 0x50) + iVar7;
      fVar12 = *(float *)(iVar10 + 0x38);
      fVar13 = *(float *)(iVar10 + 0x34);
      fVar16 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar5 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar13 - *(float *)(iVar5 + 0x34);
      *(undefined4 *)(iVar17 + 0x8c) = uVar3;
      *(float *)(iVar5 + 0x88) = fVar12 - fVar16;
      uVar3 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      iVar10 = *(int *)(param_2 + 0x38);
      *(undefined4 *)(iVar5 + 0x8c) = uVar3;
      iVar5 = iVar7;
    } while (iVar9 < iVar10);
  }
  CalcLengthZ((cRPath *)param_2);
  return;
}
