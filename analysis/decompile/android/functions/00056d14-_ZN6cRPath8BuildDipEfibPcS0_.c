/*
 * mangled: _ZN6cRPath8BuildDipEfibPcS0_
 * demangled: cRPath::BuildDip(float, int, bool, char*, char*)
 * address: 00056d14
 * size: 1116
 */

/* cRPath::BuildDip(float, int, bool, char*, char*) */

void cRPath::BuildDip(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  tVector *ptVar2;
  undefined4 uVar3;
  tMatrix *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint in_fpscr;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  int iVar16;
  undefined4 uVar17;
  float fVar18;
  float fVar19;
  float fVar20;

  fVar20 = DAT_0005706c;
  fVar15 = (float)(uint)param_3 * DAT_00057068;
  *(undefined4 *)(param_2 + 0x2c) = 0x18;
  *(char **)(param_2 + 0x48) = param_4;
  fVar1 = DAT_0005707c;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(float *)(param_2 + 0x44) = fVar1;
  *(undefined4 *)(param_2 + 0x34) = 0;
  uVar3 = DAT_00057080;
  fVar11 = DAT_00057074;
  fVar13 = DAT_00057070;
  iVar16 = (int)fVar15;
  fVar15 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_2 + 0x38) = iVar16 + 2;
  iVar7 = (iVar16 + 1) * 0xa8;
  uVar17 = VectorSignedToFloat(iVar16 + 2,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_2 + 0x40) = uVar17;
  fVar20 = (fVar15 / fVar20) * fVar11 * DAT_00057078;
  GetNodes((cRPath *)param_2);
  ptVar4 = *(tMatrix **)(param_2 + 0x4c);
  *(undefined4 *)(ptVar4 + 0x90) = uVar3;
  *(undefined4 *)(ptVar4 + 0x98) = uVar3;
  *(undefined4 *)(ptVar4 + 0x94) = uVar3;
  *(undefined4 *)(ptVar4 + 0xa0) = uVar3;
  *(float *)(ptVar4 + 0x9c) = fVar1;
  *(undefined1 *)(param_2 + 0x84) = 0;
  tMatrix::Identity(ptVar4);
  iVar5 = *(int *)(param_2 + 0x4c);
  ptVar4 = *(tMatrix **)(param_2 + 0x50);
  *(undefined4 *)(iVar5 + 0x38) = uVar3;
  *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  *(undefined4 *)(iVar5 + 0x34) = uVar3;
  tMatrix::Identity(ptVar4);
  iVar6 = *(int *)(param_2 + 0x4c);
  iVar5 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
  uVar17 = VectorSignedToFloat(iVar16 + 1,(byte)(in_fpscr >> 0x16) & 3);
  ptVar4 = (tMatrix *)(iVar6 + iVar7);
  *(undefined4 *)(iVar5 + 0x38) = uVar3;
  *(float *)(iVar5 + 0x34) = fVar13;
  *(undefined4 *)(ptVar4 + 0x90) = uVar3;
  *(undefined4 *)(ptVar4 + 0x98) = uVar3;
  *(undefined4 *)(ptVar4 + 0x94) = uVar3;
  *(undefined4 *)(ptVar4 + 0xa0) = uVar3;
  *(float *)(ptVar4 + 0x9c) = fVar1;
  tMatrix::Identity(ptVar4);
  iVar5 = *(int *)(param_2 + 0x50);
  iVar6 = *(int *)(param_2 + 0x4c) + iVar7;
  *(undefined4 *)(iVar6 + 0x38) = uVar17;
  *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
  *(undefined4 *)(iVar6 + 0x34) = uVar3;
  tMatrix::Identity((tMatrix *)(iVar5 + iVar7));
  iVar6 = *(int *)(param_2 + 0x4c);
  iVar5 = *(int *)(param_2 + 0x50) + iVar7;
  *(undefined4 *)(iVar5 + 0x38) = uVar17;
  *(float *)(iVar5 + 0x34) = fVar13;
  *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar6 + iVar7 + 0x90);
  if (0 < iVar16) {
    iVar5 = 0;
    iVar7 = 0;
    while( true ) {
      iVar8 = iVar5 + 0xa8;
      ptVar4 = (tMatrix *)(iVar6 + iVar8);
      *(undefined4 *)(ptVar4 + 0x90) = uVar3;
      *(undefined4 *)(ptVar4 + 0x98) = uVar3;
      *(undefined4 *)(ptVar4 + 0x94) = uVar3;
      *(undefined4 *)(ptVar4 + 0xa0) = uVar3;
      *(float *)(ptVar4 + 0x9c) = fVar1;
      iVar9 = iVar7 + 1;
      fVar11 = (float)tMatrix::Identity(ptVar4);
      iVar10 = *(int *)(param_2 + 0x4c) + iVar8;
      *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar10 + 0x90);
      uVar17 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
      fVar11 = (float)Cos(fVar11);
      iVar6 = *(int *)(param_2 + 0x50);
      *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar8 + 0x38) = uVar17;
      *(float *)(iVar10 + 0x34) = -((fVar1 - fVar11) * fVar20);
      fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar8));
      iVar6 = *(int *)(param_2 + 0x50) + iVar8;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar8 + 0x90);
      fVar11 = (float)Cos(fVar11);
      *(undefined4 *)(*(int *)(param_2 + 0x50) + iVar8 + 0x38) = uVar17;
      *(float *)(iVar6 + 0x34) = fVar13 - (fVar1 - fVar11) * fVar20;
      if (iVar7 < 1) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar5));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar5));
      }
      else {
        iVar7 = *(int *)(param_2 + 0x4c);
        iVar10 = iVar7 + iVar5;
        iVar6 = iVar7 + iVar8;
        fVar18 = *(float *)(iVar10 + 0x30);
        fVar12 = *(float *)(iVar6 + 0x38);
        fVar11 = *(float *)(iVar6 + 0x34);
        fVar14 = *(float *)(iVar10 + 0x34);
        fVar15 = *(float *)(iVar6 + 0x30);
        *(undefined4 *)(iVar10 + 8) = uVar3;
        *(undefined4 *)(iVar10 + 4) = uVar3;
        *(float *)(iVar7 + iVar5) = fVar1;
        *(float *)(iVar10 + 0x24) = fVar11 - fVar14;
        *(float *)(iVar10 + 0x20) = fVar15 - fVar18;
        *(float *)(iVar10 + 0x28) = fVar12 - *(float *)(iVar10 + 0x38);
        tVector::Normalize((tVector *)(iVar10 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar5);
        tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
        iVar7 = *(int *)(param_2 + 0x50);
        iVar10 = iVar7 + iVar5;
        iVar6 = iVar7 + iVar8;
        fVar18 = *(float *)(iVar10 + 0x30);
        fVar12 = *(float *)(iVar6 + 0x38);
        fVar11 = *(float *)(iVar6 + 0x34);
        fVar15 = *(float *)(iVar6 + 0x30);
        fVar14 = *(float *)(iVar10 + 0x34);
        fVar19 = *(float *)(iVar10 + 0x38);
        *(undefined4 *)(iVar10 + 8) = uVar3;
        *(float *)(iVar7 + iVar5) = fVar1;
        *(undefined4 *)(iVar10 + 4) = uVar3;
        *(float *)(iVar10 + 0x20) = fVar15 - fVar18;
        *(float *)(iVar10 + 0x24) = fVar11 - fVar14;
        *(float *)(iVar10 + 0x28) = fVar12 - fVar19;
        tVector::Normalize((tVector *)(iVar10 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_2 + 0x50) + iVar5);
        tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
      }
      if (iVar16 <= iVar9) break;
      iVar6 = *(int *)(param_2 + 0x4c);
      iVar5 = iVar8;
      iVar7 = iVar9;
    }
    iVar6 = *(int *)(param_2 + 0x4c);
  }
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar5 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar16 = 0;
    iVar7 = 0;
    while( true ) {
      iVar9 = iVar7 + 0xa8;
      iVar8 = iVar6 + iVar7;
      iVar6 = iVar6 + iVar9;
      fVar13 = *(float *)(iVar6 + 0x38);
      fVar20 = *(float *)(iVar6 + 0x34);
      iVar16 = iVar16 + 1;
      *(float *)(iVar8 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar20 - *(float *)(iVar8 + 0x34);
      *(float *)(iVar8 + 0x88) = fVar13 - *(float *)(iVar8 + 0x38);
      uVar3 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar7 = *(int *)(param_2 + 0x50) + iVar7;
      iVar5 = *(int *)(param_2 + 0x50) + iVar9;
      fVar13 = *(float *)(iVar5 + 0x38);
      fVar20 = *(float *)(iVar5 + 0x34);
      fVar11 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar20 - *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar8 + 0x8c) = uVar3;
      *(float *)(iVar7 + 0x88) = fVar13 - fVar11;
      uVar3 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar5 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar7 + 0x8c) = uVar3;
      if (iVar5 <= iVar16) break;
      iVar6 = *(int *)(param_2 + 0x4c);
      iVar7 = iVar9;
    }
    iVar6 = *(int *)(param_2 + 0x4c);
  }
  uVar3 = DAT_00057080;
  fVar20 = DAT_0005707c;
  iVar7 = *(int *)(param_2 + 0x50) + iVar5 * 0xa8;
  iVar6 = iVar6 + iVar5 * 0xa8;
  *(float *)(iVar6 + 0x8c) = DAT_0005707c;
  *(float *)(iVar6 + 0x88) = fVar20;
  *(undefined4 *)(iVar6 + 0x84) = uVar3;
  *(undefined4 *)(iVar6 + 0x80) = uVar3;
  *(float *)(iVar7 + 0x8c) = fVar20;
  *(undefined4 *)(iVar7 + 0x80) = uVar3;
  *(float *)(iVar7 + 0x88) = fVar20;
  *(undefined4 *)(iVar7 + 0x84) = uVar3;
  CalcLengthZ((cRPath *)param_2);
  return;
}
