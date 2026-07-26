/*
 * mangled: _ZN6cRPath8BuildDipEfibPcS0_
 * demangled: cRPath::BuildDip(float, int, bool, char*, char*)
 * address: 00056d14
 * size: 1116
 */

/* cRPath::BuildDip(float, int, bool, char*, char*) */

void cRPath::BuildDip(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  tMatrix *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  float fVar11;
  int iVar12;
  undefined4 uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  *(undefined4 *)(param_2 + 0x2c) = 0x18;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x34) = 0;
  iVar12 = (int)((float)(uint)param_3 * 5.0);
  fVar17 = (float)VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar12 + 2;
  iVar5 = (iVar12 + 1) * 0xa8;
  uVar13 = VectorSignedToFloat(iVar12 + 2,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar13;
  fVar17 = (fVar17 / 6.2831855) * 0.6 * 0.5;
  GetNodes((cRPath *)param_2);
  ptVar2 = *(tMatrix **)(param_2 + 0x4c);
  *(undefined4 *)(ptVar2 + 0x90) = 0;
  *(undefined4 *)(ptVar2 + 0x98) = 0;
  *(undefined4 *)(ptVar2 + 0x94) = 0;
  *(undefined4 *)(ptVar2 + 0xa0) = 0;
  *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
  *(undefined1 *)(param_2 + 0x84) = 0;
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_2 + 0x4c);
  ptVar2 = *(tMatrix **)(param_2 + 0x50);
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar3 + 0x34) = 0;
  tMatrix::Identity(ptVar2);
  iVar4 = *(int *)(param_2 + 0x4c);
  iVar3 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  uVar13 = VectorSignedToFloat(iVar12 + 1,(byte)(in_fpscr >> 0x16) & 3);
  ptVar2 = (tMatrix *)(iVar4 + iVar5);
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
  *(undefined4 *)(ptVar2 + 0x90) = 0;
  *(undefined4 *)(ptVar2 + 0x98) = 0;
  *(undefined4 *)(ptVar2 + 0x94) = 0;
  *(undefined4 *)(ptVar2 + 0xa0) = 0;
  *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_2 + 0x50);
  iVar4 = *(int *)(param_2 + 0x4c) + iVar5;
  *(undefined4 *)(iVar4 + 0x38) = uVar13;
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar4 + 0x34) = 0;
  tMatrix::Identity((tMatrix *)(iVar3 + iVar5));
  iVar4 = *(int *)(param_2 + 0x4c);
  iVar3 = *(int *)(param_2 + 0x50) + iVar5;
  *(undefined4 *)(iVar3 + 0x38) = uVar13;
  *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar4 + iVar5 + 0x90);
  if (0 < iVar12) {
    iVar3 = 0;
    iVar5 = 0;
    while( true ) {
      iVar6 = iVar3 + 0xa8;
      ptVar2 = (tMatrix *)(iVar4 + iVar6);
      *(undefined4 *)(ptVar2 + 0x90) = 0;
      *(undefined4 *)(ptVar2 + 0x98) = 0;
      *(undefined4 *)(ptVar2 + 0x94) = 0;
      *(undefined4 *)(ptVar2 + 0xa0) = 0;
      *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
      iVar7 = iVar5 + 1;
      fVar9 = (float)tMatrix::Identity(ptVar2);
      iVar8 = *(int *)(param_2 + 0x4c) + iVar6;
      *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
      uVar13 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      fVar9 = (float)Cos(fVar9);
      iVar4 = *(int *)(param_2 + 0x50);
      *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar6 + 0x38) = uVar13;
      *(float *)(iVar8 + 0x34) = -((1.0 - fVar9) * fVar17);
      fVar9 = (float)tMatrix::Identity((tMatrix *)(iVar4 + iVar6));
      iVar4 = *(int *)(param_2 + 0x50) + iVar6;
      *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar6 + 0x90);
      fVar9 = (float)Cos(fVar9);
      *(undefined4 *)(*(int *)(param_2 + 0x50) + iVar6 + 0x38) = uVar13;
      *(float *)(iVar4 + 0x34) = 0.49 - (1.0 - fVar9) * fVar17;
      if (iVar5 < 1) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar3));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar3));
      }
      else {
        iVar5 = *(int *)(param_2 + 0x4c);
        iVar8 = iVar5 + iVar3;
        iVar4 = iVar5 + iVar6;
        fVar14 = *(float *)(iVar8 + 0x30);
        fVar10 = *(float *)(iVar4 + 0x38);
        fVar9 = *(float *)(iVar4 + 0x34);
        fVar11 = *(float *)(iVar8 + 0x34);
        fVar16 = *(float *)(iVar4 + 0x30);
        *(undefined4 *)(iVar8 + 8) = 0;
        *(undefined4 *)(iVar8 + 4) = 0;
        *(undefined4 *)(iVar5 + iVar3) = 0x3f800000;
        *(float *)(iVar8 + 0x24) = fVar9 - fVar11;
        *(float *)(iVar8 + 0x20) = fVar16 - fVar14;
        *(float *)(iVar8 + 0x28) = fVar10 - *(float *)(iVar8 + 0x38);
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar3);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
        iVar5 = *(int *)(param_2 + 0x50);
        iVar8 = iVar5 + iVar3;
        iVar4 = iVar5 + iVar6;
        fVar14 = *(float *)(iVar8 + 0x30);
        fVar10 = *(float *)(iVar4 + 0x38);
        fVar9 = *(float *)(iVar4 + 0x34);
        fVar16 = *(float *)(iVar4 + 0x30);
        fVar11 = *(float *)(iVar8 + 0x34);
        fVar15 = *(float *)(iVar8 + 0x38);
        *(undefined4 *)(iVar8 + 8) = 0;
        *(undefined4 *)(iVar5 + iVar3) = 0x3f800000;
        *(undefined4 *)(iVar8 + 4) = 0;
        *(float *)(iVar8 + 0x20) = fVar16 - fVar14;
        *(float *)(iVar8 + 0x24) = fVar9 - fVar11;
        *(float *)(iVar8 + 0x28) = fVar10 - fVar15;
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar3);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      }
      if (iVar12 <= iVar7) break;
      iVar4 = *(int *)(param_2 + 0x4c);
      iVar3 = iVar6;
      iVar5 = iVar7;
    }
    iVar4 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar3 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar12 = 0;
    iVar5 = 0;
    while( true ) {
      iVar7 = iVar5 + 0xa8;
      iVar6 = iVar4 + iVar5;
      iVar4 = iVar4 + iVar7;
      fVar9 = *(float *)(iVar4 + 0x38);
      fVar17 = *(float *)(iVar4 + 0x34);
      iVar12 = iVar12 + 1;
      *(float *)(iVar6 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar17 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x88) = fVar9 - *(float *)(iVar6 + 0x38);
      uVar13 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar5 = *(int *)(param_2 + 0x50) + iVar5;
      iVar3 = *(int *)(param_2 + 0x50) + iVar7;
      fVar9 = *(float *)(iVar3 + 0x38);
      fVar17 = *(float *)(iVar3 + 0x34);
      fVar16 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar5 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar17 - *(float *)(iVar5 + 0x34);
      *(undefined4 *)(iVar6 + 0x8c) = uVar13;
      *(float *)(iVar5 + 0x88) = fVar9 - fVar16;
      uVar13 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      iVar3 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar5 + 0x8c) = uVar13;
      if (iVar3 <= iVar12) break;
      iVar4 = *(int *)(param_2 + 0x4c);
      iVar5 = iVar7;
    }
    iVar4 = *(int *)(param_2 + 0x4c);
  }
  iVar5 = *(int *)(param_2 + 0x50) + iVar3 * 0xa8;
  iVar4 = iVar4 + iVar3 * 0xa8;
  *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x80) = 0;
  *(undefined4 *)(iVar5 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
