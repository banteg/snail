/*
 * mangled: _ZN6cRPath6BuildPEififfiPcS0_
 * demangled: cRPath::BuildP(int, float, int, float, float, int, char*, char*)
 * address: 00053c04
 * size: 1264
 */

/* cRPath::BuildP(int, float, int, float, float, int, char*, char*) */

void cRPath::BuildP(int param_1,float param_2,int param_3,float param_4,float param_5,int param_6,
                   char *param_7,char *param_8)

{
  float fVar1;
  float fVar2;
  tVector *ptVar3;
  undefined4 uVar4;
  tMatrix *ptVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint in_fpscr;
  uint uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  float fVar21;
  float in_stack_00000004;
  int in_stack_00000008;

  *(undefined4 *)(param_1 + 0x44) = DAT_00054000;
  fVar21 = DAT_00053fe8;
  *(char **)(param_1 + 0x48) = param_7;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(int *)(param_1 + 0x2c) = param_3 + 0x29;
  iVar10 = 0xa8;
  *(undefined1 *)(param_1 + 0x30) = 0;
  uVar4 = DAT_00054000;
  *(int *)(param_1 + 0x38) = in_stack_00000008 + 2;
  fVar17 = DAT_00053fec;
  iVar11 = 0;
  fVar21 = (in_stack_00000004 - (float)param_8) * fVar21;
  iVar12 = (in_stack_00000008 + 1) * 0xa8;
  uVar18 = VectorSignedToFloat(in_stack_00000008 + 2,(byte)(in_fpscr >> 0x16) & 3);
  uVar13 = in_fpscr & 0xfffffff | (uint)(fVar21 < 0.0) << 0x1f;
  *(undefined4 *)(param_1 + 0x40) = uVar18;
  if (SUB41(uVar13 >> 0x1f,0)) {
    fVar21 = (in_stack_00000004 - (float)param_8) * DAT_00053ff0;
  }
  GetNodes((cRPath *)param_1);
  ptVar5 = *(tMatrix **)(param_1 + 0x4c);
  *(char **)(ptVar5 + 0x90) = param_8;
  *(undefined4 *)(ptVar5 + 0x9c) = uVar4;
  uVar18 = DAT_00054004;
  *(undefined4 *)(ptVar5 + 0x98) = DAT_00054004;
  *(undefined4 *)(ptVar5 + 0x94) = uVar18;
  *(undefined4 *)(ptVar5 + 0xa0) = uVar18;
  *(undefined1 *)(param_1 + 0x84) = 0;
  uVar19 = VectorSignedToFloat(in_stack_00000008 + 1,(byte)(uVar13 >> 0x16) & 3);
  tMatrix::Identity(ptVar5);
  iVar6 = *(int *)(param_1 + 0x4c);
  *(undefined4 *)(iVar6 + 0x38) = uVar18;
  *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
  *(undefined4 *)(iVar6 + 0x34) = uVar18;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x50));
  iVar6 = *(int *)(param_1 + 0x50);
  ptVar5 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar12);
  *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar6 + 0x38) = uVar18;
  *(float *)(iVar6 + 0x34) = fVar17;
  *(undefined4 *)(ptVar5 + 0x98) = uVar18;
  *(undefined4 *)(ptVar5 + 0x94) = uVar18;
  *(undefined4 *)(ptVar5 + 0xa0) = uVar18;
  *(undefined4 *)(ptVar5 + 0x9c) = uVar4;
  *(float *)(ptVar5 + 0x90) = in_stack_00000004;
  tMatrix::Identity(ptVar5);
  iVar6 = *(int *)(param_1 + 0x50);
  iVar7 = *(int *)(param_1 + 0x4c) + iVar12;
  *(undefined4 *)(iVar7 + 0x38) = uVar19;
  *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
  *(undefined4 *)(iVar7 + 0x34) = uVar18;
  fVar14 = (float)tMatrix::Identity((tMatrix *)(iVar6 + iVar12));
  iVar7 = *(int *)(param_1 + 0x4c);
  iVar6 = *(int *)(param_1 + 0x50) + iVar12;
  *(undefined4 *)(iVar6 + 0x38) = uVar19;
  *(float *)(iVar6 + 0x34) = fVar17;
  *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar7 + iVar12 + 0x90);
  fVar2 = DAT_00053ff8;
  fVar1 = DAT_00053fe8;
  if (0 < in_stack_00000008) {
    iVar6 = 1;
    VectorSignedToFloat(in_stack_00000008,(byte)(uVar13 >> 0x16) & 3);
    iVar12 = 0;
    while( true ) {
      VectorSignedToFloat(iVar12,(byte)(uVar13 >> 0x16) & 3);
      iVar9 = *(int *)(param_1 + 0x2c);
      if (iVar9 == 0x2a) {
        fVar14 = (float)Cos(fVar14);
        iVar9 = iVar7 + iVar10;
        iVar7 = *(int *)(param_1 + 0x4c);
        *(float *)(iVar9 + 0x90) = ((fVar2 + -fVar21 * fVar14) - fVar21) + fVar1;
      }
      else if (iVar9 == 0x2b) {
        fVar14 = (float)Sin(fVar14);
        iVar9 = iVar7 + iVar10;
        iVar7 = *(int *)(param_1 + 0x4c);
        *(float *)(iVar9 + 0x90) = fVar21 + fVar21 * fVar14 + fVar1;
      }
      else if (iVar9 == 0x29) {
        fVar14 = (float)Sin(fVar14);
        iVar9 = iVar7 + iVar10;
        iVar7 = *(int *)(param_1 + 0x4c);
        *(float *)(iVar9 + 0x90) = (fVar21 * fVar14 - fVar21) + fVar1;
      }
      uVar20 = VectorSignedToFloat(iVar6,(byte)(uVar13 >> 0x16) & 3);
      ptVar5 = (tMatrix *)(iVar7 + iVar10);
      *(undefined4 *)(ptVar5 + 0x98) = uVar18;
      *(undefined4 *)(ptVar5 + 0x94) = uVar18;
      *(undefined4 *)(ptVar5 + 0xa0) = uVar18;
      *(undefined4 *)(ptVar5 + 0x9c) = uVar4;
      tMatrix::Identity(ptVar5);
      iVar7 = *(int *)(param_1 + 0x50);
      iVar9 = *(int *)(param_1 + 0x4c) + iVar10;
      *(undefined4 *)(iVar9 + 0x34) = uVar18;
      *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
      *(undefined4 *)(iVar9 + 0x38) = uVar20;
      tMatrix::Identity((tMatrix *)(iVar7 + iVar10));
      iVar8 = *(int *)(param_1 + 0x4c);
      iVar9 = iVar8 + iVar10;
      fVar14 = *(float *)(iVar9 + 0x34);
      iVar7 = *(int *)(param_1 + 0x50) + iVar10;
      uVar19 = *(undefined4 *)(iVar9 + 0x90);
      *(undefined4 *)(iVar7 + 0x38) = uVar20;
      *(undefined4 *)(iVar7 + 0x30) = uVar19;
      *(float *)(iVar7 + 0x34) = fVar14 + fVar17;
      if (iVar12 < 1) {
        tMatrix::RotIdentity((tMatrix *)(iVar8 + iVar11));
        fVar14 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar11));
      }
      else {
        iVar8 = iVar8 + iVar11;
        fVar16 = *(float *)(iVar9 + 0x38);
        fVar14 = *(float *)(iVar9 + 0x34);
        fVar15 = *(float *)(iVar9 + 0x30);
        *(undefined4 *)(iVar8 + 0x18) = uVar18;
        *(undefined4 *)(iVar8 + 0x14) = uVar4;
        *(undefined4 *)(iVar8 + 0x10) = uVar18;
        *(float *)(iVar8 + 0x24) = fVar14 - *(float *)(iVar8 + 0x34);
        *(float *)(iVar8 + 0x20) = fVar15 - *(float *)(iVar8 + 0x30);
        *(float *)(iVar8 + 0x28) = fVar16 - *(float *)(iVar8 + 0x38);
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar3 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar11);
        tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
        iVar7 = *(int *)(param_1 + 0x50) + iVar10;
        iVar9 = *(int *)(param_1 + 0x50) + iVar11;
        fVar16 = *(float *)(iVar7 + 0x38);
        fVar14 = *(float *)(iVar7 + 0x34);
        fVar15 = *(float *)(iVar7 + 0x30);
        *(undefined4 *)(iVar9 + 0x18) = uVar18;
        *(undefined4 *)(iVar9 + 0x14) = uVar4;
        *(undefined4 *)(iVar9 + 0x10) = uVar18;
        *(float *)(iVar9 + 0x20) = fVar15 - *(float *)(iVar9 + 0x30);
        *(float *)(iVar9 + 0x24) = fVar14 - *(float *)(iVar9 + 0x34);
        *(float *)(iVar9 + 0x28) = fVar16 - *(float *)(iVar9 + 0x38);
        tVector::Normalize((tVector *)(iVar9 + 0x20));
        ptVar3 = (tVector *)(*(int *)(param_1 + 0x50) + iVar11);
        fVar14 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
      }
      if (in_stack_00000008 <= iVar6) break;
      iVar6 = iVar6 + 1;
      iVar12 = iVar12 + 1;
      iVar11 = iVar11 + 0xa8;
      iVar10 = iVar10 + 0xa8;
      iVar7 = *(int *)(param_1 + 0x4c);
    }
    iVar7 = *(int *)(param_1 + 0x4c);
  }
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar10 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar12 = 0;
    iVar11 = 0;
    while( true ) {
      iVar9 = iVar11 + 0xa8;
      iVar6 = iVar7 + iVar11;
      iVar7 = iVar7 + iVar9;
      fVar17 = *(float *)(iVar7 + 0x38);
      fVar21 = *(float *)(iVar7 + 0x34);
      iVar12 = iVar12 + 1;
      *(float *)(iVar6 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar21 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x88) = fVar17 - *(float *)(iVar6 + 0x38);
      uVar4 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar11 = *(int *)(param_1 + 0x50) + iVar11;
      iVar10 = *(int *)(param_1 + 0x50) + iVar9;
      fVar17 = *(float *)(iVar10 + 0x38);
      fVar21 = *(float *)(iVar10 + 0x34);
      fVar14 = *(float *)(iVar11 + 0x38);
      *(float *)(iVar11 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar21 - *(float *)(iVar11 + 0x34);
      *(undefined4 *)(iVar6 + 0x8c) = uVar4;
      *(float *)(iVar11 + 0x88) = fVar17 - fVar14;
      uVar4 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar10 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar11 + 0x8c) = uVar4;
      if (iVar10 <= iVar12) break;
      iVar7 = *(int *)(param_1 + 0x4c);
      iVar11 = iVar9;
    }
    iVar7 = *(int *)(param_1 + 0x4c);
  }
  uVar18 = DAT_00054004;
  uVar4 = DAT_00054000;
  iVar11 = *(int *)(param_1 + 0x50) + iVar10 * 0xa8;
  iVar7 = iVar7 + iVar10 * 0xa8;
  *(undefined4 *)(iVar7 + 0x8c) = DAT_00054000;
  *(undefined4 *)(iVar7 + 0x88) = uVar4;
  *(undefined4 *)(iVar7 + 0x84) = uVar18;
  *(undefined4 *)(iVar7 + 0x80) = uVar18;
  *(undefined4 *)(iVar11 + 0x8c) = uVar4;
  *(undefined4 *)(iVar11 + 0x80) = uVar18;
  *(undefined4 *)(iVar11 + 0x88) = uVar4;
  *(undefined4 *)(iVar11 + 0x84) = uVar18;
  CalcLengthZ((cRPath *)param_1);
  return;
}
