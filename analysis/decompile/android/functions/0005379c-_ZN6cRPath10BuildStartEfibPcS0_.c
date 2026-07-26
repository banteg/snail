/*
 * mangled: _ZN6cRPath10BuildStartEfibPcS0_
 * demangled: cRPath::BuildStart(float, int, bool, char*, char*)
 * address: 0005379c
 * size: 1112
 */

/* cRPath::BuildStart(float, int, bool, char*, char*) */

void cRPath::BuildStart(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  int iVar2;
  int iVar3;
  tMatrix *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  int iVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 uVar18;
  float fVar19;

  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x2c) = 0x2c;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_2 + 0x30) = 0;
  iVar7 = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar8 = 0;
  iVar12 = (int)((float)(uint)param_3 * 3.1415927);
  fVar19 = (float)VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar12 + 0x10;
  fVar19 = fVar19 / 3.1415927;
  uVar14 = VectorSignedToFloat(iVar12 + 0xf,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar14;
  GetNodes((cRPath *)param_2);
  iVar3 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  *(int *)(param_2 + 0x38) = *(int *)(param_2 + 0x38) + -1;
  do {
    uVar14 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(undefined4 *)(ptVar4 + 0x90) = 0;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    iVar8 = iVar8 + 1;
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar5 + 0x34) = fVar19 + fVar19;
    *(undefined4 *)(iVar5 + 0x38) = uVar14;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(param_2 + 0x4c);
    iVar2 = *(int *)(param_2 + 0x50) + iVar7;
    *(undefined4 *)(iVar2 + 0x38) = uVar14;
    iVar5 = iVar3 + iVar7;
    *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar2 + 0x34) = fVar19 + fVar19 + 0.49;
  } while (iVar8 != 5);
  iVar8 = iVar12 + 5;
  iVar7 = iVar8 * 0xa8;
  do {
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(undefined4 *)(ptVar4 + 0x90) = 0;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    tMatrix::Identity(ptVar4);
    uVar14 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = *(int *)(param_2 + 0x50);
    iVar8 = iVar8 + 1;
    iVar5 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar14;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(param_2 + 0x4c);
    iVar2 = *(int *)(param_2 + 0x50) + iVar7;
    *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
    iVar5 = iVar3 + iVar7;
    *(undefined4 *)(iVar2 + 0x34) = 0x3efae148;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar2 + 0x38) = *(undefined4 *)(iVar5 + 0x38);
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  } while (iVar8 != iVar12 + 0x10);
  if (0 < iVar12) {
    iVar8 = 0;
    iVar7 = 0x2a0;
    do {
      iVar6 = iVar7 + 0xa8;
      ptVar4 = (tMatrix *)(iVar3 + iVar6);
      *(undefined4 *)(ptVar4 + 0x90) = 0;
      *(undefined4 *)(ptVar4 + 0x98) = 0;
      *(undefined4 *)(ptVar4 + 0x94) = 0;
      *(undefined4 *)(ptVar4 + 0xa0) = 0;
      *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
      fVar10 = (float)tMatrix::Identity(ptVar4);
      VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = *(int *)(param_2 + 0x4c) + iVar6;
      *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
      uVar18 = VectorSignedToFloat(iVar8 + 5,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(iVar5 + 0x38) = uVar18;
      fVar10 = (float)Cos(fVar10);
      iVar3 = *(int *)(param_2 + 0x50);
      *(float *)(iVar5 + 0x34) = fVar19 + fVar10 * fVar19;
      tMatrix::Identity((tMatrix *)(iVar3 + iVar6));
      iVar9 = *(int *)(param_2 + 0x4c);
      iVar5 = iVar9 + iVar6;
      fVar10 = *(float *)(iVar5 + 0x34);
      iVar2 = iVar9 + iVar7;
      iVar3 = *(int *)(param_2 + 0x50) + iVar6;
      uVar14 = *(undefined4 *)(iVar5 + 0x90);
      *(undefined4 *)(iVar3 + 0x38) = uVar18;
      *(undefined4 *)(iVar3 + 0x30) = uVar14;
      *(float *)(iVar3 + 0x34) = fVar10 + 0.49;
      if (iVar8 == 0) {
        tMatrix::RotIdentity((tMatrix *)(iVar9 + iVar7));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar7));
        if (iVar12 < 2) break;
      }
      else {
        fVar11 = *(float *)(iVar5 + 0x38);
        fVar15 = *(float *)(iVar2 + 0x30);
        fVar10 = *(float *)(iVar5 + 0x34);
        fVar13 = *(float *)(iVar2 + 0x34);
        fVar17 = *(float *)(iVar5 + 0x30);
        *(undefined4 *)(iVar2 + 8) = 0;
        *(undefined4 *)(iVar9 + iVar7) = 0x3f800000;
        *(undefined4 *)(iVar2 + 4) = 0;
        *(float *)(iVar2 + 0x24) = fVar10 - fVar13;
        *(float *)(iVar2 + 0x20) = fVar17 - fVar15;
        *(float *)(iVar2 + 0x28) = fVar11 - *(float *)(iVar2 + 0x38);
        tVector::Normalize((tVector *)(iVar2 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar7);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
        iVar5 = *(int *)(param_2 + 0x50);
        iVar2 = iVar5 + iVar7;
        iVar3 = iVar5 + iVar6;
        fVar15 = *(float *)(iVar2 + 0x30);
        fVar11 = *(float *)(iVar3 + 0x38);
        fVar10 = *(float *)(iVar3 + 0x34);
        fVar17 = *(float *)(iVar3 + 0x30);
        fVar13 = *(float *)(iVar2 + 0x34);
        fVar16 = *(float *)(iVar2 + 0x38);
        *(undefined4 *)(iVar2 + 8) = 0;
        *(undefined4 *)(iVar5 + iVar7) = 0x3f800000;
        *(undefined4 *)(iVar2 + 4) = 0;
        *(float *)(iVar2 + 0x20) = fVar17 - fVar15;
        *(float *)(iVar2 + 0x24) = fVar10 - fVar13;
        *(float *)(iVar2 + 0x28) = fVar11 - fVar16;
        tVector::Normalize((tVector *)(iVar2 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar7);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
        if (iVar12 <= iVar8 + 1) break;
      }
      iVar8 = iVar8 + 1;
      iVar3 = *(int *)(param_2 + 0x4c);
      iVar7 = iVar6;
    } while( true );
  }
  if (0 < *(int *)(param_2 + 0x38)) {
    iVar7 = 0;
    iVar3 = 0;
    do {
      iVar5 = iVar3 + 0xa8;
      iVar7 = iVar7 + 1;
      iVar12 = *(int *)(param_2 + 0x4c) + iVar3;
      iVar8 = *(int *)(param_2 + 0x4c) + iVar5;
      fVar10 = *(float *)(iVar8 + 0x38);
      fVar19 = *(float *)(iVar8 + 0x34);
      *(float *)(iVar12 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar12 + 0x30);
      *(float *)(iVar12 + 0x84) = fVar19 - *(float *)(iVar12 + 0x34);
      *(float *)(iVar12 + 0x88) = fVar10 - *(float *)(iVar12 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar12 + 0x80));
      iVar3 = *(int *)(param_2 + 0x50) + iVar3;
      iVar8 = *(int *)(param_2 + 0x50) + iVar5;
      fVar10 = *(float *)(iVar8 + 0x38);
      fVar19 = *(float *)(iVar8 + 0x34);
      fVar17 = *(float *)(iVar3 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar19 - *(float *)(iVar3 + 0x34);
      *(undefined4 *)(iVar12 + 0x8c) = uVar14;
      *(float *)(iVar3 + 0x88) = fVar10 - fVar17;
      uVar14 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar8 = *(int *)(param_2 + 0x38);
      *(undefined4 *)(iVar3 + 0x8c) = uVar14;
      iVar3 = iVar5;
    } while (iVar7 < iVar8);
  }
  CalcLengthZ((cRPath *)param_2);
  return;
}
